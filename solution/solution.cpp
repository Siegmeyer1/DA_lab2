#include <iostream>
#include "patricia.h"
#include "my_string.h"
#include "save_load.h"

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    //TPatricia patricia;
    auto patricia = new TPatricia;
    //char c;
    unsigned long long val;
    /*while (true) {
        c = std::cin.get();
        if (c == EOF) {
            break;
        } else if (c == '+') {
            auto tmp = new TString;
            std::cin.get();
            tmp->AddWord();
            tmp->ToLower();
            std::cin >> val;
            std::cin.get();
            patricia->Insert(tmp, val);
        } else if (c == '-') {
            auto tmp = new TString;
            std::cin.get();
            tmp->AddWord();
            tmp->ToLower();
            patricia->Delete(*tmp);
            delete tmp;
        } else if (c == '!') {
            std::cin.get();
            auto tmp = new TString;
            tmp->AddWord();
            if (tmp->mass[0] == 'S') {
                //std::cout << "Saving to ";
                tmp->Clear();
                tmp->AddWord();
                //tmp->Print();
                //std::cout << '\n';
                Save(*patricia, tmp);
                delete tmp;
            } else {
                //std::cout << "Loading from ";
                tmp->Clear();
                tmp->AddWord();
                //tmp->Print();
                //std::cout << '\n';
                auto newPatricia = new TPatricia;
                Load(*newPatricia, tmp);
                delete patricia;
                patricia = newPatricia;
                delete tmp;
            }
        } else if (c == '\n') {
            continue;
        }
        else {
            auto tmp = new TString;
            tmp->PushBack(c);
            tmp->AddWord();
            tmp->ToLower();
            patricia->Search(*tmp);
            delete tmp;
        }
    }*/

    char str[264];
    while(std::cin >> str) {
        if (str[0] == '+') {
            std::cin >> str;
            std::cin >> val;
            auto tmp = new TString(str);
            tmp->ToLower();
            patricia->Insert(tmp, val);
        } else if (str[0] == '-') {
            std::cin >> str;
            auto tmp = new TString(str);
            tmp->ToLower();
            patricia->Delete(*tmp);
            delete tmp;
        }  else if (str[0] == '!') {
            std::cin >> str;
            if (str[0] == 'S') {
                std::cin >> str;
                //auto tmp = new TString(str);
                Save(*patricia, str);
                //delete tmp;
            } else {
                std::cin >> str;
                //auto tmp = new TString(str);
                auto newPatricia = new TPatricia;
                Load(*newPatricia, str);
                delete patricia;
                patricia = newPatricia;
                //delete tmp;
            }
        } else {
            auto tmp = new TString(str);
            tmp->ToLower();
            patricia->Search(*tmp);
            delete tmp;
        }
    }

    delete patricia;
    return 0;
}