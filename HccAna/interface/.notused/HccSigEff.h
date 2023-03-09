#ifndef HZZ4LSIGEFF_H
#define HZZ4LSIGEFF_H

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
 #include "DataFormats/Candidate/interface/CandidateFwd.h"
 #include "DataFormats/PatCandidates/interface/CompositeCandidate.h"

typedef vector<const reco::Candidate *> vrc; 

class HZZ4LSigEff
{

 public:

  HZZ4LSigEff();
  HZZ4LSigEff(TString treename);
  ~HZZ4LSigEff();


  void bookSigEffHistograms(edm::Service<TFileService> fs);
  void plotSigEffHistograms();
  void makeSigEffTree();
  void advanceSigDenCounters(edm::Handle<reco::GenParticleCollection> genParticles, std::string &event, double evtWeight);
  void advanceSigDenCountersPseudo(edm::Handle<reco::GenParticleCollection> genParticles, std::string &event, double evtWeight);
  void printDecayList(edm::Handle<reco::GenParticleCollection> genParticles);
  bool IsMotherZ(const reco::GenParticle* p);
  void advanceSigNumCounters_ID(std::string genEvent, double evtWeight);
  void advanceSigNumCounters_MZ1(std::string genEvent, double evtWeight);
  void advanceSigNumCounters_MZ2(std::string genEvent, std::string recoEvent, double evtWeight);
  void advanceSigNumCounters_M4L(std::string genEvent, std::string recoEvent, double evtWeight);
  void advanceSigNumCounters_FINAL(std::string genEvent, std::string recoEvent, double evtWeight);
  void advanceSigNumCounters_FINAL(std::string genEvent, std::string recoEvent, double evtWeight,std::vector<pat::Muon> selectedMuons, std::vector<pat::Electron> selectedElectrons);
  void advanceSigNumCounters_4GeV(std::string genEvent, std::string recoEvent, double evtWeight);
  void advanceSigNumCounters_PT2010(std::string genEvent, std::string recoEvent, double evtWeight);
  double getNGen4mu();
  double getNGen4e();
  double getNGen2e2mu();
  double getNGen4muPseudo();
  double getNGen4ePseudo();
  double getNGen2e2muPseudo();




 private:

  double nGen4mu, nGen4e, nGen2e2mu;
  double nGen4muPseudo, nGen4ePseudo, nGen2e2muPseudo;
  double nReco4mu, nReco4e, nReco2e2mu;
  
  double nReco4mu_ID, nReco4e_ID, nReco2e2mu_ID;
  double nReco4mu_MZ1, nReco4e_MZ1, nReco2e2mu_MZ1;
  double nReco4mu_MZ2, nReco4e_MZ2, nReco2e2mu_MZ2;
  double nReco4mu_M4L, nReco4e_M4L, nReco2e2mu_M4L;
  double nReco4mu_PT2010, nReco4e_PT2010, nReco2e2mu_PT2010;
  double nReco4mu_4GeV, nReco4e_4GeV, nReco2e2mu_4GeV;
  double nReco4mu_FINAL, nReco4e_FINAL, nReco2e2mu_FINAL;

  double nReco4mu_FINAL_3, nReco4mu_FINAL_4, nReco4mu_FINAL_5;
  double nReco4e_FINAL_5, nReco4e_FINAL_6, nReco4e_FINAL_7;  
  double nReco2e2mu_FINAL_35, nReco2e2mu_FINAL_36, nReco2e2mu_FINAL_37;  
  double nReco2e2mu_FINAL_45, nReco2e2mu_FINAL_46, nReco2e2mu_FINAL_47;  
  double nReco2e2mu_FINAL_55, nReco2e2mu_FINAL_56, nReco2e2mu_FINAL_57;  


  TH1F *SigEff_4mu_Den, *SigEff_4e_Den, *SigEff_2e2mu_Den;
  TH1F *SigEff_4mu_Num, *SigEff_4e_Num, *SigEff_2e2mu_Num;

  TString globalTreename;

};

#endif

#ifndef HZZ4LSIGEFF_CC
#define HZZ4LSIGEFF_CC


