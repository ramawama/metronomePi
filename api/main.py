from flask import Flask, request, jsonify

app = Flask(__name__)

@app.route("/bpm/")
def bpm():
    return "bpm"

@app.route("/bpm/min/")
def min():
    return "min"

@app.route("/bpm/max/")
def max():
    return "max"

if __name__ == "__main__":
    app.run(debug=True)