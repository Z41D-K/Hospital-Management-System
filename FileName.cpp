#define _CRT_SECURE_NO_WARNINGS  
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <conio.h>
#include <ctime>
#include <iomanip>
#include <string>
#include <limits>
#include <thread>
#include <chrono>
#include <SFML/Graphics.hpp> 
using namespace std;
// Function Prototypes
void login();
void showMenu();
void addNewPatient();
void addDiagnosisInfo();
void dischargePatient();
void viewPatientHistory();
void aboutHospital();
void exitProgram();

class Person
{
public:
    float contact;
    string name, address,  age, gender;
    void inputBasicInfo()
    {
        cout << "Enter patient name: ";
        getline(cin, name);
        cout << "Enter address: ";
        getline(cin, address);
        cout << "Enter contact number: ";
        cin >> contact;
        cout << "Enter age: ";
        getline(cin, age);
        cout << "Enter gender(M/F): ";
        getline(cin, gender);
    }
};

class Patient : public Person
{
public:
    string bloodGroup, disease, id;
    void inputPatientDetails()
    {
        inputBasicInfo();
        cout << "Enter Blood Group: ";
        getline(cin, bloodGroup);
        cout << "Any Major disease suffered earlier: ";
        getline(cin, disease);
        cout << "Patient ID (CNIC): ";
        getline(cin, id);
    }
    void saveToFile(string filename)
    {
        ofstream file(filename);
        file << "Patient Information\n";
        file << "-------------------\n\n";
        file << "Name: " << name << "\n";
        file << "Address: " << address << "\n";
        file << "Contact Number: " << contact << "\n";
        file << "Age: " << age << "\n";
        file << "Gender: " << gender << "\n";
        file << "Blood Group: " << bloodGroup << "\n";
        file << "Past Disease: " << disease << "\n";
        file << "Patient ID: " << id << "\n\n";
        file << "-------------------\n";
        file.close();
    }
};
void showWelcomeScreen(bool& proceed) {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Welcome");

    sf::Font font;
    if (!font.loadFromFile("arial.ttf")) return;

    sf::Text title("Welcome to Zaid's Hospital System", font, 32);
    title.setFillColor(sf::Color::Red);
    title.setPosition(100, 100);

    sf::RectangleShape button(sf::Vector2f(200, 50));
    button.setPosition(300, 350);
    button.setFillColor(sf::Color(0, 180, 0));

    sf::Text buttonText("Enter", font, 24);
    buttonText.setFillColor(sf::Color::White);
    buttonText.setPosition(360, 360);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::MouseButtonPressed) {
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                if (button.getGlobalBounds().contains((float)mousePos.x, (float)mousePos.y)) {
                    proceed = true;
                    window.close();
                }
            }

            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Enter) {
                    proceed = true;
                    window.close();
                }
            }
        }

        window.clear(sf::Color(245, 245, 245));
        window.draw(title);
        window.draw(button);
        window.draw(buttonText);
        window.display();
    }
}

void showGoodbyeScreen() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Goodbye");

    sf::Font font;
    if (!font.loadFromFile("arial.ttf")) return;

    sf::Text title("Thanks for Visiting Zaid's Hospital", font, 30);
    title.setFillColor(sf::Color::Green);
    title.setPosition(120, 100);

    sf::RectangleShape button(sf::Vector2f(200, 50));
    button.setPosition(300, 350);
    button.setFillColor(sf::Color(180, 0, 0));

    sf::Text buttonText("Exit", font, 24);
    buttonText.setFillColor(sf::Color::White);
    buttonText.setPosition(370, 360);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::MouseButtonPressed) {
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                if (button.getGlobalBounds().contains((float)mousePos.x, (float)mousePos.y)) {
                    window.close();
                }
            }

            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Escape)
                    window.close();
            }
        }

        window.clear(sf::Color::Black);
        window.draw(title);
        window.draw(button);
        window.draw(buttonText);
        window.display();
    }
}



// Main Function 
int main() {
    try {
        bool proceed = false;
        showWelcomeScreen(proceed);

            

            if (proceed) {
                login();
                showMenu();
                showGoodbyeScreen(); // Once done


        }
    }
    catch (const exception& e) {
        cerr << "\n\n\t\t\t\tAn unexpected error occurred: " << e.what() << "\n";
    }
    return 0;
}


