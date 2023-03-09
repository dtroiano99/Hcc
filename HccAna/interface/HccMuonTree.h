#ifndef HCCMUONTREE_H
#define HCCMUONTREE_H

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
#include "TLorentzVector.h"
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
#include "Hcc/HccAna/interface/HccHelper.h"

class HccMuonTree
{

 public:

  HccMuonTree(TString treeName,edm::Service<TFileService> fs);
  ~HccMuonTree();


  void fillMuonDumpTree(std::vector<pat::Muon> muons, const edm::Event& iEvent, double muonRho, const reco::Vertex *&vertex, const int nvtx);

 private:
  
  double Event, Run, LumiSect;
  int nVtx;
  double pT, eta, phi, rho, SIP, pX, pY, pZ;
  int id, pfmuon;
  double relIso, relIsoUncorr, isoNH, isoCH, isoPhot;
  double dxy, dz, energy, dB;

  HccHelper myHelper;
  TTree *muonTree;

};

#endif

#ifndef HCCMUONTREE_CC
#define HCCMUONTREE_CC


HccMuonTree::HccMuonTree(TString treeName,edm::Service<TFileService> fs)
{
  TFileDirectory muons = fs->mkdir("muons");
  muonTree = muons.make<TTree>(treeName,treeName);
  muonTree->Branch("Event",&Event,"Event/D");
  muonTree->Branch("Run",&Run,"Run/D");
  muonTree->Branch("Lumi",&LumiSect,"Lumi/D");
  muonTree->Branch("nVtx",&nVtx,"nVtx/I");
  muonTree->Branch("pT",&pT,"pT/D");
  muonTree->Branch("pdgid",&id,"pdgid/I");
  muonTree->Branch("eta",&eta,"eta/D");
  muonTree->Branch("phi",&phi,"phi/D");
  muonTree->Branch("rho",&rho,"rho/D");
  muonTree->Branch("SIP",&SIP,"SIP/D");
  muonTree->Branch("pX",&pX,"pX/D");
  muonTree->Branch("pY",&pY,"pY/D");
  muonTree->Branch("pZ",&pZ,"pZ/D");
  muonTree->Branch("relIso",&relIso,"relIso/D");
  muonTree->Branch("relIsoUncorr",&relIsoUncorr,"relIsoUncorr/D");
  muonTree->Branch("isoNH",&isoNH,"isoNH/D");
  muonTree->Branch("isoCH",&isoCH,"isoCH/D");
  muonTree->Branch("isoPhot",&isoPhot,"isoPhot/D");
  muonTree->Branch("isPFMuon",&pfmuon,"isPFMuon/O");
  muonTree->Branch("dz",&dz,"dz/D");
  muonTree->Branch("dxy",&dxy,"dxy/D");
  muonTree->Branch("energy",&energy,"energy/D");
  muonTree->Branch("dB",&dB,"dB/D");
 
}


HccMuonTree::~HccMuonTree()
{

}


void HccMuonTree::fillMuonDumpTree(std::vector<pat::Muon> muons, const edm::Event& iEvent, double muonRho, const reco::Vertex *&vertex, const int nvtx)
{
  Run = iEvent.id().run();
  Event = iEvent.id().event();
  LumiSect = iEvent.id().luminosityBlock();
  rho = muonRho;
  nVtx = nvtx;

  for(int i=0; i < (int)muons.size(); i++)
  {
    pT = muons[i].pt();
    eta = muons[i].eta();
    phi = muons[i].phi();
    SIP = myHelper.getSIP3D(muons[i]);
    pX = muons[i].px();
    pY = muons[i].py();
    pZ = muons[i].pz();
    id = muons[i].pdgId();
    pfmuon = muons[i].isPFMuon();
    energy = muons[i].energy();
    isoNH = muons[i].neutralHadronIso();
    isoCH = muons[i].chargedHadronIso();
    isoPhot = muons[i].photonIso();
    relIso = myHelper.pfIso(muons[i],muonRho);
    relIsoUncorr = myHelper.pfIso(muons[i],-1);
    dz = muons[i].muonBestTrack()->dz(vertex->position()); 
    dxy = muons[i].muonBestTrack()->dxy(vertex->position()); 
    dB = muons[i].userIsolation("PfPUChargedHadronIso");
    muonTree->Fill();
  }
      
}



#endif
