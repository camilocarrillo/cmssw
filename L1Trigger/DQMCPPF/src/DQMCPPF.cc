#include <memory>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "TVector3.h"
#include "TLorentzVector.h"
#include <ios>
#include <map>
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
  
  //Fill the specific bin for each EMTF sector 
  for(int i = 1; i < 7; i++ ){
    EMTFsector1bins.push_back(i);
    EMTFsector2bins.push_back(i+6);
    EMTFsector3bins.push_back(i+12);
    EMTFsector4bins.push_back(i+18);
    EMTFsector5bins.push_back(i+24);
    EMTFsector6bins.push_back(i+30);
  }
  //FIll the map for each EMTF sector 
  fill_info[1] = EMTFsector1bins;
  fill_info[2] = EMTFsector2bins;
  fill_info[3] = EMTFsector3bins;
  fill_info[4] = EMTFsector4bins;
  fill_info[5] = EMTFsector5bins;
  fill_info[6] = EMTFsector6bins;
  
  
  for(auto& rec_hits : *recHits){
    RPCDetId rpcId = rec_hits.rpcId();
    int ring = rpcId.ring(); 
    int station = rpcId.station();
    int region = rpcId.region();
    //int sector = rpcId.sector();
    int subsector = rpcId.subsector();
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
    
    int EMTF_sector = 0;    
    int EMTF_subsector = 0;
    
    for(auto& cppf_digis : *CppfDigis){
      
      if((cppf_digis.rpcId().rawId() == rpcId.rawId()) && (cppf_digis.first_strip() == rechitstrip)){
        //Region -	
        if(region == -1){
	  
	  //for Occupancy
          EMTF_sector = cppf_digis.emtf_sector();
          EMTF_subsector = fill_info[EMTF_sector][subsector-1];
	  
	  if((station == 4) && (ring == 3))
	    Occupancy_EMTFSector->Fill(EMTF_subsector, 1);
	  else if((station == 4) && (ring == 2))
	    Occupancy_EMTFSector->Fill(EMTF_subsector, 2);
	  else if((station == 3) && (ring == 3))
	    Occupancy_EMTFSector->Fill(EMTF_subsector, 3);
	  else if((station == 3) && (ring == 2))
	    Occupancy_EMTFSector->Fill(EMTF_subsector, 4);
	  else if((station == 2) && (ring == 2))
	    Occupancy_EMTFSector->Fill(EMTF_subsector, 5);
	  else if((station == 1) && (ring == 2))
	    Occupancy_EMTFSector->Fill(EMTF_subsector, 6);
	  
	  //for Track_Bx 
          if(EMTF_sector==1)
            Track_Bx->Fill(6,cppf_digis.bx());
          else if(EMTF_sector==2)
            Track_Bx->Fill(5,cppf_digis.bx());
          else if(EMTF_sector==3)
            Track_Bx->Fill(4,cppf_digis.bx());
          else if(EMTF_sector==4)
            Track_Bx->Fill(3,cppf_digis.bx());
          else if(EMTF_sector==5)
            Track_Bx->Fill(2,cppf_digis.bx());
          else if(EMTF_sector==6)
            Track_Bx->Fill(1,cppf_digis.bx());
        }
        //Region +	
        else if(region == 1){
	  
	  //for Occupancy
          EMTF_sector = cppf_digis.emtf_sector();
          EMTF_subsector = fill_info[EMTF_sector][subsector-1]; 
	  
	  if((station == 1) && (ring == 2)) 
	    Occupancy_EMTFSector->Fill(EMTF_subsector, 7);          
	  else if((station == 2) && (ring == 2))
	    Occupancy_EMTFSector->Fill(EMTF_subsector, 8);          
	  else if((station == 3) && (ring == 2))
	    Occupancy_EMTFSector->Fill(EMTF_subsector, 9);          
	  else if((station == 3) && (ring == 3))
	    Occupancy_EMTFSector->Fill(EMTF_subsector, 10);          
	  else if((station == 4) && (ring == 2))
	    Occupancy_EMTFSector->Fill(EMTF_subsector, 11);          
	  else if((station == 4) && (ring == 3))
	    Occupancy_EMTFSector->Fill(EMTF_subsector, 12);          
	  //for Track_Bx
          if(EMTF_sector==1)
            Track_Bx->Fill(7,cppf_digis.bx());
          else if(EMTF_sector==2)
            Track_Bx->Fill(8,cppf_digis.bx());
          else if(EMTF_sector==3)
            Track_Bx->Fill(9,cppf_digis.bx());
          else if(EMTF_sector==4)
            Track_Bx->Fill(10,cppf_digis.bx());
          else if(EMTF_sector==5)
            Track_Bx->Fill(11,cppf_digis.bx());
          else if(EMTF_sector==6)
            Track_Bx->Fill(12,cppf_digis.bx());
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
  Occupancy_EMTFSector = fs->make<TH2D>("Occupancy_EMTFSector", "Occupancy_EMTFSector", 36, 1., 37., 12, 1.,13.); 
  Track_Bx = fs->make<TH2D>("Track_Bx","Track_Bx", 12, 1., 13., 7,-3.,4.);
  return;
}
//define this as a plug-in
DEFINE_FWK_MODULE(DQM_CPPF);
