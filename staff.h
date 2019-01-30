#ifndef STAFF_H
#define STAFF_H
#include <iostream>
#include <string>
#include <fstream>
#include "book.h"

using namespace std;

class staff : public book
{
private:
    int StaffNo;
    struct StaffNode
    {
        int StaffFine=0, StaffBorrow=0;
        string StaffID, StaffName, StaffPassword;
        StaffNode *next;
    } *StaffHead, *newStaffNode, *StaffNodePtr;
public:
    staff();                //Constructor use to retrieve all the data in file.
    ~staff();               //Destructor use to delete all the node in the memory.
    void StaffRegister();   //This function allow Staff to register account.
    void StaffCompare(string PassID, string password);  //This function will compare ID & Password.
    void StaffSelectOption(string PassID);              //This function will let Staff choose option.
    void StaffViewProfileBorrowedBook(string PassID);   //This function will let Staff view their profile & borrow history.
    void StaffBorrowBook(string PassID);    //This function will let Staff borrow book.
    void StaffReturnBook(string PassID);    //This function will let Staff return book.
    void StaffFile();   //This function use to write all the data into file after every option.
};

staff::staff()
{
    //Initialize value to variables & pointers.
    StaffNo = 19000;
    StaffHead = nullptr;
    newStaffNode = nullptr;
    StaffNodePtr = nullptr;

    ifstream fread;                 //Declare file object.
    fread.open("StaffRecord.txt");  //Use object to open the file for retrieve data from "StaffRecord.txt".
    if(!fread.eof())
    {
        newStaffNode = new StaffNode;   //Create a new Staff Node in memory & retrieve data from file into Node's variables.
        while(fread>>newStaffNode->StaffID >>newStaffNode->StaffName >>newStaffNode->StaffPassword >>newStaffNode->StaffFine >>newStaffNode->StaffBorrow)
        {
            StaffNo++;
            newStaffNode->next = nullptr;
            if(StaffHead == nullptr)
            {
                StaffHead = newStaffNode;
            }
            else
            {
                StaffNodePtr = StaffHead;
                while(StaffNodePtr->next != nullptr)
                {
                    StaffNodePtr = StaffNodePtr->next;
                }
                StaffNodePtr->next = newStaffNode;
            }
            newStaffNode = new StaffNode;
        }
        fread.close();  //Close "StaffRecord.txt" file.
    }
}

staff::~staff()
{
    //Delete all StaffNode from memory by travel all Node.
    while(StaffHead != nullptr)
    {
        StaffNodePtr = StaffHead;
        StaffHead = StaffHead->next;
        delete StaffNodePtr;
    }
}

void staff::StaffRegister()
{
    int POC;        //POC is position of character which use to indicate index of string.
    size_t SFound;  //SFound use to find " " in name & author.
    newStaffNode = new StaffNode;   //Create a new Node in memory.
    newStaffNode->StaffID = "C" + to_string(StaffNo);
    StaffNo++;

    cout<<"\t--- Staff Registration ---" <<endl;
    cout<<"\t--------------------------" <<endl;
    cout<<"\tEnter your name     : ";
    getline(cin, newStaffNode->StaffName);
    cout<<"\tEnter your password : ";
    getline(cin, newStaffNode->StaffPassword);
    newStaffNode->next = nullptr;

    POC=0;
    while(newStaffNode->StaffName[POC]) //Change name to uppercase.
    {
        newStaffNode->StaffName[POC] = toupper(newStaffNode->StaffName[POC]);
        POC++;
    }

    SFound = newStaffNode->StaffName.find(" ");     //If there is no " " in name, the number will more than the name's length.
    while(SFound <= newStaffNode->StaffName.size()) //While SFound is smaller or equal to book's name length, change " " to "_".
    {
        newStaffNode->StaffName.replace(newStaffNode->StaffName.find(" "), 1, "_");
        SFound = newStaffNode->StaffName.find(" ");
    }

    //If Head is pointing to null, assign Head pointer to the first new Node.
    //Then the new Node created will be assigned to every Node's next.
    //So, every Node created is linked together.
    if(StaffHead == nullptr)
    {
        StaffHead = newStaffNode;
    }
    else
    {
        StaffNodePtr = StaffHead;
        while(StaffNodePtr->next != nullptr)
        {
            StaffNodePtr = StaffNodePtr->next;
        }
        StaffNodePtr->next = newStaffNode;
    }

    ofstream fwrite;                //Declare file object.
    fwrite.open("StaffRecord.txt"); //Use object to open the file for write data into "StaffRecord.txt" from linked Node.
    if(StaffHead != nullptr)        //If Head is not pointing to null.
    {
        //Assign pointer to Head, so the pointer can travel all the linked Node.
        //It will write data into "StaffRecord.txt" until pointer pointing to null.
        StaffNodePtr = StaffHead;
        while(StaffNodePtr != nullptr)
        {
            fwrite<<setw(8) <<StaffNodePtr->StaffID <<setw(20) <<StaffNodePtr->StaffName <<setw(20) <<StaffNodePtr->StaffPassword <<setw(9) <<StaffNodePtr->StaffFine <<setw(3) <<StaffNodePtr->StaffBorrow <<endl;
            StaffNodePtr = StaffNodePtr->next;
        }
        fwrite.close(); //Close "StaffRecord.txt" file.
    }

    cout<<endl;
    cout<<"\tUse this ID to login : " <<newStaffNode->StaffID;
}

