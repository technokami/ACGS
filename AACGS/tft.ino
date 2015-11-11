
void IntroDisplay()
{
  #if defined(Debug)
    Debug_Port.println("start splash screen");
  #endif
  LED(blu);
  tft.clrScr();
  tft.setFont(SmallFont);
  tft.fillScr(bianco);
  tft.setColor(nero);
  tft.setBackColor(bianco);
  tft.print("* Arduino Anti Collision Gps System *", CENTER, 15);
  tft.print("*www.cussigh.it*     *Green.Pixel*", CENTER, 35);
  tft.drawBitmap (110, 70, 100, 100, logo_gpx);
  tft.setFont(BigFont);  
  tft.setColor(blu);
  tft.print("Plane: " + textmarca, CENTER, 180);
  tft.setColor(rosso);
  tft.print("Good landing!", CENTER, 210);
  delay(2500);
  tft.setColor(bianco);
  tft.fillRect(110, 70, 210, 170);
  #if defined(Debug)
    Debug_Port.println("end splash screen");
  #endif
}

void attendigps()
{
  #if defined(Debug)
    Debug_Port.println("waiting GPS fix...");
  #endif
  LED(ciano);
  //while(!gps.location.isValid())
  for(int i=0; i<10;i++)
  {
    #if defined(Debug)
      Debug_Port.print(".");
    #endif
    tft.drawBitmap (200, 70, 100, 100, logo_gpx);
    tft.setFont(SmallFont);
    tft.setColor(magenta);
    tft.setBackColor(bianco);
    tft.print("Waiting for gps 3D fix ", 20, 70);
    
    tft.drawBitmap (70, 105, 50, 50, attesa, angoloAttesa, 25, 25);
    angoloAttesa += 30 ;
    if(angoloAttesa == 360)
      angoloAttesa = 0 ;
      
    leggiGPS(50);
  }
  #if defined(Debug)
    Debug_Port.println();
    Debug_Port.println("GPS: OK!");
  #endif
}

