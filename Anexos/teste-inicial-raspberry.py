from xbee import ZigBee
import serial

ser = serial.Serial('/dev/ttyUSB0', 9600)
xbee = ZigBee(ser)

while True:
	try:
		response = xbee.wait_read_frame()
		print(response)
	except:
		break;

ser.close()