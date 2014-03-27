//
//  FloorSystemSwitch.cpp
//  TheGiantMap
//
//  Created by 深津 貴之 on 2014/03/03.
//
//

#include "FloorSystemSwitch.h"


FloorSystemSwitch::FloorSystemSwitch(){
    
}

void FloorSystemSwitch::setup(string portName, int speed){
    serial.setup(portName ,speed);
    isUpdated = false;
}



void FloorSystemSwitch::update(){
    string str;
    do {
        str = ofxGetSerialString(serial,'\n'); //read until end of line
        if (str==""){
            continue;
        }
        switches = ofSplitString(str, ",");
        isUpdated = true;
    } while (str!="");
    
    if(isUpdated && switches.size() > 16) {
        //Compare Touch
        for (int i=0; i<3; i++) {
            for(int j=0; j<3; j++) {
                int flag = (atoi(switches[i*3+j].c_str())>1000)? 1 : 0;
                int touch = ((int)touches[i*3+j]);
                
                if(flag==0 && touch==0){
                    touches[i*3+j] = 0;
                    //Nothing
                }else if(flag==0 && touch==1){
                    touches[i*3+j] = 0;
                    //Release
                }else if(flag==1 && touch==0){
                    //Press
                    touches[i*3+j] = 1;
                    notifyEvent(i, j);
                }else if(flag==1 && touch==1){
                    //Pressing
                    touches[i*3+j] = 1;
                }
            }
        }
        isUpdated = false;
    }
}




#pragma utils


string FloorSystemSwitch::ofxTrimStringRight(string str) {
    size_t endpos = str.find_last_not_of("\t\r\n");
    return (string::npos != endpos) ? str.substr( 0, endpos+1) : str;
}


string FloorSystemSwitch::ofxTrimStringLeft(string str) {
    size_t startpos = str.find_first_not_of("\t\r\n");
    return (string::npos != startpos) ? str.substr(startpos) : str;
}


string FloorSystemSwitch::ofxTrimString(string str) {
    return ofxTrimStringLeft(ofxTrimStringRight(str));;
}


string FloorSystemSwitch::ofxGetSerialString(ofSerial &serial, char until) {
    static string str;
    stringstream ss;
    char ch;
    int ttl=1000;
    
    while ((ch=serial.readByte())>0 && ttl-->0 && ch!=until) {
        ss << ch;
    }
    str+=ss.str();
    if (ch==until) {
        string tmp=str;
        str="";
        return ofxTrimString(tmp);
    } else {
        return "";
    }
}