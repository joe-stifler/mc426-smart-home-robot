from database import Database

class SensorController:
    def __init__(self):
        self.mydb = Database()

        # self.clear_sensors()

        self.add_sensor('luz1', '1')
        self.add_sensor('luz2', '0')
        self.add_sensor('energy', '100')
        self.add_sensor('air', '0')
        self.add_sensor('camera', '1')
        self.add_sensor('presence', '0')
        self.add_sensor('temperature', '24')

    def clear_sensors(self):
        self.mydb.drop_sensor_collection()

    def add_sensor(self, name, status, t='str'):
        if t == 'int':
            self.mydb.update_sensor({'name' : name, 'status': int(status)})
        elif t == 'bool':
            self.mydb.update_sensor({'name' : name, 'status': bool(status)})
        elif t == 'str':
            self.mydb.update_sensor({'name' : name, 'status': str(status)})
        elif t == 'float':
            self.mydb.update_sensor({'name' : name, 'status': float(status)})

    def getAvailableSensor(self, num_sensors):
        counter = 0
        list_sensors = []
        cursor = self.mydb.find_all_sensors()

        for document in cursor:
            if num_sensors >= 0 and counter >= num_sensors:
                break

            counter += 1

            list_sensors.append(document['name'])

        return list_sensors

    def process_sensor_list(self, sensor_list):
        counter = 0
        sensor_str = ""

        for s in sensor_list:
            if counter != 0:
                sensor_str = sensor_str + "&"
            
            counter += 1

            sensor_str = sensor_str + s

        return sensor_str
    
    def setSensorStatus(self, name, status, t='str'):
        sensor = self.getSensorStatus(name)

        if sensor and type(sensor['status']).__name__ == t:
            self.add_sensor(name, status, t=t)

            return True
        
        return False

    def getSensorStatus(self, name):
        cursor = self.mydb.find_sensor(name)

        for document in cursor:
            return document

        return None

    def getSensorHistory(self, name):
        history = []
        cursor = self.mydb.get_history(name)

        for document in cursor:
            history.append(document['date'])

        return history