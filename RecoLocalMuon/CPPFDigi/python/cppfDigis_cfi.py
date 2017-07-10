import FWCore.ParameterSet.Config as cms

cppfDigis = cms.EDProducer("CPPFDigiProducer",
    recHitLabel = cms.InputTag("rpcRecHits"),
)

