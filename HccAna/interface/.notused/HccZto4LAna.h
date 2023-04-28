#ifndef HZZ4LZTO4LANA_H
#define HZZ4LZTO4LANA_H

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


class HZZ4LZto4LAna
{

 public:

  HZZ4LZto4LAna();
  HZZ4LZto4LAna(std::string appendName);
  ~HZZ4LZto4LAna();

  void bookZto4LHistograms(edm::Service<TFileService> fs, std::map<std::string,TH1F*> &histContainer_);
  void fillZto4LHistograms(std::map<std::string,TH1F*> &histContainer_ , std::vector<pat::Muon> muons, std::vector<pat::Electron> electrons, double evtWeight);
  void plotZto4LHistograms(std::map<std::string,TH1F*> &histContainer_ ,  bool weightEvents, double scaleWeight);

  
 private:
  
  std::string appName;
  std::string pt1_4mu,pt2_4mu,pt3_4mu,pt4_4mu;
  std::string pt1_4e,pt2_4e,pt3_4e,pt4_4e;
  std::string pt1_2e2mu,pt2_2e2mu,pt3_2e2mu,pt4_2e2mu;
  std::string pt1_4l,pt2_4l,pt3_4l,pt4_4l;
  std::string mass3s, massall;

  

};


#endif

#ifndef HZZ4LZTO4LANA_CC
#define HZZ4LZTO4LANA_CC

HZZ4LZto4LAna::HZZ4LZto4LAna()
{

  appName = "";
  pt1_4mu = "Zto4L_pT1_4mu";
  pt2_4mu = "Zto4L_pT2_4mu";
  pt3_4mu = "Zto4L_pT3_4mu";
  pt4_4mu = "Zto4L_pT4_4mu";
  pt1_4e = "Zto4L_pT1_4e";
  pt2_4e = "Zto4L_pT2_4e";
  pt3_4e = "Zto4L_pT3_4e";
  pt4_4e = "Zto4L_pT4_4e";
  pt1_2e2mu = "Zto4L_pT1_2e2mu";
  pt2_2e2mu = "Zto4L_pT2_2e2mu";
  pt3_2e2mu = "Zto4L_pT3_2e2mu";
  pt4_2e2mu = "Zto4L_pT4_2e2mu";
  pt1_4l = "Zto4L_pT1_4l";
  pt2_4l = "Zto4L_pT2_4l";
  pt3_4l = "Zto4L_pT3_4l";
  pt4_4l = "Zto4L_pT4_4l";
  
  mass3s = "Zto4L_mass_3softest";
  massall = "Zto4L_massAll";

  

}

HZZ4LZto4LAna::HZZ4LZto4LAna(std::string appendName)
{

  appName = appendName;
  pt1_4mu = "Zto4L_pT1_4mu"+appName;
  pt2_4mu = "Zto4L_pT2_4mu"+appName;
  pt3_4mu = "Zto4L_pT3_4mu"+appName;
  pt4_4mu = "Zto4L_pT4_4mu"+appName;
  pt1_4e = "Zto4L_pT1_4e"+appName;
  pt2_4e = "Zto4L_pT2_4e"+appName;
  pt3_4e = "Zto4L_pT3_4e"+appName;
  pt4_4e = "Zto4L_pT4_4e"+appName;
  pt1_2e2mu = "Zto4L_pT1_2e2mu"+appName;
  pt2_2e2mu = "Zto4L_pT2_2e2mu"+appName;
  pt3_2e2mu = "Zto4L_pT3_2e2mu"+appName;
  pt4_2e2mu = "Zto4L_pT4_2e2mu"+appName;
  pt1_4l = "Zto4L_pT1_4l"+appName;
  pt2_4l = "Zto4L_pT2_4l"+appName;
  pt3_4l = "Zto4L_pT3_4l"+appName;
  pt4_4l = "Zto4L_pT4_4l"+appName;
  
  mass3s = "Zto4L_mass_3softest"+appName;
  massall = "Zto4L_massAll"+appName;

}


HZZ4LZto4LAna::~HZZ4LZto4LAna()
{

}


