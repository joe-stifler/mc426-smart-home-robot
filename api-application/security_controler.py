
class SecurityController(object):
    MIN_PASSWORD_SIZE = 8
    MAX_PASSWORD_SIZE = 15

    def sign_in(self): pass

    def sign_up(self, name, email, password):
        if len(password) < SecurityController.MIN_PASSWORD_SIZE: return False
        if len(password) > SecurityController.MAX_PASSWORD_SIZE: return False

        return True