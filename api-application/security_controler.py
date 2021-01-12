import jwt
import datetime
from database import Database

class SecurityController(object):
    MIN_NAME_SIZE = 1
    MAX_NAME_SIZE = 20

    MIN_PASSWORD_SIZE = 8
    MAX_PASSWORD_SIZE = 15

    ALGORITHMS = ["HS256"]
    SECRET_KEY = "hunter_x_hunter_2020"

    def __init__(self):
        self.mydb = Database()

    def sign_in(self, email, password):
        user = None

        # Verifies if a user with the same email already exists
        cursor = self.mydb.find(email)

        for document in cursor:
            user = document

            break

        if user and user['password'] == password: return True

        return False

    def reset_pass(self, email):
        # Verifies if a user with the same email already exists
        cursor = self.mydb.find(email)

        for document in cursor:
            # Here we send a reset email password to the client

            return True

        return False

    def remove_user(self, email):
        self.mydb.update({}, email)

    def sign_up(self, name, email, password):
        if not any(c.isalpha() for c in password): return False
        if not any(c.isdigit() for c in password): return False

        if len(name) < SecurityController.MIN_NAME_SIZE: return False
        if len(name) > SecurityController.MAX_NAME_SIZE: return False

        if len(password) < SecurityController.MIN_PASSWORD_SIZE: return False
        if len(password) > SecurityController.MAX_PASSWORD_SIZE: return False

        # Verifies if a user with the same email already exists
        cursor = self.mydb.find(email)

        for document in cursor: return False

        data = {"name": name, "email": email, "password": password} 

        self.mydb.insert(data)

        return True

    def generate_token(self, email):
        return jwt.encode({'user' : email, 'exp' : datetime.datetime.utcnow() + datetime.timedelta(minutes=180)}, SecurityController.SECRET_KEY)

    def valid_token(self, token):
        try:
            data = jwt.decode(token, SecurityController.SECRET_KEY, algorithms=ALGORITHMS)

            return True
        except:
            # "Token is invalid!"
            return False
