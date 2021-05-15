#ifndef FUNCTION__H
#define FUNCTION__H


#include "class_user.h"
#include "class_ATM_tree.h"
using namespace std;

string creat_password();
void screen_ATM_login(ATM *data,int n,bool &_continue, int &location);
void screen_ATM_sign_up(string &Name, string &Password);
string Convert_int_to_str(int a);
void Write_to_transaction_history(int location,int amount_needed);
void withdrawal_service(ATM *data,int location,Balance_ATM *data_ATM);
void deposit_order_service(ATM *data,int location,Balance_ATM *data_ATM);
char *Get_link_history(int location);
void watch_history_service(char *path);
Balance_ATM *Get_data_ATM_from_file(char const *path);
ATM* Get_infor_user_from_file(char const *path, int &j);
void service_watch_balance(ATM *data, int location);

#endif // FUNCTION__H
