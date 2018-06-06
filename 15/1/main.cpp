//
// Created by a.shibaev on 31.05.2018.
//

/*
 * 1. Напишите программу, которая удаляет элемент из связного списка. Функция, выполняющая удаление,
 * должна принимать в качестве аргумента только удаляемый элемент. Легко ли написать эту функцию?
 * Будет ли она быстро работать? Можно ли упростить или ускорорить её работу, добавив в список указатель?
 *
 * 2. Напишите программу, которая добавляет элементы в связанный список в порядке его сортировки,
 * а не в начало
 *
 * 3. Напишите программу, которая находит элемент в связанном списке по его имени.
 */

#include <iostream>
#include <string>
#include <ctime>

std::string randomHash();

std::string randomHash() {
    char s[6];
    for (unsigned int i = 0; i != 6; i++) {
        s[i] = 'A' + rand() % 26;
    }

    return std::string(s);
}

struct Block {
    std::string hash = randomHash();
    std::string Data;
    std::string Timestamp;
    int number;
    Block * nextBlock;
};

Block * p_headBlock = nullptr;
unsigned blockCounter = 0;

void menu ();
void removeBlock();
void addBlock();
void findBlock();
void printBlocks();
void exit();


void removeBlock() {

}

void addBlock() {
    Block * newBlock = new Block;
    newBlock->number = ++blockCounter;
    newBlock->nextBlock = p_headBlock;
    p_headBlock = newBlock;
}

void findBlock() {

}

void printBlocks() {
    Block * iter = p_headBlock;
    if (p_headBlock != nullptr) {
        while (iter != nullptr && iter->nextBlock != nullptr) {
            std::cout << iter->number << std::endl;
            std::cout << iter->hash << std::endl;
            iter = iter->nextBlock;
            std::cout <<std::endl;
        }
    }
}

void exit() {

}

void menu () {
    int item;
    enum menuList {REMOVE = 1, ADD, FIND, PRINT, EXIT};
    do {
        std::cout << "\nPlease choose an option" << std::endl;
        std::cout << "1. Remove block" << std::endl;
        std::cout << "2. Add block" << std::endl;
        std::cout << "3. Find block by hash" << std::endl;
        std::cout << "4. Print full list" << std::endl;
        std::cout << "5. Exit" << std::endl;
        std::cout << "Item: ";
        std::cin >> item;
        std::cout << std::endl;
        switch (item) {
            case REMOVE:
                removeBlock();
                break;
            case ADD:
                addBlock();
                break;
            case FIND:
                findBlock();
                break;
            case PRINT:
                printBlocks();
                break;
            case EXIT:
                exit();
                break;
            default:
                exit();
        }

    } while (item != EXIT);
}

int main () {
    srand(time(nullptr));
//    addBlock();
//    std::cout << randomHash();
    menu();
    return 0;
}