void HZZ4LZto4LAna::bookZto4LHistograms(edm::Service<TFileService> fs, std::map<std::string,TH1F*> &histContainer_)
{
  using namespace std;
  
  

  histContainer_[pt1_4mu]=fs->make<TH1F>(pt1_4mu.c_str(),"pT of Leading Muon; pT (GeV); N Events/2 GeV",50,0,100);
  histContainer_[pt2_4mu]=fs->make<TH1F>(pt2_4mu.c_str(),"pT of 2nd Muon; pT (GeV); N Events/2 GeV",50,0,100);
  histContainer_[pt3_4mu]=fs->make<TH1F>(pt3_4mu.c_str(),"pT of 3rd Muon; pT (GeV); N Events/2 GeV",50,0,100);
  histContainer_[pt4_4mu]=fs->make<TH1F>(pt4_4mu.c_str(),"pT of 4th Muon; pT (GeV); N Events/2 GeV",50,0,100);

  histContainer_[pt1_4e]=fs->make<TH1F>(pt1_4e.c_str(),"pT of Leading Electron; pT (GeV); N Events/2 GeV",50,0,100);
  histContainer_[pt2_4e]=fs->make<TH1F>(pt2_4e.c_str(),"pT of 2nd Electron; pT (GeV); N Events/2 GeV",50,0,100);
  histContainer_[pt3_4e]=fs->make<TH1F>(pt3_4e.c_str(),"pT of 3rd Electron; pT (GeV); N Events/2 GeV",50,0,100);
  histContainer_[pt4_4e]=fs->make<TH1F>(pt4_4e.c_str(),"pT of 4th Electron; pT (GeV); N Events/2 GeV",50,0,100);

  histContainer_[pt1_2e2mu]=fs->make<TH1F>(pt1_2e2mu.c_str(),"pT of Leading Lepton; pT (GeV); N Events/2 GeV",50,0,100);
  histContainer_[pt2_2e2mu]=fs->make<TH1F>(pt2_2e2mu.c_str(),"pT of 2nd Lepton; pT (GeV); N Events/2 GeV",50,0,100);
  histContainer_[pt3_2e2mu]=fs->make<TH1F>(pt3_2e2mu.c_str(),"pT of 3rd Lepton; pT (GeV); N Events/2 GeV",50,0,100);
  histContainer_[pt4_2e2mu]=fs->make<TH1F>(pt4_2e2mu.c_str(),"pT of 4th Lepton; pT (GeV); N Events/2 GeV",50,0,100);

  histContainer_[pt1_4l]=fs->make<TH1F>(pt1_4l.c_str(),"pT of Leading Lepton; pT (GeV); N Events/2 GeV",50,0,100);
  histContainer_[pt2_4l]=fs->make<TH1F>(pt2_4l.c_str(),"pT of 2nd Lepton; pT (GeV); N Events/2 GeV",50,0,100);
  histContainer_[pt3_4l]=fs->make<TH1F>(pt3_4l.c_str(),"pT of 3rd Lepton; pT (GeV); N Events/2 GeV",50,0,100);
  histContainer_[pt4_4l]=fs->make<TH1F>(pt4_4l.c_str(),"pT of 4th Lepton; pT (GeV); N Events/2 GeV",50,0,100);


  histContainer_[mass3s]=fs->make<TH1F>(mass3s.c_str(),"Mass of 3 Softest Leptons in pT;Mass (GeV); N Events/2.0 GeV",85,0,170);
  histContainer_[massall]=fs->make<TH1F>(massall.c_str(),"Invariant Mass;Mass (GeV); N Events/2.0 GeV",85,0,170);


}

