#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <limits>

#ifdef _WIN32
#include <windows.h>
#define CLEAR_CONSOLE system("cls")
#else
#include <cstdlib>
#define CLEAR_CONSOLE system("clear")
#endif

using namespace std;


struct Student {
    string studentNumber;
    string name;
    string program;
    int creditUnits;
    double gwa;
    int year;     
    int term;      
    string controlNumber;  
};

void addNewStudent(vector<Student>& students);
void deleteStudent(vector<Student>& students);
void editStudentRecord(vector<Student>& students);
void viewStudentRecords(const vector<Student>& students);
void displayStudentRecord(const Student& student);

// Custom comparator for sorting students by Student Number
bool compareStudentNumber(const Student& student1, const Student& student2);

int main() {
    
    vector<Student> students;

    // Menu loop
    int choice;
    do {
        CLEAR_CONSOLE;  

        cout << "Menu:\n";
        cout << "1. Add a New Student\n";
        cout << "2. Delete Student Records\n";
        cout << "3. Update Student Record\n";
        cout << "4. View Student Records\n";
        cout << "5. Exit\n";
        cout << "Select your operation: ";
        cin >> choice;

        switch (choice) {
            case 1:
                addNewStudent(students);
                break;

            case 2:
                deleteStudent(students);
                break;

            case 3:
                editStudentRecord(students);
                break;

            case 4:
                viewStudentRecords(students);
                break;

            case 5:
                cout << "Exiting the program.\n";
                break;

            default:
                cout << "Invalid choice. Please enter a valid option.\n";
                cin.clear(); 
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
                cin.get();    
                break;
        }

    } while (choice != 5);

    return 0;
}

// Function to add a new student
void addNewStudent(vector<Student>& students) {
    CLEAR_CONSOLE;  
    Student student;

    cout << "1. Student Number:\n";
    
    // Enter Year
    cout << "   Enter Year: ";
    cin >> student.year;

    // Enter Term
    cout << "   Enter Term (1-4): ";
    do {
        cin >> student.term;
        if (cin.fail() || (student.term < 1 || student.term > 4)) {
            cin.clear(); 
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
            cout << "      Invalid input. Please enter a valid term (1-4): ";
        }
    } while (cin.fail() || (student.term < 1 || student.term > 4));

    // Enter Control Number
    cout << "   Enter Control Number: ";
    cin >> student.controlNumber;

    // Construct the student number
    student.studentNumber = to_string(student.year) + "-" + to_string(student.term) + "-" + student.controlNumber;

    // Enter Name
    cout << "2. Name of Student: ";
    cin.ignore(); 
    getline(cin, student.name);

    // Enter Program
    cout << "3. Program (Choose from BSIT, BSEMC, BSCS, BSIS): ";
    do {
        cin >> student.program;
        if (cin.fail() || (student.program != "BSIT" && student.program != "BSEMC" &&
                           student.program != "BSCS" && student.program != "BSIS")) {
            cin.clear(); 
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
            cout << "      Invalid input. Please enter a valid program (BSIT, BSEMC, BSCS, BSIS): ";
        }
    } while (cin.fail() || (student.program != "BSIT" && student.program != "BSEMC" &&
                            student.program != "BSCS" && student.program != "BSIS"));

    // Enter Credit Units
    cout << "4. Credit Units (Enter a number from 0 to 400): ";
    cin >> student.creditUnits;

    // Enter GWA
    cout << "5. GWA (Enter a number from 0 to 100): ";
    cin >> student.gwa;

    students.push_back(student);
    cout << "Student added successfully.\n";
    cout << "Press enter to go back...";
    cin.ignore(); 
    cin.get();    
}


