#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

// Global Constants
const int MAX_STAT = 20;
const int MAX_LEVEL = 10;

int main() {
    // Character Variables
    string charName = "";
    string charClass = "None";
    int level = 1;
    int str = 0, intel = 0, dex = 0, con = 0;
    int choice, classChoice;
    bool characterCreated = false;

    do {
        // 1. Main Menu System
        cout << "\n=== GAMESTAT CHARACTER MANAGER ===" << endl;
        cout << "1. Create New Character" << endl;
        cout << "2. View Character Stats" << endl;
        cout << "3. Calculate Combat Ratings" << endl;
        cout << "4. Level Up Character" << endl;
        cout << "5. Exit" << endl;
        cout << "Enter choice: ";
        
        // Input Validation for Menu
        while (!(cin >> choice) || choice < 1 || choice > 5) {
            cout << "Invalid choice. Please enter 1-5: ";
            cin.clear();
            cin.ignore(1000, '\n');
        }

        switch (choice) {
            case 1: { // Create Character
                cout << "\n=== CREATE NEW CHARACTER ===" << endl;
                cout << "Enter character name: ";
                cin.ignore(); // Clear buffer
                getline(cin, charName);

                cout << "Select class:\n1. Warrior\n2. Mage\n3. Rogue\n4. Cleric" << endl;
                cout << "Enter choice (1-4): ";
                while (!(cin >> classChoice) || classChoice < 1 || classChoice > 4) {
                    cout << "Invalid choice. Enter 1-4: ";
                    cin.clear();
                    cin.ignore(1000, '\n');
                }

                // Stat Entry & Validation Loops
                auto getStat = [](string name) {
                    int val;
                    cout << name << " (1-20): ";
                    while (!(cin >> val) || val < 1 || val > MAX_STAT) {
                        cout << "Invalid range! Enter " << name << " (1-20): ";
                        cin.clear();
                        cin.ignore(1000, '\n');
                    }
                    return val;
                };

                str = getStat("Strength");
                intel = getStat("Intelligence");
                dex = getStat("Dexterity");
                con = getStat("Constitution");

                // Class Bonuses
                switch (classChoice) {
                    case 1: charClass = "Warrior"; str += 2; cout << "Warrior bonus: Strength +2\n"; break;
                    case 2: charClass = "Mage"; intel += 2; cout << "Mage bonus: Intelligence +2\n"; break;
                    case 3: charClass = "Rogue"; dex += 2; cout << "Rogue bonus: Dexterity +2\n"; break;
                    case 4: charClass = "Cleric"; intel += 1; str += 1; cout << "Cleric bonus: Str +1, Int +1\n"; break;
                }

                characterCreated = true;
                level = 1;
                cout << "Character " << charName << " created successfully!" << endl;
                break;
            }

            case 2: // View Stats
                if (!characterCreated) {
                    cout << "Error: No character exists yet!" << endl;
                } else {
                    cout << "\n=== CHARACTER PROFILE ===" << endl;
                    cout << "Name: " << charName << "\nClass: " << charClass << "\nLevel: " << level << endl;
                    cout << "\nBase Stats:" << endl;
                    cout << "  Strength:     " << str << endl;
                    cout << "  Intelligence: " << intel << endl;
                    cout << "  Dexterity:    " << dex << endl;
                    cout << "  Constitution: " << con << endl;
                }
                break;

            case 3: // Calculate Combat Ratings
                if (!characterCreated) {
                    cout << "Error: No character exists yet!" << endl;
                } else {
                    // Formulas
                    double hp = (con * 10) + (level * 5) + (charClass == "Warrior" ? 20 : 0);
                    double mp = (intel * 10) + (level * 3) + (charClass == "Mage" ? 30 : 0);
                    double defense = (con + dex) / 2.0;
                    double attackPower = 0;

                    if (charClass == "Warrior") attackPower = str * 1.5;
                    else if (charClass == "Mage") attackPower = intel * 1.3;
                    else if (charClass == "Rogue") attackPower = dex * 1.4;
                    else if (charClass == "Cleric") attackPower = (str + intel) * 0.8;

                    cout << fixed << setprecision(1);
                    cout << "\n=== COMBAT RATINGS ===" << endl;
                    cout << "Health Points: " << hp << endl;
                    cout << "Mana Points:   " << mp << endl;
                    cout << "Attack Power:  " << attackPower << endl;
                    cout << "Defense:       " << defense << endl;
                }
                break;

            case 4: // Level Up
                if (!characterCreated) {
                    cout << "Error: No character exists yet!" << endl;
                } else if (level >= MAX_LEVEL) {
                    cout << "Max level " << MAX_LEVEL << " reached!" << endl;
                } else {
                    cout << "\n=== LEVEL UP ===" << endl;
                    cout << "Level " << level << " -> " << level + 1 << endl;
                    level++; str++; intel++; dex++; con++;
                    cout << "All stats increased by +1!" << endl;
                }
                break;
        }
    } while (choice != 5);

    cout << "Exiting GameStat. Goodbye!" << endl;
    return 0;
}
