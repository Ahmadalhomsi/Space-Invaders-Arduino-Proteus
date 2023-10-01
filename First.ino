#include <Adafruit_SSD1306.h>
#include <splash.h>


#include <Adafruit_GFX.h>
#include <Wire.h>


// Ahmad
bool MenuS = true;
int MenuInd = 0;
int zorluk = 1;
int skor = 0;

// DISPLAY SETTINGS
#define OLED_ADDRESS 0x3C
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

// Input settings
#define FIRE_BUT 4
#define RIGHT_BUT 3
#define LEFT_BUT 2

// Alien Settings

#define X_START_OFFSET 6
int SBAC = 5; // Space Between Alien Columns
#define SPACE_BETWEEN_ROWS 8
#define INVADERS_DROP_BY 1            // pixel amount that invaders move down by
#define INVADERS_SPEED 6             // speed of movement, lower=faster.
#define INVADER_HEIGHT 6
#define EXPLOSION_GFX_TIME 7  // How long an ExplosionGfx remains on screen before dissapearing

// Player settingsc
#define TANKGFX_WIDTH 8
#define TANKGFX_HEIGHT 6
#define PLAYER_X_MOVE_AMOUNT 2
int lives = 3;
int silah = 3;
boolean dokunulmazlik = false;
#define PLAYER_Y_START 120
#define PLAYER_X_START 0

#define MISSILE_HEIGHT 8
#define MISSILE_WIDTH 2
#define MISSILE_SPEED 6

// Status of a game object constants
#define ACTIVE 0
#define EXPLODING 1
#define DESTROYED 2

unsigned int matris [8] [16];
// Player = 9, Alien 1,2, Odul = 3


// graphics
// aliens

const unsigned char InvaderTopGfx [] PROGMEM = {
  B00000000,
  B11111111,
  B11111111,
  B11011011,
  B11111111,
  B00100100,
  B01011010,
  B10100101
};

const unsigned char PROGMEM InvaderMiddleGfx [] = // odul puani
{
  B11111111, B11111111,
  B11111111, B11111111,
  B11111111, B11111111,
  B11111111, B11111111,
  B11111111, B11111111,
  B11111111, B11111111,
  B11111111, B11111111,
  B11111111, B11111111
};

const unsigned char PROGMEM InvaderBottomGfx [] = {
  B00000011, B11000000,
  B00000111, B11100000,
  B00001111, B11110000,
  B00011111, B11111000,
  B00001111, B11110000,
  B00000111, B11100000,
  B00000011, B11000000,
  B00000001, B10000000
};


const unsigned char PROGMEM InvaderDokunulmazlikGfx [] = { // dokunulmazlik
  B11111111, B00000000,
  B11000011, B11000011,
  B11000011, B11000011,
  B11000011, B11000011,
  B11000011, B11000011,
  B11000011, B11000011,
  B11111111, B11000011,
  B11111111, B11111111
};

const unsigned char PROGMEM InvaderSilahGfx [] = { // Silah GFX 6
  B11111111, B11111111,
  B11000011, B11000011,
  B11111111, B11000011,
  B11111111, B11000011,
  B11000011, B11000011,
  B11000011, B11000011,
  B11111111, B11000011,
  B11111111, B11111111
};

/*
  const unsigned char PROGMEM InvaderBottomGfx [] = {
  B00001111, B00000000,
  B01111111, B11100000,
  B11111111, B11110000,
  B11100110, B01110000,
  B11111111, B11110000,
  B00111001, B11000000,
  B01100110, B01100000,
  B00110000, B11000000
  };

*/


static const unsigned char PROGMEM ExplosionGfx [] = {
  B00001000, B10000000,
  B01000101, B00010000,
  B00100000, B00100000,
  B00010000, B01000000,
  B11000000, B00011000,
  B00010000, B01000000,
  B00100101, B00100000,
  B01001000, B10010000
};

// Player grafix
const unsigned char PROGMEM TankGfx [] = {
  B00011000, B00011000,
  B00111100, B00111100,
  B01111110, B01111110,
  B01111111, B11111111,
  B11111111, B11111111,
  B11110000, B00000000,
  B11110000, B00000000,
  B11110000, B00000000,
};

