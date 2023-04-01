// Copyright (c) 2022 tobias
// 
// This software is released under the MIT License.
// https://opensource.org/licenses/MIT

#include "Arduino.h"
#include "defines.h"
#include "WebSettings.h"

/* ***********************************************************************************
 * Wichtiger Hinweis!
 * params.h nicht manuell bearbeiten! Änderungen immer in der params_py.h vornehmen!
 * Die params.h wird beim Build automatisch erstellt!
 * ***********************************************************************************/



const char paramSystem[] = "["
  /*"{"
    "'label':'Master/Slave',"
    "'type':13,"
  "},"
  "{"
    "'name':111,"
    "'label':'Master/Slave',"
    "'type':9,"
    "'options':["
      "{'v':'0 //Auswahl Master/Slave','l':'Master'},"
      "{'v':'16','l':'Slave 0'},"
      "{'v':'17','l':'Slave 1'}"
    "],"
    "'default':'0'"
  "},"*/

  "{"
    "'label':'WLAN',"
    "'type':13,"
  "},"
  "{"
  "'name':40,"
  "'label':'WLAN SSID',"
  "'type':0,"
  "'default':''"
  "},"
  "{"
  "'name':41,"
  "'label':'WLAN Passwort',"
  "'type':2,"
  "'default':''"
  "},"
  "{"
  "'name':96,"
  "'label':'WLAN connect Timeout',"
  "'type':3,"
  "'unit':'s',"
  "'default':30,"
  "'min':0,"
  "'max':3600,"
  "'help':'Der Timeout gibt an, nach welcher Zeit ein Verbindungsversuch abgebrochen wird und ein Accesspoint erstellt wird.\n"
    "0 deaktiviert den Timeout.'"
  "},"
  "{"
  "'label':'MQTT',"
  "'type':13"
  "},"
  "{"
  "'name':44,"
  "'label':'MQTT enable',"
  "'type':10,"
  "'default':0"
  "},"
  "{"
  "'name':42,"
  "'label':'MQTT Server IP',"
  "'type':0,"
  "'default':''"
  "},"
  "{"
  "'name':43,"
  "'label':'MQTT Server Port',"
  "'type':3,"
  "'default':1883,"
  "'min':1,"
  "'max':10000"
  "},"
  "{"
  "'name':86,"
  "'label':'Username',"
  "'type':0,"
  "'default':''"
  "},"
  "{"
  "'name':87,"
  "'label':'Passwort',"
  "'type':2,"
  "'default':''"
  "},"
  "{"
  "'name':45,"
  "'label':'MQTT Device Name',"
  "'type':0,"
  "'default':'bsc'"
  "},"

  "{"
    "'label':'Triggername',"
    "'type':13,"
  "},"
  "{"
  "'name':117,"
  "'label':'Trigger',"
  "'type':0,"
  "'size':10,"
  "'default':'',"
  "'flash':'1',"
  "'dt':8"
  "}"

  "]";


const char paramBluetooth[] PROGMEM = "["
  "{"
    "'name':3,"
    "'label':'Bluetooth',"
    "'label_entry':'BT Device',"
    "'groupsize':7,"
    "'type':12,"
    "'group':["
    "{"
      "'name':4,"
      "'label':'Bluetooth',"
      "'type':9,"
      "'options':["
        "{'v':'0','l':'nicht belegt'},"
        "{'v':'1','l':'NEEY Balancer 4A'},"
        "{'v':'2','l':'JK-BMS [Test]'},"
        "{'v':'3','l':'JK-BMS (32S) [Test]'}],"
        
      "'default':'0'"
    "},"
    "{"
      "'name':5,"
      "'label':'MAC-Adresse',"
      "'type':0,"
      "'default':''"
    "}]"
  "}"
  "]";
  
 
const char paramSerial[] PROGMEM = "["
  "{"
    "'label':'Serielle Schnitstellen',"
    "'label_entry':'Serial',"
    "'groupsize':3,"
    "'type':12,"
    "'group':["
      "{"
        "'name':1,"
        "'label':'Serial',"
        "'type':9,"
        "'options':["
          "{'v':'0','l':'nicht belegt'},"
          "{'v':'1','l':'JBD BMS'},"
          "{'v':'2','l':'JK-BMS'},"
          "{'v':'3','l':'Seplos-BMS'}],"
        "'default':'0'"
      "}"
    "]"
  "},"
  "{"
    "'label':'Seplos BMS',"
    "'type':13,"
  "},"
  "{"
    "'name':108,"
    "'label':'Abfrage IDs',"
    "'help':'Abgefragt werden alles Seplos von ID 0 bis zur hier eingestellten ID.\n"
      "Die Einstellung betrifft nur das Seplos BMS an der Serial 2.',"
    "'type':3,"
    "'default':0,"
    "'min':0,"
    "'max':2"
  "}"
