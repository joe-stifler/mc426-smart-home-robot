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

        name = "joe"
        email = "joe@gmail.com"
        password = "abc123abc"

        self.controller.remove_user(email)
        self.controller.sign_up(name, email, password)

        token = self.controller.generate_token(email)

        self.assertTrue(self.controller.valid_token(token))

    def test_token_2(self):
        #####################
        # token recebido: sim
        # token valido: sim
        # token expirou: sim
        #####################
        # usuario autenticado: nao

        token = "eyJ0eXAiOiJKV1QiLCJhbGciOiJIUzI1NiJ9.eyJ1c2VyIjoidGVzdGVAdGVzdGUuY29tLmJyIiwiZXhwIjoxNjA2NjAwOTgyfQ.EVpPpzji2Lp6CIo6INlxZi1u0V4feQ-VXBW8muI72c4"

        self.assertFalse(self.controller.valid_token(token))

    def test_token_3(self):
        #####################
        # token recebido: sim
        # token valido: nao
        #####################
        # usuario autenticado: nao

        token = "123abacate"

        self.assertFalse(self.controller.valid_token(token))
    
    def test_token_4(self):
        #####################
        # token recebido: nao
        #####################
        # usuario autenticado: nao

        token = None

        self.assertFalse(self.controller.valid_token(token))