ssh -X -Y username@lxplus.cern.ch
setenv SCRAM_ARCH slc6_amd64_gcc530 (or export SCRAM_ARCH=slc6_amd64_gcc530)
cmsrel CMSSW_9_2_5_patch2
cd CMSSW_9_2_5_patch2/src
cmsenv
git cms-init
git cms-addpkg DataFormats/L1TMuon
git cms-addpkg L1Trigger/L1TCommon
git cms-addpkg L1Trigger/L1TMuon
git cms-addpkg L1Trigger/L1TMuonEndCap
git remote add cms-l1t-offline git@github.com:cms-l1t-offline/cmssw.git
git fetch cms-l1t-offline
git cms-merge-topic -u cms-l1t-offline:l1t-integration-CMSSW_9_2_5_patch2
git checkout cms-l1t-offline/l1t-integration-CMSSW_9_2_5_patch2
git clone https://github.com/cms-l1t-offline/L1Trigger-L1TMuon.git L1Trigger/L1TMuon/data
rehash; scram b clean; scram b -j 6

git fetch abrinke1
git cms-merge-topic -u abrinke1:CPPF_emul_9_2_5_patch2
scram b clean
scram b -j 6

git remote add YourGitHubName git@github.com:YourGitHubName/cmssw.git
git fetch YourGitHubName
git checkout -b YourBranchName

cd L1Trigger/L1TMuonCPPF
cmsRun test/RunCPPF_MC.py  
## This runs off already-generated MC, which is much faster
## You can still run the MC generation+CPPF emulation with RunCPPF_GEN_MC.py

## Modify files
git add <Modified files>
git commit -m "Commit message"
git push YourGitHubName YourBranchName

for my study the branch is 
Study_Alejandro
