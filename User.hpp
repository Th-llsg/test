#ifndef __USER_H__
#define __USER_H__
#include <string>
using namespace std;

class User{
    private:
        string name;
        string phone;
        string email;
        string password;
    public:
        User();
        User(string name_,string phone_,string email_,string password_);
        string getName() const;
        string getPhone() const;
        string getEmail() const;
        string getPassword() const;
        void setName(string name_);
        void setPhone(string phone_);
        void setEmail(string email_);
        void setPassword(string password_);
};

#endif