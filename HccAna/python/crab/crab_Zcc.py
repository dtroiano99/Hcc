from CRABClient.UserUtilities import config, getUsername
config = config()

config.General.requestName = 'Zcc_HT200to400_ntupl'
config.General.workArea = 'crab_projects'
config.General.transferOutputs = True
config.General.transferLogs = True

config.JobType.pluginName = 'Analysis'
config.JobType.psetName = '../templateMC_Zcc_Run3.py'
config.Data.inputDBS = 'phys03'
config.Data.inputDataset = '/ZJetsToQQ_HT200to400_TuneCP5_13TeV-madgraphMLM-pythia8/fsimone-124X_mcRun3_2022_realistic_v12_MINIAODSIM-62b8fefc005f1de470b29e2d794227f3/USER'
config.Data.splitting = 'FileBased'
config.Data.unitsPerJob = 3
config.JobType.numCores = 2
config.Data.publication = True
# This string is used to construct the output dataset name
config.Data.outputDatasetTag = 'Zcc_HT200to400_ntuple'

config.Site.storageSite = 'T2_IT_Bari'
#config.JobType.allowUndistributedCMSSW = True
#config.Site.ignoreGlobalBlacklist  = True
