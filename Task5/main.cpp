#include <iostream>
#include <thread>
#include "entities/PirateGang.h"

#include <queue>
#include <string>
#include <mutex>


int parseInt(int min, int max) {
    std::string input;
    std::cin >> input;
    int res;

    bool is_correct = false;
    while (!is_correct) {
        try {
            res = std::stoi(input);
            if (res < min || res > max) {
                throw std::invalid_argument("Invalid argument");
            }

            is_correct = true;
        } catch (std::invalid_argument &ex) {
            std::cout << "Incorrect input!" << '\n';
            is_correct = false;
            std::cin >> input;
        }
    }

    return res;
}

void createGangs(std::vector<PirateGang *> *gangs, int pirates_number, Island *island) {
    int number_of_gangs = 0;
    while (pirates_number > 0) {
        std::cout << pirates_number << " pirates left\n";
        std::cout << "Next group" << number_of_gangs + 1 << " will contain " << "\n";

        int next_size = parseInt(1, pirates_number);
        gangs->push_back(new PirateGang(number_of_gangs + 1, next_size, island));

        pirates_number -= next_size;
        ++number_of_gangs;
    }
}

void searchForTreasure(std::vector<PirateGang *> gangs, Island *island) {
    std::cout << "Searching started!\n";
    std::vector<std::thread> threads;
    std::queue<PirateGang *> workers;
    bool *is_found = new bool(false);

    int max_cells = island->getVerticalSize() * island->getHorizontalSize();

    auto *trs = new std::thread[gangs.size()];

    for (int i = 0; i < gangs.size(); ++i) {
        trs[i] = std::thread(&PirateGang::findTreasure, std::ref(gangs[i]), is_found, &workers);
        workers.push(gangs[i]);
    }

    std::this_thread::sleep_for(std::chrono::milliseconds(300));

    for (int i = 0; i < max_cells; ++i) {
        while (workers.empty()) {
            if (*is_found) {
                break;
            }

            // Waiting.
        }
        if (*is_found) {
            break;
        }

        PirateGang *current = workers.front();

        current->setStatus(Status::WORKING);
        workers.pop();
    }
    while (!*is_found) {

    }

    for (int i = 0; i < gangs.size(); ++i) {
        gangs[i]->setStatus(Status::DONE);
    }

    for (int i = 0; i < gangs.size(); ++i) {
        trs[i].join();
    }
    std::cout << "DONE!";
    delete is_found;
    delete[] trs;
}

int main() {
    srand(time(0));

    std::cout << "Enter horizontal size [0; 100]:\n";
    int horizontal_size = parseInt(1, 100);

    std::cout << "Enter vertical size [0; 100]:\n";
    int vertical_size = parseInt(1, 100);

    Island *island = new Island(horizontal_size, vertical_size);
    island->out();

    std::cout << "Enter number of pirates:\n";
    int pirates_number = parseInt(1, 300);

    std::vector<PirateGang *> gangs;
    createGangs(&gangs, pirates_number, island);

    searchForTreasure(gangs, island);

    for (auto gang: gangs) {
        delete gang;
    }
    delete island;
    return 0;
}
