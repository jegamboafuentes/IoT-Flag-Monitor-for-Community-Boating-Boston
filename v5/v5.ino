#include <TFT_eSPI.h>
#include <SPI.h>
#include "WiFi.h"
#include <HTTPClient.h>

// WiFi credentials
const char* ssid = "myWIFI_Network";
const char* password = "myWIFI_Password";

// API URLs
const char* apiURL = "https://tv.community-boating.org/api/flag-color";
const char* textApiURL = "https://tv.community-boating.org/api/fotv";

TFT_eSPI tft = TFT_eSPI(135, 240); // Initialize the TFT display
String activeTitle = "";  // Variable to store the active title

void setup() {
  Serial.begin(115200);
  tft.init();
  tft.setRotation(3);  // Rotate display 180 degrees
  tft.fillScreen(TFT_BLACK);
  tft.setTextSize(2);
  tft.setCursor(0, 0);
  tft.setTextDatum(MC_DATUM);
  tft.setTextSize(1);

  // Connect to WiFi
  WiFi.begin(ssid, password);
  tft.setTextColor(TFT_GREEN);
  tft.drawString("Connecting to WiFi...", tft.width() / 2, tft.height() / 2);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  
  tft.fillScreen(TFT_BLACK);
  tft.setTextColor(TFT_GREEN);
  tft.drawString("Connected to WiFi", tft.width() / 2, tft.height() / 2);

  // Fetch the active title from the API
  fetchActiveTitle();

  // Fetch and display the flag color for the first time
  fetchAndDisplayFlagColor();
}

void fetchActiveTitle() {
  HTTPClient http;
  http.begin(textApiURL);
  int httpResponseCode = http.GET();

  if (httpResponseCode > 0) {
    String payload = http.getString();
    Serial.println(payload);

    // Find the title with active: true in the JSON response
    int startIndex = payload.indexOf("\"active\":true");
    if (startIndex != -1) {
      int titleIndex = payload.lastIndexOf("\"title\":\"", startIndex) + 9;
      int endIndex = payload.indexOf("\"", titleIndex);
      activeTitle = payload.substring(titleIndex, endIndex);
    }
  } else {
    Serial.println("Error on HTTP request");
  }

  http.end();
}

void fetchAndDisplayFlagColor() {
  HTTPClient http;
  http.begin(apiURL);
  int httpResponseCode = http.GET();

  if (httpResponseCode > 0) {
    String payload = http.getString();
    Serial.println(payload);
    
    // Parse the JSON response
    int index = payload.indexOf("flagColor\":\"") + 12;
    char flagColor = payload.charAt(index);

    // Determine the status and corresponding flag color
    String status;
    uint16_t flagColorCode;
    switch (flagColor) {
      case 'C':
        status = "Closed";
        flagColorCode = TFT_WHITE;
        break;
      case 'G':
        status = "Green";
        flagColorCode = TFT_GREEN;
        break;
      case 'Y':
        status = "Yellow";
        flagColorCode = TFT_YELLOW;
        break;
      case 'R':
        status = "Red";
        flagColorCode = TFT_RED;
        break;
      default:
        status = "Unknown";
        flagColorCode = TFT_WHITE;
        break;
    }

    // Add the "FLAG" label in blue
    tft.fillScreen(TFT_BLACK);
    tft.setTextSize(3);
    tft.setTextColor(TFT_BLUE);
    tft.drawString("FLAG", 10, 10);  // Draw "FLAG" on the top left

    // Display the status text below the "FLAG" label in the appropriate color
    tft.setTextColor(flagColorCode);
    tft.drawString(status, 10, 39); // Status text directly below "FLAG"

    // Draw the flag (a rectangle with a pole and wave effect)
    int flagWidth = 50;   // Increased width to make the flag bigger
    int flagHeight = 35;  // Increased height to make the flag bigger
    int flagX = tft.width() - flagWidth - 10; // Top right with a margin of 10 pixels
    int flagY = 10; // Top with a margin of 10 pixels

    // Draw the pole
    tft.fillRect(flagX - 5, flagY, 3, flagHeight, TFT_DARKGREY); 

    // Draw the flag with a simple wave effect
    for (int i = 0; i < flagHeight; i++) {
      int waveOffset = (i % 2 == 0) ? 0 : 4; // Adjusted for the larger flag
      tft.drawFastHLine(flagX + waveOffset, flagY + i, flagWidth, flagColorCode);
    }

    // Display the "status:" label and active title on separate lines
    tft.setTextSize(1);
    tft.setTextColor(TFT_PURPLE);  // Purple color for the title label
    tft.drawString("status:", 10, tft.height() - 40);  // Label "status:" above the title
    tft.setTextColor(TFT_WHITE);
    tft.drawString(activeTitle, 10, tft.height() - 20); // Title text on the next line
  } else {
    Serial.println("Error on HTTP request");
    tft.fillScreen(TFT_BLACK);
    tft.setTextColor(TFT_WHITE);
    tft.drawString("Error fetching data", tft.width() / 2, tft.height() / 2);
  }

  http.end();
}

void loop() {
  fetchAndDisplayFlagColor();  // Fetch and display flag color continuously
  delay(10000);  // Wait 10 seconds before making another API call
}