static const unsigned char PROGMEM MissileGfx [] = {
  B10000000,
  B10000000,
  B10000000,
  B10000000

};


// Game structures

struct GameObjectStruct  {
  // base object which most other objects will include
  signed int X;
  signed int Y;
  unsigned char Status;  //0 active, 1 exploding, 2 destroyed
};

struct AlienStruct  {
  GameObjectStruct Ord;
  unsigned char ExplosionGfxCounter; // how long we want the ExplosionGfx to last
  int AlienLives;
  int AlienType;
};

struct PlayerStruct  {
  GameObjectStruct Ord;
};


// general global variables
#include <Wire.h>
Adafruit_SSD1306 display(128, 64, &Wire, -1);


//alien global vars
//The array of aliens across the screen
AlienStruct  Alien[8][16];


// widths of aliens
// as aliens are the same type per row we do not need to store their graphic width per alien in the structure above
// that would take a byte per alien rather than just three entries here, 1 per row, saving significnt memory
byte AlienWidth[] = {7, 7, 7}; // top, middle ,bottom widths // {8, 11, 12}



// Player global variables
PlayerStruct Player;
GameObjectStruct Missile;
GameObjectStruct Missile2;
GameObjectStruct Missile3;

int InitDown = -1;


void setup()
{

  display.setRotation(1);
  //display.invertDisplay(true);

  display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDRESS);


  Serial.begin(9600);

  pinMode(RIGHT_BUT, INPUT_PULLUP);
  pinMode(LEFT_BUT, INPUT_PULLUP);
  pinMode(FIRE_BUT, INPUT_PULLUP);

  // 7 Segment
  pinMode(22, OUTPUT);
  pinMode(23, OUTPUT);
  pinMode(24, OUTPUT);
  pinMode(25, OUTPUT);
  pinMode(26, OUTPUT);
  pinMode(27, OUTPUT);
  pinMode(28, OUTPUT);

  pinMode(29, OUTPUT);
  pinMode(30, OUTPUT);
  pinMode(31, OUTPUT);
  pinMode(32, OUTPUT);
  pinMode(33, OUTPUT);
  pinMode(34, OUTPUT);
  pinMode(35, OUTPUT);

  pinMode(36, OUTPUT);
  pinMode(37, OUTPUT);
  pinMode(38, OUTPUT);
  pinMode(39, OUTPUT);
  pinMode(40, OUTPUT);
  pinMode(41, OUTPUT);
  pinMode(42, OUTPUT);

  //----

  // LED // Can Hakki
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);

  // LED // Silah Hakki
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);

  // Potentiometre
  pinMode(A1, OUTPUT);


  // Buzzer
  pinMode(A2, OUTPUT);

  // Move Initilized missiles out
  Missile.X = 150;
  Missile.Y = 150;
  Missile2.X = 150;
  Missile2.Y = 150;
  Missile3.X = 150;
  Missile3.Y = 150;

  //
  MenuShow();
  InitAliens(0);
  InitPlayer();

}


long previousMillis2 = 0; // for Alien Respawn
long previousMillis4 = 0; // for Alien Control
long previousMillis5 = 0; // for 10 Sec Speed Control

void loop()
{
  /*
    for (int contrast = 255; contrast >= 0; contrast--) {
    display.ssd1306_command(SSD1306_SETCOMPINS);
    display.ssd1306_command(SSD1306_SETCONTRAST);
    display.ssd1306_command(contrast);
    display.display();
    delay(10);
    }
  */
  //digitalWrite(10,HIGH);




  LDR();


  if (!MenuS)
  {
    UpdateDisplay();
    AlienRespawn();
    Physics();
    LivesCheck();
    SilahCheck();
    GameSpeed();
  }
  else
  {
    MenuShow();
    previousMillis2 = millis();
    previousMillis4 = millis() - 500;
    previousMillis5 = millis();
  }
  //Serial.println("Hello");

}

void clearAll()
{
  for (int Down = 0; Down < 16; Down++)
  {
    for (int Across = 0; Across < 8; Across++)
    {
      Alien[Across][Down].AlienType = 0;
    }
  }

}

