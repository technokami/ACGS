
char getNum (short x)
{
  return x + segreto ;
}

void creamiastringa()
{
  float mylat = gps.location.lat() ;
  float mylng = gps.location.lng() ;
  short myalt = gps.altitude.meters() ;
  short myroute = gps.course.deg() ;
  short myspeed = gps.speed.kmph() ;
  short myposage = gps.location.age() ;
  short myhdop = gps.hdop.value() ;
    
  char mionome[] = miamarca ;
  for(int i=0; i<38; i++)
    miastringa[i] = '*' ;
  miastringa[0] = '#' ;
  for(int i=0; i<8; i++)
    miastringa[i+1] = mionome[i] ;
  if(mylat>=0)
    miastringa[9] = '+' ;
  else
    miastringa[9] = '-' ;
  long latA = (float)(mylat * 1000000) ;
  latA = abs(latA) ;
  miastringa[10] = getNum((latA/pow(10,7))-((latA/100000000)*10)) ;
  miastringa[11] = getNum((latA/pow(10,6))-((latA/10000000)*10)) ;
  miastringa[12] = getNum((latA/pow(10,5))-((latA/1000000)*10)) ;
  miastringa[13] = getNum((latA/pow(10,4))-((latA/100000)*10)) ;
  miastringa[14] = getNum((latA/pow(10,3))-((latA/10000)*10)) ;
  miastringa[15] = getNum((latA/pow(10,2))-((latA/1000)*10)) ;
  miastringa[16] = getNum((latA/pow(10,1))-((latA/100)*10)) ;
  if(mylng>=0)
      miastringa[17] = '+' ;
  else
      miastringa[17] = '-' ;
  if(mylng<100 && mylng>-100)
    miastringa[18] = '0' ;
  else
  {
    if(mylng>=0)
      mylng = mylng - 100 ;
    else
      mylng = mylng + 100 ;
    
    miastringa[17] = '1' ;
  }
  long lngA = (float)(mylng * 1000000) ;
  lngA = abs(lngA) ;
  miastringa[19] = getNum((lngA/pow(10,7))-((lngA/100000000)*10)) ;
  miastringa[20] = getNum((lngA/pow(10,6))-((lngA/10000000)*10)) ;
  miastringa[21] = getNum((lngA/pow(10,5))-((lngA/1000000)*10)) ;
  miastringa[22] = getNum((lngA/pow(10,4))-((lngA/100000)*10)) ;
  miastringa[23] = getNum((lngA/pow(10,3))-((lngA/10000)*10)) ;
  miastringa[24] = getNum((lngA/pow(10,2))-((lngA/1000)*10)) ;
  miastringa[25] = getNum((lngA/pow(10,1))-((lngA/100)*10)) ;
  miastringa[26] = getNum(myalt/1000) ;
  miastringa[27] = getNum((myalt/100)-((myalt/1000)*10));
  miastringa[28] = getNum((myalt/10)-((myalt/100)*10));
  miastringa[29] = getNum((myalt/1)-((myalt/10)*10));
  miastringa[30] = getNum((myroute/100)-((myroute/1000)*10));
  miastringa[31] = getNum((myroute/10)-((myroute/100)*10));
  miastringa[32] = getNum((myroute/1)-((myroute/10)*10));
  miastringa[33] = getNum((myspeed/100)-((myspeed/1000)*10));
  miastringa[34] = getNum((myspeed/10)-((myspeed/100)*10));
  miastringa[35] = getNum((myspeed/1)-((myspeed/10)*10));

  miastringa[36] = miotipo ;
  int cks = 0 ;
  for(int i=0; i<36; i++)
      cks = cks + (miastringa[i]);
  cks = cks % 7 ;
  miastringa[37] = getNum(cks);
  miastringa[38] = '!' ;
}

