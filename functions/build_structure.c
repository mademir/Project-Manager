/** Used for building the folder structure.
 * Takes the path name (pname) as a parameter to create the folders inside.
 * Uses 'make_folder' to create the folders 'bin', 'docs', 'lib', 'src' and 'tests'.
 * External functions used: make_folder.
*/
void build_structure(char *pname){
    char path[2024];
    strcpy(path, pname);
    strcat(path, "/bin");
    make_folder(path, 0);

    strcpy(path, pname);
    strcat(path, "/docs");
    make_folder(path, 0);

    strcpy(path, pname);
    strcat(path, "/lib");
    make_folder(path, 0);

    strcpy(path, pname);
    strcat(path, "/src");
    make_folder(path, 0);

    strcpy(path, pname);
    strcat(path, "/tests");
    make_folder(path, 0);

    return;
}