#include <iostream>
#include <string>
#include "miniGit.h"
using namespace std;



int main()
{
    int option;
    string inputLine;

    miniGit git;
    string fileName = " ";
    int exist;
    string file = " ";
    int comNum = 0;

    bool quit = false;
    while (!quit)
    {
        cout << "======Main Menu======" << endl;
        cout << "1. Create Empty Repository" << endl;
        cout << "2. Add File" << endl;
        cout << "3. Remove File" << endl;
        cout << "4. Commit Changes" << endl;
        cout << "5. Checkout" << endl;
        cout << "6. Quit" << endl;

        getline(cin, inputLine);

        if (inputLine.length() != 1 || inputLine[0] < '0' || inputLine[1] > '6')
        {
            cerr << "Invalid option : " << inputLine << endl;
            continue;
        }

        option = stoi(inputLine);
         switch(option)
        {
            case 1:
                git.initialize();
                cout << "Created New Repository." << endl;

                break;
            case 2:
                cout << "Enter file name you want to add: " << endl;
                cin >> fileName;

                exist = git.add_file(fileName);
                while(exist == -1 || exist == -2)
                {
                    cout << "File already exists, please enter new name" << endl;
                    cout << "Enter file name: " << endl;
                    cin >> fileName;
                    exist = git.add_file(fileName);
                }

                cout << "File has been successfully added." << endl;
                break;
            case 3:
                cout << "Enter file name you want to remove: " << endl;
                cin >> file;

                git.remove_file(file);
                cout << "Your chosen file has been removed." << endl;
                break;
            case 4:
                git.commit();
                cout << "Commit function was implemented." << endl;
                break;
            case 5:
                cout << "Before you enter a commit number be warned: you will loose your local changes if you checkout a different version before making a commit with your current local changes." << endl;
                cout << "Enter commit number: " << endl;
                cin >> comNum;

                git.check_out(comNum);
                cout << "Successfully checked out." << endl;
                break;
            case 6:
            {
                quit = true;
                break;
            }
        }
    }
    return 0;
}