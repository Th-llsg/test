#include <iostream>
#include "User.hpp"
#include <string>
using namespace std;
User::User(){
}
User::User(string name_,string phone_,string email_,string password_){
    name = name_;
    phone = phone_;
    email = email_;
    password = password_;
}
string User::getName() const{
    return name;
}
string User::getPhone() const{
    return phone;
}
string User::getEmail() const{
    return email;
}
string User::getPassword() const{
    return password;
}
void User::setName(string name_){
    name = name_;
}
void User::setPhone(string phone_){
    phone = phone_;
}
void User::setEmail(string email_){
    email = email_;
}
void User::setPassword(string password_){
    password = password_;
}