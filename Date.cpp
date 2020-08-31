#include <iostream>
#include "Date.hpp"
#include <math.h>
#include <string>
#include <sstream>
using namespace std;
int isLeap(int year_){
    if((year_ % 4 == 0 && year_ % 100 > 0) ||(year_ % 400 == 0))
        return 1;
    else
        return 0;
}
string addZero(int num){
    stringstream ss;
    if(num < 10)
        ss << '0' << num;
    else
        ss << num;
    return ss.str();
}
bool isValid(Date date_){
    if(((date_.getYear() < 1000)||(date_.getYear() > 9999))||((date_.getMonth() < 1)||(date_.getMonth() > 12))||((date_.getHour() < 0)||(date_.getHour() > 23))||((date_.getMin() < 0)||(date_.getMin() > 59)))
        return false;
    int mon[12] = {31,28,31,30,31,30,31,31,30,31,30,31};
    int flag = isLeap(date_.getYear());
    int is2 = date_.getMonth() == 2? 1 : 0;
    if((date_.getDay() < 1)||(date_.getDay() > (mon[date_.getMonth()] + is2*flag)))
        return false;
    return true;
}
int Date::getYear(){
    return year;
}
int Date::getMonth(){
    return month;
}
int Date::getDay(){
    return day;
}
int Date::getHour(){
    return hour;
}
int Date::getMin(){
    return min;
}
void Date::setYear(int year_){
    year = year_;
}
void Date::setMonth(int month_){
    month = month_;
}
void Date::setDay(int day_){
    day = day_;
}
void Date::setHour(int hour_){
    hour = hour_;
}
void Date::setMin(int min_){
    min = min_;
}
Date Date::stringtoDate(std::string string_){
    stringstream str;
    int year_ , month_ , day_ , hour_ , min_;
    char tmp;
    str << string_;
    str >> year_ >> tmp >> month_ >> tmp >> day_ >> tmp >> hour_ >> tmp >> min_;
    return Date(year_ , month_ , day_ , hour_ , min_);
}
std::string Date::datetoString(Date date_){
    stringstream sstr;
    sstr << addZero(date_.getYear()) << '-' << addZero(date_.getMonth()) << '-' << addZero(date_.getDay()) << '/' << addZero(date_.getHour()) << ':' << addZero(date_.getMin());
    return sstr.str();
}
Date& Date::operator=(const Date &date_){
    setYear(date_.year);
    setMonth(date_.month);
    setDay(date_.day);
    setHour(date_.hour);
    setMin(date_.min);
    return *this;
}
bool Date::operator==(const Date &date_) const{
    return ((((year == date_.year)&&(month == date_.month))&&((day == date_.day)&&(hour == date_.hour)))&&(min == date_.min));
}
bool Date::operator>(const Date &date_) const{
    if((((year <= date_.year)||(month <= date_.month))||((day <= date_.day)||(hour <= date_.hour)))||min <= date_.min);
        return false;
    return true;
}
bool Date::operator<(const Date &date_) const{
    if((((year >= date_.year)||(month >= date_.month))||((day >= date_.day)||(hour >= date_.hour)))||min >= date_.min);
        return false;
    return true;
}
bool Date::operator>=(const Date &date_) const{
    if((((year < date_.year)||(month < date_.month))||((day < date_.day)||(hour < date_.hour)))||min < date_.min);
        return false;
    return true;
}
bool Date::operator<=(const Date &date_) const{
    if((((year > date_.year)||(month > date_.month))||((day > date_.day)||(hour > date_.hour)))||min > date_.min);
        return false;
    return true;
}