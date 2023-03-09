// -*- C++ -*-
//
// Package:    HccGenEvents
// Class:      HccGenEvents
// 
/*
 
  Inherit from UFHZZ4LGenEvents UFHZZ4LGenEvents.cc UFHZZAnalysis8TeV/UFHZZ4LGenEvents/src/UFHZZ4LGenEvents.cc HZZ4L analysis
  
*/
//
//
//

// system include files
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

#define PI 3.14159

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
#include "DataFormats/Common/interface/Association.h"
#include "DataFormats/Common/interface/ValueMap.h"

using namespace std;
using namespace edm;

//
// class declaration
//

class HccGenEvents : public edm::EDAnalyzer {
public:
  explicit HccGenEvents(const edm::ParameterSet&);
  ~HccGenEvents();
  
  static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);
  
  
private:
  virtual void beginJob() ;
  virtual void analyze(const edm::Event&, const edm::EventSetup&);
  virtual void endJob() ;
  
  virtual void beginRun(edm::Run const&, const edm::EventSetup& iSetup);
  virtual void endRun(edm::Run const&, edm::EventSetup const&);
  virtual void beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&);
  virtual void endLuminosityBlock(edm::LuminosityBlock const& lumiSeg,edm::EventSetup const& eSetup);
  


  void fillGenEvent(edm::Handle<reco::GenParticleCollection> genParticles,std::vector<reco::GenParticle> &Higgs, 
		    std::vector<reco::GenParticle> &Zs, 
		    std::vector<reco::GenParticle> &leptonsS1, std::vector<reco::GenParticle> &leptonsS3);
  void fillGenTree(edm::Handle<reco::GenParticleCollection> genParticles);
  void fillTreeVariables(std::vector<reco::GenParticle> Higgs, 
			 std::vector<reco::GenParticle> Zs, 
			 std::vector<reco::GenParticle> leptonsS1, std::vector<reco::GenParticle> leptonsS3);

  
  void printDecayList(edm::Handle<reco::GenParticleCollection> genParticles);
  bool IsMotherZ(const reco::GenParticle* p);
  void getMotherZ(const reco::GenParticle* p, double &px, double &py, double &pz, double &E);
  void getStatusThree(const reco::GenParticle* p, TLorentzVector &pv, int pdgid, int &id);


  int idL1_S1, idL2_S1, idL3_S1, idL4_S1;
  double pTL1_S1, pTL2_S1, pTL3_S1, pTL4_S1;
  double pXL1_S1, pXL2_S1, pXL3_S1, pXL4_S1;
  double pYL1_S1, pYL2_S1, pYL3_S1, pYL4_S1;
  double pZL1_S1, pZL2_S1, pZL3_S1, pZL4_S1;
  double EL1_S1, EL2_S1, EL3_S1, EL4_S1;
  double EZ1, EZ2;
  double pTZ1, pTZ2;
  double pXZ1, pXZ2;
  double pYZ1, pYZ2;
  double pZZ1, pZZ2;
  int chargeL1_S1, chargeL2_S1, chargeL3_S1, chargeL4_S1;
  double etaL1_S1, etaL2_S1, etaL3_S1, etaL4_S1;
  double phiL1_S1, phiL2_S1, phiL3_S1, phiL4_S1;

  int idL1_S3, idL2_S3, idL3_S3, idL4_S3;
  double pTL1_S3, pTL2_S3, pTL3_S3, pTL4_S3;
  double pXL1_S3, pXL2_S3, pXL3_S3, pXL4_S3;
  double pYL1_S3, pYL2_S3, pYL3_S3, pYL4_S3;
  double pZL1_S3, pZL2_S3, pZL3_S3, pZL4_S3;
  double EL1_S3, EL2_S3, EL3_S3, EL4_S3;
  int chargeL1_S3, chargeL2_S3, chargeL3_S3, chargeL4_S3;
  double etaL1_S3, etaL2_S3, etaL3_S3, etaL4_S3;
  double phiL1_S3, phiL2_S3, phiL3_S3, phiL4_S3;

  double MH, MZ1, MZ2;

  TTree *GenEventsTree;

  int nEventsTotal;

  // register to the TFileService
  edm::Service<TFileService> fs;
  std::map<std::string,TH1F*> histContainer_;

};


