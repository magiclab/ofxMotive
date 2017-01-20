// magicLab 2016
// http://www.magiclab.nyc
// author: enrico viola
// license: GPL v.3

#include "ofxMotive.h"

ofxMotive::ofxMotive() {
	initAll();
}

void ofxMotive::initAll() {
	bWinding = false;
	bInited = false;
	bFlagged = false;
	bDrawVoxels = false;
	bDrawFlaggedVoxels = false;
	bDrawRays = false;
	setVoxelSize(0.3);
	setMinNumCameras(1);
	initMotiveAPI();
	vboHull.setUsage(GL_STATIC_DRAW);
	vboHull.setMode(OF_PRIMITIVE_TRIANGLES);

#ifdef SIM_DATA
	numCams = 6;

	simPos.clear();
	simPos.resize(numCams);
	simPos[0].set(-2.10389, 3.19339, -0.135761);//(2.18659, 3.18719, -0.235848);
	simPos[1].set(-1.05608, 3.20073, -0.123571);//(0.92312, 3.22028, -0.147699);
	simPos[2].set(0.265263, 3.19557, -0.109868);//(-0.392187, 3.1976, -0.102874);
	simPos[3].set(2.18659, 3.18719, -0.235848);//(-2.10389, 3.19339, -0.135761);
	simPos[4].set(0.92312, 3.22028, -0.147699);//(0.265263, 3.19557, -0.109868);
	simPos[5].set(-0.392187, 3.1976, -0.102874);//(-1.05608, 3.20073, -0.123571);

	simNames.clear();
	simNames.resize(numCams);
	simNames[0] = "Prime 17W";
	simNames[1] = "Prime 13W";
	simNames[2] = "Prime 13W";
	simNames[3] = "Prime 17W";
	simNames[4] = "Prime 13W";
	simNames[5] = "Prime 13W";

	simRes.clear();
	simRes.resize(numCams);
	simRes[0].set(1664, 1088);
	simRes[1].set(1280, 1024);
	simRes[2].set(1280, 1024);
	simRes[3].set(1664, 1088);
	simRes[4].set(1280, 1024);
	simRes[5].set(1280, 1024);

	simPilotRays.clear();
	simPilotRays.resize(numCams);
	simPilotRays[0].set(ofVec3f(2.18659, 3.18719, -0.235848), ofVec3f(-7.25521, -8.64797));
	simPilotRays[1].set(ofVec3f(0.92312, 3.22028, -0.147699), ofVec3f(1.35577, -2.853));
	simPilotRays[2].set(ofVec3f(-0.392187, 3.1976, -0.102874), ofVec3f(-0.183891, -2.8971));
	simPilotRays[3].set(ofVec3f(-2.10389, 3.19339, -0.135761), ofVec3f(8.98991, -7.17779));
	simPilotRays[4].set(ofVec3f(0.265263, 3.19557, -0.109868), ofVec3f(0.269405, -2.90012));
	simPilotRays[5].set(ofVec3f(-1.05608, 3.20073, -0.123571), ofVec3f(-0.949836, -2.89596));


	set3x3Mat(simOrMat[0], 0.769506, -0.197645, 0.607286, -0.616299, 0.0194912, 0.787271, -0.167437, -0.98008, -0.10681);
	set3x3Mat(simOrMat[1], 0.0199351, 0.997893, -0.0617402, 0.0627024, 0.0603833, 0.996204, 0.997833, -0.0237308, -0.0613666);
	set3x3Mat(simOrMat[2], 0.0158529, 0.999684, -0.0195289, 0.0403527, 0.018876, 0.999007, 0.99906, -0.0166253, -0.0400408);
	set3x3Mat(simOrMat[3], 0.686276, 0.0936363, -0.721288, 0.724583, -0.00173502, 0.689185, 0.0632812, -0.995605, -0.0690379);
	set3x3Mat(simOrMat[4], 0.00547545, 0.99998, 0.00322983, 0.0508805, -0.00350398, 0.998698, 0.99869, -0.00530408, -0.0508987);
	set3x3Mat(simOrMat[5], 0.00168861, 0.999982, -0.00571552, 0.0351506, 0.00565287, 0.999366, 0.99938, -0.00188854, -0.0351405);

	/*
	0.769506, -0.197645,  0.607286,-0.616299,  0.0194912,  0.787271, -0.167437, -0.98008, -0.10681
	0.0199351,  0.997893, -0.0617402, 0.0627024,  0.0603833,  0.996204, 0.997833, -0.0237308, -0.0613666
	0.0158529,  0.999684, -0.0195289, 0.0403527,  0.018876,  0.999007, 0.99906, -0.0166253, -0.0400408
	0.686276,  0.0936363, -0.721288, 0.724583, -0.00173502,  0.689185, 0.0632812, -0.995605, -0.0690379
	0.00547545,  0.99998,  0.00322983, 0.0508805, -0.00350398,  0.998698, 0.99869, -0.00530408, -0.0508987
	0.00168861,  0.999982, -0.00571552, 0.0351506,  0.00565287,  0.999366, 0.99938, -0.00188854, -0.0351405
	*/

	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 4; j++) {
			simRays[i][j].start = simPos[i];
		}
	}
	simRays[0][0].end.set(11.5527, 1.30668, 6.26557);
	simRays[0][1].end.set(0.205974, -10.8284, 5.25799);
	simRays[0][2].end.set(1.19819, -10.6298, -5.52605);
	simRays[0][3].end.set(12.345, 1.2939, -4.4558);

	simRays[1][0].end.set(-3.80988, -0.821424, 3.5437);
	simRays[1][1].end.set(-3.80263, -1.06103, -3.51532);
	simRays[1][2].end.set(1.80427, -0.999012, -3.49857);
	simRays[1][3].end.set(1.8356, -0.760375, 3.50381);

	simRays[2][0].end.set(-2.53837, -0.760126, 3.59177);
	simRays[2][1].end.set(-2.54397, -1.08185, -3.42979);
	simRays[2][2].end.set(3.03849, -1.08894, -3.45085);
	simRays[2][3].end.set(3.10966, -0.767927, 3.55211);

	simRays[3][0].end.set(2.45824, -11.1646, 4.76343);
	simRays[3][1].end.set(-10.2896, -0.801522, 7.47608);
	simRays[3][2].end.set(-12.262, -0.57202, -3.09021);
	simRays[3][3].end.set(0.296396, -10.7927, -5.89522);

	simRays[4][0].end.set(-1.52483, -0.846976, 3.68309);
	simRays[4][1].end.set(-1.66587, -1.28302, -3.34574);
	simRays[4][2].end.set(3.93645, -0.924111, -3.45736);
	simRays[4][3].end.set(4.07606, -0.490973, 3.52593);

	simRays[5][0].end.set(-3.03635, -0.866689, 3.59847);
	simRays[5][1].end.set(-3.11091, -1.1049, -3.46547);
	simRays[5][2].end.set(2.47207, -0.961933, -3.52402);
	simRays[5][3].end.set(2.62304, -0.723075, 3.46738);