void Physics()  {
  AlienControl();
  PlayerControl();
  MissileControl();
  CheckCollisions();
  DokCheck(); // Dokunulmazlik Checker

}




void SilahCheck()
{


  if (silah >= 3)
  {
    digitalWrite(5, HIGH);
    digitalWrite(6, HIGH);
    digitalWrite(7, HIGH);

  }

  else if (silah == 2)
  {
    digitalWrite(5, HIGH);
    digitalWrite(6, HIGH);
    digitalWrite(7, LOW);

  }

  else if (silah == 1)
  {
    digitalWrite(5, HIGH);
    digitalWrite(6, LOW);
    digitalWrite(7, LOW);

  }

  else
  {
    digitalWrite(5, LOW);
    digitalWrite(6, LOW);
    digitalWrite(7, LOW);

  }

}


void LivesCheck()
{
  if (lives >= 4)
  {
    digitalWrite(10, HIGH);
    digitalWrite(11, HIGH);
    digitalWrite(12, HIGH);
    digitalWrite(13, HIGH);
  }

  else if (lives == 3)
  {
    digitalWrite(10, HIGH);
    digitalWrite(11, HIGH);
    digitalWrite(12, HIGH);
    digitalWrite(13, LOW);
  }

  else if (lives == 2)
  {
    digitalWrite(10, HIGH);
    digitalWrite(11, HIGH);
    digitalWrite(12, LOW);
    digitalWrite(13, LOW);
  }

  else if (lives == 1)
  {
    digitalWrite(10, HIGH);
    digitalWrite(11, LOW);
    digitalWrite(12, LOW);
    digitalWrite(13, LOW);
  }

  else
  {
    digitalWrite(10, LOW);
    digitalWrite(11, LOW);
    digitalWrite(12, LOW);
    digitalWrite(13, LOW);
  }

}


void LDR()
{
  int sensorValue = analogRead(A0);
  if (sensorValue >= 50)
  {
    display.invertDisplay(true);
  }
  else
  {
    display.invertDisplay(false);
  }
}




long interval3 = 3003;
long previousMillis3 = 0;

void DokCheck()  { // Dokunulmazlik Checker

  unsigned long currentMillis = millis();

  if ((currentMillis - previousMillis3 > interval3) && (dokunulmazlik == true)) {
    previousMillis3 = currentMillis;
    //Player.Ord.Y -= 1;
    dokunulmazlik = false;
    Serial.println("QWQWQWQQWQWQWQWQWQWQWQWQWWQ");
  }

}


long interval2 = 1000; // for Alien Respawn
long interval4 = 1000; // for Alien Control

//int a = 60; XXXXXX



void AlienRespawn()  {

  unsigned long currentMillis2 = millis();

  if (currentMillis2 - previousMillis2 > interval2) {
    previousMillis2 = currentMillis2;
    Serial.println("Respawned");
    InitAliens(0);
  }

}

long interval5 = 10003;

// Ahmad Methods
void GameSpeed()
{
   unsigned long currentMillis5 = millis();

  if ((currentMillis5 - previousMillis5 > interval5) && (zorluk == 2)) {
    previousMillis5 = currentMillis5;
    Serial.println("55555555555555555555555555555555555555555555555555555555555");
    interval2 -= (interval2 * 0.2);
  interval4 -= (interval4 * 0.2);
  }

  
}