void disegna()
{
  int aereiRossi = 0 ;
  int aereiMagenta = 0 ;
  int aereiGialli = 0 ;
  int aereiNeri = 0 ;
  int aereicontati = 0 ;
 
  if(firstClear)
  {
    tft.clrScr();
    tft.setColor(nero);
    tft.fillRect(0, 0, 319, 239);
    firstClear = false ;
  }

  
  tft.setColor(nero);
  tft.fillRect(0, 0, 239, 239);
  
  tft.setColor(blu);
  tft.setBackColor(nero);
  tft.drawRect(0, 0, 239, 239);

  tft.drawLine(120, 110, 120, 130);
  tft.drawLine(110, 120, 130, 120);
  
  tft.drawCircle(120, 120, 35);
  tft.drawCircle(120, 120, 70);
  tft.drawCircle(120, 120, 105);


  int rottamia = gps.course.deg() ;

  delay(1);
  
  tft.setColor(rosso);
  for(int i=0; i<righematr; i++)
  {
    delay(10);
    if(nomi[0][i]!='_' && nomi[5][i]!='_')
    {
      double ang = aria[7][i] - rottamia ;
      if(ang<0)
        ang = 360 + ang ;
      ang -= 90 ;
      double pix = aria[6][i] / 1;
      int xp =(float) ( pix * cos(ang*(pi/180)) ) + 120;
      int yp =(float) ( pix * sin(ang*(pi/180)) ) + 120;
      
      if(xp>=0 && xp<=239 && yp>=0 && yp <= 239)
      {
          tft.fillCircle(xp, yp, 5);
          String text1 ;
          for(int x=0; x<6; x++)
            text1 = text1 + nomi[x][i] ;
          tft.setFont(SmallFont);
          tft.print(text1, (xp+8), (yp+6));
          String text2 = (String) aria[0][i];
          tft.print(text2, (xp+8), (yp-6));
      }

      ang += 90 ;
      
      if(aria[9][i] < 10)
        aereiRossi++;
      else if(aria[6][i] <= aria[9][i])
      {
        if(ang >= 270 || ang <= 90)
          aereiMagenta++;
        else if(ang > 90 && ang < 270)
          aereiGialli++;
      }
      else if(aria[6][i] > aria[9][i])
          aereiNeri++;
      aereicontati++ ;      
    }
  }

  if(aereiRossi > 0)
    LED(rosso);
  else if(aereiRossi == 0 && aereiMagenta > 0)
    LED(magenta);
  else if(aereiRossi == 0 && aereiMagenta == 0 && aereiGialli > 0)
    LED(giallo);
  else if(aereiRossi == 0 && aereiMagenta == 0 && aereiGialli == 0 && aereiNeri == 0 && aereicontati > 0)
    LED(nero);
  else if(aereiRossi == 0 && aereiMagenta == 0 && aereiGialli == 0 && aereiNeri == 0 && aereicontati == 0)
    LED(nero);

  delay(1);

  tft.setColor(nero);
  
  String textDate = (String)gps.date.day() + '/' + (String)gps.date.month() + '/' + (String)(gps.date.year()-2000) ;
  if(textDate.length() != oldtextDatelength)
  {
    oldtextDatelength = textDate.length() ;
    tft.fillRect(242, 20, 319, 40);
  }
  String textTime = (String)gps.time.hour() + ':' + (String)gps.time.minute() + ':' + (String)gps.time.second() ;
  if(textTime.length() != oldtextTimelength)
  {
    oldtextTimelength = textTime.length() ;
    tft.fillRect(242, 60, 319, 80);
  }
  String textAltM = (String)(int)gps.altitude.meters() ;
  if(textAltM.length() != oldtextAltMlength)
  {
    oldtextAltMlength = textAltM.length() ;
    tft.fillRect(242, 100, 319, 120);
  }
  String textAltF = (String)(int)gps.altitude.feet() ;
  if(textAltF.length() != oldtextAltFlength)
  {
    oldtextAltFlength = textAltF.length() ;
    tft.fillRect(242, 140, 319, 160);
  }
  String textSpeed = (String)(int)gps.speed.kmph() ;
  if(textSpeed.length() != oldtextSpeedlength)
  {
    oldtextSpeedlength = textSpeed.length() ;
    tft.fillRect(242, 180, 319, 200);
  }
  String textHDOP = (String)gps.hdop.value() ;
  if(textHDOP.length() != oldtextHDOPlength)
  {
    oldtextHDOPlength = textHDOP.length() ;
    tft.fillRect(242, 220, 319, 239);
  }
  String textCourse = (String)(int)gps.course.deg() + (String)(char)'^' ;
  if(textCourse.length() != oldtextCourselength)
  {
    oldtextCourselength = textCourse.length() ;
    tft.fillRect(102, 0, 142, 20);
  }

  delay(1);
  
  tft.setColor(verde);
  tft.setFont(SmallFont);
  
  tft.drawRect(242, 20, 319, 40);
  tft.drawRect(242, 60, 319, 80);
  tft.drawRect(242, 100, 319, 120);
  tft.drawRect(242, 140, 319, 160);
  tft.drawRect(242, 180, 319, 200);
  tft.drawRect(242, 220, 319, 239);
  
  tft.print(" UTC Date ", 245, 5 + offset);
  tft.print(" UTC Time ", 245, 45 + offset);
  tft.print(" Alt m ", 245, 85 + offset);
  tft.print(" Alt ft ", 245, 125 + offset);
  tft.print(" Spd km/h ", 245, 165 + offset);
  tft.print(" HDOP ", 245, 205 + offset);

  if(gps.hdop.value()>1000)
    tft.setColor(rosso);
    
  tft.print(textDate, 250, 25);
  tft.print(textTime, 250, 65);
  tft.print(textAltM, 250, 105);
  tft.print(textAltF, 250, 145);
  tft.print(textSpeed, 250, 185);
  tft.print(textCourse, 110, 0);
  
  if(gps.hdop.value()>1000)
    tft.setColor(rosso);
  else if(gps.hdop.value()<=1000 && gps.hdop.value()>500)
    tft.setColor(giallo);
  else if(gps.hdop.value()<=500)
    tft.setColor(verde);
  
  tft.print(textHDOP, 250, 225);

  delay(1001);
}
