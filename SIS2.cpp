#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <algorithm>
#include <iomanip>
#include <ctime>
#include <cstring> // For static array operations

using namespace std;

struct Student {
    string studentNumber;
    string name;
    string program;
    int creditUnits;
    double gwa;
};

const int MAX_STUDENTS = 1000; // Maximum number of students
Student students[MAX_STUDENTS]; // Array to store student records
int numStudents = 0; // Number of active students

Student deletedStudents[MAX_STUDENTS]; // Array to store deleted student records
int numDeletedStudents = 0; // Number of deleted students

// Function Prototypes
void runApp();
void addStudent();
void deleteStudent();
void displayRecords();
void displayUpdatedStudentList();
void displayDeletedStudentList();
void saveToFile(const Student[], int, const string&);
void loadFromFile(Student[], int&, const string&);
void writeToReport(const string&);
Student createStudent(); // For static array use
void printStudent(const Student&); // Utilize pointers

// Main Function
int main() {
    try {
        runApp();
    } catch (const std::exception& e) {
        cerr << "An error occurred: " << e.what() << endl;
        ofstream errorLog("error_log.txt", ios::app);
        if (errorLog) {
            errorLog << "Error on " << __DATE__ << " at " << __TIME__ << ": " << e.what() << endl;
        }
        errorLog.close();
    }
    return 0;
}

// Function Definitions
void runApp() {
    char choice;
    loadFromFile(students, numStudents, "students.txt");
    loadFromFile(deletedStudents, numDeletedStudents, "deleted_students.txt");

    do {
        cout << "Main Menu\n";
        cout << "[a] Add record\n";
        cout << "[b] Delete record\n";
        cout << "[c] Display record\n";
        cout << "[d] Exit\n";
        cout << "Select your operation: ";
        cin >> choice;

        switch (choice) {
            case 'a':
                addStudent();
                break;
            case 'b':
                deleteStudent();
                break;
            case 'c':
                displayRecords();
                break;
            case 'd':
                cout << "Exiting the program.\n";
                saveToFile(students, numStudents, "students.txt");
                saveToFile(deletedStudents, numDeletedStudents, "deleted_students.txt");
                writeToReport("report.txt");
                break;
            default:
                cout << "Invalid choice. Please enter a valid option.\n";
                break;
        }
    } while (choice != 'd');
}

void addStudent() {
    if (numStudents < MAX_STUDENTS) {
        students[numStudents] = createStudent(); // Utilizes static array for input
        numStudents++;
        cout << "Student added successfully.\n";
    } else {
        cout << "Maximum number of students reached. Cannot add more.\n";
    }
    
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear input buffer
    cout << "Press Enter to continue...";
    cin.get();
}

void deleteStudent() {
    string studentNumber;
    cout << "Enter Student Number to delete: ";
    cin >> studentNumber;

    int deletedCount = 0;
    for (int i = 0; i < numStudents; i++) {
        if (students[i].studentNumber == studentNumber) {
            // Move deleted student to deletedStudents array
            deletedStudents[numDeletedStudents] = students[i];
            numDeletedStudents++;
            // Shift remaining students to fill the gap
            for (int j = i; j < numStudents - 1; j++) {
                students[j] = students[j + 1];
            }
            numStudents--;
            deletedCount++;
            cout << "Student deleted successfully.\n";
        }
    }

    if (deletedCount == 0) {
        cout << "Student not found.\n";
    }
    
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear input buffer
    cout << "Press Enter to continue...";
    cin.get();
}

void displayRecords() {
    char choice;
    do {
        cout << "Display Records\n";
        cout << "a. Updated student list\n";
        cout << "b. All deleted students\n";
        cout << "c. Go Back\n";
        cout << "Select an option: ";
        cin >> choice;

        switch (choice) {
            case 'a':
                displayUpdatedStudentList();
                break;
            case 'b':
                displayDeletedStudentList();
                break;
            case 'c':
                break; // Go back
            default:
                cout << "Invalid choice. Please enter a valid option.\n";
                break;
        }
    } while (choice != 'c');
}

void displayUpdatedStudentList() {
    cout << "Updated Student List:\n";
    for (int i = 0; i < numStudents; i++) {
        printStudent(students[i]);
    }
    cout << "Press Enter to continue...";
    cin.ignore(); cin.get(); // Pause for user to read output
}

void displayDeletedStudentList() {
    cout << "Deleted Student List:\n";
    for (int i = 0; i < numDeletedStudents; i++) {
        printStudent(deletedStudents[i]);
    }
    cout << "Press Enter to continue...";
    cin.ignore(); cin.get(); // Pause for user to read output
}

void saveToFile(const Student data[], int numRecords, const string& filename) {
    ofstream outFile(filename);
    if (!outFile) throw runtime_error("Could not open file for writing.");

    for (int i = 0; i < numRecords; i++) {
        outFile << data[i].studentNumber << ","
                << data[i].name << ","
                << data[i].program << ","
                << data[i].creditUnits << ","
                << fixed << setprecision(2) << data[i].gwa << "\n";
    }
}

void loadFromFile(Student data[], int& numRecords, const string& filename) {
    ifstream inFile(filename);
    string line;

    numRecords = 0; // Initialize the number of records

    while (getline(inFile, line) && numRecords < MAX_STUDENTS) {
        stringstream ss(line);
        getline(ss, data[numRecords].studentNumber, ',');
        getline(ss, data[numRecords].name, ',');
        getline(ss, data[numRecords].program, ',');
        ss >> data[numRecords].creditUnits;
        ss.ignore();
        ss >> data[numRecords].gwa;
        numRecords++; // Increment the number of records
    }
}

void writeToReport(const string& filename) {
    ofstream report(filename);
    if (!report) throw runtime_error("Could not open report file for writing.");

    report << "Student Records Report - " << __DATE__ << "\n";
    report << "Total students: " << numStudents << "\n";
    report << "Deleted students: " << numDeletedStudents << "\n";
    // Add more detailed reporting as needed
}

Student createStudent() {
    Student s;
    cout << "Enter student details\n";
    cout << "Student Number: ";
    cin >> s.studentNumber;
    cout << "Name: ";
    cin.ignore();
    getline(cin, s.name);
    cout << "Program: ";
    cin >> s.program;
    cout << "Credit Units: ";
    cin >> s.creditUnits;
    cout << "GWA: ";
    cin >> s.gwa;
    return s;
}

void printStudent(const Student& s) {
    cout << "Student Number: " << s.studentNumber
         << ", Name: " << s.name
         << ", Program: " << s.program
         << ", Credit Units: " << s.creditUnits
         << ", GWA: " << fixed << setprecision(2) << s.gwa << endl;
}
