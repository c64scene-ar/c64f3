//#include <Console.h>
#include <stdarg.h>

int iToC64;
char format[100];

// digital pin 2 has a pushbutton attached to it. Give it a name:
int atn_button = 2;  // BLUE
int data_button = 3; // BROWN
int clk_button = 4;  // BLACK

int atn_state, data_state, clk_state;

int debug = 0;
int prev_state = 0xFFFF,
    cur_state;

void waitForPeer(void)
{
  //Console.begin();
  Serial.begin(115200);
  while (! Serial); // Wait until Serial is ready - Leonardo
}

void setup() {
  // Now we're ready to wait for the PI to respond to our connection attempts.
  // initial connection handling.
  waitForPeer();
}

void loop() {
  //
  // First stage: PC -> C64
  //
  if (Serial.available() > 0) {
    pinMode(atn_button, OUTPUT);
    pinMode(clk_button, OUTPUT);
    pinMode(data_button, OUTPUT);
  
    iToC64 = Serial.read();
        
    data_state = (iToC64 >> 2) & 1;
    digitalWrite(data_button, data_state);
    
    clk_state = (iToC64 >> 1) & 1;
    digitalWrite(clk_button, clk_state);
  
    atn_state = iToC64 & 1;
    digitalWrite(atn_button, atn_state);
    
    if (debug) {
      snprintf(format, sizeof(format), "<<< ATN : %d - CLK : %d - DATA : %d\r", atn_state, clk_state, data_state);
      Serial.print(format);
    }
  }
  
  //
  // Second stage: C64 -> PC
  //
  pinMode(atn_button, INPUT);
  pinMode(clk_button, INPUT);
  pinMode(data_button, INPUT);
  
  data_state = digitalRead(data_button);
  clk_state = digitalRead(clk_button);
  atn_state = digitalRead(atn_button);
  
  cur_state = (data_state << 2) | (clk_state << 1) | atn_state;
    
  if (debug) {
    if (prev_state != cur_state) {
      
      prev_state = cur_state;
      
      snprintf(format, sizeof(format), ">>> ATN : %d - CLK : %d - DATA : %d", atn_state, clk_state, data_state);
      Serial.println(format);
    
      //if ((atn_state | data_state | clk_state) == 1) {
      //  Serial.println("Gotcha.....");
      //  delay(1000);
      //}
    }
  }
  else {
    Serial.write(cur_state);
  }
}
