/* This is an example of how to integrate maximilain into openFrameworks,
 including using audio received for input and audio requested for output.
 
 
 You can copy and paste this and use it as a starting example.
 
 */

#include "ofApp.h"

vector<double> display_buffer;
bool saving = false;

//--------------------------------------------------------------
void ofApp::setup(){
    
    ofBackground(50);
    ofSetColor(200);
    ofSetCircleResolution(100);
    ofSetVerticalSync(true);
    
    ofSetFrameRate(60);
    ofBackground(0,0,0);
    
    // audio setup
    sampleRate 	= 44100; /* Sampling Rate */
    bufferSize	= 512; /* Buffer Size. you have to fill this buffer with sound using the for loop in the audioOut method */
    display_buffer.resize(bufferSize);
    
    ofxMaxiSettings::setup(sampleRate, 2, bufferSize);
    
    ofSetVerticalSync(true);
    ofEnableAlphaBlending();
    ofEnableSmoothing();
    
    ofSoundStreamSetup(2,2,this, sampleRate, bufferSize, 4); /* this has to happen at the end of setup - it switches on the DAC */
    
    // GUI
    
    params.add(op1_freq.set("osc 1 freq", OP1_FREQ_DEF, 10, 5000));
    params.add(op1_amp.set("osc 1 volume", OP1_AMP_DEF, 0, 1));
    params.add(fm1_freq.set("fm 1 freq", FM1_FREQ_DEF, 20, 5000));
    params.add(fm1_index.set("fm 1 index", FM1_INDEX_DEF, 1, 5000));
    params.add(fm1_amount.set("fm 1 amount", FM1_AMOUNT_DEF, 0, 1));
    
    params.add(op2_freq.set("osc 2 freq", OP2_FREQ_DEF, 10, 20000));
    params.add(op2_amp.set("osc 2 volume", OP2_AMP_DEF, 0, 1));
    params.add(fm2_freq.set("fm 2 freq", FM2_FREQ_DEF, 20, 5000));
    params.add(fm2_index.set("fm 2 index", FM2_INDEX_DEF, 1, 5000));
    params.add(fm2_amount.set("fm 2 amount", FM2_AMOUNT_DEF, 0, 1));
    
    params.add(filter_cut.set("filter cutoff", FILTER_CUTOFF_DEF, 20, 20000));
    params.add(filter_res.set("filter res", FILTER_RES_DEF, 0, 100));
    
    gui.setup(params);
//    gui.add(radius.set( "radius", 140, 10, 300 ));
    
    
}

//--------------------------------------------------------------
void ofApp::update(){
    
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    if(saving) {
        ofBeginSaveScreenAsPDF(ofToString(ofGetFrameNum()) + ".pdf");
    }
    ofPushMatrix();
    float scale = 100;
    ofTranslate(ofGetWidth()/2, ofGetHeight()/2);
    ofPolyline line;
    double angle;
//    double v1_x,v1_y;
    for(int i = 0 ; i < bufferSize ; i++) {
        angle = i * 0.1;
        line.curveTo(display_buffer[i] * sin(angle) * scale, display_buffer[i] * cos(angle) * scale);
    }
//    line.curveTo(v1_x, v1_y);
    line.draw();
    ofPopMatrix();
    
    if(saving) {
        ofEndSaveScreenAsPDF();
        saving = false;
    }
    
    // GUI
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
  
        double filter_out = filter.lores(mix, filter_cut, filter_res);

        output[i*nChannels    ] = filter_out;
        output[i*nChannels + 1] = filter_out;
        
        display_buffer[i] = filter_out;

    }
    
    
}

//--------------------------------------------------------------
void ofApp::audioIn(float * input, int bufferSize, int nChannels){
    
    for(int i = 0; i < bufferSize; i++){
        /* you can also grab the data out of the arrays*/
        
    }
    
}


//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
    if(key == ' ') {
        saving = true;
    }
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
