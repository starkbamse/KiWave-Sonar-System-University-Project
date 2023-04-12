#include "KiwiTemp.h"
#include "Arduino.h"
#include "math.h"

KiwiTemp::KiwiTemp(int sigPin) {
    _sigPin = sigPin;
    thermistorValue = 4275;
    //this is a constant ranging from 4250 to 4299 and the middle
    //value which is 4275 is chosen. 
    R0 = 100000;
    //this is the value for the resistor used in the sesnor for the 
    //formula NTC = ((Vcc/V) - 1) * R0 which is 100000.
}

float KiwiTemp::measureTemp() {
    float notProcessedTemp = ((1023.0/analogRead(_sigPin)) - 1.0) * R0;
    //notProcessedTemp = (1023.0/notProcessedTemp - 1.0) * R0;
    float processedTemp = 1.0 / (log(notProcessedTemp/R0) / thermistorValue + 1 / 298.15) - 273.15;
    //This formula processes the date and gives the temperature in
    //celsius degrees
    //source: https://wiki.seeedstudio.com/Grove-Temperature_Sensor_V1.2/#play-with-arduino
    return processedTemp;
}

int KiwiTemp::getThermistorValue() {
    return thermistorValue;
}

int KiwiTemp::getR0() {
    return R0;
}
