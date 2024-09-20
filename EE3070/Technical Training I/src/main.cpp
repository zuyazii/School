#include <Arduino.h>

const int redPin = 11;
const int greenPin = 10;
const int bluePin = 9;

void ledBlink();
void readColor();
void setColor(String color);
void readColorAndBrightness();
void setColorAndBrightness(String command);

void setup() {
  // put your setup code here, to run once:
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT); 
  pinMode(bluePin, OUTPUT);

  Serial.begin(115200);
  // Serial.println("Enter a color: yellow, green, blue, or off"); // Task 3B
  // Serial.println("Enter a command (e.g., R50 for 50% Red, G100 for 100\% Green)"); // Task 3C
}

void loop() {
  ledBlink();  // Task 3A
  // readColor(); // Task 3B
  // readColorAndBrightness(); // Task 3C
}

void readColor() {
  if (Serial.available() > 0) {
    // Read the input string from the Serial monitor
    String command = Serial.readStringUntil('\n');
    command.trim();  // Remove any extra spaces or newlines
    if (command == "yellow" || command == "green" || command == "blue" || command == "off") {
      setColor(command);
    } else {
      Serial.println("Invalid command. Please enter yellow, green, blue, or off");
    }
  }
}

void setColor(String color) {
  // Yellow
  if (color == "yellow") {
    digitalWrite(redPin, HIGH);
    digitalWrite(greenPin, HIGH);
    digitalWrite(bluePin, LOW);
    Serial.println("Color set to Yellow");
  }
  // Green
  if (color == "green") {
    digitalWrite(redPin, LOW);
    digitalWrite(greenPin, HIGH);
    digitalWrite(bluePin, LOW);
    Serial.println("Color set to Green");
  }
  // Blue
  if (color == "blue") {
    digitalWrite(redPin, LOW);
    digitalWrite(greenPin, LOW);
    digitalWrite(bluePin, HIGH);
    Serial.println("Color set to Blue");
  }
  if (color == "off") {
    digitalWrite(redPin, LOW);
    digitalWrite(greenPin, LOW);
    digitalWrite(bluePin, LOW);
    Serial.println("LED turned off");
  }
}

void readColorAndBrightness() {
  if (Serial.available() > 0) {
    // Read the input string from the Serial monitor
    String command = Serial.readStringUntil('\n');
    command.trim();  // Remove any extra spaces or newlines

    // Call function to control RGB LED based on the command
    setColorAndBrightness(command);
  }
}

void setColorAndBrightness(String command) {
  // Check the first character to determine the color
  char color = command.charAt(0);
  // Extract the brightness value (assuming a 2-digit percentage, e.g., "50" or "100")
  int brightness = command.substring(1).toInt();

  // Map the percentage brightness to PWM values (0 to 255)
  int pwmValue = map(brightness, 0, 100, 0, 255);

  // Set the color based on the command
  if (color == 'R') {
    analogWrite(redPin, pwmValue);  // Set Red LED brightness
    analogWrite(greenPin, 0);       // Turn off Green LED
    analogWrite(bluePin, 0);        // Turn off Blue LED
    Serial.println("Red color with " + String(brightness) + "% brightness");
  } 
  else if (color == 'G') {
    analogWrite(redPin, 0);         // Turn off Red LED
    analogWrite(greenPin, pwmValue);// Set Green LED brightness
    analogWrite(bluePin, 0);        // Turn off Blue LED
    Serial.println("Green color with " + String(brightness) + "% brightness");
  } 
  else if (color == 'B') {
    analogWrite(redPin, 0);         // Turn off Red LED
    analogWrite(greenPin, 0);       // Turn off Green LED
    analogWrite(bluePin, pwmValue); // Set Blue LED brightness
    Serial.println("Blue color with " + String(brightness) + "% brightness");
  } 
  else {
    Serial.println("Invalid command! Please enter Rxx, Gxx, or Bxx (e.g., R50 for 50% Red).");
  }
}

void ledBlink() {
  // Yellow
  digitalWrite(redPin, HIGH);
  digitalWrite(greenPin, HIGH);
  digitalWrite(bluePin, LOW);
  // Green
  delay(1000);
  digitalWrite(redPin, LOW);
  digitalWrite(greenPin, HIGH);
  digitalWrite(bluePin, LOW);
  // Blue
  delay(1000);
  digitalWrite(redPin, LOW);
  digitalWrite(greenPin, LOW);
  digitalWrite(bluePin, HIGH);
  delay(1000);
}
