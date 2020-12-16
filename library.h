#include <iostream>
#include <fstream>
#include <string>
using namespace std;

const int MEMBERSIZE = 100;

struct Member {
	string firstName;
	string lastName;
	string phoneNumber;
	int areaCode;
};
int getUserInput();

// display functions
void printLine();
void printColumn();
void printAllMembers(const Member mInfo[], int numberofMembers);
void printOneMember(const Member mInfo[], const int memberID_index);
void printMemberOutline(const Member mInfo[], const int memberID_index);
void printSpecificMembers(const Member mInfo[], int numberofResults, const int resultIndex[]); // numberofResults needed to check for how many members are going to be printed



// procedural functions
void getAllMembers(ifstream&, Member mInfo[], int& numberofMembers);
void promptOptions(Member mInfo[], int& numberofMembers);
void addNewMember(Member mInfo[], int& numberofMembers);
void editMember(Member mInfo[], const int numberofMembers);
void removeMember(Member mInfo[], int& numberofMembers);
void searchMember_byName(const Member mInfo[], int numberofMembers);
void searchMember_byNumbers(const Member mInfo[], int numberofMembers);
