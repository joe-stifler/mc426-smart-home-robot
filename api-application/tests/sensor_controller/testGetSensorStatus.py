import sys
sys.path.insert(1, str().join(['/' + i for i in __file__.split('/')[1:-3]]))

import unittest
from sensor_controller import *

class TestGetetSensor(unittest.TestCase):

    def setUp(self):
        self.controller = SensorController()
        
    def test_get_sensor_1(self):  
    
        # air sensor esta disponivel e retorna seu status
       
        self.controller.add_sensor('air', 18.8, t='float')

        self.assertEqual(self.controller.getSensorStatus("air")['status'], 18.8)
        
    def test_get_sensor_2(self):  
    
        # air sensor esta disponivel e retorna seu status do tipo float
       
        self.controller.add_sensor('air', 18.8, t='float')

        self.assertEqual(type(self.controller.getSensorStatus("air")['status']), float)
        
    def test_get_sensor_3(self):  
    
        # air sensor esta disponivel mas seu status nao e do tipo float retorna 400
       
        self.controller.add_sensor('air', 18.8, t='float')

        self.assertNotEqual(type(self.controller.getSensorStatus("air")['status']), int)
        
    def test_get_sensor_4(self):  
    
        # air sensor nao esta disponivel e retorna 400
       
        self.assertEqual(self.controller.getSensorStatus("air3ddd"), None)    
                   
