#ifndef ADMIN_H
#define ADMIN_H
#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
#include "book.h"

using namespace std;

class admin : public book
{
private:
    string AdminID, AdminPassword;
    struct StaffNode
    {
        int StaffFine=0, StaffBorrow=0;
        string StaffID, StaffName, StaffPassword;
        StaffNode *next;
    } *StaffHead, *newStaffNode, *StaffNodePtr;

    struct StudentNode
    {
        int StudentFine=0, StudentBorrow=0;
        string StudentID, StudentName, StudentPassword;
        StudentNode *next;
    } *StudentHead, *newStudentNode, *StudentNodePtr;
public:
    admin();                    //Constructor use to retrieve all the data in file.
    ~admin();                   //Destructor use to delete all the node in the memory.
    void AdminSelectOption();   //This function will show all the option for Admin to choose.
    void AddBook();             //This function will let Admin to add book.
    void UpdateBook();          //This function will let Admin update the book with book ID.
    void DeleteBook();          //This function will let Admin delete the book with book ID.
    void ViewStaffList();       //This function will let Admin check all the staff.
    void ViewStudentList();     //This function will let admin check all the student.
    void ViewBorrowerList();    //This function will let Admin check all the borrower.
    void FineCharge();          //This function will let Admin charge FINE on borrower who return book late or destroy book.
    void FineChargeID(int PassFine);   //This function will let Admin to type the ID for charge FINE.
    void ClearFine();   //This function will let Admin clear the FINE of staff or student.
    void AdminFile();   //This function use to write all the data into file after every option.
};

