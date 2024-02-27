import FWCore.ParameterSet.Config as cms

from FWCore.ParameterSet.VarParsing import VarParsing

process = cms.Process("HccAnalysis")

process.load("FWCore.MessageService.MessageLogger_cfi")
process.MessageLogger.cerr.FwkReport.reportEvery = 1000
#process.MessageLogger.categories.append('HccAna')

process.load("Configuration.StandardSequences.MagneticField_cff")
process.load("Configuration.Geometry.GeometryRecoDB_cff")
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')
process.load('Configuration.StandardSequences.Services_cff')
process.GlobalTag.globaltag='130X_mcRun3_2022_realistic_v5' #MC2022v4

#from Configuration.AlCa.GlobalTag import GlobalTag
#process.GlobalTag = GlobalTag(process.GlobalTag, '130X_mcRun3_2022_realistic_v5','')

process.Timing = cms.Service("Timing",
                             summaryOnly = cms.untracked.bool(True)
                             )


process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )

process.options = cms.untracked.PSet(
        numberOfThreads = cms.untracked.uint32(1),
				#SkipEvent = cms.untracked.vstring('ProductNotFound')
)

process.options.numberOfConcurrentLuminosityBlocks = 1
'''
process.load("SimGeneral.HepPDTESSource.pythiapdt_cfi")
process.printTree = cms.EDAnalyzer("ParticleListDrawer",
  maxEventsToPrint = cms.untracked.int32(1),
  printVertex = cms.untracked.bool(False),
  printOnlyHardInteraction = cms.untracked.bool(False), # Print only status=3 particles. This will not work for Pythia8, which does not have any such particles.
  src = cms.InputTag("genParticles")
)
'''

myfilelist = cms.untracked.vstring(
'/store/mc/Run3Summer22MiniAODv4/Zto2Q-4Jets_HT-800_TuneCP5_13p6TeV_madgraphMLM-pythia8/MINIAODSIM/130X_mcRun3_2022_realistic_v5-v2/2530000/048ed41a-cbb0-4b6d-afe1-12f5da3650c7.root',
)

process.source = cms.Source("PoolSource",fileNames = myfilelist,
           #                 duplicateCheckMode = cms.untracked.string('noDuplicateCheck'),
           #eventsToProcess = cms.untracked.VEventRange('1:12:66017')
                            )

process.TFileService = cms.Service("TFileService",
                                   #fileName = cms.string("prova.root")
                                   fileName = cms.string("ZToQQ_2022_CD.root")
)

# clean muons by segments 
process.boostedMuons = cms.EDProducer("PATMuonCleanerBySegments",
				     src = cms.InputTag("slimmedMuons"),
				     preselection = cms.string("track.isNonnull"),
				     passthrough = cms.string("isGlobalMuon && numberOfMatches >= 2"),
				     fractionOfSharedSegments = cms.double(0.499),
				     )


# Kalman Muon Calibrations
process.calibratedMuons = cms.EDProducer("KalmanMuonCalibrationsProducer",
                                         muonsCollection = cms.InputTag("boostedMuons"),
                                         isMC = cms.bool(True),
                                         isSync = cms.bool(True),
                                         useRochester = cms.untracked.bool(True),
                                         year = cms.untracked.int32(2018)
                                         )

#from EgammaAnalysis.ElectronTools.regressionWeights_cfi import regressionWeights
#process = regressionWeights(process)
#process.load('EgammaAnalysis.ElectronTools.regressionApplication_cff')

process.selectedElectrons = cms.EDFilter("PATElectronSelector",
                                         src = cms.InputTag("slimmedElectrons"),
                                         #cut = cms.string("pt > 5 && abs(eta)<2.5 && abs(-log(tan(superClusterPosition.theta/2)))<2.5")
                                         cut = cms.string("pt > 5 && abs(eta)<2.5 ")
                                         )

process.RandomNumberGeneratorService = cms.Service("RandomNumberGeneratorService",
    calibratedPatElectrons = cms.PSet(
        #initialSeed = cms.untracked.uint32(SEED), # for HPC
        initialSeed = cms.untracked.uint32(123456), # for crab
        engineName = cms.untracked.string('TRandom3')
    )
)

