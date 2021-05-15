#ifndef CLASS_ATM_TREE__H
#define CLASS_ATM_TREE__H

#include <iostream>
using namespace std;

class Balance_ATM{
    int Amount;    // bills amount
    int Price;      //par value
public:
    Balance_ATM (int _Amount = 0,int _Price = 0);
    friend Balance_ATM *Get_data_ATM_from_file(char const *path);
    friend void Write_data_ATM_to_file(char const *path, Balance_ATM *data_ATM);
    friend bool check_money_of_ATM(Balance_ATM *_data_ATM,long amount_needed);
    void change_no_of_balance_ATM(Balance_ATM *data_ATM,int no, int i);
};


#endif // CLASS_ATM_TREE__H
