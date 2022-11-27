import pymongo
myclient = pymongo.MongoClient("mongodb://localhost:27017/")
mydb = myclient["local"]
mycol = mydb["test"]
x= mycol.find_one()
for x in mycol.find():
    print(x)
    print('temp',x['am'])