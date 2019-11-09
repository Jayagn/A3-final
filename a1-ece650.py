import re
import sys

class Point(object):
    def __init__(self,x,y):
        self.x = float(x)
        self.y = float(y)
    def __repr__(self):
        return'({0:.2f},{1:.2f})'.format(self.x,self.y)

class Line(object):
    def __init__(self,p1,p2):
        self.src = p1
        self.dst = p2
    def __repr__(self):
        return repr(self.src) + '-->' + repr(self.dst)


def intersection(l1, l2):
    x1, y1 = l1.src.x, l1.src.y
    x2, y2 = l1.dst.x, l1.dst.y
    x3, y3 = l2.src.x, l2.src.y
    x4, y4 = l2.dst.x, l2.dst.y

    x_num = ((x1 * y2 - y1 * x2) * (x3 - x4) - (x1 - x2) * (x3 * y4 - y3 * x4))
    x_den = ((x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4))
    if x_den == 0:
         return None
    x_coor = x_num / x_den


    y_num = (x1 * y2 - y1 * x2) * (y3 - y4) - (y1 - y2) * (x3 * y4 - y3 * x4)
    y_den = (x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4)
    if y_den == 0:
        return None
    y_coor = y_num / y_den

    if (min(x1, x2) <= x_coor <= max(x1, x2) and min(y1, y2) <= y_coor <= max(y1, y2)) and (
    (min(x3, x4) <= x_coor <= max(x3, x4) and min(y3, y4) <= y_coor <= max(y3, y4))):
        return Point(x_coor, y_coor), l1, l2
    else:
        return None

def Graph(vertice_dict, edge_list):
    print("V" + " " + str(len(vertice_dict)))
    sys.stdout.write("E {")
    for e in range(len(edge_list)):
        if e == len(edge_list) - 1:
            sys.stdout.write("<" + str(edge_list[e][0]) + "," + str(edge_list[e][1]) + ">")
        else:
            sys.stdout.write("<" + str(edge_list[e][0]) + "," + str(edge_list[e][1]) + ">,")
    print("}")
    sys.stdout.flush()


def distance_sort(vertices):
    for i in range(len(vertices)):
        for j in range(len(vertices[i])):
            for k in range(len(vertices[i][j])):
                vertices[i][j][k][1] = distance(vertices[i][j][0][0], vertices[i][j][k][0])
            vertices[i][j].sort(key=lambda x: x[1])
    return vertices


def distance(p1,p2):
    return ((p1[0] - p2[0]) ** 2) + ((p1[1] - p2[1]) ** 2)


def r_vertice(vertices, intersect_segment):
    for i in range(len(intersect_segment)):
        for j in range(len(intersect_segment[i])):
            if intersect_segment[i][j] == 0:
                vertices[i][j] = []
    return vertices


def g_vertice_edge(vertices):
    vertice_dict = {}
    edge_list = []
    index = 0
    for i in range(len(vertices)):
        for j in range(len(vertices[i])):
            for k in range(len(vertices[i][j])):
                if vertices[i][j][k][0] not in vertice_dict:
                    vertice_dict[vertices[i][j][k][0]] = index
                    index = index + 1

    for i in range(len(vertices)):
        for j in range(len(vertices[i])):
            for k in range(len(vertices[i][j]) - 1):
                edge_list.append((vertice_dict[vertices[i][j][k][0]], vertice_dict[vertices[i][j][k + 1][0]]))

    return vertice_dict, edge_list


Dictionary = {}
l = []

