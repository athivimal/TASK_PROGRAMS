import paho.mqtt.client as paho
import pymongo
import json

myclient = pymongo.MongoClient("mongodb://localhost:27017/")
mydb = myclient["IOT"]
mycol = mydb["test"]
mydict=[]

def on_subscribe(client, userdata, mid, granted_qos):
    print("Subscribed: "+str(mid)+" "+str(granted_qos))

def on_message(client, userdata, msg):
    #print(msg.topic+" "+str(msg.qos)+" "+str(msg.payload))
    print('Received')    
    print(str(msg.payload))
    print(type(msg.payload))
    jo= {"am":str(msg.payload)}
    #mydict=json.loads(str(jo))
    x = mycol.insert_one(jo)
    #print(x.inserted_id)

client = paho.Client()
client.on_subscribe = on_subscribe

client.connect("broker.hivemq.com", 1883)
client.subscribe([("esp32/temperature", 1),("esp32/humidity",2)])
client.on_message = on_message
client.loop_forever()
#client.loop(90000)
#client.disconnect()
#client.loop_stop()
print(mydict,"tp")