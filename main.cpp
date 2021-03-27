#include <dirent.h>  // used to search for file

#include <cstdlib>  // exit()
#include <fstream>
#include <iostream>
#include <sstream>  // 4194504836
#include <string>
#include <vector>
#include <chrono>

#include "ClientLib.h"
#include "Member.h"
void readFromFile(std::ifstream &memberFile, std::vector<Member> *&members,
                  int &currentID);

char searchMember();
bool searchMemberAssign(std::vector<Member> *&members, char searchType);
std::vector<int> searchByName(std::vector<Member> *&members);
std::vector<int> searchByPhone(std::vector<Member> *&members);
std::vector<int> searchByAreaCode(std::vector<Member> *&members);
int searchByID(std::vector<Member> *&members, int key);

Member addNewMember(int &currentID);
void removeMember(std::vector<Member> *&members);
void editMember(std::vector<Member> *&members);
void editMemberAssign(Member &member, char editType);
void saveInformation(std::vector<Member> *&Members);

std::string getNameInput();
std::string getPhoneNumberInput();
int getMemberIDinput(std::vector<Member> *&members);
int getAreaCodeInput();

char getMenuInput(char minimum, char maximum);
int getIntInput(int minimum, int maximum);
template<typename T> T getUserInput(T minimum, T maximum); // come back to later for testing
bool confirmChange(std::string action, int memberID, 
                   std::string memberFirstName, std::string memberLastName);

void saveAndExit(std::vector<Member> *&members, std::string filename);

int main() {
    clearScreen();
    std::vector<Member> *members = new std::vector<Member>;
    std::ifstream memberFile;
    std::string filename;
    char loadResponse;
    int currentID = 1000;
    while (loadResponse != 'C' || memberFile.is_open()) {
        printDate();
        loadMenu();
        loadResponse = getMenuInput('A', 'D');
        switch (loadResponse) {
            case ('A'):
                filename = "data.txt";
                break;
            case ('B'):
                std::cout << "Enter filename: ";
                std::cin >> filename;
                break;
            case ('C'):
                break;
            case ('D'):
                std::cout << "~Goodbye~" << std::endl;
                return 0;
                break;
        }
        memberFile.open(filename.c_str());
        if (!memberFile.is_open()) {
            clearScreen();
            loadMenuFailed(filename);
        } else {
            readFromFile(memberFile, members, currentID);
            break;
        }
    }
    memberFile.close();
    char userResponse, editType, searchType, editMenuResponse;
    bool isFound;
    clearScreen();
    while (1) {
        isFound = false;
        mainMenu();
        userResponse = getMenuInput('A', 'D');
        switch (userResponse) {
            case ('A'):
                clearScreen();
                viewAllMembers(members);
                break;
            case ('B'):
                clearScreen();
                while (isFound == false) {
                    searchType = searchMember();
                    isFound = searchMemberAssign(members, searchType);
                }
                break;
            case ('C'):
                clearScreen();
                break;
            case ('D'):
                saveAndExit(members, filename);
                std::cout << "~Goodbye~" << std::endl;
                return 0;  // terminate application with code 0
                break;
        }
        if (searchType == 'E') {
            clearScreen();
            continue;
        }
        editMenu();
        editMenuResponse = getMenuInput('A', 'D');

        switch (editMenuResponse) {
            case ('A'):
                members->push_back(addNewMember(currentID));
                break;
            case ('B'):
                removeMember(members);
                break;
            case ('C'):
                editMember(members);
                break;
            case('D'):
                clearScreen();
                continue;
        }
    }
}

char searchMember() {  // return a character to tell previous function which
                       // menu to stay
    char searchType;
    searchMemberMenu();
    searchType = getMenuInput('A', 'E');
    return searchType;
}

void readFromFile(std::ifstream &memberFile, std::vector<Member> *&members,
                  int &currentID) {
    if (!memberFile.is_open()) {
        return;
    }
    std::string firstname, lastname, phonenumber;
    int areaCode;
    while (!memberFile.eof()) {
        memberFile >> firstname;
        memberFile >> lastname >> phonenumber >> areaCode;
        memberFile.ignore();
        Member m(firstname, lastname, phonenumber, currentID++, areaCode);
        members->push_back(m);
    }
    // check duplicate
    int index = members->size() - 1;
    if((*members)[index].getFirstName() == (*members)[index - 1].getFirstName()
      && (*members)[index].getLastName() == (*members)[index - 1].getLastName()) {
        members->erase(members->begin() + index);
      }
}

char getMenuInput(char minimum, char maximum) {
    char userInput;
    std::cout << "Select Option: ";
    std::cin >> userInput;
    std::cin.ignore(250, '\n');  // ignore additional input
    userInput = toupper(userInput);
    while (userInput < minimum || userInput > maximum) {
        std::cin.clear();
        std::cout << "Invalid Input. Enter Again: ";
        std::cin >> userInput;
        std::cin.ignore(250, '\n');
        userInput = toupper(userInput);
    }
    return userInput;
}

