#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>
#include <BLE2902.h>

#define SERVICE_UUID        "03b80e5a-ede8-4b33-a751-6ce34ec4c700"
#define CHARACTERISTIC_UUID "7772e5db-3868-4112-a1a9-f2669d106bf3"

BLECharacteristic *pCharacteristic;
bool deviceConnected = false;

uint8_t midiPacket[] = {
  0x80,  // header
  0x80,  // timestamp, not implemented
  0x00,  // status
  0x3c,  // 0x3c == 60 == middle c
  0x00   // velocity
};

uint8_t clockByte[1] = {0xF8};

class MyServerCallbacks: public BLEServerCallbacks {
    void onConnect(BLEServer* pServer) {
      Serial.println("Bluetooth Connected!!!");
      deviceConnected = true;
      loadMIDIMenu();
    };

    void onDisconnect(BLEServer* pServer) {
      loadConnectionPage();
      deviceConnected = false;
    }
};

void bluetoothSetup() {

  BLEDevice::init("Wavey Watch");
  DEBUG_PRINTLN("Bluetooth Setup");
  // Create the BLE Server
  BLEServer *pServer = BLEDevice::createServer();
  pServer->setCallbacks(new MyServerCallbacks());

  // Create the BLE Service
  BLEService *pService = pServer->createService(BLEUUID(SERVICE_UUID));

  // Create a BLE Characteristic
  pCharacteristic = pService->createCharacteristic(
                      BLEUUID(CHARACTERISTIC_UUID),
                      BLECharacteristic::PROPERTY_READ   |
                      BLECharacteristic::PROPERTY_WRITE  |
                      BLECharacteristic::PROPERTY_NOTIFY |
                      BLECharacteristic::PROPERTY_WRITE_NR
                    );

  // https://www.bluetooth.com/specifications/gatt/viewer?attributeXmlFile=org.bluetooth.descriptor.gatt.client_characteristic_configuration.xml
  // Create a BLE Descriptor
  pCharacteristic->addDescriptor(new BLE2902());

  // Start the service
  pService->start();

  // Start advertising
  BLEAdvertising *pAdvertising = pServer->getAdvertising();
  pAdvertising->addServiceUUID(pService->getUUID());
  pAdvertising->start();
}

void bleNoteOn(char note, char velocity, char channel) {
  midiPacket[2] = 0x90; // note down
  midiPacket[3] = note; // note down
  midiPacket[4] = velocity;  // velocity
  pCharacteristic->setValue(midiPacket, 5); // packet, length in bytes
  pCharacteristic->notify();
}

void bleNoteOff(char note, char velocity, char channel) {
  midiPacket[2] = 0x80; // note down
  midiPacket[3] = note;
  midiPacket[4] = velocity;  // velocity
  pCharacteristic->setValue(midiPacket, 5); // packet, length in bytes
  pCharacteristic->notify();
}

void blePitchBend (int pitchbend, char channel) {
  uint16_t currentTimeStamp = millis() & 0x01FFF;
  midiPacket[0] = 0x80; // ((currentTimeStamp >> 7) & 0x3F) | 0x80; //6 bits plus MSB
  midiPacket[1] = 0x80; // (currentTimeStamp & 0x7F) | 0x80; //7 bits plus MSB
  midiPacket[2] = 0xE0; // pitchbend
  midiPacket[3] = pitchbend & 0x7F;
  midiPacket[4] = (pitchbend) >> 7;
  pCharacteristic->setValue(midiPacket, 5); // packet, length in bytes
  pCharacteristic->notify();
}

void bleControlChange (char control, char value) {
  midiPacket[0] = 0x80; // ((currentTimeStamp >> 7) & 0x3F) | 0x80; //6 bits plus MSB
  midiPacket[1] = 0x80; // (currentTimeStamp & 0x7F) | 0x80; //7 bits plus MSB
  midiPacket[2] = 0xB0; // control change status byte
  midiPacket[3] = control; //cc number
  midiPacket[4] = value;
  pCharacteristic->setValue(midiPacket, 5); // packet, length in bytes
  pCharacteristic->notify();
}

void setPitchBendRange (char range) {
  bleControlChange(101, 0);
  bleControlChange(100, 0);
  bleControlChange(6, range);
  bleControlChange(101, 127);
  bleControlChange(100, 127);
}

void bleClock() {
  //  DEBUG_PRINTLN("tick");
  pCharacteristic->setValue(clockByte, 1); // packet, length in bytes
  pCharacteristic->notify();
}

bool bluetoothConnected() {
  return deviceConnected;
}