HccGenEvents::HccGenEvents(const edm::ParameterSet& iConfig):
  histContainer_()
{
  histContainer_["NEVENTS"]=fs->make<TH1F>("nEvents","nEvents in Sample",2,0,2);


  GenEventsTree = new TTree("AllGenEvents","AllGenEvents");

  GenEventsTree->Branch("idL1_S1",&idL1_S1,"idL1_S1/I");
  GenEventsTree->Branch("idL2_S1",&idL2_S1,"idL2_S1/I");
  GenEventsTree->Branch("idL3_S1",&idL3_S1,"idL3_S1/I");
  GenEventsTree->Branch("idL4_S1",&idL4_S1,"idL4_S1/I");
  GenEventsTree->Branch("EL1_S1",&EL1_S1,"EL1_S1/D");
  GenEventsTree->Branch("EL2_S1",&EL2_S1,"EL2_S1/D");
  GenEventsTree->Branch("EL3_S1",&EL3_S1,"EL3_S1/D");
  GenEventsTree->Branch("EL4_S1",&EL4_S1,"EL4_S1/D");
  
  GenEventsTree->Branch("idL1_S3",&idL1_S3,"idL1_S3/I");
  GenEventsTree->Branch("idL2_S3",&idL2_S3,"idL2_S3/I");
  GenEventsTree->Branch("idL3_S3",&idL3_S3,"idL3_S3/I");
  GenEventsTree->Branch("idL4_S3",&idL4_S3,"idL4_S3/I");
  GenEventsTree->Branch("EL1_S3",&EL1_S3,"EL1_S3/D");
  GenEventsTree->Branch("EL2_S3",&EL2_S3,"EL2_S3/D");
  GenEventsTree->Branch("EL3_S3",&EL3_S3,"EL3_S3/D");
  GenEventsTree->Branch("EL4_S3",&EL4_S3,"EL4_S3/D");
  
  GenEventsTree->Branch("EZ1",&EZ1,"EZ1/D");
  GenEventsTree->Branch("EZ2",&EZ2,"EZ2/D");
  
  GenEventsTree->Branch("massZ1",&MZ1,"massZ1/D");
  GenEventsTree->Branch("massZ2",&MZ2,"massZ2/D");
  
  GenEventsTree->Branch("pTL1_S1",&pTL1_S1,"pTL1_S1/D");
  GenEventsTree->Branch("pTL2_S1",&pTL2_S1,"pTL2_S1/D");
  GenEventsTree->Branch("pTL3_S1",&pTL3_S1,"pTL3_S1/D");
  GenEventsTree->Branch("pTL4_S1",&pTL4_S1,"pTL4_S1/D");
  GenEventsTree->Branch("pXL1_S1",&pXL1_S1,"pXL1_S1/D");
  GenEventsTree->Branch("pXL2_S1",&pXL2_S1,"pXL2_S1/D");
  GenEventsTree->Branch("pXL3_S1",&pXL3_S1,"pXL3_S1/D");
  GenEventsTree->Branch("pXL4_S1",&pXL4_S1,"pXL4_S1/D");
  GenEventsTree->Branch("pYL1_S1",&pYL1_S1,"pYL1_S1/D");
  GenEventsTree->Branch("pYL2_S1",&pYL2_S1,"pYL2_S1/D");
  GenEventsTree->Branch("pYL3_S1",&pYL3_S1,"pYL3_S1/D");
  GenEventsTree->Branch("pYL4_S1",&pYL4_S1,"pYL4_S1/D");
  GenEventsTree->Branch("pZL1_S1",&pZL1_S1,"pZL1_S1/D");
  GenEventsTree->Branch("pZL2_S1",&pZL2_S1,"pZL2_S1/D");
  GenEventsTree->Branch("pZL3_S1",&pZL3_S1,"pZL3_S1/D");
  GenEventsTree->Branch("pZL4_S1",&pZL4_S1,"pZL4_S1/D");
  
  GenEventsTree->Branch("pTL1_S3",&pTL1_S3,"pTL1_S3/D");
  GenEventsTree->Branch("pTL2_S3",&pTL2_S3,"pTL2_S3/D");
  GenEventsTree->Branch("pTL3_S3",&pTL3_S3,"pTL3_S3/D");
  GenEventsTree->Branch("pTL4_S3",&pTL4_S3,"pTL4_S3/D");
  GenEventsTree->Branch("pXL1_S3",&pXL1_S3,"pXL1_S3/D");
  GenEventsTree->Branch("pXL2_S3",&pXL2_S3,"pXL2_S3/D");
  GenEventsTree->Branch("pXL3_S3",&pXL3_S3,"pXL3_S3/D");
  GenEventsTree->Branch("pXL4_S3",&pXL4_S3,"pXL4_S3/D");
  GenEventsTree->Branch("pYL1_S3",&pYL1_S3,"pYL1_S3/D");
  GenEventsTree->Branch("pYL2_S3",&pYL2_S3,"pYL2_S3/D");
  GenEventsTree->Branch("pYL3_S3",&pYL3_S3,"pYL3_S3/D");
  GenEventsTree->Branch("pYL4_S3",&pYL4_S3,"pYL4_S3/D");
  GenEventsTree->Branch("pZL1_S3",&pZL1_S3,"pZL1_S3/D");
  GenEventsTree->Branch("pZL2_S3",&pZL2_S3,"pZL2_S3/D");
  GenEventsTree->Branch("pZL3_S3",&pZL3_S3,"pZL3_S3/D");
  GenEventsTree->Branch("pZL4_S3",&pZL4_S3,"pZL4_S3/D");
  
  GenEventsTree->Branch("pTZ1",&pTZ1,"pTZ1/D");
  GenEventsTree->Branch("pTZ2",&pTZ2,"pTZ2/D");
  GenEventsTree->Branch("pXZ1",&pXZ1,"pXZ1/D");
  GenEventsTree->Branch("pXZ2",&pXZ2,"pXZ2/D");
  GenEventsTree->Branch("pYZ1",&pYZ1,"pYZ1/D");
  GenEventsTree->Branch("pYZ2",&pYZ2,"pYZ2/D");
  GenEventsTree->Branch("pZZ1",&pZZ1,"pZZ1/D");
  GenEventsTree->Branch("pZZ2",&pZZ2,"pZZ2/D");
  
  GenEventsTree->Branch("chargeL1_S1",&chargeL1_S1,"chargeL1_S1/D");
  GenEventsTree->Branch("chargeL2_S1",&chargeL2_S1,"chargeL2_S1/D");
  GenEventsTree->Branch("chargeL3_S1",&chargeL3_S1,"chargeL3_S1/D");
  GenEventsTree->Branch("chargeL4_S1",&chargeL4_S1,"chargeL4_S1/D");
  GenEventsTree->Branch("etaL1_S1",&etaL1_S1,"etaL1_S1/D");
  GenEventsTree->Branch("etaL2_S1",&etaL2_S1,"etaL2_S1/D");
  GenEventsTree->Branch("etaL3_S1",&etaL3_S1,"etaL3_S1/D");
  GenEventsTree->Branch("etaL4_S1",&etaL4_S1,"etaL4_S1/D");
  GenEventsTree->Branch("phiL1_S1",&phiL1_S1,"phiL1_S1/D");
  GenEventsTree->Branch("phiL2_S1",&phiL2_S1,"phiL2_S1/D");
  GenEventsTree->Branch("phiL3_S1",&phiL3_S1,"phiL3_S1/D");
  GenEventsTree->Branch("phiL4_S1",&phiL4_S1,"phiL4_S1/D");
  
  GenEventsTree->Branch("chargeL1_S3",&chargeL1_S3,"chargeL1_S3/D");
  GenEventsTree->Branch("chargeL2_S3",&chargeL2_S3,"chargeL2_S3/D");
  GenEventsTree->Branch("chargeL3_S3",&chargeL3_S3,"chargeL3_S3/D");
  GenEventsTree->Branch("chargeL4_S3",&chargeL4_S3,"chargeL4_S3/D");
  GenEventsTree->Branch("etaL1_S3",&etaL1_S3,"etaL1_S3/D");
  GenEventsTree->Branch("etaL2_S3",&etaL2_S3,"etaL2_S3/D");
  GenEventsTree->Branch("etaL3_S3",&etaL3_S3,"etaL3_S3/D");
  GenEventsTree->Branch("etaL4_S3",&etaL4_S3,"etaL4_S3/D");
  GenEventsTree->Branch("phiL1_S3",&phiL1_S3,"phiL1_S3/D");
  GenEventsTree->Branch("phiL2_S3",&phiL2_S3,"phiL2_S3/D");
  GenEventsTree->Branch("phiL3_S3",&phiL3_S3,"phiL3_S3/D");
  GenEventsTree->Branch("phiL4_S3",&phiL4_S3,"phiL4_S3/D");
  
  GenEventsTree->Branch("mass4l",&MH,"mass4l/D");


}


