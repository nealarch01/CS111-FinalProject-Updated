#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <string>
#include <stdlib.h>
#include "library.h"
using namespace std;
// ** I used jump statements in some functions to prevent the whole menu from reprinting again when the user enters an invalid option. The menu is already inside a loop with switch statements so doing this as a shortcut
int getUserInput() {
	int x;
	bool validNum = false;
	cin >> x;
	while (cin.fail() || x < 1) {
		cin.clear();
		cin.ignore(50, '\n');
		cout << "Inavlid Number. Enter Again: ";
		cin >> x;
	}
	return x;
}

// this function prints a line made of '=' characters
void printLine() {
	cout << setfill('=') << right << setw(80) << "=";
	cout << setfill(' ') << endl; // set back to space
}
// this function prints the column outline
void printColumn() {
	cout << left << setw(15) << "[MEMBER ID]" << left << setw(20) << "[FIRST NAME]" << left << setw(20) << "[LAST NAME]" << left << setw(20) << "[PHONE NUMBER]" << left << setw(20) << "[ZIP CODE]" << endl;
}

// iomanip structure of how data will be printed
void printMemberOutline(const Member mInfo[], const int i) {
	cout << right << setw(9) << i + 1 << "\t\t"; // i + 1 is the memberID
	cout << left << setw(20) << mInfo[i].firstName;
	cout << left << setw(20) << mInfo[i].lastName;
	cout << left << setw(20) << mInfo[i].phoneNumber;
	cout << mInfo[i].areaCode << endl;
}
// gathers the data from the input file and assigns it to struct
void getAllMembers(ifstream& file, Member mInfo[], int& numberofMembers) {
	while (!file.eof()) {
		getline(file, mInfo[numberofMembers].firstName, ' ');
		getline(file, mInfo[numberofMembers].lastName, ',');
		getline(file, mInfo[numberofMembers].phoneNumber, ',');
		file >> mInfo[numberofMembers].areaCode;
		file.ignore();
		numberofMembers++;
	}
}
// prints all members in the struct array, not the input file
void printAllMembers(const Member mInfo[], int numberofMembers) {
	printLine();
	printColumn();
	for (int i = 0; i < numberofMembers; i++) {
		printMemberOutline(mInfo, i);
	}
}
//prints one member, the only difference between this function and the printMemberOutline is this prints a column
void printOneMember(const Member mInfo[], const int memberID_index) {
	printColumn();
	printMemberOutline(mInfo, memberID_index);
}

//print a specific set of members found from a search
void printSpecificMembers(const Member mInfo[], int numberofResults, const int resultsIndex[]) {
	// I had to create this function because the index is found through an array with saved integers (integers from the instances a string or number was found) so there's an additional parameter
	printLine();
	cout << numberofResults << " results found: " << endl;
	printColumn();
	for (int i = 0; i < numberofResults; i++) {
		cout << right << setw(9) << resultsIndex[i] + 1 << "\t\t";
		cout << left << setw(20) << mInfo[resultsIndex[i]].firstName;
		cout << left << setw(20) << mInfo[resultsIndex[i]].lastName;
		cout << left << setw(20) << mInfo[resultsIndex[i]].phoneNumber;
		cout << mInfo[resultsIndex[i]].areaCode << endl;
	}
	return;
}

// this function is going to pass information and call functions responsible for making changes to the struct array
void promptOptions(Member mInfo[], int& numberofMembers) {
	short int numberResponse;
	do {
		printLine();
		cout << right << setw(55) << "ADD/REMOVE/EDIT MENU" << endl;
		printLine();
		cout << "[1.] Add Member" << endl;
		cout << "[2.] Remove Member" << endl;
		cout << "[3.] Edit Member" << endl;
		cout << "[4.] Go Back To Main Menu" << endl;
	ASKRESPONSE:cout << "Enter Option (1 - 4): ";
		numberResponse = getUserInput();
		switch (numberResponse) {
		case(1):
			addNewMember(mInfo, numberofMembers);
			break;
		case(2):
			// call remove member function
			removeMember(mInfo, numberofMembers);
			break;
		case(3):
			// call edit member function
			editMember(mInfo, numberofMembers);
			break;
		case(4):
			cout << "Returning Back To Menu" << endl;
			break;
		default:
			cout << "Invalid Input. No Option Selected." << endl;
			goto ASKRESPONSE;
			break;
		}
	} while (numberResponse != 4);
	system("cls");
}

