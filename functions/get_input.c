#define INPUT_TIME_LIMIT 30 ///Time limit in seconds.
#define GOODBYE "\n\033[1;36mExiting the wizard. Goodbye!\033[0m\n\n" ///Goodbye message when exiting the wizard.

void flush_stdin();

void flush_stdin(){ ///Reads 'stdin' until new line to flush it, so that whatever left in 'stdin' will not be passed when a new input is requested.
    while (fgetc(stdin) != '\n'){
        continue;
    }
}

/* Gets user input from the terminal and returns the input as a string or exits the program in special cases.
* Keeps asking for an input until it meets with all the requirements or until the user exceeds the time limit or types the exit option (!exit).
* (size) parameter is passed as the maximum length for the input.
* If (restricted_chars) is set but the (allowed_only_chars) is emty, the characters in (restricted_chars) are not allowed in the input.
* If (allowed_only_chars) is set, the (restricted_chars) is ignored. Only the characters in (allowed_only_chars) are allowed in the input.
*/
char* get_input(int size, char *restricted_chars, char *allowed_only_chars){
    size += 1;
    char res[size];
    memset(res, '\0', size);
    char tmp;

    time_t time_limit = time(0) + INPUT_TIME_LIMIT; ///Sets timer.

    int flag = fcntl(STDIN_FILENO, F_GETFL, 0); ///Sets the flags for stdin.
    fcntl(STDIN_FILENO, F_SETFL, flag | O_NONBLOCK); ///Sets stdin to nonblock, so it does not halt the execution for user input.

    char closers[2] = {'\n', EOF};

    while ((res[0] == '\0') && (time(0) < time_limit)){ ///Takes input until the input is not empty or until the timer runs out. (Input is set to empty when it is too long or has bad characters.)
        int i = 0;

        for (;strchr(closers, tmp = fgetc(stdin)) == NULL; i++){ ///If 'stdin' file is empty, 'fgetc(stdin)' asks for user input, if it is not empty it reads the first character and removes it from 'stdin'.
            if (i+1 < size){ ///Continues until the input is still within the length limit.
                int includes_bad_char = -1;

                if (strcmp(allowed_only_chars,"") == 0){ ///Checks for restricted characters only, if there are no allowed characters.
                    for (int n = 0; restricted_chars[n] != '\0'; n++){
                        if (restricted_chars[n] == tmp){
                            printf("\033[2A\033[KYour input includes a bad character '%c'. Please type it again excluding this character.\033[u\033[K", tmp);
                            includes_bad_char = 1;
                        }
                    }
                }
                else{ ///Checks for allowed characters only if there are any. Ignores restricted characters.
                    if (strchr(allowed_only_chars, tmp) == NULL){
                        printf("\033[2A\033[KYour input includes a bad character '%c'. Please type it again excluding this character.\033[u\033[K", tmp);
                        includes_bad_char = 1;
                    }
                }
                if (includes_bad_char == 1){ ///If the input has a bad character, notifies the user, asks for a new input and resets the timer.
                    memset(res, '\0', size);
                    flush_stdin();
                    time_limit = time(0) + INPUT_TIME_LIMIT; //Reset timer.
                    break;
                }
                res[i] = tmp;
            }
            else{ ///If the input is longer than the limit specified, notifies the user, asks for a new input and resets timer.
                memset(res, '\0', size);
                printf("\033[2A\033[KYour input is too long. Please type it again. Maximum length for this input is %d characters.\033[u\033[K", size - 1);
                flush_stdin();
                time_limit = time(0) + INPUT_TIME_LIMIT; //Reset timer.
                break;
            }
        }

        if ((i == 0) && (tmp == '\n')){ ///If the input is empty, notifies the user, asks for a new input and resets timer.
            memset(res, '\0', size);
            printf("\033[2A\033[KYour input is empty. Please type it again.\033[u\033[K");
            time_limit = time(0) + INPUT_TIME_LIMIT; //Reset timer.
        }
    }

    if (time(0) >= time_limit){ ///If user exceeded the time limit, notifies the user and exits the program.
        system("clear");
        printf("\033[1;33mTimed out! You need to enter your input within %d seconds.\033[0m\n", INPUT_TIME_LIMIT);
        printf(GOODBYE);
        exit(0);
    }

    if (strcmp(res, "!exit") == 0){ ///If user types the exit option (!exit), exits the program.
        system("clear");
        printf(GOODBYE);
        exit(0);
    }

    char *ptr_res = res;
    return ptr_res;
}