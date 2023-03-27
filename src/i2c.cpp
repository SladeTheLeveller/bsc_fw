// Copyright (c) 2022 Tobias Himmler
// 
// This software is released under the MIT License.
// https://opensource.org/licenses/MIT

#include "Wire.h"
#include "Wire.h"
#include "defines.h"
#include "log.h"
#include "WebSettings.h"
#include "Canbus.h"
#include "Alarmrules.h"
#include "BmsData.h"

static const char *TAG = "I2C";

//TwoWire I2C = TwoWire(0);

struct  bmsData_s *p_lBmsData;
struct  inverterData_s *p_lInverterData;
bool    bo_mDisplayEnabled;
bool    bo_mSlaveEnabled[I2C_CNT_SLAVES];
uint8_t u8_mMasterSlaveId;

//Slaves
uint8_t u8_mI2cRxBuf[4];
boolean bo_mI2cRxOk=false;
SemaphoreHandle_t mutexI2cRx = NULL;


void isI2CdeviceConn();
void displaySendData_bms();  
void i2cSendData(uint8_t i2cAdr, uint8_t data1, uint8_t data2, uint8_t data3, const void *dataAdr, uint8_t dataLen);
void getBscSlaveData(uint8_t u8_slaveNr);
void i2cSendDataToMaster();


/*
 * Slave
 */
void onRequest()
{
  i2cSendDataToMaster();

  #if 0
  if(u8_mI2cRxBuf[0]==BSC_GET_SLAVE_DATA)
  {
    u8_mI2cRxBuf[0]=0;

    uint8_t u8_bmsNr = u8_mI2cRxBuf[2];
    switch(u8_mI2cRxBuf[1])
    {
      case BMS_CELL_VOLTAGE:
        Wire.write((uint8_t*)&p_lBmsData->bmsCellVoltage[u8_bmsNr], 48);
        break;
      case BMS_TOTAL_VOLTAGE:
        Wire.write((uint8_t*)&p_lBmsData->bmsTotalVoltage[u8_bmsNr], 4);
        break;
      case BMS_MAX_CELL_DIFFERENCE_VOLTAGE:
        Wire.write((uint8_t*)&p_lBmsData->bmsMaxCellDifferenceVoltage[u8_bmsNr], 2);
        break;
      case BMS_AVG_VOLTAGE:
        Wire.write((uint8_t*)&p_lBmsData->bmsAvgVoltage[u8_bmsNr], 2);
        break;
      case BMS_TOTAL_CURRENT:
        Wire.write((uint8_t*)&p_lBmsData->bmsTotalCurrent[u8_bmsNr], 4);
        break;
      case BMS_MAX_CELL_VOLTAGE:
        Wire.write((uint8_t*)&p_lBmsData->bmsMaxCellVoltage[u8_bmsNr], 2);
        break;
      case BMS_MIN_CELL_VOLTAGE:
        Wire.write((uint8_t*)&p_lBmsData->bmsMinCellVoltage[u8_bmsNr], 2);
        break;
      case BMS_MAX_VOLTAGE_CELL_NUMBER:
        Wire.write((uint8_t*)&p_lBmsData->bmsMaxVoltageCellNumber[u8_bmsNr], 1);
        break;
      case BMS_MIN_VOLTAGE_CELL_NUMBER:
        Wire.write((uint8_t*)&p_lBmsData->bmsMinVoltageCellNumber[u8_bmsNr], 1);
        break;
      case BMS_IS_BALANCING_ACTIVE:
        Wire.write((uint8_t*)&p_lBmsData->bmsIsBalancingActive[u8_bmsNr], 1);
        break;
      case BMS_BALANCING_CURRENT:
        Wire.write((uint8_t*)&p_lBmsData->bmsBalancingCurrent[u8_bmsNr], 4);
        break;
      case BMS_TEMPERATURE:
        Wire.write((uint8_t*)&p_lBmsData->bmsTempature[u8_bmsNr], 12);
        break;
      case BMS_CHARGE_PERCENT:
        Wire.write((uint8_t*)&p_lBmsData->bmsChargePercentage[u8_bmsNr], 1);
        break;
      case BMS_ERRORS:
        Wire.write((uint8_t*)&p_lBmsData->bmsErrors[u8_bmsNr], 4);
        break;
      case BMS_LAST_DATA_MILLIS:
        if(p_lBmsData->bmsLastDataMillis[u8_bmsNr]+5000>millis()) Wire.write(true);
        else Wire.write(false);
        break;

      default:
        break;
    }
  }
  #endif
}


