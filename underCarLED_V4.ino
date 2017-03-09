#include <FastLED.h>


#define LED_PIN     2
#define NUM_LEDS    100
#define BRIGHTNESS  255
#define LED_TYPE    WS2811
#define COLOR_ORDER GRB
CRGB leds[NUM_LEDS];

#define UPDATES_PER_SECOND 100

struct node {
  float speed;
  float position;
  int * pattern;
  struct node *next;
}*start=NULL;

char mode = '0';

String inString = "";

//int numberOfBlobs = 1;

int redPurple[][2] = {       
    {20,28},
    {40,18},
    {70,9},
    {200,1},
    {255,1},
    {255,1},
    {200,251},
    {90,248},
    {40,239},
    {20,229},
    {-1,-1}
    };

int greenYellow[][2] = {       
    {20,140},
    {40,145},
    {70,150},
    {200,155},
    {255,160},
    {255,165},
    {200,170},
    {90,175},
    {40,180},
    {20,190},
    {-1,-1}
    };

int longGlow[][2] = {       
    {10,145},
    {20,145},
    {30,145},
    {40,145},
    {50,145},
    {60,145},
    {70,145},
    {80,145},
    {90,145},
    {100,145},
    {110,145},
    {120,145},
    {130,145},
    {140,145},
    {150,145},
    {160,145},
    {170,145},
    {180,145},
    {200,145},
    {210,145},
    {220,145},
    {230,145},
    {240,145},
    {255,145},
    {255,145},
    {255,145},
    {255,145},
    {255,145},
    {255,145},
    {255,145},
    {255,145},
    {255,145},
    {255,145},
    {255,145},
    {255,145},
    {255,145},
    {255,145},
    {255,145},
    {255,145},
    {255,145},
    {255,145},
    {255,145},
    {255,145},
    {255,145},
    {255,145},
    {255,145},
    {255,145},
    {255,145},
    {255,145},
    {255,145},
    {255,145},
    {240,145},
    {230,145},
    {220,145},
    {210,145},
    {200,145},
    {190,145},
    {180,145},
    {170,145},
    {160,145},
    {150,145},
    {140,145},
    {130,145},
    {120,145},
    {110,145},
    {100,145},
    {90,145},
    {80,145},
    {70,145},
    {60,145},
    {50,145},
    {40,145},
    {30,145},
    {20,145},
    {10,145},
    {-1,-1}
    };

int rearBrightness = 0;
int rearBrightnessDecreaseCoef = -1;
int frontBrightness = 0;
int frontBrightnessDecreaseCoef = -1;

float breatheAccel = -0.001;
float breatheSpeed = 0.4;
float tempBreatheSpeed = 0.1;
float breathePos = 1;
bool breatheIn = true;

int zones[][3] = {{"front",0,27},{"middle",28,71},{"back",72,99}};


CRGBPalette16 currentPalette;
TBlendType    currentBlending;

int prevTime = 0;

void setup() {
    Serial.begin(9600);
    //delay( 1000 ); // power-up safety delay
    FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
    FastLED.setBrightness(  BRIGHTNESS );
    
    currentPalette = RainbowColors_p;
    currentBlending = LINEARBLEND;
    prevTime = millis();
}



