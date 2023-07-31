#for calibrating the value of gyrometer in a loop in lsm6dsx in .py

import smbus

LSM6DSx_ADDRESS = 0x6B
LSM6DSx_GYRO_SENSITIVITY = 250 / 32768

bus = smbus.SMBus(1)
bus.write_byte_data(LSM6DSx_ADDRESS, 0x10, 0x60)  


print('recording data')
while True:
    raw_data = bus.read_i2c_block_data(LSM6DSx_ADDRESS, 0x22, 2)
    raw_value = (raw_data[1] << 8) | raw_data[0]
    
    if raw_value > 32767:
        raw_value -= 65536
    angular_velocity = raw_value * LSM6DSx_GYRO_SENSITIVITY

    print("Raw Angular Velocity:", raw_value)
    print("Angular Velocity (dps):", angular_velocity)
