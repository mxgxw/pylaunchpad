/*
    SmartMatrix Features Demo - Louis Beaudoin (Pixelmatix)
    This example code is released into the public domain
*/

//#include "SmartMatrix_16x32.h"
#include "SmartMatrix_32x32.h"
#include "mpr121.h"
#include <Wire.h>

SmartMatrix matrix;

const int defaultBrightness = 100*(255/100);    // full brightness
//const int defaultBrightness = 15*(255/100);    // dim: 15% brightness
const int defaultScrollOffset = 6;
const rgb24 defaultBackgroundColor = {0x40, 0, 0};

// Teensy 3.0 has the LED on pin 13
const int ledPin = 11;
const int irqTouch1 = 17;
const int irqTouch2 = 16;
// the setup() method runs once, when the sketch starts


rgb24 fillColor = {(uint8_t)192, (uint8_t)192, (uint8_t)192};

int btn_status[5][4] = {
  {0,0,0,0,0},
  {0,0,0,0,0},
  {0,0,0,0,0},
  {0,0,0,0,0}
};


void setup() {
    // initialize the digital pin as an output.
    pinMode(ledPin, OUTPUT);
    digitalWrite(ledPin, LOW);
    
    
    pinMode(irqTouch1, INPUT);
    pinMode(irqTouch2, INPUT);

    Serial.begin(38400);

    matrix.begin();
    matrix.setBrightness(defaultBrightness);

    matrix.setScrollOffsetFromEdge(defaultScrollOffset);

    matrix.setColorCorrection(cc24);
    
    // Draw 4x4 Matrix
    drawMatrix();
    
    Serial.println("Trying to set-up touch sensor");
    digitalWrite(ledPin, HIGH);
    Wire.begin();
    mpr121_setup();
    mpr121_setupB();
}

#define DEMO_INTRO              1
#define DEMO_DRAWING_INTRO      1
#define DEMO_DRAWING_PIXELS     1
#define DEMO_DRAWING_LINES      1
#define DEMO_DRAWING_TRIANGLES  1
#define DEMO_DRAWING_CIRCLES    1
#define DEMO_DRAWING_RECTANGLES 1
#define DEMO_DRAWING_ROUNDRECT  1
#define DEMO_DRAWING_FILLED     1
#define DEMO_FILL_SCREEN        1
#define DEMO_DRAW_CHARACTERS    1
#define DEMO_FONT_OPTIONS       1
#define DEMO_MONO_BITMAP        1
#define DEMO_SCROLL_COLOR       1
#define DEMO_SCROLL_MODES       1
#define DEMO_SCROLL_SPEED       1
#define DEMO_SCROLL_FONTS       1
#define DEMO_SCROLL_POSITION    1
#define DEMO_SCROLL_ROTATION    1
#define DEMO_BRIGHTNESS         1
#define DEMO_RAW_BITMAP         1
#define DEMO_COLOR_CORRECTION   1

boolean touchStates1[12];
boolean touchStates2[12];

// the loop() method runs over and over again,
// as long as the board has power

rgb24 GREEN_COLOR = {(uint8_t)0, (uint8_t)192, (uint8_t)0};
rgb24 WHITE_COLOR = {(uint8_t)75, (uint8_t)75, (uint8_t)75};

void drawMatrix() {
  for(int i=0;i<4;i++) {
    for(int j=0;j<4;j++) {
      if(btn_status[i][j]==1) {
        matrix.fillRectangle(1+(5*i), 1+(7*j), 4+(5*i), 6+(7*j), GREEN_COLOR);
      } else {
        matrix.fillRectangle(1+(5*i), 1+(7*j), 4+(5*i), 6+(7*j), WHITE_COLOR);
      }
    }
  }
}

void loop() {
  matrix.fillScreen(defaultBackgroundColor);
  drawMatrix();
  matrix.swapBuffers();
  readTouchInputs();
  readTouchInputsB();
}

