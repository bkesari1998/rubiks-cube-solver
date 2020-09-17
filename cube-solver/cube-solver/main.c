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
#include "cubeSolve.h"
#include "rubiksDefAssignments.h"

FILE* fp_instruct = NULL;
VECTOR hVector = NULL;

int main(int argc, const char * argv[]) {
    
    // Create references to colors array and Cube object
    char colorArr[NUM_SQUARES];
    Cube rubiks;
    
    // Initialized vector to hold the instructions array
    hVector = vector_init();
    
    // Open empty instruction file for reading and writing
    fp_instruct = fopen("/Users/bharatkesari/Documents/rubiks-cube-solver/cube-solver/cube-solver/instr.txt", "w+");
    
    // Check that file opened correctly, exit function if file opened incorrectly
    if (fp_instruct == NULL)
    {
        fprintf(stderr, "Could not open 'instr.txt'.\n");
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
    
    optimizeInstructions();
    vector_print_data(hVector, fp_instruct);
    
    vector_destroy(&hVector);
    
    // Close instuction files
    fclose(fp_instruct);
    
    return 0;
}
