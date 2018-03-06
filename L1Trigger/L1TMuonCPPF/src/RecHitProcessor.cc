
#include "L1Trigger/L1TMuonCPPF/interface/RecHitProcessor.h"

RecHitProcessor::RecHitProcessor() {
}

RecHitProcessor::~RecHitProcessor() {
}

void RecHitProcessor::process(
    const edm::Event& iEvent,
    const edm::EventSetup& iSetup,
    const edm::EDGetToken& recHitToken,
    l1t::CPPFDigiCollection& cppfDigis
) const {

  // Get the RPC Geometry
  edm::ESHandle<RPCGeometry> rpcGeom;
  iSetup.get<MuonGeometryRecord>().get(rpcGeom);

  // Get the RecHits from the event
  edm::Handle<RPCRecHitCollection> recHits;
  iEvent.getByToken(recHitToken, recHits);

  // Loop over ... what, exactly?
  for ( TrackingGeometry::DetContainer::const_iterator iDet = rpcGeom->dets().begin(); iDet < rpcGeom->dets().end(); iDet++ ) {

    // What does this do?  Check whether the chamber is an RPC chamber?
    if (dynamic_cast<const RPCChamber*>( *iDet ) == 0 ) continue;

    auto chamb = dynamic_cast<const RPCChamber* >( *iDet ); 
    std::vector<const RPCRoll*> rolls = (chamb->rolls());

    // Loop over rolls in the chamber
    for (std::vector<const RPCRoll*>::const_iterator iRoll = rolls.begin(); iRoll != rolls.end(); ++iRoll) {
      
      RPCDetId rpcId = (*iRoll)->id();	
      
      typedef std::pair<RPCRecHitCollection::const_iterator, RPCRecHitCollection::const_iterator> rangeRecHits;
      rangeRecHits recHitCollection =  recHits->get(rpcId);
      
      
      for (RPCRecHitCollection::const_iterator recHit = recHitCollection.first; recHit != recHitCollection.second; recHit++) {	  
	
	int bx = recHit->BunchX();
	// int sector = rpcId.sector(); 
	int isValid = recHit->isValid();
	int firststrip = recHit->firstClusterStrip();
	int clustersize = recHit->clusterSize();
	
	LocalPoint lPos = recHit->localPosition(); 
	const RPCRoll* roll = rpcGeom->roll(rpcId);
	const BoundPlane& rollSurface = roll->surface();
	GlobalPoint gPos = rollSurface.toGlobal(lPos);
	
	// Global theta 
	float glob_theta = emtf::rad_to_deg(gPos.theta().value());
	// Local EMTF
	int8_t int_theta=0; 
	if (glob_theta <= 90.){
	  int_theta=(int8_t)glob_theta*32./36.5-8.5*32./36.5;
	  if (glob_theta < 8.5) int_theta=0;
	  if (glob_theta > 45.) int_theta=31;
	}
	else if (glob_theta > 90.){	 
	  float glob_thetaM = 180. - glob_theta;
	  int_theta=(int8_t)glob_thetaM*32./36.5-8.5*32./36.5;
	  if (glob_theta > 171.5) int_theta=0;
	  if (glob_theta < 135.) int_theta=31;
	}
	
	//Global Phi calculation
	double glob_phi   = emtf::rad_to_deg(gPos.phi().value());
	//Local EMTF
	double local_phi1 = 0.;
	double local_phi2 = 0.;
	int EMTFsector1 = 0;
	int EMTFsector2 = 0;
	
	//sector 1
	if ((glob_phi > 15) && (glob_phi <= 16.3)) {
	  local_phi1 = glob_phi-15;
	  EMTFsector1 = 1;
	  local_phi2 = glob_phi+45;
	  EMTFsector2 = 6;
	}
	if ((glob_phi > 16.3) && (glob_phi <= 53)) {
	  local_phi1 = glob_phi-15;
	  EMTFsector1 = 1;
	  local_phi2 = 0.;
	  EMTFsector2 = 0;
	}
	if ((glob_phi > 53) && (glob_phi <= 75)) {
	  local_phi1 = glob_phi-15;
	  EMTFsector1 = 1;
	  local_phi2 = glob_phi-75;
	  EMTFsector2 = 2;
	}
	//sector 2 
	if ((glob_phi > 75) && (glob_phi <= 76.3)) {
	  local_phi1 = glob_phi-15;
	  EMTFsector1 = 1;
	  local_phi2 = glob_phi-75;
	  EMTFsector2 = 2;
	}
	if ((glob_phi > 76.3) && (glob_phi <= 113)) {
	  local_phi1 = glob_phi-75;
	  EMTFsector1 = 2;
	  local_phi2 = 0.;
	  EMTFsector2 = 0;
	}
	if ((glob_phi > 113) && (glob_phi <= 135)) {
	  local_phi1 = glob_phi-75;
	  EMTFsector1 = 2;
	  local_phi2 = glob_phi-135;
	  EMTFsector2 = 3;
	}
	//sector 3
	//less than 180
	if ((glob_phi > 135) && (glob_phi <= 136.3)) {
	  local_phi1 = glob_phi-75;
	  EMTFsector1 = 2;
	  local_phi2 = glob_phi-135;
	  EMTFsector2 = 3;
	}
	if ((glob_phi > 136.3) && (glob_phi <= 173)) {
	  local_phi1 = glob_phi-135;
	  EMTFsector1 = 3;
	  local_phi2 = 0.;
	  EMTFsector2 = 0;
	}
	if ((glob_phi > 173) && (glob_phi <= 180)) {
	  local_phi1 = glob_phi-135;
	  EMTFsector1 = 3;
	  local_phi2 = glob_phi-195;
	  EMTFsector2 = 4;
	}
	//Greater than -180
	if ((glob_phi < -165) && (glob_phi >= -180)) {
	  local_phi1 = glob_phi+225;
	  EMTFsector1 = 3;
	  local_phi2 = glob_phi+165;
	  EMTFsector2 = 4;
	}
	//Fourth sector
	if ((glob_phi > -165.) && (glob_phi <= -163.7)) {
	  local_phi1 = glob_phi+225;
	  EMTFsector1 = 3;
	  local_phi2 = glob_phi+165;
	  EMTFsector2 = 4;
	}
	if ((glob_phi > -163.7) && (glob_phi <= -127)) {
	  local_phi1 = glob_phi+165;
	  EMTFsector1 = 4;
	  local_phi2 = 0.;
	  EMTFsector2 = 0;
	}
	if ((glob_phi > -127.) && (glob_phi <= -105)) {
	  local_phi1 = glob_phi+165;
	  EMTFsector1 = 4;
	  local_phi2 = glob_phi+105;
	  EMTFsector2 = 5;
	}
	//fifth sector
	if ((glob_phi > -105.) && (glob_phi <= -103.7)) {
	  local_phi1 = glob_phi+165;
	  EMTFsector1 = 4;
	  local_phi2 = glob_phi+105;
	  EMTFsector2 = 5;
	}
	if ((glob_phi > -103.7) && (glob_phi <= -67)) {
	  local_phi1 = glob_phi+105;
	  EMTFsector1 = 5;
	  local_phi2 = 0.;
	  EMTFsector2 = 0;
	}
	if ((glob_phi > -67.) && (glob_phi <= -45)) {
	  local_phi1 = glob_phi+105;
	  EMTFsector1 = 5;
	  local_phi2 = glob_phi+45;
	  EMTFsector2 = 6;
	} 
	//sixth sector
	if ((glob_phi > -45.) && (glob_phi <= -43.7)) {
	  local_phi1 = glob_phi+105;
	  EMTFsector1 = 5;
	  local_phi2 = glob_phi+45;
	  EMTFsector2 = 6;
	} 
	if ((glob_phi > -43.7) && (glob_phi <= -7)) {
	  local_phi1 = glob_phi+45;
	  EMTFsector1 = 6;
	  local_phi2 = 0.;
	  EMTFsector2 = 0;
	}
	if ((glob_phi > -7.) && (glob_phi <= 15)) {
	  local_phi1 = glob_phi+45;
	  EMTFsector1 = 6;
	  local_phi2 = glob_phi-15;
	  EMTFsector2 = 1;
	} 
	
	int16_t int_phi1 = (int)local_phi1*15. + 22.*15.; 
	int16_t int_phi2 = (int)local_phi2*15. + 22.*15.;  
	
	//Invalid hit
	if (isValid == 0) int_phi1 = 2047;	 
	if (isValid == 0) int_phi2 = 2047; 
	//Right integers range
	assert(0 <= int_phi1 && int_phi1 < 1250);
	assert(0 <= int_phi2 && int_phi2 < 1250);
	assert(0 <= int_theta && int_theta < 32);
	
	l1t::CPPFDigi* MainVariables1 = new l1t::CPPFDigi(rpcId, bx, int_phi1, int_theta, EMTFsector1, isValid, 
							  firststrip, clustersize, glob_phi, glob_theta );
	l1t::CPPFDigi* MainVariables2 = new l1t::CPPFDigi(rpcId, bx, int_phi2, int_theta, EMTFsector2, isValid, 
							  firststrip, clustersize, glob_phi, glob_theta );
	
	cppfDigis.push_back(*MainVariables1);
	if (local_phi2 != 0.) cppfDigis.push_back(*MainVariables2);
	
      } // End loop: for (RPCRecHitCollection::const_iterator recHit = recHitCollection.first; recHit != recHitCollection.second; recHit++)
      
    } // End loop: for (std::vector<const RPCRoll*>::const_iterator r = rolls.begin(); r != rolls.end(); ++r)
  } // End loop: for (TrackingGeometry::DetContainer::const_iterator iDet = rpcGeom->dets().begin(); iDet < rpcGeom->dets().end(); iDet++)
  
} // End function: void RecHitProcessor::process()
