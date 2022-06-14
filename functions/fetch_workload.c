/** Reads and returns the wrokload value of a folder with the folder name (fname) as an integer.
 * If there is no .pm_workload file to read the value from, returns 0.
*/
int fetch_workload(char *fname){
    char file[2048];
    strcpy(file, fname);
    strcat(file, "/.pm_workload");
    FILE *fp = fopen(file, "r");
    if (fp != NULL){
        char str_workload[100];
        fgets(str_workload, 100, fp);
        return atoi(str_workload);
    }
    else{
        return 0;
    }
}

/** Reads and returns the total wrokload value of a folder with the folder name (fname) as an integer.
 * If there is no .pm_total_workload file to read the value from, returns 0.
 */
int fetch_total_workload(char *fname){
    char file[2048];
    strcpy(file, fname);
    strcat(file, "/.pm_total_workload");
    FILE *fp = fopen(file, "r");
    if (fp != NULL){
        char str_workload[100];
        fgets(str_workload, 100, fp);
        return atoi(str_workload);
    }
    else{
        return 0;
    }
}