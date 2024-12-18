import os
from CRABClient.UserUtilities import config, getUsername
config = config()

config.General.requestName = 'RUN2023D0_corrected'
config.General.workArea = 'crab_projects'
config.General.transferOutputs = True
config.General.transferLogs = True

config.JobType.pluginName = 'Analysis'
config.JobType.psetName = '../templateData_RUN2023D.py'
basepath = os.getenv('CMSSW_BASE')+'/src//Hcc/HccAna'
config.JobType.inputFiles = [basepath+'/data/Summer23BPixPrompt23_RunD_V1_DATA.db']
config.Data.inputDBS = 'global'
config.Data.inputDataset = '/JetMET0/Run2023D-19Dec2023-v1/MINIAOD'
config.Data.splitting = 'FileBased'
config.Data.unitsPerJob = 1
config.JobType.numCores = 2
config.Data.publication = True
config.Data.allowNonValidInputDataset = True
config.Data.lumiMask = 'https://cms-service-dqmdc.web.cern.ch/CAF/certification/Collisions23/Cert_Collisions2023_eraD_369803_370790_Golden.json'
# This string is used to construct the output dataset name
config.Data.outputDatasetTag = 'RUN2023D0_corrected'

config.Site.storageSite = 'T2_IT_Bari'
#config.JobType.allowUndistributedCMSSW = True
#config.Site.ignoreGlobalBlacklist  = True
