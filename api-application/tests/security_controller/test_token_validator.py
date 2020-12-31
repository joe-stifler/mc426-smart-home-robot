import sys
sys.path.insert(1, str().join(['/' + i for i in __file__.split('/')[1:-3]]))

import unittest
from security_controler import SecurityController

class TokenValidatorTestCase(unittest.TestCase):
    def setUp(self):
        self.controller = SecurityController()

    def test_token_1(self):
        #####################
        # token recebido: sim
        # token valido: sim
        # token expirou: nao
        #####################
        # usuario autenticado: sim

        token = ""

        self.assertTrue(self.controller.valid_token(token))

    def test_token_2(self):
        #####################
        # token recebido: sim
        # token valido: sim
        # token expirou: sim
        #####################
        # usuario autenticado: nao

        token = ""

        self.assertFalse(self.controller.valid_token(token))

    def test_token_3(self):
        #####################
        # token recebido: sim
        # token valido: nao
        #####################
        # usuario autenticado: nao

        token = ""

        self.assertFalse(self.controller.valid_token(token))
    
    def test_token_4(self):
        #####################
        # token recebido: nao
        #####################
        # usuario autenticado: nao

        token = ""

        self.assertFalse(self.controller.valid_token(token))

if __name__ == '__main__':
    unittest.main()