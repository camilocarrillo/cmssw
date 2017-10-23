from CRABClient.UserUtilities import config, getUsernameFromSiteDB
config = config()

config.General.requestName = 'MC_Crab3_CPPF'
config.General.workArea ='Crab3_CPPFRPC'
config.General.transferOutputs = True
config.General.transferLogs = True

config.section_('JobType')
config.JobType.pluginName = 'PrivateMC'
config.JobType.psetName = '/afs/cern.ch/user/m/masegura/CMSSW_9_2_5_patch2/src/L1Trigger/L1TMuonCPPF/test/RunCPPF_GEN_MC.py'
#config.JobType.outputFiles = ['output.root']

config.section_("Data")
config.Data.outputPrimaryDataset = 'MinBias'
config.Data.splitting = 'EventBased'
config.Data.unitsPerJob = 10000
NJOBS = 100  # This is not a configuration parameter, but an auxiliary variable that we use in the next line.
config.Data.totalUnits = config.Data.unitsPerJob * NJOBS
config.Data.outLFNDirBase = '/store/group/dpg_rpc/comm_rpc/Sandbox/%s/' % (getUsernameFromSiteDB())
config.Data.publication = True
config.Data.publishWithGroupName = True
config.Data.ignoreLocality = True
config.Data.outputDatasetTag = 'CRAB3_OCT2017_MC_Generation'
#config.Data.publishDataName = 'CRAB3_OCT2017_MC_Generation'


config.section_("Site")
config.Site.storageSite = "T2_CH_CERN"
