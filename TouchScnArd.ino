#include <SoftwareSerial.h>
#include <Nextion.h>

SoftwareSerial nextion(3,2);
Nextion myNextion(nextion,9600);
char charstring[80];
char*pch;
int field,event,page,id;
int fsrAnalogPin = 1;
int fsrReading;
int scaled_value;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  myNextion.init();
  myNextion.sendCommand("page page0");
}

void loop(){
  fsrReading = analogRead(fsrAnalogPin);
  Serial.println(fsrReading);
  String message = myNextion.listen();
  field = 0;
  message.toCharArray(charstring,80);
  if(message !=""){
    Serial.println(charstring);
    pch=strtok(charstring,"");
    while(pch !=NULL){
      field++;
    }
    if(field==1) event = atoi(pch);
    if(field==2) page = atoi(pch);
    if(field==3) id = atoi(pch);
    pch = strtok(NULL,"");
  }
  Serial.println(event);
  Serial.println(page);
  Serial.println(id);
  scaled_value = map(fsrReading, 0, 670, 0, 100);
  myNextion.setComponentValue("n0",scaled_value);
  myNextion.setComponentValue("h0",scaled_value);
  if (scaled_value > 100){
    myNextion.sendCommand("page page1");
    myNextion.setComponentText("t0","Stronger than Baggio!");
    }
  //myNextion.setComponentText("t0","Wow, you're strong");
  //myNextion.updateProgressBar(25,228,200,25,fsrReading,0,2);
  }   
/*
myNextion.sendCommand("page1")
if (message == "65 00 03 01 ffff ffff ffff"){
  myNextion.setComponentText("t0","Baggio, Yes")
delay(1000)
myNextion.setComponentText("t0","Baggio,No")
}
}
*/
/*
void loop() {
  String message = myNextion.listen();          //check for message
  if (message != "") {                          // if a message is received...
    Serial.println(message);                    // print it out
  }
  if (message == "65 0 2 0 ffff ffff ffff") {
    Serial.println("Pressed Checkbox 1!");
  }
}
*/
