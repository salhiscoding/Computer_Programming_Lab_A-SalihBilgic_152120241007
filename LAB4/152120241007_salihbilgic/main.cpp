#include <iostream>
#include <cstdlib>
using namespace std;

const int QUEUE_SIZE = 5;

struct Package {
    string PackageID;
    string destinationCity;
    int dimensions[3]; // length, width, height
    Package* next;

};
struct Courier {
    string CourierID;
    string name;
    string vehicleType;
};

Package* topNode = NULL;
Courier courierQueue[QUEUE_SIZE];
int frontIndex = -1;
int rearIndex = -1;

void Arrival(string id, string city, int length, int width, int height) {
    Package* newPackage = new Package;
    newPackage -> PackageID = id;
    newPackage -> destinationCity = city;
    newPackage -> dimensions[0] = length;
    newPackage -> dimensions[1] = width;
    newPackage -> dimensions[2] = height;

    newPackage -> next = topNode;
    topNode = newPackage;

    cout<<"Package "<<id<<" arrived at the warehouse."<<endl;

}
void CourierRegister(string name, string vehicle) {
    //kuyruk dolu mu kontrolu yapýyom
    if ((rearIndex + 1) % QUEUE_SIZE == frontIndex){
        cout << "Courier queue is full. Cannot register new courier right now."<<name<<endl;
    return;
    }
    //kuyruk boþsa
    if (frontIndex == -1) {
        frontIndex = 0;
        rearIndex = 0;
    }else {     //degilse
        rearIndex = (rearIndex + 1) % QUEUE_SIZE;
    }
    courierQueue[rearIndex].name = name;
    courierQueue[rearIndex].vehicleType = vehicle;
    cout<<"Courier "<<name<<" registered with vehicle "<<vehicle<<"."<<endl;
}
void Dispatch() {
    if (topNode == NULL){ //gonderilecek paket yoksa verilecek mesaj
        cout << "No packages to dispatch." << endl;
        return;
    }
    if (frontIndex == -1){ //gonderici yoksa verilecek mesaj
        cout << "No couriers available for dispatch." << endl;
        return;
    }
    //en üstteki kargoyu al ve sýradaki kuryeye ata
    Package* packageToDispatch = topNode;
    topNode = topNode -> next;

    Courier courierAssigned = courierQueue[frontIndex];
    if (frontIndex == rearIndex) { //kuyrukta tek bir kurye kaldýysa
    frontIndex = -1;
    rearIndex = -1;
    }else { //deðilse sýradaki kurye sýraya girecek
        frontIndex = (frontIndex + 1) % QUEUE_SIZE;
    }
    cout<<"Dispatching package "<<courierAssigned.name<<" with vehicle "<<courierAssigned.vehicleType<<" to deliver package "<<packageToDispatch -> PackageID<<" to "<<packageToDispatch -> destinationCity<<endl;
    delete packageToDispatch; //en son paket gonderildikten sonra hafýzadan sil
}
void Display(){
    cout<<"------------Warehouse Status----------"<<endl;
    cout<<"Packages in Warehouse: "<<endl;
    Package* currentPackage = topNode;
    if (currentPackage == NULL){
        cout<<"No packages in the warehouse."<<endl;
    }else {
        while(currentPackage != NULL){
          cout<<" ->Package ID: "<<currentPackage -> PackageID
              <<" |Destination: "<<currentPackage -> destinationCity
              <<" |Dimensions: "<<currentPackage -> dimensions[0]<<"x"<<currentPackage -> dimensions[1]<<"x"<<currentPackage -> dimensions[2]<<endl;
              currentPackage = currentPackage -> next;
        }
    }
    cout<<"Couriers in Queue: "<<endl;
    if (frontIndex == -1){
        cout<<"No couriers in the queue."<<endl;
    }else {
        int i = frontIndex;
        while (true){
            cout<<" ->Courier Name: "<<courierQueue[i].name
                <<" |Vehicle Type: "<<courierQueue[i].vehicleType<<endl;
            if (i == rearIndex){
                break; //kuyruk sonuna geldiysek bitir
            }
            i = (i + 1) % QUEUE_SIZE;
        }
    }
    cout<<"------------------------------------"<<endl;
}

int main() {
    Arrival("package1", "Istanbul", 10, 20, 30);
    Arrival("package2", "Izmir", 15, 25, 35);
    Arrival("package3", "Ankara", 20, 30, 40);

    CourierRegister("Salih", "motor");
    CourierRegister("Ahmet", "araba");
    cout<<"\n Teslimat oncesi durum: "<<endl;
    Display();
    cout<<"\n Teslimat Basliyor... "<<endl;
    Dispatch();
    Dispatch();
    cout<<"\n Teslimat sonrasi durum: "<<endl;
    Display();
    return 0;
}
