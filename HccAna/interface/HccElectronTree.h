#ifndef HCCELECTRONTREE_H
#define HCCELECTRONTREE_H

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
 #include "DataFormats/PatCandidates/interface/Muon.h"
 #include "DataFormats/PatCandidates/interface/Photon.h"
 #include "DataFormats/PatCandidates/interface/Electron.h"
 #include "DataFormats/PatCandidates/interface/Tau.h"
 #include "DataFormats/PatCandidates/interface/Jet.h"
 #include "DataFormats/PatCandidates/interface/MET.h"
 #include "DataFormats/PatCandidates/interface/TriggerEvent.h"
 #include "DataFormats/Provenance/interface/Timestamp.h"
 #include "DataFormats/Candidate/interface/Candidate.h"
 #include "DataFormats/PatCandidates/interface/CompositeCandidate.h"
 #include "Hcc/HccAna/interface/HccHelper.h"

class HccElectronTree
{

 public:

  HccElectronTree(TString treeName,edm::Service<TFileService> fs);
  ~HccElectronTree();

  void fillElectronDumpTree(std::vector<pat::Electron> electrons, const edm::Event& iEvent, double electronRho, const reco::Vertex *&vertex, std::string elecID, const int nvtx);
  void fillElectronDumpTree(std::vector<pat::Electron> electrons, const edm::Event& iEvent, double electronRho, const reco::Vertex *&vertex, const int nvtx);


 private:
  
  double Event, Run, LumiSect;
  int nVtx;
  double pT, eta, phi, rho, SIP, pX, pY, pZ;
  int id;
  double relIso, relIsoUncorr, isoNH, isoCH, isoPhot;
  double dxy, dz, energy;
  double mva;

  HccHelper myHelper;
  
  TTree *electronTree;
    

};

#endif

#ifndef HCCELECTRONTREE_CC
#define HCCELECTRONTREE_CC


HccElectronTree::HccElectronTree(TString treeName,edm::Service<TFileService> fs)
{
  TFileDirectory electrons = fs->mkdir("electrons");
  electronTree = electrons.make<TTree>(treeName,treeName);
  electronTree->Branch("Event",&Event,"Event/D");
  electronTree->Branch("Run",&Run,"Run/D");
  electronTree->Branch("Lumi",&LumiSect,"Lumi/D");
  electronTree->Branch("nVtx",&nVtx,"nVtx/I");
  electronTree->Branch("pdgid",&id,"pdgid/I");
  electronTree->Branch("pT",&pT,"pT/D");
  electronTree->Branch("eta",&eta,"eta/D");
  electronTree->Branch("phi",&phi,"phi/D");
  electronTree->Branch("rho",&rho,"rho/D");
  electronTree->Branch("SIP",&SIP,"SIP/D");
  electronTree->Branch("pX",&pX,"pX/D");
  electronTree->Branch("pY",&pY,"pY/D");
  electronTree->Branch("pZ",&pZ,"pZ/D");
  electronTree->Branch("relIso",&relIso,"relIso/D");
  electronTree->Branch("relIsoUncorr",&relIsoUncorr,"relIsoUncorr/D");
  electronTree->Branch("isoNH",&isoNH,"isoNH/D");
  electronTree->Branch("isoCH",&isoCH,"isoCH/D");
  electronTree->Branch("isoPhot",&isoPhot,"isoPhot/D");
  electronTree->Branch("mvaID",&mva,"mvaID/D");
  electronTree->Branch("dz",&dz,"dz/D");
  electronTree->Branch("dxy",&dxy,"dxy/D");
  electronTree->Branch("energy",&energy,"energy/D");

 
}


HccElectronTree::~HccElectronTree()
{

}


void HccElectronTree::fillElectronDumpTree(std::vector<pat::Electron> electrons, const edm::Event& iEvent, double electronRho, const reco::Vertex *&vertex, const int nvtx)
{
  this->fillElectronDumpTree(electrons, iEvent, electronRho, vertex, std::string("mvaNonTrigV0"), nvtx); 
}

void HccElectronTree::fillElectronDumpTree(std::vector<pat::Electron> electrons, const edm::Event& iEvent, 
           double electronRho, const reco::Vertex *&vertex, std::string elecID, const int nvtx)
{

  Run = iEvent.id().run();
  Event = iEvent.id().event();
  LumiSect = iEvent.id().luminosityBlock();
  rho = electronRho;
  nVtx = nvtx;

  for(int i=0; i<(int)electrons.size(); i++)
  {
    pT = electrons[i].pt();
    eta = electrons[i].eta();
    phi = electrons[i].phi();
    SIP = myHelper.getSIP3D(electrons[i]);
    pX = electrons[i].px();
    pY = electrons[i].py();
    pZ = electrons[i].pz();
    id = electrons[i].pdgId();
    mva = elecID=="noEID" ? -100 :electrons[i].electronID(elecID);
    energy = electrons[i].energy();
    isoNH = electrons[i].neutralHadronIso();
    isoCH = electrons[i].chargedHadronIso();
    isoPhot = electrons[i].photonIso();
    relIso = myHelper.pfIso(electrons[i],electronRho);
    relIsoUncorr = myHelper.pfIso(electrons[i],0);
    dz = electrons[i].gsfTrack()->dz(vertex->position());  
    dxy = electrons[i].gsfTrack()->dxy(vertex->position()); 
    electronTree->Fill();
  }
      
}



#endif