HZZ4LSigEff::HZZ4LSigEff()
{

  nGen4mu = 0;
  nGen4e = 0;
  nGen2e2mu = 0;

  nGen4muPseudo = 0;
  nGen4ePseudo = 0;
  nGen2e2muPseudo = 0;

  nReco4mu_ID = 0;
  nReco4e_ID = 0;
  nReco2e2mu_ID = 0;
  
  nReco4mu_MZ1 = 0;
  nReco4e_MZ1 = 0;
  nReco2e2mu_MZ1 = 0;
  
  nReco4mu_MZ2 = 0;
  nReco4e_MZ2 = 0;
  nReco2e2mu_MZ2 = 0;
  
  nReco4mu_M4L = 0;
  nReco4e_M4L = 0;
  nReco2e2mu_M4L = 0;
  
  nReco4mu_FINAL = 0;
  nReco4e_FINAL = 0;
  nReco2e2mu_FINAL = 0;

  nReco4mu_FINAL_3 = 0; nReco4mu_FINAL_4 = 0; nReco4mu_FINAL_5 = 0;
  nReco4e_FINAL_5 = 0; nReco4e_FINAL_6 = 0; nReco4e_FINAL_7 = 0;  
  nReco2e2mu_FINAL_35 = 0; nReco2e2mu_FINAL_36 = 0; nReco2e2mu_FINAL_37 = 0;  
  nReco2e2mu_FINAL_45 = 0; nReco2e2mu_FINAL_46 = 0; nReco2e2mu_FINAL_47 = 0;  
  nReco2e2mu_FINAL_55 = 0; nReco2e2mu_FINAL_56 = 0; nReco2e2mu_FINAL_57 = 0;  

  nReco4mu_PT2010 = 0;
  nReco4e_PT2010 = 0;
  nReco2e2mu_PT2010 = 0;

  nReco4mu_4GeV = 0;
  nReco4e_4GeV = 0;
  nReco2e2mu_4GeV = 0;


}


HZZ4LSigEff::HZZ4LSigEff(TString treename)
{

  nGen4mu = 0;
  nGen4e = 0;
  nGen2e2mu = 0;

  nGen4muPseudo = 0;
  nGen4ePseudo = 0;
  nGen2e2muPseudo = 0;

  nReco4mu_ID = 0;
  nReco4e_ID = 0;
  nReco2e2mu_ID = 0;
  
  nReco4mu_MZ1 = 0;
  nReco4e_MZ1 = 0;
  nReco2e2mu_MZ1 = 0;
  
  nReco4mu_MZ2 = 0;
  nReco4e_MZ2 = 0;
  nReco2e2mu_MZ2 = 0;
  
  nReco4mu_M4L = 0;
  nReco4e_M4L = 0;
  nReco2e2mu_M4L = 0;
  
  nReco4mu_FINAL = 0;
  nReco4e_FINAL = 0;
  nReco2e2mu_FINAL = 0;

  nReco4mu_FINAL_3 = 0; nReco4mu_FINAL_4 = 0; nReco4mu_FINAL_5 = 0;
  nReco4e_FINAL_5 = 0; nReco4e_FINAL_6 = 0; nReco4e_FINAL_7 = 0;  
  nReco2e2mu_FINAL_35 = 0; nReco2e2mu_FINAL_36 = 0; nReco2e2mu_FINAL_37 = 0;  
  nReco2e2mu_FINAL_45 = 0; nReco2e2mu_FINAL_46 = 0; nReco2e2mu_FINAL_47 = 0;  
  nReco2e2mu_FINAL_55 = 0; nReco2e2mu_FINAL_56 = 0; nReco2e2mu_FINAL_57 = 0;  


  nReco4mu_PT2010 = 0;
  nReco4e_PT2010 = 0;
  nReco2e2mu_PT2010 = 0;

  nReco4mu_4GeV = 0;
  nReco4e_4GeV = 0;
  nReco2e2mu_4GeV = 0;

  globalTreename = treename;

}


HZZ4LSigEff::~HZZ4LSigEff()
{

}


void HZZ4LSigEff::bookSigEffHistograms(edm::Service<TFileService> fs)
{

  using namespace std;

  SigEff_4mu_Den=fs->make<TH1F>("SigEff_4mu_Den","SigEff 4mu",3,0,3);
  SigEff_4e_Den=fs->make<TH1F>("SigEff_4e_Den","SigEff 4e",3,0,3);
  SigEff_2e2mu_Den=fs->make<TH1F>("SigEff_2e2mu_Den","SigEff 2e2mu",3,0,3);
 
  SigEff_4mu_Num=fs->make<TH1F>("SigEff_4mu_Num","SigEff 4mu",10,0,10);
  SigEff_4e_Num=fs->make<TH1F>("SigEff_4e_Num","SigEff 4e",10,0,10);
  SigEff_2e2mu_Num=fs->make<TH1F>("SigEff_2e2mu_Num","SigEff 2e2mu",10,0,10);


}


