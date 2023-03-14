#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>
#include "FirebaseESP8266.h"
#include <ESP8266WiFi.h>
#include <DHT.h>
#define DHTTYPE    DHT11
#define DHTPIN D3

DHT dht(DHTPIN, DHTTYPE);



#define FIREBASE_HOST "smarthometa-5dabc-default-rtdb.asia-southeast1.firebasedatabase.app"     // the project name address from firebase id
#define FIREBASE_AUTH "eq6UQdsfbrJ66r5ejfyicIrRtGQxd8OD3zEpzTUb"                                         // the secret key generated from firebase
#define API_KEY "AIzaSyBxfaRILvmexo-W9KuzciuJ3FxWHnwUK94"
#define FIREBASE_PROJECT_ID "smarthometa-5dabc"

//String ssid = "Algeas";
//String pass = "aezakmi123";

String ssid = "Septa";
String pass = "aezakmi10";

int relay0 = D0;
int relay1 = D1;
int relay2 = D2;
int Gas_analog = A0;
 

FirebaseData firebaseData;
FirebaseData kipasData;
FirebaseData doorData;
FirebaseData lampuData;
FirebaseData humiData;
FirebaseData tempData;
FirebaseData gasData;

FirebaseJson json;

void setup(){
  Serial.begin(115200);

//  sambung wifi
  WiFi.begin(ssid,pass);
  Serial.print("Menghubungkan....");
   while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print("-");
  }
  Serial.println("");
  Serial.println("WiFi Connected");

  pinMode(relay0, OUTPUT);
  pinMode(relay1, OUTPUT);
  pinMode(relay2, OUTPUT);


    Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
//    Firebase.set(firebaseData,"STATUS_LAMPU",1);
//    Firebase.set(firebaseData,"STATUS_DOOR",0);
//    Firebase.set(firebaseData,"STATUS_KIPAS",0);

}

void loop(){


  Firebase.getInt(kipasData, "STATUS_KIPAS");
  Serial.println(kipasData.stringData());





//  kondisi
  if(kipasData.stringData()=="1"){
    Serial.print("Kipas Menyala ");
    digitalWrite(relay0, HIGH);
    delay(100);
  }else{
    Serial.print("Kipas Padam ");
    digitalWrite(relay0, LOW);
  }

  Firebase.getInt(doorData, "STATUS_DOOR");
  Serial.println(doorData.stringData());
  
  if(doorData.stringData()=="1"){
    Serial.print("Pintu Terbuka ");
    digitalWrite(relay1, HIGH);
    delay(100);
  }else{
    Serial.print("Pintu Tertutup ");
    digitalWrite(relay1, LOW);
  }

  Firebase.getInt(lampuData, "STATUS_LAMPU");
  Serial.println(lampuData.stringData());

  if(lampuData.stringData()=="1"){
    Serial.print("Lampu Menyala ");
    digitalWrite(relay2, HIGH);
    delay(100);
  }else{
    Serial.print("Lampu Padam ");
    digitalWrite(relay2, LOW);
  }

  // Read DHT11 temperature and humidity data
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();

  //  Read MQ2
  int gas = analogRead(Gas_analog);

  //  Print temperature
  Serial.print("Temp ");
  Serial.print(temperature);

  //  Print humidity
  Serial.print("humidity ");
  Serial.print(humidity);

    //  Print gas
  Serial.print("gasLevel ");
  Serial.print(gas);

  //  Kirim data ke Firebase
   Firebase.setFloat(tempData, "/temperature", temperature);
   Firebase.setFloat(humiData, "/humidity", humidity);
   Firebase.setFloat(gasData, "/gas", gas);


  
}
