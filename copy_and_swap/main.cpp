#include <algorithm>
#include <cstddef>

class dumb_array {
public:
    dumb_array(std::size_t size = 0): mSize(size), mArray(mSize ? new int[mSize]() : nullptr) {
    }

    // copy constructor
    dumb_array(const dumb_array& other): mSize(other.mSize), mArray(mSize ? new int[mSize]() : nullptr) {
        std::copy(other.mArray, other.mArray + mSize, mArray);
    }

    // move constructor
    dumb_array(dumb_array&& other): dumb_array() { // initialize via default constructor, C++11 only
        swap(*this, other);
    }

    ~dumb_array() {
        delete[] mArray;
    }

    dumb_array& operator=(dumb_array other) {
        swap(*this, other);
        return *this;
    }

    friend void swap(dumb_array& first, dumb_array& second) { // no throw
        // enable ADL
        using std::swap;

        swap(first.mSize, second.mSize);
        swap(first.mArray, second.mArray);
    }

private:
    std::size_t mSize;
    int* mArray;
};

// What is copy-and-swap idom?
// First, you need a working swap non-member friend function, which takes care of swaping the internal states of two objects.
// Second, you implement an assignment operator. An assignment operator is responsible for two steps:
// 1. tearing down the object's old inner state.
// 2. build its new state as a copy of some other object's state.
//
// Now if we use copy-by-value for assignment operator method's argument, this would re-use class's copy-constructor to build a temporary object, which is an independend copy of the outside object that we want to copy from.
// Then we re-use the overloaded swap function, which swaps the temporary object's state with the current internal state.
// Finally when method ends, the temporary object falls out of scope, and it gets destructed with the old states.
//
// A big beneft from having the assignment operator's parameter a value rather than a reference, is because in C++ 11, if we already have a move constructor, when the assignment operator's lhs is a rvalue, the move constructor will be picked up, instead of the copy constructor.

int main() {
}
