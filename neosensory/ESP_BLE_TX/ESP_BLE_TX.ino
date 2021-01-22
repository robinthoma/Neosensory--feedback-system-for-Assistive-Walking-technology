

#include <BLEDevice.h> //Header file for BLE 

static BLEUUID serviceUUID("E400001-B5A3-F393-E0A9-E50E24DCCA9E"); //Service UUID of fitnessband obtained through nRF connect application 
static BLEUUID    charUUID("6E400002-B5A3-F393-E0A9-E50E24DCCA9E"); //Characteristic  UUID of fitnessband obtained through nRF connect application 
String My_BLE_Address = "2c:f7:f1:1b:3f:25"; //Hardware Bluetooth MAC of my fitnessband, will vary for every band obtained through nRF connect application 
static BLERemoteCharacteristic* pRemoteCharacteristic;

BLEScan* pBLEScan; //Name the scanning device as pBLEScan
BLEScanResults foundDevices;

static BLEAddress *Server_BLE_Address;
String Scaned_BLE_Address;

boolean paired = false; //boolean variable to togge light

bool connectToserver (BLEAddress pAddress){
    
    BLEClient*  pClient  = BLEDevice::createClient();
    Serial.println(" - Created client");

    // Connect to the BLE Server.
    pClient->connect(pAddress);
    Serial.println(" - Connected to wio terminal");

    // Obtain a reference to the service we are after in the remote BLE server.
    BLERemoteService* pRemoteService = pClient->getService(serviceUUID);
    if (pRemoteService != nullptr)
    {
      Serial.println(" - Found our service");
      return true;
    }
    else
    return false;

    // Obtain a reference to the characteristic in the service of the remote BLE server.
    pRemoteCharacteristic = pRemoteService->getCharacteristic(charUUID);
    if (pRemoteCharacteristic != nullptr)
      Serial.println(" - Found our characteristic");

      return true;
}

class MyAdvertisedDeviceCallbacks: public BLEAdvertisedDeviceCallbacks 
{
    void onResult(BLEAdvertisedDevice advertisedDevice) {
      Serial.printf("Scan Result: %s \n", advertisedDevice.toString().c_str());
      Server_BLE_Address = new BLEAddress(advertisedDevice.getAddress());
      
      Scaned_BLE_Address = Server_BLE_Address->toString().c_str();
      
    }
};

void setup() {
    Serial.begin(115200); //Start serial monitor 
    Serial.println("ESP32 BLE Server program"); //Intro message 

    BLEDevice::init("");
    pBLEScan = BLEDevice::getScan(); //create new scan
    pBLEScan->setAdvertisedDeviceCallbacks(new MyAdvertisedDeviceCallbacks()); //Call the class that is defined above 
    pBLEScan->setActiveScan(true); //active scan uses more power, but get results faster

    
}

void loop() {

  foundDevices = pBLEScan->start(3); //Scan for 3 seconds to find the Fitness band 

  while (foundDevices.getCount() >= 1)
  {
    if (Scaned_BLE_Address == My_BLE_Address && paired == false)
    {
      Serial.println("Found Device :-)... connecting to Server as client");
       if (connectToserver(*Server_BLE_Address))
      {
      paired = true;
      Serial.println("Hello");
      
      break;
      }
      else
      {
      Serial.println("Pairing failed");
      break;
      }
    }
    
   
  } 
}
