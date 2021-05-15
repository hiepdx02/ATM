#ifndef CLASS_ATM__H
#define CLASS_ATM__H

#include <iostream>

using namespace std;
class ATM{
    string id;      // ID of user
    string password;    // Password of user
    string full_name;   // Name of user
    long balance; // balance of account
    int status; // 1 is active, 0 is not active
public:
    ATM (string _id = "", string _password = "", string _full_name = "", long _blance = 0, int _status = 1);
    friend ATM* Get_infor_user_from_file(char const *path, int &j);     // Get information of users from file
    friend void Write_data_to_file(char const *path,int n, ATM *data);  // Return information of users to file
    friend void sign_up_new_user(ATM *data, int &n, string const _Name,string const _password); // sign up a new user
    bool Check_login_id (ATM const *data, int const n) const;   // Check ID entered true or false
    bool Check_login_password(ATM const *data, int const n) const;  // Check password entered true or false
    friend void Lock_user(ATM* data, int &j, string ID);    // Lock account of user
    bool check_balance_of_account(long amount_needed);      // check balance: if enough return 1 else return 0
    void change_money_of_account(ATM *data,int i ,int money);
    string get_id();
    string get_full_name();
    long get_balance();
};

#endif // CLASS_ATM__H

