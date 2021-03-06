//
//  cubeSolve.c
//  cube-solver
//
//  Created by Bharat Kesari on 7/5/20.
//  Copyright © 2020 Bharat Kesari. All rights reserved.
//

#include "cubeSolve.h"

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
        rotateBackFace(pCube, false, true);
        
        // Rotate top face until edge location not occupied by a daisy edge
        // Compare color of edge with the color of the piece it will replace
        while (oppColor == pCube->pieces[TOP_RIGHT_EDGE].z)
        {
            // Rotate the top face of the cube if a daisy piece is in that position
            rotateTopFace(pCube, true, true);
        }
        // Put piece in daisy
        rotateRightFace(pCube, false, true);
    }
    // Put piece in daisy if originally on front face
    else if (piece.yCoord == 2)
    {
        // Move out of top face
        rotateFrontFace(pCube, true, true);
        // Rotate top face until edge location not occupied by a daisy edge
        // Compare color of edge with the color of the piece it will replace
        while (oppColor == pCube->pieces[TOP_LEFT_EDGE].z)
        {
            // Rotate the top face of the cube if a daisy piece is in that position
            rotateTopFace(pCube, true, true);
        }
        // Put piece in daisy
        rotateLeftFace(pCube, true, true);
    }
    // Put Piece in daisy if originally on right/left face
    else
    {
        // Piece originally on left face
        if (piece.xCoord == 0)
        {
            // Move piece out of top face
            rotateLeftFace(pCube, false, true);
            
            // Rotate top face until edge location not occupied by a daisy edge
            // Compare color of edge with the color of the piece it will replace
            while (oppColor == pCube->pieces[TOP_FRONT_EDGE].z)
            {
                // Rotate the top face of the cube if a daisy piece is in that position
                rotateTopFace(pCube, true, true);
            }
            // Put piece in daisy
            rotateFrontFace(pCube, false, true);
        }
        // Piece originally on right face
        else
        {
            // Move piece out of top face
            rotateRightFace(pCube, true, true);
            
            // Rotate top face until edge location not occupied by a daisy edge
            while (oppColor == pCube->pieces[TOP_BACK_EDGE].z)
            {
                rotateTopFace(pCube, true, true);
            }
            // Put piece in daisy
            rotateBackFace(pCube, true, true);
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
                    rotateTopFace(pCube, true, true);
                }
                // Put piece in daisy
                rotateBackFace(pCube, false, true);
            }
            // Desired piece is on front face
            else
            {
                // Rotate top face until edge edge location not occupied with a daisy edge
                while (oppColor == pCube->pieces[TOP_FRONT_EDGE].z)
                {
                    rotateTopFace(pCube, true, true);
                }
                // Put piece in daisy
                rotateFrontFace(pCube, false, true);
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
                    rotateTopFace(pCube, true, true);
                }
                // Put piece in daisy
                rotateBackFace(pCube, true, true);
            }
            // Desired piece is on front face
            else
            {
                // Rotate top face until edge location not occupied with a daisy edge
                while (oppColor == pCube->pieces[TOP_FRONT_EDGE].z)
                {
                    rotateTopFace(pCube, true, true);
                }
                // Put piece in daisy
                rotateFrontFace(pCube, true, true);
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
                    rotateTopFace(pCube, true, true);
                }
                // Put piece in daisy
                rotateLeftFace(pCube, false, true);
            }
            // Desired piece is on right face
            else
            {
                // Rotate top until edge location not occupied with daisy edge
                while(oppColor == pCube->pieces[TOP_RIGHT_EDGE].z)
                {
                    rotateTopFace(pCube, true, true);
                }
                // Put piece in daisy
                rotateRightFace(pCube, false, true);
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
                    rotateTopFace(pCube, true, true);
                }
                // Put piece in daisy
                rotateLeftFace(pCube, true, true);
            }
            // Desired piece is on right face
            else
            {
                // Rotate top until edge location not occupied with daisy edge
                while(oppColor == pCube->pieces[TOP_RIGHT_EDGE].z)
                {
                    rotateTopFace(pCube, true, true);
                }
                // Put piece in daisy
                rotateRightFace(pCube, true, true);
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
                rotateTopFace(pCube, true, true);
            }
            // Place piece in middle layer
            rotateLeftFace(pCube, true, true);
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
                    rotateTopFace(pCube, true, true);
                }
                // Place piece in middle layer
                rotateBackFace(pCube, true, true);
                // Place piece in daisy
                daisyMid(pCube, piece, oppColor);
            }
            // Piece is on front face
            else
            {
                // Rotate top until edge location not occupied with daisy edge
                while (oppColor == pCube->pieces[TOP_FRONT_EDGE].z)
                {
                    rotateTopFace(pCube, true, true);
                }
                // Place piece in middle layer
                rotateFrontFace(pCube, true, true);
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
                rotateTopFace(pCube, true, true);
            }
            // Place piece in middle layer
            rotateRightFace(pCube, true, true);
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
                rotateTopFace(pCube, true, true);
            }
            // Place piece in daisy
            rotateLeftFace(pCube, true, true);
            rotateLeftFace(pCube, true, true);
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
                    rotateTopFace(pCube, true, true);
                }
                // Place piece in daisy
                rotateBackFace(pCube, true, true);
                rotateBackFace(pCube, true, true);
            }
            // Piece is on front face
            else
            {
                // Rotate top until edge location not occupied with daisy edge
                while (oppColor == pCube->pieces[TOP_FRONT_EDGE].z)
                {
                    rotateTopFace(pCube, true, true);
                }
                // Place piece in daisy
                rotateFrontFace(pCube, true, true);
                rotateFrontFace(pCube, true, true);
            }
        }
        // Piece is on right face
        else
        {
            // Rotate top until edge location not occupied with daisy edge
            while (oppColor == pCube->pieces[TOP_RIGHT_EDGE].z)
            {
                rotateTopFace(pCube, true, true);
            }
            // Place piece in daisy
            rotateRightFace(pCube, true, true);
            rotateRightFace(pCube, true, true);
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
                rotateTopFace(pCube, true, true);
            }
            // Put piece in place
            rotateBackFace(pCube, true, true);
            rotateBackFace(pCube, true, true);
        }
        else if (i == 1)
        {
           // Check that top left edge piece is on correct face and that piece is a cross piece
            while ((pCube->pieces[TOP_LEFT_EDGE].x != pCube->pieces[LEFT_CENTER].x) || pCube->pieces[TOP_LEFT_EDGE].z != oppColor)
            {
                // Rotate top until matching piece found
               rotateTopFace(pCube, true, true);
            }
            // Put piece in place
            rotateLeftFace(pCube, true, true);
            rotateLeftFace(pCube, true, true);
        }
        else if (i == 2)
        {
           // Check that top right edge piece is on correct face
            while ((pCube->pieces[TOP_RIGHT_EDGE].x != pCube->pieces[RIGHT_CENTER].x) || pCube->pieces[TOP_RIGHT_EDGE].z != oppColor)
            {
                // Rotate top until matching piece found
               rotateTopFace(pCube, true, true);
            }
            // Put piece in place
            rotateRightFace(pCube, true, true);
            rotateRightFace(pCube, true, true);
        }
        else
        {
           // Check that top front edge piece is on correct face
            while ((pCube->pieces[TOP_FRONT_EDGE].y != pCube->pieces[FRONT_CENTER].y) || pCube->pieces[TOP_FRONT_EDGE].z != oppColor)
            {
                // Rotate top until matching piece found
               rotateTopFace(pCube, true, true);
            }
            // Put piece in place
            rotateFrontFace(pCube, true, true);
            rotateFrontFace(pCube, true, true);
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
                    rotateLeftFace(pCube, false, true);
                    rotateBottomFace(pCube, true, true);
                    rotateLeftFace(pCube, true, true);
                    
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
                    rotateRightFace(pCube, false, true);
                    rotateBottomFace(pCube, false, true);
                    rotateRightFace(pCube, true, true);
                    
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
            rotateBottomFace(pCube, true, true);
            turnZ(pCube, false);
            
        }
        // Desired color is facing down, rieorient so desired color facing front
        if (piece.z == color)
        {
            rotateFrontFace(pCube, true, true);
            rotateBottomFace(pCube, true, true);
            rotateFrontFace(pCube, false, true);
            rotateBottomFace(pCube, false, true);
            rotateBottomFace(pCube, false, true);
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
            rotateBottomFace(pCube, true, true);
            rotateLeftFace(pCube, false, true);
            rotateBottomFace(pCube, false, true);
            rotateLeftFace(pCube, true, true);
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
            rotateBottomFace(pCube, true, true);
            turnZ(pCube, false);
        }
        // Desired color is facing down, rieorient so desired color facing front
        if (piece.z == color)
        {
            rotateFrontFace(pCube, true, true);
            rotateBottomFace(pCube, true, true);
            rotateFrontFace(pCube, false, true);
            rotateBottomFace(pCube, false, true);
            rotateBottomFace(pCube, false, true);
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
            rotateBottomFace(pCube, true, true);
            rotateLeftFace(pCube, false, true);
            rotateBottomFace(pCube, false, true);
            rotateLeftFace(pCube, true, true);
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
            rotateBottomFace(pCube, true, true);
            turnZ(pCube, false);
        }
        // Desired color is facing down, rieorient so desired color facing front
        if (piece.z == color)
        {
            rotateFrontFace(pCube, false, true);
            rotateBottomFace(pCube, false, true);
            rotateFrontFace(pCube, true, true);
            rotateBottomFace(pCube, true, true);
            rotateBottomFace(pCube, true, true);
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
            rotateBottomFace(pCube, false, true);
            rotateRightFace(pCube, false, true);
            rotateBottomFace(pCube, true, true);
            rotateRightFace(pCube, true, true);
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
            rotateBottomFace(pCube, true, true);
            turnZ(pCube, false);
        }
        // Desired color is facing down, rieorient so desired color facing front
        if (piece.z == color)
        {
            rotateFrontFace(pCube, false, true);
            rotateBottomFace(pCube, false, true);
            rotateFrontFace(pCube, true, true);
            rotateBottomFace(pCube, true, true);
            rotateBottomFace(pCube, true, true);
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
            rotateBottomFace(pCube, false, true);
            rotateRightFace(pCube, false, true);
            rotateBottomFace(pCube, true, true);
            rotateRightFace(pCube, true, true);
        }
    }
}