#process.load('EgammaAnalysis.ElectronTools.calibratedElectronsRun2_cfi')
#process.calibratedPatElectrons = cms.EDProducer("CalibratedPatElectronProducerRun2",
#                                        # input collections
#                                        #electrons = cms.InputTag('selectedElectrons'),
#                                        electrons = cms.InputTag('electronsMVA'),
#
#                                        gbrForestName = cms.vstring('electron_eb_ECALTRK_lowpt', 'electron_eb_ECALTRK',
#                                                                    'electron_ee_ECALTRK_lowpt', 'electron_ee_ECALTRK',
#                                                                    'electron_eb_ECALTRK_lowpt_var', 'electron_eb_ECALTRK_var',
#                                                                    'electron_ee_ECALTRK_lowpt_var', 'electron_ee_ECALTRK_var'),
#
#                                        isMC = cms.bool(True),
#                                        autoDataType = cms.bool(True),
#                                        isSynchronization = cms.bool(False),
#                                        #correctionFile = cms.string("EgammaAnalysis/ElectronTools/data/ScalesSmearings/Run2017_17Nov2017_v1_ele_unc"),
#                                        correctionFile = cms.string("EgammaAnalysis/ElectronTools/data/ScalesSmearings/Run2018_Step2Closure_CoarseEtaR9Gain_v2"),
#
#                                        recHitCollectionEB = cms.InputTag('reducedEgamma:reducedEBRecHits'),
#                                        recHitCollectionEE = cms.InputTag('reducedEgamma:reducedEERecHits')
#
#
#                                        )
'''
from RecoEgamma.EgammaTools.EgammaPostRecoTools import setupEgammaPostRecoSeq
setupEgammaPostRecoSeq(process,
                       runEnergyCorrections=True,
                       runVID=True,
                       eleIDModules=['RecoEgamma.ElectronIdentification.Identification.mvaElectronID_Summer18UL_ID_ISO_cff','RecoEgamma.ElectronIdentification.Identification.heepElectronID_HEEPV70_cff'],
                       phoIDModules=['RecoEgamma.PhotonIdentification.Identification.cutBasedPhotonID_Fall17_94X_V2_cff'],
                       era='2018-UL'
			)
'''
###############################################
#####   mva calcution before calibrated   #####
###############################################
'''
process.load("RecoEgamma.EgammaTools.calibratedEgammas_cff")
#process.calibratedPatElectrons.correctionFile = "EgammaAnalysis/ElectronTools/data/ScalesSmearings/Run2018_Step2Closure_CoarseEtaR9Gain"
process.calibratedPatElectrons.correctionFile = "EgammaAnalysis/ElectronTools/data/ScalesSmearings/Run2018_29Sep2020_RunFineEtaR9Gain"
#process.calibratedPatElectrons.src = cms.InputTag("selectedElectrons")
#process.calibratedPatElectrons.src = cms.InputTag("electronsMVA")
process.calibratedPatElectrons.src = cms.InputTag("slimmedElectrons")
'''
##  from PhysicsTools.SelectorUtils.tools.vid_id_tools import *
##  dataFormat = DataFormat.MiniAOD
##  switchOnVIDElectronIdProducer(process, dataFormat)
##  # define which IDs we want to produce
##  my_id_modules = [ 'RecoEgamma.ElectronIdentification.Identification.mvaElectronID_Autumn18_ID_ISO_cff','RecoEgamma.ElectronIdentification.Identification.heepElectronID_HEEPV70_cff' ]
##  # add them to the VID producer
##  for idmod in my_id_modules:
##      setupAllVIDIdsInModule(process,idmod,setupVIDElectronSelection)
##  #process.electronMVAValueMapProducer.srcMiniAOD = cms.InputTag("calibratedPatElectrons")
##  #process.egmGsfElectronIDs.physicsObjectSrc = cms.InputTag('slimmedElectrons')
##  #process.electronMVAVariableHelper.srcMiniAOD = cms.InputTag('slimmedElectrons')
##  #process.electronMVAValueMapProducer.srcMiniAOD = cms.InputTag("slimmedElectrons")
##  process.egmGsfElectronIDs.physicsObjectSrc = cms.InputTag('selectedElectrons')
##  process.electronMVAVariableHelper.srcMiniAOD = cms.InputTag('selectedElectrons')
##  process.electronMVAValueMapProducer.srcMiniAOD = cms.InputTag('selectedElectrons')
##  
##  process.electronsMVA = cms.EDProducer("SlimmedElectronMvaIDProducer",
##                                        mvaValuesMap = cms.InputTag("electronMVAValueMapProducer:ElectronMVAEstimatorRun2Autumn18IdIsoValues"),
##  #                                      electronsCollection = cms.InputTag("calibratedPatElectrons"),
##                                        #electronsCollection = cms.InputTag("slimmedElectrons"),
##                                        electronsCollection = cms.InputTag("selectedElectrons"),
##                                        idname = cms.string("ElectronMVAEstimatorRun2Autumn18IdIsoValues"),
##  )

