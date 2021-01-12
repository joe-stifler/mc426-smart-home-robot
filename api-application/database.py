import pymongo

class Database(object):
    
    URI = "mongodb://localhost:27017/"

    # URI = "mongodb+srv://joe:joe123@cluster0.l9x0m.mongodb.net/EngSoftware?retryWrites=true&w=majority"

    def __init__(self):
        connect = pymongo.MongoClient(self.URI)

        self.db = connect.EngSoftware
        
    def insert_user(self, data):
        self.db.users.insert_one(data)

    def find_user(self, email):
        return self.db.users.find({"email": email})
        
    def update_user(self, data, email):
        self.db.users.replace_one({"email": email}, data)
        
    def drop_sensor_collection(self):
        self.db.sensors.drop()

    def insert_sensor(self, data):
        self.db.sensors.insert_one(data)

    def find_all_sensors(self):
        return self.db.sensors.find()

    def find_sensor(self, name):
        return self.db.sensors.find({"name": name})
        
    def update_sensor(self, data):
        found = False
        cursor = self.find_sensor(data['name'])

        for document in cursor:
            found = True

        if found:
            self.db.sensors.replace_one({"name": data['name']}, data)
        else:
            self.insert_sensor(data)