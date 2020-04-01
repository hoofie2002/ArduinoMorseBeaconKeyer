/************************************************************************
  Arduino Morse Beacon Keyer
  Copyright (c) 2020 Graeme Hill VK6HIL
  Release under GNU Public Licence
  Release History:
  Release 1: Original Release
*************************************************************************/

#include <Arduino.h>
#include "ArduinoMorseBeaconKeyer.h"

//Constants
#define SerialPort Serial           //Please uncomment this line to use the USB port.

const int TIME_UNIT = 125;
const int DOT = TIME_UNIT;
const int DASH = 3 * TIME_UNIT;
const int SYMBOL_SPACE = TIME_UNIT;
const int LETTER_SPACE = 3 * TIME_UNIT - SYMBOL_SPACE;
const int WORD_SPACE = 7 * TIME_UNIT - LETTER_SPACE;

const int relayPin = 5;                   // Pin used for relay

const char* callsign = "de vk6hil/b of78 73\0";               // My Callsign

void setup()
{
    // Set relay pin to output and set it LOW
    pinMode(relayPin, OUTPUT);
    pinMode(13, OUTPUT);
    // Initiate Serial Line
    SerialPort.begin(9600);
    SerialPort.println("Arduino Morse Beacon v0.1") ;
    SerialPort.println("Graeme Hill <vk6hil>") ;
    SerialPort.println("Email hoofie2002@gmail.com or find me on QRZ") ;
    SerialPort.println("") ;
}

void loop()
{
  int size = strlen(callsign);

  //loop through the callsign
  for (int i = 0; i < size; i++)
  {
    
    const char* ch = strchr(characters, tolower(callsign[i]));    
    if (ch != NULL)
    {
      int index = (int)(ch - characters);    
      const char* morseSymbols = mappings[index];
      int count = strlen(morseSymbols);

      for (int i = 0; i < count; i++)
      {
        digitalWrite(relayPin, HIGH);
        digitalWrite(13, HIGH);
        
        int symbolTime;
        char symbol = morseSymbols[i];
        if (symbol == '.')
          symbolTime = DOT;
        else
          symbolTime = DASH; 
        
        delay(symbolTime);
        digitalWrite(relayPin, LOW);
        digitalWrite(13, LOW);
        delay(SYMBOL_SPACE);
      }
      delay(LETTER_SPACE);        
    }
  }
  delay(WORD_SPACE);
}
