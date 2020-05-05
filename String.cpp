#include "String.hpp"
#include <iostream>

String::String() {
    string = new char[16];
}

String::String(const char* string){
    this->string = new char[strlen(string) + 1];
    strcpy(this->string, string);
}

String::String(const String& other) {
    copy(other);
}

String& String::operator=(const String& other) {
    if(this != &other) {
        erase();
        copy(other);
    }
    return *this;
}

String& String::operator+=(const String& other) {
    resize(strlen(string) + strlen(other.string));
    strcat(string, other.string);
    return *this; 
}

bool String::operator!=(const String& other) {
    return strcmp(string, other.string);
}

bool String::operator==(const String& other) {
    return !strcmp(string, other.string);
}

std::ostream& operator<<(std::ostream& os, const String& str) {
    os << str.to_cstr();
    return os;
}

const char* String::to_cstr() const {
    return string;
}

int String::length() const {
    return strlen(string);
}

char& String::operator[](int pos) {
    return string[pos];
}

String::~String() {
    erase();
}

String operator+(const String& one, const String& two) {
    String result(one);
    result += two;   
    return result;
}

std::istream& operator>>(std::istream& is, String& str) {
    is >> str.string;
    return is;
}

int String::count_words() const {
    int result = 1;
    for(int i = 0; i < length(); i++) {
        if(string[i] == ' ') result++;
    }
    return result;
}