void MenuShow()
{

  if (MenuInd == 0)
  {
    display.clearDisplay();
    display.setTextSize(0);
    display.setTextColor(WHITE);
    display.setCursor(-30, 10);
    // Display static text
    display.println("    -> Baslat\n");
    display.print("  Zorluk \n\n  = ");
    display.print(zorluk);
    display.display();
  }


  if ((digitalRead(FIRE_BUT) == 0) && (MenuInd == 0))
  {
    delay(400);
    MenuS = false;
  }

  if ((digitalRead(FIRE_BUT) == 0) && (MenuInd == 1))
  {
    delay(400);

    if (zorluk == 1)
    {
      zorluk = 2;

    }


    else
      zorluk = 1;


    display.clearDisplay();
    display.setTextSize(0);
    display.setTextColor(WHITE);
    display.setCursor(-30, 10);
    // Display static text
    display.println("       Baslat\n");
    display.print("> Zorluk \n\n  = ");
    display.print(zorluk);
    display.display();

  }

  if ((digitalRead(RIGHT_BUT) == 0))
  {
    display.clearDisplay();
    display.setTextSize(0);
    display.setTextColor(WHITE);
    display.setCursor(-30, 10);
    // Display static text
    display.println("       Baslat\n");
    display.print("> Zorluk \n\n  = ");
    display.print(zorluk);
    display.display();
    MenuInd = 1;
  }
  if ((digitalRead(LEFT_BUT) == 0))
  {
    display.clearDisplay();
    display.setTextSize(0);
    display.setTextColor(WHITE);
    display.setCursor(-30, 10);
    // Display static text
    display.println("    -> Baslat\n");
    display.print("  Zorluk \n\n  = ");
    display.print(zorluk);
    display.display();
    MenuInd = 0;
  }

}
// End Of MenuShow()


void PlayerControl()  {
  // user input checks

  int v = analogRead(A1);
  //Serial.println(v);


  if (1000 < v && v < 1030)
    Player.Ord.X = 56;

  else if (900 < v && v < 920)
    Player.Ord.X = 48;

  else if (700 < v && v < 750)
    Player.Ord.X = 40;

  else if (580 < v && v < 650)
    Player.Ord.X = 32;

  else if (500 < v && v < 550)
    Player.Ord.X = 24;

  else if (440 < v && v < 470)
    Player.Ord.X = 16;

  else if (390 < v && v < 420)
    Player.Ord.X = 8;

  else if (300 < v && v < 380)
    Player.Ord.X = 0;




  if ((digitalRead(RIGHT_BUT) == 0) & (Player.Ord.X + TANKGFX_WIDTH < SCREEN_WIDTH))
    Player.Ord.X += (64 / 8);
  if ((digitalRead(LEFT_BUT) == 0) & (Player.Ord.X > 0))
    Player.Ord.X -= (64 / 8);
  if ((digitalRead(FIRE_BUT) == 0) & (Missile.Status != ACTIVE) && (silah == 3)) // && (silah!=0)
  {
    silah--;
    Missile.X = Player.Ord.X + (TANKGFX_WIDTH / 2);
    Missile.Y = Player.Ord.Y;
    Missile.Status = ACTIVE;
    delay(400);
    previousMillis2 += 400;
    previousMillis4 += 400;
  }
  else if ((digitalRead(FIRE_BUT) == 0) & (Missile2.Status != ACTIVE) && (silah == 2))
  {
    silah--;
    Missile2.X = Player.Ord.X + (TANKGFX_WIDTH / 2);
    Missile2.Y = Player.Ord.Y;
    Missile2.Status = ACTIVE;
    delay(400);
    previousMillis2 += 400;
    previousMillis4 += 400;
  }
  else if ((digitalRead(FIRE_BUT) == 0) & (Missile3.Status != ACTIVE) && (silah == 1))
  {
    silah--;
    Missile3.X = Player.Ord.X + (TANKGFX_WIDTH / 2);
    Missile3.Y = Player.Ord.Y;
    Missile3.Status = ACTIVE;
    delay(400);
    previousMillis2 += 400;
    previousMillis4 += 400;
  }

  /*
    Serial.println(Player.Ord.X);
    Serial.println(Player.Ord.Y);
  */

}

void MissileControl()
{
  if ((Missile.Status == ACTIVE))
  {

    Missile.Y -= MISSILE_SPEED;
    if (Missile.Y + MISSILE_HEIGHT < 0)  // If off top of screen destroy so can be used again
      Missile.Status = DESTROYED;
  }
  if ((Missile2.Status == ACTIVE))
  {

    Missile2.Y -= MISSILE_SPEED;
    if (Missile2.Y + MISSILE_HEIGHT < 0)  // If off top of screen destroy so can be used again
      Missile2.Status = DESTROYED;
  }
  if ((Missile3.Status == ACTIVE))
  {

    Missile3.Y -= MISSILE_SPEED;
    if (Missile3.Y + MISSILE_HEIGHT < 0)  // If off top of screen destroy so can be used again
      Missile3.Status = DESTROYED;
  }

}




