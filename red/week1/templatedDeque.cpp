/**
 * @file templatedDeque.cpp
 * @author arusakova (arusakova917@gmail.com)
 * @brief
 * @version 0.1
 * @date 2020-03-21
 *
 * @copyright Copyright (c) 2020
 *
 * To compile if test_runner in include directory upper:
 * g++ -std=c++17 -I.. templatedDeque.cpp -o deque
 */

#include <vector>
#include <stdexcept>

#include "include/test_runner.h"

using namespace std;

template <typename T>
class Deque {
public:
    Deque(){
        m_size = 0;
    }
    bool Empty() const
    {
        return m_size == 0;
    }
    size_t Size() const
    {
        return m_size;
    }

    T& operator[](int index)
    {
        return At(index);
    }
    const T& operator[](int index) const
    {
        return At(index);
    }

    T& At(int index){
        if(index >= m_size) {
            throw out_of_range("Index out of range");
        }

        if(isFront(index)){
            return front[front.size() - index - 1];
        } else {
            return back[index - front.size()];
        }
    }

    const T& At(int index) const
    {
        if(index >= m_size) {
            throw out_of_range("Index out of range");
        }

        if(isFront(index)){
            return front.at(front.size() - index - 1);
        } else {
            return back.at(index - front.size());
        }
    }

    const T& Front() const
    {
        return At(0);
    }

    T& Front()
    {
        return (*this)[0];
    }

    T& Back()
    {
        return (*this)[m_size - 1];
    }

    const T& Back() const
    {
        return At(m_size - 1);
    }

    void PushFront(T item){
        front.push_back(item);
        m_size++;
    }

    void PushBack(T item) {
        back.push_back(item);
        m_size++;
    }
private:
    vector<T> front;
    vector<T> back;
    size_t m_size;

    bool isFront(int index) const {
        return front.size() > index;
    }
};

void DequeIsCreatingTest() {
    Deque<int> d_int;
    Deque<string> d_string;
    Deque <vector<int>> d_vector;
}

void PushFrontAddToFront() {
    Deque<int> d_int;
    d_int.PushFront(1);
    d_int.PushFront(2);
    d_int.PushFront(3);

    AssertEqual(d_int.Size(), 3, "PushFrontAddToFront");
}

void PushBackAddToBack() {
    Deque<int> d_int;
    d_int.PushBack(1);
    d_int.PushBack(2);
    d_int.PushBack(3);

    AssertEqual(d_int.Size(), 3, "PushBackAddToBack");
}

void MixedPushReturnsCorrectSize() {
    Deque<int> d_int;
    d_int.PushBack(1);
    d_int.PushBack(2);
    d_int.PushBack(3);
    d_int.PushFront(1);
    d_int.PushFront(2);
    d_int.PushFront(3);

    AssertEqual(d_int.Size(), 6, "MixedPushReturnsCorrectSize");
}

void PushFrontPopFronAllowModification() {
    Deque<int> d_int;
    d_int.PushFront(1);
    d_int.PushFront(2);
    d_int.PushFront(3);

    AssertEqual(d_int.Front(), 3, "PushFrontPopFronAllowModification1");

    int &p = d_int.Front();
    p = 5;

    AssertEqual(d_int.Front(), 5, "PushFrontPopFronAllowModification2");
}

void PushBackPopBackAllowModification() {
    Deque<int> d_int;
    d_int.PushBack(1);
    d_int.PushBack(2);
    d_int.PushBack(3);

    AssertEqual(d_int.Back(), 3, "PushBackPopBackAllowModification1");

    int &p = d_int.Back();
    p = 5;

    AssertEqual(d_int.Back(), 5, "PushBackPopBackAllowModification2");
}

void PushBackPopFront() {
    Deque<int> d_int;
    d_int.PushBack(1);
    d_int.PushBack(2);
    d_int.PushBack(3);

    AssertEqual(d_int.Front(), 1, "PushBackPopFront");
}

void PushFrontPopBack() {
    Deque<int> d_int;
    d_int.PushFront(1);
    d_int.PushFront(2);
    d_int.PushFront(3);

    AssertEqual(d_int.Back(), 1, "PushFrontPopBack");
}

void FrontReturnsOutOfRangeExceptionForEmptyArray() {
    Deque<int> d_int;

    try {
        d_int.Front();
        AssertEqual(1, 2, "FrontReturnsOutOfRangeExceptionForEmptyArray");
    } catch (out_of_range &ex) {
    }
}

void BackReturnsOutOfRangeExceptionForEmptyArray() {
    Deque<int> d_int;

    try {
        d_int.Back();
        AssertEqual(1, 2, "BackReturnsOutOfRangeExceptionForEmptyArray");
    } catch (out_of_range &ex) {
    }
}




int main() {
    TestRunner runner;
    RUN_TEST(runner, DequeIsCreatingTest);
    RUN_TEST(runner, PushFrontAddToFront);
    RUN_TEST(runner, PushBackAddToBack);
    RUN_TEST(runner, MixedPushReturnsCorrectSize);
    RUN_TEST(runner, PushFrontPopFronAllowModification);
    RUN_TEST(runner, PushBackPopBackAllowModification);
    RUN_TEST(runner, PushBackPopFront);
    RUN_TEST(runner, PushFrontPopBack);
    RUN_TEST(runner, FrontReturnsOutOfRangeExceptionForEmptyArray);
    RUN_TEST(runner, BackReturnsOutOfRangeExceptionForEmptyArray);

    return 0;
}