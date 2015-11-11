

#define segreto 48


void leggiGPS(int ms)
{
  #if defined(Debug)
    Debug_Port.print("reading GPS for ");
    Debug_Port.print(ms);
    Debug_Port.println("ms");
  #endif
  unsigned long long start = millis();
  do 
  {
    while (GPS_Port.available())
      gps.encode(GPS_Port.read());
    delay(5);
  } while (millis() - start < ms);
}


void LED (int red, int green, int blue)
{
  
  digitalWrite(led_pin_vcc, HIGH);
  analogWrite(led_pin_red, (255 - red));
  analogWrite(led_pin_green, (255 - green));
  analogWrite(led_pin_blue, (255 - blue));
  #if defined(Debug)
    Debug_Port.print("LED R:");
    Debug_Port.print(red);
    Debug_Port.print(" G:");
    Debug_Port.print(green);
    Debug_Port.print(" B:");
    Debug_Port.println(blue);
  #endif
}



/*

TinyGPSPlus::distanceBetween( gps.location.lat(), gps.location.lng(), LONDON_LAT, LONDON_LON)
TinyGPSPlus::courseTo(gps.location.lat(), gps.location.lng(), LONDON_LAT, LONDON_LON)
TinyGPSPlus::cardinal(gps.course.value())

*/

/*
#if defined(Debug)
  Debug_Port.println();
#endif

  */