void HZZ4LSigEff::plotSigEffHistograms()
{

  using namespace std;

  SigEff_4mu_Den->SetBinContent(1,nGen4mu);
  SigEff_4e_Den->SetBinContent(1,nGen4e);
  SigEff_2e2mu_Den->SetBinContent(1,nGen2e2mu);

  SigEff_4mu_Den->SetBinContent(2,nGen4muPseudo);
  SigEff_4e_Den->SetBinContent(2,nGen4ePseudo);
  SigEff_2e2mu_Den->SetBinContent(2,nGen2e2muPseudo);
 
  SigEff_4mu_Num->SetBinContent(1,nReco4mu_ID);
  SigEff_4e_Num->SetBinContent(1,nReco4e_ID);
  SigEff_2e2mu_Num->SetBinContent(1,nReco2e2mu_ID);

  SigEff_4mu_Num->SetBinContent(2,nReco4mu_MZ1);
  SigEff_4e_Num->SetBinContent(2,nReco4e_MZ1);
  SigEff_2e2mu_Num->SetBinContent(2,nReco2e2mu_MZ1);

  SigEff_4mu_Num->SetBinContent(3,nReco4mu_MZ2);
  SigEff_4e_Num->SetBinContent(3,nReco4e_MZ2);
  SigEff_2e2mu_Num->SetBinContent(3,nReco2e2mu_MZ2);

  SigEff_4mu_Num->SetBinContent(4,nReco4mu_PT2010);
  SigEff_4e_Num->SetBinContent(4,nReco4e_PT2010);
  SigEff_2e2mu_Num->SetBinContent(4,nReco2e2mu_PT2010);

  SigEff_4mu_Num->SetBinContent(5,nReco4mu_4GeV);
  SigEff_4e_Num->SetBinContent(5,nReco4e_4GeV);
  SigEff_2e2mu_Num->SetBinContent(5,nReco2e2mu_4GeV);

  SigEff_4mu_Num->SetBinContent(6,nReco4mu_M4L);
  SigEff_4e_Num->SetBinContent(6,nReco4e_M4L);
  SigEff_2e2mu_Num->SetBinContent(6,nReco2e2mu_M4L);

  SigEff_4mu_Num->SetBinContent(7,nReco4mu_FINAL);
  SigEff_4e_Num->SetBinContent(7,nReco4e_FINAL);
  SigEff_2e2mu_Num->SetBinContent(7,nReco2e2mu_FINAL);


}