void AlienControl()
{
  unsigned long currentMillis4 = millis();

  if (currentMillis4 - previousMillis4 > interval4) {
    previousMillis4 = currentMillis4;
    

    // update the alien postions
    for (int Down = 0; Down < 16; Down++)
    {
      for (int Across = 0; Across < 8; Across++)
      {
        if ((Alien[Across][Down].Ord.Status == ACTIVE) && (Alien[Across][Down].AlienType != 0))
        {
          /*
            if (Dropped == false)
            Alien[Across][Down].Ord.X += AlienXMoveAmount;
            else
          */
          Alien[Across][Down].Ord.Y += (128 / 16);


        }
      }
      
    }

    segmsInc();

  }
}


void CheckCollisions()
{
  MissileAndAlienCollisions();

  // Ahmad
  /*
    Serial.println("Player:");
    Serial.println(Player.Ord.X);
    Serial.println(Player.Ord.Y);// Alien[Across][Down].Ord.X

    Serial.println("Alien:");
    Serial.println(Alien[0][0].Ord.X);
    Serial.println(Alien[0][0].Ord.Y);
  */
  // 13 8

  Serial.println("--------");

  //delay(250);

  /*
    for (int Across = 0; Across < NAC; Across++)
    {
    for (int Down = 0; Down < 3; Down++)
    {

        if ( (Alien[Across][Down].Ord.X == Player.Ord.X) && ((Alien[Across][Down].Ord.Y +10) == Player.Ord.Y) )
        {
          MenuS = true;
          setup();
        }

    }
    }
  */


}


//555555
void MissileAndAlienCollisions() // And Player Collision
{

  for (int across = 0; across < 8; across++)
  {
    for (int down = 0; down < 16; down++)
    {
      if (Alien[across][down].Ord.Status == ACTIVE)
      {
        if (Missile.Status == ACTIVE)
        {
          if (Collision(Missile, MISSILE_WIDTH, MISSILE_HEIGHT, Alien[across][down].Ord, AlienWidth[Alien[across][down].AlienType - 1], INVADER_HEIGHT))
          {
            if ((Alien[across][down].AlienType != 2) && (Alien[across][down].AlienType != 4))
            {
              if ((Alien[across][down].AlienLives == 0) )
              {
                // missile hit
                Alien[across][down].Ord.Status = EXPLODING;
                Missile.Status = DESTROYED;
                Serial.println("Destroyed");
                Serial.println(across);
                Serial.println(down);
              }
              else
              {
                Alien[across][down].AlienLives = 0;
                Missile.Status = DESTROYED;
              }
            }


          }

        }

        if (Missile2.Status == ACTIVE)
        {
          if (Collision(Missile2, MISSILE_WIDTH, MISSILE_HEIGHT, Alien[across][down].Ord, AlienWidth[Alien[across][down].AlienType - 1], INVADER_HEIGHT))
          {
            if (Alien[across][down].AlienType != 2)
            {
              if ((Alien[across][down].AlienLives == 0) )
              {
                // missile hit
                Alien[across][down].Ord.Status = EXPLODING;
                Missile2.Status = DESTROYED;
                Serial.println("Destroyed");
                Serial.println(across);
                Serial.println(down);
              }
              else
              {
                Alien[across][down].AlienLives = 0;
                Missile2.Status = DESTROYED;
              }
            }


          }

        }

        if (Missile3.Status == ACTIVE)
        {
          if (Collision(Missile3, MISSILE_WIDTH, MISSILE_HEIGHT, Alien[across][down].Ord, AlienWidth[Alien[across][down].AlienType - 1], INVADER_HEIGHT))
          {
            if (Alien[across][down].AlienType != 2)
            {
              if ((Alien[across][down].AlienLives == 0) )
              {
                // missile hit
                Alien[across][down].Ord.Status = EXPLODING;
                Missile3.Status = DESTROYED;
                Serial.println("Destroyed");
                Serial.println(across);
                Serial.println(down);
              }
              else
              {
                Alien[across][down].AlienLives = 0;
                Missile3.Status = DESTROYED;
              }
            }


          }

        }

        if (Collision(Player.Ord, 8, 6, Alien[across][down].Ord, 7, INVADER_HEIGHT)) // 13 8 Actually W H // AlienWidth[down]
        {
          /*
            Serial.print("TEEEEEEEEEEEEEEEEEEEEEEEEEST: "); // Alien[across][down].AlienType
            Serial.println(Alien[across][down].AlienType);
          */
          if (((Alien[across][down].AlienType == 1) || (Alien[across][down].AlienType == 3)) && (dokunulmazlik == false))
          {
            // HIIIIT
            Serial.print("The Player is Crashed with: ");
            Serial.println(Alien[across][down].AlienType);
            if (lives == 0)
            {
              tone(A2, 6000); // 600 mhz
              delay(400);
              noTone(A2);

              Serial.println("Lives: 0");
              skor = 0;
              lives = 3;
              silah = 3;
              MenuS = true;
              Alien[across][down].AlienType = 0; // empty
              MenuShow();
              clearAll();
            }
            else
            {
              tone(A2, 2000); // 600 mhz
              delay(200);
              noTone(A2);

              lives--;
              Serial.print("Lives: ");
              Serial.println(lives);
              Alien[across][down].AlienType = 0; // empty
            }
            dokunulmazlik = true;
            previousMillis3 = millis();
          }
          // Odul Puani
          else if (Alien[across][down].AlienType == 2)
          {
            Serial.println("Odul Puani Kazandiniz");
            Alien[across][down].AlienType = 0; // empty
            lives++;

          }
          // Dokunulmazlik
          else if (Alien[across][down].AlienType == 4)
          {
            Serial.println("AAAAAAAAAAAAAAAAAAAAAAAAAAAAA Dokunulmazlik");
            Alien[across][down].AlienType = 0; // empty
            dokunulmazlik = true;
            previousMillis3 = millis();

          }
          // Silah
          else if (Alien[across][down].AlienType == 5)
          {
            Serial.println("SSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSS Silah");
            Alien[across][down].AlienType = 0; // empty
            silah++;

          }


        }
      }
    }
  }
}

