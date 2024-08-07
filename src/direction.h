


 
class MyCharWriteCallbacks: public BLECharacteristicCallbacks {
    void onWrite(BLECharacteristic *pCharacteristic)
    {
      g_lastActivityTime = millis();
      std::string value = pCharacteristic->getValue();

      if (value.length() > 0)
      {
        g_naviData = value;
        g_isNaviDataUpdated = true;
        Serial.print("New value, length = ");
        Serial.print(value.length());
        Serial.print(": ");
        for (int i = 0; i < value.length(); ++i)
        {
          char tmp[4] = "";
          sprintf(tmp, "%02X ", value[i]);
          Serial.print(tmp);
        }
        //  Serial.println();
      }
    }
};
void directionsStop(){
  NimBLEAdvertising *pAdvertising = NimBLEDevice::getAdvertising();
  if (pAdvertising->isAdvertising()) {
    pAdvertising->stop();
  }
  NimBLEDevice::deinit();
}
void directionsInit() {
  Serial.println("BLENaviPeripheral2 setup() started");
  uint8_t new_mac[8] = {0x09, 0x01, 0x01, 0x01, 0x05, 0x06};
  esp_base_mac_addr_set(new_mac);
  NimBLEDevice::init("ESP32 HUD");
  g_pServer = NimBLEDevice::createServer();
  NimBLEService* pService = g_pServer->createService(SERVICE_UUID1);
  // characteristic for indicate
  {

    g_pCharIndicate = pService->createCharacteristic(CHAR_INDICATE_UUID1, NIMBLE_PROPERTY::INDICATE);
    g_pCharIndicate->setValue("");
  }
  // characteristic for write
  {
    NimBLECharacteristic *pCharWrite = pService->createCharacteristic(CHAR_WRITE_UUID1, NIMBLE_PROPERTY::WRITE);
    pCharWrite->setCallbacks(new MyCharWriteCallbacks());
  }
  pService->start();
  NimBLEAdvertising* pAdvertising = NimBLEDevice::getAdvertising();
  pAdvertising->addServiceUUID(SERVICE_UUID1);
  pAdvertising->setScanResponse(true);
  pAdvertising->setMinPreferred(0x06); // functions that help with iPhone connections issue
  pAdvertising->setMaxPreferred(0x12);
  // added the two below lines to try and make phone see device as a different device all together. //
  pAdvertising->setAppearance(0x0340); // Appearance: Heart Rate Sensor
  ////////////////////////////////////////////////////////////////////////////////////////////////////
  NimBLEDevice::startAdvertising();
  Serial.println("BLE init done");
  Serial.println("setup() finished");
  g_deviceConnected = true;
} 
const String ImageFromDirection(uint8_t direction) {
  switch (direction) {
    case DirectionNone: return "NONE";
    case DirectionStart: return "Starting Route";
    case DirectionEasyLeft: return "Slight Left";
    case DirectionEasyRight: return "Slight Right";
    case DirectionEnd: return "Ending Route";
    case DirectionVia: return "Via";
    case DirectionKeepLeft: return "Keep left";
    case DirectionKeepRight: return "Keep Right";
    case DirectionLeft: return "Turn Left";
    case DirectionOutOfRoute: return "DirectionOutOfRoute";
    case DirectionRight: return "Turn Right";
    case DirectionSharpLeft: return "Sharp Left";
    case DirectionSharpRight: return "Sharp Right";
    case DirectionStraight: return "Straight";
    case DirectionUTurnLeft: return "Uturn <-";
    case DirectionUTurnRight: return "Uturn ->";
    case DirectionExitLeft: return "Exit <-";
    case DirectionExitRight: return "Exit ->";
  }
  return "Error!!!";
}
void directions() {
  if (g_isNaviDataUpdated)
  {
    //Serial.println("New Data");
    g_isNaviDataUpdated = false;
    std::string currentData = g_naviData;
    if (currentData.size() > 0)
    {
      if (currentData[0] == 1)
      {
        //Serial.print("Reading basic data: length = ");
        //Serial.println(currentData.length());
        const int speedOffset = 1;
        const int instructionOffset = 2;
        const int textOffset = 3;
        
        if (currentData.length() > textOffset)
        {
           const char* text = currentData.c_str() + textOffset;
           const int textLen = strlen(text);
           distance = String(currentData.c_str() + textOffset);
           nav_command = String(ImageFromDirection(currentData.c_str()[instructionOffset]));
           draw_navigation_command(nav_command,distance,String(currentData.c_str()[1]));
          //tft.drawCentreString(distance, 20, 50, 1);
        }
        if (currentData.length() > instructionOffset)
          Serial.println("DATA STREAM:(A) " + distance); // this prints out the distance
          Serial.println("DATA COMMAND : " + nav_command); // this prints out the command
          
        if (currentData.length() > speedOffset)
          Serial.println(" SPEED MAYBE " + String(currentData.c_str()[1])); // this prints out the speed maybe
      }
      else
      {
        Serial.println("invalid first byte");
      }
    }
  }
  else
  {
    uint32_t time = millis();
    if (time - g_lastActivityTime > 4000)
    {
      g_lastActivityTime = time;
      g_pCharIndicate->indicate();
    }
  }
}

