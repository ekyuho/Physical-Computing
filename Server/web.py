import ewha
from flask import Flask, request
app = Flask(__name__)


@app.route("/ewha/lookup")
def _ewha1():
    r= ewha.lookup(request.args)
    print(r)
    return r[0],r[1],r[2]


if __name__ == "__main__":
    app.run(host='0.0.0.0', port=8082)