bool Collision(GameObjectStruct Obj1, unsigned char Width1, unsigned char Height1, GameObjectStruct Obj2, unsigned char Width2, unsigned char Height2)
{
  return ((Obj1.X + Width1 > Obj2.X) & (Obj1.X < Obj2.X + Width2) & (Obj1.Y + Height1 > Obj2.Y) & (Obj1.Y < Obj2.Y + Height2));
}




void UpdateDisplay()
{


  display.clearDisplay();
  for (int across = 0; across < 8; across++)
  {
    for (int down = 0; down < 16; down++)
    {
      int type = Alien[across][down].AlienType;

      if (Alien[across][down].Ord.Status == ACTIVE) {
        switch (type)  {
          case 0: //Empty - Space

            break;
          case 1:

            display.drawBitmap(Alien[across][down].Ord.X, Alien[across][down].Ord.Y,  InvaderTopGfx, AlienWidth[type - 1], INVADER_HEIGHT, WHITE);

            break;
          case 2:

            display.drawBitmap(Alien[across][down].Ord.X, Alien[across][down].Ord.Y,  InvaderMiddleGfx, AlienWidth[type - 1], INVADER_HEIGHT, WHITE);

            break;
          case 3:

            display.drawBitmap(Alien[across][down].Ord.X, Alien[across][down].Ord.Y,  InvaderBottomGfx, AlienWidth[type - 1], INVADER_HEIGHT, WHITE); /////////  AlienWidth[down]
            break;

          case 4:
            // InvaderDokunulmazlikGfx
            display.drawBitmap(Alien[across][down].Ord.X, Alien[across][down].Ord.Y,  InvaderDokunulmazlikGfx, 7, INVADER_HEIGHT, WHITE);
            break;

          case 5:
            // InvaderDokunulmazlikGfx
            display.drawBitmap(Alien[across][down].Ord.X, Alien[across][down].Ord.Y,  InvaderSilahGfx, 7, INVADER_HEIGHT, WHITE); // InvaderSilahGfx
            break;

          default:
            Serial.println("DEFAUUUUUUUULT TYPE**");
            break;

        }
      }
      else  {
        if (Alien[across][down].Ord.Status == EXPLODING) {
          Alien[across][down].ExplosionGfxCounter--;
          if (Alien[across][down].ExplosionGfxCounter > 0)  {
            display.drawBitmap(Alien[across][down].Ord.X, Alien[across][down].Ord.Y,  ExplosionGfx, 8, 6, WHITE);
          }
          else
            Alien[across][down].Ord.Status = DESTROYED;
        }
      }

    }
  }

  // player
  display.drawBitmap(Player.Ord.X, Player.Ord.Y,  TankGfx, TANKGFX_WIDTH, TANKGFX_HEIGHT, WHITE);
  //missile
  if (Missile.Status == ACTIVE)
    display.drawBitmap(Missile.X, Missile.Y,  MissileGfx, MISSILE_WIDTH, MISSILE_HEIGHT, WHITE);

  if (Missile2.Status == ACTIVE)
    display.drawBitmap(Missile2.X, Missile2.Y,  MissileGfx, MISSILE_WIDTH, MISSILE_HEIGHT, WHITE);

  if (Missile3.Status == ACTIVE)
    display.drawBitmap(Missile3.X, Missile3.Y,  MissileGfx, MISSILE_WIDTH, MISSILE_HEIGHT, WHITE);

  display.display();
}