"]";


const char paramAlarmBms[] PROGMEM = "["
  "{"
    "'name':10,"
    "'label':'BMS Alarmregeln',"
    "'label_entry':'Alarmregel',"
    "'groupsize':10,"
    "'type':12,"
    "'group':["
      "{"
      "'name':9,"
      "'label':'Zu &uuml;berwachendes BMS',"
      "'type':9,"
      "'options':["
        "{'v':'0','l':'Aus'},"
        "{'v':'1','l':'Bluetooth 0'},"
        "{'v':'2','l':'Bluetooth 1'},"
        "{'v':'3','l':'Bluetooth 2'},"
        "{'v':'4','l':'Bluetooth 3'},"
        "{'v':'5','l':'Bluetooth 4'},"
        "{'v':'6','l':'Bluetooth 5'},"
        "{'v':'7','l':'Bluetooth 6'},"
        "{'v':'8','l':'Serial 0'},"
        "{'v':'9','l':'Serial 1'},"
        "{'v':'10','l':'Serial 2'}"
        "],"
      "'default':0"
      "},"
      "{"
        "'label':'Keine Daten vom BMS',"
        "'type':13,"
      "},"
      "{"
      "'name':17,"
      "'label':'Aktion bei Trigger',"
      "'type':9,"
      "'options':["
        "{'v':'0','l':'Aus'},"
        "{'v':'1','l':'Trigger 1','d':122683392},{'v':'2','l':'Trigger 2','d':122683393},{'v':'3','l':'Trigger 3','d':122683394},{'v':'4','l':'Trigger 4','d':122683395},{'v':'5','l':'Trigger 5','d':122683396},{'v':'6','l':'Trigger 6','d':122683397},{'v':'7','l':'Trigger 7','d':122683398},{'v':'8','l':'Trigger 8','d':122683399},{'v':'9','l':'Trigger 9','d':122683400},{'v':'10','l':'Trigger 10','d':122683401}"
        "],"
      "'default':'0'"
      "},"
      "{"
        "'name':12,"
        "'label':'Trigger keine Daten',"
        "'unit':'s',"
        "'type':3,"
        "'default':15,"
        "'min':1,"
        "'max':255"
      "},"
      "{"
        "'label':'Spannungs&uuml;berwachung Zelle Min/Max',"
        "'type':13,"
      "},"
      "{"
      "'name':18,"
      "'label':'Aktion bei Trigger',"
      "'type':9,"
      "'options':["
        "{'v':'0','l':'Aus'},"
        "{'v':'1','l':'Trigger 1','d':122683392},{'v':'2','l':'Trigger 2','d':122683393},{'v':'3','l':'Trigger 3','d':122683394},{'v':'4','l':'Trigger 4','d':122683395},{'v':'5','l':'Trigger 5','d':122683396},{'v':'6','l':'Trigger 6','d':122683397},{'v':'7','l':'Trigger 7','d':122683398},{'v':'8','l':'Trigger 8','d':122683399},{'v':'9','l':'Trigger 9','d':122683400},{'v':'10','l':'Trigger 10','d':122683401}"
        "],"
      "'default':'0'"
      "},"
      "{"
        "'name':14,"
        "'label':'Anzahl Zellen Monitoring',"
        "'type':3,"
        "'default':16,"
        "'min':1,"
        "'max':24"
      "},"
      "{"
        "'name':15,"
        "'label':'Zellspannung Min',"
        "'unit':'mV',"
        "'type':3,"
        "'default':2500,"
        "'min':2000,"
        "'max':5000"
      "},"
      "{"
        "'name':16,"
        "'label':'Zellspannung Max',"
        "'unit':'mV',"
        "'type':3,"
        "'default':3650,"
        "'min':2000,"
        "'max':5000"
      "},"
      /*"{"
        "'name':"+String(ID_PARAM_ALARM_BT_CELL_SPG_MAX_HYSTERESE)+","
        "'label':'Hysterese',"
        "'unit':'mV',"
        "'type':3,"
        "'default':20,"
        "'min':0,"
        "'max':255"
      "},"*/
      "{"
        "'label':'Spannungs&uuml;berwachung Gesamt Min/Max',"
        "'type':13,"
      "},"
      "{"
      "'name':19          //0=AUS; 1-5=Alarm 1-5,"
      "'label':'Aktion bei Trigger',"
      "'type':9,"
      "'options':["
        "{'v':'0','l':'Aus'},"
        "{'v':'1','l':'Trigger 1','d':122683392},{'v':'2','l':'Trigger 2','d':122683393},{'v':'3','l':'Trigger 3','d':122683394},{'v':'4','l':'Trigger 4','d':122683395},{'v':'5','l':'Trigger 5','d':122683396},{'v':'6','l':'Trigger 6','d':122683397},{'v':'7','l':'Trigger 7','d':122683398},{'v':'8','l':'Trigger 8','d':122683399},{'v':'9','l':'Trigger 9','d':122683400},{'v':'10','l':'Trigger 10','d':122683401}"
        "],"
      "'default':'0'"
      "},"
      "{"
        "'name':72,"
        "'label':'Spannung Min',"
        "'unit':'V',"
        "'type':4,"
        "'default':48.0,"
        "'min':0,"
        "'max':60"
      "},"
      "{"
        "'name':73,"
        "'label':'Spannung Max',"
        "'unit':'V',"
        "'type':4,"
        "'default':54.0,"
        "'min':0,"
        "'max':60"
      "}"
    "]"
  "}"
