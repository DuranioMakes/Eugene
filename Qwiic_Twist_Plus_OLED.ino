/* DURANIO LABS, YouTube, 2025
 * This sketch illuminates the RGB LED of the Qwiic Twist and changes its color 
 * as you twist the knob while displaying the name of the color and the Qwiic Twist
 * counts on one of four different SparkFun OLED displays.
 * 
 * This is an updated version of the sketch created by Marcus Stevenson on September 21, 2020.
 * The original version of this sketch is in the GitHub repo here-> 
 * (https://github.com/marcus-stevenson/SFESimpleSketches/tree/master/QwiicTwistMicroOLEDDisplay)
*/
#include <Wire.h>
#include "SparkFun_Qwiic_Twist_Arduino_Library.h"
#include <SparkFun_Qwiic_OLED.h> //http://librarymanager/All#SparkFun_Qwiic_OLED

// The OLED Library supports four different types of SparkFun boards. The demo uses the following
// defines to determine which device is being used. Uncomment the device being used for this demo.

//QwiicMicroOLED myOLED;
//QwiicTransparentOLED myOLED;
QwiicNarrowOLED myOLED;
//Qwiic1in3OLED myOLED;

TWIST twist;  //Create instance of this object

void setup()
{
  Serial.begin(9600);
  Serial.println("Qwiic Twist and OLED Example");
  Wire1.begin(); //"Wire1" for Uno R4 wifi. "Wire" for other boards.
  
  // Initalize the OLED device
    if (myOLED.begin(Wire1) == false) //"Wire1" for Uno R4 wifi.
    {
        Serial.println("OLED Device begin failed. Freezing...");
        while (true);
    }
    Serial.println("OLED success");

  // Initialize the Qwiic Twist switch
    if (twist.begin(Wire1) == false) //"Wire1" for Uno R4 wifi. I added the Qwiic Twist I2C address, just in case
    {
        Serial.println("Twist does not appear to be connected. Please check wiring. Freezing...");
        while(1);
    }
    Serial.println("Qwiic Twist success");
    delay(1000); //Delay 1 second

    Wire1.setClock(400000); //Optional: increase I2C speed to max, 400kHz. "Wire1" for UNO R4 wifi only, "Wire" for all others

    // Fill a rectangle on the screen that has a 4 pixel board
    myOLED.rectangleFill(4, 4, myOLED.getWidth() - 8, myOLED.getHeight() - 8);

    String message = "I2C is Okay";
          
    // starting x position - screen width minus string width  / 2
    int x0 = (myOLED.getWidth() - myOLED.getStringWidth(message)) / 2;

    // starting y position - screen height minus string height / 2 
    int y0 = (myOLED.getHeight() - myOLED.getStringHeight(message)) / 2;

    // Draw the text - color of black (0)
    myOLED.text(x0, y0, message, 0);

    // There's nothing on the screen yet - Now send the graphics to the device
    myOLED.display();
    delay(2000); //Display message for 2 seconds
}