void InitPlayer()  {
  Player.Ord.Y = PLAYER_Y_START;
  Player.Ord.X = PLAYER_X_START;
  Missile.Status = DESTROYED;
  Serial.println(PLAYER_X_START);
  Serial.println(PLAYER_Y_START);
  Serial.println("Player Initilized");
  matris[0][15] = 9; // Player LOC
}


void InitAliens(int YStart)  {


  SBAC = 0; // Space Between Aliens

  if (InitDown == 15)
  {
    InitDown = 0;
    Serial.println("XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX");
    previousMillis2 = millis();
  }
  else
  {
    InitDown++;
  }
  // resotre deletetion the else



  for (int across = 0; across < 8; across++)  {

    int type = random(1, 6); // this should be randommmmmmmmxxxxxx
    // Uzay copu = 0, Meteor = 1


    //Serial.println("Alien row");
    // we add down to centralise the aliens, just happens to be the right value we need per row!
    // we need to adjust a little as row zero should be 2, row 1 should be 1 and bottom row 0
    Alien[across][InitDown].Ord.X = SBAC; // AlienWidth[across]




    Alien[across][InitDown].Ord.Y = 0;

    Alien[across][InitDown].Ord.Status = ACTIVE;
    Alien[across][InitDown].ExplosionGfxCounter = EXPLOSION_GFX_TIME;
    Alien[across][InitDown].AlienType = type;
    matris[across][InitDown] = type; // Alien LOC;

    /*
    Serial.println("-*-*-*-*-*-*-*");
    Serial.println(Alien[across][InitDown].Ord.X);
    Serial.println(Alien[across][InitDown].Ord.Y);
    */

    if (type == 3)
    {
      Alien[across][InitDown].AlienLives = 1;
    }
    else
    {
      Alien[across][InitDown].AlienLives = 0;
    }


    SBAC += (64 / 8);


  }


  Alien[random(0, 8)][InitDown].AlienType = 0;




}


/// SEGMENT AREA

void segmsInc()
{
  skor++;

  oneSegm1Inc(skor % 10, 0);
  oneSegm1Inc((skor / 10) % 10, 1);
  oneSegm1Inc(skor / 100, 2);

  if(skor%14==0)
  {
    lives++;
    silah++;
  }

}

int a = 22; // Pinleri tanımlıyoruz
int b = 23;
int c = 24;
int d = 25;
int e = 26;
int f = 27;
int g = 28;

