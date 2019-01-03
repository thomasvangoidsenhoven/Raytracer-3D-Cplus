import json


def writeJson(data, outfile="D:\\optimized2.json"):
    string = json.dumps(data)
    file = open(outfile, "w")
    file.write(string)
    file.close()
