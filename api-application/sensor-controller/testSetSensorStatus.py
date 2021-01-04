import unittest
from sensor_controller import SensorController

class TestSetSensor(unittest.TestCase):
            
    def setUp(self):
        self.controller = SensorController()        
            
    def test_set_sensor_1(self):  
    
        # air sensor esta disponivel e o status e do tipo float
       
        self.controller.air = 1
        self.assertEqual(self.controller.setSensorStatus("air", 18.8), 18.8) 
        
    def test_set_sensor_2(self): 
    
        # air sensor esta disponivel e retorna tipo float
     
        self.controller.air = 1
        self.assertEqual(type(self.controller.setSensorStatus("air", 18.8)), float)
     
    def test_set_sensor_3(self):
        
        # air sensor retorna somente tipo float
        
        self.controller.air = 1
        self.assertNotEqual(type(self.controller.setSensorStatus("air", 18.8)), int) 
        
    def test_set_sensor_4(self):
        
        # air sensor nao esta disponivel retorna 400
        
        self.controller.air = -1
        self.assertEqual(self.controller.setSensorStatus("air", 18.8), 400)   
        
    def test_set_sensor_5(self):
    
        # air sensor esta disponivel e somente aceita status do tipo float se nao retorna 400
        
        self.controller.air = 1
        self.assertEqual(self.controller.setSensorStatus("air", 18), 400)
        
    def test_set_sensor_6(self):  
    
        # energy sensor esta disponivel e o status e do tipo int
       
        self.controller.energy = 1
        self.assertEqual(self.controller.setSensorStatus("energy", 95), 95)  
        
    def test_set_sensor_7(self):  
    
        # energy sensor esta disponivel e retorna tipo int
       
        self.controller.energy = 1
        self.assertEqual(type(self.controller.setSensorStatus("energy", 95)), int)  
        
    def test_set_sensor_8(self):  
    
        # energy sensor retorna somente tipo int
       
        self.controller.energy = 1
        self.assertNotEqual(type(self.controller.setSensorStatus("energy", 95)), float) 
        
    def test_set_sensor_9(self):  
    
        # energy sensor esta disponivel e somente aceita status do tipo int se nao retorna 400
       
        self.controller.energy = 1
        self.assertEqual(self.controller.setSensorStatus("energy", 95.5), 400)    
        
    def test_set_sensor_10(self):  
    
        # lamp sensor esta disponivel e o status e do boolean
       
        self.controller.lamp = 1
        self.assertEqual(self.controller.setSensorStatus("lamp", True), True)  
        
    def test_set_sensor_11(self):  
    
        # lamp sensor esta disponivel e retorna tipo boolean
       
        self.controller.lamp = 1
        self.assertEqual(type(self.controller.setSensorStatus("lamp", True)), bool)   
        
    def test_set_sensor_12(self):  
    
        # lamp sensor retorna somente tipo boolean
       
        self.controller.lamp = 1
        self.assertNotEqual(type(self.controller.setSensorStatus("lamp", True)), int)    
        
    def test_set_sensor_13(self):  
    
        # lamp sensor esta disponivel e somente aceita status do tipo boolean se nao retorna 400
       
        self.controller.lamp = 1
        self.assertEqual(self.controller.setSensorStatus("lamp", 1), 400)       
                                
        
if __name__ == '__main__':
   unittest.main()

