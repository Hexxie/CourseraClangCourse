#include <iostream>
#include <vector>
#include <map>
#include <utility>

using namespace std;

template<typename T> T FuncA(T x);
template<typename T> void FuncB(T x);

template <typename First, typename Second>
pair<First, Second> operator *(const pair<First, Second>& p1,
                               const pair<First, Second> &p2) {
    First f = p1.first * p2.first;
    Second s = p1.second * p2.second;

    return {f, s};
}

template <typename Key , typename Value>
map<Key , Value> Sqr(map<Key , Value> vi) {
    for(auto& i : vi) {
        i.second = i.second * i.second;
    }

    return vi;
}

template <typename T>
vector<T> Sqr(vector<T> vi) {
    for(T& i : vi) {
        i = i * i;
    }

    return vi;
}

template <typename T>
T Sqr(T x) {
    return x * x;
}

int main()
{
    vector<int> v = {1, 2, 3};
    cout << "vector:";
    for (int x : Sqr(v)) {
        cout << ' ' << x;
    }
    cout << endl;

    map<int, pair<int, int>> map_of_pairs = {
    {4, {2, 2}},
    {7, {4, 3}}
    };
    cout << "map of pairs:" << endl;
    for (const auto& x : Sqr(map_of_pairs)) {
        cout << x.first << ' ' << x.second.first << ' ' << x.second.second << endl;
    }
    return 0;
}