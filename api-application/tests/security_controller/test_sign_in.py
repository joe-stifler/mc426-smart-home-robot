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

        name = "joe"
        email = "joe@gmail.com"
        password = "abc123abc"
        
        # guarantee that the user exists
        self.controller.sign_up(name, email, password)

        self.assertTrue(self.controller.sign_in(email, password))

    def test_sign_in_2(self):
        #####################
        # Usuário Existe: Sim
        # Senha Correta: Não
        #####################
        # resultado: invalido

        name = "joe"
        email = "joe@gmail.com"
        password = "abc123cab"

        # guarantee that the user exists
        self.controller.sign_up(name, email, password)

        self.assertFalse(self.controller.sign_in(email, password))
       
    def test_sign_in_3(self):
        #####################
        # Usuário Existe: Não
        # Senha Correta: -
        #####################
        # resultado: invalido

        email = "joe@gmail"
        password = "abc123abc"

        # guarantee that the user does not exists
        self.controller.remove_user(email)

        self.assertFalse(self.controller.sign_in(email, password))
         