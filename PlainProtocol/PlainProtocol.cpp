//
// PlainProtocol.cpp
// Library C++ code
// ----------------------------------
// Developed with embedXcode
// http://embedXcode.weebly.com
//
// Project PlainProtocol
//
// Created by qiao, 13-4-2 上午9:17
// qiao
//
//
// Copyright © qiao, 2013年
// Licence CC = BY NC SA
////

/*
 PlainProtocol Frame
 |----------------------------------------------------------|-------------------------------|
 |  <Command>Content;                                       | <speed>100;                   |
 |----------------------------------------------------------|-------------------------------|
 |  <Command>Content1,Content2;                             | <speed>100,200;               |
 |----------------------------------------------------------|-------------------------------|
 |  <Command1>Content1;<Command2>Content2;                  | <speed>100; <direction>100;   |
 |----------------------------------------------------------|-------------------------------|
 |  #Address<Command>Content;                               | #1<speed>100;                 |
 |----------------------------------------------------------|-------------------------------|
 |  #Address<Command>Content1,Content2;                     | #1<speed>100,200;             |
 |----------------------------------------------------------|-------------------------------|
 |  #Address1<Command1>Content1;#Address2<Command2>Content2;| #1<speed>100;#2<direction>100;|
 |----------------------------------------------------------|-------------------------------|
 
 New in version 1.1
 |----------------------------------------------------------|-------------------------------|
 |  <Command+ExtraString>Content;                           | <dispHello word!>10,10;       |
 |----------------------------------------------------------|-------------------------------|
 The command is "disp" and the ExtraString is"Hello word!"
 
 */

#include "PlainProtocol.h"
#include <stdarg.h>


//Constructor
PlainProtocol::PlainProtocol(HardwareSerial& serialSelect, unsigned long baud):
SerialTransceiver(serialSelect)
{
    //initiate the variables
    frame="";
    receivedCommand="";
    sendingCommand="";
    receivedAddress=0;
    sendingAddress=0;
    sendingContentLenth=0;
    memset(receivedContent, 0x00, sizeof(receivedContent));
    memset(sendingContent, 0x00, sizeof(sendingContent));
    isSendingAddress=false;
    isReceivedAddress=false;
    serialBaud=baud;
}

//initiate the Serial for PlainProtocol, this function should be put in setup() function
void PlainProtocol::init()
{
    SerialTransceiver.begin(serialBaud);
    while (!SerialTransceiver) ;
}

void PlainProtocol::write(String commandOrFrame)
{
    sendFrame(commandOrFrame);
}
void PlainProtocol::write(String command,int sendingContent0)
{
    sendFrame(command, 1, sendingContent0);
}
void PlainProtocol::write(String command,int sendingContent0, int sendingContent1)
{
    sendFrame(command, 2, sendingContent0, sendingContent1);
}
void PlainProtocol::write(String command,int sendingContent0, int sendingContent1, int sendingContent2)
{
    sendFrame(command, 3, sendingContent0, sendingContent1, sendingContent2);
}
void PlainProtocol::write(String command,int sendingContent0, int sendingContent1, int sendingContent2, int sendingContent3)
{
    sendFrame(command, 4, sendingContent0, sendingContent1, sendingContent2, sendingContent3);
}
void PlainProtocol::write(String command,int sendingContent0, int sendingContent1, int sendingContent2, int sendingContent3, int sendingContent4)
{
    sendFrame(command, 5, sendingContent0, sendingContent1, sendingContent2, sendingContent3, sendingContent4);
}

void PlainProtocol::write(String command,String extraString)
{
    sendFrame(command+extraString,0);
}
void PlainProtocol::write(String command,String extraString,int sendingContent0)
{
    sendFrame(command+extraString, 1, sendingContent0);
}
void PlainProtocol::write(String command,String extraString,int sendingContent0, int sendingContent1)
{
    sendFrame(command+extraString, 2, sendingContent0, sendingContent1);
}
void PlainProtocol::write(String command,String extraString,int sendingContent0, int sendingContent1, int sendingContent2)
{
    sendFrame(command+extraString, 3, sendingContent0, sendingContent1, sendingContent2);
}
void PlainProtocol::write(String command,String extraString,int sendingContent0, int sendingContent1, int sendingContent2, int sendingContent3)
{
    sendFrame(command+extraString, 4, sendingContent0, sendingContent1, sendingContent2, sendingContent3);
}
void PlainProtocol::write(String command,String extraString,int sendingContent0, int sendingContent1, int sendingContent2, int sendingContent3, int sendingContent4)
{
    sendFrame(command+extraString, 5, sendingContent0, sendingContent1, sendingContent2, sendingContent3, sendingContent4);
}

