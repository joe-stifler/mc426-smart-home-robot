import sys
sys.path.insert(1, str().join(['/' + i for i in __file__.split('/')[1:-3]]))

import unittest
from security_controler import *

class SignUpTestCase(unittest.TestCase):
    def setUp(self):
        self.controller = SecurityController()

    def test_sign_up_1(self):
        #####################
        # password contem letras: sim
        # password contem digitos: sim
        # numero de caracters no nome: 1 <= t <= 20
        # numero de caracters no password: 8 <= t <= 15
        # usuario ja existe: nao
        #####################
        # resultado: valido

        name = "joe"
        email = "joe@gmail.com"
        password = "abc123abc"

        self.controller.remove_user(email)

        self.assertTrue(self.controller.sign_up(name, email, password))

    def test_sign_up_2(self):
        #####################
        # password contem letras: nao (culpado da invalidez)
        # password contem digitos: sim
        # numero de caracters no nome: 1 <= t <= 20
        # numero de caracters no password: 8 <= t <= 15
        # usuario ja existe: nao
        #####################
        # resultado: invalido

        name = "joe"
        email = "joe@gmail.com"
        password = "123123123"

        self.assertFalse(self.controller.sign_up(name, email, password))

    def test_sign_up_3(self):
        #####################
        # password contem letras: sim
        # password contem digitos: nao (culpado da invalidez)
        # numero de caracters no nome: 1 <= t <= 20
        # numero de caracters no password: 8 <= t <= 15
        # usuario ja existe: nao
        #####################
        # resultado: invalido

        name = "joe"
        email = "joe@gmail.com"
        password = "abcabcabc"

        self.assertFalse(self.controller.sign_up(name, email, password))

    def test_sign_up_4(self):
        #####################
        # password contem letras: sim
        # password contem digitos: sim
        # numero de caracters no nome: t = 0 (culpado da invalidez)
        # numero de caracters no password: 8 <= t <= 15
        # usuario ja existe: nao
        #####################
        # resultado: invalido
        
        name = ""
        email = "joe@gmail.com"
        password = "abc123abc"

        self.assertFalse(self.controller.sign_up(name, email, password))

    def test_sign_up_5(self):
        #####################
        # password contem letras: sim
        # password contem digitos: sim
        # numero de caracters no nome: t = 21 (culpado da invalidez)
        # numero de caracters no password: 8 <= t <= 15
        # usuario ja existe: nao
        #####################
        # resultado: invalido
        
        name = "joejoejoejoejoejoejoe"
        email = "joe@gmail.com"
        password = "abc123abc"

        self.assertFalse(self.controller.sign_up(name, email, password))

    def test_sign_up_6(self):
        #####################
        # password contem letras: sim
        # password contem digitos: sim
        # numero de caracters no nome: 1 <= t <= 20
        # numero de caracters no password: t < 8 (culpado da invalidez)
        # usuario ja existe: nao
        #####################
        # resultado: invalido

        name = "joe"
        email = "joe@gmail.com"
        password = "abc123a"

        self.assertFalse(self.controller.sign_up(name, email, password))

    def test_sign_up_7(self):
        #####################
        # password contem letras: sim
        # password contem digitos: sim
        # numero de caracters no nome: 1 <= t <= 20
        # numero de caracters no password: t > 15 (culpado da invalidez)
        # usuario ja existe: nao
        #####################
        # resultado: invalido

        name = "joe"
        email = "joe@gmail.com"
        password = "abc123abc123abc1"

        self.assertFalse(self.controller.sign_up(name, email, password))

    def test_sign_up_8(self):
        #####################
        # password contem letras: sim
        # password contem digitos: sim
        # numero de caracters no nome: 1 <= t <= 20
        # numero de caracters no password: 8 <= t <= 15
        # usuario ja existe: sim (culpado da invalidez)
        #####################
        # resultado: invalido

        name = "joe"
        email = "joe@gmail.com"
        password = "abc123abc"

        # insert user once
        self.controller.sign_up(name, email, password)

        # try to insert user again
        self.assertFalse(self.controller.sign_up(name, email, password))