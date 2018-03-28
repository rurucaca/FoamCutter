#include <LiquidCrystal.h>
#include <MultitapKeypad.h>

const byte ROW0 = 52;
const byte ROW1 = 50;
const byte ROW2 = 48;
const byte ROW3 = 46;
const byte COL0 = 44;
const byte COL1 = 42;
const byte COL2 = 40;
const byte COL3 = 38;

const byte LCD_RS = 30;
const byte LCD_EN = 28;
const byte LCD_D4 = 24;
const byte LCD_D5 = 26;
const byte LCD_D6 = 22;
const byte LCD_D7 = 32;
const byte BACKLIGHT = 3;
const byte BEEP = 2;

// creates lcd as LiquidCrystal object
LiquidCrystal lcd(LCD_RS, LCD_EN, LCD_D4, LCD_D5, LCD_D6, LCD_D7);
// creates kpd as MultitapKeypad object
// for matrix 4 x 3 keypad
// MultitapKeypad kpd( ROW0, ROW1, ROW2, ROW3, COL0, COL1, COL2 );
// for matrix 4 x 4 keypad
MultitapKeypad kpd( ROW0, ROW1, ROW2, ROW3, COL0, COL1, COL2, COL3 );
// creates key as Key object
Key key;

void setup() {
  lcd.begin( 16, 4 );
  pinMode( BACKLIGHT, OUTPUT );
  digitalWrite(BACKLIGHT, LOW );
  lcd.print( F( "Key States Test" ) );
  lcd.setCursor( 0, 1 );
  lcd.print( F( "by ZulNs" ) );
  delay( 5000 );
  lcd.clear();
  lcd.print( F( "Press [*] key..." ) );
  // wait until [*] key has been pressed
  do {
    key = kpd.getKey();
  } while ( key.beforeLastCode != NO_KEY || key.lastCode != KEY_ASTERISK || key.code != NO_KEY );
  tone( BEEP, 4000, 50 );
  lcd.clear();
  //lcd.cursor();
  //lcd.blink();
}

void loop() {
  key = kpd.getKey();
  lcd.setCursor( 0, 0 );
  lcd.print( F( "Key " ) );
  if ( key.character > 0 )
    lcd.print( char( key.character ) );
  else
    lcd.print( F( "?" ) );
  switch (key.state) {
  case KEY_DOWN:
  case MULTI_TAP:
    tone( BEEP, 5000, 20 );
    lcd.print( F( " down" ) );
    if ( key.state == MULTI_TAP ) {
      lcd.setCursor( 0, 1 );
      lcd.print( F( "TapCounter: " ) );
      if ( key.tapCounter < 10 )
        lcd.print( key.tapCounter, DEC );
      else {
        kpd.resetTapCounter();
        lcd.print( '0' );
      }
    }
    break;
  case LONG_TAP:
    tone( BEEP, 5000, 20 );
    lcd.print( F( " hold" ) );
    break;
  case MULTI_KEY_DOWN:
    tone( BEEP, 4000, 100 );
    lcd.print( F( " down" ) );
    break;
  case KEY_UP:
    lcd.print( F( " up  " ) );
  }
  if ( key.state != MULTI_TAP && key.state != KEY_UP ) {
    lcd.setCursor( 0, 1 );
    lcd.print( F( "             " ) );
  }
}
