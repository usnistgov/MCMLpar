#pragma once

using namespace std;

class Layer {
	private:
	double n;
	double mus;
	double mua;
	double mut;
	double musDivMut;
	double g;
	double zMin;
	double zMax;
	unsigned int layerNum;

	public:
	Layer( double, double, double, double, double );
	Layer();

	/* get functions */
	double getN();
	double getMus();
	double getMua();
	double getMut();
	double getMusDivMut();
	double getG();
	double getZMin();
	double getZMax();
	double getDist();
	unsigned int getLayerNum();

	/* set functions */
    void setN(double);
	void setMus(double);
	void setMua(double);
	void setDist(double);
	void setG(double);
	void setZMin(double);
	void setZMax(double);
	void setLayerNum(int);
};
