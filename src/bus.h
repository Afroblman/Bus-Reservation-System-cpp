// bus page
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

using namespace std;

struct Bus {
	int busNumber;
	string source, destination,startingTime;
	float tarrif;
};
Bus bus;
void addBus();
void updateBusData();
void deleteBus();
Bus searchBus();
void report();
void displayBusData();
void adminTasks() {
	cout<<"\t\t\t\t\t---------Bus Management----------"<<endl;
	int choice;
	bool exitProg = false;
	
	do {
	cout<<"\t\t\t\t\t1. Add Bus"<<endl;
	cout<<"\t\t\t\t\t2. Update Bus"<<endl;
	cout<<"\t\t\t\t\t3. Delete Bus"<<endl;
	cout<<"\t\t\t\t\t4. Display Bus"<<endl;
	cout<<"\t\t\t\t\t5. Bus Report"<<endl;
	cout<<"\t\t\t\t\t6. Exit"<<endl;
	cout<<"\t\t\tEnter your choice: ";
	cin>>choice;
	if (cin.fail()) {
     cout << "\t\t\t\t\tERROR -- You did not enter an integer\n";
     cin.clear(); 
     cin.ignore();
     }
     else {
     	switch(choice) {
     		case 1:
     			system("cls");
     			addBus();
     			break;
     		case 2:
     			system("cls");
     			updateBusData();
     			break;
     		case 3:
     			system("cls");
     			deleteBus();
     			break;
     		case 4:
     			system("cls");
     			displayBusData();
     			break;
     		case 5:
     			system("cls");
     			report();
     			break;
     		case 6:
     			system("cls");
     			exitProg = true;
     			break;
     		default:
     			cout<<"\t\t\t\t\t\tInvalid Selection...."<<endl;
     			
		 }
	 }
	}while(!exitProg);
}



void addBus() {
	cout<<"\t\t\t\t------Bus Registration-------"<<endl;
	cout<<"\t\t\t\t\tEnter Bus Plate Number: ";
	cin>>bus.busNumber;
	cin.ignore();
	cout<<"\t\t\t\t\tEnter Source Place: ";
	getline(cin, bus.source);
	cout<<"\t\t\t\t\tEnter Destination Place: ";
	getline(cin, bus.destination);
	cout<<"\t\t\t\t\tEnter Starting Time: ";
	getline(cin, bus.startingTime);
	cout<<"\t\t\t\t\tEnter Tarrif (in Birr): ";
	cin>>bus.tarrif;
	
	ofstream busFile("busData.txt", ios::app);
	busFile<<bus.busNumber<<"\n"<<bus.source<<"\n"<<bus.destination<<"\n"
	<<bus.startingTime<<"\n"<<bus.tarrif<<"\n"<<endl;
	busFile.close();
}

Bus searchBus() {
	Bus bus;
	int searchBusNumber;
	cout<<"\t\t\t\t\tEnter Bus Plate Number: ";
	cin>>searchBusNumber;
	
	ifstream busFile("busData.txt");
	while(busFile>>bus.busNumber && ws(busFile) && getline(busFile,bus.source) && 
	getline(busFile, bus.destination) && 
	getline(busFile, bus.startingTime) && busFile>>bus.tarrif) {
		if(bus.busNumber == searchBusNumber) {
			return bus;
		}
	}
	busFile.close();
	return Bus{};
}

