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
string creat_password(){
    string password = "";
    char c = ' ';
    while(c != '\r') { //Loop until 'Enter' is pressed
        c = getch();
        if(c == '\b'){ //If the 'Backspace' key is pressed
            if(password.size() != 0){  //If the password string contains data, erase last character
                cout << "\b \b";
                password.erase(password.size() - 1, 1);
            }
            continue;
        }
        else if (password.size() == 6) continue;
        else if(c <= '9' && c >= '0'){  //If user enters 1-9, a-z, or A-Z, add it to the password and display an asterisk
            password += c;
            cout << "*";
        }
        else continue;
    }
    cout << endl;
return password;
}
void screen_ATM_login(ATM *data,int n,bool &_continue, int &location){
    bool check_id = 0, check = 0;
    int _count = 0;
    int count_id = 0;
    string id;
    string password;
    do {
        cout << "Enter your ID ?" << endl;
        cin >> id;
        ATM ID(id);
        check_id = ID.Check_login_id(data,n);
        if (!check_id) {
            cout << "Your id is not valid." << endl;
            count_id++;
        }
        if (count_id == 5){
            cout << "You enterid wrong much times." << endl;
            _continue = 0;
        }
    } while (!check_id && count_id!=5);
    if (count_id < 5)
    do {
        location = stoi(id);
        cout << "Enter your password ?" << endl;
        password = creat_password();
        ATM user(id,password);
        check = user.Check_login_password(data,n);
        if (!check) {
            cout << "Password is incorret." << endl;
            _count++;
            cout << "You entered " << _count << "/5 times." << endl;
        }
        if (_count == 5) {
            cout << "Your card has been locked." << endl;
            Lock_user(data,n,id);
            _continue = 0;
        }
    } while (_count != 5 && !check);
    if (_count == 5) _continue = 0;
return;
}
void screen_ATM_sign_up(string &Name, string &Password){
    bool check = 0;
    int count_name = 0; // count enter name is wrong
    cin.ignore();
    while (check == 0 && count_name != 5) {
        cout << "Your full name is: NOTE: word is uppercase" << endl;
        string _Name = "";
        getline(cin,_Name);
        for (int i = 0; i < _Name.size(); i++) {
            if (_Name[i] > 'Z' || _Name[i] < 'A' && _Name[i] != ' ') {
                cout << "ERROR: All word is uppercase" << endl;
                check = 0;
                count_name++;
                break;
            }
            if (i == _Name.size() - 1) check = 1;
        }
        for (int i = 0; i < _Name.size(); i++) {
            if (_Name[i] == ' ')
                if (_Name[i-1]==' '){
                    check = 0;
                    cout << "ERRPR: redundant space character." << endl;
                    count_name++;
                    break;
                }
        }
        if (check) Name = _Name;
    }
    check = 0;
    int count_password = 0;
    while (check == 0 && count_name != 5 && count_password != 5) {
        cout << "Your password is: NOTE: password have six number." << endl;
        string _Password;
        _Password = creat_password();
        cout << "Enter your password again: " << endl;
        if (_Password.size() == 6) {
            string _Password_again;
            _Password_again = creat_password();
            if (_Password == _Password_again) {
                check = 1;
                Password = _Password;
            } else {
                count_password++;
                cout << "Password incorrect!" << endl;
            }
        } else {
            cout << "Password error!" << endl;
            count_password++;
        }
    }
return;
}
string Convert_int_to_str(int a) {
    string str;
    string _str = to_string(a);
    int n = 5 - _str.size();
    for (int i = 0;i < n; i++) {
        str += "0";
    }
    str += _str;
return str;
}
void Write_to_transaction_history(int location,int amount_needed){
    string _path = "transaction_history_of_user/history_";
    char _location = char(location+48);
    _path += _location;
    _path += ".txt";
    _path += '\0';
    char *path = new char[_path.size()];
    for (int i = 0;i < _path.size(); i++) {
        path[i] = _path[i];
    }
    ofstream outfile;
    outfile.open(path,ios ::app);
        outfile.seekp( 0, ios::end);
        time_t now = time(0);
        char *dt = ctime(&now);
        if (amount_needed < 0) outfile << dt << "-You withdrawned " << -amount_needed<< " thousand." << endl;
        else outfile << dt << "-You sent " << amount_needed << " thousand." << endl;
    outfile.close();
return;
}
void withdrawal_service(ATM *data,int location,Balance_ATM *data_ATM){
    Balance_ATM *_data_ATM = new Balance_ATM[6];
    for (int i = 0;i < 6; i++){
        _data_ATM[i] = data_ATM[i];
    }
    cout << "How much money do you need to withdraw ?" << endl;
    cout << "Multiples of 10000." << endl;
    long amount_needed;
    do{
        long _amount_needed;  // amount_money_needed
        cin >> _amount_needed;
        amount_needed = _amount_needed;
    } while (amount_needed % 10000);
    bool check_1 = data[location].check_balance_of_account(amount_needed);
    if (check_1 == 0) cout << "Balance of yout account is insufficient." << endl;
    bool check_2 = check_money_of_ATM(_data_ATM,amount_needed);
    if (check_1 && !check_2) cout << "ATM does not have enough money or lacks face value."<< endl;
    if (check_1 && check_2) {
        cout << "successful transaction." << endl;
        data[location].change_money_of_account(data,location,-amount_needed);
        for (int i = 0;i < 6; i++){
            data_ATM[i] = _data_ATM[i];
        }
        Write_data_ATM_to_file("balance_ATM.txt",data_ATM);
        Write_to_transaction_history(location, -amount_needed);
    }
    delete[] _data_ATM;
    return;
}
void deposit_order_service(ATM *data,int location,Balance_ATM *data_ATM) {
    string str;
    cout << "Choose denominations: " << endl;
    cout << "Enter 1: 500000" << endl << "Enter 2: 200000" << endl << "Enter 3: 100000" << endl << "Enter 4: 50000" << endl << "Enter 5: 20000" << endl << "Enter 6: 10000" << endl;
    cin >> str;
    if (str > "6" || str < "1") {
        cout << "Error" << endl;
        system("pause");
        return;
    }
    if (str == "1") {
        cout << "Enter no: " << endl;
        int No;
        cin >> No;
        long Sum = No* 500000;
        data[location].change_money_of_account(data,location,Sum);
        data_ATM[0].change_no_of_balance_ATM(data_ATM,No,0);
        Write_to_transaction_history(location,Sum);
        cout << "successful transaction." << endl;
    } else
    if (str == "2") {
        cout << "Enter no: " << endl;
        int No;
        cin >> No;
        long Sum = No* 200000;
        data[location].change_money_of_account(data,location,Sum);
        data_ATM[1].change_no_of_balance_ATM(data_ATM,No,1);
        Write_to_transaction_history(location,Sum);
        cout << "successful transaction." << endl;
    } else
    if (str == "3") {
        cout << "Enter no: " << endl;
        int No;
        cin >> No;
        long Sum = No* 100000;
        data[location].change_money_of_account(data,location,Sum);
        data_ATM[2].change_no_of_balance_ATM(data_ATM,No,2);
        Write_to_transaction_history(location,Sum);
        cout << "successful transaction." << endl;
    } else
    if (str == "4") {
        cout << "Enter no: " << endl;
        int No;
        cin >> No;
        long Sum = No* 50000;
        data[location].change_money_of_account(data,location,Sum);
        data_ATM[3].change_no_of_balance_ATM(data_ATM,No,3);
        Write_to_transaction_history(location,Sum);
        cout << "successful transaction." << endl;
    } else
    if (str == "5") {
        cout << "Enter no: " << endl;
        int No;
        cin >> No;
        long Sum = No* 20000;
        data[location].change_money_of_account(data,location,Sum);
        data_ATM[4].change_no_of_balance_ATM(data_ATM,No,4);
        Write_to_transaction_history(location,Sum);
        cout << "successful transaction." << endl;
    } else
    if (str == "6") {
        cout << "Enter no: " << endl;
        int No;
        cin >> No;
        long Sum = No* 10000;
        data[location].change_money_of_account(data,location,Sum);
        data_ATM[5].change_no_of_balance_ATM(data_ATM,No,5);
        Write_to_transaction_history(location,Sum);
        cout << "successful transaction." << endl;
    }
    Write_data_ATM_to_file("balance_ATM.txt",data_ATM);
return;
}
char *Get_link_history(int location){
    string _path = "transaction_history_of_user/history_";
    char _location = char(location+48);
    _path += _location;
    _path += ".txt";
    _path += '\0';
    char *path = new char[_path.size()];
    for (int i = 0;i < _path.size(); i++) {
        path[i] = _path[i];
    }
return path;
}
void watch_history_service(char *path) {
    ifstream infile;
    infile.open(path,ios_base :: in);
        if (infile.good()) {
            while (!infile.eof()){
                string line;
                getline(infile,line);
                cout << line << endl;
            }
        } else cout << "Not have a transaction history." << endl;
    infile.close();
return;
}
void service_watch_balance(ATM *data, int location) {
    cout << "ID: " << data[location].get_id() << endl;
    cout << "Name of user: " << data[location].get_full_name() << endl;
    cout << "Balance: " << data[location].get_balance() << endl;
return;
}
