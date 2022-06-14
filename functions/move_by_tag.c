/** Moves the folder with the tag tag1 (tag1) to folder with the tag tag2 (tag2).
 * Calls 'find_path' to get the paths for the tags.
 * Aborts if either tag is not found.
 * Uses the system call "mv" to operate.
 * External functions used: find_tag.
*/
void move_by_tag(char *tag1, char *tag2){
    char cmd[1024];

    char path1[1024];
    char path2[1024];

    char *temp_path1 = find_tag(tag1);
    if (temp_path1 == NULL){
        return;
    }
    strcpy(path1, temp_path1);

    char *temp_path2 = find_tag(tag2);
    if (temp_path2 == NULL){
        return;
    }
    strcpy(path2, temp_path2);

    strcpy(cmd, "mv ");
    strcat(cmd, path1);
    strcat(cmd, " ");
    strcat(cmd, path2);

    if(system(cmd) == 0){
        printf("\033[1;32mMoved the folder '%s' inside '%s'.\n\033[0m", path1, path2);
    }
    else{
        printf("\033[1;33mAborted! Cannot move the folder '%s' inside '%s'.\n\033[0m", path1, path2);
    }

    return;
}