HccGenEvents::~HccGenEvents()
{
  
  //destructor --- don't do anything here
  
}



// ------------ method called for each event  ------------
void
HccGenEvents::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{

  // ======= Get Collections ======= //

  // GEN collection
  edm::Handle<reco::GenParticleCollection> genParticles;
  iEvent.getByLabel("genParticles", genParticles);

  std::vector<reco::GenParticle> Higgs, Zs, leptonsS1, leptonsS3;
  //fillGenTree(genParticles);
  fillGenEvent(genParticles,Higgs,Zs,leptonsS1,leptonsS3);
  fillTreeVariables(Higgs,Zs,leptonsS1,leptonsS3);
  //GenEventsTree->Fill();


 #ifdef THIS_IS_AN_EVENT_EXAMPLE
     Handle<ExampleData> pIn;
    iEvent.getByLabel("example",pIn);
 #endif

 #ifdef THIS_IS_AN_EVENTSETUP_EXAMPLE
    ESHandle<SetupData> pSetup;
    iSetup.get<SetupRecord>().get(pSetup);
 #endif
 }


 // ------------ method called once each job just before starting event loop  ------------
 void 
 HccGenEvents::beginJob()
 {
   
 }

 // ------------ method called once each job just after ending the event loop  ------------
 void 
 HccGenEvents::endJob() 
 {
 }

 void
 HccGenEvents::beginRun(edm::Run const&, const edm::EventSetup& iSetup)
 {
 }


 // ------------ method called when ending the processing of a run  ------------
 void 
 HccGenEvents::endRun(edm::Run const&, edm::EventSetup const&)
 {
 }

 // ------------ method called when starting to processes a luminosity block  ------------
 void 
 HccGenEvents::beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
 {
 }

 // ------------ method called when ending the processing of a luminosity block  ------------
 void 
 HccGenEvents::endLuminosityBlock(edm::LuminosityBlock const& lumiSeg,edm::EventSetup const& eSetup)
 {

   // Keep track of all the events run over
   edm::Handle<MergeableCounter> numEventsCounter;
   lumiSeg.getByLabel("nEventsTotal", numEventsCounter);
   if(numEventsCounter.isValid())
     {
       nEventsTotal += numEventsCounter->value;
     }


 }