int getIntInput(int minimum, int maximum) {
    int input;
    std::cin >> input;
    if(std::cin.fail() || input < minimum || input > maximum) {
        std::cin.clear();
        std::cin.ignore(); // used to avoid infinite loop
        std::cout << "Invalid Input. Enter again: ";
        std::cin >> input;
    }
    return input;
}

bool searchMemberAssign(std::vector<Member> *&members, char searchType) {
    std::vector<int> instancesFound;
    int ID_input, ID_index;
    switch (searchType) {
        case ('A'):
            instancesFound = searchByName(members);
            break;
        case ('B'):
            instancesFound = searchByPhone(members);
            break;
        case ('C'):
            instancesFound = searchByAreaCode(members);
            break;
        case ('D'):
            std::cout << "Enter member ID: ";
            ID_input = getIntInput(0, 999999);
            ID_index = searchByID(members, ID_input);
            viewSpecificMember(members, ID_index);
            if (ID_index == -1) return false;
            break;
        case ('E'):
            return true;
            break;
    }
    clearScreen();
    if (instancesFound[0] == -1) {
        std::cout << "No Results Found" << std::endl;
        return false;
    }
    std::cout << instancesFound.size() << " results found" << std::endl;
    printMenuOutline();
    for (int i = 0; i < instancesFound.size(); i++) {
        viewSpecificMember(members, instancesFound[i]);
    }
    return true;
}

std::vector<int> searchByName(std::vector<Member> *&members) {
    std::vector<int> instancesFound;
    std::string nameInput;
    std::string name[2];
    std::cout << "Enter member name: ";
    getline(std::cin, nameInput);
    std::stringstream sstr(nameInput);
    int count = 0;

    while (sstr >> nameInput) {
        name[count++] = nameInput;
    }
    for (int i = 0; i < members->size(); i++) {
        for (int j = 0; j < count; j++) {
            if (name[j] == (*members)[i].getFirstName() ||
                name[j] == (*members)[i].getLastName())
                instancesFound.push_back(i);
        }
    }
    if (instancesFound.size() == 0)
        instancesFound.push_back(-1);  // push back -1 which means empty
    return instancesFound;
}

std::vector<int> searchByPhone(std::vector<Member> *&members) {
    std::vector<int> instancesFound;
    std::string phoneNumber;
    std::cout << "Enter member phone number: ";
    phoneNumber = getPhoneNumberInput();
    for (int i = 0; i < members->size(); i++) {
        if ((*members)[i].getPhoneNumber() == phoneNumber)
            instancesFound.push_back(i);
    }
    if (instancesFound.size() == 0) instancesFound.push_back(-1);
    return instancesFound;
}

std::vector<int> searchByAreaCode(std::vector<Member> *&members) {
    int areacode;
    std::vector<int> instancesFound;
    std::cout << "Enter Area Code: ";
    areacode = getAreaCodeInput();
    for (int i = 0; i < members->size(); i++) {
        if ((*members)[i].getAreaCode() == areacode)
            instancesFound.push_back(i);
    }
    if (instancesFound.size() == 0) instancesFound.push_back(-1);
    return instancesFound;
}

// passing key since we want to loop this function if the ID is invalid
int searchByID(std::vector<Member> *&members, int key) {
    for (int i = 0; i < members->size(); i++) {
        if (key == (*members)[i].getMemberID()) return i;
    }
    return -1;
}

bool confirmChange(std::string action, int memberID,
                   std::string memberFirstName, std::string memberLastName) {
    std::cout << "Confirm " << action << " Member: " << memberFirstName << " "
              << memberLastName << " ID: " << memberID << std::endl;
    std::cout << "[A.] Make Changes" << std::endl;
    std::cout << "[B.] Go Back" << std::endl;
    char userInput = getMenuInput('A', 'B');
    if (userInput == 'A') return true;
    return false;
}

Member addNewMember(int &currentID) {
    std::string firstname, lastname, phonenumber;
    int areacode;
    std::cout << "Enter member first name: ";
    firstname = getNameInput();
    std::cout << "Enter member last name: ";
    lastname = getNameInput();
    std::cout << "Enter phone number: ";
    phonenumber = getPhoneNumberInput();
    std::cout << "Enter area code: ";
    areacode = getAreaCodeInput();
    Member m(firstname, lastname, phonenumber, currentID++, areacode);
    clearScreen();
    return m;
}

void removeMember(std::vector<Member> *&members) {
    int ID;
    std::cout << "Enter member ID: ";
    ID = getIntInput(0, 999999);
    int index = searchByID(members, ID);
    if (index == -1) {
        std::cout << "No Member Associated With ID: " << ID << std::endl;
        return;
    }
    if (!confirmChange("Removing", ID, (*members)[index].getFirstName(),
                       (*members)[index].getLastName()) == true) {
        std::cout << "No Changes Were Made" << std::endl;
        return;
    }
    members->erase(members->begin() + index);  // erase at the certain index
    clearScreen();
    std::cout << "Successfully Removed Member: "
              << "Member ID " << ID << ": " << (*members)[index].getFirstName()
              << " " << (*members)[index].getLastName() << std::endl;
}

