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
#include "RgbLedsClient.h"

using namespace std;
using namespace android;
namespace android{

    class Tester : public IBinder::DeathRecipient {
        public:
            Tester() = default;
            ~Tester() override = default;
            void binderDied(const wp<IBinder>& who) override{
                cout << "death tester" << endl;
            }
    };

};


static sp<com::fv::BpRgbLedsService> gRgbLedsService;
static sp<Tester> gTester(new Tester()) ;

void* get_service(const char * name){

    if(gRgbLedsService == NULL){
        sp<IBinder> binder = defaultServiceManager()->getService(String16(name));
        if (binder == NULL) return NULL;
        gRgbLedsService = new com::fv::BpRgbLedsService(binder);
        printf("==============================\n");
        if(binder->linkToDeath(gTester) != OK){
           printf("==============linkToDeath fail================\n"); 
        }else{
            ProcessState::self()->startThreadPool();
        }
    }

    return static_cast<void *> (gRgbLedsService.get()); 
}

void call_set_rgb_color(void * srv, int a, int b){
    bool state;
    if(! srv) return;
    if(gRgbLedsService == static_cast<com::fv::BpRgbLedsService *>(srv) && IInterface::asBinder(gRgbLedsService)->isBinderAlive()){
        gRgbLedsService->setRgbColor(a,b,&state);
    }
    return;  
}

void call_set_rgb_brightness(void * srv, int a, int b){
    if(! srv) return;
    if(gRgbLedsService == static_cast<com::fv::BpRgbLedsService *>(srv) && IInterface::asBinder(gRgbLedsService)->isBinderAlive()){
        gRgbLedsService->setRgbBrightness(a,b);
    }
    return;
}
#if 0
int main(void){
    sp<IServiceManager> sm = defaultServiceManager();
    sp<IBinder> binder = sm->getService(String16("com.fv.IRgbLedsService"));

    sp<com::fv::BpRgbLedsService> client = new com::fv::BpRgbLedsService(binder);
 
    bool state;
    while(1){
        client->setRgbColor(1,0,&state);
        client->setRgbBrightness(1, 0); 
        usleep(1500*1000);
	cout << "client sleep done!" << endl;
    }  
    return 0;
}
#endif