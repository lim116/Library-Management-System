#ifndef BOOK_H
#define BOOK_H
#include <iostream>
#include <iomanip>
#include <string>
#include <ctime>
#include <fstream>

using namespace std;

class book
{
protected:
    int BookNo;
    struct BookNode
    {
        string BookID, BookName, BookAuthor, BookStatus = "O";
        BookNode *next;
    } *BookHead, *newBookNode, *BookNodePtr, *previousBookNode;

    struct BorrowBookNode
    {
        string BorrowerID, BorrowBookID, BorrowDate, ReturnDate;
        BorrowBookNode *next;
    } *BorrowHead, *newBorrowNode, *BorrowNodePtr;
public:
    book();             //Constructor use to retrieve all the data in file.
    ~book();            //Destructor use to delete all the node in the memory.
    void SearchBook();  //This function allow user to choose option of search book.
    void SearchBookID();    //This function allow user to search book by ID.
    void SearchBookName();  //This function allow user to search book by name.
    void ViewBookList();    //This function allow user to view all the book.
    bool BorrowBook(string PassID); //This function will let user borrow book by enter book ID.
    bool ReturnBook(string PassID); //This function will let user return book by enter book ID.
    void BookFile();    //This function use to write all the data into file after every option.
};

book::book()
{
    //Initialize value to variables & pointers.
    BookNo = 19000;
    BookHead = nullptr;
    newBookNode = nullptr;
    previousBookNode = nullptr;
    BorrowHead = nullptr;
    newBorrowNode = nullptr;
    BorrowNodePtr = nullptr;

    ifstream fread;                 //Declare file object.
    fread.open("BookRecord.txt");   //Use object to open the file for retrieve data from "BookRecord.txt".
    if(!fread.eof())
    {
        newBookNode = new BookNode; //Create a new Staff Node in memory & retrieve data from file into Node's variables.
        while(fread>>newBookNode->BookID >>newBookNode->BookName >>newBookNode->BookAuthor >>newBookNode->BookStatus)
        {
            newBookNode->next = nullptr;
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
            newBookNode = new BookNode;
        }
        fread.close();  //Close "BookRecord.txt" file.
    }

    fread.open("BorrowerRecord.txt");   //Use object to open the file for retrieve data from "BorrowerRecord.txt".
    if(!fread.eof())
    {
        newBorrowNode = new BorrowBookNode; //Create a new Staff Node in memory & retrieve data from file into Node's variables.
        while(fread>>newBorrowNode->BorrowerID >>newBorrowNode->BorrowBookID >>newBorrowNode->BorrowDate >>newBorrowNode->ReturnDate)
        {
            newBorrowNode->next = nullptr;
            if(BorrowHead == nullptr)
            {
                BorrowHead = newBorrowNode;
            }
            else
            {
                BorrowNodePtr = BorrowHead;
                while(BorrowNodePtr->next != nullptr)
                {
                    BorrowNodePtr = BorrowNodePtr->next;
                }
                BorrowNodePtr->next = newBorrowNode;
            }
            newBorrowNode = new BorrowBookNode;
        }
        fread.close();  //Close "BorrowerRecord.txt" file.
    }

    fread.open("BookNo.txt");   //Use object to open the file for retrieve data from "BorrowerRecord.txt".
    if(!fread.eof())
    {
        fread>>BookNo;
    }
    fread.close();  //Close "BookNo.txt" file.
}

book::~book()
{
    //Delete all StaffNode from memory by travel all Node.
    while(BookHead != nullptr)
    {
        BookNodePtr = BookHead;
        BookHead = BookHead->next;
        delete BookNodePtr;
    }

    //Delete all StaffNode from memory by travel all Node.
    while(BorrowHead != nullptr)
    {
        BorrowNodePtr = BorrowHead;
        BorrowHead = BorrowHead->next;
        delete BorrowNodePtr;
    }
}

