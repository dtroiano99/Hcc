import FWCore.ParameterSet.Config as cms

from FWCore.ParameterSet.VarParsing import VarParsing

process = cms.Process("HccAnalysis")

process.load("FWCore.MessageService.MessageLogger_cfi")
process.MessageLogger.cerr.threshold = 'DEBUG'
process.MessageLogger.cerr.FwkReport.reportEvery = 1000
#process.MessageLogger.categories.append('HccAna')

process.load("Configuration.StandardSequences.MagneticField_cff")
process.load("Configuration.Geometry.GeometryRecoDB_cff")
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')
process.load('Configuration.StandardSequences.Services_cff')
process.GlobalTag.globaltag='130X_dataRun3_Prompt_HcalSiPM_v1'

process.Timing = cms.Service("Timing",
                             summaryOnly = cms.untracked.bool(True)
                             )


process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )

process.options = cms.untracked.PSet(
        numberOfThreads = cms.untracked.uint32(2),
                #SkipEvent = cms.untracked.vstring('ProductNotFound')
)

process.options.numberOfConcurrentLuminosityBlocks = 1

myfilelist = cms.untracked.vstring(
'/store/data/Run2023C/JetMET0/MINIAOD/19Dec2023-v1/2540000/6e592b85-b54c-4833-bff2-8b8b72afc412.root',
)

process.source = cms.Source("PoolSource",fileNames = myfilelist,
                            duplicateCheckMode = cms.untracked.string('noDuplicateCheck'),
                            )

process.TFileService = cms.Service("TFileService",
                                   fileName = cms.string("Data_2023Cv4.root")
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
                                         isMC = cms.bool(False),
                                         isSync = cms.bool(False),  
                                         year = cms.untracked.int32(2018)
                                         )

#from EgammaAnalysis.ElectronTools.regressionWeights_cfi import regressionWeights
#process = regressionWeights(process)
#process.load('EgammaAnalysis.ElectronTools.regressionApplication_cff')

