/** The recursive function that looks for subfolders and stores the names in the (wbs) variable in wbs style.
 * (sub_level) parameter is passed to record the distance of the folder when function is called recursively.
 * Adds the link for the directories to the diagram.
 * Also lists the workload and the total workload values of a directory after the name of it.
 * Returns the final wbs text in strings.
 * External functions used: fetch_workload, fetch_total_workloads.
*/
char * wbs_sub_search(char *wbs, int sub_level){
    sub_level++;
    DIR *dir;
    struct dirent *entry;
    char real_path[2048];
    dir = opendir(".");
    while((entry = readdir(dir)) != NULL){
        if (entry->d_type == DT_DIR && entry->d_name[0] != '.' && strcmp(entry->d_name, "bin") != 0 && strcmp(entry->d_name, "tests") != 0 && strcmp(entry->d_name, "docs") != 0 && strcmp(entry->d_name, "src") != 0 && strcmp(entry->d_name, "lib") != 0){ ///Skips if the folder name starts with a '.' or is src, lib, docs, tests, bin.
            for(int i = 0; i<=sub_level; i++){
                strcat(wbs, "*"); ///Adds a star for each sub_level before the folder name.
            }
            strcat(wbs, " [[file://");
            realpath(entry->d_name, real_path);
            strcat(wbs, real_path);
            strcat(wbs, " ");
            strcat(wbs, entry->d_name);
            strcat(wbs, " (W: ");
            char str_workload[100];
            sprintf(str_workload, "%d, T: %d", fetch_workload(entry->d_name), fetch_total_workload(entry->d_name));
            strcat(wbs, str_workload);
            strcat(wbs, ")]]");
            strcat(wbs, "\n");
            chdir(entry->d_name);
            strcpy(wbs, wbs_sub_search(wbs, sub_level));
        }
    }
    closedir(dir);
    chdir("..");
    sub_level--;
    return wbs;
}

/** Uses the 'wbs_sub_search' function and retrieves the wbs string, puts it into its final form.
* (pname) is the path/name of the directory the output_svg is called for.
* (home_path) is the current directory where output_svg started running. Used to go back to that directory.
* Stores the final wbs in a file. (Which will be used in 'output_svg' function while running plantuml.)
* Returns 1 if successful, 0 if not.
* External functions used: calculate_workloads, remove_total_workloads, fetch_workload, fetch_total_workload.
*/
int build_wbs(char *pname, char *home_path){
    char wbs[4048];
    char real_path[2048];
    strcpy(wbs, "@startwbs\n* [[file://"); ///'file://' at the beginning is for the path added to be treated as a link.
    realpath(".", real_path);
    strcat(wbs, real_path);
    strcat(wbs, " ");
    strcat(wbs, pname);
    strcat(wbs, " (Workload: ");
    char str_workload[100];
    remove_total_workloads(".");
    calculate_workloads(".");
    sprintf(str_workload, "%d, Total Workload: %d", fetch_workload("."), fetch_total_workload("."));
    strcat(wbs, str_workload);
    strcat(wbs, ")]]");
    strcat(wbs, "\n");
    strcpy(wbs, wbs_sub_search(wbs, 0));
    strcat(wbs, "@endwbs");

    char wbs_fname[1024];
    strcpy(wbs_fname, pname);
    strcat(wbs_fname, "_diagram.wbs");

    chdir(home_path);

    FILE *fp;
    fp = fopen(wbs_fname, "w+");
    if(fp != NULL){
        if(fputs(wbs, fp) == 1){
            printf("\033[1;32mDiagram text file '%s' is successfully created.\033[0m\n", wbs_fname);
            fclose(fp);
            return 1;
        }
        else{
            printf("\033[1;33mAborted! Cannot write to the file '%s'.\n\033[0m", wbs_fname);
            return 0;
        }
        return 1;
    }
    else{
        printf("\033[1;33mAborted! Cannot create the file '%s'.\n\033[0m", wbs_fname);
        return 0;
    }

    return 1;
}

/** Builds the content of the text file for the Gantt diagram with the workload values of the folders.
* (pname) is the path/name of the directory the output_svg is called for.
* Returns the edited Gantt context (gantt) as a string.
* Aborts and returns null if the (pname) is not a directory.
* External functions used: fetch_workload.
*/
char* build_gantt(char *pname, char *gantt){
    DIR *dir;
    struct dirent *entry;
    int workload;
    dir = opendir(pname);
    if (!dir){
        printf("\033[1;33mAborted! There is no directory '%s'.\033[0m\n", pname);
        return NULL;
    }

    while((entry = readdir(dir)) != NULL){
        if (entry->d_type == DT_DIR && entry->d_name[0] != '.'){
            char path[2048];
            strcpy(path, pname);
            strcat(path, "/");
            strcat(path, entry->d_name);
            workload = fetch_workload(path);
            char str_workload[100];
            sprintf(str_workload, "%d", workload);

            strcat(gantt, "[");
            strcat(gantt, path);
            strcat(gantt, "] lasts ");
            strcat(gantt, str_workload);
            strcat(gantt, " days\n");

            build_gantt(path, gantt);
        }
    }

    closedir(dir);
    return gantt;
}