void onReceive(int len)
{
  uint8_t u8_lRxCnt=0;
  if(len<=4)
  {    
    while(Wire.available())
    {
      u8_mI2cRxBuf[u8_lRxCnt] = Wire.read();
      u8_lRxCnt++;
    }
  }
}


/*
 * Allgemein
 */
void i2cInit()
{
  mutexI2cRx = xSemaphoreCreateMutex();

  for(uint8_t i=0; i<I2C_CNT_SLAVES; i++)
  {
    bo_mSlaveEnabled[i]=false;
  }

  p_lBmsData = getBmsData();
  p_lInverterData = getInverterData();
  
  u8_mMasterSlaveId = WebSettings::getInt(ID_PARAM_MASTER_SLAVE_TYP,0,0,0);

  if(u8_mMasterSlaveId==ID_I2C_MASTER) //Master
  {
    bool i2cBegin = Wire.begin(I2C_SDA_PIN, I2C_SCL_PIN, I2C_FREQUENCY);
    ESP_LOGD(TAG,"Master begin=%d",i2cBegin);
    isI2CdeviceConn();
  }
  else //Slave
  {
    Wire.onReceive(onReceive);
    Wire.onRequest(onRequest);
    if(Wire.begin(u8_mMasterSlaveId,I2C_SDA_PIN, I2C_SCL_PIN, I2C_FREQUENCY))
    {
      ESP_LOGD(TAG,"Slave: Adr=%i",u8_mMasterSlaveId);
    }
  }
}

void isI2CdeviceConn()
{
  uint8_t u8_lErr;
  uint8_t txBuf[1];
  txBuf[0]=0;

  //Display
  Wire.beginTransmission(I2C_DEV_ADDR_DISPLAY);
  Wire.write(txBuf,1);
  u8_lErr = Wire.endTransmission();
  if (u8_lErr == 0)
  {
    bo_mDisplayEnabled = true;
    ESP_LOGI(TAG,"Display found");
  }
  else
  {
    bo_mDisplayEnabled = false;
    ESP_LOGI(TAG,"Display not found (%i)",u8_lErr);
  }   

  //Slaves
  for(uint8_t i=0;i<I2C_CNT_SLAVES;i++)
  {
    uint8_t u8_slaveAdr=I2C_DEV_ADDR_SLAVE1;
    if(i==0)u8_slaveAdr=I2C_DEV_ADDR_SLAVE1;
    else if(i==1)u8_slaveAdr=I2C_DEV_ADDR_SLAVE2;

    Wire.beginTransmission(u8_slaveAdr);
    Wire.write(txBuf,1);
    u8_lErr = Wire.endTransmission();
    if (u8_lErr == 0)
    {
      bo_mSlaveEnabled[i] = true;
      ESP_LOGI(TAG,"Slave %i (Adr=%i) found",i,u8_slaveAdr);
    }
    else
    {
      bo_mSlaveEnabled[i] = false;
      ESP_LOGI(TAG,"Slave %i (Adr=%i) not found (%i)",i,u8_slaveAdr,u8_lErr);
    }  
  }
  
}


void i2cCyclicRun()
{
  if(u8_mMasterSlaveId==ID_I2C_MASTER) 
  {
    //Display
    if(bo_mDisplayEnabled)
    {
      displaySendData_bms();
    } 
    
    //Slaves
    for(uint8_t i=0; i<I2C_CNT_SLAVES; i++)
    {
      if(bo_mSlaveEnabled[i]) getBscSlaveData(i);
    }
  }
}


void i2cSendData(uint8_t i2cAdr, uint8_t data1, uint8_t data2, uint8_t data3, const void *dataAdr, uint8_t dataLen)
{
  uint8_t   txBuf[104];
  txBuf[0]=data1;
  txBuf[1]=data2;
  txBuf[2]=data3; //z.B. Nr. des BMS
  txBuf[3]=0x00;  //Reserve (evtl. CRC8)

  if(data1==BMS_DATA){bmsDataSemaphoreTake();}
  else if(data1==INVERTER_DATA){inverterDataSemaphoreTake();}

  if(dataLen>0) memcpy(&txBuf[TXBUFF_OFFSET], dataAdr, dataLen);

  if(data1==BMS_DATA){bmsDataSemaphoreGive();}
  else if(data1==INVERTER_DATA){inverterDataSemaphoreGive();}

  Wire.beginTransmission(i2cAdr);
  uint8_t quant = Wire.write(txBuf,TXBUFF_OFFSET+dataLen);
  uint8_t error = Wire.endTransmission();

  //vTaskDelay(pdMS_TO_TICKS(10));
}


