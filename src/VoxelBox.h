// magicLab 2016
// http://www.magiclab.nyc
// author: enrico viola
// license: GPL v.3

#pragma once
#include "ofMain.h"
#include "Voxel.h"

namespace ofxMotiveTools {
	class VoxelBox {
	public:
		VoxelBox() {
			nCams = NULL;
		}

		~VoxelBox() {
			deallocateVoxels();
		}

		void setup(ofVec3f _boxSz, float _voxelSz, int * _nCams) {
			nCams = _nCams;
			setBoxSizes(_boxSz);
			setVoxelSize(_voxelSz);
			setupVoxels();

			std::cout << "Search space is " << getBoxXSize() << "m by " << getBoxYSize() << "m by " << getBoxZSize() << "m" << std::endl;
			std::cout << "Voxel size is " << getVoxelSize() << "m and space resolution is " << getNumVoxelsX() << " by " << getNumVoxelsY() << " by " << getNumVoxelsZ() << std::endl;

		}

		void setBoxSizes(ofVec3f _sz) { boxSizes = _sz; }
		float getBoxXSize() { return boxSizes.x; }
		float getBoxYSize() { return boxSizes.y; }
		float getBoxZSize() { return boxSizes.z; }

		int getNumVoxelsX() { return numXVoxels; }
		int getNumVoxelsY() { return numYVoxels; }
		int getNumVoxelsZ() { return numZVoxels; }

		void setVoxelSize(float _sz) { voxelSize = _sz; }
		float getVoxelSize() { return voxelSize; }

		ofxMotiveTools::Voxel * getVoxel(int _x, int _y, int _z) { return &voxels[_x][_y][_z]; }

		static int calcVoxelsForAxis(float & _voxSz, float & _axisSz) {
			return int(_axisSz / _voxSz);
		}
		int calcVoxelsForX() { return calcVoxelsForAxis(voxelSize, boxSizes.x); }
		int calcVoxelsForY() { return calcVoxelsForAxis(voxelSize, boxSizes.y); }
		int calcVoxelsForZ() { return calcVoxelsForAxis(voxelSize, boxSizes.z); }
		void setupVoxels() {
			numXVoxels = calcVoxelsForX();
			numYVoxels = calcVoxelsForY();
			numZVoxels = calcVoxelsForZ();

			allocateVoxels();

			float sz2 = voxelSize / 2;
			float minX = -boxSizes.x / 2 + sz2;
			float minY = sz2;
			float minZ = -boxSizes.z / 2 + sz2;

			for (int x = 0; x < numXVoxels; x++) {
				for (int y = 0; y < numYVoxels; y++) {
					for (int z = 0; z < numZVoxels; z++) {
						voxels[x][y][z].set(minX + voxelSize*x,
							minY + voxelSize*y,
							minZ + voxelSize*z,
							&voxelSize, nCams);
					}
				}
			}
		}

		static bool isPointCaptured(float sx, float sy, int resW, int resH) {
			return (sx >= 0 && sx <= resW && sy >= 0 && sy <= resH);
		}
	protected:
		void allocateVoxels() {
			voxels = new ofxMotiveTools::Voxel **[numXVoxels];
			for (int x = 0; x < numXVoxels; x++) {
				voxels[x] = new ofxMotiveTools::Voxel *[numYVoxels];
				for (int y = 0; y < numYVoxels; y++) {
					voxels[x][y] = new ofxMotiveTools::Voxel[numZVoxels];
				}
			}
		}

		void deallocateVoxels() {
			for (int x = 0; x < numXVoxels; x++) {
				for (int y = 0; y < numYVoxels; y++) {
					delete[] voxels[x][y];
				}
				delete[] voxels[x];
			}
			delete[] voxels;
		}

		ofxMotiveTools::Voxel *** voxels;
		ofVec3f boxSizes;
		float voxelSize;
		int numXVoxels;
		int numYVoxels;
		int numZVoxels;
		int * nCams;
	};
}