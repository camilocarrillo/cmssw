#ifndef DataFormats_CPPFDigi_H
#define DataFormats_CPPFDigi_H

/* \class CPPFDigi 
 *
 * \author A. Segura -- Universidad de los Andes 
 */
#include "DataFormats/MuonDetId/interface/RPCDetId.h"

#include <iostream>
#include <cstdint>
#include <iosfwd>
#include <stdint.h>

class CPPFDigi{
 public:
  
  CPPFDigi(const RPCDetId& rpcId, int bx);
  //Default constructor
  CPPFDigi ();
  // Constructor for angular variables
  explicit CPPFDigi (const RPCDetId& rpcId, 
		     int bx, 
		     int16_t phi, 
		     int8_t theta,
		     double Gphi,
		     double Gtheta,
 		     int isvalid,
		     int firstStrip,
		     int clustSize); 
  
  bool operator==(const CPPFDigi& cppf) const;
  
  RPCDetId rpcId() const {
    return theRPCId;
  }
  
  int BunchX() const {
    return theBx;
  }
  
  
  double phi() const { 
    return thePhi_int;
  }
  
  double theta() const { 
    return theTheta_int;
  }

  double Gphi() const {
    return theGPhi;
  }

  double Gtheta() const {
    return theGTheta;
  }
 
 
  int IsValid() const{
    return theIsvalid;
  }
  
  int firstClusterStrip() const {
    return theFirstStrip;
  }
  
  int clusterSize() const {
    return theClusterSize;
  }
  
  virtual ~CPPFDigi();
  
  virtual CPPFDigi* clone() const;
  
 private:
  
  RPCDetId theRPCId;
  int theBx;
  int16_t thePhi_int;
  int8_t theTheta_int;
  double theGPhi;
  double theGTheta;
  int theIsvalid;
  int theFirstStrip;
  int theClusterSize;
  
};

#endif

/// The ostream operator
std::ostream & operator<<(std::ostream & o, const CPPFDigi& cppf);
