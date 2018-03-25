//Initialitation and connection to the configured Router Station

void WiFiStart() {
  //Serial.print("Connecting to ");
  //Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(100);
    //Serial.print("_");
  }
  //Serial.println();
  //Serial.println("Done");
  //Serial.print("IP address: ");
  //Serial.println(WiFi.localIP());
  //Serial.println("");

  server.begin();
}
