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
#include <Scheduler.h>
#include <UTFT.h>

// setup aereo
/* marca o nome del veiviolo o
 * codice icao dell'areoporto o dell'aviosuperfice
 * deve essere di 6 caratteri es:
 * LIPQ --> "_LIPQ_"
 */
#define miamarca "I-9332"

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
#define miotipo 4

// pin setup
#define led_pin_red 8
#define led_pin_vcc 9
#define led_pin_green 10
#define led_pin_blue 11

// colori per tft e led
#define verde   0, 255, 0
#define rosso   255, 0, 0
#define blu     0, 0, 255
#define bianco  255, 255, 255
#define nero    0, 0, 0
#define giallo  255, 255, 0
#define magenta 255, 0, 255
#define ciano   0, 255, 255

// altri setups
#define righematr 15
#define TTL 10

// debug setup
#define Debug               // general debug: GPS + miastringa + rx/tx info
//#define Debug_aria

// serial ports setup
#define GPS_Baud 9600
#define Radio_Baud 9600
#define Debug_Baud 115200
#define GPS_Port Serial3
#define Radio_Port Serial2
#define Debug_Port SerialUSB

// objects declaration
TinyGPSPlus gps;
UTFT tft(ITDB32S,38,39,40,41);

// global variabile/array declaration
unsigned long long DoldMillis = 0 ;
unsigned long long AoldMillis = 0 ;

extern uint8_t SmallFont[];
extern uint8_t BigFont[];

const double pi = 3.141592653589793 ;

unsigned long stringhe_lette = 0 ;
unsigned long errori_lettura = 0 ;
unsigned long errori_cks = 0 ;
unsigned long letture_ok = 0 ;
unsigned long cks_ok = 0 ;

char miastringa[55] ;
char tuastringa[55] ;
char tuanome[6];

char nomi[6][righematr];  // 6xnome
int aria[10][righematr] ;  // altezza, rotta, velocità, etàposizione, hdop, tempo, distanza, angolo

String textmarca = miamarca ;

short angoloAttesa = 0 ; // per rotazione bitmap attesa
bool firstClear = true ; // per la prima pulizia completa dello schermo

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
  
  #if defined(Debug)
    delay(3000);
    Debug_Port.println("BOOTING UP... ");
  #endif

  #if defined(Debug)
    Debug_Port.println("initialization serial ports... ");
  #endif
  GPS_Port.begin(GPS_Baud);
  Radio_Port.begin(Radio_Baud);
  Debug_Port.begin(Debug_Baud);
  #if defined(Debug)
    Debug_Port.print(" ...DONE");
  #endif
  
  #if defined(Debug)
    Debug_Port.println("initialization pins... ");
  #endif
  pinMode(13, OUTPUT) ;
  digitalWrite(13, LOW) ;
  pinMode(led_pin_red, OUTPUT) ;
  pinMode(led_pin_vcc, OUTPUT) ;
  pinMode(led_pin_green, OUTPUT) ;
  pinMode(led_pin_blue, OUTPUT) ;  
  #if defined(Debug)
    Debug_Port.print(" ...DONE");
  #endif
  LED(nero);
  
  #if defined(Debug)
    Debug_Port.println("initialization TFT... ");
  #endif
  tft.InitLCD(LANDSCAPE);
  #if defined(Debug)
    Debug_Port.print(" ...DONE");
  #endif
  
  IntroDisplay();

  #if defined(Debug)
    Debug_Port.println("initialization arrays... ");
  #endif
  for(word i=0; i<56; i++)
    tuastringa[i] = 0 ;

  for(word y=0; y<righematr; y++)
    for(word x=0; x<6; x++)
      nomi[x][y] = '_' ;

  for(word y=0; y<righematr; y++)
    for(word x=0; x<8; x++)
      aria[x][y] = 0 ;
  #if defined(Debug)
    Debug_Port.print(" ...DONE");
  #endif
  
  randomSeed(millis());
  attendigps();
  LED(nero);

  #if defined(Debug)
    Debug_Port.println("starting radio_read loop... ");
  #endif
  Scheduler.startLoop( leggitutto );
  #if defined(Debug)
    Debug_Port.print(" ...DONE");
  #endif
  #if defined(Debug)
    Debug_Port.println("starting main loop... ");
  #endif
}

void loop()                             // INIZIO LOOP PRINCIPALE
{
  leggiGPS(1000);                       // leggo i dati provenienti dal gps

  if(gps.location.isValid())            // se la posizione è valida
  {
    creamiastringa();                   // costruisco la mia stringa
                                        // invio la mia stringa via radio
    for(int i=0; i<56; i++)
      Radio_Port.print(miastringa[i]) ;  
    Radio_Port.println();
    #if defined(Debug)                    // se abilitato il debug scrivo la stringa sulla seriale di debug
      Debug_Port.print("mia stringa: ") ;
      for(int i=0; i<56; i++)
        Debug_Port.print(miastringa[i]) ;  
      Debug_Port.println();
    #endif
  }
  #if defined(Debug)                    // se abilitato il debug
    else
      Debug_Port.println("mia stringa: no GPS fix !!") ;
  #endif
  disegna();                            // disegno la grafica sul display
  delay(random(10, 100));               // aspetto un tempo random per evitare collisioni, overflow o errori in ricezione
}                                       // FINE LOOP PRINCIPALE

