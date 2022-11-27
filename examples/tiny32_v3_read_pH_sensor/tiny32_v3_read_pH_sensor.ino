/***********************************************************************
 * Project      :     tiny32_v3_read_pH_sensor
 * Description  :     read pH sensor
 *                    https://wiki.dfrobot.com/Gravity__Analog_pH_Sensor_Meter_Kit_V2_SKU_SEN0161-V2
 *                    
 * Hardware     :     tiny32_v3         
 * Author       :     Tenergy Innovation Co., Ltd.
 * Date         :     04/07/2022
 * Revision     :     1.0
 * Rev1.0       :     Origital
 * website      :     http://www.tenergyinnovation.co.th
 * Email        :     admin@innovation.co.th
 * TEL          :     +66 82-308-3299
 ***********************************************************************/
#include <Arduino.h>
#include <tiny32_v3.h>
#include <SPI.h>
#include <Adafruit_ADS1X15.h>
#include <tiny32_pH_sensor.h>
#include <EEPROM.h> /* สามารถเปลี่ยนค่าตำแหน่งที่เก็บค่า calibration */


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
float readTemperature();
float read_pH(int channel);


/***********************************************************************
 * FUNCTION:    setup
 * DESCRIPTION: setup process
 * PARAMETERS:  nothing
 * RETURNED:    nothing
 ***********************************************************************/
void setup()
{
    Serial.begin(115200);
    Serial.printf("**** tiny32_v3_read_pH_sensor  ****\r\n");
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
    float _pH_sensor = read_pH(0);
    Serial.printf("pH: %.2f\r\n",_pH_sensor);
    vTaskDelay(1000);
}

/***********************************************************************
 * FUNCTION:    read_pH
 * DESCRIPTION: read pH sensor
 * PARAMETERS:  adc channel [0-3]
 * RETURNED:    float
 ***********************************************************************/
float read_pH(int channel)
{
    int16_t _adc;
    float _voltage;
    float _phValue;
    //temperature = readTemperature();         // read your temperature sensor to execute temperature compensation
    _adc = ads.readADC_SingleEnded(channel); //can change channel here [0-3]
    _voltage = ads.computeVolts(_adc)*1000;
    _phValue = ph.readPH(_voltage,temperature);  // convert voltage to pH with temperature compensation
    return _phValue;
}


 /***********************************************************************
 * FUNCTION:    readTemperature
 * DESCRIPTION: read tempeature sensor (ถ้าไม่มีเซนเซอร์จริง ให้ใช้ค่า 25 บรรทัดที่ 52)
 * PARAMETERS:  nothing
 * RETURNED:    nothing
 ***********************************************************************/
float readTemperature()
{
  //add your code here to get the temperature from your temperature sensor
}