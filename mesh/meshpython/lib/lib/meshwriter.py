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
                p1x = '{:f}'.format(p1[0])
                p1y = '{:f}'.format(p1[1])
                p1z = '{:f}'.format(p1[2])
                p2x = '{:f}'.format(p2[0])
                p2y = '{:f}'.format(p2[1])
                p2z = '{:f}'.format(p2[2])
                p3x = '{:f}'.format(p3[0])
                p3y = '{:f}'.format(p3[1])
                p3z = '{:f}'.format(p3[2])
                s = "[["+p1x+" "+p1y+" "+p1z+"],["+ \
                    p2x+" "+p2y+" "+p2z+"],["+ \
                    p3x+" "+p3y+" "+p3z+"]]"
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
