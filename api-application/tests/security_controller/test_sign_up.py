import unittest
from security_controler import SecurityController

class SignUpTestCase(unittest.TestCase):
    def setUp(self):
        self.controller = SecurityController()

    def test_sign_up_1(self):
        #####################
        # password contem letras: sim
        # password contem digitos: sim
        # numero de caracters no nome: 1 <= t <= 20
        # numero de caracters no password: 8 <= t <= 15
        #####################
        # resultado: valido

        name = "joe"
        email = "joe@gmail.com"
        password = "abc123abc"

        self.assertTrue(self.controller.sign_up(name, email, password))

    def test_sign_up_2(self):
        #####################
        # password contem letras: nao
        # password contem digitos: sim
        # numero de caracters no nome: 1 <= t <= 20
        # numero de caracters no password: 8 <= t <= 15
        #####################
        # resultado: invalido

        name = "joe"
        email = "joe@gmail.com"
        password = "123123123"

        self.assertFalse(self.controller.sign_up(name, email, password))

    def test_sign_up_3(self):
        #####################
        # password contem letras: sim
        # password contem digitos: nao
        # numero de caracters no nome: 1 <= t <= 20
        # numero de caracters no password: 8 <= t <= 15
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
        # numero de caracters no nome: t = 0
        # numero de caracters no password: 8 <= t <= 15
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
        # numero de caracters no nome: t = 21
        # numero de caracters no password: 8 <= t <= 15
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
        # numero de caracters no password: t < 8
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
        # numero de caracters no password: t > 15
        #####################
        # resultado: invalido

        name = "joe"
        email = "joe@gmail.com"
        password = "abc123abc123abc1"

        self.assertFalse(self.controller.sign_up(name, email, password))

if __name__ == '__main__':
    unittest.main()