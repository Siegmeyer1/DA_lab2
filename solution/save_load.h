#ifndef DA_LAB2_SAVE_LOAD_H
#define DA_LAB2_SAVE_LOAD_H

#include "patricia.h"
#include "my_string.h"
#include <fstream>

int Save(TPatricia& tree, /*TString**/char* filePath);
int RecursiveSave(TNode* node, std::ofstream& file);

int Load(TPatricia& tree, /*TString**/char* filePath);

#endif //DA_LAB2_SAVE_LOAD_H
