#include <stdio.h> //stdio
#include <sys/types.h> //mkdir
#include <errno.h> //errno
#include <string.h> //for string operations
#include <unistd.h> //chdir
#include <stdlib.h> //system
#include <dirent.h> //for directory operations
#include <time.h> //timer
#include <fcntl.h> //flags
#include "functions.h" //my functions for the program

/* Color formats for the messages:
    \033[1;31m \033[0m        //Red - Error
    \033[1;33m \033[0m        //Yellow - Warning
    \033[1;36m \033[0m        //Blue - Info / Input
    \033[1;32m \033[0m        //Green - Done
    \033[0m        //No Color
*/

/** Checks if there are any arguments passed from the command line. 
    Tries to match it with the exsiting commands if there is.
    Returns error message with info if there is a wrong command or a wrong number of arguments entered.
*/
int main(int argc, char *argv[]){ ///RUNS WIZARD IF THERE ARE NO ARGUMENTS PASSED.
    if (argc > 1){
        /// Simple 'help' command that gives info about the possible commands and their usage. Used as 'pm help'.
        if (strcmp(argv[1],"help") == 0){
            char help[1000];
            memset(help, '\0', 1000);
            strcpy(help, "\033[1;36m'help' for the list of options.\n");
            strcat(help, "Running the program (pm) with no arguments will run the wizard.\n");
            strcat(help, "'create_project [project_name] [[-cost=]]' to create a new git project.\n");
            strcat(help, "'add_feature [feature_name] [[-cost=]]'    to add feature.\n");
            strcat(help, "'add_tag [tag_name]'        to add tag.\n");
            strcat(help, "'find_tag [tag_name]'       to find tag.\n");
            strcat(help, "'move_by_tag [tag1] [tag2]' to move the feature with 'tag1' to the feature with 'tag2'.\n");
            strcat(help, "'output_svg [project_name]' to create diagrams from the project folder in svg files.\n");
            strcat(help, "'rename_feature [old_feature] [new_name]'                 to rename a feature.\n");
            strcat(help, "'move_feature [origin_directory] [destination_directory]' to move feature.\n");
            strcat(help, "'create_folder [folder_name] [[-cost=]]' to create a new folder/directory.\n");
            strcat(help, "'calculate_workloads [folder_name]'      to calculate the workload for a project/feature.\n");
            strcat(help, "'set_estimate [directory] [workload]'    to set the workload estimate of a project/feature/folder.\n");
            strcat(help, "\033[0m\n");
            printf("%s", help);
            return 0;
        }

        /** 'create_project' command that creates a new git project and builds a folder structure inside.
        Additional optional argument to set the estimate workload value for it when running.
        Takes 2 or 3 arguments, aborts otherwise. Used as 'pm create_project project_name [-cost=]'.
        */
       if (strcmp(argv[1],"create_project") == 0){
            if (argc == 3){
                git_init(argv[2], 0);
                return 0;
            }
            if (argc == 4){
                if (strncmp(argv[3], "-cost=", 6) == 0){
                    git_init(argv[2], atoi(argv[3]+6));
                    return 0;
                }
            }
            else {
                printf("\033[1;33mWrong number of parameters entered, should be 'pm [command] [arg] [optinal arg]'. Please try agin.\n\033[0m");
                return 0;
            }
        }

        /** 'add_feature' command that adds a feature folder and builds a folder structure inside.
        Additional optional argument to set the estimate workload value for it when running.
        Takes 2 or 3 arguments, aborts otherwise. Used as 'pm add_feature feature_name [-cost=]'.
        */
        if (strcmp(argv[1],"add_feature") == 0){
            if (argc == 3){
                add_feature(argv[2], 0);
                return 0;
            }
            if (argc == 4){
                if (strncmp(argv[3], "-cost=", 6) == 0){
                    add_feature(argv[2], atoi(argv[3]+6));
                    return 0;
                }
            }
            else {
                printf("\033[1;33mWrong number of parameters entered, should be 'pm [command] [arg] [optinal arg]'. Please try agin.\n\033[0m");
                return 0;
            }
        }

        /** 'add_tag' command that adds a tag file with the tag inside.
        Takes only 2 arguments, aborts otherwise. Used as 'pm add_tag tag'
        */
        if (strcmp(argv[1],"add_tag") == 0){
            if (argc == 3){
                add_tag(argv[2]);
                return 0;
            }
            else {
                printf("\033[1;33mWrong number of parameters entered, should be 'pm [command] [arg]'. Please try agin.\n\033[0m");
                return 0;
            }
        }

        /** 'find_tag' command that finds and prints the path where the given tag exists.
        Takes only 2 arguments, aborts otherwise. Used as 'pm find_tag tag'
        */
        if (strcmp(argv[1],"find_tag") == 0){
            if (argc == 3){
                find_tag(argv[2]);
                return 0;
            }
            else {
                printf("\033[1;33mWrong number of parameters entered, should be 'pm [command] [arg]'. Please try agin.\n\033[0m");
                return 0;
            }
        }

        /** 'move_by_tag' command that moves a folder with the first given tag to the folder with the second given tag.
        Takes only 3 arguments, aborts otherwise. Used as 'pm move_by_tag tag1 tag2'
        */
        if (strcmp(argv[1],"move_by_tag") == 0){
            if (argc == 4){
                move_by_tag(argv[2], argv[3]);
                return 0;
            }
            else {
                printf("\033[1;33mWrong number of parameters entered, should be 'pm [command] [arg] [arg]'. Please try agin.\n\033[0m");
                return 0;
            }
        }

        /** 'output_svg' command that creates a file in plantuml wbs format for the contents of the given project folder and an svg file created from it.
        * Also creates another file in plantuml gantt format with the workload values of thr given project folder and an svg file created from it.
        * Takes only 2 arguments, aborts otherwise. Used as 'pm output_svg project_name'
        */
        if (strcmp(argv[1],"output_svg") == 0){
            if (argc == 3){
                output_svg(argv[2]);
                return 0;
            }
            else {
                printf("\033[1;33mWrong number of parameters entered, should be 'pm [command] [arg]'. Please try agin.\n\033[0m");
                return 0;
            }
        }

        /** 'rename_feature' command that renames a folder.
        Can specify the path for the directory in the 2nd argument, as in 'parent/old_folder'.
        Should give only the new name for the directory in the 3rd argument as in 'new_name'.
        Takes only 3 arguments, aborts otherwise. Used as 'pm rename_feature old_folder new_name'.
        */
        if (strcmp(argv[1],"rename_feature") == 0){
            if (argc == 4){
                rename_feature(argv[2], argv[3]);
                return 0;
            }
            else {
                printf("\033[1;33mWrong number of parameters entered, should be 'pm [command] [arg] [arg]'. Please try agin.\n\033[0m");
                return 0;
            }
        }

        /** 'move_feature' command that moves a directory to another directory.
        It creates the parent directories specified in the 3rd argument as 'parent1/parent2/destination', if they do not exist already. 
        Takes only 3 arguments, aborts otherwise. Used as 'pm move_feature origin_directory destination_directory'.
        */
        if (strcmp(argv[1],"move_feature") == 0){
            if (argc == 4){
                move_feature(argv[2], argv[3]);
                return 0;
            }
            else {
                printf("\033[1;33mWrong number of parameters entered, should be 'pm [command] [arg] [arg]'. Please try agin.\n\033[0m");
                return 0;
            }
        }

        /** 'create_folder' command that creates a new folder/directory.
        Additional optional argument to set the estimate workload value for it when running.
        Takes 2 or 3 arguments, aborts otherwise. Used as 'pm create_folder folder_name [-cost=]'.
        */
        if (strcmp(argv[1],"create_folder") == 0){
            if (argc == 3){
                make_folder(argv[2], 0);
                return 0;
            }
            if (argc == 4){
                if (strncmp(argv[3], "-cost=", 6) == 0){
                    make_folder(argv[2], atoi(argv[3]+6));
                    return 0;
                }
            }
            else {
                printf("\033[1;33mWrong number of parameters entered, should be 'pm [command] [arg]'. Please try agin.\n\033[0m");
                return 0;
            }
        }

        /** 'run_calculate_workloads' command that calculates the workload value of a folder with path/name 'pname', and the every subfolder inside it.
        * Stores the workload value of each folder and subfolder to a file called '.pm_workload' inside it.
        * Takes only 2 arguments, aborts otherwise. Used as 'pm calculate_workloads folder_name'
        */
        if (strcmp(argv[1],"calculate_workloads") == 0){
            if (argc == 3){
                run_calculate_workloads(argv[2]);
                return 0;
            }
            else {
                printf("\033[1;33mWrong number of parameters entered, should be 'pm [command] [arg]'. Please try agin.\n\033[0m");
                return 0;
            }
        }

        /** 'set_estimate' command that stores the given workload estimate value inside the given directory.
        It creates/writes the value to a file with the name ".pm_workload". 
        Takes only 3 arguments, aborts otherwise. Used as 'pm set_estimate directory workload'.
        */
        if (strcmp(argv[1],"set_estimate") == 0){
            if (argc == 4){
                set_estimate(argv[2], atoi(argv[3]));
                return 0;
            }
            else {
                printf("\033[1;33mWrong number of parameters entered, should be 'pm [command] [arg] [arg]'. Please try agin.\n\033[0m");
                return 0;
            }
        }

        printf("\033[1;33mWrong command. Use 'pm help' for the list of options.\n\033[0m");
        return 0;
    }
    else{
        wizard();
        return 0;
    }
    return 0;
}