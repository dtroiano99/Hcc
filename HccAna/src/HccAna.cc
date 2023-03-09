// -*- C++ -*-
//
// Package:    HccAna
// Class:      HccAna
// 
///

// system include files
#include <memory>
#include <string>
#include <map>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <algorithm>
#include <stdlib.h>
#include <stdio.h>
#include <cmath>
#include <iomanip>
#include <set>

#define PI 3.14159

// user include files 
#include "TROOT.h"
#include "TH1.h"
#include "TH2.h"
#include "TTree.h"
#include "TSpline.h"
#include "TMath.h"
#include "TRandom3.h"
#include "TString.h"
#include "TLorentzVector.h"
#include "Math/VectorUtil.h"
#include "TClonesArray.h"
#include "TCanvas.h"

#include "FWCore/Framework/interface/Frameworkfwd.h"
//#include "FWCore/Framework/interface/limited/EDAnalyzerBase.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"
#include "FWCore/Framework/interface/LuminosityBlock.h"
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "FWCore/Utilities/interface/InputTag.h"
#include "DataFormats/Common/interface/MergeableCounter.h"
#include "DataFormats/Math/interface/Point3D.h"
#include "DataFormats/Common/interface/RefToBase.h"
#include "DataFormats/Math/interface/deltaR.h"
#include "DataFormats/Math/interface/deltaPhi.h"
#include "DataFormats/ParticleFlowCandidate/interface/PFCandidate.h"
#include "DataFormats/Common/interface/Association.h"
#include "DataFormats/Common/interface/ValueMap.h"
#include "DataFormats/HepMCCandidate/interface/GenParticle.h"
#include "DataFormats/PatCandidates/interface/PackedGenParticle.h"
#include "FWCore/Common/interface/TriggerNames.h"
#include "DataFormats/HLTReco/interface/TriggerObject.h"
#include "DataFormats/HLTReco/interface/TriggerEvent.h"
#include "DataFormats/Common/interface/TriggerResults.h"
#include "HLTrigger/HLTcore/interface/HLTConfigProvider.h"
#include "DataFormats/HLTReco/interface/TriggerEventWithRefs.h"
#include "SimDataFormats/GeneratorProducts/interface/GenEventInfoProduct.h"
#include "SimDataFormats/GeneratorProducts/interface/LHERunInfoProduct.h"
#include "SimDataFormats/GeneratorProducts/interface/LHEEventProduct.h"
#include "SimDataFormats/GeneratorProducts/interface/HepMCProduct.h"

//HTXS
#include "SimDataFormats/HTXS/interface/HiggsTemplateCrossSections.h"
//#include "SimDataFormats/HZZFiducial/interface/HZZFiducialVolume.h"

// PAT
#include "DataFormats/PatCandidates/interface/PFParticle.h"
#include "DataFormats/PatCandidates/interface/Electron.h"
#include "DataFormats/PatCandidates/interface/Photon.h"
#include "DataFormats/PatCandidates/interface/Muon.h"
#include "DataFormats/PatCandidates/interface/Tau.h"
#include "DataFormats/PatCandidates/interface/Jet.h"
#include "DataFormats/PatCandidates/interface/MET.h"
#include "DataFormats/PatCandidates/interface/TriggerEvent.h"
#include "DataFormats/Provenance/interface/Timestamp.h"
#include "DataFormats/Candidate/interface/Candidate.h"
#include "DataFormats/PatCandidates/interface/CompositeCandidate.h"
#include "DataFormats/ParticleFlowCandidate/interface/PFCandidateFwd.h"
#include "DataFormats/ParticleFlowCandidate/interface/PFCandidate.h"
#include "PhysicsTools/SelectorUtils/interface/JetIDSelectionFunctor.h"
#include "DataFormats/PatCandidates/interface/PackedCandidate.h"

//L1trigger
#include "DataFormats/L1GlobalTrigger/interface/L1GlobalTriggerReadoutRecord.h"
#include "DataFormats/L1TGlobal/interface/GlobalAlgBlk.h"
#include "DataFormats/L1TGlobal/interface/GlobalExtBlk.h"
#include "L1Trigger/L1TGlobal/interface/L1TGlobalUtil.h"
#include "CondFormats/DataRecord/interface/L1TUtmTriggerMenuRcd.h"
#include "CondFormats/L1TObjects/interface/L1TUtmTriggerMenu.h"
#include "CondFormats/L1TObjects/interface/L1GtTriggerMenu.h"
#include "CondFormats/DataRecord/interface/L1GtTriggerMenuRcd.h"

// Reco
#include "DataFormats/VertexReco/interface/Vertex.h"
#include "DataFormats/BeamSpot/interface/BeamSpot.h"
#include "DataFormats/MuonReco/interface/MuonSelectors.h"
#include "DataFormats/GsfTrackReco/interface/GsfTrack.h"
#include "DataFormats/TrackReco/interface/Track.h"
#include "DataFormats/EgammaReco/interface/SuperCluster.h"
#include "DataFormats/Common/interface/TriggerResults.h"
#include "DataFormats/HLTReco/interface/TriggerEvent.h"
#include "DataFormats/CaloTowers/interface/CaloTowerCollection.h"
#include "RecoVertex/VertexTools/interface/VertexDistance3D.h"

//Helper
#include "Hcc/HccAna/interface/HccHelper.h"
//Muons
#include "Hcc/HccAna/interface/HccMuonAna.h"
#include "Hcc/HccAna/interface/HccMuonTree.h"
//Electrons
#include "Hcc/HccAna/interface/HccElectronTree.h"
//Photons
#include "Hcc/HccAna/interface/HccPhotonTree.h"
//Jets
#include "Hcc/HccAna/interface/HccJetTree.h"
//Final Leps
#include "Hcc/HccAna/interface/HccFinalLepTree.h"
//Sip
#include "Hcc/HccAna/interface/HccSipAna.h"
//PU
#include "Hcc/HccAna/interface/HccPileUp.h"
#include "PhysicsTools/Utilities/interface/LumiReWeighting.h"
#include "SimDataFormats/PileupSummaryInfo/interface/PileupSummaryInfo.h"

//GEN
#include "Hcc/HccAna/interface/HccGENAna.h"
//VBF Jets
#include "Hcc/HccAna/interface/HccJets.h"

// Jet energy correction
#include "CondFormats/JetMETObjects/interface/JetCorrectorParameters.h"
#include "CondFormats/JetMETObjects/interface/JetCorrectionUncertainty.h"
#include "JetMETCorrections/Objects/interface/JetCorrectionsRecord.h"

#include <vector>

// Kinematic Fit
#include "RecoParticleFlow/PFClusterTools/interface/PFEnergyResolution.h"

// EWK corrections
#include "Hcc/HccAna/interface/EwkCorrections.h"

// JEC related
//#include "PhysicsTools/PatAlgos/plugins/PATJetUpdater.h"
#include "JetMETCorrections/JetCorrector/interface/JetCorrector.h"
 
//JER related
#include "JetMETCorrections/Modules/interface/JetResolution.h"
#include "DataFormats/PatCandidates/interface/Jet.h"

//BTag Calibration

#include "CondFormats/BTauObjects/interface/BTagCalibration.h"
#include "CondTools/BTau/interface/BTagCalibrationReader.h"

//Muon MVA
//#include "MuonMVAReader/Reader/interface/MuonGBRForestReader.hpp"

// KalmanVertexFitter  
#include "RecoVertex/KalmanVertexFit/interface/KalmanVertexFitter.h"
#include "RecoVertex/VertexTools/interface/InvariantMassFromVertex.h"
#include "TrackingTools/TransientTrack/interface/TransientTrackBuilder.h"
#include "TrackingTools/Records/interface/TransientTrackRecord.h"
#include "TrackingTools/TransientTrack/interface/TransientTrack.h"
// Rochester Corrections
//#include "Hcc/KalmanMuonCalibrationsProducer/src/RoccoR.cc"

#include "RecoVertex/KalmanVertexFit/interface/SingleTrackVertexConstraint.h"

//
// class declaration
//
using namespace EwkCorrections;

class HccAna : public edm::EDAnalyzer {
public:
    explicit HccAna(const edm::ParameterSet&);
    ~HccAna();
  
    static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);
    static bool sortByPt( const reco::GenParticle &p1, const reco::GenParticle &p2 ){ return (p1.pt() > p2.pt()); };
  
