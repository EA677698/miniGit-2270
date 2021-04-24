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

void miniGit::copy_file(string fileName) {
}

