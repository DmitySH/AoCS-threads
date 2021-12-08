#ifndef TASK5_ISLAND_H
#define TASK5_ISLAND_H


#include <string>

class Island {
public:
    Island() = default;

    Island(int horizontal_size, int vertical_size) {
        this->horizontal_size = horizontal_size;
        this->vertical_size = vertical_size;

        island = new char *[vertical_size];
        for (int i = 0; i < vertical_size; ++i) {
            island[i] = new char [horizontal_size];
        }

        for (int i = 0; i < vertical_size; ++i) {
            for (int j = 0; j < horizontal_size; ++j) {
                island[i][j] = 'E';
            }
        }

        treasure = std::make_pair(horizontal_size, vertical_size);
    }

    bool checkNextPart(std::pair<int, int> current_cell);

    int getVerticalSize() const;
    int getHorizontalSize() const;
    void out() const;
private:
    int horizontal_size;
    int vertical_size;
    char **island;
    std::pair<int, int> treasure;

    static int random(int from, int to);
};


#endif
