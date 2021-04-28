#include <iostream>
#include <string>
#include "miniGit.h"
using namespace std;



int main()
{
    int option;
    //string inputLine;

    miniGit *git = nullptr;
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

        cout << "Enter a number 1-6: " << endl;
        //getline(cin, inputLine);
        cin >> option;
        //option = stoi(inputLine);

//        if (inputLine.length() != 1 || inputLine[0] < '0' || inputLine[1] > '6') //TODO: MAKE IT STOP PRINTING INVALID WHEN IT'S NOT INVALID
//        {
//            // (inputLine.length() != 1 || inputLine[0] < '0' || inputLine[1] > '6')
//            cout << "Invalid option : " << inputLine << endl;
//            //cout << "Invalid option : " << option << endl;
//        }
        if(option == 1 || option == 2 || option == 3 || option == 4 || option == 5 || option == 6)
        {
            switch (option)
            {
                case 1:
                    if (git)
                    {
                        delete git;
                    }
                    git = new miniGit;
                    git->initialize();
                    cout << "Created New Repository." << endl;

                    break;
                case 2:
                    if (!git)
                    {
                        cout << "Repository not initialized" << endl;
                        continue;
                    }
                    cout << "Enter file name you want to add: " << endl;
                    cin >> fileName;

                    exist = git->add_file(fileName);
                    while (exist == -1 || exist == -2)
                    {
                        if (exist == -1)
                        {
                            cout << "The file you are trying to add does not exist. Please enter another name" << endl;
                        }
                        else
                        {
                            cout << "File already exists, please enter new name" << endl;
                        }
                        cout << "Enter file name: " << endl;
                        cin >> fileName;
                        exist = git->add_file(fileName);
                    }

                    cout << "File has been successfully added." << endl;
                    cout << "DEBUG, FILES IN COMMIT: " << endl;
                    git->printFilesInCommit(); //DEBUG
                    break;
                case 3:
                    if (!git)
                    {
                        cout << "Repository not initialized" << endl;
                        continue;
                    }
                    cout << "Enter file name you want to remove: " << endl;
                    cin >> file;

                    git->remove_file(file);
                    cout << "Your chosen file has been removed." << endl;
                    cout << "DEBUG, FILES IN COMMIT: " << endl;
                    git->printFilesInCommit(); //DEBUG
                    break;
                case 4:
                    if (!git)
                    {
                        cout << "Repository not initialized" << endl;
                        continue;
                    }
                    git->commit();
                    cout << "Commit function was implemented." << endl;
                    cout << "DEBUG, FILES IN COMMIT: " << endl;
                    git->printFilesInCommit(); //DEBUG
                    break;
                case 5:
                    if (!git)
                    {
                        cout << "Repository not initialized" << endl;
                        continue;
                    }
                    cout
                            << "Before you enter a commit number be warned: you will loose your local changes if you checkout a different version before making a commit with your current local changes."
                            << endl;
                    cout << "Enter commit number: " << endl;
                    cin >> comNum;

                    git->check_out(comNum);
                    cout << "Successfully checked out." << endl;
                    break;
                case 6:
                {
                    if (git)
                    {
                        delete git;
                    }
                    quit = true;
                    break;
                }
            }
        }
        else
        {
            cout << "Invalid option : " << option << endl;
        }
    }
    return 0;
}