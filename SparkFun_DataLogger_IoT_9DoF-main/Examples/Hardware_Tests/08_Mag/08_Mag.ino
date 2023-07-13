// SparkFun DataLogger IoT – 9DoF Test Example
// Tested with Espressif ESP32 v2.0.5 and the "ESP32 Dev Module" board definition

/**********************************************************************************************
 *
 * WARNING!
 * 
 * This is a sketch we wrote to test the DataLogger IoT – 9DoF hardware.
 * Please think very carefully before uploading it to your DataLogger.
 * 
 * You will overwrite the DataLogger firmware, leaving it unable to update or restore itself. 
 * 
 * The DataLogger IoT – 9DoF comes pre-programmed with amazing firmware which can do _so_ much.
 * It is designed to be able to update itself and restore itself if necessary.
 * But it can not do that if you overwrite the firmware with this test sketch.
 * It is just like erasing the restore partition on your computer hard drive.
 * Do not do it - unless you really know what you are doing.
 * 
 * Really. We mean it.
 * 
 * Your friends at SparkFun.
 * 
 * License: MIT. Please see LICENSE.MD for more details
 * 
 **********************************************************************************************/

// Needs v1.0.3 of the MMC5983MA Library

//#define MAG_CS 27 // The MMC5983 chip select is connected to D27
int MAG_CS = 27;

#include <SPI.h>

#include <SparkFun_MMC5983MA_Arduino_Library.h> //Click here to get the library: http://librarymanager/All#SparkFun_MMC5983MA

SFE_MMC5983MA myMag;

void setup()
{
    Serial.begin(115200);
    Serial.println("MMC5983MA Example");

    SPI.begin();

    if (myMag.begin(MAG_CS) == false)
    {
        Serial.println("MMC5983MA did not respond - check your wiring. Freezing.");
        while (true)
            ;
    }

    Serial.println("MMC5983MA connected");

    myMag.softReset();

    int celsius = myMag.getTemperature();

    Serial.print("Die temperature: ");
    Serial.print(celsius);
    Serial.println("°C");
}

void loop()
{
    uint32_t currentX = 0;
    uint32_t currentY = 0;
    uint32_t currentZ = 0;
    double normalizedX = 0;
    double normalizedY = 0;
    double normalizedZ = 0;

    myMag.getMeasurementXYZ(&currentX, &currentY, &currentZ);

    Serial.print("X axis raw value: ");
    Serial.print(currentX);
    Serial.print("\tY axis raw value: ");
    Serial.print(currentY);
    Serial.print("\tZ axis raw value: ");
    Serial.println(currentZ);

    normalizedX = (double)currentX - 131072.0;
    normalizedX /= 131072.0;
    normalizedY = (double)currentY - 131072.0;
    normalizedY /= 131072.0;
    normalizedZ = (double)currentZ - 131072.0;
    normalizedZ /= 131072.0;

    Serial.print("X axis field (Gauss): ");
    Serial.print(normalizedX * 8, 5);

    Serial.print("\tY axis field (Gauss): ");
    Serial.print(normalizedY * 8, 5);

    Serial.print("\tZ axis field (Gauss): ");
    Serial.println(normalizedZ * 8, 5);

    Serial.println();
    delay(100);
}