#endif
}

void ofxMotive::reset() {
	closeMotiveAPI();
	initAll();
}

ofxMotive::~ofxMotive() {
	closeMotiveAPI();
}

void ofxMotive::initMotiveAPI() {
	std::cout << "=== MagicLab Motive Tool ===" << std::endl;
	std::cout << "Initializing Optitrack devices...";
	TT_Initialize();
	std::cout << "done." << std::endl;
	//safety update to make sure we have all the cameras
	TT_Update();

	bInited = true;
}

void ofxMotive::closeMotiveAPI() {
	if (bInited) {
		TT_Shutdown();
	}
}

void ofxMotive::checkNPResult(NPRESULT res) {
	if (res != NPRESULT_SUCCESS) {
		cout<<"ofxMotive: API error: "<<TT_GetResultString(res)<<endl;
		ofExit();
	}
}

ofVec3f ofxMotive::makeSearchSpace(float maxH) {
	ofVec3f v;
	v.y = maxH;
	v.x = v.y * 3;
	v.z = v.x;
	return v;
}

void ofxMotive::loadRayLengths(ofxXmlSettings & xml) {
	camSpecs.clear();
	if (xml.tagExists("ray_length")) {
		xml.pushTag("ray_length");
		int nTags = xml.getNumTags("cam");
		for (int i = 0; i < nTags; i++) {
			string model = xml.getAttribute("cam", "model", "default", i);
			camSpecs[model].rayLength = xml.getValue("cam",1.1,i);
			camSpecs[model].fov.x = xml.getAttribute("cam", "fov_x", 70, i);
			camSpecs[model].fov.y = xml.getAttribute("cam", "fov_y", 70, i);
		}
		xml.popTag();
	}
	else {
		ofLogError("ofxMotive::loadRayLengths", "cannot find <ray_length>");
	}
}