void HZZ4LZto4LAna::fillZto4LHistograms(std::map<std::string,TH1F*> &histContainer_, std::vector<pat::Muon> muons, std::vector<pat::Electron> electrons, double evtWeight)
{
  using namespace std;

  double mass13=0, massAll=0;

  if(muons.size() == 4)
    {

      std::vector<math::XYZTLorentzVector> myLeptons;

      myLeptons.push_back(muons[0].p4());
      myLeptons.push_back(muons[1].p4());
      myLeptons.push_back(muons[2].p4());
      myLeptons.push_back(muons[3].p4());

      //Order leptons
      double highestPt = 0;
      int ordered[4] = {100,100,100,100};
      int tmpTaken = 100;

      for( int i = 0; i < 4; i++ )
	{
	  for(int j = 0; j < 4; j++)
	    {
	      if( j != ordered[0] && j != ordered[1] && j != ordered[2] )
		{
		  if( myLeptons[j].Pt() > highestPt ){ highestPt = myLeptons[j].pt(); tmpTaken = j;}
		}
	    }
	  
	  ordered[i] = tmpTaken;
	  highestPt = 0;
	}	  



      mass13 = (muons[1].p4() + muons[2].p4() + muons[3].p4()).M();
      massAll = (muons[1].p4() + muons[2].p4() + muons[3].p4() + muons[0].p4()).M();

      histContainer_[pt1_4mu]->Fill(myLeptons[ordered[0]].Pt(),evtWeight);
      histContainer_[pt2_4mu]->Fill(myLeptons[ordered[1]].Pt(),evtWeight);
      histContainer_[pt3_4mu]->Fill(myLeptons[ordered[2]].Pt(),evtWeight);
      histContainer_[pt4_4mu]->Fill(myLeptons[ordered[3]].Pt(),evtWeight);

      histContainer_[pt1_4l]->Fill(myLeptons[ordered[0]].Pt(),evtWeight);
      histContainer_[pt2_4l]->Fill(myLeptons[ordered[1]].Pt(),evtWeight);
      histContainer_[pt3_4l]->Fill(myLeptons[ordered[2]].Pt(),evtWeight);
      histContainer_[pt4_4l]->Fill(myLeptons[ordered[3]].Pt(),evtWeight);



    }


  if(electrons.size() == 4)
    {


      std::vector<math::XYZTLorentzVector> myLeptons;

      myLeptons.push_back(electrons[0].p4());
      myLeptons.push_back(electrons[1].p4());
      myLeptons.push_back(electrons[2].p4());
      myLeptons.push_back(electrons[3].p4());

      //Order leptons
      double highestPt = 0;
      int ordered[4] = {100,100,100,100};
      int tmpTaken = 100;

      for( int i = 0; i < 4; i++ )
	{
	  for(int j = 0; j < 4; j++)
	    {
	      if( j != ordered[0] && j != ordered[1] && j != ordered[2] )
		{
		  if( myLeptons[j].Pt() > highestPt ){ highestPt = myLeptons[j].pt(); tmpTaken = j;}
		}
	    }
	  
	  ordered[i] = tmpTaken;
	  highestPt = 0;
	}	  



      mass13 = (electrons[1].p4() + electrons[2].p4() + electrons[3].p4()).M();
      massAll = (electrons[1].p4() + electrons[2].p4() + electrons[3].p4() + electrons[0].p4()).M();

      histContainer_[pt1_4e]->Fill(myLeptons[ordered[0]].Pt(),evtWeight);
      histContainer_[pt2_4e]->Fill(myLeptons[ordered[1]].Pt(),evtWeight);
      histContainer_[pt3_4e]->Fill(myLeptons[ordered[2]].Pt(),evtWeight);
      histContainer_[pt4_4e]->Fill(myLeptons[ordered[3]].Pt(),evtWeight);

      histContainer_[pt1_4l]->Fill(myLeptons[ordered[0]].Pt(),evtWeight);
      histContainer_[pt2_4l]->Fill(myLeptons[ordered[1]].Pt(),evtWeight);
      histContainer_[pt3_4l]->Fill(myLeptons[ordered[2]].Pt(),evtWeight);
      histContainer_[pt4_4l]->Fill(myLeptons[ordered[3]].Pt(),evtWeight);
      


    }

  if(electrons.size() == 2 && muons.size() == 2)
    {

      std::vector<math::XYZTLorentzVector> myLeptons;

      myLeptons.push_back(muons[0].p4());
      myLeptons.push_back(muons[1].p4());
      myLeptons.push_back(electrons[0].p4());
      myLeptons.push_back(electrons[1].p4());

      //Order leptons
      double highestPt = 0;
      int ordered[4] = {100,100,100,100};
      int tmpTaken = 100;

      for( int i = 0; i < 4; i++ )
	{
	  for(int j = 0; j < 4; j++)
	    {
	      if( j != ordered[0] && j != ordered[1] && j != ordered[2] )
		{
		  if( myLeptons[j].Pt() > highestPt ){ highestPt = myLeptons[j].pt(); tmpTaken = j;}
		}
	    }
	  
	  ordered[i] = tmpTaken;
	  highestPt = 0;
	}	  

      mass13 = (myLeptons[ordered[1]] + myLeptons[ordered[2]] + myLeptons[ordered[3]]).M();
      massAll = (myLeptons[ordered[1]] + myLeptons[ordered[2]] + myLeptons[ordered[3]] + myLeptons[ordered[0]]).M();

      histContainer_[pt1_2e2mu]->Fill(myLeptons[ordered[0]].Pt(),evtWeight);
      histContainer_[pt2_2e2mu]->Fill(myLeptons[ordered[1]].Pt(),evtWeight);
      histContainer_[pt3_2e2mu]->Fill(myLeptons[ordered[2]].Pt(),evtWeight);
      histContainer_[pt4_2e2mu]->Fill(myLeptons[ordered[3]].Pt(),evtWeight);

      histContainer_[pt1_4l]->Fill(myLeptons[ordered[0]].Pt(),evtWeight);
      histContainer_[pt2_4l]->Fill(myLeptons[ordered[1]].Pt(),evtWeight);
      histContainer_[pt3_4l]->Fill(myLeptons[ordered[2]].Pt(),evtWeight);
      histContainer_[pt4_4l]->Fill(myLeptons[ordered[3]].Pt(),evtWeight);
      
    }



  histContainer_[mass3s]->Fill(mass13,evtWeight);
  histContainer_[massall]->Fill(massAll,evtWeight);

}


