//
//  globalConst.h
//  cube-solver
//
//  Created by Bharat Kesari on 7/5/20.
//  Copyright © 2020 Bharat Kesari. All rights reserved.
//

#ifndef globalVars_h
#define globalVars_h

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

#endif /* globalVars_h */
