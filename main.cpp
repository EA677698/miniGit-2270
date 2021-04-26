#include <iostream>
#include <string>
using namespace std;



int main()
{
    cout<<stoi("00")<<endl;
    std::cout << "Hello, World!" << std::endl;

    int option;
    string inputLine;

    bool quit = false;
    while (!quit)
    {
        cout << "======Main Menu======" << endl;
        cout << "1. Add File" << endl;
        cout << "2. Remove File" << endl;
        cout << "3. Commit Changes" << endl;
        cout << "4. Checkout" << endl;
        cout << "5. Quit" << endl;

        getline(cin, inputLine);

        if (inputLine.length() != 1 || inputLine[0] < '0' || inputLine[1] > '4')
        {
            cerr << "Invalid option : " << inputLine << endl;
            continue;
        }

        option = stoi(inputLine);
        switch (option)
        {
            case 1:
                cout << "Enter file name" << endl;
                string fileName;
                cin >> fileName;

                add_file(fileName);
                break;

            case 2:
                break;

            case 3:
                break;

            case 4:
                break;

            case 5:
            {
                quit = true;
            }
        }
    }
}