#include "my_string.h"
#include <iostream>
#include <cstring>

TString::TString() {
    mass = new char[2];
    size = 0;
    cap = 2;
}

TString::TString(size_t trgSize) { //?
    mass = new char[trgSize+1];
    size = 0;
    cap = trgSize+1;
}

TString::TString(const char *str) {
    /*mass = new char[2];
    size = 0;
    cap = 2;
    size_t length = strlen(str);
    for(size_t i = 0; i < length; ++i) {
        this->PushBack( (char)std::tolower(str[i]) );
    }*/
    cap = strlen(str)+1;
    mass = new char[cap];
    size = cap -1;
    std::copy(str, str + cap - 1, mass);
    this->PushBack('\0');
}

void TString::AddWord() {
    char c;
    while (true) {
        c = std::cin.get();
        if (c == ' ' || c == '\n' || c == EOF) {
            break;
        }
        this->PushBack(c);
    }
    this->PushBack('\0');
}

void TString::PushBack(const char &c) {
    if (size == cap) {
        cap *= 2;
        auto *newMass = new char[cap];
        std::copy(mass, mass + size, newMass);
        delete[] mass;
        mass = newMass;
    }
    mass[size] = c;
    size++;
}

TString::~TString() {
    delete[] mass;
    size = 0;
    cap = 0;
    mass = nullptr;
}

void TString::Clear() {
    delete[] mass;
    mass = new char[2];
    size = 0;
    cap = 2;
}

void TString::ToLower() {
    for (size_t i = 0; i < size; i++) {
        mass[i] = (char)std::tolower(mass[i]);
    }
}

void TString::Print() {
    for (size_t i = 0; i < size; i++) {
        std::cout << mass[i];
    }
}

bool TString::operator==(TString &other) {
    if (this->size != other.size) {
        return false;
    } else {
        for (size_t i = 0; i < size; i++) {
            if (this->mass[i] != other.mass[i]) {
                return false;
            }
        }
        return true;
    }
}

bool TString::operator==(const char *other) {
    if (this->size != strlen(other) + 1) {
        return false;
    } else {
        for (size_t i = 0; i < size; i++) {
            if (this->mass[i] != other[i]) {
                return false;
            }
        }
        return true;
    }
}

TString& TString::operator=(TString const &other) {
    delete[] mass;
    this->size = other.size;
    this->cap = other.cap;
    this->mass = new char[cap];
    std::copy(other.mass, other.mass + other.size, this->mass);
    return *this;
}

std::ofstream& TString::operator<<(std::ofstream &out) {
    /*for (size_t i = 0; i < size-1; i++) {
        out << mass[i];
    }*/
    out << mass;
    return out;
}

std::ofstream& operator<<(std::ofstream& out, TString& string) {
    /*for (size_t i = 0; i < string.size-1; i++) {
        out << string.mass[i];
    }*/
    out << string.mass;
    return out;
}

std::ifstream& operator>>(std::ifstream& in, TString& string) {
    char c;
    while (true) {
        c = in.get();
        if (c == ' ' || c == '\n' || c == EOF) {
            break;
        }
        string.PushBack(c);
    }
    string.PushBack('\0');

    return in;
}