admin::admin()
{
    //Initialize value to variables & pointers.
    AdminID = "A19000";
    AdminPassword = "123";

    StaffHead = nullptr;
    newStaffNode = nullptr;
    StaffNodePtr = nullptr;
    StudentHead = nullptr;
    newStudentNode = nullptr;
    StudentNodePtr = nullptr;

    ifstream fread;                 //Declare file object.
    fread.open("StaffRecord.txt");  //Use object to open the file for retrieve data from "StaffRecord.txt".
    if(!fread.eof())
    {
        newStaffNode = new StaffNode;   //Create a new Staff Node in memory & retrieve data from file into Node's variables.
        while(fread>>newStaffNode->StaffID >>newStaffNode->StaffName >>newStaffNode->StaffPassword >>newStaffNode->StaffFine >>newStaffNode->StaffBorrow)
        {
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

    fread.open("StudentRecord.txt");    //Use object to open the file for retrieve data from "StudentRecord.txt".
    if(!fread.eof())
    {
        newStudentNode = new StudentNode;
        while(fread>>newStudentNode->StudentID >>newStudentNode->StudentName >>newStudentNode->StudentPassword >>newStudentNode->StudentFine >>newStudentNode->StudentBorrow)
        {
            newStudentNode->next = nullptr;
            if(StudentHead == nullptr)
            {
                StudentHead = newStudentNode;
            }
            else
            {
                StudentNodePtr = StudentHead;
                while(StudentNodePtr->next != nullptr)
                {
                    StudentNodePtr = StudentNodePtr->next;
                }
                StudentNodePtr->next = newStudentNode;
            }
            newStudentNode = new StudentNode;
        }
        fread.close();  //Close "StudentRecord.txt" file.
    }
}

admin::~admin()
{
    //Delete all StaffNode from memory by travel all Node.
    while(StaffHead != nullptr)
    {
        StaffNodePtr = StaffHead;
        StaffHead = StaffHead->next;
        delete StaffNodePtr;
    }

    //Delete all StudentNode from memory by travel all Node.
    while(StudentHead != nullptr)
    {
        StudentNodePtr = StudentHead;
        StudentHead = StudentHead->next;
        delete StudentNodePtr;
    }
}

void admin::AdminSelectOption()
{
    int choice;

    do
    {
        system("CLS");
        cout<<endl;
        cout<<"\t--- ADMIN ---" <<endl;
        cout<<"\t-------------" <<endl;
        cout<<"\t1. Add New Book" <<endl;
        cout<<"\t2. Update Book" <<endl;
        cout<<"\t3. Delete Book" <<endl;
        cout<<"\t4. Search Book" <<endl;
        cout<<"\t5. View Book List" <<endl;
        cout<<"\t6. View Staff List" <<endl;
        cout<<"\t7. View Student List" <<endl;
        cout<<"\t8. View Borrower List" <<endl;
        cout<<"\t9. Fine Charge" <<endl;
        cout<<"\t10. Clear Fine" <<endl;
        cout<<"\t11. Log Out" <<endl <<endl;

        cout<<"\tEnter the choice : ";
        cin>>choice;

        system("CLS");
        fflush(stdin);
        cout<<endl;
        switch(choice)
        {
            case 1: AddBook(); break;
            case 2: UpdateBook(); break;
            case 3: DeleteBook(); break;
            case 4: SearchBook(); break;
            case 5: ViewBookList(); break;
            case 6: ViewStaffList(); break;
            case 7: ViewStudentList(); break;
            case 8: ViewBorrowerList(); break;
            case 9: FineCharge(); break;
            case 10: ClearFine(); break;
            case 11: cout<<"\tLogging out...";
        }
        AdminFile();    //Go to AdminFile() function after every option.
        cout<<endl <<endl <<"\t";
        system("pause");
    }while(choice != 11);
}

void admin::AddBook()
{
    int POC;        //POC is position of character which use to indicate index of string.
    size_t SFound;  //SFound use to find " " in name & author.

    newBookNode = new BookNode;
    newBookNode->BookID = "B" + to_string(BookNo);
    BookNo++;
    cout<<"\t--- Add Book ---" <<endl;
    cout<<"\t----------------" <<endl;
    cout<<"\tEnter Book Name   : ";
    getline(cin, newBookNode->BookName);
    cout<<"\tEnter Author Name : ";
    getline(cin, newBookNode->BookAuthor);
    newBookNode->next = nullptr;

    POC=0;
    while(newBookNode->BookName[POC])   //Change book's name to uppercase.
    {
        newBookNode->BookName[POC] = toupper(newBookNode->BookName[POC]);
        POC++;
    }
    SFound = newBookNode->BookName.find(" ");       //If there is no " " in name, the number will more than the name's length.
    while(SFound <= newBookNode->BookName.size())   //While SFound is smaller or equal to book's name length, change " " to "_".
    {
        newBookNode->BookName.replace(newBookNode->BookName.find(" "), 1, "_");
        SFound = newBookNode->BookName.find(" ");
    }

    POC=0;
    while(newBookNode->BookAuthor[POC]) //Change book's author to uppercase.
    {
        newBookNode->BookAuthor[POC] = toupper(newBookNode->BookAuthor[POC]);
        POC++;
    }
    SFound = newBookNode->BookAuthor.find(" ");     //If there is no " " in author, the number will more than the author's length.
    while(SFound <= newBookNode->BookAuthor.size()) //While SFound is smaller or equal to book's author length, change " " to "_".
    {
        newBookNode->BookAuthor.replace(newBookNode->BookAuthor.find(" "), 1, "_");
        SFound = newBookNode->BookAuthor.find(" ");
    }

    //If Head is pointing to null, assign Head pointer to the first new Node.
    //Then the new Node created will be assigned to every Node's next.
    //So, every Node created is linked together.
    if(BookHead == nullptr)
    {
        BookHead = newBookNode;
    }
    else
    {
        BookNodePtr = BookHead;
        while(BookNodePtr->next != nullptr)
        {
            BookNodePtr = BookNodePtr->next;
        }
        BookNodePtr->next = newBookNode;
    }

    cout<<endl;
    cout<<"\tBook added Successfully";
}

void admin::UpdateBook()
{
    int POC;        //POC is position of character which use to indicate index of string.
    size_t SFound;  //SFound use to find " " in name & author.
    string id, name, author;

    cout<<"\t--- Update Book ---" <<endl;
    cout<<"\t-------------------" <<endl;
    cout<<"\tEnter the Book ID to update: ";
    getline(cin, id);

    BookNodePtr = BookHead;             //Assign pointer to Head, so the pointer can travel all the linked Node.
    while(BookNodePtr != nullptr)       //Travel the linked Node, while the pointer is not pointing to null.
    {
        if(BookNodePtr->BookID == id)   //If the Node having the same ID as the Admin's input, execute below statement.
        {
            fflush(stdin);
            cout<<endl;
            cout<<"\tEnter \'-\' to not update" <<endl;
            cout<<"\tUpdate Book's Name   : ";
            getline(cin, name);

            cout<<endl;
            cout<<"\tEnter \'-\' to not update" <<endl;
            cout<<"\tUpdate Book's Author : ";
            getline(cin, author);

            if(name != "-")         //If input not equal to "-", update the book's name.
            {
                POC=0;
                while(name[POC])    //Change book's name to uppercase.
                {
                    name[POC] = toupper(name[POC]);
                    POC++;
                }

                SFound = name.find(" ");        //If there is no " " in name, the number will more than the name's length.
                while(SFound <= name.size())    //while SFound is smaller or equal to book's name length, change " " to "_".
                {
                    name.replace(name.find(" "), 1, "_");
                    SFound = name.find(" ");
                }
                BookNodePtr->BookName = name;   //Update Node's book name.
            }

            if(author != "-")       //If input not equal to "-", update the book's author.
            {
                POC=0;
                while(author[POC])  //Change book's author to uppercase.
                {
                    author[POC] = toupper(author[POC]);
                    POC++;
                }

                SFound = author.find(" ");      //If there is no " " in author, the number will more than the author's length.
                while(SFound <= author.size())  //while SFound is smaller or equal to book's name length, change " " to "_".
                {
                    author.replace(author.find(" "), 1, "_");
                    SFound = author.find(" ");
                }
                BookNodePtr->BookAuthor = author;   //Update Node's book author.
            }

            if(name != "-" || author != "-")
            {
                cout<<endl;
                cout<<"\tSuccessfully update." <<endl;
                cout<<"\tGo to Search or View Book to see the update.";
            }
            break;
        }
        BookNodePtr = BookNodePtr->next;
    }

    //If the pointer travel to the end of linked Node and cannot find the ID.
    //The system will show below output.
    if(BookNodePtr == nullptr)
    {
        cout<<endl;
        cout<<"\tBook ID is not found.";
    }
}

void admin::DeleteBook()
{
    string id;

    cout<<"\t--- Delete Book ---" <<endl;
    cout<<"\t-------------------" <<endl;
    cout<<"\tEnter the Book ID to delete: ";
    getline(cin,id);

    //If the first Node is having the same ID as Admin's input.
    //Delete the first Node and assign Head to the next Node.
    if(BookHead->BookID == id)
    {
        BookNodePtr = BookHead->next;
        delete BookHead;
        BookHead = BookNodePtr;
    }
    else
    {
        BookNodePtr = BookHead;         //Assign pointer to Head, so the pointer can travel all the linked Node.
        while(BookNodePtr != nullptr)   //Travel the linked Node, while the pointer is not pointing to null.
        {
            if(BookNodePtr->BookID != id)   //If Node's book ID is not same as Admin's input, continue travel linked Node.
            {
                previousBookNode = BookNodePtr;
                BookNodePtr = BookNodePtr->next;
            }
            else                            //Else let the previous Node's next point to the next Node and delete current Node.
            {
                previousBookNode->next = BookNodePtr->next;
                delete BookNodePtr;
                break;
            }
        }
    }

    //If the pointer travel to the end of linked Node and cannot find the ID.
    //The system will show below output.
    if(BookNodePtr == nullptr)
    {
        cout<<endl;
        cout<<"\tBook ID is not in the list";
    }
    else
    {
        cout<<endl;
        cout<<"\tSuccessfully delete.";
    }
}

void admin::ViewStaffList()
{
    int number=0;

    cout<<"\t--- Staff List ---" <<endl;
    cout<<"\t------------------" <<endl;
    cout<<"\t" <<setw(4) <<"NO" <<setw(8) <<"ID" <<setw(20) <<"NAME" <<setw(5) <<"FINE" <<setw(16) <<"CURRENT BORROW" <<endl <<endl;

    //Assign pointer to Head, so the pointer can travel all the linked Node.
    //It will show all the Node's details until pointer pointing to null.
    StaffNodePtr = StaffHead;
    while(StaffNodePtr != nullptr)
    {
        cout<<"\t" <<setw(4) <<++number <<setw(8) <<StaffNodePtr->StaffID <<setw(20) <<StaffNodePtr->StaffName <<setw(5) <<StaffNodePtr->StaffFine <<setw(16) <<StaffNodePtr->StaffBorrow <<endl;
        StaffNodePtr = StaffNodePtr->next;
    }
}

void admin::ViewStudentList()
{
    int number=0;

    cout<<"\t--- Student List ---" <<endl;
    cout<<"\t--------------------" <<endl;
    cout<<"\t" <<setw(4) <<"NO" <<setw(8) <<"ID" <<setw(20) <<"NAME" <<setw(5) <<"FINE" <<setw(16) <<"CURRENT BORROW" <<endl <<endl;

    //Assign pointer to Head, so the pointer can travel all the linked Node.
    //It will show all the Node's details until pointer pointing to null.
    StudentNodePtr = StudentHead;
    while(StudentNodePtr != nullptr)
    {
        cout<<"\t" <<setw(4) <<++number <<setw(8) <<StudentNodePtr->StudentID <<setw(20) <<StudentNodePtr->StudentName <<setw(5) <<StudentNodePtr->StudentFine <<setw(16) <<StudentNodePtr->StudentBorrow <<endl;
        StudentNodePtr = StudentNodePtr->next;
    }
}

void admin::ViewBorrowerList()
{
    int number=0;

    cout<<"\t--- Borrower List ---" <<endl;
    cout<<"\t---------------------" <<endl;
    cout<<"\t" <<setw(4) <<"NO"<<setw(12) <<"BORROWER ID" <<setw(10) <<"BOOK ID" <<setw(14) <<"BORROW DATE" <<setw(14) <<"RETURN DATE" <<endl <<endl;

    //Assign pointer to Head, so the pointer can travel all the linked Node.
    //It will show all the Node's details until pointer pointing to null.
    BorrowNodePtr = BorrowHead;
    while(BorrowNodePtr != nullptr)
    {
        cout<<"\t" <<setw(4) <<++number <<setw(12) <<BorrowNodePtr->BorrowerID <<setw(10) <<BorrowNodePtr->BorrowBookID <<setw(14) <<BorrowNodePtr->BorrowDate <<setw(14) <<BorrowNodePtr->ReturnDate <<endl;
        BorrowNodePtr = BorrowNodePtr->next;
    }
}

void admin::FineCharge()
{
    int choice;

    cout<<"\t--- FINE CHARGE ---" <<endl;
    cout<<"\t-------------------" <<endl;
    cout<<"\t1. Late Return Book (RM 20)" <<endl;
    cout<<"\t2. Book Destroyed (RM 50)" <<endl <<endl;

    cout<<"\tEnter the choice : ";
    cin>>choice;

    switch(choice)
    {
        //go to FineChargeID() function by passing different amount as parameter.
        case 1: FineChargeID(20); break;
        case 2: FineChargeID(50); break;
        default : cout<<"\tInvalid Input Entered" <<endl;
                  cout<<"\tReturning to Menu Page" <<endl;
    }
}

void admin::FineChargeID(int PassFine)
{
    size_t CFound, DFound;  //size_t is an unsigned int data type.
    string id;

    fflush(stdin);
    cout<<endl;
    cout<<"\tEnter the ID : ";
    getline(cin, id);
    cout<<endl;

    CFound = id.find("C");  //CFound use to find "C" in ID, if there is no "C" in ID, the number will more than the ID's length.
    DFound = id.find("D");  //DFound use to find "D" in ID, if there is no "D" in ID, the number will more than the ID's length.

    if(CFound <= id.size()) //If CFound is smaller or equal to ID's length.
    {
        //Assign pointer to Head, so the pointer can travel all the linked Node.
        //Travel the linked Node, while the pointer is not pointing to null.
        StaffNodePtr = StaffHead;
        while(StaffNodePtr != nullptr)
        {
            //If Node's ID is same as Admin's input.
            //Add FINE into the Node.
            if(StaffNodePtr->StaffID == id)
            {
                StaffNodePtr->StaffFine += PassFine;
                cout<<"\tFINE RM" <<PassFine <<" added into ID : " <<StaffNodePtr->StaffID <<endl;
                break;
            }
            StaffNodePtr = StaffNodePtr->next;
        }

        //If the pointer travel to the end of linked Node and cannot find the ID.
        //The system will show below output.
        if(StaffNodePtr == nullptr)
        {
            cout<<"\tID NOT FOUND!" <<endl;
            cout<<"\tFailed to FINE" <<endl;
        }
    }
    else if(DFound <= id.size())    //Else if DFound is smaller or equal to ID's length.
    {
        //Assign pointer to Head, so the pointer can travel all the linked Node.
        //Travel the linked Node, while the pointer is not pointing to null.
        StudentNodePtr = StudentHead;
        while(StudentNodePtr != nullptr)
        {
            //If Node's ID is same as Admin's input.
            //Add FINE into the Node.
            if(StudentNodePtr->StudentID == id)
            {
                StudentNodePtr->StudentFine += PassFine;
                cout<<"\tFINE RM" <<PassFine <<" added into ID : " <<StudentNodePtr->StudentID <<endl;
                break;
            }
            StudentNodePtr = StudentNodePtr->next;
        }

        //If the pointer travel to the end of linked Node and cannot find the ID.
        //The system will show below output.
        if(StudentNodePtr == nullptr)
        {
            cout<<"\tID NOT FOUND!" <<endl;
            cout<<"\tFailed to FINE" <<endl;
        }
    }
    else    //Else show below output.
    {
        cout<<"\tID NOT FOUND!" <<endl;
        cout<<"\tFailed to FINE" <<endl;
    }
}

void admin::ClearFine()
{
    size_t CFound, DFound;  //size_t is an unsigned int data type.
    string id;

    cout<<"\t--- CLEAR FINE ---" <<endl;
    cout<<"\tEnter the ID to Clear FINE : ";
    getline(cin, id);
    cout<<endl;

    CFound = id.find("C");  //CFound use to find "C" in ID, if there is no "C" in ID, the number will more than the ID's length.
    DFound = id.find("D");  //DFound use to find "D" in ID, if there is no "D" in ID, the number will more than the ID's length.

    if(CFound <= id.size()) //If CFound is smaller or equal to ID's length.
    {
        //Assign pointer to Head, so the pointer can travel all the linked Node.
        //Travel the linked Node, while the pointer is not pointing to null.
        StaffNodePtr = StaffHead;
        while(StaffNodePtr != nullptr)
        {
            //If Node's ID is same as Admin's input.
            //Clear Node's FINE.
            if(StaffNodePtr->StaffID == id)
            {
                StaffNodePtr->StaffFine = 0;
                cout<<"\tFINE Cleared" <<endl;
                break;
            }
            StaffNodePtr = StaffNodePtr->next;
        }

        //If the pointer travel to the end of linked Node and cannot find the ID.
        //The system will show below output.
        if(StaffNodePtr == nullptr)
        {
            cout<<"\tID NOT FOUND!" <<endl;
            cout<<"\tFailed to clear FINE" <<endl;
        }
    }
    else if(DFound <= id.size())    //If DFound is smaller or equal to ID's length.
    {
        //Assign pointer to Head, so the pointer can travel all the linked Node.
        //Travel the linked Node, while the pointer is not pointing to null.
        StudentNodePtr = StudentHead;
        while(StudentNodePtr != nullptr)
        {
            //If Node's ID is same as Admin's input.
            //Clear Node's FINE.
            if(StudentNodePtr->StudentID == id)
            {
                StudentNodePtr->StudentFine = 0;
                cout<<"\tFINE Cleared" <<endl;
                break;
            }
            StudentNodePtr = StudentNodePtr->next;
        }

        //If the pointer travel to the end of linked Node and cannot find the ID.
        //The system will show below output.
        if(StudentNodePtr == nullptr)
        {
            cout<<"\tID NOT FOUND!" <<endl;
            cout<<"\tFailed to clear FINE" <<endl;
        }
    }
    else    //Else show below output.
    {
        cout<<"\tID NOT FOUND!" <<endl;
        cout<<"\tFailed to clear FINE" <<endl;
    }
}

void admin::AdminFile()
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

    fwrite.open("StudentRecord.txt");   //Use object to open the file for write data into "StudentRecord.txt" from linked Node.
    if(StudentHead != nullptr)          //If Head is not pointing to null.
    {
        //Assign pointer to Head, so the pointer can travel all the linked Node.
        //It will write data into "StaffRecord.txt" until pointer pointing to null.
        StudentNodePtr = StudentHead;
        while(StudentNodePtr != nullptr)
        {
            fwrite<<setw(8) <<StudentNodePtr->StudentID <<setw(20) <<StudentNodePtr->StudentName <<setw(20) <<StudentNodePtr->StudentPassword <<setw(9) <<StudentNodePtr->StudentFine <<setw(3) <<StudentNodePtr->StudentBorrow <<endl;
            StudentNodePtr = StudentNodePtr->next;
        }
        fwrite.close(); //Close "StudentRecord.txt" file.
    }
}

#endif
