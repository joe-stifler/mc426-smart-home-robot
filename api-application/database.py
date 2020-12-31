import pymongo

class Database(object):
    
    URI = "mongodb://localhost:27017/"

    # URI = "mongodb+srv://gabriel:bussunda123@cluster0.ltmtq.mongodb.net/EngSof?retryWrites=true&w=majority"

    def __init__(self):
        connect = pymongo.MongoClient(self.URI)

        self.db = connect.EngSof
        
    def insert(self, data):
        self.db.users.insert_one(data)

    def find(self, email):
        return self.db.users.find({"email": email})
        
    def update(self, data, email):
        self.db.users.replace_one({"email": email}, data)
        