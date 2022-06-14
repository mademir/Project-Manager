#include "functions/get_input.c"
#include "functions/set_estimate.c"
#include "functions/make_folder.c"
#include "functions/build_structure.c"
#include "functions/git_init.c"
#include "functions/add_feature.c"
#include "functions/add_tag.c"
#include "functions/find_tag.c"
#include "functions/move_by_tag.c"
#include "functions/rename_feature.c"
#include "functions/move_feature.c"
#include "functions/remove_total_workloads.c"
#include "functions/calculate_workloads.c"
#include "functions/fetch_workload.c"
#include "functions/output_svg.c"
#include "functions/wizard.c"

char* get_input(int size, char *restricted_chars, char *allowed_only_chars);
void wizard();
int make_folder(char *fname, int workload);
void build_structure(char *pname);
void set_estimate(char *fname, int workload);
void git_init(char *pname, int workload);
void add_feature(char *fname, int workload);
void add_tag(char *tag);
char* find_tag(char *tag);
char* search_tag(char *tag);
char* check_tag(char *tag);
void move_by_tag(char *tag1, char *tag2);
void rename_feature(char *fname1, char *fname2);
void move_feature(char *fname1, char *fname2);
void remove_total_workloads(char *pname);
void calculate_workloads(char *pname);
void run_calculate_workloads(char *pname);
int fetch_workload(char *fname);
int fetch_total_workload(char *fname);
void output_svg(char *pname);
int build_wbs(char *pname, char *home_path);
char * wbs_sub_search(char *wbs, int sub_level);
char* build_gantt(char *pname, char *gantt);