bool HccGenEvents::IsMotherZ(const reco::GenParticle* p){
	bool yes = false;
	int nMo = p->numberOfMothers();
	const reco::Candidate* g= (const reco::Candidate*)p;
	while (nMo==1) {
	  //cout << "Z            " << nMo << "  " << g->mother()->pdgId() << endl;
	  if(g->mother()->pdgId() == 23 || g->mother()->pdgId() == 25) return true;
	  else {
	    g = (g->mother());
	    nMo = g->numberOfMothers();
	  }
	}
	return yes;
}

void HccGenEvents::getMotherZ(const reco::GenParticle* p, double &px, double &py, double &pz, double &E)
{
  bool done = false;
  int nMo = p->numberOfMothers();
  const reco::Candidate* g= (const reco::Candidate*)p;
  while (nMo>0 && !done) {
    if(g->mother()->pdgId() == 23 && g->mother()->status() == 3){
      //cout << g->mother()->px() << nMo << endl;
      px = g->mother()->px();
      py = g->mother()->py();
      pz = g->mother()->pz();
      E  = g->mother()->energy();
      done = true;
    }
    else {
      g = (g->mother());
      nMo = g->numberOfMothers();
    }
  }

}

void HccGenEvents::getStatusThree(const reco::GenParticle* p, TLorentzVector &pv, int pdgid, int &id)
{
  bool done = false;;
  int nMo = p->numberOfMothers();
  const reco::Candidate* g= (const reco::Candidate*)p;
  while (nMo>0 && !done) {
    if(abs(g->mother()->pdgId()) == pdgid && g->mother()->status() == 3){
      //cout << g->mother()->px() << nMo << endl;
      pv.SetPxPyPzE(g->mother()->px(),g->mother()->py(),g->mother()->pz(),g->mother()->energy());
      done = true;
      id = g->pdgId();
    }
    else {
      g = (g->mother());
      nMo = g->numberOfMothers();
    }
  }

}



