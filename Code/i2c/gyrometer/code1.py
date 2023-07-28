import smbus

bus = smbus.SMBus(1)
address = 0x6b

bus.write_byte_data(address, 0x10, 0x60)

gyro_x = bus.read_byte_data(address, 0x22)
gyro_y = bus.read_byte_data(address, 0x24)
gyro_z = bus.read_byte_data(address, 0x26)

gyro_value = (gyro_z << 16) | (gyro_y << 8) | gyro_x

print("Gyrometer value:", gyro_value)
