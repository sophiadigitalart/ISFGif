#pragma once
#include "ofMain.h"
#include "ofxGifEncoder.h"
#include "ofxISF.h"

class ofApp : public ofBaseApp
{
public:

	ofxISF::Chain chain;
	ofVideoGrabber vid;
	int index;
	void setup();
	void update();
	void draw();

	void keyPressed(int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y);
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void mouseEntered(int x, int y);
	void mouseExited(int x, int y);
	void windowResized(int w, int h);
	void dragEvent(ofDragInfo dragInfo);
	void gotMessage(ofMessage msg);
	ofxGifEncoder							gifEncoder;
	void									onGifSaved(string & fileName);
	int										frameW, frameH;
	int										nFrames;
	void									captureFrame();
	//8 bits red, 8 bits green, 8 bits blue, from 0 to 255 in 256 steps
	ofFbo 									rgbaFbo; // with alpha
	vector <ofTexture *>					txs; // for previewing

};
