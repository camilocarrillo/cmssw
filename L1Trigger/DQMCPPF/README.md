# DQM CPPF 

This is the first version of the DQM CPPF Plots for CMSSW_10_1_X.

# Out of the box instructions

```
ssh -XY username@lxplus.cern.ch
#setenv SCRAM_ARCH slc6_amd64_gcc630 
#(or export SCRAM_ARCH=slc6_amd64_gcc630)
cmsrel CMSSW_10_1_X_2018-03-25-2300
cd CMSSW_10_1_X_2018-03-25-2300/src
cmsenv
```

```
git cms-init
git fetch maseguracern
git cms-merge-topic -u maseguracern:DQM_CPPF
#scram b clean 
scram b -j6
```

## Run the code (check the input)
```
cd L1Trigger/DQM_CPPF/test/
cmsRun Generator_DQM_CPPF.py
```

## Setup your Github space (In case you haven't)
```
git remote add YourGitHubName git@github.com:YourGitHubName/cmssw.git
git fetch YourGitHubName
git checkout -b YourBranchName
```

## Modifying files
```
git add <Modified files>
git commit -m "Commit message"
git push my-cmssw YourBranchName
```
