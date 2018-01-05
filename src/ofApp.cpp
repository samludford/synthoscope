/* This is an example of how to integrate maximilain into openFrameworks,
 including using audio received for input and audio requested for output.
 
 
 You can copy and paste this and use it as a starting example.
 
 */

#include "ofApp.h"

vector<double> display_buffer;

//--------------------------------------------------------------
void ofApp::setup(){
    
    // drawing
    
    ofSetColor(200);
    ofSetCircleResolution(100);
    ofSetVerticalSync(true);
    ofSetFrameRate(60);
    ofBackground(0);
    
    // audio
    
    sampleRate 	= 44100;
    bufferSize	= 512;
    display_buffer.resize(bufferSize);
    
    ofxMaxiSettings::setup(sampleRate, 2, bufferSize);
    
    ofSetVerticalSync(true);
    ofEnableAlphaBlending();
    ofEnableSmoothing();
    
    ofSoundStreamSetup(2,2,this, sampleRate, bufferSize, 4);
    
    // gui
    
    params.add(op1_freq.set("carrier 1 freq", OP1_FREQ_DEF, 10, 5000));
    params.add(op1_amp.set("carrier 1 vol", OP1_AMP_DEF, 0, 1));
    params.add(fm1_freq.set("mod 1 freq", FM1_FREQ_DEF, 20, 5000));
    params.add(fm1_index.set("mod 1 index", FM1_INDEX_DEF, 1, 5000));
    params.add(fm1_amount.set("fm 1 amount", FM1_AMOUNT_DEF, 0, 1));
    
    params.add(op2_freq.set("carrier 2 freq", OP2_FREQ_DEF, 10, 20000));
    params.add(op2_amp.set("carrier 2 vol", OP2_AMP_DEF, 0, 1));
    params.add(fm2_freq.set("mod 2 freq", FM2_FREQ_DEF, 20, 5000));
    params.add(fm2_index.set("mod 2 index", FM2_INDEX_DEF, 1, 5000));
    params.add(fm2_amount.set("fm 2 amount", FM2_AMOUNT_DEF, 0, 1));
    
    gui.setup(params);
    
    
}

//--------------------------------------------------------------
void ofApp::update(){
    
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    ofPushMatrix();
    float scale = 100;
    ofTranslate(ofGetWidth()/2, ofGetHeight()/2);
    ofPolyline line;
    double angle;
    for(int i = 0 ; i < bufferSize ; i++) {
        angle = i * 0.1;
        line.curveTo(display_buffer[i] * sin(angle) * scale, display_buffer[i] * cos(angle) * scale);
    }
    line.draw();
    ofPopMatrix();
    
    gui.draw();
}

//--------------------------------------------------------------
void ofApp::audioOut(float * output, int bufferSize, int nChannels) {
    
    for (int i = 0; i < bufferSize; i++){
        
        double fm1_out = fm1.sinewave(fm1_freq) * fm1_index * fm1_amount;
        double fm2_out = fm2.sinewave(fm2_freq) * fm2_index * fm2_amount;
        
        double op1_out = op1.sinewave(op1_freq + fm1_out);
        double op2_out = op2.sinewave(op2_freq + fm2_out);
        
        double mix = ((op1_out * op1_amp) + (op2_out * op2_amp))*0.5;

        output[i*nChannels    ] = mix;
        output[i*nChannels + 1] = mix;
        
        display_buffer[i] = mix;

    }
    
    
}

//--------------------------------------------------------------
void ofApp::audioIn(float * input, int bufferSize, int nChannels){
    
    for(int i = 0; i < bufferSize; i++){

    }
    
}


//--------------------------------------------------------------
void ofApp::keyPressed(int key){
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y){
    
    
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
void ofApp::windowResized(int w, int h){
    
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){
    
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){
    
}