// Function to delete a student
void deleteStudent(vector<Student>& students) {
    CLEAR_CONSOLE;  // Clear console

    if (students.empty()) {
        cout << "No student records available.\n";
        cout << "Press enter to go back...";
        cin.ignore(); 
        cin.get();    
    } else {
        // Category menu
        cout << "Delete Student by Category:\n";
        cout << "1. All Freshmen\n";
        cout << "2. All Sophomores\n";
        cout << "3. All Juniors\n";
        cout << "4. All Seniors\n";
        cout << "5. All Graduating\n";
        cout << "6. All Graduates\n";
        cout << "7. Display All\n";
        cout << "Select a category: ";
        int category;
        cin >> category;

        CLEAR_CONSOLE; 

        // Filter students based on the selected category
        vector<Student> filteredStudents;
        switch (category) {
            case 1:
                copy_if(students.begin(), students.end(), back_inserter(filteredStudents),
                        [](const Student& s) { return s.creditUnits >= 0 && s.creditUnits <= 100; });
                break;

            case 2:
                copy_if(students.begin(), students.end(), back_inserter(filteredStudents),
                        [](const Student& s) { return s.creditUnits >= 101 && s.creditUnits <= 200; });
                break;

            case 3:
                copy_if(students.begin(), students.end(), back_inserter(filteredStudents),
                        [](const Student& s) { return s.creditUnits >= 201 && s.creditUnits <= 300; });
                break;

            case 4:
                copy_if(students.begin(), students.end(), back_inserter(filteredStudents),
                        [](const Student& s) { return s.creditUnits >= 301 && s.creditUnits <= 350; });
                break;

            case 5:
                copy_if(students.begin(), students.end(), back_inserter(filteredStudents),
                        [](const Student& s) { return s.creditUnits >= 351 && s.creditUnits <= 399; });
                break;

            case 6:
                copy_if(students.begin(), students.end(), back_inserter(filteredStudents),
                        [](const Student& s) { return s.creditUnits == 400; });
                break;

            case 7:
                filteredStudents = students;
                break;

            default:
                cout << "Invalid category. Deleting all students.\n";
                students.clear();
                break;
        }

        // Sort filtered students by Student Number
        sort(filteredStudents.begin(), filteredStudents.end(), compareStudentNumber);

        // Display filtered students
        cout << "Sorted Student Records:\n";
        int option = 1;
        for (const Student& student : filteredStudents) {
            cout << option++ << ". " << student.name << " (" << student.studentNumber << ")\n";
        }

        // Menu for selecting an action after choosing a category
        cout << option << ". Go Back\n";
        cout << "Select an action: ";
        int action;
        cin >> action;

        if (action >= 1 && action < option) {
            CLEAR_CONSOLE;  
            displayStudentRecord(filteredStudents[action - 1]);
            cout << "Do you want to delete this student? (y/n): ";
            char confirm;
            cin >> confirm;

            if (confirm == 'y' || confirm == 'Y') {
                // Find and erase the student from the main list
                string studentNumberToDelete = filteredStudents[action - 1].studentNumber;
                students.erase(remove_if(students.begin(), students.end(),
                                         [studentNumberToDelete](const Student& s) {
                                             return s.studentNumber == studentNumberToDelete;
                                         }),
                               students.end());

                cout << "Student deleted successfully.\n";
            }
        }
    }
}


// Function to display the Edit Student Menu and return the selected option
int displayEditStudentMenu() {
    cout << "Edit Student Options:\n";
    cout << "1. Edit Name\n";
    cout << "2. Edit Program\n";
    cout << "3. Edit Credit Units\n";
    cout << "4. Edit GWA\n";
    cout << "5. Go Back\n";
    cout << "Select an option: ";

    int option;
    cin >> option;
    return option;
}


