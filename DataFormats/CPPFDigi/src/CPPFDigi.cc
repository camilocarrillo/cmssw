/*  See header file for a description of this class.
    \author A. Segura -- Universidad de los Andes
*/

#include "DataFormats/CPPFDigi/interface/CPPFDigi.h"

#include <iostream>


CPPFDigi::CPPFDigi(const RPCDetId& rpcId, int bx) : theRPCId(rpcId), theBx(bx),
						    thePhi_int(0), theTheta_int(0),
						    theGPhi(0), theGTheta(0)
{
}


CPPFDigi::CPPFDigi(): theRPCId(), theBx(99),
		      thePhi_int(0), theTheta_int(0),
		      theGPhi(0), theGTheta(0)
{
}

CPPFDigi::CPPFDigi (const RPCDetId& rpcId,
		    int bx,
		    int16_t phi,
		    int8_t theta,
		    double Gphi,
		    double Gtheta,		 
		    int isvalid,
		    int firstStrip,
		    int clustSize) : theRPCId(rpcId),
				     theBx(bx), thePhi_int(phi), theTheta_int(theta), theGPhi(Gphi), theGTheta(Gtheta), theIsvalid(isvalid), theFirstStrip(firstStrip), theClusterSize(clustSize)
{
}

CPPFDigi::~CPPFDigi(){
}

CPPFDigi * CPPFDigi::clone() const {
  return new CPPFDigi(*this);
}

std::ostream & operator<<(std::ostream & o, const CPPFDigi& cppf){
o << "Local Phi: " << cppf.phi() ;
o << "Local Theta: " << cppf.theta() ;
return o;
}
