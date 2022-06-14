/** Adds a feature by creating a folder with the feature name (fname) from the paramter.
Also runs 'set_estimate' with (workload) value to set the estimate value for the folder if given.
Builds a folder structure inside that folder.
Creates and switches to a branch with the name of the feature (fname).
Edits or creates a readme.md file, adds it to git and commits it.
Switches back to master branch.
If the (workload) value is not 0, then set_estimate is called.
Aborts if the directory is not inside a git project.
External functions used: make_folder, build_structure, set_estimate.
*/
void add_feature(char *fname, int workload){
    /// Runs 'git status' and the returned value of 0 means the current directory is inside a git repository. Suppresses the output message and the error message of the system call.
    if(system("git status>/dev/null 2>/dev/null") == 0){
        int res = make_folder(fname, 0); ///Runs make_folder to make a folder for the feature.

        if (res == 1){
            build_structure(fname); ///Runs build_structure to create the folder structure inside the new feature.

            char cmd[2024];
            strcpy(cmd, "git branch "); ///Uses a system call to add a new branch with the name of the new feature.
            strcat(cmd, fname);
            system(cmd);

            strcpy(cmd, "git switch "); ///Uses a system call to switch to the new branch.
            strcat(cmd, fname);
            system(cmd);

            strcpy(cmd, "echo 'Created branch "); ///Stores a custom text inside readme.md.
            strcat(cmd, fname);
            strcat(cmd, ".' > readme.md");
            system(cmd);

            strcpy(cmd, "git add readme.md"); ///Uses a system call to add readme.md to git.
            system(cmd);

            strcpy(cmd, "git commit -m 'Created branch "); ///Uses a system call to commit with a custom message.
            strcat(cmd, fname);
            strcat(cmd, ".'");
            strcat(cmd, " >/dev/null 2>/dev/null"); ///Suppresses the output message and the error message of the system call.
            system(cmd);

            system("git switch master"); ///Uses a system call to switch back to the master branch.

            if (workload != 0){
                set_estimate(fname, workload); ///Runs set_estimate if workload value is not 0.
            }

            return;
        }
    }
    else{
        printf("\033[1;33mAborted! You must be inside a git repository to add a feature successfully.\n\033[0m");

        return;
    }
}