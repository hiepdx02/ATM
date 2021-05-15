#include "class_user.h"
#include "class_ATM_tree.h"
#include "function.h"
#include <iostream>
#include <fstream>
#include <vector>
#include<cstring>
#include <ctime>
#include <conio.h>

using namespace std;


Balance_ATM::Balance_ATM (int _Amount,int _Price){
    Amount = _Amount;
    Price = _Price;
};
Balance_ATM *Get_data_ATM_from_file(char const *path){
    Balance_ATM *data_ATM;
    data_ATM = new Balance_ATM[7];
    ifstream infile;
    infile.open(path, ios_base::in);
        string line1;
        getline(infile, line1);
        for (int i = 0;i < 6; i++) {
            int _Amount;
            infile >>  _Amount;
            char ch_2_dot;    // get two dots mark
            infile >> ch_2_dot;
            int _Price;
            infile >> _Price;
            char ch_dot;        // get dot
            infile >> ch_dot;
            data_ATM[i].Amount = _Amount;
            data_ATM[i].Price = _Price;
        }
    infile.close();
return data_ATM;
};
void Write_data_ATM_to_file(char const *path, Balance_ATM *data_ATM){
    ofstream outfile;
    outfile.open(path,ios_base :: out);
        outfile << "Amount:Price." << endl;
        for (int i = 0;i < 5;i++){
            outfile << data_ATM[i].Amount << ':'<< data_ATM[i].Price << '.' << endl;
        }
        outfile << data_ATM[5].Amount << ':'<< data_ATM[5].Price << '.';
    outfile.close();
return;
};
bool check_money_of_ATM(Balance_ATM *_data_ATM,long amount_needed){
    if (amount_needed >= _data_ATM[0].Price && _data_ATM[0].Amount > 0) {
        _data_ATM[0].Amount--;
        return check_money_of_ATM(_data_ATM,amount_needed-500000);
    } else
    if (amount_needed >= _data_ATM[1].Price && _data_ATM[1].Amount > 0) {
         _data_ATM[1].Amount--;
        return check_money_of_ATM(_data_ATM,amount_needed-200000);
    } else
    if (amount_needed >= _data_ATM[2].Price && _data_ATM[2].Amount > 0) {
         _data_ATM[2].Amount--;
        return check_money_of_ATM(_data_ATM,amount_needed-100000);
    } else
    if (amount_needed >= _data_ATM[3].Price && _data_ATM[3].Amount > 0) {
         _data_ATM[3].Amount--;
        return check_money_of_ATM(_data_ATM,amount_needed-50000);
    } else
    if (amount_needed >= _data_ATM[4].Price && _data_ATM[4].Amount > 0) {
         _data_ATM[4].Amount--;
        return check_money_of_ATM(_data_ATM,amount_needed-20000);
    } else
    if (amount_needed >= _data_ATM[5].Price && _data_ATM[5].Amount > 0) {
         _data_ATM[5].Amount--;
        return check_money_of_ATM(_data_ATM,amount_needed-10000);
    } else
    if (amount_needed == 0) return 1;
    else return 0;
};
void Balance_ATM::change_no_of_balance_ATM(Balance_ATM *data_ATM,int no, int i){
    data_ATM[i].Amount += no;
};
