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
#include <list>
#include <utility>
#include <algorithm>  
#include <unordered_map>
#include "com/fv/BnEventBusInterface.h"
#include "com/fv/BpEventListenerInterface.h"

using namespace std;
using namespace android;

namespace com {

namespace fv {
    class EventBus : public BnEventBusInterface, public IBinder::DeathRecipient{
        public :
            
            ::android::binder::Status post_evt(const ::std::string& tag, const ::std::string& content){
                
                if(_topic_map.find(tag) == _topic_map.end()){
                    return binder::Status::ok();
                }

                auto listener_list = _topic_map.at(tag);
                std::list<std::string>::iterator iter;

                for(iter = listener_list->begin(); iter!=listener_list->end(); iter++){
                    try{
                        _listener_map.at(*iter)->onEvent(tag, content);
                    }catch(const out_of_range &e){
                        cerr << "Exception AT" << e.what() << endl;
                    }
                }
                return binder::Status::ok();
            };

            ::android::binder::Status register_evt(const ::std::string& name, const ::android::sp<::android::IBinder>& listener, const ::std::string& subscribe){
                /*
                * check the listener is in the map or not
                * If not, add it into map and link the deathRecipient
                * If yes, ignore
                */
                if(_listener_map.find(name) == _listener_map.end()){
                    listener->linkToDeath(this);
                    _listener_map.emplace(name, new com::fv::BpEventListenerInterface(listener));
                }

                /*
                * check the topic is a new topic or not
                * If not, add it into map and link the deathRecipient
                * If yes, ignore
                * !!!Maybe we should read topic items from config file and Limit the max topic num
                *
                */
                if(_topic_map.find(subscribe) == _topic_map.end()){
                    _topic_map.emplace(subscribe, new std::list<std::string>);
                }
                
                /*check the listeners on this topic, add it if not find*/
                auto listener_list = _topic_map.at(subscribe);
                std::list<std::string>::iterator iter = std::find(listener_list->begin(),listener_list->end(), name);
                if(iter == listener_list->end()){
                    listener_list->push_back(name);
                }
                
                return binder::Status::ok();
            };

            ::android::binder::Status unregister_evt(const ::std::string& name, const ::android::sp<::android::IBinder>& listener, const ::std::string& subscribe){
                if(_topic_map.find(subscribe) == _topic_map.end()){
                    return binder::Status::ok();
                }

                auto listener_list = _topic_map.at(subscribe);
                
                listener_list->remove(name);

                return binder::Status::ok();
            };

        private:
            virtual void binderDied(const wp<IBinder>& who){
                auto iter = _listener_map.begin();
                while(iter != _listener_map.end()){
                    sp<IBinder> mb(IInterface::asBinder(iter->second.get()));
                    if(mb == who){
                        /*clear the sp pointer*/
                        iter->second.clear();
                        register_topic_clear(iter->first);
                        _listener_map.erase(iter);
                        break;
                    }
                    iter++;
                }
            }

            void register_topic_clear(const ::std::string& name){

                /*remove from topic map first*/
                tTopicMap::iterator iter = _topic_map.begin();
                while(iter != _topic_map.end()){
                    auto tmp_list = iter->second;
                    tmp_list->remove(name);
                    if(tmp_list->size() == 0){
                        /*
                        * nobody care about this topic, clear it from the topic map.
                        */
                        delete tmp_list;
                        iter = _topic_map.erase(iter);
                    }else{
                        iter++;
                    }
                }

            };

            typedef std::unordered_map<std::string, ::android::sp<::com::fv::BpEventListenerInterface> > tListenerMap;
            
            typedef std::unordered_map<std::string, std::list<std::string> *> tTopicMap; 

            tListenerMap _listener_map;
            tTopicMap _topic_map;
    };
}

}


int main(void){
    sp<IServiceManager> sm = defaultServiceManager();
    sp<ProcessState> proc(ProcessState::self());

    sm->addService(String16("com.fv.IEventBusService"), new com::fv::EventBus());
    ProcessState::self()->startThreadPool();
    sleep(60);
    //IPCThreadState::self()->joinThreadPool();
    return 0;
}