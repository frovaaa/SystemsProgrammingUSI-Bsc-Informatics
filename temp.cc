#include <iostream>
#include <vector>
#include <string>

using namespace std;

void print_values(const vector<int> &);

int main(int argc, char const *argv[])
{
    if (argc < 2)
    {
        cout << "Usage: " << argv[0] << " <nItems> <item1> <item2> <...> <itemn>" << endl;
        return 1;
    }

    int count = stoi(argv[1]);

    cout << "Count: " << count << endl;

    vector<int> test;

    count++;

    for (unsigned i = 1; i <= count; i++)
    {
        int currentVal = stoi(argv[i]);
        test.push_back(currentVal);
        // cout << "Pushed back value " << currentVal << endl;
    }

    print_values(test);
    return 0;
}

void print_values(const vector<int> & v)
{
    for (int val : v)
    {
        cout << "Val: " << val << endl;
    }
}