// passenger page
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <ctime>
#include <cstdlib>
#include <sstream>

using namespace std;

struct ticket {
	string ticketId, passengerName, passengerPhoneNum;
	int busNumber;
	string source, destination, startingTime;
	float tarrif;
};

ticket travelTicket;

bool busFound = false;
void searchBusRoute();
void buyTicket();
void updateTicket();
void displayTicket();
void cancel();
void reserve();
ticket searchTicket();

void passengerTasks() {
    cout<<"\t\t\t\t\tWelcome to Travel Bus Reservation System"<<endl;
	int choice;
	bool exitPass = false;

	do {
	cout<<"\t\t\t\t\t1. Book Ticket"<<endl;
	cout<<"\t\t\t\t\t2. Update Ticket"<<endl;
	cout<<"\t\t\t\t\t3. Display Ticket"<<endl;
	cout<<"\t\t\t\t\t4. cancel Ticket"<<endl;
	cout<<"\t\t\t\t\t5. Exit"<<endl;
	cout<<"\t\t\tEnter your choice: ";
	cin>>choice;
	cin.ignore();
	if (cin.fail()) {
     cout << "\t\t\t\t\tERROR -- You did not enter an integer\n";
     cin.clear();
     cin.ignore();
     }
     else {
     	switch(choice) {
     		case 1:
     			system("cls");
     			buyTicket();
     			break;
     		case 2:
     			system("cls");
     			updateTicket();
     			break;
     		case 3:
     			system("cls");
     			displayTicket();
     			break;
     		case 4:
     			system("cls");
     			cancel();
     			break;
     		case 5:
     			system("cls");
     			exitPass = true;
     			break;
     		default:
     			cout<<"\t\t\t\t\tInvalid Selection...."<<endl;

		 }
		 }
	}while(!exitPass);
}
void searchBusRoute() {
	Bus bus;
	string searchSource, searchDestination;
	cout << "\t\t\t\t\tEnter Source: ";
	getline(cin, searchSource);
	cout << "\t\t\t\t\tEnter Destination: ";
	getline(cin, searchDestination);

	ifstream busFile("busData.txt");
	while(busFile>>bus.busNumber && ws(busFile) && getline(busFile,bus.source) &&
	getline(busFile, bus.destination) &&
	getline(busFile, bus.startingTime) && busFile>>bus.tarrif) {
		if(bus.source == searchSource && bus.destination == searchDestination) {
		cout << "\t\t\t\t\tBus Number: " << bus.busNumber <<endl;
		cout << "\t\t\t\t\tBus Source: " << bus.source <<endl;
		cout << "\t\t\t\t\tBus Destination: " << bus.destination <<endl;
		cout << "\t\t\t\t\tBus Starting Time: " << bus.startingTime <<endl;
		cout << "\t\t\t\t\tBus Tarrif: " << bus.tarrif <<endl;
		busFound = true;
		break;
		}
	}
	if(bus.source != searchSource || bus.destination != searchDestination) {
		cout<<"\t\t\t\t\tNo Available Bus"<<endl;
		busFound = false;
	}
	busFile.close();

}

void buyTicket() {
	cout<<"\t\t\t\t\t--------Reserve Ticket---------"<<endl;
	cout<<"\t\t\t\t\tSelect your Preferred Bus"<<endl;
	searchBusRoute();
	if(busFound) {
		reserve();
	}
}
void reserve() {
	cout<<"\t\t\t\t\tEnter Your name: ";
	getline(cin, travelTicket.passengerName);
	cout<<"\t\t\t\t\tEnter Phone Number: ";
	getline(cin,travelTicket.passengerPhoneNum);
       stringstream ss;
       srand(static_cast<unsigned int>(time(NULL)));
       ss << rand() % 9000 + 1000;
       travelTicket.ticketId = ss.str();
	cout<<"\t\t\t\t\tEnter Bus Number from the given list to buy ticket"<<endl;
	Bus bookBus = searchBus();
	if(bookBus.busNumber != 0) {

		ofstream ticketFile("ticketData.txt",ios::app);
		ticketFile<<travelTicket.ticketId<<"\n"<<travelTicket.passengerName<<"\n"
		<<travelTicket.passengerPhoneNum<<"\n"<<bookBus.busNumber<<"\n"
		<<bookBus.source<<"\n"<<bookBus.destination<<"\n"<<bookBus.startingTime<<"\n"
		<<bookBus.tarrif <<"\n" <<endl;
        cout<<"\t\t\t\tYour Ticket Id Number: "<<travelTicket.ticketId<<endl;
        cout<<"\t\t\t\tDon't forget to save this number"<<endl;
	}
	else {
		cout<<"\t\t\t\t\tEnter the correct Bus Number"<<endl;
	}

}

ticket searchTicket() {
	string searchTicketId;
	cout<<"\t\t\t\t\tEnter Your Ticket Id: ";
	getline(cin, searchTicketId);

	ifstream ticketFile("ticketData.txt");
	while(ws(ticketFile)&&getline(ticketFile, travelTicket.ticketId) && getline(ticketFile, travelTicket.passengerName) &&
	getline(ticketFile, travelTicket.passengerPhoneNum) && ticketFile>>travelTicket.busNumber && ws(ticketFile)
	&& getline(ticketFile,travelTicket.source) && getline(ticketFile, travelTicket.destination) &&
	getline(ticketFile, travelTicket.startingTime) && ticketFile>>travelTicket.tarrif) {
		if(travelTicket.ticketId == searchTicketId) {
			return travelTicket;
		}
	}
	ticketFile.close();
	return ticket{};
}