// search member by name. Prompts user for what type of search
void searchMember_byName(const Member mInfo[], int numberofMembers) {
	short int optionResponse;
	string find_firstName, find_lastName;
	string find_phoneNumber;
	int find_areaCode;
	int resultsFound = 0;
	int resultsFound_indexNum[MEMBERSIZE];
	printLine();
	cout << right << setw(50) << "SEARCH BY NAME" << endl;
	printLine();
	while (resultsFound == 0) {
		cout << "[1.] Search By First Name" << endl;
		cout << "[2.] Search By Last Name" << endl;
		cout << "[3.] Search By Full Name" << endl;
		cout << "[4.] Go To Edit Menu / Main Menu" << endl;
	ASKRESPONSE:cout << "Enter Option: ";
		optionResponse = getUserInput();
		switch (optionResponse) {
		case(1):
			cout << "Enter Member's First Name: ";
			cin >> find_firstName;
			for (int i = 0; i < numberofMembers; i++) {
				if (mInfo[i].firstName == find_firstName) {
					resultsFound_indexNum[resultsFound] = i;
					resultsFound++;
				}
			} // end of case(1) for loop
			break;
		case(2):
			cout << "Enter Member's Last Name: ";
			cin >> find_lastName;
			for (int i = 0; i < numberofMembers; i++) {
				if (mInfo[i].lastName == find_lastName) {
					resultsFound_indexNum[resultsFound] = i;
					resultsFound++;
				}
			} // end of case(2) for loop
			break;
		case(3):
			cout << "Enter Member's First and Last Name: ";
			cin >> find_firstName;
			cin.ignore();
			cin >> find_lastName;
			for (int i = 0; i < numberofMembers; i++) {
				if (mInfo[i].firstName == find_firstName && mInfo[i].lastName == find_lastName) {
					resultsFound_indexNum[resultsFound] = i;
					resultsFound++;
				}
			} // end of case(3) foor loop
			break;
		case(4):
			cout << "Returning To Previous Menu" << endl;
			system("cls");
			return;
			break;
		default:
			cout << "Invalid Input. Try Again: ";
			break;
		} // end of switch statement

		if (resultsFound == 0) {
			printLine();
			cout << "No Results Found" << endl;
			printLine();
		}
	} // end of while loop

	printSpecificMembers(mInfo, resultsFound, resultsFound_indexNum);
}

void searchMember_byNumbers(const Member mInfo[], int numberofMembers) {
	string find_phoneNumber;
	int find_areaCode;
	short int optionResponse;
	int resultsFound = 0;
	int resultsFound_indexNum[MEMBERSIZE];
	printLine();
	cout << right << setw(50) << "SEARCH BY ZIP / PHONE" << endl;
	printLine();
	while (resultsFound == 0) {
		cout << "[1.] Search By Phone Number" << endl;
		cout << "[2.] Search By ZIP Code" << endl;
		cout << "[3.] Go To Edit / Main Menu" << endl;
	ASKRESPONSE:cout << "Enter Option (1-3): ";
		optionResponse = getUserInput();

		switch (optionResponse) {
		case(1):
			cout << "Enter Phone Number xxx-xxx-xxxx Format: ";
			cin.ignore(); // ignore input from optionResponse input
			getline(cin, find_phoneNumber);
			cout << find_phoneNumber << endl;
			for (int i = 0; i < numberofMembers; i++) {
				if (mInfo[i].phoneNumber == find_phoneNumber) {
					resultsFound_indexNum[resultsFound] = i;
					resultsFound++;
				}
			} // end of for loop
			break;
		case(2):
			cout << "Enter ZIP Code: ";
			cin >> find_areaCode;
			for (int i = 0; i < numberofMembers; i++) {
				if (mInfo[i].areaCode == find_areaCode) {
					resultsFound_indexNum[resultsFound] = i;
					resultsFound++;
				}
			}
			break;
		case(3):
			system("cls");
			return;
			break;
		default:
			cout << "Invalid Input. Try Again: ";
			goto ASKRESPONSE;
			break;
		} // end of switch statement
		if (resultsFound == 0) {
			printLine();
			cout << "No Results Found" << endl;
			printLine();
		}
	} // end of while loop
	printSpecificMembers(mInfo, resultsFound, resultsFound_indexNum);
}

