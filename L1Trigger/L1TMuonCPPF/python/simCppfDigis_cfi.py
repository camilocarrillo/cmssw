import FWCore.ParameterSet.Config as cms

simCppfDigis = cms.EDProducer("L1TMuonCPPFDigiProducer",
    
    ## Input collection
    recHitLabel = cms.InputTag("rpcRecHits"),
                              
    )

