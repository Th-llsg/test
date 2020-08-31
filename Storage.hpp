#ifndef __STORAGE_H__
#define __STORAGE_H__

#define DISALLOW_COPY_AND_ASSIGN(TypeName) \
  TypeName(const TypeName&); \
  void operator=(const TypeName&)

#include <list>
#include <string>
#include <functional>
#include <fstream>
#include <iostream>

#include "User.hpp"
#include "Meeting.hpp"
using namespace std;

class Storage {
    private:
        static Storage *instance_;
        DISALLOW_COPY_AND_ASSIGN(Storage);
        Storage() {
            readFromFile("agenda.data");
        }
        // storage structure with list, or you have better structures
        // e.g. balanced tree
        std::list<User> userList_;
        std::list<Meeting> meetingList_;
        // File IO
        bool readFromFile(const char *fpath) {
            ifstream fin(fpath);
            if (!fin.is_open())
                return false;
            int userCount, meetingCount;
            string str;
            stringstream ss;
            fin >> str;
            str = str.substr(str.find("total:") + 6);
            ss << str;
            ss >> userCount;
            ss.str("");
            for (int i = 0; i < userCount; i++) {
                fin >> str;
                userList_.push_back(JSONToUser(str));
            }

            fin >> str;
            str = str.substr(str.find("total:") + 6);
            ss << str;
            ss >> meetingCount;
            for (int i = 0; i < meetingCount; i++) {
                fin >> str;
                meetingList_.push_back(JSONToMeeting(str));
            }
            return true;
        }
        bool writeToFile(const char *fpath) {
            ofstream fout(fpath);
            if (!fout.is_open())
                return false;
            fout << "{colletion:\"User\",total:" << userList_.size() << "}\n";
            for (auto itr = userList_.begin(); itr != userList_.end(); itr++) {
                fout << UserToJSON(*itr) << endl;
            }
            fout << "{colletion:\"Meeting\",total:" << meetingList_.size() << "}\n";
            for (auto itr = meetingList_.begin(); itr != meetingList_.end(); itr++) {
                fout << MeetingToJSON(*itr) << endl;
            }
            return true;
        }
        string UserToJSON(const User& user) {
            stringstream ss;
            ss << "{name:" << "\"" << user.getName() << "\","
               << "password:" << "\"" << user.getPassWord() << "\","
               << "email:" << "\"" << user.getEmail() << "\","
               << "phone:" << "\"" << user.getPhone() << "\"}";
            return ss.str();
        }
        string MeetingToJSON(const Meeting& meeting) {
            stringstream ss;
            ss << "{sponsor:" << "\"" << meeting.getSponsor() << "\","
               << "partipator:" << "\"" << meeting.getParticipator() << "\","
               << "sdate:" << "\"" << Date::dateToString(meeting.getStartDate()) << "\","
               << "edate:" << "\"" << Date::dateToString(meeting.getEndDate()) << "\","
               << "title:" << "\"" << meeting.getTitle() << "\"}";
            return ss.str();
        }
        User JSONToUser(const string& json) {
            string name, password, email, phone;
            int pos, len;
            pos = json.find("name:\"") + 6;
            len = json.find("\",password") - pos;
            name = json.substr(pos, len);
            pos = json.find("password:\"") + 10;
            len = json.find("\",email") - pos;
            password = json.substr(pos, len);
            pos = json.find("email:\"") + 7;
            len = json.find("\",phone") - pos;
            email = json.substr(pos, len);
            pos = json.find("phone:\"") + 7;
            len = json.find("\"}") - pos;
            phone = json.substr(pos, len);
            return User(name, password, email, phone);
        }
        Meeting JSONToMeeting(const string& json) {
            string sponsor, partipator, sdate, edate, title;
            int pos, len;
            pos = json.find("sponsor:\"") + 9;
            len = json.find("\",partipator") - pos;
            sponsor = json.substr(pos, len);
            pos = json.find("partipator:\"") + 12;
            len = json.find("\",sdate") - pos;
            partipator = json.substr(pos, len);
            pos = json.find("sdate:\"") + 7;
            len = json.find("\",edate") - pos;
            sdate = json.substr(pos, len);
            pos = json.find("edate:\"") + 7;
            len = json.find("\",title") - pos;
            edate = json.substr(pos, len);
            pos = json.find("title:\"") + 7;
            len = json.find("\"}") - pos;
            title = json.substr(pos, len);
            return Meeting(sponsor, partipator,
                Date::stringToDate(sdate), Date::stringToDate(edate), title);
        }
    public:
        // singleton
        static Storage *getInstance(void) {
            if (instance_ == nullptr)
                instance_ = new Storage();
            return instance_;
        }
        ~Storage() {}
        // CRUD for User & Meeting
        // using C++11 Function Template and Lambda Expressions
        void createUser(const User& user) {
            userList_.push_back(user);
        }
        std::list<User> queryUser(std::function<bool(const User&)> filter) {
            list<User> returnList;
            for (auto itr = userList_.begin(); itr != userList_.end(); itr++) {
                if (filter(*itr)) {
                    returnList.push_back(*itr);
                }
            }
            return returnList;
        }
        // return found users
        int updateUser(std::function<bool(const User&)> filter,
                       std::function<void(User&)> switcher) {
            int count = 0;
            for (auto itr = userList_.begin(); itr != userList_.end(); itr++) {
                if (filter(*itr)) {
                    switcher(*itr);
                    count++;
                }
            }
            return count;
        }
        // return the number of updated users
        int deleteUser(std::function<bool(const User&)> filter) {
            int count = 0;
            for (auto itr = userList_.begin(); itr != userList_.end(); itr++) {
                if (filter(*itr)) {
                    userList_.push_back(*itr);
                    count++;
                }
            }
            return count;
        }
        // return the number of deleted users
        void createMeeting(const Meeting& meeting) {
            meetingList_.push_back(meeting);
        }
        std::list<Meeting> queryMeeting(
                       std::function<bool(const Meeting&)> filter) {
            list<Meeting> returnList;
            for (auto itr = meetingList_.begin(); itr != meetingList_.end(); itr++) {
                if (filter(*itr)) {
                    returnList.push_back(*itr);
                }
            }
            return returnList;
        }
        // return found meetings
        int updateMeeting(std::function<bool(const Meeting&)> filter,
            std::function<void(Meeting&)> switcher) {
            int count = 0;
            for (auto itr = meetingList_.begin(); itr != meetingList_.end(); itr++) {
                if (filter(*itr)) {
                    switcher(*itr);
                    count++;
                }
            }
            return count;
        }
        // return the number of updated meetings
        int deleteMeeting(std::function<bool(const Meeting&)> filter) {
            int count = 0;
            for (auto itr = meetingList_.begin(); itr != meetingList_.end(); itr++) {
                if (filter(*itr)) {
                    meetingList_.erase(itr);
                    count++;
                }
            }
            return count;
        }
        // return the number of deleted meetings
        // File IO
        bool sync(void) {
            return writeToFile("agenda.data");
        }
};
Storage* Storage::instance_ = nullptr;
#endif