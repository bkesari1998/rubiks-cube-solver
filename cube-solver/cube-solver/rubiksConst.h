//
//  rubiksConst.h
//  cube-solver
//
//  Created by Bharat Kesari on 7/3/20.
//  Copyright © 2020 Bharat Kesari. All rights reserved.
//

#ifndef rubiksConst_h
#define rubiksConst_h

// Constants and definitions

// Pieces in a Rubik's cube
#define NUM_PIECES 26

// Number of corner pieces in a Rubik's cube
#define NUM_CORNER 8

// Number of edge pieces in a Rubiks's cube
#define NUM_EDGE 12

// Number of center pieces in a Rubik's cube
#define NUM_CENTER 6

// Number of pieces on a face of a Rubik's cube
#define NUM_PIECES_ON_FACE 9

// Number of pieces on a row of a Rubik's cube
#define NUM_PIECES_IN_ROW 3

// Squares on a Rubik's cube
#define NUM_SQUARES 54

// Edges on one side of a Rubik's Cube
#define NUM_EDGES_ON_FACE 4

// Corners on one side of a Rubik's Cube
#define NUM_CORNERS_ON_FACE 4

// Indexes of pieces[] in a Cube struct that correspond to the top face
#define TOP_LEFT_BACK_CORNER 0
#define TOP_BACK_EDGE 1
#define TOP_RIGHT_BACK_CORNER 2
#define TOP_LEFT_EDGE 3
#define TOP_CENTER 4
#define TOP_RIGHT_EDGE 5
#define TOP_LEFT_FRONT_CORNER 6
#define TOP_FRONT_EDGE 7
#define TOP_RIGHT_FRONT_CORNER 8

// Indexes of pieces[] in a Cube struct that correspond to the back face
#define BACK_LEFT_TOP_CORNER 0
#define BACK_TOP_EDGE 1
#define BACK_RIGHT_TOP_CORNER 2
#define BACK_LEFT_EDGE 9
#define BACK_CENTER 10
#define BACK_RIGHT_EDGE 11
#define BACK_LEFT_BOTTOM_CORNER 17
#define BACK_BOTTOM_EDGE 18
#define BACK_RIGHT_BOTTOM_CORNER 19

// Indexes of pieces[] in a Cube struct that correspond to the left face
#define LEFT_BACK_TOP_CORNER 0
#define LEFT_TOP_EDGE 3
#define LEFT_FRONT_TOP_CORNER 6
#define LEFT_BACK_EDGE 9
#define LEFT_CENTER 12
#define LEFT_FRONT_EDGE 14
#define LEFT_BACK_BOTTOM_CORNER 17
#define LEFT_BOTTOM_EDGE 20
#define LEFT_FRONT_BOTTOM_CORNER 23

// Indexes of pieces[] in a Cube struct that correspond to the right face
#define RIGHT_BACK_TOP_CORNER 2
#define RIGHT_TOP_EDGE 5
#define RIGHT_FRONT_TOP_CORNER 8
#define RIGHT_BACK_EDGE 11
#define RIGHT_CENTER 13
#define RIGHT_FRONT_EDGE 16
#define RIGHT_BACK_BOTTOM_CORNER 19
#define RIGHT_BOTTOM_EDGE 22
#define RIGHT_FRONT_BOTTOM_CORNER 25

// Indexes of pieces[] in a Cube struct that correspond to the front face
#define FRONT_LEFT_TOP_CORNER 6
#define FRONT_TOP_EDGE 7
#define FRONT_RIGHT_TOP_CORNER 8
#define FRONT_LEFT_EDGE 14
#define FRONT_CENTER 15
#define FRONT_RIGHT_EDGE 16
#define FRONT_LEFT_BOTTOM_CORNER 23
#define FRONT_BOTTOM_EDGE 24
#define FRONT_RIGHT_BOTTOM_CORNER 25

// Indexes of pieces[] in a Cube struct that correspond to the bottom face
#define BOTTOM_LEFT_BACK_CORNER 17
#define BOTTOM_BACK_EDGE 18
#define BOTTOM_RIGHT_BACK_CORNER 19
#define BOTTOM_LEFT_EDGE 20
#define BOTTOM_CENTER 21
#define BOTTOM_RIGHT_EDGE 22
#define BOTTOM_LEFT_FRONT_CORNER 23
#define BOTTOM_FRONT_EDGE 24
#define BOTTOM_RIGHT_FRONT_CORNER 25

// Define DNE constant for arrays
#define DNE -1

// Create const arrays for indexes in user input string that correspond to the color of each side
extern const int X_INDEXES[];

extern const int Y_INDEXES[];

extern const int Z_INDEXES[];

// Corner piece indexes in pieces[] of a Cube struct
extern const int CORNER_POS[];

// Center piece indexes in pieces[] of a Cube struct
extern const int CENTER_POS[];

// Edge piece indexes in pieces[] of a Cube struct
extern const int EDGE_POS[];

// Front face piece indexes in pieces[] of a Cube struct
extern const int FRONT_POS[];

// Back face piece indexes in pieces[] of a Cube struct
extern const int BACK_POS[];

// Right face piece indexes in pieces[] of a Cube struct
extern const int RIGHT_POS[];

// Left face piece indexes in pieces[] of a Cube struct
extern const int LEFT_POS[];

// Top face piece indexes in pieces[] of a Cube struct
extern const int TOP_POS[];

// Bottom face piece indexes in pieces[] of a Cube struct
extern const int BOTTOM_POS[];

// Middle Layer perpendicular to x piece indexes in pieces[] of a Cube struct
extern const int X_MID[];

// Middle Layer perpendicular to y piece indexes in pieces[] of a Cube struct
extern const int Y_MID[];

// Middle Layer perpendicular to z piece indexes in pieces[] of a Cube struct
extern const int Z_MID[];

// Enumerations and structures

// Define possible colors on a Rubik's cube
typedef enum colors {
    WHITE,
    YELLOW,
    ORANGE,
    RED,
    BLUE,
    GREEN,
    UNDEFINED
} Color;

// Define possible piece types on a Rubik's cube
typedef enum pieceTypes {
    CENTER,
    EDGE,
    CORNER,
    NONE
} PieceType;

// Define possible faces of a Rubik's cube
typedef enum faces {
    FRONT,
    BACK,
    LEFT,
    RIGHT,
    TOP,
    BOTTOM
} Face;

// Define piece on a Rubik's cube
typedef struct piece {
    PieceType pieceType;
    int pieceNum;
    int xCoord;
    int yCoord;
    int zCoord;
    Color x;
    Color y;
    Color z;
} Piece;

// Define a Rubik's cube
typedef struct cubes {
    Piece pieces[NUM_PIECES];
} Cube;

#endif /* rubiksConst.h */