// Middle layer functions

/**
 * Solves the middle layer edge pieces
 *
 * @param pCube
 * Pointer to a cube structure
 */
void solveMidLayerEdges(Cube* pCube)
{
    Piece piece;
    
    // Rotate cube so solved layer is on bottom
    turnY(pCube, true);
    turnY(pCube, true);
    
    // Get side face center colors
    Color center1 = pCube->pieces[FRONT_CENTER].y;
    Color center2 = pCube->pieces[LEFT_CENTER].x;
    Color center3 = pCube->pieces[BACK_CENTER].y;
    Color center4 = pCube->pieces[RIGHT_CENTER].x;
   
    
    // Place center colors in an array
    Color centerColors[NUM_CENTER - 2] = {center1, center2, center3, center4};
    
    // Create an edge piece array
    Piece edgePieces[NUM_EDGES_ON_FACE];
    
    // Iterate for each side face
    for (int i = 0; i < NUM_CENTER - 2; ++i)
    {
        locateMidEdges(pCube, edgePieces, centerColors[i]);
        // Iterate through edge piece array
        while (!(faceMidEdgesInPlace(pCube, centerColors[i])))
        {
            for (int j = 0; j < NUM_EDGES_ON_FACE; ++j)
            {
                piece = edgePieces[j];
                // Check if an edge piece that belongs in the middle layer is on the top layer and has desired color on x or y face
                if (piece.zCoord == 0 && piece.z != pCube->pieces[TOP_CENTER].z && piece.z != pCube->pieces[FRONT_CENTER].y)
                {
                    // Rotate piece to front face
                    while ((pCube->pieces[TOP_FRONT_EDGE].y != centerColors[i]) || (pCube->pieces[TOP_FRONT_EDGE].z == pCube->pieces[TOP_CENTER].z))
                    {
                        rotateTopFace(pCube, true, true);
                    }
                    // Reassign piece
                    piece = pCube->pieces[TOP_FRONT_EDGE];
                    
                    // Moving right
                    if (piece.z == pCube->pieces[RIGHT_CENTER].x)
                    {
                        swapTopEdgeRightEdge(pCube);
                    }
                    // Moving left
                    else
                    {
                        swapTopEdgeLeftEdge(pCube);
                    }
                }
                // Check if an edge piece that belongs in the middle layer is on the top layer and has desired color on z face
                else if (piece.zCoord == 0 && piece.z != pCube->pieces[TOP_CENTER].z && piece.z == pCube->pieces[FRONT_CENTER].y)
                {
                    // Piece is on left face
                    if (piece.xCoord == 0)
                    {
                        // X color matches left center color
                        if (piece.x == pCube->pieces[LEFT_CENTER].x)
                        {
                            turnZ(pCube, true);
                            swapTopEdgeRightEdge(pCube);
                            turnZ(pCube, false);
                        }
                        // X color matches right center color
                        else if (piece.x == pCube->pieces[RIGHT_CENTER].x)
                        {
                            rotateTopFace(pCube, true, true);
                            rotateTopFace(pCube, true, true);
                            turnZ(pCube, false);
                            swapTopEdgeLeftEdge(pCube);
                            turnZ(pCube, true);
                        }
                    }
                    // Piece is on back face
                    else if (piece.xCoord == 1 && piece.yCoord == 0)
                    {
                        // Y color matches left center color
                        if (piece.y == pCube->pieces[LEFT_CENTER].x)
                        {
                            rotateTopFace(pCube, true, true);
                            turnZ(pCube, true);
                            swapTopEdgeRightEdge(pCube);
                            turnZ(pCube, false);
                        }
                        // Y color matches right center color
                        else if (piece.y == pCube->pieces[RIGHT_CENTER].x)
                        {
                            rotateTopFace(pCube, false, true);
                            turnZ(pCube, false);
                            swapTopEdgeLeftEdge(pCube);
                            turnZ(pCube, true);
                        }
                    }
                    // Piece is on front face
                    else if (piece.xCoord == 1 && piece.yCoord == 2)
                    {
                        // Y color matches left center color
                        if (piece.y == pCube->pieces[LEFT_CENTER].x)
                        {
                            rotateTopFace(pCube, false, true);
                            turnZ(pCube, true);
                            swapTopEdgeRightEdge(pCube);
                            turnZ(pCube, false);
                        }
                        // Y color matches right center color
                        else if (piece.y == pCube->pieces[RIGHT_CENTER].x)
                        {
                            rotateTopFace(pCube, true, true);
                            turnZ(pCube, false);
                            swapTopEdgeLeftEdge(pCube);
                            turnZ(pCube, true);
                        }
                    }
                    // Piece is on right face
                    else
                    {
                        // X color matches left center color
                        if (piece.x == pCube->pieces[RIGHT_CENTER].x)
                        {
                            turnZ(pCube, false);
                            swapTopEdgeLeftEdge(pCube);
                            turnZ(pCube, true);
                        }
                        // X color matches right center color
                        else if (piece.x == pCube->pieces[LEFT_CENTER].x)
                        {
                            rotateTopFace(pCube, true, true);
                            rotateTopFace(pCube, true, true);
                            turnZ(pCube, true);
                            swapTopEdgeRightEdge(pCube);
                            turnZ(pCube, false);
                        }
                    }
                }
                // Check if desired piece is in middle layer
                else if (piece.zCoord == 1)
                {
                    // Piece is on front face
                    if (piece.yCoord == 2)
                    {
                        // Piece is on left side
                        if (piece.xCoord == 0)
                        {
                            // Piece is not in correct position
                            if (piece.y != pCube->pieces[FRONT_CENTER].y || piece.x != pCube->pieces[LEFT_CENTER].x)
                            {
                                swapTopEdgeLeftEdge(pCube);
                            }
                        }
                        // Piece is on right side
                        else
                        {
                            // Piece is not in correct postion
                            if (piece.y != pCube->pieces[FRONT_CENTER].y || piece.x != pCube->pieces[RIGHT_CENTER].x)
                            {
                                swapTopEdgeRightEdge(pCube);
                            }
                        }
                    }
                    // Piece is on back face
                    else
                    {
                        // Piece is on left side
                        if (piece.xCoord == 0)
                        {
                            // Move piece to top layer
                            turnZ(pCube, true);
                            swapTopEdgeLeftEdge(pCube);
                            turnZ(pCube, false);
                        }
                        // Piece is on right side
                        else
                        {
                            // Move piece to top layer
                            turnZ(pCube, false);
                            swapTopEdgeRightEdge(pCube);
                            turnZ(pCube, true);
                        }
                    }
                }
                locateMidEdges(pCube, edgePieces, centerColors[i]);
            }
        }
        // Go to the next face
        turnZ(pCube, true);
    }
}

