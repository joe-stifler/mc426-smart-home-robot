import pymongo
import datetime

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
        self.db.history_sensor.drop()

    def insert_sensor(self, data):
        self.db.sensors.insert_one(data)

        self.insert_history(data['name'])

    def insert_history(self, name):
        now = datetime.datetime.now()
        year = '{:02d}'.format(now.year)
        month = '{:02d}'.format(now.month)
        day = '{:02d}'.format(now.day)
        hour = '{:02d}'.format(now.hour)
        minute = '{:02d}'.format(now.minute)
        second = '{:02d}'.format(now.second)
        day_month_year = '{}-{}-{}-{}-{}-{}'.format(year, month, day, hour, minute, second)

        self.db.history_sensor.insert_one({'name' : name, 'date' : day_month_year})

    def get_history(self, name):
        return self.db.history_sensor.find({"name": name})

    def find_all_sensors(self):
        return self.db.sensors.find()

    def find_sensor(self, name):
        return self.db.sensors.find({"name": name})
        
    def update_sensor(self, data):
        found = False
        sensor_found = None
        cursor = self.find_sensor(data['name'])

        for document in cursor:
            found = True
            sensor_found = document

        if found:
            self.db.sensors.replace_one({"name": data['name']}, data)

            if data['status'] != sensor_found['status']:
                self.insert_history(data['name'])
        else:
            self.insert_sensor(data)