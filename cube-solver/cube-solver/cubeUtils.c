//
//  cubeUtils.c
//  cube-solver
//
//  Created by Bharat Kesari on 7/5/20.
//  Copyright © 2020 Bharat Kesari. All rights reserved.
//

#include "cubeUtils.h"

// Global file pointer defined in main
extern FILE* fp_instruct;

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
    int numWhite = 0;
    int numYellow = 0;
    int numRed = 0;
    int numOrange = 0;
    int numBlue = 0;
    int numGreen = 0;
    
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
            printf("Invalid char: %c\n", ch);
            exit(1);
        }
        
        switch (ch)
        {
            case 'w':
                ++numWhite;
                break;
            case 'y':
                ++numYellow;
                break;
            case 'r':
                ++numRed;
                break;
            case 'o':
                ++numOrange;
                break;
            case 'b':
                ++numBlue;
                break;
            case 'g':
                ++numGreen;
                break;
        }
    }
    
    if (numWhite != 9 || numYellow != 9 || numOrange != 9
        || numRed != 9 || numBlue != 9 || numGreen != 9)
    {
        printf("Invalid input.\n");
        printf("W: %d Y: %d O: %d R: %d B: %d G: %d\n", numWhite, numYellow, numOrange, numRed, numBlue, numGreen);
        exit(1);
    }
    
    // Check if input length does not exceed NUM_SQUARES
    scanf("%c", &ch);
    // Exit function if input is too long
    if (ch != '\n')
    {
        printf("Invalid input.\n");
        printf("Input is too long\n");
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
    if ((*pX != 0) && (*pX != 1))
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
 * Rotates the front face of the cube 90 degrees and writes the instruction to a file
 *
 * @param pCube
 * Pointer to a cube structure
 *
 * @param isCntr
 * Specifies the direction of the rotation
 *
 * @param outputInstruct
 * Writes instruction to file if true
 */
void rotateFrontFace(Cube* pCube, bool isCntr, bool outputInstruct)
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
    
    // Output instruction if indicated
    if (outputInstruct)
    {
        // Output CC instruction
        if (isCntr)
        {
            vector_append_item(hVector, 'f');
        }
        // Output Clck instruction
        else
        {
            vector_append_item(hVector, 'F');
        }
    }
}

/**
 * Rotates the front face of the cube 90 degrees and writes the instruction to a file
 *
 * @param pCube
 * Pointer to a cube structure
 *
 * @param isCntr
 * Specifies the direction of the rotation
 *
 * @param outputInstruct
 * Writes instruction to file if true
 */
void rotateBackFace(Cube* pCube, bool isCntr, bool outputInstruct)
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
    
     // Output instruction if indicated
    if (outputInstruct)
    {
        // Output CC instruction
        if (isCntr)
        {
            vector_append_item(hVector, 'B');
        }
        // Output Clck instruction
        else
        {
            vector_append_item(hVector, 'b');
        }
    }
}

/**
 * Rotates the left face of the cube 90 degrees and writes the instruction to a file
 *
 * @param pCube
 * Pointer to a cube structure
 *
 * @param isCntr
 * Specifies the direction of the rotation
 *
 * @param outputInstruct
 * Writes instruction to file if true
 */
void rotateLeftFace(Cube* pCube, bool isCntr, bool outputInstruct)
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
    
    // Output instruction if indicated
    if (outputInstruct)
    {
        // Output CC instruction
        if (isCntr)
        {
            vector_append_item(hVector, 'l');
        }
        // Output Clck instruction
        else
        {
            vector_append_item(hVector, 'L');
        }
    }
}

/**
 * Rotates the right face of the cube 90 degrees and writes the instruction to a file
 *
 * @param pCube
 * Pointer to a cube structure
 *
 * @param isCntr
 * Specifies the direction of the rotation
 *
 * @param outputInstruct
 * Writes instruction to file if true
 */
void rotateRightFace(Cube* pCube, bool isCntr, bool outputInstruct)
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
    
    // Output instruction if indicated
    if (outputInstruct)
    {
        // Output CC instruction
        if (isCntr)
        {
            vector_append_item(hVector, 'R');
        }
        // Output Clck instruction
        else
        {
            vector_append_item(hVector, 'r');
        }
    }
}

/**
 * Rotates the top face of the cube 90 degrees and writes the instruction to a file
 *
 * @param pCube
 * Pointer to a cube structure
 *
 * @param isCntr
 * Specifies the direction of the rotation
 *
 * @param outputInstruct
 * Writes instruction to file if true
 */
void rotateTopFace(Cube* pCube, bool isCntr, bool outputInstruct)
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
    
    // Output instruction if indicated
    if (outputInstruct)
    {
        // Output CC instruction
        if (isCntr)
        {
            vector_append_item(hVector, 'u');
        }
        // Output Clck instruction
        else
        {
            vector_append_item(hVector, 'U');
        }
    }
}

/**
 * Rotates the bottom face of the cube 90 degrees and writes instruction to a file
 *
 * @param pCube
 * Pointer to a cube structure
 *
 * @param isCntr
 * Specifies the direction of the rotation
 *
 * @param outputInstruct
 * Writes instruction to file if true
 */
