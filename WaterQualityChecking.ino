#include <Arduino.h>
#include <SoftwareSerial.h>

const int tdsSensorPin = A1;//Connect output of TDS Sensor with A1 pin of Arduino 
const int pHSensorPin = A0;//Connect output of PH Sensor with A0 pin of Arduino
const int turbiditySensorPin = A2;// Connect output of Turbbidity Sensor with A2 pin of Arduino


const float voltageReference = 5.0;  
const float tdsFactor = 2.0;   

  
const float pH7Voltage = 2.5;         
const float pHDifferencePerVolt = 0.18;


const int bluetoothTxPin = 2; 
const int bluetoothRxPin = 3;
SoftwareSerial bluetoothSerial(bluetoothRxPin, bluetoothTxPin);


void setup() {
  Serial.begin(9600);
  bluetoothSerial.begin(9600);
}

void loop() {
  // Read the analog value from the TDS sensor
  int tds = analogRead(tdsSensorPin);
  float voltagetds = (tds / 1024.0) * voltageReference;
  float tdsValue = -280+(voltagetds * tdsFactor * 10000);
  //Serial Monitor prints the value of TDS
  Serial.print("\t TDS Value: ");
  Serial.print(tdsValue, 2); // Print TDS value with 2 decimal places
  Serial.println(" ppm");    // ppm stands for parts per million
  delay(1000);

  // Read the analog value from the pH sensor
  int ph = analogRead(pHSensorPin);
  float voltageph = (ph / 1024.0) * voltageReference;
  float pHValue = -1.6+(pH7Voltage - voltageph) / pHDifferencePerVolt;
   //Serial Monitor prints the value of PH
  Serial.print("\t pH Value: ");
  Serial.print(pHValue, 2);
  Serial.println();
  delay(1000);

  // Read the analog value from the turbidity sensor
  float turbidity = (analogRead(turbiditySensorPin)/100)-3.5;
   //Serial Monitor prints the value of Turbidity
  Serial.print("\t Turbidity Value: ");
  Serial.println(turbidity);
  delay(1000);
  
  if(tdsValue>150 && tdsValue<350 && pHValue>6.5 && pHValue<7.5 && turbidity>1 && turbidity<5){
    Serial.println("\t Good Quality Water for Drinking.");
  }
  else{
    Serial.println("\t Water is not fitered for Drinking.");
  }
  Serial.println("\n------------------------------------------------------------------\n");
  //After connecting with Bluetooth;
  //Display the value of TDS
  bluetoothSerial.print("\t\t\t\t TDS: ");
  bluetoothSerial.print(tdsValue, 2); 
  bluetoothSerial.println(" ppm"); 
  delay(1000);
  //Display the value of PH
  bluetoothSerial.print("\t\t\t\t pH: ");
  bluetoothSerial.print(pHValue, 2);
  bluetoothSerial.println();
  delay(1000);
  //Display the value of Turbidity
  bluetoothSerial.print("\t\t\t\t Turbidity: ");
  bluetoothSerial.println(turbidity);
  delay(1000);
  //
   if(tdsValue>150 && tdsValue<350 && pHValue>6.5 && pHValue<7.5 && turbidity>1 && turbidity<5)//Condition to determine the quality of water;
   {
    bluetoothSerial.println("\t\t\t\t Good Quality Water for Drinking.");
    }
  else{
    bluetoothSerial.println("\t\t\t\t Water is not fitered for Drinking.");
  }
  bluetoothSerial.println("\n----------------------------------------------------------\n");
  
}
