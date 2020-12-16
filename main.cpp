#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include "library.h"
using namespace std;


int main() {
	printLine();
	cout << right << setw(55) << "MEMBERSHIP MANAGER" << endl;
	Member mInfo[MEMBERSIZE];
	ifstream memberFile;
	memberFile.open("input.dat");

	if (!memberFile.is_open()) {
		cout << "Error opening file";
		return 1;
	}
	int numberofMembers = 0;


	getAllMembers(memberFile, mInfo, numberofMembers);

	char response;
	
	do {
		printLine();
		cout << right << setw(46) << "MAIN MENU" << endl;
		printLine();
		cout << "[A.] View All Members" << endl;
		cout << "[B.] Search Member By Name" << endl;
		cout << "[C.] Search Member By Number / ZIP Code" << endl;
		cout << "[D.] Exit Application" << endl;
		ASKRESPONSE:cout << "Enter Options (A - D): ";
		cin >> response;

		switch (response) {
		case('A'):
		case('a'):
			printAllMembers(mInfo, numberofMembers);
			promptOptions(mInfo, numberofMembers);
			break;
		case('B'):
		case('b'):
			searchMember_byName(mInfo, numberofMembers);
			promptOptions(mInfo, numberofMembers);
			break;
		case('C'):
		case('c'):
			searchMember_byNumbers(mInfo, numberofMembers);
			promptOptions(mInfo, numberofMembers);
			break;
		case('D'):
		case('d'):
			cout << "Exiting Application. Goodbye!" << endl;
			break;
		default:
			cout << "Invalid Input. No Option Selected. Try Again" << endl;
			cin.ignore(50, '\n');
			cin.clear();
			goto ASKRESPONSE;
		}
	} while (response != 'd' && response != 'D');


	return 0;
}