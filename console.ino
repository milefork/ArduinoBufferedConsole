#include <SoftwareSerial.h>

#define RX   9
#define TX   10

#define READ_FROM_TIME 500
#define READ_TO_TIME 500


SoftwareSerial softser(RX, TX);
String readStringFrom = "";
String readStringTo = "";

void setup() {
  softser.begin(115200); // Soft serial connection to remote
  Serial.begin(9600); while(!Serial); // UART serial debug 
  Serial.println(F("console ready"));

}

int counterFrom = 0;
int counterTo = 0;

void loop() {
  //readLoop from localSerial
    while (Serial.available()>0) {
        char c = Serial.read();
        readStringTo += c;
        counterTo = 0;
    }
    

  //readLoop from remoteSerial
  while (softser.available()>0) {     
        char c = softser.read();
        readStringFrom += c;
        counterFrom = 0;
  }
  
  //pad time until nothing happens on serial
  if(softser.available()<=0){
    counterFrom++;
  }
  else{
    delay(1);
  }

  if(Serial.available()<=0){
    counterTo++;
  }
  else{
    delay(1);
  }

  //check if time elapsed
  checkCounter();
}
  


void checkCounter(){
    if(counterFrom>READ_FROM_TIME){      
      if (readStringFrom.length() >0 ) {
          Serial.println(readStringFrom);
          Serial.flush();
          readStringFrom = "";
          }
    counterFrom = 0;
  }
  if(counterTo>READ_TO_TIME){
    if (readStringTo.length() > 0) {
          softser.println(readStringTo);
          softser.flush();
          readStringTo = "";
    }
    counterTo = 0;
  }
}

