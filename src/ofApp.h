#pragma once

#include "ofMain.h"
#include "ofxMaxim.h"
#include "ofxGui.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
    // Audio output and input methods
    
        void audioOut(float * output, int bufferSize, int nChannels);
        void audioIn(float * input, int bufferSize, int nChannels);
     
     
    
    int		bufferSize; /* buffer size */
    int		sampleRate;
    
    ofxPanel gui;
    
    ofParameterGroup params;
    
    ofParameter<double> op1_freq;
    ofParameter<double> op1_amp;
    ofParameter<double> op2_freq;
    ofParameter<double> op2_amp;
    
    ofParameter<double> fm1_freq;
    ofParameter<double> fm1_index;
    ofParameter<double> fm1_amount;
    
    ofParameter<double> fm2_freq;
    ofParameter<double> fm2_index;
    ofParameter<double> fm2_amount;
    
    ofParameter<double> filter_cut;
    ofParameter<double> filter_res;
    
    const double OP1_FREQ_DEF {200};
    const double OP1_AMP_DEF {1};
    
    const double OP2_FREQ_DEF {210};
    const double OP2_AMP_DEF {1};
    
    const double FM1_FREQ_DEF {600};
    const double FM1_INDEX_DEF {100};
    const double FM1_AMOUNT_DEF {1.};
    
    const double FM2_FREQ_DEF {500};
    const double FM2_INDEX_DEF {1000};
    const double FM2_AMOUNT_DEF {1.};
    
//    double am1_amount {1};
//    double am1_freq {13};
    
//    double am2_amount {1};
//    double am2_freq {131};
    
    const double FILTER_CUTOFF_DEF {4000};
    const double FILTER_RES_DEF {40};
		
    maxiOsc op1;
    maxiOsc op2;
    maxiOsc fm1;
    maxiOsc fm2;
//    maxiOsc am1;
//    maxiOsc am2;
    
//    maxiOsc lfo1, lfo2, lfo3, lfo4;

    maxiFilter filter;
};
