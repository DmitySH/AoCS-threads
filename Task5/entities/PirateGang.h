#ifndef TASK5_PIRATEGANG_H
#define TASK5_PIRATEGANG_H

#include <queue>
#include "Island.h"

enum Status {
    WAITING,
    WORKING,
    DONE,
};

class PirateGang {
public:
    PirateGang(int group_number, int number_of_pirates, Island island) {
        this->gang_number = group_number;
        this->number_of_pirates = number_of_pirates;
        this->island = island;
        status = Status::WAITING;
        last_move = 0;
    }

    ~PirateGang() = default;

    void findTreasure(bool *found, std::queue<PirateGang> *workers);

    void setStatus(Status status);

    int getGangNumber() const;

    static int last_move;


private:
    Status status;
    int gang_number;
    int number_of_pirates;
    Island island;
    std::pair<int, int> getNextCell() const;
};

#endif
