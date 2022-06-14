/* Renames the folder with the path/name (fname1) with the new name (fname2).
 * Can specify the path for the directory in fname1, as in 'parent/old_folder'.
 * Should give only the new name for the directory in fname2 as in 'new_name'.
 * If the feature is in a git project and has a branch for it, it renames the branch as well.
*/
void rename_feature(char *fname1, char *fname2){
    char cmd[2024];

    if (fname1[strlen(fname1)-1] == '/'){ ///Aborts if there is a bad character
        printf("\033[1;33mAborted! Do not put '/' at the end of the first parameter.\n\033[0m");
        return;
    }

    strcpy(cmd, "ls ");
    strcat(cmd, fname1);
    strcat(cmd, " >/dev/null 2>/dev/null"); //Suppresses the output message and the error message of the system call.
    if (system(cmd) != 0){ ///Aborst if the directory is not found.
        printf("\033[1;33mAborted! There is no directory named '%s'.\n\033[0m", fname1);
        return;
    }

    if (strchr(fname2, '/') != NULL){ ///Aborts if the new name is given in path format.
        printf("\033[1;33mAborted! Do not include '/' in the new name.\n\033[0m");
        return;
    }
    
    char tmp_fname1[2024];
    char tmp_fname2[2024];

    if (strchr(fname1, '/') != NULL){ ///Series of operations to replace the end bit after the last '/' in the path with the new name.
        strcpy(tmp_fname1, fname1);
        strncpy(tmp_fname2, tmp_fname1, strrchr(tmp_fname1, '/') - tmp_fname1);
        strcat(tmp_fname2, "/");
        strcat(tmp_fname2, fname2);
    }
    else{
        strcpy(tmp_fname2, fname2);
    }

    strcpy(cmd, "ls ");
    strcat(cmd, tmp_fname2);
    strcat(cmd, " >/dev/null 2>/dev/null"); //Suppresses the output message and the error message of the system call.
    if (system(cmd) == 0){
        printf("\033[1;33mAborted! There is already a directory named '%s'.\n\033[0m", fname2);
        return;
    }
    
    strcpy(cmd, "mv "); ///Uses bash command 'mv' to rename.
    strcat(cmd, fname1);
    strcat(cmd, " ");
    strcat(cmd, tmp_fname2);
    strcat(cmd, " >/dev/null 2>/dev/null"); //Suppresses the output message and the error message of the system call.

    if (system(cmd) == 0){
        printf("\033[1;32mSuccessfully renamed the directory '%s' as '%s'.\n\033[0m", fname1, fname2);

        ///If the feature is in a git project and has a branch for it, rename the branch as well.
        char home_path[2024];
        getcwd(home_path, 2024);
        chdir(tmp_fname2);
        strcpy(cmd, "git rev-parse --verify --quiet "); ///Checks if there is a branch with the name of the old folder.

        char old_name[255];
        if (strchr(tmp_fname1, '/') != NULL){
            strcat(old_name, strrchr(tmp_fname1, '/')+1);
        }
        else{
            strcat(old_name, tmp_fname1);
        }
        strcat(cmd, old_name);
        strcat(cmd, " >/dev/null 2>/dev/null"); ///Suppresses the output message and the error message of the system call.
        int sys = system(cmd);
        if (sys == 0){
            strcpy(cmd, "git branch -m "); ///Uses system call to run 'git branch -m' to rename the branch.
            strcat(cmd, old_name);
            strcat(cmd, " ");
            strcat(cmd, fname2);

            if (system(cmd) == 0){
                printf("\033[1;32mSuccessfully renamed the branch '%s' to '%s'.\033[0m\n", old_name, fname2);
            }
        }
        chdir(home_path);
    }
    else{
        printf("\033[1;31mError. Cannot rename the directory '%s' as '%s'. Aborting.\n\033[0m", fname1, fname2);
    }
}