#include <iostream>
#include <string>



using namespace std;



void intro();
void crewQuarters();
void medBay();
void engineRoom();
void cargoBay();
void hallway();
void ventCrawl();
void inventoryCheck();
void endGame(bool success, string causeOfDeath = "");

bool hasKeycard = false;
bool hasSleepingGas = false;
bool ateCaptain = false;
bool alive = true;

int main() {
    intro();


    string choice;
    while (alive) {
        cout << "\nWhere do you want to go?\n";
        cout << "1. Crew Quarters\n";
        cout << "2. Med Bay\n";
        cout << "3. Engine Room\n";
        cout << "4. Cargo Bay (danger!)\n";
        cout << "5. Hallway Patrol (danger!)\n";
        cout << "6. Crawl Through Vents (risky!)\n";
        cout << "7. Check Inventory\n";
        cout << "8. Quit\n";
        cout << "Enter your choice: ";
        getline(cin, choice);



        if (choice == "1") crewQuarters();
        else if (choice == "2") medBay();
        else if (choice == "3") engineRoom();
        else if (choice == "4") cargoBay();
        else if (choice == "5") hallway();
        else if (choice == "6") ventCrawl();
        else if (choice == "7") inventoryCheck();
        else if (choice == "8") {
            endGame(false);
            break;
        }
        else cout << "Invalid choice. Try again.\n";


        if (ateCaptain && alive) {
            endGame(true);
            break;
        }

    }

    return 0;
}




void intro() {
    cout << "=== Alien Feast: Space Snack Edition ===\n";
    cout << "You are a tiny alien stowaway on a human spaceship.\n";
    cout << "Eat the crew one by one — but watch out! Danger lurks around every corner.\n";
}



void crewQuarters() {
    static bool crewEaten = false;
    if (!crewEaten) {
        if (hasSleepingGas) {
            cout << "You release sleeping gas into the air vents...\n";
            cout << "The crew falls asleep. You feast in silence.\n";
            crewEaten = true;
        } else {
            cout << "The crew is awake. You'd be vaporized in seconds!\n";
        }
    } else {
        cout << "Only empty bunks remain. You’ve already fed here.\n";
    }
}

void medBay() {
    static bool visited = false;
    if (!visited) {
        cout << "You sneak into the med bay. A canister of sleeping gas lies unattended.\n";
        hasSleepingGas = true;
        visited = true;
    } else {
        cout << "The med bay is silent. Nothing new here.\n";
    }
}

void engineRoom() {
    static bool guardEaten = false;
    if (!guardEaten) {
        if (hasKeycard) {
            cout << "You unlock a side hatch and ambush the engineer.\n";
            cout << "A short scuffle and... one less human. You consume the captain too.\n";
            guardEaten = true;
            ateCaptain = true;
        } else {
            cout << "The door is locked. You need a keycard.\n";
        }
    } else {
        cout << "The engine room smells like cooked meat. You’ve already fed here.\n";
    }
    
}

void cargoBay() {
    cout << "You enter the dimly-lit Cargo Bay. A human guard is patrolling.\n";
    cout << "Do you:\n";
    cout << "1. Hide behind crates\n";
    cout << "2. Leap out and attack\n";
    string decision;
    getline(cin, decision);

    if (decision == "1") {
        cout << "You hide and wait... the guard drops a keycard while checking supplies.\n";
        cout << "You slither over and grab it. Keycard acquired!\n";
        hasKeycard = true;
    } else if (decision == "2") {
        cout << "You leap out, but the guard is armed!\n";
        cout << "ZAP! You're vaporized by a stun rifle.\n";
        alive = false;
        endGame(false, "Killed by guard in Cargo Bay");
    } else {
        cout << "Hesitation is death. The guard spots you.\n";
        alive = false;
        endGame(false, "Caught in the Cargo Bay");
    }

}





void hallway() {
    cout << "A security droid patrols the hallway. It detects heat and movement.\n";
    cout << "Do you:\n";
    cout << "1. Cling to the ceiling and stay perfectly still\n";
    cout << "2. Throw a tool as a distraction\n";
    string choice;
    getline(cin, choice);

    if (choice == "1") {
        cout << "The droid scans the hallway but misses you clinging silently above.\n";
        cout << "It rolls past, and you slip through undetected.\n";
    } else if (choice == "2") {
        cout << "You toss a tool across the hall. The droid turns and fires!\n";
        cout << "You’re caught in the blast radius. Sizzling alien sushi.\n";
        alive = false;
        endGame(false, "Fried by security droid");
    } else {
        cout << "Indecision is deadly. The droid detects you.\n";
        alive = false;
        endGame(false, "Caught by security patrol");
    }
}

void ventCrawl() {

    cout << "You squeeze into a narrow ventilation shaft. It splits into two tunnels.\n";
    cout << "Left tunnel smells like food. Right tunnel hums with power.\n";
    cout << "Do you go:\n";
    cout << "1. Left\n";
    cout << "2. Right\n";

    string input;
    getline(cin, input);


    if (input == "1") {
        cout << "You crawl toward the scent. It leads to the kitchen vents. Safe.\n";
    } else if (input == "2") {
        cout << "You crawl into the power conduit. A surge fries you instantly.\n";
        alive = false;
        endGame(false, "Fried in power conduit");
    } else {

        cout << "You hesitate and get stuck. You suffocate in the vents.\n";
        alive = false;
        endGame(false, "Suffocated in the vents");
    }
}

void inventoryCheck() {
    cout << "\n=== Inventory ===\n";
    cout << "Sleeping Gas: " << (hasSleepingGas ? "Yes" : "No") << endl;

    cout << "Keycard: " << (hasKeycard ? "Yes" : "No") << endl;
    cout << "Humans Eaten: " << (ateCaptain ? "All" : (hasSleepingGas ? "1" : "0")) << endl;
    cout << "=================\n";
}









void endGame(bool success, string causeOfDeath) {
    if (success) {
        cout << "\nYou've eaten the captain and now control the ship!\n";
        cout << "The stars are your buffet. Time to go home... fat and happy.\n";
    } else if (!alive && !causeOfDeath.empty()) {
        cout << "\n=== YOU DIED ===\nCause of death: " << causeOfDeath << endl;
        cout << "The humans survive... for now.\n";
    } else {
        cout << "\nYou return to your vent. Hunger gnaws at your gut.\n";
        cout << "Mission incomplete.\n";
    }
    cout << "=== GAME OVER ===\n";
}
