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
#include "com/fv/BnEventListenerInterface.h"
#include "com/fv/BpEventBusInterface.h"

using namespace std;
using namespace android;

namespace com {

namespace fv {
    class EventListener : public BnEventListenerInterface{
        public:
        ::android::binder::Status onEvent(const ::std::string& tag, const ::std::string& content){
            cout << "EventListener Tag:" << tag << "\n content:" << content << endl;
            return binder::Status::ok();
        };
        private:
          int32_t callback;
    };
}

}

int main(int argc, char *argv[]){
    std::string listener_name, topic;
    sp<IServiceManager> sm = defaultServiceManager();
    sp<ProcessState> proc(ProcessState::self());

    sp<IBinder> binder = sm->getService(String16("com.fv.IEventBusService"));

    sp<IBinder> evt_listener = new com::fv::EventListener();

    if(argc > 1){
        listener_name = argv[1];
    }else{
        listener_name = "com.fv.IEventListener.test";
    }

    if(argc > 2){
        topic = argv[2];
    }else{
        topic = "test";
    }
    sm->addService(String16(listener_name.c_str()), evt_listener);

    sp<com::fv::BpEventBusInterface> evt_bus = new com::fv::BpEventBusInterface(binder);

    evt_bus->register_evt(listener_name,evt_listener, topic);

    ProcessState::self()->startThreadPool();
    IPCThreadState::self()->joinThreadPool();
#if 0
    sleep(12);
    evt_bus->unregister_evt("com.fv.IEventListener.test",evt_listener, "test");

    sleep(12);
#endif
    return 0;
}