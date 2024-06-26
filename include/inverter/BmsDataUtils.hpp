// Copyright (c) 2024 Tobias Himmler
//
// This software is released under the MIT License.
// https://opensource.org/licenses/MIT

#pragma once

#include <cstdint>

class BmsDataUtils
{
public:
    BmsDataUtils(); // Konstruktor
    ~BmsDataUtils(); // Dekonstruktor

    static uint8_t getNumberOfBatteryModules(uint8_t u8_mBmsDatasource, uint16_t u16_mBmsDatasourceAdd);
    static uint8_t getNumberOfBatteryModulesCharge(uint8_t u8_mBmsDatasource, uint16_t u16_mBmsDatasourceAdd);
    static uint8_t getNumberOfBatteryModulesDischarge(uint8_t u8_mBmsDatasource, uint16_t u16_mBmsDatasourceAdd);
    static uint16_t getMaxCellSpannungFromBms(uint8_t u8_mBmsDatasource, uint16_t u16_mBmsDatasourceAdd);
    static uint16_t getMaxCellSpannungFromBms(uint8_t u8_mBmsDatasource, uint16_t u16_mBmsDatasourceAdd, uint8_t &BmsNr,uint8_t &CellNr);
    static uint16_t getMinCellSpannungFromBms(uint8_t u8_mBmsDatasource, uint16_t u16_mBmsDatasourceAdd);
    static uint16_t getMinCellSpannungFromBms(uint8_t u8_mBmsDatasource, uint16_t u16_mBmsDatasourceAdd, uint8_t &BmsNr,uint8_t &CellNr);
    static uint16_t getMaxCellDifferenceFromBms(uint8_t u8_mBmsDatasource, uint16_t u16_mBmsDatasourceAdd);
    static float getMinCurrentFromBms(uint8_t u8_mBmsDatasource, uint16_t u16_mBmsDatasourceAdd);

    static void buildBatteryCellText(char *buffer, uint8_t batteryNr, uint8_t cellNr);

private:

};
