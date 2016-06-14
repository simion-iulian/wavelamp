#include "FastLED.h"


#define NUM_LEDS 49
#define DATA_PIN 2
#define CLK_PIN 13
#define FRAME_TIME 15
#define BRIGHTNESS 255
const float pi = 3.14159;

// This is an array of leds.  One item for each led in your strip.
CRGB leds[NUM_LEDS];

//GROUP LEDS INTO HALF LINES
const int NUM_GROUPS1 = 13;
int group1[NUM_GROUPS1][15] = {
                    { 0},
                    { 1},
                  { 2,  3},
                  { 4,  5},  
                { 6,  7,  8,},
                { 9, 10, 11,},
              {12, 13, 14, 15},
              {16, 17, 18, 19},
            {20, 21, 22, 23, 24},
            {25, 26, 27, 28, 29},
          {30, 31, 32, 33, 34, 35},
          {36, 37, 38, 39, 40, 41},
       { 42, 43, 44, 45, 46, 47, 48}};
//     { 49, 50, 51, 52, 53, 54, 55},
//    {57, 58, 59, 60, 61, 62, 63, 64}

//int groupMax1[NUM_GROUPS1] = {7,6,6,5,5,4,4,3,3,2,2,1,1};
  int groupMax1[NUM_GROUPS1] = {1,1,2,2,3,3,4,4,5,5,6,6,7};

//group5 divider
const int NUM_GROUPS5 = 7;
int group5[NUM_GROUPS5][15] = {
  {42,48},//2
  {36,30,41,35},//4
  {43,20,25,47,24,29},//6
  {37,31,12,16,40,34,15,19},//8
  {44,21,26, 6, 9,46,23,28, 8,11},//10
  {38,32,13,17, 2, 4, 3, 5,14,18,33,39},//12
  {45,22,27, 7,10, 1, 0}//7
};
int groupMax5[NUM_GROUPS5] = {2,4,6,8,10,12,7};

//group4 is the fractal animation pattern
const int NUM_GROUPS4 = 12;
int group4[NUM_GROUPS4][15] = {
  {20,44,24,46,48,0,12,15}, //8
  {16,19,45},                  //3
  {9,8,1,25,29},               //5
  {30,31,34,35, 2, 3, 6,13,8,14},//10
  {17,18,26,28,38,39},         //6
  { 4, 5,10, 36, 37,40,41},    //7
  {22,32,33},                 //3
  {1},                        //1
  {7,43,47},                  //3
  {21,23,45},                 //3
  {27}};                      //1
int groupMax4[NUM_GROUPS4] = {8,3,5,10,6,7,3,1,3,3,1};


//GROUP LEDS INTO CONCENTRIC CIRCLES
const int NUM_GROUPS2 = 9;
int group2[NUM_GROUPS2][15] ={
  { 0,42,48},
  {43,44,45,46,47,35,24,15, 8, 3, 2, 6,12,20,30},
  { 1,36,41},
  { 5,11,19,29,40,39,38,37,25,16, 9, 4},
  { 7, 31,34},
  { 10,26,28},
  {21,13,14,23,33,32},
  {17,18,27},
  {22}
};
int groupMax2[NUM_GROUPS2] = {3,15,3,12,3,3,6,3,1};

const int NUM_GROUPS3 = 7; 
int group3[NUM_GROUPS3][15]={
  {42,30,20,12, 6, 2, 0, 3, 8,15,24,35,48}, //13
  {36,25,16, 9, 4, 1, 5,11,19,29,41},       //11
  {43,31,21,13, 7,14,23,34,47},             //9
  {37,26,17,10,18,28,40},                   //7
  {44,32,22,33,46},                         //5
  {38,27,39},                               //3
  {45}};                                      //1
int groupMax3[NUM_GROUPS3] = {13,11,9,7,5,3,1};



const int NUM_STEPS = 630;
const int NUM_COLORS = 7;
CRGB colors1[NUM_COLORS] = {
  CRGB::Red,
  CRGB::Blue,
  CRGB::Orange,
  CRGB::Magenta,
  CRGB::Yellow,
  CRGB::Purple,
  CRGB::Cyan 
};
CRGB purple = CHSV( HUE_PURPLE, 255, 255);
CRGB green  = CHSV( HUE_GREEN, 255, 255);
CRGB yellow  = CHSV( HUE_YELLOW, 255, 255);
CRGB blue  = CHSV(HUE_BLUE, 255, 255);
CRGB black  = CRGB::Black;

CRGBPalette16 gCurrentPaletteA( CRGB::Black);
CRGBPalette16 gCurrentPaletteB( CRGB::Blue);

CRGBPalette16 gTargetPaletteA( RainbowColors_p);
CRGBPalette16 gTargetPaletteB( CRGB::Red );

CRGBPalette16 gBeatPalette;




