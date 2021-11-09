#include <OneWire.h>
#include <DallasTemperature.h> 
#define ONE_WIRE_BUS D4
int fanPin = 14;
int dutyCycle = 0;
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);
void setup() {
  Serial.begin(115200);
  pinMode(fanPin, OUTPUT); 
  sensors.begin(); 
  analogWriteRange(100);
  analogWriteFreq(15000);
}
float readSensorTemp() {
  sensors.requestTemperatures();
  Serial.print("Temperature: ");  
  Serial.println(sensors.getTempCByIndex(0));
  return sensors.getTempCByIndex(0);
}
void controlFanSpeed (int fanSpeedPercent) {
  Serial.print("Fan Speed: ");
  Serial.print(fanSpeedPercent);
  Serial.println("%");  
  analogWrite(fanPin, fanSpeedPercent); 
}
void loop() {
  float sensorTemp = readSensorTemp();
  int fanSpeedPercent = map(sensorTemp, 23, 36, 30, 100);
  controlFanSpeed (fanSpeedPercent); 
  delay(1000);
}
