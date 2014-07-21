#include <SPI.h>
#include <Ethernet.h>

// Enter a MAC address and IP address for your controller below.
// The IP address will be dependent on your local network:
byte mac[] = { 
  0x00, 0xAA, 0xBB, 0xCC, 0xDE, 0x01 };
IPAddress ip(10,20,196,73); //<<< ENTER YOUR IP ADDRESS HERE!!!

// initialize the library instance:
EthernetClient client;

//const int requestInterval = 60000;  // delay between requests

char serverName[] = "198.199.82.132";  // 

boolean requested;                   // whether you've made a request since connecting

String currentLine = "";            // string to hold the text from server

//Weight settings

long time = 0;            // last time weight reading was taken
int timeBetweenReadings = 12000;

float loadA= 161; //grams
int analogvalA = 3200;

float loadB = 91;
int analogvalB = 1800;

float analogValueAverage = 0;


void setup() {
  
  currentLine.reserve(256);

  Serial.begin(9600);

  if (!Ethernet.begin(mac)) {
    Ethernet.begin(mac, ip);
  }
}


void loop(){
  int analogValue = analogRead(0);
  analogValueAverage = 0.99*analogValueAverage + 0.01*analogValue;

  if(millis() > time + timeBetweeenReadings){
    float load = analogToLoad(analogValueAverage);
    Serial.print("analogValue: ");
    Serial.print(avanlogValueAverage);
    time = millis();
    if(load < 440){
        delay(10*60*1000);
        verify_weight();
    }
  }

  if (client.connected()) {
    if (client.available()) {
      char inChar = client.read();
      currentLine += inChar; 
      if (inChar == '\n') {
        currentLine = "";
      } 
      Serial.print(inChar);
    }
    client.stop();
  } 
}

void connectToServer() {
  // attempt to connect, and wait a millisecond:
  Serial.println("connecting to server...");
  if (client.connect(serverName, 80)) {
    Serial.println("making HTTP request...");
  // make HTTP GET request to twitter:
    client.println("GET /ping HTTP/1.1");
    client.println("HOST: 198.199.82.132");
    client.println();
  }
  // note the time of this connect attempt:
  lastAttemptTime = millis();
}

void verifyWeight(){
  int analogValue = analogRead(0);
  analogValueAverage = 0.99*analogValueAverage + 0.01*analogValue;
  float load = analogToLoad(analogValueAverage);
  if(load <440){
    connectToServer();
  }
}

float analogToLoad(float analogval){
  float load = mapfloat(analogval, analogvalA, analogvalB, loadA, loadB);
  return load
}

float mapfloat(float x, float in_min, float in_max, float out_max){
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}
