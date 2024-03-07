// bus reservation system login page
#include <iostream>
#include <fstream>
#include <string>
#include <limits>
#include "bus.h"

using namespace std;

void signUp();
void login();
void forgotPassword();
void tasks();
string userName, password, email;
string searchName, searchPass, searchEmail;

void tasks() {
	cout<<"\t\t\t\tWelcome to Travel Bus Reservation System\n";
	int choice;
	bool exitProgram = false;
	do {
	cout<<"\t\t\t\t\t1. Login\n";
	cout<<"\t\t\t\t\t2. Sign up\n";
	cout<<"\t\t\t\t\t3. Forgot Password\n";
	cout<<"\t\t\t\t\t4. Exit\n";
	cout<<"\t\tEnter your choice:  ";
	cin>>choice;
     if (cin.fail()) {
     cout << "\t\t\t\tERROR -- You did not enter an integer\n";
     cin.clear(); 
     cin.ignore();
     }
     else {
	switch(choice) {
		case 1:
			system("cls");
			login();
			break;
	    case 2:
	    	system("cls");
	    	signUp();
	    	break;
	    case 3:
	    	system("cls");
	    	forgotPassword();
	    	break;
		case 4:
			exitProgram = true;
	    	break;	
	    default:
	    	cout<<"\t\t\t\t\t\tInvalid Selection...!\n";
	}
}
}
	while(!exitProgram);
}

void signUp() {
	cout<<"\t\t\t\t\t--------SIGN UP---------"<<endl;
	cin.ignore();//clear the newline character from the input buffer(previous input)
	cout<<"\t\t\t\t\tEnter User Name: ";
	getline(cin, userName);
	cout<<"\t\t\t\t\tEnter Password: ";
	getline(cin, password);
	cout<<"\t\t\t\t\tEnter Your Email: ";
	getline(cin, email);
	//write login data to file
	ofstream loginFile;
	loginFile.open("loginData.txt", ios::out | ios::app);
	loginFile<<userName<<" "<<password<<" "<<email<<endl;
	adminTasks();
	loginFile.close();	
}
void login() {
	cout<<"\t\t\t\t\t-----------LOGIN------"<<endl;
	cin.ignore();
	cout<<"\t\t\t\t\tEnter User Name: ";
	getline(cin, searchName);
	cout<<"\t\t\t\t\tEnter Password: ";
	getline(cin, searchPass);
	
	ifstream loginFile("loginData.txt");
while(loginFile>>userName>>password>>email) {
	if(userName == searchName) {
		if(password == searchPass) {
			cout<<"\t\t\t\t\t-------LOGIN SUCCESSFULLY-----"<<endl;
			adminTasks();
			break;
		}
		else {
			cout<<"\t\t\t\t\tPassword Incorrect\n";
	        break;
		}
	}
}
 if(userName != searchName) {
		cout<<"\t\t\t\t\tLogin failed. User not found or incorrect credentials.\n";
	}
  loginFile.close();
}

void forgotPassword() {
	cout<<"\t\t\t\t\t--------Password Recovery---------\n";
	cin.ignore();
	cout<<"\t\t\t\t\tEnter User Name: ";
	getline(cin, searchName);
	cout<<"\t\t\t\t\tEnter Email: ";
	getline(cin, searchEmail);
	
	ifstream loginFile("loginData.txt");
	while(loginFile>>userName>>password>>email) {
		if(userName == searchName) {
			if(email == searchEmail) {
				cout<<"\t\t\t\t\tYour password is "<<password<<endl;
				break;
			}
			else {
				cout<<"\t\t\t\t\tIncorrect Email\n";
				break;
			}
		}
	}
	if(userName != searchName) {
		cout<<"\t\t\t\t\tUser Name Not Found!\n";
	}
	loginFile.close();
}
