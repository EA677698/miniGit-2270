//
// Created by Erick on 4/24/2021.
//

#ifndef MINIGIT_MINIGIT_H
#define MINIGIT_MINIGIT_H
#include <string>
#include <filesystem>
namespace fs = std::filesystem;
using namespace std;

class miniGit {

public:

    struct singlyNode{
        std::string fileName;
        std::string fileVersion;
        singlyNode *next;
    };

    struct doublyNode{
        int commitNumber;
        singlyNode *head;
        doublyNode *previous;
        doublyNode *next;

    };

    doublyNode *head;

    miniGit();

    ~miniGit();

    void printFilesInCommit();

    void initialize();

    void commit();

    int add_file(string fileName);

    void remove_file(string);

    void check_out(int);

    void copy_file(string originalName, string copyName, bool dir);



private:
    int currentCommit;
    doublyNode* get_current_commit();


};


#endif //MINIGIT_MINIGIT_H