"]";


const char paramAlarmTemp[] PROGMEM = "["
  //Alarm bei Sensorfehler
  "{"
    "'label':'Alarm bei Sensorfehler',"
    "'type':13,"
  "},"
  "{"
    "'name':109,"
    "'label':'Trigger',"
    "'type':9,"
    "'options':["
    "{'v':'0','l':'Aus'},"
    "{'v':'1','l':'Trigger 1','d':122683392},{'v':'2','l':'Trigger 2','d':122683393},{'v':'3','l':'Trigger 3','d':122683394},{'v':'4','l':'Trigger 4','d':122683395},{'v':'5','l':'Trigger 5','d':122683396},{'v':'6','l':'Trigger 6','d':122683397},{'v':'7','l':'Trigger 7','d':122683398},{'v':'8','l':'Trigger 8','d':122683399},{'v':'9','l':'Trigger 9','d':122683400},{'v':'10','l':'Trigger 10','d':122683401}"
    "],"
    "'default':'0'"
  "},"
  "{"
    "'name':110,"
    "'label':'Timeout',"
    "'unit':'s',"
    "'type':3,"
    "'default':'5',"
    "'min':5,"
    "'max':240"
  "},"

  "{"
    "'label':'Temperatur &#220;berwachung',"
    "'type':13,"
  "},"
  "{"
    "'name':20,"
    "'label':'Temperatur &#220;berwachung',"
    "'label_entry':'&#220;berwachung',"
    "'groupsize':10,"
    "'type':12,"
    "'group':["
      "{"
        "'name':21,"
        "'label':'Sensornummer von',"
        "'type':3,"
        "'default':'',"
        "'min':0,"
        "'max':255"
      "},"
      "{"
        "'name':22,"
        "'label':'Sensornummer bis',"
        "'type':3,"
        "'default':'',"
        "'min':0,"
        "'max':255"
      "},"
      "{"
        "'name':27,"
        "'label':'&Uuml;berwachung',"
        "'type':9,"
        "'options':["
          "{'v':'0','l':'nicht belegt'},"
          "{'v':'1','l':'Maximalwert-&Uuml;berschreitung'},"
          "{'v':'2','l':'Maximalwert-&Uuml;berschreitung (Referenz)'},"
          "{'v':'3','l':'Differenzwert-&Uuml;berwachung'}],"
        "'default':'0',"
        "'help':'Maximalwert-&Uuml;berschreitung: Wert1=Maximale Temperatur\n"
          "Maximalwert-&Uuml;berschreitung (Referenz): Wert1=Temperatur Offset'\n"
          "Differenzwert-&Uuml;berwachung: Wert1=Maximal erlaubte Differenz'"
      "},"
      "{"
        "'name':23,"
        "'label':'Referenzsensor',"
        "'type':3,"
        "'default':'',"
        "'min':0,"
        "'max':255"
      "},"
      "{"
        "'name':24,"
        "'label':'Wert 1',"
        "'type':4,"
        "'default':'',"
        "'min':0,"
        "'max':70"
      "},"
      "{"
        "'name':25,"
        "'label':'Wert 2',"
        "'type':4,"
        "'default':'',"
        "'min':0,"
        "'max':70"
      "},"
      "{"
      "'name':26,"
      "'label':'Ausl&ouml;sung',"
      "'type':9,"
      "'options':["
        "{'v':'0','l':'Aus'},"
        "{'v':'1','l':'Trigger 1','d':122683392},{'v':'2','l':'Trigger 2','d':122683393},{'v':'3','l':'Trigger 3','d':122683394},{'v':'4','l':'Trigger 4','d':122683395},{'v':'5','l':'Trigger 5','d':122683396},{'v':'6','l':'Trigger 6','d':122683397},{'v':'7','l':'Trigger 7','d':122683398},{'v':'8','l':'Trigger 8','d':122683399},{'v':'9','l':'Trigger 9','d':122683400},{'v':'10','l':'Trigger 10','d':122683401}"
        "],"
      "'default':'0'"
      "}"
    "]"
  "}"
"]";


