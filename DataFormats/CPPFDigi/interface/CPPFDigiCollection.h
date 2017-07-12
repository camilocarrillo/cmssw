#ifndef DataFormats_CPPFDigiCollection_H
#define DataFormats_CPPFDigiCollection_H

/* \class CPPFDigiCollection
*  Collection of CPPFDigi for storage in the event
*  \author A. Segura - Universidad de los Andes
*/

#include <DataFormats/MuonDetId/interface/RPCDetId.h>
#include <DataFormats/CPPFDigi/interface/CPPFDigi.h>
#include <DataFormats/MuonData/interface/MuonDigiCollection.h>

#include "DataFormats/Common/interface/RangeMap.h"
#include "DataFormats/Common/interface/ClonePolicy.h"
#include "DataFormats/Common/interface/OwnVector.h"


typedef edm::RangeMap <RPCDetId, edm::OwnVector<CPPFDigi>> CPPFDigiCollection;

#endif

