import pymongo

class Database(object):
    
    URI = "mongodb+srv://gabriel:bussunda123@cluster0.ltmtq.mongodb.net/EngSof?retryWrites=true&w=majority"
    db = None

    def __init__(self):
        connect = pymongo.MongoClient(self.URI)
        self.db = connect.EngSof
        
    def insert(self, data):
        self.db.users.insert_one(data)
        return "User added successfully"
        
    def find(self, name):
        return self.db.users.find({"name": name})
        
    def update(self, data, name):
        self.db.users.replace_one({"name": name}, data)
        return "User updated successfully"
    
        
