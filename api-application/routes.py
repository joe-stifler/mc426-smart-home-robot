import jwt
import datetime
from functools import wraps
from flask import  Flask, request

app = Flask("Teste")

app.config['SECRET_KEY'] = "hunter_x_hunter_2020"


def token_required(f):
    @wraps(f)
    def decorated(*args, **kwargs):
        body = request.get_json()
        token = body.get('token')

        if not token:
            return generateResponse(403, "Token is missing!")

        try:
            data = jwt.decode(token, app.config['SECRET_KEY'])
        except:
            return generateResponse(403, "Token is invalid!")

        return f(*args, **kwargs)

    return decorated


@app.route("/auth/logout", methods=["GET"])
@token_required
def authLogout():
    return generateResponse(401, "Could not verify user authentication!", auth)


@app.route("/auth/login", methods=["GET"])
def userSignIn():
    body = request.get_json()

    if body['password'] == "password123":
        token = jwt.encode({'user' : body['email'], 'exp' : datetime.datetime.utcnow() + datetime.timedelta(minutes=30)}, app.config['SECRET_KEY'])
    
        return generateResponse(200, "User authenticated!", token)
    else:
        return generateResponse(401, "Could not verify user authentication!")


@app.route("/auth/register", methods=["POST"])
def userSignUp():
    body = request.get_json()

    if ("name" not in body):
        return generateResponse(400, "The `name` field is mandatory")

    if ("email" not in body):
        return generateResponse(400, "The `email` field is mandatory")

    if ("password" not in body):
        return generateResponse(400, "The `password` field is mandatory")

    return  generateResponse(200, "User created successfully!")


@app.route("/auth/reset", methods=["PUT"])
def userPasswordReset():
    body = request.get_json()

    if ("email" not in body):
        return generateResponse(400, "The `email` field is mandatory")

    return  generateResponse(200, "An e-mail was sent to the user!")


@app.route("/sensors/available-sensors", methods=["GET"])
@token_required
def sensorAvailable():
    body = request.get_json()

    return  generateResponse(200, "Returning all sensors!")


@app.route("/sensors/sensor-status", methods=["GET"])
@token_required
def sensorGetStatus():
    body = request.get_json()

    if ("token" not in body):
        return generateResponse(400, "The `token` field is mandatory")

    return  generateResponse(200, "Returning sensor status!")


@app.route("/sensors/set-sensor-status", methods=["PUT"])
@token_required
def sensorSetStatus():
    body = request.get_json()

    if ("token" not in body):
        return generateResponse(400, "The `token` field is mandatory")

    return  generateResponse(200, "Returning sensor status!")


def generateResponse(status, message, content = False):
    response = {}
    response["status"] = status
    response["message"] = message

    response["content"] = {}

    if (content): response["content"] = content

    return response


app.run()