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
#include "rubiksConst.h"
#include "cubeUtils.h"
#include "cubeSolve.h"
#include "globalVars.h"

FILE* fp_instruct = NULL;

int main(int argc, const char * argv[]) {
    char colorArr[NUM_SQUARES];
    Cube rubiks;
    
    // Open instruction file for writing
    fp_instruct = fopen("/Users/bharatkesari/Documents/Rubiks-Cube-Solver/rubiks-cube-solver/cube-solver/cube-solver/instructions.txt", "w");
    
    // Check that file opened correctly, exit function if file opened incorrectly
    if (fp_instruct == NULL)
    {
        fprintf(stderr, "Could not open 'instructions.txt'.\n");
        exit(1);
    }
    
    // Get user input
    getColors(colorArr);
    createCube(&rubiks, colorArr);
    printCube(&rubiks);
    

    // Solve cube
    solveFirstLayerCross(&rubiks);
    printCube(&rubiks);
    solveFirstLayerCorners(&rubiks);
    printCube(&rubiks);
    solveMidLayerEdges(&rubiks);
    printCube(&rubiks);
    createTopCross(&rubiks);
    printCube(&rubiks);
    orientTopCorners(&rubiks);
    printCube(&rubiks);
    solveTopCorners(&rubiks);
    printCube(&rubiks);
    solveTopEdges(&rubiks);
    printCube(&rubiks);

    // Close instuction file
    fclose(fp_instruct);
    
    return 0;
}
