#include "main.h"
#include <unistd.h>
#include <stdlib.h>

int change_directory(char *directory) {
    if (directory == NULL) {
            char *home_dir = getenv("HOME");
        if (home_dir == NULL) {
                return -1;
        }
        if (chdir(home_dir) != 0) {
            
    	return -1;
        }
    } else {
        if (chdir(directory) != 0) {
            return -1;
        }
    }
    return 0;
}
