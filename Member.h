#ifndef MEMBER_H
#define MEMBER_H
#include <string>
class Member {
friend std::ostream& operator<<(std::ostream& out, Member &member);
private:
    std::string firstName;
    std::string lastName;
    std::string phoneNumber;
    int memberID;
    int areaCode;
public:
    Member();
    Member(std::string firstName, std::string lastName, std::string phoneNumber, int memberID, int areaCode);
    std::string getFirstName() const;
    std::string getLastName() const;
    std::string getPhoneNumber() const;
    int getMemberID() const;
    int getAreaCode() const;

    void changeFirstName(std::string firstName);
    void changeLastName(std::string lastName);
    void changePhoneNumber(std::string phoneNumber);
    void changeMemberID(int memberID);
    void changeAreaCode(int areaCode);
};


#endif