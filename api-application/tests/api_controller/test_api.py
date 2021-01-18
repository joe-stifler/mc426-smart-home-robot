import requests
import unittest

class TestFlaskAPI(unittest.TestCase):
    def setUp(self):
        pass

    def test_sign_up(self):
        content = {
            "name" : "Teste",
            "email" : "teste@teste.com.br",
            "password" : "password123"
        }

        url = 'http://127.0.0.1:5000/auth/register'

        response = requests.post(url, json = content)

        response = requests.post(url, json = content)

        # print(response.json())

        self.assertEqual(int(response.json()['status']), 401)


    def test_sign_in_valid(self):
        # real_token = 'eyJ0eXAiOiJKV1QiLCJhbGciOiJIUzI1NiJ9.eyJ1c2VyIjoidGVzdGVAdGVzdGUuY29tLmJyIiwiZXhwIjoxNjA2NjAwOTgyfQ.EVpPpzji2Lp6CIo6INlxZi1u0V4feQ-VXBW8muI72c4'

        content = {
            "name" : "Teste",
            "email" : "teste@teste.com.br",
            "password" : "password123",
            # "token" : real_token
        }

        url = 'http://127.0.0.1:5000/auth/register'

        response = requests.post(url, json = content)

        url = 'http://127.0.0.1:5000/auth/login'

        response = requests.get(url, json = content)

        self.assertEqual(int(response.json()['status']), 200)


    def test_sign_in_invalid(self):
        url = 'http://127.0.0.1:5000/auth/login'

        content = {
            "name" : "Teste",
            "email" : "teste@teste.com.br",
            "password" : "password",
            # "token" : real_token
        }

        url = 'http://127.0.0.1:5000/auth/login'

        response = requests.get(url, json = content)

        self.assertEqual(int(response.json()['status']), 401)


    def test_available_sensors(self):
        content = {
            "name" : "Teste",
            "email" : "teste@teste.com.br",
            "password" : "password123",
            # "token" : real_token
        }

        url = 'http://127.0.0.1:5000/auth/register'

        response = requests.post(url, json = content)

        url = 'http://127.0.0.1:5000/auth/login'

        response = requests.get(url, json = content)

        content = {
            "token" : response.json()['content']
        }

        url = 'http://127.0.0.1:5000/sensors/available-sensors'

        response = requests.get(url, json = content)

        self.assertEqual(int(response.json()['status']), 200)


    def test_get_sensor_status(self):
        content = {
            "name" : "Teste",
            "email" : "teste@teste.com.br",
            "password" : "password123",
            # "token" : real_token
        }

        url = 'http://127.0.0.1:5000/auth/register'

        response = requests.post(url, json = content)

        url = 'http://127.0.0.1:5000/auth/login'

        response = requests.get(url, json = content)

        content = {
            "name" : "air", 
            "token" : response.json()['content']
        }

        url = 'http://127.0.0.1:5000/sensors/get-sensor-status'

        response = requests.get(url, json = content)

        self.assertEqual(int(response.json()['status']), 200)


    def test_set_sensor_status(self):
        content = {
            "name" : "Teste",
            "email" : "teste@teste.com.br",
            "password" : "password123",
            # "token" : real_token
        }

        url = 'http://127.0.0.1:5000/auth/register'

        response = requests.post(url, json = content)

        url = 'http://127.0.0.1:5000/auth/login'

        response = requests.get(url, json = content)

        content = {
            "name" : "air", 
            "status": "123",
            "token" : response.json()['content']
        }

        url = 'http://127.0.0.1:5000/sensors/set-sensor-status'

        response = requests.put(url, json = content)

        self.assertEqual(int(response.json()['status']), 200)
        

    def test_get_sensor_history(self):
        content = {
            "name" : "Teste",
            "email" : "teste@teste.com.br",
            "password" : "password123",
            # "token" : real_token
        }

        url = 'http://127.0.0.1:5000/auth/register'

        response = requests.post(url, json = content)

        url = 'http://127.0.0.1:5000/auth/login'

        response = requests.get(url, json = content)

        content = {
            "name" : "luz1",
            "token" : response.json()['content']
        }

        url = 'http://127.0.0.1:5000/sensors/get-sensor-history'

        response = requests.get(url, json = content)

        print(response.json()['content'])

        self.assertEqual(int(response.json()['status']), 200)