string ofxMotive::getModelFromName(string camName) {
	return camName.substr(6, 3);
}

ofxMotiveTools::CameraSpecs ofxMotive::getCameraSpecs(string camModel) {
	for (map<string, ofxMotiveTools::CameraSpecs>::const_iterator it = camSpecs.begin(); it != camSpecs.end(); it++) {
		if (it->first == camModel) {
			return it->second;
		}
	}
	return ofxMotiveTools::CameraSpecs();
}

float ofxMotive::getRayLengthForModel(string camModel) {
	return getCameraSpecs(camModel).rayLength;
}

ofVec2f ofxMotive::getFovForModel(string camModel) {
	return getCameraSpecs(camModel).fov;
}

void ofxMotive::setVoxelSize(float sz) {
	voxelSz = sz;
	vboVoxel.clear();
	ofBoxPrimitive tmp;
	tmp.set(sz,sz,sz,1,1,1);
	vboVoxel = tmp.getMesh();
}

void ofxMotive::loadTTP(string _pthTTP) {
	pthTTP = _pthTTP;
	cout << "Loading project: " << pthTTP << "...";
	checkNPResult(TT_LoadProject(pthTTP.c_str()));
	cout << "done." << endl;
}

void ofxMotive::loadCAL(string _pthCAL) {
	pthCAL = _pthCAL;
	cout << "Loading calibration: " << pthCAL << "...";
	checkNPResult(TT_LoadProject(pthTTP.c_str()));
	cout << "done." << endl;
}

void ofxMotive::set3x3Mat(float * mat, float f0, float f1, float f2, float f3, float f4, float f5, float f6, float f7, float f8) {
	mat[0] = f0;
	mat[1] = f1;
	mat[2] = f2;
	mat[3] = f3;
	mat[4] = f4;
	mat[5] = f5;
	mat[6] = f6;
	mat[7] = f7;
	mat[8] = f8;
}