/**
 * Locates the edge pieces that have a square with a specified color and puts pieces that are in the correct position in the middle layer at the begining of the array
 *
 * @param pCube
 * Pointer to a cube structure
 *
 * @param faceEdges
 * An array holding the edge pieces
 *
 * @param edgeColor
 * The desired color
 */
void locateMidEdges(Cube* pCube, Piece faceEdges[], Color edgeColor)
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
            faceEdges[cntr] = piece;
            
            // Advance counter
            ++cntr;
            
            // Break loop if all edge pieces of desired color were found
            if (cntr >= NUM_EDGES_ON_FACE)
            {
                break;
            }
        }
    }
    
    for (int i = 0; i < NUM_EDGES_ON_FACE; ++i)
    {
        piece = faceEdges[i];
        if (piece.y == pCube->pieces[FRONT_CENTER].y && (piece.x == pCube->pieces[RIGHT_CENTER].x || piece.x == pCube->pieces[LEFT_CENTER].x))
        {
            // Move all pieces preceding one index back
            for (int j = i; j > 0; --j)
            {
                faceEdges[j] = faceEdges[j - 1];
            }
            // Move piece to the front of the array
            faceEdges[0] = piece;
        }
    }
}

/**
 * Checks if the middle edges of a face are in place
 *
 * @param pCube
 * Pointer to a cube struct
 *
 * @param faceColor
 * The color of the face
 *
 * @return
 * True if mid layer edges for the face are in place
 * False if mid layer edges for the face are not in place
 */
