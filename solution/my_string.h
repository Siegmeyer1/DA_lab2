#ifndef DA_LAB2_MY_STRING_H
#define DA_LAB2_MY_STRING_H

#include <iostream>
#include <fstream>

class TString {
public:
    char *mass;
    size_t size;
    size_t cap;
    TString();
    explicit TString(size_t trgSize);
    explicit TString(const char *str);
    ~TString();
    void Clear();
    void PushBack(const char &c);
    void AddWord();
    void Print();
    void ToLower();
    bool operator==(TString& other);
    bool operator==(const char* other);
    TString& operator=(TString const& other);
    std::ofstream& operator<<(std::ofstream& out);
};

std::ofstream& operator<<(std::ofstream& out, TString& string);
std::ifstream& operator>>(std::ifstream& out, TString& string);

#endif //DA_LAB2_MY_STRING_H