// login with exception handling incase of any in appropriate thing enters
void login() {
    string password;
    int attempts = 0;
    int waitTime = 5;

    while (true) {
        system("cls"); // Clear screen on each attempt
        password = "";
        char ch;

        cout << "\n\n\t\tLOGIN TO SYSTEM\n";
        cout << "\t\tEnter Password: ";

        // Read password with masking
        while (true) {
            ch = _getch();
            if (ch == '\r') break;         // Enter pressed
            else if (ch == 8 && !password.empty()) {
                password.pop_back();
                cout << "\b \b";           // Backspace
            }
            else if (ch != 8) {
                password += ch;
                cout << "*";              // Mask character
            }
        }

        if (password == "pass") {
            cout << "\n\n\t\tAccess Granted!\n";
            break;
        }
        else {
            attempts++;
            cout << "\n\n\t\tAccess Denied. Wrong password! Try again\n";

            if (attempts >= 3) {
                cout << "\n\tToo many failed attempts. Please wait " << waitTime << " seconds...\n";

                // Lockout loop (disable input)
                for (int i = waitTime; i > 0; i--) {
                    cout << "\r\tYou can try again in " << i << " seconds... ";
                    cout.flush();
                    this_thread::sleep_for(chrono::seconds(1));
                }

                attempts = 0;
                waitTime *= 2; // Increase wait time next time
                cout << "\r\tYou can try again now.                 \n";
                this_thread::sleep_for(chrono::seconds(1));
            }
            else {
                this_thread::sleep_for(chrono::seconds(1)); // Short pause before retry
            }
        }
    }
    system("pause");
    system("cls");
}


// showMenu with input exception handling
void showMenu() {
    int choice;
    while (true) {
        cout << "\n\n\t\t\t\t\tHOSPITAL MANAGEMENT SYSTEM\n";
        cout << "\t\t\t\t\t1. Add New Patient Record\n";
        cout << "\t\t\t\t\t2. Add Diagnosis Information\n";
        cout << "\t\t\t\t\t3. Discharge  Information\n";
        cout << "\t\t\t\t\t4. Full History of the Patient\n";
        cout << "\t\t\t\t\t5. Information About the Hospital\n";
        cout << "\t\t\t\t\t6. Exit the Program\n";
        cout << "\n\t\t\t\t\tEnter your choice: ";

        try {
            if (!(cin >> choice)) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                throw invalid_argument("Invalid input. Please enter a number.");
            }
            cin.ignore(); // clear newline

            switch (choice) {
            case 1:
                addNewPatient();
                break;
            case 2:
                addDiagnosisInfo();
                break;
            case 3:
                dischargePatient();
                break;
            case 4:
                viewPatientHistory();
                break;
            case 5:
                aboutHospital();
                break;
            case 6:
                exitProgram();
                return;
            default:
                cout << "\n\t\t\t\t\tInvalid choice. Please try again.\n";
            }
        }
        catch (const exception& e) {
            cout << "\n\t\t\t\t\tError: " << e.what() << "\n";
        }
    }
}

// addNewPatient 
bool fileExists(const string& filename) {
    ifstream file(filename);
    return file.good();
}

void addNewPatient()
{
    try
    {
        string filename;
        cout << "\nEnter patient file name to store in record: ";
        getline(cin, filename);
        if (fileExists(filename))
        {
            cout << "File already exists!\n";
            return;
        }
        Patient p;
        p.inputPatientDetails();
        p.saveToFile(filename);
        cout << "Patient Information Saved Successfully!\n";
    }
    catch (const exception& e)
    {
        cout << "Exception: " << e.what() << "\n";
    }
}


// dischargePatient with file 
// dischargePatient with file 
void dischargePatient() {
    fstream file;
    string filename;

    try {
        cout << "\n\n\t\t\t\tEnter patient file name to discharge: ";
        getline(cin, filename);

        file.open(filename, ios::in);
        if (!file) throw runtime_error("Record not found");

        cout << "\n\t\t\t\tCurrent Patient Record:\n\n";
        string line;
        bool admitted = false;
        bool wardAssigned = false;

        while (getline(file, line)) {
            cout << line << endl;
            if (line.find("Admission: y") != string::npos || line.find("Admission: Y") != string::npos) {
                admitted = true;
            }
            if (line.find("Ward:") != string::npos && line.find("N/A") == string::npos) {
                wardAssigned = true;
            }
        }
        file.close();

        if (!(admitted && wardAssigned)) {
            cout << "\n\t\t\t\tPatient is not admitted \n";
            system("pause");
            system("cls");
            return;
        }

        file.open(filename, ios::app);
        if (!file) throw runtime_error("Error opening file!");

        time_t now = time(0);
        file << "\n--- Patient Discharge Summary ---\n";
        file << "Discharge Date: " << ctime(&now);

        string finalDiagnosis, prescription;
        cout << "\n\t\t\t\tEnter Final Diagnosis: "; getline(cin, finalDiagnosis);
        cout << "\t\t\t\tEnter Prescription on Discharge: "; getline(cin, prescription);

        file << "Final Diagnosis: " << finalDiagnosis << "\n";
        file << "Prescription: " << prescription << "\n";

        float roomCharges, medicineCharges, doctorFee, total;

        cout << "\n\t\t\t\tEnter Room Charges: ";
        if (!(cin >> roomCharges)) throw invalid_argument("Invalid input for room charges.");
        cin.ignore();

        cout << "\t\t\t\tEnter Medicine Charges: ";
        if (!(cin >> medicineCharges)) throw invalid_argument("Invalid input for medicine charges.");
        cin.ignore();

        cout << "\t\t\t\tEnter Doctor Fee: ";
        if (!(cin >> doctorFee)) throw invalid_argument("Invalid input for doctor fee.");
        cin.ignore();
        total = roomCharges + medicineCharges + doctorFee;

        file << fixed << setprecision(2);
        file << "-------------------------------------------\n";
        file << "--- Billing Summary ---\n";
        file << " Room Charges: Rs" << roomCharges << "\n";
        file << " Medicine Charges: Rs" << medicineCharges << "\n";
        file << " Doctor Fee: Rs" << doctorFee << "\n";
        file << " Total Bill: Rs" << total << "\n";
        file << "------------------------\n";

        file.close();
        cout << "\n\t\t\t\tPatient discharged and billing completed.\n";
    }
    catch (const exception& e) {
        cout << "\n\t\t\t\tError: " << e.what() << "\n";
    }

    system("pause");
    system("cls");
}

