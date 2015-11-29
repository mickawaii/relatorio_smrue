from xbee import XBee, ZigBee
import serial
import httplib, urllib, urllib2

WEB_ENDPOINT = "http://smrue-mi.herokuapp.com/consumption/create"
ser = serial.Serial('/dev/ttyUSB0', 9600)
xbee = ZigBee(ser)
output = "output.txt"

def sendDataToWeb(hashFormattedData):
  params = urllib.urlencode({
    "code": hashFormattedData['source_addr_long'].encode("hex"),
    "current": 1,
    "voltage": 1
  })
  req = urllib2.Request(WEB_ENDPOINT, params)
  response = urllib2.urlopen(req)

def readConsumption():
  output_file = open(output, "w")
  while True:
    try:
      response = xbee.wait_read_frame()
      output_file.write("Options\n")
      output_file.write(str(response['options'].encode("hex")$
      output_file.write("Src_addrs"+"\n")
      output_file.write(str(response['source_addr'].encode("h$")
      output_file.write("Src_addrs_long"+"\n")
      output_file.write(str(response['source_addr_long'].enco$
      output_file.write(str(response)+"\n")
      print(response)

    except Exception as e:
      print("Um erro foi dado: ")
      print(e)
      
    except KeyboardInterrupt:
      break
  output_file.close()
  ser.close()

readConsumption()