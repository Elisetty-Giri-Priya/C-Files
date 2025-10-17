#include <iostream>
#include <cstring>
using namespace std;
class Account
{
    // Attributes
public:
    string name;
    double balance;

    // methods
    void deposit(double amount)
    {
        balance += amount;
        cout << "updated Balance is: " << balance << endl;
    }
    bool withdraw(double amount)
    {
        balance -= amount;
        cout << "updated Balance is: " << balance << endl;
    }
};
int main()
{
    // Account jenny_Account;
    // jenny_Account.name = "hi";
    // jenny_Account.balance = 500.0;
    // jenny_Account.deposit(400);
    // jenny_Account.withdraw(400);

    Account* jenny_Account=new Account();//pointer to object
    (*jenny_Account).name="jayant";
    (*jenny_Account).balance=4000;
    (*jenny_Account).deposit(400);
    (*jenny_Account).withdraw(400); 

    return 0;
}