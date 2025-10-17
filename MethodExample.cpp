#include <iostream>
using namespace std;
class car
{
public:
    string brand;
    int speed;
    void start()
    {
        cout << brand << "  is starting at " << speed << "km/h" << endl;
    }
    void run()
    {
        cout << brand << "  is running " << speed << "km/h" << endl;
    }
};
int main()
{
    car c1;
    c1.brand = "Bmw";
    c1.speed = 20;
    c1.start();
    c1.run();
}