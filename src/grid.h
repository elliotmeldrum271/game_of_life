// Header file for the grid that conway's game of life takes place on
#ifndef __GRID_H
#define __GRID_H

#include <vector>

const int NUM_ROWS = 60;
const int NUM_COLS = 60;


class Grid {
    private:
        bool* bit_array;
        int count_neighbors(int row, int col);
        bool in_bounds(int row, int col);
        std::vector<bool*> prev_states;
    public:
        Grid();
        bool get_cell(int i, int j);
        void set_cell(int i, int j, bool is_alive);
        void update();
        void prev_state();
        void clear();
        ~Grid();
};

#endif
