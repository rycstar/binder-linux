#include <binder/IPCThreadState.h>
#include <binder/ProcessState.h>
#include <binder/IServiceManager.h>
#include <stdio.h>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <string>
#include "com/fv/BpRgbLedsService.h"

using namespace std;
using namespace android;

int main(void){
    sp<IServiceManager> sm = defaultServiceManager();
    sp<IBinder> binder = sm->getService(String16("com.fv.IRgbLedsService"));

    sp<com::fv::BpRgbLedsService> client = new com::fv::BpRgbLedsService(binder);
 
    bool state;
    while(1){
        client->setRgbColor(1,0,&state);
        client->setRgbBrightness(1, 0, &state); 
        usleep(1500*1000);
	cout << "client sleep done!" << endl;
    }  
    return 0;
}
