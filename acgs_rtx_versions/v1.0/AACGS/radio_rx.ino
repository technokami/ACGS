
char getChar (char x)
{
  return x - segreto ;
}

float gettualat (char string[39])
{
  float _latB = 0 ;
  _latB = _latB + getChar(string[10])*10 ;
  _latB = _latB + getChar(string[11])*1 ;
  _latB = _latB + getChar(string[12])*0.1 ;
  _latB = _latB + getChar(string[13])*0.01 ;
  _latB = _latB + getChar(string[14])*0.001 ;
  _latB = _latB + getChar(string[15])*0.0001 ;
  _latB = _latB + getChar(string[16])*0.00001 ;
  if(string[9]=='-')
      _latB = -_latB ;
  return _latB ;
}

float gettualng (char string[39])
{
  float _lngB = 0 ;
  _lngB = _lngB + getChar(string[18])*100 ;
  _lngB = _lngB + getChar(string[19])*10 ;
  _lngB = _lngB + getChar(string[20])*1 ;
  _lngB = _lngB + getChar(string[21])*0.1 ;
  _lngB = _lngB + getChar(string[22])*0.01 ;
  _lngB = _lngB + getChar(string[23])*0.001 ;
  _lngB = _lngB + getChar(string[24])*0.0001 ;
  _lngB = _lngB + getChar(string[25])*0.00001 ;
  if(string[17]=='-')
      _lngB = -_lngB ;
  return _lngB ;
}

int gettuaalt (char string[39])
{   
  int altB = 0 ;
  
  int _altB = 0 ;
  _altB = _altB + getChar(string[26])*1000 ;
  _altB = _altB + getChar(string[27])*100 ;
  _altB = _altB + getChar(string[28])*10 ;
  _altB = _altB + getChar(string[29])*1 ;
  return _altB ;
}

int gettuaroute (char string[39])
{   
  int _routeB = 0 ;
  _routeB = _routeB + getChar(string[30])*100 ;
  _routeB = _routeB + getChar(string[31])*10 ;
  _routeB = _routeB + getChar(string[32])*1 ;
  return _routeB ;
}
    
int gettuaspeed (char string[39])
{   
  int _speedB = 0 ;
  _speedB = _speedB + getChar(string[33])*100 ;
  _speedB = _speedB + getChar(string[34])*10 ;
  _speedB = _speedB + getChar(string[35])*1 ;
  return _speedB ;
}

bool getcks (char string[39])
{
  int cksck = 0 ;
  for(int i=0; i<36; i++)
      cksck = cksck + (string[i]);
  cksck = cksck % 7 ;
  if(string[37] == '*')
      return true;
  if(getChar(string[37]) == cksck)
      return true ;
  else
      return false ;        
}

void leggitutto()
{                                        
  char recivechar = Radio_Port.read(); 
  if (recivechar == '#')                            
  {
    tuastringa[0]= recivechar ;
    for(short i=1; i<39; i++)
    {
      delay(2) ;                
      tuastringa[i] = Radio_Port.read();
    }
    if(tuastringa[0]=='#' && tuastringa[38]=='!')
    {
      if( getcks(tuastringa) )
      {
        for(int i=0; i<6; i++)
          tuanome[i] = tuastringa[i+1];
        short place = 0 ;
        bool nuovo = false ;
        short match = 0 ;
        do                                          
        {
          match = 0 ;
          for(int z=0; z<6; z++)
            if(nomi[z][place] == tuanome[z])
              match++ ;
          place++ ;
        } while(match != 6 && place < righematr );
        if(place >= righematr)                     
        {
          place = -1 ;
          do
          {
           place++ ;
          } while(nomi[0][place] != '_');
          nuovo = true ;
        }

        if(!nuovo) 
          place--;

        for(int i=0; i<6; i++)
          nomi[i][place] = tuanome[i] ;
        aria[0][place] = gettuaalt(tuastringa) ;          
        aria[1][place] = gettuaroute(tuastringa) ; 
        aria[2][place] = gettuaspeed(tuastringa) ;  
        aria[5][place] = gps.time.second() + (gps.time.minute()*60) + (gps.time.hour()*3600) ;
        aria[9][place] = aria[6][place] ;
        aria[6][place] = TinyGPSPlus::distanceBetween(gps.location.lat(), gps.location.lng(), gettualat(tuastringa), gettualng(tuastringa)) ; 
        aria[7][place] = TinyGPSPlus::courseTo(gps.location.lat(), gps.location.lng(), gettualat(tuastringa), gettualng(tuastringa)) ;
        if(nuovo)
          aria[9][place] = aria[6][place] ;
      }

    }

  }
  int mytimesec = gps.time.second() + (gps.time.minute()*60) + (gps.time.hour()*3600) ;
  for(int y=0; y<righematr; y++)
  {
    if(nomi[0][y]!='_' && nomi[5][y]!='_')
      {
        int timediff = mytimesec  - aria[5][y] ;

        aria[8][y] = timediff ;
        
        if(timediff > TTL  )
        {
          for(int x=0; x<10; x++)
            aria[x][y] = 0 ;
          for(int x=0; x<6; x++)
            nomi[x][y] = '_' ;
        }
      }
  }
}