void addNewMember(Member mInfo[], int& numberofMembers) {
	int memberNumber_index = numberofMembers;
	numberofMembers++; // add plus one to the total number of members

	cout << "Enter New Member First Name: ";
	cin >> mInfo[memberNumber_index].firstName;
	cout << "Enter New Member Last Name: ";
	cin >> mInfo[memberNumber_index].lastName;
	cout << "Enter New Member Phone Number xxx-xxx-xxx Format: ";
	cin >> mInfo[memberNumber_index].phoneNumber;
	cout << "Enter New Member Area Code: ";
	cin >> mInfo[memberNumber_index].areaCode;
	cout << "One New Member Added!" << endl;
	cout << "New Member Information: " << endl;

	printOneMember(mInfo, memberNumber_index);
}

void editMember(Member mInfo[], const int numberofMembers) { // using const int for second parameter because we are not changing the number of users
	short int optionResponse;
	int memberID_input;
	int memberID_index;

	printLine();
	cout << right << setw(55) << "EDIT MEMBER MENU" << endl;
	printLine();

	do {
		cout << "Enter Member ID To Edit: ";
		memberID_input = getUserInput();
		if (memberID_input > numberofMembers) {
			cout << "Member ID Entered Does Not Exist. Try Again" << endl;
		}
	} while (memberID_input > numberofMembers);

	memberID_index = memberID_input - 1; // subtract one to access the desired element

	cout << "Editting Information for [" << memberID_input << "] " << mInfo[memberID_index].firstName << " " << mInfo[memberID_index].lastName << endl;

	do {
		printLine();
		cout << right << setw(55) << "EDIT INFORMATION" << endl;
		printLine();
		cout << "[1.] Edit First Name" << endl;
		cout << "[2.] Edit Last Name" << endl;
		cout << "[3.] Edit Phone Number" << endl;
		cout << "[4.] Edit Area Code" << endl;
		cout << "[5.] Finish Editting" << endl;
		cout << "Enter Option: ";
	ASKRESPONSE:optionResponse = getUserInput();

		switch (optionResponse) {
		case(1):
			cout << "Enter Member's New First Name: ";
			cin >> mInfo[memberID_index].firstName;
			cout << "New First Name: " << mInfo[memberID_index].firstName << endl;
			break;
		case(2):
			cout << "Enter Member's New Last Name: ";
			cin >> mInfo[memberID_index].lastName;
			cout << "New Last Name: " << mInfo[memberID_index].lastName << endl;
			break;
		case(3):
			cout << "Enter Member's Phone Number: ";
			cin >> mInfo[memberID_index].phoneNumber;
			cout << "New Phone Number: " << mInfo[memberID_index].phoneNumber << endl;;
			break;
		case(4):
			cout << "Enter Member's Area Code: ";
			cin >> mInfo[memberID_index].areaCode;
			cout << "New Area Code: " << mInfo[memberID_index].areaCode << endl;
			break;
		case(5):
			cout << "Returning Back" << endl;
			break;
		default:
			cout << "Invalid Input. Try Again" << endl;
			goto ASKRESPONSE;
		}
	} while (optionResponse != 5);
	system("cls");
	cout << "New Member Information:" << endl;
	printOneMember(mInfo, memberID_index);
	return;
}
// remove member function
void removeMember(Member mInfo[], int& numberofMembers) {
	int memberID_input;
	int memberID_indexFromInput;
	int optionResponse;
	do {
		cout << "Enter Member ID To Remove: ";
		memberID_input = getUserInput();
		if (memberID_input > numberofMembers) {
			cout << "Member ID Entered Does Not Exist. Try Again" << endl;
		}
	} while (memberID_input > numberofMembers);

	memberID_indexFromInput = memberID_input - 1; // obtain the index for the member to be removed


	printLine();
	cout << right << setw(56) << "CONFIRM REMOVING MEMBER" << endl;
	printLine();

	printOneMember(mInfo, memberID_indexFromInput);


	do {
		cout << "[1.] Yes, Remove Member" << endl;
		cout << "[2.] No, Do Not Remove" << endl;
		cout << "Enter Option: ";
		optionResponse = getUserInput();
	} while (optionResponse >= 3);

	if (optionResponse == 1) {
		numberofMembers--;
		for (int i = memberID_indexFromInput; i < numberofMembers; i++) { // numberofMembers - 1 is to access index
			mInfo[i].firstName = mInfo[i + 1].firstName;
			mInfo[i].lastName = mInfo[i + 1].lastName;
			mInfo[i].phoneNumber = mInfo[i + 1].phoneNumber;
			mInfo[i].areaCode = mInfo[i + 1].areaCode;

		}
		system("cls");
		printLine();
		cout << right << setw(49) << "MEMBER REMOVED" << endl;
	}
	else {
		system("cls");
		cout << "No Member Removed" << endl;
		return;
	}
}