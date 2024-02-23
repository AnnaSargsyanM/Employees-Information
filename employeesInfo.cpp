//     This program reads the employees' names from the file and 
//     organizes them in columns. Additionally, it asks the user whether they want
//     to add more employees or not.
//
//****************************************************************************************************

#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

using namespace std;

struct Date
{
	int month;
	int day;
	int year;
};

struct Employee
{
	string name;
	int age;
	Date dateEmployed;
};

Employee* readEmployees(const string&, int&);
void displayEmployees(const Employee[], int);
void inputEmployees(Employee*&, int&);

//****************************************************************************************************

int main()
{
    string empFile = "Employees.txt";
    int numEmps;
    Employee* employees = readEmployees(empFile, numEmps);

    displayEmployees(employees, numEmps);

    char addMore;
    cout << "Do you want to add more employees (y/n)? ";
    cin >> addMore;

    if (addMore == 'y' || addMore == 'Y') 
    {
        inputEmployees(employees, numEmps);
        displayEmployees(employees, numEmps);
    }

    ofstream dataFile;
    dataFile.open(empFile);

    dataFile << numEmps << endl;
    for (int i = 0; i < numEmps; i++) 
    {
        dataFile << employees[i].name << "," << employees[i].age << ","
            << employees[i].dateEmployed.month << "/"
            << employees[i].dateEmployed.day << "/"
            << employees[i].dateEmployed.year << endl;
    }
    dataFile.close();

    delete[] employees;

    return 0;
}
	
//****************************************************************************************************

Employee* readEmployees(const string& empFile, int& numEmps)
{
    ifstream inFile(empFile);
    if (!inFile.is_open()) 
    {
        cerr << "Error: Unable to open file " << empFile << endl;
        exit(1);
    }

    inFile >> numEmps;
    inFile.ignore(); 

    Employee* employees = new Employee[numEmps];

    for (int i = 0; i < numEmps; i++) 
    {
        getline(inFile, employees[i].name, ',');
        inFile >> employees[i].age;
        inFile.ignore(); 
        inFile >> employees[i].dateEmployed.month;
        inFile.ignore(); 
        inFile >> employees[i].dateEmployed.day;
        inFile.ignore();
        inFile >> employees[i].dateEmployed.year;
    }

    inFile.close();
    return employees;

}

//****************************************************************************************************

void displayEmployees(const Employee emps[], int numEmps)
{
    cout << left << setw(50) << "NAME" << setw(20) << "AGE" << setw(15) << "DATE EMPLOYED" << endl;
    for (int i = 0; i < numEmps; i++) 
    {
        cout << left << setw(50) << emps[i].name;
        cout << setw(20) << emps[i].age;
        cout << setw(2) << emps[i].dateEmployed.month << "/";
        cout << setw(2) << emps[i].dateEmployed.day << "/";
        cout << setw(4) << emps[i].dateEmployed.year;
        cout << endl;
    }
}

//****************************************************************************************************

void inputEmployees(Employee*& emps, int& numEmps)
{
    int numNewEmployees;
    cout << "How many new employees do you want to add? ";
    cin >> numNewEmployees;

    Employee* newEmployees = new Employee[numEmps + numNewEmployees];

    for (int i = 0; i < numEmps; i++) 
    {
        newEmployees[i] = emps[i];
    }

    for (int i = numEmps; i < numEmps + numNewEmployees; i++) 
    {
        cout << "NAME: ";
        cin.ignore();
        getline(cin, newEmployees[i].name);

        cout << "AGE: ";
        cin >> newEmployees[i].age;

        cout << "EMPLOYED (MM/DD/YYYY): ";
        cin >> newEmployees[i].dateEmployed.month;
        cin.ignore(); 
        cin >> newEmployees[i].dateEmployed.day;
        cin.ignore();
        cin >> newEmployees[i].dateEmployed.year;
    }

    delete[] emps;  
    emps = newEmployees;
    numEmps += numNewEmployees;
}

//****************************************************************************************************
/*

NAME                                              AGE                 DATE EMPLOYED
Stephen Smith                                     25                  15/12/2001


Susan Kim-Jones                                 33                  9 /1 /2012


Kun Joom Jadav                                  52                  22/8 /1999

Anna Sargsyan                                    22                  8 /16/2023
Do you want to add more employees (y/n)? y
How many new employees do you want to add? 1
NAME: John Smith
AGE: 42
EMPLOYED (MM/DD/YYYY): 09/15/2016
NAME                                              AGE                 DATE EMPLOYED
Stephen Smith                                     25                  15/12/2001


Susan Kim-Jones                                 33                  9 /1 /2012


Kun Joom Jadav                                  52                  22/8 /1999

Anna Sargsyan                                    22                  8 /16/2023
John Smith                                        42                  9 /15/2016

*/
