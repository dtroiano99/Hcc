#ifndef HCCHELPER_H
#define HCCHELPER_H

#define PI 3.14159

//system includes
#include <memory>
#include <string>
#include <map>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <algorithm>
#include <stdlib.h>
#include <cmath>
#include <iomanip>

#include "TROOT.h"
#include "TH1.h"
#include "TH2.h"
#include "TTree.h"
#include "TMath.h"
#include "TString.h"
#include "TLorentzVector.h"
#include "TLorentzRotation.h"

// user include files 
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "DataFormats/HepMCCandidate/interface/GenParticle.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"
#include "TROOT.h"
#include "TH1.h"
#include "TH2.h"
#include "TTree.h"
#include "TMath.h"
#include "TString.h"
#include "FWCore/Framework/interface/LuminosityBlock.h"
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "FWCore/Utilities/interface/InputTag.h"
#include "Math/VectorUtil.h"
#include "DataFormats/Common/interface/MergeableCounter.h"
#include "DataFormats/Math/interface/Point3D.h"
#include "DataFormats/Common/interface/RefToBase.h"
#include "DataFormats/Math/interface/deltaR.h"
#include "DataFormats/Math/interface/deltaPhi.h"
#include "CommonTools/Utils/interface/StringCutObjectSelector.h"
#include "DataFormats/VertexReco/interface/Vertex.h"
#include "RecoVertex/VertexTools/interface/VertexDistance3D.h"
//#include "RecoEgamma/EgammaTools/interface/ConversionTools.h"
#include "CommonTools/Egamma/interface/ConversionTools.h"

// PAT
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
#include "DataFormats/ParticleFlowCandidate/interface/PFCandidate.h"

//Boost
#include "CommonTools/CandUtils/interface/CenterOfMassBooster.h"
#include "CommonTools/CandUtils/interface/Booster.h"

//Muon MVA
//#include "MuonMVAReader/Reader/interface/MuonGBRForestReader.hpp"
//class MuonGBRForestReader;
class HccHelper
{

public:

    HccHelper();
    ~HccHelper();
  
    std::vector<pat::Electron> goodLooseElectrons2012(edm::Handle<edm::View<pat::Electron> > Electrons, double elPtCut);
    std::vector<pat::Electron> goodLooseElectrons2012(edm::Handle<edm::View<pat::Electron> > Electrons, edm::Handle<edm::View<pat::Electron> > ElectronsUnS, double elPtCut);
    std::vector<pat::Muon> goodLooseMuons2012(edm::Handle<edm::View<pat::Muon> > Muons, double muPtCut);
    std::vector<pat::Tau> goodLooseTaus2015(edm::Handle<edm::View<pat::Tau> > Taus, double tauPtCut);
    std::vector<pat::Photon> goodLoosePhotons2015(edm::Handle<edm::View<pat::Photon> > Photons, double phoPtCut);

    std::vector<pat::Electron> goodElectrons2015_noIso_noBdt(std::vector<pat::Electron> Electrons, double elecPtCut, std::string elecID, const reco::Vertex *&vertex,const edm::Event& iEvent, double sip3dCut, bool ScaleAndSmearing); 
    std::vector<pat::Muon> goodMuons2015_noIso_noPf(std::vector<pat::Muon> Muons, double muPtCut, const reco::Vertex *&vertex);
    std::vector<pat::Tau> goodTaus2015(std::vector<pat::Tau> Taus, double tauPtCut);
    std::vector<pat::Photon> goodPhotons2015(std::vector<pat::Photon> Photons, double phoPtCut, int year);

    void cleanOverlappingLeptons(std::vector<pat::Muon> &Muons, std::vector<pat::Electron> &Electrons,const reco::Vertex *&vertex);
    void cleanOverlappingTaus(std::vector<pat::Muon> &Muons, std::vector<pat::Electron> &Electrons, std::vector<pat::Tau> &Taus, double isoCutMu, double IsoCutEl, double muRho, double elRho);

    double getSIP3D(pat::Muon muon);
    double getSIP3D(pat::Electron electron);
    double getPUIso(pat::Muon muon, double Rho);
    double getPUIso03(pat::Muon muon, double Rho);
    double getPUIso(pat::Electron elec, double Rho);
    double getPUIso03(pat::Electron elec, double Rho);
    double pfIso(pat::Muon muon, double Rho);
    double pfIso03(pat::Muon muon, double Rho);
    double pfIso(pat::Electron elec, double Rho);
    double pfIso03(pat::Electron elec, double Rho);
    double miniIsolation(edm::Handle<pat::PackedCandidateCollection> pfcands, const reco::Candidate* ptcl, double r_iso_min, double r_iso_max, double kt_scale, double rho, bool charged_only);
    double ptRatio(pat::Electron electron, edm::Handle<edm::View<pat::Jet> > jets,bool isMC);
    double ptRatio(pat::Muon muon, edm::Handle<edm::View<pat::Jet> > jets,bool isMC);
    double ptRel(pat::Electron electron, edm::Handle<edm::View<pat::Jet> > jets,bool isMC);
    double ptRel(pat::Muon muon, edm::Handle<edm::View<pat::Jet> > jets,bool isMC);
    double photonPfIso03(pat::PFParticle pho, edm::Handle<pat::PackedCandidateCollection> pfcands);

    bool passTight_Id(pat::Muon muon, const reco::Vertex *&vertex);
    bool passTight_Id_SUS(pat::Muon muon, const reco::Vertex *&vertex);
    //bool passTight_BDT_Id(pat::Electron electron, float mvavalue, int year);
    bool passTight_BDT_Id(pat::Electron electron, int year);
    bool passTight_Id_SUS(pat::Electron electron, std::string elecID, const reco::Vertex *&vertex, const reco::BeamSpot BS, std::vector<reco::Conversion> theConversions, int year);
    
    bool isTrackerHighPt(pat::Muon muon, const reco::Vertex *&vertex);
    //float get_Muon_MVA_Value(pat::Muon muon, edm::Handle<reco::VertexCollection> vertices, double rho, int year, const reco::Vertex *&vertex);
    //bool passTight_BDT_Id(pat::Muon muon, edm::Handle<reco::VertexCollection> vertices, double rho, int year, const reco::Vertex *&vertex);
    //float get_Muon_MVA_Value(pat::Muon muon, const reco::Vertex *&vertices, double rho, int year);
    //bool passTight_BDT_Id(pat::Muon muon, const reco::Vertex *&vertices, double rho, int year);

    float kfactor_qqZZ_qcd_dPhi(float GENdPhiZZ, int finalState);
    float kfactor_qqZZ_qcd_Pt(float GENpTZZ, int finalState);
    float kfactor_qqZZ_qcd_M(float GENmassZZ, int finalState);

    float dataMC(pat::Electron electron, TH2F* hElecScaleFac, TH2F* hElecScalFac_Cracks, TH2F* hElecScaleFacGsf, TH2F* hElecScaleFacGsfLowET);
    float dataMCErr(pat::Electron electron, TH2F* hElecScaleFac, TH2F* hElecScalFacUnc_Cracks);
    float dataMC(pat::Muon muon, TH2F* hMuScaleFac);
    float dataMCErr(pat::Muon muon, TH2F* hMuScaleFac);
    float dataMC(double pt, float eta, TH2F* hMuScaleFac);
    float dataMCErr(double pt, float eta, TH2F* hMuScaleFac);
    
    float get_bTagEffi(float _pt_jet, float _eta_jet, TH2F* hbTagEffi);
    
    float getDVBF2jetsConstant(float ZZMass);
    float getDVBF1jetConstant(float ZZMass);
    float getDWHhConstant(float ZZMass);
    float getDZHhConstant(float ZZMass);

    float getDbkgVBFdecConstant(int ZZflav, float ZZMass);
    float getDbkgVHdecConstant(int ZZflav, float ZZMass);

    float getDbkgkinConstant(int ZZflav, float ZZMass);
    float getDbkgConstant(int ZZflav, float ZZMass);

    enum MuonEffectiveAreaType {
        kMuTrkIso03, 
        kMuEcalIso03, 
        kMuHcalIso03, 
        kMuTrkIso05, 
        kMuEcalIso05, 
        kMuHcalIso05, 
        kMuChargedIso03, 
        kMuGammaIso03, 
        kMuNeutralHadronIso03, 
        kMuGammaAndNeutralHadronIso03,
        kMuGammaIso03Tight, 
        kMuNeutralHadronIso03Tight, 
        kMuGammaAndNeutralHadronIso03Tight,
        kMuChargedIso04, 
        kMuGammaIso04, 
        kMuNeutralHadronIso04, 
        kMuGammaAndNeutralHadronIso04,
        kMuGammaIso04Tight, 
        kMuNeutralHadronIso04Tight, 
        kMuGammaAndNeutralHadronIso04Tight,
        kMuGammaIsoDR0p0To0p1,
        kMuGammaIsoDR0p1To0p2,
        kMuGammaIsoDR0p2To0p3,
        kMuGammaIsoDR0p3To0p4,
        kMuGammaIsoDR0p4To0p5,
        kMuNeutralHadronIsoDR0p0To0p1,
        kMuNeutralHadronIsoDR0p1To0p2,
        kMuNeutralHadronIsoDR0p2To0p3,
        kMuNeutralHadronIsoDR0p3To0p4,
        kMuNeutralHadronIsoDR0p4To0p5,
        kMuGammaIso05,
        kMuNeutralIso05
    };
  
    enum MuonEffectiveAreaTarget {
        kMuNoCorr,
        kMuEAData2011,
        kMuEASummer11MC,
        kMuEAFall11MC,
        kMuEAData2012
    };

    enum ElecEffectiveAreaType {
        kEGammaNeutralHadIso04,
        kENeutralHadIso04,
        kEGammaNeutralIso04,
        kEGammaIso04,
        kENeutralHadIso03,
        kEGammaNeutralHadIso03,
        kEGammaIso03    
    };

    enum ElecEffectiveAreaTarget {
        kElNoCorr,
        kElEAData2015,
        kElEAData2012,
        kElEAData2011,
        kElEAFall11MC
    };

    double MuonEffArea(MuonEffectiveAreaType type, double SCEta, MuonEffectiveAreaTarget EffectiveAreaTarget);
    double ElecEffArea(ElecEffectiveAreaType type, double SCEta, ElecEffectiveAreaTarget EffectiveAreaTarget);

    MuonEffectiveAreaType muEAtype;
    MuonEffectiveAreaTarget muEAtarget;
    ElecEffectiveAreaType elEAtype;
    ElecEffectiveAreaTarget elEAtarget;

    TSpline3 *DbkgkinSpline2e2mu;
    TSpline3 *DbkgkinSpline4e;
    TSpline3 *DbkgkinSpline4mu;

    TSpline3 *DbkgVBFdecSpline2l2l;
    TSpline3 *DbkgVBFdecSpline4l;
    TSpline3 *DbkgVHdecSpline2l2l;
    TSpline3 *DbkgVHdecSpline4l;

    TSpline3 *DjjVBFSpline;
    TSpline3 *DjVBFSpline;
    TSpline3 *DjjZHSpline;
    TSpline3 *DjjWHSpline;


};

#endif


#ifndef HCCHELPER_CC
#define HCCHELPER_CC

HccHelper::HccHelper()
{
    muEAtype = kMuGammaAndNeutralHadronIso04;
    muEAtarget = kMuEAData2012;
    elEAtype = kEGammaNeutralHadIso04;
    elEAtarget = kElEAData2015;
    //declarations

    edm::FileInPath DbkgkinSpline2e2mufileInPath("Hcc/HccAna/data/SmoothKDConstant_m4l_Dbkgkin_2e2mu13TeV.root");
    TFile *fDbkgkinSpline2e2mu = TFile::Open(DbkgkinSpline2e2mufileInPath.fullPath().c_str());
    DbkgkinSpline2e2mu = (TSpline3*) fDbkgkinSpline2e2mu->Get("sp_gr_varReco_Constant_Smooth");
    fDbkgkinSpline2e2mu->Close();
    delete fDbkgkinSpline2e2mu;

    edm::FileInPath DbkgkinSpline4efileInPath("Hcc/HccAna/data/SmoothKDConstant_m4l_Dbkgkin_4e13TeV.root");
    TFile *fDbkgkinSpline4e = TFile::Open(DbkgkinSpline4efileInPath.fullPath().c_str());
    DbkgkinSpline4e = (TSpline3*) fDbkgkinSpline4e->Get("sp_gr_varReco_Constant_Smooth");
    fDbkgkinSpline4e->Close();
    delete fDbkgkinSpline4e;

    edm::FileInPath DbkgkinSpline4mufileInPath("Hcc/HccAna/data/SmoothKDConstant_m4l_Dbkgkin_4mu13TeV.root");
    TFile *fDbkgkinSpline4mu = TFile::Open(DbkgkinSpline4mufileInPath.fullPath().c_str());
    DbkgkinSpline4mu = (TSpline3*) fDbkgkinSpline4mu->Get("sp_gr_varReco_Constant_Smooth");
    fDbkgkinSpline4mu->Close();
    delete fDbkgkinSpline4mu;

    edm::FileInPath DbkgVBFdecSpline2l2lfileInPath("Hcc/HccAna/data/SmoothKDConstant_m4l_DbkgjjEWQCD_2l2l_JJVBFTagged_13TeV.root");
    TFile *fDbkgVBFdecSpline2l2l = TFile::Open(DbkgVBFdecSpline2l2lfileInPath.fullPath().c_str());
    DbkgVBFdecSpline2l2l = (TSpline3*) fDbkgVBFdecSpline2l2l->Get("sp_gr_varReco_Constant_Smooth");
    fDbkgVBFdecSpline2l2l->Close();
    delete fDbkgVBFdecSpline2l2l;

    edm::FileInPath DbkgVBFdecSpline4lfileInPath("Hcc/HccAna/data/SmoothKDConstant_m4l_DbkgjjEWQCD_4l_JJVBFTagged_13TeV.root");
    TFile *fDbkgVBFdecSpline4l = TFile::Open(DbkgVBFdecSpline4lfileInPath.fullPath().c_str());
    DbkgVBFdecSpline4l = (TSpline3*) fDbkgVBFdecSpline4l->Get("sp_gr_varReco_Constant_Smooth");
    fDbkgVBFdecSpline4l->Close();
    delete fDbkgVBFdecSpline4l;

    edm::FileInPath DbkgVHdecSpline2l2lfileInPath("Hcc/HccAna/data/SmoothKDConstant_m4l_DbkgjjEWQCD_2l2l_HadVHTagged_13TeV.root");
    TFile *fDbkgVHdecSpline2l2l = TFile::Open(DbkgVHdecSpline2l2lfileInPath.fullPath().c_str());
    DbkgVHdecSpline2l2l = (TSpline3*) fDbkgVHdecSpline2l2l->Get("sp_gr_varReco_Constant_Smooth");
    fDbkgVHdecSpline2l2l->Close();
    delete fDbkgVHdecSpline2l2l;

    edm::FileInPath DbkgVHdecSpline4lfileInPath("Hcc/HccAna/data/SmoothKDConstant_m4l_DbkgjjEWQCD_4l_HadVHTagged_13TeV.root");
    TFile *fDbkgVHdecSpline4l = TFile::Open(DbkgVHdecSpline4lfileInPath.fullPath().c_str());
    DbkgVHdecSpline4l = (TSpline3*) fDbkgVHdecSpline4l->Get("sp_gr_varReco_Constant_Smooth");
    fDbkgVHdecSpline4l->Close();
    delete fDbkgVHdecSpline4l;

    edm::FileInPath DjjVBFSplinefileInPath("Hcc/HccAna/data/SmoothKDConstant_m4l_DjjVBF13TeV.root");
    TFile *fDjjVBFSpline = TFile::Open(DjjVBFSplinefileInPath.fullPath().c_str());
    DjjVBFSpline = (TSpline3*) fDjjVBFSpline->Get("sp_gr_varReco_Constant_Smooth");
    fDjjVBFSpline->Close();
    delete fDjjVBFSpline;

    edm::FileInPath DjVBFSplinefileInPath("Hcc/HccAna/data/SmoothKDConstant_m4l_DjVBF13TeV.root");
    TFile *fDjVBFSpline = TFile::Open(DjVBFSplinefileInPath.fullPath().c_str());
    DjVBFSpline = (TSpline3*) fDjVBFSpline->Get("sp_gr_varReco_Constant_Smooth");
    fDjVBFSpline->Close();
    delete fDjVBFSpline;

    edm::FileInPath DjjZHSplinefileInPath("Hcc/HccAna/data/SmoothKDConstant_m4l_DjjZH13TeV.root");
    TFile *fDjjZHSpline = TFile::Open(DjjZHSplinefileInPath.fullPath().c_str());
    DjjZHSpline = (TSpline3*) fDjjZHSpline->Get("sp_gr_varReco_Constant_Smooth");
    fDjjZHSpline->Close();
    delete fDjjZHSpline;

    edm::FileInPath DjjWHSplinefileInPath("Hcc/HccAna/data/SmoothKDConstant_m4l_DjjWH13TeV.root");
    TFile *fDjjWHSpline = TFile::Open(DjjWHSplinefileInPath.fullPath().c_str());
    DjjWHSpline = (TSpline3*) fDjjWHSpline->Get("sp_gr_varReco_Constant_Smooth");
    fDjjWHSpline->Close();
    delete fDjjWHSpline;


}


