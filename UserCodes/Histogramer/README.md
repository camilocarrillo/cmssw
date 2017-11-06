cmsrel CMSSW_9_2_5_patch2
cd CMSSW_9_2_5_patch2/src
cmsenv
git clone $path L1Trigger/L1TMuon/data
scram b 
cd Histogramer/test/
cmsRun test/XXXXX.py
