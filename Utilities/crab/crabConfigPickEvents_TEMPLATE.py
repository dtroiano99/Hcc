from WMCore.Configuration import Configuration
from CRABClient.UserUtilities import config, getUsernameFromSiteDB
config = Configuration()

config.section_('General')
config.General.workArea = 'resultsPickEvents_JOBTAG/'
config.General.requestName = 'OUTFILENAME'
config.General.transferOutputs = True
config.General.transferLogs=True
config.General.failureLimit=1

config.section_("JobType")
config.JobType.pluginName = 'Analysis'
config.JobType.psetName = '/cvmfs/cms.cern.ch/slc6_amd64_gcc530/cms/cmssw/CMSSW_8_0_10/src/PhysicsTools/Utilities/configuration/copyPickMerge_cfg.py'
config.JobType.pyCfgParams = ['eventsToProcess_load=pickevents_runEvents.txt', 'outputFile=pickevents_OUTFILENAME.root']

config.section_("Data")
config.Data.inputDBS = 'https://cmsweb.cern.ch/dbs/prod/global/DBSReader/'
config.Data.inputDataset = 'DATASETNAME'
config.Data.splitting = 'LumiBased'
config.Data.unitsPerJob = 5
config.Data.lumiMask = 'pickevents.json'
config.Data.publication = False
config.Data.outLFNDirBase = '/store/user/%s/UFHZZAnalysisRun2/pickEvents_JOBTAG/' % (getUsernameFromSiteDB())
config.Data.ignoreLocality = True
config.Data.allowNonValidInputDataset = True


config.section_('Site')
config.Site.storageSite = 'T2_US_Florida'
config.Site.whitelist = ['T2_US_*']
