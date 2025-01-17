#if !defined(ULTILITY_H )
#define ULTILITY_H
#pragma once

#include <cstdlib>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <math.h>
#include <omp.h>
#include <stdarg.h>

#include <ceres/ceres.h>
#include <ceres/rotation.h>
#include <opencv2/opencv.hpp>
#include <opencv2/features2d/features2d.hpp>
#include <Eigen/Dense>

#include "Visualization.h"
#include "DataStructure.h"
#include "ImagePro.h"

#include "SiftGPU/src/SiftGPU/SiftGPU.h"
#include <vl/generic.h>
#include <vl/mathop.h>
#include <vl/sift.h>
#include <vl/covdet.h>

#ifdef _WIN32
#include <direct.h>
#else
#include <sys/stat.h>
#endif

using namespace cv;
using namespace std;

int writeVisualSFMSiftGPU(const char* fn, float *KeyPts, unsigned char *desc, int nsift);
int readVisualSFMSiftGPU(char *fn, vector<KeyPoint>&kpts, Mat &descriptors, bool silent = true);
int readVisualSFMSiftGPU(char *fn, vector<SiftKeypoint>&kpts, Mat &descriptors, bool silent = true);

bool WriteKPointsSIFT(char *fn, vector<SiftKeypoint>kpts, bool silent);
bool WriteKPointsBinarySIFT(char *fn, vector<SiftGPU::SiftKeypoint>kpts, bool silent = false);
bool ReadKPointsBinarySIFT(char *fn, vector<SiftGPU::SiftKeypoint> &kpts, bool silent = false);
bool WriteKPointsBinarySIFT(char *fn, vector<KeyPoint>kpts, bool silent = false);
bool ReadKPointsBinarySIFT(char *fn, vector<KeyPoint> &kpts, bool silent = false);
bool WriteDescriptorBinarySIFT(char *fn, vector<float > descriptors, bool silent = false);
bool WriteDescriptorBinarySIFT(char *fn, Mat descriptor, bool silent = false);
bool ReadDescriptorBinarySIFT(char *fn, vector<float > &descriptors, bool silent = false);
Mat ReadDescriptorBinarySIFT(char *fn, bool silent = false);

void GenereteKeyPointsRGB(char *ImgName, char *KName, char *KeyRGBName);
bool WriteRGBBinarySIFT(char *fn, vector<Point3i> rgb, bool silent = false);
bool ReadRGBBinarySIFT(char *fn, vector<Point3i> &rgb, bool silent = false);
bool WriteKPointsRGBBinarySIFT(char *fn, vector<SiftKeypoint>kpts, vector<Point3i> rgb, bool silent = false);
bool ReadKPointsRGBBinarySIFT(char *fn, vector<SiftKeypoint> &kpts, vector<Point3i> &rgb, bool silent = false);
bool WriteKPointsRGBBinarySIFT(char *fn, vector<KeyPoint>kpts, vector<Point3i> rgb, bool silent = false);
bool ReadKPointsRGBBinarySIFT(char *fn, vector<KeyPoint> &kpts, vector<Point3i> &rgb, bool silent = false);

//npts>0 specifiies intial points whose descriptors are to be computed
int VLSIFT(char *Fname, SiftFeature &SF, int &npts, int verbose = 0);
//npts>0 specifiies intial points whose descriptors are to be computed
int VLCOVDET(char *ImgName, CovFeature &CovF, int &npts, int verbose = 0);
int ComputeFeatureScaleAndDescriptor(Mat Img, KeyPoint &key, float *desc, int nOctaveLayers = 3, double sigma = 1.6, double contrastThreshold = 0.01, double edgeThreshold = 10);

int SiftOpenCVPair(char *Fname1, char *Fname2, const float nndrRatio, const double fractionMatchesDisplayed);
int SiftGPUPair(char *Fname1, char *Fname2, const float nndrRatio, const double fractionMatchesDisplayed);
int vfFeatPair(char *Fname1, char *Fname2, const float nndrRatio, const double fractionMatchesDisplayed);
int SiftMatch(char *Path, char *Fname1, char *Fname2, float nndrRatio, double density, bool useBFMatcher = false);

int ExtractSiftGPUfromExtractedFrames(char *Path, vector<int> &nviews, int startF, int stopF, int increF, int HistogramEqual = 0);
int ExtractFeaturefromExtractedFrames(char *Path, vector<int> &nviews, int startF, int stopF, int increF, int HistogramEqual = 0, int ExtractionMethod = 0);
int ExtractFeatureForVisualSfM(char *Path, int startF, int stopF, int increF, int HistogramEqual = 0, int CovDet = 0);

int GeneratePointsCorrespondenceMatrix_SiftGPU(char *Path, int nviews, int timeID, int HistogramEqual, float nndrRatio = 0.8, int *FrameOffset = NULL);
int GeneratePointsCorrespondenceMatrix_CPU(char *Path, int nviews, int timeID, int HistogramEqual, float nndrRatio, int *FrameOffset, int extractionMethod);
int GeneratePointsCorrespondenceMatrix(char *Path, int nviews, int timeID);
int GetPoint2DPairCorrespondence(char *Path, int timeID, vector<int>viewID, vector<KeyPoint>&keypoints1, vector<KeyPoint>&keypoints2, vector<int>&CorrespondencesID, bool useGPU = true);

