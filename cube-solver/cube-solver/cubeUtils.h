//
//  cubeUtils.h
//  cube-solver
//
//  Created by Bharat Kesari on 7/5/20.
//  Copyright © 2020 Bharat Kesari. All rights reserved.
//

#ifndef cubeUtils_h
#define cubeUtils_h

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
void rotateFrontFace(Cube* pCube, bool isCntr, bool outputInstruct);
void rotateBackFace(Cube* pCube, bool isCntr, bool outputInstruct);
void rotateLeftFace(Cube* pCube, bool isCntr, bool outputInstruct);
void rotateRightFace(Cube* pCube, bool isCntr, bool outputInstruct);
void rotateTopFace(Cube* pCube, bool isCntr, bool outputInstruct);
void rotateBottomFace(Cube* pCube, bool isCntr, bool outputInstruct);
void rotateMidX(Cube* pCube, bool isCntr);
void rotateMidY(Cube* pCube, bool isCntr);
void rotateMidZ(Cube* pCube, bool isCntr);
void turnX(Cube* pCube, bool isCntr);
void turnY(Cube* pCube, bool isCntr);
void turnZ(Cube* pCube, bool isCntr);

// Matrix rotation
void rotateMatClck(Piece face[NUM_PIECES_IN_ROW][NUM_PIECES_IN_ROW]);
void rotateMatCntr(Piece face[NUM_PIECES_IN_ROW][NUM_PIECES_IN_ROW]);

// Cube printing
void printCube(Cube* pCube);

#endif /* cubeUtils_h */
