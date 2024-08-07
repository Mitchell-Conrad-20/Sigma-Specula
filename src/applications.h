void driving_app(){
    Serial.println("Setting up driving app!");
    stop_ancs();
    delay(1000);
    directionsInit();
}