private:
    virtual void beginJob() ;
    virtual void analyze(const edm::Event&, const edm::EventSetup&);
    virtual void endJob() ;
  
    virtual void beginRun(edm::Run const&, const edm::EventSetup& iSetup);
    virtual void endRun(edm::Run const&, edm::EventSetup const&);
    virtual void beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&);
    virtual void endLuminosityBlock(edm::LuminosityBlock const& lumiSeg,edm::EventSetup const& eSetup);
  
    //Helper Class
    HccHelper helper;
    //GEN
    HccGENAna genAna;
    //VBF
    HccJets jetHelper;
    //PU Reweighting
    edm::LumiReWeighting *lumiWeight;
    HccPileUp pileUp;
    //JES Uncertainties
    std::unique_ptr<JetCorrectionUncertainty> jecunc;
    // kfactors
    TSpline3 *kFactor_ggzz;
    std::vector<std::vector<float> > tableEwk;
    // data/MC scale factors
    TH2F *hElecScaleFac;
    TH2F *hElecScaleFac_Cracks;
    TH2F *hElecScaleFacGsf;
    TH2F *hElecScaleFacGsfLowET;
    TH2F *hMuScaleFac;
    TH2F *hMuScaleFacUnc;
    TH1D *h_pileup;
    TH1D *h_pileupUp;
    TH1D *h_pileupDn;
    std::vector<TH1F*> h_medians;
    TH2F *hbTagEffi;
    TH2F *hcTagEffi;
    TH2F *hudsgTagEffi;

    BTagCalibrationReader* reader;

    //Saved Events Trees
    TTree *passedEventsTree_All;

    void bookPassedEventTree(TString treeName, TTree *tree);
    /*void setTreeVariables( const edm::Event&, const edm::EventSetup&, 
                           std::vector<pat::Muon> selectedMuons, std::vector<pat::Electron> selectedElectrons, 
                           std::vector<pat::Muon> recoMuons, std::vector<pat::Electron> recoElectrons, 
                           std::vector<pat::Jet> goodJets, std::vector<float> goodJetQGTagger, 
                           std::vector<float> goodJetaxis2, std::vector<float> goodJetptD, std::vector<int> goodJetmult, 
                           std::vector<pat::Jet> selectedMergedJets,
                           std::map<unsigned int, TLorentzVector> selectedFsrMap);
    void setGENVariables(edm::Handle<reco::GenParticleCollection> prunedgenParticles,
                         edm::Handle<edm::View<pat::PackedGenParticle> > packedgenParticles,
                         edm::Handle<edm::View<reco::GenJet> > genJets);*/
		void setTreeVariables( const edm::Event&, const edm::EventSetup&,
                           std::vector<pat::Jet> goodJets, std::vector<float> goodJetQGTagger,
                           std::vector<float> goodJetaxis2, std::vector<float> goodJetptD, std::vector<int> goodJetmult,
                           std::vector<pat::Jet> selectedMergedJets,
                           edm::Handle<edm::View<pat::Jet> > AK4PuppiJets,
                           edm::Handle<edm::View<pat::Jet> > AK8PuppiJets,
                           //edm::Handle<std::vector<reco::PFJet>> hltjets,
                           //edm::Handle<edm::View<reco::PFJet>> hltjetsForBTag,
                           //edm::Handle<edm::View<reco::PFJet>> hltAK4PFJetsCorrected,
                           //edm::Handle<reco::JetTagCollection> pfJetTagCollectionPrticleNetprobc,
                           //edm::Handle<reco::JetTagCollection> pfJetTagCollectionPrticleNetprobb,
                           //edm::Handle<reco::JetTagCollection> pfJetTagCollectionPrticleNetprobuds,
                           //edm::Handle<reco::JetTagCollection> pfJetTagCollectionPrticleNetprobg,
                           //edm::Handle<reco::JetTagCollection> pfJetTagCollectionPrticleNetprobtauh,
                           edm::Handle<BXVector<l1t::Jet> > bxvCaloJets,
                           edm::Handle<BXVector<l1t::Muon> > bxvCaloMuons,
                           edm::Handle<BXVector<l1t::EtSum> > bxvCaloHT,
                           std::vector<pat::Muon> AllMuons, std::vector<pat::Electron> AllElectrons);
    void setGENVariables(edm::Handle<reco::GenParticleCollection> prunedgenParticles,
                         edm::Handle<edm::View<pat::PackedGenParticle> > packedgenParticles,
                         edm::Handle<edm::View<reco::GenJet> > genJets);


    // -------------------------
    // RECO level information
    // -------------------------

    // Event Variables
    ULong64_t Run, Event, LumiSect, puN;
    int nVtx, nInt;
    int finalState;
    std::string triggersPassed;
    bool passedTrig, passedFullSelection, passedZ4lSelection, passedQCDcut;

    std::vector<string>  Trigger_l1name;
    std::vector<int> Trigger_l1decision;
    std::vector<string>  Trigger_hltname;
    std::vector<int> Trigger_hltdecision;
    
    float PV_x, PV_y, PV_z; 
    float BS_x, BS_y, BS_z; 
    float BS_xErr, BS_yErr, BS_zErr; 
    float BeamWidth_x, BeamWidth_y;
    float BeamWidth_xErr, BeamWidth_yErr;


    // Event Weights
    float genWeight, pileupWeight, pileupWeightUp, pileupWeightDn, dataMCWeight, eventWeight, prefiringWeight;
    float k_qqZZ_qcd_dPhi, k_qqZZ_qcd_M, k_qqZZ_qcd_Pt, k_qqZZ_ewk;
    // pdf weights                                                                   
    vector<float> qcdWeights;
    vector<float> nnloWeights;
    vector<float> pdfWeights;
    int posNNPDF;
    float pdfRMSup, pdfRMSdown, pdfENVup, pdfENVdown;
    // lepton variables
    vector<double> lep_pt; vector<double> lep_eta; vector<double> lep_phi; vector<double> lep_mass; vector<int> lep_ID;
	vector<double> ALLlep_pt; vector<double> ALLlep_eta; vector<double> ALLlep_phi; vector<double> ALLlep_mass; vector<int> ALLlep_id;
	vector<double> AK4lep_pt; vector<double> AK4lep_eta; vector<double> AK4lep_phi; vector<double> AK4lep_mass; vector<int> AK4lep_id;


   /* vector<double> lep_pt_genFromReco;
    vector<double> lep_pt; vector<double> lep_pterr; vector<double> lep_pterrold; 
    vector<double> lep_p; vector<double> lep_ecalEnergy; vector<int> lep_isEB; vector<int> lep_isEE;
    vector<double> lep_eta; vector<double> lep_phi; vector<double> lep_mass;
    vector<double> lepFSR_pt; vector<double> lepFSR_eta; vector<double> lepFSR_phi; vector<double> lepFSR_mass; vector<int> lepFSR_ID;

    vector<double> lep_errPre_Scale, lep_errPost_Scale, lep_errPre_noScale, lep_errPost_noScale;
    vector<double> lep_pt_UnS, lep_pterrold_UnS;

    int lep_Hindex[4];//position of Higgs candidate leptons in lep_p4: 0 = Z1 lead, 1 = Z1 sub, 2 = Z2 lead, 3 = Z2 sub

    vector<float> lep_d0BS;
	vector<float> lep_numberOfValidPixelHits;
	vector<float> lep_trackerLayersWithMeasurement;

    vector<float> lep_d0PV;
    vector<float> lep_dataMC; vector<float> lep_dataMCErr;
    vector<float> dataMC_VxBS; vector<float> dataMCErr_VxBS;
    vector<int> lep_genindex; //position of lepton in GENlep_p4 (if gen matched, -1 if not gen matched)
    vector<int> lep_matchedR03_PdgId, lep_matchedR03_MomId, lep_matchedR03_MomMomId; // gen matching even if not in GENlep_p4
    vector<int> lep_id;
    vector<float> lep_mva; vector<int> lep_ecalDriven; 
    vector<int> lep_tightId; vector<int> lep_tightIdSUS; vector<int> lep_tightIdHiPt; //vector<int> lep_tightId_old;
    vector<float> lep_Sip; vector<float> lep_IP; vector<float> lep_isoNH; vector<float> lep_isoCH; vector<float> lep_isoPhot;
    vector<float> lep_isoPU; vector<float> lep_isoPUcorr; 
    vector<float> lep_RelIso; vector<float> lep_RelIsoNoFSR; vector<float> lep_MiniIso; 
    vector<float> lep_ptRatio; vector<float> lep_ptRel;
    vector<int> lep_missingHits;
    vector<string> lep_filtersMatched; // for each lepton, all filters it is matched to
    int nisoleptons;
    double muRho, elRho, rhoSUS;

    // tau variables
    vector<int> tau_id;
    vector<double> tau_pt, tau_eta, tau_phi, tau_mass;

    // photon variables
    vector<double> pho_pt, pho_eta, pho_phi, photonCutBasedIDLoose;

    // Higgs candidate variables

    vector<double> H_pt; vector<double> H_eta; vector<double> H_phi; vector<double> H_mass;
    vector<double> H_noFSR_pt; vector<double> H_noFSR_eta; vector<double> H_noFSR_phi; vector<double> H_noFSR_mass;
    float mass4l, mass4l_noFSR, mass4e, mass4mu, mass2e2mu, pT4l, eta4l, phi4l, rapidity4l;
    float cosTheta1, cosTheta2, cosThetaStar, Phi, Phi1;
    float mass3l;

    // kin fit
    float mass4lREFIT, massZ1REFIT, massZ2REFIT, mass4lErr, mass4lErrREFIT;
    float mass4l_singleBS, mass4l_singleBS_FSR, mass4lREFIT_singleBS, mass4lErr_singleBS, mass4lErrREFIT_singleBS;
    float mass4l_vtx, mass4l_vtxFSR, mass4lREFIT_vtx, mass4lErr_vtx, mass4lErrREFIT_vtx;
    float massZ1REFIT_singleBS, massZ2REFIT_singleBS;

    // Z candidate variables
    vector<double> Z_pt; vector<double> Z_eta; vector<double> Z_phi; vector<double> Z_mass;
    vector<double> Z_noFSR_pt; vector<double> Z_noFSR_eta; vector<double> Z_noFSR_phi; vector<double> Z_noFSR_mass;
    int Z_Hindex[2]; // position of Z1 and Z2 in Z_p4
    float massZ1, massZ1_Z1L, massZ2, pTZ1, pTZ2;
    float massErrH_vtx;*/

    // MET
    float met; float met_phi;
    float met_jesup, met_phi_jesup, met_jesdn, met_phi_jesdn;
    float met_uncenup, met_phi_uncenup, met_uncendn, met_phi_uncendn;

    //L1 HT
    float L1ht;

    //hlt jets for B Tag
    vector<double> hltjetForBTag_pt;
    vector<double> hltjetForBTag_eta;
    vector<double> hltjetForBTag_phi;
    vector<double> hltjetForBTag_mass;
    vector<float> hltParticleNetONNXJetTags_probb, hltParticleNetONNXJetTags_probc,hltParticleNetONNXJetTags_probuds, hltParticleNetONNXJetTags_probg, hltParticleNetONNXJetTags_probtauh;    
		
    // HLT jets hltAK4PFJetsCorrected
		
    vector<double> hltAK4PFJetsCorrected_pt;
    vector<double> hltAK4PFJetsCorrected_eta;
    vector<double> hltAK4PFJetsCorrected_phi;
    vector<double> hltAK4PFJetsCorrected_mass;
    
    // Puppi AK4jets with ParticleNet taggers

    vector<double> AK4PuppiJets_pt;
    vector<double> AK4PuppiJets_eta;
    vector<double> AK4PuppiJets_phi;
    vector<double> AK4PuppiJets_mass;

    vector<float> jet_pfParticleNetAK4JetTags_probb, jet_pfParticleNetAK4JetTags_probc, jet_pfParticleNetAK4JetTags_probuds,jet_pfParticleNetAK4JetTags_probg, jet_pfParticleNetAK4JetTags_probtauh;  
    // Puppi AK8jets with ParticleNet(-MD) and DeepDoubleX taggers
	
		vector<double> AK8PuppiJets_pt;
		vector<double> AK8PuppiJets_eta;
		vector<double> AK8PuppiJets_phi;
		vector<double> AK8PuppiJets_mass;
	
		vector<float> jet_pfParticleNetJetTags_probZbb, jet_pfParticleNetJetTags_probZcc, jet_pfParticleNetJetTags_probZqq, jet_pfParticleNetJetTags_probQCDbb, jet_pfParticleNetJetTags_probQCDcc, jet_pfParticleNetJetTags_probQCDb, jet_pfParticleNetJetTags_probQCDc, jet_pfParticleNetJetTags_probQCDothers, jet_pfParticleNetJetTags_probHbb, jet_pfParticleNetJetTags_probHcc, jet_pfParticleNetJetTags_probHqqqq;  
		
		vector<float> jet_pfMassDecorrelatedParticleNetJetTags_probXbb, jet_pfMassDecorrelatedParticleNetJetTags_probXcc, jet_pfMassDecorrelatedParticleNetJetTags_probXqq, jet_pfMassDecorrelatedParticleNetJetTags_probQCDbb, jet_pfMassDecorrelatedParticleNetJetTags_probQCDcc, jet_pfMassDecorrelatedParticleNetJetTags_probQCDb, jet_pfMassDecorrelatedParticleNetJetTags_probQCDc, jet_pfMassDecorrelatedParticleNetJetTags_probQCDothers;
    vector<float> jet_pfMassIndependentDeepDoubleBvLV2JetTags_probHbb, jet_pfMassIndependentDeepDoubleCvLV2JetTags_probHcc, jet_pfMassIndependentDeepDoubleCvBV2JetTags_probHcc;

    // Jets
    vector<int>    jet_iscleanH4l;
    int jet1index, jet2index;
    vector<double> jet_pt; vector<double> jet_eta; vector<double> jet_phi; vector<double> jet_mass; vector<double> jet_pt_raw;
    vector<float>  jet_csv_cTag_vsL, jet_csv_cTag_vsB;
    vector<float>  jet_pumva, jet_csvv2,  jet_csvv2_; vector<int> jet_isbtag;
	vector<float>  jet_pfDeepCSVJetTags_probb, jet_pfDeepFlavourJetTags_probbb, jet_pfDeepFlavourJetTags_probc, jet_pfDeepFlavourJetTags_probuds;
    vector<int>    jet_hadronFlavour, jet_partonFlavour;
    vector<float>  jet_QGTagger, jet_QGTagger_jesup, jet_QGTagger_jesdn; 
    vector<float> jet_axis2, jet_ptD; vector<int> jet_mult;
    vector<float>  jet_relpterr; vector<float>  jet_phierr;
    vector<float>  jet_bTagEffi;
    vector<float>  jet_cTagEffi;
    vector<float>  jet_udsgTagEffi;
    vector<int>    jet_jesup_iscleanH4l;
    vector<double> jet_jesup_pt; vector<double> jet_jesup_eta; 
    vector<double> jet_jesup_phi; vector<double> jet_jesup_mass;
    vector<int>    jet_jesdn_iscleanH4l;
    vector<double> jet_jesdn_pt; vector<double> jet_jesdn_eta; 
    vector<double> jet_jesdn_phi; vector<double> jet_jesdn_mass;
    vector<int>    jet_jerup_iscleanH4l;
    vector<double> jet_jerup_pt; vector<double> jet_jerup_eta; 
    vector<double> jet_jerup_phi; vector<double> jet_jerup_mass;
    vector<int>    jet_jerdn_iscleanH4l;
    vector<double> jet_jerdn_pt; vector<double> jet_jerdn_eta; 
	vector<double> L1jet_pt; vector<double> L1jet_eta; vector<double> L1jet_phi; vector<double> L1jet_mass;
    vector<double> L1muon_pt; vector<double> L1muon_eta; vector<double> L1muon_phi; vector<double> L1muon_mass;
	vector<int> L1muon_qual;	
    vector<double> jet_jerdn_phi; vector<double> jet_jerdn_mass;    
    int njets_pt30_eta4p7; int njets_pt30_eta4p7_jesup; int njets_pt30_eta4p7_jesdn; 
    int njets_pt30_eta4p7_jerup; int njets_pt30_eta4p7_jerdn;
    int njets_pt30_eta2p5; int njets_pt30_eta2p5_jesup; int njets_pt30_eta2p5_jesdn; 
    int njets_pt30_eta2p5_jerup; int njets_pt30_eta2p5_jerdn;
    int nbjets_pt30_eta4p7; int nvjets_pt40_eta2p4;
    float pt_leadingjet_pt30_eta4p7;
    float pt_leadingjet_pt30_eta4p7_jesup; float pt_leadingjet_pt30_eta4p7_jesdn;
    float pt_leadingjet_pt30_eta4p7_jerup; float pt_leadingjet_pt30_eta4p7_jerdn;
    float pt_leadingjet_pt30_eta2p5;
    float pt_leadingjet_pt30_eta2p5_jesup; float pt_leadingjet_pt30_eta2p5_jesdn;
    float pt_leadingjet_pt30_eta2p5_jerup; float pt_leadingjet_pt30_eta2p5_jerdn;
    float absrapidity_leadingjet_pt30_eta4p7;
    float absrapidity_leadingjet_pt30_eta4p7_jesup; float absrapidity_leadingjet_pt30_eta4p7_jesdn;
    float absrapidity_leadingjet_pt30_eta4p7_jerup; float absrapidity_leadingjet_pt30_eta4p7_jerdn;
    float absdeltarapidity_hleadingjet_pt30_eta4p7;
    float absdeltarapidity_hleadingjet_pt30_eta4p7_jesup; float absdeltarapidity_hleadingjet_pt30_eta4p7_jesdn;
    float absdeltarapidity_hleadingjet_pt30_eta4p7_jerup; float absdeltarapidity_hleadingjet_pt30_eta4p7_jerdn;
    float DijetMass, DijetDEta, DijetFisher;

    // merged jets
    vector<int>   mergedjet_iscleanH4l;
    vector<float> mergedjet_pt; vector<float> mergedjet_eta; vector<float> mergedjet_phi; vector<float> mergedjet_mass;
    
    vector<float> mergedjet_tau1; vector<float> mergedjet_tau2;
    vector<float> mergedjet_btag;

    vector<float> mergedjet_L1;
    vector<float> mergedjet_prunedmass; vector<float> mergedjet_softdropmass;
    
    vector<int> mergedjet_nsubjet;
    vector<vector<float> > mergedjet_subjet_pt; vector<vector<float> > mergedjet_subjet_eta;
    vector<vector<float> > mergedjet_subjet_phi; vector<vector<float> > mergedjet_subjet_mass;
    vector<vector<float> > mergedjet_subjet_btag;
    vector<vector<int> > mergedjet_subjet_partonFlavour, mergedjet_subjet_hadronFlavour;

    // FSR Photons
    /*int nFSRPhotons;
    vector<int> fsrPhotons_lepindex; 
    vector<double> fsrPhotons_pt; vector<double> fsrPhotons_pterr;
    vector<double> fsrPhotons_eta; vector<double> fsrPhotons_phi;
    vector<double> fsrPhotons_mass;
    vector<float> fsrPhotons_dR; vector<float> fsrPhotons_iso;
    vector<float> allfsrPhotons_dR; vector<float> allfsrPhotons_pt; vector<float> allfsrPhotons_iso;

    // Z4l? FIXME
    float theta12, theta13, theta14;  
    float minM3l, Z4lmaxP, minDeltR, m3l_soft;
    float minMass2Lep, maxMass2Lep;
    float thetaPhoton, thetaPhotonZ;*/

    // Event Category
    int EventCat;

    // -------------------------
    // GEN level information
    // -------------------------

    //Event variables
    int GENfinalState;

    // lepton variables
    /*vector<double> GENlep_pt; vector<double> GENlep_eta; vector<double> GENlep_phi; vector<double> GENlep_mass; 
    vector<int> GENlep_id; vector<int> GENlep_status; 
    vector<int> GENlep_MomId; vector<int> GENlep_MomMomId;
    int GENlep_Hindex[4];//position of Higgs candidate leptons in lep_p4: 0 = Z1 lead, 1 = Z1 sub, 2 = Z2 lead, 3 = Z3 sub
    vector<float> GENlep_isoCH; vector<float> GENlep_isoNH; vector<float> GENlep_isoPhot; vector<float> GENlep_RelIso; 

    // Higgs candidate variables (calculated using selected gen leptons)
    vector<double> GENH_pt; vector<double> GENH_eta; vector<double> GENH_phi; vector<double> GENH_mass; 
    float GENmass4l, GENmass4e, GENmass4mu, GENmass2e2mu, GENpT4l, GENeta4l, GENrapidity4l;
    float GENMH; //mass directly from gen particle with id==25
    float GENcosTheta1, GENcosTheta2, GENcosThetaStar, GENPhi, GENPhi1;

    // Z candidate variables
    vector<double> GENZ_pt; vector<double> GENZ_eta; vector<double> GENZ_phi; vector<double> GENZ_mass; 
    vector<int> GENZ_DaughtersId; vector<int> GENZ_MomId;
    float  GENmassZ1, GENmassZ2, GENpTZ1, GENpTZ2, GENdPhiZZ, GENmassZZ, GENpTZZ;

    // Higgs variables directly from GEN particle
    float GENHmass;*/

    // Jets
    vector<double> GENjet_pt; vector<double> GENjet_eta; vector<double> GENjet_phi; vector<double> GENjet_mass; 
    vector<double> quark_pt; vector<double> quark_eta; vector<double> quark_phi; vector<int> quark_flavour; vector<bool> quark_VBF;
		int GENnjets_pt30_eta4p7; float GENpt_leadingjet_pt30_eta4p7; 
    int GENnjets_pt30_eta2p5; float GENpt_leadingjet_pt30_eta2p5; 
    float GENabsrapidity_leadingjet_pt30_eta4p7; float GENabsdeltarapidity_hleadingjet_pt30_eta4p7;
    int lheNb, lheNj, nGenStatus2bHad;

    // a vector<float> for each vector<double>
    /*vector<float> lep_d0BS_float;
    vector<float> lep_d0PV_float;

	vector<float> lep_numberOfValidPixelHits_float;
	vector<float> lep_trackerLayersWithMeasurement_float;


	vector<float> lep_pt_genFromReco_float;
    vector<double> lep_pt_UnS_float, lep_pterrold_UnS_float;
    vector<float> lep_errPre_Scale_float;
    vector<float> lep_errPost_Scale_float;
    vector<float> lep_errPre_noScale_float;
    vector<float> lep_errPost_noScale_float;

    vector<float> lep_pt_float, lep_pterr_float, lep_pterrold_float;
    vector<float> lep_p_float, lep_ecalEnergy_float;
    vector<float> lep_eta_float, lep_phi_float, lep_mass_float;
    vector<float> lepFSR_pt_float, lepFSR_eta_float;
    vector<float> lepFSR_phi_float, lepFSR_mass_float;
    vector<float> tau_pt_float, tau_eta_float, tau_phi_float, tau_mass_float;
    vector<float> pho_pt_float, pho_eta_float, pho_phi_float, photonCutBasedIDLoose_float;
    vector<float> H_pt_float, H_eta_float, H_phi_float, H_mass_float;
    vector<float> H_noFSR_pt_float, H_noFSR_eta_float; 
    vector<float> H_noFSR_phi_float, H_noFSR_mass_float;
    vector<float> Z_pt_float, Z_eta_float, Z_phi_float, Z_mass_float;
    vector<float> Z_noFSR_pt_float, Z_noFSR_eta_float;
    vector<float> Z_noFSR_phi_float, Z_noFSR_mass_float;*/
    vector<float> lep_pt_float, lep_eta_float, lep_phi_float, lep_mass_float;
    int n_jets=0;
    vector<float> hltjetForBTag_pt_float, hltjetForBTag_eta_float, hltjetForBTag_phi_float, hltjetForBTag_mass_float;
    vector<float> hltAK4PFJetsCorrected_pt_float, hltAK4PFJetsCorrected_eta_float, hltAK4PFJetsCorrected_phi_float, hltAK4PFJetsCorrected_mass_float;
    vector<float> hltAK8PFJetsCorrected_pt_float, hltAK8PFJetsCorrected_eta_float, hltAK8PFJetsCorrected_phi_float, hltAK8PFJetsCorrected_mass_float;
    vector<float> jet_pt_float, jet_eta_float, jet_phi_float, jet_mass_float, jet_pt_raw_float;
    
    vector<float>  jet_csv_cTag_vsL_float, jet_csv_cTag_vsB_float;
    vector<float> jet_jesup_pt_float, jet_jesup_eta_float; 
    vector<float> jet_jesup_phi_float, jet_jesup_mass_float;
    vector<float> jet_jesdn_pt_float, jet_jesdn_eta_float;
    vector<float> jet_jesdn_phi_float, jet_jesdn_mass_float;
    vector<float> jet_jerup_pt_float, jet_jerup_eta_float;
    vector<float> jet_jerup_phi_float, jet_jerup_mass_float;
    vector<float> jet_jerdn_pt_float, jet_jerdn_eta_float;
    vector<float> jet_jerdn_phi_float, jet_jerdn_mass_float;
    vector<float> fsrPhotons_pt_float, fsrPhotons_pterr_float;
    vector<float> fsrPhotons_eta_float, fsrPhotons_phi_float, fsrPhotons_mass_float;
    /*vector<float> GENlep_pt_float, GENlep_eta_float;
    vector<float> GENlep_phi_float, GENlep_mass_float;
    vector<float> GENH_pt_float, GENH_eta_float;
    vector<float> GENH_phi_float, GENH_mass_float;
    vector<float> GENZ_pt_float, GENZ_eta_float;
    vector<float> GENZ_phi_float, GENZ_mass_float;*/
    int n_GENjets=0;
    vector<float> GENjet_pt_float, GENjet_eta_float;
    vector<float> GENjet_phi_float, GENjet_mass_float;
	vector<float> quark_pt_float, quark_eta_float, quark_phi_float;
    vector<float> L1jet_pt_float, L1jet_eta_float, L1jet_phi_float, L1jet_mass_float;
    vector<float> L1muon_pt_float, L1muon_eta_float, L1muon_phi_float, L1muon_mass_float;

    vector<float> AK4PuppiJets_pt_float;
    vector<float> AK4PuppiJets_eta_float;
    vector<float> AK4PuppiJets_phi_float;
    vector<float> AK4PuppiJets_mass_float;
	
	vector<float> AK8PuppiJets_pt_float;
    vector<float> AK8PuppiJets_eta_float;
    vector<float> AK8PuppiJets_phi_float;
    vector<float> AK8PuppiJets_mass_float;

    // Global Variables but not stored in the tree
    //vector<double> lep_ptreco;
    //vector<int> lep_ptid; vector<int> lep_ptindex;
    vector<pat::Muon> recoMuons; vector<pat::Electron> recoElectrons; vector<pat::Electron> recoElectronsUnS; 
    /*vector<pat::Tau> recoTaus; vector<pat::Photon> recoPhotons;
    vector<pat::PFParticle> fsrPhotons; 
    TLorentzVector HVec, HVecNoFSR, Z1Vec, Z2Vec;
    TLorentzVector GENZ1Vec, GENZ2Vec;
    bool foundHiggsCandidate; bool firstEntry;*/
    float jet1pt, jet2pt;
		bool firstEntry;

    // hist container
    std::map<std::string,TH1F*> histContainer_;

    //Input edm
    edm::EDGetTokenT<edm::View<pat::Electron> > elecSrc_;
    edm::EDGetTokenT<edm::View<pat::Electron> > elecUnSSrc_;
    edm::EDGetTokenT<edm::View<pat::Muon> > muonSrc_;
    //edm::EDGetTokenT<edm::View<pat::Tau> > tauSrc_;
    //edm::EDGetTokenT<edm::View<pat::Photon> > photonSrc_;
    edm::EDGetTokenT<edm::View<pat::Jet> > jetSrc_;
    edm::EDGetTokenT<edm::View<pat::Jet> > AK4PuppiJetSrc_;
    edm::EDGetTokenT<edm::View<pat::Jet> > AK8PuppiJetSrc_;
    edm::EDGetTokenT<BXVector<l1t::Jet>> bxvCaloJetSrc_;
    //edm::EDGetTokenT<edm::View<reco::PFJet>> hltPFJetForBtagSrc_;
    //edm::EDGetTokenT<edm::View<reco::PFJet>> hltAK4PFJetsCorrectedSrc_;
    //edm::EDGetTokenT<reco::JetTagCollection> pfJetTagCollectionParticleNetprobcSrc_;  //value map for Particle Net tagger at hlt
    //edm::EDGetTokenT<reco::JetTagCollection> pfJetTagCollectionParticleNetprobbSrc_;  //value map for Particle Net tagger at hlt
    //edm::EDGetTokenT<reco::JetTagCollection> pfJetTagCollectionParticleNetprobudsSrc_;  //value map for Particle Net tagger at hlt
    //edm::EDGetTokenT<reco::JetTagCollection> pfJetTagCollectionParticleNetprobgSrc_;  //value map for Particle Net tagger at hlt
    //edm::EDGetTokenT<reco::JetTagCollection> pfJetTagCollectionParticleNetprobtauhSrc_;  //value map for Particle Net tagger at hlt
    edm::EDGetTokenT<BXVector<l1t::Muon>> bxvCaloMuonSrc_;
    edm::EDGetTokenT<BXVector<l1t::EtSum>> bxvCaloHTSrc_;
    edm::EDGetTokenT<edm::ValueMap<float> > qgTagSrc_;
    edm::EDGetTokenT<edm::ValueMap<float> > axis2Src_;
    edm::EDGetTokenT<edm::ValueMap<int> > multSrc_;
    edm::EDGetTokenT<edm::ValueMap<float> > ptDSrc_;
    edm::EDGetTokenT<edm::View<pat::Jet> > mergedjetSrc_;
    edm::EDGetTokenT<edm::View<pat::MET> > metSrc_;
    //edm::InputTag triggerSrc_;
    edm::EDGetTokenT<edm::TriggerResults> triggerSrc_;
    edm::EDGetTokenT<pat::TriggerObjectStandAloneCollection> triggerObjects_;
    edm::EDGetTokenT<reco::VertexCollection> vertexSrc_;
    edm::EDGetTokenT<reco::BeamSpot> beamSpotSrc_;
    edm::EDGetTokenT<std::vector<reco::Conversion> > conversionSrc_;
    edm::EDGetTokenT<double> muRhoSrc_;
    edm::EDGetTokenT<double> elRhoSrc_;
    edm::EDGetTokenT<double> rhoSrcSUS_;
    edm::EDGetTokenT<std::vector<PileupSummaryInfo> > pileupSrc_;
    edm::EDGetTokenT<pat::PackedCandidateCollection> pfCandsSrc_;
    edm::EDGetTokenT<edm::View<pat::PFParticle> > fsrPhotonsSrc_;
    edm::EDGetTokenT<reco::GenParticleCollection> prunedgenParticlesSrc_;
    edm::EDGetTokenT<edm::View<pat::PackedGenParticle> > packedgenParticlesSrc_;
    edm::EDGetTokenT<edm::View<reco::GenJet> > genJetsSrc_;
    edm::EDGetTokenT<GenEventInfoProduct> generatorSrc_;
    edm::EDGetTokenT<LHEEventProduct> lheInfoSrc_;
    edm::EDGetTokenT<LHERunInfoProduct> lheRunInfoToken_;
    edm::EDGetTokenT<HTXS::HiggsClassification> htxsSrc_;
    //edm::EDGetTokenT<HZZFid::FiducialSummary> fidRivetSrc_;
    edm::EDGetTokenT< double > prefweight_token_;
    edm::EDGetToken algTok_;
    edm::EDGetTokenT<GlobalAlgBlkBxCollection> algInputTag_;
    l1t::L1TGlobalUtil* gtUtil_;


    // Configuration
    const float Zmass;
    float mZ1Low, mZ2Low, mZ1High, mZ2High, m4lLowCut;
    float jetpt_cut, jeteta_cut;
    std::string elecID;
    bool isMC, isSignal;
    float mH;
    float crossSection;
    bool weightEvents;
    float isoCutEl, isoCutMu; 
    double isoConeSizeEl, isoConeSizeMu;
    float sip3dCut, leadingPtCut, subleadingPtCut;
    float genIsoCutEl, genIsoCutMu;
    double genIsoConeSizeEl, genIsoConeSizeMu;
    float _elecPtCut, _muPtCut, _tauPtCut, _phoPtCut;
    float BTagCut;
    bool reweightForPU;
    std::string PUVersion;
    bool doFsrRecovery, GENbestM4l;
    bool doPUJetID;
    int jetIDLevel;
    bool doJER;
    bool doJEC;
    bool doRefit;
    bool doTriggerMatching;
    bool checkOnlySingle;
    std::vector<std::string> triggerList;
    int skimLooseLeptons, skimTightLeptons;
    bool verbose;

    int year;///use to choose Muon BDT
    bool isCode4l;

edm::ESGetToken<JetCorrectorParametersCollection, JetCorrectionsRecord> mPayloadToken;

std::string res_pt_config;
std::string res_phi_config;
std::string res_sf_config;

    // register to the TFileService
    edm::Service<TFileService> fs;

    // Counters
    float nEventsTotal;
    float sumWeightsTotal;
    float sumWeightsTotalPU;

    // JER
    JME::JetResolution resolution_pt, resolution_phi;
    JME::JetResolutionScaleFactor resolution_sf;

    string EleBDT_name_161718;
    string heepID_name_161718;

};


HccAna::HccAna(const edm::ParameterSet& iConfig) :
    histContainer_(),
    //elecSrc_(consumes<edm::View<pat::Electron> >(iConfig.getUntrackedParameter<edm::InputTag>("electronSrc"))),
    elecSrc_(consumes<edm::View<pat::Electron> >(iConfig.getUntrackedParameter<edm::InputTag>("electronUnSSrc"))),
    elecUnSSrc_(consumes<edm::View<pat::Electron> >(iConfig.getUntrackedParameter<edm::InputTag>("electronUnSSrc"))),
    muonSrc_(consumes<edm::View<pat::Muon> >(iConfig.getUntrackedParameter<edm::InputTag>("muonSrc"))),
    //tauSrc_(consumes<edm::View<pat::Tau> >(iConfig.getUntrackedParameter<edm::InputTag>("tauSrc"))),
    //photonSrc_(consumes<edm::View<pat::Photon> >(iConfig.getUntrackedParameter<edm::InputTag>("photonSrc"))),
    jetSrc_(consumes<edm::View<pat::Jet> >(iConfig.getUntrackedParameter<edm::InputTag>("jetSrc"))),
    AK4PuppiJetSrc_(consumes<edm::View<pat::Jet> >(iConfig.getUntrackedParameter<edm::InputTag>("AK4PuppiJetSrc"))),
	AK8PuppiJetSrc_(consumes<edm::View<pat::Jet> >(iConfig.getUntrackedParameter<edm::InputTag>("AK8PuppiJetSrc"))),
    bxvCaloJetSrc_(consumes<BXVector<l1t::Jet>>(iConfig.getParameter<edm::InputTag>("bxvCaloJetSrc"))),
    //hltPFJetForBtagSrc_(consumes<edm::View<reco::PFJet>>(iConfig.getParameter<edm::InputTag>("hltPFJetForBtagSrc"))),
    //hltAK4PFJetsCorrectedSrc_(consumes<edm::View<reco::PFJet>>(iConfig.getParameter<edm::InputTag>("hltAK4PFJetsCorrectedSrc"))),
    //pfJetTagCollectionParticleNetprobcSrc_(consumes(iConfig.getParameter<edm::InputTag>("pfJetTagCollectionParticleNetprobcSrc"))),
    //pfJetTagCollectionParticleNetprobbSrc_(consumes(iConfig.getParameter<edm::InputTag>("pfJetTagCollectionParticleNetprobbSrc"))),
    //pfJetTagCollectionParticleNetprobudsSrc_(consumes(iConfig.getParameter<edm::InputTag>("pfJetTagCollectionParticleNetprobudsSrc"))),
    //pfJetTagCollectionParticleNetprobgSrc_(consumes(iConfig.getParameter<edm::InputTag>("pfJetTagCollectionParticleNetprobgSrc"))),
    //pfJetTagCollectionParticleNetprobtauhSrc_(consumes(iConfig.getParameter<edm::InputTag>("pfJetTagCollectionParticleNetprobtauhSrc"))),
    bxvCaloMuonSrc_(consumes<BXVector<l1t::Muon>>(iConfig.getParameter<edm::InputTag>("bxvCaloMuonSrc"))),
    bxvCaloHTSrc_(consumes<BXVector<l1t::EtSum>>(iConfig.getParameter<edm::InputTag>("bxvCaloHTSrc"))),
    qgTagSrc_(consumes<edm::ValueMap<float>>(edm::InputTag("QGTagger", "qgLikelihood"))),
    axis2Src_(consumes<edm::ValueMap<float>>(edm::InputTag("QGTagger", "axis2"))),
    multSrc_(consumes<edm::ValueMap<int>>(edm::InputTag("QGTagger", "mult"))),
    ptDSrc_(consumes<edm::ValueMap<float>>(edm::InputTag("QGTagger", "ptD"))),
    mergedjetSrc_(consumes<edm::View<pat::Jet> >(iConfig.getUntrackedParameter<edm::InputTag>("mergedjetSrc"))),
    metSrc_(consumes<edm::View<pat::MET> >(iConfig.getUntrackedParameter<edm::InputTag>("metSrc"))),
    triggerSrc_(consumes<edm::TriggerResults>(iConfig.getParameter<edm::InputTag>("triggerSrc"))),
    triggerObjects_(consumes<pat::TriggerObjectStandAloneCollection>(iConfig.getParameter<edm::InputTag>("triggerObjects"))),
    vertexSrc_(consumes<reco::VertexCollection>(iConfig.getUntrackedParameter<edm::InputTag>("vertexSrc"))),
    beamSpotSrc_(consumes<reco::BeamSpot>(iConfig.getUntrackedParameter<edm::InputTag>("beamSpotSrc"))),
    conversionSrc_(consumes<std::vector<reco::Conversion> >(iConfig.getUntrackedParameter<edm::InputTag>("conversionSrc"))),
    muRhoSrc_(consumes<double>(iConfig.getUntrackedParameter<edm::InputTag>("muRhoSrc"))),
    elRhoSrc_(consumes<double>(iConfig.getUntrackedParameter<edm::InputTag>("elRhoSrc"))),
    rhoSrcSUS_(consumes<double>(iConfig.getUntrackedParameter<edm::InputTag>("rhoSrcSUS"))),
    pileupSrc_(consumes<std::vector<PileupSummaryInfo> >(iConfig.getUntrackedParameter<edm::InputTag>("pileupSrc"))),
    pfCandsSrc_(consumes<pat::PackedCandidateCollection>(iConfig.getUntrackedParameter<edm::InputTag>("pfCandsSrc"))),
    fsrPhotonsSrc_(consumes<edm::View<pat::PFParticle> >(iConfig.getUntrackedParameter<edm::InputTag>("fsrPhotonsSrc"))),
    prunedgenParticlesSrc_(consumes<reco::GenParticleCollection>(iConfig.getUntrackedParameter<edm::InputTag>("prunedgenParticlesSrc"))),
    packedgenParticlesSrc_(consumes<edm::View<pat::PackedGenParticle> >(iConfig.getUntrackedParameter<edm::InputTag>("packedgenParticlesSrc"))),
    genJetsSrc_(consumes<edm::View<reco::GenJet> >(iConfig.getUntrackedParameter<edm::InputTag>("genJetsSrc"))),
    generatorSrc_(consumes<GenEventInfoProduct>(iConfig.getUntrackedParameter<edm::InputTag>("generatorSrc"))),
    lheInfoSrc_(consumes<LHEEventProduct>(iConfig.getUntrackedParameter<edm::InputTag>("lheInfoSrc"))),
    lheRunInfoToken_(consumes<LHERunInfoProduct,edm::InRun>(edm::InputTag("externalLHEProducer",""))),
    htxsSrc_(consumes<HTXS::HiggsClassification>(edm::InputTag("rivetProducerHTXS","HiggsClassification"))),
    //prefweight_token_(consumes< double >(edm::InputTag("prefiringweight:nonPrefiringProb"))),
    //fidRivetSrc_(consumes<HZZFid::FiducialSummary>(edm::InputTag("rivetProducerHZZFid","FiducialSummary"))),
    algTok_(consumes<BXVector<GlobalAlgBlk>>(iConfig.getParameter<edm::InputTag>("algInputTag"))),
    algInputTag_(consumes<GlobalAlgBlkBxCollection>(iConfig.getParameter<edm::InputTag>("algInputTag"))),
    gtUtil_(new l1t::L1TGlobalUtil(iConfig, consumesCollector(), *this, iConfig.getParameter<edm::InputTag>("algInputTag"), iConfig.getParameter<edm::InputTag>("algInputTag"), l1t::UseEventSetupIn::RunAndEvent)),
    Zmass(91.1876),
    mZ1Low(iConfig.getUntrackedParameter<double>("mZ1Low",40.0)),
    mZ2Low(iConfig.getUntrackedParameter<double>("mZ2Low",12.0)), // was 12
    mZ1High(iConfig.getUntrackedParameter<double>("mZ1High",120.0)),
    mZ2High(iConfig.getUntrackedParameter<double>("mZ2High",120.0)),
    m4lLowCut(iConfig.getUntrackedParameter<double>("m4lLowCut",70.0)),
