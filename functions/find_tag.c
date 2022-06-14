/** Checks if there is a .pm_tag file, and if there is, if it matches the tag (tag) searched for.
 * Returns the path of the folder the tag is found in, if there is a match.
 * Returns null otherwise.
*/
char* check_tag(char *tag){
    FILE *fp;
    fp = fopen(".pm_tag", "r");

    if(fp != NULL){
        char tag_name[100];
        fgets(tag_name, sizeof tag, fp);

        if (strcmp(tag_name, tag) == 0){
            fclose(fp);
            char path[2024];
            getcwd(path, sizeof path);
            char *final_path = path;
            return final_path;
        }
        else{
            fclose(fp);
            return NULL;
        }
    }
    else{
        return NULL;
    }
}

/** Recursively searches through the subfolders for the tag (tag) and calls 'check_tag' to check if there is a match in one of them.
 * Returns the path of the folder the tag is found in, which is returned by 'check_tag', but if null is returned from 'check_tag', it keeps searching.
 * If all the subfolders are searched and tag is not found, returns null.
*/
char* search_tag(char *tag){//RECURSIVE SEARCH
    char *path = check_tag(tag);
    if (path != NULL){
        return path;
    }
    else{
        DIR *dir;
        struct dirent *entry;
        dir = opendir(".");
        int subfolders = 0;
        while((entry = readdir(dir)) != NULL){
            if (entry->d_type == DT_DIR && entry->d_name[0] != '.'){
                subfolders++;
                chdir(entry->d_name);
                char *returned_path = search_tag(tag);
                if (returned_path != NULL){
                    closedir(dir);
                    return returned_path;
                }
                chdir("..");
            }
        }
        closedir(dir);
        if (subfolders == 0){
            return NULL;
        }
        return NULL;
    }
}

/** Finds the tag (tag) by searching through the subfolders with 'search_tag' and checking the tag with 'check_tag'.
 * Prints the path of the folder the tag is found in.
 * Also returns the path upon finding a match, which enables the other functions to use this to fetch the path of the folder with the tag.
 * Returns null upon failing.
*/
char* find_tag(char *tag){
    char sole_path[2024]; //Is the path to the folder from the current directory.
    char final_path[2024]; //Is the sole path with a '.' at the beginning to indicate it is the path from current directory.
    char home_path[2024]; //Is the current directory when the function starts running.

    getcwd(home_path, 2024);

    char *path = search_tag(tag);

    if (path != NULL){
        for(int n = 0; path[strlen(home_path)+n-1] != '\0'; n++){ ///Gets the difference between the home path and the path the tag was found in, and stores it in sole path.
            sole_path[n] = path[strlen(home_path)+n];
        }
        strcpy(final_path,".");
        strcat(final_path, sole_path);
        printf("\033[1;32mTag '%s' found in '%s'\n\033[0m", tag, final_path);
        chdir(home_path); ///Goes back to the directory the function started running in.
        char *p_final_path = final_path;
        return p_final_path;
    }
    else{
        printf("\033[1;33mTag '%s' not found.\n\033[0m", tag); ///Prints if the tag is not found, and returns null.
        chdir(home_path);
        return NULL;
    }
}