void oneSegm1Inc(int s, int digit)
{
  if (digit == 0)
  {
    a = 22; // Pinleri tanımlıyoruz
    b = 23;
    c = 24;
    d = 25;
    e = 26;
    f = 27;
    g = 28;
  }


  if (digit == 1)
  {
    a = 29; // Pinleri tanımlıyoruz
    b = 30;
    c = 31;
    d = 32;
    e = 33;
    f = 34;
    g = 35;
  }

  if (digit == 2)
  {
    a = 36; // Pinleri tanımlıyoruz
    b = 37;
    c = 38;
    d = 39;
    e = 40;
    f = 41;
    g = 42;
  }



  // "9" Sayısını yazar.
  if (s == 9)
  {
    digitalWrite(a, HIGH);
    digitalWrite(b, HIGH);
    digitalWrite(c, HIGH);
    digitalWrite(d, HIGH);
    digitalWrite(e, LOW); //
    digitalWrite(f, HIGH);
    digitalWrite(g, HIGH);
  }

  // "8" Sayısını yazar.
  if (s == 8)
  {
    digitalWrite(a, HIGH);
    digitalWrite(b, HIGH);
    digitalWrite(c, HIGH);
    digitalWrite(d, HIGH);
    digitalWrite(e, HIGH);
    digitalWrite(f, HIGH);
    digitalWrite(g, HIGH);

  }

  // "7" Sayısını yazar.
  if (s == 7)
  {
    digitalWrite(a, HIGH);
    digitalWrite(b, HIGH);
    digitalWrite(c, HIGH);
    digitalWrite(d, LOW);
    digitalWrite(e, LOW);
    digitalWrite(f, LOW);
    digitalWrite(g, LOW);

  }

  // "6" Sayısını yazar.
  if (s == 6)
  {
    digitalWrite(a, HIGH);
    digitalWrite(b, LOW);//HIGH
    digitalWrite(c, HIGH);
    digitalWrite(d, HIGH);
    digitalWrite(e, HIGH);
    digitalWrite(f, HIGH);
    digitalWrite(g, HIGH);
  }

  // "5" Sayısını yazar.
  if (s == 5)
  {
    digitalWrite(a, HIGH);
    digitalWrite(b, LOW);//
    digitalWrite(c, HIGH);
    digitalWrite(d, HIGH);
    digitalWrite(e, LOW);//
    digitalWrite(f, HIGH);
    digitalWrite(g, HIGH);
  }

  // "4" Sayısını yazar.
  if (s == 4)
  {
    digitalWrite(a, LOW);//
    digitalWrite(b, HIGH);
    digitalWrite(c, HIGH);
    digitalWrite(d, LOW);//
    digitalWrite(e, LOW);//
    digitalWrite(f, HIGH);
    digitalWrite(g, HIGH);
  }

  // "3" Sayısını yazar.
  if (s == 3)
  {
    digitalWrite(a, HIGH);
    digitalWrite(b, HIGH);
    digitalWrite(c, HIGH);
    digitalWrite(d, HIGH);
    digitalWrite(e, LOW);//
    digitalWrite(f, LOW);//
    digitalWrite(g, HIGH);
  }

  // "2" Sayısını yazar.
  if (s == 2)
  {
    digitalWrite(a, HIGH);
    digitalWrite(b, HIGH);
    digitalWrite(c, LOW);//
    digitalWrite(d, HIGH);
    digitalWrite(e, HIGH);
    digitalWrite(f, LOW);//
    digitalWrite(g, HIGH);
  }

  // "1" Sayısını yazar.
  if (s == 1)
  {
    digitalWrite(a, LOW);
    digitalWrite(b, HIGH);//
    digitalWrite(c, HIGH);//
    digitalWrite(d, LOW);
    digitalWrite(e, LOW);
    digitalWrite(f, LOW);
    digitalWrite(g, LOW);
  }

  // "0" Sayısını yazar.
  if (s == 0)
  {
    digitalWrite(a, HIGH);
    digitalWrite(b, HIGH);
    digitalWrite(c, HIGH);
    digitalWrite(d, HIGH);
    digitalWrite(e, HIGH);
    digitalWrite(f, HIGH);
    digitalWrite(g, LOW);//
  }


}
