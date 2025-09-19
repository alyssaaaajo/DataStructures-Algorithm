#include <stdio.h>
#include <stdlib.h>

// -------------------- Structs --------------------
typedef struct {
    int hours;
    int minutes;
} Time;

typedef struct {
    int id;
    char origin[50];
    char destination[50];
    Time departure_time;
    Time arrival_time;
} Flight;

typedef struct {
    Flight *flights; // dynamic array
    int count;
    int max;
} Flights;

// -------------------- Function Declarations --------------------
Time createTime(int h, int m);
Flight createFlight();
void addFlight(Flights *fList, Flight f);
Flight removeFlight(Flights *fList, int flightid);
void showFlights(Flights flight_list);
void displayFlightInfo(Flight f);
void displayTime(Time t);

// -------------------- Functions --------------------
Time createTime(int h, int m) {
    Time t;
    t.hours = h;
    t.minutes = m;
    return t;
}

void displayTime(Time t) {
    int h = t.hours % 12;
    if (h == 0) h = 12;
    printf("%02d:%02d %s", h, t.minutes, (t.hours >= 12) ? "PM" : "AM");
}

void displayFlightInfo(Flight f) {
    printf("\nFlight ID: %d\n", f.id);
    printf("Origin: %s\n", f.origin);
    printf("Destination: %s\n", f.destination);
    printf("Departure: ");
    displayTime(f.departure_time);
    printf("\nArrival: ");
    displayTime(f.arrival_time);
    printf("\n");
}

Flight createFlight() {
    Flight f;
    printf("Enter id: ");
    scanf("%d", &f.id);
    printf("Enter origin: ");
    scanf(" %[^\n]", f.origin);
    printf("Enter destination: ");
    scanf(" %[^\n]", f.destination);

    int h, m;
    printf("Enter Departure Time (HH MM in 24hr): ");
    scanf("%d %d", &h, &m);
    f.departure_time = createTime(h, m);

    printf("Enter Arrival Time (HH MM in 24hr): ");
    scanf("%d %d", &h, &m);
    f.arrival_time = createTime(h, m);

    return f;
}

void addFlight(Flights *fList, Flight f) {
    if (fList->count == fList->max) {
        fList->max *= 2;
        fList->flights = realloc(fList->flights, fList->max * sizeof(Flight));
    }
    fList->flights[fList->count] = f;
    fList->count++;
}

Flight removeFlight(Flights *fList, int flightid) {
    Flight removed;
    removed.id = -1; // default "not found"

    if (fList->count == 0) {
        printf("List is empty.\n");
        return removed;
    }

    int i, j;
    for (i = 0; i < fList->count; i++) {
        if (fList->flights[i].id == flightid) {
            removed = fList->flights[i];
            for (j = i; j < fList->count - 1; j++) {
                fList->flights[j] = fList->flights[j + 1];
            }
            fList->count--;
            return removed;
        }
    }
    return removed; // id == -1 if not found
}

void showFlights(Flights flight_list) {
    if (flight_list.count == 0) {
        printf("No flights available.\n");
        return;
    }
    for (int i = 0; i < flight_list.count; i++) {
        displayFlightInfo(flight_list.flights[i]);
        printf("-------------------------\n");
    }
}

// -------------------- Main --------------------
int main() {
    Flights flight_list;
    flight_list.count = 0;
    flight_list.max = 2;
    flight_list.flights = malloc(flight_list.max * sizeof(Flight));

    int choice, id;
    while (1) {
        printf("\n--- Flight Management System ---\n");
        printf("1. Add Flight\n");
        printf("2. Show Flights\n");
        printf("3. Remove Flight\n");
        printf("4. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        if (choice == 1) {
            Flight f = createFlight();
            addFlight(&flight_list, f);
        } 
        else if (choice == 2) {
            showFlights(flight_list);
        } 
        else if (choice == 3) {
            printf("Enter Flight ID to remove: ");
            scanf("%d", &id);
            Flight removed = removeFlight(&flight_list, id);
            if (removed.id == -1)
                printf("Flight not found.\n");
            else
                printf("Removed flight %d (%s -> %s)\n", removed.id, removed.origin, removed.destination);
        } 
        else if (choice == 4) {
            break;
        } 
        else {
            printf("Invalid choice.\n");
        }
    }

    free(flight_list.flights);
    return 0;
}
