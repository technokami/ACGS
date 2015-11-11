
char getChar (char x)
{
  return x - segreto ;
}

float gettualat (char string[51])
{
  float latB = 0 ;
  // leggo la latitudine
  latB = latB + getChar(string[8])*10 ;
  latB = latB + getChar(string[9])*1 ;
  latB = latB + getChar(string[10])*0.1 ;
  latB = latB + getChar(string[11])*0.01 ;
  latB = latB + getChar(string[12])*0.001 ;
  latB = latB + getChar(string[13])*0.0001 ;
  latB = latB + getChar(string[14])*0.00001 ;
  latB = latB + getChar(string[15])*0.000001 ;
  if(string[7]=='-')
      latB = -latB ;
  
  return latB ;
}

float gettualng (char string[51])
{
  float lngB = 0 ;
  
  lngB = lngB + getChar(string[17])*100 ;
  lngB = lngB + getChar(string[18])*10 ;
  lngB = lngB + getChar(string[19])*1 ;
  lngB = lngB + getChar(string[20])*0.1 ;
  lngB = lngB + getChar(string[21])*0.01 ;
  lngB = lngB + getChar(string[22])*0.001 ;
  lngB = lngB + getChar(string[23])*0.0001 ;
  lngB = lngB + getChar(string[24])*0.00001 ;
  lngB = lngB + getChar(string[25])*0.000001 ;
  if(string[16]=='-')
      lngB = -lngB ;
      
  return lngB ;
}

int gettuaalt (char string[51])
{   
  int altB = 0 ;
  
  altB = altB + getChar(string[26])*1000 ;
  altB = altB + getChar(string[27])*100 ;
  altB = altB + getChar(string[28])*10 ;
  altB = altB + getChar(string[29])*1 ;
  
  return altB ;
}

int gettuaroute (char string[51])
{   
  int routeB = 0 ;
  
  routeB = routeB + getChar(string[30])*100 ;
  routeB = routeB + getChar(string[31])*10 ;
  routeB = routeB + getChar(string[32])*1 ;
  
  return routeB ;
}
    
int gettuaspeed (char string[51])
{   
  int speedB = 0 ;
  
  speedB = speedB + getChar(string[33])*100 ;
  speedB = speedB + getChar(string[34])*10 ;
  speedB = speedB + getChar(string[35])*1 ;
  
  return speedB ;
}
    
int gettuaposage (char string[51])
{   
  int posageB = 0 ;

  posageB = posageB + getChar(string[36])*1000 ;
  posageB = posageB + getChar(string[37])*100 ;
  posageB = posageB + getChar(string[38])*10 ;
  posageB = posageB + getChar(string[39])*1 ;
  
  return posageB ;
}
    
int gettuahdop (char string[51])
{   
  int hdopB = 0 ;

  hdopB = hdopB + getChar(string[40])*1000 ;
  hdopB = hdopB + getChar(string[41])*100 ;
  hdopB = hdopB + getChar(string[42])*10 ;
  hdopB = hdopB + getChar(string[43])*1 ;
  
  return hdopB ;   
}
    
int gettuasec (char string[51])
{   
  int hurB = 0 ;
  int minB = 0 ;
  int secB = 0 ;
  
  hurB = hurB + getChar(string[44])*10 ;
  hurB = hurB + getChar(string[45])*1 ;
  
  minB = minB + getChar(string[46])*10 ;
  minB = minB + getChar(string[47])*1 ;
  
  secB = secB + getChar(string[48])*10 ;
  secB = secB + getChar(string[49])*1 ;
    
  int timeB = secB + (minB*60) + (hurB*3600) ;
  
  return timeB ;
}

bool getcks (char string[51])
{
  int cksck = 0 ;
  for(int i=0; i<54; i++)
      cksck = cksck + (string[i]);
  cksck = cksck % 7 ;
  if(getChar(string[54]) == cksck)
      return true ;
  else
      return false ;    
}