void ReadPointCorrespondences(char *Path, int nviews, int timeID, vector<int> *PointCorres, vector<int>&mask, int totalPts, bool Merge = false);
void ReadPointCorrespondences(char *Path, int nviews, int timeID, vector<int> *PointCorres, int totalPts, bool Merge);
void GenerateMergePointCorrespondences(vector<int> *MergePointCorres, vector<int> *PointCorres, int totalPts);
void GenerateViewandPointCorrespondences(vector<int> *ViewCorres, vector<int> *PointIDCorres, vector<int> *PointCorres, vector<int> CumIDView, int totalPts);
int ReadCumulativePoints(char *Path, int nviews, int timeID, vector<int>&cumulativePts);
void ReadCumulativePointsVisualSfm(char *Path, int nviews, vector<int>&cumulativePts);
void GenerateMatchingTable(char *Path, int nviews, int timeID, int NviewPlus = 3);
void GenerateMatchingTableVisualSfM(char *Path, int nviews);
void GenerateViewCorrespondenceMatrix(char *Path, int nviews, int timeID);
int GetPutativeMatchesForEachView(char *Path, int nviews, int startF, int stopF, int increF, Point2d ScaleThresh, int nPlus, int *FrameOffset);

void BestPairFinder(char *Path, int nviews, int timeID, int *viewPair);
int NextViewFinder(char *Path, int nviews, int timeID, int currentView, int &maxPoints, vector<int> usedPairs);
int GetPoint3D2DPairCorrespondence(char *Path, int nviews, int timeID, vector<int> cumulativePts, vector<int> viewID, Point3d *ThreeD, vector<KeyPoint>&keypoints1, vector<KeyPoint>&keypoints2, vector<int>&TwoDCorrespondencesID, vector<int> &ThreeDCorrespondencesID, vector<int>&SelectedIndex, bool SwapView, bool useGPU = true);
int GetPoint3D2DAllCorrespondence(char *Path, int nviews, int timeID, vector<int> cumulativePts, Point3d *ThreeD, vector<int> AvailViews, vector<int>&Selected3DIndex, vector<Point2d> *selected2D, vector<int>*nselectedviews, int &nselectedPts, bool useGPU = true);

void makeDir(char *Fname);
void printfLog(const char *strLog, char *Path = NULL);

//Phase shifting:
void Average_Filtering_All(char *lpD, int width, int height, int ni, int HSize, int VSize);
void MConventional_PhaseShifting(char *lpD, char *lpPBM, double* lpFO, int nipf, int length, int Mask_Threshold, double *f_atan2);
void DecodePhaseShift2(char *Image, char *PBM, double *PhaseUW, int width, int height, int *frequency, int nfrequency, int sstep, int LFstep, int half_filter_size, int m_mask);

void GenerateDCTBasis(int nsamples, double *Basis, double *Weight = NULL);
void GenerateiDCTBasis(double *Basis, int nsamples, double t);

//Bspline basis resampling
/*void GenerateSplineBasisWithBreakPts(double *Basis, double *DBasis, double *ResampledPts, double *BreakPts, int nResamples, int nbreaks, int SplineOrder, int DerivativeOrder);
void GenerateResamplingSplineBasisWithBreakPts(double *Basis, double *ResampledPts, double *BreakPts, int nResamples, int nbreaks, int SplineOrder);
void GenerateResamplingSplineBasisWithBreakPts(double *Basis, vector<double> ResampledPts, vector<double>BreakPts, int SplineOrder);
int FindActingControlPts(double t, int *ActingID, int ncontrols, gsl_bspline_workspace *bw, gsl_vector *Bi, int splineOrder, int extraNControls = 2);*/

void BSplineFindActiveCtrl(int *ActingID, const double x, double *knots, int nbreaks, int nControls, int SplineOrder, int extraNControls = 2);
int BSplineGetKnots(double *knots, double *BreakLoc, int nbreaks, int nControls, int SplineOrder);
int BSplineGetNonZeroBasis(const double x, double * dB, int * istart, int * iend, double *knots, int nbreaks, int nControls, int SplineOrder, int nderiv);
int BSplineGetBasis(const double x, double * B, double *knots, int nbreaks, int nControls, int SplineOrder, int nderiv = 0);
int BSplineGetAllBasis(double *AllB, double *samples, double *BreakPts, int nsamples, int nbreaks, int SplineOrder, int nderiv = 0, double *AlldB = 0, double *Alld2B = 0);

//Image processing
bool RoateImage180(char *fname, int nchannels, bool silent = true);
bool GrabImageCVFormat(char *fname, char *Img, int &width, int &height, int nchannels, bool silent = false);
bool GrabImage(char *fname, char *Img, int &width, int &height, int nchannels, bool silent = false);
bool GrabImage(char *fname, unsigned char *Img, int &width, int &height, int nchannels, bool silent = false);
bool GrabImage(char *fname, float *Img, int &width, int &height, int nchannels, bool silent = false);
bool GrabImage(char *fname, double *Img, int &width, int &height, int nchannels, bool silent = false);

void ShowDataToImage(char *Fname, char *Img, int width, int height, int nchannels, IplImage *cvImg = 0);

bool SaveDataToImageCVFormat(char *fname, char *Img, int width, int height, int nchannels = 1);
bool SaveDataToImage(char *fname, char *Img, int width, int height, int nchannels = 1);
bool SaveDataToImage(char *fname, unsigned char *Img, int width, int height, int nchannels = 1);
bool SaveDataToImage(char *fname, int *Img, int width, int height, int nchannels = 1);
bool SaveDataToImage(char *fname, float *Img, int width, int height, int nchannels = 1);
bool SaveDataToImage(char *fname, double *Img, int width, int height, int nchannels = 1);
int ExtractVideoFrames(char *Path, int camID, int rotateImage, int nchannels = 3);

void ShowDataAsImage(char *fname, unsigned char *Img, int width, int height, int nchannels);
void ShowDataAsImage(char *fname, double *Img, int width, int height, int nchannels);

