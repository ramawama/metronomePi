from flask import Flask, request, jsonify
from flask_cors import CORS
import os
import ctypes

os.chdir("..")
path = os.getcwd()
os.chdir("./api/")

handler = ctypes.CDLL(path + "/metronome/bpmlib.dll")

handler.get_bpm.restype = ctypes.c_int
handler.get_min.restype = ctypes.c_int
handler.get_max.restype = ctypes.c_int


app = Flask(__name__)
CORS(app)

# Dicts used to convert to json objects
bpm = {"BPM" : None}
min = {"Min" : None}
max = {"Max" : None}


# Uses put method to update BPM and get method to retrieve.
@app.route("/bpm/", methods=["PUT", "GET"])
def put_bpm():

    if request.method == "PUT":
        new_data = request.get_json()
        if ("BPM" in new_data):
            bpm["BPM"] = new_data["BPM"]
            return jsonify({"message": "BPM updated successfully"}), 200
        return jsonify({"error": "JSON not given in correct format, use \"BPM\" as key."})

    if request.method == "GET":
        if bpm["BPM"] is not None:
            return jsonify(bpm), 200
        return jsonify({'message': 'Key currently not set.'}), 400
    
    return jsonify({"error":  "Not valid HTTP method."}), 400


# Uses get method to retrieve minimum and delete to reset minimum.
@app.route("/bpm/min/", methods=["DELETE", "GET"])
def get_min():

    if request.method == "DELETE":
        if(min["Min"] is not None):
            min["Min"] = None
            return jsonify({"message": "BPM reset to 0."}), 200
        return jsonify({"message": "BPM already 0."}), 200

    if request.method == "GET":
        if min["Min"] is not None:
            return jsonify(min), 200
        return jsonify({'error': 'Minimum currently not set.'}), 400
    
    return jsonify({"message":  "Not valid HTTP method."}), 400


# Uses get method to retrieve maximum and delete to reset maximum.
@app.route("/bpm/max/", methods=["DELETE", "GET"])
def get_max():

    if request.method == "DELETE":
        if(max["Max"] is not None):
            max["Max"] = None
            return jsonify({"message": "BPM reset to None."}), 200
        return jsonify({"message": "BPM already None."}), 200
    
    if request.method == "GET":
        if max["Max"] is not None:
            return jsonify(max), 200
        return jsonify({'error': 'Maximum currently not set.'}), 400
    
    return jsonify({"message":  "Not valid HTTP method."}), 400

if __name__ == "__main__":
    app.run(debug=True)