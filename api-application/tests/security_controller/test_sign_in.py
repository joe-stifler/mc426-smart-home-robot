import sys
sys.path.insert(1, str().join(['/' + i for i in __file__.split('/')[1:-3]]))

import unittest
from security_controler import SecurityController

class SignInTestCase(unittest.TestCase):
    def setUp(self):
        self.controller = SecurityController()

    def test_sign_in_1(self):
        #####################
        # Usuário Existe: Sim
        # Senha Correta: Sim
        #####################
        # resultado: valido

        email = "joe@gmail.com"
        password = "abc123abc"

        self.assertTrue(self.controller.sign_in(email, password))

    def test_sign_in_2(self):
        #####################
        # Usuário Existe: Sim
        # Senha Correta: Não
        #####################
        # resultado: invalido

        email = "joe@gmail.com"
        password = "abc123cab"

        self.assertFalse(self.controller.sign_in(email, password))
       
    def test_sign_in_3(self):
        #####################
        # Usuário Existe: Não
        # Senha Correta: -
        #####################
        # resultado: invalido

        email = "joe@gmail"
        password = "abc123abc"

        self.assertFalse(self.controller.sign_in(email, password))
         

if __name__ == '__main__':
    unittest.main()