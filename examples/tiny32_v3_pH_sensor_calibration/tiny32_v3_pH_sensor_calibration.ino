/***********************************************************************
 * Project      :     tiny32_v3_pH_sensor_calibration
 * Description  :     Calibration pH sensor
 *                    https://wiki.dfrobot.com/Gravity__Analog_pH_Sensor_Meter_Kit_V2_SKU_SEN0161-V2
 *                    This calibration modthod we must have two standard buffer solutions of 4.0 and 7.0  
 * Hardware     :     tiny32_v3         
 * Author       :     Tenergy Innovation Co., Ltd.
 * Date         :     04/07/2022
 * Revision     :     1.0
 * Rev1.0       :     Origital
 * website      :     http://www.tenergyinnovation.co.th
 * Email        :     admin@innovation.co.th
 * TEL          :     +66 82-380-3299
 ***********************************************************************/
#include <Arduino.h>
#include <tiny32_v3.h>
#include <SPI.h>
#include <Adafruit_ADS1X15.h>
#include <tiny32_pH_sensor.h>
#include <EEPROM.h>

/**************************************/
/*        define object variable      */
/**************************************/
tiny32_v3 mcu;
Adafruit_ADS1115 ads;  /* Use this for the 16-bit version */
                       /* ADDR pin short to GND default address = 0x48*/ 


/**************************************/
/*        define global variable      */
/**************************************/
float voltage,phValue,temperature = 25;
tiny32_pH_sensor ph;


/**************************************/
/*           define function          */
/**************************************/
float DO_read_sensor(uint16_t channel);


/***********************************************************************
 * FUNCTION:    setup
 * DESCRIPTION: setup process
 * PARAMETERS:  nothing
 * RETURNED:    nothing
 ***********************************************************************/
void setup()
{
    Serial.begin(115200);
    Serial.printf("**** tiny32_v3_pH_sensor_calibration  ****\r\n");
    mcu.library_version();
    
    if (!ads.begin()) {
        Serial.println("Failed to initialize ADS1115 can't interface.");
        mcu.buzzer_beep(4);
        while (1);
    }

    ph.begin();

    mcu.buzzer_beep(2);
    mcu.TickBlueLED(0.5);

}

 /***********************************************************************
 * FUNCTION:    loop
 * DESCRIPTION: loop process
 * PARAMETERS:  nothing
 * RETURNED:    nothing
 ***********************************************************************/
void loop()
{
    int16_t _adc;
    static unsigned long timepoint = millis();
    if(millis()-timepoint>1000U){                  //time interval: 1s
        timepoint = millis();
        //temperature = readTemperature();         // read your temperature sensor to execute temperature compensation
        _adc = ads.readADC_SingleEnded(0); //can change channel here [0-3]
        voltage = ads.computeVolts(_adc)*1000;
        phValue = ph.readPH(voltage,temperature);  // convert voltage to pH with temperature compensation
        Serial.print("temperature:");
        Serial.print(temperature,1);
        Serial.print("^C  pH:");
        Serial.println(phValue,2);
    }
    ph.calibration(voltage,temperature);           // calibration process by Serail CMD
}


 /***********************************************************************
 * FUNCTION:    readTemperature
 * DESCRIPTION: read tempeature sensor
 * PARAMETERS:  nothing
 * RETURNED:    nothing
 ***********************************************************************/
float readTemperature()
{
  //add your code here to get the temperature from your temperature sensor
}
