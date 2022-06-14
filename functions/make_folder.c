int mkdir(const char *pathname, mode_t mode);

/** Gets the folder name (fname) as a parameter and creates a folder with that name.
Prints wether the operation was successful or it failed (with reasons).
If the workload value (workload) is not 0, stores the workload value inside the new folder by calling 'set_estimate'.
Returns 1 if successful, 0 if fails.
External functions used: set_estimate.
*/
int make_folder(char *fname, int workload){
    /// Checks the length of the user input. Aborts if it is longer than 255 characters (max length for linux systems).
    if (strlen(fname) > 255){
        printf("\033[1;33mAborted! Folder name '%s' is too long.\n\033[0m", fname);
        return 0;
    }
    /// Checks if there is a space in the folder name. Aborts if there is.
    if (strchr(fname, ' ') != NULL){
        printf("\033[1;33mAborted! Bad characters in folder name '%s'.\n\033[0m", fname);
        return 0;
    }

    /** Attempts to create a file and fetches the result. Notifies if succeessful.
    If it fails, checks the error code and notifies the cause of error for some common cases.
    */
    if (mkdir(fname, 0777) == 0){
        printf("\033[1;32mFolder '%s' successfully created.\n\033[0m", fname);
        if (workload != 0){
            set_estimate(fname, workload);
        }
        return 1;
    }
    else{
        switch (errno){
            case 17:
                printf("\033[1;33mAborted! Folder '%s' already exists.\n\033[0m", fname);
                return 0;
                break;
            
            case 13:
                printf("\033[1;33mAborted! Permission denied.\n\033[0m");
                return 0;
                break;

            case 28:
                printf("\033[1;33mAborted! No space left on device to create the folder '%s'.\n\033[0m", fname);
                return 0;
                break;

            case 30:
                printf("\033[1;33mAborted! Current folder is read-only.\n\033[0m");
                return 0;
                break;

            case 2:
                printf("\033[1;33mAborted! Only include the name of the folder you want to create in the current directory. Do not include '/' in the name '%s'.\n\033[0m", fname);
                return 0;
                break;

            default:
                printf("\033[1;33mAborted! Cannot create the folder '%s'.\n\033[0m", fname);
                return 0;
                break;
        }
    }
}