# FSR Photons
process.load('Hcc.FSRPhotons.fsrPhotons_cff')

import os
# Jet Energy Corrections
#from CondCore.CondDB.CondDB_cfi  import *
from CondCore.DBCommon.CondDBSetup_cfi import *


# AK4 Puppi Jets JEC
process.jec_ak4 = cms.ESSource("PoolDBESSource",
                           CondDBSetup,
                           #for hpc
                           #connect = cms.string("sqlite_file:" +os.environ.get('CMSSW_BASE')+"/src/Hcc/HccAna/python/Summer22_22Sep2023_V2_MC.db"),
                           #for crab
                           connect = cms.string("sqlite_file:src/Hcc/HccAna/python/Summer22_22Sep2023_V2_MC.db"),
                           toGet =  cms.VPSet(
                              cms.PSet(
                                 record = cms.string("JetCorrectionsRecord"),
                                 tag = cms.string("JetCorrectorParametersCollection_Summer22_22Sep2023_V2_MC_AK4PFPuppi"),
                                 label= cms.untracked.string("AK4PFPuppi")
                              ),
              )
)

# AK8 Puppi Jets JEC
process.jec_ak8 = cms.ESSource("PoolDBESSource",
                               CondDBSetup,
                               #for hpc
                               #connect = cms.string("sqlite_file:" +os.environ.get('CMSSW_BASE')+"/src/Hcc/HccAna/python/Summer22_22Sep2023_V2_MC.db"),
                               #for crab
                               connect = cms.string("sqlite_file:src/Hcc/HccAna/python/Summer22_22Sep2023_V2_MC.db"),
                               toGet =  cms.VPSet(
                                  cms.PSet(
                                     record = cms.string("JetCorrectionsRecord"),
                                     tag = cms.string("JetCorrectorParametersCollection_Summer22_22Sep2023_V2_MC_AK8PFPuppi"),
                                     label= cms.untracked.string("AK8PFPuppi")
                                  ),
                  )
)

process.es_prefer_jec_ak4 = cms.ESPrefer('PoolDBESSource', 'jec_ak4')
process.es_prefer_jec_ak8 = cms.ESPrefer('PoolDBESSource', 'jec_ak8')

from PhysicsTools.PatAlgos.tools.jetTools import updateJetCollection

updateJetCollection(
   process,
   jetSource = cms.InputTag('slimmedJetsAK8'),
   labelName = 'UpdatedJECak8',
   jetCorrections = ('AK8PFPuppi', cms.vstring(['L1FastJet', 'L2Relative', 'L3Absolute', 'L2L3Residual']), 'None')  # Update: Safe to always add 'L2L3Residual' as MC contains dummy L2L3Residual corrections (always set to 1)
)

process.jecSequence_ak8 = cms.Sequence(process.patJetCorrFactorsUpdatedJECak8 * process.updatedPatJetsUpdatedJECak8)

updateJetCollection(
   process,
   jetSource = cms.InputTag('slimmedJetsPuppi'),
   labelName = 'UpdatedJECak4',
   jetCorrections = ('AK4PFPuppi', cms.vstring(['L1FastJet', 'L2Relative', 'L3Absolute', 'L2L3Residual']), 'None')  # Update: Safe to always add 'L2L3Residual' as MC contains dummy L2L3Residual corrections (always set to 1)
)

