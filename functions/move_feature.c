/** Moves a directory (fname1) to another directory (fname2).
It creates the parent directories specified in the second  path (fname2) argument as 'parent1/parent2/destination', if they do not exist already.
Aborts if there is already a directory with the same name in the destination.
External functions used: make_folder.
*/
void move_feature(char *fname1, char *fname2){
    char cmd[2024];
    char home_path[2024];
    getcwd(home_path, 2024);

    strcpy(cmd, "ls ");
    strcat(cmd, fname1);
    strcat(cmd, " >/dev/null"); //Suppresses the output message of the system call.
    if (system(cmd) != 0){ ///Checks if there is a directory to move with the name given as the first argument.
        printf("\033[1;33mAborted! There is no directory named '%s'.\n\033[0m", fname1);
        return;
    }

    char *name_token2;
    char tmp_fname2[2024];

    strcpy(tmp_fname2, fname2);
    name_token2 = strtok(tmp_fname2, "/"); ///strtok returns the bit of the path name before the first '/'.
    if (chdir(tmp_fname2) != 0){
        if (make_folder(tmp_fname2, 0) == 1){
            chdir(tmp_fname2);
        }
        else{
            printf("\033[1;33mAborted! Cannot create the folder %s.\n\033[0m", tmp_fname2);
            return;
        }
    }
    /**Continues to check for the next bit until '/'.
    * And goes inside the directory with that name, creates the directory if it does not exist.
    */
    while (name_token2 != NULL){
        name_token2 = strtok(NULL, "/");
        if (name_token2 != NULL){
            strcpy(tmp_fname2, name_token2);
            if (chdir(tmp_fname2) != 0){
                if (make_folder(tmp_fname2, 0) == 1){
                    chdir(tmp_fname2);
                }
                else{
                    printf("\033[1;33mAborted! Cannot create the folder %s.\n\033[0m", tmp_fname2);
                    return;
                }
            }
        }
    }

    char *name_token1;
    char tmp_fname1[2024];

    strcpy(tmp_fname1, fname1);
    name_token1 = strtok(tmp_fname1, "/"); //Returns the bit of the path name before the first '/'.

    /*Continues to check for the next bit until '/'.
    * And writes it to a temproray string to end up with the final bit.
    */
    while (name_token1 != NULL){
        name_token1 = strtok(NULL, "/");
        if (name_token1 != NULL){
            strcpy(tmp_fname1, name_token1);
        }
    }

    strcpy(cmd, "ls ");
    strcat(cmd, tmp_fname1);
    strcat(cmd, " >/dev/null 2>/dev/null"); //Suppresses the output message and the error message of the system call.
    if (system(cmd) == 0){ ///Checks if there is a folder with that name in the destination.
        printf("\033[1;33mAborted! There is already a directory named '%s' in the destination folder.\n\033[0m", tmp_fname1);
        return;
    }

    strcpy(cmd, "mv "); ///Uses bash command md to move the folders.
    strcat(cmd, home_path);
    strcat(cmd, "/");
    strcat(cmd, fname1);
    strcat(cmd, " ");
    strcat(cmd, tmp_fname1);
    strcat(cmd, " >/dev/null 2>/dev/null"); //Suppresses the output message and the error message of the system call.

    if (system(cmd) == 0){ //System call to move the directories.
        printf("\033[1;32mSuccessfully moved '%s' to '%s'.\n\033[0m", fname1, fname2);
    }
    else{
        printf("\033[1;31mError! Cannot move folders. Aborting.\n\033[0m");
    }

    chdir(home_path);
}