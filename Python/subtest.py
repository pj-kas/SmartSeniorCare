import paho.mqtt.client as mqtt
import time
from time import strftime, gmtime

MESSAGE = ""

def on_message(client, data, message):
    global MESSAGE
    MESSAGE = str(message.payload.decode("utf-8"))
    #print("Topic: ", message.topic) #Used for debugging
def read_node():
    address = "192.168.0.166" #Static IP of Raspberry Pi
    client = mqtt.Client("P1") #Arbitrary client name
    client.on_message = on_message
    client.connect(address)
    client.loop_start()
    client.subscribe("motion") #Arbitrary topic name
    time.sleep(4)
    client.loop_stop()