process.jecSequence_ak4 = cms.Sequence(process.patJetCorrFactorsUpdatedJECak4 * process.updatedPatJetsUpdatedJECak4)

updateJetCollection(
   process,
   jetSource = cms.InputTag('slimmedJetsAK8PFPuppiSoftDropPacked:SubJets'),
   labelName = 'UpdatedJECsubak4',
   jetCorrections = ('AK4PFPuppi', cms.vstring(['L1FastJet', 'L2Relative', 'L3Absolute', 'L2L3Residual']), 'None'),  # Update: Safe to always add 'L2L3Residual' as MC contains dummy L2L3Residual corrections (always set to 1)
   explicitJTA = False,          # needed for subjet b tagging
   svClustering = False,        # needed for subjet b tagging (IMPORTANT: Needs to be set to False to disable ghost-association which does not work with slimmed jets)
   fatJets = cms.InputTag('slimmedJetsAK8'), # needed for subjet b tagging
   rParam = 0.8,                # needed for subjet b tagging
   algo = 'ak'                  # has to be defined but is not used with svClustering=False
)

# the corrected jet collection is "updatedPatJetsUpdatedJECsubak4"

process.jecSequence_subak4 = cms.Sequence(process.patJetCorrFactorsUpdatedJECsubak4 * process.updatedPatJetsUpdatedJECsubak4)
'''
updateJetCollection(
   process,
   labelName = 'SoftDropSubjets',
   #jetSource = cms.InputTag('slimmedJetsAK8PFPuppiSoftDropPacked'),
   jetSource = cms.InputTag('slimmedJetsAK8PFPuppiSoftDropPacked:SubJets'),
   jetCorrections = ('AK4PFPuppi', cms.vstring(['L1FastJet', 'L2Relative', 'L3Absolute', 'L2L3Residual']), 'None'),
   algo = 'ak'                  # has to be defined but is not used with svClustering=False
)
#process.updatedPatJetsSoftDropSubjets.userData.userFloats.src = []
process.jecSoftDropSubjets = cms.Sequence(process.patJetCorrFactorsUpdatedJEC * process.updatedPatJetsSoftDropSubjets)
'''

## must be un-commented
#era = "Summer19UL18_V5_MC"
### for HPC
#dBFile = os.environ.get('CMSSW_BASE')+"/src/Hcc/HccAna/data/"+era+".db"
### for crab
#dBFile = "src/Hcc/HccAna/data/"+era+".db"
#process.jec = cms.ESSource("PoolDBESSource",
#                           CondDBSetup,
#                           connect = cms.string("sqlite_file:"+dBFile),
#                           toGet =  cms.VPSet(
#        cms.PSet(
#            record = cms.string("JetCorrectionsRecord"),
#            tag = cms.string("JetCorrectorParametersCollection_"+era+"_AK4PF"),
#            label= cms.untracked.string("AK4PF")
#            ),
#        cms.PSet(
#            record = cms.string("JetCorrectionsRecord"),
#            tag = cms.string("JetCorrectorParametersCollection_"+era+"_AK4PFchs"),
#            label= cms.untracked.string("AK4PFchs")
#            ),
#
#        cms.PSet(
#            record = cms.string("JetCorrectionsRecord"),
#            tag = cms.string("JetCorrectorParametersCollection_"+era+"_AK8PFchs"),
#            label= cms.untracked.string("AK8PFchs")
#            ),
#        )
#)
#process.es_prefer_jec = cms.ESPrefer("PoolDBESSource",'jec')