//     m4lLowCut(iConfig.getUntrackedParameter<double>("m4lLowCut",0.0)),
    jetpt_cut(iConfig.getUntrackedParameter<double>("jetpt_cut",10.0)),
    jeteta_cut(iConfig.getUntrackedParameter<double>("eta_cut",47)),
    elecID(iConfig.getUntrackedParameter<std::string>("elecID","NonTrig")),
    isMC(iConfig.getUntrackedParameter<bool>("isMC",true)),
    isSignal(iConfig.getUntrackedParameter<bool>("isSignal",false)),
    mH(iConfig.getUntrackedParameter<double>("mH",0.0)),
    crossSection(iConfig.getUntrackedParameter<double>("CrossSection",1.0)),
    weightEvents(iConfig.getUntrackedParameter<bool>("weightEvents",false)),
    isoCutEl(iConfig.getUntrackedParameter<double>("isoCutEl",9999.0)),
    isoCutMu(iConfig.getUntrackedParameter<double>("isoCutMu",0.35)),/////ios is applied to new Muon BDT //previous 0.35///Qianying
    isoConeSizeEl(iConfig.getUntrackedParameter<double>("isoConeSizeEl",0.3)),
    isoConeSizeMu(iConfig.getUntrackedParameter<double>("isoConeSizeMu",0.3)),
    sip3dCut(iConfig.getUntrackedParameter<double>("sip3dCut",4)),
    leadingPtCut(iConfig.getUntrackedParameter<double>("leadingPtCut",20.0)),
    subleadingPtCut(iConfig.getUntrackedParameter<double>("subleadingPtCut",10.0)),
    genIsoCutEl(iConfig.getUntrackedParameter<double>("genIsoCutEl",0.35)), 
    genIsoCutMu(iConfig.getUntrackedParameter<double>("genIsoCutMu",0.35)), 
    genIsoConeSizeEl(iConfig.getUntrackedParameter<double>("genIsoConeSizeEl",0.3)), 
    genIsoConeSizeMu(iConfig.getUntrackedParameter<double>("genIsoConeSizeMu",0.3)), 
    _elecPtCut(iConfig.getUntrackedParameter<double>("_elecPtCut",7.0)),
    _muPtCut(iConfig.getUntrackedParameter<double>("_muPtCut",10.0)),
    _tauPtCut(iConfig.getUntrackedParameter<double>("_tauPtCut",20.0)),
    _phoPtCut(iConfig.getUntrackedParameter<double>("_phoPtCut",10.0)),
    BTagCut(iConfig.getUntrackedParameter<double>("BTagCut",0.4184)),/////2016: 0.6321; 2017: 0.4941; 2018: 0.4184
    reweightForPU(iConfig.getUntrackedParameter<bool>("reweightForPU",true)),
    PUVersion(iConfig.getUntrackedParameter<std::string>("PUVersion","Summer16_80X")),
    doFsrRecovery(iConfig.getUntrackedParameter<bool>("doFsrRecovery",true)),
    GENbestM4l(iConfig.getUntrackedParameter<bool>("GENbestM4l",false)),
    doPUJetID(iConfig.getUntrackedParameter<bool>("doPUJetID",true)),
    jetIDLevel(iConfig.getUntrackedParameter<int>("jetIDLevel",2)),
    doJER(iConfig.getUntrackedParameter<bool>("doJER",true)),
    doJEC(iConfig.getUntrackedParameter<bool>("doJEC",true)),
    doRefit(iConfig.getUntrackedParameter<bool>("doRefit",true)),
    doTriggerMatching(iConfig.getUntrackedParameter<bool>("doTriggerMatching",!isMC)),
    checkOnlySingle(iConfig.getUntrackedParameter<bool>("checkOnlySingle",false)),
    triggerList(iConfig.getUntrackedParameter<std::vector<std::string>>("triggerList")),
    skimLooseLeptons(iConfig.getUntrackedParameter<int>("skimLooseLeptons",2)),    
    skimTightLeptons(iConfig.getUntrackedParameter<int>("skimTightLeptons",2)),    
    verbose(iConfig.getUntrackedParameter<bool>("verbose",false)),
    year(iConfig.getUntrackedParameter<int>("year",2018)),
    ////for year put 
    // 20160 for pre VFP
    // 20165 for post VFP
    // 2017
    // 2018
    // to select correct training
    isCode4l(iConfig.getUntrackedParameter<bool>("isCode4l",true)),
mPayloadToken    {esConsumes(edm::ESInputTag("", iConfig.getParameter<std::string>("payload")))}
{
  
    if(!isMC){reweightForPU = false;}
    
//     if(!isCode4l)
//     	std::cout<<"OK"<<std::endl;

    nEventsTotal=0.0;
    sumWeightsTotal=0.0;
    sumWeightsTotalPU=0.0;
    histContainer_["NEVENTS"]=fs->make<TH1F>("nEvents","nEvents in Sample",2,0,2);
    histContainer_["SUMWEIGHTS"]=fs->make<TH1F>("sumWeights","sum Weights of Sample",2,0,2);
    histContainer_["SUMWEIGHTSPU"]=fs->make<TH1F>("sumWeightsPU","sum Weights and PU of Sample",2,0,2);
    histContainer_["NVTX"]=fs->make<TH1F>("nVtx","Number of Vertices",36,-0.5,35.5);
    histContainer_["NVTX_RW"]=fs->make<TH1F>("nVtx_ReWeighted","Number of Vertices",36,-0.5,35.5);
    histContainer_["NINTERACT"]=fs->make<TH1F>("nInteractions","Number of True Interactions",61,-0.5,60.5);
    histContainer_["NINTERACT_RW"]=fs->make<TH1F>("nInteraction_ReWeighted","Number of True Interactions",61,-0.5,60.5);

    passedEventsTree_All = new TTree("passedEvents","passedEvents");

    tableEwk = readFile_and_loadEwkTable("ZZBG");  //LUIGI 

	int YEAR = year - 2016 + 1;
	if(year == 20165) YEAR = 1;
	if(year == 20160) YEAR = 0;
   
    //string elec_scalefac_Cracks_name_161718[3] = {"egammaEffi.txt_EGM2D_cracks.root", "egammaEffi.txt_EGM2D_Moriond2018v1_gap.root", "egammaEffi.txt_EGM2D_Moriond2019_v1_gap.root"};
    string elec_scalefac_Cracks_name_161718[4] = {"ElectronSF_UL2016preVFP_gap.root", "ElectronSF_UL2016postVFP_gap.root", "ElectronSF_UL2017_gap.root", "ElectronSF_UL2018_gap.root"};
    edm::FileInPath elec_scalefacFileInPathCracks(("Hcc/HccAna/data/"+elec_scalefac_Cracks_name_161718[YEAR]).c_str());
    TFile *fElecScalFacCracks = TFile::Open(elec_scalefacFileInPathCracks.fullPath().c_str());
    hElecScaleFac_Cracks = (TH2F*)fElecScalFacCracks->Get("EGamma_SF2D");    
    //string elec_scalefac_name_161718[3] = {"egammaEffi.txt_EGM2D.root", "egammaEffi.txt_EGM2D_Moriond2018v1.root", "egammaEffi.txt_EGM2D_Moriond2019_v1.root"};
    string elec_scalefac_name_161718[4] = {"ElectronSF_UL2016preVFP_nogap.root", "ElectronSF_UL2016postVFP_nogap.root", "ElectronSF_UL2017_nogap.root", "ElectronSF_UL2018_nogap.root"};
    edm::FileInPath elec_scalefacFileInPath(("Hcc/HccAna/data/"+elec_scalefac_name_161718[YEAR]).c_str());
    TFile *fElecScalFac = TFile::Open(elec_scalefacFileInPath.fullPath().c_str());
    hElecScaleFac = (TH2F*)fElecScalFac->Get("EGamma_SF2D");    

    //string elec_Gsfscalefac_name_161718[3] = {"egammaEffi.txt_EGM2D_GSF.root", "egammaEffi.txt_EGM2D_Moriond2018v1_runBCDEF_passingRECO.root", "Ele_Reco_2018.root"};//was previous;
    string elec_Gsfscalefac_name_161718[4] = {"egammaEffi_ptAbove20.txt_EGM2D_UL2016preVFP.root", "egammaEffi_ptAbove20.txt_EGM2D_UL2016postVFP.root", "egammaEffi_ptAbove20.txt_EGM2D_UL2017.root", "egammaEffi_ptAbove20.txt_EGM2D_UL2018.root"};
    edm::FileInPath elec_GsfscalefacFileInPath(("Hcc/HccAna/data/"+elec_Gsfscalefac_name_161718[YEAR]).c_str());
    TFile *fElecScalFacGsf = TFile::Open(elec_GsfscalefacFileInPath.fullPath().c_str());
    hElecScaleFacGsf = (TH2F*)fElecScalFacGsf->Get("EGamma_SF2D");

    //string elec_GsfLowETscalefac_name_161718[3]= {"", "egammaEffi.txt_EGM2D_Moriond2018v1_runBCDEF_passingRECO_lowEt.root", "Ele_Reco_LowEt_2018.root"};//was previous
    string elec_GsfLowETscalefac_name_161718[4]= {"egammaEffi_ptBelow20.txt_EGM2D_UL2016preVFP.root", "egammaEffi_ptBelow20.txt_EGM2D_UL2016postVFP.root", "egammaEffi_ptBelow20.txt_EGM2D_UL2017.root", "egammaEffi_ptBelow20.txt_EGM2D_UL2018.root"};
    edm::FileInPath elec_GsfLowETscalefacFileInPath(("Hcc/HccAna/data/"+elec_GsfLowETscalefac_name_161718[YEAR]).c_str());
    TFile *fElecScalFacGsfLowET = TFile::Open(elec_GsfLowETscalefacFileInPath.fullPath().c_str());
    hElecScaleFacGsfLowET = (TH2F*)fElecScalFacGsfLowET->Get("EGamma_SF2D");

    //string mu_scalefac_name_161718[3] = {"final_HZZ_Moriond17Preliminary_v4.root", "ScaleFactors_mu_Moriond2018_final.root", "final_HZZ_muon_SF_2018RunA2D_ER_2702.root"};//was previous; 
//         string mu_scalefac_name_161718[3] = {"final_HZZ_SF_2016_legacy_mupogsysts.root", "final_HZZ_SF_2017_rereco_mupogsysts_3010.root", "final_HZZ_SF_2018_rereco_mupogsysts_3010.root"};
//         string mu_scalefac_name_161718[4] = {"final_HZZ_muon_SF_2016RunB2H_legacy_newLoose_newIso_paper.root", "final_HZZ_muon_SF_2016RunB2H_legacy_newLoose_newIso_paper.root", "final_HZZ_muon_SF_2017_newLooseIso_mupogSysts_paper.root", "final_HZZ_muon_SF_2018RunA2D_ER_newLoose_newIso_paper.root"};
        string mu_scalefac_name_161718[4] = {"final_HZZ_SF_2016UL_mupogsysts_newLoose.root","final_HZZ_SF_2016UL_mupogsysts_newLoose.root","final_HZZ_SF_2017UL_mupogsysts_newLoose.root","final_HZZ_SF_2018UL_mupogsysts_newLoose.root"};
    edm::FileInPath mu_scalefacFileInPath(("Hcc/HccAna/data/"+mu_scalefac_name_161718[YEAR]).c_str());
    TFile *fMuScalFac = TFile::Open(mu_scalefacFileInPath.fullPath().c_str());
    hMuScaleFac = (TH2F*)fMuScalFac->Get("FINAL");
    hMuScaleFacUnc = (TH2F*)fMuScalFac->Get("ERROR");

    //string pileup_name_161718[3] = {"puWeightsMoriond17_v2.root", "puWeightsMoriond18.root", "pu_weights_2018.root"};///was previous
//    string pileup_name_161718[3] = {"pu_weights_2016.root", "pu_weights_2017.root", "pu_weights_2018.root"};
    string pileup_name_161718[4] = {"pileup_UL_2016_1plusShift.root", "pileup_UL_2016_1plusShift.root", "pileup_UL_2017_1plusShift.root", "pileup_UL_2018_1plusShift.root"};
    edm::FileInPath pileup_FileInPath(("Hcc/HccAna/data/"+pileup_name_161718[YEAR]).c_str());
    TFile *f_pileup = TFile::Open(pileup_FileInPath.fullPath().c_str());
    h_pileup = (TH1D*)f_pileup->Get("weights");
    h_pileupUp = (TH1D*)f_pileup->Get("weights_varUp");
    h_pileupDn = (TH1D*)f_pileup->Get("weights_varDn");

    string bTagEffi_name_161718[4] = {"bTagEfficiencies_2016.root", "bTagEfficiencies_2016.root", "bTagEfficiencies_2017.root", "bTagEfficiencies_2018.root"};
    edm::FileInPath BTagEffiInPath(("Hcc/HccAna/data/"+bTagEffi_name_161718[YEAR]).c_str());
    TFile *fbTagEffi = TFile::Open(BTagEffiInPath.fullPath().c_str());
    hbTagEffi = (TH2F*)fbTagEffi->Get("eff_b_M_ALL");
    hcTagEffi = (TH2F*)fbTagEffi->Get("eff_c_M_ALL");
    hudsgTagEffi = (TH2F*)fbTagEffi->Get("eff_udsg_M_ALL");

    //BTag calibration
//     string csv_name_161718[4] = {"DeepCSV_2016LegacySF_V1.csv", "DeepCSV_2016LegacySF_V1.csv", "DeepCSV_106XUL17SF_V2p1.csv", "DeepCSV_106XUL18SF.csv"};
    string csv_name_161718[4] = {"DeepCSV_106XUL16preVFPSF_v1_hzz.csv", "DeepCSV_106XUL16postVFPSF_v2_hzz.csv", "wp_deepCSV_106XUL17_v3_hzz.csv", "wp_deepCSV_106XUL18_v2_hzz.csv"};
    edm::FileInPath btagfileInPath(("Hcc/HccAna/data/"+csv_name_161718[YEAR]).c_str());


bool validate = true; // HARDCODED --> IT COULD BE FALSE!!!
    BTagCalibration calib("DeepCSV", btagfileInPath.fullPath().c_str(), validate);
    reader = new BTagCalibrationReader(BTagEntry::OP_MEDIUM,  // operating point
                                       "central",             // central sys type
                                       {"up", "down"});      // other sys types
   

    reader->load(calib,                // calibration instance
                BTagEntry::FLAV_B,    // btag flavour
                "comb");               // measurement type

    if(year==2018)    {EleBDT_name_161718 = "ElectronMVAEstimatorRun2Fall17IsoV1Values"; BTagCut=0.4184; heepID_name_161718 = "heepElectronID-HEEPV70";}
    if(year==2017)    {EleBDT_name_161718 = "ElectronMVAEstimatorRun2Summer17ULIdIsoValues"; BTagCut=0.4941; heepID_name_161718 = "heepElectronID-HEEPV70";}
    if(year==20165 || year==20160)    {EleBDT_name_161718 = "ElectronMVAEstimatorRun2Summer16ULIdIsoValues"; BTagCut=0.6321; heepID_name_161718 = "heepElectronID-HEEPV70";}


}



HccAna::~HccAna()
{
    //destructor --- don't do anything here  
}


