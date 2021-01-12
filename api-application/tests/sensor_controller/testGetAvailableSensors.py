import sys
sys.path.insert(1, str().join(['/' + i for i in __file__.split('/')[1:-3]]))

import unittest
from sensor_controller import *

class TestGetAvailableSensors(unittest.TestCase):
            
    def setUp(self):
        self.controller = SensorController()                  
        
    def test_available_1(self):
    
        # 1 unico nome retorna o mesmo
    
        listName = ["air"]
        self.assertEqual(self.controller.getAvailableSensor(listName), "air")  
        
    def test_available_2(self):     
    
        # mais de 2 nomes retorna os nomes separados por "&"
    
        listName = ["air", "camera"]
        self.assertEqual(self.controller.getAvailableSensor(listName), "air&camera")      
        
    def test_available_3(self):  
    
        # lista vazia retorna ""
      
        listName = [""]
        self.assertEqual(self.controller.getAvailableSensor(listName), "")
        
    def test_available_4(self):  
    
        # o caractere separando os nomes deve ser "&"
         
        listName = ["air", "camera"]
        self.assertNotEqual(self.controller.getAvailableSensor(listName), "air,camera")  
        
    def test_available_5(self):  
    
        # a lista vazia retorna uma string vazia
      
        listName = [""]
        self.assertNotEqual(self.controller.getAvailableSensor(listName), None)    
            
        
if __name__ == '__main__':
    unittest.main()

