#ifndef RecoLocalMuon_CPPFDigiProducer_h
#define RecoLocalMuon_CPPFDigiProducer_h

/* \class CPPFDigiProducer
*  Module for CPPFDigi production. 
*  
*  \author A. Segura -- Universidad de los Andes
*/

#include "FWCore/Framework/interface/stream/EDProducer.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/Utilities/interface/InputTag.h"

#include "DataFormats/RPCDigi/interface/RPCDigiCollection.h"
#include "DataFormats/RPCRecHit/interface/RPCRecHitCollection.h"

#include "CondFormats/RPCObjects/interface/RPCDeadStrips.h"
#include <assert.h>

class CPPFDigiProducer : public edm::stream::EDProducer<> {

public:

  CPPFDigiProducer(const edm::ParameterSet& config);
  virtual ~CPPFDigiProducer() {};

  virtual void produce(edm::Event& event, const edm::EventSetup& setup) override;

private:

  // The label to be used to retrieve RPCRecHits from the event
  const edm::EDGetTokenT<RPCRecHitCollection> recHitToken_;
       
};

#endif
