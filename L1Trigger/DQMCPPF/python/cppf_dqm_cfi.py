import FWCore.ParameterSet.Config as cms

DQM_CPPF = cms.EDAnalyzer('DQM_CPPF',
		      recHitLabel = cms.InputTag("rpcRecHits"),
                      cppfdigiLabel = cms.InputTag("emulatorCppfDigis","recHit")                  
)