void HccGenEvents::fillGenEvent(edm::Handle<reco::GenParticleCollection> genParticles,std::vector<reco::GenParticle> &Higgs, 
		  std::vector<reco::GenParticle> &Zs, 
		  std::vector<reco::GenParticle> &leptonsS1, std::vector<reco::GenParticle> &leptonsS3)
{


  reco::GenParticleCollection::const_iterator  genPart;
  
  for(genPart = genParticles->begin(); genPart != genParticles->end(); genPart++)
    {
      if( abs(genPart->pdgId()) == 25 && genPart->status() == 3 ) Higgs.push_back(*genPart);
      if( abs(genPart->pdgId()) == 23 && genPart->status() == 3 ) Zs.push_back(*genPart);
      
      if( abs(genPart->pdgId()) == 13 || abs(genPart->pdgId()) == 11 )
	{
	  if( genPart->status() == 1 )
	    {
	      if(IsMotherZ(&*genPart)) leptonsS1.push_back(*genPart);
	    }
	  if( genPart->status() == 3 )
	    {
	      if(IsMotherZ(&*genPart)) leptonsS3.push_back(*genPart);
	    }
	}
      
    }
  

}

void HccGenEvents::fillGenTree(edm::Handle<reco::GenParticleCollection> genParticles)
{


  reco::GenParticleCollection::const_iterator  genPart;

  std::vector<reco::GenParticle> Higgs, Zs, leptonsS1, leptonsS3;
  
  for(genPart = genParticles->begin(); genPart != genParticles->end(); genPart++)
    {
      
      if( abs(genPart->pdgId()) == 25 && genPart->status() == 3 ) Higgs.push_back(*genPart);
      if( abs(genPart->pdgId()) == 23 && genPart->status() == 3 ) Zs.push_back(*genPart);
      
      if( abs(genPart->pdgId()) == 13 || abs(genPart->pdgId()) == 11 )
	{
	  if( genPart->status() == 1 )
	    {
	      if(IsMotherZ(&*genPart)) leptonsS1.push_back(*genPart);
	    }
	  if( genPart->status() == 3 )
	    {
	      if(IsMotherZ(&*genPart)) leptonsS3.push_back(*genPart);
	    }
	}
      
    }

  fillTreeVariables(Higgs,Zs,leptonsS1,leptonsS3);
  
}



