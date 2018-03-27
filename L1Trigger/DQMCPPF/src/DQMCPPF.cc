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
  
  for(auto& rec_hits : *recHits){
    RPCDetId rpcId = rec_hits.rpcId();
    int ring = rpcId.ring(); 
    int station = rpcId.station();
    int region = rpcId.region();
    int clustersize = rec_hits.clusterSize();
    int firststrip = rec_hits.firstClusterStrip();
    
    int rechitstrip = firststrip;
    
    if(clustersize > 2) {
      int medium = 0;
      if (clustersize % 2 == 0) medium = 0.5*(clustersize);
      else medium = 0.5*(clustersize-1);
      rechitstrip += medium;
    }
    
    if(clustersize > 3) continue;
    
    for(auto& cppf_digis : *CppfDigis){
      
      if((cppf_digis.rpcId().rawId() == rpcId.rawId()) && (cppf_digis.first_strip() == rechitstrip)){
	
        if(region == -1){
	  if((station == 4) && (ring == 3))
	    Occupancy_EMTFSector->Fill(cppf_digis.emtf_sector(), 0.5);
	  else if((station == 4) && (ring == 2))
	    Occupancy_EMTFSector->Fill(cppf_digis.emtf_sector(), 1.5);
	  else if((station == 3) && (ring == 3))
	    Occupancy_EMTFSector->Fill(cppf_digis.emtf_sector(), 2.5);
	  else if((station == 3) && (ring == 2))
	    Occupancy_EMTFSector->Fill(cppf_digis.emtf_sector(), 3.5);
	  else if((station == 2) && (ring == 2))
	    Occupancy_EMTFSector->Fill(cppf_digis.emtf_sector(), 4.5);
	  else if((station == 1) && (ring == 2))
	    Occupancy_EMTFSector->Fill(cppf_digis.emtf_sector(), 5.5);
        }
	
        else if(region == 1){
	  if((station == 1) && (ring == 2)) 
	    Occupancy_EMTFSector->Fill(cppf_digis.emtf_sector(), 6.5);          
	  else if((station == 2) && (ring == 2))
	    Occupancy_EMTFSector->Fill(cppf_digis.emtf_sector(), 7.5);          
	  else if((station == 3) && (ring == 2))
	    Occupancy_EMTFSector->Fill(cppf_digis.emtf_sector(), 8.5);          
	  else if((station == 3) && (ring == 3))
	    Occupancy_EMTFSector->Fill(cppf_digis.emtf_sector(), 9.5);          
	  else if((station == 4) && (ring == 2))
	    Occupancy_EMTFSector->Fill(cppf_digis.emtf_sector(), 10.5);          
	  else if((station == 4) && (ring == 3))
	    Occupancy_EMTFSector->Fill(cppf_digis.emtf_sector(), 11.5);          
        }
	
	//For Track_Bx
        if(region == -1){
          if(cppf_digis.emtf_sector()==1)
            Track_Bx->Fill(5.5,cppf_digis.bx());
          else if(cppf_digis.emtf_sector()==2)
            Track_Bx->Fill(4.5,cppf_digis.bx());
          else if(cppf_digis.emtf_sector()==3)
            Track_Bx->Fill(3.5,cppf_digis.bx());
          else if(cppf_digis.emtf_sector()==4)
            Track_Bx->Fill(2.5,cppf_digis.bx());
          else if(cppf_digis.emtf_sector()==5)
            Track_Bx->Fill(1.5,cppf_digis.bx());
          else if(cppf_digis.emtf_sector()==6)
            Track_Bx->Fill(0.5,cppf_digis.bx());
        }
 	else if(region == 1){
          if(cppf_digis.emtf_sector()==1)
            Track_Bx->Fill(6.5,cppf_digis.bx());
          else if(cppf_digis.emtf_sector()==2)
            Track_Bx->Fill(7.5,cppf_digis.bx());
          else if(cppf_digis.emtf_sector()==3)
            Track_Bx->Fill(8.5,cppf_digis.bx());
          else if(cppf_digis.emtf_sector()==4)
            Track_Bx->Fill(9.5,cppf_digis.bx());
          else if(cppf_digis.emtf_sector()==5)
            Track_Bx->Fill(10.5,cppf_digis.bx());
          else if(cppf_digis.emtf_sector()==6)
            Track_Bx->Fill(11.5,cppf_digis.bx());
	}
	
      } //Condition to save CPPFDIgis
      
    } // loop over CPPFDigis
    
  } //Loop over rechits
  
  for(auto& cppf_digis : *CppfDigis){
    Phi_Integer->Fill(cppf_digis.phi_int());
    Theta_Integer->Fill(cppf_digis.theta_int());
    Phi_Global->Fill(cppf_digis.phi_glob()*TMath::Pi()/180.);
    Theta_Global->Fill(cppf_digis.theta_glob()*TMath::Pi()/180.);
    Phi_Global_Integer->Fill(cppf_digis.phi_glob(), cppf_digis.phi_int());
    Theta_Global_Integer->Fill(cppf_digis.theta_glob(), cppf_digis.theta_int());
  }
  
  
} //End class

void DQM_CPPF::beginRun(const edm::Run& run, const edm::EventSetup& iSetup){
  //  edm::ESHandle<RPCGeometry> rpcGeom;
  iSetup.get<MuonGeometryRecord>().get(rpcGeom);
}

void DQM_CPPF::beginJob(){
  Service<TFileService> fs;
  Phi_Integer = fs->make<TH1D>("Phi_Integer", "Phi_Integer", 1240, 0., 1240.);
  Theta_Integer = fs->make<TH1D>("Theta_Integer", "Theta_Integer", 32, 0., 32.);
  Phi_Global = fs->make<TH1D>("Phi_Global", "Phi_Global", 72, -3.15, 3.15);
  Theta_Global = fs->make<TH1D>("Theta_Global", "Theta_Global", 32, 0., 3.15);
  Phi_Global_Integer = fs->make<TH2D>("Phi_Global_Integer", "Phi_Global_Integer", 360, -180, 180, 1240, 0.,1240.);
  Theta_Global_Integer = fs->make<TH2D>("Theta_Global_Integer", "Theta_Global_Integer", 45, 0, 45, 32, 0.,32.);
  Occupancy_EMTFSector = fs->make<TH2D>("Occupancy_EMTFSector", "Occupancy_EMTFSector", 42, 1., 7., 11, 0.,12.); 
  Track_Bx = fs->make<TH2D>("Track_Bx","Track_Bx", 12, 0, 12., 7,-3.,4.);
  return;
}
//define this as a plug-in
DEFINE_FWK_MODULE(DQM_CPPF);