process.selectedElectrons = cms.EDFilter("PATElectronSelector",
                                         #src = cms.InputTag("slimmedElectrons"),
                                         src = cms.InputTag("electronsMVA"),
                                         cut = cms.string("pt > 5 && abs(eta)<2.5 && abs(-log(tan(superClusterPosition.theta/2)))<2.5")
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
#                                        electrons = cms.InputTag('selectedElectrons'),
#
#                                        gbrForestName = cms.vstring('electron_eb_ECALTRK_lowpt', 'electron_eb_ECALTRK',
#                                                                    'electron_ee_ECALTRK_lowpt', 'electron_ee_ECALTRK',
#                                                                    'electron_eb_ECALTRK_lowpt_var', 'electron_eb_ECALTRK_var',
#                                                                    'electron_ee_ECALTRK_lowpt_var', 'electron_ee_ECALTRK_var'),
#
#                                        isMC = cms.bool(False),
#                                        autoDataType = cms.bool(True),
#                                        isSynchronization = cms.bool(False),
#                                        correctionFile = cms.string("EgammaAnalysis/ElectronTools/data/ScalesSmearings/Run2017_17Nov2017_v1_ele_unc"),
#
#                                        recHitCollectionEB = cms.InputTag('reducedEgamma:reducedEBRecHits'),
#                                        recHitCollectionEE = cms.InputTag('reducedEgamma:reducedEERecHits')
#
#
#                                        )
#
from PhysicsTools.SelectorUtils.tools.vid_id_tools import *
dataFormat = DataFormat.MiniAOD
switchOnVIDElectronIdProducer(process, dataFormat)
# define which IDs we want to produce
my_id_modules = [ 'RecoEgamma.ElectronIdentification.Identification.mvaElectronID_Fall17_iso_V2_cff' ]
# add them to the VID producer
for idmod in my_id_modules:
    setupAllVIDIdsInModule(process,idmod,setupVIDElectronSelection)
#process.electronMVAValueMapProducer.srcMiniAOD = cms.InputTag("calibratedPatElectrons")
#process.electronMVAValueMapProducer.srcMiniAOD = cms.InputTag("slimmedElectrons")

process.electronsMVA = cms.EDProducer("SlimmedElectronMvaIDProducer",
                                      mvaValuesMap = cms.InputTag("electronMVAValueMapProducer:ElectronMVAEstimatorRun2Fall17IsoV2Values"),
                                      #electronsCollection = cms.InputTag("calibratedPatElectrons"),
                                      #electronsCollection = cms.InputTag("selectedElectrons"),
                                      electronsCollection =  cms.InputTag("slimmedElectrons"),
                                      idname = cms.string("ElectronMVAEstimatorRun2Fall17IsoV2Values"),
)

# FSR Photons
process.load('Hcc.FSRPhotons.fsrPhotons_cff')

import os
# Jet Energy Corrections
#from CondCore.DBCommon.CondDBSetup_cfi import *
from CondCore.CondDB.CondDB_cfi  import *

# AK4 Puppi Jets JEC
process.jec_ak4 = cms.ESSource("PoolDBESSource",
                           #for hpc
                           #CondDB.clone(connect = cms.string("sqlite_file:" +os.environ.get('CMSSW_BASE')+"/src/Hcc/HccAna/data/Summer23Prompt23_RunCv4_V1_DATA.db")),
                           #for crab
                           CondDB.clone(connect = cms.string("sqlite_file:Summer23Prompt23_RunCv4_V1_DATA.db")),
                           toGet =  cms.VPSet(
                              cms.PSet(
                                 record = cms.string("JetCorrectionsRecord"),
                                 tag = cms.string("JetCorrectorParametersCollection_Summer23Prompt23_RunCv4_V1_DATA_AK4PFPuppi"),
                                 label= cms.untracked.string("AK4PFPuppi")
                              ),
              )
)

# AK8 Puppi Jets JEC
process.jec_ak8 = cms.ESSource("PoolDBESSource",
                               #for hpc
                               #CondDB.clone(connect = cms.string("sqlite_file:" +os.environ.get('CMSSW_BASE')+"/src/Hcc/HccAna/data/Summer23Prompt23_RunCv4_V1_DATA.db")),
                               #for crab
                               CondDB.clone(connect = cms.string("sqlite_file:Summer23Prompt23_RunCv4_V1_DATA.db")),
                               toGet =  cms.VPSet(
                                  cms.PSet(
                                     record = cms.string("JetCorrectionsRecord"),
                                     tag = cms.string("JetCorrectorParametersCollection_Summer23Prompt23_RunCv4_V1_DATA_AK8PFPuppi"),
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
# la collezione di jet con le correzioni applicate si chiama "updatedPatJetsUpdatedJEC"

#process.jecSequence = cms.Sequence(process.patJetCorrFactorsUpdatedJEC * process.updatedPatJetsUpdatedJEC)
process.jecSequence_subak4 = cms.Sequence(process.patJetCorrFactorsUpdatedJECsubak4 * process.updatedPatJetsUpdatedJECsubak4)

#from CondCore.CondDB.CondDB_cfi import *
era = "Fall17_17Nov2017BCDEF_V6_DATA"
# for HPC
#dBFile = os.environ.get('CMSSW_BASE')+"/src/Hcc/HccAna/data/"+era+".db"
# for crab
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
              'L3Absolute',
              'L2L3Residual'],
    payload = 'AK4PFchs' ) 

process.AK8PFJetCorrFactors = process.updatedPatJetCorrFactors.clone(
    src = cms.InputTag("slimmedJetsAK8"),
    levels = ['L1FastJet',
              'L2Relative',
              'L3Absolute',
              'L2L3Residual'],
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
# JER
#process.load("JetMETCorrections.Modules.JetResolutionESProducer_cfi")
## for hpc
#dBJERFile = os.environ.get('CMSSW_BASE')+"/src/Hcc/HccAna/data/Summer15_25nsV6_MC_JER.db"
## for crab
#dBFile = "src/Hcc/HccAna/data/Summer15_25nsV6_MC_JER.db"
#process.jer = cms.ESSource("PoolDBESSource",
#        CondDBSetup,
#        connect = cms.string("sqlite_file:"+dBJERFile),
#        toGet = cms.VPSet(
#            cms.PSet(
#                record = cms.string('JetResolutionRcd'),
#                tag    = cms.string('JR_Summer15_25nsV6_MC_PtResolution_AK4PFchs'),
#                label  = cms.untracked.string('AK4PFchs_pt')
#                ),
#            cms.PSet(
#                record = cms.string('JetResolutionRcd'),
#                tag    = cms.string('JR_Summer15_25nsV6_MC_PhiResolution_AK4PFchs'),
#                label  = cms.untracked.string('AK4PFchs_phi')
#                ),
#            cms.PSet(
#                record = cms.string('JetResolutionScaleFactorRcd'),
#                tag    = cms.string('JR_Summer15_25nsV6_DATA_SF_AK4PFchs'),
#                label  = cms.untracked.string('AK4PFchs')
#                )
#            )
#        )
#process.es_prefer_jer = cms.ESPrefer('PoolDBESSource', 'jer')


#QGTag
process.load("CondCore.CondDB.CondDB_cfi")
qgDatabaseVersion = 'cmssw8020_v2'
# for hpc
#QGdBFile = os.environ.get('CMSSW_BASE')+"/src/Hcc/HccAna/data/QGL_"+qgDatabaseVersion+".db"
# for crab
#QGdBFile = "src/Hcc/HccAna/data/QGL_"+qgDatabaseVersion+".db"
'''
process.QGPoolDBESSource = cms.ESSource("PoolDBESSource",
      DBParameters = cms.PSet(messageLevel = cms.untracked.int32(1)),
      timetype = cms.string('runnumber'),
      toGet = cms.VPSet(
        cms.PSet(
            record = cms.string('QGLikelihoodRcd'),
            tag    = cms.string('QGLikelihoodObject_'+qgDatabaseVersion+'_AK4PFchs'),
            label  = cms.untracked.string('QGL_AK4PFchs')
        ),
      ),
      connect = cms.string('sqlite_file:'+QGdBFile)
)
'''
#process.es_prefer_qg = cms.ESPrefer('PoolDBESSource','QGPoolDBESSource')
process.load('RecoJets.JetProducers.QGTagger_cfi')
process.QGTagger.srcJets = cms.InputTag( 'slimmedJets' )
process.QGTagger.jetsLabel = cms.string('QGL_AK4PFchs')
process.QGTagger.srcVertexCollection=cms.InputTag("offlinePrimaryVertices")

# compute corrected pruned jet mass
process.corrJets = cms.EDProducer ( "CorrJetsProducer",
                                    jets    = cms.InputTag( "slimmedJetsAK8JEC" ),
                                    vertex  = cms.InputTag( "offlineSlimmedPrimaryVertices" ), 
                                    rho     = cms.InputTag( "fixedGridRhoFastjetAll"   ),
                                    payload = cms.string  ( "AK8PFchs" ),
                                    isData  = cms.bool    (  True ))


# Recompute MET
from PhysicsTools.PatUtils.tools.runMETCorrectionsAndUncertainties import runMetCorAndUncFromMiniAOD

runMetCorAndUncFromMiniAOD(process,
            isData=True,
            )

## STXS
#process.load("SimGeneral.HepPDTESSource.pythiapdt_cfi")
#process.mergedGenParticles = cms.EDProducer("MergedGenParticleProducer",
#    inputPruned = cms.InputTag("prunedGenParticles"),
#    inputPacked = cms.InputTag("packedGenParticles"),
#)
#process.myGenerator = cms.EDProducer("GenParticles2HepMCConverter",
#    genParticles = cms.InputTag("mergedGenParticles"),
#    genEventInfo = cms.InputTag("generator"),
#    signalParticlePdgIds = cms.vint32(25)
#)
#process.rivetProducerHTXS = cms.EDProducer('HTXSRivetProducer',
#  HepMCCollection = cms.InputTag('myGenerator','unsmeared'),
#  LHERunInfo = cms.InputTag('externalLHEProducer'),
#  ProductionMode = cms.string('AUTO'),
#)
## HZZ Fiducial from RIVET
#process.rivetProducerHZZFid = cms.EDProducer('HZZRivetProducer',
#  HepMCCollection = cms.InputTag('myGenerator','unsmeared'),
#)



# Analyzer
process.Ana = cms.EDAnalyzer('HccAna',
                              photonSrc    = cms.untracked.InputTag("slimmedPhotons"),
                              electronSrc  = cms.untracked.InputTag("slimmedElectrons"),
                              electronUnSSrc  = cms.untracked.InputTag("selectedElectrons"),
                              muonSrc      = cms.untracked.InputTag("slimmedMuons"),
                              #muonSrc      = cms.untracked.InputTag("boostedMuons"),
                              tauSrc      = cms.untracked.InputTag("slimmedTaus"),
                              jetSrc       = cms.untracked.InputTag("slimmedJets"),
                              #AK4PuppiJetSrc       = cms.InputTag("slimmedJetsPuppi"),
                              AK4PuppiJetSrc       = cms.InputTag("updatedPatJetsUpdatedJECak4"),
                              #AK8PuppiJetSrc       = cms.untracked.InputTag("slimmedJetsAK8"),
                              AK8PuppiJetSrc       = cms.untracked.InputTag("updatedPatJetsUpdatedJECak8"),
                              #AK8PFPuppiSoftDropPackedSrc = cms.untracked.InputTag("slimmedJetsAK8PFPuppiSoftDropPacked:SubJets"),
                              AK8PFPuppiSoftDropPackedSrc       = cms.untracked.InputTag("updatedPatJetsUpdatedJECsubak4"),
                              hltAK4PFJetsCorrectedSrc  = cms.InputTag("hltAK4PFJetsCorrected", "", "HLT"),
                              bxvCaloJetSrc =  cms.InputTag("caloStage2Digis","Jet"),
                              bxvCaloMuonSrc =  cms.InputTag("gmtStage2Digis","Muon"),
                              bxvCaloHTSrc =  cms.InputTag("caloStage2Digis","EtSum"),
                              mergedjetSrc = cms.untracked.InputTag("slimmedJets"),
                              metSrc       = cms.untracked.InputTag("slimmedMETs","","HccAnalysis"),
                              vertexSrc    = cms.untracked.InputTag("offlineSlimmedPrimaryVertices"),
                              beamSpotSrc  = cms.untracked.InputTag("offlineBeamSpot"),
                              conversionSrc  = cms.untracked.InputTag("reducedEgamma","reducedConversions"),
                              isMC         = cms.untracked.bool(False),
                              isHcc         = cms.untracked.bool(False),
                              isZcc         = cms.untracked.bool(False),
                              isZbb         = cms.untracked.bool(False),
                              isZqq         = cms.untracked.bool(False),
                              isC         = cms.untracked.bool(True),
                              isSignal     = cms.untracked.bool(False),
                              mH           = cms.untracked.double(125.0),
                              CrossSection = cms.untracked.double(1.0),
                              FilterEff    = cms.untracked.double(1),
                              weightEvents = cms.untracked.bool(False),
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
                              reweightForPU = cms.untracked.bool(False),
                              triggerSrc = cms.InputTag("TriggerResults","","HLT"),
                              triggerObjects = cms.InputTag("slimmedPatTrigger"),
                              doJER = cms.untracked.bool(True),
                              doJEC = cms.untracked.bool(True),
                              algInputTag = cms.InputTag("gtStage2Digis"),
                              doTriggerMatching = cms.untracked.bool(True),
                              triggerList = cms.untracked.vstring(
                                  #AK8 for Zqq
                                  'HLT_PFHT1050_v',
                                  'HLT_PFJet450_v',
                                  'HLT_AK8PFJet450_v',
                                  'HLT_AK8PFJet425_SoftDropMass40_v',
                              ),
                              skimLooseLeptons = cms.untracked.int32(4),              
                              skimTightLeptons = cms.untracked.int32(4),              
                              doMela = cms.untracked.bool(False),
                              payload = cms.string("AK4PFchs"),
                              #verbose = cms.untracked.bool(True)              
                             )

process.p = cms.Path(#process.fsrPhotonSequence*
                     #process.boostedMuons*
                     #process.calibratedMuons*
                     #process.regressionApplication*
                     #process.calibratedPatElectrons*
                     #process.electronMVAValueMapProducer*
                     #process.egmGsfElectronIDSequence*
                     #process.electronsMVA*
                     #process.selectedElectrons*
                     #process.jetCorrFactors*
                     #process.slimmedJetsJEC*
                     #process.jecSequence*
                     process.jecSequence_subak4*
                     process.jecSequence_ak4*
                     process.jecSequence_ak8*
                     #process.QGTagger*
                     #process.AK8PFJetCorrFactors*
                     #process.slimmedJetsAK8JEC*
                     #process.fullPatMetSequence*
                     #process.corrJets*
                     #process.mergedGenParticles*process.myGenerator*process.rivetProducerHTXS*#process.rivetProducerHZZFid*
                     process.Ana
                     )
