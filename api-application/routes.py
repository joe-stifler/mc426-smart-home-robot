import jwt
import datetime
from functools import wraps
from flask import  Flask, request

app = Flask("RESTAPISmartHouse")

app.config['SECRET_KEY'] = "hunter_x_hunter_2020"

def getBody():
    body = request.get_json()

    if not body:
        body = dict(request.form)

    return body

    

def token_required(f):
    @wraps(f)
    def decorated(*args, **kwargs):
        body = getBody()

        if not body:
            return generateResponse(403, "Body is missing!")

        if 'token' not in body:
            return generateResponse(403, "Token is missing!")

        token = body.get('token')

        try:
            data = jwt.decode(token, app.config['SECRET_KEY'])
        except:
            return generateResponse(403, "Token is invalid!")

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
        return generateResponse(400, "The `email` field is mandatory")

    if ("password" not in body):
        return generateResponse(400, "The `password` field is mandatory")

    if body['password'] == "password123":
        token = jwt.encode({'user' : body['email'], 'exp' : datetime.datetime.utcnow() + datetime.timedelta(minutes=30)}, app.config['SECRET_KEY'])
    
        return generateResponse(200, "User authenticated!", token.decode("utf-8"))
    else:
        return generateResponse(401, "Could not verify user authentication!")


@app.route("/auth/register", methods=["POST"])
def userSignUp():
    body = getBody()

    if not body:
        return generateResponse(403, "Body is missing!")

    if ("name" not in body):
        return generateResponse(400, "The `name` field is mandatory")

    if ("email" not in body):
        return generateResponse(400, "The `email` field is mandatory")

    if ("password" not in body):
        return generateResponse(400, "The `password` field is mandatory")

    return  generateResponse(200, "User created successfully!")


@app.route("/auth/reset", methods=["PUT"])
def userPasswordReset():
    body = getBody()

    if not body:
        return generateResponse(403, "Body is missing!")

    if ("email" not in body):
        return generateResponse(400, "The `email` field is mandatory")

    return  generateResponse(200, "An e-mail was sent to the user!")


@app.route("/sensors/available-sensors", methods=["GET"])
@token_required
def sensorAvailable():
    body = getBody()

    if not body:
        return generateResponse(403, "Body is missing!")

    sensors = "luz1" + "&" + "luz2" + "&" + "energia"

    return  generateResponse(200, "Returning all sensors!", sensors)


@app.route("/sensors/get-sensor-status", methods=["GET"])
@token_required
def sensorGetStatus():
    body = getBody()

    if not body:
        return generateResponse(403, "Body is missing!")

    if ("name" not in body):
        return generateResponse(400, "The `name` field is mandatory")

    status = "123"

    return  generateResponse(200, "Returning sensor status!", status)


@app.route("/sensors/set-sensor-status", methods=["PUT"])
@token_required
def sensorSetStatus():
    body = getBody()

    if not body:
        return generateResponse(403, "Body is missing!")

    if ("name" not in body):
        return generateResponse(400, "The `name` field is mandatory")

    if ("status" not in body):
        return generateResponse(400, "The `status` field is mandatory")

    status = "123"

    return  generateResponse(200, "New value setted for the sensor!", status)


def generateResponse(status, message, content = False):
    response = {}
    response["status"] = str(status)
    response["message"] = str(message)

    if (content):
        response["content"] = str(content)

    return response


app.run()