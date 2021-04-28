//
// Created by Erick on 4/24/2021.
//

#include "miniGit.h"
#include <fstream>
#include <iostream>

bool isFileUpdated(string previousFile, string newFile){ //TODO: FIX THE FUNCTION
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

//Works successfully
miniGit::miniGit() {
    head = nullptr;
}

//Works successfully
miniGit::~miniGit() {
    if(head->commitNumber==currentCommit){
        singlyNode *SSL = head->head;
        singlyNode *previous;
        while(SSL != nullptr){
            previous = SSL;
            SSL = SSL->next;
            delete previous;
        }
    } else{
        doublyNode *traverse = get_current_commit();
        while(traverse->previous != nullptr){
            traverse = traverse->previous;
            singlyNode *previous;
            if(traverse->next->head){
                singlyNode *SSL = traverse->next->head;
                while(SSL != nullptr){
                    previous = SSL;
                    SSL = SSL->next;
                    delete previous;
                }
            }
            delete traverse->next;
        }
    }
}

//Works successfully
void miniGit::initialize() {
    fs::remove_all(".minigit");
    fs::create_directory(".minigit");
    head = new doublyNode;
    head->commitNumber = 0;
    currentCommit = 0;
}

void miniGit::commit() { // WORKS SUCCESSFULLY
    singlyNode *traverse = get_current_commit()->head;
    while(traverse!= nullptr){
        ifstream temp(".minigit/"+traverse->fileName+traverse->fileVersion);
        if(!temp) { //Checks to see if file opened successfully (file found)
            copy_file(traverse->fileName, traverse->fileVersion+traverse->fileName, false);
        } else{
            if(isFileUpdated(traverse->fileName,traverse->fileName+traverse->fileVersion)){ //Checks to see if the original file has been modified
                copy_file(traverse->fileName, traverse->fileVersion+traverse->fileName, false); //Copies the original file over if it has been modified.
                int increment = stoi(traverse->fileVersion); //Increments file version
                increment++;
                traverse->fileVersion = to_string(increment);
            }
        }
        traverse = traverse->next;
    }
    traverse = get_current_commit()->head;
    get_current_commit()->next = new doublyNode; //Makes new commit
    get_current_commit()->next->previous = get_current_commit();
    get_current_commit()->next->commitNumber = currentCommit+1;
    currentCommit++;
    get_current_commit()->head = nullptr;
    singlyNode *newTraverse = get_current_commit()->head; // Copies original SSL to new commit
    while(traverse!= nullptr){
        newTraverse = new singlyNode;
        newTraverse->fileVersion = traverse->fileVersion;
        newTraverse->fileName = traverse->fileName;
        traverse = traverse->next;
        newTraverse = newTraverse->next;
    }
}

int miniGit::add_file(string fileName) { // WORKS SUCCESSFULLY
    if(!fs::exists(fileName)){ //Checks to see if the file exists
        return -1;
    }
    doublyNode *commit = get_current_commit();
    singlyNode *file = commit->head;
    if(commit->head){
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
    } else{
        cout<<"ACTIVE"<<endl;
        commit->head = new singlyNode;
        file = commit->head;
    }
    file->fileName = fileName;
    if(commit==head){ //Checks to see if the commit is the initial commit
        file->fileVersion = "00";
    } else{
        singlyNode *prev = commit->previous->head;
        while(prev!= nullptr){ //Looks for the file in the previous commit
            if(prev->fileName==file->fileName){
                break;
            }
            prev = prev->next;
        }
        if(prev!= nullptr&&isFileUpdated(prev->fileName+prev->fileVersion,file->fileName)){ //Checks to see if the file is different
            int version = stoi(file->fileVersion);
            version++; //Updates the version
            if(file->fileVersion[0]=='0'){
                file->fileVersion = "0"+to_string(version);
            } else{
                file->fileVersion = to_string(version);
            }
        } else{
            file->fileVersion = "00";
        }
    }
    return 0; // Returns 0 if no problems
}

//Works successfully
void miniGit::remove_file(string file)
{
    doublyNode* ches = get_current_commit();
    singlyNode* temph = ches -> head;

    if(head == NULL)
    {
        return;
    }
    else
    {
        if(temph->fileName==file){
            if(temph->next){
                ches->head = temph->next;
            } else{
                get_current_commit()->head = 0;
            }
            delete temph;
            return;
        }
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

//Works successfully
void miniGit::check_out(int comnum)
{
    doublyNode* ches = get_current_commit();
    singlyNode* temph;
    if (comnum < ches -> commitNumber)
    {
        while (ches != nullptr)
        {
            cout<<ches -> commitNumber<<endl;
            if (comnum == ches -> commitNumber)
            {
                if(ches->head){
                    temph = ches->head;
                    while (temph){
                        copy_file( temph -> fileName, temph -> fileVersion+temph -> fileName, true);
                        temph = temph->next;
                    }
                }
                break;
            }
            else
            {
                ches = ches -> previous;
            }
        }
    }
}

//Works successfully
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

//Works successfully
void miniGit::copy_file(string originalName, string copyName, bool dir) { //Dir bool is to know if the copying is occurring from the .minigit folder to the directory (true)
    if(dir){
        string temp = originalName;
        originalName = ".minigit/"+copyName;
        copyName = temp;
    } else{
        copyName = ".minigit/"+copyName;
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

void miniGit::printFilesInCommit() {
    if(!get_current_commit()->head){
        return;
    }
    singlyNode *files = get_current_commit()->head;
    while(files!= nullptr){
        cout<<"File name: "<<files->fileName<<endl;
        cout<<"File version: "<<files->fileVersion<<endl;
        files = files->next;
    }

}

