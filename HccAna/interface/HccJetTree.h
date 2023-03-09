#ifndef HCCJETTREE_H
#define HCCJETTREE_H

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
 #include "DataFormats/PatCandidates/interface/Jet.h"
 #include "DataFormats/PatCandidates/interface/Tau.h"
 #include "DataFormats/PatCandidates/interface/Jet.h"
 #include "DataFormats/PatCandidates/interface/MET.h"
 #include "DataFormats/PatCandidates/interface/TriggerEvent.h"
 #include "DataFormats/Provenance/interface/Timestamp.h"
 #include "DataFormats/Candidate/interface/Candidate.h"
 #include "DataFormats/PatCandidates/interface/CompositeCandidate.h"
 #include "Hcc/HccAna/interface/HccJets.h"
 //#include "CMGTools/External/interface/PileupJetIdAlgo.h" // for miniAOD
 //#include "CMGTools/External/interface/PileupJetIdentifier.h" // for miniAOD


class HccJetTree
{

 public:

  HccJetTree(TString treeName,edm::Service<TFileService> fs);
  ~HccJetTree();


  void fillJetDumpTree(edm::Handle<edm::View<pat::Jet> > jets,edm::Handle<edm::View<pat::Jet> > correctedJets, const edm::Event& iEvent, int year);

 private:
  
  double Event, Run, LumiSect;
  double pT, eta, phi;
  double pumva;
  int pfid, puidflag, puidpass;
  
  TTree *jetTree;

  HccJets JetHelper;
    

};

#endif

#ifndef HCCJETTREE_CC
#define HCCJETTREE_CC


HccJetTree::HccJetTree(TString treeName,edm::Service<TFileService> fs)
{
  TFileDirectory jets = fs->mkdir("jets");
  jetTree = jets.make<TTree>(treeName,treeName);
  jetTree->Branch("Event",&Event,"Event/D");
  jetTree->Branch("Run",&Run,"Run/D");
  jetTree->Branch("Lumi",&LumiSect,"Lumi/D");
  jetTree->Branch("pT",&pT,"pT/D");
  jetTree->Branch("eta",&eta,"eta/D");
  jetTree->Branch("phi",&phi,"phi/D");
  jetTree->Branch("PFid",&pfid,"PFid/I");
  jetTree->Branch("PUIdFlag",&puidflag,"PUIdFlag/I");
  jetTree->Branch("PUIdPass",&puidpass,"PUIdPass/I");
  jetTree->Branch("PUMVA",&pumva,"PUMVA/D");

 
}


HccJetTree::~HccJetTree()
{

}


void HccJetTree::fillJetDumpTree(edm::Handle<edm::View<pat::Jet> >  jets, edm::Handle<edm::View<pat::Jet> >  correctedJets, const edm::Event& iEvent, int year)
{

  edm::Handle<edm::ValueMap<float> > puJetIdMva;
  iEvent.getByLabel("puJetMva","full53xDiscriminant",puJetIdMva);
  //iEvent.getByLabel("puJetMva","fullDiscriminant",puJetIdMva);

  edm::Handle<edm::ValueMap<int> > puJetIdFlag;
  iEvent.getByLabel("puJetMva","full53xId",puJetIdFlag); 
  //iEvent.getByLabel("puJetMva","fullId",puJetIdFlag);

  using namespace std;

  
  Run = iEvent.id().run();
  Event = iEvent.id().event();
  LumiSect = iEvent.id().luminosityBlock();

  for(unsigned int i = 0; i < jets->size(); ++i) 
    {
      const pat::Jet & patjet = jets->at(i);
      const pat::Jet & correctedjet = correctedJets->at(i);
      //pumva   = (*puJetIdMva)[jets->refAt(i)]; // for miniAOD
      //puidflag = (*puJetIdFlag)[jets->refAt(i)]; // for miniAOD
      //puidpass =  PileupJetIdentifier::passJetId( puidflag, PileupJetIdentifier::kLoose ); // for miniAOD
      puidpass = patjet.userFloat("pileupJetId:fullDiscriminant"); // for miniAOD
      pfid = JetHelper.patjetID(correctedjet, year);
      pT = correctedjet.pt();
      eta = patjet.eta();
      phi = patjet.phi();
            
      jetTree->Fill();

    }
   
}



#endif