void book::SearchBook()
{
    int choice;

    cout<<"\t--- Search Book ---" <<endl;
    cout<<"\t-------------------" <<endl;
    cout<<"\t1. Search by Book ID" <<endl;
    cout<<"\t2. Search by Book Name" <<endl<<endl;

    cout<<"\tEnter the choice : ";
    cin>>choice;

    system("CLS");
    fflush(stdin);
    cout<<endl;
    switch(choice)
    {
        case 1: SearchBookID(); break;
        case 2: SearchBookName(); break;
        default: cout<<"\tInvalid input entered!" <<endl;
                 cout<<"\tReturning to Menu Page...";
    }
}

void book::SearchBookID()
{
    int number = 0;
    string id;

    cout<<"\t--- Search Book ID ---" <<endl;
    cout<<"\t----------------------" <<endl;
    cout<<"\tEnter Book ID: ";
    getline(cin, id);
    cout<<endl;


    //Assign pointer to Head, so the pointer can travel all the linked Node.
    //It will show all the Node's details until pointer pointing to null.
    BookNodePtr = BookHead;
    while(BookNodePtr != nullptr)
    {
        //If Node's ID is same as user's input, show the details.
        if(BookNodePtr->BookID == id)
        {
            cout<<"\t" <<setw(4) <<"NO" <<setw(8) <<"ID" <<setw(20) <<"NAME" <<setw(20) <<"AUTHOR" <<setw(9) <<"STATUS" <<endl <<endl;
            cout<<"\t" <<setw(4) <<++number <<setw(8) <<BookNodePtr->BookID <<setw(20) <<BookNodePtr->BookName <<setw(20) <<BookNodePtr->BookAuthor <<setw(9) <<BookNodePtr->BookStatus <<endl;
            break;
        }
        BookNodePtr = BookNodePtr->next;
    }

    //If the pointer travel to the end of linked Node and cannot find the ID.
    //The system will show below output.
    if(BookNodePtr == nullptr)
    {
        cout<<"\tBook is not found";
    }
}

void book::SearchBookName()
{
    int POC=0 , number=0;   //POC is position of character which use to indicate index of string.
    size_t NFound, SFound;  //size_t is an unsigned int data type.
    string name;

    cout<<"\t--- Search Book Name ---" <<endl;
    cout<<"\t------------------------" <<endl;
    cout<<"\tEnter Book Name: ";
    getline(cin, name);

    while(name[POC])    //Change name to uppercase.
    {
        name[POC] = toupper(name[POC]);
        POC++;
    }

    SFound = name.find(" ");        //If there is no " " in name, the number will more than the name's length.
    while(SFound <= name.size())    //While SFound is smaller or equal to book's name length, change " " to "_".
    {
        name.replace(name.find(" "), 1, "_");
        SFound = name.find(" ");
    }

    cout<<endl;
    cout<<"\t--- Search Result of " <<name <<" ---" <<endl;
    cout<<"\t" <<setw(4) <<"NO" <<setw(8) <<"ID" <<setw(20) <<"NAME" <<setw(20) <<"AUTHOR" <<setw(9) <<"STATUS"<<endl <<endl;

    //Assign pointer to Head, so the pointer can travel all the linked Node.
    //It will show all the Node's details until pointer pointing to null.
    BookNodePtr = BookHead;
    while(BookNodePtr != nullptr)
    {
        NFound = BookNodePtr->BookName.find(name);  //If there is no similar string in Node's book name, the number will more than the Node's book name length.
        if(NFound <= BookNodePtr->BookName.size())  //While SFound is smaller or equal to book's name length, show the book details.
        {
            cout<<"\t" <<setw(4) <<++number <<setw(8) <<BookNodePtr->BookID <<setw(20) <<BookNodePtr->BookName <<setw(20) <<BookNodePtr->BookAuthor <<setw(9) <<BookNodePtr->BookStatus <<endl;
        }
        BookNodePtr = BookNodePtr->next;
    }
}