void rotateBottomFace(Cube* pCube, bool isCntr, bool outputInstruct)
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
    
    // Output instruction if indicated
    if (outputInstruct)
    {
        // Output CC instruction
        if (isCntr)
        {
            vector_append_item(hVector, 'D');
        }
        // Output Clck instruction
        else
        {
            vector_append_item(hVector, 'd');
        }
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
 * Turns the cube around the x axis 90 degrees and writes instruction to a file
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
    rotateLeftFace(pCube, isCntr, false);
    rotateMidX(pCube, isCntr);
    rotateRightFace(pCube, isCntr, false);
    
    // Output CC instruction
    if (isCntr)
    {
        vector_append_item(hVector, 'x');
    }
    // Output Clck instruction
    else
    {
        vector_append_item(hVector, 'X');
    }
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
    rotateFrontFace(pCube, isCntr, false);
    rotateMidY(pCube, isCntr);
    rotateBackFace(pCube, isCntr, false);

    // Output CC instruction
    if (isCntr)
    {
        vector_append_item(hVector, 'y');
    }
    // Output Clck instruction
    else
    {
        vector_append_item(hVector, 'Y');
    }
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
    rotateTopFace(pCube, isCntr, false);
    rotateMidZ(pCube, isCntr);
    rotateBottomFace(pCube, isCntr, false);
    
    // Output CC instruction
    if (isCntr)
    {
        vector_append_item(hVector, 'z');
    }
    // Output Clck instruction
    else
    {
        vector_append_item(hVector, 'Z');
    }
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

// Instructions optimization functions

/**
 * Optimizes the cube solving instructions by 'removing' any successive instructions to rotate a face and rotate it back or to rotate a face 4 rotations in the same direction
 *
 * @return
 * Returns true if any optimization was executed by the function
 * Returns false if the instructions remained the same
 */
bool optimizeInstructions(void)
{
    // Boolean value to return
    bool optimized = false;
    
    // Counter varaible for while loop
    int counter = 0;

    // Loop for every group of four instructions in the Vector
    while (counter < vector_get_size(hVector) - 3)
    {
        // Get four consecutive instructions
        char instr_1 = vector_pop_item(hVector, counter);
        char instr_2 = vector_pop_item(hVector, counter + 1);
        char instr_3 = vector_pop_item(hVector, counter + 2);
        char instr_4 = vector_pop_item(hVector, counter + 3);
        
        // Check if all four instructions are identical
        if (instr_1 == instr_2 && instr_1 == instr_3 && instr_1 == instr_4)
        {
            // Set boolean variable
            optimized = true;
            
            // Remove the unneccessary instructions
            vector_remove_item(hVector, counter);
            vector_remove_item(hVector, counter);
            vector_remove_item(hVector, counter);
            vector_remove_item(hVector, counter);
            
            continue;
        }
        
        // Check if consecutive instructions are redundant
        if ((instr_1 != instr_2) && (toupper(instr_1) == toupper(instr_2)))
        {
            // Set boolean variable
            optimized = true;
            
            // Remove unneccessary instructions
            vector_remove_item(hVector, counter);
            vector_remove_item(hVector, counter);
            
            continue;
        }
        
        // Check for three rotatations of the same face in the same direction
        if (instr_1 == instr_2 && instr_1 == instr_3)
        {
            optimized = true;
            
            // Remove unneccessary instructions
            vector_remove_item(hVector, counter + 1);
            vector_remove_item(hVector, counter + 1);
            
            // Flip direction of first instruction in group
            if (islower(instr_1))
            {
                vector_replace_item(hVector, counter, toupper(instr_1));
            }
            else
            {
                vector_replace_item(hVector, counter, tolower(instr_1));
            }
            
            continue;
        }
        
        // Increase counter
        counter++;
    }
    
    // Edge cases
    char instr_1 = vector_pop_item(hVector, vector_get_size(hVector) - 3);
    char instr_2 = vector_pop_item(hVector, vector_get_size(hVector) - 2);
    char instr_3 = vector_pop_item(hVector, vector_get_size(hVector) - 1);
    
    // Check if consecutive instructions are redundant
    if ((instr_1 != instr_2) && (toupper(instr_1) == toupper(instr_2)))
    {
        // Set boolean variable
        optimized = true;
        
        // Remove unneccessary instructions
        vector_remove_item(hVector, counter);
        vector_remove_item(hVector, counter);
    }
    
    // Check for three rotatations of the same face in the same direction
    if (instr_1 == instr_2 && instr_1 == instr_3)
    {
        // Remove unneccessary instructions
        vector_remove_item(hVector, counter + 1);
        vector_remove_item(hVector, counter + 1);
        
        // Flip direction of first instruction in group
        if (islower(instr_1))
        {
            vector_replace_item(hVector, counter, toupper(instr_1));
        }
        else
        {
            vector_replace_item(hVector, counter, tolower(instr_1));
        }
    }
    
    instr_1 = vector_pop_item(hVector, vector_get_size(hVector) - 2);
    instr_2 = vector_pop_item(hVector, vector_get_size(hVector) - 1);
    
    // Check if consecutive instructions are redundant
    if ((instr_1 != instr_2) && (toupper(instr_1) == toupper(instr_2)))
    {
        // Set boolean variable
        optimized = true;
        
        // Remove unneccessary instructions
        vector_remove_item(hVector, counter);
        vector_remove_item(hVector, counter);
    }

    return optimized;
}

// Cube printing functions

/**
 * Prints a flattened Rubiks cube with numbers corresponding to each sqauare
 *
 * @param pCube
 * Pointer to a cube struct
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