bool faceMidEdgesInPlace(Cube* pCube, Color faceColor)
{
    // Check if both edge pieces are in place
    if ((pCube->pieces[FRONT_LEFT_EDGE].y == pCube->pieces[FRONT_CENTER].y && pCube->pieces[FRONT_LEFT_EDGE].x == pCube->pieces[LEFT_CENTER].x)
        && (pCube->pieces[FRONT_RIGHT_EDGE].y == pCube->pieces[FRONT_CENTER].y && pCube->pieces[FRONT_RIGHT_EDGE].x == pCube->pieces[RIGHT_CENTER].x))
    {
        return true;
    }
    
    // Both edge pieces are not in place
    return false;
}

/**
 * Algorithm to swap the top front edge with the front right edge
 *
 * @param pCube
 * Pointer to a Cube structure
 */
void swapTopEdgeRightEdge(Cube* pCube)
{
    rotateTopFace(pCube, false, true);
    rotateRightFace(pCube, true, true);
    rotateTopFace(pCube, true, true);
    rotateRightFace(pCube, false, true);
    rotateTopFace(pCube, true, true);
    rotateFrontFace(pCube, true, true);
    rotateTopFace(pCube, false, true);
    rotateFrontFace(pCube, false, true);
}

/**
 * Algorithm to swap the top front edge with the left front edge
 *
 * @param pCube
 * Pointer to a Cube struct
 */
