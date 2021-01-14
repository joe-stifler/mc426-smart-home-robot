from sensor_controller import SensorController
from security_controler import SecurityController

class FacadeAPI(object):

    def __init__(self):
        self.sensor = SensorController()
        self.security = SecurityController()

    # security module

    def sign_in(self, email, password):
        return self.security.sign_in(email, password)

    def reset_pass(self, email):
        return self.security.reset_pass(email)

    def sign_up(self, name, email, password):
        return self.security.sign_up(name, email, password)

    def generate_token(self, email):
        return self.security.generate_token(email)

    def valid_token(self, token):
        return self.security.valid_token(token)

    # sensor module

    def getAvailableSensor(self, num_sensors):
        sensor_list = self.sensor.getAvailableSensor(num_sensors)

        return self.sensor.process_sensor_list(sensor_list)

    def setSensorStatus(self, name, status):
        if self.sensor.setSensorStatus(name, status):
            return self.getSensorStatus(name)    

        return None

    def getSensorStatus(self, name):
        sensor = self.sensor.getSensorStatus(name)

        if sensor == None:
            return None
            
        return str(sensor['status'])