#include "ofApp.h"

#define RECONNECT_TIME 400
 int recivedata = 0;
//--------------------------------------------------------------
void ofApp::setup(){
    ofSetBackgroundColor(230);
    
    // our send and recieve strings
    msgTx    = "";
    msgRx    = "";
    
    ofxTCPSettings sett4ings("127.0.0.1", 11999);
    
    // set other options:
    //settings.blocking = false;
    //settings.messageDelimiter = "\n";
    
    // connect to the server - if this fails or disconnects
    // we'll check every few seconds to see if the server exists
    tcpClient.setup(sett4ings);
    
    // optionally set the delimiter to something else.  The delimiter in the client and the server have to be the same
    tcpClient.setMessageDelimiter("\n");
    
    connectTime = 0;
    deltaTime = 0;
    
    //videoset
    ofSetVerticalSync(true);
    Video1.load("movies/video1.mov");
    Video1.setLoopState(OF_LOOP_NORMAL);
    Video1.play();
    Video2.load("movies/video2.mov");
    Video2.setLoopState(OF_LOOP_NORMAL);
    Video2.play();
    Video3.load("movies/video3.mov");
    Video3.setLoopState(OF_LOOP_NORMAL);
    Video3.play();
    Video4.load("movies/video4.mov");
    Video4.setLoopState(OF_LOOP_NORMAL);
    Video4.play();
//
}

//--------------------------------------------------------------
void ofApp::update(){
    
    //VIDEO update
    Video1.update();
    Video2.update();
    Video3.update();
    Video4.update();
    
    
    //
    
    if(tcpClient.isConnected()){
        // we are connected - lets try to receive from the server
        string str = tcpClient.receive();
        
        if (str == "1"){
        ofDrawBitmapString("v1", 15, 500);
        }
        
    if( str.length() > 0 ){
            msgRx = str;
        }
    }else{
        msgTx = "";
        // if we are not connected lets try and reconnect every 5 seconds
        deltaTime = ofGetElapsedTimeMillis() - connectTime;
        
        if( deltaTime > 5000 ){
            tcpClient.setup("127.0.0.1", 11999);
            tcpClient.setMessageDelimiter("\n");
            connectTime = ofGetElapsedTimeMillis();
        }
        
    }
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    //ofSetColor(20);
    ofDrawBitmapString("Multi Video Player Client", 15, 20);
    
    if(tcpClient.isConnected()){
        
        if(!msgTx.empty()){
            ofDrawBitmapString("sending:", 15, 55);
            ofDrawBitmapString(msgTx, 85, 55);
        }else{
            ofDrawBitmapString("status: type something to send data to port 11999", 15, 30);
        }
        ofDrawBitmapString("from server: " + msgRx, 15, 40);
    }else{
        ofDrawBitmapString("status: server not found. launch server app and check ports!\n\nreconnecting in "+ofToString( (5000 - deltaTime) / 1000 )+" seconds", 15, 45);
    }
    
    if (msgRx == "0"){
        recivedata=0;
    }else if (msgRx == "1") {
        Video1.firstFrame();
        recivedata=1;
    }else if (msgRx == "2"){
        Video2.firstFrame();
        recivedata=2;
    }else if (msgRx == "3"){
        Video3.firstFrame();
        recivedata=3;
    }
    
    if (recivedata == 0) {
        ofDrawBitmapString("Server Checking", 10, 60);
    }
    else if (recivedata == 1) {
        ofDrawBitmapString("Now playing video1", 10, 60);
        Video1.draw(0,0);
    }else if (recivedata == 2) {
        ofDrawBitmapString("Now playing video2", 10, 60);
        Video2.draw(0,0);
    }else if (recivedata == 3) {
        ofDrawBitmapString("Now playing video3", 10, 60);
        Video3.draw(0,0);
    }else if (recivedata == 4) {
        ofDrawBitmapString("Now playing video4", 10, 60);
        Video4.draw(0,0);
    }


}

//--------------------------------------------------------------
void ofApp::keyPressed(ofKeyEventArgs & key){
    // you can only type if you're connected
    // we accumulate 1 line of text and send every typed character
    // on the next character after a breakline we clear the buffer
    if(tcpClient.isConnected()){
        if(key.key == OF_KEY_BACKSPACE || key.key == OF_KEY_DEL){
            if( !msgTx.empty() ){
                msgTx = msgTx.substr(0, msgTx.size()-1);
            }
        }else if (key.codepoint != 0){
            ofUTF8Append(msgTx, key.codepoint);
        }
        tcpClient.send(msgTx);
        if (!msgTx.empty() && msgTx.back() == '\n') {
            msgTx.clear();
        }
    }
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
    
}