void ResizeImage(unsigned char *Image, unsigned char *OutImage, int width, int height, int nchannels, double Rfactor, double sigma, int InterpAlgo, double *InPara = 0);
void ResizeImage(float *Image, float *OutImage, int width, int height, int channels, double Rfactor, double sigma, int InterpAlgo, float *Para = 0);
void ResizeImage(double *Image, double *OutImage, int width, int height, int nchannels, double Rfactor, double sigma, int InterpAlgo, double *Para = 0);

void RemoveNoiseMedianFilter(float *data, int width, int height, int ksize, float thresh);
void RemoveNoiseMedianFilter(double *data, int width, int height, int ksize, float thresh, float *fdata = 0);

//Image pyramid
int BuildImgPyr(char *ImgName, ImgPyr &Pyrad, int nOtaves, int nPerOctaves, bool color, int interpAlgo, double sigma = 1.0);

//Descriptor
template <class myType> bool WriteGridBinary(char *fn, myType *data, int width, int height, bool silent = false)
{
	ofstream fout;
	fout.open(fn, ios::binary);
	if (!fout.is_open())
	{
		if (silent)
			cout << "Cannot write: " << fn << endl;
		return false;
	}

	for (int j = 0; j < height; ++j)
		for (int i = 0; i < width; ++i)
			fout.write(reinterpret_cast<char *>(&data[i + j*width]), sizeof(myType));
	fout.close();

	return true;
}
template <class myType> bool ReadGridBinary(char *fn, myType *data, int width, int height, bool silent = false)
{
	ifstream fin;
	fin.open(fn, ios::binary);
	if (!fin.is_open())
	{
		cout << "Cannot open: " << fn << endl;
		return false;
	}
	if (silent)
		cout << "Load " << fn << endl;

	for (int j = 0; j < height; ++j)
		for (int i = 0; i < width; ++i)
			fin.read(reinterpret_cast<char *>(&data[i + j*width]), sizeof(myType));
	fin.close();

	return true;
}

//Math
void dec2bin(int dec, int*bin, int num_bin);
double nChoosek(int n, int k);
double nPermutek(int n, int k);
int MyFtoI(double W);
bool IsNumber(double x);
bool IsFiniteNumber(double x);
double UniformNoise(double High, double Low);
double gaussian_noise(double mean, double std);

double Distance2D(Point2d X, Point2d Y);
double Distance3D(Point3d X, Point3d Y);
double Distance3D(double *X, double * Y);
Point3d ProductPoint3d(Point3d X, Point3d Y);
Point3d DividePoint3d(Point3d X, Point3d Y);
double L1norm(vector<double>A);
double L2norm(double *A, int dim);
float MeanArray(float *data, int length);
double MeanArray(double *data, int length);
double VarianceArray(double *data, int length, double mean = NULL);
double MeanArray(vector<double>&data);
double VarianceArray(vector<double>&data, double mean = NULL);
void normalize(double *x, int dim = 3);
double dotProduct(double *x, double *y, int dim = 3);
double dotProduct(float *x, float *y, int dim = 3);
double norm_dot_product(double *x, double *y, int dim = 3);
void cross_product(double *x, double *y, double *xy);
void conv(float *A, int lenA, float *B, int lenB, float *C);
void conv(double *A, int lenA, double *B, int lenB, double *C);
void ZNCC1D(float *A, const int dimA, float *B, const int dimB, float *Result, float *nB = NULL);
void ZNCC1D(double *A, int Asize, double *B, int Bsize, double *Result);
void XCORR1D(float *s, const int sdim, float *b, const int bdim, float *res);

void mat_invert(double* mat, double* imat, int dims = 3);
void mat_invert(float* mat, float* imat, int dims = 3);
void mat_mul(float *aa, float *bb, float *out, int rowa, int col_row, int colb);
void mat_mul(double *aa, double *bb, double *out, int rowa, int col_row, int colb);
void mat_add(double *aa, double *bb, double* cc, int row, int col, double scale_a = 1.0, double scale_b = 1.0);
void mat_subtract(double *aa, double *bb, double* cc, int row, int col, double scale_a = 1.0, double scale_b = 1.0);
void mat_transpose(double *in, double *out, int row_in, int col_in);
void mat_mul_symetric(double *A, double *B, int row, int column);
void mat_add_symetric(double *A, double * B, double *C, int row, int column);
void mat_completeSym(double *mat, int size, bool upper = true);

template <class myType>void RemoveEleFromArray(myType *Array, int neles, int eleID)
{
	for (int i = eleID; i < neles - 1; i++)
		Array[i] = Array[i + 1];
}

void LS_Solution_Double(double *lpA, double *lpB, int m, int n);
void QR_Solution_Double(double *lpA, double *lpB, int m, int n);
void Quick_Sort_Double(double * A, int *B, int low, int high);
void Quick_Sort_Float(float * A, int *B, int low, int high);
void Quick_Sort_Int(int * A, int *B, int low, int high);

double SimpsonThreeEightIntegration(double *y, double step, int npts);

bool in_polygon(double u, double v, Point2d *vertex, int num_vertex);

void ConvertToHeatMap(double *Map, unsigned char *ColorMap, int width, int height, bool *mask = 0);


template <class myType>void Get_Sub_Mat(myType *srcMat, myType *dstMat, int srcWidth, int srcHeight, int dstWidth, int startCol, int startRow)
{
	int ii, jj;

	for (jj = startRow; jj < startRow + srcHeight; jj++)
		for (ii = startCol; ii < startCol + srcWidth; ii++)
			dstMat[ii - startCol + (jj - startRow)*dstWidth] = srcMat[ii + jj*srcWidth];

	return;
}
template <class myType>void Set_Sub_Mat(myType *srcMat, myType *dstMat, int srcWidth, int srcHeight, int dstWidth, int startCol, int startRow)
{
	int ii, jj;

	for (jj = 0; jj < srcHeight; jj++)
	{
		for (ii = 0; ii < srcWidth; ii++)
		{
			dstMat[ii + startCol + (jj + startRow)*dstWidth] = srcMat[ii + jj*srcWidth];
		}
	}

	return;
}

template <class m_Type> class m_TemplateClass_1
{
public:
	void Quick_Sort(m_Type* A, int *B, int low, int high);
	void QR_Solution(m_Type *lpA, m_Type *lpB, int m, int n);
	void QR_Solution_2(m_Type *lpA, m_Type *lpB, int m, int n, int k);
};

template <class m_Type> void m_TemplateClass_1<m_Type>::Quick_Sort(m_Type* A, int *B, int low, int high)
//A: array to be sorted (from min to max); B: index of the original array; low and high: array range
//After sorting, A: sorted array; B: re-sorted index of the original array, e.g., the m-th element of
// new A[] is the original n-th element in old A[]. B[m-1]=n-1;
//B[] is useless for most sorting, it is added here for the special application in this program.  
{
	m_Type A_pivot, A_S;
	int B_pivot, B_S;
	int scanUp, scanDown;
	int mid;
	if (high - low <= 0)
		return;
	else if (high - low == 1)
	{
		if (A[high] < A[low])
		{
			//	Swap(A[low],A[high]);
			//	Swap(B[low],B[high]);
			A_S = A[low];
			A[low] = A[high];
			A[high] = A_S;
			B_S = B[low];
			B[low] = B[high];
			B[high] = B_S;
		}
		return;
	}
	mid = (low + high) / 2;
	A_pivot = A[mid];
	B_pivot = B[mid];

	//	Swap(A[mid],A[low]);
	//	Swap(B[mid],B[low]);
	A_S = A[mid];
	A[mid] = A[low];
	A[low] = A_S;
	B_S = B[mid];
	B[mid] = B[low];
	B[low] = B_S;

	scanUp = low + 1;
	scanDown = high;
	do
	{
		while (scanUp <= scanDown && A[scanUp] <= A_pivot)
			scanUp++;
		while (A_pivot < A[scanDown])
			scanDown--;
		if (scanUp < scanDown)
		{
			//	Swap(A[scanUp],A[scanDown]);
			//	Swap(B[scanUp],B[scanDown]);
			A_S = A[scanUp];
			A[scanUp] = A[scanDown];
			A[scanDown] = A_S;
			B_S = B[scanUp];
			B[scanUp] = B[scanDown];
			B[scanDown] = B_S;
		}
	} while (scanUp < scanDown);

	A[low] = A[scanDown];
	B[low] = B[scanDown];
	A[scanDown] = A_pivot;
	B[scanDown] = B_pivot;
	if (low < scanDown - 1)
		Quick_Sort(A, B, low, scanDown - 1);
	if (scanDown + 1 < high)
		Quick_Sort(A, B, scanDown + 1, high);
}
template <class m_Type> void m_TemplateClass_1<m_Type>::QR_Solution(m_Type *lpA, m_Type *lpB, int m, int n)
{
	int ii, jj, mm, kk;
	m_Type t, d, alpha, u;
	m_Type *lpC = new m_Type[n];
	m_Type *lpQ = new m_Type[m*m];

	for (ii = 0; ii < m; ii++)
	{
		for (jj = 0; jj < m; jj++)
		{
			*(lpQ + ii*m + jj) = (m_Type)0;
			if (ii == jj)
				*(lpQ + ii*m + jj) = (m_Type)1;
		}
	}

	for (kk = 0; kk<n; kk++)
	{
		u = (m_Type)0;
		for (ii = kk; ii<m; ii++)
		{
			if (fabs(*(lpA + ii*n + kk))>u)
				u = (m_Type)(fabs(*(lpA + ii*n + kk)));
		}

		alpha = (m_Type)0;
		for (ii = kk; ii < m; ii++)
		{
			t = *(lpA + ii*n + kk) / u;
			alpha = alpha + t*t;
		}
		if (*(lpA + kk*n + kk) > (m_Type)0)
			u = -u;
		alpha = (m_Type)(u*sqrt(alpha));
		u = (m_Type)(sqrt(2.0*alpha*(alpha - *(lpA + kk*n + kk))));
		if (fabs(u)>1e-8)
		{
			*(lpA + kk*n + kk) = (*(lpA + kk*n + kk) - alpha) / u;
			for (ii = kk + 1; ii < m; ii++)
				*(lpA + ii*n + kk) = *(lpA + ii*n + kk) / u;
			for (jj = 0; jj < m; jj++)
			{
				t = (m_Type)0;
				for (mm = kk; mm < m; mm++)
					t = t + *(lpA + mm*n + kk)*(*(lpQ + mm*m + jj));
				for (ii = kk; ii < m; ii++)
					*(lpQ + ii*m + jj) = *(lpQ + ii*m + jj) - (m_Type)(2.0*t*(*(lpA + ii*n + kk)));
			}
			for (jj = kk + 1; jj < n; jj++)
			{
				t = (m_Type)0;
				for (mm = kk; mm < m; mm++)
					t = t + *(lpA + mm*n + kk)*(*(lpA + mm*n + jj));
				for (ii = kk; ii < m; ii++)
					*(lpA + ii*n + jj) = *(lpA + ii*n + jj) - (m_Type)(2.0*t*(*(lpA + ii*n + kk)));
			}
			*(lpA + kk*n + kk) = alpha;
			for (ii = kk + 1; ii < m; ii++)
				*(lpA + ii*n + kk) = (m_Type)0;
		}
	}
	for (ii = 0; ii < m - 1; ii++)
	{
		for (jj = ii + 1; jj < m; jj++)
		{
			t = *(lpQ + ii*m + jj);
			*(lpQ + ii*m + jj) = *(lpQ + jj*m + ii);
			*(lpQ + jj*m + ii) = t;
		}
	}
	//Solve the equation
	for (ii = 0; ii < n; ii++)
	{
		d = (m_Type)0;
		for (jj = 0; jj < m; jj++)
			d = d + *(lpQ + jj*m + ii)*(*(lpB + jj));
		*(lpC + ii) = d;
	}
	*(lpB + n - 1) = *(lpC + n - 1) / (*(lpA + (n - 1)*n + n - 1));
	for (ii = n - 2; ii >= 0; ii--)
	{
		d = (m_Type)0;
		for (jj = ii + 1; jj < n; jj++)
			d = d + *(lpA + ii*n + jj)*(*(lpB + jj));
		*(lpB + ii) = (*(lpC + ii) - d) / (*(lpA + ii*n + ii));
	}

	delete[]lpQ;
	delete[]lpC;
	return;
}
template <class m_Type> void m_TemplateClass_1<m_Type>::QR_Solution_2(m_Type *lpA, m_Type *lpB, int m, int n, int k)
{
	int ii, jj, mm, kk;
	m_Type t, d, alpha, u;
	m_Type *lpC = new m_Type[n];
	m_Type *lpQ = new m_Type[m*m];

	for (ii = 0; ii < m; ii++)
	{
		for (jj = 0; jj < m; jj++)
		{
			*(lpQ + ii*m + jj) = (m_Type)0;
			if (ii == jj)
				*(lpQ + ii*m + jj) = (m_Type)1;
		}
	}

	for (kk = 0; kk<n; kk++)
	{
		u = (m_Type)0;
		for (ii = kk; ii<m; ii++)
		{
			if (fabs(*(lpA + ii*n + kk))>u)
				u = (m_Type)(fabs(*(lpA + ii*n + kk)));
		}

		alpha = (m_Type)0;
		for (ii = kk; ii < m; ii++)
		{
			t = *(lpA + ii*n + kk) / u;
			alpha = alpha + t*t;
		}
		if (*(lpA + kk*n + kk) > (m_Type)0)
			u = -u;
		alpha = (m_Type)(u*sqrt(alpha));
		u = (m_Type)(sqrt(2.0*alpha*(alpha - *(lpA + kk*n + kk))));
		if (fabs(u)>1e-8)
		{
			*(lpA + kk*n + kk) = (*(lpA + kk*n + kk) - alpha) / u;
			for (ii = kk + 1; ii < m; ii++)
				*(lpA + ii*n + kk) = *(lpA + ii*n + kk) / u;
			for (jj = 0; jj < m; jj++)
			{
				t = (m_Type)0;
				for (mm = kk; mm < m; mm++)
					t = t + *(lpA + mm*n + kk)*(*(lpQ + mm*m + jj));
				for (ii = kk; ii < m; ii++)
					*(lpQ + ii*m + jj) = *(lpQ + ii*m + jj) - (m_Type)(2.0*t*(*(lpA + ii*n + kk)));
			}
			for (jj = kk + 1; jj < n; jj++)
			{
				t = (m_Type)0;
				for (mm = kk; mm < m; mm++)
					t = t + *(lpA + mm*n + kk)*(*(lpA + mm*n + jj));
				for (ii = kk; ii < m; ii++)
					*(lpA + ii*n + jj) = *(lpA + ii*n + jj) - (m_Type)(2.0*t*(*(lpA + ii*n + kk)));
			}
			*(lpA + kk*n + kk) = alpha;
			for (ii = kk + 1; ii < m; ii++)
				*(lpA + ii*n + kk) = (m_Type)0;
		}
	}
	for (ii = 0; ii < m - 1; ii++)
	{
		for (jj = ii + 1; jj < m; jj++)
		{
			t = *(lpQ + ii*m + jj);
			*(lpQ + ii*m + jj) = *(lpQ + jj*m + ii);
			*(lpQ + jj*m + ii) = t;
		}
	}
	//Solve the equation

	m_Type *lpBB;
	for (mm = 0; mm < k; mm++)
	{
		lpBB = lpB + mm*m;

		for (ii = 0; ii < n; ii++)
		{
			d = (m_Type)0;
			for (jj = 0; jj < m; jj++)
				d = d + *(lpQ + jj*m + ii)*(*(lpBB + jj));
			*(lpC + ii) = d;
		}
		*(lpBB + n - 1) = *(lpC + n - 1) / (*(lpA + (n - 1)*n + n - 1));
		for (ii = n - 2; ii >= 0; ii--)
		{
			d = (m_Type)0;
			for (jj = ii + 1; jj < n; jj++)
				d = d + *(lpA + ii*n + jj)*(*(lpBB + jj));
			*(lpBB + ii) = (*(lpC + ii) - d) / (*(lpA + ii*n + ii));
		}
	}

	delete[]lpQ;
	delete[]lpC;
	return;
}


int PickStaticImagesFromVideo(char *PATH, char *VideoName, int SaveFrameDif, int redetectInterval, double percentile, double MovingThresh2, int &nNonBlurImages, bool visual);
int PickStaticImagesFromImages(char *PATH, int SaveFrameDif, int redetectInterval, double percentile, double MovingThresh2, bool visual);
template <class myType>void nonMinimaSuppression1D(myType *src, int nsample, int *MinEle, int &nMinEle, int halfWnd)
{
	int i = 0, minInd = 0, srcCnt = 0, ele;
	nMinEle = 0;
	while (i < nsample)
	{
		if (minInd < i - halfWnd)
			minInd = i - halfWnd;

		ele = min(i + halfWnd, nsample);
		while (minInd <= ele)
		{
			srcCnt++;
			if (src[minInd] < src[i])
				break;
			minInd++;
		}

		if (minInd > ele) // src(i) is a maxima in the search window
		{
			MinEle[nMinEle] = i, nMinEle++; // the loop above suppressed the maximum, so set it back
			minInd = i + 1;
			i += halfWnd;
		}
		i++;
	}

	return;
}
template <class myType>void nonMaximaSuppression1D(myType *src, int nsample, int *MaxEle, int &nMaxEle, int hWind)
{
	myType *src2 = new myType[nsample];
	for (int ii = 0; ii < nsample; ii++)
		src2[ii] = -src[ii];

	nonMinimaSuppression1D(src2, nsample, MaxEle, nMaxEle, hWind);

	return;
}
void nonMaximaSuppression(const Mat& src, const int sz, Mat& dst, const Mat mask);

int LensCorrectionVideoDriver(char *Path, char *VideoName, double *K, double *distortion, int LensType, int nimages, double Imgscale = 1.0, double Contscale = 1.0, int interpAlgo = 5);
int LensCorrectionImageSequenceDriver(char *Path, double *K, double *distortion, int LensType, int StartFrame, int StopFrame, double Imgscale = 1.0, double Contscale = 1.0, int interpAlgo = 5);
int LensCorrectionDriver(char *Path, double *K, double *distortion, int LensType, int startID, int stopID, double Imgscale = 1.0, double Contscale = 1.0, int interpAlgo = 5);

int DisplayImageCorrespondence(IplImage* correspond, int offsetX, int offsetY, vector<KeyPoint> keypoints1, vector<KeyPoint> keypoints2, vector<int>pair, double density);
int DisplayImageCorrespondence(IplImage* correspond, int offsetX, int offsetY, vector<Point2d> keypoints1, vector<Point2d> keypoints2, vector<int>pair, double density);
int DisplayImageCorrespondencesDriver(char *Path, vector<int>viewsID, int timeID, int nchannels, double density = 0.25);


void SetIntrinisc(CameraData &CamInfo, double *Intrinsic);
void GetIntrinsicFromK(CameraData *AllViewsParas, vector<int> AvailViews);
void GetIntrinsicFromK(CameraData *AllViewsParas, int nviews);
void GetKFromIntrinsic(CameraData *AllViewsParas, vector<int> AvailViews);
void GetKFromIntrinsic(CameraData *AllViewsParas, int nviews);
void GetIntrinsicFromK(CameraData &camera);
void GetKFromIntrinsic(CameraData &camera);

void getTwistFromRT(double *R, double *T, double *twist);
void getRTFromTwist(double *twist, double *R, double *T);
void getrFromR(double *R, double *r);
void getRfromr(double *r, double *R);

void Rotation2Quaternion(double *R, double *q);
void Quaternion2Rotation(double *q, double *R);

void GetrtFromRT(CameraData *AllViewsParas, vector<int> AvailViews);
void GetrtFromRT(CameraData *AllViewsParas, int nviews);
void GetrtFromRT(CameraData &cam);
void GetrtFromRT(double *rt, double *R, double *T);
void GetRTFromrt(CameraData *AllViewsParas, vector<int> AvailViews);
void GetRTFromrt(CameraData *AllViewsParas, int nviews);
void GetRTFromrt(CameraData &camera);
void GetRTFromrt(double *rt, double *R, double *T);

void GetTfromC(CameraData &camInfo);
void GetTfromC(double *R, double *C, double *T);
void GetCfromT(CameraData &camInfo);
void GetCfromT(double *R, double *T, double *C);
void InvertCameraPose(double *R, double *T, double *iR, double *iT);

void AssembleRT(double *R, double *T, double *RT, bool GivenCenter = false);
void DesembleRT(double *R, double *T, double *RT);
void AssembleP(CameraData &camera);
void AssembleP(double *K, double *RT, double *P);
void AssembleP(double *K, double *R, double *T, double *P);
void CopyCamereInfo(CameraData Src, CameraData &Dst, bool Extrinsic = true);

void ComputeInterCamerasPose(double *R1, double *T1, double *R2, double *T2, double *R21, double *T21);

void QuaternionLinearInterp(double *quad1, double *quad2, double *quadi, double u);
int Pose_se_BSplineInterpolation(char *Fname1, char *Fname2, int nsamples, char *Fname3 = 0);
int Pose_se_DCTInterpolation(char *FnameIn, char *FnameOut, int nsamples);

double DistanceOfTwoPointsSfM(char *Path, int id1, int id2, int id3);

int IsBlurred(const unsigned char* const luminance, const int width, const int height, float &blur, float &extent, float blurThresh = 0.075);
void BlurDetectionDriver(char *Path, int nimages, int width, int height, float blurThresh);

bool ReadIntrinsicResults(char *path, CameraData *DeviceParas);
int SaveIntrinsicResults(char *path, CameraData *AllViewsParas, int nCams);
void SaveCurrentSfmInfo(char *path, CameraData *AllViewParas, vector<int>AvailViews, Point3d *All3D, int npts);
void ReadCurrentSfmInfo(char *path, CameraData *AllViewParas, vector<int>&AvailViews, Point3d *All3D, int npts);

