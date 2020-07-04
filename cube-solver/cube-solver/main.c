//
//  main.c
//  cube-solver
//
//  Created by Bharat Kesari on 7/3/20.
//  Copyright © 2020 Bharat Kesari. All rights reserved.
//

// Solved Cube: wwwwwwwwwooooooooogggggggggrrrrrrrrrbbbbbbbbbyyyyyyyyy
// wowgybwyogygybyoggrowbrgywrborwggybrbwororbwborgowryby

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

// Function prototypes

// User input fuctions
void getColors(char* colorArr);
bool isColor(char input);

// Cube creation and color checking functions
void createCube(Cube* pCube, char* colors);
PieceType checkPieceType(int index);
void assignPieceColors(Color* pXCol, Color* pYCol, Color* pZCol, int pieceNum, char* colors);
void assignPieceCoords(int* pX, int* pY, int* pZ, int pieceNum);
Color abbreiveToColor(char colorAbreive);
Color getOpposite(Color squareColor);

// Cube manipulation
void rotateFrontFace(Cube* pCube, bool isCntr);
void rotateBackFace(Cube* pCube, bool isCntr);
void rotateLeftFace(Cube* pCube, bool isCntr);
void rotateRightFace(Cube* pCube, bool isCntr);
void rotateTopFace(Cube* pCube, bool isCntr);
void rotateBottomFace(Cube* pCube, bool isCntr);
void rotateMidX(Cube* pCube, bool isCntr);
void rotateMidY(Cube* pCube, bool isCntr);
void rotateMidZ(Cube* pCube, bool isCntr);
void turnX(Cube* pCube, bool isCntr);
void turnY(Cube* pCube, bool isCntr);
void turnZ(Cube* pCube, bool isCntr);

// First layer cross functions
void solveFirstLayerCross(Cube* pCube);
void locateFirstLayerEdges(Cube* pCube, Piece edgePieces[], Color edgeColor);
bool edgeInDaisy(Cube* pCube, Piece edge, Color oppColor);
void daisyTop(Cube* pCube, Piece piece, Color oppColor);
void daisyMid(Cube* pCube, Piece piece, Color oppColor);
void daisyBottom(Cube* pCube, Piece piece, Color oppColor);
void daisyToCross(Cube* pCube, Color oppColor);

// First layer corners functions
void solveFirstLayerCorners(Cube* pCube);
void locateFirstLayerCorners(Cube* pCube, Piece faceCorners[], Color cornerColor);
bool firstLayerCornerInPlace(Cube* pCube, Piece corner, Color color);
void putBottomLeftCornerOnTop(Cube* pCube, Piece piece, Color color);
void putBottomRightCornerOnTop(Cube* pCube, Piece piece, Color color);

// Matrix rotation
void rotateMatClck(Piece face[NUM_PIECES_IN_ROW][NUM_PIECES_IN_ROW]);
void rotateMatCntr(Piece face[NUM_PIECES_IN_ROW][NUM_PIECES_IN_ROW]);

// Cube printing
void printCube(Cube* pCube);

