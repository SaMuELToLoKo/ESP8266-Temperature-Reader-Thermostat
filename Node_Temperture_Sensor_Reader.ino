//NodeMCU Samuel's Room

#include <ESP8266WiFi.h>
#include <DHT.h>

///// DHT SETTINGS - Replace with your values /////////////////

#define DHTTYPE DHT22  //Definition of temperature sensor type
#define DHTPIN  4 //D19 - Temperature sensor
DHT dht(DHTPIN, DHTTYPE, 11);  //Temperature configuration
const long interval = 2000; //delay to get new temperature value
unsigned long previousMillis = 0;
float humidity, temp_c; //Temperature and Humidity data variable initialitation
float humidity_p = 0, temp_c_p = 0; //Variable to storage old value in case the sensor fail reading values.

////////////////////////////////////////////////////////////////////

WiFiServer server(80); //Set server port

////////////////////////////////////////////////////////////////////


///////// WiFi SETTINGS - Replace with your values /////////////////

const char* ssid = "Your SSID";
const char* password = "Your Password";

////////////////////////////////////////////////////////////////////


void setup() {
  //Serial.begin(115200); //Initialize serial debbuging
  WiFi.mode(WIFI_STA);
  WiFiStart(); //Function to Start WiFi connection
}

void loop() {

  //Reconnect on lost WiFi connection
  if (WiFi.status() != WL_CONNECTED) {
    WiFiStart();
  }

  WiFiClient client = server.available();
  
//check when the client is not available, is is not available restart the program (is a good point to place and set up another variables and functions in to the program)

  if (!client) {
    return;
  }

  while (client.connected() && !client.available()) {
    delay(1);
  }

  String req = client.readStringUntil('\r');
  client.flush();


  // Match the request
  if (req.indexOf("") != -10) {  //checks if you're on the main page

    ////////////////////////////Temperature Sensor////////////////////////////
    if (req.indexOf("/dht") != -1) {
      client.println("HTTP/1.1 200 OK");
      client.println("Content-Type: text/html");
      client.println();
      gettemperature();
      if (String(temp_c) == "nan") {
        temp_c = temp_c_p;
      }
      else {
        temp_c_p = temp_c;
      }
      if (String(humidity) == "nan") {
        humidity = humidity_p;
      }
      else {
        humidity_p = humidity;
      }
      client.println("{\n" "\"temperature\": " + String(temp_c) + ",\n " "\"humidity\": " + String(humidity) + "" "\n}");
      delay(10);
      return;
    }

  }
  else {
    //Serial.println("invalid request");
    client.stop();
    return;
  }

  delay(1);

}
