// Template ID, Device Name and Auth Token are provided by the Blynk.Cloud
// See the Device Info tab, or Template settings
#define BLYNK_TEMPLATE_ID "your template ID"
#define BLYNK_DEVICE_NAME "your device name"
#define BLYNK_AUTH_TOKEN "your auth token"


// Comment this out to disable prints and save space
#define BLYNK_PRINT Serial


#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>

char auth[] = BLYNK_AUTH_TOKEN;

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "your ssid";
char pass[] = "your password";


int timerID; //a global variable to track the timer using its ID.
long duration = 5000; //time in millisocends.

int menuindex; //a global variable to hold the menu widget item index.

String URL; //a global variable to hold the url.
String payload; // a global variable to hold the http request content.

String value_1; //a global variable to hold the extracted values from the arduinojson document.
String value_2; //a global variable to hold the extracted values from the arduinojson document.
String value_3; //a global variable to hold the extracted values from the arduinojson document.
String value_4; //a global variable to hold the extracted values from the arduinojson document.
String value_5; //a global variable to hold the extracted values from the arduinojson document.

String placeholder_1 = "Placeholder 1"; //a global variable to hold the menu items.
String placeholder_2 = "Placeholder 2"; //a global variable to hold the menu items.
String placeholder_3 = "Placeholder 3"; //a global variable to hold the menu items.
String placeholder_4 = "Placeholder 4"; //a global variable to hold the menu items.
String placeholder_5 = "Placeholder 5"; //a global variable to hold the menu items.


BlynkTimer timer;

void setup()
{
  // Debug console
  Serial.begin(115200);

  Blynk.begin(auth, ssid, pass);
  
  timerID = timer.setInterval(duration, GET_DATA);
  timer.disable(timerID); //timer will be disabled at startup.
}

void loop()
{
  Blynk.run();
  timer.run();

}

BLYNK_CONNECTED() {
    Blynk.syncAll();
}

BLYNK_WRITE(V0)
{
  int Value = param.asInt(); //assigning the incoming value from pin V0 to a local variable called "value".
  
  if (Value == 0){
    Blynk.setProperty(V2, "isDisabled", false); //GET button is enabled.
    Blynk.setProperty(V3, "isDisabled", true); //time setting menu is disabled.
    timer.disable(timerID); //disable timer.

  } else if (Value == 1) {
    Blynk.setProperty(V2, "isDisabled", true); //GET button is disabled.
    Blynk.setProperty(V3, "isDisabled", false); //time setting menu is enabled.
    timer.enable(timerID); //enable timer.
  }
 }

BLYNK_WRITE(V1) {
   URL = param.asStr(); //assigning the incoming string from pin V1 to a global variable called "URL".
}

BLYNK_WRITE(V2) {
  int Value = param.asInt(); //assigning incoming value from pin V2 to a local variable called "value".
  
  if (Value == 1){

  HTTPClient http;
  http.begin(URL);

  int httpResponseCode = http.GET();
  if (httpResponseCode > 0) {
    Serial.print("HTTP ");
    Serial.println(httpResponseCode);
    payload = http.getString();
    Serial.println();
    Serial.println(payload);
  }
  else {
    Serial.print("Error code: ");
    Serial.println(httpResponseCode);
    Serial.println(":-(");

    http.end();
    
  }
    Blynk.virtualWrite(V4, httpResponseCode);

    DynamicJsonDocument doc(1024);

  // Parse JSON object
    DeserializationError error = deserializeJson(doc, payload);
    if (error) {
    Serial.print(F("deserializeJson() failed: "));
    Serial.println(error.f_str());
    http.end();
    return;
    }

    // Extract values
    Serial.println(F("Response:"));
    value_1 = (doc[placeholder_1].as<String>()); //assigning the extracted value to a global variable called "value_1".
    Serial.println(value_1);
    value_2 = (doc[placeholder_2].as<String>()); //assigning the extracted value to a global variable called "value_2".
    Serial.println(value_2);
    value_3 = (doc[placeholder_3].as<String>()); //assigning the extracted value to a global variable called "value_3".
    Serial.println(value_3);
    value_4 = (doc[placeholder_4].as<String>()); //assigning the extracted value to a global variable called "value_4".
    Serial.println(value_4);
    value_5 = (doc[placeholder_5].as<String>()); //assigning the extracted value to a global variable called "value_5".
    Serial.println(value_5);


  // Disconnect
    http.end();

    Blynk.virtualWrite(V7, value_1); //send "value_1" to a labeled value widget attached to virtual pin 7.
    Blynk.virtualWrite(V8, value_2); //send "value_1" to a labeled value widget attached to virtual pin 8.
    Blynk.virtualWrite(V9, value_3); //send "value_1" to a labeled value widget attached to virtual pin 9.
    Blynk.virtualWrite(V10, value_4); //send "value_1" to a labeled value widget attached to virtual pin 10.
    Blynk.virtualWrite(V11, value_5); //send "value_1" to a labeled value widget attached to virtual pin 11.
 }
} 