void swapTopEdgeLeftEdge(Cube* pCube)
{
    rotateTopFace(pCube, true, true);
    rotateLeftFace(pCube, true, true);
    rotateTopFace(pCube, false, true);
    rotateLeftFace(pCube, false, true);
    rotateTopFace(pCube, false, true);
    rotateFrontFace(pCube, false, true);
    rotateTopFace(pCube, true, true);
    rotateFrontFace(pCube, true, true);
}

// Top cross solving functions

/**
 * Creates a cross on the top face of the cube
 *
 * @param pCube
 * Pointer to a Cube struct
 */
void createTopCross(Cube* pCube)
{
    Color faceColor = pCube->pieces[TOP_CENTER].z;
    
    // Loop while top cross is unsolved
    while (!(checkTopCross(pCube, faceColor)))
    {
        // Orient top face
        orientCubeForTopCross(pCube, faceColor);
        
        // Perform cross solving algorithm
        rotateFrontFace(pCube, false, true);
        rotateTopFace(pCube, false, true);
        rotateRightFace(pCube, true, true);
        rotateTopFace(pCube, true, true);
        rotateRightFace(pCube, false, true);
        rotateFrontFace(pCube, true, true);
    }
}

/**
 * Orients the cube to preform the algorithm to create the top layer cross
 *
 * @param pCube
 * Pointer to a Cube struct
 *
 * @param faceColor
 * The color of the top face
 */