HccHelper::~HccHelper()
{
    //destructor ---do nothing
}

std::vector<pat::Electron> HccHelper::goodLooseElectrons2012(edm::Handle<edm::View<pat::Electron> > Electrons, double elPtCut) {
    using namespace pat;
    using namespace std;    
    vector<pat::Electron> bestElectrons;
    for(edm::View<pat::Electron>::const_iterator elec=Electrons->begin(); elec!=Electrons->end(); ++elec) {        

//        if( abs(elec->eta()) < 2.5 && elec->pt() > elPtCut) {
        if( abs(elec->eta()) < 2.5 && elec->pt() > 0) {
            bestElectrons.push_back(*elec);
        }
    }
    return bestElectrons;    
}

std::vector<pat::Electron> HccHelper::goodLooseElectrons2012(edm::Handle<edm::View<pat::Electron> > Electrons, edm::Handle<edm::View<pat::Electron> > ElectronsUnS, double elPtCut) {
    using namespace pat;
    using namespace std;
    vector<pat::Electron> bestElectrons;
    vector <bool> Ele_passLoose;
    for(edm::View<pat::Electron>::const_iterator elec=Electrons->begin(); elec!=Electrons->end(); ++elec) {

        if( abs(elec->eta()) < 2.5 && elec->pt() > 0) {
            Ele_passLoose.push_back(true);
        }
        else    Ele_passLoose.push_back(false);
    }
    int i = 0;
    for(edm::View<pat::Electron>::const_iterator elec_=ElectronsUnS->begin(); elec_!=ElectronsUnS->end(); ++elec_) {
        if(Ele_passLoose[i]) {
            bestElectrons.push_back(*elec_);
        }
        i++;
    }
    return bestElectrons;
}

std::vector<pat::Muon> HccHelper::goodLooseMuons2012(edm::Handle<edm::View<pat::Muon> > Muons, double muPtCut) {
    using namespace pat;
    using namespace std;    
    vector<pat::Muon> bestMuons;    
    for(edm::View<pat::Muon>::const_iterator mu=Muons->begin(); mu != Muons->end(); ++mu) {
        //std::cout<<"global? "<<mu->isGlobalMuon()<<" tracker? "<<mu->isTrackerMuon()<<" PF "<<mu->isPFMuon()<<" pt: "<< mu->pt()<<std::endl;
		if(mu->pt() > muPtCut && fabs(mu->eta()) < 2.4 && mu->isLooseMuon()){
            bestMuons.push_back(*mu);
        }
    }
    return bestMuons;    
}


std::vector<pat::Tau> HccHelper::goodLooseTaus2015(edm::Handle<edm::View<pat::Tau> > Taus, double tauPtCut) {
    using namespace pat;
    using namespace std;    
    vector<pat::Tau> bestTaus;    
    for(edm::View<pat::Tau>::const_iterator tau=Taus->begin(); tau != Taus->end(); ++tau) {
        if( fabs(tau->eta()) < 2.3 && tau->pt() > tauPtCut) {
            bestTaus.push_back(*tau);
        }
    }
    return bestTaus;    
}


std::vector<pat::Photon> HccHelper::goodLoosePhotons2015(edm::Handle<edm::View<pat::Photon> > Photons, double phoPtCut) {
    using namespace pat;
    using namespace std;    
    vector<pat::Photon> bestPhotons;    
    for(edm::View<pat::Photon>::const_iterator photon=Photons->begin(); photon != Photons->end(); ++photon) {
        //if( fabs(photon->eta()) < 2.3 && photon->pt() > phoPtCut) {
            bestPhotons.push_back(*photon);
        //}
    }
    return bestPhotons;    
}


std::vector<pat::Muon> HccHelper::goodMuons2015_noIso_noPf(std::vector<pat::Muon> Muons, double muPtCut, const reco::Vertex *&vertex)
{
    //using namespace edm;
    using namespace pat;
    using namespace std;
    vector<pat::Muon> bestMuons;
    for(unsigned int i = 0; i < Muons.size(); i++) {
        //std::cout<<"pt: "<<Muons[i].pt()<<std::endl;
        if( Muons[i].pt() > muPtCut && abs(Muons[i].eta()) < 2.4 && Muons[i].isTightMuon(*vertex))
			bestMuons.push_back(Muons[i]);
    }
    return bestMuons;

}

std::vector<pat::Electron> HccHelper::goodElectrons2015_noIso_noBdt(std::vector<pat::Electron> Electrons, double elecPtCut, std::string elecID, const reco::Vertex *&vertex,const edm::Event& iEvent, double sip3dCut, bool ScaleAndSmearing)
{
    using namespace edm;
    using namespace pat;
    using namespace std;

    vector<pat::Electron> bestElectrons;
  
    /****** E L E C T R O N  C U T S ******/
    int missingHitsCuts = 99999;
    double dxyCut = 0.5;
    double dzCut = 1;

//std::cout<<Electrons.size()<<std::endl;

    for(unsigned int i = 0; i < Electrons.size(); i++) {

//std::cout<<ScaleAndSmearing<<"\t"<<Electrons[i].energy()<<std::endl;



//std::cout<<"Before = "<<Electrons[i].pt()<<"\t"<<Electrons[i].eta()<<"\t"<<Electrons[i].phi()<<"\t"<<Electrons[i].mass()<<std::endl;
if(ScaleAndSmearing){
//std::cout<<"Before = "<<Electrons[i].pt()<<"\t"<<Electrons[i].eta()<<"\t"<<Electrons[i].phi()<<"\t"<<Electrons[i].mass()<<std::endl;

	auto corrP4  = Electrons[i].p4();// * Electrons[i].userFloat("ecalTrkEnergyPostCorr") / Electrons[i].energy();
	Electrons[i].setP4(corrP4);

//std::cout<<"After = "<<Electrons[i].pt()<<"\t"<<Electrons[i].eta()<<"\t"<<Electrons[i].phi()<<"\t"<<Electrons[i].mass()<<std::endl;
//	if(Electrons[i].pt() < elecPtCut) continue;

}
else
   elecPtCut = 5;

//std::cout<<ScaleAndSmearing<<"\t"<<Electrons[i].energy()<<std::endl;
//std::cout<<"\t"<<std::endl;
//std::cout<<Electrons[i].pt()<<std::endl;



        //std::cout<<"el pt: "<<Electrons[i].pt()<<" eta: "<<Electrons[i].eta()<<" phi: "<<Electrons[i].phi()<<std::endl;
    if(Electrons[i].pt() > elecPtCut){
        if( abs(getSIP3D(Electrons[i])) < sip3dCut) {
            if (fabs(Electrons[i].gsfTrack()->dxy(vertex->position())) < dxyCut) {
                if (fabs(Electrons[i].gsfTrack()->dz(vertex->position())) < dzCut ) {                  
                    int misHits = Electrons[i].gsfTrack()->hitPattern().numberOfAllHits(reco::HitPattern::MISSING_INNER_HITS); // for miniAOD
                    if (misHits < missingHitsCuts) { bestElectrons.push_back(Electrons[i]);} //else {std::cout<<"el with pt "<<Electrons[i].pt()<<" failed misHitsCut "<<misHits <<std::endl;}
                }  //else {std::cout<<"el with pt "<<Electrons[i].pt()<<" failed dzCut "<<fabs(Electrons[i].gsfTrack()->dz(vertex->position())) <<std::endl;}
            } //else {std::cout<<"el with pt "<<Electrons[i].pt()<<" failed dxyCut "<<fabs(Electrons[i].gsfTrack()->dxy(vertex->position())) <<std::endl;}
        } //else {std::cout<<"el with pt "<<Electrons[i].pt()<<" failed sip3dcut "<<abs(getSIP3D(Electrons[i]))<<std::endl;}
    }
}  

//std::cout<<bestElectrons.size()<<std::endl;

    return bestElectrons;
}

std::vector<pat::Tau> HccHelper::goodTaus2015(std::vector<pat::Tau> Taus, double tauPtCut)
{
    using namespace edm;
    using namespace pat;
    using namespace std;

    vector<pat::Tau> bestTaus;
  
    for(unsigned int i = 0; i < Taus.size(); i++) {

        if ( Taus[i].pt()<tauPtCut ) continue;
        if ( Taus[i].tauID("byLooseIsolationMVArun2v1DBnewDMwLT") < 0.5) continue;
        bestTaus.push_back(Taus[i]);

    }
  
    return bestTaus;
}

std::vector<pat::Photon> HccHelper::goodPhotons2015(std::vector<pat::Photon> Photons, double photonPtCut, int year)
{
    using namespace edm;
    using namespace pat;
    using namespace std;

    vector<pat::Photon> bestPhotons;
  
    for(unsigned int i = 0; i < Photons.size(); i++) {

        /*
        if ( Photons[i].pt()<photonPtCut ) continue;

        float phoid;
        try {
            if(year == 2016)
                phoid=Photons[i].photonID("mvaPhoID-Spring15-25ns-nonTrig-V2p1-wp90");
            else if(year == 2017)
                phoid=Photons[i].photonID("PhotonMVAEstimatorRun2Spring16NonTrigV1Values");
            else if(year == 2018)
                phoid=Photons[i].photonID("cutBasedPhotonID-Fall17-94X-V2-loose");
        }
        catch(...) {
            std::cout<<"photon ID  missing!"<<std::endl;
            phoid=0.0;
        }
        if ( phoid < 0.5) continue;

        if ( Photons[i].hasPixelSeed() ) continue; 
        */ 
        bestPhotons.push_back(Photons[i]);

    }
  
    return bestPhotons;
}


double HccHelper::miniIsolation(edm::Handle<pat::PackedCandidateCollection> pfcands, const reco::Candidate* ptcl, double r_iso_min, double r_iso_max, double kt_scale, double rho, bool charged_only) {

    double deadcone_nh(0.), deadcone_ch(0.), deadcone_ph(0.), deadcone_pu(0.);
    double EA=0.0;
    if(ptcl->isElectron()) {
        if (fabs(ptcl->eta())>1.479) {deadcone_ch = 0.015; deadcone_pu = 0.015; deadcone_ph = 0.08;}
        if (fabs(ptcl->eta())>=0.0   && fabs(ptcl->eta())<1.0)   EA=0.1752;
        if (fabs(ptcl->eta())>=1.0   && fabs(ptcl->eta())<1.479) EA=0.1862;
        if (fabs(ptcl->eta())>=1.479 && fabs(ptcl->eta())<2.0)   EA=0.1411;
        if (fabs(ptcl->eta())>=2.0   && fabs(ptcl->eta())<2.2)   EA=0.1534;
        if (fabs(ptcl->eta())>=2.2   && fabs(ptcl->eta())<2.3)   EA=0.1903;
        if (fabs(ptcl->eta())>=2.3   && fabs(ptcl->eta())<2.4)   EA=0.2243;
        if (fabs(ptcl->eta())>=2.4   && fabs(ptcl->eta())<2.5)   EA=0.2687;
    } else if(ptcl->isMuon()) {
        deadcone_ch = 0.0001; deadcone_pu = 0.01; deadcone_ph = 0.01;deadcone_nh = 0.01;
        if (fabs(ptcl->eta())>=0.0 && fabs(ptcl->eta())<0.8) EA=0.0735;
        if (fabs(ptcl->eta())>=0.8 && fabs(ptcl->eta())<1.3) EA=0.0619;
        if (fabs(ptcl->eta())>=1.3 && fabs(ptcl->eta())<2.0) EA=0.0465;
        if (fabs(ptcl->eta())>=2.0 && fabs(ptcl->eta())<2.2) EA=0.0433;
        if (fabs(ptcl->eta())>=2.2 && fabs(ptcl->eta())<2.5) EA=0.0577;
    }

    double iso_nh(0.); double iso_ch(0.);
    double iso_ph(0.); double iso_pu(0.);
    double ptThresh(0.5);
    if (ptcl->isElectron()) ptThresh = 0;
    double r_iso = max(r_iso_min,min(r_iso_max, kt_scale/ptcl->pt()));

    for (const pat::PackedCandidate &pfc : *pfcands) {
        if (abs(pfc.pdgId())<7) continue;

        double dr = deltaR(pfc, *ptcl);
        if (dr > r_iso) continue;

        //////////////////  NEUTRALS  /////////////////////////
        if (pfc.charge()==0){
            if (pfc.pt()>ptThresh) {
                /////////// PHOTONS ////////////
                if (abs(pfc.pdgId())==22) {
                    if(dr < deadcone_ph) continue;
                    iso_ph += pfc.pt();
                    /////////// NEUTRAL HADRONS ////////////
                } else if (abs(pfc.pdgId())==130) {
                    if(dr < deadcone_nh) continue;
                    iso_nh += pfc.pt();
                }
            }
            //////////////////  CHARGED from PV  /////////////////////////
        } else if (pfc.fromPV()>1){
            if (abs(pfc.pdgId())==211) {
                if(dr < deadcone_ch) continue;
                iso_ch += pfc.pt();
            }
            //////////////////  CHARGED from PU  /////////////////////////
        } else {
            if (pfc.pt()>ptThresh){
                if(dr < deadcone_pu) continue;
                iso_pu += pfc.pt();
            }
        }
    }
    double iso(0.);
    if (charged_only){
        iso = iso_ch;
    } else {
        iso = iso_ph + iso_nh;
        iso -= rho*EA*(r_iso/0.3)*(r_iso/0.3);
        if (iso>0) iso += iso_ch;
        else iso = iso_ch;
    }
    iso = iso/ptcl->pt();

    return iso;

}


void HccHelper::cleanOverlappingLeptons(std::vector<pat::Muon> &Muons, std::vector<pat::Electron> &Electrons,const reco::Vertex *&vertex) {
  
    using namespace pat;
    using namespace std;
    /********** M U O N  C U T S **********/
    double muEtaCut = 2.4;
    double dxyCut = 0.5;
    double dzCut = 1;
    double tmpDeltR =100;
    double sip3dCut = 4;
    double muPtCut = 5;
    /**************************************/
    // changed above cuts by Ahmad

    for( unsigned int i = 0; i < Muons.size(); i++ ) {
        if( Muons[i].pt() > muPtCut && abs(Muons[i].eta()) < muEtaCut &&
	    passTight_Id(Muons[i], vertex) &&
            //Muons[i].isPFMuon() == 1 &&
            (Muons[i].isGlobalMuon() || (Muons[i].isTrackerMuon() && Muons[i].numberOfMatches(/*reco::Muon::SegmentArbitration*/) > 0 /*numberOfMatchedStations() > 0*/ ) ) &&
            Muons[i].muonBestTrackType() != 2 ) {
            if( abs(getSIP3D(Muons[i])) < sip3dCut ) {	       
                if( fabs(Muons[i].muonBestTrack()->dxy(vertex->position())) < dxyCut ) { //miniAOD                     
                    if( fabs(Muons[i].muonBestTrack()->dz(vertex->position())) < dzCut ) {// miniAOD                        
                        for( unsigned int j = 0; j < Electrons.size(); j++ ) {
                            tmpDeltR = deltaR(Muons[i].eta(),Muons[i].phi(),Electrons[j].eta(),Electrons[j].phi());
                            if( tmpDeltR < 0.05 ) {		
                                Electrons.erase(Electrons.begin()+j);
                            }
                        } 
                    }
                }
            }
        }   
    }    
}

void HccHelper::cleanOverlappingTaus(std::vector<pat::Muon> &Muons, std::vector<pat::Electron> &Electrons, std::vector<pat::Tau> &Taus, double isoCutMu, double isoCutEl, double muRho, double elRho) {
  
    using namespace pat;
    using namespace std;

    double tmpDeltR =999.0;

    for( unsigned int i = 0; i < Muons.size(); i++ ) {
        if (pfIso03(Muons[i],muRho)>isoCutMu) continue;
        for( unsigned int j = 0; j < Taus.size(); j++ ) {
            tmpDeltR = deltaR(Muons[i].eta(),Muons[i].phi(),Taus[j].eta(),Taus[j].phi());
            if( tmpDeltR < 0.05 ) {		
                Taus.erase(Taus.begin()+j);
            }
        }
    }

    for( unsigned int i = 0; i < Electrons.size(); i++ ) {
        if (pfIso03(Electrons[i],elRho)>isoCutEl) continue;
        for( unsigned int j = 0; j < Taus.size(); j++ ) {
            tmpDeltR = deltaR(Electrons[i].eta(),Electrons[i].phi(),Taus[j].eta(),Taus[j].phi());
            if( tmpDeltR < 0.05 ) {		
                Taus.erase(Taus.begin()+j);
            }
        }
    }

}

double HccHelper::getSIP3D(pat::Muon muon) {
    using namespace pat;
    using namespace std;
    
    double ip = fabs(muon.dB(pat::Muon::PV3D));
    double ipError = muon.edB(pat::Muon::PV3D);
    
    double sip = ip/ipError;
    
    return sip;
    
}

double HccHelper::getSIP3D(pat::Electron electron) {
    using namespace pat;
    using namespace std;
    
    double ip = fabs(electron.dB(pat::Electron::PV3D));
    double ipError = electron.edB(pat::Electron::PV3D);
    
    double sip = ip/ipError;
    
    return sip;    
}

bool HccHelper::passTight_BDT_Id(pat::Electron electron, int year) {
    float cutVal=1000;
    float mvaVal=-1;
    float fSCeta = fabs(electron.superCluster()->eta());
    if(year==2018)
    {
        if(electron.pt()<=10){
            if(fSCeta < 0.8) cutVal = 0.9044286167;
            if(fSCeta >= 0.8 && fSCeta < 1.479) cutVal = 0.9094166886;
            if(fSCeta >= 1.479) cutVal = 0.9443653660;
        }
        else {
            if(fSCeta < 0.8) cutVal = 0.1968600840;
            if(fSCeta >= 0.8 && fSCeta < 1.479) cutVal = 0.0759172100;
            if(fSCeta >= 1.479) cutVal = -0.5169136775;
        }
        mvaVal = electron.userFloat("ElectronMVAEstimatorRun2Fall17IsoV1Values");
    }
    if(year==2017)
    {
        if(electron.pt()<=10){
            if(fSCeta < 0.8) cutVal = 0.9128577458;
            if(fSCeta >= 0.8 && fSCeta < 1.479) cutVal = 0.9056792368;
            if(fSCeta >= 1.479) cutVal = 0.9439440575;
        }
        else {
            if(fSCeta < 0.8) cutVal = 0.1559788054;
            if(fSCeta >= 0.8 && fSCeta < 1.479) cutVal = 0.0273863727;
            if(fSCeta >= 1.479) cutVal = -0.5532483665;
        }
        mvaVal = electron.userFloat("ElectronMVAEstimatorRun2Summer17ULIdIsoValues");
    }
    if(year==20165 || year==20160)  //post and pre VFP
    {
        if(electron.pt()<=10){
            if(fSCeta < 0.8) cutVal = 0.9557993256;
            if(fSCeta >= 0.8 && fSCeta < 1.479) cutVal = 0.9475406570;
            if(fSCeta >= 1.479) cutVal = 0.9285158721;
        }
        else {
            if(fSCeta < 0.8) cutVal = 0.3272075608;
            if(fSCeta >= 0.8 && fSCeta < 1.479) cutVal = 0.2468345995;
            if(fSCeta >= 1.479) cutVal = -0.5955762814;
        }
        mvaVal = electron.userFloat("ElectronMVAEstimatorRun2Summer16ULIdIsoValues");
    }
    if( mvaVal > cutVal ) { return true;}
    //if (mvavalue > cutVal ) { return true;}
    return false;
}

bool HccHelper::passTight_Id(pat::Muon muon, const reco::Vertex *&vertex) {
    if (muon.pt()<=200.0) return muon.isPFMuon();
    else {
        return ( (muon.numberOfMatchedStations() > 1 
                  && (muon.muonBestTrack()->ptError()/muon.muonBestTrack()->pt()) < 0.3 
                  && std::abs(muon.muonBestTrack()->dxy(vertex->position())) < 0.2 
                  && std::abs(muon.muonBestTrack()->dz(vertex->position())) < 0.5 
                  && muon.innerTrack()->hitPattern().numberOfValidPixelHits() > 0 
                  && muon.innerTrack()->hitPattern().trackerLayersWithMeasurement() > 5) || muon.isPFMuon() );
    }
}

bool HccHelper::isTrackerHighPt(pat::Muon muon, const reco::Vertex *&vertex){
    return ( muon.numberOfMatchedStations() > 1 
              && (muon.muonBestTrack()->ptError()/muon.muonBestTrack()->pt()) < 0.3 
              && std::abs(muon.muonBestTrack()->dxy(vertex->position())) < 0.2 
              && std::abs(muon.muonBestTrack()->dz(vertex->position())) < 0.5 
              && muon.innerTrack()->hitPattern().numberOfValidPixelHits() > 0 
              && muon.innerTrack()->hitPattern().trackerLayersWithMeasurement() > 5 );
}

bool HccHelper::passTight_Id_SUS(pat::Muon muon, const reco::Vertex *&vertex) {
    if (muon.isPFMuon() != 1) return false;
        if (muon.isMediumMuon() != 1) return false;
    double dxyCut = 0.05;
    double dzCut = 0.1;
    if( fabs(muon.muonBestTrack()->dxy(vertex->position())) >= dxyCut ) return false;
    if( fabs(muon.muonBestTrack()->dz(vertex->position())) >= dzCut ) return false;
    return true;
}

bool HccHelper::passTight_Id_SUS(pat::Electron electron, std::string elecID, const reco::Vertex *&vertex, const reco::BeamSpot BS, std::vector<reco::Conversion>  theConversions, int year) {

    double dxyCut = 0.05;
    double dzCut = 0.1;
    if( fabs(electron.gsfTrack()->dxy(vertex->position())) >= dxyCut ) return false;
    if( fabs(electron.gsfTrack()->dz(vertex->position())) >= dzCut ) return false;

    float cutVal=1000;
    float mvaVal=-1;
    //float fSCeta = fabs(electron.eta());
    float fSCeta = fabs(electron.superCluster()->eta());
    if(year==2018)
    {
        if(electron.pt()<=10){
            if(fSCeta < 0.8) cutVal = 0.9044286167;
            if(fSCeta >= 0.8 && fSCeta < 1.479) cutVal = 0.9094166886;
            if(fSCeta >= 1.479) cutVal = 0.9443653660;
        }
        else {
            if(fSCeta < 0.8) cutVal = 0.1968600840;
            if(fSCeta >= 0.8 && fSCeta < 1.479) cutVal = 0.0759172100;
            if(fSCeta >= 1.479) cutVal = -0.5169136775;
        }
        mvaVal = electron.userFloat("ElectronMVAEstimatorRun2Fall17IsoV1Values");
    }
    if(year==2017)
    {
        if(electron.pt()<=10){
            if(fSCeta < 0.8) cutVal = 0.9128577458;
            if(fSCeta >= 0.8 && fSCeta < 1.479) cutVal = 0.9056792368;
            if(fSCeta >= 1.479) cutVal = 0.9439440575;
        }
        else {
            if(fSCeta < 0.8) cutVal = 0.1559788054;
            if(fSCeta >= 0.8 && fSCeta < 1.479) cutVal = 0.0273863727;
            if(fSCeta >= 1.479) cutVal = -0.5532483665;
        }
        mvaVal = electron.userFloat("ElectronMVAEstimatorRun2Summer17ULIdIsoValues");
    }
    if(year==20165 || year==20160)  //post and pre VFP
    {
        if(electron.pt()<=10){
            if(fSCeta < 0.8) cutVal = 0.9557993256;
            if(fSCeta >= 0.8 && fSCeta < 1.479) cutVal = 0.9475406570;
            if(fSCeta >= 1.479) cutVal = 0.9285158721;
        }
        else {
            if(fSCeta < 0.8) cutVal = 0.3272075608;
            if(fSCeta >= 0.8 && fSCeta < 1.479) cutVal = 0.2468345995;
            if(fSCeta >= 1.479) cutVal = -0.5955762814;
        }
        mvaVal = electron.userFloat("ElectronMVAEstimatorRun2Summer16ULIdIsoValues");
    }

    //if (electron.userFloat("ElectronMVAEstimatorRun2Fall17IsoV1Values") <= cutVal ) return false;
    if( mvaVal <= cutVal ) return false;

    bool vtxFitConversion = ConversionTools::hasMatchedConversion(reco::GsfElectron(electron), theConversions, BS.position());
    if( vtxFitConversion )  return false;

    int missingHitsCuts = 1;
    int misHits = electron.gsfTrack()->hitPattern().numberOfAllHits(reco::HitPattern::MISSING_INNER_HITS);
    if (misHits >= missingHitsCuts) return false;
    
    if (electron.isEB()) {
        if (electron.full5x5_sigmaIetaIeta()>=0.011) return false;
        if (electron.hcalOverEcal()>=0.08) return false;
        if (fabs(electron.deltaEtaSuperClusterTrackAtVtx())>=0.01) return false;
        if (fabs(electron.deltaPhiSuperClusterTrackAtVtx())>=0.04) return false;
        if (fabs(1.0/electron.correctedEcalEnergy() - electron.eSuperClusterOverP()/electron.correctedEcalEnergy())>=0.01) return false;
    }
    if (electron.isEE()) {
        if (electron.full5x5_sigmaIetaIeta()>=0.031) return false;
        if (electron.hcalOverEcal()>=0.08) return false;
        if (fabs(electron.deltaEtaSuperClusterTrackAtVtx())>=0.01) return false;
        if (fabs(electron.deltaPhiSuperClusterTrackAtVtx())>=0.08) return false;
        if (fabs(1.0/electron.correctedEcalEnergy() - electron.eSuperClusterOverP()/electron.correctedEcalEnergy())>=0.01) return false;
    }

    return true;
}

double HccHelper::ptRatio(pat::Electron electron, edm::Handle<edm::View<pat::Jet> > jets, bool isMC) {

    double ptratio = 9999.0;
    double mindR=9999.0;
    
    for(unsigned int j = 0; j < jets->size(); ++j) {        
        const pat::Jet & patjet = jets->at(j);
        
        TLorentzVector jet_lepawareJEC(patjet.correctedP4(0).px(),patjet.correctedP4(0).py(),patjet.correctedP4(0).pz(),patjet.correctedP4(0).energy());
        TLorentzVector lep(electron.px(),electron.py(),electron.pz(),electron.energy());
        double corr_L1 = patjet.jecFactor("L1FastJet")/patjet.jecFactor("Uncorrected");
        double corr_L2L3 = patjet.jecFactor("L3Absolute")/patjet.jecFactor("Uncorrected");
        if (!isMC) corr_L2L3=patjet.jecFactor("L2L3Residual")/patjet.jecFactor("Uncorrected");
        jet_lepawareJEC *= corr_L1;
        jet_lepawareJEC -= lep;
        jet_lepawareJEC *= corr_L2L3/corr_L1;
        jet_lepawareJEC += lep;

        double tmpdR = deltaR(electron.eta(),electron.phi(),jet_lepawareJEC.Eta(),jet_lepawareJEC.Phi());        
        if (tmpdR<mindR && tmpdR<0.4) {
            mindR = tmpdR;

            ptratio = electron.pt()/jet_lepawareJEC.Pt();
        }        
    }    
    return ptratio;
}

double HccHelper::ptRatio(pat::Muon muon, edm::Handle<edm::View<pat::Jet> > jets,bool isMC) {

    double ptratio = 9999.0;
    double mindR=9999.0;
    
    for(unsigned int j = 0; j < jets->size(); ++j) {        
        const pat::Jet & patjet = jets->at(j);

        TLorentzVector jet_lepawareJEC(patjet.correctedP4(0).px(),patjet.correctedP4(0).py(),patjet.correctedP4(0).pz(),patjet.correctedP4(0).energy());
        TLorentzVector lep(muon.px(),muon.py(),muon.pz(),muon.energy());
        double corr_L1 = patjet.jecFactor("L1FastJet")/patjet.jecFactor("Uncorrected");
        double corr_L2L3 = patjet.jecFactor("L3Absolute")/patjet.jecFactor("Uncorrected");
        if (!isMC)corr_L2L3=patjet.jecFactor("L2L3Residual")/patjet.jecFactor("Uncorrected");
        jet_lepawareJEC *= corr_L1;
        jet_lepawareJEC -= lep;
        jet_lepawareJEC *= corr_L2L3/corr_L1;
        jet_lepawareJEC += lep;

        double tmpdR = deltaR(muon.eta(),muon.phi(),jet_lepawareJEC.Eta(),jet_lepawareJEC.Phi());
        if (tmpdR<mindR && tmpdR<0.4) {
            mindR = tmpdR;
            ptratio = muon.pt()/jet_lepawareJEC.Pt();
        }
    }    
    return ptratio;
}

double HccHelper::ptRel(pat::Electron electron, edm::Handle<edm::View<pat::Jet> > jets,bool isMC) {

    double ptrel = 9999.0;
    double mindR=9999.0;
    
    for(unsigned int j = 0; j < jets->size(); ++j) {        
        const pat::Jet & patjet = jets->at(j);

        TLorentzVector jet_lepawareJEC(patjet.correctedP4(0).px(),patjet.correctedP4(0).py(),patjet.correctedP4(0).pz(),patjet.correctedP4(0).energy());
        TLorentzVector lep(electron.px(),electron.py(),electron.pz(),electron.energy());
        double corr_L1 = patjet.jecFactor("L1FastJet")/patjet.jecFactor("Uncorrected");
        double corr_L2L3 = patjet.jecFactor("L3Absolute")/patjet.jecFactor("Uncorrected");
        if (!isMC) corr_L2L3=patjet.jecFactor("L2L3Residual")/patjet.jecFactor("Uncorrected");
        jet_lepawareJEC *= corr_L1;
        jet_lepawareJEC -= lep;
        jet_lepawareJEC *= corr_L2L3/corr_L1;
        jet_lepawareJEC += lep;

        double tmpdR = deltaR(electron.eta(),electron.phi(),jet_lepawareJEC.Eta(),jet_lepawareJEC.Phi());
        if (tmpdR<mindR && tmpdR<0.4) {
            mindR = tmpdR;
            TVector3 pl(electron.px(),electron.py(),electron.pz());
            TLorentzVector p4jminusl;
            p4jminusl = lep-jet_lepawareJEC;
            TVector3 pjminusl(p4jminusl.Px(),p4jminusl.Py(),p4jminusl.Pz());
            double sin_alpha = (pl.Cross(pjminusl)).Mag()/pl.Mag()/pjminusl.Mag();
            ptrel = pl.Mag()*sin_alpha;     
        }        
    }    
    return ptrel;
}

