#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>
#include <DHT.h>

const float referenceVolts = 5.0; // the default reference on a 5-volt board const 
int batteryPin = 0; // battery is connected to analog pin 0
const float referenceVolts1 = 5.0; // the default reference on a 5-volt board const 
int solarPin = 1; // battery is connected to analog pin 0

float voltbattery=0;
float voltsolar=0;
Adafruit_PCD8544 display = Adafruit_PCD8544( 5, 4, 3);

float vout=0.0;
float vin=0.0;
float R1=30000.0;
float R2=7500.0;

#define DHTPIN 8                // Connect the signal pin of DHT11 sensor to digital pin 5
#define DHTTYPE DHT11 
DHT dht(DHTPIN, DHTTYPE);

void setup() {
    pinMode(7,OUTPUT);
    digitalWrite(7,HIGH); //Turn Backlight ON
    //digitalWrite(7,LOW); //Turn Backlight ON
    dht.begin(); 
   
    Serial.begin(9600);
    display.begin();     
}

void loop() {
  float  voltage = readVoltage(A0);
  float  voltsolar = readVoltage(A1);
  float temp = dht.readTemperature();  //dht.readTemperature();
  float humi = dht.readHumidity();     // dht.readHumidity();
  delay(500);
    display.clearDisplay(); 
    display.setTextSize(0.1);
    
    display.setTextColor(BLACK, WHITE);
    display.setCursor(0, 0);
    display.print("B_volt:");
    //display.print(voltbattery); voltage
    display.print(voltage);    
    display.setCursor(0, 10);
    display.print("S_volt:");
    display.print(voltsolar);
    display.setCursor(0, 20);
    display.print(temp);
    display.print("C");
    display.print("  ");
    display.print(humi);
    display.print("%");
    display.setCursor(0, 30);
    display.print("Fragkakhs S.");
    display.display(); 
      
 
  //  display.drawFastHLine(0,10,83,BLACK); //gramh
     

  }
  
  void turnBacklightOn()
  {
    digitalWrite(7,LOW);
    delay(60000);
    digitalWrite(7,HIGH);
  }
  float readVoltage(double a){
      int volt = analogRead(a);// read the input
      vout = (volt *5.0) /1024.0;
      vin = vout / (R2/(R1+R2));
      return vin;
  }
