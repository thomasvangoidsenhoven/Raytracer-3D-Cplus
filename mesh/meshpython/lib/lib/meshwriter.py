import json


def writeJson(data, outfile="C:\\Users\\Thomas\\Desktop\\3D 2019\\3dcg1819-team\\mesh\\meshpython\\lib\\bunnyOP2.json"):
    arr = make_array(data)
    arr.reverse()
    file = open(outfile, "w")
    for line in arr:
        file.write(line + " \n")
    file.close()


def make_array(data):
    nodes = [data[0]]
    array = []
    while len(nodes) > 0:
        node = nodes.pop(0)
        if "children" in node:
            # depth first so first insert right el, then left
            nodes.insert(0, data[node["children"][1]])
            nodes.insert(0, data[node["children"][0]])
            array.append("box " + str(node["id"]))
            continue
        elif "triangles" in node:
            array.append("box " + str(node["id"]))
            for triangle in node["triangles"]:
                p1 = triangle[0]
                p2 = triangle[1]
                p3 = triangle[2]
                s = "[["+str(p1[0])+" "+str(p1[1])+" "+str(p1[2])+"],["+\
                    str(p2[0])+" "+str(p2[1])+" "+str(p2[2])+"],["+\
                    str(p3[0])+" "+str(p3[1])+" "+str(p3[2])+"]]"
                array.append("triangle " + s)
            continue
        else:
            print("wtf?")
    return array



# write to file format
# box -> root
# box -> root child 1
# triangle
# triangle
# triangle
# box -> root child 2
# box -> child2 child
# triangle
# triangle
# triangle
# box -> child2 child
# triangle
# triangle
# triangle