double HccHelper::ptRel(pat::Muon muon, edm::Handle<edm::View<pat::Jet> > jets,bool isMC) {

    double ptrel = 9999.0;
    double mindR=9999.0;

    for(unsigned int j = 0; j < jets->size(); ++j) {
        const pat::Jet & patjet = jets->at(j);

        TLorentzVector jet_lepawareJEC(patjet.correctedP4(0).px(),patjet.correctedP4(0).py(),patjet.correctedP4(0).pz(),patjet.correctedP4(0).energy());
        TLorentzVector lep(muon.px(),muon.py(),muon.pz(),muon.energy());
        double corr_L1 = patjet.jecFactor("L1FastJet")/patjet.jecFactor("Uncorrected");
        double corr_L2L3 = patjet.jecFactor("L3Absolute")/patjet.jecFactor("Uncorrected");
        if (!isMC) corr_L2L3=patjet.jecFactor("L2L3Residual")/patjet.jecFactor("Uncorrected");
        jet_lepawareJEC *= corr_L1;
        jet_lepawareJEC -= lep;
        jet_lepawareJEC *= corr_L2L3/corr_L1;
        jet_lepawareJEC += lep;

        double tmpdR = deltaR(muon.eta(),muon.phi(),jet_lepawareJEC.Eta(),jet_lepawareJEC.Phi());
        if (tmpdR<mindR && tmpdR<0.4) {
            mindR = tmpdR;
            TVector3 pl(muon.px(),muon.py(),muon.pz());
            TLorentzVector p4jminusl;
            p4jminusl = lep-jet_lepawareJEC;
            TVector3 pjminusl(p4jminusl.Px(),p4jminusl.Py(),p4jminusl.Pz());
            double sin_alpha = (pl.Cross(pjminusl)).Mag()/pl.Mag()/pjminusl.Mag();
            ptrel = pl.Mag()*sin_alpha;
        }
    }

    return ptrel;
}

double HccHelper::pfIso(pat::Muon muon, double Rho) {
    double PUCorr = 0.5*muon.puChargedHadronIso();
    double iso = (muon.chargedHadronIso()+std::max(muon.photonIso()+muon.neutralHadronIso()-PUCorr,0.0))/muon.pt();
    return iso;
}

double HccHelper::pfIso03(pat::Muon muon, double Rho) {
    double PUCorr = 0.5*muon.pfIsolationR03().sumPUPt;
    double isoCH = muon.pfIsolationR03().sumChargedHadronPt;
    double isoNH = muon.pfIsolationR03().sumNeutralHadronEt;
    double isoPhot = muon.pfIsolationR03().sumPhotonEt;
    double iso = (isoCH+std::max(isoPhot+isoNH-PUCorr,0.0))/muon.pt();    
    return iso;
}


double HccHelper::pfIso(pat::Electron elec, double Rho) {
    double PUCorr = Rho*ElecEffArea(elEAtype,elec.eta(),elEAtarget);
    double iso = (elec.chargedHadronIso()+std::max(elec.photonIso()+elec.neutralHadronIso()-PUCorr,0.0))/elec.pt();
    return iso;
}

double HccHelper::pfIso03(pat::Electron elec, double Rho) {
    double PUCorr = Rho*ElecEffArea(kEGammaNeutralHadIso03,elec.superCluster()->eta(),elEAtarget);
    double isoCH = elec.pfIsolationVariables().sumChargedHadronPt;
    double isoNH = elec.pfIsolationVariables().sumNeutralHadronEt;
    double isoPhot = elec.pfIsolationVariables().sumPhotonEt;
    double iso = (isoCH+std::max(isoPhot+isoNH-PUCorr,0.0))/elec.pt();    
    return iso;
}

double HccHelper::getPUIso(pat::Muon muon, double Rho) {
    double puiso = 0.5*muon.puChargedHadronIso();
    if (Rho<0.0) puiso = 0.;
    return puiso;
}

double HccHelper::getPUIso03(pat::Muon muon, double Rho) {
    double puiso = 0.5*muon.pfIsolationR03().sumPUPt;
    if (Rho<0.0) puiso = 0.;
    return puiso;
}

double HccHelper::getPUIso(pat::Electron elec, double Rho) {
    double puiso = Rho*ElecEffArea(elEAtype,elec.eta(),elEAtarget); 
    return puiso;
}

double HccHelper::getPUIso03(pat::Electron elec, double Rho) {
    double puiso = Rho*ElecEffArea(kEGammaNeutralHadIso03,elec.superCluster()->eta(),elEAtarget); 
    return puiso;
}

