#ifndef INTERFACE_H
#define INTERFACE_H
#include <iostream>
#include <string>
#include "admin.h"
#include "staff.h"
#include "student.h"

using namespace std;

class interface : public admin, public staff, public student
{
private:
    string LoginID, LoginPassword;
public:
    void RegisterAccount();
    void Login();
};

void interface::RegisterAccount()
{
    int choice;

    system("CLS");
    cout<<endl;
    cout<<"\t--- REGISTER ---" <<endl;
    cout<<"\t----------------" <<endl;
    cout<<"\t1. Register As Staff" <<endl;
    cout<<"\t2. Register As Student" <<endl <<endl;

    cout<<"\tEnter the choice : ";
    cin>>choice;


    system("CLS");
    fflush(stdin);
    cout<<endl;
    switch(choice)
    {
        case 1: StaffRegister(); break;     //Go to Staff's Registration
        case 2: StudentRegister(); break;   //Go to Student's Registration
        default: cout<<"\tInvalid input entered!" <<endl;
                 cout<<"\tReturning to Menu Page...";
    }

    cout<<endl <<endl <<"\t";
    system("pause");
}

void interface::Login()
{
    system("CLS");
    fflush(stdin);
    cout<<endl;
    cout<<"\t--- LOGIN ---" <<endl;
    cout<<"\t-------------" <<endl;
    cout<<"\tEnter ID       : ";
    getline(cin, LoginID);
    cout<<"\tEnter Password : ";
    getline(cin, LoginPassword);

    size_t CFound, DFound;      //size_t is an unsigned int data type.
    CFound = LoginID.find("C"); //CFound use to find "C" in ID, if there is no "C" in ID, the number will more than the ID's length.
    DFound = LoginID.find("D"); //DFound use to find "D" in ID, if there is no "D" in ID, the number will more than the ID's length.

    if(LoginID == "A19000" && LoginPassword == "123")
    {
        AdminSelectOption();                    //Go to Admin path.
    }
    else if(CFound <= LoginID.size())           //If CFound is smaller or equal to ID's length.
    {
        StaffCompare(LoginID, LoginPassword);   //Go to Staff Compare ID & Password Function.
    }
    else if(DFound <= LoginID.size())           //If DFound is smaller or equal to ID's length.
    {
        StudentCompare(LoginID, LoginPassword); //Go to Student Compare ID & Password Function.
    }
    else                                        //If ID is not "A19000" or start with "C" & "D", it will show Wrong ID and Password.
    {
        cout<<endl;
        cout<<"\tWrong ID and Password!" <<endl <<endl <<"\t";
        system("pause");
    }
}

#endif