void readTouchInputs(){
  if(!checkInterrupt()){
    
    //read the touch state from the MPR121
    Wire.requestFrom(0x5A,2); 
    
    byte LSB = Wire.read();
    byte MSB = Wire.read();
    
    uint16_t touched = ((MSB << 8) | LSB); //16bits that make up the touch states

    
    for (int i=0; i < 12; i++){  // Check what electrodes were pressed
      if(touched & (1<<i)){
      
        if(touchStates1[i] == 0){
          switch(i) {
            case 0:
              Keyboard.press(KEY_1);
              btn_status[0][0]=1;
              break;
            case 1:
              Keyboard.press(KEY_Q);
              btn_status[0][1]=1;
              break;
            case 2:
              Keyboard.press(KEY_A);
              btn_status[0][2]=1;
              break;
            case 3:
              Keyboard.press(KEY_Z);
              btn_status[0][3]=1;
              break;
            case 4:
              Keyboard.press(KEY_2);
              btn_status[1][0]=1;
              break;
            case 5:
              Keyboard.press(KEY_W);
              btn_status[1][1]=1;
              break;
            case 6:
              Keyboard.press(KEY_S);
              btn_status[1][2]=1;
              break;
            case 7:
              Keyboard.press(KEY_X);
              btn_status[1][3]=1;
              break;
            case 8:
              Keyboard.press(KEY_3);
              btn_status[2][0]=1;
              break;
            case 9:
              Keyboard.press(KEY_E);
              btn_status[2][1]=1;
              break;
            case 10:
              Keyboard.press(KEY_D);
              btn_status[2][2]=1;
              break;
            case 11:
              Keyboard.press(KEY_C);
              btn_status[2][3]=1;
              break;
          }
        }      
        touchStates1[i] = 1;      
      }else{
        if(touchStates1[i] == 1){
          switch(i) {
            case 0:
              Keyboard.release(KEY_1);
              btn_status[0][0]=0;
              break;
            case 1:
              Keyboard.release(KEY_Q);
              btn_status[0][1]=0;
              break;
            case 2:
              Keyboard.release(KEY_A);
              btn_status[0][2]=0;
              break;
            case 3:
              Keyboard.release(KEY_Z);
              btn_status[0][3]=0;
              break;
            case 4:
              Keyboard.release(KEY_2);
              btn_status[1][0]=0;
              break;
            case 5:
              Keyboard.release(KEY_W);
              btn_status[1][1]=0;
              break;
            case 6:
              Keyboard.release(KEY_S);
              btn_status[1][2]=0;
              break;
            case 7:
              Keyboard.release(KEY_X);
              btn_status[1][3]=0;
              break;
            case 8:
              Keyboard.release(KEY_3);
              btn_status[2][0]=0;
              break;
            case 9:
              Keyboard.release(KEY_E);
              btn_status[2][1]=0;
              break;
            case 10:
              Keyboard.release(KEY_D);
              btn_status[2][2]=0;
              break;
            case 11:
              Keyboard.release(KEY_C);
              btn_status[2][3]=0;
              break;
          }
        }        
        touchStates1[i] = 0;
      }
    
    }
    
  }
}

