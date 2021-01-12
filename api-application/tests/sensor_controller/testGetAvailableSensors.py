import sys
sys.path.insert(1, str().join(['/' + i for i in __file__.split('/')[1:-3]]))

import unittest
from sensor_controller import *

class TestGetAvailableSensors(unittest.TestCase):
            
    def setUp(self):
        self.controller = SensorController()                  
        
    def test_available_1(self):
    
        # 1 unico nome retorna o mesmo
        num_sensors = 1

        self.controller.add_sensor('air', '1')

        list_sensors = self.controller.getAvailableSensor(num_sensors)

        self.assertEqual(len(list_sensors), num_sensors)  
        
    def test_available_2(self):     
    
        # mais de 2 nomes retorna os nomes separados por "&"
    
        num_sensors = 2

        self.controller.add_sensor('air', '1')
        self.controller.add_sensor('air2', '1')
        self.controller.add_sensor('camera', '0')

        list_sensors = self.controller.getAvailableSensor(num_sensors)

        self.assertEqual(len(list_sensors), num_sensors)
        
    def test_available_3(self):  
    
        # lista vazia retorna ""

        num_sensors = 0

        list_sensors = self.controller.getAvailableSensor(num_sensors)

        self.assertEqual(len(list_sensors), 0)
        