
char getNum (short x)
{
  return x + segreto ;
}

void creamiastringa()
{
  // salvo i dati dal gps
  float mylat = gps.location.lat() ;
  float mylng = gps.location.lng() ;
  short myalt = gps.altitude.meters() ;
  short myroute = gps.course.deg() ;
  short myspeed = gps.speed.kmph() ;
  short myposage = gps.location.age() ;
  short myhdop = gps.hdop.value() ;
  
  int mytime = (gps.time.second())+(gps.time.minute()*100)+(gps.time.hour()*10000) ;
  
  char mionome[] = miamarca ;
  // inizio costruzione stringa
  // inizializzo la stringa
  for(int i=0; i<52; i++)
    miastringa[i] = 48 ;
  // apro la stringa
  miastringa[0] = '#' ;
  // inserisco marche
  for(int i=0; i<6; i++)
  {
    miastringa[i+1] = mionome[i] ;
  }
  // inserisco latitudine
  if(mylat>=0)
    miastringa[7] = '+' ;
  else
    miastringa[7] = '-' ;
  long latA = (float)(mylat * 1000000) ;
  latA = abs(latA) ;
  miastringa[8] = getNum((latA/pow(10,7))-((latA/100000000)*10)) ;
  miastringa[9] = getNum((latA/pow(10,6))-((latA/10000000)*10)) ;
  miastringa[10] = getNum((latA/pow(10,5))-((latA/1000000)*10)) ;
  miastringa[11] = getNum((latA/pow(10,4))-((latA/100000)*10)) ;
  miastringa[12] = getNum((latA/pow(10,3))-((latA/10000)*10)) ;
  miastringa[13] = getNum((latA/pow(10,2))-((latA/1000)*10)) ;
  miastringa[14] = getNum((latA/pow(10,1))-((latA/100)*10)) ;
  miastringa[15] = getNum((latA/pow(10,0))-((latA/10)*10)) ;
  // inserisco la longitudine
  if(mylng>=0)
      miastringa[16] = '+' ;
  else
      miastringa[16] = '-' ;
  if(mylng<100 && mylng>-100)
    miastringa[17] = '0' ;
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
  miastringa[18] = getNum((lngA/pow(10,7))-((lngA/100000000)*10)) ;
  miastringa[19] = getNum((lngA/pow(10,6))-((lngA/10000000)*10)) ;
  miastringa[20] = getNum((lngA/pow(10,5))-((lngA/1000000)*10)) ;
  miastringa[21] = getNum((lngA/pow(10,4))-((lngA/100000)*10)) ;
  miastringa[22] = getNum((lngA/pow(10,3))-((lngA/10000)*10)) ;
  miastringa[23] = getNum((lngA/pow(10,2))-((lngA/1000)*10)) ;
  miastringa[24] = getNum((lngA/pow(10,1))-((lngA/100)*10)) ;
  miastringa[25] = getNum((lngA/pow(10,0))-((lngA/10)*10)) ;
  //  cout << mylng << "   " << lngA ;
  // inserisco l'altezza dal livello del mare (QNH)
  miastringa[26] = getNum(myalt/1000) ;
  miastringa[27] = getNum((myalt/100)-((myalt/1000)*10));
  miastringa[28] = getNum((myalt/10)-((myalt/100)*10));
  miastringa[29] = getNum((myalt/1)-((myalt/10)*10));
  // inserisco la mi rotta reale
  miastringa[30] = getNum((myroute/100)-((myroute/1000)*10));
  miastringa[31] = getNum((myroute/10)-((myroute/100)*10));
  miastringa[32] = getNum((myroute/1)-((myroute/10)*10));
  // inserisco la velocità al suolo (Ground Speed)
  miastringa[33] = getNum((myspeed/100)-((myspeed/1000)*10));
  miastringa[34] = getNum((myspeed/10)-((myspeed/100)*10));
  miastringa[35] = getNum((myspeed/1)-((myspeed/10)*10));
  // inserisco l'età della mi posizione in ms
  miastringa[36] = getNum((myposage/1000)-((myposage/10000)*10));
  miastringa[37] = getNum((myposage/100)-((myposage/1000)*10));
  miastringa[38] = getNum((myposage/10)-((myposage/100)*10));
  miastringa[39] = getNum((myposage/1)-((myposage/10)*10));
  // inserisco il mio HDOP
  miastringa[40] = getNum((myhdop/1000)-((myhdop/10000)*10));
  miastringa[41] = getNum((myhdop/100)-((myhdop/1000)*10));
  miastringa[42] = getNum((myhdop/10)-((myhdop/100)*10));
  miastringa[43] = getNum((myhdop/1)-((myhdop/10)*10));
  // inserisco il mio tempo zulu gps
  miastringa[44] = getNum((mytime/100000)-((mytime/1000000)*10));
  miastringa[45] = getNum((mytime/10000)-((mytime/100000)*10));
  miastringa[46] = getNum((mytime/1000)-((mytime/10000)*10));
  miastringa[47] = getNum((mytime/100)-((mytime/1000)*10));
  miastringa[48] = getNum((mytime/10)-((mytime/100)*10));
  miastringa[49] = getNum((mytime/1)-((mytime/10)*10));
  // inserisco il tipo di velivolo
  miastringa[50] = getNum ( miotipo ) ;
  // campi liberi
  miastringa[51] = '*' ;
  miastringa[52] = '*' ;
  miastringa[53] = '*' ;
  // eseguo il checksum
  int cks = 0 ;
  for(int i=0; i<54; i++)
      cks = cks + (miastringa[i]);
  cks = cks % 7 ;
  miastringa[54] = getNum(cks);
  // chiudo la stringa
  miastringa[55] = '!' ;
  // fine costruzione stringa
}