void readTouchInputsB(){
  if(!checkInterrupt2()){
    
    //read the touch state from the MPR121
    Wire.requestFrom(0x5D,2); 
    
    byte LSB = Wire.read();
    byte MSB = Wire.read();
    
    uint16_t touched = ((MSB << 8) | LSB); //16bits that make up the touch states

    
    for (int i=0; i < 12; i++){  // Check what electrodes were pressed
      if(touched & (1<<i)){
      
        if(touchStates2[i] == 0){
          switch(i) {
            case 0:
              Keyboard.press(KEY_4);
              btn_status[3][0]=1;
              break;
            case 1:
              Keyboard.press(KEY_R);
              btn_status[3][1]=1;
              break;
            case 2:
              Keyboard.press(KEY_F);
              btn_status[3][2]=1;
              break;
            case 3:
              Keyboard.press(KEY_V);
              btn_status[3][3]=1;
              break;
            case 4:
              Keyboard.press(KEY_5);
              break;
            case 5:
              Keyboard.press(KEY_T);
              break;
            case 6:
              Keyboard.press(KEY_G);
              break;
            case 7:
              Keyboard.press(KEY_B);
              break;
          }
        }      
        touchStates2[i] = 1;      
      }else{
        if(touchStates2[i] == 1){
          switch(i) {
            case 0:
              Keyboard.release(KEY_4);
              btn_status[3][0]=0;
              break;
            case 1:
              Keyboard.release(KEY_R);
              btn_status[3][1]=0;
              break;
            case 2:
              Keyboard.release(KEY_F);
              btn_status[3][2]=0;
              break;
            case 3:
              Keyboard.release(KEY_V);
              btn_status[3][3]=0;
              break;
            case 4:
              Keyboard.release(KEY_5);
              break;
            case 5:
              Keyboard.release(KEY_T);
              break;
            case 6:
              Keyboard.release(KEY_G);
              break;
            case 7:
              Keyboard.release(KEY_B);
              break;
          }
        }        
        touchStates2[i] = 0;
      }
    
    }
    
  }
}



void mpr121_setupB(void){

  set_register(0x5D, ELE_CFG, 0x00); 
 
  // Section A - Controls filtering when data is > baseline.
  set_register(0x5D, MHD_R, 0x01);
  set_register(0x5D, NHD_R, 0x01);
  set_register(0x5D, NCL_R, 0x00);
  set_register(0x5D, FDL_R, 0x00);

  // Section B - Controls filtering when data is < baseline.
  set_register(0x5D, MHD_F, 0x01);
  set_register(0x5D, NHD_F, 0x01);
  set_register(0x5D, NCL_F, 0xFF);
  set_register(0x5D, FDL_F, 0x02);
  
  // Section C - Sets touch and release thresholds for each electrode
  set_register(0x5D, ELE0_T, TOU_THRESH);
  set_register(0x5D, ELE0_R, REL_THRESH);
 
  set_register(0x5D, ELE1_T, TOU_THRESH);
  set_register(0x5D, ELE1_R, REL_THRESH);
  
  set_register(0x5D, ELE2_T, TOU_THRESH);
  set_register(0x5D, ELE2_R, REL_THRESH);
  
  set_register(0x5D, ELE3_T, TOU_THRESH);
  set_register(0x5D, ELE3_R, REL_THRESH);
  
  set_register(0x5D, ELE4_T, TOU_THRESH);
  set_register(0x5D, ELE4_R, REL_THRESH);
  
  set_register(0x5D, ELE5_T, TOU_THRESH);
  set_register(0x5D, ELE5_R, REL_THRESH);
  
  set_register(0x5D, ELE6_T, TOU_THRESH);
  set_register(0x5D, ELE6_R, REL_THRESH);
  
  set_register(0x5D, ELE7_T, TOU_THRESH);
  set_register(0x5D, ELE7_R, REL_THRESH);
  
  set_register(0x5D, ELE8_T, TOU_THRESH);
  set_register(0x5D, ELE8_R, REL_THRESH);
  
  set_register(0x5D, ELE9_T, TOU_THRESH);
  set_register(0x5D, ELE9_R, REL_THRESH);
  
  set_register(0x5D, ELE10_T, TOU_THRESH);
  set_register(0x5D, ELE10_R, REL_THRESH);
  
  set_register(0x5D, ELE11_T, TOU_THRESH);
  set_register(0x5D, ELE11_R, REL_THRESH);
  
  // Section D
  // Set the Filter Configuration
  // Set ESI2
  set_register(0x5D, FIL_CFG, 0x04);
  
  // Section E
  // Electrode Configuration
  // Set ELE_CFG to 0x00 to return to standby mode
  set_register(0x5D, ELE_CFG, 0x0C);  // Enables all 12 Electrodes
  
  
  // Section F
  // Enable Auto Config and auto Reconfig
  /*set_register(0x5D, ATO_CFG0, 0x0B);
  set_register(0x5D, ATO_CFGU, 0xC9);  // USL = (Vdd-0.7)/vdd*256 = 0xC9 @3.3V   set_register(0x5D, ATO_CFGL, 0x82);  // LSL = 0.65*USL = 0x82 @3.3V
  set_register(0x5D, ATO_CFGT, 0xB5);*/  // Target = 0.9*USL = 0xB5 @3.3V
  
  set_register(0x5D, ELE_CFG, 0x0C);
  
}

