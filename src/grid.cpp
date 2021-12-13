#include <iostream>
#include "grid.h"


Grid::Grid() {
    bit_array = new bool[NUM_ROWS * NUM_COLS];
    for (int i = 0; i < NUM_ROWS; i++) {
        for (int j = 0; j < NUM_COLS; j++) {
            set_cell(i, j, false);
        }
    }
}


void Grid::set_cell(int i, int j, bool is_alive) {
    bit_array[i*NUM_COLS + j] = is_alive;
}


bool Grid::get_cell_at(int i, int j) {
    return bit_array[i*NUM_COLS + j];
}


void Grid::update() {
    // update the grid according to the rules specified by conways game of life
}


Grid::~Grid() {
    delete[] bit_array;
}
