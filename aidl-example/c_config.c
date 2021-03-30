#include <stdio.h>
#include <c_config.h>

int get_c_config(const char * name){
    printf("try to get config %s\n", name);
    return 0;
}
int set_c_config(const char * name, int value){
    printf("try to set config %s to %d\n", name, value);
    return 0;
}
int save_c_config(void){
    printf("try to save config\n");
    return 0;
}

