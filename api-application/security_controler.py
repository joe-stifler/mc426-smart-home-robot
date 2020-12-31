
class SecurityController(object):
    MIN_NAME_SIZE = 1
    MAX_NAME_SIZE = 20

    MIN_PASSWORD_SIZE = 8
    MAX_PASSWORD_SIZE = 15

    def sign_in(self): pass

    def sign_up(self, name, email, password):
        if not any(c.isalpha() for c in password): return False
        if not any(c.isdigit() for c in password): return False

        if len(name) < SecurityController.MIN_NAME_SIZE: return False
        if len(name) > SecurityController.MAX_NAME_SIZE: return False

        if len(password) < SecurityController.MIN_PASSWORD_SIZE: return False
        if len(password) > SecurityController.MAX_PASSWORD_SIZE: return False

        return True