//Digitalausgang 1..6
const char paramDigitalOut[] PROGMEM = "["
  "{"
    "'label':'Digitalausg&#228;nge',"
    "'label_entry':'Digitalausgang',"
    "'groupsize':6,"
    "'type':12,"
    "'group':["
      "{"
      "'name':30,"
      "'label':'Ausl&#246;severhalten',"
      "'type':9,"
      "'options':["
        "{'v':'0','l':'Permanent'},"
        "{'v':'1','l':'Impuls'}],"
      "'default':'0'"
      "},"
      "{"
        "'name':31,"
        "'label':'Impulsdauer',"
        "'unit':'ms',"
        "'type':3,"
        "'default':500,"
        "'min':100,"
        "'max':10000"
      "},"
      "{"
        "'name':33,"
        "'label':'Verz&ouml;gerung',"
        "'unit':'s',"
        "'type':3,"
        "'default':0,"
        "'min':0,"
        "'max':254"
      "},"
      "{"
      "'name':32,"
      "'label':'Ausl&#246;sung bei',"
      "'type':9,"
      "'options':["
        "{'v':'0','l':'Aus'},"
        "{'v':'1','l':'Trigger 1','d':122683392},{'v':'2','l':'Trigger 2','d':122683393},{'v':'3','l':'Trigger 3','d':122683394},{'v':'4','l':'Trigger 4','d':122683395},{'v':'5','l':'Trigger 5','d':122683396},{'v':'6','l':'Trigger 6','d':122683397},{'v':'7','l':'Trigger 7','d':122683398},{'v':'8','l':'Trigger 8','d':122683399},{'v':'9','l':'Trigger 9','d':122683400},{'v':'10','l':'Trigger 10','d':122683401}"
        "],"
      "'default':'0'"
      "}"
    "]"
  "}"
"]";


//Digitaleingänge 1..4
const char paramDigitalIn[] PROGMEM = "["
  "{"
    "'label':'Digitaleing&#228;nge',"
    "'label_entry':'Digitaleingang',"
    "'groupsize':4,"
    "'type':12,"
    "'group':["
      "{"
      "'name':34,"
      "'label':'Eingang invertieren',"
      "'type':10,"
      "'default':'0'"
      "},"
      "{"
      "'name':35,"
      "'label':'Weiterleiten an',"
      "'type':9,"
      "'options':["
        "{'v':'0','l':'Aus'},"
        "{'v':'1','l':'Trigger 1','d':122683392},{'v':'2','l':'Trigger 2','d':122683393},{'v':'3','l':'Trigger 3','d':122683394},{'v':'4','l':'Trigger 4','d':122683395},{'v':'5','l':'Trigger 5','d':122683396},{'v':'6','l':'Trigger 6','d':122683397},{'v':'7','l':'Trigger 7','d':122683398},{'v':'8','l':'Trigger 8','d':122683399},{'v':'9','l':'Trigger 9','d':122683400},{'v':'10','l':'Trigger 10','d':122683401}"
        "],"
      "'default':'0'"
      "}"
    "]"
  "}"
"]";


const char paramOnewireAdr[] PROGMEM = "["
  "{"
  "'name':50,"
  "'label':'Onewire enable',"
  "'type':10,"
  "'default':'0'"
  "},"
  "{"
  "'name':51,"
  "'label':'OW Adr.',"
  "'type':0,"
  "'size':64,"
  "'default':''"
  "}"
  "]";


const char paramOnewire2[] PROGMEM = "["
  "{"
    "'label':'Onewire Sensoren',"
    "'label_entry':'Sensor',"
    "'groupsize':64,"
    "'type':12,"
    "'group':["
      "{"
        "'name':52,"
        "'label':'Offset',"
        "'unit':'&deg;C',"
        "'type':4,"
        "'default':0,"
        "'min':-10,"
        "'max':10"
      "}"
    "]"
  "}"
"]";


