#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class Student {
public:
    int rollNo;
    string name;
    string course;
    float marks;

    void input() {
        cout << "\nEnter Roll Number: ";
        cin >> rollNo;
        cin.ignore();

        cout << "Enter Name: ";
        getline(cin, name);

        cout << "Enter Course: ";
        getline(cin, course);

        cout << "Enter Marks: ";
        cin >> marks;
    }

    void display() {
        cout << "\nRoll Number : " << rollNo;
        cout << "\nName        : " << name;
        cout << "\nCourse      : " << course;
        cout << "\nMarks       : " << marks;
        cout << "\n--------------------------";
    }
};

void addStudent() {
    Student s;

    ofstream file("students.txt", ios::app);

    s.input();

    file << s.rollNo << endl;
    file << s.name << endl;
    file << s.course << endl;
    file << s.marks << endl;

    file.close();

    cout << "\nStudent Record Added Successfully!\n";
}

void displayStudents() {
    Student s;

    ifstream file("students.txt");

    if (!file) {
        cout << "\nNo Records Found!\n";
        return;
    }

    while (file >> s.rollNo) {
        file.ignore();
        getline(file, s.name);
        getline(file, s.course);
        file >> s.marks;

        s.display();
    }

    file.close();
}

void searchStudent() {
    Student s;
    int roll;
    bool found = false;

    ifstream file("students.txt");

    cout << "\nEnter Roll Number to Search: ";
    cin >> roll;

    while (file >> s.rollNo) {
        file.ignore();
        getline(file, s.name);
        getline(file, s.course);
        file >> s.marks;

        if (s.rollNo == roll) {
            cout << "\nStudent Found!\n";
            s.display();
            found = true;
        }
    }

    if (!found) {
        cout << "\nStudent Not Found!\n";
    }

    file.close();
}

void deleteStudent() {
    Student s;
    int roll;
    bool found = false;

    ifstream file("students.txt");
    ofstream temp("temp.txt");

    cout << "\nEnter Roll Number to Delete: ";
    cin >> roll;

    while (file >> s.rollNo) {
        file.ignore();
        getline(file, s.name);
        getline(file, s.course);
        file >> s.marks;

        if (s.rollNo != roll) {
            temp << s.rollNo << endl;
            temp << s.name << endl;
            temp << s.course << endl;
            temp << s.marks << endl;
        } else {
            found = true;
        }
    }

    file.close();
    temp.close();

    remove("students.txt");
    rename("temp.txt", "students.txt");

    if (found)
        cout << "\nRecord Deleted Successfully!\n";
    else
        cout << "\nStudent Not Found!\n";
}

void updateStudent() {
    Student s;
    int roll;
    bool found = false;

    ifstream file("students.txt");
    ofstream temp("temp.txt");

    cout << "\nEnter Roll Number to Update: ";
    cin >> roll;

    while (file >> s.rollNo) {
        file.ignore();
        getline(file, s.name);
        getline(file, s.course);
        file >> s.marks;

        if (s.rollNo == roll) {
            cout << "\nEnter New Details:\n";
            s.input();
            found = true;
        }

        temp << s.rollNo << endl;
        temp << s.name << endl;
        temp << s.course << endl;
        temp << s.marks << endl;
    }

    file.close();
    temp.close();

    remove("students.txt");
    rename("temp.txt", "students.txt");

    if (found)
        cout << "\nRecord Updated Successfully!\n";
    else
        cout << "\nStudent Not Found!\n";
}

int main() {
    int choice;

    do {
        cout << "\n====== STUDENT MANAGEMENT SYSTEM ======\n";
        cout << "1. Add Student\n";
        cout << "2. Display Students\n";
        cout << "3. Search Student\n";
        cout << "4. Update Student\n";
        cout << "5. Delete Student\n";
        cout << "6. Exit\n";

        cout << "\nEnter Your Choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                addStudent();
                break;

            case 2:
                displayStudents();
                break;

            case 3:
                searchStudent();
                break;

            case 4:
                updateStudent();
                break;

            case 5:
                deleteStudent();
                break;

            case 6:
                cout << "\nThank You!\n";
                break;

            default:
                cout << "\nInvalid Choice!\n";
        }

    } while (choice != 6);

    return 0;
}
