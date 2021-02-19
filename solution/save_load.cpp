#include <cstring>
#include "save_load.h"
#include "my_string.h"

int Save(TPatricia& tree, /*TString**/char* filePath) {
    std::ofstream file;
    file.open(filePath, std::ios_base::binary | std::ios_base::out);
    if (!file.is_open()) {
        std::cout << "ERROR: can`t open file\n";
        return -1;
    }
    if(!file.write("PATRICIA_LIB", 12)) {
        std::cout << "ERROR: can`t write to file\n";
        return -1;
    }
    if (tree.Head == nullptr) {
        char tmp[] = {"empty 0 -1\n"};
        if (!file.write(tmp, strlen(tmp))) {
            std::cout << "ERROR: can`t write to file\n";
            return -1;
        }
        std::cout << "OK\n";
        return 0;
    }
    if(!(file << *tree.Head->Key)) {
        std::cout << "ERROR: can`t write to file\n";
        return -1;
    }
    if(!(file << ' ' << tree.Head->Value << ' ' << tree.Head->BitId  << ' ' << 2020 << '\n')) {
        std::cout << "ERROR: can`t write to file\n";
        return -1;
    }
    if (tree.Head->LeftPtr == tree.Head) {
        std::cout << "OK\n";
        return 0;
    }
    if (RecursiveSave(tree.Head->LeftPtr, file) == 0) {
        std::cout << "OK\n";
        return 0;
    } else {
        std::cout << "ERROR: can`t write to file\n";
        return -1;
    }
}

int RecursiveSave(TNode* node, std::ofstream& file) {
    if(!(file << *node->Key)) {
        return -1;
    }
    if(!(file << ' ' << node->Value << ' ' << node->BitId << ' ' << 2020 << '\n')) {
        return -1;
    }

    int error = 0;
    if ((node->BitId <= node->LeftPtr->BitId) && (node->LeftPtr != node)) {
        error += RecursiveSave(node->LeftPtr, file);
    }
    if ((node->BitId <= node->RightPtr->BitId) && (node->RightPtr != node)) {
        error += RecursiveSave(node->RightPtr, file);
    }
    if (error != 0) return -1;
    return 0;
}

int Load(TPatricia& tree, /*TString**/char* filePath) {
    std::ifstream file;
    file.open(filePath, std::ios_base::binary | std::ios_base::in);
    if (!file.is_open()) {
        std::cout << "ERROR: can`t open file\n";
        return -1;
    }
    char formatKey[12];
    if (!file.read(formatKey, 12) || (strncmp(formatKey, "PATRICIA_LIB", 12) != 0)) {
        std::cout << "ERROR: wrong format1\n";
        return -1;
    }
    auto keyReadHead = new TString;
    int idRead;
    unsigned long long valRead;
    if (!(file >> *keyReadHead)) {
        std::cout << "ERROR: wrong format2\n";
        return -1;
    }
    if (*keyReadHead == "empty") { //MAY BE WRONG
        delete keyReadHead;
        std::cout << "OK\n";
        return 0;
    }
    int check;
    if(!(file >> valRead >> idRead >> check)) {
        std::cout << "ERROR: wrong format3\n";
        return -1;
    }
    if (check != 2020) {
        std::cout << "ERROR: wrong format3\n";
        return -1;
    }
    auto newNode = new TNode;
    newNode->Key = keyReadHead;
    newNode->Value = valRead;
    newNode->LeftPtr = newNode;
    tree.Head = newNode;
    file.get();

    TNode* previous = tree.Head;
    TNode* current = tree.Head->LeftPtr;

    while (true) {
        auto keyRead = new TString;
        file >> *keyRead;
        if (file.eof()) {
            std::cout << "OK\n";
            delete keyRead;
            return 0;
        }
        if(!(file >> valRead >> idRead >> check)) {
            std::cout << "ERROR: wrong format4\n";
            return -1;
        }
        if (check != 2020) {
            std::cout << "ERROR: wrong format4\n";
            return -1;
        }
        file.get();
        while ((previous->BitId < current->BitId) && (current->BitId < idRead)) {
            previous = current;
            current = BitGet(*keyRead, current->BitId) ? current->RightPtr : current->LeftPtr;
        }
        auto tmpNode = new TNode;
        tmpNode->Key = keyRead;
        tmpNode->Value = valRead;
        tmpNode->BitId = idRead;
        tmpNode->LeftPtr = BitGet(*keyRead, idRead) ? current : tmpNode;
        tmpNode->RightPtr = tmpNode->LeftPtr == current ? tmpNode : current;
        if (BitGet(*keyRead, previous->BitId)) {
            previous->RightPtr = tmpNode;
        } else {
            previous->LeftPtr = tmpNode;
        }
        previous = tree.Head;
        current = tree.Head->LeftPtr;
    }
}