// ------------ method called for each event  ------------
void
HccAna::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{

    using namespace edm;
    using namespace std;
    using namespace pat;
    using namespace trigger;
    using namespace EwkCorrections;

// if(iEvent.id().event() > 709310) 
// 	std::cout<<"PIPPO\t"<<iEvent.id().event()<<"\n";
        
    nEventsTotal += 1.0;

    Run = iEvent.id().run();
    Event = iEvent.id().event();
    LumiSect = iEvent.id().luminosityBlock();

    if (verbose) {
       cout<<"Run: " << Run << ",Event: " << Event << ",LumiSect: "<<LumiSect<<endl;
    }

    // ======= Get Collections ======= //
    if (verbose) {cout<<"getting collections"<<endl;}

    // trigger collection
    edm::Handle<edm::TriggerResults> trigger;
    iEvent.getByToken(triggerSrc_,trigger);
    const edm::TriggerNames trigNames = iEvent.triggerNames(*trigger);

    // trigger Objects
    edm::Handle<pat::TriggerObjectStandAloneCollection> triggerObjects;
    iEvent.getByToken(triggerObjects_, triggerObjects);

    // vertex collection
    edm::Handle<reco::VertexCollection> vertex;
    iEvent.getByToken(vertexSrc_,vertex);

    // electron collection
    edm::Handle<edm::View<pat::Electron> > electrons;
    iEvent.getByToken(elecSrc_,electrons);
    if (verbose) cout<<electrons->size()<<" total electrons in the collection"<<endl;

    // electron before scale/smearing corrections
    edm::Handle<edm::View<pat::Electron> > electronsUnS;
    iEvent.getByToken(elecUnSSrc_,electronsUnS);

    // muon collection
    edm::Handle<edm::View<pat::Muon> > muons;
    iEvent.getByToken(muonSrc_,muons);
    if (verbose) cout<<muons->size()<<" total muons in the collection"<<endl;

    // tau collection
    /*edm::Handle<edm::View<pat::Tau> > taus;
    iEvent.getByToken(tauSrc_,taus);
    if (verbose) cout<<taus->size()<<" total taus in the collection"<<endl;

    // photon collection 
    edm::Handle<edm::View<pat::Photon> > photons;
    iEvent.getByToken(photonSrc_,photons);
    if (verbose) cout<<photons->size()<<" total photons in the collection"<<endl;*/
  
    // met collection 
    edm::Handle<edm::View<pat::MET> > mets;
    iEvent.getByToken(metSrc_,mets);
    
    // Rho Correction
    /*edm::Handle<double> eventRhoMu;
    iEvent.getByToken(muRhoSrc_,eventRhoMu);
    muRho = *eventRhoMu;

    edm::Handle<double> eventRhoE;
    iEvent.getByToken(elRhoSrc_,eventRhoE);
    elRho = *eventRhoE;

    edm::Handle<double> eventRhoSUS;
    iEvent.getByToken(rhoSrcSUS_,eventRhoSUS);
    rhoSUS = *eventRhoSUS;*/

    // Conversions
    edm::Handle< std::vector<reco::Conversion> > theConversions;
    iEvent.getByToken(conversionSrc_, theConversions);
 
    // Beam Spot
    edm::Handle<reco::BeamSpot> beamSpot;
    iEvent.getByToken(beamSpotSrc_,beamSpot);
    const reco::BeamSpot BS = *beamSpot;

    // Particle Flow Cands
    edm::Handle<pat::PackedCandidateCollection> pfCands;
    iEvent.getByToken(pfCandsSrc_,pfCands);

    // FSR Photons
    edm::Handle<edm::View<pat::PFParticle> > photonsForFsr;
    iEvent.getByToken(fsrPhotonsSrc_,photonsForFsr);
  
    // Jets
    edm::Handle<edm::View<pat::Jet> > jets;
    iEvent.getByToken(jetSrc_,jets);
		
    // Puppi AK4jets with ParticleNet taggers
    edm::Handle<edm::View<pat::Jet> > AK4PuppiJets;
    iEvent.getByToken(AK4PuppiJetSrc_ ,AK4PuppiJets);

	// Puppi AK8jets with ParticleNet taggers
	     edm::Handle<edm::View<pat::Jet> > AK8PuppiJets;
	    iEvent.getByToken(AK8PuppiJetSrc_ ,AK8PuppiJets);
	
    //L1 Jets                                       
    edm::Handle<BXVector<l1t::Jet>> bxvCaloJets;
    iEvent.getByToken(bxvCaloJetSrc_,bxvCaloJets);
	 
    //L1 Muons
    edm::Handle<BXVector<l1t::Muon>> bxvCaloMuons;
    iEvent.getByToken(bxvCaloMuonSrc_,bxvCaloMuons);
		 
    //L1 HT Sum                                       
    edm::Handle<BXVector<l1t::EtSum>> bxvCaloHT;
    iEvent.getByToken(bxvCaloHTSrc_,bxvCaloHT);

    //HLT hltAK4PFJetsCorrectedSrc
    /*edm::Handle<edm::View<reco::PFJet>>  hltAK4PFJetsCorrected;
    iEvent.getByToken(hltAK4PFJetsCorrectedSrc_, hltAK4PFJetsCorrected);*/

    /*if (!hltAK4PFJetsCorrected.isValid()) {
        edm::LogWarning("ParticleNetJetTagMonitor") << "Jet collection not valid, will skip the event \n";
        return;
    }*/
		
    //HLT jet for B Tag
    /*edm::Handle<edm::View<reco::PFJet>>  hltjetsForBTag;
    iEvent.getByToken(hltPFJetForBtagSrc_, hltjetsForBTag);

    if (!hltjetsForBTag.isValid()) {
      edm::LogWarning("ParticleNetJetTagMonitor") << "Jet collection not valid, will skip the event \n";
      return;
    }*/
                                
    //edm::Handle<std::vector<reco::PFJet>>  hltjets;
    //iEvent.getByToken(hltPFJetForBtagSrc_, hltjets);

    /*edm::Handle<reco::JetTagCollection> pfJetTagCollectionParticleNetprobc;
    iEvent.getByToken(pfJetTagCollectionParticleNetprobcSrc_, pfJetTagCollectionParticleNetprobc);

    if (!pfJetTagCollectionParticleNetprobc.isValid()) {
      edm::LogWarning("ParticleNetJetTagMonitor") << "HLT Jet tags collection not valid, will skip event \n";
      return;
    }
		
    edm::Handle<reco::JetTagCollection> pfJetTagCollectionParticleNetprobb;
    iEvent.getByToken(pfJetTagCollectionParticleNetprobbSrc_, pfJetTagCollectionParticleNetprobb);

    if (!pfJetTagCollectionParticleNetprobb.isValid()) {
      edm::LogWarning("ParticleNetJetTagMonitor") << "HLT Jet tags collection not valid, will skip event \n";
      return;
    }
		
    edm::Handle<reco::JetTagCollection> pfJetTagCollectionParticleNetprobuds;
    iEvent.getByToken(pfJetTagCollectionParticleNetprobudsSrc_, pfJetTagCollectionParticleNetprobuds);

    if (!pfJetTagCollectionParticleNetprobuds.isValid()) {
      edm::LogWarning("ParticleNetJetTagMonitor") << "HLT Jet tags collection not valid, will skip event \n";
      return;
    }
		
    edm::Handle<reco::JetTagCollection> pfJetTagCollectionParticleNetprobg;
    iEvent.getByToken(pfJetTagCollectionParticleNetprobgSrc_, pfJetTagCollectionParticleNetprobg);

    if (!pfJetTagCollectionParticleNetprobg.isValid()) {
      edm::LogWarning("ParticleNetJetTagMonitor") << "HLT Jet tags collection not valid, will skip event \n";
      return;
    }
		
    edm::Handle<reco::JetTagCollection> pfJetTagCollectionParticleNetprobtauh;
    iEvent.getByToken(pfJetTagCollectionParticleNetprobtauhSrc_, pfJetTagCollectionParticleNetprobtauh);

    if (!pfJetTagCollectionParticleNetprobtauh.isValid()) {
      edm::LogWarning("ParticleNetJetTagMonitor") << "HLT Jet tags collection not valid, will skip event \n";
      return;
    }*/
    /*if (iEvent.getByToken(hltPFJetForBtagSrc_, hltjets)) {
    //get PF jet tags
       edm::Handle<reco::JetTagCollection> pfJetTagCollection;
       bool haveJetTags = false;
       if (iEvent.getByToken(pfJetTagCollectionSrc_, pfJetTagCollection)) {
         haveJetTags = true;
       }
	  }
      cout<<"haveJetTags"<<haveJetTags<<endl;*/
		
    if (!jecunc) {



//        edm::ESHandle<JetCorrectorParametersCollection> jetCorrParameterSet;
//        iSetup.get<JetCorrectionsRecord>().get("AK4PFchs", jetCorrParameterSet);


auto const& jetCorrParameterSet = iSetup.getData(mPayloadToken);//"AK4PFchs");
std::vector<JetCorrectorParametersCollection::key_type> keys;
jetCorrParameterSet.validKeys(keys);


//        const JetCorrectorParameters& jetCorrParameters = (*jetCorrParameterSet)["Uncertainty"]; 
        JetCorrectorParameters jetCorrParameters = (jetCorrParameterSet)["Uncertainty"];





        jecunc.reset(new JetCorrectionUncertainty(jetCorrParameters));
    }


//JME::JetResolution::Token resolution_pt_token;
//res_pt_config = "AK4PFchs_pt";
//resolution_pt_token = esConsumes(edm::ESInputTag("", res_pt_config));
//resolution_pt = JME::JetResolution::get(iSetup, resolution_pt_token);

//JME::JetResolution::Token resolution_phi_token;
//res_phi_config = "AK4PFchs_phi";
//resolution_phi_token = esConsumes(edm::ESInputTag("", res_phi_config));
//resolution_phi = JME::JetResolution::get(iSetup, resolution_phi_token);

//JME::JetResolutionScaleFactor::Token resolution_sf_token;
//res_sf_config = "AK4PFchs_sf";
//resolution_sf_token = esConsumes(edm::ESInputTag("", res_sf_config));
//resolution_sf = JME::JetResolutionScaleFactor::get(iSetup, resolution_sf_token);



    edm::Handle<edm::ValueMap<float> > qgHandle;
    iEvent.getByToken(qgTagSrc_, qgHandle);

    edm::Handle<edm::ValueMap<float> > axis2Handle;
    iEvent.getByToken(axis2Src_, axis2Handle);

    edm::Handle<edm::ValueMap<int> > multHandle;
    iEvent.getByToken(multSrc_, multHandle);

    edm::Handle<edm::ValueMap<float> > ptDHandle;
    iEvent.getByToken(ptDSrc_, ptDHandle);
 
    edm::Handle<edm::View<pat::Jet> > mergedjets;
    iEvent.getByToken(mergedjetSrc_,mergedjets);

    // GEN collections
    edm::Handle<reco::GenParticleCollection> prunedgenParticles;
    iEvent.getByToken(prunedgenParticlesSrc_, prunedgenParticles);

    edm::Handle<edm::View<pat::PackedGenParticle> > packedgenParticles;
    iEvent.getByToken(packedgenParticlesSrc_, packedgenParticles);
    
    edm::Handle<edm::View<reco::GenJet> > genJets;
    iEvent.getByToken(genJetsSrc_, genJets);
    
    edm::Handle<GenEventInfoProduct> genEventInfo;
    iEvent.getByToken(generatorSrc_,genEventInfo);
    
    //vector<edm::Handle<LHEEventProduct> > lheInfos;
    //iEvent.getManyByType(lheInfos); // using this method because the label is not always the same (e.g. "source" in the ttH sample)

    edm::Handle<LHEEventProduct> lheInfo;
    iEvent.getByToken(lheInfoSrc_, lheInfo);

    edm::Handle<BXVector<GlobalAlgBlk>> uGtAlgs;
    iEvent.getByToken(algTok_, uGtAlgs);

    if (!uGtAlgs.isValid()) {
        cout << "Cannot find uGT readout record." << endl;
    }


//    if (isMC) {    
//        edm::Handle< double > theprefweight;
//            iEvent.getByToken(prefweight_token_, theprefweight ) ;
 //               prefiringWeight =(*theprefweight);
//    }
//    else
        prefiringWeight =1.0;
    
    // ============ Initialize Variables ============= //

    // Event Variables
    if (verbose) {cout<<"clear variables"<<endl;}
    nVtx = -1.0; nInt = -1.0;
    finalState = -1;
    triggersPassed="";
		puN=-1;
    passedTrig=false; passedFullSelection=false; passedZ4lSelection=false; passedQCDcut=false; 
    Trigger_l1name.clear();
    Trigger_l1decision.clear();
    Trigger_hltname.clear();
    Trigger_hltdecision.clear();

    // Event Weights
    genWeight=1.0; pileupWeight=1.0; pileupWeightUp=1.0; pileupWeightDn=1.0; dataMCWeight=1.0; eventWeight=1.0;
    k_qqZZ_qcd_dPhi = 1.0; k_qqZZ_qcd_M = 1.0; k_qqZZ_qcd_Pt = 1.0; k_qqZZ_ewk = 1.0;

    qcdWeights.clear(); nnloWeights.clear(); pdfWeights.clear();
    pdfRMSup=1.0; pdfRMSdown=1.0; pdfENVup=1.0; pdfENVdown=1.0;

    //lepton variables
		lep_pt.clear(); lep_eta.clear(); lep_phi.clear(); lep_mass.clear(); lep_ID.clear();    
		
		ALLlep_pt.clear(); ALLlep_eta.clear(); ALLlep_phi.clear(); ALLlep_mass.clear(); ALLlep_id.clear();
        	AK4lep_pt.clear(); AK4lep_eta.clear(); AK4lep_phi.clear(); AK4lep_mass.clear(); AK4lep_id.clear();
    /*lep_d0BS.clear();
    lep_d0PV.clear();
	lep_numberOfValidPixelHits.clear();
	lep_trackerLayersWithMeasurement.clear();

	lep_pt_genFromReco.clear();
    lep_pt_UnS.clear(); lep_pterrold_UnS.clear();
    lep_pt.clear(); lep_pterr.clear(); lep_pterrold.clear(); 
    lep_p.clear(); lep_ecalEnergy.clear(); lep_isEB.clear(); lep_isEE.clear();
	lep_errPre_Scale.clear(); lep_errPost_Scale.clear(); lep_errPre_noScale.clear(); lep_errPost_noScale.clear();
    lep_eta.clear(); lep_phi.clear(); lep_mass.clear(); 
    lepFSR_pt.clear(); lepFSR_eta.clear(); lepFSR_phi.clear(); lepFSR_mass.clear(); lepFSR_ID.clear(); 
    for (int i=0; i<4; ++i) {lep_Hindex[i]=-1;}


    lep_genindex.clear(); lep_id.clear(); lep_dataMC.clear(); lep_dataMCErr.clear();
	dataMC_VxBS.clear(); dataMCErr_VxBS.clear();
    lep_matchedR03_PdgId.clear(); lep_matchedR03_MomId.clear(); lep_matchedR03_MomMomId.clear();
    lep_mva.clear(); lep_ecalDriven.clear(); 
    lep_tightId.clear(); lep_tightIdSUS.clear(); lep_tightIdHiPt.clear(); //lep_tightId_old.clear();
    lep_Sip.clear(); lep_IP.clear(); 
    lep_isoNH.clear(); lep_isoCH.clear(); lep_isoPhot.clear(); lep_isoPU.clear(); lep_isoPUcorr.clear(); 
    lep_RelIso.clear(); lep_RelIsoNoFSR.clear(); lep_MiniIso.clear();
    lep_ptRatio.clear(); lep_ptRel.clear();
    lep_missingHits.clear();
    lep_filtersMatched.clear();    
    nisoleptons=0;
    

    //tau variables //L1 Jets                                       
    tau_id.clear(); tau_pt.clear(); tau_eta.clear(); tau_phi.clear(); tau_mass.clear(); 

    // photon variables
    pho_pt.clear(); pho_eta.clear(); pho_phi.clear(); photonCutBasedIDLoose.clear(); 

    H_pt.clear(); H_eta.clear(); H_phi.clear(); H_mass.clear(); 
    H_noFSR_pt.clear(); H_noFSR_eta.clear(); H_noFSR_phi.clear(); H_noFSR_mass.clear(); 
    mass4l=-1.0; mass4l_noFSR=-1.0; mass4e=-1.0; mass4mu=-1.0; mass2e2mu=-1.0; pT4l=-1.0; eta4l=9999.0; phi4l=9999.0; rapidity4l=9999.0;
    cosTheta1=9999.0; cosTheta2=9999.0; cosThetaStar=9999.0; Phi=9999.0; Phi1=9999.0;
    mass3l=-1.0;
    
    // Z candidate variables
    Z_pt.clear(); Z_eta.clear(); Z_phi.clear(); Z_mass.clear(); 
    Z_noFSR_pt.clear(); Z_noFSR_eta.clear(); Z_noFSR_phi.clear(); Z_noFSR_mass.clear(); 
    for (int i=0; i<2; ++i) {Z_Hindex[i]=-1;}
    massZ1=-1.0; massZ1_Z1L=-1.0; massZ2=-1.0; pTZ1=-1.0; pTZ2=-1.0;*/
		
    //hlt Jets for b tag
    hltjetForBTag_pt.clear();
    hltjetForBTag_eta.clear();
    hltjetForBTag_phi.clear();
    hltjetForBTag_mass.clear();
    hltParticleNetONNXJetTags_probb.clear(); hltParticleNetONNXJetTags_probc.clear(); hltParticleNetONNXJetTags_probuds.clear(); hltParticleNetONNXJetTags_probg.clear(); hltParticleNetONNXJetTags_probtauh.clear();
	
    //hltAK4PFJetsCorrected    
		
    hltAK4PFJetsCorrected_pt.clear();
    hltAK4PFJetsCorrected_eta.clear();
    hltAK4PFJetsCorrected_phi.clear();
    hltAK4PFJetsCorrected_mass.clear();

    // Puppi AK4jets with ParticleNet taggers
    AK4PuppiJets_pt.clear();
    AK4PuppiJets_eta.clear();
    AK4PuppiJets_phi.clear();
    AK4PuppiJets_mass.clear();

    jet_pfParticleNetAK4JetTags_probb.clear(); jet_pfParticleNetAK4JetTags_probc.clear(); jet_pfParticleNetAK4JetTags_probuds.clear(); jet_pfParticleNetAK4JetTags_probg.clear(); jet_pfParticleNetAK4JetTags_probtauh.clear();
    
    // Puppi AK8jets with ParticleNet and DeepDoubleX taggers
    AK8PuppiJets_pt.clear();
    AK8PuppiJets_eta.clear();
    AK8PuppiJets_phi.clear();
    AK8PuppiJets_mass.clear();

    jet_pfParticleNetJetTags_probZbb.clear(); jet_pfParticleNetJetTags_probZcc.clear(); jet_pfParticleNetJetTags_probZqq.clear(); jet_pfParticleNetJetTags_probQCDbb .clear();  jet_pfParticleNetJetTags_probQCDcc.clear(); jet_pfParticleNetJetTags_probQCDb.clear(); jet_pfParticleNetJetTags_probQCDc.clear(); jet_pfParticleNetJetTags_probQCDothers.clear(); jet_pfParticleNetJetTags_probHbb.clear(); jet_pfParticleNetJetTags_probHcc.clear(); jet_pfParticleNetJetTags_probHqqqq.clear(); 
    jet_pfMassDecorrelatedParticleNetJetTags_probXbb.clear(); jet_pfMassDecorrelatedParticleNetJetTags_probXcc.clear(); jet_pfMassDecorrelatedParticleNetJetTags_probXqq.clear(); jet_pfMassDecorrelatedParticleNetJetTags_probQCDbb.clear(); jet_pfMassDecorrelatedParticleNetJetTags_probQCDcc.clear(); jet_pfMassDecorrelatedParticleNetJetTags_probQCDb.clear(); jet_pfMassDecorrelatedParticleNetJetTags_probQCDc.clear(); jet_pfMassDecorrelatedParticleNetJetTags_probQCDothers.clear();
    jet_pfMassIndependentDeepDoubleBvLV2JetTags_probHbb.clear(); jet_pfMassIndependentDeepDoubleCvLV2JetTags_probHcc.clear(); jet_pfMassIndependentDeepDoubleCvBV2JetTags_probHcc.clear();
    
    // MET
    met=-1.0; met_phi=9999.0;
    met_jesup=-1.0; met_phi_jesup=9999.0; met_jesdn=-1.0; met_phi_jesdn=9999.0; 
    met_uncenup=-1.0; met_phi_uncenup=9999.0; met_uncendn=-1.0; met_phi_uncendn=9999.0; 

    // Jets
    jet_pt.clear(); jet_eta.clear(); jet_phi.clear(); jet_mass.clear(); jet_pt_raw.clear(); 
    jet_jesup_pt.clear(); jet_jesup_eta.clear(); jet_jesup_phi.clear(); jet_jesup_mass.clear(); 
    jet_jesdn_pt.clear(); jet_jesdn_eta.clear(); jet_jesdn_phi.clear(); jet_jesdn_mass.clear(); 
    jet_jerup_pt.clear(); jet_jerup_eta.clear(); jet_jerup_phi.clear(); jet_jerup_mass.clear(); 
    jet_jerdn_pt.clear(); jet_jerdn_eta.clear(); jet_jerdn_phi.clear(); jet_jerdn_mass.clear(); 
    jet_csvv2_.clear();
    jet_csv_cTag_vsL.clear();
    jet_csv_cTag_vsB.clear();
    jet_pumva.clear(); jet_csvv2.clear(); jet_isbtag.clear();
	jet_pfDeepCSVJetTags_probb.clear(); jet_pfDeepFlavourJetTags_probbb.clear(); jet_pfDeepFlavourJetTags_probc.clear(); jet_pfDeepFlavourJetTags_probuds.clear();
    jet_hadronFlavour.clear(); jet_partonFlavour.clear();
    jet_QGTagger.clear(); jet_QGTagger_jesup.clear(); jet_QGTagger_jesdn.clear(); 
    jet_relpterr.clear(); jet_phierr.clear();
    jet_bTagEffi.clear();
    jet_cTagEffi.clear();
    jet_udsgTagEffi.clear();
    jet_axis2.clear(); jet_ptD.clear(); jet_mult.clear();

    jet_iscleanH4l.clear();
    jet1index=-1; jet2index=-1;
    jet_jesup_iscleanH4l.clear(); jet_jesdn_iscleanH4l.clear(); 
    jet_jerup_iscleanH4l.clear(); jet_jerdn_iscleanH4l.clear();

    njets_pt30_eta4p7=0;
    njets_pt30_eta4p7_jesup=0; njets_pt30_eta4p7_jesdn=0;
    njets_pt30_eta4p7_jerup=0; njets_pt30_eta4p7_jerdn=0;

    njets_pt30_eta2p5=0;
    njets_pt30_eta2p5_jesup=0; njets_pt30_eta2p5_jesdn=0;
    njets_pt30_eta2p5_jerup=0; njets_pt30_eta2p5_jerdn=0;

    nbjets_pt30_eta4p7=0; nvjets_pt40_eta2p4=0;

    pt_leadingjet_pt30_eta4p7=-1.0;
    pt_leadingjet_pt30_eta4p7_jesup=-1.0; pt_leadingjet_pt30_eta4p7_jesdn=-1.0;
    pt_leadingjet_pt30_eta4p7_jerup=-1.0; pt_leadingjet_pt30_eta4p7_jerdn=-1.0;

    pt_leadingjet_pt30_eta2p5=-1.0;
    pt_leadingjet_pt30_eta2p5_jesup=-1.0; pt_leadingjet_pt30_eta2p5_jesdn=-1.0;
    pt_leadingjet_pt30_eta2p5_jerup=-1.0; pt_leadingjet_pt30_eta2p5_jerdn=-1.0;

    absrapidity_leadingjet_pt30_eta4p7=-1.0;
    absrapidity_leadingjet_pt30_eta4p7_jesup=-1.0; absrapidity_leadingjet_pt30_eta4p7_jesdn=-1.0;
    absrapidity_leadingjet_pt30_eta4p7_jerup=-1.0; absrapidity_leadingjet_pt30_eta4p7_jerdn=-1.0;

    absdeltarapidity_hleadingjet_pt30_eta4p7=-1.0;
    absdeltarapidity_hleadingjet_pt30_eta4p7_jesup=-1.0; absdeltarapidity_hleadingjet_pt30_eta4p7_jesdn=-1.0;
    absdeltarapidity_hleadingjet_pt30_eta4p7_jerup=-1.0; absdeltarapidity_hleadingjet_pt30_eta4p7_jerdn=-1.0;

    DijetMass=-1.0; DijetDEta=9999.0; DijetFisher=9999.0;
    
    mergedjet_iscleanH4l.clear();
    mergedjet_pt.clear(); mergedjet_eta.clear(); mergedjet_phi.clear(); mergedjet_mass.clear();
    mergedjet_L1.clear();
    mergedjet_softdropmass.clear(); mergedjet_prunedmass.clear();
    mergedjet_tau1.clear(); mergedjet_tau2.clear();
    mergedjet_btag.clear();

    mergedjet_nsubjet.clear();
    mergedjet_subjet_pt.clear(); mergedjet_subjet_eta.clear(); 
    mergedjet_subjet_phi.clear(); mergedjet_subjet_mass.clear();
    mergedjet_subjet_btag.clear();
    mergedjet_subjet_partonFlavour.clear(); mergedjet_subjet_hadronFlavour.clear();

    L1jet_pt.clear(); L1jet_eta.clear(); L1jet_phi.clear(); L1jet_mass.clear();
    L1muon_pt.clear(); L1muon_eta.clear(); L1muon_phi.clear(); L1muon_mass.clear(); L1muon_qual.clear();

    
    // FSR Photons
    /*nFSRPhotons=0;
    fsrPhotons_lepindex.clear(); fsrPhotons_pt.clear(); fsrPhotons_pterr.clear(); 
    fsrPhotons_eta.clear(); fsrPhotons_phi.clear();
    fsrPhotons_dR.clear(); fsrPhotons_iso.clear();
    allfsrPhotons_dR.clear(); allfsrPhotons_pt.clear(); allfsrPhotons_iso.clear();

    // Z4l? FIXME
    theta12=9999.0; theta13=9999.0; theta14=9999.0;
    minM3l=-1.0; Z4lmaxP=-1.0; minDeltR=9999.0; m3l_soft=-1.0;
    minMass2Lep=-1.0; maxMass2Lep=-1.0;
    thetaPhoton=9999.0; thetaPhotonZ=9999.0;*/

    // -------------------------
    // GEN level information
    // ------------------------- 

    //Event variables
    GENfinalState=-1;

    // lepton variables
    /*GENlep_pt.clear(); GENlep_eta.clear(); GENlep_phi.clear(); GENlep_mass.clear();
    GENlep_id.clear(); GENlep_status.clear(); GENlep_MomId.clear(); GENlep_MomMomId.clear();
    for (int i=0; i<4; ++i) {GENlep_Hindex[i]=-1;};//position of Higgs candidate leptons in lep_p4: 0 = Z1 lead, 1 = Z1 sub, 2 = Z2 lead, 3 = Z3 sub
    GENlep_isoCH.clear(); GENlep_isoNH.clear(); GENlep_isoPhot.clear(); GENlep_RelIso.clear();

    // Higgs candidate variables (calculated using selected gen leptons)
    GENH_pt.clear(); GENH_eta.clear(); GENH_phi.clear(); GENH_mass.clear();
    GENmass4l=-1.0; GENmassZ1=-1.0; GENmassZ2=-1.0; GENpT4l=-1.0; GENeta4l=9999.0; GENrapidity4l=9999.0; GENMH=-1.0;
    GENcosTheta1=9999.0; GENcosTheta2=9999.0; GENcosThetaStar=9999.0; GENPhi=9999.0; GENPhi1=9999.0;

    // Z candidate variables
    GENZ_DaughtersId.clear(); GENZ_MomId.clear();
    GENZ_pt.clear(); GENZ_eta.clear(); GENZ_phi.clear(); GENZ_mass.clear();
    GENmassZ1=-1.0; GENmassZ2=-1.0; GENpTZ1=-1.0; GENpTZ2=-1.0, GENdPhiZZ=9999.0, GENmassZZ=-1.0, GENpTZZ=-1.0;

    // Higgs variables directly from GEN particle
    GENHmass=-1.0;*/

    // Jets
    GENjet_pt.clear(); GENjet_eta.clear(); GENjet_phi.clear(); GENjet_mass.clear(); 
    GENnjets_pt30_eta4p7=0;
    GENnjets_pt30_eta2p5=0;
    GENpt_leadingjet_pt30_eta4p7=-1.0; GENabsrapidity_leadingjet_pt30_eta4p7=-1.0; GENabsdeltarapidity_hleadingjet_pt30_eta4p7=-1.0;
    GENpt_leadingjet_pt30_eta2p5=-1.0; 
    lheNb=0; lheNj=0; nGenStatus2bHad=0;

    //quarks
    quark_pt.clear(); quark_eta.clear(); quark_phi.clear(); quark_flavour.clear(); quark_VBF.clear();
    quark_pt_float.clear(); quark_eta_float.clear(); quark_phi_float.clear();
    //

    if (verbose) {cout<<"clear other variables"<<endl; }
    // Resolution
    //massErrorUCSD=-1.0; massErrorUCSDCorr=-1.0; massErrorUF=-1.0; massErrorUFCorr=-1.0; massErrorUFADCorr=-1.0;

    // Event Category
    EventCat=-1;

    // Global variables not stored in tree
    /*lep_ptreco.clear(); lep_ptid.clear(); lep_ptindex.clear();
    recoMuons.clear(); recoElectrons.clear(); fsrPhotons.clear(); recoElectronsUnS.clear();
    HVec.SetPtEtaPhiM(0.0,0.0,0.0,0.0);
    HVecNoFSR.SetPtEtaPhiM(0.0,0.0,0.0,0.0);
    Z1Vec.SetPtEtaPhiM(0.0,0.0,0.0,0.0);
    Z2Vec.SetPtEtaPhiM(0.0,0.0,0.0,0.0);
    GENZ1Vec.SetPtEtaPhiM(0.0,0.0,0.0,0.0);
    GENZ2Vec.SetPtEtaPhiM(0.0,0.0,0.0,0.0);
    foundHiggsCandidate = false; 
    jet1pt=-1.0; jet2pt=-1.0;

    // Float vectors
    lep_d0BS_float.clear();
    lep_d0PV_float.clear();

	lep_numberOfValidPixelHits_float.clear();
	lep_trackerLayersWithMeasurement_float.clear();

	lep_pt_genFromReco_float.clear();

    lep_pt_UnS_float.clear(); lep_pterrold_UnS_float.clear();
    lep_errPre_Scale_float.clear();
	lep_errPost_Scale_float.clear();
	lep_errPre_noScale_float.clear();
	lep_errPost_noScale_float.clear();

    lep_pt_float.clear(); lep_pterr_float.clear(); lep_pterrold_float.clear(); 
    lep_p_float.clear(); lep_ecalEnergy_float.clear();  
    lep_eta_float.clear(); lep_phi_float.clear(); lep_mass_float.clear();
    lepFSR_pt_float.clear(); lepFSR_eta_float.clear(); lepFSR_phi_float.clear(); lepFSR_mass_float.clear();
    tau_pt_float.clear(); tau_eta_float.clear(); tau_phi_float.clear(); tau_mass_float.clear();    
    pho_pt_float.clear(); pho_eta_float.clear(); pho_phi_float.clear(); photonCutBasedIDLoose_float.clear();
    H_pt_float.clear(); H_eta_float.clear(); H_phi_float.clear(); H_mass_float.clear();
    H_noFSR_pt_float.clear(); H_noFSR_eta_float.clear(); H_noFSR_phi_float.clear(); H_noFSR_mass_float.clear();
    Z_pt_float.clear(); Z_eta_float.clear(); Z_phi_float.clear(); Z_mass_float.clear();
    Z_noFSR_pt_float.clear(); Z_noFSR_eta_float.clear(); Z_noFSR_phi_float.clear(); Z_noFSR_mass_float.clear();*/
		
    lep_pt_float.clear(); lep_eta_float.clear(); lep_phi_float.clear(); lep_mass_float.clear();

    hltjetForBTag_pt_float.clear(); hltjetForBTag_eta_float.clear(); hltjetForBTag_phi_float.clear(); hltjetForBTag_mass_float.clear();
    hltAK4PFJetsCorrected_pt_float.clear(); hltAK4PFJetsCorrected_eta_float.clear(); hltAK4PFJetsCorrected_phi_float.clear(); hltAK4PFJetsCorrected_mass_float.clear();

    jet_pt_float.clear(); jet_eta_float.clear(); jet_phi_float.clear(); jet_mass_float.clear(); jet_pt_raw_float.clear(); 
    jet_csv_cTag_vsL_float.clear(); jet_csv_cTag_vsB_float.clear();
    jet_jesup_pt_float.clear(); jet_jesup_eta_float.clear(); jet_jesup_phi_float.clear(); jet_jesup_mass_float.clear();
    jet_jesdn_pt_float.clear(); jet_jesdn_eta_float.clear(); jet_jesdn_phi_float.clear(); jet_jesdn_mass_float.clear();
    jet_jerup_pt_float.clear(); jet_jerup_eta_float.clear(); jet_jerup_phi_float.clear(); jet_jerup_mass_float.clear();
    jet_jerdn_pt_float.clear(); jet_jerdn_eta_float.clear(); jet_jerdn_phi_float.clear();  jet_jerdn_mass_float.clear();
    fsrPhotons_pt_float.clear(); fsrPhotons_pterr_float.clear(); fsrPhotons_eta_float.clear(); fsrPhotons_phi_float.clear(); fsrPhotons_mass_float.clear();
    L1jet_pt_float.clear(); L1jet_eta_float.clear(); L1jet_phi_float.clear(); L1jet_mass_float.clear();
    L1muon_pt_float.clear(); L1muon_eta_float.clear(); L1muon_phi_float.clear(); L1muon_mass_float.clear();

    AK4PuppiJets_pt_float.clear(); AK4PuppiJets_eta_float.clear(); AK4PuppiJets_phi_float.clear(); AK4PuppiJets_mass_float.clear();
	AK8PuppiJets_pt_float.clear(); AK8PuppiJets_eta_float.clear(); AK8PuppiJets_phi_float.clear(); AK8PuppiJets_mass_float.clear();


    // ====================== Do Analysis ======================== //
// if(iEvent.id().event() > 709310) 
// 	std::cout<<"PIPPO\tdopo inizializzazione\n";
		//cout<<"aaa"<<endl;
    std::map<int, TLorentzVector> fsrmap;
    vector<reco::Candidate*> selectedLeptons;
    std::map<unsigned int, TLorentzVector> selectedFsrMap;

    fsrmap.clear(); selectedFsrMap.clear(); selectedLeptons.clear();

    if (verbose) cout<<"start pileup reweighting"<<endl;
    // PU information
    if(isMC && reweightForPU) {        
       edm::Handle<std::vector< PileupSummaryInfo > >  PupInfo;
        iEvent.getByToken(pileupSrc_, PupInfo);
				puN = PupInfo->begin()->getTrueNumInteractions();      

        if (verbose) cout<<"got pileup info"<<endl;

        std::vector<PileupSummaryInfo>::const_iterator PVI;      
        int npv = -1;
        for(PVI = PupInfo->begin(); PVI != PupInfo->end(); ++PVI) {
            int BX = PVI->getBunchCrossing();
            if(BX == 0) { npv = PVI->getTrueNumInteractions(); continue;}
        }        
        if (verbose) cout<<"N true interations = "<<npv<<endl;
        nInt = npv;
        //pileupWeight = pileUp.getPUWeight(npv,PUVersion);
        pileupWeight = pileUp.getPUWeight(h_pileup,npv);
//std::cout<<pileupWeight<<"\t"<<npv<<std::endl;
        pileupWeightUp = pileUp.getPUWeight(h_pileupUp,npv);
        pileupWeightDn = pileUp.getPUWeight(h_pileupDn,npv);
        if (verbose) cout<<"pileup weight = "<<pileupWeight<<", filling histograms"<<endl;
        histContainer_["NINTERACT"]->Fill(npv);
        histContainer_["NINTERACT_RW"]->Fill(npv,pileupWeight);
    } else { pileupWeight = 1.0;}   

    if (verbose) {cout<<"finished pileup reweighting"<<endl; }
    
    if(isMC) {
        float tmpWeight = genEventInfo->weight();
        genWeight = (tmpWeight > 0 ? 1.0 : -1.0);
        if (verbose) {cout<<"tmpWeight: "<<tmpWeight<<"; genWeight: "<<genWeight<<endl;}        
        double rms = 0.0;

        //std::cout<<"tmpWeight: "<<tmpWeight<<std::endl;

        if(lheInfo.isValid()){
            
            for(unsigned int i = 0; i < lheInfo->weights().size(); i++) {

                tmpWeight = genEventInfo->weight();
                tmpWeight *= lheInfo->weights()[i].wgt/lheInfo->originalXWGTUP();
                pdfWeights.push_back(tmpWeight);

                if (i<=8 or int(i)>=posNNPDF) {
                    tmpWeight = genEventInfo->weight();
                    tmpWeight *= lheInfo->weights()[i].wgt/lheInfo->originalXWGTUP();
                    if (int(i)<posNNPDF) {qcdWeights.push_back(tmpWeight);}
                }
                else {
                    tmpWeight = lheInfo->weights()[i].wgt;
                    tmpWeight /= lheInfo->originalXWGTUP();
                    //if (i==9) genWeight = tmpWeight;
                    if (int(i)<posNNPDF) {nnloWeights.push_back(tmpWeight);}
                }
                // NNPDF30 variations
                if (int(i)>=posNNPDF && int(i)<=(posNNPDF+100)) {
                    rms += tmpWeight*tmpWeight;
                    if (tmpWeight>pdfENVup) pdfENVup=tmpWeight;
                    if (tmpWeight<pdfENVdown) pdfENVdown=tmpWeight;
                }
            }
            pdfRMSup=sqrt(rms/100.0); pdfRMSdown=1.0/pdfRMSup;
            if (verbose) cout<<"pdfRMSup "<<pdfRMSup<<" pdfRMSdown "<<pdfRMSdown<<endl;
        
            const lhef::HEPEUP& lheEvent = lheInfo->hepeup();
            std::vector<lhef::HEPEUP::FiveVector> lheParticles = lheEvent.PUP;
            for ( size_t idxParticle = 0; idxParticle < lheParticles.size(); ++idxParticle ) {
                int id = std::abs(lheEvent.IDUP[idxParticle]);
                int status = lheEvent.ISTUP[idxParticle];
                if ( status == 1 && id==5 ) { 
                    lheNb += 1;
                }
                if ( status == 1 && ((id >= 1 && id <= 6) || id == 21) ) { 
                    lheNj += 1;
                }
            }
        
        }
        
        if (verbose) cout<<"setting gen variables"<<endl;       
        setGENVariables(prunedgenParticles,packedgenParticles,genJets); 
        if (verbose) { cout<<"finshed setting gen variables"<<endl;  }


    } //end if isMC
    sumWeightsTotal += genWeight;
    sumWeightsTotalPU += pileupWeight*genWeight;

    eventWeight = pileupWeight*genWeight;
    
    // Fill L1 seeds and decisions
    gtUtil_->retrieveL1(iEvent, iSetup, algInputTag_);
    const vector<pair<string, bool> > finalDecisions = gtUtil_->decisionsFinal();
    for (size_t i_l1t = 0; i_l1t < finalDecisions.size(); i_l1t++){
        string l1tName = (finalDecisions.at(i_l1t)).first;
        if( l1tName.find("SingleJet") != string::npos || l1tName.find("DoubleJet") != string::npos || l1tName.find("TripleJet") != string::npos || l1tName.find("QuadJet") != string::npos ||  l1tName.find("HTT")!= string::npos ){
            //cout << "L1: " << l1tName << " | decision: " << finalDecisions.at(i_l1t).second << endl;
            Trigger_l1name.push_back( l1tName );
            Trigger_l1decision.push_back( finalDecisions.at(i_l1t).second );
        }
      }
    
    unsigned int _tSize = trigger->size();
    // create a string with all passing trigger names
    for (unsigned int i=0; i<_tSize; ++i) {
        std::string triggerName = trigNames.triggerName(i);
        if (strstr(triggerName.c_str(),"_step")) continue;
        if (strstr(triggerName.c_str(),"MC_")) continue;
        if (strstr(triggerName.c_str(),"AlCa_")) continue;
        if (strstr(triggerName.c_str(),"DST_")) continue;
        if (strstr(triggerName.c_str(),"HLT_HI")) continue;
        if (strstr(triggerName.c_str(),"HLT_Physics")) continue;
        if (strstr(triggerName.c_str(),"HLT_Random")) continue;
        if (strstr(triggerName.c_str(),"HLT_ZeroBias")) continue;
        if (strstr(triggerName.c_str(),"HLT_IsoTrack")) continue;
        if (strstr(triggerName.c_str(),"Hcal")) continue;
        if (strstr(triggerName.c_str(),"Ecal")) continue;
        if (trigger->accept(i)) triggersPassed += triggerName+" ";
			
				
        //if(triggerName.find("HLT_QuadPFJet70_50_45_35_PFBTagParticleNet_2BTagSum0p65") != string::npos || triggerName.find("HLT_PFJet500") != string::npos ){
        //if(triggerName.find("HLT_QuadPFJet") != string::npos || triggerName.find("HLT_PFJet") != string::npos || triggerName.find("HLT_DiPFJetAve") != string::npos || triggerName.find("HLT_AK8PFJet") != string::npos ) {
        Trigger_hltname.push_back(triggerName);
        Trigger_hltdecision.push_back(trigger->accept(i));
    //}
    }
    if (firstEntry) cout<<"triggersPassed: "<<triggersPassed<<endl;
    firstEntry = false;
    // check if any of the triggers in the user list have passed
    bool passedSingleEl=false;
    bool passedSingleMu=false;
    bool passedAnyOther=false;
    for (unsigned int i=0; i<triggerList.size(); ++i) {
        if (strstr(triggersPassed.c_str(),triggerList.at(i).c_str())) {
            passedTrig=true;
            if (!isMC) {
								//cout<<"bbb"<<endl;
                if (strstr(triggerList.at(i).c_str(),"_WP")) passedSingleEl=true;
                if (strstr(triggerList.at(i).c_str(),"HLT_Iso")) passedSingleMu=true;
                if (strstr(triggerList.at(i).c_str(),"CaloIdL")) passedAnyOther=true;
                if (strstr(triggerList.at(i).c_str(),"TrkIsoVVL")) passedAnyOther=true;
                if (strstr(triggerList.at(i).c_str(),"Triple")) passedAnyOther=true;
            }
        }
    }
    
    bool passedOnlySingle=((passedSingleEl && !passedAnyOther) || (passedSingleMu && !passedSingleEl && !passedAnyOther));
    bool trigConditionData = ( passedTrig && (!checkOnlySingle || (checkOnlySingle && passedOnlySingle)) );
if(trigConditionData && verbose)
	std::cout<<""<<std::endl;

//    bool trigConditionData = true;
        
    if (verbose) cout<<"checking PV"<<endl;       
    const reco::Vertex *PV = 0;
    int theVertex = -1;
    for (unsigned int i=0; i<vertex->size(); i++) {
        PV = &(vertex->at(i));        
        if (verbose) std::cout<<"isFake: "<<PV->isFake()<<" chi2 "<<PV->chi2()<<" ndof "<<PV->ndof()<<" rho "<<PV->position().Rho()<<" Z "<<PV->position().Z()<<endl; 
        //if (PV->chi2()==0 && PV->ndof()==0) continue;
        if (PV->isFake()) continue;
        if (PV->ndof()<=4 || PV->position().Rho()>2.0 || fabs(PV->position().Z())>24.0) continue;
        theVertex=(int)i; break;
    }        

    if (verbose) std::cout<<"vtx: "<<theVertex<<" trigConditionData "<<trigConditionData<<" passedTrig "<<passedTrig<<std::endl;
 
    //if(theVertex >= 0 && (isMC || (!isMC && trigConditionData)) )  {
    if(theVertex >= 0 && (isMC || (!isMC )) )  {

        if (verbose) cout<<"good PV "<<theVertex<<endl; 
        
        PV_x =  PV->position().X();
        PV_y =  PV->position().Y();
        PV_z =  PV->position().Z();

        BS_x =  BS.position().X();
        BS_y =  BS.position().Y();
        BS_z =  BS.position().Z();
        BS_xErr =  BS.x0Error();
        BS_yErr =  BS.y0Error();
        BS_zErr =  BS.z0Error();

        BeamWidth_x = BS.BeamWidthX();
        BeamWidth_y = BS.BeamWidthY();
        BeamWidth_xErr = BS.BeamWidthXError();
        BeamWidth_yErr = BS.BeamWidthYError();
    
        //N Vertex 
        if (verbose) {cout<<"fill nvtx histogram"<<endl;}
        nVtx = vertex->size();
        histContainer_["NVTX"]->Fill(nVtx);
        histContainer_["NVTX_RW"]->Fill(nVtx,pileupWeight);
// if(iEvent.id().event() > 709310){
// 	std::cout<<"PIPPO\tdopo vertex info\n";
// }
        //MET
        if (verbose) {cout<<"get met value"<<endl;}
        /*if (!mets->empty()) {
            met = (*mets)[0].et();
            met_phi = (*mets)[0].phi();
            met_jesup = (*mets)[0].shiftedPt(pat::MET::JetEnUp);
            met_phi_jesup = (*mets)[0].shiftedPhi(pat::MET::JetEnUp);
            met_jesdn = (*mets)[0].shiftedPt(pat::MET::JetEnDown);
            met_phi_jesdn = (*mets)[0].shiftedPhi(pat::MET::JetEnDown);
            met_uncenup = (*mets)[0].shiftedPt(pat::MET::UnclusteredEnUp);
            met_phi_uncenup = (*mets)[0].shiftedPhi(pat::MET::UnclusteredEnUp);
            met_uncendn = (*mets)[0].shiftedPt(pat::MET::UnclusteredEnDown);
            met_phi_uncendn = (*mets)[0].shiftedPhi(pat::MET::UnclusteredEnDown);        
        }*/

        if (verbose) cout<<"start lepton analysis"<<endl;           
        vector<pat::Electron> AllElectrons; 
        vector<pat::Electron> AllElectronsUnS;////uncorrected electron 
        vector<pat::Muon> AllMuons; 
       // vector<pat::Tau> AllTaus; 
       // vector<pat::Photon> AllPhotons;
        AllElectrons = helper.goodLooseElectrons2012(electrons,_elecPtCut);
       // AllElectronsUnS = helper.goodLooseElectrons2012(electrons,electronsUnS,_elecPtCut);
        AllMuons = helper.goodLooseMuons2012(muons,_muPtCut);
       // AllTaus = helper.goodLooseTaus2015(taus,_tauPtCut);
       // AllPhotons = helper.goodLoosePhotons2015(photons,_phoPtCut);

        /*helper.cleanOverlappingLeptons(AllMuons,AllElectrons,PV);
        helper.cleanOverlappingLeptons(AllMuons,AllElectronsUnS,PV);
        recoMuons = helper.goodMuons2015_noIso_noPf(AllMuons,_muPtCut,PV);
        recoElectrons = helper.goodElectrons2015_noIso_noBdt(AllElectrons,_elecPtCut,elecID,PV,iEvent,sip3dCut, true);
        recoElectronsUnS = helper.goodElectrons2015_noIso_noBdt(AllElectronsUnS,_elecPtCut,elecID,PV,iEvent,sip3dCut, false);
        helper.cleanOverlappingTaus(recoMuons,recoElectrons,AllTaus,isoCutMu,isoCutEl,muRho,elRho);
        recoTaus = helper.goodTaus2015(AllTaus,_tauPtCut);
        recoPhotons = helper.goodPhotons2015(AllPhotons,_phoPtCut,year);*/

                 
        // Jets
        if (verbose) cout<<"begin filling jet candidates"<<endl;
                
        vector<pat::Jet> goodJets;
        vector<float> patJetQGTagger, patJetaxis2, patJetptD;
        vector<float> goodJetQGTagger, goodJetaxis2, goodJetptD; 
        vector<int> patJetmult, goodJetmult;
                
        for(auto jet = jets->begin();  jet != jets->end(); ++jet){
        	 edm::RefToBase<pat::Jet> jetRef(edm::Ref<edm::View<pat::Jet> >(jets, jet - jets->begin()));
           float qgLikelihood = (*qgHandle)[jetRef];
           float axis2 = (*axis2Handle)[jetRef];
           float ptD = (*ptDHandle)[jetRef];
           int mult = (*multHandle)[jetRef];
           patJetQGTagger.push_back(qgLikelihood);  
           patJetaxis2.push_back(axis2);  
           patJetmult.push_back(mult);  
           patJetptD.push_back(ptD);  
        }
                           
        for(unsigned int i = 0; i < jets->size(); ++i) {
                   
        	const pat::Jet & jet = jets->at(i);
                    
          //JetID ID
          if (verbose) cout<<"checking jetid..."<<endl;
          float jpumva=0.;
          bool passPU;
          if (doJEC && (year==2017 || year==2018)) {
          	passPU = bool(jet.userInt("pileupJetId:fullId") & (1 << 0));
            jpumva=jet.userFloat("pileupJetId:fullDiscriminant");
          } else if (doJEC && (year==20160 || year==20165)) { 
            passPU = bool(jet.userInt("pileupJetId:fullId") & (1 << 2));
            jpumva=jet.userFloat("pileupJetId:fullDiscriminant");
          } else {
            passPU = bool(jet.userInt("pileupJetId:fullId") & (1 << 2));
            jpumva=jet.userFloat("pileupJetId:fullDiscriminant");
		     }
         if (verbose) cout<< " jet pu mva  "<<jpumva <<endl;
              
                        
         if (verbose) cout<<"pt: "<<jet.pt()<<" eta: "<<jet.eta()<<" phi: "<<jet.phi()<<" passPU: "<<passPU
                          <<" jetid: "<<jetHelper.patjetID(jet,year)<<endl;
                    
         if( jetHelper.patjetID(jet,year)>=jetIDLevel ) {
         //if(fabs(jet.eta())<jeteta_cut && jet.pt()>15.0){       
           if(fabs(jet.eta())<jeteta_cut){       
             goodJets.push_back(jet);
             goodJetQGTagger.push_back(patJetQGTagger[i]);
             goodJetaxis2.push_back(patJetaxis2[i]);
             goodJetptD.push_back(patJetptD[i]);
             goodJetmult.push_back(patJetmult[i]);
           }

          }
        } // all jets

        if(goodJets.size()>=4){
          passedFullSelection=true;
        }
                
        vector<pat::Jet> selectedMergedJets;
       
        if (verbose) cout<<"before vector assign"<<std::endl;
				//setTreeVariables(iEvent, iSetup, goodJets, goodJetQGTagger,goodJetaxis2, goodJetptD, goodJetmult, selectedMergedJets, AK4PuppiJets,  hltAK4PFJetsCorrected, bxvCaloJets, bxvCaloMuons, bxvCaloHT, AllMuons, AllElectrons);
        
				setTreeVariables(iEvent, iSetup, goodJets, goodJetQGTagger,goodJetaxis2, goodJetptD, goodJetmult, selectedMergedJets, AK4PuppiJets, AK8PuppiJets,  bxvCaloJets, bxvCaloMuons, bxvCaloHT, AllMuons, AllElectrons);
				
        //setTreeVariables(iEvent, iSetup, goodJets, goodJetQGTagger,goodJetaxis2, goodJetptD, goodJetmult, selectedMergedJets, hltjetsForBTag,  hltAK4PFJetsCorrected, pfJetTagCollectionParticleNetprobc , pfJetTagCollectionParticleNetprobb , pfJetTagCollectionParticleNetprobuds , pfJetTagCollectionParticleNetprobg ,pfJetTagCollectionParticleNetprobtauh ,  bxvCaloJets, bxvCaloMuons, bxvCaloHT, AllMuons, AllElectrons);
				//setTreeVariables(iEvent, iSetup, goodJets, goodJetQGTagger,goodJetaxis2, goodJetptD, goodJetmult, selectedMergedJets, bxvCaloJets, bxvCaloMuons, bxvCaloHT, AllMuons, AllElectrons);
      	if (verbose) cout<<"finshed setting tree variables"<<endl;

        lep_pt_float.assign(lep_pt.begin(),lep_pt.end());
      	lep_eta_float.assign(lep_eta.begin(),lep_eta.end());
      	lep_phi_float.assign(lep_phi.begin(),lep_phi.end());
      	lep_mass_float.assign(lep_mass.begin(),lep_mass.end());
   
        jet_pt_float.assign(jet_pt.begin(),jet_pt.end());
        jet_pt_raw_float.assign(jet_pt_raw.begin(),jet_pt_raw.end());
        jet_eta_float.assign(jet_eta.begin(),jet_eta.end());
        jet_phi_float.assign(jet_phi.begin(),jet_phi.end());
        jet_mass_float.assign(jet_mass.begin(),jet_mass.end());
        jet_csv_cTag_vsL_float.assign(jet_csv_cTag_vsL.begin(),jet_csv_cTag_vsL.end());
     
        jet_csv_cTag_vsB_float.assign(jet_csv_cTag_vsB.begin(),jet_csv_cTag_vsB.end());                
        jet_jesup_pt_float.assign(jet_jesup_pt.begin(),jet_jesup_pt.end());
        jet_jesup_eta_float.assign(jet_jesup_eta.begin(),jet_jesup_eta.end());
        jet_jesup_phi_float.assign(jet_jesup_phi.begin(),jet_jesup_phi.end());
        jet_jesup_mass_float.assign(jet_jesup_mass.begin(),jet_jesup_mass.end());
        jet_jesdn_pt_float.assign(jet_jesdn_pt.begin(),jet_jesdn_pt.end());
        jet_jesdn_eta_float.assign(jet_jesdn_eta.begin(),jet_jesdn_eta.end());
        jet_jesdn_phi_float.assign(jet_jesdn_phi.begin(),jet_jesdn_phi.end());
        jet_jesdn_mass_float.assign(jet_jesdn_mass.begin(),jet_jesdn_mass.end());
        jet_jerup_pt_float.assign(jet_jerup_pt.begin(),jet_jerup_pt.end());
        jet_jerup_eta_float.assign(jet_jerup_eta.begin(),jet_jerup_eta.end());
        jet_jerup_phi_float.assign(jet_jerup_phi.begin(),jet_jerup_phi.end());
        jet_jerup_mass_float.assign(jet_jerup_mass.begin(),jet_jerup_mass.end());
        jet_jerdn_pt_float.assign(jet_jerdn_pt.begin(),jet_jerdn_pt.end());
        jet_jerdn_eta_float.assign(jet_jerdn_eta.begin(),jet_jerdn_eta.end());
        jet_jerdn_phi_float.assign(jet_jerdn_phi.begin(),jet_jerdn_phi.end());
        jet_jerdn_mass_float.assign(jet_jerdn_mass.begin(),jet_jerdn_mass.end());

        quark_pt_float.assign(quark_pt.begin(),quark_pt.end());
        quark_eta_float.assign(quark_eta.begin(),quark_eta.end());
        quark_phi_float.assign(quark_phi.begin(),quark_phi.end());
	
        L1jet_pt_float.assign(L1jet_pt.begin(),L1jet_pt.end());
        L1jet_eta_float.assign(L1jet_eta.begin(),L1jet_eta.end());
        L1jet_phi_float.assign(L1jet_phi.begin(),L1jet_phi.end());
        L1jet_mass_float.assign(L1jet_mass.begin(),L1jet_mass.end());

        L1muon_pt_float.assign(L1muon_pt.begin(),L1muon_pt.end());
        L1muon_eta_float.assign(L1muon_eta.begin(),L1muon_eta.end());
        L1muon_phi_float.assign(L1muon_phi.begin(),L1muon_phi.end());
      	L1muon_mass_float.assign(L1muon_mass.begin(),L1muon_mass.end());

        hltjetForBTag_pt_float.assign(hltjetForBTag_pt.begin(), hltjetForBTag_pt.end());
        hltjetForBTag_eta_float.assign(hltjetForBTag_eta.begin(), hltjetForBTag_eta.end());
        hltjetForBTag_phi_float.assign(hltjetForBTag_phi.begin(), hltjetForBTag_phi.end());
        hltjetForBTag_mass_float.assign(hltjetForBTag_mass.begin(), hltjetForBTag_mass.end());

				
        hltAK4PFJetsCorrected_pt_float.assign(hltAK4PFJetsCorrected_pt.begin(), hltAK4PFJetsCorrected_pt.end());
        hltAK4PFJetsCorrected_eta_float.assign(hltAK4PFJetsCorrected_eta.begin(), hltAK4PFJetsCorrected_eta.end());
        hltAK4PFJetsCorrected_phi_float.assign(hltAK4PFJetsCorrected_phi.begin(), hltAK4PFJetsCorrected_phi.end());
        hltAK4PFJetsCorrected_mass_float.assign(hltAK4PFJetsCorrected_mass.begin(), hltAK4PFJetsCorrected_mass.end());

        AK4PuppiJets_pt_float.assign(AK4PuppiJets_pt.begin(), AK4PuppiJets_pt.end()); 
        AK4PuppiJets_eta_float.assign(AK4PuppiJets_eta.begin(), AK4PuppiJets_eta.end()); 
        AK4PuppiJets_phi_float.assign(AK4PuppiJets_phi.begin(), AK4PuppiJets_phi.end()); 
        AK4PuppiJets_mass_float.assign(AK4PuppiJets_mass.begin(), AK4PuppiJets_mass.end());

	AK8PuppiJets_pt_float.assign(AK8PuppiJets_pt.begin(), AK8PuppiJets_pt.end()); 
	AK8PuppiJets_eta_float.assign(AK8PuppiJets_eta.begin(), AK8PuppiJets_eta.end()); 
        AK8PuppiJets_phi_float.assign(AK8PuppiJets_phi.begin(), AK8PuppiJets_phi.end()); 
        AK8PuppiJets_mass_float.assign(AK8PuppiJets_mass.begin(), AK8PuppiJets_mass.end());

//   if(iEvent.id().event() > 709310)
// 	std::cout<<"PIPPO\t before filling 11\n";				                                  
              
        //if (!isMC && passedFullSelection==true) passedEventsTree_All->Fill();        
        if (!isMC && passedTrig==true) passedEventsTree_All->Fill();        
    }    //primary vertex,notDuplicate
    else { if (verbose) cout<<Run<<":"<<LumiSect<<":"<<Event<<" failed primary vertex"<<endl;}
    
    GENjet_pt_float.clear(); GENjet_pt_float.assign(GENjet_pt.begin(),GENjet_pt.end());
    GENjet_eta_float.clear(); GENjet_eta_float.assign(GENjet_eta.begin(),GENjet_eta.end());
    GENjet_phi_float.clear(); GENjet_phi_float.assign(GENjet_phi.begin(),GENjet_phi.end());
    GENjet_mass_float.clear(); GENjet_mass_float.assign(GENjet_mass.begin(),GENjet_mass.end());
 
    //if (isMC && passedFullSelection==true) passedEventsTree_All->Fill();
    if (isMC ) passedEventsTree_All->Fill();
    
    if (nEventsTotal==1000.0) passedEventsTree_All->OptimizeBaskets();
    
}



