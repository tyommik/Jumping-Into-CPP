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
 * 3. Напишите программу, которая находит элемент в связанном списке по его имени (хэшу).
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
    std::time_t Timestamp = std::time(nullptr);
    int number;
    Block * prevBlock;
};

Block * p_headBlock = nullptr;
unsigned blockCounter = 0;

void menu ();
void removeBlock();
void addBlock();
void findBlock();
void printBlocks();
void exit();
bool isEmpty();

bool isEmpty() {
    return (p_headBlock== nullptr);
}

void removeBlock() {
    if (!isEmpty()) {
        std::string hash_of_block;
        Block *checkingBlock = p_headBlock;
        std::cout << "Enter the hash of removing block: ";
        std::cin >> hash_of_block;

        Block *prevBlock = nullptr;
        while (checkingBlock) {
            //если нашли
            if (checkingBlock->hash == hash_of_block) {
                std::cout << "Removing block is:" << std::endl;
                std::cout << "Block number: " << checkingBlock->number << std::endl;
                std::cout << "Block SHA256: " << checkingBlock->hash << std::endl;
                std::cout << "Block created: " << checkingBlock->Timestamp << std::endl;
                //если удаляем HEAD блок
                if (checkingBlock == p_headBlock) {
                    p_headBlock = p_headBlock->prevBlock;
                } else if (!checkingBlock->prevBlock) {
                    prevBlock->prevBlock = nullptr;
                } else {
                    prevBlock->prevBlock = checkingBlock->prevBlock;
                }
                delete checkingBlock;
                return;

            }
            prevBlock = checkingBlock;
            checkingBlock = checkingBlock->prevBlock;
        }
    }
}

void addBlock() {
    Block * newBlock = new Block;
    newBlock->number = ++blockCounter;
    newBlock->prevBlock = p_headBlock;
    p_headBlock = newBlock;
}

void findBlock() {
    if (!isEmpty()) {
        std::string hash_of_block;
        Block * checkingBlock = p_headBlock;
        std::cout << "Enter the hash of block: ";
        std::cin >> hash_of_block;

        while (checkingBlock) {
            if (checkingBlock->hash == hash_of_block) {
                std::cout << "Finded block is:" << std::endl;
                std::cout << "Block number: " << checkingBlock->number << std::endl;
                std::cout << "Block SHA256: " << checkingBlock->hash << std::endl;
                std::cout << "Block created: " << checkingBlock->Timestamp << std::endl;
                return;
            }
            checkingBlock = checkingBlock->prevBlock;
        }
        std::cout << "Block not found!" << std::endl;
    } else {
        std::cout << "The blockchain is empty." << std:: endl;
    }
}

void printBlocks() {
    Block * iter = p_headBlock;
    if (!isEmpty()) {
        while (iter != nullptr) {
            std::cout << "Block number: " << iter->number << std::endl;
            std::cout << "Block SHA256: " << iter->hash << std::endl;
            std::cout << "Block created: " << iter->Timestamp << std::endl;
            iter = iter->prevBlock;
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
    menu();
    return 0;
}