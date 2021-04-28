isFileUpdated:
Helper function used to compare files with the same name to see if any changes have been made to the file.

initialize:
Starts up the repository. Deletes the old .minigit folder and creates a new one with a new doubly linked list and the commit count starting at 0.

commit:
Stores the project files and stores them by versions too.
copys files over (gathered from a list it keeps track of) to the .minigit folder with the new name which is [version+filename] after which the program
moves on to a new commit and increments the commit count.

add_file:
Adds a file to a commit by making sure it's not already in it and then makes a new singly node in the commit.
Then it compares the file from a previous commit with the current version of it to see if the version count needs to increment.

copy_file:
Helper function that opens both files (creates a file if missing) given to it and then copies the file line by line.

remove_file:
The remove_file function's purpose is to remove a file of the users choice, which is prompted in main, from the repository.
We did this by accessing the currents commit head, checking to see if it exists and if it does, then the function cycles
through the commits list to find the file name the user provides. If the file is found the file is then deleted from the
repository.

check_out:
The check_out function is used as a way for teh user to "check-out" any previous version of a commit. This function
checks to see if the commit number the user imputs is less than the currents commit number. This then allows the function
to search backward through the list. Once the commit version is found it's then copied into the repository.