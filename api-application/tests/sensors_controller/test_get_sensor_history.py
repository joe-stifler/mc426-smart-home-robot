import sys
sys.path.insert(1, str().join(['/' + i for i in __file__.split('/')[1:-3]]))

import unittest
from sensor_controller import *


class TestGetSensorHistory(unittest.TestCase):
    def setUp(self):
        self.controller = SensorController()

    def test_1(self):
        # sensor nao existe na base de dados
        # historico deve ser 0

        history = self.controller.getSensorHistory('nao_existe')

        self.assertEqual(len(history), 0)

    def test_2(self):
        # sensor existe na base de dados
        # mas possui somente um historico

        self.controller.add_sensor('nao_existe2', 1, t='bool')

        history = self.controller.getSensorHistory('nao_existe2')

        self.assertEqual(len(history), 1)

    # def test_3(self):
    #     # sensor existe na base de dados
    #     # possui masi de um historico na base

    #     self.controller.add_sensor('nao_existe3', 1, t='bool')

    #     self.controller.setSensorStatus('nao_existe3', 0, t='bool')

    #     self.controller.setSensorStatus('nao_existe3', 1, t='bool')

    #     history = self.controller.getSensorHistory('nao_existe3')

    #     self.assertEqual(len(history), 3)

    def test_4(self):
        # sensor existe na base de dados
        # mas possui somente um historico

        self.controller.add_sensor('nao_existe4', 1, t='bool')

        self.controller.setSensorStatus('nao_existe4', 1, t='bool')

        history = self.controller.getSensorHistory('nao_existe4')

        self.assertEqual(len(history), 1)