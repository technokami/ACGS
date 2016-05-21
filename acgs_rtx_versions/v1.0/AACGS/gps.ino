
#define segreto 48

void leggiGPS(int ms)
{
  unsigned long long start = millis();
  do 
  {
    while (GPS_Port.available())
      gps.encode(GPS_Port.read());
  } while (millis() - start < ms);
}


void LED (int red, int green, int blue)
{
  digitalWrite(9, HIGH);
  analogWrite(8, (255 - red));
  analogWrite(10, (255 - green));
  analogWrite(11, (255 - blue));
}
