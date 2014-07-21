#include <SPI.h>
#include <Ethernet.h>

// Enter a MAC address and IP address for your controller below.
// The IP address will be dependent on your local network:
byte mac[] = { 
  0x00, 0xAA, 0xBB, 0xCC, 0xDE, 0x01 };
IPAddress ip(10,20,196,73); //<<< ENTER YOUR IP ADDRESS HERE!!!

// initialize the library instance:
EthernetClient client;

const int requestInterval = 60000;  // delay between requests

const int buttonPin = 2;
int buttonState = 0;

char serverName[] = "198.199.82.132";  // 

boolean requested;                   // whether you've made a request since connecting
long lastAttemptTime = 0;            // last time you connected to the server, in milliseconds

String currentLine = "";            // string to hold the text from server

void setup() {
 
  pinMode(buttonPin, INPUT);
  
  // reserve space for the strings:
  currentLine.reserve(256);

// initialize serial:
  Serial.begin(9600);
  // attempt a DHCP connection:
  if (!Ethernet.begin(mac)) {
    // if DHCP fails, start with a hard-coded address:
    Ethernet.begin(mac, ip);
  }
  // make api call
  //connectToServer();
}


void loop(){
  
  buttonState = digitalRead(buttonPin);
  if(buttonState == HIGH) {
    Serial.println("button pressed!");
    connectToServer(); 
  }
  Serial.println("connection test");
  if (client.connected()) {
    if (client.available()) {
      // read incoming bytes:
      char inChar = client.read();

      // add incoming byte to end of line:
      currentLine += inChar; 

      // if you get a newline, clear the line:
      if (inChar == '\n') {
        currentLine = "";
      } 
      Serial.print(inChar);
    }
    client.stop();
    Serial.println("cooling down for 2....");
    delay(2000);
    Serial.println("ready");
  } 
  //delay(1000);
}

void connectToServer() {
  // attempt to connect, and wait a millisecond:
  Serial.println("connecting to server...");
  if (client.connect(serverName, 80)) {
    Serial.println("making HTTP request...");
  // make HTTP GET request to server
    client.println("GET /jump HTTP/1.1");
    client.println("HOST: 198.199.82.132");
    client.println();
  }
  // note the time of this connect attempt:
  lastAttemptTime = millis();
}
