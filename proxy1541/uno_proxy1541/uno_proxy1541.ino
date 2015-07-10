//#include <Console.h>
#include <stdarg.h>

int iToPC, iToC64;
char format[100];

// digital pin 2 has a pushbutton attached to it. Give it a name:
int atn_button = 2;  // BLUE
int data_button = 3; // YELLOW
int clk_button = 4;  // BLACK

int atn_state, data_state, clk_state;

void waitForPeer(void)
{
  //Console.begin();
  Serial.begin(115200);
  while (! Serial); // Wait until Serial is ready - Leonardo

  //printf("waiting...\n");
}

void setup() {
  // Now we're ready to wait for the PI to respond to our connection attempts.
  // initial connection handling.
  waitForPeer();
  
  pinMode(atn_button, INPUT);
  pinMode(clk_button, INPUT);
  pinMode(data_button, INPUT);
  
}

void loop() {
  //
  // First stage: PC -> C64
  //
  if (Serial.available() > 0) {
    iToC64 = Serial.read();
    
    snprintf(format, sizeof(format), "<<< ATN : %d - CLK : %d - DATA : %d\r", (iToC64 & 1), ((iToC64 >> 1) & 1), ((iToC64 >> 2) & 1));
    
    Serial.print(format);
  }
  
  //
  // Second stage: C64 -> PC
  //
  atn_state = digitalRead(atn_button);
  data_state = digitalRead(data_button);
  clk_state = digitalRead(clk_button);
  
  if (1) {
    snprintf(format, sizeof(format), ">>> ATN : %d - CLK : %d - DATA : %d", atn_state, clk_state, data_state);
    Serial.println(format);
    
    if ((atn_state | data_state | clk_state) == 1) {
      Serial.println("Gotcha.....");
      //delay(1000);
    }
  }
  else {
    iToPC = (data_state << 2) & (clk_state << 1) & atn_state;
    Serial.write(iToPC);
  }
}