void loop()
{   
  
    
    serialCall();

    

    //speed control starts here
    bool blobsOn = false;

    if(mode == '0'){
      int tempBounds[2] = {zones[0][2], zones[2][1]};
      int newBounds[2] = {0,99};
      zones[0][2] = newBounds[0];
      zones[1][1] = newBounds[0]+1;
      zones[1][2] = newBounds[1]-1;
      zones[2][1] = newBounds[1];
      spawnCheck(-0.2, *longGlow, 0.5);
      //spawnCheck(0.2, *longGlow, 0.5);
      updatePos();
      drawBlobs();

      zones[0][2] = tempBounds[0];
      zones[1][1] = tempBounds[0]+1;
      zones[1][2] = tempBounds[1]-1;
      zones[2][1] = tempBounds[1];
      
    }
    
    //modes for accelerating
    if(mode == 'a'){
      spawnCheck(-0.2, *redPurple, 2);
      blobsOn = true;
    }
    if(mode == 'b'){
      spawnCheck(-0.5, *redPurple, 2);
      blobsOn = true;
    }
    if(mode == 'c'){
      spawnCheck(-1.1, *redPurple, 2);
      blobsOn = true;
    }
    if(mode == 'd'){
      spawnCheck(-1.6, *redPurple, 2);
      blobsOn = true;
    }
    if(mode == 'e'){
      spawnCheck(-2.5, *redPurple, 2);
      blobsOn = true;
    }


    //modes for regening
    if(mode == 'f'){
      spawnCheck(0.2, *greenYellow, 2);
      blobsOn = true;
    }
    if(mode == 'g'){
      spawnCheck(0.5, *greenYellow, 2);
      blobsOn = true;
    }
    if(mode == 'h'){
      spawnCheck(1.1, *greenYellow, 2);
      blobsOn = true;
    }
    if(mode == 'i'){
      spawnCheck(1.6, *greenYellow, 2);
      blobsOn = true;
    }
    if(mode == 'j'){
      spawnCheck(2.5, *greenYellow, 2);
      blobsOn = true;
    }

    if(blobsOn){
      updatePos();
      drawBlobs();
  
      showRearLights();
      showFrontLights();
      
      decreaseRearBrightness();
      decreaseFrontBrightness();
    }
    
    //ends here
    
    FastLED.show();
    FastLED.delay(1000 / UPDATES_PER_SECOND);
      
}

void addBlob(float fspeed, int * fpattern){

  struct node *new_node,*current;
  new_node = (struct node *)malloc(sizeof(struct node));
  new_node -> speed = fspeed;
  

  if(fspeed < 0){
    new_node -> position = zones[1][2] - zones[1][1];
  }
  else{
    new_node -> position = 0;
  }
  
  new_node -> pattern = fpattern;
  new_node -> next=NULL;


  if(start == NULL) {
   start = new_node;
  }
  else {
    current = start;
    while(current -> next != NULL){
      current = current -> next;
    }
    current -> next = new_node;
  }
}

void drawBlobs(){

  for( int b = zones[1][1]; b <= zones[1][2]; b++) {
    leds[b] = ColorFromPalette( currentPalette, 16, 0, currentBlending);
  }

  node * currentNode = start;
  
  while(start != NULL){
    
    
    int *currentPattern = currentNode -> pattern;
    int patSize = (sizeof(currentPattern)/2)-1;
    if(currentNode -> speed > 0){
      for(int j = 0; currentPattern[j*2 + 0] != -1; j++){
        if((zones[1][1] + (round(currentNode -> position)) - j) <= zones[1][2] && (round(currentNode -> position)) - j >= 0){
          leds[zones[1][1] + (round(currentNode -> position)) - j] = ColorFromPalette( currentPalette, currentPattern[j*2 + 1], currentPattern[j*2 + 0], currentBlending);
        }
      }
    }
    else{
      for(int j = 0; currentPattern[j*2 + 0] != -1; j++){
        if((zones[1][1] + (round(currentNode -> position)) + j) >= zones[1][1] && (zones[1][1] + (round(currentNode -> position)) + j) <= zones[1][2]){
          leds[zones[1][1] + (round(currentNode -> position)) + j] = ColorFromPalette( currentPalette, currentPattern[j*2 + 1], currentPattern[j*2 + 0], currentBlending);
        }
      }
    }
    if(currentNode -> next == NULL){
      break;
    }
    else{
      currentNode = currentNode -> next;
    }
  }
  
}

