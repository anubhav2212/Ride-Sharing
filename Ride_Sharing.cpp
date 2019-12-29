// I have used only strategy as of now which is "Fastest Ride".
//Code can be scaled to offer multiple strategies, return outputs for all methods and multiple actions

#include<bits/stdc++.h>
using namespace std;

class Vehicle {
public:
    string name;
};

class User {
public:
    string name;
    string gender;
    int age;
    int fuelSaved;
    int totalRidesOffered;
    int totalRidesTaken;
    User() {
        fuelSaved = 0;
        totalRidesOffered = 0;
        totalRidesTaken = 0;
    }
};

class Ride {
public:
    string origin;
    string destination;
    int availableSeats;
    string vehicleDetails;
    //time_t startTime;
    int rideDuration;
};

class Rider {
public:
    User rider;
    vector<Vehicle> vehicles;
    vector<Ride> rides;
    Rider() {};
};

class DriverService {
    vector<Rider> riders;
public:
    void add_user(string name, string gender, int age) {
        Rider newUser;
        newUser.rider.name = name;
        newUser.rider.gender = gender;
        newUser.rider.age = age;
        riders.push_back(newUser);
    }
    void add_vehicle(string name, string vehDetails) {
        for(auto itr=riders.begin();itr!=riders.end();itr++) {
            if(itr->rider.name == name) {
                Vehicle newVeh;
                newVeh.name = vehDetails;
                itr->vehicles.push_back(newVeh);
            }
        }
    }
    void offer_ride(string name, string origin, string vehDetails, int seats, string destination, int duration) {
        for(auto itr=riders.begin();itr!=riders.end();itr++) {
            if(itr->rider.name == name) {
                Ride newRide;
                newRide.origin = origin;
                newRide.destination = destination;
                newRide.availableSeats = seats;
                newRide.vehicleDetails = vehDetails;
                newRide.rideDuration = duration;
                itr->rides.push_back(newRide);
            }
        }
    }
    void select_ride(string name, string origin, string destination, string strategy) {
        Ride ansRide;
        User ansUser;
        int minDur = INT_MAX;
        //time_t minTime;
        int flag=0;
        int gotRide = 0;
        if(strategy == "Fastest Ride") {
        for(auto itr=riders.begin();itr!=riders.end();itr++) {
            for(auto itrChild=itr->rides.begin();itrChild!=itr->rides.end();itrChild++) {
                if(itrChild->rideDuration < minDur && itrChild->availableSeats > 0) {
                    flag = 1;
                    minDur = itrChild->rideDuration;
                }
            }
            if(flag==1) {
                ansUser = itr->rider;
                flag = 0;
                gotRide = 1;
            }
        }
        }
        /*else {
            for(auto itr=riders.begin();itr!=riders.end();itr++) {
            for(auto itrChild=itr->rides.begin();itrChild!=itr->rides.end();itrChild++) {
                if(itrChild->startTime < minTime && itrChild->availableSeats > 0) {
                    flag = 1;
                    minTime = itrChild->startTime;
                }
            }
            if(flag==1) {
                ansUser = itr->rider;
                flag = 0;
                gotRide = 1;
            }
        }
        }*/
        if(gotRide) {
        for(auto itr=riders.begin();itr!=riders.end();itr++) {
            if(itr->rider.name == ansUser.name) {
                itr->rider.totalRidesOffered++;
                for(auto itrChild=itr->rides.begin();itrChild!=itr->rides.end();itrChild++) {
                    if(strategy == "Fastest Ride" && itrChild->rideDuration == minDur) {
                        itrChild->availableSeats--;
                        break;
                    }
                    /*else if(strategy == "Earliest Ride" && itrChild->startTime == minTime) {
                        itrChild->availableSeats--;
                        break;
                    }*/
                }
            }
            if(itr->rider.name == name) {
                itr->rider.totalRidesTaken++;
                itr->rider.fuelSaved += minDur;
            }
        }
        }
    }
    int fuel_saved(string name) {
        for(auto itr=riders.begin();itr!=riders.end();itr++) {
            if(itr->rider.name == name) {
                return itr->rider.fuelSaved;
            }
        }
    }
    int total_rides(string name) {
        string ans;
        for(auto itr=riders.begin();itr!=riders.end();itr++) {
            if(itr->rider.name == name) {
                return itr->rider.totalRidesTaken + itr->rider.totalRidesOffered;
            }
        }
    }
};

int main() {
    DriverService *driver = new DriverService();
    int action,t,i;
    string e,r,y,u;
    time_t p;
    while(1) {
        cout<<"Action:\n1.AddUser\n2.AddVehicle\n3.OfferRide\n4.SelectRide\n5.FuelSaved\n6.TotalRides\n0.Exit\n";
        cin>>action;
        switch(action) {
            case 1:
                cout<<"Name:";
                cin>>e;
                cout<<"Gender:";
                cin>>r;
                cout<<"Age:";
                cin>>t;
                driver->add_user(e,r,t);
                break;
            case 2:
                cout<<"Name:";
                cin>>e;
                cout<<"Vehicle Details:";
                cin>>r;
                driver->add_vehicle(e,r);
                break;
            case 3:
                cout<<"Name:";
                cin>>e;
                cout<<"Origin:";
                cin>>r;
                cout<<"Available Seats:";
                cin>>t;
                cout<<"Vehicle Details:";
                cin>>y;
                cout<<"Destination:";
                cin>>u;
                cout<<"Ride Duration:";
                cin>>i;
                driver->offer_ride(e,r,y,t,u,i);
                break;
            case 4:
                cout<<"Name:";
                cin>>e;
                cout<<"Origin:";
                cin>>r;
                cout<<"Destination:";
                cin>>u;
                cout<<"Strategy:";
                cin>>y;
                driver->select_ride(e,r,u,y);
                break;
            case 5:
                cout<<"Name:";
                cin>>e;
                cout<<"Fuel saved: "<<driver->fuel_saved(e)<<endl;
                break;
            case 6:
                cout<<"Name:";
                cin>>e;
                cout<<"Total rides(Offered+Taken): "<<driver->total_rides(e)<<endl;
                break;
            default:
                exit(0);
        }
    }
}


