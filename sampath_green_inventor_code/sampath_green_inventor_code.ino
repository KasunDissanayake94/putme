 #include <SoftwareSerial.h>
SoftwareSerial mySerial(11, 10);  // TX-Pin11, RX-Pin10
int led_red = 3; // Bin filled notification
int led_green = 4; //Bin not filled notification
int touchvalue; //get touch sensor value


void updateSerial()
{
  delay(2000);
  while (Serial.available()) {
    mySerial.write(Serial.read());//Data received by Serial will be outputted by mySerial
  }
  while(mySerial.available()) {
    Serial.write(mySerial.read());//Data received by mySerial will be outputted by Serial}
}
}
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("Starting...");
  mySerial.begin(9600);
  
  

}

 

void loop() {
  // get the touch sensor value(lid is open or not)
    touchvalue = analogRead(A0);


    //if lid is open send the message to the server and light red led
    if(touchvalue == 0){
      digitalWrite(led_red,HIGH);
      digitalWrite(led_green,LOW);
      notify();
      //if lid is not open light the green led
    }else{
      digitalWrite(led_green,HIGH);
      digitalWrite(led_red,LOW);
    }       

}
//send message to the server
void notify(){
  mySerial.println("AT");          // Once the handshake test is successful, it will back to OK
 updateSerial();
  mySerial.println("AT+CGATT=1 "); //The basic adhere network command of Internet connection
  updateSerial();
  mySerial.println("AT+CGDCONT?");//Set PDP parameter 
  updateSerial();
  mySerial.println("AT+CSTT=\"internet\","",""");//start task and setting the APN,
 //  delay(1000); 
  updateSerial(); 
  mySerial.println("AT+CIICR");//bring up wireless connection
  //delay(3000); 
  updateSerial(); 
  mySerial.println("AT+CIFSR");//get local IP adress
  updateSerial();
  //delay(2000); 
    /*
  Serial1.println("AT+CIPSTART=\"tcp\",\"http://mrbin06grp.000webhostapp.com/?arduino_data=newdata\",\"80\"");
  updateSerial();
  delay(2000); 
  mySerial.println("AT+CIPSEND");// Send data request to the server
  updateSerial();
  mySerial.print("TEST");// Send data to the server
  updateSerial();
  mySerial.write(26);// Terminator
  */
  while(1)
    { 
    if(mySerial.available()) 
    {
      //if lid close in a small time(lid open for dump garbage)
      if(analogRead(A0)!=0){
        digitalWrite(led_green,HIGH);
        digitalWrite(led_red,LOW);
        mySerial.write(26);
        Serial.println("Terminated");
        //Now bin is filled
      }else{
        digitalWrite(led_red,HIGH);
      digitalWrite(led_green,LOW);
      }
      Serial.write(mySerial.read());//Data received by mySerial will be outputted by Serial
    }
    if(Serial.available())
    {
      //if lid close in a small time(lid open for dump garbage)
      if(analogRead(A0)!=0){
        digitalWrite(led_green,HIGH);
        digitalWrite(led_red,LOW);
        mySerial.write(26);
        Serial.println("Terminated");
        //Now bin is filled
      }else{
        digitalWrite(led_red,HIGH);
      digitalWrite(led_green,LOW);
      }
      mySerial.write(Serial.read());//Data received by Serial will be outputted by mySerial
    }   
  }
  }