void orientCubeForTopCross(Cube* pCube, Color faceColor)
{
    
    // Orient cube to make reverse L or horizontal line
    if (pCube->pieces[TOP_BACK_EDGE].z == faceColor)
    {
        // Orient to reverse L
        if (pCube->pieces[TOP_RIGHT_EDGE].z == faceColor)
        {
            turnZ(pCube, true);
        }
        // Orient to horizontal line
        else if (pCube->pieces[TOP_FRONT_EDGE].z == faceColor)
        {
            turnZ(pCube, true);
        }
    }
    else if (pCube->pieces[TOP_LEFT_EDGE].z == faceColor)
    {
        // Orient to reverse L
        if (pCube->pieces[TOP_FRONT_EDGE].z == faceColor)
        {
            turnZ(pCube, false);
        }
    }
    else if (pCube->pieces[TOP_RIGHT_EDGE].z == faceColor)
    {
        // Orient to reverse L
        if (pCube->pieces[TOP_FRONT_EDGE].z == faceColor)
        {
            turnZ(pCube, true);
            turnZ(pCube, true);
        }
    }
}

/**
 * Checks if the top cross has been placed
 *
 * @param pCube
 * Pointer to a Cube struct
 *
 * @param faceColor
 * The color of the top face
 *
 * @return
 * True if top cross is solved
 * False if top cross is not solved
 */
bool checkTopCross(Cube* pCube, Color faceColor)
{
    // Top cross placed
    if (pCube->pieces[TOP_BACK_EDGE].z == faceColor && pCube->pieces[TOP_LEFT_EDGE].z == faceColor
        && pCube->pieces[TOP_RIGHT_EDGE].z == faceColor && pCube->pieces[TOP_FRONT_EDGE].z == faceColor)
    {
        return true;
    }
    
    // Top cross not placed
    return false;
}

// Top corners solving functions

/**
 * Places the top corners of the cube so top oriented squares are the same color as the top face
 *
 * @param pCube
 * Pointer to a Cube struct
 */
void orientTopCorners(Cube* pCube)
{
    Color faceColor = pCube->pieces[TOP_CENTER].z;
    
    // While the corners are not placed properly
    while (!(checkTopCorners(pCube, faceColor)))
    {
        // Orient the cube correctly
        orientCubeForTopCorners(pCube, faceColor);
        
        // Algorithm to place corner pieces
        rotateRightFace(pCube, true, true);
        rotateTopFace(pCube, false, true);
        rotateRightFace(pCube, false, true);
        rotateTopFace(pCube, false, true);
        rotateRightFace(pCube, true, true);
        rotateTopFace(pCube, false, true);
        rotateTopFace(pCube, false, true);
        rotateRightFace(pCube, false, true);
    }
}


/**
 * Orients the cube to place the top corners
 *
 * @param pCube
 * Pointer to a cube struct
 *
 * @param faceColor
 * The color of the top face
 */
void orientCubeForTopCorners(Cube* pCube, Color faceColor)
{
    int numCornersOnTop = 0;
    
    // Check how many top face corners are oriented correctly
    if (pCube->pieces[TOP_LEFT_BACK_CORNER].z == faceColor)
    {
        ++numCornersOnTop;
    }
    if (pCube->pieces[TOP_LEFT_FRONT_CORNER].z == faceColor)
    {
        ++numCornersOnTop;
    }
    if (pCube->pieces[TOP_RIGHT_BACK_CORNER].z == faceColor)
    {
        ++numCornersOnTop;
    }
    if (pCube->pieces[TOP_RIGHT_FRONT_CORNER].z == faceColor)
    {
        ++numCornersOnTop;
    }
    
    if (numCornersOnTop == 0)
    {
        while (pCube->pieces[TOP_LEFT_FRONT_CORNER].x != faceColor)
        {
            turnZ(pCube, true);
        }
    }
    else if (numCornersOnTop == 1)
    {
        while (pCube->pieces[TOP_LEFT_FRONT_CORNER].z != faceColor)
        {
            turnZ(pCube, true);
        }
    }
    else if (numCornersOnTop == 2)
    {
        while (pCube->pieces[TOP_LEFT_FRONT_CORNER].y != faceColor)
        {
            turnZ(pCube, true);
        }
    }
}

