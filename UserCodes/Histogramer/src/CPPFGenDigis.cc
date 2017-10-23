#include <memory>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "TVector3.h"
#include "TLorentzVector.h"
#include <ios>
#include "UserCodes/Histogramer/interface/CPPFGenDigis.h"

using namespace edm;
using namespace std;

CPPFGenDigis::CPPFGenDigis(const edm::ParameterSet& iConfig) :
  genParToken_(consumes<std::vector<reco::GenParticle>>(iConfig.getParameter<InputTag>("genParticlesLabel"))),
  recHitToken_(consumes<RPCRecHitCollection>(iConfig.getParameter<InputTag>("recHitLabel"))),
  cppfDigiToken_(consumes<l1t::CPPFDigiCollection>(iConfig.getParameter<InputTag>("cppfdigiLabel"))){
  
}

CPPFGenDigis::~CPPFGenDigis(){
}

void CPPFGenDigis::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup){
  
  //Get the gen level information
  Handle<vector<reco::GenParticle>> genParHandle;
  iEvent.getByToken(genParToken_,genParHandle);
  //Get the rechit 
  Handle<RPCRecHitCollection> rechits;
  iEvent.getByToken(recHitToken_,rechits);
  //Get the CPPFDigi 
  Handle<l1t::CPPFDigiCollection> SimCppfDigis;
  iEvent.getByToken(cppfDigiToken_, SimCppfDigis);

	  
	  if(SimCppfDigis.isValid()){
	    for(auto& SimCppfDigi : *SimCppfDigis){ 
	      
	      int Int_theta = SimCppfDigi.Theta_int();
	      int Int_phi = SimCppfDigi.Phi_int(); 
	      double Global_theta = SimCppfDigi.Theta_glob(); 
	      double Global_phi = SimCppfDigi.Phi_glob();
	      int EMTFSector = SimCppfDigi.EMTF_sector(); 

	      //Theta
	      Theta_int->Fill(Int_theta);
	      Phi_int->Fill(Int_phi);
	      //Phi
	      Gphi_vsIphi->Fill(Global_phi, Int_phi);
	      Gtheta_vs_Itheta->Fill(Global_theta, Int_theta);
	      if(EMTFSector == 1)   Gphi_vsIphi_sector1->Fill(Global_phi, Int_phi);
	      if(EMTFSector == 2)   Gphi_vsIphi_sector2->Fill(Global_phi, Int_phi);
	      if(EMTFSector == 3)   Gphi_vsIphi_sector3->Fill(Global_phi, Int_phi);
	      if(EMTFSector == 4)   Gphi_vsIphi_sector4->Fill(Global_phi, Int_phi);
	      if(EMTFSector == 5)   Gphi_vsIphi_sector5->Fill(Global_phi, Int_phi);
	      if(EMTFSector == 6)   Gphi_vsIphi_sector6->Fill(Global_phi, Int_phi);
	    } //Loop over CPPFDigis
           }//isValid       

} //End class

void CPPFGenDigis::beginRun(const edm::Run& run, const edm::EventSetup& iSetup){
  edm::ESHandle<RPCGeometry> rpcGeom;
  iSetup.get<MuonGeometryRecord>().get(rpcGeom);
}

void CPPFGenDigis::beginJob(){
  Service<TFileService> fs;
  Theta_int = fs->make<TH1D>("Theta_int", "Theta_int", 64, 0., 32.);
  Phi_int = fs->make<TH1D>("Phi_int", "Phi_int", 1240, 0., 1240.);
  Gtheta_vs_Itheta = fs->make<TH2D>("Gtheta_vs_Itheta", "Gtheta_vs_Itheta", 180, 0., 180., 32, 0.,32.);
  Gphi_vsIphi = fs->make<TH2D>("Gphi_vsIphi", "Gphi_vsIphi", 360, -180., 180., 1300, 0.,1300.);
  Gphi_vsIphi_sector1 = fs->make<TH2D>("Gphi_vsIphi_sector1", "Gphi_vsIphi_sector1", 360, -180., 180., 1300, 0.,1300.);
  Gphi_vsIphi_sector2 = fs->make<TH2D>("Gphi_vsIphi_sector2", "Gphi_vsIphi_sector2", 360, -180., 180., 1300, 0.,1300.);
  Gphi_vsIphi_sector3 = fs->make<TH2D>("Gphi_vsIphi_sector3", "Gphi_vsIphi_sector3", 360, -180., 180., 1300, 0.,1300.);
  Gphi_vsIphi_sector4 = fs->make<TH2D>("Gphi_vsIphi_sector4", "Gphi_vsIphi_sector4", 360, -180., 180., 1300, 0.,1300.);
  Gphi_vsIphi_sector5 = fs->make<TH2D>("Gphi_vsIphi_sector5", "Gphi_vsIphi_sector5", 360, -180., 180., 1300, 0.,1300.);
  Gphi_vsIphi_sector6 = fs->make<TH2D>("Gphi_vsIphi_sector6", "Gphi_vsIphi_sector6", 360, -180., 180., 1300, 0.,1300.);
  return;
}

//define this as a plug-in
DEFINE_FWK_MODULE(CPPFGenDigis);
