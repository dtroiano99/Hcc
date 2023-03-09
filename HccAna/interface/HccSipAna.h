#ifndef HCCSIPANA_H
#define HCCSIPANA_H

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


class HccSipAna
{

 public:

  HccSipAna();
  ~HccSipAna();

  void bookSipHistograms(edm::Service<TFileService> fs, std::map<std::string,TH1F*> &histContainer_);
  void plotSipHistograms(std::map<std::string,TH1F*> &histContainer_ );
  void advanceSipCounters(double worstSip, double evtWeight);
  
 private:
  
  double sip_Den;

  double sip_05, sip_1, sip_15, sip_2, sip_25, sip_3, sip_35, sip_4, sip_45, sip_5; 
  double sip_55, sip_6, sip_65, sip_7, sip_75, sip_8, sip_85, sip_9, sip_95, sip_10;
  double sip_20, sip_30, sip_40, sip_50;


};


#endif

#ifndef HCCSIPANA_CC
#define HCCSIPANA_CC

HccSipAna::HccSipAna()
{

  sip_05 = 0; sip_1 = 0; sip_15 = 0; sip_2 = 0; sip_25 = 0; sip_3 = 0; sip_35 = 0; sip_4 = 0; sip_45 = 0; sip_5 = 0; 
  sip_55 = 0; sip_6 = 0; sip_65 = 0; sip_7 = 0; sip_75 = 0; sip_8 = 0; sip_85 = 0; sip_9 = 0; sip_95 = 0; sip_10 = 0;
  sip_20 = 0; sip_30 = 0; sip_40 = 0; sip_50 = 0;

  sip_Den = 0;


}

HccSipAna::~HccSipAna()
{


}


void HccSipAna::bookSipHistograms(edm::Service<TFileService> fs, std::map<std::string,TH1F*> &histContainer_)
{

  using namespace std;
  
  histContainer_["SipEff_Num"]=fs->make<TH1F>("SipEff_Num","SipNum",24,0,24);
  histContainer_["SipEff_Den"]=fs->make<TH1F>("SipEff_Den","SipNum",2,0,2);




}

void HccSipAna::plotSipHistograms(std::map<std::string,TH1F*> &histContainer_ )
{

  using namespace std;

  histContainer_["SipEff_Num"]->SetBinContent(1,sip_05);
  histContainer_["SipEff_Num"]->SetBinContent(2,sip_1);
  histContainer_["SipEff_Num"]->SetBinContent(3,sip_15);
  histContainer_["SipEff_Num"]->SetBinContent(4,sip_2);
  histContainer_["SipEff_Num"]->SetBinContent(5,sip_25);
  histContainer_["SipEff_Num"]->SetBinContent(6,sip_3);
  histContainer_["SipEff_Num"]->SetBinContent(7,sip_35);
  histContainer_["SipEff_Num"]->SetBinContent(8,sip_4);
  histContainer_["SipEff_Num"]->SetBinContent(9,sip_45);
  histContainer_["SipEff_Num"]->SetBinContent(10,sip_5);
  histContainer_["SipEff_Num"]->SetBinContent(11,sip_55);
  histContainer_["SipEff_Num"]->SetBinContent(12,sip_6);
  histContainer_["SipEff_Num"]->SetBinContent(13,sip_65);
  histContainer_["SipEff_Num"]->SetBinContent(14,sip_7);
  histContainer_["SipEff_Num"]->SetBinContent(15,sip_75);
  histContainer_["SipEff_Num"]->SetBinContent(16,sip_8);
  histContainer_["SipEff_Num"]->SetBinContent(17,sip_85);
  histContainer_["SipEff_Num"]->SetBinContent(18,sip_9);
  histContainer_["SipEff_Num"]->SetBinContent(19,sip_95);
  histContainer_["SipEff_Num"]->SetBinContent(20,sip_10);
  histContainer_["SipEff_Num"]->SetBinContent(21,sip_20);
  histContainer_["SipEff_Num"]->SetBinContent(22,sip_30);
  histContainer_["SipEff_Num"]->SetBinContent(23,sip_40);
  histContainer_["SipEff_Num"]->SetBinContent(24,sip_50);

  histContainer_["SipEff_Den"]->SetBinContent(1,sip_Den);



}




void HccSipAna::advanceSipCounters(double worstSip,double evtWeight)
{

  using namespace std;

  sip_Den+=evtWeight;

  if( worstSip < 0.5 ){ sip_05+=evtWeight; }
  if( worstSip < 1.0 ){ sip_1+=evtWeight; }
  if( worstSip < 1.5 ){ sip_15+=evtWeight; }
  if( worstSip < 2.0 ){ sip_2+=evtWeight; }
  if( worstSip < 2.5 ){ sip_25+=evtWeight; }
  if( worstSip < 3.0 ){ sip_3+=evtWeight; }
  if( worstSip < 3.5 ){ sip_35+=evtWeight; }
  if( worstSip < 4.0 ){ sip_4+=evtWeight; }
  if( worstSip < 4.5 ){ sip_45+=evtWeight; }
  if( worstSip < 5.0 ){ sip_5+=evtWeight; }
  if( worstSip < 5.5 ){ sip_55+=evtWeight; }
  if( worstSip < 6.0 ){ sip_6+=evtWeight; }
  if( worstSip < 6.5 ){ sip_65+=evtWeight; }
  if( worstSip < 7.0 ){ sip_7+=evtWeight; }
  if( worstSip < 7.5 ){ sip_75+=evtWeight; }
  if( worstSip < 8.0 ){ sip_8+=evtWeight; }
  if( worstSip < 8.5 ){ sip_85+=evtWeight; }
  if( worstSip < 9.0 ){ sip_9+=evtWeight; }
  if( worstSip < 9.5 ){ sip_95+=evtWeight; }
  if( worstSip < 10.0 ){ sip_10+=evtWeight; }
  if( worstSip < 20.0 ){ sip_20+=evtWeight; }
  if( worstSip < 30.0 ){ sip_30+=evtWeight; }
  if( worstSip < 40.0 ){ sip_40+=evtWeight; }
  if( worstSip < 50.0 ){ sip_50+=evtWeight; }


}


#endif