void ofxMotive::getCameraInfos() {
#ifdef SIM_DATA
	
	
#else
	numCams = TT_CameraCount();
#endif
	cams.resize(numCams);
	cout << cams.size() << " cameras found" << endl;
	maxCamH = 0;
	for (int i = 0; i < numCams; i++) {
#ifdef SIM_DATA
		float camY = simPos[i].y;
		cams[i].setName(simNames[i]);
#else
		float camY = TT_CameraYLocation(i);
		//cout << "got pos Y" << endl;
		cams[i].setName(TT_CameraName(i));
		//cout << "got name" << endl;
#endif // SIM_DATA
		
		if (camY > maxCamH) {
			maxCamH = camY;
		}
		string camModel = getModelFromName(cams[i].getName());
		//cout << "got model" << endl;
		cams[i].rayLength = getRayLengthForModel(camModel);
		//cout << "got raylength" << endl;
#ifdef SIM_DATA
		for (int j = 0; j < 9; j++) {
			cams[i].getMotiveOrientationMatrix()[j] = simOrMat[i][j];
		}
		cams[i].setPosition(simPos[i].x, camY, simPos[i].z);
		cams[i].setFPS(100);
		cams[i].setIntensity(15);
		cams[i].setExposure(250);
		cams[i].setVideoType(2);
		cams[i].setResolution(simRes[i].x, simRes[i].y);

		cams[i].pilotRay.set(simPilotRays[i].start, simPilotRays[i].end);
#else
		for (int j = 0; j < 9; j++) {
			cams[i].getMotiveOrientationMatrix()[j] = TT_CameraOrientationMatrix(i, j);
		}
		//cout << "got matrix" << endl;
		
		cams[i].setPosition(TT_CameraXLocation(i), camY, TT_CameraZLocation(i));
		//cout << "got position" << endl;
		cams[i].setFPS(TT_CameraFrameRate(i));
		//cout << "got FPS" << endl;
		cams[i].setIntensity(TT_CameraIntensity(i));
		//cout << "got Intensity" << endl;
		cams[i].setExposure(TT_CameraExposure(i));
		//cout << "got exposure" << endl;
		cams[i].setVideoType(TT_CameraVideoType(i));
		//cout << "got vt" << endl;

		int w;
		int h;
		TT_CameraPixelResolution(i, w, h);
		cams[i].setResolution(w,h);
		//cout << "got resolution" << endl;

		cams[i].pilotRay = makeRay(i, cams[i].getWidth() / 2, cams[i].getHeight() / 2, cams[i].rayLength);
		//cout << "got pilot ray" << endl;
#endif
		
		cams[i].setCameraFov(getFovForModel(camModel));
		//cout << "got fov" << endl;

		orientCameraFromPilotRay(i);
		
		cout << cams[i].printInfo() << endl;
	}

	spaceSize = makeSearchSpace(maxCamH);
	boxSpace.set(spaceSize.x, spaceSize.y, spaceSize.z,1,1,1);
}

void ofxMotive::orientCameraFromPilotRay(int camId) {
	cams[camId].lookAt(cams[camId].pilotRay.end);
}

void ofxMotive::orientCameraFromMatrixEA(int camId) {
	ofQuaternion q;
	ofVec3f ea = ofxCodeJutsu::Matrix::rotMatrix2degEulerAngles(cams[camId].get3x3Matrix());
	ofxCodeJutsu::Matrix::applyEulerAngles(ea, 'x', 'y', 'z', q);
	cams[camId].setOrientation(q);
}
void ofxMotive::orientCameraFromMatrixQuat(int camId) {
	ofQuaternion q;
	q = ofxCodeJutsu::Matrix::rotMatrix2quaternion(cams[camId].get3x3Matrix());
	cams[camId].setOrientation(q);
}

bool ofxMotive::flagCaptureVolume(int camId, ofxMotiveTools::VoxelBox & box) {
	int camW;
	int camH;
	bool b = TT_CameraPixelResolution(camId, camW, camH);
	if (b) {
		for (int x = 0; x < box.getNumVoxelsX(); x++) {
			for (int y = 0; y < box.getNumVoxelsY(); y++) {
				for (int z = 0; z < box.getNumVoxelsZ(); z++) {
					ofxMotiveTools::Voxel * vx = box.getVoxel(x, y, z);
					float sx;
					float sy;
					TT_CameraBackproject(camId, vx->x(), vx->y(), vx->z(), sx, sy);
					TT_CameraDistort2DPoint(camId, sx, sy);
					vx->setFlag(camId, ofxMotiveTools::VoxelBox::isPointCaptured(sx, sy, camW, camH));
				}
			}
		}
	}
	return b;
}

bool ofxMotive::raycastCaptureVolume(int camId, ofxMotiveTools::VoxelBox & box) {
	if (camId < 0 || camId >= cams.size())return false;
	
	cout << "Testing voxels against camera " << camId << endl;

	vector<ofxMotiveTools::Plane> frustumPlanes = getPlanesFromRays(camId);

	for (int x = 0; x < box.getNumVoxelsX(); x++) {
		for (int y = 0; y < box.getNumVoxelsY(); y++) {
			for (int z = 0; z < box.getNumVoxelsZ(); z++) {
				ofxMotiveTools::Voxel * vx = box.getVoxel(x, y, z);
				vx->setFlag(camId, isVoxelInFrustum(vx, frustumPlanes));
			}
		}
	}
	return true;
}

