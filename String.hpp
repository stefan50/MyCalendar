#ifndef STRING_HPP
#define STRING_HPP
#include <cstring>
#include <iostream>
#include <cstdlib>
#include "Vector.hpp"

class String {
private:
    char* string;
    void copy(const String& other) {
        string = new char[strlen(other.string) + 1];
        strcpy(string, other.string);
    }
    void erase() {
        delete[] string;
    }
    void resize(int length) {
        String temp(*this);
        erase();
        string = new char[length + 1];
        strcpy(string, temp.to_cstr());
    }
public:
    String();
    String(const char* string);
    String(const String& other);
    String& operator=(const String& other);
    String& operator+=(const String& other);
    bool operator!=(const String& other);
    bool operator==(const String& other);
    char& operator[](int pos);
    const char* to_cstr() const;
    int length() const;
    int count_words() const;
    bool contains(String key);
    friend std::istream& operator>>(std::istream& is, String& str);
    int to_int() const;
    Vector<String> split();
    ~String();
};

String operator+(const String& one, const String& two);
std::ostream& operator<<(std::ostream& os, const String& str);

#endif