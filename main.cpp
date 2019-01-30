#include <iostream>
#include "interface.h"

using namespace std;

int main()
{
    int choice;

    do
    {
        interface *obj = new interface;
        system("CLS");
        cout<<endl;
        cout<<"\t--- Register or Login ---" <<endl;
        cout<<"\t1. Register Account" <<endl;
        cout<<"\t2. Login" <<endl;
        cout<<"\t3. Exit Program" <<endl <<endl;

        cout<<"\tEnter the choice : ";
        cin>>choice;

        switch(choice)
        {
            case 1: obj->RegisterAccount(); break;
            case 2: obj->Login(); break;
        }
        delete obj;
    }while(choice != 3);

    return 0;
}
