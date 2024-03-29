/*
  LiquidCrystal Library - Hello World

 Demonstrates the use a 16x2 LCD display.  The LiquidCrystal
 library works with all LCD displays that are compatible with the
 Hitachi HD44780 driver. There are many of them out there, and you
 can usually tell them by the 16-pin interface.

 This sketch prints "Hello World!" to the LCD
 and shows the time.

  The circuit:
 * LCD RS pin to digital pin 12
 * LCD Enable pin to digital pin 11
 * LCD D4 pin to digital pin 5
 * LCD D5 pin to digital pin 4
 * LCD D6 pin to digital pin 3
 * LCD D7 pin to digital pin 2
 * LCD R/W pin to ground
 * LCD VSS pin to ground
 * LCD VCC pin to 5V
 * 10K resistor:
 * ends to +5V and ground
 * wiper to LCD VO pin (pin 3)

 Library originally added 18 Apr 2008
 by David A. Mellis
 library modified 5 Jul 2009
 by Limor Fried (http://www.ladyada.net)
 example added 9 Jul 2009
 by Tom Igoe
 modified 22 Nov 2010
 by Tom Igoe

 This example code is in the public domain.

 http://www.arduino.cc/en/Tutorial/LiquidCrystal
 */

// include the library code:
#include <LiquidCrystal.h>

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

int d1=0;
int n=0,np=0;
int v=0;
int i;

void setup() {
  Serial.begin(9600);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(6, OUTPUT);
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.clear();
  lcd.print("Lights & Fan:");
}

void loop()
{
  // set the cursor to column 0, line 1
  // (note: line 1 is the second row, since counting begins with 0):
  if (Serial.available())
  {
    d1 = Serial.read();
    if (d1==76)
    {
      lcd.setCursor(6, 1);
      lcd.print("     ");
      lcd.setCursor(6, 1);
      lcd.print("Left");
      if (n>0)
      {
        n-=1;
      }
    }
    if (d1==82)
    {
      lcd.setCursor(6, 1);
      lcd.print("     ");
      lcd.setCursor(6, 1);
      lcd.print("Right");
      if (n<3)
      {
        n+=1;
      }
    }
    if (d1==85)
    {
      lcd.setCursor(6, 1);
      lcd.print("     ");
      lcd.setCursor(6, 1);
      lcd.print("Up");
      v=1;
    }
    if (d1==68)
    {
      lcd.setCursor(6, 1);
      lcd.print("     ");
      lcd.setCursor(6, 1);
      lcd.print("Down");
      v=0;
    }
  }
  // print the number of seconds since reset:
  if (n>0 && np<=n)
  {
    digitalWrite(6,HIGH);
    if(n>1 && np<=n)
    {
      digitalWrite(10,HIGH);
      if(n>2 && np<=n)
      {
        digitalWrite(9,HIGH);
      }
      else if (n<3 && np>=n)
      {
        digitalWrite(9,LOW);
      }
    }
    else if (n<2 && np>=n)
    {
      digitalWrite(10,LOW);
    }
  }
  else if (n<1 && np>=n)
  {
    digitalWrite(6,LOW);
  }
  if (v==1)
  {
    digitalWrite(8,HIGH);
  }
  else
  {
    digitalWrite(8,LOW);
  }
  np=n;
}
