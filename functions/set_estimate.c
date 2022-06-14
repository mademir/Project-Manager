/**Stores the workload value (workload) inside the folder with the name (fname).
 * Aborts if fname is not a directory.
*/
void set_estimate(char *fname, int workload){
    DIR *dir = opendir(fname);
    if (dir == NULL){
        printf("\033[1;33mAborted! '%s' is not a directory.\033[0m\n", fname);
        closedir(dir);
        return;
    }
    closedir(dir);

    char file[2048];
    strcpy(file, fname);
    strcat(file, "/.pm_workload"); ///Stores the value in the file .pm_workload
    FILE *fp = fopen(file, "w+");
    if (fp != NULL){
        char str_workload[100];
        memset(str_workload, '\0', 100);
        sprintf(str_workload, "%d", workload);
        if (fputs(str_workload, fp) != 1){
            printf("\033[1;33mAborted! Cannot write to workload file.\033[0m\n");
        }
        else{
            printf("\033[1;32mSuccessfully set the workload value of '%d'.\033[0m\n", workload);
        }
    }
    else{
        printf("\033[1;33mAborted! Cannot write to workload file.\033[0m\n");
    }

    fclose(fp);
    return;
}