import sys
sys.path.insert(1, str().join(['/' + i for i in __file__.split('/')[1:-3]]))

import unittest
from security_controler import SecurityController

class PassResetTestCase(unittest.TestCase):
    def setUp(self):
        self.controller = SecurityController()

    def test_reset_1(self):
        #####################
        # usuario existe: sim
        #####################
        # resultado: valido

        name = "joe"
        email = "joe@gmail.com"
        password = "abc123abc"

        # guarantee that the user exists
        self.controller.sign_up(name, email, password)

        self.assertTrue(self.controller.reset_pass(email))

    def test_reset_2(self):
        #####################
        # usuario existe: nao
        #####################
        # resultado: invalido

        email = "joe@gmail"

        # guarantee that the user does not exists
        self.controller.remove_user(email)

        self.assertFalse(self.controller.reset_pass(email))