/*
----------------------------------------------------------------------------------------------------------------------------------------------------------------------------
PROJECT NAME   : Helper Filtre Coffee Stand
REVİSİON DATE  : 20.12.2021
AUTHOR         : Murat Can Olgunsoy
----------------------------------------------------------------------------------------------------------------------------------------------------------------------------
Purpose        : This stand is designed for making the brewing process easier and drinking a well-brewed,non-burned filter coffee. The summarized process of this stand
               is measuring the hot water, helping it to cool with using a cooler fan, pulling the filter coffee into the french press, and giving an alert 
               sound to indicate the process ending.               
----------------------------------------------------------------------------------------------------------------------------------------------------------------------------
System Input   :
                  1) DS18B20 Liquid Temperature Sensor : To measure liquid temperature
System Output  : 
                  1) Servo1 : To move the DS18B20 Liquid Temperature sensor into the french press          
                  2) Servo2 : To move the receptacle which keeps the coffee in it into the french press
                  3) Buzzer : To give an alert sound
----------------------------------------------------------------------------------------------------------------------------------------------------------------------------
System Work    : The liquid temperature sensor moves into the french press by support a servo, measures the hot water and waits till it becomes 87 celsius.
               While the water is cooling, a cooler fan is activated. When it becomes 87 celsius, the stand will pull the filter coffee into the french press by
               the supporter receptacle and turns back to its initial position by a servo. Finally, a buzzer will give a sound. It means the process ended so, wait
               a few minutes and drink your well-brewed filter coffee.

Starting Date: 29.11.2021
*/

//-------------Codes and definitions-----------//

#include<DallasTemperature.h>           //to include the DS18B20 sensor library
#include<OneWire.h>                     //to include one wire communication library
#include <Servo.h>                      //to include the servo library   

#define DS18B20_sensor 5                //to attach the DS18B20 sensor to wire 5 on arduino
#define buzzer 12                       //to attach buzzer to wire 12 on arduino
Servo servo1;                           //to define servo1(connected DS18B20 sensor)   
Servo servo2;                           //to define servo2(connected coffee receptacle)
OneWire oneWire(DS18B20_sensor);       
DallasTemperature DS18B20(&oneWire);

int i;                                  //to define i to use in for loop
int Celsius;                            //to define celsius for the temperature value

void setup() 
  {
  pinMode(buzzer,OUTPUT);               //to define the buzzer as output
  servo1.attach(4);                     //to define servo1 attached wire 4 
  servo2.attach(6);                     //to define servo2 attached wire 6
  Serial.begin(9600);
  DS18B20.begin();                      //to make the DS18B20 sensor ready to communication
  
  }

void loop() 
{
  delay(2000);                           //in the start of the process wait  for 2000 milliseconds
 
  for(i=70;i<=140;){                     //to move the temperature sensor into the cup
      servo1.write(i);                   //adjusting the degree of the servo1      
      i=i+1;                             //to increase by one the i      
      delay(70);                         //to wait for 70 milliseconds      
    }                                    
    
  DS18B20.requestTemperatures();         //to request the temperature sensor to measure temperature
  Celsius=DS18B20.getTempCByIndex(0);    //to measure the temperature as celcius
  delay(7000);                           //to wait for it to come to its real heat for 7000 second 
  DS18B20.requestTemperatures();         //again requesting the temperature sensor to measure temperature
  Celsius=DS18B20.getTempCByIndex(0);    //to measure the temperature as celcius
  
  
  do{
      DS18B20.requestTemperatures();
      Celsius=DS18B20.getTempCByIndex(0);
      delay(3000);
      DS18B20.requestTemperatures();
      Celsius=DS18B20.getTempCByIndex(0);
      delay(3000);
      DS18B20.requestTemperatures();
      Celsius=DS18B20.getTempCByIndex(0);
      delay(3000);
      
      Serial.print(Celsius);
      Serial.print(" C  \n");      
      delay(10);
   }while(Celsius>=87);
    
  for(i=140;i>=70;){                      //to move back the servo1 its initial position
      servo1.write(i);                    //adjusting the degree of the servo1
      i=i-1;                              //to decrease by one the i
      delay(70);                          //to wait for 70 milliseconds 
   }
   delay(4000);                           //to wait for 4000 milliseconds
    
  for(i=85;i<=160;){                      //to move the servo2 for pulling coffee
      servo2.write(i);                    //adjusting the degree of the servo2
      i=i+1;                              //to increase by one the i
      delay(70);                          //to wait for 70 milliseconds
      
   }
   delay(4000);                           //to wait for 4000 milliseconds
    
  for(i=160;i>=85;){                      //to move back the servo2 its initial position
      servo2.write(i);                    //adjusting the degree of the servo2
      i=i-1;                              //to decrease by one the i
      delay(70);                          //to wait for 70 milliseconds
  } 
   delay(10000);                          //to wait for 10000 milliseconds

  for(i=0;i<=5;i++){                      //to give an alert sound 5 times to indicate process ending
     tone(buzzer,800);                    //adjusting the sound of buzzer to 800 Hz
     delay(400);                          //to wait for 400 milliseconds
     noTone(buzzer);                      //to silence the buzzer
     delay(200);                          //to wait for 200 milliseconds
     
     tone(buzzer,600);                    //adjusting the sound of buzzer to 600 Hz
     delay(400);                          //to wait for 400 milliseconds
     noTone(buzzer);                      //to silence the buzzer
     delay(200);                          //to wait for 200 milliseconds
   }
    
  }
  
  
