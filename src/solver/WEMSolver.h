/*! \file WEMSolver.h 
\brief PCM solver
*/


#ifndef WEMSOLVER_H_
#define WEMSOLVER_H_

#include <string>
#include <vector>
#include <iostream>
#include <complex>

extern "C"{
#include "vector3.h"
#include "sparse2.h"
}

using namespace std;

class WEMSolver : public PCMSolver {
 public:
    WEMSolver(GreensFunctionInterface &gfi, GreensFunctionInterface &gfo);
    WEMSolver(GreensFunctionInterface *gfi, GreensFunctionInterface *gfo);
    WEMSolver(const Section & solver);
    ~WEMSolver();
    vector3 **** getT_(){return T_;}
    int getQuadratureLevel(){return quadratureLevel_;}
    virtual void buildSystemMatrix(Cavity & cavity);
    virtual void compCharge(const VectorXd & potential, VectorXd & charge);
 protected:
    virtual void constructSystemMatrix();
    virtual void uploadCavity(WaveletCavity cavity); // different interpolation
    virtual void constructSi() = 0;
    virtual void constructSe() = 0;
    virtual void solveFirstKind(const VectorXd & potential, VectorXd & charge) = 0;
    virtual void solveSecondKind(const VectorXd & potential, VectorXd & charge) = 0;
    virtual void solveFull(const VectorXd & potential, VectorXd & charge) = 0;
    virtual void constructWavelets() = 0;
    virtual void initInterpolation() = 0;
    double threshold;
    unsigned int quadratureLevel_;
    sparse2 S_i_, S_e_; // System matrices
    bool systemMatricesInitialized_;
    vector3 *** pointList; // the old U
    vector3 *nodeList; //*P_; --     // Point list
    unsigned int **elementList; //**F_;     // Element list
    vector3 ****T_; // interpolation polynomial coefficients
    unsigned int nNodes; //np_; --    // Number of knot points or something
    unsigned int nFunctions; //nf_; --    // Number of ansatz functions
    unsigned int nPatches; // p_; --    // Number of points 
    unsigned int nLevels; //M_; --    // Patch level (2**M * 2**M elements per patch)
    int nQuadPoints; // nPoints_;    // Number of quadrature points
    double apriori1_, aposteriori1_;    // System matrix sparsities
    double apriori2_, aposteriori2_;    // System matrix sparsities
 private:
    void initWEMMembers();
};
#endif