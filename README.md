HZZ Analyzer for CMS Run2

CMSSW: 12.4.3 

------

To install:

follow install.sh instruction

--- cms vo access---------------
voms-proxy-init  --voms cms -valid 192:00
-----------------------------------

- To run on Data 

cmsRun python/templateData_Run3_Hcc_cfg.py

- To run on MC
cmsRun python/templateMC_Zcc_Run3.py

IMPORTANT: change the global tag accordingly to the dataset you use in input 
(https://github.com/BariGEMJetTau/Hcc/blob/main/HccAna/python/templateMC_Zcc_Run3.py#L17)

-To submit on CRAB use the script https://github.com/BariGEMJetTau/Hcc/blob/main/HccAna/python/crab/crab_Zcc.py
