import board
import busio
import adafruit_lsm6ds

i2c = busio.I2C(board.SCL, board.SDA)
sensor = adafruit_lsm6ds.LSM6DS33(i2c)

gyro = sensor.gyro
gyro_data = gyro
gyro_value = gyro_data[2]  # Index 2 corresponds to the Z-axis gyrometer value

print("Gyrometer value (Z-axis):", gyro_value)