void HZZ4LZto4LAna::plotZto4LHistograms(std::map<std::string,TH1F*> &histContainer_ , bool weightEvents, double scaleWeight)
{

  if(weightEvents)
    {

      if(histContainer_[pt1_4mu]->GetEntries() > 0){histContainer_[pt1_4mu]->Scale(scaleWeight);}
      if(histContainer_[pt2_4mu]->GetEntries() > 0){histContainer_[pt2_4mu]->Scale(scaleWeight);}
      if(histContainer_[pt3_4mu]->GetEntries() > 0){histContainer_[pt3_4mu]->Scale(scaleWeight);}
      if(histContainer_[pt4_4mu]->GetEntries() > 0){histContainer_[pt4_4mu]->Scale(scaleWeight);}
      
      if(histContainer_[pt1_4e]->GetEntries() > 0){histContainer_[pt1_4e]->Scale(scaleWeight);}
      if(histContainer_[pt2_4e]->GetEntries() > 0){histContainer_[pt2_4e]->Scale(scaleWeight);}
      if(histContainer_[pt3_4e]->GetEntries() > 0){histContainer_[pt3_4e]->Scale(scaleWeight);}
      if(histContainer_[pt4_4e]->GetEntries() > 0){histContainer_[pt4_4e]->Scale(scaleWeight);}
      
      if(histContainer_[pt1_2e2mu]->GetEntries() > 0){histContainer_[pt1_2e2mu]->Scale(scaleWeight);}
      if(histContainer_[pt2_2e2mu]->GetEntries() > 0){histContainer_[pt2_2e2mu]->Scale(scaleWeight);}
      if(histContainer_[pt3_2e2mu]->GetEntries() > 0){histContainer_[pt3_2e2mu]->Scale(scaleWeight);}
      if(histContainer_[pt4_2e2mu]->GetEntries() > 0){histContainer_[pt4_2e2mu]->Scale(scaleWeight);}
      
      if(histContainer_[pt1_4l]->GetEntries() > 0){histContainer_[pt1_4l]->Scale(scaleWeight);}
      if(histContainer_[pt2_4l]->GetEntries() > 0){histContainer_[pt2_4l]->Scale(scaleWeight);}
      if(histContainer_[pt3_4l]->GetEntries() > 0){histContainer_[pt3_4l]->Scale(scaleWeight);}
      if(histContainer_[pt4_4l]->GetEntries() > 0){histContainer_[pt4_4l]->Scale(scaleWeight);}
      
      if(histContainer_[mass3s]->GetEntries() > 0){histContainer_[mass3s]->Scale(scaleWeight);}
      if(histContainer_[massall]->GetEntries() > 0){histContainer_[massall]->Scale(scaleWeight);}
      
    }

}







#endif