/**
 * Checks if the top corners has been placed
 *
 * @param pCube
 * Pointer to a Cube struct
 *
 * @param faceColor
 * The color of the top face
 *
 * @return
 * True if top cross is solved
 * False if top cross is not solved
 */
bool checkTopCorners(Cube* pCube, Color faceColor)
{
    // Top corners placed
    if (pCube->pieces[TOP_LEFT_BACK_CORNER].z == faceColor && pCube->pieces[TOP_LEFT_FRONT_CORNER].z == faceColor
        && pCube->pieces[TOP_RIGHT_BACK_CORNER].z == faceColor && pCube->pieces[TOP_RIGHT_FRONT_CORNER].z == faceColor)
    {
        return true;
    }
    
    // Top corners not placed
    return false;
}

// Top corner solving functions

/**
 * Solves the top corners
 *
 * @param pCube
 * Pointer to a Cube struct
 */
void solveTopCorners(Cube* pCube)
{
    while(!(checkTopCornersSolved(pCube)))
    {
        orientCubeForTopCornerSwap(pCube);
        printCube(pCube);
        
        rotateRightFace(pCube, false, true);
        rotateFrontFace(pCube, false, true);
        rotateRightFace(pCube, false, true);
        rotateBackFace(pCube, true, true);
        rotateBackFace(pCube, true, true);
        
        rotateRightFace(pCube, true, true);
        rotateFrontFace(pCube, true, true);
        rotateRightFace(pCube, false, true);
        rotateBackFace(pCube, true, true);
        rotateBackFace(pCube, true, true);
        
        rotateRightFace(pCube, true, true);
        rotateRightFace(pCube, true, true);
        rotateTopFace(pCube, true, true);
    }
}

/**
 * Orients the cube to solve the top corners
 *
 * @param pCube
 * Pointer to a Cube struct
 */
void orientCubeForTopCornerSwap(Cube* pCube)
{
    Piece corner1 = pCube->pieces[TOP_LEFT_BACK_CORNER];
    Piece corner2 = pCube->pieces[TOP_RIGHT_BACK_CORNER];
    Piece corner3 = pCube->pieces[TOP_RIGHT_FRONT_CORNER];
    Piece corner4 = pCube->pieces[TOP_LEFT_FRONT_CORNER];
    
    Piece center1 = pCube->pieces[BACK_CENTER];
    Piece center2 = pCube->pieces[RIGHT_CENTER];
    Piece center3 = pCube->pieces[FRONT_CENTER];
    Piece center4 = pCube->pieces[LEFT_CENTER];

    
    // Loop until two corners are in the correct position
    while (!((corner1.x == center4.x && corner1.y == center1.y && ((corner2.x == center2.x && corner2.y == center1.y) || (corner3.x == center2.x && corner3.y == center3.y) || (corner4.x == center4.x && corner4.y == center3.y))) || (corner2.x == center2.x && corner2.y == center1.y && ((corner3.x == center2.x && corner3.y == center3.y) || (corner4.x == center4.x && corner4.y == center3.y))) || (corner3.x == center2.x && corner3.y == center3.y && corner4.x == center4.x && corner4.y == center3.y)))
    {
        rotateTopFace(pCube, true, true);
        
        corner1 = pCube->pieces[TOP_LEFT_BACK_CORNER];
        corner2 = pCube->pieces[TOP_RIGHT_BACK_CORNER];
        corner3 = pCube->pieces[TOP_RIGHT_FRONT_CORNER];
        corner4 = pCube->pieces[TOP_LEFT_FRONT_CORNER];
    }
    
    // Rotate Cube until two corners that are in place are located on the back face if orientation exists
    for (int i = 0; i < NUM_CENTER - 2; ++i)
    {
        if ((pCube->pieces[TOP_RIGHT_BACK_CORNER].x == pCube->pieces[RIGHT_CENTER].x)
            && (pCube->pieces[TOP_RIGHT_BACK_CORNER].y == pCube->pieces[BACK_CENTER].y)
            && (pCube->pieces[TOP_LEFT_BACK_CORNER].x == pCube->pieces[LEFT_CENTER].x)
            && (pCube->pieces[TOP_LEFT_BACK_CORNER].y == pCube->pieces[BACK_CENTER].y))
        {
            return;
        }
        turnZ(pCube, true);
    }
}

