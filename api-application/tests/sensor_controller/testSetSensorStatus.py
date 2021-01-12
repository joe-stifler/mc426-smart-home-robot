import sys
sys.path.insert(1, str().join(['/' + i for i in __file__.split('/')[1:-3]]))

import unittest
from sensor_controller import *


class TestSetSensor(unittest.TestCase):
            
    def setUp(self):
        self.controller = SensorController()        
            
    def test_set_sensor_1(self):  
    
        # air sensor esta disponivel e o status e do tipo float
       
        self.controller.add_sensor('air', 0, t='float')

        self.controller.setSensorStatus('air', 18.8, t='float')

        self.assertEqual(self.controller.getSensorStatus('air')['status'], 18.8) 
        
    def test_set_sensor_2(self): 
    
        # air sensor esta disponivel e retorna tipo float
     
        self.controller.add_sensor('air', 0, t='float')

        self.controller.setSensorStatus('air', 18.8, t='float')

        self.assertEqual(type(self.controller.getSensorStatus("air")['status']), float)
     
    def test_set_sensor_3(self):
        
        # air sensor retorna somente tipo float
        
        self.controller.add_sensor('air', 0, t='float')

        self.controller.setSensorStatus('air', 18.8, t='float')

        self.assertNotEqual(type(self.controller.getSensorStatus("air")), int) 
        
    def test_set_sensor_4(self):
        
        # air3dd sensor nao esta disponivel retorna 400
        
        self.assertFalse(self.controller.setSensorStatus("air3dd", 18.8, t='float'))   
        
    def test_set_sensor_5(self):
    
        # air sensor esta disponivel e somente aceita status do tipo float se nao retorna 400

        self.controller.add_sensor('air', 0, t='float')

        self.assertFalse(self.controller.setSensorStatus('air', 18, t='int')) 