unsigned int currentStep = 0;

// This function sets up the ledsand tells the controller about them
void setup() {
	// sanity check delay - allows reprogramming if accidently blowing power w/leds
   	delay(3000);  
   
       Serial.begin(9600);
       FastLED.addLeds<WS2811, DATA_PIN, RGB>(leds, NUM_LEDS);
       FastLED.setDither(0);
//       FastLED.setCorrection(CRGB(175,245,255));
//       FastLED.setTemperature(Tungsten40W);
       FastLED.setBrightness(BRIGHTNESS);
       FastLED.show();


}

// This function runs over and over, and is where you do the magic to light
// your leds.
void loop() {
  
   uint8_t tPerSeq = 45;
   uint8_t noSeq = 4;
   uint16_t totalTime = tPerSeq*noSeq;
   uint16_t secondHand = (millis() / 1000) % totalTime;
   //TODO: How can this be made more flexible, the cycling of patterns?
   
    if(secondHand <= tPerSeq){
      runSequence(FRAME_TIME, NUM_GROUPS1, group1, groupMax1, colors1);
    }
    if(secondHand <= 2*tPerSeq && secondHand > tPerSeq){
      runSequence(FRAME_TIME, NUM_GROUPS2, group2, groupMax2, colors1);
    }
    if(secondHand <= 3*tPerSeq && secondHand > 2*tPerSeq){
      runSequence(FRAME_TIME, NUM_GROUPS3, group3, groupMax3, colors1);
    }
    if(secondHand <= totalTime && secondHand > 3*tPerSeq){
      runSequence(FRAME_TIME, NUM_GROUPS5, group5, groupMax5, colors1);
    }
    

}

void beatSequence(){
   EVERY_N_MILLISECONDS(40) {
    nblendPaletteTowardPalette( gCurrentPaletteA, gTargetPaletteA);
    nblendPaletteTowardPalette( gCurrentPaletteB, gTargetPaletteB);
  }
   MixBeatPalette(); // mix up the new 'beat palette' to draw with
   DrawOneFrameUsingBeatPalette(); // draw a simple animation using the 'beat palette'
   FastLED.show();
   FastLED.delay(30);
}
void runSequence(uint8_t wait, int numGroups, int group[][15], int groupMax[], CRGB colors[]){
  
  currentStep=millis()/FRAME_TIME;
  Serial.println(currentStep);
  for (int i = 0; i < numGroups; i++){
      unsigned int groupStep = currentStep+i*NUM_STEPS/numGroups;
      unsigned int step = groupStep%NUM_STEPS;
      float ratio = (float)step/NUM_STEPS;
      float ratio2 = (cos(pi*(1+ratio))+1)/2;
      
    for(int j = 0; j < groupMax[i]; j++){
      int ledNo = group[i][j];
      
      int groupColor = (groupStep/NUM_STEPS)%NUM_COLORS;
      
      int nextColor = groupColor+1;
      if(nextColor >= NUM_COLORS)
        nextColor = 0;
    
      leds[ledNo] = interpolateColor(colors[groupColor], colors[nextColor], ratio2);      
    }
    
    
  }
  
  FastLED.show();

  delay(wait);      
}


CRGB interpolateColor(CRGB first, CRGB second, float ratio){
  CRGB result;
  result.r =  interpolateComponent(first.r,second.r, ratio);
  result.g =  interpolateComponent(first.g,second.g, ratio);
  result.b =  interpolateComponent(first.b,second.b, ratio);
  return result;
}

uint8_t interpolateComponent(uint8_t first, uint8_t second, float ratio){
  float result = (1-ratio)*first + ratio*second;
  
  return (uint8_t)result;
}
void MixBeatPalette()
{
  uint8_t paletteBeatsPerMinute = 5;

  uint8_t beat = beat8( paletteBeatsPerMinute); // repeats from 0..255 

  // 'cubicwave8' spends more time at each end than sin8, and less time
  // in the middle.  Try others: triwave8, quadwave8, sin8, cubicwave8
  uint8_t mixer = cubicwave8( beat);

  // Mix a new palette, gBeatPalette, with a varying amount of contribution
  // from gCurrentPaletteA and gCurrentPaletteB, depending on 'mixer'.
  // The 'beat palette' is then used to draw onto the LEDs.
  uint8_t palettesize = sizeof( gBeatPalette) / sizeof(gBeatPalette[0]); // = 16
  blend( gCurrentPaletteA, gCurrentPaletteB, gBeatPalette, palettesize, mixer);
}


// Sample draw function to draw some pixels using the colors in gBeatPalette
void DrawOneFrameUsingBeatPalette()
{
  uint8_t startindex = millis() / 2;
  uint8_t incindex = 7;
  fill_palette(leds, NUM_LEDS, startindex, incindex, gBeatPalette, 255, LINEARBLEND);
  
}