void staff::StaffCompare(string PassID, string password)
{
    StaffNode *StaffCompareNodePtr;

    StaffCompareNodePtr = StaffHead;        //Assign pointer to Head, so the pointer can travel all the linked Node.
    while(StaffCompareNodePtr != nullptr)   //Travel the linked Node, while the pointer is not pointing to null.
    {
        //If ID and Password is same, go to Staff's menu page.
        if(StaffCompareNodePtr->StaffID == PassID && StaffCompareNodePtr->StaffPassword == password)
        {
            StaffSelectOption(PassID);
            break;
        }
        StaffCompareNodePtr = StaffCompareNodePtr->next;
    }

    //If the pointer travel to the end of linked Node and cannot find the ID.
    //The system will show below output.
    if(StaffCompareNodePtr == nullptr)
    {
        cout<<endl;
        cout<<"\tWrong ID and Password!";
    }
}

void staff::StaffSelectOption(string PassID)
{
    int choice;

    do
    {
        system("CLS");
        cout<<endl;
        cout<<"\t--- STAFF ---" <<endl;
        cout<<"\t-------------" <<endl;
        cout<<"\t1. View My Profile & Borrowed Book" <<endl;
        cout<<"\t2. View Book List" <<endl;
        cout<<"\t3. Search Book" <<endl;
        cout<<"\t4. Borrow Book" <<endl;
        cout<<"\t5. Return Book" <<endl;
        cout<<"\t6. Log Out" <<endl <<endl;

        cout<<"\tEnter the choice : ";
        cin>>choice;

        system("CLS");
        fflush(stdin);
        cout<<endl;
        switch(choice)
        {
            case 1: StaffViewProfileBorrowedBook(PassID); break;
            case 2: ViewBookList(); break;
            case 3: SearchBook(); break;
            case 4: StaffBorrowBook(PassID); break;
            case 5: StaffReturnBook(PassID); break;
            case 6: cout<<"\tLogging out...";
        }
        StaffFile();    //Go to StaffFile() function after every option.
        cout<<endl <<endl <<"\t";
        system("pause");
    }while(choice != 6);
}

