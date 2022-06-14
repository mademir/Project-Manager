/** Calculates the total workload value for the folder with the path/name (pname), and the every subfolder inside it.
 * Stores the total workload value of any folder inside .pm_total_workload file.
 * Takes different approaches depending on what workload values are there for the folder and the subfolder.
*/
void calculate_workloads(char *pname){
    DIR *dir;
    struct dirent *entry;
    FILE *fp;
    int workload, total, sub_total, sub_workload;
    char str_workload[100];
    dir = opendir(pname); ///Aborts if directory with the path/name pname does not exist.
    if (!dir){
        printf("\033[1;33mAborted! There is no directory '%s'.\033[0m\n", pname);
        return;
    }

    while((entry = readdir(dir)) != NULL){ ///Uses a while loop to iterate through the subfolders and upon finding any, calls itself with the subfolders name recursively to start from the bottom of the tree and go up. 
        if (entry->d_type == DT_DIR && entry->d_name[0] != '.'){
            char path[2048];
            strcpy(path, pname);
            strcat(path, "/");
            strcat(path, entry->d_name); //Path for subfolders
            calculate_workloads(path);

            char file[2048];
            strcpy(file, path);
            strcat(file, "/.pm_total_workload");

            if ((fp = fopen(file, "r")) != NULL){//if subtotal
                fgets(str_workload, 100, fp);
                sub_total = atoi(str_workload);
                fclose(fp);

                strcpy(file, pname);
                strcat(file, "/.pm_total_workload");
                if ((fp = fopen(file, "r")) != NULL){//if total > total += sub_total
                    fgets(str_workload, 100, fp);
                    total = atoi(str_workload);
                    fclose(fp);

                    fp = fopen(file, "w+");
                    total += sub_total;
                    sprintf(str_workload, "%d", total);
                    fputs(str_workload, fp);
                    fclose(fp);
                }
                else{//no total
                    strcpy(file, pname);
                    strcat(file, "/.pm_workload");
                    if ((fp = fopen(file, "r")) != NULL){//if workload > total = workload + sub_total
                        fgets(str_workload, 100, fp);
                        workload = atoi(str_workload);
                        fclose(fp);

                        strcpy(file, pname);
                        strcat(file, "/.pm_total_workload");
                        fp = fopen(file, "w+");
                        total = workload + sub_total;
                        sprintf(str_workload, "%d", total);
                        fputs(str_workload, fp);
                        fclose(fp);
                    }
                    else{//no workload > total = sub_total
                        strcpy(file, pname);
                        strcat(file, "/.pm_total_workload");
                        fp = fopen(file, "w+");
                        total = sub_total;
                        sprintf(str_workload, "%d", total);
                        fputs(str_workload, fp);
                        fclose(fp);
                    }
                }
            }
            else{//no sub_total
                strcpy(file, path);
                strcat(file, "/.pm_workload");
                if ((fp = fopen(file, "r")) != NULL){//if sub_workload
                    fgets(str_workload, 100, fp);
                    sub_workload = atoi(str_workload);
                    fclose(fp);

                    strcpy(file, pname);
                    strcat(file, "/.pm_total_workload");
                    if ((fp = fopen(file, "r")) != NULL){//if total > total += sub_workload
                        fgets(str_workload, 100, fp);
                        total = atoi(str_workload);
                        fclose(fp);

                        fp = fopen(file, "w+");
                        total += sub_workload;
                        sprintf(str_workload, "%d", total);
                        fputs(str_workload, fp);
                        fclose(fp);
                    }
                    else{//no total
                        strcpy(file, pname);
                        strcat(file, "/.pm_workload");
                        if ((fp = fopen(file, "r")) != NULL){//if workload > total = workload + sub_workload
                            fgets(str_workload, 100, fp);
                            workload = atoi(str_workload);
                            fclose(fp);

                            strcpy(file, pname);
                            strcat(file, "/.pm_total_workload");
                            fp = fopen(file, "w+");
                            total = workload + sub_workload;
                            sprintf(str_workload, "%d", total);
                            fputs(str_workload, fp);
                            fclose(fp);
                        }
                        else{//no workload > total = sub_workload
                            strcpy(file, pname);
                            strcat(file, "/.pm_total_workload");
                            fp = fopen(file, "w+");
                            total = sub_workload;
                            sprintf(str_workload, "%d", total);
                            fputs(str_workload, fp);
                            fclose(fp);
                        }
                    }
                }
                else{//no sub_workload
                    continue;
                }
            }
        }
    }

    closedir(dir);
    return;
}

/** Runs the 'calculate_wokloads' function, passes it's parameter (pname)to it, and also prints the total workload value for the top folder.
 * Calls 'remove_total_workloads' to get rid of the old total workload values.
 * External functions used: remove_total_workloads.
*/
void run_calculate_workloads(char *pname){
    DIR *dir = opendir(pname);
    if (!dir){
        printf("\033[1;33mAborted! There is no directory '%s'.\033[0m\n", pname);
        return;
    }
    closedir(dir);

    remove_total_workloads(pname);
    calculate_workloads(pname); ///Removes the old total workload values and calculates them again.
    char str_workload[100];
    char file[2048];
    strcpy(file, pname);
    strcat(file, "/.pm_total_workload"); ///Reads the total workload value of the top folder to print it to the user.
    FILE *fp = fopen(file, "r");
    if (fp != NULL){
        fgets(str_workload, 100, fp);
        fclose(fp);
    }
    else{
        strcpy(str_workload, "0");
    }
    printf("\033[1;32mSuccessfully stored the workload values. The total workload value of '%s' is: %s.\033[0m\n", pname, str_workload);
}