# to run: source /cvmfs/cms.cern.ch/common/crab-setup.sh
# python3 submit_MC_RUND.py --version run3_DD_MM_YY --samples datasetsMCSummer23BPix.txt
import os
import subprocess
import argparse


# this will use CRAB client API
from CRABAPI.RawCommand import crabCommand
from WMCore.Configuration import Configuration
from CRABClient.UserUtilities import config
from CRABClient.ClientUtilities import getUsernameFromCRIC

parser = argparse.ArgumentParser()

parser.add_argument(
    "--samples",
    "-s",
    type=str,
    required=True,
    help="input txt file containing the sample names (one line each)",
)

parser.add_argument("--version", type=str, required=True, help="version tag")

parser.add_argument(
    "--dry", action="store_true", help="only generate configs, don't submit the jobs"
)


args = parser.parse_args()
print(args)

tag = os.path.splitext(os.path.basename(args.samples))[0]

# Configuration

config = Configuration()

config.section_("General")
config.General.workArea = "crab_" + tag
config.General.transferOutputs = True
config.General.transferLogs = True

config.section_("JobType")
config.JobType.pluginName = "Analysis"
config.JobType.psetName = "../templateMC_2023D_corrected.py"
config.JobType.numCores = 2
basepath = os.getenv('CMSSW_BASE')+'/src/Hcc/HccAna'
config.JobType.inputFiles = [basepath+'/data/Summer23BPixPrompt23_V1_MC.db', basepath+'/data/Summer23BPixPrompt23_V1_MC_UncertaintySources_AK4PFPuppi.txt']
# config.JobType.sendExternalFolder = True


config.section_("Data")
config.Data.inputDBS = "global"
config.Data.splitting = 'LumiBased'
config.Data.unitsPerJob = 25
config.Data.publication = True
##config.Data.totalUnits = 2
config.Data.outputDatasetTag = f"{tag}_{args.version}"
config.Data.allowNonValidInputDataset = False
# config.Data.lumiMask = ''
config.section_("Site")
config.Site.storageSite = "T2_IT_Bari"
#config.Site.blacklist = ['T1_US_FNAL'] 


config.section_("User")
# config.User.voGroup = "dcms"


os.makedirs(f"crab_{tag}", exist_ok=True)
with open(args.samples, "r") as samplefile:
    for sample in samplefile:
        sample = sample.strip()

        if not "#" in sample and len(sample.split("/")) == 4:
            requestName = sample.split("/")[1]

            if "ext" in sample:
                requestName += "_ext"
                requestName += sample.split("ext")[-1].split("/")[0]

            print(requestName)

            config.General.requestName = requestName
            config.Data.inputDataset = sample

            # save config
            with open(f"crab_{tag}/{requestName}.py", "w") as f:
                f.write(str(config))

            if not args.dry:
                logpath = f"crab_{tag}/crab_{requestName}"
                if os.path.isdir(logpath):
                    print(f'Already submitted (see "{logpath}"). Skipping!')
                else:
                    print(f"submitting {requestName} ...")

                    result = crabCommand("submit", config=config)
                    print(result)

