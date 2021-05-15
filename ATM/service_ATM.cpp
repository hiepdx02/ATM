#include <iostream>
#include <fstream>
#include <vector>
#include<cstring>
#include <ctime>
#include <conio.h>
#include "function.h"
#include "class_user.h"
#include "class_ATM_tree.h"
#include "service_ATM.h"

using namespace std;

void Service_ATM() {
    ATM *data;
    int n;
    data = Get_infor_user_from_file("information.txt",n);
    string str;
    do {
    system("cls");
    cout << "Enter 1 to login" << endl;
    cout << "Enter 2 to sign up" << endl;
    cin >> str;
    } while (str != "1" && str != "2");
    system("cls");
    int number = int(str[0] - 48);
    switch (number) {
        case 1:
        {
            Balance_ATM *data_ATM = Get_data_ATM_from_file("balance_ATM.txt");
            bool _continue = 1;
            int location;
            screen_ATM_login(data,n,_continue,location);
            string str;
            if (_continue) {
                do{
                    do {
                        system("cls");
                        cout << "Enter 1 to withdrawal." << endl;
                        cout << "Enter 2 to deposit order." << endl;
                        cout << "Enter 3 to watch history." << endl;
                        cout << "Enter 4 to watch balance of account" << endl;
                        cout << "Enter 5 to log out." << endl;
                        cin >> str;
                        if (str != "1" && str != "2" && str != "3" && str != "4" && str != "5") {
                            cout << "Not have service." << endl;
                            system ("pause");
                        }
                    } while (str != "1" && str != "2" && str != "3" && str != "4" && str != "5");
                    system("cls");
                    if (str == "1") withdrawal_service(data,location,data_ATM);
                    if (str == "2") deposit_order_service(data,location,data_ATM);
                    if (str == "3") {
                        char *_path = new char [100];
                        _path = Get_link_history(location);
                        watch_history_service(_path);
                    }
                    if (str == "4") service_watch_balance(data,location);
                    system("pause");
                } while (str != "5");
            }
            system("pause");
            break;
        }
        case 2:
        {
            string Name = "" , password = "";
            screen_ATM_sign_up(Name, password);
            if (Name != "" && password != "") sign_up_new_user(data,n,Name,password);
            system("pause");
            break;
        }
    }
    Write_data_to_file("information.txt",n,data);
    delete[] data;
return;
}
void Open_ATM() {
    do {
        system("cls");
        Service_ATM();
    }
    while(1);
return;
}
