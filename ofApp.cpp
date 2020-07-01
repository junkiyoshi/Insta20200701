#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openFrameworks");

	ofBackground(0);
	ofSetColor(30, 10, 10);
	ofSetLineWidth(0.5);
	ofNoFill();
	ofEnableBlendMode(ofBlendMode::OF_BLENDMODE_ADD);
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);
}

//--------------------------------------------------------------
void ofApp::draw() {

	int radius = 100;
	float handle_len = radius;
	int number_of_location = 4;
	int deg_span = 360 / number_of_location;

	for (int x = 200; x <= ofGetWidth(); x += 320) {

		for (int y = 200; y <= ofGetHeight(); y += 320) {

			for (int i = 0; i < 200; i++) {

				vector<glm::vec2> location_list;
				vector<float> deg_list;
				for (int deg = 0; deg < 360; deg += deg_span) {

					location_list.push_back(glm::vec2(x + radius * cos(deg * DEG_TO_RAD), y + radius * sin(deg * DEG_TO_RAD)));
					deg_list.push_back(deg + 90);
				}

				for (int k = 0; k < location_list.size(); k++) {

					deg_list[k] += ofMap(ofNoise(location_list[k].x, location_list[k].y, ofGetFrameNum() * 0.01 + i * 0.001), 0, 1, -90, 90);
				}

				ofBeginShape();
				for (int i = 0; i < location_list.size(); i++) {

					int n = (i + 1) % location_list.size();

					ofVertex(location_list[i]);
					ofBezierVertex(
						location_list[i] + glm::vec2(handle_len * cos(deg_list[i] * DEG_TO_RAD), handle_len * sin(deg_list[i] * DEG_TO_RAD)),
						location_list[n] + glm::vec2(handle_len * cos((deg_list[n] + 180) * DEG_TO_RAD), handle_len * sin((deg_list[n] + 180) * DEG_TO_RAD)),
						location_list[n]);
				}
				ofEndShape();
			}
		}
	}
}


//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}