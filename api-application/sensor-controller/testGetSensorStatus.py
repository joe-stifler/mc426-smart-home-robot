import unittest
from sensor_controller import SensorController

class TestGetetSensor(unittest.TestCase):

    def setUp(self):
        self.controller = SensorController()
        
    def test_get_sensor_1(self):  
    
        # air sensor esta disponivel e retorna seu status
       
        self.controller.air = 18.8
        self.assertEqual(self.controller.getSensorStatus("air"), 18.8)   
        
    def test_get_sensor_2(self):  
    
        # air sensor esta disponivel e retorna seu status do tipo float
       
        self.controller.air = 18.8
        self.assertEqual(type(self.controller.getSensorStatus("air")), float)  
        
    def test_get_sensor_3(self):  
    
        # air sensor esta disponivel mas seu status nao e do tipo float retorna 400
       
        self.controller.air = 18
        self.assertEqual(self.controller.getSensorStatus("air"), 400)    
        
    def test_get_sensor_4(self):  
    
        # air sensor nao esta disponivel e retorna 400
       
        self.controller.air = -1
        self.assertEqual(self.controller.getSensorStatus("air"), 400)    
       
    def test_get_sensor_5(self):  
    
        # energy sensor esta disponivel e retorna seu status
       
        self.controller.energy = 95
        self.assertEqual(self.controller.getSensorStatus("energy"), 95)   
        
    def test_get_sensor_6(self):  
    
        # energy sensor esta disponivel e retorna seu status do tipo int
       
        self.controller.energy = 95
        self.assertEqual(type(self.controller.getSensorStatus("energy")), int)  
        
    def test_get_sensor_7(self):  
    
        # energy sensor esta disponivel mas seu status nao e do tipo int retorna 400
       
        self.controller.energy = 95.5
        self.assertEqual(self.controller.getSensorStatus("energy"), 400)  
        
    def test_get_sensor_8(self):  
    
        # lamp sensor esta disponivel e retorna seu status
       
        self.controller.lamp = True
        self.assertEqual(self.controller.getSensorStatus("lamp"), True)
        
    def test_get_sensor_9(self):  
    
        # lamp sensor esta disponivel e retorna seu status do tipo boolean
       
        self.controller.lamp = True
        self.assertEqual(type(self.controller.getSensorStatus("lamp")), bool)    
        
    def test_get_sensor_10(self):  
    
        # lamp sensor esta disponivel mas seu status nao e do tipo boolean retorna 400
       
        self.controller.lamp = 1
        self.assertEqual(self.controller.getSensorStatus("lamp"), 400)    
        
if __name__ == '__main__':
   unittest.main()        
        
                   
