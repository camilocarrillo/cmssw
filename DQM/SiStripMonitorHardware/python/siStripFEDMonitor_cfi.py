import FWCore.ParameterSet.Config as cms

siStripFEDMonitor = cms.EDAnalyzer("SiStripFEDMonitorPlugin",
  #Raw data collection
  RawDataTag = cms.untracked.InputTag('source'),

  #Folder in DQM Store to write global histograms to
  FolderName = cms.untracked.string('SiStrip/ReadoutView/FedMonitoringSummary'),
  
  #Dump buffer info and raw data if any error is found
  PrintDebugMessages = cms.untracked.bool(False),
  #Write the DQM store to a file (DQMStore.root) at the end of the run
  WriteDQMStore = cms.untracked.bool(False),
  
  #Do not book expert histograms at global level if set to true
  DisableGlobalExpertHistograms = cms.untracked.bool(False),
  #Disable the FED level histograms if set to true
  DisableFEDHistograms = cms.untracked.bool(False),
  #Disable the error count histograms used for historic DQM if set to true
  DisableErrorCountHistograms = cms.untracked.bool(False),
  #Override previous three options and book and fill all histograms (so that files can be merged)
  FillAllHistograms = cms.untracked.bool(False)
)
