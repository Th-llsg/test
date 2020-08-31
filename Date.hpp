#ifndef __DATE_H__
#define __DATE_H__
#include <string>
using namespace std;
class Date{
    private:
        int year;
        int month;
        int day;
        int hour;
        int min;
    public:
        Date();
        Date(int year_,int month_,int day_,int hour_,int min_);
        int getYear();
        int getMonth();
        int getDay();
        int getHour();
        int getMin();
        void setYear(int year_);
        void setMonth(int month_);
        void setDay(int day_);
        void setHour(int hour_);
        void setMin(int min_);
        static Date stringtoDate(std::string string_);
        static std::string datetoString(Date date_);
        Date &operator=(const Date &date_);
        bool operator==(const Date &date_) const;
        bool operator>(const Date &date_) const;
        bool operator<(const Date &date_) const;
        bool operator>=(const Date &date_) const;
        bool operator<=(const Date &date_) const;
};

#endif