void HccGenEvents::fillTreeVariables(std::vector<reco::GenParticle> Higgs, 
		       std::vector<reco::GenParticle> Zs, 
		       std::vector<reco::GenParticle> leptonsS1, std::vector<reco::GenParticle> leptonsS3)
{


  idL1_S1 = -999; idL2_S1 = -999; idL3_S1 = -999; idL4_S1 = -999;
  pTL1_S1 = -999; pTL2_S1 = -999; pTL3_S1 = -999; pTL4_S1 = -999;
  pXL1_S1 = -999; pXL2_S1 = -999; pXL3_S1 = -999; pXL4_S1 = -999;
  pYL1_S1 = -999; pYL2_S1 = -999; pYL3_S1 = -999; pYL4_S1 = -999;
  pZL1_S1 = -999; pZL2_S1 = -999; pZL3_S1 = -999; pZL4_S1 = -999;
  EL1_S1 = -999; EL2_S1 = -999; EL3_S1 = -999; EL4_S1 = -999;
  EZ1 = -999; EZ2 = -999;
  pTZ1 = -999; pTZ2 = -999;
  pXZ1 = -999; pXZ2 = -999;
  pYZ1 = -999; pYZ2 = -999;
  pZZ1 = -999; pZZ2 = -999;
  chargeL1_S1 = -999; chargeL2_S1 = -999; chargeL3_S1 = -999; chargeL4_S1 = -999;
  etaL1_S1 = -999; etaL2_S1 = -999; etaL3_S1 = -999; etaL4_S1 = -999;
  phiL1_S1 = -999; phiL2_S1 = -999; phiL3_S1 = -999; phiL4_S1 = -999;

  idL1_S3 = -999; idL2_S3 = -999; idL3_S3 = -999; idL4_S3 = -999;
  pTL1_S3 = -999; pTL2_S3 = -999; pTL3_S3 = -999; pTL4_S3 = -999;
  pXL1_S3 = -999; pXL2_S3 = -999; pXL3_S3 = -999; pXL4_S3 = -999;
  pYL1_S3 = -999; pYL2_S3 = -999; pYL3_S3 = -999; pYL4_S3 = -999;
  pZL1_S3 = -999; pZL2_S3 = -999; pZL3_S3 = -999; pZL4_S3 = -999;
  EL1_S3 = -999; EL2_S3 = -999; EL3_S3 = -999; EL4_S3 = -999;
  chargeL1_S3 = -999; chargeL2_S3 = -999; chargeL3_S3 = -999; chargeL4_S3 = -999;
  etaL1_S3 = -999; etaL2_S3 = -999; etaL3_S3 = -999; etaL4_S3 = -999;
  phiL1_S3 = -999; phiL2_S3 = -999; phiL3_S3 = -999; phiL4_S3 = -999;

  MH = -999; MZ1 = -999; MZ2 = -999;

  if( Higgs.size() == 1) MH = Higgs[0].mass();


  if( leptonsS1.size() == 4)
    {
      idL1_S1 = leptonsS1[0].pdgId(); idL2_S1 = leptonsS1[1].pdgId(); 
      idL3_S1 = leptonsS1[2].pdgId(); idL4_S1 = leptonsS1[3].pdgId();
      
      pTL1_S1 = leptonsS1[0].pt(); pTL2_S1 = leptonsS1[1].pt(); 
      pTL3_S1 = leptonsS1[2].pt(); pTL4_S1 = leptonsS1[3].pt();

      pXL1_S1 = leptonsS1[0].px(); pXL2_S1 = leptonsS1[1].px(); 
      pXL3_S1 = leptonsS1[2].px(); pXL4_S1 = leptonsS1[3].px();

      pYL1_S1 = leptonsS1[0].py(); pYL2_S1 = leptonsS1[1].py(); 
      pYL3_S1 = leptonsS1[2].py(); pYL4_S1 = leptonsS1[3].py();

      pZL1_S1 = leptonsS1[0].pz(); pZL2_S1 = leptonsS1[1].pz(); 
      pZL3_S1 = leptonsS1[2].pz(); pZL4_S1 = leptonsS1[3].pz();

      EL1_S1 = leptonsS1[0].energy(); EL2_S1 = leptonsS1[1].energy(); 
      EL3_S1 = leptonsS1[2].energy(); EL4_S1 = leptonsS1[3].energy();

      chargeL1_S1 = leptonsS1[0].charge(); chargeL2_S1 = leptonsS1[1].charge();
      chargeL3_S1 = leptonsS1[2].charge(); chargeL4_S1 = leptonsS1[3].charge();
   
      etaL1_S1 = leptonsS1[0].eta(); etaL2_S1 = leptonsS1[1].eta();
      etaL3_S1 = leptonsS1[2].eta(); etaL4_S1 = leptonsS1[3].eta();
     
      phiL1_S1 = leptonsS1[0].phi(); phiL2_S1 = leptonsS1[1].phi();
      phiL3_S1 = leptonsS1[2].phi(); phiL4_S1 = leptonsS1[3].phi();
    
    }

  if( Zs.size() == 2)
    {
      EZ1 = Zs[0].energy(); EZ2 = Zs[1].energy();
      pTZ1 = Zs[0].pt();    pTZ2 = Zs[1].pt();
      pXZ1 = Zs[0].px();    pXZ2 = Zs[1].px();
      pYZ1 = Zs[0].py();    pYZ2 = Zs[1].py();
      pZZ1 = Zs[0].pz();    pZZ2 = Zs[1].pz();
      MZ1  = Zs[0].mass();  MZ2  = Zs[1].mass();
    
    }

  if( leptonsS3.size() == 4)
    {
      idL1_S3 = leptonsS3[0].pdgId(); idL2_S3 = leptonsS3[1].pdgId(); 
      idL3_S3 = leptonsS3[2].pdgId(); idL4_S3 = leptonsS3[3].pdgId();
      
      pTL1_S3 = leptonsS3[0].pt(); pTL2_S3 = leptonsS3[1].pt(); 
      pTL3_S3 = leptonsS3[2].pt(); pTL4_S3 = leptonsS3[3].pt();

      pXL1_S3 = leptonsS3[0].px(); pXL2_S3 = leptonsS3[1].px(); 
      pXL3_S3 = leptonsS3[2].px(); pXL4_S3 = leptonsS3[3].px();

      pYL1_S3 = leptonsS3[0].py(); pYL2_S3 = leptonsS3[1].py(); 
      pYL3_S3 = leptonsS3[2].py(); pYL4_S3 = leptonsS3[3].py();

      pZL1_S3 = leptonsS3[0].pz(); pZL2_S3 = leptonsS3[1].pz(); 
      pZL3_S3 = leptonsS3[2].pz(); pZL4_S3 = leptonsS3[3].pz();

      EL1_S3 = leptonsS3[0].energy(); EL2_S3 = leptonsS3[1].energy(); 
      EL3_S3 = leptonsS3[2].energy(); EL4_S3 = leptonsS3[3].energy();

      chargeL1_S3 = leptonsS3[0].charge(); chargeL2_S3 = leptonsS3[1].charge();
      chargeL3_S3 = leptonsS3[2].charge(); chargeL4_S3 = leptonsS3[3].charge();
   
      etaL1_S3 = leptonsS3[0].eta(); etaL2_S3 = leptonsS3[1].eta();
      etaL3_S3 = leptonsS3[2].eta(); etaL4_S3 = leptonsS3[3].eta();
     
      phiL1_S3 = leptonsS3[0].phi(); phiL2_S3 = leptonsS3[1].phi();
      phiL3_S3 = leptonsS3[2].phi(); phiL4_S3 = leptonsS3[3].phi();
    
    }

  
  GenEventsTree->Fill();

}