bool ofxMotive::isVoxelInFrustum(ofxMotiveTools::Voxel * vx, vector<ofxMotiveTools::Plane> & frustumPlanes) {
	for (int i = 0; i < frustumPlanes.size(); i++) {
		if (ofxCodeJutsu::Geometry::isPointInFrontOfPlane(vx->getPosition(), frustumPlanes[i].a, frustumPlanes[i].b, frustumPlanes[i].c, frustumPlanes[i].d)==bWinding) {
			return false;
		}
	}
	return true;
}

vector<ofxMotiveTools::Plane> ofxMotive::getPlanesFromRays(int camId) {
	vector<ofxMotiveTools::Plane> planes;
	planes.resize(5);
	getPlaneFromRays(cams[camId].getRays()[0], cams[camId].getRays()[1], planes[0]);
	getPlaneFromRays(cams[camId].getRays()[1], cams[camId].getRays()[2], planes[1]);
	getPlaneFromRays(cams[camId].getRays()[2], cams[camId].getRays()[3], planes[2]);
	getPlaneFromRays(cams[camId].getRays()[3], cams[camId].getRays()[0], planes[3]);
	getPlaneFromRayBase(cams[camId].getRays(), planes[4]);
	return planes;
}

void ofxMotive::getPlaneFromRays(ofxMotiveTools::Ray & ray0, ofxMotiveTools::Ray & ray1, ofxMotiveTools::Plane & p) {
	ofxCodeJutsu::Geometry::planeFromTriangle(ray0.start, ray0.end, ray1.end, p.a, p.b, p.c, p.d);
}

void ofxMotive::getPlaneFromRayBase(vector<ofxMotiveTools::Ray> & rays, ofxMotiveTools::Plane & p) {
	ofxCodeJutsu::Geometry::planeFromTriangle(rays[0].end, rays[3].end, rays[2].end, p.a, p.b, p.c, p.d);
}

void ofxMotive::raycastAndFlagVoxels() {
	for (int i = 0; i < cams.size(); i++) {
		raycastCaptureVolume(i, voxelBox);
	}

	for (int x = 0; x < voxelBox.getNumVoxelsX(); x++) {
		for (int y = 0; y < voxelBox.getNumVoxelsY(); y++) {
			for (int z = 0; z < voxelBox.getNumVoxelsZ(); z++) {
				ofxMotiveTools::Voxel * vx = voxelBox.getVoxel(x, y, z);
				vx->mainFlag = vx->hasMinFlags(minNumCams);
			}
		}
	}

	bFlagged = true;
}

void ofxMotive::flagVoxels() {
	
	for (int i = 0; i < cams.size(); i++) {
		flagCaptureVolume(i, voxelBox);
	}
	


	for (int x = 0; x < voxelBox.getNumVoxelsX(); x++) {
		for (int y = 0; y < voxelBox.getNumVoxelsY(); y++) {
			for (int z = 0; z < voxelBox.getNumVoxelsZ(); z++) {
				ofxMotiveTools::Voxel * vx = voxelBox.getVoxel(x, y, z);
				vx->mainFlag = vx->hasMinFlags(minNumCams);
#ifdef SIM_DATA
				vx->mainFlag = ofRandomf() > 0.7;
#endif // SIM_DATA

			}
		}
	}

	bFlagged = true;
}

void ofxMotive::setup(string _pthTTP, string _pthCAL) {
	loadTTP(_pthTTP);
	loadCAL(_pthCAL);
	getCameraInfos();

}

void ofxMotive::setupVoxels() {
	voxelBox.setup(spaceSize, voxelSz, &numCams);
	bDrawVoxels	= true;
	bDrawFlaggedVoxels = true;
}

void ofxMotive::setupRayCasting() {
	for (int i = 0; i < cams.size(); i++) {
		makeCameraRays(i);
	}
	voxelBox.setup(spaceSize, voxelSz, &numCams);
	bDrawRays = true;
	bDrawVoxels = true;
	bDrawFlaggedVoxels = true;
}

