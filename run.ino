#include <TouchScreen.h> //touch library​
#include <LCDWIKI_GUI.h> //Core graphics library​
#include <LCDWIKI_KBV.h> //Hardware-specific library​
#include <Servo.h> //Library to enable the working of servo motor​

LCDWIKI_KBV my_lcd(ILI9486,A3,A2,A1,A0,A4);​

#define YP A3  // must be an analog pin, use "An" notation!​
#define XM A2  // must be an analog pin, use "An" notation!​
#define YM 9   // can be a digital pin​
#define XP 8   // can be a digital pin​

//Setting thresholds along the x-direction in the touch screen display​
#define TS_LEFTX 133​
#define TS_RIGHTX 875​

//Setting thresholds along the y-direction in the touch screen display​
#define TS_TOPY 963 ​
#define TS_BOTTOMY 105​

//Setting the thresholds for pressure applied on the touch screen. ​
#define MINPRESSURE 10 //Minimum pressure to detect touch​
#define MAXPRESSURE 1000 //Maximum detectable pressure by the screen​

TouchScreen ts = TouchScreen(XP, YP, XM, YM, 300); //setting the touchscreen threshold parameters​
​
//defining various colours to use on the display​
#define  BLACK   0x0000​
#define BLUE    0x001F​
#define RED     0xF800​
#define GREEN   0x07E0​
#define CYAN    0x07FF​
#define MAGENTA 0xF81F​
#define YELLOW  0xFFE0​
#define WHITE   0xFFFF​

//creating the servo objects for all the three servo motors​
Servo servo1;​
Servo servo2;​
Servo servo3;​

void setup() {​
  // put your setup code here, to run once:​
  Serial.begin(9600); //Setting up the serial communication​
  my_lcd.Init_LCD(); //Initializing the LCD object​
  my_lcd.Fill_Screen(BLACK);​
  pinMode(13, OUTPUT);

  //The following 3 lines create 3 bars on the screen that can be used to move the servo motors​
  my_lcd.Fill_Rect(30, 50, 200, 30, WHITE);​
  my_lcd.Fill_Rect(30, 110, 200, 30, WHITE);​
  my_lcd.Fill_Rect(30, 170, 200, 30, WHITE);​

  //3 pins on Arduino Mega2560: 44,45,46 are used to control the servo motor shaft angles​
  servo1.attach(44);​
  servo2.attach(45);​
  servo3.attach(46);​

​//Setting all the joints to Zero position. So, the Robotic Arm comes to the Home Position​
  servo1.write(0);​
  delay(100);​
  
  servo2.write(0);​
  delay(100);​

  servo3.write(0);​
  delay(100);​
}​

int theta1,theta2,theta3,theta1_dummy,theta2_dummy,theta3_dummy;​
int pos1,pos2,pos3;​

void loop() {​
  // put your main code here, to run repeatedly:​
  TSPoint p = ts.getPoint();​
  
  if(p.z>MINPRESSURE && p.z<MAXPRESSURE){ //Checking if there is any touch detected on the screen​
    p.x = map(p.x, TS_LEFTX, TS_RIGHTX, 0, 320); //Capturing the x-coordinate on the screen​
    p.y = map(p.y, TS_TOPY, TS_BOTTOMY, 0, 480); //Capturing the y-coordinate on the screen

    if(p.x>30 && p.x<230){​
      p.x=map(p.x,30,230,10,170); //Converting the x-coordinates to joint angle value(0-180 degrees)​
      //Touch control to the first joint: Waist/Base joint​

      if(p.y>50 && p.y<80){​
        // Serial.println("Hi");​
        theta1=p.x;​
        if(theta1<theta1_dummy){​
          for(pos1=theta1;pos1<theta1_dummy;pos1++){​
            servo1.write(pos1);​
            delay(15);​
          }​
        }​
        
        else if(theta1>theta1_dummy){​
          for(pos1=theta1;pos1>theta1_dummy;pos1--){​
            servo1.write(pos1);​
            delay(15);​
          }​
        }​
        theta1_dummy=theta1;​
      }​
      //Touch control to the second joint: Shoulder joint​

      else if(p.y>110 && p.y<140){​
        // Serial.println("Hey");​
        theta2=p.x;​
        if(theta2<theta2_dummy){​
          for(pos2=theta2;pos2<theta2_dummy;pos2++){​
            servo2.write(pos2);​
            delay(15);​
          }​
        }​
        
        else if(theta2>theta2_dummy){​
          for(pos2=theta2;pos2>theta2_dummy;pos2--){​
            servo2.write(pos2);​
            delay(15);​
          }​
        }​
        theta2_dummy=theta2;​
      }​

      //Touch control to the Third joint: Claw joint​
      else if(p.y>170 && p.y<200){​
        theta3=p.x;​
        if(theta3<theta3_dummy){​
          for(pos3=theta3;pos3<theta3_dummy;pos3++){​
            servo3.write(pos3);​
            delay(15);​
          }​
        }​
        
        else if(theta3>theta3_dummy){​
          for(pos3=theta3;pos3>theta3_dummy;pos3--){​
            servo3.write(pos3);​
            delay(15);​
          }​
        }​
        theta3_dummy=theta3;        ​
      }​
    }​
    
    //Printing the Joint Angles. This Step is useful for Forward Kinematics of the Manipulator​
    Serial.println(theta1);​
    Serial.println(theta2);​
    Serial.println(theta3);​
    Serial.println(" ");​
  }​
}​
