// magicLab 2016
// http://www.magiclab.nyc
// author: enrico viola
// license: GPL v.3

#pragma once
#include "ofMain.h"

namespace ofxMotiveTools {
	class Voxel {
	public:
		Voxel() {
			sz = NULL;
			nCams = NULL;
			camFlags = NULL;
			mainFlag = false;
		}

		~Voxel() {
			if (camFlags != NULL)
				delete[] camFlags;
		}

		void set(float x, float y, float z, float * _sz, int * _nCams) {
			setSize(_sz);
			setNumCameras(_nCams);
			setPosition(x, y, z);
		}

		void setSize(float * _sz) { sz = _sz; }
		float getSize() { return *sz; }

		void setNumCameras(int * n) {
			nCams = n;
			camFlags = new bool[*nCams];
			resetFlags();
		}

		int getNumCameras() { return *nCams; }

		void resetFlags() {
			for (int i = 0; i < (*nCams); i++) {
				camFlags[i] = false;
			}
		}

		bool getFlag(int i) { return camFlags[i]; }
		void setFlag(int i, bool b) { camFlags[i] = b; }

		int getNumFlagged() {
			int n = 0;
			for (int i = 0; i < (*nCams); i++) {
				if (camFlags[i])n++;
			}
			return n;
		}
		bool hasMinFlags(int min) {
			return (getNumFlagged() >= min);
		}

		void setPosition(float x, float y, float z) {
			pos.x = x;
			pos.y = y;
			pos.z = z;
		}
		ofVec3f & getPosition() { return pos; }
		float x() { return pos.x; }
		float y() { return pos.y; }
		float z() { return pos.z; }

		std::string asCSVpoint() {
			std::stringstream ss;
			std::string s;
			ss << x() << "," << y() << "," << z();
			s = ss.str();
			return s;
		}

		bool mainFlag;
	protected:
		ofVec3f pos;
		float * sz;
		int * nCams;
		bool * camFlags;
		
	};
}
