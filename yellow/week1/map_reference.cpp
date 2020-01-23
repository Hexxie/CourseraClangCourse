#include <iostream>
#include <map>

using namespace std;

template <class A, class B>
B& GetRefStrict(map<A, B> m, const A& key) {
    auto search = m.find(key);
    if(search != m.end()){
        return search->second;
    } else {
        throw runtime_error("Element not found");
    }
}

int main()
{
    map<int, string> m = {{0, "value"}};
    string& item = GetRefStrict(m, 1);
    item = "newvalue";
    cout << m[0] << endl;
    return 0;
}