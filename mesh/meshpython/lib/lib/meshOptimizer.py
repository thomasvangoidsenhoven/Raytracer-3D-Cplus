from decimal import Decimal
from pprint import pprint
# https://stackoverflow.com/questions/3323001/what-is-the-maximum-recursion-depth-in-python-and-how-to-increase-it


def optimize(data):
    #sys.setrecursionlimit(2147483647)
    boxes = {}
    start_task = [{"id": 0, "parent": None, "triangles": data["triangles"]}]
    vertices = data["xyz_with_index"]
    return loop(boxes, start_task, vertices)

def loop(boxes, tasks, vertices):
    while len(tasks) > 0:
        first_task = tasks.pop(0)
        if len(first_task["triangles"]) < 10:
            new_t = replaceTrianglePoints(first_task["triangles"], vertices)
            returnbox = {"id": first_task["id"], "parent": first_task["parent"], "triangles": new_t}
            boxes[first_task["id"]] = returnbox
            #return loop(boxes, tasks, vertices)
            continue
        elif len(first_task["triangles"]) > 10:
            axis = findLongestAxis(first_task["triangles"], vertices)
            sorted = sortTriangleArray(first_task["triangles"], axis, vertices)
            current_id = len(tasks) + len(boxes) + 1
            med = round(len(first_task["triangles"])/2)
            task1 = {"id": current_id + 1, "parent": first_task["id"], "triangles": sorted[:med]}
            task2 = {"id": current_id + 2, "parent": first_task["id"], "triangles": sorted[med:]}
            tasks.append(task1)
            tasks.append(task2)
            newbox = {"id": first_task["id"], "parent": first_task["parent"], "children": [current_id+1, current_id+2]}
            boxes[first_task["id"]] = newbox
            #return loop(boxes, tasks, vertices)
            continue
    return boxes

def replaceTrianglePoints(arr, vertices):
    new_arr = []
    for t in arr:
        p1 = [(vertices[t[0]][0]), (vertices[t[0]][1]), (vertices[t[0]][2])]
        p2 = [(vertices[t[1]][0]), (vertices[t[1]][1]), (vertices[t[1]][2])]
        p3 = [(vertices[t[2]][0]), (vertices[t[2]][1]), (vertices[t[2]][2])]
        new_arr.append([p1, p2, p3])
    return new_arr




def findLongestAxis(array, vertices):
    minx = maxx = miny = maxy = minz = maxz = None
    for triangle in array:
        p1 = triangle[0]
        p2 = triangle[1]
        p3 = triangle[2]
        xvalues = [vertices[p1][0], vertices[p2][0], vertices[p3][0]]
        yvalues = [vertices[p1][1], vertices[p2][1], vertices[p3][1]]
        zvalues = [vertices[p1][2], vertices[p2][2], vertices[p3][2]]
        if minx is None and maxx is None:
            minx = min(xvalues)
            maxx = max(xvalues)
        if min(xvalues) < minx:
            minx = min(xvalues)
        if max(xvalues) > maxx:
            maxx = max(xvalues)

        if miny is None and maxy is None:
            miny = min(yvalues)
            maxy = max(yvalues)
        if min(yvalues) < miny:
            miny = min(yvalues)
        if max(yvalues) > maxy:
            maxy = max(yvalues)

        if minz is None and maxz is None:
            minz = min(zvalues)
            maxz = max(zvalues)
        if min(zvalues) < minz:
            minz = min(zvalues)
        if max(zvalues) > maxz:
            maxz = max(zvalues)
    difx = maxx - minx
    dify = maxy - miny
    difz = maxz - minz
    if difx >= dify and difx >= difz:
        return 0
    if dify >= difx and dify >= difz:
        return 1
    if difz >= difx and difz >= dify:
        return 2

def sortTriangleArray(array, axis, vertices):
    return sorted(array, key=lambda triangle: returnMaxPoint(triangle, axis, vertices))


def returnMaxPoint(triangle, axis, vertices):
    pval1 = vertices[triangle[0]][axis]
    pval2 = vertices[triangle[1]][axis]
    pval3 = vertices[triangle[2]][axis]
    return max(pval1, pval2, pval3)

def returnMinPoint(triangle, axis, vertices):
    pval1 = vertices[triangle[0]][axis]
    pval2 = vertices[triangle[1]][axis]
    pval3 = vertices[triangle[2]][axis]
    return max(pval1, pval2, pval3)

def returnSumPoint(triangle, axis, vertices):
    pval1 = vertices[triangle[0]][axis]
    pval2 = vertices[triangle[1]][axis]
    pval3 = vertices[triangle[2]][axis]
    return pval1+pval2+pval3

