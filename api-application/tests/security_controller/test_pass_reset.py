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

        email = "joe@gmail.com"

        self.assertTrue(self.controller.reset_pass(email))

    def test_reset_2(self):
        #####################
        # usuario existe: nao
        #####################
        # resultado: invalido

        email = "joe@gmail"

        self.assertFalse(self.controller.reset_pass(email))

if __name__ == '__main__':
    unittest.main()