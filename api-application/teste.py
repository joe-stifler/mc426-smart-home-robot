import requests

real_token = 'eyJ0eXAiOiJKV1QiLCJhbGciOiJIUzI1NiJ9.eyJ1c2VyIjoidGVzdGVAdGVzdGUuY29tLmJyIiwiZXhwIjoxNjA2MzY3NjM3fQ.EkZjG_Z-yUcZz0vMBhGcwViSWCyDT2hFYMeIewiNP28'

content = {
    "user" : "Teste",
    "email" : "teste@teste.com.br",
    "password" : "password123",
    "token" : real_token
}

url = 'http://127.0.0.1:5000/sensors/available-sensors'

response = requests.get(url, json = content)

print("Status code: ", response.status_code)
print("Printing Entire Request Response")
print(response.json())