void ofxMotive::makeCameraRays(int camId) {
	cout << "casting rays for camera " << camId << endl;
	cams[camId].getRays().clear();
	cams[camId].getRays().resize(4);
	string camModel = getModelFromName(cams[camId].getName());
	float rayL = getRayLengthForModel(camModel);
	//cout << cams[camId].getName() << ", model: " << camModel<<", ray: "<<rayL<<"m\n";
	
	vector<ofVec2f> order;
	order.resize(4);
#ifdef SIM_DATA
	float minX = -cams[camId].getFovX() / 2;
	float maxX = cams[camId].getFovX() / 2;
	float minY = -cams[camId].getFovY() / 2;
	float maxY = cams[camId].getFovY() / 2;

#else
	float minX = 0;
	float maxX = cams[camId].getWidth();
	float minY = 0;
	float maxY = cams[camId].getHeight();
#endif
	order[0].set(maxX, maxY);
	order[1].set(minX, maxY);
	order[2].set(minX, minY);
	order[3].set(maxX, minY);

	for (int i = 0; i < 4; i++) {
#ifdef SIM_DATA
		//cams[camId].getRays()[i] = makeRayFromFov(camId, order[i].x, order[i].y);
		cams[camId].getRays()[i].set(simRays[camId][i].start, simRays[camId][i].end);
#else
		cams[camId].getRays()[i] = makeRay(camId, order[i].x, order[i].y, rayL);
		cout << "Camera " << camId << ": Ray " << i << ": " << cams[camId].getRays()[i].start.x << "," << cams[camId].getRays()[i].start.y << ", " << cams[camId].getRays()[i].start.z << " -- " << cams[camId].getRays()[i].end.x << "," << cams[camId].getRays()[i].end.y << ", " << cams[camId].getRays()[i].end.z << endl;
#endif
	}

}

ofxMotiveTools::Ray ofxMotive::makeRayFromFov(int camId, float ax, float ay) {
	ofxMotiveTools::Ray ray;
	ray.start = cams[camId].getPosition();
	ray.end.set(0,0,-cams[camId].rayLength);
	ray.end.rotate(ax, ay, 0);
	ray.end = ray.end * cams[camId].getGlobalTransformMatrix();
	return ray;
}

ofxMotiveTools::Ray ofxMotive::makeRay(int camId, float sX, float sY, float rayL) {
	ofxMotiveTools::Ray ray;
	TT_CameraUndistort2DPoint(camId, sX, sY);
	float r0x;
	float r0y;
	float r0z;
	float r1x;
	float r1y;
	float r1z;
	TT_CameraRay(camId, sX, sY, r0x, r0y, r0z, r1x, r1y, r1z);
	ofVec3f v0(r0x, r0y, r0z);
	ofVec3f v1(r1x, r1y, r1z);
	v1 -= v0;
	v1.normalize();
	v1 *= rayL;
	v1 += v0;
	ray.start = v0;
	ray.end = v1;
	return ray;
}

vector<ofVec3f> ofxMotive::getFlaggedVoxelCentroids() {
	vector<ofVec3f> pts;
	for (int x = 0; x < voxelBox.getNumVoxelsX(); x++) {
		for (int y = 0; y < voxelBox.getNumVoxelsY(); y++) {
			for (int z = 0; z < voxelBox.getNumVoxelsZ(); z++) {
				ofxMotiveTools::Voxel * vx = voxelBox.getVoxel(x, y, z);
				if (vx->mainFlag) {
					pts.push_back(ofVec3f(vx->x(),vx->y(),vx->z()));
				}
			}
		}
	}
	return pts;
}

void ofxMotive::computeVolumeHull() {
	vboHull.clear();
	
	ofxQuickHull::Simplex simplex;
	simplex.hullMode = ofxQuickHull::HULL_TRIANGLES;
	vector<ofVec3f> vtx = getFlaggedVoxelCentroids();
	vector<ofVec3f> hullVtx;
	simplex.init(vtx, &hullVtx);
	vboHull.addVertices(hullVtx);
}

void ofxMotive::drawCameras() {
	for (int i = 0; i < cams.size(); i++) {
		cams[i].draw();
	}
}