void i2cSendData(uint8_t i2cAdr, uint8_t data1, uint8_t data2, uint8_t data3, String data, uint8_t dataLen)
{
  i2cSendData(i2cAdr, data1, data2, data3, data.c_str(), dataLen);
}


//Anfordern der Daten vom Slave
void getBscSlaveData(uint8_t u8_slaveNr)
{
  uint8_t u8_slaveAdr=I2C_DEV_ADDR_SLAVE1;
  if(u8_slaveNr==0)u8_slaveAdr=I2C_DEV_ADDR_SLAVE1;
  else if(u8_slaveNr==1)u8_slaveAdr=I2C_DEV_ADDR_SLAVE2;

  uint8_t u8_lBytesReceived=0;
  
  for(uint8_t u8_lBmsNr=BMSDATA_FIRST_DEV_SERIAL;u8_lBmsNr<BMSDATA_LAST_DEV_SERIAL+1;u8_lBmsNr++)
  {
    for(uint8_t u8_BmsDataTyp=(uint8_t)BMS_CELL_VOLTAGE; u8_BmsDataTyp<(uint8_t)BMS_LAST_DATA_MILLIS+1; u8_BmsDataTyp++)
    {
      //vTaskDelay(pdMS_TO_TICKS(10));
      Wire.beginTransmission(u8_slaveAdr);
      Wire.flush();
      Wire.write((uint8_t)BSC_GET_SLAVE_DATA);
      Wire.write(u8_BmsDataTyp);
      Wire.write(2); //u8_lBmsNr
      Wire.write(0);
      Wire.endTransmission();

      u8_lBytesReceived = Wire.requestFrom(u8_slaveAdr, (uint8_t)50); //len: getBmsDataBytes(u8_BmsDataTyp)+2
      if(u8_lBytesReceived>0) 
      {
        uint8_t u8_lBmsNrNew, u8_BmsDataTypRet;
        //if(u8_slaveNr==0)u8_lBmsNrNew=BMSDATA_FIRST_DEV_SLAVE1+u8_lBmsNr-BMSDATA_FIRST_DEV_SERIAL;
        //else if(u8_slaveNr==1)u8_lBmsNrNew=BMSDATA_FIRST_DEV_SLAVE2+u8_lBmsNr-BMSDATA_FIRST_DEV_SERIAL;

        uint8_t rxBuf[u8_lBytesReceived];
        Wire.readBytes(rxBuf, u8_lBytesReceived);
        
        u8_BmsDataTypRet=rxBuf[0];
        //u8_lBmsNrNew=rxBuf[1];
        if(u8_slaveNr==0)u8_lBmsNrNew=BMSDATA_FIRST_DEV_SLAVE1+rxBuf[1]-BMSDATA_FIRST_DEV_SERIAL;
        else if(u8_slaveNr==1)u8_lBmsNrNew=BMSDATA_FIRST_DEV_SLAVE2+rxBuf[1]-BMSDATA_FIRST_DEV_SERIAL;
        
        u8_lBmsNrNew=BMSDATA_FIRST_DEV_SLAVE1; //zum Test

        switch(u8_BmsDataTypRet)
        {
          case BMS_CELL_VOLTAGE:
            memcpy(&p_lBmsData->bmsCellVoltage[u8_lBmsNrNew], &rxBuf[2], 48);
            break;
          case BMS_TOTAL_VOLTAGE:
            memcpy(&p_lBmsData->bmsTotalVoltage[u8_lBmsNrNew], &rxBuf[2], 4);
            break;
          case BMS_MAX_CELL_DIFFERENCE_VOLTAGE:
            memcpy(&p_lBmsData->bmsMaxCellDifferenceVoltage[u8_lBmsNrNew], &rxBuf[2], 2);
            break;
          case BMS_AVG_VOLTAGE:
            memcpy(&p_lBmsData->bmsAvgVoltage[u8_lBmsNrNew], &rxBuf[2], 2);
            break;
          case BMS_TOTAL_CURRENT:
            memcpy(&p_lBmsData->bmsTotalCurrent[u8_lBmsNrNew], &rxBuf[2], 2);
            break;
          case BMS_MAX_CELL_VOLTAGE:
            memcpy(&p_lBmsData->bmsMaxCellVoltage[u8_lBmsNrNew], &rxBuf[2], 2);
            break;
          case BMS_MIN_CELL_VOLTAGE:
            memcpy(&p_lBmsData->bmsMinCellVoltage[u8_lBmsNrNew], &rxBuf[2], 2);
            break;
          case BMS_MAX_VOLTAGE_CELL_NUMBER:
            memcpy(&p_lBmsData->bmsMaxVoltageCellNumber[u8_lBmsNrNew], &rxBuf[2], 1);
            break;
          case BMS_MIN_VOLTAGE_CELL_NUMBER:
            memcpy(&p_lBmsData->bmsMinVoltageCellNumber[u8_lBmsNrNew], &rxBuf[2], 1);
            break;
          case BMS_IS_BALANCING_ACTIVE:
            memcpy(&p_lBmsData->bmsIsBalancingActive[u8_lBmsNrNew], &rxBuf[2], 1);
            break;
          case BMS_BALANCING_CURRENT:
            memcpy(&p_lBmsData->bmsBalancingCurrent[u8_lBmsNrNew], &rxBuf[2], 4);
            break;
          case BMS_TEMPERATURE:
            memcpy(&p_lBmsData->bmsTempature[u8_lBmsNrNew], &rxBuf[2], 12);
            break;
          case BMS_CHARGE_PERCENT:
            memcpy(&p_lBmsData->bmsChargePercentage[u8_lBmsNrNew], &rxBuf[2], 1);
            break;
          case BMS_ERRORS:
            memcpy(&p_lBmsData->bmsErrors[u8_lBmsNrNew], &rxBuf[2], 4);
            break;
          case BMS_LAST_DATA_MILLIS:
            if(rxBuf[2]==true) p_lBmsData->bmsLastDataMillis[u8_lBmsNrNew]=millis();
            //memcpy(&p_lBmsData->bmsLastDataMillis[u8_lBmsNrNew], &rxBuf[2], 4);
            break;
          default:
            break;
        }
      }
    }
  }
}



