#include <iostream>
#include <thread>
#include "entities/PirateGang.h"
#include "entities/Island.h"

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

void createGangs(std::vector<PirateGang> *gangs, int pirates_number, Island island) {
    int number_of_gangs = 0;
    int i = 1;
    while (pirates_number > 0) {
        std::cout << pirates_number << " pirates left\n";
        std::cout << "Next group" << i << " will contain " << "\n";

        int next_size = parseInt(1, pirates_number);
        gangs->push_back(PirateGang(i, pirates_number, island));

        pirates_number -= next_size;
        ++number_of_gangs;
    }
}

void searchForTreasure(std::vector<PirateGang> gangs, Island island) {
    std::cout << "Searching started!\n";
    std::vector<std::thread> threads;
    std::queue<PirateGang> workers;
    bool *is_found = new bool(false);

    int max_cells = island.getVerticalSize() * island.getHorizontalSize();

    auto *trs = new std::thread[gangs.size()];
    for (int i = 0; i < gangs.size(); ++i) {
        trs[i] = std::thread(&PirateGang::findTreasure, std::ref(gangs[i]), is_found, &workers);
    }

    for (int i = 0; i < std::min(static_cast<int>(gangs.size()), max_cells); ++i) {
        workers.push(gangs[i]);
    }

    for (int i = 0; i < max_cells; ++i) {


        while (workers.empty()) {
            // Waiting.
        }
        if (*is_found) {
            break;
        }

        PirateGang current = workers.front();
//        static std::mutex mtx; // глобальная область
//        { /*Область выполнения с общими ресурсами*/
//            mtx.lock();
//            std::cout << "Gang " << current.getGangNumber()
//                      << " is looking for treasure at " <<
//                      PirateGang::last_move % island.getHorizontalSize() << ' '
//                      << PirateGang::last_move / island.getVerticalSize()
//                      << "\n\n";
            std::cout << "HERE" << current.getGangNumber();

//            mtx.unlock();
//        }


        current.setStatus(Status::WORKING);
//        workers.pop();
    }


    while (!*is_found) {
    }

    std::cout << "DONE!";
}

int main() {
    srand(time(0));

    std::cout << "Enter horizontal size [0; 100000]:\n";
    int horizontal_size = parseInt(1, 100000);

    std::cout << "Enter vertical size [0; 100000]:\n";
    int vertical_size = parseInt(1, 100000);

    Island island(horizontal_size, vertical_size);
    island.out();

    std::cout << "Enter number of pirates:\n";
    int pirates_number = parseInt(1, 300);

    std::vector<PirateGang> gangs;
    createGangs(&gangs, pirates_number, island);

    searchForTreasure(gangs, island);

//    PirateGang pirate;
//
//    std::thread(&PirateGang::findTreasure, std::ref(pirate));
//    name.join();
    return 0;
}
