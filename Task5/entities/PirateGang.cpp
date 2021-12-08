#include "PirateGang.h"
#include <iostream>
#include <thread>

void PirateGang::setStatus(Status status) {
    this->status = status;
    std::cout << "!!!status" << this->status;
}

std::pair<int, int> PirateGang::getNextCell() const {
    return std::make_pair(PirateGang::last_move % island.getHorizontalSize(),
                          PirateGang::last_move / island.getVerticalSize());
}

void PirateGang::findTreasure(bool *found, std::queue<PirateGang> *workers) {
//    std::cout << gang_number << " created\n";
    while (true) {
        while (status == Status::WAITING) {
            this->status = this->status;
            // Waiting.
//            std::cout << "Waiting" << status << '\n';
        }

        if (status == Status::DONE) {
            return;
        }

        std::cout << "Gang " << gang_number << " is searching now\n";
        std::this_thread::sleep_for(std::chrono::milliseconds(10000 / number_of_pirates));

        std::pair<int, int> next_move = getNextCell();

        if (island.checkNextPart(next_move)) {
            std::cout << "YEAH! Gang " << gang_number << " found treasure on "
                      << next_move.first << ' ' << next_move.second;
            *found = true;

        } else {
            std::cout << "sad... Gang " << gang_number << " could not find anything interesting on "
                      << next_move.first << ' ' << next_move.second;
            if (status != Status::DONE) {
                status = Status::WAITING;
            }
            workers->push(*this);
        }
        ++PirateGang::last_move;
        island.out();

        std::cout << std::endl;
    }
}

int PirateGang::getGangNumber() const {
    return gang_number;
}

int PirateGang::last_move = 0;