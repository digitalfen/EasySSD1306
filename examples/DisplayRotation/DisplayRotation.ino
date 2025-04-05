#include <EasySSD1306.h>

// Create display with default resolution (128x64)
DisplayManager display(RESOLUTION_128x64);

// Interface components
TextView* txtTitle;
TextView* txtInfo;
ImageView* imgArrow;

// Define arrow image (pointing up)
const uint8_t arrowImg[] PROGMEM = {
  0x00, 0x00, 0x80, 0x00, 0x00,
  0x00, 0x00, 0xC0, 0x00, 0x00,
  0x00, 0x00, 0xE0, 0x00, 0x00,
  0x00, 0x00, 0xF0, 0x00, 0x00,
  0x00, 0x00, 0xF8, 0x00, 0x00,
  0x00, 0x00, 0xFC, 0x00, 0x00,
  0x00, 0x00, 0xFE, 0x00, 0x00,
  0x00, 0x00, 0xFF, 0x00, 0x00,
  0x00, 0x80, 0xFF, 0x00, 0x00,
  0xFC, 0xFF, 0xFF, 0xFF, 0x00,
  0xF8, 0xFF, 0xFF, 0xFF, 0x00,
  0x00, 0x00, 0xFC, 0x00, 0x00,
  0x00, 0x00, 0xF8, 0x00, 0x00,
  0x00, 0x00, 0xF0, 0x00, 0x00,
  0x00, 0x00, 0xE0, 0x00, 0x00,
  0x00, 0x00, 0xC0, 0x00, 0x00
};

// Variable to track current orientation
DisplayOrientation currentOrientation = NORMAL;
char orientationText[30];

void setup() {
  Serial.begin(115200);
  
  // Configure pins as input with pull-up
  pinMode(2, INPUT_PULLUP);  // Button for rotating
  
  // Initialize display
  if (!display.begin()) {
    Serial.println("Failed to initialize the display!");
    while(1);
  }
  
  // Configure button on display
  display.setButtonPins(2, -1);
  
  // Create components
  txtTitle = new TextView("Rotation Example");
  txtTitle->setPosition(0, 0);
  
  updateOrientationText();
  txtInfo = new TextView(orientationText);
  txtInfo->setPosition(0, 16);
  
  imgArrow = new ImageView(arrowImg, 16, 16);
  imgArrow->setPosition(56, 30);
  
  // Add components to display
  display.addComponent(txtTitle);
  display.addComponent(txtInfo);
  display.addComponent(imgArrow);
  
  display.update();
}

void loop() {
  // Check if button was pressed
  if (display.wasButton1Pressed()) {
    // Change to next orientation
    switch (currentOrientation) {
      case NORMAL:
        currentOrientation = RIGHT;
        break;
      case RIGHT:
        currentOrientation = INVERTED;
        break;
      case INVERTED:
        currentOrientation = LEFT;
        break;
      case LEFT:
        currentOrientation = NORMAL;
        break;
    }
    
    // Update information text
    updateOrientationText();
    txtInfo->setText(orientationText);
    
    // Apply new orientation to display
    display.setOrientation(currentOrientation);
    
    Serial.print("Orientation changed to: ");
    Serial.print(getOrientationDegrees());
    Serial.println(" degrees");
  }
  
  // Update display
  display.update();
  
  delay(50);  // Small delay to avoid bouncing
}

// Helper function to update orientation text
void updateOrientationText() {
  sprintf(orientationText, "Orientation: %d degrees", getOrientationDegrees());
}

// Helper function to get degrees from current orientation
int getOrientationDegrees() {
  switch (currentOrientation) {
    case NORMAL:   return 0;
    case RIGHT:    return 90;
    case INVERTED: return 180;
    case LEFT:     return 270;
    default:       return 0;
  }
} 