/**Adds the given tag value (tag) to the project/feature/folder by storing it inside the file '.pm_tag'.
 * Aborts if there is already a tag stored.
 */
void add_tag(char *tag){// User needs to cd into desired folder and call the pm from the parent folder
    FILE *fp;
    fp = fopen(".pm_tag", "r"); ///Checks if there is already a tag stored.
    if(fp == NULL){
        fp = fopen(".pm_tag", "w+");
        if(fputs(tag, fp) == 1){ ///If there is no tag stored already, stores the new tag value inside the .pm_tag file.
            printf("\033[1;32mAdded tag '%s' to the '.pm_tag' file.\n\033[0m", tag);
        }
        else{
            printf("\033[1;33mAborted! Cannot add the tag '%s'.\n\033[0m", tag);
        }
    }else{
        printf("\033[1;33mAborted! There is already a tag for this folder.\n\033[0m");
    }

    fclose(fp);
    return;
}
