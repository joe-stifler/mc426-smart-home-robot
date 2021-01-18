import datetime
from functools import wraps
from facade_api import FacadeAPI
from flask import  Flask, request

facade = FacadeAPI()
app = Flask("RESTAPISmartHouse")

def getBody():
    body = request.get_json()

    if not body:
        body = dict(request.form)

    return body



def generateResponse(status, message, content = False):
    response = {}
    response["status"] = str(status)
    response["message"] = str(message)

    if (content):
        response["content"] = str(content)

    return response


def token_required(f):
    @wraps(f)
    def decorated(*args, **kwargs):
        body = getBody()

        if not body:
            return generateResponse(403, "Body is missing!")

        if 'token' not in body:
            return generateResponse(403, "Token is missing!")

        if facade.valid_token(body.get('token')) == False:
            return generateResponse(401, "Token is invalid!")

        return f(*args, **kwargs)

    return decorated


@app.route("/auth/logout", methods=["GET"])
@token_required
def authLogout():
    return generateResponse(200, "Successfully logout!")


@app.route("/auth/login", methods=["GET"])
def userSignIn():
    body = getBody()

    if not body:
        return generateResponse(403, "Body is missing!")

    if ("email" not in body):
        return generateResponse(403, "The `email` field is mandatory")

    if ("password" not in body):
        return generateResponse(403, "The `password` field is mandatory")

    if facade.sign_in(body['email'], body['password']):
        token = facade.generate_token(body['email'])
        
        return generateResponse(200, "User authenticated!", token.decode("utf-8"))
    else:
        return generateResponse(401, "Could not verify user authentication!")


@app.route("/auth/register", methods=["POST"])
def userSignUp():
    body = getBody()

    if not body:
        return generateResponse(403, "Body is missing!")

    if ("name" not in body):
        return generateResponse(403, "The `name` field is mandatory")

    if ("email" not in body):
        return generateResponse(403, "The `email` field is mandatory")

    if ("password" not in body):
        return generateResponse(403, "The `password` field is mandatory")

    if facade.sign_up(body['name'], body['email'], body['password']):
        return  generateResponse(200, "User created successfully!")
    else:
        return  generateResponse(401, "Could not create user. Already exists!")


@app.route("/auth/reset", methods=["PUT"])
def userPasswordReset():
    body = getBody()

    if not body:
        return generateResponse(403, "Body is missing!")

    if ("email" not in body):
        return generateResponse(403, "The `email` field is mandatory")

    if facade.reset_pass(body['email']):
        return  generateResponse(200, "An e-mail was sent to the user!")
    else:
        return  generateResponse(400, "Could not reset password. Email not found!")


@app.route("/sensors/available-sensors", methods=["GET"])
@token_required
def sensorAvailable():
    body = getBody()

    if not body:
        return generateResponse(403, "Body is missing!")

    sensors = facade.getAvailableSensor(-1)

    return  generateResponse(200, "Returning all sensors!", sensors)


@app.route("/sensors/get-sensor-status", methods=["GET"])
@token_required
def sensorGetStatus():
    body = getBody()

    if not body:
        return generateResponse(403, "Body is missing!")

    if ("name" not in body):
        return generateResponse(403, "The `name` field is mandatory")

    status = facade.getSensorStatus(body['name'])

    if status == None:
        return  generateResponse(404, "Invalid sensor name. Sensor not found!")

    return  generateResponse(200, "Returning sensor status!", status)


@app.route("/sensors/get-sensor-history", methods=["GET"])
@token_required
def sensorGetHistory():
    body = getBody()

    if not body:
        return generateResponse(403, "Body is missing!")

    if ("name" not in body):
        return generateResponse(403, "The `name` field is mandatory")

    history = facade.getSensorHistory(body['name'])

    return  generateResponse(200, "Returning sensor history!", history)


@app.route("/sensors/set-sensor-status", methods=["PUT"])
@token_required
def sensorSetStatus():
    body = getBody()

    if not body:
        return generateResponse(403, "Body is missing!")

    if ("name" not in body):
        return generateResponse(403, "The `name` field is mandatory")

    if ("status" not in body):
        return generateResponse(403, "The `status` field is mandatory")

    status = facade.setSensorStatus(body['name'], body['status'])

    if status != None:
        return  generateResponse(200, "New value setted for the sensor!", status)
    
    return  generateResponse(404, "Invalid sensor name or status type. New value for sensor not setted!")

app.run()