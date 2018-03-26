#include <memory>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "TVector3.h"
#include "TLorentzVector.h"
#include <ios>
#include "L1Trigger/DQMCPPF/interface/DQMCPPF.h"

using namespace edm;

DQM_CPPF::DQM_CPPF(const edm::ParameterSet& iConfig) :
  recHitToken_(consumes<RPCRecHitCollection>(iConfig.getParameter<InputTag>("recHitLabel"))),
  cppfDigiToken_(consumes<l1t::CPPFDigiCollection>(iConfig.getParameter<InputTag>("cppfdigiLabel"))){
  
}

DQM_CPPF::~DQM_CPPF(){
}

void DQM_CPPF::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup){
  
  //Get the rechit 
   Handle<RPCRecHitCollection> recHits;
   iEvent.getByToken(recHitToken_, recHits);
   //Get the CPPFDigi 
   Handle<l1t::CPPFDigiCollection> CppfDigis;
   iEvent.getByToken(cppfDigiToken_, CppfDigis);
  
    for(auto& cppf_digis : *CppfDigis){

   
    Phi_Integer->Fill(cppf_digis.phi_int());
    }
   
  
} //End class

void DQM_CPPF::beginRun(const edm::Run& run, const edm::EventSetup& iSetup){
  //  edm::ESHandle<RPCGeometry> rpcGeom;
  iSetup.get<MuonGeometryRecord>().get(rpcGeom);
}

void DQM_CPPF::beginJob(){
  Service<TFileService> fs;
   Phi_Integer = fs->make<TH1D>("Phi_Integer", "Phi_Integer", 1240, 0., 1240.);
   Occupancy_EMTFSector = fs->make<TH2D>("Occupancy_EMTFSector", "Occupancy_EMTFSector", 360, -180., 180., 1300, 0.,1300.);; 
  return;
}

//define this as a plug-in
DEFINE_FWK_MODULE(DQM_CPPF);