process.load("PhysicsTools.PatAlgos.producersLayer1.jetUpdater_cff")
'''
process.jetCorrFactors = process.updatedPatJetCorrFactors.clone(
    src = cms.InputTag("slimmedJets"),
    levels = ['L1FastJet', 
              'L2Relative', 
              'L3Absolute'],
    payload = 'AK4PFchs' ) 

process.AK8PFJetCorrFactors = process.updatedPatJetCorrFactors.clone(
    src = cms.InputTag("slimmedJetsAK8"),
    levels = ['L1FastJet',
              'L2Relative',
              'L3Absolute'],
    payload = 'AK8PFchs' )

process.slimmedJetsJEC = process.updatedPatJets.clone(
    jetSource = cms.InputTag("slimmedJets"),
    jetCorrFactorsSource = cms.VInputTag(cms.InputTag("jetCorrFactors"))
    )

process.slimmedJetsAK8JEC = process.updatedPatJets.clone(
    jetSource = cms.InputTag("slimmedJetsAK8"),
    jetCorrFactorsSource = cms.VInputTag(cms.InputTag("AK8PFJetCorrFactors"))
    )
'''
### add pileup id and discriminant to patJetsReapplyJEC
from RecoJets.JetProducers.PileupJetID_cfi import _chsalgos_106X_UL18
process.load("RecoJets.JetProducers.PileupJetID_cfi")
process.pileupJetIdUpdated = process.pileupJetId.clone(
    jets=cms.InputTag("slimmedJets"),
    inputIsCorrected=False,
    applyJec=True,
    vertexes=cms.InputTag("offlineSlimmedPrimaryVertices"),
    algos=cms.VPSet(_chsalgos_106X_UL18),

)
#process.slimmedJetsJEC.userData.userFloats.src += ['pileupJetIdUpdated:fullDiscriminant']
#process.slimmedJetsJEC.userData.userInts.src += ['pileupJetIdUpdated:fullId']

# JER   un-comment this pat
#process.load("JetMETCorrections.Modules.JetResolutionESProducer_cfi")
### for hpc
#dBJERFile = os.environ.get('CMSSW_BASE')+"/src/Hcc/HccAna/data/Summer19UL18_JRV2_MC.db"   
### for crab
#dBJERFile = "src/Hcc/HccAna/data/Summer19UL18_JRV2_MC.db"
#process.jer = cms.ESSource("PoolDBESSource",
#        CondDBSetup,
#        connect = cms.string("sqlite_file:"+dBJERFile),
#        toGet = cms.VPSet(
#            cms.PSet(
#                record = cms.string('JetResolutionRcd'),
#                tag    = cms.string('JR_Summer19UL18_JRV2_MC_PtResolution_AK4PFchs'),
#                label  = cms.untracked.string('AK4PFchs_pt')
#                ),
#            cms.PSet(
#                record = cms.string('JetResolutionRcd'),
#                tag    = cms.string('JR_Summer19UL18_JRV2_MC_PhiResolution_AK4PFchs'),
#                label  = cms.untracked.string('AK4PFchs_phi')
#                ),
#            cms.PSet(
#                record = cms.string('JetResolutionScaleFactorRcd'),
#                tag    = cms.string('JR_Summer19UL18_JRV2_MC_SF_AK4PFchs'),
#                label  = cms.untracked.string('AK4PFchs')
#                )
#            )
#        )
#process.es_prefer_jer = cms.ESPrefer('PoolDBESSource', 'jer')


#QGTag
process.load("CondCore.CondDB.CondDB_cfi")
qgDatabaseVersion = 'cmssw8020_v2'
# for hpc
QGdBFile = os.environ.get('CMSSW_BASE')+"/src/Hcc/HccAna/data/QGL_"+qgDatabaseVersion+".db"
# for crab
QGdBFile = "src/Hcc/HccAna/data/QGL_"+qgDatabaseVersion+".db"

process.QGPoolDBESSource = cms.ESSource("PoolDBESSource",
      DBParameters = cms.PSet(messageLevel = cms.untracked.int32(1)),
      timetype = cms.string('runnumber'),
      toGet = cms.VPSet(
        cms.PSet(
            record = cms.string('QGLikelihoodRcd'),
            tag    = cms.string('QGLikelihoodObject_'+qgDatabaseVersion+'_AK4PFchs'),
            label  = cms.untracked.string('QGL_AK4PFPuppi')
        ),
      ),
      connect = cms.string('sqlite_file:'+QGdBFile)
)

process.es_prefer_qg = cms.ESPrefer('PoolDBESSource','QGPoolDBESSource')
process.load('RecoJets.JetProducers.QGTagger_cfi')
#process.QGTagger.srcJets = cms.InputTag( 'slimmedJetsJEC' )
process.QGTagger.srcJets = cms.InputTag( 'slimmedJets' )
process.QGTagger.jetsLabel = cms.string('QGL_AK4PFPuppi')
process.QGTagger.srcVertexCollection=cms.InputTag("offlinePrimaryVertices")

