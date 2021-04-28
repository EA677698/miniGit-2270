TEST
printFilesInCommit:

initialize:

commit:

add_file:

remove_file:
The remove_file function's purpose is to remove a file of the users choice, which is prompted in main, from the repository.
We did this by accessing the currents commit head, checking to see if it exists and if it does, then the function cycles
through the commits list to find the file name the user provides. If the file is found the file is then deleted from the
repository.

check_out:
The check_out function is used as a way for teh user to "check-out" any previous version of a commit. This function
checks to see if the commit number the user imputs is less than the currents commit number. This then allows the function
to search backward through the list. Once the commit version is found it's then copied into the repository.

copy_file: