import FWCore.ParameterSet.Config as cms

demo1 = cms.EDAnalyzer('CPPFGenDigis',
		      genParticlesLabel = cms.InputTag("genParticles"),
		      recHitLabel = cms.InputTag("rpcRecHits"),
                      cppfdigiLabel = cms.InputTag("simCppfDigis","recHit")                  
)
