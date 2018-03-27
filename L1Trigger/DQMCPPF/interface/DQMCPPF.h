#ifndef L1Trigger_L1TMuonCPPF_DQMCPPF_DQMCPPF_h
#define L1Trigger_L1TMuonCPPF_DQMCPPF_DQMCPPF_h

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/EventSetup.h"
#include "FWCore/Framework/interface/ESHandle.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/MessageLogger/interface/MessageLogger.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "Geometry/RPCGeometry/interface/RPCRoll.h"
#include "Geometry/RPCGeometry/interface/RPCGeometry.h"
#include "Geometry/Records/interface/MuonGeometryRecord.h"

#include "DataFormats/MuonDetId/interface/RPCDetId.h"
#include "DataFormats/RPCRecHit/interface/RPCRecHitCollection.h"
#include "DataFormats/L1TMuon/interface/CPPFDigi.h"
#include "DataFormats/HepMCCandidate/interface/GenParticle.h"
#include "DataFormats/L1TMuon/interface/CPPFDigi.h"
#include "DataFormats/Common/interface/Handle.h"

#include "CondFormats/RPCObjects/interface/RPCMaskedStrips.h"
#include "CondFormats/RPCObjects/interface/RPCDeadStrips.h"
#include "CondFormats/Serialization/interface/Serializable.h"

#include "CommonTools/UtilAlgos/interface/TFileService.h"
#include "L1Trigger/L1TMuonEndCap/interface/TrackTools.h"

#include<boost/cstdint.hpp>
#include "TH1.h"
#include "TH2.h"
#include "TLorentzVector.h"


class DQM_CPPF : public edm::EDAnalyzer {
  
   public:
	explicit DQM_CPPF(const edm::ParameterSet&);
	~DQM_CPPF();
        edm::ESHandle <RPCGeometry> rpcGeom;
        virtual void beginRun(const edm::Run&, const edm::EventSetup&);
        virtual void analyze(const edm::Event&, const edm::EventSetup&) override;

   private:

	virtual void beginJob() override;

   const edm::EDGetTokenT<RPCRecHitCollection> recHitToken_;
   const edm::EDGetTokenT<l1t::CPPFDigiCollection> cppfDigiToken_;

   TH1D* Phi_Integer;
   TH1D* Theta_Integer;
   TH1D* Phi_Global;
   TH1D* Theta_Global;
   TH2D* Phi_Global_Integer;
   TH2D* Theta_Global_Integer;
   TH2D* Occupancy_EMTFSector;
   TH2D* Track_Bx;
};


#endif