/******************************************************
 * Slave
 ******************************************************/
void i2cSendDataToMaster()
{
  Wire.write(u8_mI2cRxBuf[1]);
  Wire.write(u8_mI2cRxBuf[2]);

  if(u8_mI2cRxBuf[0]==BSC_GET_SLAVE_DATA)
  {
    u8_mI2cRxBuf[0]=0;

    uint8_t u8_bmsNr = u8_mI2cRxBuf[2];
    switch(u8_mI2cRxBuf[1])
    {
      case BMS_CELL_VOLTAGE:
        Wire.write((uint8_t*)&p_lBmsData->bmsCellVoltage[u8_bmsNr], 48);
        break;
      case BMS_TOTAL_VOLTAGE:
        Wire.write((uint8_t*)&p_lBmsData->bmsTotalVoltage[u8_bmsNr], 4);
        break;
      case BMS_MAX_CELL_DIFFERENCE_VOLTAGE:
        Wire.write((uint8_t*)&p_lBmsData->bmsMaxCellDifferenceVoltage[u8_bmsNr], 2);
        break;
      case BMS_AVG_VOLTAGE:
        Wire.write((uint8_t*)&p_lBmsData->bmsAvgVoltage[u8_bmsNr], 2);
        break;
      case BMS_TOTAL_CURRENT:
        Wire.write((uint8_t*)&p_lBmsData->bmsTotalCurrent[u8_bmsNr], 4);
        break;
      case BMS_MAX_CELL_VOLTAGE:
        Wire.write((uint8_t*)&p_lBmsData->bmsMaxCellVoltage[u8_bmsNr], 2);
        break;
      case BMS_MIN_CELL_VOLTAGE:
        Wire.write((uint8_t*)&p_lBmsData->bmsMinCellVoltage[u8_bmsNr], 2);
        break;
      case BMS_MAX_VOLTAGE_CELL_NUMBER:
        Wire.write((uint8_t*)&p_lBmsData->bmsMaxVoltageCellNumber[u8_bmsNr], 1);
        break;
      case BMS_MIN_VOLTAGE_CELL_NUMBER:
        Wire.write((uint8_t*)&p_lBmsData->bmsMinVoltageCellNumber[u8_bmsNr], 1);
        break;
      case BMS_IS_BALANCING_ACTIVE:
        Wire.write((uint8_t*)&p_lBmsData->bmsIsBalancingActive[u8_bmsNr], 1);
        break;
      case BMS_BALANCING_CURRENT:
        Wire.write((uint8_t*)&p_lBmsData->bmsBalancingCurrent[u8_bmsNr], 4);
        break;
      case BMS_TEMPERATURE:
        Wire.write((uint8_t*)&p_lBmsData->bmsTempature[u8_bmsNr], 12);
        break;
      case BMS_CHARGE_PERCENT:
        Wire.write((uint8_t*)&p_lBmsData->bmsChargePercentage[u8_bmsNr], 1);
        break;
      case BMS_ERRORS:
        Wire.write((uint8_t*)&p_lBmsData->bmsErrors[u8_bmsNr], 4);
        break;
      case BMS_LAST_DATA_MILLIS:
        if(p_lBmsData->bmsLastDataMillis[u8_bmsNr]+5000>millis()) Wire.write(true);
        else Wire.write(false);
        break;

      default:
        break;
    }
  }
}



