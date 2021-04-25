//
// Created by Erick on 4/24/2021.
//

#include "miniGit.h"
#include <fstream>
#include "main.cpp"

miniGit::miniGit() {
    head = nullptr;
    fs::remove_all(".minigit");
    fs::create_directory(".minigit");
}

//TODO: destroy all nodes so that there are no memory leaks
miniGit::~miniGit() {

}

void miniGit::initialize() {
    head = new doublyNode;
    head->commitNumber = 0;
    head->head = new singlyNode;
    currentCommit = 0;
}

void miniGit::commit() {

}

//TODO: check to see if a file has changed to update file version number
int miniGit::add_file(string fileName) {
    if(!fs::exists(fileName)){
        return -1;
    }
    doublyNode *commit = get_current_commit();
    singlyNode *file = commit->head;
    if(file->fileName==fileName){
        return -2;
    }
    while(file->next!= nullptr){
        if(file->next->fileName==fileName){
            return -2;
        }
        file = file->next;
    }
    file->next = new singlyNode;
    file = file->next;
    if(commit==head){
        file->fileVersion = "00";
    }
    file->fileName = fileName;
    copy_file(fileName, fileName+file->fileVersion);
}

void miniGit::remove_file() // Aria workin on
{
    doublyNode* ches = get_current_commit();
    singlyNode* temph = ches -> head;

    string file = " ";
    cout << "Enter the name for the soon to be removed file" << endl; //Prompt user to enter a file name.
    cin >> file;

    while(temph -> next != NULL)
    {
        singlyNode* temp = temph -> next;
        if(temph -> next -> fileName == file) //Check the SLL for whether the file exists in the current version of the repository.
        {
            temp = temph -> next -> next;
            delete temph -> next; // delete node
            temph->next = temp;
            break;
        }
        temph = temph -> next;
    }
}

void miniGit::check_out() {

}

miniGit::doublyNode* miniGit::get_current_commit() {
    doublyNode *commit = head;
    while(commit != nullptr){
        if(commit->commitNumber==currentCommit){
            break;
        }
        commit = commit->next;
    }
    return commit;
}

bool isFileUpdated(string previousFile, string newFile){
    string temp1,temp2;
    ifstream original(previousFile);
    ifstream newVersion(newFile);
    if(!original||!newVersion){
        return false;
    }
    while(getline(newVersion,temp2)||getline(original,temp1)){
        if(temp1!=temp2){
            return true;
        }
    }
    return false;
}

void miniGit::copy_file(string originalName, string copyName) {
    ofstream copy(".minigit\\"+copyName);
    if(!copy){
        cout<<"Failed to open file."<<endl;
        return;
    }
    ifstream original(originalName);
    if(!original){
        cout<<"Failed to open file."<<endl;
        return;
    }
    string line;
    while(getline(original,line)){
        copy << line;
    }
    copy.close();
    original.close();
}

