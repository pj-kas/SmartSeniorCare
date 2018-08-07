import paho.mqtt.client as mqtt
'''
# Don't forget to change the variables for the MQTT broker!
mqtt_topic = "motion"
mqtt_broker_ip = "192.168.0.166"

client = mqtt.Client("ESP_1")

# These functions handle what happens when the MQTT client connects
# to the broker, and what happens then the topic receives a message
def on_connect(self, client, userdata, rc):
    # rc is the error code returned when connecting to the broker
    print "Connected!", str(rc)
    
    # Once the client has connected to the broker, subscribe to the topic
    self.subscribe(mqtt_topic)
    
def on_message(client, userdata, msg):
    # This function is called everytime the topic is published to.
    # If you want to check each message, and do something depending on
    # the content, the code to do this should be run in this function
    
    print "Topic: ", self.topic + "\nMessage: " + str(client.payload)
    
    # The message itself is stored in the msg variable
    # and details about who sent it are stored in userdata

# Here, we are telling the client which functions are to be run
# on connecting, and on receiving a message
client.on_connect = on_connect
client.on_message = on_message

# Once everything has been set up, we can (finally) connect to the broker
# 1883 is the listener port that the MQTT broker is using
client.connect(mqtt_broker_ip, 1883)

# Once we have told the client to connect, let the client object run itself
client.loop_forever()
client.disconnect()
'''
import time
from datetime import datetime
import pytz
from pytz import timezone

def on_message(client, data, message):
    date_format = "%Y-%m-%d %H:%M:%S %Z"
    date = datetime.now(tz=pytz.utc)
    date = date.astimezone(timezone('US/Pacific'))
    print str(message.payload.decode("utf-8")) + ', ' + date.strftime(date_format)
    #print("Topic: ", message.topic)

address = "192.168.0.166"
client = mqtt.Client("P1")
client.on_message = on_message
client.connect(address)
#client.loop_start()
client.subscribe("motion")
time.sleep(4)
client.loop_forever()
#client.loop_stop()