boolean PlainProtocol::available()
{
    if (receiveFrame()) {
        receivedContentLenthIndex=0;
        return true;
    }
    else{
        return false;
    }
    
}

int PlainProtocol::read()
{
    if (receivedContentLenthIndex>=receivedContentLenth) {
        return -1;
    }
    
    return receivedContent[receivedContentLenthIndex++];
}

String PlainProtocol::readString()
{
    return receivedCommand.substring(receivedCommandExtraStringIndex);
}

boolean PlainProtocol::equals(String theCommand)
{
//    if (receivedCommand==theCommand) {
//        receivedCommandExtraStringIndex=0;
//        return true;
//    }
//    else
    if (receivedCommand.startsWith(theCommand)){
        receivedCommandExtraStringIndex=theCommand.length();
        return true;
    }
    else{
        return false;
    }
}

//send the frame directly
void PlainProtocol::sendFrame(String theFrame)
{
    if (theFrame.indexOf(';')!=-1) {
        // ';' in the string
        //send the frame directly
        SerialTransceiver.print(theFrame);
    }
    else{
        //no ';' in the string
        //deal with the string as command without content
        sendFrame(theFrame,0);
    }
    
}

/*********************************************************************************
 function     : sendFrame
 feather      : send the frame without address, the content should be int only
 arguments    : (String command, int lenth, ...)
 [IN] command : the command to send
 [IN] lenth   : the lenth of the content
 [IN] content : content (variable argument list)
 *******************************************************************************/
void PlainProtocol::sendFrame(String command, int lenth, ...)
{
    //variable argument list
    va_list pArguement;
    
    //close the sendingAddress mode
    isSendingAddress=false;
    //command output
    sendingCommand=command;
    //content lenth
    sendingContentLenth=lenth;
    
    va_start(pArguement, lenth);
    //content
    for (int i=0; i<lenth; i++) {
        sendingContent[i]=va_arg(pArguement, int);
    }
    va_end(pArguement);
    //sendframe prototype
    sendFrame();
}


/*********************************************************************************
 function     : sendFrame
 feather      : send the frame with address, the content should be int only
 arguments    : (int address, String command, int lenth, ...)
 [IN] address : the address to send
 [IN] command : the command to send
 [IN] lenth   : the lenth of the content
 [IN] content : content (variable argument list)
 *******************************************************************************/
void PlainProtocol::sendFrame(int address, String command, int lenth, ...)
{
    //variable argument list
    va_list pArguement;
    
    //address
    sendingAddress=address;
    //set the sendingAddress mode
    isSendingAddress=true;
    //command
    sendingCommand=command;
    //content lenth
    sendingContentLenth=lenth;
    //content
    va_start(pArguement, lenth);
    for (int i=0; i<lenth; i++) {
        sendingContent[i]=va_arg(pArguement, int);
    }
    va_end(pArguement);
    //sendframe prototype
    sendFrame();
}

//send frame prototype
void PlainProtocol::sendFrame()
{
    int index;        //index of the content
    
    //send the frame according to the Protocol
    if (isSendingAddress) {
        SerialTransceiver.print('#');
        SerialTransceiver.print(sendingAddress);
    }
    SerialTransceiver.print('<');
    SerialTransceiver.print(sendingCommand);
    SerialTransceiver.print('>');
    if (sendingContentLenth!=0) {
        for (index=0; index<sendingContentLenth-1; index++) {
            SerialTransceiver.print(sendingContent[index]);
            SerialTransceiver.print(',');
        }
        SerialTransceiver.print(sendingContent[index]);
    }
    SerialTransceiver.print(';');
}



/*********************************************************************************
 function     : receiveFrame
 feather      : Receive frame from serial. This function should be put in the loop and called periodically.
 arguments    :
 [OUT]  receivedCommand      : command received
 [OUT]  receivedAddress      : address received
 [OUT]  receivedContent      : content received
 [OUT]  receivedContentLenth : the lenth of the content
 return       : True when receiving valid frame
 
 *******************************************************************************/
