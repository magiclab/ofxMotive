// magicLab 2016
// http://www.magiclab.nyc
// author: enrico viola
// license: GPL v.3

#pragma once
#include "ofMain.h"
#include "ofxMotiveCamera.h"
#include  "NPTrackingTools.h"
#include "VoxelBox.h"
#include "ofxXmlSettings.h"
#include "GeometryJutsu.h"
#include "MatrixJutsu.h"
#include "ofxQuickHull.h"

//#define SIM_DATA

class ofxMotive {
public:

	ofxMotive();
	~ofxMotive();
	void initAll();
	void reset();
	void initMotiveAPI();
	void closeMotiveAPI();
	void loadTTP(string _pthTTP);
	void loadCAL(string _pthCAL);
	void setup(string _pthTTP, string _pthCAL);
	void setupVoxels();
	void setupRayCasting();
	void loadRayLengths(ofxXmlSettings & xml);
	vector<ofxMotiveTools::Plane> getPlanesFromRays(int camId);
	void getPlaneFromRays(ofxMotiveTools::Ray & ray0, ofxMotiveTools::Ray & ray1, ofxMotiveTools::Plane & p);
	void getPlaneFromRayBase(vector<ofxMotiveTools::Ray> & rays, ofxMotiveTools::Plane & p);
	bool isVoxelInFrustum(ofxMotiveTools::Voxel * vx, vector<ofxMotiveTools::Plane> & frustumPlanes);
	void raycastAndFlagVoxels();
	void computeVolumeHull();
	vector<ofVec3f> getFlaggedVoxelCentroids();
	ofVboMesh & getVboVolume() { return vboHull; }

	void getCameraInfos();
	void flagVoxels();
	bool raycastCaptureVolume(int camId, ofxMotiveTools::VoxelBox & box);
	static bool flagCaptureVolume(int camId, ofxMotiveTools::VoxelBox & box);

	void makeCameraRays(int camId);
	ofxMotiveTools::Ray makeRay(int camId, float sX, float sy, float rayL);
	ofxMotiveTools::Ray makeRayFromFov(int camId, float ax, float ay);
	ofxMotiveTools::CameraSpecs getCameraSpecs(string camModel);
	float getRayLengthForModel(string camModel);
	ofVec2f getFovForModel(string camModel);
	string getModelFromName(string camName);

	void draw();
	void drawCameras();
	void drawSpace();
	void drawVoxels();
	void drawVoxel(ofxMotiveTools::Voxel * vx);
	void drawRays();
	void drawCameraRays(ofxMotiveCamera & c);
	void drawRay(ofxMotiveTools::Ray & r);
	void drawVolumeHull();

	static void checkNPResult(NPRESULT res);
	static ofVec3f makeSearchSpace(float maxH);

	void orientCameraFromPilotRay(int camId);
	void orientCameraFromMatrixEA(int camId);
	void orientCameraFromMatrixQuat(int camId);

	inline void setMinNumCameras(int n) { minNumCams = n; }
	void setVoxelSize(float sz);
	inline void setWinding(bool b) { bWinding = b; }

	void saveVoxels(string pth = "");
	void saveTestRays();

	inline string getTTPPath() { return pthTTP; }
	inline string getCALPath() { return pthCAL; }
	inline bool isMotiveAPIInited() { return bInited; }
	inline int getNumCameras() { return numCams; }
	inline int getMinNumCameras() { return minNumCams; }
	inline float getMaxCameraHeight() { return maxCamH; }
	inline float getVoxelSize() { return voxelSz; }
	inline bool getWinding() { return bWinding; }

	void set3x3Mat(float * mat, float f0, float f1, float f2, float f3, float f4, float f5, float f6, float f7, float f8);

	bool bDrawVoxels;
	bool bDrawFlaggedVoxels;
	bool bDrawRays;
protected:
#ifdef  SIM_DATA
	ofxMotiveTools::Ray simRays[6][4]; 
	vector<ofVec3f> simPos;
	vector<string> simNames;
	vector<ofVec2f> simRes;
	vector<ofxMotiveTools::Ray> simPilotRays;
	float simOrMat[6][9];
#endif //  SIM_DATA

	ofxMotiveTools::VoxelBox voxelBox;
	ofVec3f spaceSize;
	ofBoxPrimitive boxSpace;
	ofVboMesh vboVoxel;
	ofVboMesh vboHull;
	vector<ofxMotiveCamera> cams;
	map<string, ofxMotiveTools::CameraSpecs> camSpecs;
	string pthTTP;
	string pthCAL;
	float maxCamH;
	float voxelSz;
	int numCams;
	int minNumCams;
	bool bInited;
	bool bFlagged;
	bool bWinding;
};