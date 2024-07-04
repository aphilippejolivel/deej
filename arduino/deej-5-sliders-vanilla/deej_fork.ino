const int NUM_SLIDERS = 3;
const int NUM_SWITCHES = 1;
const int analogInputs[NUM_SLIDERS] = {A0, A1, A2};
const int digitalInputs[NUM_SWITCHES] = {8};

int analogSliderValues[NUM_SLIDERS];
int digitalSwitchValues[NUM_SLIDERS];

void setup() { 
  for (int i = 0; i < NUM_SLIDERS; i++) {
    pinMode(analogInputs[i], INPUT);
  }
  for (int i = 0; i < NUM_SWITCHES; i++) {
    pinMode(digitalInputs[i], INPUT);
  }
  Serial.begin(9600);
}

void loop() {
  updateSliderValues();
  sendSliderValues(); // Actually send data (all the time)
  updateSwitchValues();
  sendSwitchValues(); // Actually send data (all the time)
  // printSliderValues(); // For debug
  delay(10);
}

void updateSwitchValues(){
  for (int i = 0; i < NUM_SWITCHES; i++) {
     digitalSwitchValues[i] = digitalRead(digitalInputs[i]);
  }  
}

void updateSliderValues() {
  for (int i = 0; i < NUM_SLIDERS; i++) {
     analogSliderValues[i] = analogRead(analogInputs[i]);
  }
}

void sendSwitchValues() {
  String builtString = String("Switch|");

  for (int i = 0; i < NUM_SWITCHES; i++) {
    builtString += String((int)digitalSwitchValues[i]);

    if (i < NUM_SWITCHES - 1) {
      builtString += String("|");
    }
  }
  
  Serial.println(builtString);
}

void sendSliderValues() {
  String builtString = String("Slider|");

  for (int i = 0; i < NUM_SLIDERS; i++) {
    builtString += String((int)analogSliderValues[i]);

    if (i < NUM_SLIDERS - 1) {
      builtString += String("|");
    }
  }
  
  Serial.println(builtString);
}

void printSliderValues() {
  for (int i = 0; i < NUM_SLIDERS; i++) {
    String printedString = String("Slider #") + String(i + 1) + String(": ") + String(analogSliderValues[i]) + String(" mV");
    Serial.write(printedString.c_str());

    if (i < NUM_SLIDERS - 1) {
      Serial.write(" | ");
    } else {
      Serial.write("\n");
    }
  }
}