void ofxMotive::drawSpace() {
	ofPushMatrix();
	ofTranslate(0,spaceSize.y/2,0);
	ofPushStyle();
	ofSetColor(255, 255, 255, 25);
	boxSpace.draw();
	ofSetColor(255, 255, 255, 80);
	boxSpace.drawWireframe();
	ofPopStyle();
	ofPopMatrix();
}

void ofxMotive::drawVoxel(ofxMotiveTools::Voxel * vx) {
	ofPushStyle();
	ofSetColor(255,255,255,1);
	ofPushMatrix();
	ofTranslate(vx->x(), vx->y(), vx->z());
	vboVoxel.drawWireframe();
	if (vx->mainFlag) {
		ofSetColor(0,255,0,50);
		vboVoxel.draw();
	}
	ofPopMatrix();
	ofPopStyle();
}

void ofxMotive::drawVoxels() {
	if (!bDrawVoxels)return;
	for (int x = 0; x < voxelBox.getNumVoxelsX(); x++) {
		for (int y = 0; y < voxelBox.getNumVoxelsY(); y++) {
			for (int z = 0; z < voxelBox.getNumVoxelsZ(); z++) {
				ofxMotiveTools::Voxel * vx = voxelBox.getVoxel(x, y, z);
				drawVoxel(vx);
			}
		}
	}
}

void ofxMotive::drawVolumeHull() {
	ofPushStyle();
	ofSetColor(0,255,0,50);
	vboHull.draw();
	ofSetLineWidth(3);
	ofSetColor(0,255,0,100);
	vboHull.drawWireframe();
	ofSetLineWidth(1);
	ofPopStyle();
}

void ofxMotive::drawRay(ofxMotiveTools::Ray & r) {
	ofDrawLine(r.start.x, r.start.y, r.start.z, r.end.x, r.end.y, r.end.z);
}

void ofxMotive::drawCameraRays(ofxMotiveCamera & c) {
	ofSetColor(ofColor::yellow);
	for (int i = 0; i < c.getRays().size(); i++) {
		drawRay(c.getRays()[i]);
	}
	ofSetColor(255, 255, 0, 100);
	drawRay(c.pilotRay);
}

void ofxMotive::drawRays() {
	ofPushStyle();
	
	for (int i = 0; i < cams.size(); i++) {
		drawCameraRays(cams[i]);
	}
	ofPopStyle();
}

void ofxMotive::draw() {
	drawCameras();
	drawSpace();
	drawVoxels();
	if (bDrawRays)drawRays();
}

void ofxMotive::saveVoxels(string pth) {
	if (pth == "") {
		pth = ofFilePath::getAbsolutePath("pointCloud.txt");
	}

	//if (!bFlagged) {
	//	flagVoxels();
	//}

	std::fstream fStream;
	fStream.open(pth.c_str(), std::ios::out);
	for (int x = 0; x < voxelBox.getNumVoxelsX(); x++) {
		for (int y = 0; y < voxelBox.getNumVoxelsY(); y++) {
			for (int z = 0; z < voxelBox.getNumVoxelsZ(); z++) {
				ofxMotiveTools::Voxel * vx = voxelBox.getVoxel(x, y, z);
				if (vx->mainFlag) {
					fStream << vx->asCSVpoint() << "\n";
				}
			}
		}
	}
	fStream.close();

	//saveTestRays();
}

void ofxMotive::saveTestRays() {
	string pth = ofFilePath::getAbsolutePath("testRays.txt");
	std::fstream fStream;
	fStream.open(pth.c_str(), std::ios::out);
	for (int i = 0; i < cams.size(); i++) {
		ofVec2f ctr;
		ctr.set(cams[i].getWidth()/2, cams[i].getHeight()/2);
		float r0x;
		float r0y;
		float r0z;
		float r1x;
		float r1y;
		float r1z;
		TT_CameraUndistort2DPoint(i, ctr.x, ctr.y);
		TT_CameraRay(i, ctr.x, ctr.y, r0x, r0y, r0z, r1x, r1y, r1z);
		fStream << r0x << "," << r0y << "," << r0z << "," << r1x << "," << r1y << "," << r1z << "\n";
	}
	fStream.close();
}