void leggitutto()
{
  delay(5);                                           // attendo cinque millisecondi per il multitasking e per la lettura
  char recivechar = Radio_Port.read();                // incomincio a leggere un carattere alla volta
  if (recivechar == '#')                              // se il carattere è quello chiave
  {
    tuastringa[0]= recivechar ;                       // leggo la stringa
    for(short i=1; i<56; i++)
    {
      delay(2) ;                                      // attendo due millisecondi per il multitasking e per la lettura
      tuastringa[i] = Radio_Port.read();
    }
    stringhe_lette++ ;                                // incremento il numero di stringhe lette
    if(tuastringa[0]=='#' && tuastringa[55]=='!')     // verifico se la stringa letta è valida
    {
      letture_ok++ ;
      if( getcks(tuastringa) )
      {
        cks_ok++ ;
        
        #if defined(Debug)
          Debug_Port.print("stringa ricevuta ok: ");
          for(int i=0; i<52; i++)
            Debug_Port.print(tuastringa[i]) ;  
          Debug_Port.println();
        #endif
        for(int i=0; i<6; i++)
          tuanome[i] = tuastringa[i+1];
        short place = 0 ;
        bool nuovo = false ;
        short match = 0 ;
        do                                          // vedo se c'è lo stesso aereo
        {
          match = 0 ;
          for(int z=0; z<6; z++)
            if(nomi[z][place] == tuanome[z])
              match++ ;
          place++ ;
        } while(match != 6 && place < righematr );
        if(place >= righematr)                      // se non c'è lo stesso aereo cerco un posto vuoto
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

        aria[0][place] = gettuaalt(tuastringa) ;          // altezza    [m]
        aria[1][place] = gettuaroute(tuastringa) ;        // rotta      [°]
        aria[2][place] = gettuaspeed(tuastringa) ;        // velocità   [km/h]
        aria[3][place] = gettuaposage(tuastringa) ;       // etàpos     [millis]
        aria[4][place] = gettuahdop(tuastringa) ;         // hdop       [?]
        aria[5][place] = gps.time.second() + (gps.time.minute()*60) + (gps.time.hour()*3600) ;         // tempo      [sec]
        aria[9][place] = aria[6][place] ; // salvo la vecchia distanza
        aria[6][place] = TinyGPSPlus::distanceBetween(gps.location.lat(), gps.location.lng(), gettualat(tuastringa), gettualng(tuastringa)) ;     // distanza    [m]
        aria[7][place] = TinyGPSPlus::courseTo(gps.location.lat(), gps.location.lng(), gettualat(tuastringa), gettualng(tuastringa)) ;            // angolo      [°]
        
        if(nuovo)
          aria[9][place] = aria[6][place] ; // se è nuovo la vecchia distanza sarà uguale a quella nuova
      }
      else
      {
        errori_cks++ ;                                // incremento il contatore di errori dei cecksum

        #if defined(Debug)
          Debug_Port.print("stringa ricevuta; errore checksum: ");
          for(int i=0; i<52; i++)
            Debug_Port.print(tuastringa[i]) ;  
          Debug_Port.println();
        #endif
      }
    }
    else
    {
      errori_lettura++ ;                              // incemento il contatore di errori delle stringhe

      #if defined(Debug)
        Debug_Port.print("stringa ricevuta; errore lettura: ");
        for(int i=0; i<52; i++)
          Debug_Port.print(tuastringa[i]) ;  
        Debug_Port.println();
      #endif
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
          #ifdef Debug
            Debug_Port.print("delate line: ");
            Debug_Port.println(y) ;
          #endif
          
          for(int x=0; x<10; x++)
            aria[x][y] = 0 ;
          for(int x=0; x<6; x++)
            nomi[x][y] = '_' ;
        }
      }
  }
  #if defined(Debug)
    if(millis() - DoldMillis >= 1000)
    {
      DoldMillis = millis();  
      Debug_Port.println("qualcosa");
    }
  #endif
  #if defined(Debug_aria)
  if(millis() - AoldMillis >= 1500)
  {
    AoldMillis = millis();  
      Debug_Port.println();
      Debug_Port.println("numero   marca   alt  route speed posage hdop  time  dist  ang  difftime");
      for(int y=0; y<righematr; y++)
      {
         Debug_Port.print("riga ") ;  // scrivo il numero di riga
         if(y<10)
         Debug_Port.print(" ") ;
         Debug_Port.print(y) ;
         Debug_Port.print(": ") ;
  
        for(int x=0; x<6; x++)                // scrivo il nome
            Debug_Port.print(nomi[x][y]);
        Debug_Port.print("  ");
        for(int x=0; x<9; x++)                // scrivo i valori
        { 
          printInt(aria[x][y], true , 6);
        }
        Debug_Port.println();
      }
      Debug_Port.println();
  }
  #endif
}

void printInt(int val, bool valid, int len)
{
  char sz[] = "***************************";
  if (valid)
    sprintf(sz, "%ld", val);
  sz[len] = 0;
  for (int i=strlen(sz); i<len; ++i)
    sz[i] = ' ';
  if (len > 0) 
    sz[len-1] = ' ';
  Debug_Port.print(sz);
}
