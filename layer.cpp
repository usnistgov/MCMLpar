#include "layer.h"

/* Layer is an object that represents a layer in the medium with some given
optical parameters. */

/* Members:
    n: Index of refraction
    mus: Scattering coefficient
    mua: Attenuation coefficient
    g: Anisotropy
    musDivMut, divVar, mut: Pre-calculations to reduce computation time
    zMin, zMax: Positions of layer boundaries
    layerNum: The index of the layer in the medium. Index 0 is where the particle enters.
*/

/******************************************************************************/

Layer::Layer( double nVar, double musVar, double muaVar,
             double gVar, double zMaxVar ) {
    n = nVar;
    mus = musVar;
    mua = muaVar;
    mut = musVar + muaVar;
    musDivMut = mus / mut;
    g = gVar;
    zMin = 0;
    zMax = zMaxVar;
    layerNum = 0;
}

Layer::Layer() {
    n = 1;
    mus = 1;
    mua = 1;
    mut = mus + mua;
    musDivMut = mus / mut;
    g = 0;
    zMin = 0;
    zMax = 1;
    layerNum = 0;
}

double Layer::getN() {
	return n;
}

double Layer::getMus() {
	return mus;
}

double Layer::getMua() {
	return mua;
}

double Layer::getMut() {
	return mut;
}

double Layer::getMusDivMut() {
    return musDivMut;
}

double Layer::getG() {
	return g;
}

double Layer::getZMin() {
	return zMin;
}

double Layer::getZMax() {
	return zMax;
}

unsigned int Layer::getLayerNum() {
	return layerNum;
}

void Layer::setN( double nVar ) {
	n = nVar;
}

void Layer::setMus( double musVar ) {
	mus = musVar;
	mut = mua + mus;
	musDivMut = mus / mut;
}

void Layer::setMua( double muaVar ) {
	mua = muaVar;
	mut = mua + mus;
	musDivMut = mus / mut;
}

void Layer::setG( double gVar ) {
	g = gVar;
}

void Layer::setZMin( double zMinVar ) {
	zMin = zMinVar;
}

void Layer::setZMax( double zMaxVar ) {
	zMax = zMaxVar;
}

void Layer::setLayerNum( int layerNumVar ) {
	layerNum = layerNumVar;
}
