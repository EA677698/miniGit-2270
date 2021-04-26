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

miniGit::~miniGit() {
    doublyNode *traverse = get_current_commit();
    while(traverse != nullptr){
        traverse = traverse->previous;
        singlyNode *previous;
        singlyNode *SSL = traverse->next->head;
        while(SSL != nullptr){
            previous = SSL;
            SSL = SSL->next;
            delete previous;
        }
        delete traverse->next;
    }

}

void miniGit::initialize() {
    head = new doublyNode;
    head->commitNumber = 0;
    head->head = new singlyNode;
    currentCommit = 0;
}

void miniGit::commit() {
    singlyNode *traverse = get_current_commit()->head;
    while(traverse!= nullptr){
        ifstream temp(".minigit\\"+traverse->fileName+traverse->fileVersion);
        if(!temp) { //Checks to see if file opened successfully (file found)
            copy_file(traverse->fileName, traverse->fileName + traverse->fileVersion, false);
        } else{
            if(isFileUpdated(traverse->fileName,traverse->fileName+traverse->fileVersion)){ //Checks to see if the original file has been modified
                copy_file(traverse->fileName, traverse->fileName + traverse->fileVersion, false); //Copies the original file over if it has been modified.
                int increment = stoi(traverse->fileVersion); //Increments file version
                increment++;
                traverse->fileVersion = to_string(increment);
            }
        }
        traverse = traverse->next;
    }
    traverse = get_current_commit()->head;
    get_current_commit()->next = new doublyNode; //Makes new commit
    currentCommit++;
    singlyNode *newTraverse = get_current_commit()->head; // Copies original SSL to new commit
    while(traverse!= nullptr){
        newTraverse = new singlyNode;
        newTraverse->fileVersion = traverse->fileVersion;
        newTraverse->fileName = traverse->fileName;
        traverse = traverse->next;
        newTraverse = newTraverse->next;
    }
}

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
    copy_file(fileName, fileName+file->fileVersion,false); //copys the file to .minigit
    return 0;
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

