#include <iostream>
#include <vector>
using namespace std;
int main()
{
    vector<int> numbers;
    numbers.push_back(67);
    numbers.push_back(70);
    numbers.pop_back();
    numbers.push_back(78);
    numbers.push_back(88);
    numbers.push_back(68);
    cout << "size : " << numbers.size() << endl;
    cout << "last element: " << numbers.back() << endl;
    cout << "first element: " << numbers.front() << endl;
}