void displayBusData() {
	cout<<"\t\t\t\t\t--------Display Bus Data--------"<<endl;
 Bus foundBus = searchBus();
	if(foundBus.busNumber != 0) {
		cout << "\t\t\t\t\tBus Number: " << foundBus.busNumber <<endl;
		cout << "\t\t\t\t\tBus Source: " << foundBus.source <<endl;
		cout << "\t\t\t\t\tBus Destination: " << foundBus.destination <<endl;
		cout << "\t\t\t\t\tBus Starting Time: " << foundBus.startingTime <<endl;
		cout << "\t\t\t\t\tBus Tarrif: " << foundBus.tarrif <<"\n"<<endl;
	}
	else {
		cout<<"\t\t\t\t\tBus not found"<<endl;
	}
}

 void updateBusData() {
 	cout<<"\t\t\t\t\t--------Update Bus Data-------"<<endl;
	Bus updateBus = searchBus();
	if(updateBus.busNumber != 0) {
	cin.ignore();
	cout<<"\t\t\t\t\tEnter Source Place: ";
	getline(cin, updateBus.source);
	cout<<"\t\t\t\t\tEnter Destination Place: ";
	getline(cin, updateBus.destination);
	cout<<"\t\t\t\t\tEnter Starting Time: ";
	getline(cin, updateBus.startingTime);
	cout<<"\t\t\t\t\tEnter Tarrif (in Birr): ";
	cin>>updateBus.tarrif;
	
	ifstream busFile("busData.txt");
	ofstream tempFile("tempData.txt");
	while(busFile>>bus.busNumber && ws(busFile) && getline(busFile,bus.source) && 
	getline(busFile, bus.destination) && 
	getline(busFile, bus.startingTime) && busFile>>bus.tarrif) {
		
		if (bus.busNumber == updateBus.busNumber) {
            tempFile <<updateBus.busNumber<< "\n" << updateBus.source << "\n" <<
			updateBus.destination << "\n" << updateBus.startingTime <<"\n" << updateBus.tarrif << "\n"<<endl;

        }
        else {
        tempFile << bus.busNumber << "\n" << bus.source << "\n"
                 << bus.destination << "\n" << bus.startingTime << "\n" << bus.tarrif << "\n"<<endl;
         }
    }
    busFile.close();
    tempFile.close();
    remove("busData.txt");
    rename("tempData.txt", "busData.txt");
    
    
	}
	else {
		cout<<"\t\t\t\t\tBus not found"<<endl;
	}
}

void deleteBus() {
	cout<<"\t\t\t\t--------Delete Bus Data-------"<<endl;
	Bus deletedBus = searchBus();
	if(deletedBus.busNumber != 0) {
	ifstream busFile("busData.txt");
	ofstream tempFile("tempData.txt");
	bool deleteBus = true;
	while(busFile>>bus.busNumber && ws(busFile) && getline(busFile,bus.source) && 
	      getline(busFile, bus.destination) && 
	      getline(busFile, bus.startingTime) && busFile>>bus.tarrif) {
		
		if (bus.busNumber != deletedBus.busNumber) {
		tempFile << bus.busNumber << "\n" << bus.source << "\n"
                 << bus.destination << "\n" << bus.startingTime << "\n" << bus.tarrif << "\n"<<endl;
	}
	
}
	busFile.close();
    tempFile.close();
    remove("busData.txt");
    rename("tempData.txt", "busData.txt");
    cout<<"\t\t\t\t\tDeleted Successfully"<<endl;
}
	else {
		cout<<"\t\t\t\t\tBus not found"<<endl;
	}
}

 void report() {
	cout<<"\t\t\t\t\t--------------Bus Data Report--------------"<<endl;
	Bus bus;
	ifstream busFile("busData.txt");
	int count = 0;
	while(busFile>>bus.busNumber && ws(busFile) && getline(busFile,bus.source) && 
	    getline(busFile, bus.destination) && 
	    getline(busFile, bus.startingTime) && busFile>>bus.tarrif) {
	    cout<<"-------Bus " << ++count << "--------"<<endl;
		cout << "\t\t\t\t\tBus Number: " << bus.busNumber <<endl;
		cout << "\t\t\t\t\tBus Source: " << bus.source <<endl;
		cout << "\t\t\t\t\tBus Destination: " << bus.destination <<endl;
		cout << "\t\t\t\t\tBus Starting Time: " << bus.startingTime <<endl;
		cout << "\t\t\t\t\tBus Tarrif: " << bus.tarrif <<"\n"<<endl;
}
busFile.close();
}