double HccHelper::MuonEffArea(MuonEffectiveAreaType type, double SCEta, MuonEffectiveAreaTarget EffectiveAreaTarget) {

    double EffectiveArea = 0;
    
    if (EffectiveAreaTarget == kMuNoCorr) {
        return 0.0;
    }
    
    //2012 Data Effective Areas
    else if (EffectiveAreaTarget == kMuEAData2012) {
        if (type == kMuGammaIso04){
            if (fabs(SCEta) >= 0.0 && fabs(SCEta) < 1.0 )   EffectiveArea = 0.50419;
            if (fabs(SCEta) >= 1.0 && fabs(SCEta) < 1.479 ) EffectiveArea = 0.30582;
            if (fabs(SCEta) >= 1.479 && fabs(SCEta) < 2.0 ) EffectiveArea = 0.19765;
            if (fabs(SCEta) >= 2.0 && fabs(SCEta) < 2.2 )   EffectiveArea = 0.28723;
            if (fabs(SCEta) >= 2.2 && fabs(SCEta) < 2.3 )   EffectiveArea = 0.52529;
            if (fabs(SCEta) >= 2.3 )                        EffectiveArea = 0.48818;
        }
        if (type == kMuNeutralHadronIso04){
            if (fabs(SCEta) >= 0.0 && fabs(SCEta) < 1.0 )   EffectiveArea = 0.16580;
            if (fabs(SCEta) >= 1.0 && fabs(SCEta) < 1.479 ) EffectiveArea = 0.25904;
            if (fabs(SCEta) >= 1.479 && fabs(SCEta) < 2.0 ) EffectiveArea = 0.24695;
            if (fabs(SCEta) >= 2.0 && fabs(SCEta) < 2.2 )   EffectiveArea = 0.22021;
            if (fabs(SCEta) >= 2.2 && fabs(SCEta) < 2.3 )   EffectiveArea = 0.34045;
            if (fabs(SCEta) >= 2.3 )                        EffectiveArea = 0.21592;
        }
        if (type == kMuGammaAndNeutralHadronIso04){
            if (fabs(SCEta) >= 0.0 && fabs(SCEta) < 1.0 )   EffectiveArea = 0.674;
            if (fabs(SCEta) >= 1.0 && fabs(SCEta) < 1.479 ) EffectiveArea = 0.565;
            if (fabs(SCEta) >= 1.479 && fabs(SCEta) < 2.0 ) EffectiveArea = 0.442;
            if (fabs(SCEta) >= 2.0 && fabs(SCEta) < 2.2 )   EffectiveArea = 0.515;
            if (fabs(SCEta) >= 2.2 && fabs(SCEta) < 2.3 )   EffectiveArea = 0.821;
            if (fabs(SCEta) >= 2.3 )                        EffectiveArea = 0.660;
        }
        if (type == kMuGammaAndNeutralHadronIso03){
            if (fabs(SCEta) >= 0.0 && fabs(SCEta) < 1.0 )   EffectiveArea = 0.382;
            if (fabs(SCEta) >= 1.0 && fabs(SCEta) < 1.479 ) EffectiveArea = 0.317;
            if (fabs(SCEta) >= 1.479 && fabs(SCEta) < 2.0 ) EffectiveArea = 0.242;
            if (fabs(SCEta) >= 2.0 && fabs(SCEta) < 2.2 )   EffectiveArea = 0.326;
            if (fabs(SCEta) >= 2.2 && fabs(SCEta) < 2.3 )   EffectiveArea = 0.462;
            if (fabs(SCEta) >= 2.3 )                        EffectiveArea = 0.372;
        }
        if (type == kMuGammaAndNeutralHadronIso04Tight){
            if (fabs(SCEta) >= 0.0 && fabs(SCEta) < 1.0 )   EffectiveArea = 0.340;
            if (fabs(SCEta) >= 1.0 && fabs(SCEta) < 1.479 ) EffectiveArea = 0.310;
            if (fabs(SCEta) >= 1.479 && fabs(SCEta) < 2.0 ) EffectiveArea = 0.315;
            if (fabs(SCEta) >= 2.0 && fabs(SCEta) < 2.2 )   EffectiveArea = 0.415;
            if (fabs(SCEta) >= 2.2 && fabs(SCEta) < 2.3 )   EffectiveArea = 0.658;
            if (fabs(SCEta) >= 2.3 )                        EffectiveArea = 0.405;
        }
        if (type == kMuGammaAndNeutralHadronIso03Tight){
            if (fabs(SCEta) >= 0.0 && fabs(SCEta) < 1.0 )   EffectiveArea = 0.207;
            if (fabs(SCEta) >= 1.0 && fabs(SCEta) < 1.479 ) EffectiveArea = 0.183;
            if (fabs(SCEta) >= 1.479 && fabs(SCEta) < 2.0 ) EffectiveArea = 0.177;
            if (fabs(SCEta) >= 2.0 && fabs(SCEta) < 2.2 )   EffectiveArea = 0.271;
            if (fabs(SCEta) >= 2.2 && fabs(SCEta) < 2.3 )   EffectiveArea = 0.348;
            if (fabs(SCEta) >= 2.3 )                        EffectiveArea = 0.246;
        }
    }
    //2011 Data Effective Areas
    else if (EffectiveAreaTarget == kMuEAData2011) {
        
        if (type == kMuGammaIsoDR0p0To0p1) {
            if (fabs(SCEta) >= 0.0 && fabs(SCEta) < 1.0 ) EffectiveArea = 0.004;
            if (fabs(SCEta) >= 1.0 && fabs(SCEta) < 1.479 ) EffectiveArea = 0.002;
            if (fabs(SCEta) >= 1.479 && fabs(SCEta) < 2.0 ) EffectiveArea = 0.002;
            if (fabs(SCEta) >= 2.0 && fabs(SCEta) < 2.2 ) EffectiveArea = 0.000;
            if (fabs(SCEta) >= 2.2 && fabs(SCEta) < 2.3 ) EffectiveArea = 0.000;
            if (fabs(SCEta) >= 2.3 ) EffectiveArea = 0.005;
        }
        if (type == kMuGammaIsoDR0p1To0p2) {
            if (fabs(SCEta) >= 0.0 && fabs(SCEta) < 1.0 ) EffectiveArea = 0.011;
            if (fabs(SCEta) >= 1.0 && fabs(SCEta) < 1.479 ) EffectiveArea = 0.008;
            if (fabs(SCEta) >= 1.479 && fabs(SCEta) < 2.0 ) EffectiveArea = 0.005;
            if (fabs(SCEta) >= 2.0 && fabs(SCEta) < 2.2 ) EffectiveArea = 0.008;
            if (fabs(SCEta) >= 2.2 && fabs(SCEta) < 2.3 ) EffectiveArea = 0.008;
            if (fabs(SCEta) >= 2.3 ) EffectiveArea = 0.011;
        }
        if (type == kMuGammaIsoDR0p2To0p3) {
            if (fabs(SCEta) >= 0.0 && fabs(SCEta) < 1.0 ) EffectiveArea = 0.023;
            if (fabs(SCEta) >= 1.0 && fabs(SCEta) < 1.479 ) EffectiveArea = 0.016;
            if (fabs(SCEta) >= 1.479 && fabs(SCEta) < 2.0 ) EffectiveArea = 0.010;
            if (fabs(SCEta) >= 2.0 && fabs(SCEta) < 2.2 ) EffectiveArea = 0.014;
            if (fabs(SCEta) >= 2.2 && fabs(SCEta) < 2.3 ) EffectiveArea = 0.017;
            if (fabs(SCEta) >= 2.3  ) EffectiveArea = 0.021;
        }
        if (type == kMuGammaIsoDR0p3To0p4) {
            if (fabs(SCEta) >= 0.0 && fabs(SCEta) < 1.0 ) EffectiveArea = 0.036;
            if (fabs(SCEta) >= 1.0 && fabs(SCEta) < 1.479 ) EffectiveArea = 0.026;
            if (fabs(SCEta) >= 1.479 && fabs(SCEta) < 2.0 ) EffectiveArea = 0.017;
            if (fabs(SCEta) >= 2.0 && fabs(SCEta) < 2.2 ) EffectiveArea = 0.023;
            if (fabs(SCEta) >= 2.2 && fabs(SCEta) < 2.3 ) EffectiveArea = 0.028;
            if (fabs(SCEta) >= 2.3  ) EffectiveArea = 0.032;
        }
        if (type == kMuGammaIsoDR0p4To0p5) {
            if (fabs(SCEta) >= 0.0 && fabs(SCEta) < 1.0 ) EffectiveArea = 0.051;
            if (fabs(SCEta) >= 1.0 && fabs(SCEta) < 1.479 ) EffectiveArea = 0.037;
            if (fabs(SCEta) >= 1.479 && fabs(SCEta) < 2.0 ) EffectiveArea = 0.028;
            if (fabs(SCEta) >= 2.0 && fabs(SCEta) < 2.2 ) EffectiveArea = 0.033;
            if (fabs(SCEta) >= 2.2 && fabs(SCEta) < 2.3 ) EffectiveArea = 0.042;
            if (fabs(SCEta) >= 2.3  ) EffectiveArea = 0.052;
        }
        if (type == kMuNeutralHadronIsoDR0p0To0p1) {
            if (fabs(SCEta) >= 0.0 && fabs(SCEta) < 1.0 ) EffectiveArea = 0.002;
            if (fabs(SCEta) >= 1.0 && fabs(SCEta) < 1.479 ) EffectiveArea = 0.001;
            if (fabs(SCEta) >= 1.479 && fabs(SCEta) < 2.0 ) EffectiveArea = 0.001;
            if (fabs(SCEta) >= 2.0 && fabs(SCEta) < 2.2 ) EffectiveArea = 0.001;
            if (fabs(SCEta) >= 2.2 && fabs(SCEta) < 2.3 ) EffectiveArea = 0.005;
            if (fabs(SCEta) >= 2.3  ) EffectiveArea = 0.007;
        }
        if (type == kMuNeutralHadronIsoDR0p1To0p2) {
            if (fabs(SCEta) >= 0.0 && fabs(SCEta) < 1.0 ) EffectiveArea = 0.005;
            if (fabs(SCEta) >= 1.0 && fabs(SCEta) < 1.479 ) EffectiveArea = 0.008;
            if (fabs(SCEta) >= 1.479 && fabs(SCEta) < 2.0 ) EffectiveArea = 0.009;
            if (fabs(SCEta) >= 2.0 && fabs(SCEta) < 2.2 ) EffectiveArea = 0.009;
            if (fabs(SCEta) >= 2.2 && fabs(SCEta) < 2.3 ) EffectiveArea = 0.010;
            if (fabs(SCEta) >= 2.3  ) EffectiveArea = 0.014;
        }
        if (type == kMuNeutralHadronIsoDR0p2To0p3) {
            if (fabs(SCEta) >= 0.0 && fabs(SCEta) < 1.0 ) EffectiveArea = 0.010;
            if (fabs(SCEta) >= 1.0 && fabs(SCEta) < 1.479 ) EffectiveArea = 0.015;
            if (fabs(SCEta) >= 1.479 && fabs(SCEta) < 2.0 ) EffectiveArea = 0.017;
            if (fabs(SCEta) >= 2.0 && fabs(SCEta) < 2.2 ) EffectiveArea = 0.017;
            if (fabs(SCEta) >= 2.2 && fabs(SCEta) < 2.3 ) EffectiveArea = 0.019;
            if (fabs(SCEta) >= 2.3  ) EffectiveArea = 0.024;
        }
        if (type == kMuNeutralHadronIsoDR0p3To0p4) {
            if (fabs(SCEta) >= 0.0 && fabs(SCEta) < 1.0 ) EffectiveArea = 0.015;
            if (fabs(SCEta) >= 1.0 && fabs(SCEta) < 1.479 ) EffectiveArea = 0.021;
            if (fabs(SCEta) >= 1.479 && fabs(SCEta) < 2.0 ) EffectiveArea = 0.024;
            if (fabs(SCEta) >= 2.0 && fabs(SCEta) < 2.2 ) EffectiveArea = 0.032;
            if (fabs(SCEta) >= 2.2 && fabs(SCEta) < 2.3 ) EffectiveArea = 0.038;
            if (fabs(SCEta) >= 2.3  ) EffectiveArea = 0.038;
        }
        if (type == kMuNeutralHadronIsoDR0p4To0p5) {
            if (fabs(SCEta) >= 0.0 && fabs(SCEta) < 1.0 ) EffectiveArea = 0.020;
            if (fabs(SCEta) >= 1.0 && fabs(SCEta) < 1.479 ) EffectiveArea = 0.026;
            if (fabs(SCEta) >= 1.479 && fabs(SCEta) < 2.0 ) EffectiveArea = 0.033;
            if (fabs(SCEta) >= 2.0 && fabs(SCEta) < 2.2 ) EffectiveArea = 0.045;
            if (fabs(SCEta) >= 2.2 && fabs(SCEta) < 2.3 ) EffectiveArea = 0.051;
            if (fabs(SCEta) >= 2.3  ) EffectiveArea = 0.114;
        }
        /// BEGIN FROM SLIDE 11 OF  https://indico.cern.ch/getFile.py/access?contribId=1&resId=0&materialId=slides&confId=188494
        /// NOTE: to be used with the rho from ALL pf candidates within |eta|<2.5
        if (type == kMuGammaIso03){
            if (fabs(SCEta) >= 0.0 && fabs(SCEta) < 1.0 ) EffectiveArea = 0.049;
            if (fabs(SCEta) >= 1.0 && fabs(SCEta) < 1.5 ) EffectiveArea = 0.030;
            if (fabs(SCEta) >= 1.5 && fabs(SCEta) < 2.0 ) EffectiveArea = 0.022;
            if (fabs(SCEta) >= 2.0 && fabs(SCEta) < 2.2 ) EffectiveArea = 0.034;
            if (fabs(SCEta) >= 2.2 && fabs(SCEta) < 2.3 ) EffectiveArea = 0.041;
            if (fabs(SCEta) >= 2.3 )                      EffectiveArea = 0.048;
        }
        if (type == kMuGammaIso04){
            if (fabs(SCEta) >= 0.0 && fabs(SCEta) < 1.0 ) EffectiveArea = 0.085;
            if (fabs(SCEta) >= 1.0 && fabs(SCEta) < 1.5 ) EffectiveArea = 0.052;
            if (fabs(SCEta) >= 1.5 && fabs(SCEta) < 2.0 ) EffectiveArea = 0.038;
            if (fabs(SCEta) >= 2.0 && fabs(SCEta) < 2.2 ) EffectiveArea = 0.055;
            if (fabs(SCEta) >= 2.2 && fabs(SCEta) < 2.3 ) EffectiveArea = 0.070;
            if (fabs(SCEta) >= 2.3 )                      EffectiveArea = 0.081;
        }
        if (type == kMuNeutralHadronIso03){
            if (fabs(SCEta) >= 0.0 && fabs(SCEta) < 1.0 ) EffectiveArea = 0.027;
            if (fabs(SCEta) >= 1.0 && fabs(SCEta) < 1.5 ) EffectiveArea = 0.039;
            if (fabs(SCEta) >= 1.5 && fabs(SCEta) < 2.0 ) EffectiveArea = 0.044;
            if (fabs(SCEta) >= 2.0 && fabs(SCEta) < 2.2 ) EffectiveArea = 0.047;
            if (fabs(SCEta) >= 2.2 && fabs(SCEta) < 2.3 ) EffectiveArea = 0.055;
            if (fabs(SCEta) >= 2.3 )                      EffectiveArea = 0.065;
        }
        if (type == kMuNeutralHadronIso04){
            if (fabs(SCEta) >= 0.0 && fabs(SCEta) < 1.0 ) EffectiveArea = 0.046;
            if (fabs(SCEta) >= 1.0 && fabs(SCEta) < 1.5 ) EffectiveArea = 0.067;
            if (fabs(SCEta) >= 1.5 && fabs(SCEta) < 2.0 ) EffectiveArea = 0.074;
            if (fabs(SCEta) >= 2.0 && fabs(SCEta) < 2.2 ) EffectiveArea = 0.083;
            if (fabs(SCEta) >= 2.2 && fabs(SCEta) < 2.3 ) EffectiveArea = 0.095;
            if (fabs(SCEta) >= 2.3 )                      EffectiveArea = 0.105;
        }
        if (type == kMuGammaAndNeutralHadronIso03){
            if (fabs(SCEta) >= 0.0 && fabs(SCEta) < 1.0 ) EffectiveArea = 0.076;
            if (fabs(SCEta) >= 1.0 && fabs(SCEta) < 1.5 ) EffectiveArea = 0.070;
            if (fabs(SCEta) >= 1.5 && fabs(SCEta) < 2.0 ) EffectiveArea = 0.067;
            if (fabs(SCEta) >= 2.0 && fabs(SCEta) < 2.2 ) EffectiveArea = 0.082;
            if (fabs(SCEta) >= 2.2 && fabs(SCEta) < 2.3 ) EffectiveArea = 0.097;
            if (fabs(SCEta) >= 2.3 )                      EffectiveArea = 0.115;
        }
        if (type == kMuGammaAndNeutralHadronIso04){
            if (fabs(SCEta) >= 0.0 && fabs(SCEta) < 1.0 ) EffectiveArea = 0.132;
            if (fabs(SCEta) >= 1.0 && fabs(SCEta) < 1.5 ) EffectiveArea = 0.120;
            if (fabs(SCEta) >= 1.5 && fabs(SCEta) < 2.0 ) EffectiveArea = 0.114;
            if (fabs(SCEta) >= 2.0 && fabs(SCEta) < 2.2 ) EffectiveArea = 0.139;
            if (fabs(SCEta) >= 2.2 && fabs(SCEta) < 2.3 ) EffectiveArea = 0.168;
            if (fabs(SCEta) >= 2.3 )                      EffectiveArea = 0.189;
        }
        if (type == kMuGammaIso05){
            if (fabs(SCEta) >= 0.0 && fabs(SCEta) < 1.0 ) EffectiveArea = 0.05317;
            if (fabs(SCEta) >= 1.0 && fabs(SCEta) < 1.479 ) EffectiveArea = 0.03502;
            if (fabs(SCEta) >= 1.479 && fabs(SCEta) < 2.0 ) EffectiveArea = 0.03689;
            if (fabs(SCEta) >= 2.0 && fabs(SCEta) < 2.2 ) EffectiveArea = 0.05221;
            if (fabs(SCEta) >= 2.2 && fabs(SCEta) < 2.3 ) EffectiveArea = 0.06668;
            if (fabs(SCEta) >= 2.3  ) EffectiveArea = 0.0744;
        }
        if (type == kMuNeutralIso05) {
            if (fabs(SCEta) >= 0.0 && fabs(SCEta) < 1.0 ) EffectiveArea = 0.06408;
            if (fabs(SCEta) >= 1.0 && fabs(SCEta) < 1.479 ) EffectiveArea = 0.07557;
            if (fabs(SCEta) >= 1.479 && fabs(SCEta) < 2.0 ) EffectiveArea = 0.08864;
            if (fabs(SCEta) >= 2.0 && fabs(SCEta) < 2.2 ) EffectiveArea = 0.11492;
            if (fabs(SCEta) >= 2.2 && fabs(SCEta) < 2.3 ) EffectiveArea = 0.13784;
            if (fabs(SCEta) >= 2.3  ) EffectiveArea = 0.18745;
        }
    }
    
    //Summer11 MC Effective Areas
    else if (EffectiveAreaTarget == kMuEASummer11MC) {
        if (type == kMuGammaIsoDR0p0To0p1) {
            if (fabs(SCEta) >= 0.0 && fabs(SCEta) < 1.0 ) EffectiveArea = 0.000;
            if (fabs(SCEta) >= 1.0 && fabs(SCEta) < 1.479 ) EffectiveArea = 0.000;
            if (fabs(SCEta) >= 1.479 && fabs(SCEta) < 2.0 ) EffectiveArea = 0.000;
            if (fabs(SCEta) >= 2.0 && fabs(SCEta) < 2.2 ) EffectiveArea = 0.000;
            if (fabs(SCEta) >= 2.2 && fabs(SCEta) < 2.3 ) EffectiveArea = 0.000;
            if (fabs(SCEta) >= 2.3  ) EffectiveArea = 0.006;
        }
        if (type == kMuGammaIsoDR0p1To0p2) {
            if (fabs(SCEta) >= 0.0 && fabs(SCEta) < 1.0 ) EffectiveArea = 0.012;
            if (fabs(SCEta) >= 1.0 && fabs(SCEta) < 1.479 ) EffectiveArea = 0.007;
            if (fabs(SCEta) >= 1.479 && fabs(SCEta) < 2.0 ) EffectiveArea = 0.006;
            if (fabs(SCEta) >= 2.0 && fabs(SCEta) < 2.2 ) EffectiveArea = 0.008;
            if (fabs(SCEta) >= 2.2 && fabs(SCEta) < 2.3 ) EffectiveArea = 0.019;
            if (fabs(SCEta) >= 2.3  ) EffectiveArea = 0.015;
        }
        if (type == kMuGammaIsoDR0p2To0p3) {
            if (fabs(SCEta) >= 0.0 && fabs(SCEta) < 1.0 ) EffectiveArea = 0.023;
            if (fabs(SCEta) >= 1.0 && fabs(SCEta) < 1.479 ) EffectiveArea = 0.018;
            if (fabs(SCEta) >= 1.479 && fabs(SCEta) < 2.0 ) EffectiveArea = 0.013;
            if (fabs(SCEta) >= 2.0 && fabs(SCEta) < 2.2 ) EffectiveArea = 0.016;
            if (fabs(SCEta) >= 2.2 && fabs(SCEta) < 2.3 ) EffectiveArea = 0.024;
            if (fabs(SCEta) >= 2.3  ) EffectiveArea = 0.036;
        }
        if (type == kMuGammaIsoDR0p3To0p4) {
            if (fabs(SCEta) >= 0.0 && fabs(SCEta) < 1.0 ) EffectiveArea = 0.038;
            if (fabs(SCEta) >= 1.0 && fabs(SCEta) < 1.479 ) EffectiveArea = 0.027;
            if (fabs(SCEta) >= 1.479 && fabs(SCEta) < 2.0 ) EffectiveArea = 0.019;
            if (fabs(SCEta) >= 2.0 && fabs(SCEta) < 2.2 ) EffectiveArea = 0.033;
            if (fabs(SCEta) >= 2.2 && fabs(SCEta) < 2.3 ) EffectiveArea = 0.041;
            if (fabs(SCEta) >= 2.3  ) EffectiveArea = 0.062;
        }
        if (type == kMuGammaIsoDR0p4To0p5) {
            if (fabs(SCEta) >= 0.0 && fabs(SCEta) < 1.0 ) EffectiveArea = 0.055;
            if (fabs(SCEta) >= 1.0 && fabs(SCEta) < 1.479 ) EffectiveArea = 0.038;
            if (fabs(SCEta) >= 1.479 && fabs(SCEta) < 2.0 ) EffectiveArea = 0.032;
            if (fabs(SCEta) >= 2.0 && fabs(SCEta) < 2.2 ) EffectiveArea = 0.052;
            if (fabs(SCEta) >= 2.2 && fabs(SCEta) < 2.3 ) EffectiveArea = 0.066;
            if (fabs(SCEta) >= 2.3  ) EffectiveArea = 0.093;
        }
        if (type == kMuNeutralHadronIsoDR0p0To0p1) {
            if (fabs(SCEta) >= 0.0 && fabs(SCEta) < 1.0 ) EffectiveArea = 0.002;
            if (fabs(SCEta) >= 1.0 && fabs(SCEta) < 1.479 ) EffectiveArea = 0.005;
            if (fabs(SCEta) >= 1.479 && fabs(SCEta) < 2.0 ) EffectiveArea = 0.000;
            if (fabs(SCEta) >= 2.0 && fabs(SCEta) < 2.2 ) EffectiveArea = 0.000;
            if (fabs(SCEta) >= 2.2 && fabs(SCEta) < 2.3 ) EffectiveArea = 0.000;
            if (fabs(SCEta) >= 2.3  ) EffectiveArea = 0.003;
        }
        if (type == kMuNeutralHadronIsoDR0p1To0p2) {
            if (fabs(SCEta) >= 0.0 && fabs(SCEta) < 1.0 ) EffectiveArea = 0.005;
            if (fabs(SCEta) >= 1.0 && fabs(SCEta) < 1.479 ) EffectiveArea = 0.006;
            if (fabs(SCEta) >= 1.479 && fabs(SCEta) < 2.0 ) EffectiveArea = 0.009;
            if (fabs(SCEta) >= 2.0 && fabs(SCEta) < 2.2 ) EffectiveArea = 0.008;
            if (fabs(SCEta) >= 2.2 && fabs(SCEta) < 2.3 ) EffectiveArea = 0.009;
            if (fabs(SCEta) >= 2.3  ) EffectiveArea = 0.013;
        }
        if (type == kMuNeutralHadronIsoDR0p2To0p3) {
            if (fabs(SCEta) >= 0.0 && fabs(SCEta) < 1.0 ) EffectiveArea = 0.009;
            if (fabs(SCEta) >= 1.0 && fabs(SCEta) < 1.479 ) EffectiveArea = 0.013;
            if (fabs(SCEta) >= 1.479 && fabs(SCEta) < 2.0 ) EffectiveArea = 0.015;
            if (fabs(SCEta) >= 2.0 && fabs(SCEta) < 2.2 ) EffectiveArea = 0.016;
            if (fabs(SCEta) >= 2.2 && fabs(SCEta) < 2.3 ) EffectiveArea = 0.020;
            if (fabs(SCEta) >= 2.3  ) EffectiveArea = 0.024;
        }
        if (type == kMuNeutralHadronIsoDR0p3To0p4) {
            if (fabs(SCEta) >= 0.0 && fabs(SCEta) < 1.0 ) EffectiveArea = 0.012;
            if (fabs(SCEta) >= 1.0 && fabs(SCEta) < 1.479 ) EffectiveArea = 0.019;
            if (fabs(SCEta) >= 1.479 && fabs(SCEta) < 2.0 ) EffectiveArea = 0.021;
            if (fabs(SCEta) >= 2.0 && fabs(SCEta) < 2.2 ) EffectiveArea = 0.025;
            if (fabs(SCEta) >= 2.2 && fabs(SCEta) < 2.3 ) EffectiveArea = 0.030;
            if (fabs(SCEta) >= 2.3  ) EffectiveArea = 0.044;
        }
        if (type == kMuNeutralHadronIsoDR0p4To0p5) {
            if (fabs(SCEta) >= 0.0 && fabs(SCEta) < 1.0 ) EffectiveArea = 0.016;
            if (fabs(SCEta) >= 1.0 && fabs(SCEta) < 1.479 ) EffectiveArea = 0.026;
            if (fabs(SCEta) >= 1.479 && fabs(SCEta) < 2.0 ) EffectiveArea = 0.030;
            if (fabs(SCEta) >= 2.0 && fabs(SCEta) < 2.2 ) EffectiveArea = 0.038;
            if (fabs(SCEta) >= 2.2 && fabs(SCEta) < 2.3 ) EffectiveArea = 0.048;
            if (fabs(SCEta) >= 2.3  ) EffectiveArea = 0.118;
        }
    } 
    //Fall11 MC Effective Areas
    else if (EffectiveAreaTarget == kMuEAFall11MC) {
        if (type == kMuGammaIsoDR0p0To0p1) {
            if (fabs(SCEta) >= 0.0 && fabs(SCEta) < 1.0 ) EffectiveArea = 0.004;
            if (fabs(SCEta) >= 1.0 && fabs(SCEta) < 1.479 ) EffectiveArea = 0.002;
            if (fabs(SCEta) >= 1.479 && fabs(SCEta) < 2.0 ) EffectiveArea = 0.003;
            if (fabs(SCEta) >= 2.0 && fabs(SCEta) < 2.2 ) EffectiveArea = 0.009;
            if (fabs(SCEta) >= 2.2 && fabs(SCEta) < 2.3 ) EffectiveArea = 0.003;
            if (fabs(SCEta) >= 2.3  ) EffectiveArea = 0.011;
        }
        if (type == kMuGammaIsoDR0p1To0p2) {
            if (fabs(SCEta) >= 0.0 && fabs(SCEta) < 1.0 ) EffectiveArea = 0.012;
            if (fabs(SCEta) >= 1.0 && fabs(SCEta) < 1.479 ) EffectiveArea = 0.008;
            if (fabs(SCEta) >= 1.479 && fabs(SCEta) < 2.0 ) EffectiveArea = 0.006;
            if (fabs(SCEta) >= 2.0 && fabs(SCEta) < 2.2 ) EffectiveArea = 0.012;
            if (fabs(SCEta) >= 2.2 && fabs(SCEta) < 2.3 ) EffectiveArea = 0.019;
            if (fabs(SCEta) >= 2.3  ) EffectiveArea = 0.024;
        }
        if (type == kMuGammaIsoDR0p2To0p3) {
            if (fabs(SCEta) >= 0.0 && fabs(SCEta) < 1.0 ) EffectiveArea = 0.026;
            if (fabs(SCEta) >= 1.0 && fabs(SCEta) < 1.479 ) EffectiveArea = 0.020;
            if (fabs(SCEta) >= 1.479 && fabs(SCEta) < 2.0 ) EffectiveArea = 0.012;
            if (fabs(SCEta) >= 2.0 && fabs(SCEta) < 2.2 ) EffectiveArea = 0.022;
            if (fabs(SCEta) >= 2.2 && fabs(SCEta) < 2.3 ) EffectiveArea = 0.027;
            if (fabs(SCEta) >= 2.3  ) EffectiveArea = 0.034;
        }
        if (type == kMuGammaIsoDR0p3To0p4) {
            if (fabs(SCEta) >= 0.0 && fabs(SCEta) < 1.0 ) EffectiveArea = 0.042;
            if (fabs(SCEta) >= 1.0 && fabs(SCEta) < 1.479 ) EffectiveArea = 0.033;
            if (fabs(SCEta) >= 1.479 && fabs(SCEta) < 2.0 ) EffectiveArea = 0.022;
            if (fabs(SCEta) >= 2.0 && fabs(SCEta) < 2.2 ) EffectiveArea = 0.036;
            if (fabs(SCEta) >= 2.2 && fabs(SCEta) < 2.3 ) EffectiveArea = 0.059;
            if (fabs(SCEta) >= 2.3  ) EffectiveArea = 0.068;
        }
        if (type == kMuGammaIsoDR0p4To0p5) {
            if (fabs(SCEta) >= 0.0 && fabs(SCEta) < 1.0 ) EffectiveArea = 0.060;
            if (fabs(SCEta) >= 1.0 && fabs(SCEta) < 1.479 ) EffectiveArea = 0.043;
            if (fabs(SCEta) >= 1.479 && fabs(SCEta) < 2.0 ) EffectiveArea = 0.036;
            if (fabs(SCEta) >= 2.0 && fabs(SCEta) < 2.2 ) EffectiveArea = 0.055;
            if (fabs(SCEta) >= 2.2 && fabs(SCEta) < 2.3 ) EffectiveArea = 0.092;
            if (fabs(SCEta) >= 2.3  ) EffectiveArea = 0.115;
        }
        if (type == kMuNeutralHadronIsoDR0p0To0p1) {
            if (fabs(SCEta) >= 0.0 && fabs(SCEta) < 1.0 ) EffectiveArea = 0.002;
            if (fabs(SCEta) >= 1.0 && fabs(SCEta) < 1.479 ) EffectiveArea = 0.004;
            if (fabs(SCEta) >= 1.479 && fabs(SCEta) < 2.0 ) EffectiveArea = 0.004;
            if (fabs(SCEta) >= 2.0 && fabs(SCEta) < 2.2 ) EffectiveArea = 0.004;
            if (fabs(SCEta) >= 2.2 && fabs(SCEta) < 2.3 ) EffectiveArea = 0.010;
            if (fabs(SCEta) >= 2.3  ) EffectiveArea = 0.014;
        }
        if (type == kMuNeutralHadronIsoDR0p1To0p2) {
            if (fabs(SCEta) >= 0.0 && fabs(SCEta) < 1.0 )   EffectiveArea = 0.005;
            if (fabs(SCEta) >= 1.0 && fabs(SCEta) < 1.479 ) EffectiveArea = 0.007;
            if (fabs(SCEta) >= 1.479 && fabs(SCEta) < 2.0 ) EffectiveArea = 0.009;
            if (fabs(SCEta) >= 2.0 && fabs(SCEta) < 2.2 )   EffectiveArea = 0.009;
            if (fabs(SCEta) >= 2.2 && fabs(SCEta) < 2.3 )   EffectiveArea = 0.015;
            if (fabs(SCEta) >= 2.3  )                       EffectiveArea = 0.017;
        }
        if (type == kMuNeutralHadronIsoDR0p2To0p3) {
            if (fabs(SCEta) >= 0.0 && fabs(SCEta) < 1.0 ) EffectiveArea = 0.009;
            if (fabs(SCEta) >= 1.0 && fabs(SCEta) < 1.479 ) EffectiveArea = 0.015;
            if (fabs(SCEta) >= 1.479 && fabs(SCEta) < 2.0 ) EffectiveArea = 0.016;
            if (fabs(SCEta) >= 2.0 && fabs(SCEta) < 2.2 ) EffectiveArea = 0.018;
            if (fabs(SCEta) >= 2.2 && fabs(SCEta) < 2.3 ) EffectiveArea = 0.022;
            if (fabs(SCEta) >= 2.3  ) EffectiveArea = 0.026;
        }
        if (type == kMuNeutralHadronIsoDR0p3To0p4) {
            if (fabs(SCEta) >= 0.0 && fabs(SCEta) < 1.0 ) EffectiveArea = 0.013;
            if (fabs(SCEta) >= 1.0 && fabs(SCEta) < 1.479 ) EffectiveArea = 0.021;
            if (fabs(SCEta) >= 1.479 && fabs(SCEta) < 2.0 ) EffectiveArea = 0.026;
            if (fabs(SCEta) >= 2.0 && fabs(SCEta) < 2.2 ) EffectiveArea = 0.032;
            if (fabs(SCEta) >= 2.2 && fabs(SCEta) < 2.3 ) EffectiveArea = 0.037;
            if (fabs(SCEta) >= 2.3  ) EffectiveArea = 0.042;
        }
        if (type == kMuNeutralHadronIsoDR0p4To0p5) {
            if (fabs(SCEta) >= 0.0 && fabs(SCEta) < 1.0 ) EffectiveArea = 0.017;
            if (fabs(SCEta) >= 1.0 && fabs(SCEta) < 1.479 ) EffectiveArea = 0.026;
            if (fabs(SCEta) >= 1.479 && fabs(SCEta) < 2.0 ) EffectiveArea = 0.035;
            if (fabs(SCEta) >= 2.0 && fabs(SCEta) < 2.2 ) EffectiveArea = 0.046;
            if (fabs(SCEta) >= 2.2 && fabs(SCEta) < 2.3 ) EffectiveArea = 0.063;
            if (fabs(SCEta) >= 2.3  ) EffectiveArea = 0.135;
        }
  
        return EffectiveArea;
    
    }


    return EffectiveArea;


}