//BMS to Inverter
const char paramBmsToInverter[] PROGMEM = "["
  "{"
    "'name':60,"
    "'label':'BMS Canbus enable',"
    "'type':10,"
    "'default':'0'"
  "},"
  "{"
    "'name':2,"
    "'label':'Canbus',"
    "'type':9,"
    "'options':["
      "{'v':'0','l':'nicht belegt'},"
      "{'v':'1','l':'Solis RHI'},"
      "{'v':'2','l':'DEYE'},"
      "{'v':'3','l':'VICTRON'}],"
    "'default':'nb'"
  "},"
  "{"
  "'name':61,"
  "'label':'Datenquelle (Master)',"
  "'type':9,"
  "'options':["
    "{'v':'0','l':'Bluetooth Device 0'},"
    "{'v':'1','l':'Bluetooth Device 1'},"
    "{'v':'2','l':'Bluetooth Device 2'},"
    "{'v':'3','l':'Bluetooth Device 3'},"
    "{'v':'4','l':'Bluetooth Device 4'},"
    "{'v':'5','l':'Bluetooth Device 5'},"
    "{'v':'6','l':'Bluetooth Device 6'},"
    "{'v':'7','l':'Serial Device 0'},"
    "{'v':'8','l':'Serial Device 1'},"
    "{'v':'9','l':'Serial Device 2'}],"
  "'default':'0'"
  "},"
  "{"
    "'name':83,"
    "'label':'+ Datenquelle Serial 0',"
    "'type':10,"
    "'default':'0'"
  "},"
  "{"
    "'name':84,"
    "'label':'+ Datenquelle Serial 1',"
    "'type':10,"
    "'default':'0'"
  "},"
  "{"
    "'name':85,"
    "'label':'+ Datenquelle Serial 2',"
    "'type':10,"
    "'default':'0'"
  "},"

  //Multi-BMS Settings
  "{"
    "'label':'Valuehandling Multi-BMS',"
    "'type':13,"
  "},"
  "{"
    "'name':116,"
    "'label':'SoC',"
    "'type':9,"
    "'options':["
      "{'v':'0','l':'AUS'},"
      "{'v':1,'l':'SoC Mittelwert'},"
      "{'v':2,'l':'SoC Maximalwert'}],"
    "'default':'0'"
  "},"
  /*",{"
  "'name':"+String(ID_PARAM_INVERTER_MULTI_BMS_VALUE_HANDLING)+","
  "'label':'Valuehandling Multi-BMS',"
  "'type':11,"
  "'options':["
  "{'v':'0','l':'SoC Mittelwert'},"
  "{'v':'1','l':'Test2'},"
  "{'v':'2','l':'Test3'}],"
  "'default':0"
  "}"*/

  "{"
    "'label':'Basisdaten',"
    "'type':13,"
  "},"
  "{"
    "'name':62,"
    "'label':'Max. Ladespannung',"
    "'unit':'V',"
    "'type':4,"
    "'default':'54.4',"
    "'min':40.0,"
    "'max':58.4"
  "},"
  "{"
    "'name':64,"
    "'label':'Max. Ladestrom',"
    "'unit':'A',"
    "'type':3,"
    "'default':'100',"
    "'min':0,"
    "'max':200"
  "},"
  "{"
    "'name':65,"
    "'label':'Max. Entladestrom',"
    "'unit':'A',"
    "'type':3,"
    "'default':'100',"
    "'min':0,"
    "'max':200"
  "},"
  "{"
    "'name':66,"
    "'label':'Ladeleistung auf 0 bei:',"
    "'type':9,"
    "'options':["
      "{'v':'0','l':'AUS'},"
      "{'v':'1','l':'Trigger 1','d':122683392},{'v':'2','l':'Trigger 2','d':122683393},{'v':'3','l':'Trigger 3','d':122683394},{'v':'4','l':'Trigger 4','d':122683395},{'v':'5','l':'Trigger 5','d':122683396},{'v':'6','l':'Trigger 6','d':122683397},{'v':'7','l':'Trigger 7','d':122683398},{'v':'8','l':'Trigger 8','d':122683399},{'v':'9','l':'Trigger 9','d':122683400},{'v':'10','l':'Trigger 10','d':122683401}"
      "],"
    "'default':'0'"
  "},"
  "{"
    "'name':67,"
    "'label':'Entladeleistung auf 0 bei:',"
    "'type':9,"
    "'options':["
      "{'v':'0','l':'AUS'},"
      "{'v':'1','l':'Trigger 1','d':122683392},{'v':'2','l':'Trigger 2','d':122683393},{'v':'3','l':'Trigger 3','d':122683394},{'v':'4','l':'Trigger 4','d':122683395},{'v':'5','l':'Trigger 5','d':122683396},{'v':'6','l':'Trigger 6','d':122683397},{'v':'7','l':'Trigger 7','d':122683398},{'v':'8','l':'Trigger 8','d':122683399},{'v':'9','l':'Trigger 9','d':122683400},{'v':'10','l':'Trigger 10','d':122683401}"
      "],"
    "'default':'0'"
  "},"
  "{"
    "'name':77,"
    "'label':'SOC auf 100 bei:',"
    "'type':9,"
    "'options':["
      "{'v':'0','l':'AUS'},"
      "{'v':'1','l':'Trigger 1','d':122683392},{'v':'2','l':'Trigger 2','d':122683393},{'v':'3','l':'Trigger 3','d':122683394},{'v':'4','l':'Trigger 4','d':122683395},{'v':'5','l':'Trigger 5','d':122683396},{'v':'6','l':'Trigger 6','d':122683397},{'v':'7','l':'Trigger 7','d':122683398},{'v':'8','l':'Trigger 8','d':122683399},{'v':'9','l':'Trigger 9','d':122683400},{'v':'10','l':'Trigger 10','d':122683401}"
      "],"
    "'default':'0'"
  "},"
  "{"
    "'label':'Batterypack settings',"
    "'label_entry':'BMS Serial',"
    "'groupsize':3,"
    "'type':12,"
    "'group':["
      "{"
        "'name':118,"
        "'label':'Charge current per pack',"
        "'type':3,"
        "'default':280,"
        "'min':0,"
        "'max':500"
      "},"
      "{"
        "'name':119,"
        "'label':'Discharge current per pack',"
        "'type':3,"
        "'default':280,"
        "'min':0,"
        "'max':500"
      "}"
  "]},"

