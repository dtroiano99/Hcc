import FWCore.ParameterSet.Config as cms

process = cms.Process("OWNPARTICLES")

process.load("FWCore.MessageService.MessageLogger_cfi")

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(100) )

process.source = cms.Source("PoolSource",
    # replace 'myfile.root' with the source file you want to use
    fileNames = cms.untracked.vstring(
        'file:3295EF7C-2070-E411-89C4-7845C4FC35DB.root'
    )
)


process.mvaNonTrigV025nsPHYS14 = cms.EDProducer("SkimmedElectronMvaIDProducer",
                                     electronsCollection = cms.InputTag("slimmedElectrons","","PAT"),
                                     method = cms.string("BDTSimpleCat"),
                                     mvaWeightFile = cms.vstring(
                                                                 "EgammaAnalysis/ElectronTools/data/PHYS14/EIDmva_EB1_5_oldscenario2phys14_BDT.weights.xml",
                                                                 "EgammaAnalysis/ElectronTools/data/PHYS14/EIDmva_EB2_5_oldscenario2phys14_BDT.weights.xml",
                                                                 "EgammaAnalysis/ElectronTools/data/PHYS14/EIDmva_EE_5_oldscenario2phys14_BDT.weights.xml",
                                                                 "EgammaAnalysis/ElectronTools/data/PHYS14/EIDmva_EB1_10_oldscenario2phys14_BDT.weights.xml",
                                                                 "EgammaAnalysis/ElectronTools/data/PHYS14/EIDmva_EB2_10_oldscenario2phys14_BDT.weights.xml",
                                                                 "EgammaAnalysis/ElectronTools/data/PHYS14/EIDmva_EE_10_oldscenario2phys14_BDT.weights.xml",
                                                                 ),
                                     Trig = cms.bool(False),
                                     )

process.out = cms.OutputModule("PoolOutputModule",
    fileName = cms.untracked.string('myOutputFile.root'),
    outputCommands = cms.untracked.vstring(
      "keep * ",
      "keep *_mvaNonTrigV025nsPHYS14_*_*",
    )
)

  
process.p = cms.Path(process.mvaNonTrigV025nsPHYS14)

process.e = cms.EndPath(process.out)
