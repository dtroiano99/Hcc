#ifndef HCCPHOTONTREE_H
#define HCCPHOTONTREE_H

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

class HccPhotonTree
{
  public:
    HccPhotonTree(TString treeName,edm::Service<TFileService> fs);
    ~HccPhotonTree();
    void fillPhotonDumpTree(std::vector<pat::PFParticle> photons,std::vector<double> deltaRVec, const edm::Event& iEvent, const reco::Vertex *&vertex); 

  private:
    double Event, Run, LumiSect;
    double pT, eta, phi, pX, pY, pZ;
    double relIso, isoNH, isoCH, isoCHPU, isoPhot; 
    double energy, deltaR;
    HccHelper myHelper;
    TTree *photonTree;  
};

#endif

#ifndef HCCPHOTONTREE_CC
#define HCCPHOTONTREE_CC


HccPhotonTree::HccPhotonTree(TString treeName,edm::Service<TFileService> fs)
{
  TFileDirectory photons = fs->mkdir("photons");
  photonTree = photons.make<TTree>(treeName,treeName);
  photonTree->Branch("Event",&Event,"Event/D");
  photonTree->Branch("Run",&Run,"Run/D");
  photonTree->Branch("Lumi",&LumiSect,"Lumi/D");
  photonTree->Branch("pT",&pT,"pT/D");
  photonTree->Branch("eta",&eta,"eta/D");
  photonTree->Branch("phi",&phi,"phi/D");
  photonTree->Branch("pX",&pX,"pX/D");
  photonTree->Branch("pY",&pY,"pY/D");
  photonTree->Branch("pZ",&pZ,"pZ/D");
  photonTree->Branch("relIso",&relIso,"relIso/D"); 
  photonTree->Branch("isoNH",&isoNH,"isoNH/D"); 
  photonTree->Branch("isoCH",&isoCH,"isoCH/D"); 
  photonTree->Branch("isoCHPU",&isoCHPU,"isoCHPU/D"); 
  photonTree->Branch("isoPhot",&isoPhot,"isoPhot/D"); 
  photonTree->Branch("energy",&energy,"energy/D");
  photonTree->Branch("deltaR",&deltaR,"deltaR/D");

}


HccPhotonTree::~HccPhotonTree()
{

}


void HccPhotonTree::fillPhotonDumpTree(std::vector<pat::PFParticle> photons,std::vector<double> deltaRVec, 
					 const edm::Event& iEvent, const reco::Vertex *&vertex)
{
  Run = iEvent.id().run();
  Event = iEvent.id().event();
  LumiSect = iEvent.id().luminosityBlock();

  for(int i=0; i<(int)photons.size(); i++)
  {
    pT = photons[i].pt();
    eta = photons[i].eta();
    phi = photons[i].phi();
    pX = photons[i].px();
    pY = photons[i].py();
    pZ = photons[i].pz();
    energy = photons[i].energy();
    isoNH = photons[i].userFloat("fsrPhotonPFIsoNHad03"); 
    isoCH = photons[i].userFloat("fsrPhotonPFIsoChHad03pt02"); 
    isoCHPU = photons[i].userFloat("fsrPhotonPFIsoChHadPU03pt02"); 
    isoPhot = photons[i].userFloat("fsrPhotonPFIsoPhoton03");
    deltaR = deltaRVec[i];
    relIso = (photons[i].userFloat("fsrPhotonPFIsoChHad03pt02") + 
              photons[i].userFloat("fsrPhotonPFIsoNHad03") + 
              photons[i].userFloat("fsrPhotonPFIsoPhoton03") + 
              photons[i].userFloat("fsrPhotonPFIsoChHadPU03pt02"))/photons[i].pt(); 

    photonTree->Fill();
  }      
}


#endif
