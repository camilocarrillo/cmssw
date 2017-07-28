#ifndef L1Trigger_L1TMuonCPPF_RecHitProcessor_h
#define L1Trigger_L1TMuonCPPF_RecHitProcessor_h

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/EventSetup.h"
#include "FWCore/Framework/interface/ESHandle.h"

#include "DataFormats/RPCRecHit/interface/RPCRecHitCollection.h"
#include "DataFormats/L1TMuon/interface/CPPFDigi.h"

#include "Geometry/Records/interface/MuonGeometryRecord.h"
#include "Geometry/RPCGeometry/interface/RPCGeometry.h"
#include "Geometry/RPCGeometry/interface/RPCRoll.h"

#include "L1Trigger/L1TMuonEndCap/interface/TrackTools.h"

class RecHitProcessor {
 public:
  explicit RecHitProcessor();
  ~RecHitProcessor();

  void process(
      // Input
      const edm::Event& iEvent,
      const edm::EventSetup& iSetup,
      const edm::EDGetToken& recHitToken,
      // Output
      l1t::CPPFDigiCollection& cppfDigis
  ) const;


 private:
  
};

#endif /* #define L1Trigger_L1TMuonCPPF_RecHitProcessor_h */