void book::ViewBookList()
{
    int number=0;

    cout<<"\t--- Book List ---" <<endl;
    cout<<"\t-----------------" <<endl;
    cout<<"\t" <<setw(4) <<"NO" <<setw(8) <<"ID" <<setw(20) <<"NAME" <<setw(20) <<"AUTHOR" <<setw(9) <<"STATUS" <<endl <<endl;

    //Assign pointer to Head, so the pointer can travel all the linked Node.
    //It will show all the Node's details until pointer pointing to null.
    BookNodePtr = BookHead;
    while(BookNodePtr != nullptr)
    {
        cout<<"\t" <<setw(4) <<++number <<setw(8) <<BookNodePtr->BookID <<setw(20) <<BookNodePtr->BookName <<setw(20) <<BookNodePtr->BookAuthor <<setw(9) <<BookNodePtr->BookStatus <<endl;
        BookNodePtr = BookNodePtr->next;
    }
}

bool book::BorrowBook(string PassID)
{
    bool status = true;
    string id;

    cout<<"\t--- Borrow Book ---" <<endl;
    cout<<"\t-------------------" <<endl;
    cout<<"\tEnter Book ID: ";
    getline(cin, id);
    cout<<endl;

    //Assign pointer to Head, so the pointer can travel all the linked Node.
    //It will show all the Node's details until pointer pointing to null.
    BookNodePtr = BookHead;
    while(BookNodePtr != nullptr)
    {
        //If the Node's book ID is same as user input ID & book status is equal to "O".
        //The system will show below output.
        if(BookNodePtr->BookID == id && BookNodePtr->BookStatus == "O")
        {
            time_t t = time(0);
            tm *now = localtime(&t);
            string date = to_string(now->tm_year + 1900) + "-" + to_string(now->tm_mon + 1) + "-" + to_string(now->tm_mday);

            newBorrowNode = new BorrowBookNode;
            newBorrowNode->BorrowerID = PassID;
            newBorrowNode->BorrowBookID = BookNodePtr->BookID;
            newBorrowNode->BorrowDate = date;
            newBorrowNode->ReturnDate = "-";
            newBorrowNode->next = nullptr;

            cout<<"\t--- Borrow Details ---" <<endl;
            cout<<"\t" <<setw(12) <<"Borrower ID" <<setw(10) <<"Book ID" <<setw(14) <<"Borrow Date" <<setw(14) <<"Return Date" <<endl;
            cout<<"\t" <<setw(12) <<newBorrowNode->BorrowerID <<setw(10) <<newBorrowNode->BorrowBookID <<setw(14) <<newBorrowNode->BorrowDate <<setw(14) <<newBorrowNode->ReturnDate <<endl;

            BookNodePtr->BookStatus = "X";

            if(BorrowHead == nullptr)
            {
                BorrowHead = newBorrowNode;
            }
            else
            {
                BorrowNodePtr = BorrowHead;
                while(BorrowNodePtr->next != nullptr)
                {
                    BorrowNodePtr = BorrowNodePtr->next;
                }
                BorrowNodePtr->next = newBorrowNode;
            }
            break;
        }
        //If the Node's book ID is same as user input ID, but book status is equal to "X".
        //The system will show below output.
        else if(BookNodePtr->BookID == id && BookNodePtr->BookStatus == "X")
        {
            status = false;
            cout<<"\tCurrently the Book is not available";
            break;
        }
        BookNodePtr = BookNodePtr->next;
    }

    //If the pointer travel to the end of linked Node and cannot find the ID.
    //The system will show below output.
    if(BookNodePtr == nullptr)
    {
        status = false;
        cout<<"\tBook is not found";
    }

    return status;
}