int main(int argc, const char * argv[]) {
    char colorArr[NUM_SQUARES];
    Cube rubiks;
    
    // Get user input
    getColors(colorArr);
    createCube(&rubiks, colorArr);
    printCube(&rubiks);
    solveFirstLayerCross(&rubiks);
    printCube(&rubiks);
    solveFirstLayerCorners(&rubiks);
    printCube(&rubiks);
    
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

// Cube creation functions

/**
 * Builds the structure for a Rubik's cube
 *
 * @param pCube
 * Pointer to an uninitialized cube
 */
void createCube(Cube* pCube, char* colors)
{
    int xCoord = DNE, yCoord = DNE, zCoord = DNE;
    Color xCol, yCol, zCol;
    PieceType type;
    
    // Create 26 Rubik's Pieces
    for (int i = 0; i < NUM_PIECES; ++i)
    {
        // Get the piece type based on position index
        type = checkPieceType(i);
        assignPieceCoords(&xCoord, &yCoord, &zCoord, i);
        assignPieceColors(&xCol, &yCol, &zCol, i, colors);
        
        // Create a piece based on the data
        Piece piece = {type, i, xCoord, yCoord, zCoord, xCol, yCol, zCol};
        xCoord = DNE;
        yCoord = DNE;
        zCoord = DNE;
        
        // Insert the piece in the cube's piece array
        pCube->pieces[i] = piece;
    }
}

/**
 * @param pieceNum
 * The index of the piece in pieces of a Cube struct
 *
 * @return
 * The enumeration for the type of the piece
*/
PieceType checkPieceType(int pieceNum)
{
    // Check if piece is edge piece
    for (int i = 0; i < NUM_EDGE; i++) {

        // If position is a edge position
       if (EDGE_POS[i] == pieceNum)
           return EDGE;
    }
    
    // Check if piece is corner piece
    for (int i = 0; i < NUM_CORNER; i++) {

        // If position is a edge position
       if (CORNER_POS[i] == pieceNum)
           return CORNER;
    }
    
    // Check if piece is center piece
    for (int i = 0; i < NUM_CENTER; i++) {

        // If position is a edge position
       if (CENTER_POS[i] == pieceNum)
           return CENTER;
    }
    
    return NONE;
}

/**
 * Assigns the x, y and  colors to a Piece structure based on user input
 *
 * @param pXCol
 * Pointer to a varaiable holding piece's x face color
 *
 * @param pYCol
 * Pointer to a variable holding piece's y face color
 *
 * @param pZCol
 * Pointer to a variable holding piece's z face color
 *
 * @param pieceNum
 * The piece's number in a Cube structure's pieces array
 *
 * @param colors
 * An array of user inputed characters corresponding to the colors on each face
 */
void assignPieceColors(Color* pXCol, Color* pYCol, Color* pZCol, int pieceNum, char* colors)
{
    char xColAbb, yColAbb, zColAbb;
    
    // Check if current piece has an X color
    if (X_INDEXES[pieceNum] == DNE)
    {
        *pXCol = UNDEFINED;
    }
    // Piece has an X color
    else
    {
        // Get the color abbreiviation
        xColAbb = colors[X_INDEXES[pieceNum]];
        // Convert the abbreviation to a color
        *pXCol = abbreiveToColor(xColAbb);
    }
    
    // Check if current piece has an Y color
    if (Y_INDEXES[pieceNum] == DNE)
    {
        *pYCol = UNDEFINED;
    }
    // Piece has an Y color
    else
    {
        // Get the color abbreiviation
        yColAbb = colors[Y_INDEXES[pieceNum]];
        // Convert the abbreviation to a color
        *pYCol = abbreiveToColor(yColAbb);
    }
    
    // Check if current piece has an Z color
    if (Z_INDEXES[pieceNum] == DNE)
     {
         *pZCol = UNDEFINED;
     }
    // Piece has an Z color
     else
     {
         // Get the color abbreiviation
         zColAbb = colors[Z_INDEXES[pieceNum]];
         // Convert the abbreviation to a color
         *pZCol = abbreiveToColor(zColAbb);
     }
}

/**
 * Assigns the x, y, and z coordinates of a piece based on its index
 *
 * @param pX
 * Pointer to variable storing piece's x coordinate
 *
 * @param pY
 * Pointer to variable storing piece's y coordinate
 *
 * @param pZ
 * Pointer to variable storing piece's z coordinate
 *
 * @param pieceNum
 * The index of the piece in the pieces array of a cube structure
 */
void assignPieceCoords(int* pX, int* pY, int* pZ, int pieceNum)
{

    // Assign x coordinate
    // Check if piece is on left face
    for (int j = 0; j < NUM_PIECES_ON_FACE; ++j)
    {
        if (pieceNum == LEFT_POS[j])
        {
            *pX = 0;
            break;
        }
    }
    
    // If not on left face, check if piece is in middle layer
    if (*pX != 0)
    {
        for (int j = 0; j < NUM_PIECES_ON_FACE; ++j)
        {
            if (pieceNum == X_MID[j])
            {
                *pX = 1;
                break;
            }
        }
    }
    
    // If not on left face or middle layer, piece is on right face
    if (*pX != 0 & *pX != 1)
    {
        *pX = 2;
    }
    
    // Assign y coordinate
    // Check if piece is on back face
    for (int j = 0; j < NUM_PIECES_ON_FACE; ++j)
    {
        if (pieceNum == BACK_POS[j])
        {
            *pY = 0;
            break;
        }
    }
    
    // If not on back face, check if piece is in middle layer
    if (*pY != 0)
    {
        for (int j = 0; j < NUM_PIECES_ON_FACE; ++j)
        {
            if (pieceNum == Y_MID[j])
            {
                *pY = 1;
                break;
            }
        }
    }
    
    // If not on back or middle layer, piece is on front face
    if (*pY != 0 && *pY != 1)
    {
        *pY = 2;
    }
    
    
    
    // Assign z coordinate
    // Check if piece is on top face
    for (int j = 0; j < NUM_PIECES_ON_FACE; ++j)
    {
        if (pieceNum == TOP_POS[j])
        {
            *pZ = 0;
            break;
        }
    }
    
    // If not on top face, check if piece is on middle layer
    if (*pZ != 0)
    {
        for (int j = 0; j < NUM_PIECES_ON_FACE; ++j)
        {
            if (pieceNum == Z_MID[j])
            {
                *pZ = 1;
                break;
            }
        }
    }
    
    // If not on top face or middle layer, piece on bottom face
    if (*pZ != 0 && *pZ != 1)
    {
        *pZ = 2;
    }
}

/**
 * Converts a color abbreiviation to a Color enum
 *
 * @param colorAbreive
 * The abbreiviation of a color
 *
 * @return
 * A Color enumeration
 */
Color abbreiveToColor(char colorAbreive)
{
    // Return the correct color based on the abbreiviation
    switch(colorAbreive)
    {
        case 'r':
            return RED;
        case 'g':
            return GREEN;
        case 'o':
            return ORANGE;
        case 'b':
            return BLUE;
        case 'w':
            return WHITE;
        case 'y':
            return YELLOW;
        default:
            return UNDEFINED;
    }
}
/**
 * Gets the opposite color of a square on a rubiks cube
 *
 * @return
 *  The opposite color
 */
Color getOpposite(Color squareColor)
{
    switch(squareColor)
    {
        case WHITE:
            return YELLOW;
        case YELLOW:
            return WHITE;
        case ORANGE:
            return RED;
        case RED:
            return ORANGE;
        case BLUE:
            return GREEN;
        case GREEN:
            return BLUE;
        default:
            return UNDEFINED;
    }
}

// Cube manipulation functions

/**
 * Rotates the front face of the cube 90 degrees
 *
 * @param pCube
 * Pointer to a cube structure
 *
 * @param isCntr
 * Specifies the direction of the rotation
 */
void rotateFrontFace(Cube* pCube, bool isCntr)
{
    Piece face[3][3];
    Color temp;
    
    // Populate matrix
    for (int i = 0; i < NUM_PIECES_ON_FACE; ++i)
    {
        if (i > 5)
        {
            face[2][i - 6] = pCube->pieces[FRONT_POS[i]];
        }
        else if (i > 2)
        {
            face[1][i - 3] = pCube->pieces[FRONT_POS[i]];
        }
        else
        {
            face[0][i] = pCube->pieces[FRONT_POS[i]];
        }
    }
    
    // Rotate matrix
    if (isCntr)
    {
        rotateMatCntr(face);
    }
    else
    {
        rotateMatClck(face);
    }
    
    // Repopulate pieces[] with the rotated face
    for (int i = 0; i < NUM_PIECES_ON_FACE; ++i)
    {
        if (i > 5)
        {
            pCube->pieces[FRONT_POS[i]] = face[2][i - 6];
        }
        else if (i > 2)
        {
            pCube->pieces[FRONT_POS[i]] = face[1][i - 3];
        }
        else
        {
            pCube->pieces[FRONT_POS[i]] = face[0][i];
        }
        
        // Correct color orientation
        temp = pCube->pieces[FRONT_POS[i]].x;
        pCube->pieces[FRONT_POS[i]].x = pCube->pieces[FRONT_POS[i]].z;
        pCube->pieces[FRONT_POS[i]].z = temp;
        
    }
}

/**
 * Rotates the front face of the cube 90 degrees
 *
 * @param pCube
 * Pointer to a cube structure
 *
 * @param isCntr
 * Specifies the direction of the rotation
 */
void rotateBackFace(Cube* pCube, bool isCntr)
{
    Piece face[3][3];
    Color temp;
    
    // Populate matrix
    for (int i = 0; i < NUM_PIECES_ON_FACE; ++i)
    {
        if (i > 5)
        {
            face[2][i - 6] = pCube->pieces[BACK_POS[i]];
        }
        else if (i > 2)
        {
            face[1][i - 3] = pCube->pieces[BACK_POS[i]];
        }
        else
        {
            face[0][i] = pCube->pieces[BACK_POS[i]];
        }
    }
    
    // Rotate matrix
    if (isCntr)
    {
        rotateMatCntr(face);
    }
    else
    {
        rotateMatClck(face);
    }
    
    // Repopulate pieces[] with the rotated face
    for (int i = 0; i < NUM_PIECES_ON_FACE; ++i)
    {
        if (i > 5)
        {
            pCube->pieces[BACK_POS[i]] = face[2][i - 6];
        }
        else if (i > 2)
        {
            pCube->pieces[BACK_POS[i]] = face[1][i - 3];
        }
        else
        {
            pCube->pieces[BACK_POS[i]] = face[0][i];
        }
        
        // Correct color orientation
        temp = pCube->pieces[BACK_POS[i]].x;
        pCube->pieces[BACK_POS[i]].x = pCube->pieces[BACK_POS[i]].z;
        pCube->pieces[BACK_POS[i]].z = temp;
    }
}

/**
 * Rotates the left face of the cube 90 degrees
 *
 * @param pCube
 * Pointer to a cube structure
 *
 * @param isCntr
 * Specifies the direction of the rotation
 */
void rotateLeftFace(Cube* pCube, bool isCntr)
{
    Piece face[3][3];
    Color temp;
    
    // Populate matrix
    for (int i = 0; i < NUM_PIECES_ON_FACE; ++i)
    {
        if (i > 5)
        {
            face[2][i - 6] = pCube->pieces[LEFT_POS[i]];
        }
        else if (i > 2)
        {
            face[1][i - 3] = pCube->pieces[LEFT_POS[i]];
        }
        else
        {
            face[0][i] = pCube->pieces[LEFT_POS[i]];
        }
    }
    
    // Rotate matrix
    if (isCntr)
    {
        rotateMatCntr(face);
    }
    else
    {
        rotateMatClck(face);
    }
    
    // Repopulate pieces[] with the rotated face
    for (int i = 0; i < NUM_PIECES_ON_FACE; ++i)
    {
        if (i > 5)
        {
            pCube->pieces[LEFT_POS[i]] = face[2][i - 6];
        }
        else if (i > 2)
        {
            pCube->pieces[LEFT_POS[i]] = face[1][i - 3];
        }
        else
        {
            pCube->pieces[LEFT_POS[i]] = face[0][i];
        }
        
        // Correct color orientation
        temp = pCube->pieces[LEFT_POS[i]].y;
        pCube->pieces[LEFT_POS[i]].y = pCube->pieces[LEFT_POS[i]].z;
        pCube->pieces[LEFT_POS[i]].z = temp;
    }
}

/**
 * Rotates the right face of the cube 90 degrees
 *
 * @param pCube
 * Pointer to a cube structure
 *
 * @param isCntr
 * Specifies the direction of the rotation
 */
void rotateRightFace(Cube* pCube, bool isCntr)
{
    Piece face[3][3];
    Color temp;
    
    // Populate matrix
    for (int i = 0; i < NUM_PIECES_ON_FACE; ++i)
    {
        if (i > 5)
        {
            face[2][i - 6] = pCube->pieces[RIGHT_POS[i]];
        }
        else if (i > 2)
        {
            face[1][i - 3] = pCube->pieces[RIGHT_POS[i]];
        }
        else
        {
            face[0][i] = pCube->pieces[RIGHT_POS[i]];
        }
    }
    
    // Rotate matrix
    if (isCntr)
    {
        rotateMatCntr(face);
    }
    else
    {
        rotateMatClck(face);
    }
    
    // Repopulate pieces[] with the rotated face
    for (int i = 0; i < NUM_PIECES_ON_FACE; ++i)
    {
        if (i > 5)
        {
            pCube->pieces[RIGHT_POS[i]] = face[2][i - 6];
        }
        else if (i > 2)
        {
            pCube->pieces[RIGHT_POS[i]] = face[1][i - 3];
        }
        else
        {
            pCube->pieces[RIGHT_POS[i]] = face[0][i];
        }
        
        // Correct color orientation
        temp = pCube->pieces[RIGHT_POS[i]].y;
        pCube->pieces[RIGHT_POS[i]].y = pCube->pieces[RIGHT_POS[i]].z;
        pCube->pieces[RIGHT_POS[i]].z = temp;
    }
}

/**
 * Rotates the top face of the cube 90 degrees
 *
 * @param pCube
 * Pointer to a cube structure
 *
 * @param isCntr
 * Specifies the direction of the rotation
 */
void rotateTopFace(Cube* pCube, bool isCntr)
{
    Piece face[3][3];
    Color temp;
    
    // Populate matrix
    for (int i = 0; i < NUM_PIECES_ON_FACE; ++i)
    {
        if (i > 5)
        {
            face[2][i - 6] = pCube->pieces[TOP_POS[i]];
        }
        else if (i > 2)
        {
            face[1][i - 3] = pCube->pieces[TOP_POS[i]];
        }
        else
        {
            face[0][i] = pCube->pieces[TOP_POS[i]];
        }
    }
    
    // Rotate matrix
    if (isCntr)
    {
        rotateMatCntr(face);
    }
    else
    {
        rotateMatClck(face);
    }
    
    // Repopulate pieces[] with the rotated face
    for (int i = 0; i < NUM_PIECES_ON_FACE; ++i)
    {
        if (i > 5)
        {
            pCube->pieces[TOP_POS[i]] = face[2][i - 6];
        }
        else if (i > 2)
        {
            pCube->pieces[TOP_POS[i]] = face[1][i - 3];
        }
        else
        {
            pCube->pieces[TOP_POS[i]] = face[0][i];
        }
        
        // Correct color orientation
        temp = pCube->pieces[TOP_POS[i]].x;
        pCube->pieces[TOP_POS[i]].x = pCube->pieces[TOP_POS[i]].y;
        pCube->pieces[TOP_POS[i]].y = temp;
    }
}

/**
 * Rotates the bottom face of the cube 90 degrees
 *
 * @param pCube
 * Pointer to a cube structure
 *
 * @param isCntr
 * Specifies the direction of the rotation
 */
void rotateBottomFace(Cube* pCube, bool isCntr)
{
    Piece face[3][3];
    Color temp;
    
    // Populate matrix
    for (int i = 0; i < NUM_PIECES_ON_FACE; ++i)
    {
        if (i > 5)
        {
            face[2][i - 6] = pCube->pieces[BOTTOM_POS[i]];
        }
        else if (i > 2)
        {
            face[1][i - 3] = pCube->pieces[BOTTOM_POS[i]];
        }
        else
        {
            face[0][i] = pCube->pieces[BOTTOM_POS[i]];
        }
    }
    
    // Rotate matrix
    if (isCntr)
    {
        rotateMatCntr(face);
    }
    else
    {
        rotateMatClck(face);
    }
    
    // Repopulate pieces[] with the rotated face
    for (int i = 0; i < NUM_PIECES_ON_FACE; ++i)
    {
        if (i > 5)
        {
            pCube->pieces[BOTTOM_POS[i]] = face[2][i - 6];
        }
        else if (i > 2)
        {
            pCube->pieces[BOTTOM_POS[i]] = face[1][i - 3];
        }
        else
        {
            pCube->pieces[BOTTOM_POS[i]] = face[0][i];
        }
        
        // Correct color orientation
        temp = pCube->pieces[BOTTOM_POS[i]].x;
        pCube->pieces[BOTTOM_POS[i]].x = pCube->pieces[BOTTOM_POS[i]].y;
        pCube->pieces[BOTTOM_POS[i]].y = temp;
    }
}

/**
 * Rotates the middle layer of the cube perpendicular to x  90 degrees
 *
 * @param pCube
 * Pointer to a cube structure
 *
 * @param isCntr
 * Specifies the direction of the rotation
 */
void rotateMidX( Cube* pCube, bool isCntr)
{
    Piece face[3][3];
    Color temp;

    // Populate matrix
    for (int i = 0; i < NUM_PIECES_ON_FACE; ++i)
    {
        // Fill bottom row of matrix
        if (i > 5) // 8 7 6
        {
            face[2][i - 6] = pCube->pieces[X_MID[i]];
        }
        // No center piece exists in a middle layer
        else if (i == 4) // 4
        {
            continue;
        }
        // Fill middle row of matrix
        else if (i > 2) // 5 3
        {
            face[1][i - 3] = pCube->pieces[X_MID[i]];
        }
        // Fill top row of matrix
        else // 2 1 0
        {
            face[0][i] = pCube->pieces[X_MID[i]];
        }
    }
    
    // Rotate matrix
    if (isCntr)
    {
        rotateMatCntr(face);
    }
    else
    {
        rotateMatClck(face);
    }
    
    // Repopulate pieces[] with the rotated face
    for (int i = 0; i < NUM_PIECES_ON_FACE; ++i)
    {
        // Fill bottom row of Rubik's face
        if (i > 5)
        {
            pCube->pieces[X_MID[i]] = face[2][i - 6];
        }
        // No center piece exists in a middle layer
        else if (i == 4)
        {
            continue;
        }
        // Fill middle row of Rubik's face
        else if (i > 2)
        {
            pCube->pieces[X_MID[i]] = face[1][i - 3];
        }
        // Fill top row of Rubik's face
        else
        {
            pCube->pieces[X_MID[i]] = face[0][i];
        }
        
        // Correct color orientation
        temp = pCube->pieces[X_MID[i]].y;
        pCube->pieces[X_MID[i]].y = pCube->pieces[X_MID[i]].z;
        pCube->pieces[X_MID[i]].z = temp;
    }
}

/**
 * Rotates the middle layer of the cube perpendicular to y  90 degrees
 *
 * @param pCube
 * Pointer to a cube structure
 *
 * @param isCntr
 * Specifies the direction of the rotation
 */
void rotateMidY(Cube* pCube, bool isCntr)
{
    Piece face[3][3];
    Color temp;
    
    // Populate matrix
    for (int i = 0; i < NUM_PIECES_ON_FACE; ++i)
    {
        if (i > 5)
        {
            face[2][i - 6] = pCube->pieces[Y_MID[i]];
        }
        // No center piece exists in a middle layer
        else if (i == 4)
        {
            continue;
        }
        else if (i > 2)
        {
            face[1][i - 3] = pCube->pieces[Y_MID[i]];
        }
        else
        {
            face[0][i] = pCube->pieces[Y_MID[i]];
        }
    }
    
    // Rotate matrix
    if (isCntr)
    {
        rotateMatCntr(face);
    }
    else
    {
        rotateMatClck(face);
    }
    
    // Repopulate pieces[] with the rotated face
    for (int i = 0; i < NUM_PIECES_ON_FACE; ++i)
    {
        if (i > 5)
        {
            pCube->pieces[Y_MID[i]] = face[2][i - 6];
        }
        // No center piece exists in a middle layer
        else if (i == 4)
        {
            continue;
        }
        else if (i > 2)
        {
            pCube->pieces[Y_MID[i]] = face[1][i - 3];
        }
        else
        {
            pCube->pieces[Y_MID[i]] = face[0][i];
        }
        
        // Correct color orientation
        temp = pCube->pieces[Y_MID[i]].x;
        pCube->pieces[Y_MID[i]].x = pCube->pieces[Y_MID[i]].z;
        pCube->pieces[Y_MID[i]].z = temp;
    }
}

/**
 * Rotates the middle layer of the cube perpendicular to z  90 degrees
 *
 * @param pCube
 * Pointer to a cube structure
 *
 * @param isCntr
 * Specifies the direction of the rotation
 */
void rotateMidZ(Cube* pCube, bool isCntr)
{
    Piece face[3][3];
    Color temp;
    
    // Populate matrix
    for (int i = 0; i < NUM_PIECES_ON_FACE; ++i)
    {
        if (i > 5)
        {
            face[2][i - 6] = pCube->pieces[Z_MID[i]];
        }
        // No center piece exists in a middle layer
        else if (i == 4)
        {
            continue;
        }
        else if (i > 2)
        {
            face[1][i - 3] = pCube->pieces[Z_MID[i]];
        }
        else
        {
            face[0][i] = pCube->pieces[Z_MID[i]];
        }
    }
    
    // Rotate matrix
    if (isCntr)
    {
        rotateMatCntr(face);
    }
    else
    {
        rotateMatClck(face);
    }
    
    // Repopulate pieces[] with the rotated face
    for (int i = 0; i < NUM_PIECES_ON_FACE; ++i)
    {
        if (i > 5)
        {
            pCube->pieces[Z_MID[i]] = face[2][i - 6];
        }
        // No center piece exists in a middle layer
        else if (i == 4)
        {
            continue ;
        }
        else if (i > 2)
        {
            pCube->pieces[Z_MID[i]] = face[1][i - 3];
        }
        else
        {
            pCube->pieces[Z_MID[i]] = face[0][i];
        }
        
        // Correct color orientation
        temp = pCube->pieces[Z_MID[i]].x;
        pCube->pieces[Z_MID[i]].x = pCube->pieces[Z_MID[i]].y;
        pCube->pieces[Z_MID[i]].y = temp;
    }
}

/**
 * Turns the cube around the x axis 90 degrees
 *
 * @param pCube
 * Pointer to a cube structure
 *
 * @param isCntr
 * Specifies the direction of rotation
 */
void turnX(Cube* pCube, bool isCntr)
{
    // Rotate each face of the cube around the x axis
    rotateLeftFace(pCube, isCntr);
    rotateMidX(pCube, isCntr);
    rotateRightFace(pCube, isCntr);
}

/**
 * Turns the cube around the y axis 90 degrees
 *
 * @param pCube
 *  Pointer to a cube structure
 *
 * @param isCntr
 *  Specifies the direction of rotation
 */
void turnY(Cube* pCube, bool isCntr)
{
    // Rotate each face of the cube around the x axis
    rotateFrontFace(pCube, isCntr);
    rotateMidY(pCube, isCntr);
    rotateBackFace(pCube, isCntr);
}

/**
 * Turns the cube around the z axis 90 degrees
 *
 * @param pCube
 * Pointer to a cube structure
 *
 * @param isCntr
 * Specifies the direction of rotation
 */
void turnZ(Cube* pCube, bool isCntr)
{
    // Rotate each face of the cube around the x axis
    rotateTopFace(pCube, isCntr);
    rotateMidZ(pCube, isCntr);
    rotateBottomFace(pCube, isCntr);
}

/**
 * Rotates an n x n matrix 90 degrees counter clockwise
 *
 * @param face
 *  A 3 x 3 matrix of piece structures representing a face of a Rubik's cube
 */
void rotateMatCntr(Piece face[NUM_PIECES_IN_ROW][NUM_PIECES_IN_ROW])
{
    int tempNum, tempX, tempY, tempZ;
    
    // Number of cycles
    for (int i = 0; i < (NUM_PIECES_IN_ROW / 2 ); ++i)
    {
        // Group elements
        // Rotating matrix
        for (int j = i; j < (NUM_PIECES_IN_ROW - i - 1); ++j)
        {
            // Create temp for current element
            Piece temp = face[i][j];
            tempNum = temp.pieceNum;;
            tempX = temp.xCoord;;
            tempY = temp.yCoord;
            tempZ = temp.zCoord;
            
            // Rotate element
            face[i][j] = face[j][NUM_PIECES_IN_ROW - 1 - i];
            
            // Maintain pieceNum and coordinates
            face[i][j].pieceNum = tempNum;
            face[i][j].xCoord = tempX;
            face[i][j].yCoord = tempY;
            face[i][j].zCoord = tempZ;
            
            // Replace temporary variables
            tempNum = face[j][NUM_PIECES_IN_ROW - 1 - i].pieceNum;
            tempX = face[j][NUM_PIECES_IN_ROW - 1 - i].xCoord;
            tempY = face[j][NUM_PIECES_IN_ROW - 1 - i].yCoord;
            tempZ = face[j][NUM_PIECES_IN_ROW - 1 - i].zCoord;
            
            // Rotate next element
            face[j][NUM_PIECES_IN_ROW - 1 - i] = face[NUM_PIECES_IN_ROW - 1 - i][NUM_PIECES_IN_ROW - 1 - j];
            
            // Maintain pieceNum and coordinates
            face[j][NUM_PIECES_IN_ROW - 1 - i].pieceNum = tempNum;
            face[j][NUM_PIECES_IN_ROW - 1 - i].xCoord = tempX;
            face[j][NUM_PIECES_IN_ROW - 1 - i].yCoord = tempY;
            face[j][NUM_PIECES_IN_ROW - 1 - i].zCoord = tempZ;
            
            // Replace temporary variables
            tempNum = face[NUM_PIECES_IN_ROW  - 1 - i][NUM_PIECES_IN_ROW - 1 - j].pieceNum;
            tempX = face[NUM_PIECES_IN_ROW  - 1 - i][NUM_PIECES_IN_ROW - 1 - j].xCoord;
            tempY = face[NUM_PIECES_IN_ROW  - 1 - i][NUM_PIECES_IN_ROW - 1 - j].yCoord;
            tempZ = face[NUM_PIECES_IN_ROW  - 1 - i][NUM_PIECES_IN_ROW - 1 - j].zCoord;
            
            // Rotate next element
            face[NUM_PIECES_IN_ROW  - 1 - i][NUM_PIECES_IN_ROW - 1 - j] = face[NUM_PIECES_IN_ROW - 1 - j][i];

            // Maintain pieceNum and coordinates
            face[NUM_PIECES_IN_ROW  - 1 - i][NUM_PIECES_IN_ROW - 1 - j].pieceNum = tempNum;
            face[NUM_PIECES_IN_ROW  - 1 - i][NUM_PIECES_IN_ROW - 1 - j].xCoord = tempX;
            face[NUM_PIECES_IN_ROW  - 1 - i][NUM_PIECES_IN_ROW - 1 - j].yCoord = tempY;
            face[NUM_PIECES_IN_ROW  - 1 - i][NUM_PIECES_IN_ROW - 1 - j].zCoord = tempZ;
            
            // Replace temporary variables
            tempNum = face[NUM_PIECES_IN_ROW - 1 - j][i].pieceNum;
            tempX = face[NUM_PIECES_IN_ROW - 1 - j][i].xCoord;
            tempY = face[NUM_PIECES_IN_ROW - 1 - j][i].yCoord;
            tempZ = face[NUM_PIECES_IN_ROW - 1 - j][i].zCoord;
            
            // Rotate last element in group
            face[NUM_PIECES_IN_ROW - 1 - j][i] = temp;
            
            // Maintain pieceNum and coordinates
            face[NUM_PIECES_IN_ROW - 1 - j][i].pieceNum = tempNum;
            face[NUM_PIECES_IN_ROW - 1 - j][i].xCoord = tempX;
            face[NUM_PIECES_IN_ROW - 1 - j][i].yCoord = tempY;
            face[NUM_PIECES_IN_ROW - 1 - j][i].zCoord = tempZ;
        }
    }
}

/**
 * Rotates an n x n matrix 90 degrees clockwise
 *
 * @param face
 *  A 3 x 3 matrix of piece structures representing a face of a Rubik's cube
 */
void rotateMatClck(Piece face[NUM_PIECES_IN_ROW][NUM_PIECES_IN_ROW])
{
    // Rotate the matrix 270 degrees clockwise
    rotateMatCntr(face);
    rotateMatCntr(face);
    rotateMatCntr(face);
}


// Cube solving functions

// First Layer Cross
/**
 * Solves the cross on the first layer of the cube
 *
 * @param pCube
 * Pointer to a cube struct
 */
void solveFirstLayerCross(Cube* pCube)
{
    Piece piece;
    
    // Get center piece color of top face
    Color faceColor = pCube->pieces[TOP_CENTER].z;
    
    // Get opposite color
    Color oppColor = getOpposite(faceColor);
    
    // Create an array holding edge pieces of desired color
    Piece edgePieces[NUM_EDGES_ON_FACE];
    locateFirstLayerEdges(pCube, edgePieces, oppColor);
    
    // Loop through edgePieces array
    for (int i = 0; i < NUM_EDGES_ON_FACE; ++i)
    {
        piece = edgePieces[i];
        // Solve daisy
        // Current edge is not in daisy
        if (!(edgeInDaisy(pCube, piece, oppColor)))
        {
            // Piece is on top face but orriented incorrectly
            if (piece.zCoord == 0 && piece.z != oppColor)
            {
                daisyTop(pCube, piece, oppColor);
                
            }
                // Piece is in middle layer
            else if (piece.zCoord == 1)
            {
                daisyMid(pCube, piece, oppColor);
            }
            // Piece is in bottom layer
            else
            {
                daisyBottom(pCube, piece, oppColor);
            }
            // Relocate edges
            if (i < NUM_EDGES_ON_FACE - 1)
            {
                locateFirstLayerEdges(pCube, edgePieces, oppColor);
            }
        }
    }
    // Solve cross
    daisyToCross(pCube, oppColor);
}

/**
 * Locates the edge pieces that have a square the same color as the center of the cross
 *
 * @param pCube
 *  A pointer to a Cube structure
 *
 * @param edgePieces
 * An array holding the edge pieces
 *
 * @param edgeColor
 *  The desired color
 */
void locateFirstLayerEdges(Cube* pCube, Piece edgePieces[], Color edgeColor)
{
    Piece piece;
    int cntr = 0;
    
    // Iterate through all edge pieces
    for (int i = 0; i < NUM_EDGE; ++i)
    {
        // Assign piece to an edge piece on cube
        piece = pCube->pieces[EDGE_POS[i]];
        
        // Check if piece has desired color
        if (piece.x == edgeColor || piece.y == edgeColor || piece.z == edgeColor)
        {
            // Add piece to array holding edge pieces containg desired color
            edgePieces[cntr] = piece;
            
            // Advance counter
            ++cntr;
            
            // Break loop if all edge pieces of desired color were found
            if (cntr >= NUM_EDGES_ON_FACE)
            {
                break;
            }
        }
    }
}

/**
 * Checks if edge piece is in the top daisy
 *
 * @param pCube
 * Pointer to a Cube structure
 *
 * @param edge
 * The edge piece to check
 *
 * @return
 * True if the piece is in the daisy
 * False if the piece is not in the daisy
 */
bool edgeInDaisy(Cube* pCube, Piece edge, Color oppColor)
{
    
    // Check that edge is an edge piece
    if (edge.pieceType == EDGE)
    {
        // Check if it the piece is in a daisy and oriented correctly
        if ((edge.pieceNum == TOP_BACK_EDGE || edge.pieceNum == TOP_LEFT_EDGE ||
             edge.pieceNum == TOP_RIGHT_EDGE || edge.pieceNum == TOP_FRONT_EDGE)
            && edge.z == oppColor)
        {
            return true;
        }
    }
    
    // Piece not in correct position or not an edge piece
    return false;
}

/**
 * Places an edge piece in the daisy if the piece is located in the top layer
 *
 * @param pCube
 * Pointer to a cube structure
 *
 * @param piece
 * The piece to be placed in the daisy
 *
 * @param oppColor
 * The opposite color to the daisy center
 */
void daisyTop(Cube* pCube, Piece piece, Color oppColor)
{
    // Put piece in daisy if originally on back face
    if (piece.yCoord == 0)
    {
        // Move out of back face
        rotateBackFace(pCube, false);
        
        // Rotate top face until edge location not occupied by a daisy edge
        // Compare color of edge with the color of the piece it will replace
        while (oppColor == pCube->pieces[TOP_RIGHT_EDGE].z)
        {
            // Rotate the top face of the cube if a daisy piece is in that position
            rotateTopFace(pCube, true);
        }
        // Put piece in daisy
        rotateRightFace(pCube, false);
    }
    // Put piece in daisy if originally on front face
    else if (piece.yCoord == 2)
    {
        // Move out of top face
        rotateFrontFace(pCube, true);
        // Rotate top face until edge location not occupied by a daisy edge
        // Compare color of edge with the color of the piece it will replace
        while (oppColor == pCube->pieces[TOP_LEFT_EDGE].z)
        {
            // Rotate the top face of the cube if a daisy piece is in that position
            rotateTopFace(pCube, true);
        }
        // Put piece in daisy
        rotateLeftFace(pCube, true);
    }
    // Put Piece in daisy if originally on right/left face
    else
    {
        // Piece originally on left face
        if (piece.xCoord == 0)
        {
            // Move piece out of top face
            rotateLeftFace(pCube, false);
            
            // Rotate top face until edge location not occupied by a daisy edge
            // Compare color of edge with the color of the piece it will replace
            while (oppColor == pCube->pieces[TOP_FRONT_EDGE].z)
            {
                // Rotate the top face of the cube if a daisy piece is in that position
                rotateTopFace(pCube, true);
            }
            // Put piece in daisy
            rotateFrontFace(pCube, false);
        }
        // Piece originally on right face
        else
        {
            // Move piece out of top face
            rotateRightFace(pCube, true);
            
            // Rotate top face until edge location not occupied by a daisy edge
            while (oppColor == pCube->pieces[TOP_BACK_EDGE].z)
            {
                rotateTopFace(pCube, true);
            }
            // Put piece in daisy
            rotateBackFace(pCube, true);
        }
    }
}

/**
 * Puts an edge piece in the daisy if the piece is located in the mid layer
 *
 * @param pCube
 * Pointer to a cube structure
 *
 * @param piece
 * The piece to be placed in the daisy
 *
 * @param oppColor
 * The opposite color to the daisy center
 */
void daisyMid(Cube* pCube, Piece piece, Color oppColor)
{
    // Desired color is on right or left face
    if (piece.x == oppColor)
    {
        // Desired color is on left face
        if (piece.xCoord == 0)
        {
            // Desired piece is on back face
            if (piece.yCoord == 0)
            {
                // Rotate top face until edge edge location not occupied with a daisy edge
                while (oppColor == pCube->pieces[TOP_BACK_EDGE].z)
                {
                    rotateTopFace(pCube, true);
                }
                // Put piece in daisy
                rotateBackFace(pCube, false);
            }
            // Desired piece is on front face
            else
            {
                // Rotate top face until edge edge location not occupied with a daisy edge
                while (oppColor == pCube->pieces[TOP_FRONT_EDGE].z)
                {
                    rotateTopFace(pCube, true);
                }
                // Put piece in daisy
                rotateFrontFace(pCube, false);
            }
        }
        // Desired color is on right face
        else
        {
            // Desired piece is on back face
            if (piece.yCoord == 0)
            {
                // Rotate top face until edge location not occupied with a daisy edge
                while (oppColor == pCube->pieces[TOP_BACK_EDGE].z)
                {
                    rotateTopFace(pCube, true);
                }
                // Put piece in daisy
                rotateBackFace(pCube, true);
            }
            // Desired piece is on front face
            else
            {
                // Rotate top face until edge location not occupied with a daisy edge
                while (oppColor == pCube->pieces[TOP_FRONT_EDGE].z)
                {
                    rotateTopFace(pCube, true);
                }
                // Put piece in daisy
                rotateFrontFace(pCube, true);
            }
        }
    }
    // Desired color is on front or back face
    else
    {
        // Desired color is on back face
        if (piece.yCoord == 0)
        {
            // Desired piece is on left face
            if (piece.xCoord == 0)
            {
                // Rotate top until edge location not occupied with daisy edge
                while(oppColor == pCube->pieces[TOP_LEFT_EDGE].z)
                {
                    rotateTopFace(pCube, true);
                }
                // Put piece in daisy
                rotateLeftFace(pCube, false);
            }
            // Desired piece is on right face
            else
            {
                // Rotate top until edge location not occupied with daisy edge
                while(oppColor == pCube->pieces[TOP_RIGHT_EDGE].z)
                {
                    rotateTopFace(pCube, true);
                }
                // Put piece in daisy
                rotateRightFace(pCube, false);
            }
        }
        // Desired color is on front face
        else
        {
           // Desired piece is on left face
            if (piece.xCoord == 0)
            {
                // Rotate top until edge location not occupied with daisy edge
                while(oppColor == pCube->pieces[TOP_LEFT_EDGE].z)
                {
                    rotateTopFace(pCube, true);
                }
                // Put piece in daisy
                rotateLeftFace(pCube, true);
            }
            // Desired piece is on right face
            else
            {
                // Rotate top until edge location not occupied with daisy edge
                while(oppColor == pCube->pieces[TOP_RIGHT_EDGE].z)
                {
                    rotateTopFace(pCube, true);
                }
                // Put piece in daisy
                rotateRightFace(pCube, true);
            }
        }
    }
}

/**
 * @param pCube
 * Pointer to a cube structure
 *
 * @param piece
 * The piece to be placed in the daisy
 *
 * @param oppColor
 * The opposite color to the center of the daisy
 */
void daisyBottom(Cube* pCube, Piece piece, Color oppColor)
{
    // Piece is oriented incorrectly
    if (piece.z != oppColor)
    {
        // Piece is on left face
        if (piece.xCoord == 0)
        {
            // Rotate top until edge location not occupied with daisy edge
            while (oppColor == pCube->pieces[TOP_LEFT_EDGE].z)
            {
                rotateTopFace(pCube, true);
            }
            // Place piece in middle layer
            rotateLeftFace(pCube, true);
            // Place piece in daisy
            daisyMid(pCube, piece, oppColor);
        }
        // Piece is on front or back face
        else if (piece.xCoord == 1)
        {
            // Piece is on back face
            if (piece.yCoord == 0)
            {
                // Rotate top until edge location not occupied with daisy edge
                while (oppColor == pCube->pieces[TOP_BACK_EDGE].z)
                {
                    rotateTopFace(pCube, true);
                }
                // Place piece in middle layer
                rotateBackFace(pCube, true);
                // Place piece in daisy
                daisyMid(pCube, piece, oppColor);
            }
            // Piece is on front face
            else
            {
                // Rotate top until edge location not occupied with daisy edge
                while (oppColor == pCube->pieces[TOP_FRONT_EDGE].z)
                {
                    rotateTopFace(pCube, true);
                }
                // Place piece in middle layer
                rotateFrontFace(pCube, true);
                // Place piece in daisy
                daisyMid(pCube, piece, oppColor);
            }
        }
        // Piece is on right face
        else
        {
            // Rotate top until edge location not occupied with daisy edge
            while (oppColor == pCube->pieces[TOP_RIGHT_EDGE].z)
            {
                rotateTopFace(pCube, true);
            }
            // Place piece in middle layer
            rotateRightFace(pCube, true);
            // Place piece in daisy
            daisyMid(pCube, piece, oppColor);
        }
    }
    // Piece is oriented correctly
    else
    {
        // Piece is on left face
        if (piece.xCoord == 0)
        {
            // Rotate top until edge location not occupied with daisy edge
            while (oppColor == pCube->pieces[TOP_LEFT_EDGE].z)
            {
                rotateTopFace(pCube, true);
            }
            // Place piece in daisy
            rotateLeftFace(pCube, true);
            rotateLeftFace(pCube, true);
        }
        // Piece is on front or back face
        else if (piece.xCoord == 1)
        {
            // Piece is on back face
            if (piece.yCoord == 0)
            {
                // Rotate top until edge location not occupied with daisy edge
                while (oppColor == pCube->pieces[TOP_BACK_EDGE].z)
                {
                    rotateTopFace(pCube, true);
                }
                // Place piece in daisy
                rotateBackFace(pCube, true);
                rotateBackFace(pCube, true);
            }
            // Piece is on front face
            else
            {
                // Rotate top until edge location not occupied with daisy edge
                while (oppColor == pCube->pieces[TOP_FRONT_EDGE].z)
                {
                    rotateTopFace(pCube, true);
                }
                // Place piece in daisy
                rotateFrontFace(pCube, true);
                rotateFrontFace(pCube, true);
            }
        }
        // Piece is on right face
        else
        {
            // Rotate top until edge location not occupied with daisy edge
            while (oppColor == pCube->pieces[TOP_RIGHT_EDGE].z)
            {
                rotateTopFace(pCube, true);
            }
            // Place piece in daisy
            rotateRightFace(pCube, true);
            rotateRightFace(pCube, true);
        }
    }
}

/**
 * Moves edge pieces from top daisy to bottom cross
 *
 * @param pCube
 * Pointer to a cube structure
 */
void daisyToCross(Cube* pCube, Color oppColor)
{
    for (int i = 0; i < NUM_EDGES_ON_FACE; ++i)
    {
        if (i == 0)
        {
            // Check that top back edge piece is on correct face
            while (pCube->pieces[TOP_BACK_EDGE].y != pCube->pieces[BACK_CENTER].y)
            {
                // Rotate top until matching piece found
                rotateTopFace(pCube, true);
            }
            // Put piece in place
            rotateBackFace(pCube, true);
            rotateBackFace(pCube, true);
        }
        else if (i == 1)
        {
           // Check that top left edge piece is on correct face and that piece is a cross piece
            while ((pCube->pieces[TOP_LEFT_EDGE].x != pCube->pieces[LEFT_CENTER].x) || pCube->pieces[TOP_LEFT_EDGE].z != oppColor)
            {
                // Rotate top until matching piece found
               rotateTopFace(pCube, true);
            }
            // Put piece in place
            rotateLeftFace(pCube, true);
            rotateLeftFace(pCube, true);
        }
        else if (i == 2)
        {
           // Check that top right edge piece is on correct face
            while ((pCube->pieces[TOP_RIGHT_EDGE].x != pCube->pieces[RIGHT_CENTER].x) || pCube->pieces[TOP_RIGHT_EDGE].z != oppColor)
            {
                // Rotate top until matching piece found
               rotateTopFace(pCube, true);
            }
            // Put piece in place
            rotateRightFace(pCube, true);
            rotateRightFace(pCube, true);
        }
        else
        {
           // Check that top front edge piece is on correct face
            while ((pCube->pieces[TOP_FRONT_EDGE].y != pCube->pieces[FRONT_CENTER].y) || pCube->pieces[TOP_FRONT_EDGE].z != oppColor)
            {
                // Rotate top until matching piece found
               rotateTopFace(pCube, true);
            }
            // Put piece in place
            rotateFrontFace(pCube, true);
            rotateFrontFace(pCube, true);
        }
    }
}

// First layer corners
void solveFirstLayerCorners(Cube* pCube)
{
    Piece piece;

    // Get center piece color of bottom face
    Color color = pCube->pieces[BOTTOM_CENTER].z;
    
    // Re-orient cube so bottom is on top
    turnY(pCube, true);
    turnY(pCube, true);

    // Create an array holding corner pieces with desired color
    Piece cornerPieces[NUM_CORNERS_ON_FACE];
    locateFirstLayerCorners(pCube, cornerPieces, color);
    
    // Loop through corner piece array
    for (int i = 0; i < NUM_CORNERS_ON_FACE; ++i)
    {
    
        piece = cornerPieces[i];
        
        // If piece is not in the correct positon
        if(!(firstLayerCornerInPlace(pCube, piece, color)))
        {
            // Piece on top layer and oriented incorrectly
            if (piece.zCoord == 0)
            {
                // Piece is on left face
                if (piece.xCoord == 0)
                {
                    // Piece is on back face, rotate to front face
                    if (piece.yCoord == 0)
                    {
                        turnZ(pCube, true);
                    }
                    // Move piece to bottom right front corner
                    rotateLeftFace(pCube, false);
                    rotateBottomFace(pCube, true);
                    rotateLeftFace(pCube, true);
                    
                    // Reassign piece with piece in bottom right front corner
                    piece = pCube->pieces[BOTTOM_RIGHT_FRONT_CORNER];
                }
                // Piece is on right face
                else
                {
                    // Piece is on back face, rotate to front face
                    if (piece.yCoord == 0)
                    {
                        turnZ(pCube, false);
                    }
                    // Move piece to bottom left front corner
                    rotateRightFace(pCube, false);
                    rotateBottomFace(pCube, false);
                    rotateRightFace(pCube, true);
                    
                    // Reassign piece with piece in bottom left front corner
                    piece = pCube->pieces[BOTTOM_LEFT_FRONT_CORNER];
                }
            }
            
            // Piece is on left face
            if (piece.xCoord == 0)
            {
                // Place piece in correct position
                putBottomLeftCornerOnTop(pCube, piece, color);
            }
            // Piece is on right face
            else
            {
                // Place piece in correct position
                putBottomRightCornerOnTop(pCube, piece, color);
            }
        }
        if (i < NUM_CORNERS_ON_FACE - 1)
        {
            locateFirstLayerCorners(pCube, cornerPieces, color);
        }

    }
}

/**
 * Locates the corner pieces that have a square with a specified color
 *
 * @param pCube
 *  A pointer to a Cube structure
 *
 * @param faceCorners
 *  A pointer to the first element of an array holding the edge pieces
 *
 * @param cornerColor
 *  The desired color
 */
void locateFirstLayerCorners(Cube* pCube, Piece faceCorners[], Color cornerColor)
{
    Piece * piece;
    int cntr = 0;
    
    // Iterate through all corner pieces
    for (int i = 0; i < NUM_CORNER; ++i)
    {
        // Assign piece to a corner piece on cube
        piece = &(pCube->pieces[CORNER_POS[i]]);
        
        // Check if piece has desired color
        if (piece->x == cornerColor || piece->y == cornerColor || piece->z == cornerColor)
        {
            faceCorners[cntr] = *piece;
            ++cntr;
            
            if (cntr >= NUM_CORNERS_ON_FACE)
            {
                break;
            }
        }
    }
    // Place corners that are in correct position at front of the array
    for (int i = 0; i < NUM_CORNERS_ON_FACE; ++i)
    {
        Piece temp = faceCorners[i];
        // Check if piece is in correct position
        if (firstLayerCornerInPlace(pCube, temp, cornerColor))
        {
            // Move all pieces preceding one index back
            for (int j = i; j > 0; --j)
            {
                faceCorners[j] = faceCorners[j - 1];
            }
            // Move piece to the front of the array
            faceCorners[0] = temp;
        }
    }
}

/**
 * Checks if a bottom corner position is occupied by the correct piece and oriented correctly
 *
 * @param pCube
 * Pointer to a Cube structure
 *
 * @param corner
 * The corner piece that is being checked
 *
 * @param color
 * The center piece color of the bottom face
 *
 * @return
 * True if the piece is correctly oriented in the correct corner position of the bottom layer
 * False if it is not in the corect positon or orientation
 */
bool firstLayerCornerInPlace(Cube* pCube, Piece corner, Color color)
{
    // Piece is in top layer
    if (corner.zCoord == 0)
    {
        // Correct color is facing up
        if (corner.z == color)
        {
            // Piece is on back face
            if (corner.yCoord == 0)
            {
                // Piece is on left face
                if (corner.xCoord == 0)
                {
                    // Check that x color is correct
                    if (corner.x == pCube->pieces[LEFT_CENTER].x)
                    {
                        // Check that y color is correct
                        if (corner.y == pCube->pieces[BACK_CENTER].y)
                        {
                            // Piece is in correct position
                            return true;
                        }
                    }
                }
                // Piece is on right face
                else
                {
                   // Check that x color is correct
                    if (corner.x == pCube->pieces[RIGHT_CENTER].x)
                    {
                        // Check that y color is correct
                        if (corner.y == pCube->pieces[BACK_CENTER].y)
                        {
                            // Piece is in correct position
                            return true;
                        }
                    }
                }
            }
            // Piece is on front face
            else
            {
                // Piece is on left face
                if (corner.xCoord == 0)
                {
                    // Check that x color is correct
                    if (corner.x == pCube->pieces[LEFT_CENTER].x)
                    {
                        // Check that y color is correct
                        if (corner.y == pCube->pieces[FRONT_CENTER].y)
                        {
                            // Piece is in correct position
                            return true;
                        }
                    }
                }
                // Piece is on right face
                else
                {
                   // Check that x color is correct
                    if (corner.x == pCube->pieces[RIGHT_CENTER].x)
                    {
                        // Check that y color is correct
                        if (corner.y == pCube->pieces[FRONT_CENTER].y)
                        {
                            // Piece is in correct position
                            return true;
                        }
                    }
                }
            }
        }
    }
    
    // Piece is not in correct position
    return false;
}

/**
 * Places bottom left corner piece in the top left corner position
 *
 * @param pCube
 * Pointer to a Cube structure
 *
 * @param piece
 * The piece to be moved
 *
 * @param color
 * The color of the center piece of top face
 */
void putBottomLeftCornerOnTop(Cube* pCube, Piece piece, Color color)
{
    // Piece is on back face
    if (piece.yCoord == 0)
    {
        // Turn cube to put piece on front face
        turnZ(pCube, true);
        
        // Reassign piece
        piece = pCube->pieces[FRONT_LEFT_BOTTOM_CORNER];
        
        // Rotate top until the corner is in between two matching center tiles
        while ((piece.z == color && (piece.y != pCube->pieces[LEFT_CENTER].x))
               || (piece.y == color && (piece.x != pCube->pieces[LEFT_CENTER].x))
               || (piece.x == color && (piece.y != pCube->pieces[FRONT_CENTER].y)))
        {
            rotateBottomFace(pCube, true);
            turnZ(pCube, false);
            
        }
        // Desired color is facing down, rieorient so desired color facing front
        if (piece.z == color)
        {
            rotateFrontFace(pCube, true);
            rotateBottomFace(pCube, true);
            rotateFrontFace(pCube, false);
            rotateBottomFace(pCube, false);
            rotateBottomFace(pCube, false);
        }
        
        // Top center color is facing left
        if (piece.x == color)
        {
            // Turn so piece is faceing front
            turnZ(pCube, true);
            piece = pCube->pieces[FRONT_RIGHT_BOTTOM_CORNER];
            
            putBottomRightCornerOnTop(pCube, piece, color);
        }
        // Top center color is facing front
        else
        {
            // Put piece in place
            rotateBottomFace(pCube, true);
            rotateLeftFace(pCube, false);
            rotateBottomFace(pCube, false);
            rotateLeftFace(pCube, true);
        }
    }
    // Piece is on front face
    else
    {
        // Rotate top until the corner is in between two matching center tiles
        while ((piece.z == color && (piece.y != pCube->pieces[LEFT_CENTER].x))
               || (piece.y == color && (piece.x != pCube->pieces[LEFT_CENTER].x))
               || (piece.x == color && (piece.y != pCube->pieces[FRONT_CENTER].y)))
        {
            rotateBottomFace(pCube, true);
            turnZ(pCube, false);
        }
        // Desired color is facing down, rieorient so desired color facing front
        if (piece.z == color)
        {
            rotateFrontFace(pCube, true);
            rotateBottomFace(pCube, true);
            rotateFrontFace(pCube, false);
            rotateBottomFace(pCube, false);
            rotateBottomFace(pCube, false);
        }
        
        // Top center color is facing left
        if (piece.x == color)
        {
            // Turn so piece is faceing front
            turnZ(pCube, true);
            piece = pCube->pieces[FRONT_RIGHT_BOTTOM_CORNER];
            
            putBottomRightCornerOnTop(pCube, piece, color);
        }
        // Top center color is facing front
        else
        {
            // Put piece in place
            rotateBottomFace(pCube, true);
            rotateLeftFace(pCube, false);
            rotateBottomFace(pCube, false);
            rotateLeftFace(pCube, true);
        }
    }
}

/**
 * Places bottom right corner piece in top right corner position
 *
 * @param pCube
 * Pointer to a Cube structure
 *
 * @param piece
 * The piece to be moved
 *
 * @param color
 * The color of the center piece of the top face
 */
void putBottomRightCornerOnTop(Cube* pCube, Piece piece, Color color)
{
    // Piece is on back face
    if (piece.yCoord == 0)
    {
        // Turn cube to put piece on front face
        turnZ(pCube, false);
        
        // Reassign piece
        piece = pCube->pieces[FRONT_RIGHT_BOTTOM_CORNER];
        
        // Rotate top until the corner is in between two matching center tiles
        while ((piece.z == color && (piece.y != pCube->pieces[RIGHT_CENTER].x))
               || (piece.y == color && (piece.x != pCube->pieces[RIGHT_CENTER].x))
               || (piece.x == color && (piece.y != pCube->pieces[FRONT_CENTER].y)))
        {
            rotateBottomFace(pCube, true);
            turnZ(pCube, false);
        }
        // Desired color is facing down, rieorient so desired color facing front
        if (piece.z == color)
        {
            rotateFrontFace(pCube, false);
            rotateBottomFace(pCube, false);
            rotateFrontFace(pCube, true);
            rotateBottomFace(pCube, true);
            rotateBottomFace(pCube, true);
        }
        // Top center color is facing right
        if (piece.x == color)
        {
            // Turn so piece is faceing front
            turnZ(pCube, false);
            piece = pCube->pieces[FRONT_LEFT_BOTTOM_CORNER];
            
            putBottomLeftCornerOnTop(pCube, piece, color);
        }
        // Top center color facing front
        else
        {
            // Put piece in place
            rotateBottomFace(pCube, false);
            rotateRightFace(pCube, false);
            rotateBottomFace(pCube, true);
            rotateRightFace(pCube, true);
        }
    }
    // Piece is on front face
    else
    {
        // Rotate bottom until the corner is in between two matching center tiles
        while ((piece.z == color && (piece.y != pCube->pieces[RIGHT_CENTER].x))
               || (piece.y == color && (piece.x != pCube->pieces[RIGHT_CENTER].x))
               || (piece.x == color && (piece.y != pCube->pieces[FRONT_CENTER].y)))
        {
            rotateBottomFace(pCube, true);
            turnZ(pCube, false);
        }
        // Desired color is facing down, rieorient so desired color facing front
        if (piece.z == color)
        {
            rotateFrontFace(pCube, false);
            rotateBottomFace(pCube, false);
            rotateFrontFace(pCube, true);
            rotateBottomFace(pCube, true);
            rotateBottomFace(pCube, true);
        }
        
        // Top center color is facing right
        if (piece.x == color)
        {
            // Turn so piece is faceing front
            turnZ(pCube, false);
            piece = pCube->pieces[FRONT_LEFT_BOTTOM_CORNER];
            
            putBottomLeftCornerOnTop(pCube, piece, color);
        }
        // Top center color is facing front
        else
        {
            // Put piece in place
            rotateBottomFace(pCube, false);
            rotateRightFace(pCube, false);
            rotateBottomFace(pCube, true);
            rotateRightFace(pCube, true);
        }
    }
}

// Cube printing functions

/**
 * Prints a flattened Rubiks cube with numbers corresponding to each sqauare
 *
 * @param pCube
 * Pointer to a cube structure
 */
void printCube(Cube* pCube)
{
    printf("\n");
    printf("      %d %d %d\n", pCube->pieces[0].z, pCube->pieces[1].z, pCube->pieces[2].z);
    printf("      %d %d %d\n", pCube->pieces[3].z, pCube->pieces[4].z, pCube->pieces[5].z);
    printf("      %d %d %d\n", pCube->pieces[6].z, pCube->pieces[7].z, pCube->pieces[8].z);
    printf("%d %d %d ", pCube->pieces[0].x, pCube->pieces[3].x, pCube->pieces[6].x);
    printf("%d %d %d ", pCube->pieces[6].y, pCube->pieces[7].y, pCube->pieces[8].y);
    printf("%d %d %d ", pCube->pieces[8].x, pCube->pieces[5].x, pCube->pieces[2].x);
    printf("%d %d %d\n", pCube->pieces[2].y, pCube->pieces[1].y, pCube->pieces[0].y);
    printf("%d %d %d ", pCube->pieces[9].x, pCube->pieces[12].x, pCube->pieces[14].x);
    printf("%d %d %d ", pCube->pieces[14].y, pCube->pieces[15].y, pCube->pieces[16].y);
    printf("%d %d %d ", pCube->pieces[16].x, pCube->pieces[13].x, pCube->pieces[11].x);
    printf("%d %d %d\n", pCube->pieces[11].y, pCube->pieces[10].y, pCube->pieces[9].y);
    printf("%d %d %d ", pCube->pieces[17].x, pCube->pieces[20].x, pCube->pieces[23].x);
    printf("%d %d %d ", pCube->pieces[23].y, pCube->pieces[24].y, pCube->pieces[25].y);
    printf("%d %d %d ", pCube->pieces[25].x, pCube->pieces[22].x, pCube->pieces[19].x);
    printf("%d %d %d\n", pCube->pieces[19].y, pCube->pieces[18].y, pCube->pieces[17].y);
    printf("      %d %d %d\n", pCube->pieces[23].z, pCube->pieces[24].z, pCube->pieces[25].z);
    printf("      %d %d %d\n", pCube->pieces[20].z, pCube->pieces[21].z, pCube->pieces[22].z);
    printf("      %d %d %d\n", pCube->pieces[17].z, pCube->pieces[18].z, pCube->pieces[19].z);
    printf("\n");
}
