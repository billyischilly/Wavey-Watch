const char* ssid = "Like A Virgin (Smart Hub)";
const char* password = "wbh8hzspYqnh";

WiFiUDP Udp;
const IPAddress outIp(192, 168, 0, 13);
const unsigned int outPort = 6448;

void getAccel();
float aX = 0.0f;
float aY = 0.0f;
float aZ = 0.0f;

void wifiSetup() {
  DEBUG_PRINT("Connecting to ");
  DEBUG_PRINTLN(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    digitalWrite(0, LOW);
    delay(10);
    digitalWrite(0, HIGH);
    delay(500);
    DEBUG_PRINT(".");
  }
  DEBUG_PRINTLN("");
  DEBUG_PRINTLN("WiFi connected");
  sendAllOSC();
}

void sendMessageViaOSC() {
  getAccel();
  // create an OSCMessage:
  OSCMessage msgOUT("/wek/inputs");
  msgOUT.add(aX);
  msgOUT.add(aY);
  msgOUT.add(aZ);
  Udp.beginPacket(outIp, outPort);
  msgOUT.send(Udp);
  Udp.endPacket();
  msgOUT.empty();
  delay(20);
}

void getAccel()
{
  Accel acc;
  bool res = ttgo->bma->getAccel(acc);

  if (res == false) {
  } else {
    aX = acc.x;
    aY = acc.y;
    aZ = acc.z;
  }
}
