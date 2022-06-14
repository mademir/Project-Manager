#define DIGITS "0123456789"
#define HEADER "                                         \033[44;33m PROJECT MANAGER \033[0m                                         \n" ///Header/title when listing the options on the screen.
#define GOODBYE "\n\033[1;36mExiting the wizard. Goodbye!\033[0m\n\n" ///Goodbye message when exiting the wizard.

/** Wizard that shows options to the user and calls the functions according to the user's choice and input.
* Uses 'get_input' to get the user input.
* External function used: 'get_input' and every function for each wizard option.
*/
void wizard(){
    int opt_size = 3710;
    char options[opt_size]; //The content of the page that will be printed to the user.
    memset(options, '\0', opt_size);

    strcat(options, HEADER);
    strcat(options, "Options list:\n\n"); ///List of possible actions.
    strcat(options, "1  - Create Project\n");
    strcat(options, "2  - Add Feature\n");
    strcat(options, "3  - Add Tag\n");
    strcat(options, "4  - Find Tag\n");
    strcat(options, "5  - Move By Tag\n");
    strcat(options, "6  - Output SVG\n");
    strcat(options, "7  - Rename Feature\n");
    strcat(options, "8  - Move Feature\n");
    strcat(options, "9  - Calculate Workloads\n");
    strcat(options, "10 - Set Estimate\n");
    strcat(options, "11 - Create Folder\n");

    strcat(options, "0  - Quit\n");

    int n = 20; ///Number of new lines to be added.
    
    for (int i = 1; i<=n; i++){ ///Add new lines to fill the screen.
        strcat(options, "\n");
    }

    strcat(options, "\033[1;36mSelect an option: \033[0m\033[s");

    system("clear"); ///Clear terminal
    printf("%s", options); ///Print options

    char input[256];
    memset(input, '\0', 256);
    char input_2[256];
    memset(input_2, '\0', 256);
    DIR *dir;

    switch (atoi(get_input(2, "", DIGITS))) ///Switch statement to match the selected option.
    {
    case 0: ///Exit
        system("clear");
        break;

    case 1: ///Create Project
        system("clear");
        memset(options, '\0', opt_size);

        strcat(options, HEADER);
        strcat(options, "\nSelected 'Create Project'.\n\n");

        n = 31; //number of empty new lines

        for (int i = 1; i<=n; i++){
            if (i == n-2){ //lines before input
                strcat(options, "Type '!exit' to exit.");
            }
            strcat(options, "\n");
        }

        strcat(options, "\033[1;36mPlease enter a name for the new project: \033[0m\033[s");

        printf("%s", options);

        strcpy(input, get_input(255, "\\/ ", ""));
        system("clear");

        //To ask for a workload value.
        memset(options, '\0', opt_size);
        strcat(options, HEADER);
        strcat(options, "\nSelected 'Create Project'.\n\n");

        n = 31; //number of empty new lines

        for (int i = 1; i<=n; i++){
            if (i == n-2){ //lines before input
                strcat(options, "Type '0' to continue without adding a workload value.");
            }
            strcat(options, "\n");
        }

        strcat(options, "\033[1;36mPlease enter the workload value for the project: \033[0m\033[s");

        printf("%s", options);

        strcpy(input_2, get_input(100, "", DIGITS));
        system("clear");

        git_init(input, atoi(input_2));
        break;
    
    case 2: ///Add Feature
        system("clear");
        memset(options, '\0', opt_size);

        strcat(options, HEADER);
        strcat(options, "\nSelected 'Add Feature'.\n\n");

        strcat(options, "You must specify the git repository you want the new feature to be added in.");

        n = 31; //number of empty new lines

        for (int i = 1; i<=n; i++){
            if (i == n-2){ //lines before input
                strcat(options, "Type '!exit' to exit.");
            }
            strcat(options, "\n");
        }

        strcat(options, "\033[1;36mPlease enter the name/path of the git repository: \033[0m\033[s");

        printf("%s", options);

        strcpy(input, get_input(255, "\\ ", ""));
        system("clear");
        
        if ((dir = opendir(input))){
            closedir(dir);
            char home_path[2024];
            getcwd(home_path, 2024);
            chdir(input);

            memset(options, '\0', opt_size);

            strcat(options, HEADER);
            strcat(options, "\nSelected 'Add Feature'.\n\n");

            n = 31; //number of empty new lines

            for (int i = 1; i<=n; i++){
                if (i == n-2){ //lines before input
                    strcat(options, "Type '!exit' to exit.");
                }
                strcat(options, "\n");
            }

            strcat(options, "\033[1;36mPlease enter a name for the new feature: \033[0m\033[s");

            printf("%s", options);

            memset(input, '\0', 256);
            strcpy(input, get_input(255, "\\/ ", ""));
            system("clear");

            //To ask for a workload value
            memset(options, '\0', opt_size);

            strcat(options, HEADER);
            strcat(options, "\nSelected 'Add Feature'.\n\n");

            n = 31; //number of empty new lines

            for (int i = 1; i<=n; i++){
                if (i == n-2){ //lines before input
                    strcat(options, "Type '0' to continue without adding a workload value.");
                }
                strcat(options, "\n");
            }

            strcat(options, "\033[1;36mPlease enter the workload value for the feature: \033[0m\033[s");

            printf("%s", options);

            memset(input_2, '\0', 256);
            strcpy(input_2, get_input(100, "", DIGITS));
            system("clear");

            add_feature(input, atoi(input_2));
            chdir(home_path);
            break;
        }
        else{
            printf("\033[1;33mAborted! There is no git repository with the name/path '%s'.\033[0m\n", input);
            break;
        }

    case 3: ///Add Tag
        system("clear");
        memset(options, '\0', opt_size);

        strcat(options, HEADER);
        strcat(options, "\nSelected 'Add Tag'.\n\n");

        strcat(options, "You must specify the directory you want the tag to be added in.");

        n = 31; //number of empty new lines

        for (int i = 1; i<=n; i++){
            if (i == n-2){ //lines before input
                strcat(options, "Type '!exit' to exit.");
            }
            strcat(options, "\n");
        }

        strcat(options, "\033[1;36mPlease enter the name/path of the directory: \033[0m\033[s");

        printf("%s", options);

        strcpy(input, get_input(255, "\\ ", ""));
        system("clear");
        
        if ((dir = opendir(input))){
            closedir(dir);
            char home_path[2024];
            getcwd(home_path, 2024);
            chdir(input);

            memset(options, '\0', opt_size);

            strcat(options, HEADER);
            strcat(options, "\nSelected 'Add Tag'.\n\n");

            n = 31; //number of empty new lines

            for (int i = 1; i<=n; i++){
                if (i == n-2){ //lines before input
                    strcat(options, "Type '!exit' to exit.");
                }
                strcat(options, "\n");
            }

            strcat(options, "\033[1;36mPlease enter the tag you want to add (e.g. F1): \033[0m\033[s");

            printf("%s", options);

            memset(input, '\0', 256);
            strcpy(input, get_input(50, "\\/ ", ""));
            system("clear");

            add_tag(input);
            chdir(home_path);
            break;
        }
        else{
            printf("\033[1;33mAborted! There is no directory with the name/path '%s'.\033[0m\n", input);
            break;
        }

    case 4: ///Find Tag
        system("clear");
        memset(options, '\0', opt_size);

        strcat(options, HEADER);
        strcat(options, "\nSelected 'Find Tag'.\n\n");

        n = 31; //number of empty new lines

        for (int i = 1; i<=n; i++){
            if (i == n-2){ //lines before input
                strcat(options, "Type '!exit' to exit.");
            }
            strcat(options, "\n");
        }

        strcat(options, "\033[1;36mPlease enter a tag you want to find (e.g. F1): \033[0m\033[s");

        printf("%s", options);

        strcpy(input, get_input(50, "\\/ ", ""));
        system("clear");
        find_tag(input);
        break;
    
    case 5: ///Move By Tag
        system("clear");
        memset(options, '\0', opt_size);

        strcat(options, HEADER);
        strcat(options, "\nSelected 'Move By Tag'.\n\n");

        strcat(options, "You must enter the tag for the origin folder and then the tag for the destination folder.");

        n = 31; //number of empty new lines

        for (int i = 1; i<=n; i++){
            if (i == n-2){ //lines before input
                strcat(options, "Type '!exit' to exit.");
            }
            strcat(options, "\n");
        }

        strcat(options, "\033[1;36mPlease enter the tag for the origin folder: \033[0m\033[s");

        printf("%s", options);

        strcpy(input, get_input(255, "\\ ", ""));
        system("clear");

        // Getting the next input.
        memset(options, '\0', opt_size);

        strcat(options, HEADER);
        strcat(options, "\nSelected 'Move By Tag'.\n\n");

        strcat(options, "You must enter the tag for the origin folder and then the tag for the destination folder.\n\n");
        strcat(options, "Selected tag for the origin folder: ");
        strcat(options, input);

        n = 29; //number of empty new lines

        for (int i = 1; i<=n; i++){
            if (i == n-2){ //lines before input
                strcat(options, "Type '!exit' to exit.");
            }
            strcat(options, "\n");
        }

        strcat(options, "\033[1;36mPlease enter the tag for the destination folder: \033[0m\033[s");

        printf("%s", options);

        strcpy(input_2, get_input(255, "\\ ", ""));
        system("clear");

        move_by_tag(input, input_2);
        break;
    
    case 6: ///Output SVG
        system("clear");
        memset(options, '\0', opt_size);

        strcat(options, HEADER);
        strcat(options, "\nSelected 'Output SVG'.\n\n");

        n = 31; //number of empty new lines

        for (int i = 1; i<=n; i++){
            if (i == n-2){ //lines before input
                strcat(options, "Type '!exit' to exit.");
            }
            strcat(options, "\n");
        }

        strcat(options, "\033[1;36mPlease enter the name of the folder: \033[0m\033[s");

        printf("%s", options);

        strcpy(input, get_input(255, "\\ ", ""));
        system("clear");
        output_svg(input);
        break;

    case 7: ///Rename Feature
        system("clear");
        memset(options, '\0', opt_size);

        strcat(options, HEADER);
        strcat(options, "\nSelected 'Rename Feature'.\n\n");

        strcat(options, "You must enter the name/path of the feature that will be renamed and a new name.");

        n = 31; //number of empty new lines

        for (int i = 1; i<=n; i++){
            if (i == n-2){ //lines before input
                strcat(options, "Type '!exit' to exit.");
            }
            strcat(options, "\n");
        }

        strcat(options, "\033[1;36mPlease enter the name/path of the feature: \033[0m\033[s");

        printf("%s", options);

        strcpy(input, get_input(255, "\\ ", ""));
        system("clear");

        // Getting the next input.
        memset(options, '\0', opt_size);

        strcat(options, HEADER);
        strcat(options, "\nSelected 'Rename Feature'.\n\n");

        strcat(options, "You must enter the name/path of the feature that will be renamed and a new name.\n\n");
        strcat(options, "Selected feature: ");
        strcat(options, input);

        n = 29; //number of empty new lines

        for (int i = 1; i<=n; i++){
            if (i == n-2){ //lines before input
                strcat(options, "Type '!exit' to exit.");
            }
            strcat(options, "\n");
        }

        strcat(options, "\033[1;36mPlease enter a new name for the feature: \033[0m\033[s");

        printf("%s", options);

        strcpy(input_2, get_input(255, "\\/ ", ""));
        system("clear");

        rename_feature(input, input_2);
        break;

    case 8: ///Move Feature
        system("clear");
        memset(options, '\0', opt_size);

        strcat(options, HEADER);
        strcat(options, "\nSelected 'Move Feature'.\n\n");

        strcat(options, "You must enter the name/path for the origin feature and then for the destination feature.");

        n = 31; //number of empty new lines

        for (int i = 1; i<=n; i++){
            if (i == n-2){ //lines before input
                strcat(options, "Type '!exit' to exit.");
            }
            strcat(options, "\n");
        }

        strcat(options, "\033[1;36mPlease enter the name/path for the origin feature: \033[0m\033[s");

        printf("%s", options);

        strcpy(input, get_input(255, "\\ ", ""));
        system("clear");

        // Getting the next input.
        memset(options, '\0', opt_size);

        strcat(options, HEADER);
        strcat(options, "\nSelected 'Move Feature'.\n\n");

        strcat(options, "You must enter the name/path for the origin feature and then for the destination feature.\n\n");
        strcat(options, "Selected origin feature: ");
        strcat(options, input);

        n = 29; //number of empty new lines

        for (int i = 1; i<=n; i++){
            if (i == n-2){ //lines before input
                strcat(options, "Type '!exit' to exit.");
            }
            strcat(options, "\n");
        }

        strcat(options, "\033[1;36mPlease enter the name/path for the destination feature: \033[0m\033[s");

        printf("%s", options);

        strcpy(input_2, get_input(255, "\\ ", ""));
        system("clear");

        move_feature(input, input_2);
        break;

    case 9: ///Calculate Workloads 
        system("clear");
        memset(options, '\0', opt_size);

        strcat(options, HEADER);
        strcat(options, "\nSelected 'Calculate Workloads'.\n\n");
        strcat(options, "Estimates the workload of the project/feature. This also estimates the workloads for\nthe subfolders and stores it in a file inside them.");

        n = 30; //number of empty new lines

        for (int i = 1; i<=n; i++){
            if (i == n-2){ //lines before input
                strcat(options, "Type '!exit' to exit.");
            }
            strcat(options, "\n");
        }

        strcat(options, "\033[1;36mPlease enter the name of the project/feature: \033[0m\033[s");

        printf("%s", options);

        strcpy(input, get_input(255, "\\ ", ""));
        system("clear");
        run_calculate_workloads(input);
        break;

    case 10: ///Set Estimate
        system("clear");
        memset(options, '\0', opt_size);

        strcat(options, HEADER);
        strcat(options, "\nSelected 'Set Estimate'.\n\n");

        strcat(options, "You must specify the directory you want the workload estimate to be added in.");

        n = 31; //number of empty new lines

        for (int i = 1; i<=n; i++){
            if (i == n-2){ //lines before input
                strcat(options, "Type '!exit' to exit.");
            }
            strcat(options, "\n");
        }

        strcat(options, "\033[1;36mPlease enter the name/path of the directory: \033[0m\033[s");

        printf("%s", options);

        strcpy(input, get_input(255, "\\ ", ""));
        system("clear");

        if ((dir = opendir(input))){
            closedir(dir);
            char home_path[2024];
            getcwd(home_path, 2024);
            chdir(input);

            memset(options, '\0', opt_size);

            strcat(options, HEADER);
            strcat(options, "\nSelected 'Set Estimate'.\n\n");

            n = 31; //number of empty new lines

            for (int i = 1; i<=n; i++){
                if (i == n-2){ //lines before input
                    strcat(options, "Type '!exit' to exit.");
                }
                strcat(options, "\n");
            }

            strcat(options, "\033[1;36mPlease enter workload value you want to add (e.g. 10): \033[0m\033[s");

            printf("%s", options);

            memset(input, '\0', 256);
            strcpy(input, get_input(100, "\\/ ", DIGITS));
            system("clear");

            set_estimate(".", atoi(input));
            chdir(home_path);
            break;
        }
        else{
            printf("\033[1;33mAborted! There is no directory with the name/path '%s'.\033[0m\n", input);
            break;
        }

    case 11: ///Create Folder
        system("clear");
        memset(options, '\0', opt_size);

        strcat(options, HEADER);
        strcat(options, "\nSelected 'Create Folder'.\n\n");

        n = 31; //number of empty new lines

        for (int i = 1; i<=n; i++){
            if (i == n-2){ //lines before input
                strcat(options, "Type '!exit' to exit.");
            }
            strcat(options, "\n");
        }

        strcat(options, "\033[1;36mPlease enter a name for the folder: \033[0m\033[s");

        printf("%s", options);

        strcpy(input, get_input(255, "\\/ ", ""));
        system("clear");

        //To ask for a workload value.
        memset(options, '\0', opt_size);
        strcat(options, HEADER);
        strcat(options, "\nSelected 'Create Folder'.\n\n");

        n = 31; //number of empty new lines

        for (int i = 1; i<=n; i++){
            if (i == n-2){ //lines before input
                strcat(options, "Type '0' to continue without adding a workload value.");
            }
            strcat(options, "\n");
        }

        strcat(options, "\033[1;36mPlease enter the workload value for the folder: \033[0m\033[s");

        printf("%s", options);

        strcpy(input_2, get_input(100, "", DIGITS));
        system("clear");

        make_folder(input, atoi(input_2));
        break;

    default:
        system("clear");
        printf("\033[1;33mInput is out of range!\033[0m\n");
        break;
    }

    printf(GOODBYE);
    return;
}