/**
* @author Maria Gomez Baeza
* @date Oct 18, 2024
*/

#include <Arduino.h>
#include <DHT.h>
#include <Adafruit_Sensor.h>
#include <LiquidCrystal.h>
#include <Wire.h>

#define DHT_PIN A0
#define DHT_TYPE DHT11

LiquidCrystal lcd(12, 11, 10, 9, 8, 7);

// LCD RS: Connect to digital pin 12
// LCD Enable: Connect to digital pin 11
// LCD D4: Connect to digital pin 5
// LCD D5: Connect to digital pin 4
// LCD D6: Connect to digital pin 3
// LCD D7: Connect to digital pin 2

/**
 * @brief DHT sensor object initialization
 * 
 * This initializes the DHT sensor with the specified pin and type.
 */
DHT dht(DHT_PIN, DHT_TYPE);

const float baseTemp = 17.0; //in Celsius or room temp

/**
 * @brief Checks for errors in temperature reading
 * 
 * @param temp The temperature reading to check
 */
void readError(float temp){
 if (isnan(temp)) {
    Serial.println("ERROR: Failed to read from DHT11 sensor!");
    return;
  } 
}

/**
 * @brief Setup function for initializing serial communication and sensor
 * 
 * This function sets up the serial port and initializes the DHT sensor.
 * It also configures pins 2, 3, and 4 as output pins.
 */
void setup() {
  // OPEN A SERIAL PORT: 
  //connection in cb shown as values from the analog input on your screen
  //speed at which the cb will communicate, 9600 bits per second.
  Serial.begin(9600);

  Serial.println("Welcome to <3 Love Sensor <3");
  Serial.println("Try squeezing the temperature sensor between your finger to beguin");
  
  delay(2000);

  dht.begin();
 
 //start with pin 2. Add 1 and repeat the loop.
	for (int pinNumber = 2; pinNumber < 5; pinNumber++){
		pinMode(pinNumber, OUTPUT);
		digitalWrite(pinNumber, LOW);
  }
  lcd.begin(16,2);
  lcd.setCursor(0, 0);
}

/**
 * @brief Main loop function to read temperature and control outputs
 * 
 * This function continuously reads the temperature from the DHT sensor,
 * checks for errors, and controls the output pins based on the temperature readings.
 */
void loop() {
  float temperature = dht.readTemperature();
  readError(temperature);

  Serial.println("Temperature: ");
  Serial.print(temperature);
  Serial.println(" °C");

  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Temp: ");
  lcd.print(temperature);  //printing temperarture to the LCD display
  lcd.print("'C");

  if(temperature < baseTemp){ 
		//temperature is below baseline 
		digitalWrite(2, LOW); 
		digitalWrite(3, LOW); 
		digitalWrite(4, LOW); 
	}
  //low temperature 
	else if(temperature >= baseTemp+2 && temperature < baseTemp+4){  
		digitalWrite(2, HIGH); 
		digitalWrite(3, LOW); 
		digitalWrite(4, LOW); 
	}
  //low temperature 
	else if(temperature >= baseTemp+4 && temperature < baseTemp+6){  
		digitalWrite(2, HIGH); 
		digitalWrite(3, HIGH); 
		digitalWrite(4, LOW); 
	}
  //low temperature 
	else if(temperature >= baseTemp+6){  
		digitalWrite(2, HIGH); 
		digitalWrite(3, HIGH); 
		digitalWrite(4, HIGH); 
	}

  delay(5000); // Wait a seconds between readings

}

