#include <ESP8266WiFi.h>
#include <FirebaseESP8266.h>

#include "addons/TokenHelper.h"
#include "addons/RTDBHelper.h"

#include <DHT.h>
#define DHTPIN 2
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

#define WIFI_SSID "Tin Uyen lau2_2.4G"
#define WIFI_PASSWORD "tinuyen774"

#define API_KEY "AIzaSyAVKvG8t-VSCmoTN0vPBctAkAb9PPwly90"

#define DATABASE_URL "https://weather-app-aee77-default-rtdb.asia-southeast1.firebasedatabase.app/" 

#define USER_EMAIL "taitranonlyt100920@gmail.com"
#define USER_PASSWORD "123456"

FirebaseData fbdo;

FirebaseAuth auth;
FirebaseConfig config;
void setup()
{

    Serial.begin(115200);
    Serial.println();
    Serial.println();
  
  dht.begin();

    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    Serial.print("Connecting to Wi-Fi");
    while (WiFi.status() != WL_CONNECTED)
    {
        Serial.print(".");
        delay(300);
    }
    Serial.println();
    Serial.print("Connected with IP: ");
    Serial.println(WiFi.localIP());
    Serial.println();

    Serial.printf("Firebase Client v%s\n\n", FIREBASE_CLIENT_VERSION);

    /* Assign the api key (required) */
    config.api_key = API_KEY;

    /* Assign the user sign in credentials */
    auth.user.email = USER_EMAIL;
    auth.user.password = USER_PASSWORD;

    /* Assign the RTDB URL (required) */
    config.database_url = DATABASE_URL;

    /* Assign the callback function for the long running token generation task */
    config.token_status_callback = tokenStatusCallback; //see addons/TokenHelper.h

    Firebase.begin(&config, &auth);

   
    Firebase.reconnectWiFi(true);

    fbdo.setBSSLBufferSize(512, 2048);
}

void loop() {
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  
  if(isnan(h) || isnan(t)){
    Serial.println("Khong the doc duoc DHT");
    return;
    }
    Serial.print("Nhiet do: ");
    Serial.print(t); 
    Serial.println();
    
    Serial.print("Do am: ");
    Serial.print(h); 
    Serial.println();

    Firebase.setFloatAsync(fbdo, "/nhietdo", t);
    Firebase.setFloatAsync(fbdo, "/doam", h);
}
