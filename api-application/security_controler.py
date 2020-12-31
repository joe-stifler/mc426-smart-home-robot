
class SecurityController(object):
    MAX_PASSWORD_SIZE = 15

    def sign_in(self): pass

    def sign_up(self, name, email, password):

        if len(password) > SecurityController.MAX_PASSWORD_SIZE: return False

        return True