// Function to edit a student record by category
void editStudentRecord(vector<Student>& students) {
    CLEAR_CONSOLE;  
    if (students.empty()) {
        cout << "No student records available.\n";
    } else {
        int category = displayEditStudentMenu();

        CLEAR_CONSOLE;  

        // Filter students based on the selected category
        vector<Student> filteredStudents;
        switch (category) {
            case 1:
                copy_if(students.begin(), students.end(), back_inserter(filteredStudents),
                        [](const Student& s) { return s.creditUnits >= 0 && s.creditUnits <= 100; });
                break;

            case 2:
                copy_if(students.begin(), students.end(), back_inserter(filteredStudents),
                        [](const Student& s) { return s.creditUnits >= 101 && s.creditUnits <= 200; });
                break;

            case 3:
                copy_if(students.begin(), students.end(), back_inserter(filteredStudents),
                        [](const Student& s) { return s.creditUnits >= 201 && s.creditUnits <= 300; });
                break;

            case 4:
                copy_if(students.begin(), students.end(), back_inserter(filteredStudents),
                        [](const Student& s) { return s.creditUnits >= 301 && s.creditUnits <= 350; });
                break;

            case 5:
                copy_if(students.begin(), students.end(), back_inserter(filteredStudents),
                        [](const Student& s) { return s.creditUnits >= 351 && s.creditUnits <= 399; });
                break;

            case 6:
                copy_if(students.begin(), students.end(), back_inserter(filteredStudents),
                        [](const Student& s) { return s.creditUnits == 400; });
                break;

            case 7:
                filteredStudents = students;
                break;

            default:
                cout << "Invalid category. Editing all students.\n";
                filteredStudents = students;
                break;
        }

        // Sort filtered students by Student Number
        sort(filteredStudents.begin(), filteredStudents.end(), compareStudentNumber);

        // Display filtered students
        cout << "Select a student to edit:\n";
        int option = 1;
        for (const Student& student : filteredStudents) {
            cout << option++ << ". " << student.name << " (" << student.studentNumber << ")\n";
        }

        // Menu for selecting a student to edit
        cout << option << ". Go Back\n";
        cout << "Select an option: ";
        int selectedOption;
        cin >> selectedOption;

        if (selectedOption >= 1 && selectedOption < option) {
            CLEAR_CONSOLE;  
            Student& studentToEdit = filteredStudents[selectedOption - 1];

            int editOption;
            do {
                CLEAR_CONSOLE;  
                editOption = displayEditStudentMenu();

                switch (editOption) {
                    case 1:
                        cout << "Enter New Name of Student: ";
                        cin.ignore(); 
                        getline(cin, studentToEdit.name);
                        break;

                    case 2:
                        cout << "Enter New Program (Choose from BSIT, BSEMC, BSCS, BSIS): ";
                        do {
                            cin >> studentToEdit.program;
                            if (cin.fail() || (studentToEdit.program != "BSIT" && studentToEdit.program != "BSEMC" &&
                                               studentToEdit.program != "BSCS" && studentToEdit.program != "BSIS")) {
                                cin.clear(); 
                                cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
                                cout << "      Invalid input. Please enter a valid program (BSIT, BSEMC, BSCS, BSIS): ";
                            }
                        } while (cin.fail() || (studentToEdit.program != "BSIT" && studentToEdit.program != "BSEMC" &&
                                                studentToEdit.program != "BSCS" && studentToEdit.program != "BSIS"));
                        break;

                    case 3:
                        cout << "Enter New Credit Units (Enter a number from 0 to 400): ";
                        cin >> studentToEdit.creditUnits;
                        break;

                    case 4:
                        cout << "Enter New GWA (Enter a number from 0 to 100): ";
                        cin >> studentToEdit.gwa;
                        break;

                    case 5:
                        break;

                    default:
                        cout << "Invalid option. Please enter a valid option.\n";
                        break;
                }
            } while (editOption != 5);

            CLEAR_CONSOLE;  

            
            displayStudentRecord(studentToEdit);
            cout << "Press Enter to go back...";
            cin.ignore(); 
            cin.get();    
        }
    }
}