double HccHelper::ElecEffArea(ElecEffectiveAreaType type, double SCEta, ElecEffectiveAreaTarget EffectiveAreaTarget)
{

    //From: https://twiki.cern.ch/twiki/bin/view/CMS/EgammaEARhoCorrection
    double EffectiveArea = 0;

    if (EffectiveAreaTarget == kElNoCorr) {
        return 0.0;
    }

    if(EffectiveAreaTarget == kElEAData2015)
    {

        if (type == kEGammaNeutralHadIso04){
            if (fabs(SCEta) >= 0.0 && fabs(SCEta) < 0.8 )   EffectiveArea = 0.1830;
            if (fabs(SCEta) >= 0.8 && fabs(SCEta) < 1.3 )   EffectiveArea = 0.1734;
            if (fabs(SCEta) >= 1.3 && fabs(SCEta) < 2.0 )   EffectiveArea = 0.1077;
            if (fabs(SCEta) >= 2.0 && fabs(SCEta) < 2.2 )   EffectiveArea = 0.1565;
            if (fabs(SCEta) >= 2.2 )                        EffectiveArea = 0.2680;
        }
        if (type == kEGammaNeutralHadIso03){
            if (fabs(SCEta) >= 0.0 && fabs(SCEta) < 1.0 )    EffectiveArea = 0.1752;
            if (fabs(SCEta) >= 1.0 && fabs(SCEta) < 1.479 )  EffectiveArea = 0.1862;
            if (fabs(SCEta) >= 1.479 && fabs(SCEta) < 2.0 )  EffectiveArea = 0.1411;
            if (fabs(SCEta) >= 2.0 && fabs(SCEta) < 2.2 )    EffectiveArea = 0.1534;
            if (fabs(SCEta) >= 2.2 && fabs(SCEta) < 2.3 )    EffectiveArea = 0.1903;
            if (fabs(SCEta) >= 2.3 && fabs(SCEta) < 2.4 )    EffectiveArea = 0.2243;
            if (fabs(SCEta) >= 2.4 && fabs(SCEta) < 2.5 )    EffectiveArea = 0.2687;
        }

        return EffectiveArea;
    }

  
    if(EffectiveAreaTarget == kElEAData2012)
    {
      
        if (type == kEGammaNeutralHadIso04){
            if (fabs(SCEta) >= 0.0 && fabs(SCEta) < 1.0 )   EffectiveArea = 0.19;
            if (fabs(SCEta) >= 1.0 && fabs(SCEta) < 1.479 ) EffectiveArea = 0.25;
            if (fabs(SCEta) >= 1.479 && fabs(SCEta) < 2.0 ) EffectiveArea = 0.12;
            if (fabs(SCEta) >= 2.0 && fabs(SCEta) < 2.2 )   EffectiveArea = 0.21;
            if (fabs(SCEta) >= 2.2 && fabs(SCEta) < 2.3 )   EffectiveArea = 0.27; 
            if (fabs(SCEta) >= 2.3 && fabs(SCEta) < 2.4 )   EffectiveArea = 0.44;
            if (fabs(SCEta) >= 2.4 )                        EffectiveArea = 0.52;
        }
	
        return EffectiveArea;
    }

    if(EffectiveAreaTarget == kElEAData2011){

        if (type == kENeutralHadIso04){
            if (fabs(SCEta) >= 0.0 && fabs(SCEta) < 1.0 )   EffectiveArea = 0.044;
            if (fabs(SCEta) >= 1.0 && fabs(SCEta) < 1.479 ) EffectiveArea = 0.065;
            if (fabs(SCEta) >= 1.479 && fabs(SCEta) < 2.0 ) EffectiveArea = 0.068;
            if (fabs(SCEta) >= 2.0 && fabs(SCEta) < 2.2 )   EffectiveArea = 0.057;
            if (fabs(SCEta) >= 2.2 && fabs(SCEta) < 2.3 )   EffectiveArea = 0.058; 
            if (fabs(SCEta) >= 2.3 && fabs(SCEta) < 2.4 )   EffectiveArea = 0.061;
            if (fabs(SCEta) >= 2.4 )                        EffectiveArea = 0.11;
        }
        if (type == kEGammaIso04){
            if (fabs(SCEta) >= 0.0 && fabs(SCEta) < 1.0 )   EffectiveArea = 0.14;
            if (fabs(SCEta) >= 1.0 && fabs(SCEta) < 1.479 ) EffectiveArea = 0.13;
            if (fabs(SCEta) >= 1.479 && fabs(SCEta) < 2.0 ) EffectiveArea = 0.079;
            if (fabs(SCEta) >= 2.0 && fabs(SCEta) < 2.2 )   EffectiveArea = 0.13;
            if (fabs(SCEta) >= 2.2 && fabs(SCEta) < 2.3 )   EffectiveArea = 0.15; 
            if (fabs(SCEta) >= 2.3 && fabs(SCEta) < 2.4 )   EffectiveArea = 0.16;
            if (fabs(SCEta) >= 2.4 )                        EffectiveArea = 0.18;
        }
        if (type == kEGammaNeutralHadIso04){
            if (fabs(SCEta) >= 0.0 && fabs(SCEta) < 1.0 )   EffectiveArea = 0.18;
            if (fabs(SCEta) >= 1.0 && fabs(SCEta) < 1.479 ) EffectiveArea = 0.20;
            if (fabs(SCEta) >= 1.479 && fabs(SCEta) < 2.0 ) EffectiveArea = 0.15;
            if (fabs(SCEta) >= 2.0 && fabs(SCEta) < 2.2 )   EffectiveArea = 0.19;
            if (fabs(SCEta) >= 2.2 && fabs(SCEta) < 2.3 )   EffectiveArea = 0.21; 
            if (fabs(SCEta) >= 2.3 && fabs(SCEta) < 2.4 )   EffectiveArea = 0.22;
            if (fabs(SCEta) >= 2.4 )                        EffectiveArea = 0.29;
        }

        if (type == kENeutralHadIso03){
            if (fabs(SCEta) >= 0.0 && fabs(SCEta) < 1.0 )   EffectiveArea = 0.024;
            if (fabs(SCEta) >= 1.0 && fabs(SCEta) < 1.479 ) EffectiveArea = 0.037;
            if (fabs(SCEta) >= 1.479 && fabs(SCEta) < 2.0 ) EffectiveArea = 0.037;
            if (fabs(SCEta) >= 2.0 && fabs(SCEta) < 2.2 )   EffectiveArea = 0.023;
            if (fabs(SCEta) >= 2.2 && fabs(SCEta) < 2.3 )   EffectiveArea = 0.023; 
            if (fabs(SCEta) >= 2.3 && fabs(SCEta) < 2.4 )   EffectiveArea = 0.021;
            if (fabs(SCEta) >= 2.4 )                        EffectiveArea = 0.021;
        }
        if (type == kEGammaIso03){
            if (fabs(SCEta) >= 0.0 && fabs(SCEta) < 1.0 )   EffectiveArea = 0.081;
            if (fabs(SCEta) >= 1.0 && fabs(SCEta) < 1.479 ) EffectiveArea = 0.084;
            if (fabs(SCEta) >= 1.479 && fabs(SCEta) < 2.0 ) EffectiveArea = 0.048;
            if (fabs(SCEta) >= 2.0 && fabs(SCEta) < 2.2 )   EffectiveArea = 0.089;
            if (fabs(SCEta) >= 2.2 && fabs(SCEta) < 2.3 )   EffectiveArea = 0.092; 
            if (fabs(SCEta) >= 2.3 && fabs(SCEta) < 2.4 )   EffectiveArea = 0.097;
            if (fabs(SCEta) >= 2.4 )                        EffectiveArea = 0.11;
        }
        if (type == kEGammaNeutralHadIso03){
            if (fabs(SCEta) >= 0.0 && fabs(SCEta) < 1.0 )   EffectiveArea = 0.10;
            if (fabs(SCEta) >= 1.0 && fabs(SCEta) < 1.479 ) EffectiveArea = 0.12;
            if (fabs(SCEta) >= 1.479 && fabs(SCEta) < 2.0 ) EffectiveArea = 0.085;
            if (fabs(SCEta) >= 2.0 && fabs(SCEta) < 2.2 )   EffectiveArea = 0.11;
            if (fabs(SCEta) >= 2.2 && fabs(SCEta) < 2.3 )   EffectiveArea = 0.12; 
            if (fabs(SCEta) >= 2.3 && fabs(SCEta) < 2.4 )   EffectiveArea = 0.12;
            if (fabs(SCEta) >= 2.4 )                        EffectiveArea = 0.13;
        }

        return EffectiveArea;
    }

    if(EffectiveAreaTarget == kElEAFall11MC){

        if (type == kENeutralHadIso04){
            if (fabs(SCEta) >= 0.0 && fabs(SCEta) < 1.0 )   EffectiveArea = 0.041;
            if (fabs(SCEta) >= 1.0 && fabs(SCEta) < 1.479 ) EffectiveArea = 0.068;
            if (fabs(SCEta) >= 1.479 && fabs(SCEta) < 2.0 ) EffectiveArea = 0.075;
            if (fabs(SCEta) >= 2.0 && fabs(SCEta) < 2.2 )   EffectiveArea = 0.068;
            if (fabs(SCEta) >= 2.2 && fabs(SCEta) < 2.3 )   EffectiveArea = 0.072; 
            if (fabs(SCEta) >= 2.3 && fabs(SCEta) < 2.4 )   EffectiveArea = 0.077;
            if (fabs(SCEta) >= 2.4 )                        EffectiveArea = 0.14;
        }
        if (type == kEGammaIso04){
            if (fabs(SCEta) >= 0.0 && fabs(SCEta) < 1.0 )   EffectiveArea = 0.14;
            if (fabs(SCEta) >= 1.0 && fabs(SCEta) < 1.479 ) EffectiveArea = 0.14;
            if (fabs(SCEta) >= 1.479 && fabs(SCEta) < 2.0 ) EffectiveArea = 0.084;
            if (fabs(SCEta) >= 2.0 && fabs(SCEta) < 2.2 )   EffectiveArea = 0.15;
            if (fabs(SCEta) >= 2.2 && fabs(SCEta) < 2.3 )   EffectiveArea = 0.20; 
            if (fabs(SCEta) >= 2.3 && fabs(SCEta) < 2.4 )   EffectiveArea = 0.22;
            if (fabs(SCEta) >= 2.4 )                        EffectiveArea = 0.26;
        }
        if (type == kEGammaNeutralHadIso04){
            if (fabs(SCEta) >= 0.0 && fabs(SCEta) < 1.0 )   EffectiveArea = 0.18;
            if (fabs(SCEta) >= 1.0 && fabs(SCEta) < 1.479 ) EffectiveArea = 0.21;
            if (fabs(SCEta) >= 1.479 && fabs(SCEta) < 2.0 ) EffectiveArea = 0.16;
            if (fabs(SCEta) >= 2.0 && fabs(SCEta) < 2.2 )   EffectiveArea = 0.22;
            if (fabs(SCEta) >= 2.2 && fabs(SCEta) < 2.3 )   EffectiveArea = 0.27; 
            if (fabs(SCEta) >= 2.3 && fabs(SCEta) < 2.4 )   EffectiveArea = 0.30;
            if (fabs(SCEta) >= 2.4 )                        EffectiveArea = 0.41;
        }

        if (type == kENeutralHadIso03){
            if (fabs(SCEta) >= 0.0 && fabs(SCEta) < 1.0 )   EffectiveArea = 0.022;
            if (fabs(SCEta) >= 1.0 && fabs(SCEta) < 1.479 ) EffectiveArea = 0.039;
            if (fabs(SCEta) >= 1.479 && fabs(SCEta) < 2.0 ) EffectiveArea = 0.040;
            if (fabs(SCEta) >= 2.0 && fabs(SCEta) < 2.2 )   EffectiveArea = 0.028;
            if (fabs(SCEta) >= 2.2 && fabs(SCEta) < 2.3 )   EffectiveArea = 0.027; 
            if (fabs(SCEta) >= 2.3 && fabs(SCEta) < 2.4 )   EffectiveArea = 0.024;
            if (fabs(SCEta) >= 2.4 )                        EffectiveArea = 0.030;
        }
        if (type == kEGammaIso03){
            if (fabs(SCEta) >= 0.0 && fabs(SCEta) < 1.0 )   EffectiveArea = 0.084;
            if (fabs(SCEta) >= 1.0 && fabs(SCEta) < 1.479 ) EffectiveArea = 0.090;
            if (fabs(SCEta) >= 1.479 && fabs(SCEta) < 2.0 ) EffectiveArea = 0.049;
            if (fabs(SCEta) >= 2.0 && fabs(SCEta) < 2.2 )   EffectiveArea = 0.099;
            if (fabs(SCEta) >= 2.2 && fabs(SCEta) < 2.3 )   EffectiveArea = 0.122; 
            if (fabs(SCEta) >= 2.3 && fabs(SCEta) < 2.4 )   EffectiveArea = 0.132;
            if (fabs(SCEta) >= 2.4 )                        EffectiveArea = 0.155;
        }
        if (type == kEGammaNeutralHadIso03){
            if (fabs(SCEta) >= 0.0 && fabs(SCEta) < 1.0 )   EffectiveArea = 0.11;
            if (fabs(SCEta) >= 1.0 && fabs(SCEta) < 1.479 ) EffectiveArea = 0.13;
            if (fabs(SCEta) >= 1.479 && fabs(SCEta) < 2.0 ) EffectiveArea = 0.089;
            if (fabs(SCEta) >= 2.0 && fabs(SCEta) < 2.2 )   EffectiveArea = 0.13;
            if (fabs(SCEta) >= 2.2 && fabs(SCEta) < 2.3 )   EffectiveArea = 0.15; 
            if (fabs(SCEta) >= 2.3 && fabs(SCEta) < 2.4 )   EffectiveArea = 0.16;
            if (fabs(SCEta) >= 2.4 )                        EffectiveArea = 0.19;
        }

        return EffectiveArea;
    }
  
    return EffectiveArea;

}

 
float HccHelper::kfactor_qqZZ_qcd_dPhi(float GENdPhiZZ, int finalState)
{

    // finalState=1 : 4e/4mu/4tau
    // finalState=2 : 2e2mu/2mutau/2e2tau

    float k=0.0;

    if (finalState==1) {        
        k+=1.515838921760*(abs(GENdPhiZZ)>0.0&&abs(GENdPhiZZ)<=0.1);
        k+=1.496256665410*(abs(GENdPhiZZ)>0.1&&abs(GENdPhiZZ)<=0.2);
        k+=1.495522061910*(abs(GENdPhiZZ)>0.2&&abs(GENdPhiZZ)<=0.3);
        k+=1.483273154250*(abs(GENdPhiZZ)>0.3&&abs(GENdPhiZZ)<=0.4);
        k+=1.465589701130*(abs(GENdPhiZZ)>0.4&&abs(GENdPhiZZ)<=0.5);
        k+=1.491500887510*(abs(GENdPhiZZ)>0.5&&abs(GENdPhiZZ)<=0.6);
        k+=1.441183580450*(abs(GENdPhiZZ)>0.6&&abs(GENdPhiZZ)<=0.7);
        k+=1.440830603990*(abs(GENdPhiZZ)>0.7&&abs(GENdPhiZZ)<=0.8);
        k+=1.414339019120*(abs(GENdPhiZZ)>0.8&&abs(GENdPhiZZ)<=0.9);
        k+=1.422534218560*(abs(GENdPhiZZ)>0.9&&abs(GENdPhiZZ)<=1.0);
        k+=1.401037066000*(abs(GENdPhiZZ)>1.0&&abs(GENdPhiZZ)<=1.1);
        k+=1.408539428810*(abs(GENdPhiZZ)>1.1&&abs(GENdPhiZZ)<=1.2);
        k+=1.381247744080*(abs(GENdPhiZZ)>1.2&&abs(GENdPhiZZ)<=1.3);
        k+=1.370553357430*(abs(GENdPhiZZ)>1.3&&abs(GENdPhiZZ)<=1.4);
        k+=1.347323316000*(abs(GENdPhiZZ)>1.4&&abs(GENdPhiZZ)<=1.5);
        k+=1.340113437450*(abs(GENdPhiZZ)>1.5&&abs(GENdPhiZZ)<=1.6);
        k+=1.312661036510*(abs(GENdPhiZZ)>1.6&&abs(GENdPhiZZ)<=1.7);
        k+=1.290055062010*(abs(GENdPhiZZ)>1.7&&abs(GENdPhiZZ)<=1.8);
        k+=1.255322614790*(abs(GENdPhiZZ)>1.8&&abs(GENdPhiZZ)<=1.9);
        k+=1.254455642450*(abs(GENdPhiZZ)>1.9&&abs(GENdPhiZZ)<=2.0);
        k+=1.224047664420*(abs(GENdPhiZZ)>2.0&&abs(GENdPhiZZ)<=2.1);
        k+=1.178816782670*(abs(GENdPhiZZ)>2.1&&abs(GENdPhiZZ)<=2.2);
        k+=1.162624827140*(abs(GENdPhiZZ)>2.2&&abs(GENdPhiZZ)<=2.3);
        k+=1.105401140940*(abs(GENdPhiZZ)>2.3&&abs(GENdPhiZZ)<=2.4);
        k+=1.074749265690*(abs(GENdPhiZZ)>2.4&&abs(GENdPhiZZ)<=2.5);
        k+=1.021864599380*(abs(GENdPhiZZ)>2.5&&abs(GENdPhiZZ)<=2.6);
        k+=0.946334793286*(abs(GENdPhiZZ)>2.6&&abs(GENdPhiZZ)<=2.7);
        k+=0.857458082628*(abs(GENdPhiZZ)>2.7&&abs(GENdPhiZZ)<=2.8);
        k+=0.716607670482*(abs(GENdPhiZZ)>2.8&&abs(GENdPhiZZ)<=2.9);
        k+=1.132841784840*(abs(GENdPhiZZ)>2.9&&abs(GENdPhiZZ)<=3.1416);
    }

    if (finalState==2) {
       k+=1.513834489150*(abs(GENdPhiZZ)>0.0&&abs(GENdPhiZZ)<=0.1);
       k+=1.541738780180*(abs(GENdPhiZZ)>0.1&&abs(GENdPhiZZ)<=0.2);
       k+=1.497829632510*(abs(GENdPhiZZ)>0.2&&abs(GENdPhiZZ)<=0.3);
       k+=1.534956782920*(abs(GENdPhiZZ)>0.3&&abs(GENdPhiZZ)<=0.4);
       k+=1.478217033060*(abs(GENdPhiZZ)>0.4&&abs(GENdPhiZZ)<=0.5);
       k+=1.504330859290*(abs(GENdPhiZZ)>0.5&&abs(GENdPhiZZ)<=0.6);
       k+=1.520626246850*(abs(GENdPhiZZ)>0.6&&abs(GENdPhiZZ)<=0.7);
       k+=1.507013090030*(abs(GENdPhiZZ)>0.7&&abs(GENdPhiZZ)<=0.8);
       k+=1.494243156250*(abs(GENdPhiZZ)>0.8&&abs(GENdPhiZZ)<=0.9);
       k+=1.450536096150*(abs(GENdPhiZZ)>0.9&&abs(GENdPhiZZ)<=1.0);
       k+=1.460812521660*(abs(GENdPhiZZ)>1.0&&abs(GENdPhiZZ)<=1.1);
       k+=1.471603622200*(abs(GENdPhiZZ)>1.1&&abs(GENdPhiZZ)<=1.2);
       k+=1.467700038200*(abs(GENdPhiZZ)>1.2&&abs(GENdPhiZZ)<=1.3);
       k+=1.422408690640*(abs(GENdPhiZZ)>1.3&&abs(GENdPhiZZ)<=1.4);
       k+=1.397184022730*(abs(GENdPhiZZ)>1.4&&abs(GENdPhiZZ)<=1.5);
       k+=1.375593447520*(abs(GENdPhiZZ)>1.5&&abs(GENdPhiZZ)<=1.6);
       k+=1.391901318370*(abs(GENdPhiZZ)>1.6&&abs(GENdPhiZZ)<=1.7);
       k+=1.368564350560*(abs(GENdPhiZZ)>1.7&&abs(GENdPhiZZ)<=1.8);
       k+=1.317884804290*(abs(GENdPhiZZ)>1.8&&abs(GENdPhiZZ)<=1.9);
       k+=1.314019950800*(abs(GENdPhiZZ)>1.9&&abs(GENdPhiZZ)<=2.0);
       k+=1.274641749910*(abs(GENdPhiZZ)>2.0&&abs(GENdPhiZZ)<=2.1);
       k+=1.242346606820*(abs(GENdPhiZZ)>2.1&&abs(GENdPhiZZ)<=2.2);
       k+=1.244727403840*(abs(GENdPhiZZ)>2.2&&abs(GENdPhiZZ)<=2.3);
       k+=1.146259351670*(abs(GENdPhiZZ)>2.3&&abs(GENdPhiZZ)<=2.4);
       k+=1.107804993520*(abs(GENdPhiZZ)>2.4&&abs(GENdPhiZZ)<=2.5);
       k+=1.042053646740*(abs(GENdPhiZZ)>2.5&&abs(GENdPhiZZ)<=2.6);
       k+=0.973608545141*(abs(GENdPhiZZ)>2.6&&abs(GENdPhiZZ)<=2.7);
       k+=0.872169942668*(abs(GENdPhiZZ)>2.7&&abs(GENdPhiZZ)<=2.8);
       k+=0.734505279177*(abs(GENdPhiZZ)>2.8&&abs(GENdPhiZZ)<=2.9);
       k+=1.163152837230*(abs(GENdPhiZZ)>2.9&&abs(GENdPhiZZ)<=3.1416);       
    }
    if (k==0.0) return 1.1; // if something goes wrong return inclusive k-factor
    else return k;

}