void loop() {
  Serial.print("Count: ");
  Serial.print(twist.getCount()); //Serial print "twistCount" value on the Serial Monitor
 
  //Convert "twistCount" integers to characters before displaying on OLED
  int twistCount = twist.getCount(); //Store twist count value in variable named, "twistCount"
  char ARRAY[5]; //Create a character array, size of 5 characters
  String str = String(twistCount); //Convert "twistCount" integer value to string and store in "str"
  str.toCharArray(ARRAY,5); //Place the string "str" into a character array called, "ARRAY", up to 5 characters

  //Test if Qwiic Switch is pressed, then display "Pressed!" on the Serial Monitor and the OLED display    
  if(twist.isPressed()){
    Serial.print("Pressed!"); //Send out to serial monitor
    myOLED.erase(); //Clear the screen
    myOLED.text(10, 10, "Pressed!", 1); //Draw text "white" (it actually looks blue to me)
    myOLED.display(); //Now update what's shown on the OLED display
    delay(1000); //Display "Pressed!" for 1 second
    }
  //Display "RED", along with twsit count value and twist count range
  if(0<= twistCount && twistCount <5){ 
    twist.setColor(100, 0, 0); //(Red LED, Green LED, Blue LED) Red was originally 255
    myOLED.erase(); //Clear the screen
    myOLED.text(4, 2, "RED", 1);
    myOLED.text(14, 12, ARRAY, 1); //Display "twistCount" value stored in character array "ARRAY"
    myOLED.text(4, 24,"(0 to 4 counts)", 1);
    myOLED.display(); //Now display the Text
    }
  //Display "GREEN", along with twsit count value and twist count range
    else if (5<= twistCount && twistCount <10){//------> green 
    twist.setColor(0, 100, 0); //Green was 255
    myOLED.erase(); //Clear the screen
    myOLED.text(4, 2, "GREEN", 1);
    myOLED.text(14, 12, ARRAY, 1); //Display "twistCount" value stored in character array "ARRAY"
    myOLED.text(4, 24,"(5 to 9 counts)", 1);
    myOLED.display(); //Now display the Text
    }
  //Display "VIOLET", along with twsit count value and twist count range
    else if (10<= twistCount && twistCount <15){//-----> violet
    twist.setColor(25, 0, 100); //Was (64, 0, 255)
    myOLED.erase(); //Clear the screen
    myOLED.text(4, 2, "VIOLET", 1);
    myOLED.text(14, 12, ARRAY, 1); //Display "twistCount" value stored in character array "ARRAY"
    myOLED.text(4, 24,"(10 to 14 counts))", 1);
    myOLED.display(); //Now display the Text
    }
  //Display "YELLOW", along with twsit count value and twist count range
    else if (15<= twistCount && twistCount <20){//-----> yellow
    twist.setColor(100, 100, 0); //was (255, 255, 0)
    myOLED.erase(); //Clear the screen
    myOLED.text(4, 2, "YELLOW", 1);
    myOLED.text(14, 12, ARRAY, 1); //Display "twistCount" value stored in character array "ARRAY"
    myOLED.text(4, 24,"(15 to 19 counts)", 1);
    myOLED.display(); //Now display the Text
    } 
  //Display "PINK", along with twsit count value and twist count range
    else if (20<= twistCount && twistCount <25){//-----> pink
    twist.setColor(50, 0, 100); //Was (128, 0, 255)
    myOLED.erase(); //Clear the screen
    myOLED.text(4, 2, "PINK", 1);
    myOLED.text(14, 12, ARRAY, 1); //Display "twistCount" value stored in character array "ARRAY"
    myOLED.text(4, 24,"(20 to 24 counts)", 1);
    myOLED.display(); //Now display the Text
    }
  //Display "BLUE", along with twsit count value and twist count range
    else if (25<= twistCount && twistCount <30){//-----> blue
    twist.setColor(0, 0, 100); // Blue was 255
    myOLED.erase(); //Clear the screen
    myOLED.text(4, 2, "BLUE", 1);
    myOLED.text(14, 12, ARRAY, 1); //Display "twistCount" value stored in character array "ARRAY"
    myOLED.text(4, 24,"(25 to 29 counts)", 1);
    myOLED.display(); //Now display the Text
    }
  //Display "ORANGE", along with twsit count value and twist count range
    else if (30<= twistCount && twistCount <35){//-----> orange
    twist.setColor(100, 40, 0); //Was(255, 100, 0)
    myOLED.erase(); //Clear the screen
    myOLED.text(4, 2, "ORANGE", 1);
    myOLED.text(14, 12, ARRAY, 1); //Display "twistCount" value stored in character array "ARRAY"
    myOLED.text(4, 24,"(30 to 34 counts)", 1);
    myOLED.display(); //Now display the Text
    }
  // If counts are less than zero OR greater than or equal to 35, clear OLED and only show counts
    else if (0> twistCount || twistCount >=35){
    twist.setColor(0, 0, 0); //Turn off the red, green, and blue LEDs
    myOLED.erase(); //Clear the screen
    myOLED.text(14, 12, ARRAY, 1); //Display "twistCount" value stored in character array "ARRAY"
    myOLED.text(1, 24,"(Colors from 0 to 34)", 1);
    myOLED.display(); //Only display the twist counts
    }
  
  Serial.println();

  //delay(10);
}