// ------------ method called once each job just before starting event loop  ------------
void 
HccAna::beginJob()
{
    using namespace edm;
    using namespace std;
    using namespace pat;
		
		
    bookPassedEventTree("passedEvents", passedEventsTree_All);
		
    firstEntry = true;

}

// ------------ method called once each job just after ending the event loop  ------------
void 
HccAna::endJob() 
{
    histContainer_["NEVENTS"]->SetBinContent(1,nEventsTotal);
    histContainer_["NEVENTS"]->GetXaxis()->SetBinLabel(1,"N Events in Sample");
    histContainer_["SUMWEIGHTS"]->SetBinContent(1,sumWeightsTotal);
    histContainer_["SUMWEIGHTSPU"]->SetBinContent(1,sumWeightsTotalPU);
    histContainer_["SUMWEIGHTS"]->GetXaxis()->SetBinLabel(1,"sum Weights in Sample");
    histContainer_["SUMWEIGHTSPU"]->GetXaxis()->SetBinLabel(1,"sum Weights PU in Sample");
}

void
HccAna::beginRun(const edm::Run& iRun, const edm::EventSetup& iSetup)
{

    //massErr.init(iSetup);
    if (isMC) {
        edm::Handle<LHERunInfoProduct> run;
        typedef std::vector<LHERunInfoProduct::Header>::const_iterator headers_const_iterator;
        try {

            int pos=0;
            iRun.getByLabel( edm::InputTag("externalLHEProducer"), run );
            LHERunInfoProduct myLHERunInfoProduct = *(run.product());
            typedef std::vector<LHERunInfoProduct::Header>::const_iterator headers_const_iterator;
            for (headers_const_iterator iter=myLHERunInfoProduct.headers_begin(); iter!=myLHERunInfoProduct.headers_end(); iter++){
                std::cout << iter->tag() << std::endl;
                std::vector<std::string> lines = iter->lines();
                for (unsigned int iLine = 0; iLine<lines.size(); iLine++) {
                    std::string pdfid=lines.at(iLine);
                    if (pdfid.substr(1,6)=="weight" && pdfid.substr(8,2)=="id") {
                        std::cout<<pdfid<<std::endl;
                        std::string pdf_weight_id = pdfid.substr(12,4);
                        int pdf_weightid=atoi(pdf_weight_id.c_str());
//                         std::cout<<"parsed id: "<<pdf_weightid<<std::endl;
                        if (pdf_weightid==2001) {posNNPDF=int(pos);}
                        pos+=1;
                    }
                }
            }
        }
        catch(...) {
            std::cout<<"No LHERunInfoProduct"<<std::endl;
        }
    }

}


