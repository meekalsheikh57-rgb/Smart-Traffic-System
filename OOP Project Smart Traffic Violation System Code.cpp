#include <iostream>
#include <vector>
#include <fstream>
using namespace std;

string inputCenter(string text) {
    int width = 100;

    int spaces = (width - text.length()) / 2;
    for (int i = 0; i < spaces; i++)
        cout << " ";
    cout << text << endl;

    int inputSpaces = (width - 20) / 2; 
    for (int i = 0; i < inputSpaces; i++)
        cout << " ";

    string value;
    getline(cin, value);

    return value;
}

    void verticalSpace() {
    for (int i = 0; i < 8; i++) {
        cout << endl;
    }
}

    void verticalSpace();

void centerText(string text) {
    int width = 160; 
    int spaces = (width - text.length()) / 2;

    for (int i = 0; i < spaces; i++)
        cout << " ";

    cout << text << endl;
}

string inputCentered(string prompt) {
    centerText(prompt);

    string value;

    int width = 100;
    int spaces = (width - 20) / 2; 

    for (int i = 0; i < spaces; i++)
        cout << " ";

    getline(cin, value);
    return value;
}

void showHistory() {
    ifstream file("challan.txt");

    string line;
    centerText("\n--- DRIVER HISTORY ---\n");

    while (getline(file, line)) {
        cout << line << endl;
    }

    file.close();
}

class Driver {
public:
    string driverName;
    int licenseNo;

    void inputDriver() {
    cout << "\nEnter Driver Name: ";
    cin.ignore();
    getline(cin, driverName);

    cout << "\nEnter License Number: ";
    cin >> licenseNo;
    }
};

class Vehicle {
public:
    string vehicleNo;
    string vehicleType;

    void inputVehicle() {
    cout << "\nEnter Vehicle Number: ";
    cin >> vehicleNo;

    cout << "\nVehicle Type (Car/Bike): ";
    cin >> vehicleType;
    }
};

class Violation {
public:
    string violationType;
    float fine;

    void detectViolation(int choice) {
        if (choice == 1) {
            violationType = "Signal Break ( Both Vehicles )";
            fine = 1000;
        } else if (choice == 2) {
            violationType = "Over Speed ( for Car Drivers )";
            fine = 3000;
        } else if (choice == 3) {
            violationType = "No Helmet ( for Bikers )";
            fine = 1500;
        } else if (choice == 4) {
            violationType = "Illegal Parking ( for Car Drivers )";
            fine = 2000;
        } else if (choice == 5){
        	violationType = "No Seat Belt ( for Car Drivers )";
        	fine = 2500;
		} else {
			violationType = "Unknown";
			fine = 0;
		}
    }

    void showRoadScene() {

    centerText("        LIVE ROAD SCENE ");
    cout << "\n";

    centerText("        Police Warden");
    centerText("          O");
    centerText("          /|\\");
    centerText("          / \\");
    centerText("         /   \\");

    cout << "\n";

    centerText("==============================================");
    centerText("                  ROAD");
    centerText("==============================================");

    centerText("        _________");
    centerText("       /_|_____|_\\");
    centerText("             <-----O-------O----->  CAR");

    cout << "\n";

    if (violationType == "Signal Break") {
        centerText(" SIGNAL BROKEN!");
    } else if (violationType == "Over Speed") {
        centerText(" OVER SPEED!");
    } else if (violationType == "No Helmet") {
        centerText(" NO HELMET!");
    } else if (violationType == "Illegal Parking") {
        centerText(" ILLEGAL PARKING!");
    } else if (violationType == "No SeatBelt") {
    	centerText(" NO SEATBELT!");
	} else {
		violationType = "Invalid Choice Entered";
		fine = 0;
	}	    
}
};

class Challan : public Driver, public Vehicle, public Violation {
public:
   int challanID;
   string status = "UNPAID";
    
    void saveToFile(){
    ofstream file("challan.txt", ios::app);

    file << challanID << " "
         << driverName << " "
         << licenseNo << " "
         << vehicleNo << " "
         << vehicleType << " "
         << violationType << " "
         << fine << " "
         << status
         << endl;

    file.close();
	}
    void generateChallan() {
    	
    	int pay;
        cout << "\n1. Pay Challan\n0. Skip\nChoice: ";
        cin >> pay;

        if (pay == 1) {
        status = "PAID";
        }

    cout << "\nEnter Challan ID: ";
    cin >> challanID;

    inputDriver();
    inputVehicle();

    int choice;

    centerText("\nSelect Violation:");
    centerText("\n1. Signal Break");
    centerText("\n2. Over Speed");
    centerText("\n3. No Helmet");
    centerText("\n4. Illegal Parking");
    centerText("\n5. No SeatBelt");

    cout << "\nChoice: ";
    cin >> choice;
    
    if (choice < 1 || choice > 5) {
    centerText("Wrong choice entered! Please try again.");
    return;
    }

    detectViolation(choice);

    showRoadScene();
    showReceipt();
    }

    void showReceipt() {
    centerText("==============================");
    centerText("TRAFFIC CHALLAN RECEIPT");
    centerText("==============================");

    centerText("Challan ID   : " + to_string(challanID));
    centerText("Driver Name  : " + driverName);
    centerText("License No   : " + to_string(licenseNo));
    centerText("Vehicle No   : " + vehicleNo);
    centerText("Vehicle Type : " + vehicleType);
    centerText("Violation    : " + violationType);
    centerText("Fine Amount  : Rs. " + to_string(fine));
    centerText("Status       : " + status);

    centerText("==============================");
    }

};

vector<Challan> history;

int main() {
    int again;

    centerText(" <|==== SMART TRAFFIC VIOLATION SYSTEM ====|> \n");

    do {
        Challan c1;
        c1.generateChallan();
        history.push_back(c1);
        c1.saveToFile();

        centerText("\nTraffic Warden! Generate another challan?");
        centerText("\n1. YES\n0. NO\nChoice: ");
        cin >> again;
        
        for (int i = 0; i < history.size(); i++) {
        history[i].showReceipt();
        }

    } while (again == 1);

    centerText("\nSystem Closed \n");
    return 0;
}