#ifndef DA_LAB2_PATRICIA_H
#define DA_LAB2_PATRICIA_H

#include <memory>
#include "my_string.h"

struct TNode {
    TNode();
    unsigned long long Value;
    TString* Key;
    int BitId;
    TNode* LeftPtr;
    TNode* RightPtr;
    ~TNode();
};

struct TPatricia {
    TNode* Head;
    TPatricia();
    TNode* Search(TString& SKey);
    bool Insert(TString* IKey, unsigned long long& IValue);
    bool Delete(TString& DKey);

    ~TPatricia();
    void RecursiveDestruct(TNode* node);
};

bool BitGet(TString& key, int32_t bitId);
int32_t LeftMost(TString& key1, TString& key2);

#endif //DA_LAB2_PATRICIA_H
