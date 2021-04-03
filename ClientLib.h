#ifndef CLIENTLIB_H
#define CLIENTLIB_H
#include <iostream>
#include <string>
#include <vector>
#include "Member.h"
void clearScreen();
void mainMenu();
std::ostream& operator<<(std::ostream& out, Member& member);
void printLine();
void printMenuOutline();
void loadMenu();
void loadMenuFailed(std::string filename);
void editMenu();
void viewAllMembers(std::vector<Member> *&members);
void viewSpecificMember(std::vector<Member> *& members, int index);
void editMemberInfoMenu(Member &m);
void searchMemberMenu();
void saveExitMenu();
void printDate();
#endif