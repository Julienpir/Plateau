#include <FastLED.h>
#define NUM_LEDS 1
#define DATA_PIN 4
CRGB leds[NUM_LEDS];

int tension, val;
// RemoteXY select connection mode and include library  
#define REMOTEXY_MODE__ESP8266_HARDSERIAL_POINT

#include <RemoteXY.h> 

// RemoteXY connection settings  
#define REMOTEXY_SERIAL Serial 
#define REMOTEXY_SERIAL_SPEED 115200 
#define REMOTEXY_WIFI_SSID "RemoteXY" 
#define REMOTEXY_WIFI_PASSWORD "12345678" 
#define REMOTEXY_SERVER_PORT 6377 


// RemoteXY configurate   
#pragma pack(push, 1) 
uint8_t RemoteXY_CONF[] = 
  { 255,8,0,0,0,125,0,8,13,4,
  129,0,16,5,63,6,0,17,67,111,
  110,116,114,111,108,101,32,100,101,32,
  108,97,32,99,111,117,108,101,117,114,
  0,6,0,38,22,34,34,2,2,26,
  4,0,34,19,9,34,1,203,26,4,
  0,51,19,9,34,1,36,26,4,0,
  66,20,9,34,1,135,26,131,1,2,
  23,20,7,1,2,8,83,108,105,100,
  101,114,115,0,131,0,2,13,20,7,
  2,2,8,68,105,115,113,117,101,0,
  1,0,8,40,12,12,1,1,31,88,
  0,1,0,8,40,12,12,2,1,31,
  88,0 }; 
   
// this structure defines all the variables of your control interface  
struct { 

    // input variable
  uint8_t rgb_1_r; // =0..255 Red color value 
  uint8_t rgb_1_g; // =0..255 Green color value 
  uint8_t rgb_1_b; // =0..255 Blue color value 
  int8_t slider_1; // =0..100 slider position 
  int8_t slider_2; // =0..100 slider position 
  int8_t slider_3; // =0..100 slider position 
  uint8_t Clear_Disque; // =1 if button pressed, else =0 
  uint8_t Clear_Sliders; // =1 if button pressed, else =0 

    // other variable
  uint8_t connect_flag;  // =1 if wire connected, else =0 

} RemoteXY; 
#pragma pack(pop) 

///////////////////////////////////////////// 
//           END RemoteXY include          // 
///////////////////////////////////////////// 

#define PIN_CLEAR_DISQUE 52
#define PIN_CLEAR_SLIDERS 53

bool page1 = true;
bool page2 = false;


void setup()  
{ 
  RemoteXY_Init ();  
   
  pinMode (PIN_CLEAR_DISQUE, OUTPUT);
  pinMode (PIN_CLEAR_SLIDERS, OUTPUT);
   
  FastLED.addLeds<WS2812B, DATA_PIN, GRB>(leds, NUM_LEDS);
  Serial.begin(115200);

   
} 

//============================================================

void loop()  
{  
  RemoteXY_Handler (); 
   
  digitalWrite(PIN_CLEAR_DISQUE, (RemoteXY.Clear_Disque==0)?LOW:HIGH);
  digitalWrite(PIN_CLEAR_SLIDERS, (RemoteXY.Clear_Sliders==0)?LOW:HIGH);
  
if (RemoteXY.Clear_Disque !=0 ){
  page1 = true;
  page2 = false;
  leds[0] = CRGB(int(RemoteXY.slider_2*2.55), int(RemoteXY.slider_3*2.55),int(RemoteXY.slider_1*2.55)); 
}

if (RemoteXY.Clear_Sliders !=0 ){
  page1 = true;
  page2 = false;
  leds[0] = CRGB(RemoteXY.rgb_1_r, RemoteXY.rgb_1_g, RemoteXY.rgb_1_b); 
}

 if (page1 = true){
    leds[0] = CRGB(RemoteXY.rgb_1_r, RemoteXY.rgb_1_g, RemoteXY.rgb_1_b); 
    page2 = false;
 }
 if (page2 = true){
    leds[0] = CRGB(int(RemoteXY.slider_2*2.55), int(RemoteXY.slider_3*2.55),int(RemoteXY.slider_1*2.55)); 
    page1 = false;
 }

 
  FastLED.show();


}
