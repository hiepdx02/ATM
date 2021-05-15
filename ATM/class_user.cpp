#include <iostream>
#include <fstream>
#include <vector>
#include<cstring>
#include <ctime>
#include <conio.h>
#include "function.h"
#include "class_user.h"
#include "class_ATM_tree.h"
using namespace std;

ATM::ATM (string _id, string _password, string _full_name, long _balance, int _status){
    id = _id;
    password = _password;
    full_name = _full_name;
    balance = _balance;
    status = _status;
};
ATM* Get_infor_user_from_file(char const *path, int &j){
    ATM *infor_data = new ATM[10000];
    j = 0;
    ifstream infile;
    infile.open(path,ios_base::in);
    string line1;
    getline(infile,line1);
    while (!infile.eof()){
        string line;
        getline(infile,line);
        string ID;
        int i = 0;
        while (line[i] != ':'){
            ID += line[i];
            i++;
        }

        i++;
        string Pass;
        while (line[i] != ':'){
            Pass += line[i];
            i++;
        }
        i++;
        string Name;
        while (line[i] != ':'){
            Name += line[i];
            i++;
        }
        i++;
        string _Balance;
        while (line[i] != ':'){
            _Balance += line[i];
            i++;
        }
        i++;
        long Balance = stoi(_Balance);
        int Status = int(line[i]) - 48;
        infor_data[j].id = ID;
        infor_data[j].password = Pass;
        infor_data[j].full_name = Name;
        infor_data[j].balance = Balance;
        infor_data[j].status = Status;
        j++;
    }
    infile.close();
return infor_data;
};
void Write_data_to_file(char const *path,int n, ATM *data){
    ofstream outfile;
    outfile.open(path, ios_base::out);
        outfile << "ID:PASSWORD:FULLNAME:BALANCE:STATUS." << endl;
        for (int i = 0;i < n-1;i++) {
            outfile << data[i].id << ":" << data[i].password << ":" << data[i].full_name<< ":" << data[i].balance << ":" << data[i].status << "." << endl;
        }
        outfile << data[n-1].id << ":" << data[n-1].password << ":" << data[n-1].full_name<< ":" << data[n-1].balance << ":" << data[n-1].status << ".";
    outfile.close();
return;
}
void sign_up_new_user(ATM *data, int &n, string const _Name,string const _password){
    int a = stoi(data[n-1].id) + 1;
    data[n].id = Convert_int_to_str(a);
    data[n].full_name = _Name;
    data[n].password = _password;
    cout << "Your full name is: " << _Name << endl;
    cout << "Your ID granted: " << data[n].id << endl;
    cout << "Your password: " << "******" << endl;
    cout << "Balance: 0" << endl;
    n++;
return;
};
bool ATM::Check_login_id(ATM const *data,int const n) const{
    for (int i = 0;i < n; i++) {
        if (id == data[i].id && data[i].status != 0) return 1;
    }
    return 0;
};
bool ATM::Check_login_password(ATM const *data, int const n) const{
    for (int i = 0;i < n; i++) {
        if (id == data[i].id && password == data[i].password) return 1;
    }
    return 0;
}
void Lock_user(ATM *data, int &j,string ID){
    if (ID != "00000") {
        for (int i = 0;i < j; i++) {
            if (data[i].id == ID){
                data[i].status = 0;
                break;
            }
        }
    }
};
bool ATM::check_balance_of_account(long amount_needed){
    if (balance >= amount_needed) return 1;
    else return 0;
};
void ATM::change_money_of_account(ATM *data,int const i,int money){
    data[i].balance += money;
return;
};
string ATM::get_id(){
    return id;
}
string ATM::get_full_name(){
    return full_name;
}
long ATM::get_balance() {
    return balance;
}

