#include <Arduino.h>

// Pines ADC1 del ESP32 (funcionan siempre, incluso con WiFi activo).
// GPIO34 y GPIO35 son solo entrada, ideales para potenciómetros.
const int POT1_PIN = 34;
const int POT2_PIN = 35;

void setup() {
    Serial.begin(115200);
    analogReadResolution(12);        // 0 - 4095
    analogSetAttenuation(ADC_11db);  // Rango completo 0 - 3.3 V
    delay(2000);

    Serial.println("ESP32 INICIADO");
    Serial.println("Lectura de potenciometros:");
}

void loop() {
    int pot1 = analogRead(POT1_PIN);
    int pot2 = analogRead(POT2_PIN);

    Serial.print(pot1);
    Serial.print(",");
    Serial.println(pot2);

    delay(50);
}