void HccGenEvents::printDecayList(edm::Handle<reco::GenParticleCollection> particles){
	//Handle<reco::CandidateView> particles;
	bool printOnlyHardInteraction_ = false;
	bool printVertex_ = false;
	//bool useMessageLogger_=false;

	ostringstream out;
	char buf[256];

	out << endl;

	snprintf(buf, 256, " idx  |    ID -       Name |Stat|  Mo1  Mo2  Da1  Da2 |nMo nDa|    pt       eta     phi   |     px         py         pz        m     |"); 
	out << buf;
	if (printVertex_) {
		snprintf(buf, 256, "        vx       vy        vz     |");
		out << buf;
	}
	out << endl; 

	int idx  = -999;
	int iMo1 = -999;
	int iMo2 = -999;
	int iDa1 = -999;
	int iDa2 = -999;

	//reco::GenParticleCollection cands;
	typedef std::vector<const reco::GenParticle*> GPC;
	GPC cands;
	//vector<const Candidate *>::const_iterator found = cands.begin();
	//reco::GenParticleCollection::const_iterator found = cands.begin();
	GPC::const_iterator found = cands.begin();

	reco::GenParticleCollection::const_iterator  p;
	for(p = particles->begin();
			p != particles->end(); ++ p) {
		cands.push_back(&*p);
	}

	for(p  = particles->begin();
			p != particles->end(); 
			p ++) {
		if (printOnlyHardInteraction_ && p->status() != 3) continue;

		// Particle Name
		//int id = p->pdgId();
		string particleName = "non"; //getParticleName(id);

		// Particle Index
		idx =  p - particles->begin();

		// Particles Mothers and Daighters
		iMo1 = -1;
		iMo2 = -1;
		iDa1 = -1;
		iDa2 = -1;
		int nMo = p->numberOfMothers();
		int nDa = p->numberOfDaughters();

		if(nMo>=1) {
		found = find(cands.begin(), cands.end(), p->mother(0));
		if(found != cands.end()) iMo1 = found - cands.begin() ;

		found = find(cands.begin(), cands.end(), p->mother(nMo-1));
		if(found != cands.end()) iMo2 = found - cands.begin() ;
		}


		if(nDa>=1){
		found = find(cands.begin(), cands.end(), p->daughter(0));
		if(found != cands.end()) iDa1 = found - cands.begin() ;

		found = find(cands.begin(), cands.end(), p->daughter(nDa-1));
		if(found != cands.end()) iDa2 = found - cands.begin() ;
		}

		char buf[256];
		snprintf(buf, 256,
				" %4d | %5d - %10s | %2d | %4d %4d %4d %4d | %2d %2d | %7.3f %10.3f %6.3f | %10.3f %10.3f %10.3f %8.3f |",
				idx,
				p->pdgId(),
				particleName.c_str(),
				p->status(),
				iMo1,iMo2,iDa1,iDa2,nMo,nDa,
				p->pt(),
				p->eta(),
				p->phi(),
				p->px(),
				p->py(),
				p->pz(),
				p->mass()
			);
		out << buf;

		if (printVertex_) {
			snprintf(buf, 256, " %10.3f %10.3f %10.3f |",
					p->vertex().x(),
					p->vertex().y(),
					p->vertex().z());
			out << buf;
		}

		out << endl;
	}
	cout << out.str();
}















// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void
HccGenEvents::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);
}

//define this as a plug-in
DEFINE_FWK_MODULE(HccGenEvents);