/**
 * Checks if the top corners are solved
 *
 * @param pCube
 * Pointer to a Cube struct
 */
bool checkTopCornersSolved(Cube* pCube)
{
    // Corners in place
    if ((pCube->pieces[TOP_RIGHT_FRONT_CORNER].x == pCube->pieces[RIGHT_CENTER].x) && (pCube->pieces[TOP_RIGHT_BACK_CORNER].x == pCube->pieces[RIGHT_CENTER].x)
        && (pCube->pieces[TOP_RIGHT_FRONT_CORNER].y == pCube->pieces[FRONT_CENTER].y) && (pCube->pieces[TOP_RIGHT_BACK_CORNER].y == pCube->pieces[BACK_CENTER].y)
        && (pCube->pieces[TOP_LEFT_FRONT_CORNER].x == pCube->pieces[LEFT_CENTER].x) && (pCube->pieces[TOP_LEFT_BACK_CORNER].x == pCube->pieces[LEFT_CENTER].x)
        && (pCube->pieces[TOP_LEFT_FRONT_CORNER].y == pCube->pieces[FRONT_CENTER].y) && (pCube->pieces[TOP_LEFT_BACK_CORNER].y == pCube->pieces[BACK_CENTER].y))
    {
        return true;
    }
    // Corners not in place
    return false;
}

// Solve top edges

/**
 * Solves the top edges of the cube
 *
 * @param pCube
 * Pointer to a Cube struct
 */
void solveTopEdges(Cube* pCube)
{
    // Iterate while edge pieces are not in place
    while (!(checkTopEdgeSolved(pCube)))
    {
        
        // Places a solved face in the back position
        orientCubeForTopEdgeSolve(pCube);
        
        // Algorithm to rotate 3 edge pieces
        rotateFrontFace(pCube, false, true);
        rotateFrontFace(pCube, false, true);
        rotateTopFace(pCube, false, true);
        rotateLeftFace(pCube, false, true);
        rotateRightFace(pCube, false, true);
        rotateFrontFace(pCube, false, true);
        rotateFrontFace(pCube, false, true);
        rotateLeftFace(pCube, true, true);
        rotateRightFace(pCube, true, true);
        rotateTopFace(pCube, false, true);
        rotateFrontFace(pCube, false, true);
        rotateFrontFace(pCube, false, true);
    }
}

/**
 * Orients the cube so top edges can be solved, places solved face in the back position
 *
 * @param pCube
 * Pointer to a Cube struct
 */
void orientCubeForTopEdgeSolve(Cube* pCube)
{
    // Iterate until the function returns
    for(int i = 0; i < NUM_CENTER - 2; ++i)
    {
        for (int j = 0; j < NUM_PIECES_IN_ROW; ++j)
        {
            // Turn the cube 90 degrees if current face isn't solved
            if (pCube->pieces[BACK_POS[j]].y != pCube->pieces[BACK_CENTER].y)
            {
                turnZ(pCube, true);
                printCube(pCube);
                break;
            }
            // Return to caller if back face is completely solved
            if (j == NUM_PIECES_IN_ROW - 1)
            {
                return;
            }
        }
    }
}

/**
 * Checks if the top edges are in the correct position
 *
 * @param pCube
 * Pointer to a Cube struct
 *
 * @return
 * True if edges are in the correct position
 * False if edges are in the incorrect position
 */
bool checkTopEdgeSolved(Cube* pCube)
{
    if ((pCube->pieces[TOP_BACK_EDGE].y == pCube->pieces[BACK_CENTER].y)
        && (pCube->pieces[TOP_LEFT_EDGE].x == pCube->pieces[LEFT_CENTER].x)
        && (pCube->pieces[TOP_RIGHT_EDGE].x == pCube->pieces[RIGHT_CENTER].x)
        && (pCube->pieces[TOP_FRONT_EDGE].y == pCube->pieces[FRONT_CENTER].y))
    {
        return true;
    }
    
    return false;
}