void updatePos(){
  node * currentNode = start;
  node * pastNode = start;
  int nodeCount = 0;
  
  while(start != NULL){

    nodeCount ++;
    int patternSize = 0;
    for(int j = 0; (currentNode -> pattern)[j*2 + 0] != -1; j++){
      patternSize ++;
    }
                                                                                                                          //this part serves to know if the blob has ended it's run... if so, it must be unlinked
    if((((zones[1][1] + (currentNode -> position) - patternSize) < zones[1][2]) && ((currentNode -> speed) > 0)) || ((((currentNode -> position) + patternSize) > 0) && (currentNode -> speed) < 0)){   //dividing by 2 because it doesn't distinguish between inner arrays.

                                                              //not gonna deal with delta time now since it has to be updated every cycle
      currentNode -> position += (currentNode -> speed);// * (deltaTime()/20); //this is to keep all the movements fluid regardless of update delays... the /20 is just an arbitrary divider
    }
    else{

      if(currentNode -> speed > 0){
        increaseFrontBrightness((8)*(currentNode -> speed));
      }
      else{
        increaseRearBrightness((-8)*(currentNode -> speed));

      }

      if(nodeCount == 1){
        start = currentNode -> next;
        pastNode = currentNode -> next;
        
        node * tempNode = currentNode;
        free(tempNode);
        currentNode = pastNode;
        nodeCount = 0;
      }
      else{
        pastNode -> next = currentNode -> next;
        node * tempNode = currentNode;
        free(tempNode);
        currentNode = pastNode;
      }
      
    }
    if(currentNode -> next == NULL){
      break;
    }
    else{
      pastNode = currentNode;
      currentNode = currentNode -> next;
      
    }
    
  }
}

void serialCall(){
  while (Serial.available() > 0) {
      int inChar = Serial.read();
      mode = inChar;
      Serial.println(inChar);
  }
}

int deltaTime(){
    //this is the code to see the delay between updates
    int currentTime = millis();
    int delta = currentTime - prevTime;
    prevTime = currentTime;
    return(delta);
    
}

int sign(float val){
  if(val > 0){
    return 1;
  }
  else if(val < 0){
    return -1;
  }
  else{
    return 0;
  }
}

void increaseRearBrightness(int amount){
  if((rearBrightness + amount) > 255){
    rearBrightness = 255;
  }
  else{
    rearBrightness += amount;
  }
  
}

void increaseFrontBrightness(int amount){
  if((frontBrightness + amount) > 255){
    frontBrightness = 255;
  }
  else{
    frontBrightness += amount;
  }
}

void decreaseRearBrightness(){
  if((rearBrightness + rearBrightnessDecreaseCoef) < 0){
    rearBrightness = 0;
  }
  else{
    rearBrightness += rearBrightnessDecreaseCoef;
  }
}

void decreaseFrontBrightness(){
  if((frontBrightness + frontBrightnessDecreaseCoef) < 0){
    frontBrightness = 0;
  }
  else{
    frontBrightness += frontBrightnessDecreaseCoef;
  }
}

void showRearLights(){
  for(int i = zones[0][1]; i <= zones[0][2]; i++){
    leds[i] = ColorFromPalette( currentPalette, 255, rearBrightness, currentBlending);
  }
}

void showFrontLights(){
  for(int i = zones[2][1]; i <= zones[2][2]; i++){
    leds[i] = ColorFromPalette( currentPalette, 170, frontBrightness, currentBlending);
  }
}

void spawnCheck(float fspeed, int * fpattern, float blobCount){
  bool blobNeeded = true;
  if(start == NULL){
    addBlob(fspeed,fpattern);
  }
  else{
    node * currentNode = start;
    while(true){

      if(currentNode -> speed > 0){
        if((currentNode -> position) < ((zones[1][2] - zones[1][1])/blobCount)){
          blobNeeded = false;
        }
      }
      else{
        if(((zones[1][2]) - (zones[1][1] + (currentNode -> position))) < ((zones[1][2] - zones[1][1])/blobCount)){
          blobNeeded = false;
        }
      }
      
      if(currentNode -> next == NULL){
        break;
      }
      else{
      currentNode = currentNode -> next;
      }
    }
    if(blobNeeded){
      addBlob(fspeed,fpattern);
    }
  }
}