//Alarm über Trigger
  "{"
    "'label':'Alarme (Inverter)',"
    "'type':13,"
  "},"
  "{"
    "'name':112,"
    "'label':'High battery voltage',"
    "'type':9,"
    "'options':["
      "{'v':'0','l':'AUS'},"
      "{'v':'1','l':'Trigger 1','d':122683392},{'v':'2','l':'Trigger 2','d':122683393},{'v':'3','l':'Trigger 3','d':122683394},{'v':'4','l':'Trigger 4','d':122683395},{'v':'5','l':'Trigger 5','d':122683396},{'v':'6','l':'Trigger 6','d':122683397},{'v':'7','l':'Trigger 7','d':122683398},{'v':'8','l':'Trigger 8','d':122683399},{'v':'9','l':'Trigger 9','d':122683400},{'v':'10','l':'Trigger 10','d':122683401}"
      "],"
    "'default':'0'"
  "},"
  "{"
    "'name':113,"
    "'label':'Low battery voltage',"
    "'type':9,"
    "'options':["
      "{'v':'0','l':'AUS'},"
      "{'v':'1','l':'Trigger 1','d':122683392},{'v':'2','l':'Trigger 2','d':122683393},{'v':'3','l':'Trigger 3','d':122683394},{'v':'4','l':'Trigger 4','d':122683395},{'v':'5','l':'Trigger 5','d':122683396},{'v':'6','l':'Trigger 6','d':122683397},{'v':'7','l':'Trigger 7','d':122683398},{'v':'8','l':'Trigger 8','d':122683399},{'v':'9','l':'Trigger 9','d':122683400},{'v':'10','l':'Trigger 10','d':122683401}"
      "],"
    "'default':'0'"
  "},"
  "{"
    "'name':114,"
    "'label':'High Temperature',"
    "'type':9,"
    "'options':["
      "{'v':'0','l':'AUS'},"
      "{'v':'1','l':'Trigger 1','d':122683392},{'v':'2','l':'Trigger 2','d':122683393},{'v':'3','l':'Trigger 3','d':122683394},{'v':'4','l':'Trigger 4','d':122683395},{'v':'5','l':'Trigger 5','d':122683396},{'v':'6','l':'Trigger 6','d':122683397},{'v':'7','l':'Trigger 7','d':122683398},{'v':'8','l':'Trigger 8','d':122683399},{'v':'9','l':'Trigger 9','d':122683400},{'v':'10','l':'Trigger 10','d':122683401}"
      "],"
    "'default':'0'"
  "},"
  "{"
    "'name':115,"
    "'label':'Low Temperature',"
    "'type':9,"
    "'options':["
      "{'v':'0','l':'AUS'},"
      "{'v':'1','l':'Trigger 1','d':122683392},{'v':'2','l':'Trigger 2','d':122683393},{'v':'3','l':'Trigger 3','d':122683394},{'v':'4','l':'Trigger 4','d':122683395},{'v':'5','l':'Trigger 5','d':122683396},{'v':'6','l':'Trigger 6','d':122683397},{'v':'7','l':'Trigger 7','d':122683398},{'v':'8','l':'Trigger 8','d':122683399},{'v':'9','l':'Trigger 9','d':122683400},{'v':'10','l':'Trigger 10','d':122683401}"
      "],"
    "'default':'0'"
  "},"

  "{"
    "'label':'Batterietemperatur',"
    "'type':13,"
  "},"
  "{"
    "'name':97,"
    "'label':'Quelle',"
    "'type':9,"
    "'options':["
      "{'v':'1','l':'BMS'},"
      "{'v':'2','l':'Onewire'}"
      "],"
    "'default':'1'"
  "},"
  "{"
    "'name':98,"
    "'label':'Sensornummer',"
    "'type':3,"
    "'default':'0',"
    "'min':0,"
    "'max':64,"
    "'help':'Mögliche Wert:\nBMS:0-2\nOnewire:0-63'"
  "},"

  "{"
    "'label':'Zell-Spannungsabhängige Drosselung',"
    "'type':13,"
    "'help':'Für die Drosselung wird die h&ouml;chste Zellspannung aller ausgew&auml;hlten BMSen genommen.',"
  "},"
  "{"
    "'name':74,"
    "'label':'Ein/Aus',"
    "'type':10,"
    "'default':'0'"
  "},"
  "{"
    "'name':75,"
    "'label':'Starten bei Zellspg. gr&ouml;ßer',"
    "'help':'Sobald die h&ouml;chste Zellspannung diesen Wert &uuml;bersteigt wird die Drosselung aktiv.',"
    "'unit':'mV',"
    "'type':3,"
    "'default':'3325',"
    "'min':2500,"
    "'max':5000"
  "},"
  "{"
    "'name':76,"
    "'label':'Maximale Zellspannung',"
    "'help':'Sobald die h&ouml;chste Zellspannung diesen Wert &uuml;bersteigt wird nur noch mit dem Mindest-Ladestrom geladen.\n"
      "Hinweis: Der Wert muss gr&ouml;ßer sein als die Zell-Startspannung.',"
    "'unit':'mV',"
    "'type':3,"
    "'default':'3300',"
    "'min':2500,"
    "'max':5000"
  "},"
  "{"
    "'name':78,"
    "'label':'Mindest Ladestrom',"
    "'unit':'A',"
    "'type':3,"
    "'default':'5',"
    "'min':0,"
    "'max':200"
  "},"
  "{"
    "'label':'Ladestrom reduzieren bei Zelldrift',"
    "'type':13,"
  "},"
  "{"
    "'name':68,"
    "'label':'Ein/Aus',"
    "'type':10,"
    "'default':'0'"
  "},"
  "{"
    "'name':71,"
    "'label':'Starten bei Zellspg. gr&ouml;ßer',"
    "'unit':'mV',"
    "'type':3,"
    "'default':'3400',"
    "'min':2500,"
    "'max':5000"
  "},"
  "{"
    "'name':69,"
    "'label':'Starten bei Drift gr&ouml;ßer',"
    "'unit':'mV',"
    "'type':3,"
    "'default':'10',"
    "'min':1,"
    "'max':200"
  "},"
  "{"
    "'name':70,"
    "'label':'Reduzierung pro mV Abweichung',"
    "'unit':'A',"
    "'type':3,"
    "'default':'1',"
    "'min':1,"
    "'max':200"
  "},"

  //Ladestrom reduzieren ab bestimmten SoC
  "{"
    "'label':'Ladesstrom reduzieren - SoC',"
    "'type':13,"
  "},"
  "{"
    "'name':79,"
    "'label':'Ein/Aus',"
    "'type':10,"
    "'default':'0'"
  "},"
  "{"
    "'name':80,"
    "'label':'Reduzierung ab SoC',"
    "'unit':'%',"
    "'type':3,"
    "'default':'98',"
    "'min':1,"
    "'max':99"
  "},"
  "{"
    "'name':81,"
    "'label':'Pro 1% um x A reduzieren',"
    "'unit':'A',"
    "'type':3,"
    "'default':'48',"
    "'min':1,"
    "'max':100"
  "},"  

  //Bei unterschreiten von Zellspannung melde SoC x% 
  "{"
    "'label':'SoC beim Unterschreiten der Zellspannung',"
    "'type':13,"
    "'help':'Wenn die eingestellte Zellspannung für den Ladebeginn unterschritten wird, dann kann durch das senden eines beliebigen SoC an den Wechselrichter ein Nachladen veranlasst werden.\n"
      "Es wird so lange nachgeladen, bis die Zellspannung Ladeende überschritten wird.'"
  "},"
  "{"
    "'name':88,"
    "'label':'Ein/Aus',"
    "'type':10,"
    "'default':'0'"
  "},"
  "{"
    "'name':89,"
    "'label':'Zellspannung Ladebeginn',"
    "'unit':'mV',"
    "'type':3,"
    "'default':'3000',"
    "'min':2500,"
    "'max':4000"
  "},"
  "{"
    "'name':92,"
    "'label':'Zellspannung Ladeende',"
    "'unit':'mV',"
    "'type':3,"
    "'default':'0',"
    "'min':0,"
    "'max':4000,"
    "'help':'Wenn Zellspannung Ladeende 0, dann wird geladen, bis die Zellspannung Ladebeginn wieder überschritten wird.'"
  "},"
  "{"
    "'name':90,"
    "'label':'SoC',"
    "'unit':'%',"
    "'type':3,"
    "'default':'9',"
    "'min':1,"
    "'max':100"
  "},"  
  "{"
    "'name':91,"
    "'label':'Sperrzeit zwischen zwei Nachladungen',"
    "'unit':'s',"
    "'type':3,"
    "'default':'600',"
    "'min':0,"
    "'max':3600"
  "}," 

  /* Wenn eine Zelle z.B. >3.4V ist und das Delta zwischen größter und kleinster größer als z.B. 5mV ist, 
  dann Ladespannung reduzieren. */
  "{"
    "'label':'Dynamische Ladespannungsbegrenzung (Beta!)',"
    "'type':13,"
    "'help':'Sobald die Spannung einer Zelle und das Delta zwischen der niedrigsten und der höchsten Zellenspannung größer als eingestellt werden, "
      "wird die Ladespannung dynamisch angepasst, um die maximale Ladeleistung zu erreichen, ohne dass die Zellen weiter auseinander driften.'"
  "},"
  "{"
    "'name':93,"
    "'label':'Ein/Aus',"
    "'type':10,"
    "'default':'0'"
  "},"
  "{"
    "'name':94,"
    "'label':'Start-Zellspannung',"
    "'unit':'mV',"
    "'type':3,"
    "'default':'3400',"
    "'min':2000,"
    "'max':4000"
  "},"
  "{"
    "'name':95,"
    "'label':'Spg.-Delta Min/Max',"
    "'unit':'mV',"
    "'type':3,"
    "'default':'5',"
    "'min':1,"
    "'max':100"
  "},"

