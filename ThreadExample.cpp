#include <iostream>
#include <thread>
using namespace std;
void Printing1(int start, int end)
{
    this_thread::sleep_for(chrono::seconds(3));
    for (int i = start; i <= end; i++)
    {
        cout << i << endl;
    }
}

void Printing2(int start, int end)
{
    for (int i = start; i <= end; i++)
    {
        cout << i << endl;
    }
}
int main()
{
    thread t(Printing1, 1, 10);
    thread t2(Printing2, 11, 20);
    t.detach();
    t2.join();
    cout << " thread ends " << ends;
}