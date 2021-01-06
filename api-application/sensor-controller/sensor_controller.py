class SensorController:
  
    def __init__(self):
       self.lamp = -1
       self.energy = -1
       self.air = -1
       self.camera = -1
       self.presence = -1
       self.temperature = -1     
       return None
  
    def getAvailableSensor(self, listSensors):
       if listSensors == "":
          return ""
      
       if len(listSensors) == 1:
          if listSensors[0] == "lamp":
             self.lamp = 1
          if listSensors[0] == "energy":
             self.energy = 1
          if listSensors[0] == "air":
             self.air = 1
          if listSensors[0] == "camera":
             self.camera = 1
          if listSensors[0] == "presence":
             self.presence = 1 
          if listSensors[0] == "temperature":
             self.temperature = 1              
          return listSensors[0]   
        
       if len(listSensors) > 1:
          sensors = ""
          for x in listSensors: 
             sensors = sensors + x + "&" 
             if x == "lamp":
                self.lamp = 1
             if x == "energy":
                self.energy = 1
             if x == "air":
                self.air = 1
             if x == "camera":
                self.camera = 1
             if x == "presence":
                self.presence = 1 
             if x == "temperature":
                self.temperature = 1 
          sensors = sensors[:-1]
       return sensors
    
    def setSensorStatus(self, name, status):
       if name == "lamp":
          if self.lamp != -1:
             if type(status) == bool:
                self.lamp = status
                return status
             else:
                return 400    
          else:
             return 400   
       if name == "energy":
          if self.energy != -1:
             if type(status) == int:
                self.energy = status
                return status
             else:
                return 400   
          else:
             return 400 
       if name == "air":
          if self.air != -1:
             if type(status) == float:
                self.air = status
                return status
             else:
                return 400   
          else:
             return 400 
       if name == "camera":
          if self.camera != -1:
             if type(status) == bool:
                self.camera = status
                return status
             else:
                return 400   
          else:
             return 400 
       if name == "presence":
          if self.presence != -1:
             if type(status) == bool:
                self.presence = status
                return status
             else:
                return 400   
          else:
             return 400 
       if name == "temperature":
          if self.temperature != -1:
             if type(status) == float:
                self.temperature = status
                return status
             else:
                return 400   
          else:
             return 400       
       return status  
      
    def getSensorStatus(self, name):
       if name == "lamp":
          if self.lamp != -1:
             if type(self.lamp) == bool:
                return self.lamp
             else:
                return 400   
          else:
             return 400   
       if name == "energy":
          if self.energy != -1:
             if type(self.energy) == int:
                return self.energy
             else:
                return 400   
          else:
             return 400 
       if name == "air":
          if self.air != -1:
             if type(self.air) == float:
                return self.air
             else:
                return 400   
          else:
             return 400 
       if name == "camera":
          if self.camera != -1:
             if type(self.camera) == bool:
                return self.camera
             else:
                return 400   
          else:
             return 400 
       if name == "presence":
          if self.presence != -1:
             if type(self.lamp) == bool:
                return self.presence
             else:
                return 400   
          else:
             return 400 
       if name == "temperature":
          if self.temperature != -1:
             if type(self.lamp) == float:
                return self.temperature
             else:
                return 400   
          else:
             return 400
     