// ------------ method called when ending the processing of a run  ------------
void 
HccAna::endRun(const edm::Run& iRun, edm::EventSetup const&)
{
}

// ------------ method called when starting to processes a luminosity block  ------------
void 
HccAna::beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
{
}

// ------------ method called when ending the processing of a luminosity block  ------------
void 
HccAna::endLuminosityBlock(edm::LuminosityBlock const& lumiSeg,edm::EventSetup const& eSetup)
{
    using namespace edm;
    using namespace std;
    // Keep track of all the events run over
    edm::Handle<MergeableCounter> numEventsCounter;
    lumiSeg.getByLabel("nEventsTotal", numEventsCounter);    
    if(numEventsCounter.isValid()) {
        std::cout<<"numEventsCounter->value "<<numEventsCounter->value<<endl;
        nEventsTotal += numEventsCounter->value;        
    }
}

// ============================ UF Functions ============================= //



void HccAna::bookPassedEventTree(TString treeName, TTree *tree)
{     


    using namespace edm;
    using namespace pat;
    using namespace std;

    // -------------------------                                                                                                                                                                        
    // RECO level information                                                                                                                                                                           
    // -------------------------                                                                                                                                                                        
    // Event variables
    tree->Branch("Run",&Run,"Run/l");
    tree->Branch("Event",&Event,"Event/l");
    tree->Branch("LumiSect",&LumiSect,"LumiSect/l");
    tree->Branch("nVtx",&nVtx,"nVtx/I");
    tree->Branch("nInt",&nInt,"nInt/I");
    tree->Branch("puN", &puN, "puN/I");
    tree->Branch("PV_x", &PV_x, "PV_x/F");
    tree->Branch("PV_y", &PV_y, "PV_y/F");
    tree->Branch("PV_z", &PV_z, "PV_z/F");
    tree->Branch("BS_x", &BS_x, "BS_x/F");
    tree->Branch("BS_y", &BS_y, "BS_y/F");
    tree->Branch("BS_z", &BS_z, "BS_z/F");
    tree->Branch("BS_xErr", &BS_xErr, "BS_xErr/F");
    tree->Branch("BS_yErr", &BS_yErr, "BS_yErr/F");
    tree->Branch("BS_zErr", &BS_zErr, "BS_zErr/F");
    tree->Branch("BeamWidth_x", &BeamWidth_x, "BeamWidth_x/F");
    tree->Branch("BeamWidth_y", &BeamWidth_y, "BeamWidth_y/F");
    tree->Branch("BeamWidth_xErr", &BeamWidth_xErr, "BeamWidth_xErr/F");
    tree->Branch("BeamWidth_yErr", &BeamWidth_yErr, "BeamWidth_yErr/F");
    tree->Branch("finalState",&finalState,"finalState/I");
    tree->Branch("triggersPassed",&triggersPassed);
    tree->Branch("passedTrig",&passedTrig,"passedTrig/O");
    tree->Branch("Trigger_l1name",&Trigger_l1name);
    tree->Branch("Trigger_l1decision",&Trigger_l1decision);
    tree->Branch("Trigger_hltname",&Trigger_hltname);
    tree->Branch("Trigger_hltdecision",&Trigger_hltdecision);
		

    /*tree->Branch("passedFullSelection",&passedFullSelection,"passedFullSelection/O");
    tree->Branch("passedZ4lSelection",&passedZ4lSelection,"passedZ4lSelection/O");
    tree->Branch("passedQCDcut",&passedQCDcut,"passedQCDcut/O");
    tree->Branch("genWeight",&genWeight,"genWeight/F");
    tree->Branch("k_qqZZ_qcd_dPhi",&k_qqZZ_qcd_dPhi,"k_qqZZ_qcd_dPhi/F");
    tree->Branch("k_qqZZ_qcd_M",&k_qqZZ_qcd_M,"k_qqZZ_qcd_M/F");
    tree->Branch("k_qqZZ_qcd_Pt",&k_qqZZ_qcd_Pt,"k_qqZZ_qcd_Pt/F");
    tree->Branch("k_qqZZ_ewk",&k_qqZZ_ewk,"k_qqZZ_ewk/F");
    tree->Branch("qcdWeights",&qcdWeights);
    tree->Branch("nnloWeights",&nnloWeights);
    tree->Branch("pdfWeights",&pdfWeights);
    tree->Branch("pdfRMSup",&pdfRMSup,"pdfRMSup/F");
    tree->Branch("pdfRMSdown",&pdfRMSdown,"pdfRMSdown/F");
    tree->Branch("pdfENVup",&pdfENVup,"pdfENVup/F");
    tree->Branch("pdfENVdown",&pdfENVdown,"pdfENVdown/F");
    tree->Branch("pileupWeight",&pileupWeight,"pileupWeight/F");
    tree->Branch("pileupWeightUp",&pileupWeightUp,"pileupWeightUp/F");
    tree->Branch("pileupWeightDn",&pileupWeightDn,"pileupWeightDn/F");
    tree->Branch("dataMCWeight",&dataMCWeight,"dataMCWeight/F");
    tree->Branch("eventWeight",&eventWeight,"eventWeight/F");
    tree->Branch("prefiringWeight",&prefiringWeight,"prefiringWeight/F");
    tree->Branch("crossSection",&crossSection,"crossSection/F");

    // Lepton variables
    tree->Branch("lep_d0BS",&lep_d0BS_float);
    tree->Branch("lep_d0PV",&lep_d0PV_float);

    tree->Branch("lep_numberOfValidPixelHits",&lep_numberOfValidPixelHits_float);
    tree->Branch("lep_trackerLayersWithMeasurement",&lep_trackerLayersWithMeasurement_float);

    tree->Branch("lep_p",&lep_p_float);
    tree->Branch("lep_ecalEnergy",&lep_ecalEnergy_float);
    tree->Branch("lep_isEB",&lep_isEB);
    tree->Branch("lep_isEE",&lep_isEE);

    tree->Branch("lep_pt_UnS",&lep_pt_UnS_float);
    tree->Branch("lep_pterrold_UnS",&lep_pterrold_UnS_float);
    tree->Branch("lep_errPre_Scale",&lep_errPre_Scale_float);
    tree->Branch("lep_errPost_Scale",&lep_errPost_Scale_float);
    tree->Branch("lep_errPre_noScale",&lep_errPre_noScale_float);
    tree->Branch("lep_errPost_noScale",&lep_errPost_noScale_float);


    tree->Branch("lep_pt_genFromReco",&lep_pt_genFromReco_float);*/

    tree->Branch("lep_id",&lep_ID);
    tree->Branch("lep_pt",&lep_pt_float);
    //tree->Branch("lep_pterr",&lep_pterr_float);
    //tree->Branch("lep_pterrold",&lep_pterrold_float);
    tree->Branch("lep_eta",&lep_eta_float);
    tree->Branch("lep_phi",&lep_phi_float);
    tree->Branch("lep_mass",&lep_mass_float);
	tree->Branch("ALLlep_id",&ALLlep_id);
    	tree->Branch("ALLlep_pt",&ALLlep_pt);
    	tree->Branch("ALLlep_eta",&ALLlep_eta);
    	tree->Branch("ALLlep_phi",&ALLlep_phi);
    	tree->Branch("ALLlep_mass",&ALLlep_mass);
	tree->Branch("AK4lep_id",&AK4lep_id);
        tree->Branch("AK4lep_pt",&AK4lep_pt);
        tree->Branch("AK4lep_eta",&AK4lep_eta);
        tree->Branch("AK4lep_phi",&AK4lep_phi);
        tree->Branch("AK4lep_mass",&AK4lep_mass);
    /*tree->Branch("lepFSR_pt",&lepFSR_pt_float);
    tree->Branch("lepFSR_eta",&lepFSR_eta_float);
    tree->Branch("lepFSR_phi",&lepFSR_phi_float);
    tree->Branch("lepFSR_mass",&lepFSR_mass_float);
    tree->Branch("lep_Hindex",&lep_Hindex,"lep_Hindex[4]/I");
    tree->Branch("lep_genindex",&lep_genindex);
    tree->Branch("lep_matchedR03_PdgId",&lep_matchedR03_PdgId);
    tree->Branch("lep_matchedR03_MomId",&lep_matchedR03_MomId);
    tree->Branch("lep_matchedR03_MomMomId",&lep_matchedR03_MomMomId);
    tree->Branch("lep_missingHits",&lep_missingHits);
    tree->Branch("lep_mva",&lep_mva);
    tree->Branch("lep_ecalDriven",&lep_ecalDriven);
    tree->Branch("lep_tightId",&lep_tightId);
    //tree->Branch("lep_tightId_old",&lep_tightId_old);
    tree->Branch("lep_tightIdSUS",&lep_tightIdSUS);
    tree->Branch("lep_tightIdHiPt",&lep_tightIdHiPt);
    tree->Branch("lep_Sip",&lep_Sip);
    tree->Branch("lep_IP",&lep_IP);
    tree->Branch("lep_isoNH",&lep_isoNH);
    tree->Branch("lep_isoCH",&lep_isoCH);
    tree->Branch("lep_isoPhot",&lep_isoPhot);
    tree->Branch("lep_isoPU",&lep_isoPU);
    tree->Branch("lep_isoPUcorr",&lep_isoPUcorr);
    tree->Branch("lep_RelIso",&lep_RelIso);
    tree->Branch("lep_RelIsoNoFSR",&lep_RelIsoNoFSR);
    tree->Branch("lep_MiniIso",&lep_MiniIso);
    tree->Branch("lep_ptRatio",&lep_ptRatio);
    tree->Branch("lep_ptRel",&lep_ptRel);
    tree->Branch("lep_filtersMatched",&lep_filtersMatched);
    tree->Branch("lep_dataMC",&lep_dataMC);
    tree->Branch("lep_dataMCErr",&lep_dataMCErr);
    tree->Branch("dataMC_VxBS",&dataMC_VxBS);
    tree->Branch("dataMCErr_VxBS",&dataMCErr_VxBS);
    tree->Branch("nisoleptons",&nisoleptons,"nisoleptons/I");
    tree->Branch("muRho",&muRho,"muRho/F");
    tree->Branch("elRho",&elRho,"elRho/F");
    tree->Branch("tau_id",&tau_id);
    tree->Branch("tau_pt",&tau_pt_float);
    tree->Branch("tau_eta",&tau_eta_float);
    tree->Branch("tau_phi",&tau_phi_float);
    tree->Branch("tau_mass",&tau_mass_float);
    tree->Branch("pho_pt",&pho_pt_float);
    tree->Branch("pho_eta",&pho_eta_float);
    tree->Branch("pho_phi",&pho_phi_float);
    tree->Branch("photonCutBasedIDLoose",&photonCutBasedIDLoose_float);

    //Higgs Candidate Variables
    tree->Branch("H_pt",&H_pt_float);
    tree->Branch("H_eta",&H_eta_float);
    tree->Branch("H_phi",&H_phi_float);
    tree->Branch("H_mass",&H_mass_float);
    tree->Branch("H_noFSR_pt",&H_noFSR_pt_float);
    tree->Branch("H_noFSR_eta",&H_noFSR_eta_float);
    tree->Branch("H_noFSR_phi",&H_noFSR_phi_float);
    tree->Branch("H_noFSR_mass",&H_noFSR_mass_float);
    tree->Branch("mass4l",&mass4l,"mass4l/F");
    tree->Branch("mass4l_noFSR",&mass4l_noFSR,"mass4l_noFSR/F");

    tree->Branch("mass4mu",&mass4mu,"mass4mu/F");
    tree->Branch("mass4e",&mass4e,"mass4e/F");
    tree->Branch("mass2e2mu",&mass2e2mu,"mass2e2mu/F");
    tree->Branch("pT4l",&pT4l,"pT4l/F");
    tree->Branch("eta4l",&eta4l,"eta4l/F");
    tree->Branch("phi4l",&phi4l,"phi4l/F");
    tree->Branch("rapidity4l",&rapidity4l,"rapidity4l/F");
    tree->Branch("cosTheta1",&cosTheta1,"cosTheta1/F");
    tree->Branch("cosTheta2",&cosTheta2,"cosTheta2/F");
    tree->Branch("cosThetaStar",&cosThetaStar,"cosThetaStar/F");
    tree->Branch("Phi",&Phi,"Phi/F");
    tree->Branch("Phi1",&Phi1,"Phi1/F");
    tree->Branch("mass3l",&mass3l,"mass3l/F");

    // Z candidate variables
    tree->Branch("Z_pt",&Z_pt_float);
    tree->Branch("Z_eta",&Z_eta_float);
    tree->Branch("Z_phi",&Z_phi_float);
    tree->Branch("Z_mass",&Z_mass_float);
    tree->Branch("Z_noFSR_pt",&Z_noFSR_pt_float);
    tree->Branch("Z_noFSR_eta",&Z_noFSR_eta_float);
    tree->Branch("Z_noFSR_phi",&Z_noFSR_phi_float);
    tree->Branch("Z_noFSR_mass",&Z_noFSR_mass_float);
    tree->Branch("Z_Hindex",&Z_Hindex,"Z_Hindex[2]/I");
    tree->Branch("massZ1",&massZ1,"massZ1/F");
    tree->Branch("massZ1_Z1L",&massZ1_Z1L,"massZ1_Z1L/F");
    tree->Branch("massZ2",&massZ2,"massZ2/F");  
    tree->Branch("pTZ1",&pTZ1,"pTZ1/F");
    tree->Branch("pTZ2",&pTZ2,"pTZ2/F");*/

    // MET
    tree->Branch("met",&met,"met/F");
    tree->Branch("met_phi",&met_phi,"met_phi/F");
    tree->Branch("met_jesup",&met_jesup,"met_jesup/F");
    tree->Branch("met_phi_jesup",&met_phi_jesup,"met_phi_jesup/F");
    tree->Branch("met_jesdn",&met_jesdn,"met_jesdn/F");
    tree->Branch("met_phi_jesdn",&met_phi_jesdn,"met_phi_jesdn/F");
    tree->Branch("met_uncenup",&met_uncenup,"met_uncenup/F");
    tree->Branch("met_phi_uncenup",&met_phi_uncenup,"met_phi_uncenup/F");
    tree->Branch("met_uncendn",&met_uncendn,"met_uncendn/F");
    tree->Branch("met_phi_uncendn",&met_phi_uncendn,"met_phi_uncendn/F");

    // Jets
    tree->Branch("n_jets", &n_jets);
    //tree->Branch("jet_iscleanH4l",&jet_iscleanH4l);
    //tree->Branch("jet1index",&jet1index,"jet1index/I");
    //tree->Branch("jet2index",&jet2index,"jet2index/I");
    tree->Branch("jet_pt",&jet_pt_float);
    //tree->Branch("jet_pt_raw",&jet_pt_raw_float);
    //tree->Branch("jet_relpterr",&jet_relpterr);    
    tree->Branch("jet_eta",&jet_eta_float);
    tree->Branch("jet_phi",&jet_phi_float);
    //tree->Branch("jet_phierr",&jet_phierr);
    tree->Branch("jet_csv_cTag_vsL",&jet_csv_cTag_vsL_float);
    tree->Branch("jet_csv_cTag_vsB",&jet_csv_cTag_vsB_float);
    //tree->Branch("jet_bTagEffi",&jet_bTagEffi);
    //tree->Branch("jet_cTagEffi",&jet_cTagEffi);
    //tree->Branch("jet_udsgTagEffi",&jet_udsgTagEffi);
    tree->Branch("jet_mass",&jet_mass_float);    
    /*tree->Branch("jet_jesup_iscleanH4l",&jet_jesup_iscleanH4l);
    tree->Branch("jet_jesup_pt",&jet_jesup_pt_float);
    tree->Branch("jet_jesup_eta",&jet_jesup_eta_float);
    tree->Branch("jet_jesup_phi",&jet_jesup_phi_float);
    tree->Branch("jet_jesup_mass",&jet_jesup_mass_float);
    tree->Branch("jet_jesdn_iscleanH4l",&jet_jesdn_iscleanH4l);
    tree->Branch("jet_jesdn_pt",&jet_jesdn_pt_float);
    tree->Branch("jet_jesdn_eta",&jet_jesdn_eta_float);
    tree->Branch("jet_jesdn_phi",&jet_jesdn_phi_float);
    tree->Branch("jet_jesdn_mass",&jet_jesdn_mass_float);
    tree->Branch("jet_jerup_iscleanH4l",&jet_jerup_iscleanH4l);
    tree->Branch("jet_jerup_pt",&jet_jerup_pt_float);
    tree->Branch("jet_jerup_eta",&jet_jerup_eta_float);
    tree->Branch("jet_jerup_phi",&jet_jerup_phi_float);
    tree->Branch("jet_jerup_mass",&jet_jerup_mass_float);
    tree->Branch("jet_jerdn_iscleanH4l",&jet_jerdn_iscleanH4l);
    tree->Branch("jet_jerdn_pt",&jet_jerdn_pt_float);
    tree->Branch("jet_jerdn_eta",&jet_jerdn_eta_float);
    tree->Branch("jet_jerdn_phi",&jet_jerdn_phi_float);
    tree->Branch("jet_jerdn_mass",&jet_jerdn_mass_float);
    tree->Branch("jet_pumva",&jet_pumva);
    tree->Branch("jet_csvv2",&jet_csvv2);
    tree->Branch("jet_csvv2_",&jet_csvv2_);*/
    tree->Branch("jet_isbtag",&jet_isbtag);
    tree->Branch("jet_pfDeepCSVJetTags_probb", &jet_pfDeepCSVJetTags_probb);
    tree->Branch("jet_pfDeepFlavourJetTags_probbb", &jet_pfDeepFlavourJetTags_probbb);
    tree->Branch("jet_pfDeepFlavourJetTags_probc", &jet_pfDeepFlavourJetTags_probc);
    tree->Branch("jet_pfDeepFlavourJetTags_probuds",&jet_pfDeepFlavourJetTags_probuds);
    /*tree->Branch("jet_hadronFlavour",&jet_hadronFlavour);
    tree->Branch("jet_partonFlavour",&jet_partonFlavour);    
    tree->Branch("jet_QGTagger",&jet_QGTagger);
    tree->Branch("jet_QGTagger_jesup",&jet_QGTagger_jesup);
    tree->Branch("jet_QGTagger_jesdn",&jet_QGTagger_jesdn);
    tree->Branch("jet_axis2",&jet_axis2);
    tree->Branch("jet_ptD",&jet_ptD);
    tree->Branch("jet_mult",&jet_mult);
    tree->Branch("njets_pt30_eta4p7",&njets_pt30_eta4p7,"njets_pt30_eta4p7/I");
    tree->Branch("njets_pt30_eta4p7_jesup",&njets_pt30_eta4p7_jesup,"njets_pt30_eta4p7_jesup/I");
    tree->Branch("njets_pt30_eta4p7_jesdn",&njets_pt30_eta4p7_jesdn,"njets_pt30_eta4p7_jesdn/I");
    tree->Branch("njets_pt30_eta4p7_jerup",&njets_pt30_eta4p7_jerup,"njets_pt30_eta4p7_jerup/I");
    tree->Branch("njets_pt30_eta4p7_jerdn",&njets_pt30_eta4p7_jerdn,"njets_pt30_eta4p7_jerdn/I");
    tree->Branch("pt_leadingjet_pt30_eta4p7",&pt_leadingjet_pt30_eta4p7,"pt_leadingjet_pt30_eta4p7/F");
    tree->Branch("pt_leadingjet_pt30_eta4p7_jesup",&pt_leadingjet_pt30_eta4p7_jesup,"pt_leadingjet_pt30_eta4p7_jesup/F");
    tree->Branch("pt_leadingjet_pt30_eta4p7_jesdn",&pt_leadingjet_pt30_eta4p7_jesdn,"pt_leadingjet_pt30_eta4p7_jesdn/F");
    tree->Branch("pt_leadingjet_pt30_eta4p7_jerup",&pt_leadingjet_pt30_eta4p7_jerup,"pt_leadingjet_pt30_eta4p7_jerup/F");
    tree->Branch("pt_leadingjet_pt30_eta4p7_jerdn",&pt_leadingjet_pt30_eta4p7_jerdn,"pt_leadingjet_pt30_eta4p7_jerdn/F");
    tree->Branch("absrapidity_leadingjet_pt30_eta4p7",&absrapidity_leadingjet_pt30_eta4p7,"absrapidity_leadingjet_pt30_eta4p7/F");
    tree->Branch("absrapidity_leadingjet_pt30_eta4p7_jesup",&absrapidity_leadingjet_pt30_eta4p7_jesup,"absrapidity_leadingjet_pt30_eta4p7_jesup/F");
    tree->Branch("absrapidity_leadingjet_pt30_eta4p7_jesdn",&absrapidity_leadingjet_pt30_eta4p7_jesdn,"absrapidity_leadingjet_pt30_eta4p7_jesdn/F");
    tree->Branch("absrapidity_leadingjet_pt30_eta4p7_jerup",&absrapidity_leadingjet_pt30_eta4p7_jerup,"absrapidity_leadingjet_pt30_eta4p7_jerup/F");
    tree->Branch("absrapidity_leadingjet_pt30_eta4p7_jerdn",&absrapidity_leadingjet_pt30_eta4p7_jerdn,"absrapidity_leadingjet_pt30_eta4p7_jerdn/F");
    tree->Branch("absdeltarapidity_hleadingjet_pt30_eta4p7",&absdeltarapidity_hleadingjet_pt30_eta4p7,"absdeltarapidity_hleadingjet_pt30_eta4p7/F");
    tree->Branch("absdeltarapidity_hleadingjet_pt30_eta4p7_jesup",&absdeltarapidity_hleadingjet_pt30_eta4p7_jesup,"absdeltarapidity_hleadingjet_pt30_eta4p7_jesup/F");
    tree->Branch("absdeltarapidity_hleadingjet_pt30_eta4p7_jesdn",&absdeltarapidity_hleadingjet_pt30_eta4p7_jesdn,"absdeltarapidity_hleadingjet_pt30_eta4p7_jesdn/F");
    tree->Branch("absdeltarapidity_hleadingjet_pt30_eta4p7_jerup",&absdeltarapidity_hleadingjet_pt30_eta4p7_jerup,"absdeltarapidity_hleadingjet_pt30_eta4p7_jerup/F");
    tree->Branch("absdeltarapidity_hleadingjet_pt30_eta4p7_jerdn",&absdeltarapidity_hleadingjet_pt30_eta4p7_jerdn,"absdeltarapidity_hleadingjet_pt30_eta4p7_jerdn/F");
    tree->Branch("nbjets_pt30_eta4p7",&nbjets_pt30_eta4p7,"nbjets_pt30_eta4p7/I");
    tree->Branch("nvjets_pt40_eta2p4",&nvjets_pt40_eta2p4,"nvjets_pt40_eta2p4/I");
    tree->Branch("DijetMass",&DijetMass,"DijetMass/F");
    tree->Branch("DijetDEta",&DijetDEta,"DijetDEta/F");
    tree->Branch("DijetFisher",&DijetFisher,"DijetFisher/F");
    tree->Branch("njets_pt30_eta2p5",&njets_pt30_eta2p5,"njets_pt30_eta2p5/I");
    tree->Branch("njets_pt30_eta2p5_jesup",&njets_pt30_eta2p5_jesup,"njets_pt30_eta2p5_jesup/I");
    tree->Branch("njets_pt30_eta2p5_jesdn",&njets_pt30_eta2p5_jesdn,"njets_pt30_eta2p5_jesdn/I");
    tree->Branch("njets_pt30_eta2p5_jerup",&njets_pt30_eta2p5_jerup,"njets_pt30_eta2p5_jerup/I");
    tree->Branch("njets_pt30_eta2p5_jerdn",&njets_pt30_eta2p5_jerdn,"njets_pt30_eta2p5_jerdn/I");
    tree->Branch("pt_leadingjet_pt30_eta2p5",&pt_leadingjet_pt30_eta2p5,"pt_leadingjet_pt30_eta2p5/F");
    tree->Branch("pt_leadingjet_pt30_eta2p5_jesup",&pt_leadingjet_pt30_eta2p5_jesup,"pt_leadingjet_pt30_eta2p5_jesup/F");
    tree->Branch("pt_leadingjet_pt30_eta2p5_jesdn",&pt_leadingjet_pt30_eta2p5_jesdn,"pt_leadingjet_pt30_eta2p5_jesdn/F");
    tree->Branch("pt_leadingjet_pt30_eta2p5_jerup",&pt_leadingjet_pt30_eta2p5_jerup,"pt_leadingjet_pt30_eta2p5_jerup/F");
    tree->Branch("pt_leadingjet_pt30_eta2p5_jerdn",&pt_leadingjet_pt30_eta2p5_jerdn,"pt_leadingjet_pt30_eta2p5_jerdn/F");*/

    // Puppi AK4jets with ParticleNet taggers
    tree->Branch("AK4PuppiJets_pt",&AK4PuppiJets_pt_float);
    tree->Branch("AK4PuppiJets_eta",&AK4PuppiJets_eta_float);
    tree->Branch("AK4PuppiJets_phi",&AK4PuppiJets_phi_float);
    tree->Branch("AK4PuppiJets_mass",&AK4PuppiJets_mass_float);
   
    tree->Branch("jet_pfParticleNetAK4JetTags_probb", &jet_pfParticleNetAK4JetTags_probb);	
    tree->Branch("jet_pfParticleNetAK4JetTags_probc", &jet_pfParticleNetAK4JetTags_probc);	
    tree->Branch("jet_pfParticleNetAK4JetTags_probuds", &jet_pfParticleNetAK4JetTags_probuds);	
    tree->Branch("jet_pfParticleNetAK4JetTags_probg", &jet_pfParticleNetAK4JetTags_probg);	
    tree->Branch("jet_pfParticleNetAK4JetTags_probtauh", &jet_pfParticleNetAK4JetTags_probtauh);

	// Puppi AK8jets with ParticleNet(-MD) and DeepDoubleX taggers
	tree->Branch("AK8PuppiJets_pt",&AK8PuppiJets_pt_float);	
	tree->Branch("AK8PuppiJets_eta",&AK8PuppiJets_eta_float);
	tree->Branch("AK8PuppiJets_phi",&AK8PuppiJets_phi_float);
	tree->Branch("AK8PuppiJets_mass",&AK8PuppiJets_mass_float);
	
	   tree->Branch("jet_pfParticleNetJetTags_probZbb", &jet_pfParticleNetJetTags_probZbb);
	tree->Branch("jet_pfParticleNetJetTags_probZcc", &jet_pfParticleNetJetTags_probZcc);
	tree->Branch("jet_pfParticleNetJetTags_probZqq", &jet_pfParticleNetJetTags_probZqq);
	tree->Branch("jet_pfParticleNetJetTags_probQCDbb", &jet_pfParticleNetJetTags_probQCDbb);
	tree->Branch("jet_pfParticleNetJetTags_probQCDcc", &jet_pfParticleNetJetTags_probQCDcc);
	tree->Branch("jet_pfParticleNetJetTags_probQCDb", &jet_pfParticleNetJetTags_probQCDb);
	tree->Branch("jet_pfParticleNetJetTags_probQCDc", &jet_pfParticleNetJetTags_probQCDc);
	tree->Branch("jet_pfParticleNetJetTags_probQCDothers", &jet_pfParticleNetJetTags_probQCDothers);
	tree->Branch("jet_pfParticleNetJetTags_probHbb", &jet_pfParticleNetJetTags_probHbb);
	tree->Branch("jet_pfParticleNetJetTags_probHcc", &jet_pfParticleNetJetTags_probHcc);
	tree->Branch("jet_pfParticleNetJetTags_probHqqqq", &jet_pfParticleNetJetTags_probHqqqq);

	tree->Branch("jet_pfMassDecorrelatedParticleNetJetTags_probXbb", &jet_pfMassDecorrelatedParticleNetJetTags_probXbb);
        tree->Branch("jet_pfMassDecorrelatedParticleNetJetTags_probXcc", &jet_pfMassDecorrelatedParticleNetJetTags_probXcc);
        tree->Branch("jet_pfMassDecorrelatedParticleNetJetTags_probXqq", &jet_pfMassDecorrelatedParticleNetJetTags_probXqq);
        tree->Branch("jet_pfMassDecorrelatedParticleNetJetTags_probQCDbb", &jet_pfMassDecorrelatedParticleNetJetTags_probQCDbb);
        tree->Branch("jet_pfMassDecorrelatedParticleNetJetTags_probQCDcc", &jet_pfMassDecorrelatedParticleNetJetTags_probQCDcc);
        tree->Branch("jet_pfMassDecorrelatedParticleNetJetTags_probQCDb", &jet_pfMassDecorrelatedParticleNetJetTags_probQCDb);
        tree->Branch("jet_pfMassDecorrelatedParticleNetJetTags_probQCDc", &jet_pfMassDecorrelatedParticleNetJetTags_probQCDc);
        tree->Branch("jet_pfMassDecorrelatedParticleNetJetTags_probQCDothers", &jet_pfMassDecorrelatedParticleNetJetTags_probQCDothers);

	tree->Branch("jet_pfMassIndependentDeepDoubleBvLV2JetTags_probHbb", &jet_pfMassIndependentDeepDoubleBvLV2JetTags_probHbb);
	tree->Branch("jet_pfMassIndependentDeepDoubleCvLV2JetTags_probHcc", &jet_pfMassIndependentDeepDoubleCvLV2JetTags_probHcc);
	tree->Branch("jet_pfMassIndependentDeepDoubleCvBV2JetTags_probHcc", &jet_pfMassIndependentDeepDoubleCvBV2JetTags_probHcc);

    //hlt jets
    tree->Branch("hltjetForBTag_pt",&hltjetForBTag_pt_float);
    tree->Branch("hltjetForBTag_eta",&hltjetForBTag_eta_float);
    tree->Branch("hltjetForBTag_phi",&hltjetForBTag_phi_float);
    tree->Branch("hltjetForBTag_mass",&hltjetForBTag_mass_float);
    tree->Branch("hltjetForBTag_ParticleNet_probb",&hltParticleNetONNXJetTags_probb);
    tree->Branch("hltjetForBTag_ParticleNet_probc",&hltParticleNetONNXJetTags_probc);
    tree->Branch("hltjetForBTag_ParticleNet_probuds",&hltParticleNetONNXJetTags_probuds);
    tree->Branch("hltjetForBTag_ParticleNet_probg",&hltParticleNetONNXJetTags_probg);
    tree->Branch("hltjetForBTag_ParticleNet_probtauh",&hltParticleNetONNXJetTags_probtauh);

    //hltAK4PFJetsCorrected
    tree->Branch("hltAK4PFJetsCorrected_pt",&hltAK4PFJetsCorrected_pt_float);
    tree->Branch("hltAK4PFJetsCorrected_eta",&hltAK4PFJetsCorrected_eta_float);
    tree->Branch("hltAK4PFJetsCorrected_phi",&hltAK4PFJetsCorrected_phi_float);
    tree->Branch("hltAK4PFJetsCorrected_mass",&hltAK4PFJetsCorrected_mass_float);

    //L1 jets
    tree->Branch("L1jet_pt",&L1jet_pt_float);
    tree->Branch("L1jet_eta",&L1jet_eta_float);
    tree->Branch("L1jet_phi",&L1jet_phi_float);
    tree->Branch("L1jet_mass",&L1jet_mass_float);
	
    //L1 muons
    tree->Branch("L1muon_pt",&L1muon_pt_float);
    tree->Branch("L1muon_eta",&L1muon_eta_float);
    tree->Branch("L1muon_phi",&L1muon_phi_float);
    tree->Branch("L1muon_mass",&L1muon_mass_float);
    tree->Branch("L1muon_qual",&L1muon_qual);
		
    //L1 HT
    tree->Branch("L1ht",&L1ht, "L1ht/F");
		


    // merged jets
    /*tree->Branch("mergedjet_iscleanH4l",&mergedjet_iscleanH4l);
    tree->Branch("mergedjet_pt",&mergedjet_pt);
    tree->Branch("mergedjet_eta",&mergedjet_eta);
    tree->Branch("mergedjet_phi",&mergedjet_phi);
    tree->Branch("mergedjet_mass",&mergedjet_mass);    
    tree->Branch("mergedjet_tau1",&mergedjet_tau1);
    tree->Branch("mergedjet_tau2",&mergedjet_tau2);
    tree->Branch("mergedjet_btag",&mergedjet_btag);
    
    tree->Branch("mergedjet_L1",&mergedjet_L1);
    tree->Branch("mergedjet_softdropmass",&mergedjet_softdropmass);
    tree->Branch("mergedjet_prunedmass",&mergedjet_prunedmass);

    tree->Branch("mergedjet_nsubjet",&mergedjet_nsubjet);
    tree->Branch("mergedjet_subjet_pt",&mergedjet_subjet_pt);
    tree->Branch("mergedjet_subjet_eta",&mergedjet_subjet_eta);
    tree->Branch("mergedjet_subjet_phi",&mergedjet_subjet_phi);
    tree->Branch("mergedjet_subjet_mass",&mergedjet_subjet_mass);
    tree->Branch("mergedjet_subjet_btag",&mergedjet_subjet_btag);
    tree->Branch("mergedjet_subjet_partonFlavour",&mergedjet_subjet_partonFlavour);
    tree->Branch("mergedjet_subjet_hadronFlavour",&mergedjet_subjet_hadronFlavour);

    // FSR Photons
    tree->Branch("nFSRPhotons",&nFSRPhotons,"nFSRPhotons/I");
    tree->Branch("allfsrPhotons_dR",&allfsrPhotons_dR);
    tree->Branch("allfsrPhotons_iso",&allfsrPhotons_iso);
    tree->Branch("allfsrPhotons_pt",&allfsrPhotons_pt);
    tree->Branch("fsrPhotons_lepindex",&fsrPhotons_lepindex);
    tree->Branch("fsrPhotons_pt",&fsrPhotons_pt_float);
    tree->Branch("fsrPhotons_pterr",&fsrPhotons_pterr_float);
    tree->Branch("fsrPhotons_eta",&fsrPhotons_eta_float);
    tree->Branch("fsrPhotons_phi",&fsrPhotons_phi_float);
    tree->Branch("fsrPhotons_dR",&fsrPhotons_dR);
    tree->Branch("fsrPhotons_iso",&fsrPhotons_iso);

    // Z4l? FIXME
    tree->Branch("theta12",&theta12,"theta12/F"); 
    tree->Branch("theta13",&theta13,"theta13/F"); 
    tree->Branch("theta14",&theta14,"theta14/F");
    tree->Branch("minM3l",&minM3l,"minM3l/F"); 
    tree->Branch("Z4lmaxP",&Z4lmaxP,"Z4lmaxP/F"); 
    tree->Branch("minDeltR",&minDeltR,"minDeltR/F"); 
    tree->Branch("m3l_soft",&m3l_soft,"m3l_soft/F");
    tree->Branch("minMass2Lep",&minMass2Lep,"minMass2Lep/F"); 
    tree->Branch("maxMass2Lep",&maxMass2Lep,"maxMass2Lep/F");
    tree->Branch("thetaPhoton",&thetaPhoton,"thetaPhoton/F"); 
    tree->Branch("thetaPhotonZ",&thetaPhotonZ,"thetaPhotonZ/F");

    // Event Category
    tree->Branch("EventCat",&EventCat,"EventCat/I");

    // -------------------------                                                                                                                                                                        
    // GEN level information                                                                                                                                                                            
    // -------------------------                                                                                                                                                                        
    //Event variables
    tree->Branch("GENfinalState",&GENfinalState,"GENfinalState/I");

    // lepton variables
    tree->Branch("GENlep_pt",&GENlep_pt_float);
    tree->Branch("GENlep_eta",&GENlep_eta_float);
    tree->Branch("GENlep_phi",&GENlep_phi_float);
    tree->Branch("GENlep_mass",&GENlep_mass_float);
    tree->Branch("GENlep_id",&GENlep_id);
    tree->Branch("GENlep_status",&GENlep_status);
    tree->Branch("GENlep_MomId",&GENlep_MomId);
    tree->Branch("GENlep_MomMomId",&GENlep_MomMomId);
    tree->Branch("GENlep_Hindex",&GENlep_Hindex,"GENlep_Hindex[4]/I");
    tree->Branch("GENlep_isoCH",&GENlep_isoCH);
    tree->Branch("GENlep_isoNH",&GENlep_isoNH);
    tree->Branch("GENlep_isoPhot",&GENlep_isoPhot);
    tree->Branch("GENlep_RelIso",&GENlep_RelIso);

    // Higgs candidate variables (calculated using selected gen leptons)
    tree->Branch("GENH_pt",&GENH_pt_float);
    tree->Branch("GENH_eta",&GENH_eta_float);
    tree->Branch("GENH_phi",&GENH_phi_float);
    tree->Branch("GENH_mass",&GENH_mass_float);
    tree->Branch("GENmass4l",&GENmass4l,"GENmass4l/F");
    tree->Branch("GENmass4mu",&GENmass4mu,"GENmass4mu/F");
    tree->Branch("GENmass4e",&GENmass4e,"GENmass4e/F");
    tree->Branch("GENmass2e2mu",&GENmass2e2mu,"GENmass2e2mu/F");
    tree->Branch("GENpT4l",&GENpT4l,"GENpT4l/F");
    tree->Branch("GENeta4l",&GENeta4l,"GENeta4l/F");
    tree->Branch("GENrapidity4l",&GENrapidity4l,"GENrapidity4l/F");
    tree->Branch("GENcosTheta1",&GENcosTheta1,"GENcosTheta1/F");
    tree->Branch("GENcosTheta2",&GENcosTheta2,"GENcosTheta2/F");
    tree->Branch("GENcosThetaStar",&GENcosThetaStar,"GENcosThetaStar/F");
    tree->Branch("GENPhi",&GENPhi,"GENPhi/F");
    tree->Branch("GENPhi1",&GENPhi1,"GENPhi1/F");
    tree->Branch("GENMH",&GENMH,"GENMH/F");

    // Z candidate variables
    tree->Branch("GENZ_pt",&GENZ_pt_float);
    tree->Branch("GENZ_eta",&GENZ_eta_float);
    tree->Branch("GENZ_phi",&GENZ_phi_float);
    tree->Branch("GENZ_mass",&GENZ_mass_float);
    tree->Branch("GENZ_DaughtersId",&GENZ_DaughtersId); 
    tree->Branch("GENZ_MomId",&GENZ_MomId);
    tree->Branch("GENmassZ1",&GENmassZ1,"GENmassZ1/F");
    tree->Branch("GENmassZ2",&GENmassZ2,"GENmassZ2/F");  
    tree->Branch("GENpTZ1",&GENpTZ1,"GENpTZ1/F");
    tree->Branch("GENpTZ2",&GENpTZ2,"GENpTZ2/F");
    tree->Branch("GENdPhiZZ",&GENdPhiZZ,"GENdPhiZZ/F");
    tree->Branch("GENmassZZ",&GENmassZZ,"GENmassZZ/F");
    tree->Branch("GENpTZZ",&GENpTZZ,"GENpTZZ/F");

    // Higgs variables directly from GEN particle
    tree->Branch("GENHmass",&GENHmass,"GENHmass/F");*/

    //quark
    tree->Branch("quark_pt", &quark_pt_float);
    tree->Branch("quark_eta", &quark_eta_float);
    tree->Branch("quark_phi", &quark_phi_float);
    tree->Branch("quark_flavour", &quark_flavour);
    tree->Branch("quark_VBF", &quark_VBF);


    // Jets
    tree->Branch("n_GENjets", &n_GENjets);
    tree->Branch("GENjet_pt",&GENjet_pt_float);
    tree->Branch("GENjet_eta",&GENjet_eta_float);
    tree->Branch("GENjet_phi",&GENjet_phi_float);
    tree->Branch("GENjet_mass",&GENjet_mass_float);
    /*tree->Branch("GENnjets_pt30_eta4p7"iamate hltParticleNetONNXJetTags:probtauh&GENnjets_pt30_eta4p7,"GENnjets_pt30_eta4p7/I");
    tree->Branch("GENpt_leadingjet_pt30_eta4p7",&GENpt_leadingjet_pt30_eta4p7,"GENpt_leadingjet_pt30_eta4p7/F");
    tree->Branch("GENabsrapidity_leadingjet_pt30_eta4p7",&GENabsrapidity_leadingjet_pt30_eta4p7,"GENabsrapidity_leadingjet_pt30_eta4p7/F");
    tree->Branch("GENabsdeltarapidity_hleadingjet_pt30_eta4p7",&GENabsdeltarapidity_hleadingjet_pt30_eta4p7,"GENabsdeltarapidity_hleadingjet_pt30_eta4p7/F");
    tree->Branch("GENnjets_pt30_eta2p5",&GENnjets_pt30_eta2p5,"GENnjets_pt30_eta2p5/I");
    tree->Branch("GENpt_leadingjet_pt30_eta2p5",&GENpt_leadingjet_pt30_eta2p5,"GENpt_leadingjet_pt30_eta2p5/F");
    tree->Branch("lheNj",&lheNj,"lheNj/I");
    tree->Branch("lheNb",&lheNb,"lheNb/I");
    tree->Branch("nGenStatus2bHad",&nGenStatus2bHad,"nGenStatus2bHad/I");*/



}

