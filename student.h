#ifndef STUDENT_H
#define STUDENT_H
#include <iostream>
#include <string>
#include <fstream>
#include "book.h"

using namespace std;

class student : public book
{
private:
    int StudentNo;
    struct StudentNode
    {
        int StudentFine=0, StudentBorrow=0;
        string StudentID, StudentName, StudentPassword;
        StudentNode *next;
    } *StudentHead, *newStudentNode, *StudentNodePtr;
public:
    student();              //Constructor use to retrieve all the data in file.
    ~student();             //Destructor use to delete all the node in the memory.
    void StudentRegister(); //This function allow Student to register account.
    void StudentCompare(string PassID, string password);    //This function will compare ID & Password.
    void StudentSelectOption(string PassID);                //This function will let Student choose option.
    void StudentViewProfileBorrowedBook(string PassID);     //This function will let Student view their profile & borrow history.
    void StudentBorrowBook(string PassID);  //This function will let Student borrow book.
    void StudentReturnBook(string PassID);  //This function will let Student return book.
    void StudentFile(); //This function use to write all the data into file after every option.
};

student::student()
{
    //Initialize value to variables & pointers.
    StudentNo = 19000;
    StudentHead = nullptr;
    newStudentNode = nullptr;
    StudentNodePtr = nullptr;

    ifstream fread;                     //Declare file object.
    fread.open("StudentRecord.txt");    //Use object to open the file for retrieve data from "StaffRecord.txt".
    if(!fread.eof())
    {
        newStudentNode = new StudentNode;   //Create a new Staff Node in memory & retrieve data from file into Node's variables.
        while(fread>>newStudentNode->StudentID >>newStudentNode->StudentName >>newStudentNode->StudentPassword >>newStudentNode->StudentFine >>newStudentNode->StudentBorrow)
        {
            StudentNo++;
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

student::~student()
{
    //Delete all StaffNode from memory by travel all Node.
    while(StudentHead != nullptr)
    {
        StudentNodePtr = StudentHead;
        StudentHead = StudentHead->next;
        delete StudentNodePtr;
    }
}

void student::StudentRegister()
{
    int POC;        //POC is position of character which use to indicate index of string.
    size_t SFound;  //SFound use to find " " in name & author.
    newStudentNode = new StudentNode;   //Create a new Node in memory.
    newStudentNode->StudentID = "D" + to_string(StudentNo);
    StudentNo++;

    cout<<"\t--- Student Registration ---" <<endl;
    cout<<"\t----------------------------" <<endl;
    cout<<"\tEnter your name     : ";
    getline(cin, newStudentNode->StudentName);
    cout<<"\tEnter your password : ";
    getline(cin, newStudentNode->StudentPassword);
    newStudentNode->next = nullptr;

    POC=0;
    while(newStudentNode->StudentName[POC]) //Change name to uppercase.
    {
        newStudentNode->StudentName[POC] = toupper(newStudentNode->StudentName[POC]);
        POC++;
    }

    SFound = newStudentNode->StudentName.find(" ");     //If there is no " " in name, the number will more than the name's length.
    while(SFound <= newStudentNode->StudentName.size()) //While SFound is smaller or equal to book's name length, change " " to "_".
    {
        newStudentNode->StudentName.replace(newStudentNode->StudentName.find(" "), 1, "_");
        SFound = newStudentNode->StudentName.find(" ");
    }

    //If Head is pointing to null, assign Head pointer to the first new Node.
    //Then the new Node created will be assigned to every Node's next.
    //So, every Node created is linked together.
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

    ofstream fwrite;                    //Declare file object.
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

    cout<<endl;
    cout<<"\tUse this ID to login : " <<newStudentNode->StudentID;
}

void student::StudentCompare(string PassID, string password)
{
    StudentNode *StudentCompareNodePtr;

    StudentCompareNodePtr = StudentHead;    //Assign pointer to Head, so the pointer can travel all the linked Node.
    while(StudentCompareNodePtr != nullptr) //Travel the linked Node, while the pointer is not pointing to null.
    {
        //If ID and Password is same, go to Staff's menu page.
        if(StudentCompareNodePtr->StudentID == PassID && StudentCompareNodePtr->StudentPassword == password)
        {
            StudentSelectOption(PassID);
            break;
        }
        StudentCompareNodePtr = StudentCompareNodePtr->next;
    }

    //If the pointer travel to the end of linked Node and cannot find the ID.
    //The system will show below output.
    if(StudentCompareNodePtr == nullptr)
    {
        cout<<endl;
        cout<<"\tWrong ID and Password!";
    }
}

void student::StudentSelectOption(string PassID)
{
    int choice;

    do
    {
        system("CLS");
        cout<<endl;
        cout<<"\t--- STUDENT ---" <<endl;
        cout<<"\t---------------" <<endl;
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
            case 1: StudentViewProfileBorrowedBook(PassID); break;
            case 2: ViewBookList(); break;
            case 3: SearchBook(); break;
            case 4: StudentBorrowBook(PassID); break;
            case 5: StudentReturnBook(PassID); break;
            case 6: cout<<"\tLogging out...";
        }
        StudentFile();  //Go to StudentFile() function after every option.
        cout<<endl <<endl <<"\t";
        system("pause");
    }while(choice != 6);
}

void student::StudentViewProfileBorrowedBook(string PassID)
{
    int number=0;

    cout<<"\t--- MY PROFILE ---" <<endl <<endl;

    //Assign pointer to Head, so the pointer can travel all the linked Node.
    //It will show all the Node's details until pointer pointing to null.
    StudentNodePtr = StudentHead;
    while(StudentNodePtr != nullptr)
    {
        //If Node's ID is same as user ID, show all the details.
        if(StudentNodePtr->StudentID == PassID)
        {
            cout<<"\tID : " <<StudentNodePtr->StudentID <<"\t\tNAME : " <<StudentNodePtr->StudentName <<endl <<endl;
            cout<<"\tCurrent Borrow : " <<StudentNodePtr->StudentBorrow <<"\t\tFINE : " <<StudentNodePtr->StudentFine <<endl <<endl;

            //If user's FINE is not equal to "0".
            //The system will show below output.
            if(StudentNodePtr->StudentFine != 0)
            {
                cout<<"\t-------------------------------------" <<endl;
                cout<<"\tPlease CLEAR FINE to Admin at counter" <<endl;
                cout<<"\t-------------------------------------" <<endl;
            }
            break;
        }
        StudentNodePtr = StudentNodePtr->next;
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

void student::StudentBorrowBook(string PassID)
{
    //Assign pointer to Head, so the pointer can travel all the linked Node.
    //Travel the linked Node, while the pointer is not pointing to null.
    StudentNodePtr = StudentHead;
    while(StudentNodePtr != nullptr)
    {
        if(StudentNodePtr->StudentID == PassID)
        {
            break;
        }
        StudentNodePtr = StudentNodePtr->next;
    }

    //If user's current borrow is less than "3" and FINE is equal to "0".
    //Go to BorrowBook() function.
    if(StudentNodePtr->StudentBorrow < 3 && StudentNodePtr->StudentFine == 0)
    {
        //If BorrowBook() function return true, user's current borrow+1.
        if(BorrowBook(PassID))
        {
            StudentNodePtr->StudentBorrow++;
        }
    }
    //If user's current borrow is equal to 3.
    //The system will show below output.
    else if(StudentNodePtr->StudentBorrow == 3)
    {
        cout<<"\tYou cannot borrow more than 3 books.";
    }
    //If user's FINE is not equal to "0".
    //The system will show below output.
    else if(StudentNodePtr->StudentFine > 0)
    {
        cout<<"\tPlease clear the FINE to borrow book.";
    }
}

void student::StudentReturnBook(string PassID)
{
    //If ReturnBook() function return true.
    if(ReturnBook(PassID))
    {
        //Assign pointer to Head, so the pointer can travel all the linked Node.
        //Travel the linked Node, while the pointer is not pointing to null.
        StudentNodePtr = StudentHead;
        while(StudentNodePtr != nullptr)
        {
            if(StudentNodePtr->StudentID == PassID)
            {
                break;
            }
            StudentNodePtr = StudentNodePtr->next;
        }
        StudentNodePtr->StudentBorrow--;
    }
}

void student::StudentFile()
{
    BookFile(); //Call BookFile function from book.h.

    ofstream fwrite;                    //Declare file object.
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
        fwrite.close(); //Close "StaffRecord.txt" file.
    }
}

#endif
