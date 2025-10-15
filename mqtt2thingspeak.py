import json
import paho.mqtt.client as mqtt
from myutil import d2s
import sys
import requests
import json

APIKEY='use-your-own-thingspeak-apk-key'

def on_connect(client, userdata, flags, rc, properties=None):
    print("Connected" )
    client.subscribe("ewha/0317137263")

def on_message(client, userdata, msg):
    doit(msg.topic, msg.payload.decode('utf8'))

client = mqtt.Client(mqtt.CallbackAPIVersion.VERSION2)
client.on_connect = on_connect
client.on_message = on_message
client.connect("damoa.io", 1883)

def doit(t, d):
    j=json.loads(d)
    print(j)
    url=f'https://api.thingspeak.com/update?api_key={APIKEY}&field1={j["온도"]}&field2={j["습도"]}'
    print(url)
    r=requests.get(url)
    print(r.text)

client.loop_forever()
