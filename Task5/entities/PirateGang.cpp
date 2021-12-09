#include "PirateGang.h"
#include <iostream>
#include <thread>
#include <mutex>

std::mutex lock;
std::mutex lock_queue;

Status PirateGang::getStatus() {
    return status_;
}


void PirateGang::setStatus(Status status) {
    this->status_ = status;
}

std::pair<int, int> PirateGang::getNextCell(Island *island) {
    std::lock_guard<std::mutex> guard(lock);
    auto next = std::make_pair(PirateGang::last_move % island->getHorizontalSize(),
                               PirateGang::last_move / island->getHorizontalSize());
    increaseLastMove();

    return next;
}

void PirateGang::findTreasure(bool *found, std::queue<PirateGang *> *workers) {
    while (true) {
        while (status_ == Status::WAITING) {
        }

        if (status_ == Status::DONE) {
            {
                std::lock_guard<std::mutex> guard(lock_out);
                std::cout << "Gang " << gang_number << " returned\n";
            }
            return;
        }
        std::pair<int, int> next_move = getNextCell(island);


        {
            std::lock_guard<std::mutex> guard(lock_out);
            std::cout << "Gang " << getGangNumber()
                      << " is looking for treasure at " <<
                      next_move.first << ' '
                      << next_move.second
                      << "\n\n";
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(15000 / number_of_pirates));

        if (island->checkNextPart(next_move)) {
            {
                std::lock_guard<std::mutex> guard(lock_out);
                std::cout << "YEAH! Gang " << gang_number << " found treasure on "
                          << next_move.first << ' ' << next_move.second << " at " << clock() / 1000000.0 << '\n';
            }
            *found = true;
            status_ = Status::DONE;
        } else {
            {
                std::lock_guard<std::mutex> guard(lock_out);
                std::cout << "sad... Gang " << gang_number << " could not find anything interesting on "
                          << next_move.first << ' ' << next_move.second << " at " << clock() / 1000000.0 << '\n';
            }
            if (!*found) {
                status_ = Status::WAITING;
            } else {
                status_ = Status::DONE;
            }

            {
                std::lock_guard<std::mutex> guard(lock_queue);
                workers->push(this);
            }
        }
    }
}

int PirateGang::getGangNumber() const {
    return gang_number;
}

int PirateGang::last_move = 0;

void PirateGang::increaseLastMove() {
    ++last_move;
}

std::mutex PirateGang::lock_out;
