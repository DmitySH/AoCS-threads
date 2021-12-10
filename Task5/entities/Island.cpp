#include <iostream>
#include <mutex>
#include "Island.h"
#include "PirateGang.h"

std::mutex lock_island;

void Island::out() const {
    std::cout << '\n';
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
    std::lock_guard<std::mutex> guard(lock_island);
    if (current_cell == treasure) {
        island[current_cell.second][current_cell.first] = 'X';
        out();
        return true;
    }
    island[current_cell.second][current_cell.first] = 'O';
    {
        std::lock_guard<std::mutex> guard(PirateGang::lock_out);
        out();
    }
    return false;
}