/******************************************************
 * Display
 ******************************************************/
void displaySendData_bms()
{
  for(uint8_t i=0;i<BT_DEVICES_COUNT-2;i++) //ToDo: Erweitern auf 7 Devices. Dazu muss aber auch das Display angepasst werden
  {
    i2cSendData(I2C_DEV_ADDR_DISPLAY, BMS_DATA, BMS_CELL_VOLTAGE, i, &p_lBmsData->bmsCellVoltage[i], 48);
    i2cSendData(I2C_DEV_ADDR_DISPLAY, BMS_DATA, BMS_TOTAL_VOLTAGE, i, &p_lBmsData->bmsTotalVoltage[i], 4);
    i2cSendData(I2C_DEV_ADDR_DISPLAY, BMS_DATA, BMS_MAX_CELL_DIFFERENCE_VOLTAGE, i, &p_lBmsData->bmsMaxCellDifferenceVoltage[i], 2);
    i2cSendData(I2C_DEV_ADDR_DISPLAY, BMS_DATA, BMS_AVG_VOLTAGE, i, &p_lBmsData->bmsAvgVoltage[i], 2);
    i2cSendData(I2C_DEV_ADDR_DISPLAY, BMS_DATA, BMS_TOTAL_CURRENT, i, &p_lBmsData->bmsTotalCurrent[i], 4);
    i2cSendData(I2C_DEV_ADDR_DISPLAY, BMS_DATA, BMS_MAX_CELL_VOLTAGE, i, &p_lBmsData->bmsMaxCellVoltage[i], 2);
    i2cSendData(I2C_DEV_ADDR_DISPLAY, BMS_DATA, BMS_MIN_CELL_VOLTAGE, i, &p_lBmsData->bmsMinCellVoltage[i], 2);
    i2cSendData(I2C_DEV_ADDR_DISPLAY, BMS_DATA, BMS_MAX_VOLTAGE_CELL_NUMBER, i, &p_lBmsData->bmsMaxVoltageCellNumber[i], 1);
    i2cSendData(I2C_DEV_ADDR_DISPLAY, BMS_DATA, BMS_MIN_VOLTAGE_CELL_NUMBER, i, &p_lBmsData->bmsMinVoltageCellNumber[i], 1);
    i2cSendData(I2C_DEV_ADDR_DISPLAY, BMS_DATA, BMS_IS_BALANCING_ACTIVE, i, &p_lBmsData->bmsIsBalancingActive[i], 1);
    i2cSendData(I2C_DEV_ADDR_DISPLAY, BMS_DATA, BMS_BALANCING_CURRENT, i, &p_lBmsData->bmsBalancingCurrent[i], 4);
    i2cSendData(I2C_DEV_ADDR_DISPLAY, BMS_DATA, BMS_TEMPERATURE, i, &p_lBmsData->bmsTempature[i], 12);
    i2cSendData(I2C_DEV_ADDR_DISPLAY, BMS_DATA, BMS_CHARGE_PERCENT, i, &p_lBmsData->bmsChargePercentage[i], 1);
    i2cSendData(I2C_DEV_ADDR_DISPLAY, BMS_DATA, BMS_ERRORS, i, &p_lBmsData->bmsErrors[i], 4);
  }
  
  uint i=5;
  for(uint8_t n=BT_DEVICES_COUNT;n<(BT_DEVICES_COUNT+3);n++)
  {
    i2cSendData(I2C_DEV_ADDR_DISPLAY, BMS_DATA, BMS_CELL_VOLTAGE, i, &p_lBmsData->bmsCellVoltage[n], 48);
    i2cSendData(I2C_DEV_ADDR_DISPLAY, BMS_DATA, BMS_TOTAL_VOLTAGE, i, &p_lBmsData->bmsTotalVoltage[n], 4);
    i2cSendData(I2C_DEV_ADDR_DISPLAY, BMS_DATA, BMS_MAX_CELL_DIFFERENCE_VOLTAGE, i, &p_lBmsData->bmsMaxCellDifferenceVoltage[n], 2);
    i2cSendData(I2C_DEV_ADDR_DISPLAY, BMS_DATA, BMS_AVG_VOLTAGE, i, &p_lBmsData->bmsAvgVoltage[n], 2);
    i2cSendData(I2C_DEV_ADDR_DISPLAY, BMS_DATA, BMS_TOTAL_CURRENT, i, &p_lBmsData->bmsTotalCurrent[n], 4);
    i2cSendData(I2C_DEV_ADDR_DISPLAY, BMS_DATA, BMS_MAX_CELL_VOLTAGE, i, &p_lBmsData->bmsMaxCellVoltage[n], 2);
    i2cSendData(I2C_DEV_ADDR_DISPLAY, BMS_DATA, BMS_MIN_CELL_VOLTAGE, i, &p_lBmsData->bmsMinCellVoltage[n], 2);
    i2cSendData(I2C_DEV_ADDR_DISPLAY, BMS_DATA, BMS_MAX_VOLTAGE_CELL_NUMBER, i, &p_lBmsData->bmsMaxVoltageCellNumber[n], 1);
    i2cSendData(I2C_DEV_ADDR_DISPLAY, BMS_DATA, BMS_MIN_VOLTAGE_CELL_NUMBER, i, &p_lBmsData->bmsMinVoltageCellNumber[n], 1);
    i2cSendData(I2C_DEV_ADDR_DISPLAY, BMS_DATA, BMS_IS_BALANCING_ACTIVE, i, &p_lBmsData->bmsIsBalancingActive[n], 1);
    i2cSendData(I2C_DEV_ADDR_DISPLAY, BMS_DATA, BMS_BALANCING_CURRENT, i, &p_lBmsData->bmsBalancingCurrent[n], 4);
    i2cSendData(I2C_DEV_ADDR_DISPLAY, BMS_DATA, BMS_TEMPERATURE, i, &p_lBmsData->bmsTempature[n], 12);
    i2cSendData(I2C_DEV_ADDR_DISPLAY, BMS_DATA, BMS_CHARGE_PERCENT, i, &p_lBmsData->bmsChargePercentage[n], 1);
    i2cSendData(I2C_DEV_ADDR_DISPLAY, BMS_DATA, BMS_ERRORS, i, &p_lBmsData->bmsErrors[n], 4);
    i++;
  }

  i2cSendData(I2C_DEV_ADDR_DISPLAY, INVERTER_DATA, INVERTER_VOLTAGE, 0, &p_lInverterData->inverterVoltage, 2);
  i2cSendData(I2C_DEV_ADDR_DISPLAY, INVERTER_DATA, INVERTER_CURRENT, 0, &p_lInverterData->inverterCurrent, 2);
  i2cSendData(I2C_DEV_ADDR_DISPLAY, INVERTER_DATA, INVERTER_SOC, 0, &p_lInverterData->inverterSoc, 2);
  i2cSendData(I2C_DEV_ADDR_DISPLAY, INVERTER_DATA, INVERTER_CHARGE_CURRENT, 0, &p_lInverterData->inverterChargeCurrent, 2);
  i2cSendData(I2C_DEV_ADDR_DISPLAY, INVERTER_DATA, INVERTER_DISCHARG_CURRENT, 0, &p_lInverterData->inverterDischargeCurrent, 2);

  uint16_t u16_lBscAlarms = getAlarm();
  i2cSendData(I2C_DEV_ADDR_DISPLAY, BSC_DATA, BSC_ALARMS, 0, &u16_lBscAlarms, 2);
}
