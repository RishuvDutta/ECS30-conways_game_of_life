/* 
 * Rishi Dutta 912790628
 * conways_game_of_life.c
 * The game functions including creating the new generations
 * Uses many functions together to determine if each cell survives
 * the next generation or is born
 */
#include "conways_game_of_life.h"

#include <stdio.h>
#include <stdlib.h>

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
BinaryMatrix* FirstGeneration(int num_rows, int num_cols, List* seed_cells) {
    BinaryMatrix* result = ConstructBinaryMatrix(num_rows, num_cols);
    int size = seed_cells->size;
    ListNode* new_node = seed_cells->head;
    Coordinate coord = seed_cells->head->data;
    for (int i = 0; i < size; i++){
        UpdateEntry(result, coord.x, coord.y, 1);
        if (i != (size - 1)){
            new_node = new_node->next;
            coord = new_node->data; 
        }
    }
    return result;
}

/*
 * Input:
 *      BinaryMatrix* generation, a pointer to a game state
 * Output:
 *      Returns a BinaryMatrix*, a pointer to a game state
 * Summary:
 *      Calculates the game state of the generation directly
 *      after *generation and returns it
 */

BinaryMatrix* NextGeneration(BinaryMatrix* generation) {
    BinaryMatrix* result = ConstructBinaryMatrix(generation->num_rows, generation->num_cols);
    int a = 0;
    for (int i = 0; i < generation->num_rows; i++){
        for (int j = 0; j < generation->num_cols; j++){
            a = LivingNeighbors(generation, NeighboringCells(ConstructCoordinate(i,j), generation));
            if ((a == 3) && (generation->data[i][j] == 0)){
                result->data[i][j] = 1;
            }
            if (((a == 2) || (a == 3)) && (generation->data[i][j] == 1)){
                result->data[i][j] = 1;
            }
            if ((a >=4) && (generation->data[i][j] == 1)){
                result->data[i][j] = 0;
            }
            if ((a <= 1) && (generation->data[i][j] == 1)){
                result->data[i][j] = 0;
            }
        }
    }
    return result;                  
}

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
int Live(BinaryMatrix* generation, Coordinate coord) {
    if (IsMatrixIndex(generation, coord.x, coord.y)){
        int i = coord.x;
        int j = coord.y;
        if (generation->data[i][j] ==  1){
            return 1;
        }
        else {
            return 0;
        }
    }
    else {
        return 0;
    }
}

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
List* NeighboringCells(Coordinate coord, BinaryMatrix* generation) {
    List* result = ConstructList();
    int i, j;
    if (result == (List*) NULL) {
        printf("Error in NeighboringCells: List construction failed\n");
        exit(EXIT_FAILURE);
    }
    for (i = -1; i <= 1; i++) {
        for (j = -1; j <= 1; j++) {
            Coordinate coord_neighbor = ConstructCoordinate(coord.x + i, coord.y + j);
            if (IsNeighbor(coord, coord_neighbor) && IsMatrixIndex(generation, coord.x + i, coord.y + j)) {
                PushFrontList(result, coord_neighbor);
            }
        }
    }
    return result;
}

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
int LivingNeighbors(BinaryMatrix* generation, List* neighbors) {
    int live = 0;
    int size = neighbors->size;
    ListNode* new_node = neighbors->head;
    Coordinate coord = neighbors->head->data;
    for (int i = 0; i < size; i++){
        if (Live(generation, coord)){
                live++;
        }
        if (i != (size - 1)){
            new_node = new_node->next;
            coord = new_node->data;
        }
    }
    return live;
}

/*
 * Input:
 *      BinaryMatrix* generation, a pointer to a game state
 *      FILE* fp, a file opened for writing
 * Summary:
 *      Prints the game state of *generation to *fp
 */
void PrintGeneration(BinaryMatrix* generation, FILE* fp) {
    int i, j;
    for (i = 0; i < generation->num_rows; i++) {
        for (j = 0; j < generation->num_cols; j++) {
            if (Live(generation, ConstructCoordinate(i, j))) {
                fprintf(fp, "#");
            } else {
                fprintf(fp, " ");
            }
        }
        fprintf(fp, "\n");
    }
    return;
}
