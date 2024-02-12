from flask import Flask, request, jsonify

app = Flask(__name__)

# bpm json object
bpm = {"BPM" : None}

@app.route("/bpm/", methods=["PUT", "GET"])
def put_bpm():
    # Put request 
    if request.method == "PUT":
        new_data = request.get_json()
        if ("BPM" in new_data):
            bpm["BPM"] = new_data["BPM"]
            return jsonify({"message": "BPM updated successfully"}), 200
        return 400
    # Checks if request was updated
    if request.method == "GET":
        if bpm["BPM"] is None:
            return jsonify({'error': 'Key not found'}), 400
        return jsonify(bpm), 200
    return jsonify({"message":  "Not valid method"}), 400

min = {"Min" : None}
@app.route("/bpm/min/", methods=["DELETE", "GET"])
def get_min():
    if request.method == "DELETE":
        if(min["Min"] == None):
            return jsonify({"message": "BPM already 0"}), 200
        min["Min"] = None
        return jsonify({"message": "BPM set to 0"}), 200
    if request.method == "GET":
        if min["Min"] is None:
            return jsonify({'error': 'Min not set'}), 400
        return jsonify(min), 200
    return jsonify({"message":  "Not valid method"}), 400
    
max = {"Max" : None}
@app.route("/bpm/max/", methods=["DELETE", "GET"])
def get_max():
    if request.method == "DELETE":
        if(max["Max"] == None):
            return jsonify({"message": "BPM already 0"}), 200
        max["Max"] = None
        return jsonify({"message": "BPM set to 0"}), 200
    if request.method == "GET":
        if max["Max"] is None:
            return jsonify({'error': 'Max not set'}), 400
        return jsonify(max), 200
    return jsonify({"message":  "Not valid method"}), 400
if __name__ == "__main__":
    app.run(debug=True)