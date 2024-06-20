# Space Invaders on OLED

## Overview

This project is a recreation of the classic Space Invaders game using an Arduino and an OLED display. The game includes features such as player movement, alien invaders, and collision detection. The code utilizes libraries like Adafruit SSD1306 for display handling and Adafruit GFX for graphics rendering.

## Features

- **Player Movement**: Control the player's tank with buttons.
- **Alien Invaders**: Rows of aliens move down the screen.
- **Missiles**: The player can shoot missiles to destroy the aliens.
- **Collision Detection**: Aliens can be destroyed by missiles, and the player has lives that decrease on collision with aliens.
- **Menu System**: Simple menu for starting the game and selecting difficulty levels.
- **Display Inversion**: Changes the display contrast based on light levels.

## Requirements

- **Hardware**:
  - Arduino board (e.g., Arduino Uno)
  - OLED display (e.g., 128x64 OLED screen)
  - Push buttons for input
  - Various components (LEDs, Potentiometer, Buzzer)

- **Libraries**:
  - `Adafruit_GFX.h`
  - `Adafruit_SSD1306.h`
  - `Wire.h`

## Pin Configuration

- **Buttons**:
  - FIRE_BUT: Pin 4
  - RIGHT_BUT: Pin 3
  - LEFT_BUT: Pin 2

- **Display**:
  - OLED Address: 0x3C

- **Player LED Indicators**:
  - Pins 10, 11, 12, 13

- **Missile LED Indicators**:
  - Pins 5, 6, 7

- **Miscellaneous**:
  - Potentiometer: Pin A1
  - Buzzer: Pin A2

## Setup Instructions

1. **Connect Hardware**:
   - Wire up the OLED display to the Arduino using I2C (SCL and SDA).
   - Connect the buttons to the designated pins.
   - Attach LEDs, potentiometer, and buzzer as specified in the pin configuration.

2. **Install Libraries**:
   - Install the `Adafruit_GFX` and `Adafruit_SSD1306` libraries using the Arduino Library Manager.

3. **Upload the Code**:
   - Open the `.ino` file in the Arduino IDE.
   - Select the appropriate board and port in the Arduino IDE.
   - Upload the code to your Arduino.

4. **Run the Game**:
   - After uploading, the game should start. Use the buttons to navigate the menu and start the game.
   - Control the tank using the left and right buttons and fire missiles using the fire button.

## Code Breakdown

### Constants and Macros

- **Display Settings**:
  - `OLED_ADDRESS`: The I2C address for the OLED display.
  - `SCREEN_WIDTH` and `SCREEN_HEIGHT`: Dimensions of the display.

- **Player Settings**:
  - Initial position, missile speed, and other gameplay constants.

- **Alien Settings**:
  - Alien movement speed, spacing between aliens, and graphics.

### Graphics Data

- Defined graphical representations of the player tank, missiles, and aliens using PROGMEM arrays.

### Game Structures

- **GameObjectStruct**: Base structure for game objects.
- **AlienStruct**: Structure for aliens with additional attributes.
- **PlayerStruct**: Structure for the player.

### Functions

- **setup()**: Initializes the display, inputs, and game objects.
- **loop()**: Main game loop handling game states, display updates, and input processing.
- **MenuShow()**: Displays the menu and handles menu navigation.
- **PlayerControl()**: Manages player movement and firing.
- **MissileControl()**: Controls the movement and status of missiles.
- **AlienControl()**: Manages alien movement and behavior.
- **CheckCollisions()**: Detects and handles collisions between game objects.

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

## Contact

For any queries or issues, please contact [your email or GitHub profile].

---

**Enjoy playing Space Invaders on your Arduino!**