void mpr121_setup(void){

  set_register(0x5A, ELE_CFG, 0x00); 
 
  // Section A - Controls filtering when data is > baseline.
  set_register(0x5A, MHD_R, 0x01);
  set_register(0x5A, NHD_R, 0x01);
  set_register(0x5A, NCL_R, 0x00);
  set_register(0x5A, FDL_R, 0x00);

  // Section B - Controls filtering when data is < baseline.
  set_register(0x5A, MHD_F, 0x01);
  set_register(0x5A, NHD_F, 0x01);
  set_register(0x5A, NCL_F, 0xFF);
  set_register(0x5A, FDL_F, 0x02);
  
  // Section C - Sets touch and release thresholds for each electrode
  set_register(0x5A, ELE0_T, TOU_THRESH);
  set_register(0x5A, ELE0_R, REL_THRESH);
 
  set_register(0x5A, ELE1_T, TOU_THRESH);
  set_register(0x5A, ELE1_R, REL_THRESH);
  
  set_register(0x5A, ELE2_T, TOU_THRESH);
  set_register(0x5A, ELE2_R, REL_THRESH);
  
  set_register(0x5A, ELE3_T, TOU_THRESH);
  set_register(0x5A, ELE3_R, REL_THRESH);
  
  set_register(0x5A, ELE4_T, TOU_THRESH);
  set_register(0x5A, ELE4_R, REL_THRESH);
  
  set_register(0x5A, ELE5_T, TOU_THRESH);
  set_register(0x5A, ELE5_R, REL_THRESH);
  
  set_register(0x5A, ELE6_T, TOU_THRESH);
  set_register(0x5A, ELE6_R, REL_THRESH);
  
  set_register(0x5A, ELE7_T, TOU_THRESH);
  set_register(0x5A, ELE7_R, REL_THRESH);
  
  set_register(0x5A, ELE8_T, TOU_THRESH);
  set_register(0x5A, ELE8_R, REL_THRESH);
  
  set_register(0x5A, ELE9_T, TOU_THRESH);
  set_register(0x5A, ELE9_R, REL_THRESH);
  
  set_register(0x5A, ELE10_T, TOU_THRESH);
  set_register(0x5A, ELE10_R, REL_THRESH);
  
  set_register(0x5A, ELE11_T, TOU_THRESH);
  set_register(0x5A, ELE11_R, REL_THRESH);
  
  // Section D
  // Set the Filter Configuration
  // Set ESI2
  set_register(0x5A, FIL_CFG, 0x04);
  
  // Section E
  // Electrode Configuration
  // Set ELE_CFG to 0x00 to return to standby mode
  set_register(0x5A, ELE_CFG, 0x0C);  // Enables all 12 Electrodes
  
  
  // Section F
  // Enable Auto Config and auto Reconfig
  /*set_register(0x5A, ATO_CFG0, 0x0B);
  set_register(0x5A, ATO_CFGU, 0xC9);  // USL = (Vdd-0.7)/vdd*256 = 0xC9 @3.3V   set_register(0x5A, ATO_CFGL, 0x82);  // LSL = 0.65*USL = 0x82 @3.3V
  set_register(0x5A, ATO_CFGT, 0xB5);*/  // Target = 0.9*USL = 0xB5 @3.3V
  
  set_register(0x5A, ELE_CFG, 0x0C);
  
}

boolean checkInterrupt2(void){
  return digitalRead(irqTouch2);
}
boolean checkInterrupt(void){
  return digitalRead(irqTouch1);
}


void set_register(int address, unsigned char r, unsigned char v){
    Wire.beginTransmission(address);
    Wire.write(r);
    Wire.write(v);
    Wire.endTransmission();
}
