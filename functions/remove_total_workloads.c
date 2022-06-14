/** Removes the .pm_total_workload files in any directory under the path (pname).
 * This enables 'calculate_workloads' to function properly without the involving the old values.
 * '.pm_workload' files stay the same without any editing.
*/
void remove_total_workloads(char *pname){
    DIR *dir = opendir(pname);
    struct dirent *entry;
    char file[2048];
    char sub[2048];

    strcpy(file, pname);
    strcat(file, "/.pm_total_workload");
    unlink(file);

    while ((entry = readdir(dir)) != NULL){
        if (entry->d_type == DT_DIR && entry->d_name[0] != '.'){
            strcpy(sub, pname);
            strcat(sub, "/");
            strcat(sub, entry->d_name);
            remove_total_workloads(sub);
        }
    }
    closedir(dir);
    return;
}
