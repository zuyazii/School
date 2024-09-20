const int redPin = 11;
const int greenPin = 10;
const int bluePin = 9;

void readColor();
void setColor(String color);

void setup() {
  // put your setup code here, to run once:
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT); 
  pinMode(bluePin, OUTPUT);

  Serial.begin(115200);
  Serial.println("Enter a color: yellow, green, blue, or off"); // Task 3B
}

void loop() {
  readColor();
}

void readColor() {
  if (Serial.available() > 0) {
    // Read the input string from the Serial monitor
    String command = Serial.readStringUntil('\n');
    command.trim();  // Remove any extra spaces or newlines
    if (command == "red" || command == "yellow" || command == "green" || command == "blue" || command == "off") {
      setColor(command);
    } else {
      Serial.println("Invalid command. Please enter red, yellow, green, blue, or off");
    }
  }
}

void setColor(String color) {
  // Red
  if (color == "red") {
    digitalWrite(redPin, HIGH);
    digitalWrite(greenPin, LOW);
    digitalWrite(bluePin, LOW);
    Serial.println("Color set to Red");
  }
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

