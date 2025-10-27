import paho.mqtt.client as mqtt
import paho.mqtt.publish as publish
import json
import re
import ewha

def on_connect(client, userdata, flags, rc, properties=None):
    print("Connected" )
    client.subscribe("ewha/#")

def on_message(client, userdata, msg):
    if msg.topic.startswith('ewha/exam'):
        doit(msg.topic, msg.payload.decode('utf8'))
client = mqtt.Client(mqtt.CallbackAPIVersion.VERSION2)
client.on_connect = on_connect
client.on_message = on_message
client.connect("damoa.io", 1883)

def doit(t, d):
    print(t,d)
    no=t.split('/')[-1]

    if not re.match("\\d{7}", no):
        with open('mqtt.log',"a") as f: print(f'{t} {d} 학번 숫자 오류',file=f)
        return

    no=int(no)
    if no not in ewha.stu:
        with open('mqtt.log',"a") as f: print(f'{t} {d} 학번 없음 오류',file=f)
        return

    try:
        j=json.loads(d)
    except:
        with open('mqtt.log',"a") as f: print(f'{t} {d} json 오류',file=f)
        return

    name=j.get('name')
    if name!=ewha.stu[no][0]:
        with open('mqtt.log',"a") as f: print(f'{t} {d} 이름 오류',file=f)
        return

    r={'secret':f"{ewha.stu[no][4]}"}
    client.publish(f"ewha/exam/ans/{no}", json.dumps(r))

client.loop_forever()