void HZZ4LSigEff::makeSigEffTree()
{

  using namespace std;

  TTree *MyTree = new TTree(globalTreename,globalTreename);

  MyTree->Branch("Gen4mu",&nGen4mu,"Gen4mu/I");
  MyTree->Branch("Gen4e",&nGen4e,"Gen4e/I");
  MyTree->Branch("Gen2e2mu",&nGen2e2mu,"Gen2e2mu/I");

  MyTree->Branch("Gen4muPseudo",&nGen4muPseudo,"Gen4muPseudo/I");
  MyTree->Branch("Gen4ePseudo",&nGen4ePseudo,"Gen4ePseudo/I");
  MyTree->Branch("Gen2e2muPseudo",&nGen2e2muPseudo,"Gen2e2muPseudo/I");

  MyTree->Branch("Reco4mu_ID",&nReco4mu_ID,"Reco4mu_ID/I");
  MyTree->Branch("Reco4e_ID",&nReco4e_ID,"Reco4e_ID/I");
  MyTree->Branch("Reco2e2mu_ID",&nReco2e2mu_ID,"Reco2e2mu_ID/I");

  MyTree->Branch("Reco4mu_MZ1",&nReco4mu_MZ1,"Reco4mu_MZ1/I");
  MyTree->Branch("Reco4e_MZ1",&nReco4e_MZ1,"Reco4e_MZ1/I");
  MyTree->Branch("Reco2e2mu_MZ1",&nReco2e2mu_MZ1,"Reco2e2mu_MZ1/I");

  MyTree->Branch("Reco4mu_MZ2",&nReco4mu_MZ2,"Reco4mu_MZ2/I");
  MyTree->Branch("Reco4e_MZ2",&nReco4e_MZ2,"Reco4e_MZ2/I");
  MyTree->Branch("Reco2e2mu_MZ2",&nReco2e2mu_MZ2,"Reco2e2mu_MZ2/I");

  MyTree->Branch("Reco4mu_PT2010",&nReco4mu_PT2010,"Reco4mu_PT2010/I");
  MyTree->Branch("Reco4e_PT2010",&nReco4e_PT2010,"Reco4e_PT2010/I");
  MyTree->Branch("Reco2e2mu_PT2010",&nReco2e2mu_PT2010,"Reco2e2mu_PT2010/I");

  MyTree->Branch("Reco4mu_4GeV",&nReco4mu_4GeV,"Reco4mu_4GeV/I");
  MyTree->Branch("Reco4e_4GeV",&nReco4e_4GeV,"Reco4e_4GeV/I");
  MyTree->Branch("Reco2e2mu_4GeV",&nReco2e2mu_4GeV,"Reco2e2mu_4GeV/I");

  MyTree->Branch("Reco4mu_M4L",&nReco4mu_M4L,"Reco4mu_M4L/I");
  MyTree->Branch("Reco4e_M4L",&nReco4e_M4L,"Reco4e_M4L/I");
  MyTree->Branch("Reco2e2mu_M4L",&nReco2e2mu_M4L,"Reco2e2mu_M4L/I");

  MyTree->Branch("Reco4mu_FINAL_3",&nReco4mu_FINAL_3,"Reco4mu_FINAL_3/I");
  MyTree->Branch("Reco4mu_FINAL_4",&nReco4mu_FINAL_4,"Reco4mu_FINAL_4/I");
  MyTree->Branch("Reco4mu_FINAL_5",&nReco4mu_FINAL_5,"Reco4mu_FINAL_5/I");

  MyTree->Branch("Reco4e_FINAL_5",&nReco4e_FINAL_5,"Reco4e_FINAL_5/I");
  MyTree->Branch("Reco4e_FINAL_6",&nReco4e_FINAL_6,"Reco4e_FINAL_6/I");
  MyTree->Branch("Reco4e_FINAL_7",&nReco4e_FINAL_7,"Reco4e_FINAL_7/I");

  MyTree->Branch("Reco2e2mu_FINAL_35",&nReco2e2mu_FINAL_35,"Reco2e2mu_FINAL_35/I");
  MyTree->Branch("Reco2e2mu_FINAL_36",&nReco2e2mu_FINAL_36,"Reco2e2mu_FINAL_36/I");
  MyTree->Branch("Reco2e2mu_FINAL_37",&nReco2e2mu_FINAL_37,"Reco2e2mu_FINAL_37/I");
  MyTree->Branch("Reco2e2mu_FINAL_45",&nReco2e2mu_FINAL_45,"Reco2e2mu_FINAL_45/I");
  MyTree->Branch("Reco2e2mu_FINAL_46",&nReco2e2mu_FINAL_46,"Reco2e2mu_FINAL_46/I");
  MyTree->Branch("Reco2e2mu_FINAL_47",&nReco2e2mu_FINAL_47,"Reco2e2mu_FINAL_47/I");
  MyTree->Branch("Reco2e2mu_FINAL_55",&nReco2e2mu_FINAL_55,"Reco2e2mu_FINAL_55/I");
  MyTree->Branch("Reco2e2mu_FINAL_56",&nReco2e2mu_FINAL_56,"Reco2e2mu_FINAL_56/I");
  MyTree->Branch("Reco2e2mu_FINAL_57",&nReco2e2mu_FINAL_57,"Reco2e2mu_FINAL_57/I");

  MyTree->Fill();

}



bool HZZ4LSigEff::IsMotherZ(const reco::GenParticle* p){
	bool yes = false;
	int nMo = p->numberOfMothers();
	const reco::Candidate* g= (const reco::Candidate*)p;
	while (nMo>0) {
		if(g->mother()->pdgId() == 23) return true;
		else {
			g = (g->mother());
			nMo = g->numberOfMothers();
		}
	}
	return yes;
}


