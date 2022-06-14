/** Attempts to create a folder with the given project name (pname), using 'make_folder', and initializes a git repository on that folder if successfull.
Executes command on bash to initialize git.
Builds a folder structure using 'build_structure' in that folder.
Creates a readme.md file, adds to git and commits.
If the workload value (workload) is not 0, stores the workload value inside the project by calling 'set_estimate'.
External functions used: set_estimate, make_folder, build_structure.
*/
void git_init(char *pname, int workload){
    int res = make_folder(pname, 0);
    if (res==1){
        char cmd[2024];
        strcpy(cmd, "git init "); ///Initialises the git calling git init from the system.
        strcat(cmd, pname);
        system(cmd);

        build_structure(pname); ///Runs build_structure to create the folder structure inside the new project.
        
        chdir(pname);

        strcpy(cmd, "echo 'Initialized' > readme.md"); ///Writes to a new readme.md file.
        system(cmd);

        strcpy(cmd, "git add readme.md"); ///Adds readme.md to git.
        system(cmd);
        
        FILE *fp;
        fp = fopen(".git/config", "a"); ///Edits the local config for git to store the name and email values for the user to successfully commit for the first time.
        fputs("[user]\n\tname = pm\n\temail = pm@pm.pm", fp);
        fclose(fp);

        strcpy(cmd, "git commit -m 'Initialized'"); ///Makes the first commit.
        strcat(cmd, " >/dev/null 2>/dev/null"); //Suppresses the output message and the error message of the system call.
        system(cmd);

        if (workload != 0){ ///If the workload value is not 0, runs set_estimates with that value.
            set_estimate(".", workload);
        }

        chdir("..");
        
    }
    return;
}