# compute corrected pruned jet mass
#process.corrJets = cms.EDProducer ( "CorrJetsProducer",
#                                    jets    = cms.InputTag( "slimmedJetsAK8JEC" ),
#                                    vertex  = cms.InputTag( "offlineSlimmedPrimaryVertices" ), 
#                                    rho     = cms.InputTag( "fixedGridRhoFastjetAll"   ),
#                                    payload = cms.string  ( "AK8PFchs" ),
#                                    isData  = cms.bool    (  False ),
#                                    year = cms.untracked.int32(2018))


# Recompute MET
from PhysicsTools.PatUtils.tools.runMETCorrectionsAndUncertainties import runMetCorAndUncFromMiniAOD

runMetCorAndUncFromMiniAOD(process,
            isData=False,
            )
'''
from PhysicsTools.PatUtils.l1PrefiringWeightProducer_cfi import l1PrefiringWeightProducer
process.prefiringweight = l1PrefiringWeightProducer.clone(
#                TheJets = cms.InputTag("slimmedJetsJEC"), #this should be the slimmedJets collection with up to date JECs !
		TheJets = cms.InputTag("slimmedJets"), #this should be the slimmedJets collection with up to date JECs !
		DataEraECAL = cms.string("None"),
		DataEraMuon = cms.string("20172018"),
		UseJetEMPt = cms.bool(False),
		PrefiringRateSystematicUnctyECAL = cms.double(0.2),
		PrefiringRateSystematicUnctyMuon = cms.double(0.2)
)
'''
# STXS
process.load("SimGeneral.HepPDTESSource.pythiapdt_cfi")
process.mergedGenParticles = cms.EDProducer("MergedGenParticleProducer",
    inputPruned = cms.InputTag("prunedGenParticles"),
    inputPacked = cms.InputTag("packedGenParticles"),
)
process.myGenerator = cms.EDProducer("GenParticles2HepMCConverter",
    genParticles = cms.InputTag("mergedGenParticles"),
    genEventInfo = cms.InputTag("generator"),
    signalParticlePdgIds = cms.vint32(25)
)
process.rivetProducerHTXS = cms.EDProducer('HTXSRivetProducer',
  HepMCCollection = cms.InputTag('myGenerator','unsmeared'),
  LHERunInfo = cms.InputTag('externalLHEProducer'),
  ProductionMode = cms.string('AUTO'),
)
# HZZ Fiducial from RIVET
process.rivetProducerHZZFid = cms.EDProducer('HZZRivetProducer',
  HepMCCollection = cms.InputTag('myGenerator','unsmeared'),
)



