//#include <Console.h>
#include <stdarg.h>

int iToC64;
char format[100];

// digital pin 2 has a pushbutton attached to it. Give it a name:
int atn_button = 2;  // BLUE
int data_button = 3; // YELLOW
int clk_button = 4;  // BLACK

int atn_state, data_state, clk_state;

int debug = 1;
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
    
    if (debug) {
      snprintf(format, sizeof(format), "<<< ATN : %d - CLK : %d - DATA : %d\r", (iToC64 & 1), ((iToC64 >> 1) & 1), ((iToC64 >> 2) & 1));
      Serial.print(format);
    }
  }
  
  //
  // Second stage: C64 -> PC
  //
  pinMode(atn_button, INPUT);
  pinMode(clk_button, INPUT);
  pinMode(data_button, INPUT);
  
  atn_state = digitalRead(atn_button);
  data_state = digitalRead(data_button);
  clk_state = digitalRead(clk_button);
  
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

  /*
  for (int i = 0; i < 20; i++) {
    Serial.println("high");
    digitalWrite(data_button, HIGH);
    delay(2000);
    Serial.println("low");
    digitalWrite(data_button, LOW);
    delay(2000);
  }
  */
}
