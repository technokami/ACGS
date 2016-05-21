/*
 Copyright (C) 2015 Cussigh Matteo
 This program is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 You should have received a copy of the GNU General Public License
 along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */


// includo le librerie
#include <TinyGPS++.h>
#include <UTFT.h>

// setup aereo
/* marca o nome del veiviolo o
 * codice icao dell'areoporto o dell'aviosuperfice
 * deve essere di 6 caratteri es:
 * LIPQ --> "_LIPQ_"
 */
#define miamarca "I-9332__"

/* tipo di oggetto:
 *  0 sconosciuto o militare
 *  1 pallone aereostatico
 *  2 dirigibile
 *  3 aliante
 *  4 ultraleggiero o certificato (vds e ppl)
 *  5 aviazione generale (commerciale)
 *  6 elicottero
 *  7 autogiro
 *  8 aviosuperfice o aereoporto civile o militare
 *  9 parapendio, paramotore, paracarello, deltaplano
 */
#define miotipo '4'



#define verde   0, 255, 0
#define rosso   255, 0, 0
#define blu     0, 0, 255
#define bianco  255, 255, 255
#define nero    0, 0, 0
#define giallo  255, 255, 0
#define magenta 255, 0, 255
#define ciano   0, 255, 255

#define righematr 15
#define TTL 10
#define scala 50

#define GPS_Baud 9600
#define Radio_Baud 9600
#define GPS_Port Serial3
#define Radio_Port Serial2

TinyGPSPlus gps;
UTFT tft(ITDB32S,38,39,40,41);

unsigned long long TxOldMillis = 0 ;
unsigned long long TFTOldMillis = 0 ;
unsigned long long GpsOldMillis = 0 ;
unsigned int TxInterval = 0 ;

extern uint8_t SmallFont[];
extern uint8_t BigFont[];

char miastringa[39] ;
char tuastringa[39] ;
char tuanome[6];

String textmarca = miamarca ;

char nomi[6][righematr];
int aria[10][righematr] ; 

short angoloAttesa = 0 ;
bool firstClear = true ; 

int offset = 5 ;

short oldtextDatelength = 0 ;
short oldtextTimelength = 0 ;
short oldtextAltMlength = 0 ;
short oldtextAltFlength = 0 ;
short oldtextSpeedlength = 0 ;
short oldtextHDOPlength = 0 ;
short oldtextCourselength = 0 ;

extern unsigned short logo_gpx[0x2710];
extern unsigned short attesa[0x9C4];

void setup()
{

 
  GPS_Port.begin(GPS_Baud);
  Radio_Port.begin(Radio_Baud);

  pinMode(13, OUTPUT) ;
  digitalWrite(13, LOW) ;
  pinMode(8, OUTPUT) ;
  pinMode(9, OUTPUT) ;
  pinMode(10, OUTPUT) ;
  pinMode(11, OUTPUT) ;  

  LED(nero);

  tft.InitLCD(LANDSCAPE);
  
  IntroDisplay();
  attendigps(); 

  for(word i=0; i<38; i++)
    tuastringa[i] = 0 ;

  for(word y=0; y<righematr; y++)
    for(word x=0; x<6; x++)
      nomi[x][y] = '_' ;

  for(word y=0; y<righematr; y++)
    for(word x=0; x<8; x++)
      aria[x][y] = 0 ;

  randomSeed(millis());
  
  LED(nero); 

}

void loop()
{
  leggitutto();
  
  if(millis() - GpsOldMillis >= 1000)
  {
    GpsOldMillis = millis();  
    while (GPS_Port.available())
      gps.encode(GPS_Port.read());
  }

  if(millis() - TxOldMillis >= TxInterval)
  {
    TxInterval = 1357 + random(10, 100) ;
    TxOldMillis = millis();   

    if(gps.location.isValid())
    {
      creamiastringa();
      for(int i=0; i<39; i++)
        Radio_Port.print(miastringa[i]) ;  
      Radio_Port.println();
    }
  }
  
  if(millis() - TFTOldMillis >= 1000)
  {
    TFTOldMillis = millis();   
    disegna();
  }
}