void staff::StaffViewProfileBorrowedBook(string PassID)
{
    int number=0;

    cout<<"\t--- MY PROFILE ---" <<endl <<endl;

    //Assign pointer to Head, so the pointer can travel all the linked Node.
    //It will show all the Node's details until pointer pointing to null.
    StaffNodePtr = StaffHead;
    while(StaffNodePtr != nullptr)
    {
        //If Node's ID is same as user ID, show all the details.
        if(StaffNodePtr->StaffID == PassID)
        {
            cout<<"\tID : " <<StaffNodePtr->StaffID <<"\t\tNAME : " <<StaffNodePtr->StaffName <<endl <<endl;
            cout<<"\tCurrent Borrow : " <<StaffNodePtr->StaffBorrow <<"\t\tFINE : " <<StaffNodePtr->StaffFine <<endl <<endl;

            //If user's FINE is not equal to "0".
            //The system will show below output.
            if(StaffNodePtr->StaffFine != 0)
            {
                cout<<"\t-------------------------------------" <<endl;
                cout<<"\tPlease CLEAR FINE to Admin at counter" <<endl;
                cout<<"\t-------------------------------------" <<endl;
            }
            break;
        }
        StaffNodePtr = StaffNodePtr->next;
    }

    //Show user borrow history.
    cout<<endl;
    cout<<"\t--- MY BORROWED BOOK LIST ---" <<endl <<endl;
    cout<<"\t" <<setw(4) <<"NO" <<setw(10) <<"Book ID" <<setw(14) <<"Borrow Date" <<setw(14) <<"Return Date" <<endl;

    //Assign pointer to Head, so the pointer can travel all the linked Node.
    //Travel the linked Node, while the pointer is not pointing to null.
    BorrowNodePtr = BorrowHead;
    while(BorrowNodePtr != nullptr)
    {
        //If Node's borrower ID is same as user ID, show user's borrow history.
        if(BorrowNodePtr->BorrowerID == PassID)
        {
            cout<<"\t" <<setw(4) <<++number <<setw(10) <<BorrowNodePtr->BorrowBookID <<setw(14) <<BorrowNodePtr->BorrowDate <<setw(14) <<BorrowNodePtr->ReturnDate <<endl;
        }
        BorrowNodePtr = BorrowNodePtr->next;
    }
}

void staff::StaffBorrowBook(string PassID)
{
    //Assign pointer to Head, so the pointer can travel all the linked Node.
    //Travel the linked Node, while the pointer is not pointing to null.
    StaffNodePtr = StaffHead;
    while(StaffNodePtr != nullptr)
    {
        if(StaffNodePtr->StaffID == PassID)
        {
            break;
        }
        StaffNodePtr = StaffNodePtr->next;
    }

    //If user's current borrow is less than "3" and FINE is equal to "0".
    //Go to BorrowBook() function.
    if(StaffNodePtr->StaffBorrow < 3 && StaffNodePtr->StaffFine == 0)
    {
        //If BorrowBook() function return true, user's current borrow+1.
        if(BorrowBook(PassID))
        {
            StaffNodePtr->StaffBorrow++;
        }
    }
    //If user's current borrow is equal to 3.
    //The system will show below output.
    else if(StaffNodePtr->StaffBorrow == 3)
    {
        cout<<"\tYou cannot borrow more than 3 books.";
    }
    //If user's FINE is not equal to "0".
    //The system will show below output.
    else if(StaffNodePtr->StaffFine > 0)
    {
        cout<<"\tPlease clear the FINE to borrow book.";
    }
}

void staff::StaffReturnBook(string PassID)
{
    //If ReturnBook() function return true.
    if(ReturnBook(PassID))
    {
        //Assign pointer to Head, so the pointer can travel all the linked Node.
        //Travel the linked Node, while the pointer is not pointing to null.
        StaffNodePtr = StaffHead;
        while(StaffNodePtr != nullptr)
        {
            if(StaffNodePtr->StaffID == PassID)
            {
                break;
            }
            StaffNodePtr = StaffNodePtr->next;
        }
        StaffNodePtr->StaffBorrow--;
    }
}

void staff::StaffFile()
{
    BookFile(); //Call BookFile function from book.h.

    ofstream fwrite;                //Declare file object.
    fwrite.open("StaffRecord.txt"); //Use object to open the file for write data into "StaffRecord.txt" from linked Node.
    if(StaffHead != nullptr)        //If Head is not pointing to null.
    {
        //Assign pointer to Head, so the pointer can travel all the linked Node.
        //It will write data into "StaffRecord.txt" until pointer pointing to null.
        StaffNodePtr = StaffHead;
        while(StaffNodePtr != nullptr)
        {
            fwrite<<setw(8) <<StaffNodePtr->StaffID <<setw(20) <<StaffNodePtr->StaffName <<setw(20) <<StaffNodePtr->StaffPassword <<setw(9) <<StaffNodePtr->StaffFine <<setw(3) <<StaffNodePtr->StaffBorrow <<endl;
            StaffNodePtr = StaffNodePtr->next;
        }
        fwrite.close(); //Close "StaffRecord.txt" file.
    }
}

#endif
