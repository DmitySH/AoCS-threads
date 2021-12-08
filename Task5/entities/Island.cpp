#include <iostream>
#include "Island.h"

void Island::out() const {
    for (int i = 0; i < vertical_size; ++i) {
        for (int j = 0; j < horizontal_size; ++j) {
            std::cout << island[i][j] << ' ';
        }

        std::cout << '\n';
    }
}

int Island::getHorizontalSize() const {
    return horizontal_size;
}

int Island::getVerticalSize() const {
    return vertical_size;
}

int Island::random(int from, int to) {
    return from + rand() % (to - from + 1);
}

bool Island::checkNextPart(std::pair<int, int> current_cell) {
    if (current_cell == treasure) {
        island[current_cell.first][current_cell.second] = 'X';
        return true;
    }
    island[current_cell.first][current_cell.second] = '+';
    return false;
}
