// magicLab 2016
// http://www.magiclab.nyc
// author: enrico viola
// license: GPL v.3

#pragma once
#include "ofMain.h"

namespace ofxMotiveTools {
	class Ray {
	public:
		inline void set(ofVec3f _start, ofVec3f _end) { start = _start; end = _end; }
		ofVec3f start;
		ofVec3f end;
	};

	class Plane {
	public:
		float a;
		float b;
		float c;
		float d;
	};

	static const float defaultCameraRayLength = 6.11;

	class CameraSpecs {
	public:
		CameraSpecs() {
			rayLength = ofxMotiveTools::defaultCameraRayLength;
			fov.set(70, 70);
		}
		ofVec2f fov;
		float rayLength;
	};
}

class ofxMotiveCamera : public ofNode {
public:

	void customDraw() {
		ofDrawAxis(0.5);
	}

	inline void setName(string n) { name = n; }
	inline string getName() { return name; }
	inline void setFPS(int _fps) { fps = _fps; }
	inline int getFPS() { return fps; }
	inline void setIntensity(int n) { intensity = n; }
	inline int getIntensity() { return intensity; }
	inline void setExposure(int n) { exposure = n; }
	inline int getExposure() { return exposure; }
	inline void setVideoType(int vt) { videoType = vt; }
	inline int getVideoType() { return videoType; }
	inline void setResolution(float w, float h) { res.set(w, h); }
	inline float getWidth() { return res.x; }
	inline float getHeight() { return res.y; }

	inline vector<ofxMotiveTools::Ray> & getRays() { return rays; }
	inline float * getMotiveOrientationMatrix() { return motiveMatrix; }
	inline ofMatrix3x3 get3x3Matrix() {
		return ofMatrix3x3(motiveMatrix[0], motiveMatrix[1], motiveMatrix[2], 
						   motiveMatrix[3], motiveMatrix[4], motiveMatrix[5], 
			               motiveMatrix[6], motiveMatrix[7], motiveMatrix[8]);
	}

	inline void setCameraFov(ofVec2f _fov) {
		modelFov = _fov;
	}

	inline float getFovX() { return modelFov.x; }
	inline float getFovY() { return modelFov.y; }

	inline string printInfo() {
		stringstream ss;
		ss << "Camera " << name << ":" << endl;
		ss << "    resolution: " << getWidth() << "x" << getHeight() << endl;
		ss << "    FOV: " << modelFov.x << " - " << modelFov.y << endl;
		ss << "    positioned at: " << getPosition().x << ", " << getPosition().y << ", " << getPosition().z << endl;
		ss << "    FPS: " << fps << endl;
		ss << "    Intensity: " << intensity << endl;
		ss << "    Exposure: " << exposure << endl;
		ss << "    Video Type: " << videoType << endl;
		//ss << "    Orientation (yaw: "<<getHeading()<<" pitch: "<<getPitch()<<" roll: "<<getRoll()<<"):" << endl;
		//ss << "        " << motiveMatrix[0] << "  " << motiveMatrix[1] << "  " << motiveMatrix[2] << endl;
		//ss << "        " << motiveMatrix[3] << "  " << motiveMatrix[4] << "  " << motiveMatrix[5] << endl;
		//ss << "        " << motiveMatrix[6] << "  " << motiveMatrix[7] << "  " << motiveMatrix[8] << endl;
		return ss.str();
	}

	ofxMotiveTools::Ray pilotRay;
	float rayLength;
protected:
	
	vector<ofxMotiveTools::Ray> rays;
	string name;
	ofVec2f res;
	ofVec2f modelFov;
	
	float motiveMatrix[9];
	int fps;
	int intensity;
	int exposure;
	int videoType;
};