//
//  main.c
//  cube-solver
//
//  Created by Bharat Kesari on 7/3/20.
//  Copyright © 2020 Bharat Kesari. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

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
const int X_INDEXES[26] = { 9, DNE, 29, 10, DNE, 28, 11, DNE, 27, 12, DNE, 32, 13, 31, 14, DNE, 30,
    15, DNE, 35, 16, DNE, 34, 17, DNE, 33 };

const int Y_INDEXES[26] = { 38, 37, 36, DNE, DNE, DNE, 18, 19, 20, 41, 40, 39, DNE, DNE, 21, 22,
    23, 44, 43, 42, DNE, DNE, DNE, 24, 25, 26};

const int Z_INDEXES[26] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, DNE, DNE, DNE, DNE, DNE, DNE, DNE, DNE, 51,
    52, 53, 48, 49, 50, 45, 46, 47};

// Corner piece indexes in pieces[] of a Cube struct
const int CORNER_POS[8] = { 0, 2, 6, 8, 17, 19, 23, 25 };

// Corner piece coordinates
const int CORNER_COORD[8][3] = { {0, 0, 0}, {2, 0, 0}, {0, 2, 0}, {2, 2, 0}, {0, 0, 2}, {2, 0, 0}, {0, 2, 2}, {2, 2, 2} };

// Center piece indexes in pieces[] of a Cube struct
const int CENTER_POS[6] = { 4, 10, 12, 13, 15, 21 };

// Center piece coordinates
const int CENTER_COORD[6][3] = { {1, 1, 0}, {1, 0, 1}, {0, 1, 1}, {2, 1, 1}, {1, 2, 1}, {1, 1, 2} };

// Edge piece indexes in pieces[] of a Cube struct
const int EDGE_POS[12] = { 1, 3, 5, 7, 9, 11, 14, 16, 18, 20, 22, 24 };

// Edge piece coordinates
const int EDGE_COORD[12][3] = {{1, 0, 0}, {0, 1, 0}, {2, 1, 0}, {1, 2, 0} };

// Front face piece indexes in pieces[] of a Cube struct
const int FRONT_POS[9] = { 6, 7, 8, 14, 15, 16, 23, 24, 25 };

// Front face piece coordinates
const int FRONT_COORD[9][3] = { {0, 2, 0}, {1, 2, 0}, {2, 2, 0}, {0, 2, 1}, {1, 2, 1}, {2, 2, 1}, {0, 2, 2}, {1, 2, 2}, {2, 2, 2} };

// Back face piece indexes in pieces[] of a Cube struct
const int BACK_POS[9] = { 0, 1, 2, 9, 10, 11, 17, 18, 19 };

// Back face piece coordinates
const int BACK_COORD[9][3] = { {0, 0, 0}, {1, 0, 0}, {2, 0, 0}, {0, 0, 1}, {1, 0, 1}, {2, 0, 1}, {0, 0, 2}, {1, 0, 2}, {2, 0, 2} };

// Right face piece indexes in pieces[] of a Cube struct
const int RIGHT_POS[9] = { 2, 5, 8, 11, 13, 16, 19, 22, 25 };

// Right face piece coordinates
const int RIGHT_COORD[9][3] = { {2, 0, 0}, {2, 1, 0}, {2, 2, 0}, {2, 0, 1}, {2, 0, 1}, {2, 2, 1}, {2, 0, 2}, {2, 1, 2}, {2, 2, 2} };

// Left face piece indexes in pieces[] of a Cube struct
const int LEFT_POS[9] = { 0, 3, 6, 9, 12, 14, 17, 20, 23 };

// Left face piece coordinates
const int LEFT_COORD[9][3] = { {0, 0, 0}, {0, 1, 0}, {0, 2, 0}, {0, 0, 1}, {0, 0, 1}, {0, 2, 1}, {0, 0, 2}, {0, 1, 2}, {0, 2, 2} };

// Top face piece indexes in pieces[] of a Cube struct
const int TOP_POS[9] = { 0, 1, 2, 3, 4, 5, 6, 7, 8 };

// Top face piece coordinates
const int TOP_COORD[9][3] = { {0, 0, 0}, {1, 0, 0}, {2, 0, 0}, {0, 1, 0}, {1, 1, 0}, {2, 1, 0}, {0, 2, 0}, {1, 2, 0}, {2, 2, 0} };

// Bottom face piece indexes in pieces[] of a Cube struct
const int BOTTOM_POS[9] = { 17, 18, 19, 20, 21, 22, 23, 24, 25 };

// Bottom face piece coordinates
const int BOTTOM_COORD[9][3] = { {0, 0, 2}, {1, 0, 2}, {2, 0, 2}, {0, 1, 2}, {1, 1, 2}, {2, 1, 2}, {0, 2, 2}, {1, 2, 2}, {2, 2, 2} };

// Middle Layer perpendicular to x piece indexes in pieces[] of a Cube struct
const int X_MID[9] = { 1, 4, 7, 10, DNE, 15, 18, 21, 24 };

// Middle Layer perpendicular to y piece indexes in pieces[] of a Cube struct
const int Y_MID[9] = { 3, 4, 5, 12, DNE, 13, 20, 21, 22 };

// Middle Layer perpendicular to z piece indexes in pieces[] of a Cube struct
const int Z_MID[9] = { 9, 10, 11, 12, DNE, 13, 14, 15, 16 };

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

// Define DNE constant for arrays
#define DNE -1

// Function prototypes

// User input fuctions
void getColors(char* colorArr);
bool isColor(char input);

int main(int argc, const char * argv[]) {
    
    // Create an array to hold user's input
    char colorArr[NUM_SQUARES];
    
    // Get user input
    getColors(colorArr);

    
    return 0;
}

// User input functions

/**
 * Gathers user input of color abbreviations and stores the input in a character array.
 * Makes sure that user input is of proper length and contains allowable values.
 * Exits the function if the user input is invalid.
 *
 * @param colorArr
 * A pointer to an array used to hold the color abbreviations from the user input
 */
void getColors(char* colorArr)
{
    char ch;
    
    // Prompt user to enter color abbreviations string
    printf("Enter Rubik's cube permutation:\n");
    
    // Iterate through input and populate the array with the abbreviations
    for (int i = 0; i < NUM_SQUARES; ++i)
    {
        scanf("%c", &ch);
        
        // Make sure input char is valid
        if (isColor(ch))
        {
            *colorArr = ch;
            ++colorArr;
        }
        // Exit the function if char is invalid
        else
        {
            printf("Invalid input.\n");
            exit(1);
        }
    }
    
    // Check if input length does not exceed NUM_SQUARES
    scanf("%c", &ch);
    // Exit function if input is too long
    if (ch != '\n')
    {
        printf("Invalid input.\n");
        exit(1);
    }
}

/**
 * Checks if a character is an abbreviation for a color on a Rubiks cube
 *
 * @param input
 * The character to be checked
 *
 * @return
 * True if input is a valid char
 * False if input is not a valid char
 */
bool isColor(char input)
{
    // Check if input is color abbreviation
    if (input == 'r' || input == 'g' || input == 'y'
        || input == 'w' || input == 'o' || input == 'b')
    {
        return true;
    }
    else
    {
        return false;
    }
}