//Sperrzeit einstellbar
  "{"
    "'label':'Sonstiges',"
    "'type':13,"
  "},"
  "{"
    "'name':82,"
    "'label':'Sperrzeit wenn Ladestrom 0',"
    "'unit':'s',"
    "'type':3,"
    "'default':'1800',"
    "'min':0,"
    "'max':65000"
  "}"
  "]";


const char paramDeviceNeeyBalancer[] PROGMEM = "["
  "{"
    "'label':'NEEY Active Balancer',"
    "'label_entry':'NEEY',"
    "'groupsize':7,"
    "'type':12,"
    "'group':["
    "{"
      "'name':99,"
      "'label':'Cells',"
      "'type':3,"
      "'default':16,"
      "'min':4,"
      "'max':24,"
      "'flash':'1',"
      "'dt':1"
    "},"
    "{"
      "'name':100,"
      "'label':'Start Voltage',"
      "'type':4,"
      "'default':0.005,"
      "'min':0,"
      "'max':1,"
      "'unit':'V',"
      "'step':'0.001',"
      "'flash':'1',"
      "'dt':7"
    "},"
    "{"
      "'name':101,"
      "'label':'Max. Balance Current',"
      "'type':4,"
      "'default':4.0,"
      "'min':0.1,"
      "'max':4,"
      "'unit':'A',"
      "'step':'0.01',"
      "'flash':'1',"
      "'dt':7"
    "},"
    "{"
      "'name':102,"
      "'label':'Sleep Voltage',"
      "'type':4,"
      "'default':3.30,"
      "'min':1,"
      "'max':5,"
      "'unit':'V',"
      "'step':'0.001',"
      "'flash':'1',"
      "'dt':7"
    "},"
    "{"
      "'name':103,"
      "'label':'Equalization Voltage',"
      "'type':4,"
      "'default':3.31,"
      "'min':1,"
      "'max':5,"
      "'unit':'V',"
      "'step':'0.001',"
      "'flash':'1',"
      "'dt':7"
    "},"
    "{"
      "'name':104,"
      "'label':'Bat. Capacity',"
      "'type':3,"
      "'default':200,"
      "'min':1,"
      "'max':500,"
      "'unit':'Ah',"
      "'flash':'1',"
      "'dt':3"
    "},"
    "{"
      "'name':105,"
      "'label':'BatType',"
      "'type':9,"
      "'options':["
        "{'v':'1','l':'NCM'},"
        "{'v':'2','l':'LFP'},"
        "{'v':'3','l':'LTO'},"
        "{'v':'4','l':'PbAc'}],"
      "'default':'2',"
      "'flash':'1',"
      "'dt':1"
    "},"
    //Buzzer mode (Shut)
    
    "{"
      "'name':107,"
      "'label':'Balancer On',"
      "'type':9,"
      "'options':["
        "{'v':'0','l':'Aus'},"
        "{'v':'110','l':'Ein'},"
        "{'v':'1','l':'Trigger 1','d':122683392},{'v':'2','l':'Trigger 2','d':122683393},{'v':'3','l':'Trigger 3','d':122683394},{'v':'4','l':'Trigger 4','d':122683395},{'v':'5','l':'Trigger 5','d':122683396},{'v':'6','l':'Trigger 6','d':122683397},{'v':'7','l':'Trigger 7','d':122683398},{'v':'8','l':'Trigger 8','d':122683399},{'v':'9','l':'Trigger 9','d':122683400},{'v':'10','l':'Trigger 10','d':122683401}"
        "],"
      "'default':'0',"
      "'flash':'1',"
      "'dt':1"
    "}"
    "]"
  "}"
  "]";
  