boolean PlainProtocol::receiveFrame()
{
    static boolean isFrameExist=false;
    static int semicolonIndex;
    boolean isFrameValid=false;
    
    if (SerialTransceiver.available()) {
        
        while (SerialTransceiver.available()) {
            frame += (char)SerialTransceiver.read();
        }
        
        if ((semicolonIndex=frame.indexOf(';')) != -1) {
            isFrameExist=true;
        }
        else{
            if (frame.length() >= MaxFrameBufferLenth) {
                frame="";
            }
        }
    }
    if (isFrameExist) {
        if (parseFrame(frame.substring(0, semicolonIndex))) {
            isFrameValid=true;
        }
        else{
            SerialTransceiver.println("<Wrong frame>;");
        }
        frame=frame.substring(semicolonIndex+1);
        if ((semicolonIndex=frame.indexOf(';')) != -1) {
            isFrameExist=true;
        }
        else{
            isFrameExist=false;
        }
    }
    
    return isFrameValid;
}

//confirm whether the string is a valid number
boolean PlainProtocol::isNumber(String& stringBuf)
{
    int i;
    if (stringBuf[0]<'0'||stringBuf[0]>'9') {
        if (stringBuf[0]!='-') {
            return false;
        }
    }
    for (i=1; i<stringBuf.length(); i++) {
        if (stringBuf[i]<'0'||stringBuf[i]>'9') {
            return false;
        }
    }
    return true;
}

/*********************************************************************************
 function     : parseFrame
 feather      : Parse the frame. This function will be called automatically when receiving a valid frame
 arguments    :
 [OUT]  receivedCommand      : command received
 [OUT]  receivedAddress      : address received
 [OUT]  receivedContent      : content received
 [OUT]  receivedContentLenth : the lenth of the content
 return       : True when frame is valid
 *******************************************************************************/
boolean PlainProtocol::parseFrame(String theFrame)
{
    int commaIndex=theFrame.indexOf(',');             //index of the ','
    int commaIndexLast;                               //index of the last ','
    int leftAngleBracketIndex=theFrame.indexOf('<');  //index of the '<'
    int rightAngleBracketIndex=theFrame.indexOf('>'); //index of the '>'
    int poundSignIndex=theFrame.indexOf('#');         //index of the '#'
    int contentIndex=0;                               //index of the content
    String stringBuf;                                 //string buff
    
    if (leftAngleBracketIndex!=-1   &&
        rightAngleBracketIndex!=-1  &&
        (poundSignIndex==-1 || poundSignIndex<leftAngleBracketIndex)  &&
        leftAngleBracketIndex < rightAngleBracketIndex  &&
        (commaIndex==-1 || rightAngleBracketIndex < commaIndex)
        ) {
        //frame valid
        //command Input
        receivedCommand=theFrame.substring(leftAngleBracketIndex+1, rightAngleBracketIndex);
        
        if (commaIndex==-1) {
            //no comma
            
            if (rightAngleBracketIndex+1==theFrame.length()) {
                //no content
                receivedContentLenth=0;
            }
            else{
                //one contnet
                stringBuf=theFrame.substring(rightAngleBracketIndex+1);
                
                //string to number
                if (isNumber(stringBuf)) {
                    //is a number
                    receivedContent[0]=stringBuf.toInt();
                    receivedContentLenth=1;
                }
                else{
                    //not a number
                    return false;
                }
            }
        }
        else{
            //comma
            stringBuf=theFrame.substring(rightAngleBracketIndex+1,commaIndex);
            if (isNumber(stringBuf)) {
                //is a number
                //content input
                receivedContent[contentIndex++]=stringBuf.toInt();
            }
            else{
                //not a number
                return false;
            }
            //remember the index of the last ','
            commaIndexLast=commaIndex;
            //find the next ','
            commaIndex=theFrame.indexOf(',',commaIndex+1);
            while (commaIndex!=-1) {
                //process until there is no ','
                stringBuf=theFrame.substring(commaIndexLast+1,commaIndex);
                if (isNumber(stringBuf)) {
                    //is a number
                    //content input
                    receivedContent[contentIndex++]=stringBuf.toInt();
                }
                else{
                    //not a number
                    return false;
                }
                //remember the index of the last ','
                commaIndexLast=commaIndex;
                //find the next ','
                commaIndex=theFrame.indexOf(',',commaIndex+1);
            }
            stringBuf=theFrame.substring(commaIndexLast+1);
            if (isNumber(stringBuf)) {
                //is a number
                //content input
                receivedContent[contentIndex]=stringBuf.toInt();
                receivedContentLenth=contentIndex+1;
            }
            else{
                //not a number
                return false;
            }
        }
        
        if (theFrame.indexOf('#')!=-1){
            //address available
            receivedAddress=(theFrame.substring(theFrame.indexOf('#')+1, theFrame.indexOf('<'))).toInt();
            isReceivedAddress=true;
        }
        else{
            isReceivedAddress=false;
        }
    }
    else{
        //frame error
        return false;
    }
    
    //all done successfully
    return true;
}