/*void HccAna::setTreeVariables( const edm::Event& iEvent, const edm::EventSetup& iSetup,
                                   std::vector<pat::Muon> selectedMuons, std::vector<pat::Electron> selectedElectrons, 
                                   std::vector<pat::Muon> recoMuons, std::vector<pat::Electron> recoElectrons, 
                                   std::vector<pat::Jet> goodJets, std::vector<float> goodJetQGTagger, 
                                   std::vector<float> goodJetaxis2, std::vector<float> goodJetptD, std::vector<int> goodJetmult,
                                   std::vector<pat::Jet> selectedMergedJets,
                                   std::map<unsigned int, TLorentzVector> selectedFsrMap)*/
void HccAna::setTreeVariables( const edm::Event& iEvent, const edm::EventSetup& iSetup,
                                   std::vector<pat::Jet> goodJets, std::vector<float> goodJetQGTagger,
                                   std::vector<float> goodJetaxis2, std::vector<float> goodJetptD, std::vector<int> goodJetmult,
                                   std::vector<pat::Jet> selectedMergedJets,
                                   edm::Handle<edm::View<pat::Jet> > AK4PuppiJets,
                                   edm::Handle<edm::View<pat::Jet> > AK8PuppiJets,
                                 //edm::Handle<std::vector<reco::PFJet>> hltjets,
                                 //edm::Handle<edm::View<reco::PFJet>> hltjetsForBTag,
                                 //edm::Handle<edm::View<reco::PFJet>> hltAK4PFJetsCorrected,
                                 //edm::Handle<reco::JetTagCollection> pfJetTagCollectionParticleNetprobc,
                                 //edm::Handle<reco::JetTagCollection> pfJetTagCollectionParticleNetprobb,
                                 //edm::Handle<reco::JetTagCollection> pfJetTagCollectionParticleNetprobuds,
                                 //edm::Handle<reco::JetTagCollection> pfJetTagCollectionParticleNetprobg,
                                 //edm::Handle<reco::JetTagCollection> pfJetTagCollectionParticleNetprobtauh,
                                   edm::Handle<BXVector<l1t::Jet> > bxvCaloJets,
                                   edm::Handle<BXVector<l1t::Muon> > bxvCaloMuons,
                                   edm::Handle<BXVector<l1t::EtSum> > bxvCaloHT,
                                 //edm::Handle<edm::View<pat::Muon> > muons,
                                 //edm::Handle<edm::View<pat::Electron> > electrons)
                                   std::vector<pat::Muon> AllMuons, std::vector<pat::Electron> AllElectrons)
{

   

    using namespace edm;
    using namespace pat;
    using namespace std;

    // Jet Info
    //std::cout<<"ELISA = "<<"good jets "<<goodJets.size()<<std::endl;
    for( unsigned int k = 0; k < goodJets.size(); k++) {
      jet_pt.push_back(goodJets[k].pt());
      jet_pt_raw.push_back(goodJets[k].pt());///jet Pt without JEC applied
      jet_eta.push_back(goodJets[k].eta());
      jet_phi.push_back(goodJets[k].phi());
      jet_mass.push_back(goodJets[k].mass());
      jet_csv_cTag_vsL.push_back(goodJets[k].bDiscriminator("pfDeepFlavourJetTags:probc") / (goodJets[k].bDiscriminator("pfDeepFlavourJetTags:probc") + goodJets[k].bDiscriminator("pfDeepFlavourJetTags:probuds") + goodJets[k].bDiscriminator("pfDeepFlavourJetTags:probg")) );
      jet_csv_cTag_vsB.push_back(goodJets[k].bDiscriminator("pfDeepFlavourJetTags:probc") / (goodJets[k].bDiscriminator("pfDeepFlavourJetTags:probc") + goodJets[k].bDiscriminator("pfDeepFlavourJetTags:probb") + goodJets[k].bDiscriminator("pfDeepFlavourJetTags:probbb") + goodJets[k].bDiscriminator("pfDeepFlavourJetTags:problepb")) );
      if ((goodJets[k].bDiscriminator("pfDeepCSVJetTags:probb")+goodJets[k].bDiscriminator("pfDeepCSVJetTags:probbb"))>BTagCut) {
      	jet_isbtag.push_back(1);
      } else {
      	jet_isbtag.push_back(0);
      }
      jet_pfDeepCSVJetTags_probb.push_back(goodJets[k].bDiscriminator("pfDeepCSVJetTags:probb"));
      jet_pfDeepFlavourJetTags_probbb.push_back(goodJets[k].bDiscriminator("pfDeepFlavourJetTags:probbb"));
      jet_pfDeepFlavourJetTags_probc.push_back(goodJets[k].bDiscriminator("pfDeepFlavourJetTags:probc"));
      jet_pfDeepFlavourJetTags_probuds.push_back(goodJets[k].bDiscriminator("pfDeepFlavourJetTags:probuds"));
			
      for(unsigned int imu=0; imu<AllMuons.size(); imu++){
        double this_dR_jetLep = deltaR(goodJets[k].eta(), goodJets[k].phi(), AllMuons[imu].eta(), AllMuons[imu].phi());
        if(this_dR_jetLep<0.6){
          lep_pt.push_back(AllMuons[imu].pt());
          lep_eta.push_back(AllMuons[imu].eta());
          lep_phi.push_back(AllMuons[imu].phi());
          lep_mass.push_back(AllMuons[imu].mass());
          lep_ID.push_back(AllMuons[imu].pdgId());
        }
      }

      for(unsigned int iel=0; iel<AllElectrons.size(); iel++){
        double this_dR_jetLep = deltaR(goodJets[k].eta(), goodJets[k].phi(), AllElectrons[iel].eta(), AllElectrons[iel].phi());
        if(this_dR_jetLep<0.6){
          lep_pt.push_back(AllElectrons[iel].pt());
          lep_eta.push_back(AllElectrons[iel].eta());
          lep_phi.push_back(AllElectrons[iel].phi());
          lep_mass.push_back(AllElectrons[iel].mass());
          lep_ID.push_back(AllElectrons[iel].pdgId());
         }
       }

       
    } // loop over jets


	for(unsigned int jmu=0; jmu<AllMuons.size(); jmu++){
       		ALLlep_pt.push_back(AllMuons[jmu].pt());
          	ALLlep_eta.push_back(AllMuons[jmu].eta());
          	ALLlep_phi.push_back(AllMuons[jmu].phi());
          	ALLlep_mass.push_back(AllMuons[jmu].mass());
          	ALLlep_id.push_back(AllMuons[jmu].pdgId());
        }

	for(unsigned int jel=0; jel<AllElectrons.size(); jel++){
        	ALLlep_pt.push_back(AllElectrons[jel].pt());
          	ALLlep_eta.push_back(AllElectrons[jel].eta());
          	ALLlep_phi.push_back(AllElectrons[jel].phi());
          	ALLlep_mass.push_back(AllElectrons[jel].mass());
          	ALLlep_id.push_back(AllElectrons[jel].pdgId());
         }
       	
    //L1 jets Variables
    for (std::vector<l1t::Jet>::const_iterator l1jet = bxvCaloJets->begin(0); l1jet != bxvCaloJets->end(0); ++l1jet) {
      L1jet_pt.push_back(l1jet->pt());
      L1jet_eta.push_back(l1jet->eta());
      L1jet_phi.push_back(l1jet->phi());
      L1jet_mass.push_back(l1jet->mass());
    }

    //L1 muon Variables
    for (std::vector<l1t::Muon>::const_iterator l1muon = bxvCaloMuons->begin(0); l1muon != bxvCaloMuons->end(0); ++l1muon) {
      L1muon_pt.push_back(l1muon->pt());
      L1muon_eta.push_back(l1muon->eta());
      L1muon_phi.push_back(l1muon->phi());
      L1muon_mass.push_back(l1muon->mass());
      L1muon_qual.push_back(l1muon->hwQual());
    }

    //L1 HT sum
    for (std::vector<l1t::EtSum>::const_iterator l1Et = bxvCaloHT->begin(0); l1Et != bxvCaloHT->end(0); ++l1Et) {
      if (l1Et->getType() == l1t::EtSum::EtSumType::kTotalHt){
        L1ht= l1Et->et();
      }
    }

	
    //hltAK4PFJetsCorrected
    /*for(unsigned int ijet=0; ijet<hltAK4PFJetsCorrected->size(); ijet++){
	  //std::cout<<"index jet: "<<ijet<<std::endl;
      //std::cout<<"jet pt: "<<hltjets->at(ijet).pt()<<std::endl;
	  hltAK4PFJetsCorrected_pt.push_back(hltAK4PFJetsCorrected->at(ijet).pt());
	  hltAK4PFJetsCorrected_eta.push_back(hltAK4PFJetsCorrected->at(ijet).eta());
	  hltAK4PFJetsCorrected_phi.push_back(hltAK4PFJetsCorrected->at(ijet).phi());
	  hltAK4PFJetsCorrected_mass.push_back(hltAK4PFJetsCorrected->at(ijet).mass());
    }*/

    //Puppi AK4jets with ParticleNet taggers
    for(unsigned int ijet=0; ijet<AK4PuppiJets->size(); ijet++){
      AK4PuppiJets_pt.push_back(AK4PuppiJets->at(ijet).pt());
      AK4PuppiJets_eta.push_back(AK4PuppiJets->at(ijet).eta());
      AK4PuppiJets_phi.push_back(AK4PuppiJets->at(ijet).phi());
      AK4PuppiJets_mass.push_back(AK4PuppiJets->at(ijet).mass());

      jet_pfParticleNetAK4JetTags_probb.push_back(AK4PuppiJets->at(ijet).bDiscriminator("pfParticleNetAK4JetTags:probb"));
      jet_pfParticleNetAK4JetTags_probc.push_back(AK4PuppiJets->at(ijet).bDiscriminator("pfParticleNetAK4JetTags:probc"));
      jet_pfParticleNetAK4JetTags_probuds.push_back(AK4PuppiJets->at(ijet).bDiscriminator("pfParticleNetAK4JetTags:probuds"));
      jet_pfParticleNetAK4JetTags_probg.push_back(AK4PuppiJets->at(ijet).bDiscriminator("pfParticleNetAK4JetTags:probg"));
      jet_pfParticleNetAK4JetTags_probtauh.push_back(AK4PuppiJets->at(ijet).bDiscriminator("pfParticleNetAK4JetTags:probtauh"));
      
    }
    
    //Puppi AK8jets with ParticleNet and DeepDoubleX taggers     
    for(unsigned int jjet=0; jjet<AK8PuppiJets->size(); jjet++){
      AK8PuppiJets_pt.push_back(AK8PuppiJets->at(jjet).pt());
      AK8PuppiJets_eta.push_back(AK8PuppiJets->at(jjet).eta());
      AK8PuppiJets_phi.push_back(AK8PuppiJets->at(jjet).phi());
      AK8PuppiJets_mass.push_back(AK8PuppiJets->at(jjet).mass());

      jet_pfParticleNetJetTags_probZbb.push_back(AK8PuppiJets->at(jjet).bDiscriminator("pfParticleNetJetTags:probZbb"));
      jet_pfParticleNetJetTags_probZcc.push_back(AK8PuppiJets->at(jjet).bDiscriminator("pfParticleNetJetTags:probZcc"));
      jet_pfParticleNetJetTags_probZqq.push_back(AK8PuppiJets->at(jjet).bDiscriminator("pfParticleNetJetTags:probZqq"));
      jet_pfParticleNetJetTags_probQCDbb.push_back(AK8PuppiJets->at(jjet).bDiscriminator("pfParticleNetJetTags:probQCDbb"));
      jet_pfParticleNetJetTags_probQCDcc.push_back(AK8PuppiJets->at(jjet).bDiscriminator("pfParticleNetJetTags:probQCDcc"));
      jet_pfParticleNetJetTags_probQCDb.push_back(AK8PuppiJets->at(jjet).bDiscriminator("pfParticleNetJetTags:probQCDb"));
      jet_pfParticleNetJetTags_probQCDc.push_back(AK8PuppiJets->at(jjet).bDiscriminator("pfParticleNetJetTags:probQCDc"));
      jet_pfParticleNetJetTags_probQCDothers.push_back(AK8PuppiJets->at(jjet).bDiscriminator("pfParticleNetJetTags:probQCDothers"));
      jet_pfParticleNetJetTags_probHbb.push_back(AK8PuppiJets->at(jjet).bDiscriminator("pfParticleNetJetTags:probHbb"));
      jet_pfParticleNetJetTags_probHcc.push_back(AK8PuppiJets->at(jjet).bDiscriminator("pfParticleNetJetTags:probHcc"));
      jet_pfParticleNetJetTags_probHqqqq.push_back(AK8PuppiJets->at(jjet).bDiscriminator("pfParticleNetJetTags:probHqqqq"));
      
      jet_pfMassDecorrelatedParticleNetJetTags_probXbb.push_back(AK8PuppiJets->at(jjet).bDiscriminator("pfMassDecorrelatedParticleNetJetTags:probXbb"));
      jet_pfMassDecorrelatedParticleNetJetTags_probXcc.push_back(AK8PuppiJets->at(jjet).bDiscriminator("pfMassDecorrelatedParticleNetJetTags:probXcc"));
    	jet_pfMassDecorrelatedParticleNetJetTags_probXqq.push_back(AK8PuppiJets->at(jjet).bDiscriminator("pfMassDecorrelatedParticleNetJetTags:probXqq"));
      jet_pfMassDecorrelatedParticleNetJetTags_probQCDbb.push_back(AK8PuppiJets->at(jjet).bDiscriminator("pfMassDecorrelatedParticleNetJetTags:probQCDbb"));
      jet_pfMassDecorrelatedParticleNetJetTags_probQCDcc.push_back(AK8PuppiJets->at(jjet).bDiscriminator("pfMassDecorrelatedParticleNetJetTags:probQCDcc"));
      jet_pfMassDecorrelatedParticleNetJetTags_probQCDb.push_back(AK8PuppiJets->at(jjet).bDiscriminator("pfMassDecorrelatedParticleNetJetTags:probQCDb"));
      jet_pfMassDecorrelatedParticleNetJetTags_probQCDc.push_back(AK8PuppiJets->at(jjet).bDiscriminator("pfMassDecorrelatedParticleNetJetTags:probQCDc"));
      jet_pfMassDecorrelatedParticleNetJetTags_probQCDothers.push_back(AK8PuppiJets->at(jjet).bDiscriminator("pfMassDecorrelatedParticleNetJetTags:probQCDothers"));
      
      jet_pfMassIndependentDeepDoubleBvLV2JetTags_probHbb.push_back(AK8PuppiJets->at(jjet).bDiscriminator("pfMassIndependentDeepDoubleBvLV2JetTags:probHbb"));// DeepDoubleX discriminator (mass-decorrelation) for H(Z)->bb vs QCD
      jet_pfMassIndependentDeepDoubleCvLV2JetTags_probHcc.push_back(AK8PuppiJets->at(jjet).bDiscriminator("pfMassIndependentDeepDoubleCvLV2JetTags:probHcc"));// DeepDoubleX discriminator (mass-decorrelation) for H(Z)->cc vs QCD
      jet_pfMassIndependentDeepDoubleCvBV2JetTags_probHcc.push_back(AK8PuppiJets->at(jjet).bDiscriminator("pfMassIndependentDeepDoubleCvBV2JetTags:probHcc"));// DeepDoubleX discriminator (mass-decorrelation) for H(Z)->cc vs for H(Z)->bb
      
    }
    
    for( unsigned int kmu = 0; kmu < AllMuons.size(); kmu++) {
      for(unsigned int kk=0; kk < AK4PuppiJets->size(); kk++){
        bool isMuonFound = false;			
        double this_dR_AKmu = deltaR(AK4PuppiJets_eta.at(kk), AK4PuppiJets_phi.at(kk), AllMuons[kmu].eta(), AllMuons[kmu].phi());
          if(this_dR_AKmu<0.4 && !isMuonFound){ 	
            AK4lep_pt.push_back(AllMuons[kmu].pt());
            AK4lep_eta.push_back(AllMuons[kmu].eta());
            AK4lep_phi.push_back(AllMuons[kmu].phi());
            AK4lep_mass.push_back(AllMuons[kmu].mass());
            AK4lep_id.push_back(AllMuons[kmu].pdgId());
            isMuonFound = true;//stop jet cicle if the muon is asscociated to one AK4 jet
          }	
        }
      }
      
      for(unsigned int kel=0; kel<AllElectrons.size(); kel++){
        for(unsigned int jk=0; jk < AK4PuppiJets->size(); jk++){
          bool isElectronFound = false;
          double this_dR_AKel = deltaR(AK4PuppiJets_eta.at(jk), AK4PuppiJets_phi.at(jk), AllElectrons[kel].eta(), AllElectrons[kel].phi());
            if(this_dR_AKel<0.4 && !isElectronFound){
              AK4lep_pt.push_back(AllElectrons[kel].pt());
              AK4lep_eta.push_back(AllElectrons[kel].eta());
              AK4lep_phi.push_back(AllElectrons[kel].phi());
              AK4lep_mass.push_back(AllElectrons[kel].mass());
              AK4lep_id.push_back(AllElectrons[kel].pdgId());
              isElectronFound = true;//stop jet cicle if the muon is asscociated to one AK4 jet
            }
          }
        }

     //hlt jets
     //std::cout<<"hltPFJetForBtag size: "<< hltjets->size()<<std::endl;
     //std::cout<<"pfJetTagCollection: "<<pfJetTagCollection->size()<<std::endl;
     /*for(unsigned int ijet=0; ijet<hltjetsForBTag->size(); ijet++){
     //std::cout<<"index jet: "<<ijet<<std::endl;
     //std::cout<<"jet pt: "<<hltjets->at(ijet).pt()<<std::endl;
     hltjetForBTag_pt.push_back(hltjetsForBTag->at(ijet).pt());
     hltjetForBTag_eta.push_back(hltjetsForBTag->at(ijet).eta());
     hltjetForBTag_phi.push_back(hltjetsForBTag->at(ijet).phi());
     hltjetForBTag_mass.push_back(hltjetsForBTag->at(ijet).mass());
     //hltParticleNetONNXJetTags_probb.push_back(hltjets->at(ijet).bDiscriminator("hltParticleNetONNXJetTags:probb"));
     //hltParticleNetONNXJetTags_probc.push_back(hltjets->at(ijet).bDiscriminator("hltParticleNetONNXJetTags:probc"));
     //hltParticleNetONNXJetTags_probuds.push_back(hltjets->at(ijet).bDiscriminator("hltParticleNetONNXJetTags:probuds"));
     //hltParticleNetONNXJetTags_probtauh.push_back(hltjets->at(ijet).bDiscriminator("hltParticleNetONNXJetTags:probtauh"));
		
     float tagValue_b = -20;
     float tagValue_c = -20;
     float tagValue_uds = -20;
     float tagValue_g = -20;
     float tagValue_tauh = -20;
     float minDR2_b = 0.01;
     float minDR2_c = 0.01;
     float minDR2_uds = 0.01;
     float minDR2_g = 0.01;
     float minDR2_tauh = 0.01;
      
     int index_tag=0;
     //std::cout<<"pfJetTagCollection: "<<pfJetTagCollection->size()<<std::endl;
	
     for (auto const &tag : *pfJetTagCollectionParticleNetprobc) {
        float dR2 = reco::deltaR2(hltjetsForBTag->at(ijet), *(tag.first));
        //std::cout<<"tag "<<index_tag<<"   deltaR= "<<dR2<<std::endl;
        if (dR2 < minDR2_c) {
          minDR2_c = dR2;
          tagValue_c = tag.second;
        }
        index_tag++;
     }
     for (auto const &tag : *pfJetTagCollectionParticleNetprobb) {
       float dR2 = reco::deltaR2(hltjetsForBTag->at(ijet), *(tag.first));
       //std::cout<<"tag "<<index_tag<<"   deltaR= "<<dR2<<std::endl;
       if (dR2 < minDR2_b) {
         minDR2_b = dR2;
         tagValue_b = tag.second;
       }
       //index_tag++;
      }
      for (auto const &tag : *pfJetTagCollectionParticleNetprobuds) {
        float dR2 = reco::deltaR2(hltjetsForBTag->at(ijet), *(tag.first));
        //std::cout<<"tag "<<index_tag<<"   deltaR= "<<dR2<<std::endl;
        if (dR2 < minDR2_uds) {
          minDR2_uds = dR2;
          tagValue_uds = tag.second;
        }
        //index_tag++;
       }
      for (auto const &tag : *pfJetTagCollectionParticleNetprobg) {
        float dR2 = reco::deltaR2(hltjetsForBTag->at(ijet), *(tag.first));
        //std::cout<<"tag "<<index_tag<<"   deltaR= "<<dR2<<std::endl;
        if (dR2 < minDR2_g) {
          minDR2_g = dR2;
          tagValue_g = tag.second;
        }
        //index_tag++;
      }
      for (auto const &tag : *pfJetTagCollectionParticleNetprobtauh) {
        float dR2 = reco::deltaR2(hltjetsForBTag->at(ijet), *(tag.first));
        //std::cout<<"tag "<<index_tag<<"   deltaR= "<<dR2<<std::endl;
          if (dR2 < minDR2_tauh) {
            minDR2_tauh = dR2;
            tagValue_tauh = tag.second;
          }
	      //index_tag++;
      }
      hltParticleNetONNXJetTags_probc.push_back(tagValue_c);	
      hltParticleNetONNXJetTags_probb.push_back(tagValue_b);	
      hltParticleNetONNXJetTags_probuds.push_back(tagValue_uds);	
      hltParticleNetONNXJetTags_probg.push_back(tagValue_g);	
      hltParticleNetONNXJetTags_probtauh.push_back(tagValue_tauh);	
    } */ 

    //std::cout<<"hltPFJetForBtag size: "<< hltjets->size()<<std::endl;

    /*for (auto const &hltjet : *hltjets) {
      std::cout<<"jet pt "<<hltjet.pt()<<std::endl;
      hltjet_pt.push_back(hltjet.pt());
      float tagValue = -20;
      float minDR2 = 0.01;
      
      for (auto const &tag : *pfJetTagCollection) {
        float dR2 = reco::deltaR2(hltjet, *(tag.first));
          if (dR2 < minDR2) {
            minDR2 = dR2;
            tagValue = tag.second;
          }
      }
      hltParticleNetONNXJetTags_probc.push_back(tagValue);	
      
				
    }*/
}


