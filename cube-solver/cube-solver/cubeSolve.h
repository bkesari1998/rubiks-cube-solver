//
//  cubeSolve.h
//  cube-solver
//
//  Created by Bharat Kesari on 7/5/20.
//  Copyright © 2020 Bharat Kesari. All rights reserved.
//

#ifndef cubeSolve_h
#define cubeSolve_h

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

// Middle layer functions
void solveMidLayerEdges(Cube* pCube);
void locateMidEdges(Cube* pCube, Piece faceEdges[], Color edgeColor);
bool faceMidEdgesInPlace(Cube* pCube, Color faceColor);
void swapTopEdgeRightEdge(Cube* pCube);
void swapTopEdgeLeftEdge(Cube* pCube);

// Top cross creation functions
void createTopCross(Cube* pCube);
void orientCubeForTopCross(Cube* pCube, Color faceColor);
bool checkTopCross(Cube* pCube, Color faceColor);

// Top corners placement function
void orientTopCorners(Cube* pCube);
void orientCubeForTopCorners(Cube* pCube, Color faceColor);
bool checkTopCorners(Cube* pCube, Color faceColor);

// Top corner solving functions
void solveTopCorners(Cube* pCube);
void orientCubeForTopCornerSwap(Cube* pCube);
bool checkTopCornersSolved(Cube* pCube);

// Solve top edges
void solveTopEdges(Cube* pCube);
void orientCubeForTopEdgeSolve(Cube* pCube);
bool checkTopEdgeSolved(Cube* pCube);

#endif /* cubeSolve_h */