/** Uses 'build_wbs' 'build_gantt' functions to create the files to run plantuml with, for the directory with the name (pname), and then runs plantuml.
* Creates an svg file with the diagram of the folder structure inside the project folder given as the parameter (pname).
* Also creates a svg file with the Gantt diagram for the workload of the project folder given as the parameter (pname).
* External functions used: fetch_workload
*/
void output_svg(char *pname){
    if (strchr(pname, '\\') != NULL){ /// Checks if there is a '\' in the name.
        printf("\033[1;33mAborted! Don't include '\\'.\n\033[0m"); ///Aborts if bad characters are in the pname.
        return;
    }

    if (pname[strlen(pname)-1] == '/'){ ///Checks if the path name ends with a '/'.
        printf("\033[1;33mAborted! Do not put '/' at the end of the first parameter.\n\033[0m");
        return;
    }

    DIR *tmp_dir;
    if (!(tmp_dir = opendir(pname))){ /// Checks if the project folder exists.
        printf("\033[1;33mAborted! Folder does not exist.\n\033[0m"); ///Aborts if the folder does not exists
        return;
    }
    closedir(tmp_dir);

    //To build the Gantt diagram text file.
    char gantt[4048];
    memset(gantt, '\0', 4048);
    strcpy(gantt, "@startgantt\nprintscale daily zoom 2.5\n");
    strcat(gantt, "[");
    strcat(gantt, pname);
    strcat(gantt, "] lasts ");
    char str_workload[100];
    sprintf(str_workload, "%d", fetch_workload(pname));
    strcat(gantt, str_workload);
    strcat(gantt, " days\n");
    strcpy(gantt, build_gantt(pname, gantt));
    strcat(gantt, "@endgantt\n");

    char *tmp_pname = pname;
    if (strrchr(tmp_pname, '/') != NULL){ ///Edits the path name to end up with the bit after the last '/'.
        tmp_pname = strrchr(tmp_pname, '/');
        tmp_pname = tmp_pname+1;
    }
    char gantt_fname[1024];
    strcpy(gantt_fname, tmp_pname);
    strcat(gantt_fname, "_gantt_diagram.gantt");

    FILE *fp;
    fp = fopen(gantt_fname, "w+");
    if(fp != NULL){
        if(fputs(gantt, fp) == 1){
            printf("\033[1;32mDiagram text file '%s' is successfully created.\033[0m\n", gantt_fname);
            fclose(fp);
        }
        else{
            printf("\033[1;33mAborted! Cannot write to the file '%s'.\033[0m\n", gantt_fname);
            return;
        }
    }
    else{
        printf("\033[1;33mAborted! Cannot create the file '%s'.\033[0m\n", gantt_fname);
        return;
    }
    

    //To build the wbs text file.
    char home_path[2024];
    getcwd(home_path, 2024);

    chdir(pname); ///Goes into the project folder.
    
    if (strrchr(pname, '/') != NULL){ ///Edits the path name to end up with the bit after the last '/'.
        pname = strrchr(pname, '/');
        pname = pname+1;
    }
    
    int res = build_wbs(pname, home_path); ///Builds the wbs text and writes it to a file inside the 'home_path'. 'build_wbs' ends up in the 'home_path' after called.
    
    if(res == 1){ ///To run the plantuml and checks if the files are created successfullly.
        char cmd[2024];
        strcpy(cmd, "plantuml -tsvg ");
        strcat(cmd, pname);
        strcat(cmd, "_diagram.wbs ");
        strcat(cmd, gantt_fname);
        
        system(cmd);
        
        ///Checks the diagram file.
        char svg_fname[2024];
        strcpy(svg_fname, pname);
        strcat(svg_fname, "_diagram.svg");

        FILE *fp;
        fp = fopen(svg_fname, "r");
        if (fp != NULL){
            printf("\033[1;32mSuccessfully created the '%s' file.\033[0m\n", svg_fname);
            fclose(fp);
        }
        else{
            printf("\033[1;33mAborted! PlantUML error.\033[0m\n");
            fclose(fp);
        }

        ///Checks the Gantt diagram file.
        strcpy(svg_fname, pname);
        strcat(svg_fname, "_gantt_diagram.svg");

        fp = fopen(svg_fname, "r");
        if (fp != NULL){
            printf("\033[1;32mSuccessfully created the '%s' file.\033[0m\n", svg_fname);
            fclose(fp);
        }
        else{
            printf("\033[1;33mAborted! PlantUML error.\033[0m\n");
            fclose(fp);
        }
        return;
    }
    else{
        return;
    }
    
    return;
}