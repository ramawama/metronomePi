from flask import Flask, request, jsonify

app = Flask(__name__)

@app.route("/bpm/<bpm>", methods=["PUT", "GET"])
def get_bpm(bpm):
    if request.method == "PUT":
        data = request.get.json()
        return jsonify(data), 201
    if request.method == "GET":
        bpm_data = {
            "BPM"   :   bpm
        }
        return jsonify(bpm_data), 200
    else:
        return 403

@app.route("/bpm/min/<min>", methods=["DELETE", "GET"])
def get_min(min):
    bpm_min = {
        "min"   :   min
    }
    return jsonify(bpm_min), 200

@app.route("/bpm/max/<max>", methods=["DELETE", "GET"])
def get_max(max):
    bpm_max =   {
        "max"   :   max
    }
    return jsonify(bpm_max), 200

if __name__ == "__main__":
    app.run(debug=True)