#ifndef HCCMUONANA_H
#define HCCMUONANA_H

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


class HccMuonAna
{

 public:

  HccMuonAna();
  ~HccMuonAna();


  void bookMuonHistograms(edm::Service<TFileService> fs, std::map<std::string,TH1F*> &histContainer_);
  void plotMuonHistograms(std::map<std::string,TH1F*> &histContainer_, std::vector<pat::Muon> muons);
  std::vector<pat::Muon> testMuons(edm::Handle<edm::View<pat::Muon> > muons, double muPtCut);


};

#endif

#ifndef HCCMUONANA_CC
#define HCCMUONANA_CC


HccMuonAna::HccMuonAna()
{

}


HccMuonAna::~HccMuonAna()
{

}


void HccMuonAna::bookMuonHistograms(edm::Service<TFileService> fs, std::map<std::string,TH1F*> &histContainer_)
{

  using namespace std;

  histContainer_["MuonMatches"]=fs->make<TH1F>("MuonMatches","Muon Matches; N Matches; N Muons",15, 0, 15);
  histContainer_["MuonNormChi2"]=fs->make<TH1F>("MuonNormChi2","Muon Normalized Chi2; chi2/ndof; N Muons",1000, 0, 30);
  histContainer_["MuonValidHits"]=fs->make<TH1F>("MuonValidHits","Muon Valid Hits; Valid Hits; N Muons",75, 0, 75);
  histContainer_["MuonTrackerHits"]=fs->make<TH1F>("MuonTrackerHits","Muon Tracker Hits; Valid Hits; N Muons",50, 0, 50);
  histContainer_["MuonInnerTrackHits"]=fs->make<TH1F>("MuonInnerTrackHits","Muon Inner Track Hits; Valid Hits; N Muons",50, 0, 50);
  histContainer_["MuonGlobalTracker"]=fs->make<TH1F>("MuonGlobalTracker","Muon Global and Tracker; ; N Muons",3, 0, 3);
  histContainer_["MuonGlobalTracker"]->GetXaxis()->SetBinLabel(1,"Global");
  histContainer_["MuonGlobalTracker"]->GetXaxis()->SetBinLabel(2,"Global & Tracker");
 
}


void HccMuonAna::plotMuonHistograms(std::map<std::string,TH1F*> &histContainer_, std::vector<pat::Muon> muons)
{

  using namespace std;

  int tmp = 0;

  for( unsigned int i = 0; i < muons.size(); i++ )
    {
      histContainer_["MuonMatches"]->Fill(muons[i].numberOfMatches());
      histContainer_["MuonNormChi2"]->Fill(muons[i].normChi2());
      histContainer_["MuonValidHits"]->Fill(muons[i].globalTrack()->hitPattern().numberOfValidMuonHits());
      histContainer_["MuonTrackerHits"]->Fill(muons[i].globalTrack()->hitPattern().numberOfValidTrackerHits());
      histContainer_["MuonInnerTrackHits"]->Fill(muons[i].muonBestTrack()->numberOfValidHits()); // miniAOD
     
      if( muons[i].isGlobalMuon() == 1 && muons[i].isTrackerMuon() == 0 ){tmp = 0;}
      if( muons[i].isTrackerMuon() == 1 && muons[i].isGlobalMuon() == 1){tmp = 1;}
      histContainer_["MuonGlobalTracker"]->Fill(tmp);

    }

}

std::vector<pat::Muon> HccMuonAna::testMuons(edm::Handle<edm::View<pat::Muon> > Muons, double muPtCut)
{

  //using namespace edm;
  using namespace pat;
  using namespace std;
  
  vector<pat::Muon> bestMuons;
  
  /********** M U O N  C U T S **********/
  double muEtaCut = 2.4;
  
  for(edm::View<pat::Muon>::const_iterator mu=Muons->begin(); mu != Muons->end(); ++mu)
    {
      if( mu->pt() > muPtCut && abs(mu->eta()) < muEtaCut && mu->isGlobalMuon() == 1 )
	{
	  bestMuons.push_back(*mu);
	}
    }
  
  return bestMuons;
  
}







#endif