void HccAna::setGENVariables(edm::Handle<reco::GenParticleCollection> prunedgenParticles,
                                 edm::Handle<edm::View<pat::PackedGenParticle> > packedgenParticles,
                                 edm::Handle<edm::View<reco::GenJet> > genJets)
{
  reco::GenParticleCollection::const_iterator genPart;
  bool first_quarkgen=false;
  for(genPart = prunedgenParticles->begin(); genPart != prunedgenParticles->end(); genPart++) {
    if(abs(genPart->pdgId())==1 || abs(genPart->pdgId())==2 || abs(genPart->pdgId())==3 || abs(genPart->pdgId())==4 || abs(genPart->pdgId())==5 || abs(genPart->pdgId())==6  || abs(genPart->pdgId())==7  || abs(genPart->pdgId())==23  || abs(genPart->pdgId())==24 || abs(genPart->pdgId())==25){
      //cout<<"pdg: "<< abs(genPart->pdgId()) <<"  pT: "<<genPart->pt() <<"   eta: "<<genPart->eta() <<"   phi: "<<genPart->phi() <<endl;
      const reco::Candidate * mom = genPart->mother(0);
      //cout<<"mother: "<< mom->pdgId()<<"   pT: "<< mom->pt() <<"   eta: "<< mom->eta() <<"   phi: "<< mom->phi() <<endl;
    bool Higgs_daughter=false;
    int n = genPart->numberOfDaughters();
    if(mom->pdgId()==2212 && first_quarkgen==false){
      for(int j_d = 0; j_d < n; ++ j_d) {
        const reco::Candidate * d = genPart->daughter( j_d );
        if((d->pdgId())==25){
          Higgs_daughter=true;
        }

        if(Higgs_daughter==true && (abs(d->pdgId())==1 || abs(d->pdgId())==2 || abs(d->pdgId())==3  || abs(d->pdgId())==4 || abs(d->pdgId())==5 || abs(d->pdgId())==6 || abs(d->pdgId())==7)){
          quark_pt.push_back(d->pt());
          quark_eta.push_back(d->eta());
          quark_phi.push_back(d->phi());
          quark_flavour.push_back(d->pdgId());
          quark_VBF.push_back(true);
          first_quarkgen=true;
        }

      }
    }

    if(( abs(genPart->pdgId())==4 || abs(genPart->pdgId())==5) && (mom->pdgId())==25){
      quark_pt.push_back(genPart->pt());
      quark_eta.push_back(genPart->eta());
      quark_phi.push_back(genPart->phi());
      quark_flavour.push_back(genPart->pdgId());
      quark_VBF.push_back(false);
     }

		

  }

    /*if( abs(genPart->pdgId())==1 || abs(genPart->pdgId())==2 || abs(genPart->pdgId())==3 || abs(genPart->pdgId())==4 || abs(genPart->pdgId())==5 || abs(genPart->pdgId())==17 || abs(genPart->pdgId())==21   ){
    quark_pt.push_back(genPart->pt());
    quark_eta.push_back(genPart->eta());
    quark_phi.push_back(genPart->phi());
    quark_flavour.push_back(genPart->pdgId());
    }*/

}

	edm::View<reco::GenJet>::const_iterator genjet;

  for(genjet = genJets->begin(); genjet != genJets->end(); genjet++) {

	GENjet_pt.push_back(genjet->pt());
	GENjet_eta.push_back(genjet->eta());
	GENjet_phi.push_back(genjet->phi());
	GENjet_mass.push_back(genjet->mass());
	} //loop over gen jets


}


// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void
HccAna::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
    //The following says we do not know what parameters are allowed so do no validation
    // Please change this to state exactly what you do use, even if it is no parameters
    edm::ParameterSetDescription desc;
    desc.setUnknown();
    descriptions.addDefault(desc);
}

//define this as a plug-in
DEFINE_FWK_MODULE(HccAna);

//  LocalWords:  ecalDriven
