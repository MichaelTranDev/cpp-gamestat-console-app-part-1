#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

// Global Constants
const int MAX_STAT = 20;
const int MAX_LEVEL = 10;
const int STAT_COUNT = 4;

int main() {
    // Character info
    string charName = "";
    string charClass = "None";
    int level = 1;
    bool characterCreated = false;

    // Base stats (never permanently changed)
    int baseStats[STAT_COUNT] = {0, 0, 0, 0};
    string statNames[STAT_COUNT] = {"Strength", "Intelligence", "Dexterity", "Constitution"};

    int choice, classChoice;

    do {
        cout << "\n=== GAMESTAT CHARACTER MANAGER ===" << endl;
        cout << "1. Create New Character" << endl;
        cout << "2. View Character Stats" << endl;
        cout << "3. Calculate Combat Ratings" << endl;
        cout << "4. Level Up Character" << endl;
        cout << "5. Exit" << endl;
        cout << "Enter choice: ";

        while (!(cin >> choice) || choice < 1 || choice > 5) {
            cout << "Invalid choice. Please enter 1-5: ";
            cin.clear();
            cin.ignore(1000, '\n');
        }

        switch (choice) {

            case 1: {   // CREATE CHARACTER
                cout << "\n=== CREATE NEW CHARACTER ===" << endl;

                cin.ignore(1000, '\n');
                cout << "Enter character name: ";
                getline(cin, charName);

                cout << "Select class:\n1. Warrior\n2. Mage\n3. Rogue\n4. Cleric" << endl;
                cout << "Enter choice (1-4): ";

                while (!(cin >> classChoice) || classChoice < 1 || classChoice > 4) {
                    cout << "Invalid choice. Enter 1-4: ";
                    cin.clear();
                    cin.ignore(1000, '\n');
                }

                // Enter base stats using loop
                for (int i = 0; i < STAT_COUNT; i++) {
                    cout << statNames[i] << " (1-20): ";
                    while (!(cin >> baseStats[i]) || baseStats[i] < 1 || baseStats[i] > MAX_STAT) {
                        cout << "Invalid range! Enter " << statNames[i] << " (1-20): ";
                        cin.clear();
                        cin.ignore(1000, '\n');
                    }
                }

                switch (classChoice) {
                    case 1: charClass = "Warrior"; break;
                    case 2: charClass = "Mage"; break;
                    case 3: charClass = "Rogue"; break;
                    case 4: charClass = "Cleric"; break;
                }

                level = 1;
                characterCreated = true;

                cout << "Character " << charName << " created successfully!" << endl;
                break;
            }

            case 2: {   // VIEW STATS
                if (!characterCreated) {
                    cout << "Error: No character exists yet!" << endl;
                    break;
                }

                cout << "\n=== CHARACTER PROFILE ===" << endl;
                cout << "Name: " << charName << endl;
                cout << "Class: " << charClass << endl;
                cout << "Level: " << level << endl;

                cout << "\nStats (with bonuses):" << endl;

                for (int i = 0; i < STAT_COUNT; i++) {
                    int total = baseStats[i];

                    // class bonuses
                    if (charClass == "Warrior" && i == 0) total += 2;
                    if (charClass == "Mage" && i == 1) total += 2;
                    if (charClass == "Rogue" && i == 2) total += 2;
                    if (charClass == "Cleric" && (i == 0 || i == 1)) total += 1;

                    // level bonus
                    total += (level - 1);

                    if (total > MAX_STAT) total = MAX_STAT;

                    cout << "  " << setw(13) << left << statNames[i] << ": " << total << endl;
                }

                break;
            }

            case 3: {   // COMBAT
                if (!characterCreated) {
                    cout << "Error: No character exists yet!" << endl;
                    break;
                }

                // Build modified stats first
                int finalStats[STAT_COUNT];

                for (int i = 0; i < STAT_COUNT; i++) {
                    finalStats[i] = baseStats[i];

                    if (charClass == "Warrior" && i == 0) finalStats[i] += 2;
                    if (charClass == "Mage" && i == 1) finalStats[i] += 2;
                    if (charClass == "Rogue" && i == 2) finalStats[i] += 2;
                    if (charClass == "Cleric" && (i == 0 || i == 1)) finalStats[i] += 1;

                    finalStats[i] += (level - 1);

                    if (finalStats[i] > MAX_STAT) finalStats[i] = MAX_STAT;
                }

                int str = finalStats[0];
                int intel = finalStats[1];
                int dex = finalStats[2];
                int con = finalStats[3];

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

                break;
            }

            case 4: {   // LEVEL UP
                if (!characterCreated) {
                    cout << "Error: No character exists yet!" << endl;
                }
                else if (level >= MAX_LEVEL) {
                    cout << "Max level " << MAX_LEVEL << " reached!" << endl;
                }
                else {
                    cout << "\n=== LEVEL UP ===" << endl;
                    cout << "Level " << level << " -> " << level + 1 << endl;
                    level++;
                    cout << "Stats will scale with level automatically." << endl;
                }
                break;
            }
        }

    } while (choice != 5);

    cout << "Exiting GameStat. Goodbye!" << endl;
    return 0;
}
