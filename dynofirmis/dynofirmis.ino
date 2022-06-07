int signalPin = 2;
int sigState = 0;
int lastSigState = 0;
int changes = 0;
int t_values[254];

unsigned long lastMillis = 0;

unsigned long lastPulse = 0;

void setup() {
  pinMode(signalPin, INPUT);
  Serial.begin(19200);
  lastMillis = millis();
  lastPulse = millis();

  

}

void loop() {
   
  sigState = digitalRead(signalPin);
  if(sigState == 0 && lastSigState == 1){
    int t = millis() - lastPulse;
    t_values[changes] = t;
    changes ++;
    lastPulse = millis();
    
    
  }
  lastSigState = sigState;
  if((millis() - lastMillis) >= 100){
    int t_average;
    int t_sum;
    for (int i= 0; i <= changes; i++){
      t_sum = t_values[i];
    }
    t_average = t_sum / changes;
    
    //Serial.println(changes);
    Serial.println(t_average);
    changes = 0;
    lastMillis = millis();
  }
  
  
}