int GenerateVisualSFMinput(char *path, int startFrame, int stopFrame, int npts);
bool loadNVMLite(const char *filepath, Corpus &CorpusData, int sharedIntrinsics, int nHDs = 30, int nVGAs = 24, int nPanels = 20);
bool loadNVM(const char *filepath, Corpus &CorpusData, vector<Point2i> &ImgSize, int nplus = 0, vector<KeyPoint> *AllKeyPts = 0, Mat *AllDesc = 0);
bool loadBundleAdjustedNVMResults(char *BAfileName, Corpus &CorpusData);
bool saveBundleAdjustedNVMResults(char *BAfileName, Corpus &CorpusData);
bool ReSaveBundleAdjustedNVMResults(char *BAfileName, double ScaleFactor = 1.0);
bool ReSaveBundleAdjustedNVMResults(char *BAfileName, Corpus &CorpusData, double ScaleFactor = 1.0);

void Save3DPoints(char *Path, Point3d *All3D, vector<int>Selected3DIndex);
int SaveCorpusInfo(char *Path, Corpus &CorpusData, bool outputtext = false, bool saveDescriptor = true);
int ReadCorpusInfo(char *Path, Corpus &CorpusData, bool inputtext = false, bool notReadDescriptor = false);
bool loadIndividualNVMforpose(char *Path, CameraData *CameraInfo, vector<int>availViews, int timeIDstart, int timeIDstop, int nviews, bool sharedIntrinsics);
int ReadCorpusAndVideoData(char *Path, CorpusandVideo &CorpusandVideoInfo, int ScannedCopursCam, int nVideoViews, int startTime, int stopTime, int LensModel = RADIAL_TANGENTIAL_PRISM, int distortionCorrected = 1);
int ReadVideoData(char *Path, VideoData &AllVideoInfo, int nVideoViews, int startTime, int stopTime, double threshold = 5.0, int ninliersThresh = 40);
int ReadVideoDataI(char *Path, VideoData &VideoInfo, int viewID, int startTime, int stopTime, double threshold = 5.0, int ninliersThresh = 40);
int WriteVideoDataI(char *Path, VideoData &VideoInfo, int viewID, int startTime, int stopTime);

void SaveVideoCameraIntrinsic(char *Fname, CameraData *AllViewParas, vector<int>&AvailTime, int camID, int StartTime);
void SaveVideoCameraPoses(char *Fname, CameraData *AllViewParas, vector<int>&AvailTime, int camID, int StartTime = 0);

int DownSampleSpatialCalib(char *Path, int nviews, int startFrame, int stopFrame, int Factor);

void DetectBlobCorrelation(double *img, int width, int height, Point2d *Checker, int &npts, double sigma, int search_area, int NMS_BW, double thresh);

int GenerateCorpusVisualWords(char *Path, int nimages);
int ComputeWordsHistogram(char *Path, int nimages);

int ReadDomeCalibFile(char *Path, CameraData *AllCamInfo);
int ReadDomeCalibFile2(char *Path, VideoData  &AllCamInfo);

bool LoadTrackData(char* filePath, int CurrentFrame, TrajectoryData &TrajectoryInfo, bool loadVis);
void Write3DMemAtThatTime(char *Path, TrajectoryData &TrajectoryInfo, CameraData *AllCamInfo, int refFrame, int curFrame);
void Genrate2DTrajectory(char *Path, int CurrentFrame, TrajectoryData InfoTraj, CameraData *AllCamInfo, vector<int> trajectoriesUsed);
void Genrate2DTrajectory2(char *Path, int CurrentFrame, TrajectoryData InfoTraj, VideoData  &AllCamInfo, vector<int> trajectoriesUsed);
void Genrate2DTrajectory3(char *Path, int CurrentFrame, TrajectoryData InfoTraj, VideoData &AllVideoData, vector<int> trajectoriesUsed);
int Load2DTrajectory(char *Path, TrajectoryData &inoTraj, int ntrajectories);
int Compute3DTrajectoryErrorColorVar(char *Path, vector<int> SyncOff, int *pair);
int Compute3DTrajectoryErrorZNCC(char *Path, TrajectoryData inoTraj, int nTraj, int minFrame, int maxFrame, int *cameraPair, int* range);
int Compute3DTrajectoryErrorZNCC2(char *Path, TrajectoryData inoTraj, int nTraj, int minFrame, int maxFrame, int *cameraPair, int* range);
int Compute3DTrajectoryErrorZNCCDif(char *Path, TrajectoryData infoTraj, int nTraj, int minFrame, int maxFrame, int viewID, int *range);
int Compute3DTrajectoryError2DTracking(char *Path, TrajectoryData infoTraj, int nTraj, int minFrame, int maxFrame, int SelectedViewID, int *range);

int ImportCalibDatafromHanFormat(char *Path, VideoData &AllVideoInfo, int nVGAPanels, int nVGACamsPerPanel, int nHDs);
void ExportCalibDatatoHanFormat(char *Path, VideoData &AllVideoInfo, int nVideoViews, int startTime, int stopTime, int selectedCam = -1);

void GenerateViewAll_3D_2DInliers(char *Path, int viewID, int startID, int stopID, int n3Dcorpus);

void LaplacianOfGaussian(double *LOG, int sigma);
void synthesize_concentric_circles_mask(double *ring_mask_smooth, int *pattern_bi_graylevel, int pattern_size, double sigma, double scale, double *ring_info, int flag, int num_ring_edge);
void DetectBlobCorrelation(char *ImgName, vector<KeyPoint> &kpts, int nOctaveLayers, int nScalePerOctave, double sigma, int templateSize, int NMS_BW, double thresh);
int DetectRGBBallCorrelation(char *ImgName, vector<KeyPoint> &kpts, vector<int> &ballType, int nOctaveLayers, int nScalePerOctave, double sigma, int PatternSize, int NMS_BW, double thresh, bool visualize);

