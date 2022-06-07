int signalPin = 2;
int sigState = 0;
int lastSigState = 0;
int changes = 0;

unsigned long lastMillis;
unsigned long  currentMillis;
void setup() {
  pinMode(signalPin, INPUT);
  Serial.begin(19200);
  lastMillis = millis();

}

void loop() {
  //currentMillis = millis();  
  sigState = digitalRead(signalPin);
  if(sigState != lastSigState){
    changes ++;
    lastSigState = sigState;
  }
  int t = millis() - lastMillis;
  if(t >= 100){
    int rpm = changes * (3000 / t); // 1 rpm => 1/60 per s => 1/60000 per 1 ms. Code registers every change in state, so twice the actual number of pulses -> dive by 2 => 1/30000 per ms. Our plate that we measure has 10 holes, so we divede by 10 => 1/3000.
    //Serial.println(changes);
    Serial.println(rpm);
    changes = 0;
    lastMillis = millis();
  }
  
}