# Analyzer
process.Ana = cms.EDAnalyzer('HccAna',
                              photonSrc    = cms.untracked.InputTag("slimmedPhotons"),
                              electronSrc  = cms.untracked.InputTag("slimmedElectrons"),
                              #electronUnSSrc  = cms.untracked.InputTag("electronsMVA"),
                              electronUnSSrc  = cms.untracked.InputTag("selectedElectrons"),
                              #electronUnSSrc  = cms.untracked.InputTag("slimmedElectrons"),
                              #electronSrc  = cms.untracked.InputTag("calibratedPatElectrons"),
                              muonSrc      = cms.untracked.InputTag("slimmedMuons"),
                              #muonSrc      = cms.untracked.InputTag("boostedMuons"),
                              tauSrc      = cms.untracked.InputTag("slimmedTaus"),
                              jetSrc       = cms.untracked.InputTag("slimmedJets"),
                              #AK4PuppiJetSrc       = cms.InputTag("slimmedJetsPuppi"),
                              AK4PuppiJetSrc       = cms.InputTag("updatedPatJetsUpdatedJECak4"),
			                  #AK8PuppiJetSrc       = cms.untracked.InputTag("slimmedJetsAK8"),
                              AK8PuppiJetSrc       = cms.untracked.InputTag("updatedPatJetsUpdatedJECak8"),
                              #AK8PFPuppiSoftDropPackedSrc = cms.untracked.InputTag("slimmedJetsAK8PFPuppiSoftDropPacked:SubJets")
                              AK8PFPuppiSoftDropPackedSrc       = cms.untracked.InputTag("updatedPatJetsUpdatedJECsubak4"),
                              #hltPFJetForBtagSrc  = cms.InputTag("hltPFJetForBtag", "", "HLT"),
                              hltAK4PFJetsCorrectedSrc  = cms.InputTag("hltAK4PFJetsCorrected", "", "HLT"),
                              #pfJetTagCollectionParticleNetprobcSrc = cms.InputTag("hltParticleNetONNXJetTags","probc","HLT"),
                              #pfJetTagCollectionParticleNetprobbSrc = cms.InputTag("hltParticleNetONNXJetTags","probb","HLT"),
                              #pfJetTagCollectionParticleNetprobudsSrc = cms.InputTag("hltParticleNetONNXJetTags","probuds","HLT"),
                              #pfJetTagCollectionParticleNetprobgSrc = cms.InputTag("hltParticleNetONNXJetTags","probg","HLT"),
                              #pfJetTagCollectionParticleNetprobtauhSrc = cms.InputTag("hltParticleNetONNXJetTags","probtauh","HLT"),
                              #jetSrc       = cms.untracked.InputTag("slimmedJets"),
                              #mergedjetSrc = cms.untracked.InputTag("corrJets"),
                              bxvCaloJetSrc =  cms.InputTag("caloStage2Digis","Jet"),
                              bxvCaloMuonSrc =  cms.InputTag("gmtStage2Digis","Muon"),
                              bxvCaloHTSrc =  cms.InputTag("caloStage2Digis","EtSum"),
                              mergedjetSrc = cms.untracked.InputTag("slimmedJets"),
                              metSrc       = cms.untracked.InputTag("slimmedMETs","","HccAnalysis"),
                              #metSrc       = cms.untracked.InputTag("slimmedMETs","","Hcc"),
                              #metSrc       = cms.untracked.InputTag("slimmedMETs"),
                              vertexSrc    = cms.untracked.InputTag("offlineSlimmedPrimaryVertices"),
                              beamSpotSrc  = cms.untracked.InputTag("offlineBeamSpot"),
                              conversionSrc  = cms.untracked.InputTag("reducedEgamma","reducedConversions"),
                              isMC         = cms.untracked.bool(True),
                              isHcc         = cms.untracked.bool(False),
                              isZqq         = cms.untracked.bool(True),
                              ispreEE         = cms.untracked.bool(True),
                              isBCDE         = cms.untracked.bool(True),
                              isZcc         = cms.untracked.bool(False),
                              isZbb         = cms.untracked.bool(False),
                              isSignal     = cms.untracked.bool(True),
                              mH           = cms.untracked.double(125.0),
                              CrossSection = cms.untracked.double(1),#DUMMYCROSSSECTION),
                              FilterEff    = cms.untracked.double(1),
                              weightEvents = cms.untracked.bool(True),
                              elRhoSrc     = cms.untracked.InputTag("fixedGridRhoFastjetAll"),
                              muRhoSrc     = cms.untracked.InputTag("fixedGridRhoFastjetAll"),
                              rhoSrcSUS    = cms.untracked.InputTag("fixedGridRhoFastjetCentralNeutral"),
                              pileupSrc     = cms.untracked.InputTag("slimmedAddPileupInfo"),
                              pfCandsSrc   = cms.untracked.InputTag("packedPFCandidates"),
                              fsrPhotonsSrc = cms.untracked.InputTag("boostedFsrPhotons"),
                              prunedgenParticlesSrc = cms.untracked.InputTag("prunedGenParticles"),
                              packedgenParticlesSrc = cms.untracked.InputTag("packedGenParticles"),
                              genJetsSrc = cms.untracked.InputTag("slimmedGenJets"),
                              generatorSrc = cms.untracked.InputTag("generator"),
                              lheInfoSrc = cms.untracked.InputTag("externalLHEProducer"),
                              reweightForPU = cms.untracked.bool(True),
                              triggerSrc = cms.InputTag("TriggerResults","","HLT"),
                              triggerObjects = cms.InputTag("selectedPatTrigger"),
                              doJER = cms.untracked.bool(True),
                              doJEC = cms.untracked.bool(True),
                              algInputTag = cms.InputTag("gtStage2Digis"),
                              doTriggerMatching = cms.untracked.bool(False),
                              triggerList = cms.untracked.vstring(
				#VBFHToCC
				'HLT_QuadPFJet70_50_45_35_PFBTagParticleNet_2BTagSum0p65_v',
				'HLT_PFJet500_v',
                                  # Toni
                                  #'HLT_Ele32_WPTight_Gsf_v#', 
                                  #'HLT_IsoMu24_v#',
                                  #'HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_v#',
                                  #'HLT_DoubleEle25_CaloIdL_MW_v#',
                                  #'HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass3p8_v#',
                                  #'HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_v#',
                                  #'HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ_v#',
                                  #'HLT_Mu12_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ_v#',
                                  #'HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v#',
                                  #'HLT_DiMu9_Ele9_CaloIdL_TrackIdL_DZ_v#',
                                  #'HLT_TripleMu_10_5_5_DZ_v#',             
                                  #'HLT_TripleMu_12_10_5_v#',               
                                  #'HLT_Mu8_DiEle12_CaloIdL_TrackIdL_v#',   
                                  #'HLT_Mu8_DiEle12_CaloIdL_TrackIdL_DZ_v#',
                                  # OLD
                                  #'HLT_Ele32_WPTight_Gsf_v#',
                                  #'HLT_IsoMu24_v#',
                                  #'HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_v#',
                                  #'HLT_DoubleEle25_CaloIdL_MW_v#',
                                  #'HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass3p8_v#',
                                  #'HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass8_v#',
                                  #'HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_v#',
                                  #'HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ_v#',
                                  #'HLT_Mu12_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ_v#',
                                  #'HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v#',
                                  #'HLT_DiMu9_Ele9_CaloIdL_TrackIdL_DZ_v#',
                                  #'HLT_Ele16_Ele12_Ele8_CaloIdL_TrackIdL_v#',
                                  #'HLT_TripleMu_10_5_5_DZ_v#',
                                  #'HLT_TripleMu_12_10_5_v#',
                              ),
                              verbose = cms.untracked.bool(False),              
                              skimLooseLeptons = cms.untracked.int32(0),              
                              skimTightLeptons = cms.untracked.int32(0),              
                              #bestCandMela = cms.untracked.bool(False),
                              year = cms.untracked.int32(2018),####for year put 2016,2017, or 2018 to select correct setting
                              isCode4l = cms.untracked.bool(True),
                              payload = cms.string("AK4PFPuppi"),
                              #for hpc
                              #uncertainty_source_path_src = cms.untracked.string(os.environ.get('CMSSW_BASE')+"/src/Hcc/HccAna/data/Summer22_22Sep2023_V2_MC_UncertaintySources_AK4PFPuppi.txt"),
                              #for crab
                              uncertainty_source_path_src = cms.untracked.string("src/Hcc/HccAna/data/Summer22_22Sep2023_V2_MC_UncertaintySources_AK4PFPuppi.txt"),
                             )


process.p = cms.Path(#process.fsrPhotonSequence*
                     #process.boostedMuons*
                     #process.calibratedMuons*
                     #process.regressionApplication*
                     #process.selectedElectrons*
                     #process.calibratedPatElectrons*
                     #process.egmGsfElectronIDSequence*
                     #process.electronMVAValueMapProducer*
                     #process.electronsMVA*
                     #process.egmPhotonIDSequence*
                     #process.egammaPostRecoSeq*
 	             #process.calibratedPatElectrons*
                     process.jecSequence_subak4*
                     process.jecSequence_ak4*
                     process.jecSequence_ak8*
                     #process.jecSoftDropSubjets*
                     #process.jetCorrFactors*
                     process.pileupJetIdUpdated*
                     #process.slimmedJetsJEC*
                     process.QGTagger*
                     #process.AK8PFJetCorrFactors*
                     #process.slimmedJetsAK8JEC*
                     #process.fullPatMetSequence*
                     #process.corrJets*
                     process.mergedGenParticles*process.myGenerator*process.rivetProducerHTXS*#process.rivetProducerHZZFid*
		     #process.prefiringweight *
                     #process.printTree*
                     process.Ana
                     )

