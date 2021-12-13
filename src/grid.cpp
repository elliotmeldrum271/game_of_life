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

bool Grid::get_cell(int i, int j) {
    return bit_array[i*NUM_COLS + j];
}

bool Grid::in_bounds(int row, int col) {
    return (row >= 0 && row < NUM_ROWS && col >= 0 && col < NUM_COLS);
}

void Grid::print_neighbors() {

    std::cout << "in print neighbors\n";
    for(int i = 0; i <  NUM_ROWS; i++) {
        for(int j = 0; j < NUM_COLS; j++) {
            std::cout << get_cell(i, j) << " ";
        }
        std::cout << std::endl;
    }

    std::cout << "end of print neighbors" << std::endl;

}

int Grid::count_neighbors(int row, int col) {


    int live_neighbors = 0;
    for(int i = row - 1; i < row + 2; i++) {
        for(int j = col - 1; j < col + 2; j++) {
            if(in_bounds(i, j)) {
                if(!(i == row && j == col)) {
                     if(get_cell(i, j)) {
                        live_neighbors++;
                    }
                }
            }
        }
    }

    //std::cout << "Cell (" << row << ", " << col << ") has " << live_neighbors << " neighbors." << std::endl;

    return live_neighbors;
}

void Grid::update() {
    // update the grid according to the rules specified by conways game of life
    // Any live cell with fewer than two live neighbours dies, as if by underpopulation.
    // Any live cell with two or three live neighbours lives on to the next generation.
    // Any live cell with more than three live neighbours dies, as if by overpopulation.
    // Any dead cell with exactly three live neighbours becomes a live cell, as if by reproduction.
    bool* updated_bit_array = new bool[NUM_ROWS * NUM_COLS];

    // std::cout << "count neighbors before" << std::endl;
    // for(int i = 0; i < NUM_ROWS; i++) {
    //     for(int j = 0; j < NUM_COLS; j++) {
    //         std::cout << count_neighbors(i, j) << " ";
    //     }
    //     std::cout << std::endl;
    // }

    //     std::cout << "\nidxs\n" << std::endl;
    // for(int i = 0; i < NUM_ROWS; i++) {
    //     for(int j = 0; j < NUM_COLS; j++) {
    //         std::cout << "(" << i << "," << j <<")" << " ";
    //     }
    //     std::cout << std::endl;
    // }

    for(int i = 0; i < NUM_ROWS; i++) {
        for(int j = 0; j < NUM_COLS; j++) {
            updated_bit_array[i * NUM_COLS + j] = bit_array[i * NUM_COLS + j];
            int live_neighbors = count_neighbors(i, j);
            if(get_cell(i, j)) { // live
                if(live_neighbors < 2 || live_neighbors > 3) {
                    //std::cout << "Cell (" << i << ", " << j << ") is dying with " << live_neighbors << " live neighbors." << std::endl;
                    //std::cout << "before " << updated_bit_array[i*NUM_COLS + j] << std::endl;
                    updated_bit_array[i*NUM_COLS + j] = false;
                    //std::cout << "after " << updated_bit_array[i*NUM_COLS + j] << std::endl;
                }
            } else { // dead
                if(live_neighbors == 3) {
                    updated_bit_array[i*NUM_COLS + j] = true;
                }
            }
        }
    }

    bool* old_bit_array = bit_array;
    bit_array = updated_bit_array;
    delete[] old_bit_array;  

    // std::cout << "count neighbors after" << std::endl;
    // for(int i = 0; i < NUM_ROWS; i++) {
    //     for(int j = 0; j < NUM_COLS; j++) {
    //         std::cout << count_neighbors(i, j) << " ";
    //     }
    //     std::cout << std::endl;
    // }
    // print_neighbors();

    std::cout << get_cell(2, 1) << std::endl;

    // for(int i = 0; i < NUM_ROWS; i++) {
    //     for(int j = 0; j < NUM_COLS; j++) {
    //         bit_array[i * NUM_COLS + j] = updated_bit_array[i * NUM_COLS + j];
    //     }
    // }

    // delete[] updated_bit_array; 
}


Grid::~Grid() {
    delete[] bit_array;
}