// addDiagnosisInfo with file exception
void addDiagnosisInfo() {
    fstream file;
    string filename;

    try {
        cout << "\n\n\t\t\t\tEnter patient file name to open : ";
        getline(cin, filename);

        file.open(filename, ios::in);
        if (!file) throw runtime_error("Record not found");

        cout << "\n\t\t\t\tCurrent Patient Record:\n\n";
        string line;
        while (getline(file, line)) {
            cout << line << endl;
        }
        file.close();

        file.open(filename, ios::app);
        if (!file) throw runtime_error("Error opening file!");

        time_t now = time(0);
        file << "\nDiagnosis Date: " << ctime(&now);

        string symptom, diagnosis, medicine, admission, ward = "N/A";
        cout << "\n\t\t\t\tEnter Symptoms: "; getline(cin, symptom);
        cout << "\t\t\t\tEnter Diagnosis: "; getline(cin, diagnosis);
        cout << "\t\t\t\tEnter Medicines: "; getline(cin, medicine);
        cout << "\t\t\t\tAdmission Required? (y/n): ";
        getline(cin, admission);

        if (admission[0] == 'Y' || admission[0] == 'y') {
            cout << "\t\t\t\tType of Ward: ";
            getline(cin, ward);
        }

        file << "\n--- Patient Admission Summary ---\n";
        file << "-----------------------------\n";
        file << "Symptoms: " << symptom << "\n";
        file << "Diagnosis: " << diagnosis << "\n";
        file << "Medicines: " << medicine << "\n";
        file << "Admission: " << admission << "\n";
        file << "Ward: " << ward << "\n";
        file << "--------------------------------\n\n";

        file.close();
        cout << "\n\t\t\t\tDiagnosis information added successfully.\n";
    }
    catch (const exception& e) {
        cout << "\n\t\t\t\tError: " << e.what() << "\n";
    }

    system("pause");
    system("cls");
}

// viewPatientHistory with file check
void viewPatientHistory() {
    ifstream file;
    string filename;

    try {
        cout << "\n\n\t\t\t\tEnter patient file name to open  ";
        getline(cin, filename);

        file.open(filename);
        if (!file) throw runtime_error("Error opening file!");

        cout << "\n\t\t\t\tFull Patient History:\n\n";
        string line;
        while (getline(file, line)) {
            cout << line << endl;
        }

        file.close();
    }
    catch (const exception& e) {
        cout << "\n\t\t\t\tError: " << e.what() << "\n";
    }

    system("pause");
    system("cls");
}

// aboutHospital with file check
void aboutHospital() {
    ifstream file;

    try {
        file.open("data.txt");
        if (!file) throw runtime_error("Error opening data.txt! Make sure it exists.");

        cout << "\n\t\t\t\t--- About the Hospital ---\n\n";
        string line;
        while (getline(file, line)) {
            cout << line << endl;
        }

        file.close();
    }
    catch (const exception& e) {
        cout << "\n\t\t\t\t" << e.what() << "\n";
    }

    system("pause");
    system("cls");
}

void exitProgram() {
    system("cls");
    cout << "\n\n\t\t\t\t\tGOOD BYE :)\n";
    cout << "\t\t\t\t\t-----------------------------------------------\n";
    system("pause");
}



