Hcc, Zqq Analyzer for CMS Run3

CMSSW: 12.4.3 

------

# Install

follow install.sh instruction

# access to cms vo
    voms-proxy-init  --voms cms -valid 192:00

# Run the ntuplizer
- To run on Data 

    cmsRun python/templateData_Run3_Hcc_cfg.py

- To run on MC
    cmsRun python/templateMC_Zcc_Run3.py

!IMPORTANT: change the global tag accordingly to the dataset you use in input 
(https://github.com/BariGEMJetTau/Hcc/blob/main/HccAna/python/templateMC_Zcc_Run3.py#L17)

-To submit on CRAB use the script https://github.com/BariGEMJetTau/Hcc/blob/main/HccAna/python/crab/crab_Zcc.py
