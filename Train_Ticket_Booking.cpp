#include <iostream>
#include <vector>
#include <string>

using namespace std;

int ticketNumber=0;

int totLowerBerth=2;
int totSideLowerBerth=2;
int totMiddleBerth=2;
int totUpperBerth=2;

int lowerBerth=0;
int sideLowerBerth=0;
int middleBerth=0;
int upperBerth=0;


struct Passenger {
    string name;
    int age;
    char gender;
    string berthPreference;
    int coachNum;
    int ticketNum;
};

class RailwayReservationSystem {
private:
    struct Ticket {
        Passenger passenger;
        bool isConfirmed=false;
    };

    vector<Ticket> confirmedTickets;
    vector<Ticket> racTickets;
    vector<Ticket> waitingList;

    const int totalBerths = 63;
    const int totalRacBerths = 18;
    const int maxWaitingListSize = 10;
    

public:
	
	void lowerAvailability(Ticket& newTicket,Passenger& passenger){
		if(lowerBerth<totLowerBerth)
		{
			newTicket.passenger.berthPreference = "Lower";
			lowerBerth++;
			newTicket.isConfirmed = true;
		}
		else{
			passenger.berthPreference="Side-Lower";
		}	
	}
	
	void sideLowerAvailability(Ticket& newTicket,Passenger& passenger)
	{
		if(sideLowerBerth<totSideLowerBerth)
		{
			newTicket.passenger.berthPreference="Side-Lower";
			sideLowerBerth++;
			newTicket.isConfirmed = true;
		}else{
			passenger.berthPreference="Middle";
		}
	}
	
	void middleAvailability(Ticket& newTicket,Passenger& passenger)
	{
		if(middleBerth<totMiddleBerth)
		{
			newTicket.passenger.berthPreference="Middle";
			middleBerth++;
			newTicket.isConfirmed = true;
		}else{
			passenger.berthPreference="Upper";
		}
	}
	
	void upperAvailability(Ticket& newTicket,Passenger& passenger)
	{
		if(upperBerth<totUpperBerth)
		{
			newTicket.passenger.berthPreference="Upper";
			upperBerth++;
			newTicket.isConfirmed = true;
		}
	}
	
    void bookTicket( Passenger& passenger) {
        if (waitingList.size() >= maxWaitingListSize) {
            cout << "No tickets available" << endl;
            return;
        }

        if (passenger.age < 5) {
            cout << "Children below 5 years are not allowed to book tickets." << endl;
            return;
        }

        Ticket newTicket;
        newTicket.passenger = passenger;

		if (passenger.age >= 60 || (passenger.gender == 'F' || passenger.gender == 'f' || passenger.berthPreference == "Lower")) {
			if(!newTicket.isConfirmed){
				lowerAvailability(newTicket,passenger);
			}if(!newTicket.isConfirmed)
			{
	        	sideLowerAvailability(newTicket,passenger);
	    	}if(!newTicket.isConfirmed)
			{
				middleAvailability(newTicket,passenger);
			}if(!newTicket.isConfirmed)
			{
				upperAvailability(newTicket,passenger);
			}	
		}else if(passenger.berthPreference=="Side-Lower")
		{
			if(!newTicket.isConfirmed)
			{
	        	sideLowerAvailability(newTicket,passenger);
	    	}if(!newTicket.isConfirmed){
				lowerAvailability(newTicket,passenger);
			}if(!newTicket.isConfirmed)
			{
				middleAvailability(newTicket,passenger);
			}if(!newTicket.isConfirmed)
			{
				upperAvailability(newTicket,passenger);
			}
		}else if(passenger.berthPreference=="Middle")
		{
			if(!newTicket.isConfirmed)
			{
				middleAvailability(newTicket,passenger);
			}if(!newTicket.isConfirmed){
				lowerAvailability(newTicket,passenger);
			}if(!newTicket.isConfirmed)
			{
	        	sideLowerAvailability(newTicket,passenger);
	    	}if(!newTicket.isConfirmed)
			{
				upperAvailability(newTicket,passenger);
			}	
		}else if(passenger.berthPreference=="Upper")
		{
			if(!newTicket.isConfirmed)
			{
				upperAvailability(newTicket,passenger);
			}if(!newTicket.isConfirmed){
				lowerAvailability(newTicket,passenger);
			}if(!newTicket.isConfirmed)
			{
	        	sideLowerAvailability(newTicket,passenger);
	    	}if(!newTicket.isConfirmed)
			{
				middleAvailability(newTicket,passenger);
			}	
		}
		
        if (confirmedTickets.size() < totalBerths) {
            newTicket.isConfirmed = true;
            confirmedTickets.push_back(newTicket);
            ticketNumber++;
            passenger.ticketNum=ticketNumber;
        } else if (racTickets.size() < totalRacBerths) {
            newTicket.isConfirmed = false;
            racTickets.push_back(newTicket);
        } else {
            newTicket.isConfirmed = false;
            waitingList.push_back(newTicket);
        }

        cout << "Ticket booked successfully!" << endl;
    }

