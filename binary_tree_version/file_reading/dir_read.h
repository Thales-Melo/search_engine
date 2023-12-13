#ifndef _DIR_READ_H_
#define _DIR_READ_H_

#include "../std_data/vector/vector.h"


Vector *dir_build_file_names(char *dir, char *file_list_file_name);

Vector *read_file_splited(char *file_name);


#endif