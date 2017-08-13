#include <cstring>
#include <algorithm>
#include <iostream>

class string {
    char* data;

public:
    string(const char* p) {
        size_t size = strlen(p) + 1;
        data = new char[size];
        memcpy(data, p, size);
    }

    ~string() {
        delete[] data;
    }

    string(const string& that) {
        std::cout << "copy constructor called" << std::endl;
        size_t size = strlen(that.data) + 1;
        data = new char[size];
        memcpy(data, that.data, size);
    }

    string(string&& that) { // move constructro
        data = that.data;
        that.data = nullptr;
    }

    // assignment operator
    string& operator=(string that) {
        std::swap(data, that.data);
        return *this;
    }

    friend string operator+(const string lhs, const string& rhs) {
        size_t lhs_size = strlen(lhs.data);
        size_t rhs_size = strlen(rhs.data);
        char* data = new char[lhs_size + rhs_size + 1];
        memcpy(data, lhs.data, lhs_size + 1);
        strcpy(data, rhs.data);
        return string(data);
    }
};

string getString() {
    return string("world");
}

int main() {
    string x("nihao");
    string y("hello");

    string a(x);            // Line 1
    string b(x+y);          // Line 2
    string c(getString());  // Line 3

    // only line 1 is necessary, because we don't want 'a' and 'x' to be the same object.

    // Line 2 and Line 3 they are not lvalues, but rvalues.
}
