package com.fv;

interface  IRgbLedsService {
    boolean setRgbColor(int id,int reg);
    @utf8InCpp List<String> setRgbList(int count);
    oneway void setRgbBrightness(int id,int reg);
}
