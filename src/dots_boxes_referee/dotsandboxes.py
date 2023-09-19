class Edge:
    def __init__(self, coord1, coord2):
        r1, c1 = coord1
        r2, c2 = coord2

        if r1 > r2 or c1 > c2:
            self.coord2 = coord1
            self.coord1 = coord2
        else:
            self.coord1 = coord1  # tuple of (r, c) where r is row value and c is column value
            self.coord2 = coord2  # tuple of (r, c) where r is row value and c is column value

        # self.coord1 = coord1  # tuple of (r, c) where r is row value and c is column value
        # self.coord2 = coord2  # tuple of (r, c) where r is row value and c is column value
        self.marked = False

    def __eq__(self, obj):
        if isinstance(obj, Edge):
            if obj.coord1 == self.coord1:
                if obj.coord2 == self.coord2:
                    return True
            elif obj.coord1 == self.coord2:
                if obj.coord2 == self.coord1:
                    return True
        return False

    def __hash__(self):
        return id(Edge(self.coord1, self.coord2))

    def __str__(self):
        return str(self.coord1) + " " + str(self.coord2) + " " + str(self.marked)

    def setMarked(self):
        self.marked = True

    def getMarked(self):
        return self.marked


def generateEdges(r, c):  # how many rows, how many columns
    edges = {}
    for i in range(r+1):
        for j in range(c+1):
            coord1 = (i, j)
            if i != r:
                # newEdge = Edge(coord1, (i + 1, j))
                # edges[newEdge] = newEdge
                coord2 = (i + 1, j)
                edges[(coord1, coord2)] = 0
            if j != c:
                # newEdge = Edge(coord1, (i, j + 1))
                # edges[newEdge] = newEdge
                coord2 = (i, j + 1)
                edges[(coord1, coord2)] = 0
    return edges


# return number of squares completed
# -1 for invalid edge/move
# 0 for no squares completed
# 1 or 2 for 1 or 2 squares completed
def getPoints(edge, player):
    points = 0
    marked = board.get(edge)  # asserts orientation will be correct for below computations
    # if edge is in edges and if edge is not marked, then valid move
    if marked is not None and marked == 0:
        board[edge] = player
        r1, c1 = edge[0]
        r2, c2 = edge[1]
        # determine vertical vs horizontal
        # see planning.txt for coordinate modification source
        if r1 == r2:  # horizontal edge
            # square 1 check
            mod1 = ((r1-1, c1), (r2-1, c2))
            mod2 = ((r1-1, c1), (r2, c2-1))
            mod3 = ((r1-1, c1+1), (r2, c2))
            points += checkSquareCompleted(mod1, mod2, mod3)

            # square 2 check
            mod1 = ((r1, c1), (r2+1, c2-1))
            mod2 = ((r1, c1+1), (r2+1, c2))
            mod3 = ((r1+1, c1), (r2+1, c2))
            points += checkSquareCompleted(mod1, mod2, mod3)

            return points

        if c1 == c2:  # vertical edge
            # square 1 check
            mod1 = ((r1, c1-1), (r2-1, c2))
            mod2 = ((r1, c1-1), (r2, c2-1))
            mod3 = ((r1+1, c1-1), (r2, c2))
            points += checkSquareCompleted(mod1, mod2, mod3)

            # square 2 check
            mod1 = ((r1, c1), (r2-1, c2+1))
            mod2 = ((r1+1, c1), (r2, c2+1))
            mod3 = ((r1, c1+1), (r2, c2+1))
            points += checkSquareCompleted(mod1, mod2, mod3)

            return points

    # if it makes it outside the above if statements without returning,
    # then it is an invalid move
    return -1


# takes the 3 associated edges of a valid edge completed, and
# determines if a square has been completed for a specific orientation
# returns 1 if square was completed, and 0 if not completed
# edge 1 should always contain top left coordinate for square completion tracking purposes
def checkSquareCompleted(edge1, edge2, edge3):
    # TODO save top left coordinate completed square
    coord, _ = edge1
    edge1 = board.get(edge1)
    if edge1 is not None and edge1:
        edge2 = board.get(edge2)
        if edge2 is not None and edge2:
            edge3 = board.get(edge3)
            if edge3 is not None and edge3:

                return 1  # if it makes it here, then all edges are in bounds and have been previously marked
    return 0  # if it makes it here, not all edges were in bound and marked, so no square has been completed



r, c = 9, 9 #board size
board = generateEdges(r, c)

def getmove():
    return None

turn = 1

def changeTurn(player):
    return player * -1


def addPoints(player):
    # TODO add points to player score value
    None

def gameplay():
    endmsg = ""
    while endmsg == "":
        move = getmove()
        player = 1
        points = getPoints(move, player)

        if points == -1:
            endmsg = "Game ended, invalid move" + str(player *-1) + "wins"
        if points == 0:
            player = changeTurn()
        if points == 1 or points == 2:
            addPoints(player)
        return points
    print(endmsg)






