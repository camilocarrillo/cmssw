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
  //int idsector  = idRoll.sector();
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

  //Global Phi calculation
  double glob_phi   = emtf::rad_to_deg(gPos.phi().value());
  double int_phi = 0.;
 
  //Local phi EMTF calculation   
  double localEMTFPhi = 0.;
  if((glob_phi > 15.) && (glob_phi <= 75.)) localEMTFPhi = glob_phi-15.; 
  if((glob_phi > 75.) && (glob_phi <= 135.)) localEMTFPhi = glob_phi-75.; 
  if((glob_phi > 135.) && (glob_phi <= -165.)) localEMTFPhi = glob_phi-135.; 
  if((glob_phi > -165.) && (glob_phi <= -105.)) localEMTFPhi = glob_phi+165.; 
  if((glob_phi > -105.) && (glob_phi <= -45.)) localEMTFPhi = glob_phi+105.; 
  if((glob_phi > -45.) && (glob_phi <= 15.)) localEMTFPhi = glob_phi+45.;  

  //Invalid hit
  if(isValid == 0) int_phi = 2047;

  int_phi = (localEMTFPhi + 22.0)*15.0; 
 
  CPPFDigi* MainVariables = new CPPFDigi(idRoll, bx, int_phi, int_theta, glob_phi, glob_theta ,isValid, firststrip, clustersize);

  OwnVector<CPPFDigi> Angular;
  Angular.push_back(MainVariables);

  cppfdigiCollection->put(idRoll,Angular.begin(), Angular.end());

  }
  event.put(std::move(cppfdigiCollection));

}