float HccHelper::kfactor_qqZZ_qcd_M(float GENmassZZ, int finalState)
{

    // finalState=1 : 4e/4mu/4tau
    // finalState=2 : 2e2mu/2mutau/2e2tau

    float k=0.0;

    if (finalState==1) {
        k+=1.23613311013*(abs(GENmassZZ)>0.0&&abs(GENmassZZ)<=25.0);
        k+=1.17550314639*(abs(GENmassZZ)>25.0&&abs(GENmassZZ)<=50.0);
        k+=1.17044565911*(abs(GENmassZZ)>50.0&&abs(GENmassZZ)<=75.0);
        k+=1.03141209689*(abs(GENmassZZ)>75.0&&abs(GENmassZZ)<=100.0);
        k+=1.05285574912*(abs(GENmassZZ)>100.0&&abs(GENmassZZ)<=125.0);
        k+=1.11287217794*(abs(GENmassZZ)>125.0&&abs(GENmassZZ)<=150.0);
        k+=1.13361441158*(abs(GENmassZZ)>150.0&&abs(GENmassZZ)<=175.0);
        k+=1.10355603327*(abs(GENmassZZ)>175.0&&abs(GENmassZZ)<=200.0);
        k+=1.10053981637*(abs(GENmassZZ)>200.0&&abs(GENmassZZ)<=225.0);
        k+=1.10972676811*(abs(GENmassZZ)>225.0&&abs(GENmassZZ)<=250.0);
        k+=1.12069120525*(abs(GENmassZZ)>250.0&&abs(GENmassZZ)<=275.0);
        k+=1.11589101635*(abs(GENmassZZ)>275.0&&abs(GENmassZZ)<=300.0);
        k+=1.13906170314*(abs(GENmassZZ)>300.0&&abs(GENmassZZ)<=325.0);
        k+=1.14854594271*(abs(GENmassZZ)>325.0&&abs(GENmassZZ)<=350.0);
        k+=1.14616229031*(abs(GENmassZZ)>350.0&&abs(GENmassZZ)<=375.0);
        k+=1.14573157789*(abs(GENmassZZ)>375.0&&abs(GENmassZZ)<=400.0);
        k+=1.13829430515*(abs(GENmassZZ)>400.0&&abs(GENmassZZ)<=425.0);
        k+=1.15521193686*(abs(GENmassZZ)>425.0&&abs(GENmassZZ)<=450.0);
        k+=1.13679822698*(abs(GENmassZZ)>450.0&&abs(GENmassZZ)<=475.0);
        k+=1.13223956942*(abs(GENmassZZ)>475.0);
    }

    if (finalState==2) {
        k+=1.25094466582*(abs(GENmassZZ)>0.0&&abs(GENmassZZ)<=25.0);
        k+=1.22459455362*(abs(GENmassZZ)>25.0&&abs(GENmassZZ)<=50.0);
        k+=1.19287368979*(abs(GENmassZZ)>50.0&&abs(GENmassZZ)<=75.0);
        k+=1.04597506451*(abs(GENmassZZ)>75.0&&abs(GENmassZZ)<=100.0);
        k+=1.08323413771*(abs(GENmassZZ)>100.0&&abs(GENmassZZ)<=125.0);
        k+=1.09994968030*(abs(GENmassZZ)>125.0&&abs(GENmassZZ)<=150.0);
        k+=1.16698455800*(abs(GENmassZZ)>150.0&&abs(GENmassZZ)<=175.0);
        k+=1.10399053155*(abs(GENmassZZ)>175.0&&abs(GENmassZZ)<=200.0);
        k+=1.10592664340*(abs(GENmassZZ)>200.0&&abs(GENmassZZ)<=225.0);
        k+=1.10690381480*(abs(GENmassZZ)>225.0&&abs(GENmassZZ)<=250.0);
        k+=1.11194928918*(abs(GENmassZZ)>250.0&&abs(GENmassZZ)<=275.0);
        k+=1.13522586553*(abs(GENmassZZ)>275.0&&abs(GENmassZZ)<=300.0);
        k+=1.11895090244*(abs(GENmassZZ)>300.0&&abs(GENmassZZ)<=325.0);
        k+=1.13898508615*(abs(GENmassZZ)>325.0&&abs(GENmassZZ)<=350.0);
        k+=1.15463977506*(abs(GENmassZZ)>350.0&&abs(GENmassZZ)<=375.0);
        k+=1.17341664594*(abs(GENmassZZ)>375.0&&abs(GENmassZZ)<=400.0);
        k+=1.20093349763*(abs(GENmassZZ)>400.0&&abs(GENmassZZ)<=425.0);
        k+=1.18915554919*(abs(GENmassZZ)>425.0&&abs(GENmassZZ)<=450.0);
        k+=1.18546007375*(abs(GENmassZZ)>450.0&&abs(GENmassZZ)<=475.0);
        k+=1.12864505708*(abs(GENmassZZ)>475.0);
    }

    if (k==0.0) return 1.1;
    else return k; // if something goes wrong return inclusive k-factor

}

