// membership implementation file
#include <iostream> // std::ostream and std::istream
#include <iomanip> // formatting
#include "Member.h"

Member::Member() {
    firstName = "Unknown";
    lastName = "Unknown";
    phoneNumber = "Unknown";
    memberID = -1;
    areaCode = -1;
}

Member::Member(std::string firstName, std::string lastName, std::string phoneNumber, int memberID, int areaCode) {
    this->firstName = firstName;
    this->lastName = lastName;
    this->phoneNumber = phoneNumber;
    this->memberID = memberID;
    this->areaCode = areaCode;
}

std::string Member::getFirstName() const {
    return firstName;
}

std::string Member::getLastName() const {
    return lastName;
}

std::string Member::getPhoneNumber() const {
    return phoneNumber;
}

int Member::getMemberID() const {
    return memberID;
}

int Member::getAreaCode() const {
    return areaCode;
}

void Member::changeFirstName(std::string firstName) {
    this->firstName = firstName;
}

void Member::changeLastName(std::string lastName) {
    this->lastName = lastName;
}

void Member::changePhoneNumber(std::string phoneNumber) {
    this->phoneNumber = phoneNumber;
}

void Member::changeMemberID(int memberID) {
    this->memberID = memberID;
}

void Member::changeAreaCode(int areaCode) {
    this->areaCode = areaCode;
}