#include <iostream>
#include "Date.hpp"
#include <string>
#include "Meeting.hpp"
using namespace::std;

Meeting::Meeting(){}
Meeting::Meeting(string sponsor_,string participator_,Date beginning_,Date ending_,string title_){
    sponsor = sponsor_;
    participator = participator_;
    beginning = beginning_;
    ending = ending_;
    title = title_;
}
void Meeting::setSponsor(string sponsor_){
    sponsor = sponsor_;
}
void Meeting::setParticipator(string participator_){
    participator = participator_;
}
void Meeting::setBeginning(Date beginning_){
    beginning = beginning_;
}
void Meeting::setEnding(Date ending_){
    ending = ending_;
}
void Meeting::setTitle(string title_){
    title = title_;
}
string Meeting::getSponsor() const{
    return sponsor;
}
string Meeting::getParticipator() const{
    return participator;
}
Date Meeting::getBeginning() const{
    return beginning;
}
Date Meeting::getEnding() const{
    return ending;
}
string Meeting::getTitle() const{
    return title;
}