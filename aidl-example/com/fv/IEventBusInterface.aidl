package com.fv;

interface IEventBusInterface {

    oneway void post_evt(@utf8InCpp String tag, @utf8InCpp String content);

    void register_evt(@utf8InCpp String name, IBinder listener, @utf8InCpp String subscribe);

    void unregister_evt(@utf8InCpp String name, IBinder listener, @utf8InCpp String subscribe);

}
