#ifndef __MEETING_H__
#define __MEETING_H__
#include <string>
#include "Date.hpp"
using namespace std;

class Meeting{
    private:
        string sponsor;
        string participator;
        Date beginning;
        Date ending;
        string title;
    public:
        Meeting();
        Meeting(string sponsor_,string participator_,Date beginning_,Date ending_,string title_);
        void setSponsor(string sponsor_);
        void setParticipator(string participator_);
        void setBeginning(Date beginning_);
        void setEnding(Date ending_);
        void setTitle(string title_);
        string getSponsor() const;
        string getParticipator() const;
        Date getBeginning() const;
        Date getEnding() const;
        string getTitle() const;
};

#endif