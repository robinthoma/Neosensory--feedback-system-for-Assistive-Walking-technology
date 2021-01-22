

/*
  Scan
  This example scans for BLE peripherals and prints out their advertising details:
  address, local name, adverised service UUID's.
  The circuit:
  - Arduino MKR WiFi 1010, Arduino Uno WiFi Rev2 board, Arduino Nano 33 IoT,
    Arduino Nano 33 BLE, or Arduino Nano 33 BLE Sense board.
  This example code is in the public domain.
*/
#include <ArduinoBLE.h>
void setup() {
  Serial.begin(115200);
  while (!Serial);
  // initialize the BLE hardware
  if (!BLE.begin()) {
    Serial.println("starting BLE failed!");
    while (1);
  }
  Serial.println("BLE Central - Buzz");
  // start scanning for peripheral
  //  int r = BLE.scanForUuid("6E400001-B5A3-F393-E0A9-E50E24DCCA9E");
  //  Serial.printf("SCAN RESULT = %d",r);
  //  delay(1000);
  BLE.scan();
}
void loop() {
  // check if a peripheral has been discovered
  BLEDevice peripheral = BLE.available();
  if (peripheral) {
    if (peripheral.hasLocalName()) {
      Serial.print("Local Name: ");
      Serial.println(peripheral.localName());
      if (peripheral.localName().indexOf("Buzz") == -1) {
        return;
      }
      Serial.println("Buzz found. Connect to it");
      // stop scanning
      BLE.stopScan();
      controlLBuzz(peripheral);
      Serial.println("Re-scan");
      BLE.scan();
      //BLE.scanForUuid("6e400001-b5a3-f393-e0a9-e50e24dcca9e");
      return;
    }
  }
}
void controlLBuzz(BLEDevice peripheral) {
  // connect to the peripheral
  Serial.println("Connecting ...");
  peripheral.connect();
  if (peripheral.connected()) {
    Serial.println("Connected to Buzz");
  } else {
    Serial.println("Failed to connect!");
    return;
  }
  // discover peripheral attributes
//  Serial.println("Discovering attributes ...");
//  if (peripheral.discoverAttributes()) {
//    Serial.println("Attributes discovered");
//  } else {
//    Serial.println("Attribute discovery failed!");
//    peripheral.disconnect();
//    return;
//  }
Serial.println("Discovering service  ...");
  if (peripheral.discoverService("6e400001-b5a3-f393-e0a9-e50e24dcca9e")) {
    Serial.println("Service discovered");
  } else {
    Serial.println("Attribute discovery failed.");
    peripheral.disconnect();
    return;
  }
  // loop the services of the peripheral and explore each
  for (int i = 0; i < peripheral.serviceCount(); i++) {
    BLEService service = peripheral.service(i);
    exploreService(service);
  }
//  BLECharacteristic writeCharacteristic = peripheral.characteristic("6e400002-b5a3-f393-e0a9-e50e24dcca9e", BLEWrite);
//  BLECharacteristic readCharacteristic = peripheral.characteristic("6e400003-b5a3-f393-e0a9-e50e24dcca9e", BLERead);
//  readCharacteristic.setEventHandler(BLEWritten, notifyRead);
////
////
////
//  if (!writeCharacteristic) {
//    Serial.println("Peripheral does not have WRITE characteristic!");
//    peripheral.disconnect();
//    return;
//  } else if (!writeCharacteristic.canWrite()) {
//    Serial.println("Peripheral does not have a permission to WRITE characteristic!");
//    peripheral.disconnect();
//    return;
//  }
//  writeCharacteristic.writeValue("auth for developer\n");
  while (peripheral.connected()) {
    Serial.print(".");
  }
  Serial.println("Peripheral disconnected");
}
void notifyRead(BLEDevice central, BLECharacteristic characteristic) {
  // central wrote new value to characteristic, update LED
  Serial.print("Characteristic event, written: ");
  //  Serial.println(characteristic.value());
}
void exploreService(BLEService service) {
  // print the UUID of the service
  Serial.print("Service ");
  Serial.println(service.uuid());
  if (String(service.uuid()) == "6e400001-b5a3-f393-e0a9-e50e24dcca9e") {
    // loop the characteristics of the service and explore each
    for (int i = 0; i < service.characteristicCount(); i++) {
      BLECharacteristic characteristic = service.characteristic(i);
      String uuid = String(characteristic.uuid());
      if( uuid == "6e400002-b5a3-f393-e0a9-e50e24dcca9e"){
        Serial.print("This is WRITE characteristic ");Serial.println(characteristic.uuid());
        if(characteristic.canWrite()){
          Serial.println("CAN WRITE");
          characteristic.writeValue("auth for developer\n");
          characteristic.writeValue("accept\n");
          delay(5000);
        }else{
          Serial.println("! CAN NOT WRITE");
        }
      }
      if(uuid == "6e400003-b5a3-f393-e0a9-e50e24dcca9e"){
        Serial.print("This is READ characteristic ");Serial.println(characteristic.uuid());
        if(characteristic.canSubscribe()){
          Serial.println("Can subscribe");
          if(characteristic.subscribe()){
            Serial.println("Subscribed ... ");
          }
          characteristic.setEventHandler(BLESubscribed, notifyRead);
          characteristic.setEventHandler(BLEWritten, notifyRead);
          characteristic.setEventHandler(BLERead, notifyRead);
        }else{
          Serial.println("! CAN NOT READ");
        }
      }
    }
  }
}
void exploreCharacteristic(BLECharacteristic characteristic) {
  // print the UUID and properties of the characteristic
  Serial.print("\tCharacteristic ");
  Serial.print(characteristic.uuid());
  Serial.print(", properties 0x");
  Serial.print(characteristic.properties(), HEX);
  // check if the characteristic is readable
  if (characteristic.canRead()) {
    // read the characteristic value
    characteristic.read();
    if (characteristic.valueLength() > 0) {
      // print out the value of the characteristic
      Serial.print(", value 0x");
      printData(characteristic.value(), characteristic.valueLength());
    }
  }
  Serial.println();
  // loop the descriptors of the characteristic and explore each
  //  for (int i = 0; i < characteristic.descriptorCount(); i++) {
  //    BLEDescriptor descriptor = characteristic.descriptor(i);
  //
  //    exploreDescriptor(descriptor);
  //  }
}
void exploreDescriptor(BLEDescriptor descriptor) {
  // print the UUID of the descriptor
  Serial.print("\t\tDescriptor ");
  Serial.print(descriptor.uuid());
  // read the descriptor value
  descriptor.read();
  // print out the value of the descriptor
  Serial.print(", value 0x");
  printData(descriptor.value(), descriptor.valueLength());
  Serial.println();
}
void printData(const unsigned char data[], int length) {
  for (int i = 0; i < length; i++) {
    unsigned char b = data[i];
    if (b < 16) {
      Serial.print("0");
    }
    Serial.print(b, HEX);
  }
}