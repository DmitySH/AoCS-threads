#include <iostream>
#include <thread>
#include "entities/PirateGang.h"

#include <queue>
#include <string>
#include <mutex>
#include <fstream>


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

void createGangsConsole(std::vector<PirateGang *> *gangs, int pirates_number, Island *island) {
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

void createGangsFile(std::ifstream *in, std::vector<PirateGang *> *gangs, int pirates_number, Island *island) {
    int number_of_gangs = 0;
    while (pirates_number > 0) {
        std::string line;
        getline(*in, line);;
        int next_size = std::stoi(line);
        gangs->push_back(new PirateGang(number_of_gangs + 1, next_size, island));
        pirates_number -= next_size;
        ++number_of_gangs;
    }
}


std::pair<Island *, std::vector<PirateGang *> *> fileInput(std::string path) {
    std::string line;
    std::ifstream *in = new std::ifstream(path);
    int horizontal_size, vertical_size, pirates_number;
    if (in->is_open()) {
        getline(*in, line);
        horizontal_size = stoi(line);
        getline(*in, line);
        vertical_size = stoi(line);
        getline(*in, line);
        pirates_number = stoi(line);
    }
    auto gangs = new std::vector<PirateGang *>;
    Island *island = new Island(horizontal_size, vertical_size);
    createGangsFile(in, gangs, pirates_number, island);

    in->close();
    delete in;

    return std::make_pair(island, gangs);
}

void searchForTreasure(std::vector<PirateGang *> *gangs, Island *island) {
    std::cout << "Searching started!\n";
    std::vector<std::thread> threads;
    std::queue<PirateGang *> workers;
    bool *is_found = new bool(false);

    int max_cells = island->getVerticalSize() * island->getHorizontalSize();

    auto *trs = new std::thread[gangs->size()];

    for (int i = 0; i < gangs->size(); ++i) {
        trs[i] = std::thread(&PirateGang::findTreasure, std::ref((*gangs)[i]), is_found, &workers);
        workers.push((*gangs)[i]);
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

    for (int i = 0; i < gangs->size(); ++i) {
        (*gangs)[i]->setStatus(Status::DONE);
    }

    for (int i = 0; i < gangs->size(); ++i) {
        trs[i].join();
    }
    std::cout << "DONE!";
    delete is_found;
    delete[] trs;
}


std::pair<Island *, std::vector<PirateGang *> *> consoleInput() {
    std::cout << "Enter horizontal size of an island [1; 100]:\n";
    int horizontal_size = parseInt(1, 100);

    std::cout << "Enter vertical size of an island [1; 100]:\n";
    int vertical_size = parseInt(1, 100);

    Island *island = new Island(horizontal_size, vertical_size);
    island->out();

    std::cout << "Enter number of pirates [1; 300]:\n";
    int pirates_number = parseInt(1, 300);
    auto gangs = new std::vector<PirateGang *>;
    createGangsConsole(gangs, pirates_number, island);

    return std::make_pair(island, gangs);
}

int main() {
    srand(time(0));
    std::pair<Island *, std::vector<PirateGang *> *> pair;
    std::string line;

    std::cout << "Enter f for file input\n";
    std::cout << "Enter c for console input\n";
    std::cin >> line;

    if (line == "f") {
        std::cout << "enter path for file (ex: ../tests/test<number>.txt)\n";
        std::cin >> line;
        try {
            pair = fileInput(line);
        } catch (std::exception &ex) {
            std::cout << "Incorrect input!";
            return 1;
        }
    } else if (line == "c") {
        pair = consoleInput();
    } else {
        std::cout << "Incorrect input!";
        return 1;
    }

    searchForTreasure(pair.second, pair.first);

    for (auto gang: *(pair.second)) {
        delete gang;
    }

    delete pair.first;
    delete pair.second;

    return 0;
}