void editMember(std::vector<Member> *&members) {
    int memberID_search, index;
    char editType;
    std::cout << "Enter Member ID: ";
    memberID_search = getIntInput(0, 999999);
    index = searchByID(members, memberID_search);
    while (index == -1) {
        std::cout << "No Member Associated With ID: " << memberID_search
                  << std::endl;
        std::cout << "Enter Member ID: ";
        memberID_search = getIntInput(0, 999999);
        searchByID(members, memberID_search);
    }
    editMemberInfoMenu((*members)[index]);
    editType = getMenuInput('A', 'E');
    editMemberAssign((*members)[index], editType);
    clearScreen();
    std::cout << "Changes Succesfully Made" << std::endl;
}

void editMemberAssign(Member &member, char editType) {
    std::string firstName_new, lastName_new, phoneNumber_new;
    int areaCode_new, memberID_new;
    switch (editType) {
        case ('A'):
            std::cout << "Enter New Name: ";
            firstName_new = getNameInput();
            member.changeFirstName(firstName_new);
            break;
        case ('B'):
            std::cout << "Enter New Last Name: ";
            lastName_new = getNameInput();
            member.changeLastName(lastName_new);
            break;
        case ('C'):
            std::cout << "Enter New Phone Number: ";
            phoneNumber_new = getPhoneNumberInput();
            member.changePhoneNumber(phoneNumber_new);
            break;
        case ('D'):
            std::cout << "Enter New Area Code: ";
            areaCode_new = getAreaCodeInput();
            member.changeAreaCode(areaCode_new);
            break;
        case('E'):
            return;
    }
}

std::string getNameInput() {
    bool isValid = true;
    std::string nameInput;
    do {
        isValid = true;
        std::cin >> nameInput;
        for (std::string::size_type i = 0; i < nameInput.length(); i++) {
            if (nameInput[i] >= '0' && nameInput[i] <= '9') {
                isValid = false;
                std::cout << "Names Cannot Have Numerical Values" << std::endl;
                std::cout << "Enter again: ";
                break;  // break out the for loop
            }
        }
    } while (isValid == false);
    return nameInput;
}

std::string getPhoneNumberInput() {
    bool isValid = true;
    int dashCount = 0;
    std::string phoneNumberInput;
    do {
        isValid = true;
        std::cin >> phoneNumberInput;
        for(std::string::size_type i = 0; i < phoneNumberInput.length(); i++) {
            if(phoneNumberInput[i] < '0' || phoneNumberInput[i] > '9') {
                if(phoneNumberInput[i] == '-') continue;
                std::cout << "Number Cannot Have Non-Numerical Values" << std::endl;
                std::cout << "Enter Again: ";
                isValid = false;
                break;
            }
        }
        if(isValid == false) continue;
        if(phoneNumberInput.length() == 10) {
            phoneNumberInput.insert(3, "-");
            phoneNumberInput.insert(7, "-");
        } else if(phoneNumberInput.length() == 12) {
            if(phoneNumberInput[3] != '-' || phoneNumberInput[6] == '-') {
                std::cout << "Invalid Number Syntax" << std::endl;
                std::cout << "Enter Again: ";
                isValid = false;
                continue;
            }
        }
        else {
            std::cout << "Invalid Number Syntax" << std::endl;
            std::cout << "Enter Again: ";
            isValid = false;
        }
    } while(isValid == false);
    return phoneNumberInput;
}

int getAreaCodeInput() {
    int areaCode_input;
    areaCode_input = getIntInput(10000, 99999);
    return areaCode_input;
}

void saveAndExit(std::vector<Member> *&members, std::string filename) {
    std::ofstream out;
    std::string fileExt[2] = {"txt", "dat"};
    char saveType;
    saveExitMenu();
    saveType = getMenuInput('A', 'B');
    switch (saveType) {
        case ('A'):
            out.open(filename.c_str());
            break;
        case ('B'):
            std::cout << "Enter name for file: ";
            std::cin >> filename;
            std::cout << "Save As: " << std::endl;
            std::cout << "[A.] .txt" << std::endl;
            std::cout << "[B.] .dat" << std::endl;
            switch(getMenuInput('A', 'B')) {
                case('A'):
                    filename += ".txt";
                    break;
                case('B'):
                    filename += ".dat";
                    break;
            }
            out.open(filename.c_str());
            break;
    }
    int membsize = members->size() - 1;
    for(int i = 0; i < membsize; i++) {
        out << (*members)[i].getFirstName() << " ";
        out << (*members)[i].getLastName() << " ";
        out << (*members)[i].getPhoneNumber() << " ";
        out << (*members)[i].getAreaCode() << std::endl;
    }
    delete members; // free up space
    std::cout << "~Goodbye~" << std::endl;
    exit(0); // exit with no errors
}