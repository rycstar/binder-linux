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
#include "c_config.h"
#include "com/fv/BnRgbLedsService.h"

using namespace std;
using namespace android;

namespace com {

namespace fv {

    class rgbLedsService : public BnRgbLedsService{
        public:
          ::android::binder::Status setRgbColor(int32_t id, int32_t reg, bool* _aidl_return){
            std::cout << "set RGB" << endl;
                (void) _aidl_return;
                get_c_config("color");
                set_c_config("color", 10);
                save_c_config();
                return binder::Status::ok();
          };

          ::android::binder::Status setRgbList(int32_t count, ::std::vector<::std::string>* _aidl_return){
            _aidl_return->push_back("rgb 0 red");
            _aidl_return->push_back("rgb 1 red");
            _aidl_return->push_back("rgb 2 red");
            _aidl_return->push_back("rgb 3 red");
            _aidl_return->push_back("rgb 4 red");
            _aidl_return->push_back("rgb 5 red");
            _aidl_return->push_back("rgb 6 red");
            return binder::Status::ok();
          }

          ::android::binder::Status setRgbBrightness(int32_t id, int32_t reg){
                std::cout << "set Brightness" << endl;
                sleep(3);
                std::cout << "set Brightness done" << endl;
                return binder::Status::ok();
          };

        private:
          int32_t unused;
    };

}

}

int main(void){
    sp<IServiceManager> sm = defaultServiceManager();
    sp<ProcessState> proc(ProcessState::self());
    sm->addService(String16("com.fv.IRgbLedsService"), new com::fv::rgbLedsService());
    ProcessState::self()->startThreadPool();
    IPCThreadState::self()->joinThreadPool();

    return 0;
}
