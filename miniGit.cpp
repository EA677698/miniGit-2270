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
    file->fileName = fileName+file->fileVersion;
    copy_file(fileName, file->fileName);
}

void miniGit::remove_file() {

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