// Function to view all student records
void viewStudentRecords(const vector<Student>& students) {
    CLEAR_CONSOLE; 
    if (students.empty()) {
        cout << "No student records available.\n";
    } else {
        // Category menu
        cout << "View Student Records by Category:\n";
        cout << "1. All Freshmen\n";
        cout << "2. All Sophomores\n";
        cout << "3. All Juniors\n";
        cout << "4. All Seniors\n";
        cout << "5. All Graduating\n";
        cout << "6. All Graduates\n";
        cout << "7. Display All\n";
        cout << "Select a category: ";
        int category;
        cin >> category;

        CLEAR_CONSOLE; 

        // Filter students based on the selected category
        vector<Student> filteredStudents;
        switch (category) {
            case 1:
                copy_if(students.begin(), students.end(), back_inserter(filteredStudents),
                        [](const Student& s) { return s.creditUnits >= 0 && s.creditUnits <= 100; });
                break;

            case 2:
                copy_if(students.begin(), students.end(), back_inserter(filteredStudents),
                        [](const Student& s) { return s.creditUnits >= 101 && s.creditUnits <= 200; });
                break;

            case 3:
                copy_if(students.begin(), students.end(), back_inserter(filteredStudents),
                        [](const Student& s) { return s.creditUnits >= 201 && s.creditUnits <= 300; });
                break;

            case 4:
                copy_if(students.begin(), students.end(), back_inserter(filteredStudents),
                        [](const Student& s) { return s.creditUnits >= 301 && s.creditUnits <= 350; });
                break;

            case 5:
                copy_if(students.begin(), students.end(), back_inserter(filteredStudents),
                        [](const Student& s) { return s.creditUnits >= 351 && s.creditUnits <= 399; });
                break;

            case 6:
                copy_if(students.begin(), students.end(), back_inserter(filteredStudents),
                        [](const Student& s) { return s.creditUnits == 400; });
                break;

            case 7:
                filteredStudents = students;
                break;

            default:
                cout << "Invalid category. Showing all students.\n";
                filteredStudents = students;
                break;
        }

        // Sort filtered students by Student Number
        sort(filteredStudents.begin(), filteredStudents.end(), compareStudentNumber);

        // Display filtered students
        cout << "Sorted Student Records:\n";
        int option = 1;
        for (const Student& student : filteredStudents) {
            cout << option++ << ". " << student.name << " (" << student.studentNumber << ")\n";
        }

        // Menu for selecting an action after choosing a category
        cout << option << ". Go Back\n";
        cout << "Select an action: ";
        int action;
        cin >> action;

        if (action >= 1 && action < option) {
            CLEAR_CONSOLE;  
            displayStudentRecord(filteredStudents[action - 1]);
            cout << "Press Enter to go back...";
            cin.ignore(); 
            cin.get();    
        }
    }
}

// Function to display a single student record
void displayStudentRecord(const Student& student) {
    cout << "Student Number: " << student.studentNumber << endl;
    cout << "Name of Student: " << student.name << endl;
    cout << "Program: " << student.program << endl;
    cout << "Credit Units: " << student.creditUnits << endl;

    
    string status = (student.creditUnits >= 0 && student.creditUnits <= 350) ? "Non Graduating" : "Graduating";
    cout << "Status: " << status << endl;

    cout << "GWA: " << student.gwa << endl;

   
    string honors;
    if (status == "Non Graduating") {
        if (student.gwa >= 96 && student.gwa <= 100) {
            honors = "First Honor";
        } else if (student.gwa >= 93 && student.gwa <= 95) {
            honors = "Second Honor";
        } else if (student.gwa >= 90 && student.gwa <= 92) {
            honors = "Third Honor";
        } else {
            honors = "No Honor";
        }
    } else {  // Graduating
        if (student.gwa >= 96 && student.gwa <= 100) {
            honors = "Summa Cum Laude";
        } else if (student.gwa >= 93 && student.gwa <= 95) {
            honors = "Magna Cum Laude";
        } else if (student.gwa >= 90 && student.gwa <= 92) {
            honors = "Cum Laude";
        } else {
            honors = "No Honor";
        }
    }

    cout << "Honors: " << honors << endl;
}


bool compareStudentNumber(const Student& student1, const Student& student2) {
    return student1.studentNumber < student2.studentNumber;
}