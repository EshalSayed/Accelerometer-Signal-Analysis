#include <Wire.h>
#include <MPU6050.h>

MPU6050 mpu;

void setup() {
  Serial.begin(38400); // Make sure Serial Monitor is set to 38400
  Wire.begin();

  Serial.println("Setup complete!");
  Serial.println("Initializing I2C devices...");

  mpu.initialize();

  if (mpu.testConnection()) {
    Serial.println("MPU6050 connection successful!");
  } else {
    Serial.println("MPU6050 connection failed!");
    while (1); // Stop here if connection fails
  }
}

void loop() {
  int16_t ax, ay, az, gx, gy, gz;
  mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);

  // Convert to human-friendly units
  float ax_g = ax / 16384.0;
  float ay_g = ay / 16384.0;
  float az_g = az / 16384.0;

  float gx_dps = gx / 131.0;
  float gy_dps = gy / 131.0;
  float gz_dps = gz / 131.0;

  // Print readings
  Serial.print("Accel (g): X="); Serial.print(ax_g, 2);
  Serial.print(" Y="); Serial.print(ay_g, 2);
  Serial.print(" Z="); Serial.println(az_g, 2);

  Serial.print("Gyro (°/s): X="); Serial.print(gx_dps, 2);
  Serial.print(" Y="); Serial.print(gy_dps, 2);
  Serial.print(" Z="); Serial.println(gz_dps, 2);

  Serial.println("---------------------");
  delay(200); // Update every 0.2 seconds
}

