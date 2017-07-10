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

class CPPFDigi{
 public:
  
  CPPFDigi(const RPCDetId& rpcId, int bx);
  //Default constructor
  CPPFDigi ();
  // Constructor for angular variables
  explicit CPPFDigi (const RPCDetId& rpcId, 
		     int bx, 
		     double phi, 
		     double theta,
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
  double thePhi_int;
  double theTheta_int;
  int theIsvalid;
  int theFirstStrip;
  int theClusterSize;
  
};

#endif

/// The ostream operator
std::ostream & operator<<(std::ostream & o, const CPPFDigi& cppf);
