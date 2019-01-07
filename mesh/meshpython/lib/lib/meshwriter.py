import json


def writeJson(data, outfile="bunnyOp.json"):
    string = json.dumps(data)
    file = open(outfile, "w")
    file.write(string)
    file.close()
