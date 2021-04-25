//
// Created by Erick on 4/24/2021.
//

#include "miniGit.h"
#include <fstream>
#include "main.cpp"

bool isFileUpdated(string previousFile, string newFile){
    string temp1,temp2;
    ifstream original(previousFile);
    ifstream newVersion(newFile);
    if(!original||!newVersion){
        return false;
    }
    while(getline(newVersion,temp2)&&getline(original,temp1)){
        if(temp1!=temp2){
            return true;
        }
    }
    return false;
}

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
    if(!fs::exists(fileName)){ //Checks to see if the file exists
        return -1;
    }
    doublyNode *commit = get_current_commit();
    singlyNode *file = commit->head;
    if(file->fileName==fileName){ //Checks the head's name
        return -2;
    }
    while(file->next!= nullptr){ //Checks all other names in the list
        if(file->next->fileName==fileName){
            return -2;
        }
        file = file->next;
    }
    file->next = new singlyNode; //Creates new node with the new information
    file = file->next; //Moves to the new node
    file->fileName = fileName;
    if(commit==head){ //Checks to see if the commit is the initial commit
        file->fileVersion = "00";
    } else{
        singlyNode *prev = commit->previous->head;
        while(prev!= nullptr){ //Looks for the file in the previous commit
            prev = (prev->fileName==file->fileName)?prev: prev->next;
        }
        if(isFileUpdated(prev->fileName+prev->fileVersion,file->fileName)){ //Checks to see if the file is different
            int version = stoi(file->fileVersion);
            version++; //Updates the version
            if(file->fileVersion[0]=='0'){
                file->fileVersion = "0"+to_string(version);
            } else{
                file->fileVersion = to_string(version);
            }
        }
    }
    copy_file(fileName, fileName+file->fileVersion,false); //copys the file to .minigit
    return 0;
}

void miniGit::remove_file(string file) // Aria working on
{
    doublyNode* ches = get_current_commit();
    singlyNode* temph = ches -> head;

    if(head == NULL)
    {
        return;
    }
    else
    {
        while (temph->next != NULL)
        {
            singlyNode *temp = temph->next;
            if (temph->next->fileName == file) //Check the SLL for whether the file exists in the current version of the repository.
            {
                temp = temph->next->next;
                delete temph->next; // delete node
                temph->next = temp;
                break;
            }
            temph = temph->next;
        }
        return;
    }
}

void miniGit::check_out(int comnum)
{
    doublyNode* ches = get_current_commit();
    singlyNode* temph = ches -> head;

    while(ches != NULL)
    {
        if(comnum = ches -> commitNumber)
        {
            singlyNode *temp = temph->next;
            if (temph->next->fileName == file) //Check the SLL for whether the file exists in the current version of the repository.
            {

            }
            temph = temph->next;
        }
    }
    return;
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

void miniGit::copy_file(string originalName, string copyName, bool dir) { //Dir bool is to know if the copying is occurring from the .minigit folder to the directory (true)
    if(dir){
        string temp = originalName;
        originalName = ".minigit\\"+copyName;
        copyName = temp;
    } else{
        copyName = ".minigit\\"+copyName;
    }
    ofstream copy(copyName);
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