while True:
    try:
        cmd_input = raw_input()
        if cmd_input == "exit":
            break

        if re.match(r'[ac] \"[a-zA-Z *]+\" (\(-?[0-9]+,-?[0-9]+\) ?)+', cmd_input) or re.match(r'r (\"[a-zA-z\s]+\")$', cmd_input) or re.match(r'g',cmd_input):
            # print("Valid Input")
            cmd_add_change_street = re.match("([ac]) (\"[a-zA-Z *]+\") ((\(-?[0-9]+,-?[0-9]+\) ?)+)", cmd_input)
            cmd_remove_street = re.match("(r) (\"[a-zA-z\s]+\")", cmd_input)
            cmd_generate = re.match("(g)", cmd_input)

            if cmd_add_change_street:
                action = (cmd_add_change_street.group(1))
                # print(action)
                street_name = (cmd_add_change_street.group(2))
                # print(street_name)
                if action == 'a' and street_name in Dictionary:
                    sys.stderr.write("Error: Street already exists\n")
                else:
                    coor = (cmd_add_change_street.group(3))
                if action == 'c' and street_name not in Dictionary:
                    sys.stderr.write("Error: Street does not exists\n")
                    continue


                # find = (re.findall("\(-?[0-9],-?[0-9]\)", coor))
                # xcoor = (re.findall("\(-?[0-9],find)")
                # print(xcoor.split('('))

                find = re.findall("-?[0-9]+", coor)
                coor_list = []
                for i in range(0, len(find), 2):
                    coor_list.append((float(find[i]), float(find[i + 1])))
                    #print(coor_list)


                # print(find)
                p = []

                for i in range(len(coor_list)):
                    point = Point(coor_list[i][0],coor_list[i][1])
                    p.append(point)
                    Dictionary[street_name] = p
                    #find[i] = int(find[i])
                # for i in range(0,len(find),2):
                #     p.append(Point(float(find[i]),float(find[i+1])))
                #for i in range(0,len(p)-1):
                   # l.append(Line(p[i],p[i+1]))
                # print(l)
                #print(p)

                # for i in range(1,len(l)):
                #     poi, g1, g2= intersection(l[i-1],l[i])
                #     print(i, ":", poi)

                #Dictionary[street_name] = p
                # print(Dictionary)
                pass

            elif cmd_remove_street:
                action = (cmd_remove_street.group(1))
                # print(action)
                street_name = (cmd_remove_street.group(2))
                # print(street_name)
                if action == 'r' and street_name not in Dictionary:
                    sys.stderr.write("Error: Street does not exist\n")
                else:
                    del Dictionary[street_name]
                #print(Dictionary)
                pass

            elif cmd_generate:
                vertice_dict = {}
                edge_list = []
                action = (cmd_generate.group(1))
                intersect_segment = []
                vertices = []
                street_lines = []

                for street_name in Dictionary:
                    p = Dictionary[street_name]
                    segment_list = []
                    segment_points = []
                    intersecting = []
                    for i in range(len(p) - 1):
                        intersecting.append(0)
                        segment_points.append([[(p[i].x, p[i].y), 0], [(p[i + 1].x, p[i + 1].y), 0]])
                        segment_list.append(Line(p[i], p[i + 1]))
                    intersect_segment.append(intersecting)
                    street_lines.append(segment_list)
                    vertices.append(segment_points)
                for i in range(len(street_lines) - 1):
                    for j in range(len(street_lines[i])):
                        for k in range(i + 1, len(street_lines)):
                            for l in range(len(street_lines[k])):
                                final_intersection = intersection(street_lines[i][j], street_lines[k][l])
                                if final_intersection:
                                    inter_point = (final_intersection[0].x, final_intersection[0].y)

                                    if [inter_point, 0] not in vertices[i][j]:
                                        vertices[i][j].append([inter_point, 0])
                                    if [inter_point, 0] not in vertices[k][l]:
                                        vertices[k][l].append([inter_point, 0])

                                    intersect_segment[i][j] = 1
                                    intersect_segment[k][l] = 1
                vertices = distance_sort(vertices)
                vertices = r_vertice(vertices, intersect_segment)
                vertice_dict , edge_list = g_vertice_edge(vertices)
                #return vertice_dict , edge_list
            #if len(Dictionary) <= 1:
                #vertice_dict = {}
                #edge_list =[]
                Graph(vertice_dict, edge_list)

            # print(action)
            # print(l)
            # print(p)
            #     # for i in range(1,len(l)):
            #     #     poi, g1, g2= intersection(l[i-1],l[i])
            #     #     print(i, ":", poi)
            # print(Dictionary)


        else:
            sys.stderr.write("Error: Invalid Input\n")
    except EOFError:
        sys.exit(0)
