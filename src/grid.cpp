#include <iostream>
#include "grid.h"
#include <vector>
#include <stdlib.h>


Grid::Grid() {
    bit_array = new bool[NUM_ROWS * NUM_COLS];
	probability = 0;
    clear();
}


void Grid::set_cell(int row, int col, bool is_alive) {
    // Set value at (row, col) to is_alive
    bit_array[row*NUM_COLS + col] = is_alive;
}

bool Grid::get_cell(int row, int col) {
    // Return value at (row, col)
    return bit_array[row*NUM_COLS + col];
}

bool Grid::in_bounds(int row, int col) {
    // Return true if (row, col) is in bounds
    return (row >= 0 && row < NUM_ROWS && col >= 0 && col < NUM_COLS);
}

int Grid::count_neighbors(int row, int col) {
    int live_neighbors = 0;
    // Iterate through all 8 adjacent cells
    for(int i = row - 1; i < row + 2; i++) {
        for(int j = col - 1; j < col + 2; j++) {
            // Make sure it is within the bounds of the grid
            if(in_bounds(i, j)) {
                // Make sure it is not the cell at (row, cell)
                if(!(i == row && j == col)) {
                    // If there is a cell at (i, j), increment live_neighbors
                     if(get_cell(i, j)) {
                        live_neighbors++;
                    }
                }
            }
        }
    }

    return live_neighbors;
}

void Grid::update() {
    // Update the grid based on rules to Conway's Game of Life
    // Any live cell with fewer than two live neighbours dies, as if by underpopulation.
    // Any live cell with two or three live neighbours lives on to the next generation.
    // Any live cell with more than three live neighbours dies, as if by overpopulation.
    // Any dead cell with exactly three live neighbours becomes a live cell, as if by reproduction.
    bool* updated_bit_array = new bool[NUM_ROWS * NUM_COLS];

    for(int i = 0; i < NUM_ROWS; i++) {
        for(int j = 0; j < NUM_COLS; j++) {
            updated_bit_array[i * NUM_COLS + j] = bit_array[i * NUM_COLS + j];
            int live_neighbors = count_neighbors(i, j);
            // If the cell is alive
            if(get_cell(i, j)) { 
                // Set the cell to dead is it does not have 2 or 3 live neighbors
                if(live_neighbors < 2 || live_neighbors > 3) {
                    updated_bit_array[i*NUM_COLS + j] = false;
                }
            // If the cell is dead
            } else { 
                // Set the cell to alive if it has exactly 3 neighbors
                if(live_neighbors == 3) {
                    updated_bit_array[i*NUM_COLS + j] = true;
                }
            }
        }
    }

	// inject some randomness into the mix
    for(int i = 0; i < NUM_ROWS; i++) {
        for(int j = 0; j < NUM_COLS; j++) {
			int rand_num = rand() % 100;
			if (rand_num < probability) {
				updated_bit_array[i*NUM_COLS + j] = true;
			}
		}
	}


    // Store previous state in prev_states vector
    prev_states.push_back(bit_array);
    // Update the bit array
    bit_array = updated_bit_array;
}

void Grid::prev_state() {
    // Make sure there is history to rewind to
    if(prev_states.size() > 0) {
        // Rewind one step and delete entry in vector
        bit_array = prev_states[prev_states.size() - 1];
        prev_states.pop_back();
    }
}

void Grid::clear() {
    for (int i = 0; i < NUM_ROWS; i++) {
        for (int j = 0; j < NUM_COLS; j++) {
            set_cell(i, j, false);
        }
    }
}

void Grid::incr_prob() {
	probability++;
}

void Grid::decr_prob() {
	probability--;
}
Grid::~Grid() {
    delete[] bit_array;
}
