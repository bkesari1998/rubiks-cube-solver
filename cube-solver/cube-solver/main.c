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
InstructLink* instrList = NULL;

int main(int argc, const char * argv[]) {
    char colorArr[NUM_SQUARES];
    Cube rubiks;

    instrList = createNextLink(instrList);
    const InstructLink* head = instrList;
    
    InstructLink* instrLink_processed = NULL;
    instrLink_processed = createNextLink(instrLink_processed);
    InstructLink* head_processed = instrLink_processed;
    
    // Open empty instruction file for reading and writing
    fp_instruct = fopen("/Users/bharatkesari/Documents/Rubiks-Cube-Solver/rubiks-cube-solver/cube-solver/cube-solver/instr.txt", "w+");
    
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

    optimizeInstruct((InstructLink*)head);
    printInstruct((InstructLink*)head, fp_instruct);
    rewind(fp_instruct);
    
    // Read each instruction from instructions file and store in a linked list
    char ch;
    int ret = fscanf(fp_instruct, "%c", &ch);
    while (ret != EOF)
    {
        // Create new link if necessary
        if (instrLink_processed->next != NULL || instrLink_processed->instr_index >= INSTR_SIZE)
        {
            instrLink_processed = createNextLink(instrLink_processed);
        }
        // Do not read spaces into linked list
        if (ch != ' ')
        {
            instrLink_processed->instrArr[instrLink_processed->instr_index++] = ch;
        }
        ret = fscanf(fp_instruct, "%c", &ch);
    }
    
    // Open empty instruction file for writing to hold re-optimized instructions
    FILE* fp_instruct2 = fopen("/Users/bharatkesari/Documents/Rubiks-Cube-Solver/rubiks-cube-solver/cube-solver/cube-solver/instr2.txt", "w");
    
    // Check that file opened correctly, exit function if file opened incorrectly
    if (fp_instruct2 == NULL)
    {
        fprintf(stderr, "Could not open 'instr2.txt'.\n");
        exit(1);
    }
    
    // Re-optimize the instructions and print them to a file
    optimizeInstruct((InstructLink*)head_processed);
    printInstruct((InstructLink*)head_processed, fp_instruct2);
    
    // Close instuction files
    fclose(fp_instruct);
    fclose(fp_instruct2);
    
    return 0;
}
