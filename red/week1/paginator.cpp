/**
 * @file paginator.cpp
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2020-03-25
 *
 * @copyright Copyright (c) 2020
 *
 * To compile if test_runner in include directory upper:
 * g++ -std=c++17 -I.. paginator.cpp -o paginator
 */

#include "include/test_runner.h"

#include <numeric>
#include <iostream>
#include <vector>
#include <string>
using namespace std;

// Реализуйте шаблон класса Paginator

template <typename Iterator>
class Page {
private:
    Iterator first, last;

public:
    Page(Iterator f, Iterator l)
    : first(f)
    , last(l)
    {}

    Iterator begin() const
    {
        return first;
    }

    Iterator end() const
    {
        return last;
    }

    size_t size() const
    {
        return last - first;
    }
};

template <typename Iterator>
class Paginator {
private:
    Iterator m_begin, m_end;
    size_t m_pageSize;
    vector<Page<Iterator>> pages;

public:
    Paginator(Iterator begin, Iterator end, size_t size)
      : m_begin(begin)
      , m_end(end)
      , m_pageSize(size)
      {
          Iterator first_part = begin;
          int full_size = end - begin;
          if(full_size != 0) {
            bool continue_loop = true;
            while(continue_loop) {
                Iterator second_part = first_part + size;
                int chunkSize = second_part - begin;
                if(chunkSize >= full_size) {
                  second_part = end;
                  continue_loop = false;
                }
                pages.push_back({first_part, second_part});
                first_part = second_part;
            }
          }

      }

      typename vector<Page<Iterator>>::const_iterator begin() const {
          return pages.begin();
      }

      typename vector<Page<Iterator>>::const_iterator end() const {
          return pages.end();
      }

      size_t size() const {
          return pages.size();
      }
};


//Like makePair functionality
template <typename C>
auto Paginate(C& c, size_t page_size) {
  return Paginator(c.begin(), c.end(), page_size);
}

////////////// TESTS \\\\\\\\\\\\\\\\\\


void TestPageCounts() {
  vector<int> v(15);
 iota(begin(v), end(v), 1);
  ASSERT_EQUAL(Paginate(v, 1).size(), v.size());
  cout << "done 1"<<endl;
  ASSERT_EQUAL(Paginate(v, 3).size(), 5u);
    cout << "done 2"<<endl;
  ASSERT_EQUAL(Paginate(v, 5).size(), 3u);
    cout << "done 3"<<endl;
  ASSERT_EQUAL(Paginate(v, 4).size(), 4u);
    cout << "done 4"<<endl;
  ASSERT_EQUAL(Paginate(v, 15).size(), 1u);
    cout << "done 5"<<endl;
  ASSERT_EQUAL(Paginate(v, 150).size(), 1u);
    cout << "done 6"<<endl;
  ASSERT_EQUAL(Paginate(v, 14).size(), 2u);
    cout << "done 7"<<endl;
}

void TestLooping() {
  vector<int> v(15);
  iota(begin(v), end(v), 1);

  Paginator<vector<int>::iterator> paginate_v(v.begin(), v.end(), 6);
  ostringstream os;
  for (const auto& page : paginate_v) {
    for (int x : page) {
      os << x << ' ';
    }
    os << '\n';
  }

  ASSERT_EQUAL(os.str(), "1 2 3 4 5 6 \n7 8 9 10 11 12 \n13 14 15 \n");
}

void TestModification() {
  vector<string> vs = {"one", "two", "three", "four", "five"};
  for (auto page : Paginate(vs, 2)) {
    for (auto& word : page) {
      word[0] = toupper(word[0]);
    }
  }

  const vector<string> expected = {"One", "Two", "Three", "Four", "Five"};
  ASSERT_EQUAL(vs, expected);
}

void TestPageSizes() {
  string letters(26, ' ');

  Paginator letters_pagination(letters.begin(), letters.end(), 11);
  vector<size_t> page_sizes;
  for (const auto& page : letters_pagination) {
    page_sizes.push_back(page.size());
  }

  const vector<size_t> expected = {11, 11, 4};
  ASSERT_EQUAL(page_sizes, expected);
}

void TestConstContainer() {
  const string letters = "abcdefghijklmnopqrstuvwxyz";

  vector<string> pages;
  for (const auto& page : Paginate(letters, 10)) {
    pages.push_back(string(page.begin(), page.end()));
  }

  const vector<string> expected = {"abcdefghij", "klmnopqrst", "uvwxyz"};
  ASSERT_EQUAL(pages, expected);
}

void TestPagePagination() {
  vector<int> v(22);
  iota(begin(v), end(v), 1);

  vector<vector<int>> lines;
  for (const auto& split_by_9 : Paginate(v, 9)) {
    for (const auto& split_by_4 : Paginate(split_by_9, 4)) {
      lines.push_back({});
      for (int item : split_by_4) {
        lines.back().push_back(item);
      }
    }
  }

  const vector<vector<int>> expected = {
      {1, 2, 3, 4},
      {5, 6, 7, 8},
      {9},
      {10, 11, 12, 13},
      {14, 15, 16, 17},
      {18},
      {19, 20, 21, 22}
  };
  ASSERT_EQUAL(lines, expected);
}


int main() {
  TestRunner tr;
  RUN_TEST(tr, TestPageCounts);
  RUN_TEST(tr, TestLooping);
  RUN_TEST(tr, TestModification);
  RUN_TEST(tr, TestPageSizes);
  RUN_TEST(tr, TestConstContainer);
  RUN_TEST(tr, TestPagePagination);

}
