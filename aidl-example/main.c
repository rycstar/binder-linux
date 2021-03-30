#include <stdio.h>
#include "RgbLedsClient.h"

int main(int argc, char *argv[]){
    int i = 0;
    void *srv = get_service("com.fv.IRgbLedsService");
    //while(i++ < 10){
        call_set_rgb_color(srv, 0 ,0);

        call_set_rgb_brightness(srv, 1, 1);
        
        call_set_rgb_list(srv, 10);
    //}
    
    printf("main over!\n");
    return 0;
}