void TransformImage(double *oImg, int Owidth, int Oheight, double *iImg, int Iwidth, int Iheight, double *Trans, int nchannels, int interpAlgo, double *iPara = NULL);
int ComputeAverageImage(char *Path, unsigned char *MeanImg, int width, int height, int camID, int panelID, int startF, int stopF);
int DetectRedLaserCorrelationMultiScale(char *ImgName, int width, int height, unsigned char *MeanImg, vector<Point2d> &kpts, double sigma, int PatternSize, int nscales, int NMS_BW, double thresh, bool visualize,
	unsigned char *ColorImg, float *colorResponse, double *DImg, double *ImgPara, double *maskSmooth, double *Znssd_reqd);

int CleanCheckBoardDetection(char *Path, int viewID, int startF, int stopF);

double Compute_AffineHomo(vector<Point2d> &From, vector<Point2d> To, double *Affine, double *A = 0, double *B = 0);
double Compute_AffineHomo(Point2d *From, Point2d *To, int npts, double *Affine, Point2d *sFrom, Point2d *sTo, double *A = 0, double *B = 0);
double findTransformECC(InputArray templateImage, InputArray inputImage, InputOutputArray warpMatrix, int motionType, TermCriteria criteria);
double findTransformECC_Optimized(Mat &templateFloat, Mat &imageFloat, Mat &gradientX, Mat &gradientY, Mat &gradientXWarped, Mat &gradientYWarped, Mat &warpMatrix, int motionType, TermCriteria criteria);
double TMatchingSuperCoarse(double *Pattern, int pattern_size, int hsubset, double *Image, int width, int height, int nchannels, Point2i &POI, int search_area, double thresh, double *T = NULL);
double TMatchingFine_ZNCC(double *Pattern, int pattern_size, int hsubset, double *Para, int width, int height, int nchannels, Point2d &POI, int advanced_tech, int Convergence_Criteria, double ZNCCthresh, int InterpAlgo, double *Znssd_reqd = 0);

void RefineCornersFromInit(double *Para, int width, int height, int nchannels, Point2d *Checker, int &npts, vector<double>PatternAngles, int hsubset1, int hsubset2, int searchArea, double ZNCCCoarseThresh, double ZNCCthresh, int InterpAlgo);
void RefineCorners(double *Para, int width, int height, int nchannels, Point2d *Checker, Point2d *Fcorners, int *FStype, int &npts, vector<double>PatternAngles, int hsubset1, int hsubset2, int searchArea, double ZNCCCoarseThresh, double ZNCCthresh, int InterpAlgo);
int CornerDetectorDriver(char *Path, int checkerSize, double ZNCCThreshold, int startF, int stopF, int width, int height);

//Image Correlation
double ComputeZNCCPatch(double *RefPatch, double *TarPatch, int hsubset, int nchannels = 1, double *T = NULL);
double ComputeZNCCImagePatch(Mat &Ref, Mat &Tar, Point2i RefPt, Point2i TarPt, int hsubset, int nchannels = 1, double *T = 0);
double ComputeSSIG(double *Para, int x, int y, int hsubset, int width, int height, int nchannels, int InterpAlgo);
double TemplateMatching0(double *RefPara, double *TarPara, int hsubset, int widthRef, int heightRef, int widthTar, int heightTar, int nchannels, Point2d PR, Point2d PT, int advanced_tech, int Convergence_Criteria, double ZNCCThreshold, int Iter_Max, int InterpAlgo, double *fufv, bool greedySearch = 0, double *ShapePara = 0, double *oPara = 0, double *Timg = 0, double *T = 0, double *ZNCC_reqd = 0);
double TemplateMatching0(float *RefPara, float *TarPara, int hsubset, int widthRef, int heightRef, int widthTar, int heightTar, int nchannels, Point2d PR, Point2d PT, int advanced_tech, int Convergence_Criteria, double ZNCCThreshold, int Iter_Max, int InterpAlgo, double *fufv, bool greedySearch = 0, double *ShapePara = 0, double *oPara = 0, double *Timg = 0, double *T = 0, double *ZNCC_reqd = 0);
double TemplateMatching(double *RefPara, double *TarPara, int refWidth, int refHeight, int tarWidth, int tarHeight, int nchannels, Point2d From, Point2d &Target, LKParameters LKArg, bool greedySearch, double *Timg = 0, double *CorrelBuf = 0, double *iWp = 0, double *direction = 0);
int TrackOpenCVLK(char *Path, int startFrame, int stopFrame, int npryLevels = 5);

int TrackAllPointsWithRefTemplateDriver(char *Path, int viewID, int startF, int fps = 60, int trackingTime = 2, int WinSize = 31, int nWins = 3, int WinStep = 3, int cvPyrLevel = 5, double MeanSSGThresh = 500.0);
int VisualizeTracking(char *Path, int viewID, int startF, int fps, int trackingTime, int npts, int raw = 1);

int ReadCorresAndRunTracking(char *Path, int nviews, int startFrame, int beginFrame, int endFrame, int *FrameOffset, int HighFrameRateFactor = 4);
int CleanUp2DTrackingByGradientConsistency(char *Path, int nviews, int ntrajects);
int DownSampleTracking(char *Path, int nviews, int ntrajects, int HighFrameRateFactor);
int DeletePointsOf2DTracks(char *Path, int nCams, int npts);

int CheckerBoardDetection(char *Path, int viewID, int startF, int stopF, int bw, int bh);
int SingleCameraCalibration(char *Path, int camID, int startFrame, int stopFrame, int bw, int bh, bool hasPoint, int step, float squareSize, int calibrationPattern, int width = 1920, int height = 1080, bool showUndistorsed = false);
#endif
