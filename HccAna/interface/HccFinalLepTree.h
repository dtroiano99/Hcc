#ifndef HCCFINALLEPTREE_H
#define HCCFINALLEPTREE_H

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

class HccFinalLepTree
{

 public:

  HccFinalLepTree(TString treeName,edm::Service<TFileService> fs);
  ~HccFinalLepTree();

  void fillFinalLepDumpTree(std::vector<pat::Muon> muons, std::vector<pat::Electron> electrons, 
			    const edm::Event& iEvent, double muonRho, double elecRho, const reco::Vertex *&vertex,
                            std::string elecID);

  void fillFinalLepDumpTree(std::vector<pat::Muon> muons, std::vector<pat::Electron> electrons, 
			    const edm::Event& iEvent, double muonRho, double elecRho, const reco::Vertex *&vertex);

 private:
  
  double Event, Run, LumiSect;
  double pT, eta, phi, rho, SIP, pX, pY, pZ, mvaID;
  int id;
  double relIso, relIsoUncorr, isoNH, isoCH, isoPhot;
  double dxy, dz, energy, dB;

  HccHelper myHelper;
  
  TTree *FinalLepTree;
    

};

#endif

#ifndef HCCFINALLEPTREE_CC
#define HCCFINALLEPTREE_CC


HccFinalLepTree::HccFinalLepTree(TString treeName,edm::Service<TFileService> fs)
{
  TFileDirectory FinalLeps = fs->mkdir("finalLeptons");
  FinalLepTree = FinalLeps.make<TTree>(treeName,treeName);
  FinalLepTree->Branch("Event",&Event,"Event/D");
  FinalLepTree->Branch("Run",&Run,"Run/D");
  FinalLepTree->Branch("Lumi",&LumiSect,"Lumi/D");
  FinalLepTree->Branch("pT",&pT,"pT/D");
  FinalLepTree->Branch("pdgid",&id,"pdgid/I");
  FinalLepTree->Branch("eta",&eta,"eta/D");
  FinalLepTree->Branch("phi",&phi,"phi/D");
  FinalLepTree->Branch("rho",&rho,"rho/D");
  FinalLepTree->Branch("SIP",&SIP,"SIP/D");
  FinalLepTree->Branch("pX",&pX,"pX/D");
  FinalLepTree->Branch("pY",&pY,"pY/D");
  FinalLepTree->Branch("pZ",&pZ,"pZ/D");
  FinalLepTree->Branch("relIso",&relIso,"relIso/D");
  FinalLepTree->Branch("relIsoUncorr",&relIsoUncorr,"relIsoUncorr/D");
  FinalLepTree->Branch("isoNH",&isoNH,"isoNH/D");
  FinalLepTree->Branch("isoCH",&isoCH,"isoCH/D");
  FinalLepTree->Branch("isoPhot",&isoPhot,"isoPhot/D");
  FinalLepTree->Branch("mvaID",&mvaID,"mvaID/D");
  FinalLepTree->Branch("dz",&dz,"dz/D");
  FinalLepTree->Branch("dxy",&dxy,"dxy/D");
  FinalLepTree->Branch("energy",&energy,"energy/D");
  FinalLepTree->Branch("dB",&dB,"dB/D");
 
}


HccFinalLepTree::~HccFinalLepTree()
{

}


void HccFinalLepTree::fillFinalLepDumpTree(std::vector<pat::Muon> muons, std::vector<pat::Electron> electrons, 
					     const edm::Event& iEvent, double muonRho, double elecRho, const reco::Vertex *&vertex)
{
  this->fillFinalLepDumpTree(muons, electrons, iEvent, muonRho, elecRho, vertex, std::string("mvaNonTrigV0"));
}

void HccFinalLepTree::fillFinalLepDumpTree(std::vector<pat::Muon> muons, std::vector<pat::Electron> electrons, 
                       const edm::Event& iEvent, double muonRho, double elecRho, const reco::Vertex *&vertex,
                        std::string elecID)
{

  Run = iEvent.id().run();
  Event = iEvent.id().event();
  LumiSect = iEvent.id().luminosityBlock();

  for(unsigned int i = 0; i < muons.size(); i++)
    {
      pT = muons[i].pt();
      eta = muons[i].eta();
      phi = muons[i].phi();
      SIP = myHelper.getSIP3D(muons[i]);
      pX = muons[i].px();
      pY = muons[i].py();
      pZ = muons[i].pz();
      id = muons[i].pdgId();
      mvaID = muons[i].isPFMuon();
      energy = muons[i].energy();
      isoNH = muons[i].neutralHadronIso();
      isoCH = muons[i].chargedHadronIso();
      isoPhot = muons[i].photonIso();
      relIso = myHelper.pfIso(muons[i],muonRho);
      relIsoUncorr = myHelper.pfIso(muons[i],0);
      dz = muons[i].track()->dz(vertex->position()); 
      dxy = muons[i].track()->dxy(vertex->position());
      rho = muonRho;
      dB = muons[i].userIsolation("PfPUChargedHadronIso");

      FinalLepTree->Fill();

    }

  for(unsigned int i = 0; i < electrons.size(); i++)
    {
      pT = electrons[i].pt();
      eta = electrons[i].eta();
      phi = electrons[i].phi();
      SIP = myHelper.getSIP3D(electrons[i]);
      pX = electrons[i].px();
      pY = electrons[i].py();
      pZ = electrons[i].pz();
      id = electrons[i].pdgId();
      mvaID = elecID=="noEID" ? -100 : electrons[i].electronID(elecID);
      energy = electrons[i].energy();
      isoNH = electrons[i].neutralHadronIso();
      isoCH = electrons[i].chargedHadronIso();
      isoPhot = electrons[i].photonIso();
      relIso = myHelper.pfIso(electrons[i],elecRho);
      relIsoUncorr = myHelper.pfIso(electrons[i],0);
      dz = electrons[i].gsfTrack()->dz(vertex->position()); 
      dxy = electrons[i].gsfTrack()->dxy(vertex->position());
      rho = elecRho;
      dB = -1;

      FinalLepTree->Fill();

    }
      
}



#endif
