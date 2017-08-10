#include <string>
#include <utility>
#include <iostream>

using std::string;

void foo(string& l_ref) {
    std::cout << "In the lvalue function." << std::endl;
}

void foo(string&& r_ref) {
    std::cout << "In the rvalue function." << std::endl;
}

int main() {
    string s;

    string& s_ref1 = s; // b is an lvalue reference, bind to a, cannot rebind after binding
    // string&& s_ref2 = s; // ERROR: anything with a name is a lvalue, a is not considered as an rvalue
    string&& s_ref3 = std::move(s); // must explicitly use std::move to convert 'a' to an rvalue

    ////// usage
    // 1. rvalue reference can bind to a temporary value.
    string&& s_ref4 = string();
    // string& s_ref5 = string(); // ERROR: cannot bind a lvalue reference to a temporary value
    const string& s_ref6 = string(); // this is fine, can bind a cosnt-lvalue reference to a temporary value

    string& s_ref7 = s_ref4; //OK, it's fine to bind an lvalue reference to an rvalue reference, but not the other way around, see #9

    // 2. overload resolution
    foo(s_ref1); // call lvalue version
    foo(s_ref4); // N.B. this would still call lvalue version
                 // Because it's OK to bind a lvalue reference to a rvalue reference.
    foo(string()); // This would call the rvalue version, because cannot bind a lvalue reference to a temporary value.
}
