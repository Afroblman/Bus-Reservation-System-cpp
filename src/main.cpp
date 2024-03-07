#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include "login-page.h"
#include "passenger.h"

using namespace std;

int main() {
cout<<"\t\t\t\t\tWelcome to Travel Bus Reservation System"<<endl;
int role;
cout<<"\t\t\t\t\t\t1. Adminstrator"<<endl;
cout<<"\t\t\t\t\t\t2. Passenger"<<endl;
cout<<"\t\t\t\t\t\t3. Exit"<<endl;
cout<<"\t\t Enter Your Choice ";
cin>>role;
switch(role) {
	case 1:
		system("cls");
		system("COLOR 2E");
		tasks();
		break;
	case 2:
		system("cls");
		system("COLOR 3F");
		passengerTasks();
		break;
	case 3:
		exit(0);
	default:
		cout<<"\t\t\t\t\t\tInvalid Selection"<<endl;

}
	return 0;
}


