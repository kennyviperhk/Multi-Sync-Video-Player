#include "ofApp.h"

int video=0;
//--------------------------------------------------------------
void ofApp::setup(){
    
    ofSetBackgroundColor(20);
    
    // setup the server to listen on 11999
    ofxTCPSettings settings(11999);
    
    // set other options
    //settings.blocking = false;
    //settings.messageDelimiter = "\n";
    
    TCP.setup(settings);
    
    // optionally set the delimiter to something else.  The delimiter in the client and the server have to be the same, default being [/TCP]
    TCP.setMessageDelimiter("\n");
    lastSent = 0;
    
    //videoset
    
    Video1.load("movies/video1.mov");
    Video1.setLoopState(OF_LOOP_NONE);
    
    Video2.load("movies/video2.mov");
    Video2.setLoopState(OF_LOOP_NONE);
    
    Video3.load("movies/video3.mov");
    Video3.setLoopState(OF_LOOP_NONE);
    
    Video4.load("movies/video4.mov");
    Video4.setLoopState(OF_LOOP_NONE);
}

//--------------------------------------------------------------
void ofApp::update(){
    
    // for each client lets send them a message letting them know what port they are connected on
    // we throttle the message sending frequency to once every 100ms
    uint64_t now = ofGetElapsedTimeMillis();
    if(now - lastSent >= 100){
        for(int i = 0; i < TCP.getLastID(); i++){
            if( !TCP.isClientConnected(i) ) continue;
            
            TCP.send(i, "hello client - you are connected on port - "+ofToString(TCP.getClientPort(i)) );
        }
        lastSent = now;
    }
    
    //VIDEO update
    Video1.update();
    Video2.update();
    Video3.update();
    Video4.update();
    
    
}

//--------------------------------------------------------------
void ofApp::draw(){

    ofSetColor(220);
    ofDrawBitmapString("Multi-Sync-Video-Player Server -connect on port: "+ofToString(TCP.getPort()), 10, 20);
    
    ofSetColor(0);
    ofDrawRectangle(600, 10, 400, 10);
    
    ofSetColor(220);
    
    // for each connected client lets get the data being sent and lets print it to the screen
    
    for(unsigned int i = 0; i < (unsigned int)TCP.getLastID(); i++){
        
        if( !TCP.isClientConnected(i) )continue;
        
        // give each client its own color
    //    ofSetColor(255 - i*30, 255 - i * 20, 100 + i*40);
        
        // calculate where to draw the text
        int xPos = 15;
        int yPos = 200 + (12 * i * 4);
        
        // get the ip and port of the client
        string port = ofToString( TCP.getClientPort(i) );
        string ip   = TCP.getClientIP(i);
        string info = "client "+ofToString(i)+" -connected from "+ip+" on port: "+port;
        
        
        // if we don't have a string allocated yet
        // lets create one
        if(i >= storeText.size() ){
            storeText.push_back(string() );
        }
        
        // receive all the available messages, separated by \n
        // and keep only the last one
        string str;
        string tmp;
        do{
            str = tmp;
            tmp = TCP.receive(i);
        }while(tmp!="");
        
        
        // if there was a message set it to the corresponding client
        if(str.length() > 0){
            storeText[i] = str;
            
        }
        
        // draw the info text and the received text bellow it
        ofDrawBitmapString("Client:", xPos-10, yPos-10);
        ofDrawBitmapString(info, xPos, yPos);
        ofDrawBitmapString(storeText[i], 25, yPos + 20);
    }
    
    string guide="Guide:""\n""TAB - Guide""\n""F1 -VIDEO1""\n""F2 -VIDEO2""\n""F3- VIDEO3""\n""F4- VIDEO4";
    
    switch(video){
    //video playlist controller
    case 0:
            ofDrawBitmapString(guide, 10, 60);
    break;

    case 1:
            ofDrawBitmapString("Now playing video1", 10, 60);
            Video1.draw(0,0);
            if (Video1.getIsMovieDone()==true) {
                video++;
                loadandplay();
            }
    break;
    
    case 2:
            ofDrawBitmapString("Now playing video2", 10, 60);
            Video2.draw(0,0);
            if (Video2.getIsMovieDone()==true) {
                Video3.firstFrame();
                video++;
                loadandplay();
            }
    break;
   
    case 3:
            ofDrawBitmapString("Now playing video3", 10, 60);
            Video3.draw(0,0);
            if (Video3.getIsMovieDone()==true) {
                Video4.firstFrame();
                video++;
                loadandplay();
            }
    break;
    
    case 4:
            ofDrawBitmapString("Now playing video4", 10, 60);
            Video4.draw(0,0);
            if (Video4.getIsMovieDone()==true) {
                video=0;
                loadandplay();
            }
    break;
            case 5:
            ofDrawBitmapString("Done", 10, 60);
    }
    
}

void ofApp::loadandplay(){
    switch(video){
        case 0:
            TCP.sendToAll("0");
            break;
        case 1:
            Video1.firstFrame();
            Video1.play();
            TCP.sendToAll("1");
            break;
        case 2:
            Video2.firstFrame();
            Video2.play();
            TCP.sendToAll("2");
            break;
        case 3:
            Video3.firstFrame();
            Video3.play();
            TCP.sendToAll("3");
            break;
        case 4:
            Video4.firstFrame();
            Video4.play();
            TCP.sendToAll("4");
            break;
    }
}
//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    //video playlist controller
    if(key == OF_KEY_TAB){
    video=0;
    TCP.sendToAll("0");
    }else if (key == OF_KEY_F1){
        video=1;
    }else if (key == OF_KEY_F2){
        video=2;
    }else if (key == OF_KEY_F3){
        video=3;
    }else if (key == OF_KEY_F4){
        video=4;
    }
    loadandplay();
}


//--------------------------------------------------------------
void ofApp::keyReleased(int key){
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){
    
}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){
    
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){
    
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){
    
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){
//--------------------------------------------------------------
}