float HccHelper::kfactor_qqZZ_qcd_Pt(float GENpTZZ, int finalState)
{

    // finalState=1 : 4e/4mu/4tau
    // finalState=2 : 2e2mu/2mutau/2e2tau

    float k=0.0;

    if (finalState==1) {
        k+=0.64155491983*(abs(GENpTZZ)>0.0&&abs(GENpTZZ)<=5.0);
        k+=1.09985240531*(abs(GENpTZZ)>5.0&&abs(GENpTZZ)<=10.0);
        k+=1.29390628654*(abs(GENpTZZ)>10.0&&abs(GENpTZZ)<=15.0);
        k+=1.37859998571*(abs(GENpTZZ)>15.0&&abs(GENpTZZ)<=20.0);
        k+=1.42430263312*(abs(GENpTZZ)>20.0&&abs(GENpTZZ)<=25.0);
        k+=1.45038493266*(abs(GENpTZZ)>25.0&&abs(GENpTZZ)<=30.0);
        k+=1.47015377651*(abs(GENpTZZ)>30.0&&abs(GENpTZZ)<=35.0);
        k+=1.48828685748*(abs(GENpTZZ)>35.0&&abs(GENpTZZ)<=40.0);
        k+=1.50573440448*(abs(GENpTZZ)>40.0&&abs(GENpTZZ)<=45.0);
        k+=1.50211655928*(abs(GENpTZZ)>45.0&&abs(GENpTZZ)<=50.0);
        k+=1.50918720827*(abs(GENpTZZ)>50.0&&abs(GENpTZZ)<=55.0);
        k+=1.52463089491*(abs(GENpTZZ)>55.0&&abs(GENpTZZ)<=60.0);
        k+=1.52400838378*(abs(GENpTZZ)>60.0&&abs(GENpTZZ)<=65.0);
        k+=1.52418067701*(abs(GENpTZZ)>65.0&&abs(GENpTZZ)<=70.0);
        k+=1.55424382578*(abs(GENpTZZ)>70.0&&abs(GENpTZZ)<=75.0);
        k+=1.52544284222*(abs(GENpTZZ)>75.0&&abs(GENpTZZ)<=80.0);
        k+=1.57896384602*(abs(GENpTZZ)>80.0&&abs(GENpTZZ)<=85.0);
        k+=1.53034682567*(abs(GENpTZZ)>85.0&&abs(GENpTZZ)<=90.0);
        k+=1.56147329708*(abs(GENpTZZ)>90.0&&abs(GENpTZZ)<=95.0);
        k+=1.54468169268*(abs(GENpTZZ)>95.0&&abs(GENpTZZ)<=100.0);
        k+=1.57222952415*(abs(GENpTZZ)>100.0);
    }

    if (finalState==2) {
        k+=0.743602533303*(abs(GENpTZZ)>0.0&&abs(GENpTZZ)<=5.0);
        k+=1.14789453219*(abs(GENpTZZ)>5.0&&abs(GENpTZZ)<=10.0);
        k+=1.33815867892*(abs(GENpTZZ)>10.0&&abs(GENpTZZ)<=15.0);
        k+=1.41420044104*(abs(GENpTZZ)>15.0&&abs(GENpTZZ)<=20.0);
        k+=1.45511318916*(abs(GENpTZZ)>20.0&&abs(GENpTZZ)<=25.0);
        k+=1.47569225244*(abs(GENpTZZ)>25.0&&abs(GENpTZZ)<=30.0);
        k+=1.49053003693*(abs(GENpTZZ)>30.0&&abs(GENpTZZ)<=35.0);
        k+=1.50622827695*(abs(GENpTZZ)>35.0&&abs(GENpTZZ)<=40.0);
        k+=1.50328889799*(abs(GENpTZZ)>40.0&&abs(GENpTZZ)<=45.0);
        k+=1.52186945281*(abs(GENpTZZ)>45.0&&abs(GENpTZZ)<=50.0);
        k+=1.52043468754*(abs(GENpTZZ)>50.0&&abs(GENpTZZ)<=55.0);
        k+=1.53977869986*(abs(GENpTZZ)>55.0&&abs(GENpTZZ)<=60.0);
        k+=1.53491994434*(abs(GENpTZZ)>60.0&&abs(GENpTZZ)<=65.0);
        k+=1.51772882172*(abs(GENpTZZ)>65.0&&abs(GENpTZZ)<=70.0);
        k+=1.54494489131*(abs(GENpTZZ)>70.0&&abs(GENpTZZ)<=75.0);
        k+=1.57762411697*(abs(GENpTZZ)>75.0&&abs(GENpTZZ)<=80.0);
        k+=1.55078339014*(abs(GENpTZZ)>80.0&&abs(GENpTZZ)<=85.0);
        k+=1.57078191891*(abs(GENpTZZ)>85.0&&abs(GENpTZZ)<=90.0);
        k+=1.56162666568*(abs(GENpTZZ)>90.0&&abs(GENpTZZ)<=95.0);
        k+=1.54183774627*(abs(GENpTZZ)>95.0&&abs(GENpTZZ)<=100.0);
        k+=1.58485762205*(abs(GENpTZZ)>100.0);
    }

    if (k==0.0) return 1.1;
    else return k; // if something goes wrong return inclusive k-factor

}

float HccHelper::dataMC(pat::Electron electron, TH2F* hElecScaleFac, TH2F* hElecScaleFac_Cracks, TH2F* hElecScaleFacGsf, TH2F* hElecScaleFacGsfLowET)
{
    float pt = std::min(electron.pt(),499.0);
    float sceta = electron.superCluster()->eta();
    float eta = electron.eta();

    if ( eta <= 2.5 && sceta >= 2.5) sceta = 2.49;
    else if ( eta >= -2.5 && sceta <= -2.5) sceta = -2.49;

    float fac=1.0;
    if (electron.isGap()) {
        fac*=hElecScaleFac_Cracks->GetBinContent(hElecScaleFac_Cracks->FindBin(sceta,pt));        
    } else {
        fac*=hElecScaleFac->GetBinContent(hElecScaleFac->FindBin(sceta,pt));        
    }
    // GSF SF flat vs pt
    if (pt>20.0) {
        fac*=hElecScaleFacGsf->GetBinContent(hElecScaleFacGsf->FindBin(sceta,pt));
    } else {
        fac*=hElecScaleFacGsfLowET->GetBinContent(hElecScaleFacGsfLowET->FindBin(sceta,std::max((float)10.5,pt)));
    }    
    return fac;
}

float HccHelper::dataMCErr(pat::Electron electron, TH2F* hElecScaleFac, TH2F* hElecScaleFacUnc_Cracks)
{
    float pt = std::min(electron.pt(),199.0);
    float sceta = electron.superCluster()->eta();
    
    float unc = 0.0;
    if (electron.isGap()) {
        int bin = hElecScaleFacUnc_Cracks->FindBin(sceta,pt);
        unc+=hElecScaleFacUnc_Cracks->GetBinError(bin);
    } else {
        int bin = hElecScaleFac->FindBin(sceta,pt);
        unc+=hElecScaleFac->GetBinError(bin);
    }
    if (pt<20.0 || pt>75.0) unc+=0.01;

    return unc;

}

float HccHelper::dataMC(pat::Muon muon, TH2F* hMuScaleFac)
{
    float pt = std::min(muon.pt(),199.0);
    float eta = muon.eta();
    return hMuScaleFac->GetBinContent(hMuScaleFac->FindBin(eta,pt)); 
}

float HccHelper::dataMCErr(pat::Muon muon, TH2F* hMuScaleFacUnc)
{
    float pt = std::min(muon.pt(),199.0);
    float eta = muon.eta();
    return hMuScaleFacUnc->GetBinContent(hMuScaleFacUnc->FindBin(eta,pt)); 
}

float HccHelper::dataMC(double pt, float eta, TH2F* hMuScaleFac)
{
    float PT = std::min(pt,199.0);
    return hMuScaleFac->GetBinContent(hMuScaleFac->FindBin(eta,PT)); 
}

float HccHelper::dataMCErr(double pt, float eta, TH2F* hMuScaleFacUnc)
{
    float PT = std::min(pt,199.0);
    return hMuScaleFacUnc->GetBinContent(hMuScaleFacUnc->FindBin(eta,PT)); 
}




float HccHelper::get_bTagEffi(float _pt_jet, float _eta_jet, TH2F* hbTagEffi)
{
    //float = pt = std::min(jet.pt(), 599.0);
    //float eta = jet.eta();
    float pt = std::min(_pt_jet, (float)599.0);
    float aeta = abs(_eta_jet);
    return hbTagEffi->GetBinContent(hbTagEffi->FindBin(pt,aeta));
}

float HccHelper::getDVBF2jetsConstant(float ZZMass){
    return DjjVBFSpline->Eval(ZZMass);
}

float HccHelper::getDVBF1jetConstant(float ZZMass){
    return DjVBFSpline->Eval(ZZMass);
}

float HccHelper::getDWHhConstant(float ZZMass){
    return DjjWHSpline->Eval(ZZMass);
}

float HccHelper::getDZHhConstant(float ZZMass){
    return DjjZHSpline->Eval(ZZMass);
}


float HccHelper::getDbkgkinConstant(int ZZflav, float ZZMass){ // ZZflav==id1*id2*id3*id4
    if (abs(ZZflav)==11*11*11*11 || abs(ZZflav)==2*11*11*11*11 || abs(ZZflav)==2*11*11*2*11*11) return DbkgkinSpline4e->Eval(ZZMass);
    if (abs(ZZflav)==11*11*13*13 || abs(ZZflav)==2*11*11*13*13 || abs(ZZflav)==2*11*11*2*13*13) return DbkgkinSpline2e2mu->Eval(ZZMass);
    if (abs(ZZflav)==13*13*13*13 || abs(ZZflav)==2*13*13*13*13 || abs(ZZflav)==2*13*13*2*13*13) return DbkgkinSpline4mu->Eval(ZZMass);
    return 0.0;
}

float HccHelper::getDbkgConstant(int ZZflav, float ZZMass){
    return getDbkgkinConstant(ZZflav, ZZMass);
}



float HccHelper::getDbkgVBFdecConstant(int ZZflav, float ZZMass) { // ZZflav==id1*id2*id3*id4
    if (abs(ZZflav)==11*11*11*11 || abs(ZZflav)==2*11*11*11*11 || abs(ZZflav)==2*11*11*2*11*11) return DbkgVBFdecSpline4l->Eval(ZZMass);
    if (abs(ZZflav)==11*11*13*13 || abs(ZZflav)==2*11*11*13*13 || abs(ZZflav)==2*11*11*2*13*13) return DbkgVBFdecSpline2l2l->Eval(ZZMass);
    if (abs(ZZflav)==13*13*13*13 || abs(ZZflav)==2*13*13*13*13 || abs(ZZflav)==2*13*13*2*13*13) return DbkgVBFdecSpline4l->Eval(ZZMass);
    return 0.0;
}

float HccHelper::getDbkgVHdecConstant(int ZZflav, float ZZMass) { // ZZflav==id1*id2*id3*id4
    if (abs(ZZflav)==11*11*11*11 || abs(ZZflav)==2*11*11*11*11 || abs(ZZflav)==2*11*11*2*11*11) return DbkgVHdecSpline4l->Eval(ZZMass);
    if (abs(ZZflav)==11*11*13*13 || abs(ZZflav)==2*11*11*13*13 || abs(ZZflav)==2*11*11*2*13*13) return DbkgVHdecSpline2l2l->Eval(ZZMass);
    if (abs(ZZflav)==13*13*13*13 || abs(ZZflav)==2*13*13*13*13 || abs(ZZflav)==2*13*13*2*13*13) return DbkgVHdecSpline4l->Eval(ZZMass);
    return 0.0;
}

double HccHelper::photonPfIso03(pat::PFParticle pho, edm::Handle<pat::PackedCandidateCollection> pfcands) {

    double ptsum=0.0;

    for (const pat::PackedCandidate &pfc : *pfcands) {

        double dr = deltaR(pho.p4(), pfc.p4());

        if (dr>=0.3) continue;

        if (pfc.charge()!=0 && abs(pfc.pdgId())==211 && pfc.pt()>0.2) {
            if (dr>0.0001) ptsum+=pfc.pt();
        } 
        else if (pfc.charge()==0 && (abs(pfc.pdgId())==22||abs(pfc.pdgId())==130) && pfc.pt()>0.5) {
            if (dr>0.01) ptsum+=pfc.pt();
        }

    }
    return ptsum;
}

#endif