void HZZ4LSigEff::advanceSigDenCounters(edm::Handle<reco::GenParticleCollection> genParticles, std::string &event, double evtWeight)
{

  using namespace std;
  using namespace pat;
  //using namespace edm;

  int tauCount=0, nMuon=0, nElec=0, nMuonPseudo=0, nElecPseudo=0;
  //bool Brem = false;

  event = "";

  reco::GenParticleCollection::const_iterator  genPart;
  
  for(genPart = genParticles->begin(); genPart != genParticles->end(); genPart++){
    
    if( genPart->pdgId() == 15 || genPart->pdgId() == -15)
      {
	if( IsMotherZ(&*genPart) ) 
	  {
	    tauCount++;
	    
	  }
      }
    
    /*
    if( genPart->pdgId() == 22 )
      {
	if( abs(genPart->mother()->pdgId()) == 11 || abs(genPart->mother()->pdgId()) == 13 )
	  {
	    if( genPart->mother()->mother()->pdgId() == 23 || genPart->mother()->mother()->mother()->pdgId() == 23  )
	      {
		Brem = true;
	      }
	  }
      }
    */
    
    if ( (genPart->pdgId() == 13 || genPart->pdgId() == -13 || genPart->pdgId() == 11 || genPart->pdgId() == -11) && genPart->status() == 3)
      {
	// Mother is a Z                                                                                                                                   
	//if ( genPart->mother()->pdgId() == 23 || genPart->mother()->mother()->pdgId() == 23 ||
	//     genPart->mother()->mother()->mother()->pdgId() == 23 || genPart->mother()->mother()->mother()->mother()->pdgId() == 23)
	if(IsMotherZ(&*genPart))
	  {
	    
	    if( abs(genPart->pdgId()) == 13 ){ nMuon++;}                                                                  
	    if( abs(genPart->pdgId()) == 11 ){ nElec++;}                                                              
	    
	    // In fiducial volume:                                                                                                                         
	    if ( (abs(genPart->pdgId()) == 13 && abs(genPart->eta()) < 2.4) || (abs(genPart->pdgId()) == 11 && abs(genPart->eta()) < 2.5) )
	      {
		//if( abs(genPart->pdgId()) == 13 ){ nMuon++;}
		//if( abs(genPart->pdgId()) == 11 ){ nElec++;}
		
		if ( (abs(genPart->pdgId()) == 11 && genPart->pt() > 7) || ( abs(genPart->pdgId()) == 13 && genPart->pt() > 5) )
		  {
		    if( abs(genPart->pdgId()) == 13 ){ nMuonPseudo++;}
		    if( abs(genPart->pdgId()) == 11 ){ nElecPseudo++;}
		    
		  }
	      }
	    
	  }
      }
    
  }


  if( tauCount < 2 )
    {
      if( nMuon == 4 ){ nGen4mu+=evtWeight; event = "4mu";}
      if( nElec == 4 ){ nGen4e+=evtWeight; event = "4e";}
      if( nMuon == 2 && nElec == 2 ){ nGen2e2mu+=evtWeight; event = "2e2mu";}

      if( nMuonPseudo == 4 ){ nGen4muPseudo+=evtWeight;}
      if( nElecPseudo == 4 ){ nGen4ePseudo+=evtWeight; }
      if( nMuonPseudo == 2 && nElecPseudo == 2 ){ nGen2e2muPseudo+=evtWeight; }

    }else {
	    event = "tau";
    }
  if(event==""){
    //cout<<" DEBUGMATT event NONETYPE :"<<endl;
    //printDecayList(genParticles);
	
  }
  
  // cout<<"** DEBUGMATT higgs event "<<event<<endl; 
}


void HZZ4LSigEff::advanceSigNumCounters_ID(std::string genEvent, double evtWeight)
{

  using namespace std;
  using namespace pat;
  //using namespace edm;

  if( genEvent == "4mu"  ){ nReco4mu_ID+=evtWeight;   }
  if( genEvent == "4e"   ){ nReco4e_ID+=evtWeight;    }
  if( genEvent == "2e2mu"){ nReco2e2mu_ID+=evtWeight; }
  
  //cout<<"** DEBUGMATT pass 2l:  "<< genEvent <<endl;
  
}


