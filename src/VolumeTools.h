// magicLab 2016
// http://www.magiclab.nyc
// author: enrico viola
// license: GPL v.3

#include <windows.h>
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <iostream>
#include <sstream>

namespace VolumeTools{
	class Vec3f{
	public:
		Vec3f(){ x = 0; y = 0; y = 0; }
		float x;
		float y;
		float z;
	};

	class Voxel{
	public:
		Voxel(){
			sz = NULL;
			nCams = NULL;
			camFlags = NULL;
		}
		
		~Voxel(){
			if (camFlags!= NULL)
				delete [] camFlags;
		}

		void set(float x, float y, float z, float * _sz, int * _nCams){
			setSize(_sz);
			setNumCameras(_nCams);
			setPosition(x,y,z);
		}

		void setSize(float * _sz){ sz = _sz; }
		float getSize(){ return *sz; }

		void setNumCameras(int * n){
			nCams = n;
			camFlags = new bool[*nCams];
			resetFlags();
		}

		int getNumCameras(){ return *nCams; }

		void resetFlags(){
			for (int i = 0; i < (*nCams); i++){
				camFlags[i] = false;
			}
		}

		bool getFlag(int i){ return camFlags[i]; }
		void setFlag(int i, bool b){ camFlags[i] = b; }
		int getNumFlagged(){
			int n = 0;
			for (int i = 0; i < (*nCams); i++){
				if (camFlags[i])n++;
			}
			return n;
		}
		bool hasMinFlags(int min){
			return (getNumFlagged()>=min);
		}

		void setPosition(float x, float y, float z){
			pos.x = x;
			pos.y = y;
			pos.z = z;
		}
		Vec3f & getPosition(){ return pos; }
		float x(){ return pos.x; }
		float y(){ return pos.y; }
		float z(){ return pos.z; }

		std::string asCSVpoint(){
			std::stringstream ss;
			std::string s;
			ss << x() << "," << y() << "," << z();
			s = ss.str();
			return s;
		}
	protected:
		Vec3f pos;
		float * sz;
		int * nCams;
		bool * camFlags;
	};

	class VoxelBox{
	public:
		VoxelBox(){
			nCams = NULL;
		}

		~VoxelBox(){
			deallocateVoxels();
		}

		void setup(Vec3f _boxSz, float _voxelSz, int * _nCams){
			nCams = _nCams;
			setBoxSizes(_boxSz);
			setVoxelSize(_voxelSz);
			setupVoxels();

			std::cout << "Search space is " << getBoxXSize() << "m by " << getBoxYSize() << "m by " << getBoxZSize() << "m" << std::endl;
			std::cout << "Voxel size is " << getVoxelSize() << "m and space resolution is " << getNumVoxelsX() << " by " << getNumVoxelsY() << " by " << getNumVoxelsZ() << std::endl;

		}

		void setBoxSizes(Vec3f _sz){ boxSizes = _sz; }
		float getBoxXSize(){ return boxSizes.x; }
		float getBoxYSize(){ return boxSizes.y; }
		float getBoxZSize(){ return boxSizes.z; }

		int getNumVoxelsX(){ return numXVoxels; }
		int getNumVoxelsY(){ return numYVoxels; }
		int getNumVoxelsZ(){ return numZVoxels; }

		void setVoxelSize(float _sz){ voxelSize = _sz; }
		float getVoxelSize(){ return voxelSize; }

		Voxel * getVoxel(int _x, int _y, int _z){ return &voxels[_x][_y][_z]; }

		static int calcVoxelsForAxis(float & _voxSz, float & _axisSz){
			return int(_axisSz/_voxSz);
		}
		int calcVoxelsForX(){ return calcVoxelsForAxis(voxelSize, boxSizes.x); }
		int calcVoxelsForY(){ return calcVoxelsForAxis(voxelSize, boxSizes.y); }
		int calcVoxelsForZ(){ return calcVoxelsForAxis(voxelSize, boxSizes.z); }
		void setupVoxels(){
			numXVoxels = calcVoxelsForX();
			numYVoxels = calcVoxelsForY();
			numZVoxels = calcVoxelsForZ();

			allocateVoxels();
			
			float sz2 = voxelSize / 2;
			float minX = -boxSizes.x / 2 - sz2;
			float minY = 0;
			float minZ = -boxSizes.z / 2 - sz2;

			for (int x = 0; x < numXVoxels; x++){
				for (int y = 0; y < numYVoxels; y++){
					for (int z = 0; z < numZVoxels; z++){
						voxels[x][y][z].set(minX + voxelSize*x, 
											minY + voxelSize*y, 
											minZ + voxelSize*z, 
											&voxelSize, nCams);
					}
				}
			}
		}
		
		static bool isPointCaptured(float sx, float sy, int resW, int resH){
			return (sx>=0 && sx<=resW && sy>=0 && sy<=resH);
		}
	protected:
		void allocateVoxels(){
			voxels = new Voxel **[numXVoxels];
			for (int x = 0; x < numXVoxels; x++){
				voxels[x] = new Voxel *[numYVoxels];
				for (int y = 0; y < numYVoxels; y++){
					voxels[x][y] = new Voxel[numZVoxels];
				}
			}
		}

		void deallocateVoxels(){
			for (int x = 0; x < numXVoxels; x++){
				for (int y = 0; y < numYVoxels; y++){
					delete[] voxels[x][y];
				}
				delete[] voxels[x];
			}
			delete[] voxels;
		}

		Voxel *** voxels;
		Vec3f boxSizes;
		float voxelSize;
		int numXVoxels;
		int numYVoxels;
		int numZVoxels;
		int * nCams;
	};
}