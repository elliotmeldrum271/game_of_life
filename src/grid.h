// Header file for the grid that conway's game of life takes place on
#ifndef __GRID_H
#define __GRID_H

const int NUM_ROWS = 50;
const int NUM_COLS = 50;

class Grid {
    private:
        bool* bit_array;
        int count_neighbors(int row, int col);
        bool in_bounds(int row, int col);
    public:
        Grid();
        bool get_cell(int i, int j);
        void set_cell(int i, int j, bool is_alive);
        void update();
        ~Grid();
};

#endif
