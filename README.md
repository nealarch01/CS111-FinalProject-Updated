# cs-membership-proj

For my final project I'm going to make a membership database program. The input.dat file contains information of 
	- First name, last name, phonenumber (declared as unsigned long long int), and area code

The names in my database are randomly generated from an external website
	- http://random-name-generator.info/

I chose to have phone numbers declared as an unsigned long long int instead of a string so I can meet the criteria of searching for numeric query

- The phone number look up will find one member (numeric query)
- The zip code will find multiple members (numeric query)

I also decided to add a zipcode (also randomly generated)
I made my own program to generate the random phone numbers and zip codes
https://repl.it/join/tqgtgiqx-neala1



How the app works: 
1. Membership App greets user
2. Will prompt user 4 options:
		A. View all members
		B. Search for member by first, last, and both names
		C. Search for member by phone number
		D. Search for member by area code
3. another function called promptOptions() will be called in main() displaying another set of options a user can do
		A. Add new member
		B. Remove member
		C. Edit member information
		D. Edit
	This function will use pass by reference. Once promptOptions() is called, it is going to split into 3 different functions that can manipulate information of the database

	addNewMember function parameters be pass by reference
	removeMember function parameters be pass by reference
	editMember function only struct array object parameter will be pass by reference, numberofmembers will be const int since the number of members will not change

	
	** Also: changes within the database only occur in the struct array and do not change the data in the input.dat so if the application ends, no new information will be saved


I already started the code but I'm working on it on my own IDE but will paste it here as soon as my github processes my information so I can get the hacker plan
I did put a sample of what the code looks like though in main
