#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <string>

using namespace std;

int main(int argc, char const *argv[])
{
    vector<int> v;
    int temp;
    while (cin >> temp)
        v.push_back(temp);

    sort(v.begin(), v.end());

    for (vector<int>::iterator it = v.begin(); it != v.end(); ++it)
        cout << "VAL: " << *it << endl;
    ///////////////////////////////////////////////////////////////
    for (auto it = v.begin(); it != v.end(); ++it)
        cout << "VAL: " << *it << endl;
    ///////////////////////////////////////////////////////////////
    for (auto t : v)
        cout << "VAL: " << t << endl;

    map<int, string> m;
    auto i = m.insert({5, "CIAO"});

    return 0;
}
