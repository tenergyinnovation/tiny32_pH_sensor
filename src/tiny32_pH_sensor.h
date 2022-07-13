/***********************************************************************
 * File         :     tiny32_pH_sensor.h
 * Description  :     Class for tiny32 library for Gravity: Analog pH Sensor / Meter Kit V2, SKU: SEN0161-V2
 * Author       :     Tenergy Innovation Co., Ltd.
 * Date         :     13 July 2022
 * Rev          :     1.0
 * Rev1.0       :     Original
 * website      :     http://www.tenergyinnovation.co.th
 * Email        :     uten.boonliam@innovation.co.th
 * TEL          :     089-140-7205
 ***********************************************************************/
/*
 * **** Original code from *****
 * @brief Arduino library for Gravity: Analog pH Sensor / Meter Kit V2, SKU: SEN0161-V2
 * @copyright   Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
 * @license     The MIT License (MIT)
 * @author [Jiawei Zhang](jiawei.zhang@dfrobot.com)
 * @version  V1.0
 * @date  2018-11-06
 * @url https://github.com/DFRobot/DFRobot_PH
 */

#ifndef _TINY32_PH_SENSOR_
#define _TINY32_PH_SENSOR_

#if ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#define ReceivedBufferLength 10  //length of the Serial CMD buffer

class tiny32_pH_sensor
{
public:
  tiny32_pH_sensor();
  ~tiny32_pH_sensor();
  /**
   * @fn calibration
   * @brief Calibrate the calibration data
   *
   * @param voltage     : Voltage value
   * @param temperature : Ambient temperature
   * @param cmd         : enterph -> enter the PH calibration mode
   * @n                   calph   -> calibrate with the standard buffer solution, two buffer solutions(4.0 and 7.0) will be automaticlly recognized
   * @n                   exitph  -> save the calibrated parameters and exit from PH calibration mode
   */
  void    calibration(float voltage, float temperature,char* cmd);  //calibration by Serial CMD
  void    calibration(float voltage, float temperature);
  /**
   * @fn readPH
   * @brief Convert voltage to PH with temperature compensation
   * @note voltage to pH value, with temperature compensation
   *
   * @param voltage     : Voltage value
   * @param temperature : Ambient temperature
   * @return The PH value
   */
  float   readPH(float voltage, float temperature); 
  /**
   * @fn begin
   * @brief Initialization The Analog pH Sensor
   */
  void begin();

private:
    float  _phValue;
    float  _acidVoltage;
    float  _neutralVoltage;
    float  _voltage;
    float  _temperature;

    char   _cmdReceivedBuffer[ReceivedBufferLength];  //store the Serial CMD
    byte   _cmdReceivedBufferIndex;

private:
    boolean cmdSerialDataAvailable();
    void    phCalibration(byte mode); // calibration process, wirte key parameters to EEPROM
    byte    cmdParse(const char* cmd);
    byte    cmdParse();
};

#endif
