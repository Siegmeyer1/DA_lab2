#include <iostream>
#include "patricia.h"
#include "my_string.h"

TNode::TNode() : Value{0}, BitId{-1}, LeftPtr{nullptr}, RightPtr{nullptr}, Key{nullptr} {}

TNode::~TNode() {
    LeftPtr = nullptr;
    RightPtr = nullptr;
    delete Key;
}

TPatricia::TPatricia() {
    Head = nullptr;
}

TNode* TPatricia::Search(TString& SKey) {//проверено на ошибки в алгоритме
    if (Head == nullptr) {
        std::cout << "NoSuchWord\n";
        return nullptr;
    }
    TNode* previous = this->Head;
    TNode* current = this->Head->LeftPtr;
    while(previous->BitId < current->BitId) {
        previous = current;
        current = BitGet(SKey, current->BitId) ? current->RightPtr : current->LeftPtr;
    }
    if (*current->Key == SKey) {
        std::cout << "OK: " << current->Value << '\n';
    } else {
        std::cout << "NoSuchWord\n";
        return nullptr;
    }
    return current;
}

bool TPatricia::Insert(TString* IKey, unsigned long long& IValue) {//проверено на ошибки в алгоритме
    if (this->Head == nullptr) {
        auto newNode = new TNode;
        newNode->Value = IValue;
        newNode->Key = IKey;
        newNode->RightPtr = nullptr;
        newNode->LeftPtr = newNode;
        this->Head = newNode;
        std::cout << "OK\n";
        return true;
    } else {
        //search//
        TNode* previous = this->Head;
        TNode* current = this->Head->LeftPtr;
        while(previous->BitId < current->BitId) {
            previous = current;
            current = BitGet(*IKey, current->BitId) ? current->RightPtr : current->LeftPtr;
        }
        //end-of-search//
        if (*current->Key == *IKey) {
            std::cout << "Exist\n";
            delete IKey;
            return false;
        }
        TNode* newNode = new TNode;
        newNode->Value = IValue;
        newNode->Key = IKey;
        newNode->BitId = LeftMost(*IKey, *current->Key);
        //search-again//
        previous = this->Head;
        current = this->Head->LeftPtr;
        while((current->BitId > previous->BitId) && (current->BitId < newNode->BitId)) {
            previous = current;
            current = BitGet(*IKey, current->BitId) ? current->RightPtr : current->LeftPtr;
        }
        //end-of-another-search//
	if (BitGet(*IKey, newNode->BitId)) {
	    newNode->LeftPtr = current;
	    newNode->RightPtr = newNode;
	} else {
	    newNode->LeftPtr = newNode;
	    newNode->RightPtr = current;
	}
        if (current == previous->RightPtr) {
            previous->RightPtr = newNode;
        } else {
            previous->LeftPtr = newNode;
        }
    }
    std::cout << "OK\n";
    return true;
}

bool TPatricia::Delete(TString& DKey) {
    if (Head == nullptr) {
        std::cout << "NoSuchWord\n";
        return false;
    }
    if (Head->LeftPtr == Head) {
        if (*Head->Key == DKey) {
            delete Head;
            Head = nullptr;
            std::cout << "OK\n";
            return true;
        } else {
            std::cout << "NoSuchWord\n";
            return false;
        }
    }//если хэдер - единственный нод
    TNode *prePrev = nullptr, *parOfPrev = nullptr, *previous = Head, *current = Head->LeftPtr;
    while (previous->BitId < current->BitId) {
        prePrev = previous;
        previous = current;
        current = BitGet(DKey, current->BitId) ? current->RightPtr : current->LeftPtr;
    }//ищем удаляемый нод
    if (!(*current->Key == DKey)) {
        std::cout << "NoSuchWord\n";
        return false;
    }//не нашли :(
    if (current == previous) {
        if (prePrev->LeftPtr == current) {
            prePrev->LeftPtr = (current->LeftPtr == current ? current->RightPtr : current->LeftPtr);
        } else {
            prePrev->RightPtr = (current->LeftPtr == current ? current->RightPtr : current->LeftPtr);
        }
        delete current;
        std::cout << "OK\n";
        return true;
    }//если у нода есть селф-поинтер, то мы просто выпиливаем его с пути, поинтер с отца
    // переходит туда, куда ведёт НЕселф-поинтер удаляемого нода. Отец - точно отец, т.к. от него точно не бэквард-поинтер был.
    TNode *p = current, *q = previous, *qPar = prePrev, *r = nullptr; //новые обозначения как в учебнике, иначе я с ума сойду
    current = Head->LeftPtr;
    r = Head;
    while (r->BitId < current->BitId) {//ищем бэквард, по которому мы попали в q
        r = current;
        current = BitGet(*q->Key, current->BitId) ? current->RightPtr : current->LeftPtr;
    }
    bool rLocationFlag = BitGet(*r->Key, q->BitId); //флаг, отражающий, справа ли находится r по отношению к q в дереве.
    // нужен, чтобы понять, через какого ребёнка q мы нашли r
    if (r->RightPtr == q) r->RightPtr = p;
    else r->LeftPtr = p;
    if (qPar->RightPtr == q) {
        qPar->RightPtr = rLocationFlag ? q->RightPtr : q->LeftPtr;
    } else {
        qPar->LeftPtr = rLocationFlag ? q->RightPtr : q->LeftPtr;
    }
    *p->Key = *q->Key;
    p->Value = q->Value;
    delete q;
    std::cout << "OK\n";
    return true;

}

void TPatricia::RecursiveDestruct(TNode *node) {
    if (node == nullptr) {
        return;
    }
    if ((node->LeftPtr->BitId > node->BitId)/*&& (node->RightPtr != this->Head)*/) {
        RecursiveDestruct(node->LeftPtr);
    }
    if ((node->RightPtr != nullptr) && (node->RightPtr->BitId > node->BitId) /*&& (node->RightPtr != this->Head)*/) {
        RecursiveDestruct(node->RightPtr);
    }
    delete node;
}

TPatricia::~TPatricia() {
    /*if (Head != nullptr) {
        if (Head->LeftPtr != Head) RecursiveDestruct(Head->LeftPtr);
        delete Head;
    }*/
    RecursiveDestruct(Head);
}

bool BitGet(TString& key, int32_t bitId) {
    if (bitId < 0) {
        return false;
    }
    uint32_t byteNo = bitId / 8;
    uint8_t bitNo = bitId % 8;
    uint8_t symb;
    if (byteNo >= key.size) {
        //symb = '\0';
        return false;
    } else {
        symb = key.mass[byteNo];
    }
    //uint8_t bit = (symb >> (uint8_t)(7 - bitNo)) % 2;
    //return bit;
    return (symb & (128 >> bitNo)) != 0;
}

int32_t LeftMost(TString& key1, TString& key2) {
    int32_t i = 0;
    int max_size = std::max(key1.size, key2.size);
    while (key1.mass[i] == key2.mass[i]) {
        i++;
        if (i == max_size) {
            std::cout << "wrong answer\n";
            return i*8;
        }
    }
    i*=8;
    while(BitGet(key1, i) == BitGet(key2, i)) { //можно чуть-чуть улучшить
        i++;
    }
    return i;
}
