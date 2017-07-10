/* \source
*
*  \author S. Alejandro , Universidad de los Andes
*/

#include "RecoLocalMuon/CPPFDigi/interface/CPPFDigiProducer.h"

#include "FWCore/MessageLogger/interface/MessageLogger.h"
#include "FWCore/Framework/interface/ESHandle.h"

#include "DataFormats/MuonDetId/interface/RPCDetId.h"
#include "DataFormats/CPPFDigi/interface/CPPFDigi.h"
#include "DataFormats/CPPFDigi/interface/CPPFDigiCollection.h"

#include "Geometry/RPCGeometry/interface/RPCRoll.h"
#include "Geometry/RPCGeometry/interface/RPCGeometry.h"
#include "Geometry/Records/interface/MuonGeometryRecord.h"

#include "L1Trigger/L1TMuonEndCap/interface/PrimitiveConversion.h"
#include "L1Trigger/L1TMuonEndCap/interface/SectorProcessorLUT.h"
#include "L1Trigger/L1TMuonEndCap/interface/TrackTools.h"


#include <string>
#include <fstream>
#include "TVector3.h"

using namespace edm;
using namespace std;

CPPFDigiProducer::CPPFDigiProducer(const ParameterSet& config):
recHitToken_(consumes<RPCRecHitCollection>(config.getParameter<InputTag>("recHitLabel"))){
produces<CPPFDigiCollection>();
}

void CPPFDigiProducer::produce(Event& event, const EventSetup& setup) {


  //Get the RecHits from the event
  Handle<RPCRecHitCollection> rechits;
  event.getByToken(recHitToken_,rechits);
  // Get the RPC Geometry
  ESHandle<RPCGeometry> rpcGeo;
  setup.get<MuonGeometryRecord>().get(rpcGeo);

  // Create the pointer to the collection which will store the cppfdigis 
  auto cppfdigiCollection = std::make_unique<CPPFDigiCollection>();
//  std::unique_ptr<CPPFDigiCollection> cppfdigiCollection(new CPPFDigiCollection());
  //Create rechit iterator

  for ( auto rechit_it  = rechits->begin(); rechit_it  != rechits->end(); ++rechit_it  ) {

  
  RPCDetId idRoll(rechit_it->rpcId()); 
  int idsector  = idRoll.sector();
  int bx = rechit_it->BunchX(); 
  int isValid = rechit_it->isValid();
  int firststrip = rechit_it->firstClusterStrip();
  int clustersize = rechit_it->clusterSize();

  LocalPoint lPos = rechit_it->localPosition(); 
  const RPCRoll* roll = rpcGeo->roll(idRoll);
  const BoundPlane& rollSurface = roll->surface();
  GlobalPoint gPos = rollSurface.toGlobal(lPos);
 
  //theta calculation
  double glob_theta = emtf::rad_to_deg(gPos.theta());
  double int_theta=0.; 
  int_theta=(glob_theta-8.5)*32./36.5;
  if(glob_theta < 8.5) int_theta=0.;
  if(glob_theta > 45.) int_theta=31.;

  //Phi calculation
  double glob_phi   = emtf::rad_to_deg(gPos.phi().value());
//  double int_phi = 0.;
  int fph = emtf::calc_phi_loc_int(glob_phi, idsector, 11);
//  assert(0 <= fph && fph < 1250);
//  int_phi = (lPos.phi().value() + 22.0)*15.0; 

 
  CPPFDigi* MainVariables = new CPPFDigi(idRoll, bx, fph, int_theta, isValid, firststrip, clustersize);

  OwnVector<CPPFDigi> Angular;
  Angular.push_back(MainVariables);

  cppfdigiCollection->put(idRoll,Angular.begin(), Angular.end());

  }
  event.put(std::move(cppfdigiCollection));

}
