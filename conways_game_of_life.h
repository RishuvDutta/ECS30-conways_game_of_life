/*
 * conways_game_of_life.h
 * Rishi Dutta 912790628
 * Header file for conways_game_of_life functions
 * Uses functions from list.c binary_matrix.c and coordinate.c
 */
#ifndef _CONWAYS_GAME_
#define _CONWAYS_GAME_
#include "list.h"
#include "binary_matrix.h"
#include "coordinate.h"

/*
 * Input:
 *      int num_rows, the number of rows in the game
 *      int num_cols, the number of cols in the game
 * Output:
 *      Returns a BinaryMatrix* that corresponds to the
 *      first generation game state
 * Summary:
 *      Returns the game state of the first generation
 */
BinaryMatrix* FirstGeneration(int num_rows, int num_cols, List* seed_cells);

/*
 * Input:
 *      BinaryMatrix* generation, a pointer to a game state
 * Output:
 *      Returns a BinaryMatrix*, a pointer to a game state
 * Summary:
 *      Calculates the game state of the generation directly
 *      after *generation and returns it
 */
BinaryMatrix* NextGeneration(BinaryMatrix* generation);

/*
 * Input:
 *      BinaryMatrix* generation, a pointer to a game state
 *      Coordinate coord, a cell of the game state
 * Output:
 *      Returns true if the cell is Live
 * Summary:
 *      Checks if coord is a valid index of *generation and
 *      its corresponding cell is Live
 */
int Live(BinaryMatrix* generation, Coordinate coord);

/*
 * Input:
 *      Coordinate coord, a cell of the game state
 *      BinaryMatrix* generation, a pointer to a game state
 * Output:
 *      Returns a List* to a List of neighboring cells
 * Summary:
 *      Calculates neighboring cells of *generation at coord and
 *      returns them as a List
 */
List* NeighboringCells(Coordinate coord, BinaryMatrix* generation);

/*
 * Input:
 *      BinaryMatrix* generation, a pointer to a game state
 *      List* neighbors, a List of neighbors of a coordinate
 * Output:
 *      Returns the number of neighboring cells that are Live
 * Summary:
 *      Counts the number of Coordinates in *neighbors that
 *      correspond to live cells in *generation
 */
int LivingNeighbors(BinaryMatrix* generation, List* neighbors);

/*
 * Input:
 *      BinaryMatrix* generation, a pointer to a game state
 *      FILE* fp, a file opened for writing
 * Summary:
 *      Prints the game state of *generation to *fp
 */
void PrintGeneration(BinaryMatrix* generation, FILE* fp);

#endif /*_CONWAYS_GAME_ */