void HZZ4LSigEff::advanceSigNumCounters_MZ1(std::string genEvent,  double evtWeight)
{

  using namespace std;
  using namespace pat;
  //using namespace edm;

  if( genEvent == "4mu" ){ nReco4mu_MZ1+=evtWeight;   }
  if( genEvent == "4e"    ){ nReco4e_MZ1+=evtWeight;    }
  if( genEvent == "2e2mu" ){ nReco2e2mu_MZ1+=evtWeight; }
  
  
}


void HZZ4LSigEff::advanceSigNumCounters_MZ2(std::string genEvent, std::string recoEvent, double evtWeight)
{

  using namespace std;
  using namespace pat;
  //using namespace edm;

  if( genEvent == "4mu" && recoEvent == "reco4mu" ){ nReco4mu_MZ2+=evtWeight;   }
  if( genEvent == "4e" && recoEvent == "reco4e"   ){ nReco4e_MZ2+=evtWeight;    }
  if( genEvent == "2e2mu" && recoEvent == "reco2e2mu" ){ nReco2e2mu_MZ2+=evtWeight; }
  
  
}


void HZZ4LSigEff::advanceSigNumCounters_M4L(std::string genEvent, std::string recoEvent, double evtWeight)
{

  using namespace std;
  using namespace pat;
  //using namespace edm;

  if( genEvent == "4mu" && recoEvent == "reco4mu" ){ nReco4mu_M4L+=evtWeight;   }
  if( genEvent == "4e" && recoEvent == "reco4e"   ){ nReco4e_M4L+=evtWeight;    }
  if( genEvent == "2e2mu" && recoEvent == "reco2e2mu" ){ nReco2e2mu_M4L+=evtWeight; }
  
  
}



void HZZ4LSigEff::advanceSigNumCounters_FINAL(std::string genEvent, std::string recoEvent, double evtWeight)
{

  using namespace std;
  using namespace pat;
  //using namespace edm;

  if( genEvent == "4mu" && recoEvent == "reco4mu" ){ nReco4mu_FINAL+=evtWeight;   }
  if( genEvent == "4e" && recoEvent == "reco4e"   ){ nReco4e_FINAL+=evtWeight;    }
  if( genEvent == "2e2mu" && recoEvent == "reco2e2mu" ){ nReco2e2mu_FINAL+=evtWeight; }
  
  
}