BLYNK_WRITE(V3) { //change timer duration based on the selected menu item.
  switch (param.asInt()) {
    case 0: { // Item 1
      timer.deleteTimer(timerID); //delete the timer.
      duration = 5000; //set the duration to 5 seconds.
      timerID = timer.setInterval(duration, GET_DATA); //create a timer based on the new duration.
      break;
    }
    case 1: { // Item 2
      timer.deleteTimer(timerID); //delete the timer.
      duration = 10000; //set the duration to 5 seconds.
      timerID = timer.setInterval(duration, GET_DATA); //create a timer based on the new duration.
      break;
    }
     case 2: { // Item 2
      timer.deleteTimer(timerID); //delete the timer.
      duration = 15000; //set the duration to 5 seconds.
      timerID = timer.setInterval(duration, GET_DATA); //create a timer based on the new duration.
      break;
    }
     case 3: { // Item 2
      timer.deleteTimer(timerID); //delete the timer.
      duration = 20000; //set the duration to 5 seconds.
      timerID = timer.setInterval(duration, GET_DATA); //create a timer based on the new duration.
      break;
    }
    case 4: { // Item 2
      timer.deleteTimer(timerID); //delete the timer.
      duration = 25000; //set the duration to 5 seconds.
      timerID = timer.setInterval(duration, GET_DATA); //create a timer based on the new duration.
      break;
    }
    case 5: { // Item 2
      timer.deleteTimer(timerID); //delete the timer.
      duration = 30000; //set the duration to 5 seconds.
      timerID = timer.setInterval(duration, GET_DATA); //create a timer based on the new duration.
      break;
    }
    case 6: { // Item 2
      timer.deleteTimer(timerID); //delete the timer.
      duration = 60000; //set the duration to 5 seconds.
      timerID = timer.setInterval(duration, GET_DATA); //create a timer based on the new duration.
      break;
    }
     case 7: { // Item 2
      timer.deleteTimer(timerID); //delete the timer.
      duration = 120000; //set the duration to 5 seconds.
      timerID = timer.setInterval(duration, GET_DATA); //create a timer based on the new duration.
      break;
    }
     case 8: { // Item 2
      timer.deleteTimer(timerID); //delete the timer.
      duration = 180000; //set the duration to 5 seconds.
      timerID = timer.setInterval(duration, GET_DATA); //create a timer based on the new duration.
      break;
    }
    case 9: { // Item 2
      timer.deleteTimer(timerID); //delete the timer.
      duration = 240000; //set the duration to 5 seconds.
      timerID = timer.setInterval(duration, GET_DATA); //create a timer based on the new duration.
      break;
    }
     case 10: { // Item 2
      timer.deleteTimer(timerID); //delete the timer.
      duration = 300000; //set the duration to 5 seconds.
      timerID = timer.setInterval(duration, GET_DATA); //create a timer based on the new duration.
      break;
    }
    case 11: { // Item 2
      timer.deleteTimer(timerID); //delete the timer.
      duration = 600000; //set the duration to 5 seconds.
      timerID = timer.setInterval(duration, GET_DATA); //create a timer based on the new duration.
      break;
    }
    case 12: { // Item 2
      timer.deleteTimer(timerID); //delete the timer.
      duration = 900000; //set the duration to 5 seconds.
      timerID = timer.setInterval(duration, GET_DATA); //create a timer based on the new duration.
      break;
    }                                           
  }
}

BLYNK_WRITE(V5) {
  menuindex = param.asInt(); //assigning the menu item index to a global variable called "menuindex".
}

BLYNK_WRITE(V6) {
  String data = param.asStr(); //assigning the incoming string to a local variable called "data"
  if (menuindex == 0) {
    placeholder_1 = data; 
  } else if (menuindex == 1) {
    placeholder_2 = data;
  } else if (menuindex == 2) {
    placeholder_3 = data;
  } else if (menuindex == 3) {
    placeholder_4 = data;
  } else if (menuindex == 4) {
    placeholder_5 = data;
  }
    Blynk.setProperty(V5, "labels", placeholder_1, placeholder_2, placeholder_3, placeholder_4, placeholder_5); //change menu items based on variables values.
}

BLYNK_WRITE(V12) {
  int value = param.asInt();
  if (value == 1){
    placeholder_1 = "Placeholder 1"; //reset the variable to the defalt value.
    placeholder_2 = "Placeholder 2"; //reset the variable to the defalt value.
    placeholder_3 = "Placeholder 3"; //reset the variable to the defalt value.
    placeholder_4 = "Placeholder 4"; //reset the variable to the defalt value.
    placeholder_5 = "Placeholder 5"; //reset the variable to the defalt value.

    Blynk.setProperty(V5, "labels", placeholder_1, placeholder_2, placeholder_3, placeholder_4, placeholder_5); //reset the menu items to their default labels.
  }
}


void GET_DATA()
{
  HTTPClient http;
  http.begin(URL);

  int httpResponseCode = http.GET();
  if (httpResponseCode > 0) {
    Serial.print("HTTP ");
    Serial.println(httpResponseCode);
    payload = http.getString();
    Serial.println();
    Serial.println(payload);
  }
  else {
    Serial.print("Error code: ");
    Serial.println(httpResponseCode);
    Serial.println(":-(");

    http.end();
    
  }
    Blynk.virtualWrite(V4, httpResponseCode);

    DynamicJsonDocument doc(1024);

  // Parse JSON object
    DeserializationError error = deserializeJson(doc, payload);
    if (error) {
    Serial.print(F("deserializeJson() failed: "));
    Serial.println(error.f_str());
    http.end();
    return;
    }

    // Extract values
    Serial.println(F("Response:"));
    value_1 = (doc[placeholder_1].as<String>());
    Serial.println(value_1);
    value_2 = (doc[placeholder_2].as<String>());
    Serial.println(value_2);
    value_3 = (doc[placeholder_3].as<String>());
    Serial.println(value_3);
    value_4 = (doc[placeholder_4].as<String>());
    Serial.println(value_4);
    value_5 = (doc[placeholder_5].as<String>());
    Serial.println(value_5);


  // Disconnect
    http.end();

    Blynk.virtualWrite(V7, value_1);
    Blynk.virtualWrite(V8, value_2);
    Blynk.virtualWrite(V9, value_3);
    Blynk.virtualWrite(V10, value_4);
    Blynk.virtualWrite(V11, value_5);
 }
