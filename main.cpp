#include <iostream>
#include <string>
using namespace std;
struct Node {
    int bus_number;
    string driver_initials;
    int route_number;
    bool location;
    Node* next;
    Node* prev;
};
Node* first(int bus_number, char driver_initials[50], int route_number, bool location);
void bus_arrived(Node** tail, int bus_number, char driver_initials[50], int route_number, bool location);
void print_station(Node* const head);
void print_route(Node* const head);
void bus_left(Node** head, Node** tail, int key);
Node* find(Node* const head, int key);

Node* first(int bus_number, char driver_initials[50], int route_number, bool location){
    Node* node = new Node();
    node->bus_number = bus_number;
    node->driver_initials = driver_initials;
    node->route_number = route_number;
    node->location = location;
    return node;
}

Node* find(Node* const head, int key){
    Node* node = head;
    while(node != nullptr){
        if(node->bus_number==key) break;
        node = node->next;
    }
    return node;
}

void bus_left(Node** head, Node** tail, int key){
    if(Node* node = find(*head,key)){
        if(node == *head){
            *head = (*head)->next;
            (*head)->prev = nullptr;
        }else if(node == *tail){
            *tail = (*tail)->prev;
            (*tail)->next = nullptr;
        }else{
            (node->prev)->next = node->next;
            (node->next)->prev = node->prev;
        }
    }
}

void bus_arrived(Node** tail, int bus_number, char driver_initials[50], int route_number, bool location){
    Node* node = new Node();
    node->bus_number = bus_number;
    node->driver_initials = driver_initials;
    node->route_number = route_number;
    node->location = location;
    node->next = nullptr;
    node->prev = *tail;
    (*tail)->next = node;
    *tail = node;
}

void print_station(Node* const head){
    Node* node = head;
    cout << "----------------" << endl << "\t" << "STATION" << endl << "----------------"<<endl;
    while(node != nullptr){
        if(node->location==1) {
            cout << "Bus number:" << node->bus_number << endl << "Driver's initials:" << node->driver_initials << endl
                 << "Route number:" << node->route_number << endl;
        }
        node = node->next;
    }
}

void print_route(Node* const head){
    Node* node = head;
    cout << "----------------" << endl << "\t" << " ROUTE" << endl << "----------------"<<endl;
    while(node != nullptr){
        if(node->location==0) {
            cout << "Bus number:" << node->bus_number << endl << "Driver's initials:" << node->driver_initials << endl
                 << "Route number:" << node->route_number << endl;
        }
        node = node->next;
    }
}

static void enter_data(int amount, int &bus_number, char *driver_initials, bool &location, int &route_number, Node *&tail);
int main(){
    bool n = 1;
    int key, amount, choose = 0;
    int bus_number, route_number;
    char driver_initials[50];
    bool location;
    cout << "Enter the amount of busses:";
    cin >> amount;
    cout << "Enter the bus number:";
    cin >> bus_number;
    cout << "Enter the driver's initials:";
    cin >> driver_initials;
    cout << "Enter the route number:";
    cin >> route_number;
    cout << "Enter 0 if the bus is on the route(otherwise 1):";
    cin >> location;
    Node* head = first(bus_number, driver_initials, route_number, location);
    Node* tail = head;
    enter_data(amount, bus_number, driver_initials, location, route_number, tail);

    while(n){
        cout << "Choose the action:"<<endl<<" 1. The bus arrived\n 2. The bus left\n 3. Station list\n 4. Route list\n";
        cin >> choose;
        if(choose == 1){
            cout << "Enter the amount of busses:";
            cin >> amount;
            cout << "Enter the bus number:";
            cin >> bus_number;
            cout << "Enter the driver's initials:";
            cin >> driver_initials;
            cout << "Enter the route number:";
            cin >> route_number;
            cout << "Enter 0 if the bus is on the route(otherwise 1):";
            cin >> location;
            bus_arrived(&tail, bus_number, driver_initials, route_number, location);
        }else if(choose == 2){
            cout << "Enter the number of the bus that left the station:";
            cin >> key;
            bus_left(&head, &tail, key);
        }else if(choose == 3) print_station(head);
        else if(choose == 4) print_route(head);
        cout << "Enter 0 to stop or 1 to continue:";
        cin >> n;
    }
}
static void enter_data(int amount, int &bus_number, char *driver_initials, bool &location, int &route_number, Node *&tail) {
    for(int i = 1; i < amount; i++) {
        cout << "Enter the bus number:";
        cin >> bus_number;
        cout << "Enter the driver's initials:";
        cin >> driver_initials;
        cout << "Enter the route number:";
        cin >> route_number;
        cout << "Enter 0 if the bus is on the route(otherwise 1):";
        cin >> location;
        bus_arrived(&tail, bus_number, driver_initials, route_number, location);
    }
}