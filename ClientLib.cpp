// function for all the displays
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <stdlib.h>
#include <chrono>

#include "Member.h"
#include "ClientLib.h"

void clearScreen() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

std::ostream& operator<<(std::ostream& out, Member& member) {
    out << std::right << std::setw(4) << member.getMemberID() << "\t\t" << std::left << std::setw(16) << member.getFirstName();
    out << std::left << std::setw(16) << member.getLastName() << std::left << std::setw(16) << member.getPhoneNumber();
    out << member.getAreaCode();
    return out;
} 

void printLine() {
    std::cout << "-------------------------------------------------------------------------------------" << std::endl;
}

void mainMenu() {
    std::cout << "+-------------------------+\n";
    std::cout << "|        MAIN MENU        |\n";
    std::cout << "+-------------------------+\n";
    std::cout << "|[A.] View All Members    |\n";
    std::cout << "|[B.] Search Members      |\n";
    std::cout << "|[C.] Edit Members        |\n";
    std::cout << "|[D.] Exit Application    |\n";
    std::cout << "+-------------------------+" << std::endl; // clear the buffer
}

void printMenuOutline() {
    printLine();
    std::cout << std::right << std::setw(4) << "ID#" << "\t\t" << std::left << std::setw(16) << "First Name";
    std::cout << std::left << std::setw(16) << "Last Name" << std::left << std::setw(16) << "Phone Number";
    std::cout << std::left << std::setw(12) << "ZIP Code" << std::endl;
    printLine();
}

void loadMenu() {
    std::cout << "+-----------------------------------+\n";
    std::cout << "|             LOAD MENU             |\n";
    std::cout << "+-----------------------------------+\n";
    std::cout << "|[A.] Load From Main File           |\n";
    std::cout << "|[B.] Load From Custom File         |\n";
    std::cout << "|[C.] Load Empty                    |\n";
    std::cout << "|[D.] Exit Application              |\n";
    std::cout << "+-----------------------------------+" << std::endl;
}

void loadMenuFailed(std::string filename) {
    if(filename == "data.txt") {
        std::cout << "Error Opening Main File. Check Data.txt Folder";
    }
    else {
        std::cout << "Could not open " << filename << std::endl;
    }
}

void editMenu() {
    std::cout << "+-------------------------+\n";
    std::cout << "|        EDIT MENU        |\n";
    std::cout << "+-------------------------+\n";
    std::cout << "|[A.] Add Member          |\n";
    std::cout << "|[B.] Remove Member       |\n";
    std::cout << "|[C.] Edit Member         |\n";
    std::cout << "|[D.] Go Back             |\n";
    std::cout << "+-------------------------+" << std::endl; // clear the buffer
}

void viewAllMembers(std::vector<Member> *&members) {
    printMenuOutline();
    for(int i = 0; i < members->size(); i++) {
        viewSpecificMember(members, i);
    }
}

void viewSpecificMember(std::vector<Member> *& members, int index) {
    std::cout << (*members)[index] << std::endl;
    printLine();
}

void editMemberInfoMenu(Member &m) {
    std::cout << "+--------------------------------------+\n";
    std::cout << "Editing Information For Member ID: " << m.getMemberID() << std::endl;
    std::cout << "Member Name: " << m.getFirstName() << " " << m.getLastName() << std::endl;
    std::cout << "Phone Number: " << m.getPhoneNumber() << std::endl;
    std::cout << "Area Code: "<< m.getAreaCode() << std::endl;
    std::cout << "+--------------------------------------+\n";
    std::cout << "[A.] Edit First Name\n";
    std::cout << "[B.] Edit Last Name \n";
    std::cout << "[C.] Edit Phone Number\n";
    std::cout << "[D.] Edit Area Code\n";
    std::cout << "[E.] Go Back\n";
    std::cout << "+--------------------------------------+\n";
}


void searchMemberMenu() {
    std::cout << "+-------------------------+\n";
    std::cout << "|      Search Member      |\n";
    std::cout << "+-------------------------+\n";
    std::cout << "|[A.] Search Name         |\n";
    std::cout << "|[B.] Search Phone Number |\n";
    std::cout << "|[C.] Search Area Code    |\n";
    std::cout << "|[D.] Search ID           |\n";
    std::cout << "|[E.] Go Back             |\n";
    std::cout << "+-------------------------+" << std::endl;
}

void saveExitMenu() {
    std::cout << "+------------------------+\n";
    std::cout << "|       Save Menu        |\n";
    std::cout << "+------------------------+\n";
    std::cout << "|[A.] Overwrite File     |\n";
    std::cout << "|[B.] Save As New File   |\n";
    std::cout << "+------------------------+\n";    
}

void printDate() {
    auto currentTime = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    std::cout << "Today's Time & Date: " << ctime(&currentTime);
}