bool book::ReturnBook(string PassID)
{
    bool status = true;
    string id;

    cout<<"\t--- Return Book ---" <<endl;
    cout<<"\t-------------------" <<endl;
    cout<<"\tEnter the Book ID to return : ";
    getline(cin, id);
    cout<<endl;

    //Assign pointer to Head, so the pointer can travel all the linked Node.
    //It will show all the Node's details until pointer pointing to null.
    BorrowNodePtr = BorrowHead;
    while(BorrowNodePtr != nullptr)
    {
        //If Node's book ID same as user input book ID, borrower ID same as user ID & return date is equal to "-".
        //The system will show below output.
        if(BorrowNodePtr->BorrowBookID == id && BorrowNodePtr->BorrowerID == PassID && BorrowNodePtr->ReturnDate == "-")
        {
            time_t t = time(0);
            tm *now = localtime(&t);
            string date = to_string(now->tm_year + 1900) + "-" + to_string(now->tm_mon + 1) + "-" + to_string(now->tm_mday);

            BorrowNodePtr->ReturnDate = date;

            cout<<"\t" <<setw(12) <<"Borrower ID" <<setw(10) <<"Book ID" <<setw(14) <<"Borrow Date" <<setw(14) <<"Return Date" <<endl;
            cout<<"\t" <<setw(12) <<BorrowNodePtr->BorrowerID <<setw(10) <<BorrowNodePtr->BorrowBookID <<setw(14) <<BorrowNodePtr->BorrowDate <<setw(14) <<BorrowNodePtr->ReturnDate <<endl <<endl;

            cout<<"\tBook return successfully";

            //Assign pointer to Head, so the pointer can travel all the linked Node.
            //Travel the linked Node, while the pointer is not pointing to null.
            BookNodePtr = BookHead;
            while(BookNodePtr != nullptr)
            {
                if(BookNodePtr->BookID == id)
                {
                    BookNodePtr->BookStatus = "O";
                    break;
                }
                BookNodePtr = BookNodePtr->next;
            }
            break;
        }
        BorrowNodePtr = BorrowNodePtr->next;
    }

    //If the pointer travel to the end of linked Node and cannot find the ID.
    //The system will show below output.
    if(BorrowNodePtr == nullptr)
    {
        cout<<"\tFailed to return book";
        status = false;
    }

    return status;
}

void book::BookFile()
{
    ofstream fwrite;            //Declare file object.
    fwrite.open("BookNo.txt");  //Use object to open the file for write data into "BookNo.txt".
    {
        fwrite<<BookNo;
    }
    fwrite.close(); //Close "BookNo.txt" file.

    fwrite.open("BookRecord.txt");  //Use object to open the file for write data into "BookRecord.txt" from linked Node.
    if(BookHead != nullptr)         //If Head is not pointing to null.
    {
        //Assign pointer to Head, so the pointer can travel all the linked Node.
        //It will write data into "StaffRecord.txt" until pointer pointing to null.
        BookNodePtr = BookHead;
        while(BookNodePtr != nullptr)
        {
            fwrite<<setw(8) <<BookNodePtr->BookID <<setw(20) <<BookNodePtr->BookName <<setw(20) <<BookNodePtr->BookAuthor <<setw(9) <<BookNodePtr->BookStatus <<endl;
            BookNodePtr = BookNodePtr->next;
        }
        fwrite.close(); //Close "BookRecord.txt" file.
    }

    fwrite.open("BorrowerRecord.txt");  //Use object to open the file for write data into "BorrowerRecord.txt" from linked Node.
    if(BorrowHead != nullptr)           //If Head is not pointing to null.
    {
        //Assign pointer to Head, so the pointer can travel all the linked Node.
        //It will write data into "StaffRecord.txt" until pointer pointing to null.
        BorrowNodePtr = BorrowHead;
        while(BorrowNodePtr != nullptr)
        {
            fwrite<<setw(12) <<BorrowNodePtr->BorrowerID <<setw(10) <<BorrowNodePtr->BorrowBookID <<setw(14) <<BorrowNodePtr->BorrowDate <<setw(14) <<BorrowNodePtr->ReturnDate <<endl;
            BorrowNodePtr = BorrowNodePtr->next;
        }
        fwrite.close(); //Close "BorrowerRecord.txt" file.
    }
}

#endif