    void cancelTicket(int ticketNumber) {
        if (ticketNumber >= 1 && ticketNumber <= confirmedTickets.size()) {
            confirmedTickets.erase(confirmedTickets.begin() + ticketNumber - 1);
            if (!racTickets.empty()) {
                confirmedTickets.push_back(racTickets.front());
                racTickets.erase(racTickets.begin());
            }
            if (!waitingList.empty()) {
                racTickets.push_back(waitingList.front());
                waitingList.erase(waitingList.begin());
            }
            cout << "Ticket canceled successfully!" << endl;
        } else {
            cout << "Invalid ticket number!" << endl;
        }
    }

    void printBookedTickets() {
        cout << "Booked Tickets:" << endl;
        for (int i = 0; i < confirmedTickets.size(); ++i) {
            cout << "Ticket " << i + 1 << ":" << endl;
            cout << "Name: " << confirmedTickets[i].passenger.name << endl;
            cout << "Age: " << confirmedTickets[i].passenger.age << endl;
            cout << "Gender: " << confirmedTickets[i].passenger.gender << endl;
            cout << "Berth Preference: " << confirmedTickets[i].passenger.berthPreference << endl;
            cout << endl;
        }
        cout << "Total booked tickets: " << confirmedTickets.size() << endl;
    }

    void printAvailableTickets() {
        cout << "Available Tickets:" << endl;
        int availableBerths = totalBerths - confirmedTickets.size();
        int availableRacBerths = totalRacBerths - racTickets.size();
        int availableWaitingListBerths = maxWaitingListSize - waitingList.size();
        
        cout << "Confirmed Berths: " << availableBerths << endl;
        cout << "RAC Berths: " << availableRacBerths << endl;
        cout << "Waiting List Berths: " << availableWaitingListBerths << endl;
        cout << "Total available tickets: " << availableBerths + availableRacBerths + availableWaitingListBerths << endl;
    }
};

int main() {
    RailwayReservationSystem reservationSystem;
    int choice;

    do {
        cout << "\nRailway Ticket Reservation System" << endl;
        cout << "1. Book Ticket" << endl;
        cout << "2. Cancel Ticket" << endl;
        cout << "3. Print Booked Tickets" << endl;
        cout << "4. Print Available Tickets" << endl;
        cout << "5. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                Passenger passenger;
                cout << "Enter Passenger Name: ";
                cin >> passenger.name;
                cout << "Enter Passenger Age: ";
                cin >> passenger.age;
                cout << "Enter Passenger Gender (M/F): ";
                cin >> passenger.gender;
                cout << "Enter Passenger Berth Preference: ";
                cin >> passenger.berthPreference;
                reservationSystem.bookTicket(passenger);
                break;
            }
            case 2: {
                int ticketNumber;
                cout << "Enter Ticket Number to cancel: ";
                cin >> ticketNumber;
                reservationSystem.cancelTicket(ticketNumber);
                break;
            }
            case 3:
                reservationSystem.printBookedTickets();
                break;
            case 4:
                reservationSystem.printAvailableTickets();
                break;
            case 5:
                cout << "Exiting..." << endl;
                break;
            default:
                cout << "Invalid choice! Please try again." << endl;
        }
    } while (choice != 5);

    return 0;
}

