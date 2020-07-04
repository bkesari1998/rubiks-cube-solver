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
#include "rubiks.h"

int main(int argc, const char * argv[]) {
    char colorArr[NUM_SQUARES];
    Cube rubiks;
    
    // Get user input
    getColors(colorArr);
    createCube(&rubiks, colorArr);
    printCube(&rubiks);
    solveFirstLayerCross(&rubiks);
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
