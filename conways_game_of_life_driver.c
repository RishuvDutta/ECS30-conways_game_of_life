/*
 * conways_game_of_life_driver.c
 * Name / StudentID
 * A driver for conways_game_of_life.h
 * Reads a seed (starting generation) from a file and runs 
 * Conways' Game of Life, printing to stdout
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "conways_game_of_life.h"
#include "coordinate.h"

int main(int argc, char* argv[]) {
    FILE* fp;
    List* seed;
    BinaryMatrix* current_generation, *next_generation;
    int rows, cols, generations, i;
    struct timespec sleep_time;
    sleep_time.tv_sec = 0;
    sleep_time.tv_nsec = 500000000L;
    if (argc != 5) {
        printf("Usage: %s <filename> <rows> <columns> <generations>\n", argv[0]);
        exit(EXIT_FAILURE); 
    }
    /* Get first generation cells */
    fp = fopen(argv[1], "r");
    seed = ReadList(fp);
    fclose(fp);
    /* Get game parameters */
    sscanf(argv[2], "%d", &rows);
    sscanf(argv[3], "%d", &cols);
    sscanf(argv[4], "%d", &generations);
    /* Run game */
    current_generation = FirstGeneration(rows, cols, seed);
    PrintGeneration(current_generation, stdout);
    for (i = 1; i < generations; i++) {
        nanosleep(&sleep_time, NULL);
        next_generation = NextGeneration(current_generation);
        DeleteBinaryMatrix(current_generation);
        current_generation = next_generation;
        printf("\033[H\033[J");
        printf("\033[%d;%dH", 0, 0);
        PrintGeneration(current_generation, stdout);
    }
    DeleteBinaryMatrix(current_generation);
    DeleteList(seed);
    return 0;
}
