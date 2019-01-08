from decimal import Decimal


def read_values(filename="D:\\bunny.mesh"):
    f = open(filename, "r")
    counter = 0
    status = "start"
    vertices_length = ""
    triangle_length = ""
    vertices = {}
    triangles = []
    for x in f:
        x = x.strip()
        splitted = x.split(" ")
        if status == "start" and len(splitted) == 1:
            vertices_length = splitted[0].strip()
            status = "Vertices"
            continue
        elif status == "Vertices" and len(splitted) == 3:
            x = Decimal(splitted[0])
            y = Decimal(splitted[1])
            z = Decimal(splitted[2])
            vertices[counter] = [x, y, z]
            counter = counter + 1
            continue
        elif status == "Vertices" and len(splitted) == 1:
            triangle_length = splitted[0].strip()
            status = "Triangles"
            continue
        elif status == "Triangles" and len(splitted) == 3:
            p1 = int(splitted[0])
            p2 = int(splitted[1])
            p3 = int(splitted[2])
            triangles.append([p1, p2, p3])
            continue
        print("Something strange happened with line: " + x + "\n")
    return {"xyz_with_index": vertices, "triangles": triangles,
            "vertices_length": vertices_length, "triangle_length": triangle_length}

