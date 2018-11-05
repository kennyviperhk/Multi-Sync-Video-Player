#pragma once

#include "ofMain.h"
#include "ofxNetwork.h"

class ofApp : public ofBaseApp{
    
public:
    
    void setup();
    void update();
    void draw();
    
    void keyPressed(ofKeyEventArgs & key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void mouseEntered(int x, int y);
    void mouseExited(int x, int y);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    
    ofxTCPClient tcpClient;
    string msgTx, msgRx , msgEx;
    
    ofTrueTypeFont  mono;
    ofTrueTypeFont  monosm;
    
    float counter;
    int connectTime;
    int deltaTime;
    
    int size;
    
    ofVideoPlayer Video1;
    ofVideoPlayer Video2;
    ofVideoPlayer Video3;
    ofVideoPlayer Video4;
    ofVideoPlayer Video5;
};