void HZZ4LSigEff::advanceSigNumCounters_FINAL(std::string genEvent, std::string recoEvent, double evtWeight,
					      std::vector<pat::Muon> selectedMuons, std::vector<pat::Electron> selectedElectrons )
{

  using namespace std;
  using namespace pat;
  //using namespace edm;

  if( genEvent == "4mu" && recoEvent == "reco4mu" )
    {
      if(selectedMuons[0].pt() > 3 && selectedMuons[1].pt() > 3 && selectedMuons[2].pt() > 3 && selectedMuons[3].pt() > 3) nReco4mu_FINAL_3 += evtWeight;  
      if(selectedMuons[0].pt() > 4 && selectedMuons[1].pt() > 4 && selectedMuons[2].pt() > 4 && selectedMuons[3].pt() > 4) nReco4mu_FINAL_4 += evtWeight;  
      if(selectedMuons[0].pt() > 5 && selectedMuons[1].pt() > 5 && selectedMuons[2].pt() > 5 && selectedMuons[3].pt() > 5) nReco4mu_FINAL_5 += evtWeight;  
    }
  if( genEvent == "4e" && recoEvent == "reco4e"   )
    {
      if(selectedElectrons[0].pt() > 5 && selectedElectrons[1].pt() > 5 && selectedElectrons[2].pt() > 5 && selectedElectrons[3].pt() > 5) nReco4e_FINAL_5 += evtWeight;  
      if(selectedElectrons[0].pt() > 6 && selectedElectrons[1].pt() > 6 && selectedElectrons[2].pt() > 6 && selectedElectrons[3].pt() > 6) nReco4e_FINAL_6 += evtWeight;  
      if(selectedElectrons[0].pt() > 7 && selectedElectrons[1].pt() > 7 && selectedElectrons[2].pt() > 7 && selectedElectrons[3].pt() > 7) nReco4e_FINAL_7 += evtWeight;  
    }

  if( genEvent == "2e2mu" && recoEvent == "reco2e2mu" )
    {
      if(selectedMuons[0].pt() > 3 && selectedMuons[1].pt() > 3 && selectedElectrons[0].pt() > 5 && selectedElectrons[1].pt() > 5) nReco2e2mu_FINAL_35 += evtWeight;  
      if(selectedMuons[0].pt() > 3 && selectedMuons[1].pt() > 3 && selectedElectrons[0].pt() > 6 && selectedElectrons[1].pt() > 6) nReco2e2mu_FINAL_36 += evtWeight;  
      if(selectedMuons[0].pt() > 3 && selectedMuons[1].pt() > 3 && selectedElectrons[0].pt() > 7 && selectedElectrons[1].pt() > 7) nReco2e2mu_FINAL_37 += evtWeight;  
      if(selectedMuons[0].pt() > 4 && selectedMuons[1].pt() > 4 && selectedElectrons[0].pt() > 5 && selectedElectrons[1].pt() > 5) nReco2e2mu_FINAL_45 += evtWeight;  
      if(selectedMuons[0].pt() > 4 && selectedMuons[1].pt() > 4 && selectedElectrons[0].pt() > 6 && selectedElectrons[1].pt() > 6) nReco2e2mu_FINAL_46 += evtWeight;  
      if(selectedMuons[0].pt() > 4 && selectedMuons[1].pt() > 4 && selectedElectrons[0].pt() > 7 && selectedElectrons[1].pt() > 7) nReco2e2mu_FINAL_47 += evtWeight;  
      if(selectedMuons[0].pt() > 5 && selectedMuons[1].pt() > 5 && selectedElectrons[0].pt() > 5 && selectedElectrons[1].pt() > 5) nReco2e2mu_FINAL_55 += evtWeight;  
      if(selectedMuons[0].pt() > 5 && selectedMuons[1].pt() > 5 && selectedElectrons[0].pt() > 6 && selectedElectrons[1].pt() > 6) nReco2e2mu_FINAL_56 += evtWeight;  
      if(selectedMuons[0].pt() > 5 && selectedMuons[1].pt() > 5 && selectedElectrons[0].pt() > 7 && selectedElectrons[1].pt() > 7) nReco2e2mu_FINAL_57 += evtWeight;  
        
    }
  
  
}


void HZZ4LSigEff::advanceSigNumCounters_PT2010(std::string genEvent,std::string recoEvent, double evtWeight)
{

  using namespace std;
  using namespace pat;
  //using namespace edm;

  if( genEvent == "4mu" && recoEvent == "reco4mu" ){ nReco4mu_PT2010+=evtWeight;   }
  if( genEvent == "4e" && recoEvent == "reco4e"  ){ nReco4e_PT2010+=evtWeight;    }
  if( genEvent == "2e2mu" && recoEvent == "reco2e2mu"){ nReco2e2mu_PT2010+=evtWeight; }
  
  
}


void HZZ4LSigEff::advanceSigNumCounters_4GeV(std::string genEvent, std::string recoEvent, double evtWeight)
{

  using namespace std;
  using namespace pat;
  //using namespace edm;

  if( genEvent == "4mu" && recoEvent == "reco4mu" ){ nReco4mu_4GeV+=evtWeight;   }
  if( genEvent == "4e" && recoEvent == "reco4e"   ){ nReco4e_4GeV+=evtWeight;    }
  if( genEvent == "2e2mu" && recoEvent == "reco2e2mu" ){ nReco2e2mu_4GeV+=evtWeight; }
  
  
}

void HZZ4LSigEff::printDecayList(edm::Handle<reco::GenParticleCollection> particles){
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

	int idx  = -1;
	int iMo1 = -1;
	int iMo2 = -1;
	int iDa1 = -1;
	int iDa2 = -1;

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



double HZZ4LSigEff::getNGen4mu(){ return nGen4mu;}
double HZZ4LSigEff::getNGen4e(){ return nGen4e;}
double HZZ4LSigEff::getNGen2e2mu(){return nGen2e2mu;}

double HZZ4LSigEff::getNGen4muPseudo(){ return nGen4muPseudo;}
double HZZ4LSigEff::getNGen4ePseudo(){ return nGen4ePseudo;}
double HZZ4LSigEff::getNGen2e2muPseudo(){return nGen2e2muPseudo;}


#endif
