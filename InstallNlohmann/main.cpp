#include <iostream>
#include "json.hpp"
using namespace std;
using json = nlohmann::json;
int main()
{
    json obj = {
        {"name", "naveen"},
        {"age", 20},
        {"skills", {"c++", "Rust", "Python"}}};
    cout << obj.dump(4) << endl;
}
