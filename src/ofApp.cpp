#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
	
	ofSetFrameRate(60);
	ofSetVerticalSync(true);
	ofBackground(0);
	ofSetLogLevel(OF_LOG_VERBOSE);
	// gif
	frameW = 120;
	frameH = 68;

	gifEncoder.setup(frameW, frameH, .25, 256);
	ofAddListener(ofxGifEncoder::OFX_GIF_SAVE_FINISHED, this, &ofApp::onGifSaved);
	vid.initGrabber(frameW, frameH);
	rgbaFbo.allocate(frameW, frameH, GL_RGB);

	chain.setup(frameW, frameH);
	ofDirectory dir;
	dir.allowExt("fs");
	dir.allowExt("vs");

	//         This is the local ISF folder in bin/data/ISF
	dir.listDir(ofToDataPath("ISF-Folder"));

	dir.sort();
	int count = 0;
	for (int i = 0; i < dir.size(); i++) {
		// Multi Pass Gaussian and Layer Masks are currently broken in OF
		if (!ofIsStringInString(dir.getPath(i), "Multi Pass Gaussian") && !ofIsStringInString(dir.getPath(i), "Layer Mask")) {
			cout << dir.getPath(i) << endl;
			chain.load(dir.getPath(i));
			chain.setEnable(count, false);
			count++;
		}
	}
	index = 0;
	chain.setImage(vid.getTextureReference());


}
void ofApp::onGifSaved(string & fileName) {
	cout << "gif saved as " << fileName << endl;
	ofLogNotice("onGifSaved: " + fileName);
	gifEncoder.reset();
	ofLogNotice("onGifSaved reset");
}
void ofApp::captureFrame() {

	ofPixels fboPixels;
	rgbaFbo.readToPixels(fboPixels);
	gifEncoder.addFrame(fboPixels.getPixels(), frameW, frameH);

	//gifEncoder.addFrame(fbo.)
	ofTexture * tx = new ofTexture();
	tx->allocate(frameW, frameH, GL_RGB);
	tx->loadData(vid.getPixels(), GL_RGB);//, frameW, frameH
	txs.push_back(tx);

	nFrames++;
}
//--------------------------------------------------------------
void ofApp::update() {
	vid.update();
	chain.update();
	ofSetWindowTitle(ofToString(ofGetFrameRate()));
}

//--------------------------------------------------------------
void ofApp::draw() {
	rgbaFbo.begin();
	ofClear(0, 0, 0, 1);
	chain.draw(0, 0);
	rgbaFbo.end();
	rgbaFbo.draw(460, 200);
	for (int i = 0; i < nFrames; i++) {
		txs[i]->draw(i* (frameW / 2 + 5), frameH, frameW / 2, frameH / 2);
	}
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
	//chain.setEnable("ZoomBlur", !chain.getEnable("ZoomBlur"));
	if (key == OF_KEY_LEFT) {
		chain.setEnable(index, false);
		index--;
		if (index < 0) {
			index = chain.size() - 1;;
		}
		chain.setEnable(index, true);
	}
	else if (key == OF_KEY_RIGHT) {
		chain.setEnable(index, false);
		index++;
		if (index >= chain.size()) {
			index = 0;
		}
		chain.setEnable(index, true);
	}
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {
	switch (key) {
	case 'f':
		ofToggleFullscreen();
		break;
	case ' ':
		captureFrame();
		break;
	case 's':
		cout << "start saving\n" << endl;
		gifEncoder.save(ofToString( index) + ".gif");
		break;
	default:
		break;
	}
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h) {

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg) {

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo) {

}