void displayTicket() {
	cout<<"\t\t\t\t\t--------Display Your Ticket--------"<<endl;
 ticket foundTicket = searchTicket();
	if(foundTicket.busNumber != 0) {
		cout << "\t\t\t\t\tTicket Id: " << foundTicket.ticketId <<endl;
		cout<<"\t\t\t\t\tPassenger Name: " << foundTicket.passengerName <<endl;
		cout<<"\t\t\t\t\tPhone Number: " << foundTicket.passengerPhoneNum <<endl;
		cout<<"\t\t\t\t\tBus Number: " << foundTicket.busNumber <<endl;
		cout << "\t\t\t\t\tBus Source: " << foundTicket.source <<endl;
		cout << "\t\t\t\t\tBus Destination: " << foundTicket.destination <<endl;
		cout << "\t\t\t\t\tBus Starting Time: " << foundTicket.startingTime <<endl;
		cout << "\t\t\t\t\tBus Tarrif: " << foundTicket.tarrif <<"\n"<<endl;
	}
	else {
		cout<<"\t\t\t\t\tTicket not found"<<endl;
	}
}

void updateTicket() {
	cout<<"\t\t\t\t\t--------Update Your Ticket-------"<<endl;
	ticket updateTicket = searchTicket();
	if(updateTicket.ticketId != "") {
	cout<<"\t\t\t\t\tSelect your New Bus"<<endl;
	searchBusRoute();

    if(busFound) {
	ifstream ticketFile("ticketData.txt");
	ofstream tempFile("tempTicketData.txt");
    while (ws(ticketFile) && getline(ticketFile, travelTicket.ticketId) &&
               getline(ticketFile, travelTicket.passengerName) &&
               getline(ticketFile, travelTicket.passengerPhoneNum) &&
               ticketFile>>travelTicket.busNumber && ws(ticketFile)&&
               getline(ticketFile, travelTicket.source) &&
               getline(ticketFile, travelTicket.destination) &&
               getline(ticketFile, travelTicket.startingTime) &&
               ticketFile>>travelTicket.tarrif && ws(ticketFile)) {

		if (travelTicket.ticketId == updateTicket.ticketId) {
            Bus bookBus = searchBus();
	    if(bookBus.busNumber != 0) {
		tempFile<<travelTicket.ticketId<<"\n"<<travelTicket.passengerName<<"\n"<<travelTicket.passengerPhoneNum
		<<"\n"<<bookBus.busNumber<<"\n"<<bookBus.source<<"\n"
		<<bookBus.destination<<"\n"<<bookBus.startingTime<<"\n"
		<<bookBus.tarrif<<"\n"<<endl;
        
	}
	else {
		cout<<"\t\t\t\t\tWrong Bus Number"<<endl;
	}

        }
        else {
        tempFile << travelTicket.ticketId << "\n" << travelTicket.passengerName << "\n"
		<< travelTicket.passengerPhoneNum << "\n" << travelTicket.busNumber << "\n"
		<< travelTicket.source << "\n" << travelTicket.destination
		<< "\n" << travelTicket.startingTime << "\n" << travelTicket.tarrif<<"\n"<<endl;
         }
    }

    ticketFile.close();
    tempFile.close();
    remove("ticketData.txt");
    rename("tempTicketData.txt", "ticketData.txt");
    cout<<"\t\t\t\t\tTicket Updated Successfully"<<endl;
}
else {
	return;
}
}
else {
	cout<<"\t\t\t\t\tTicket not found"<<endl;
}
	}


void cancel() {
	cout<<"\t\t\t\t\t--------Cancel Your Ticket-------"<<endl;
    ticket deletedTicket = searchTicket();
    cout<<"\t\t\t\tAre you sure to cancel this ticket Y/N: ";
    char decision;
    cin>>decision;
    if(decision == 'Y') {
    if (deletedTicket.ticketId != "") {
        ifstream ticketFile("ticketData.txt");
        ofstream tempFile("tempTicketData.txt");

        while (ws(ticketFile) && getline(ticketFile, travelTicket.ticketId) &&
               getline(ticketFile, travelTicket.passengerName) &&
               getline(ticketFile, travelTicket.passengerPhoneNum) &&
               ticketFile>>travelTicket.busNumber && ws(ticketFile)&&
               getline(ticketFile, travelTicket.source) &&
               getline(ticketFile, travelTicket.destination) &&
               getline(ticketFile, travelTicket.startingTime) &&
               ticketFile>>travelTicket.tarrif && ws(ticketFile)) {

            if (travelTicket.ticketId != deletedTicket.ticketId) {
                tempFile << travelTicket.ticketId << "\n" << travelTicket.passengerName << "\n"
                         << travelTicket.passengerPhoneNum << "\n" << travelTicket.busNumber << "\n"
                         << travelTicket.source << "\n" << travelTicket.destination << "\n"
                         << travelTicket.startingTime << "\n" << travelTicket.tarrif << "\n"<<endl;
            }
        }

        ticketFile.close();
        tempFile.close();
        remove("ticketData.txt");
        rename("tempTicketData.txt", "ticketData.txt");
        cout << "\t\t\t\t\tTicket Cancelled Successfully" << endl;
    } else {
        cout << "\t\t\t\t\tTicket not found" << endl;
    }
}
else {
	return;
}
}

