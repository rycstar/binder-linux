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

#include "com/fv/BpEventBusInterface.h"

using namespace std;
using namespace android;

int main(int argc, char * argv[]){

    sp<IServiceManager> sm = defaultServiceManager();
    sp<IBinder> binder = sm->getService(String16("com.fv.IEventBusService"));
 
    sp<com::fv::BpEventBusInterface> evt_bus = new com::fv::BpEventBusInterface(binder);
    
    evt_bus->post_evt(argv[1], argv[2]);
    return 0;
}