#ifndef HZZ4LISOEFF_H
#define HZZ4LISOEFF_H

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


class HZZ4LIsoEff
{

 public:

  HZZ4LIsoEff(TString appendName);
  ~HZZ4LIsoEff();


  void bookIsoHistograms(edm::Service<TFileService> fs);
  void plotIsoHistograms( double eventWeight);
  void advanceIsoCounters(double m4l, double iso1, double iso2, bool isSignal, double evtWeight);


 private:

  double nEvAfterSip;
  
  TString name;

  double plotA_005, plotA_0075, plotA_010, plotA_0125, plotA_015, plotA_0175, plotA_020, plotA_0225, plotA_025, plotA_0275, plotA_030;
  double plotA_0325, plotA_035, plotA_0375, plotA_040, plotA_0425,plotA_045,plotA_0475,plotA_050,plotA_0525,plotA_055,plotA_0575,plotA_060;
  double plotA_0625, plotA_065, plotA_0675, plotA_070, plotA_0725, plotA_075, plotA_0775, plotA_080,plotA_0825,plotA_085, plotA_0875, plotA_090;
  double plotA_0925, plotA_095, plotA_0975, plotA_1, plotA_1025, plotA_105, plotA_1075, plotA_11;

  double plotB_005, plotB_0075, plotB_010, plotB_0125, plotB_015, plotB_0175, plotB_020, plotB_0225, plotB_025, plotB_0275, plotB_030;
  double plotB_0325, plotB_035, plotB_0375, plotB_040, plotB_0425, plotB_045, plotB_0475, plotB_050, plotB_0525, plotB_055, plotB_0575, plotB_060;
  double plotB_0625, plotB_065, plotB_0675, plotB_070, plotB_0725, plotB_075, plotB_0775, plotB_080, plotB_0825, plotB_085, plotB_0875, plotB_090;
  double plotB_0925, plotB_095, plotB_0975, plotB_1, plotB_1025, plotB_105, plotB_1075, plotB_11;


  double plota_005, plota_0075, plota_010, plota_0125, plota_015, plota_0175, plota_020, plota_0225, plota_025, plota_0275, plota_030;
  double plota_0325, plota_035, plota_0375, plota_040, plota_0425,plota_045,plota_0475, plota_050,plota_0525,plota_055,plota_0575,plota_060;
  double plota_0625, plota_065, plota_0675, plota_070, plota_0725, plota_075, plota_0775, plota_080,plota_0825,plota_085, plota_0875, plota_090;
  double plota_0925, plota_095, plota_0975, plota_1, plota_1025, plota_105, plota_1075, plota_11;

  double plotb_005, plotb_0075, plotb_010, plotb_0125, plotb_015, plotb_0175, plotb_020, plotb_0225, plotb_025, plotb_0275, plotb_030;
  double plotb_0325, plotb_035, plotb_0375, plotb_040, plotb_0425, plotb_045, plotb_0475, plotb_050, plotb_0525, plotb_055, plotb_0575, plotb_060;
  double plotb_0625, plotb_065, plotb_0675, plotb_070, plotb_0725, plotb_075, plotb_0775, plotb_080, plotb_0825, plotb_085, plotb_0875, plotb_090;
  double plotb_0925, plotb_095, plotb_0975, plotb_1, plotb_1025, plotb_105, plotb_1075, plotb_11;


  double plotN0_005, plotN0_0075, plotN0_010, plotN0_0125, plotN0_015, plotN0_0175, plotN0_020, plotN0_0225, plotN0_025, plotN0_0275, plotN0_030;
  double plotN0_0325, plotN0_035, plotN0_0375, plotN0_040, plotN0_0425, plotN0_045, plotN0_0475, plotN0_050, plotN0_0525, plotN0_055, plotN0_0575, plotN0_060;

  double plotN1_005, plotN1_0075, plotN1_010, plotN1_0125, plotN1_015, plotN1_0175, plotN1_020, plotN1_0225, plotN1_025, plotN1_0275, plotN1_030;
  double plotN1_0325, plotN1_035, plotN1_0375, plotN1_040, plotN1_0425, plotN1_045, plotN1_0475, plotN1_050, plotN1_0525, plotN1_055, plotN1_0575, plotN1_060;

  double plotN2_005, plotN2_0075, plotN2_010, plotN2_0125, plotN2_015, plotN2_0175, plotN2_020, plotN2_0225, plotN2_025, plotN2_0275, plotN2_030;
  double plotN2_0325, plotN2_035, plotN2_0375, plotN2_040, plotN2_0425, plotN2_045, plotN2_0475, plotN2_050, plotN2_0525, plotN2_055, plotN2_0575, plotN2_060;

  TH1F *plotA_Eff, *plotB_Eff, *plotA_EffNum, *plotA_EffDen, *plotB_EffNum, *plotB_EffDen, *plotN0, *plotN1, *plotN2;
  TH1F *plota_EffEv, *plotb_EffEv;

};

#endif

#ifndef HZZ4LISOEFF_CC
#define HZZ4LISOEFF_CC


HZZ4LIsoEff::HZZ4LIsoEff(TString appendName)
{

  name = appendName;

  nEvAfterSip = 0;

  plotA_005 = 0;
  plotA_0075 = 0;
  plotA_010 = 0;
  plotA_0125 = 0;
  plotA_015 = 0;
  plotA_0175 = 0;
  plotA_020 = 0;
  plotA_0225 = 0;
  plotA_025 = 0;
  plotA_0275 = 0;
  plotA_030 = 0;
  plotA_0325 = 0;
  plotA_035 = 0;
  plotA_0375 = 0;
  plotA_040 = 0;
  plotA_0425 = 0;
  plotA_045 = 0;
  plotA_0475 = 0;
  plotA_050 = 0;
  plotA_0525 = 0;
  plotA_055 = 0;
  plotA_0575 = 0;
  plotA_060 = 0;
  plotA_0625 = 0;
  plotA_065 = 0;
  plotA_0675 = 0;
  plotA_070 = 0;
  plotA_0725 = 0;
  plotA_075 = 0;
  plotA_0775 = 0;
  plotA_080 = 0;
  plotA_0825 = 0;
  plotA_085 = 0;
  plotA_0875 = 0;
  plotA_090 = 0;
  plotA_0925 = 0;
  plotA_095 = 0;
  plotA_0975 = 0;
  plotA_1 = 0;
  plotA_1025 = 0;
  plotA_105 = 0;
  plotA_1075 = 0;
  plotA_11 = 0;
 
  plotB_005 = 0;
  plotB_0075 = 0;
  plotB_010 = 0;
  plotB_0125 = 0;
  plotB_015 = 0;
  plotB_0175 = 0;
  plotB_020 = 0;
  plotB_0225 = 0;
  plotB_025 = 0;
  plotB_0275 = 0;
  plotB_030 = 0;
  plotB_0325 = 0;
  plotB_035 = 0;
  plotB_0375 = 0;
  plotB_040 = 0;
  plotB_0425 = 0;
  plotB_045 = 0;
  plotB_0475 = 0;
  plotB_050 = 0;
  plotB_0525 = 0;
  plotB_055 = 0;
  plotB_0575 = 0;
  plotB_060 = 0;
  plotB_0625 = 0;
  plotB_065 = 0;
  plotB_0675 = 0;
  plotB_070 = 0;
  plotB_0725 = 0;
  plotB_075 = 0;
  plotB_0775 = 0;
  plotB_080 = 0;
  plotB_0825 = 0;
  plotB_085 = 0;
  plotB_0875 = 0;
  plotB_090 = 0;
  plotB_0925 = 0;
  plotB_095 = 0;
  plotB_0975 = 0;
  plotB_1 = 0;
  plotB_1025 = 0;
  plotB_105 = 0;
  plotB_1075 = 0;
  plotB_11 = 0;





  plota_005 = 0;
  plota_0075 = 0;
  plota_010 = 0;
  plota_0125 = 0;
  plota_015 = 0;
  plota_0175 = 0;
  plota_020 = 0;
  plota_0225 = 0;
  plota_025 = 0;
  plota_0275 = 0;
  plota_030 = 0;
  plota_0325 = 0;
  plota_035 = 0;
  plota_0375 = 0;
  plota_040 = 0;
  plota_0425 = 0;
  plota_045 = 0;
  plota_0475 = 0;
  plota_050 = 0;
  plota_0525 = 0;
  plota_055 = 0;
  plota_0575 = 0;
  plota_060 = 0;
  plota_0625 = 0;
  plota_065 = 0;
  plota_0675 = 0;
  plota_070 = 0;
  plota_0725 = 0;
  plota_075 = 0;
  plota_0775 = 0;
  plota_080 = 0;
  plota_0825 = 0;
  plota_085 = 0;
  plota_0875 = 0;
  plota_090 = 0;
  plota_0925 = 0;
  plota_095 = 0;
  plota_0975 = 0;
  plota_1 = 0;
  plota_1025 = 0;
  plota_105 = 0;
  plota_1075 = 0;
  plota_11 = 0;
 
  plotb_005 = 0;
  plotb_0075 = 0;
  plotb_010 = 0;
  plotb_0125 = 0;
  plotb_015 = 0;
  plotb_0175 = 0;
  plotb_020 = 0;
  plotb_0225 = 0;
  plotb_025 = 0;
  plotb_0275 = 0;
  plotb_030 = 0;
  plotb_0325 = 0;
  plotb_035 = 0;
  plotb_0375 = 0;
  plotb_040 = 0;
  plotb_0425 = 0;
  plotb_045 = 0;
  plotb_0475 = 0;
  plotb_050 = 0;
  plotb_0525 = 0;
  plotb_055 = 0;
  plotb_0575 = 0;
  plotb_060 = 0;
  plotb_0625 = 0;
  plotb_065 = 0;
  plotb_0675 = 0;
  plotb_070 = 0;
  plotb_0725 = 0;
  plotb_075 = 0;
  plotb_0775 = 0;
  plotb_080 = 0;
  plotb_0825 = 0;
  plotb_085 = 0;
  plotb_0875 = 0;
  plotb_090 = 0;
  plotb_0925 = 0;
  plotb_095 = 0;
  plotb_0975 = 0;
  plotb_1 = 0;
  plotb_1025 = 0;
  plotb_105 = 0;
  plotb_1075 = 0;
  plotb_11 = 0;
 

  plotN0_005 = 0;
  plotN0_0075 = 0;
  plotN0_010 = 0;
  plotN0_0125 = 0;
  plotN0_015 = 0;
  plotN0_0175 = 0;
  plotN0_020 = 0;
  plotN0_0225 = 0;
  plotN0_025 = 0;
  plotN0_0275 = 0;
  plotN0_030 = 0;
  plotN0_0325 = 0;
  plotN0_035 = 0;
  plotN0_0375 = 0;
  plotN0_040 = 0;
  plotN0_0425 = 0;
  plotN0_045 = 0;
  plotN0_0475 = 0;
  plotN0_050 = 0;
  plotN0_0525 = 0;
  plotN0_055 = 0;
  plotN0_0575 = 0;
  plotN0_060 = 0;

  plotN1_005 = 0;
  plotN1_0075 = 0;
  plotN1_010 = 0;
  plotN1_0125 = 0;
  plotN1_015 = 0;
  plotN1_0175 = 0;
  plotN1_020 = 0;
  plotN1_0225 = 0;
  plotN1_025 = 0;
  plotN1_0275 = 0;
  plotN1_030 = 0;
  plotN1_0325 = 0;
  plotN1_035 = 0;
  plotN1_0375 = 0;
  plotN1_040 = 0;
  plotN1_0425 = 0;
  plotN1_045 = 0;
  plotN1_0475 = 0;
  plotN1_050 = 0;
  plotN1_0525 = 0;
  plotN1_055 = 0;
  plotN1_0575 = 0;
  plotN1_060 = 0;


  plotN2_005 = 0;
  plotN2_0075 = 0;
  plotN2_010 = 0;
  plotN2_0125 = 0;
  plotN2_015 = 0;
  plotN2_0175 = 0;
  plotN2_020 = 0;
  plotN2_0225 = 0;
  plotN2_025 = 0;
  plotN2_0275 = 0;
  plotN2_030 = 0;
  plotN2_0325 = 0;
  plotN2_035 = 0;
  plotN2_0375 = 0;
  plotN2_040 = 0;
  plotN2_0425 = 0;
  plotN2_045 = 0;
  plotN2_0475 = 0;
  plotN2_050 = 0;
  plotN2_0525 = 0;
  plotN2_055 = 0;
  plotN2_0575 = 0;
  plotN2_060 = 0;

}


HZZ4LIsoEff::~HZZ4LIsoEff()
{

}


void HZZ4LIsoEff::bookIsoHistograms(edm::Service<TFileService> fs)
{

  using namespace std;

  plotA_Eff=fs->make<TH1F>("plotAND_Eff"+name,"Plot AND Eff",43,0,43);
  plotB_Eff=fs->make<TH1F>("plotSUM_Eff"+name,"Plot SUM Eff",43,0,43);

  plotA_EffNum=fs->make<TH1F>("plotAND_EffNum"+name,"Plot A Eff",43,0,43);
  plotB_EffNum=fs->make<TH1F>("plotSUM_EffNum"+name,"Plot B Eff",43,0,43);

  plotA_EffDen=fs->make<TH1F>("plotAND_EffDen"+name,"Plot A Eff",43,0,43);
  plotB_EffDen=fs->make<TH1F>("plotSUM_EffDen"+name,"Plot B Eff",43,0,43);

  plota_EffEv=fs->make<TH1F>("plotAND_Ev"+name,"Plot A Eff",43,0,43);
  plotb_EffEv=fs->make<TH1F>("plotSUM_Ev"+name,"Plot B Eff",43,0,43);

  plotN0=fs->make<TH1F>("plotN0"+name,"Plot N0",23,0,23);
  plotN1=fs->make<TH1F>("plotN1"+name,"Plot N0",23,0,23);
  plotN2=fs->make<TH1F>("plotN2"+name,"Plot N0",23,0,23);

}


void HZZ4LIsoEff::plotIsoHistograms(double eventWeight)
{

  using namespace std;

  plotA_Eff->SetBinContent(1,(double)plotA_005/nEvAfterSip);
  plotA_Eff->SetBinContent(2,(double)plotA_0075/nEvAfterSip);
  plotA_Eff->SetBinContent(3,(double)plotA_010/nEvAfterSip);
  plotA_Eff->SetBinContent(4,(double)plotA_0125/nEvAfterSip);
  plotA_Eff->SetBinContent(5,(double)plotA_015/nEvAfterSip);
  plotA_Eff->SetBinContent(6,(double)plotA_0175/nEvAfterSip);
  plotA_Eff->SetBinContent(7,(double)plotA_020/nEvAfterSip);
  plotA_Eff->SetBinContent(8,(double)plotA_0225/nEvAfterSip);
  plotA_Eff->SetBinContent(9,(double)plotA_025/nEvAfterSip);
  plotA_Eff->SetBinContent(10,(double)plotA_0275/nEvAfterSip);
  plotA_Eff->SetBinContent(11,(double)plotA_030/nEvAfterSip);
  plotA_Eff->SetBinContent(12,(double)plotA_0325/nEvAfterSip);
  plotA_Eff->SetBinContent(13,(double)plotA_035/nEvAfterSip);
  plotA_Eff->SetBinContent(14,(double)plotA_0375/nEvAfterSip);
  plotA_Eff->SetBinContent(15,(double)plotA_040/nEvAfterSip);
  plotA_Eff->SetBinContent(16,(double)plotA_0425/nEvAfterSip);
  plotA_Eff->SetBinContent(17,(double)plotA_045/nEvAfterSip);
  plotA_Eff->SetBinContent(18,(double)plotA_0475/nEvAfterSip);
  plotA_Eff->SetBinContent(19,(double)plotA_050/nEvAfterSip);
  plotA_Eff->SetBinContent(20,(double)plotA_0525/nEvAfterSip);
  plotA_Eff->SetBinContent(21,(double)plotA_055/nEvAfterSip);
  plotA_Eff->SetBinContent(22,(double)plotA_0575/nEvAfterSip);
  plotA_Eff->SetBinContent(23,(double)plotA_060/nEvAfterSip);
  plotA_Eff->SetBinContent(24,(double)plotA_0625/nEvAfterSip);
  plotA_Eff->SetBinContent(25,(double)plotA_065/nEvAfterSip);
  plotA_Eff->SetBinContent(26,(double)plotA_0675/nEvAfterSip);
  plotA_Eff->SetBinContent(27,(double)plotA_070/nEvAfterSip);
  plotA_Eff->SetBinContent(28,(double)plotA_0725/nEvAfterSip);
  plotA_Eff->SetBinContent(29,(double)plotA_075/nEvAfterSip);
  plotA_Eff->SetBinContent(30,(double)plotA_0775/nEvAfterSip);
  plotA_Eff->SetBinContent(31,(double)plotA_080/nEvAfterSip);
  plotA_Eff->SetBinContent(32,(double)plotA_0825/nEvAfterSip);
  plotA_Eff->SetBinContent(33,(double)plotA_085/nEvAfterSip);
  plotA_Eff->SetBinContent(34,(double)plotA_0875/nEvAfterSip);
  plotA_Eff->SetBinContent(35,(double)plotA_090/nEvAfterSip);
  plotA_Eff->SetBinContent(36,(double)plotA_0925/nEvAfterSip);
  plotA_Eff->SetBinContent(37,(double)plotA_095/nEvAfterSip);
  plotA_Eff->SetBinContent(38,(double)plotA_0975/nEvAfterSip);
  plotA_Eff->SetBinContent(39,(double)plotA_1/nEvAfterSip);
  plotA_Eff->SetBinContent(40,(double)plotA_1025/nEvAfterSip);
  plotA_Eff->SetBinContent(41,(double)plotA_105/nEvAfterSip);
  plotA_Eff->SetBinContent(42,(double)plotA_1075/nEvAfterSip);
  plotA_Eff->SetBinContent(43,(double)plotA_11/nEvAfterSip);


  plotA_EffNum->SetBinContent(1,plotA_005);
  plotA_EffNum->SetBinContent(2,plotA_0075);
  plotA_EffNum->SetBinContent(3,plotA_010);
  plotA_EffNum->SetBinContent(4,plotA_0125);
  plotA_EffNum->SetBinContent(5,plotA_015);
  plotA_EffNum->SetBinContent(6,plotA_0175);
  plotA_EffNum->SetBinContent(7,plotA_020);
  plotA_EffNum->SetBinContent(8,plotA_0225);
  plotA_EffNum->SetBinContent(9,plotA_025);
  plotA_EffNum->SetBinContent(10,plotA_0275);
  plotA_EffNum->SetBinContent(11,plotA_030);
  plotA_EffNum->SetBinContent(12,plotA_0325);
  plotA_EffNum->SetBinContent(13,plotA_035);
  plotA_EffNum->SetBinContent(14,plotA_0375);
  plotA_EffNum->SetBinContent(15,plotA_040);
  plotA_EffNum->SetBinContent(16,plotA_0425);
  plotA_EffNum->SetBinContent(17,plotA_045);
  plotA_EffNum->SetBinContent(18,plotA_0475);
  plotA_EffNum->SetBinContent(19,plotA_050);
  plotA_EffNum->SetBinContent(20,plotA_0525);
  plotA_EffNum->SetBinContent(21,plotA_055);
  plotA_EffNum->SetBinContent(22,plotA_0575);
  plotA_EffNum->SetBinContent(23,plotA_060);
  plotA_EffNum->SetBinContent(24,plotA_0625);
  plotA_EffNum->SetBinContent(25,plotA_065);
  plotA_EffNum->SetBinContent(26,plotA_0675);
  plotA_EffNum->SetBinContent(27,plotA_070);
  plotA_EffNum->SetBinContent(28,plotA_0725);
  plotA_EffNum->SetBinContent(29,plotA_075);
  plotA_EffNum->SetBinContent(30,plotA_0775);
  plotA_EffNum->SetBinContent(31,plotA_080);
  plotA_EffNum->SetBinContent(32,plotA_0825);
  plotA_EffNum->SetBinContent(33,plotA_085);
  plotA_EffNum->SetBinContent(34,plotA_0875);
  plotA_EffNum->SetBinContent(35,plotA_090);
  plotA_EffNum->SetBinContent(36,plotA_0925);
  plotA_EffNum->SetBinContent(37,plotA_095);
  plotA_EffNum->SetBinContent(38,plotA_0975);
  plotA_EffNum->SetBinContent(39,plotA_1);
  plotA_EffNum->SetBinContent(40,plotA_1025);
  plotA_EffNum->SetBinContent(41,plotA_105);
  plotA_EffNum->SetBinContent(42,plotA_1075);
  plotA_EffNum->SetBinContent(43,plotA_11);



  plotA_EffDen->SetBinContent(1,nEvAfterSip);
 
  plotB_Eff->SetBinContent(1,(double)plotB_005/nEvAfterSip);
  plotB_Eff->SetBinContent(2,(double)plotB_0075/nEvAfterSip);
  plotB_Eff->SetBinContent(3,(double)plotB_010/nEvAfterSip);
  plotB_Eff->SetBinContent(4,(double)plotB_0125/nEvAfterSip);
  plotB_Eff->SetBinContent(5,(double)plotB_015/nEvAfterSip);
  plotB_Eff->SetBinContent(6,(double)plotB_0175/nEvAfterSip);
  plotB_Eff->SetBinContent(7,(double)plotB_020/nEvAfterSip);
  plotB_Eff->SetBinContent(8,(double)plotB_0225/nEvAfterSip);
  plotB_Eff->SetBinContent(9,(double)plotB_025/nEvAfterSip);
  plotB_Eff->SetBinContent(10,(double)plotB_0275/nEvAfterSip);
  plotB_Eff->SetBinContent(11,(double)plotB_030/nEvAfterSip);
  plotB_Eff->SetBinContent(12,(double)plotB_0325/nEvAfterSip);
  plotB_Eff->SetBinContent(13,(double)plotB_035/nEvAfterSip);
  plotB_Eff->SetBinContent(14,(double)plotB_0375/nEvAfterSip);
  plotB_Eff->SetBinContent(15,(double)plotB_040/nEvAfterSip);
  plotB_Eff->SetBinContent(16,(double)plotB_0425/nEvAfterSip);
  plotB_Eff->SetBinContent(17,(double)plotB_045/nEvAfterSip);
  plotB_Eff->SetBinContent(18,(double)plotB_0475/nEvAfterSip);
  plotB_Eff->SetBinContent(19,(double)plotB_050/nEvAfterSip);
  plotB_Eff->SetBinContent(20,(double)plotB_0525/nEvAfterSip);
  plotB_Eff->SetBinContent(21,(double)plotB_055/nEvAfterSip);
  plotB_Eff->SetBinContent(22,(double)plotB_0575/nEvAfterSip);
  plotB_Eff->SetBinContent(23,(double)plotB_060/nEvAfterSip);
  plotB_Eff->SetBinContent(24,(double)plotB_0625/nEvAfterSip);
  plotB_Eff->SetBinContent(25,(double)plotB_065/nEvAfterSip);
  plotB_Eff->SetBinContent(26,(double)plotB_0675/nEvAfterSip);
  plotB_Eff->SetBinContent(27,(double)plotB_070/nEvAfterSip);
  plotB_Eff->SetBinContent(28,(double)plotB_0725/nEvAfterSip);
  plotB_Eff->SetBinContent(29,(double)plotB_075/nEvAfterSip);
  plotB_Eff->SetBinContent(30,(double)plotB_0775/nEvAfterSip);
  plotB_Eff->SetBinContent(31,(double)plotB_080/nEvAfterSip);
  plotB_Eff->SetBinContent(32,(double)plotB_0825/nEvAfterSip);
  plotB_Eff->SetBinContent(33,(double)plotB_085/nEvAfterSip);
  plotB_Eff->SetBinContent(34,(double)plotB_0875/nEvAfterSip);
  plotB_Eff->SetBinContent(35,(double)plotB_090/nEvAfterSip);
  plotB_Eff->SetBinContent(36,(double)plotB_0925/nEvAfterSip);
  plotB_Eff->SetBinContent(37,(double)plotB_095/nEvAfterSip);
  plotB_Eff->SetBinContent(38,(double)plotB_0975/nEvAfterSip);
  plotB_Eff->SetBinContent(39,(double)plotB_1/nEvAfterSip);
  plotB_Eff->SetBinContent(40,(double)plotB_1025/nEvAfterSip);
  plotB_Eff->SetBinContent(41,(double)plotB_105/nEvAfterSip);
  plotB_Eff->SetBinContent(42,(double)plotB_1075/nEvAfterSip);
  plotB_Eff->SetBinContent(43,(double)plotB_11/nEvAfterSip);

  plotB_EffNum->SetBinContent(1,plotB_005);
  plotB_EffNum->SetBinContent(2,plotB_0075);
  plotB_EffNum->SetBinContent(3,plotB_010);
  plotB_EffNum->SetBinContent(4,plotB_0125);
  plotB_EffNum->SetBinContent(5,plotB_015);
  plotB_EffNum->SetBinContent(6,plotB_0175);
  plotB_EffNum->SetBinContent(7,plotB_020);
  plotB_EffNum->SetBinContent(8,plotB_0225);
  plotB_EffNum->SetBinContent(9,plotB_025);
  plotB_EffNum->SetBinContent(10,plotB_0275);
  plotB_EffNum->SetBinContent(11,plotB_030);
  plotB_EffNum->SetBinContent(12,plotB_0325);
  plotB_EffNum->SetBinContent(13,plotB_035);
  plotB_EffNum->SetBinContent(14,plotB_0375);
  plotB_EffNum->SetBinContent(15,plotB_040);
  plotB_EffNum->SetBinContent(16,plotB_0425);
  plotB_EffNum->SetBinContent(17,plotB_045);
  plotB_EffNum->SetBinContent(18,plotB_0475);
  plotB_EffNum->SetBinContent(19,plotB_050);
  plotB_EffNum->SetBinContent(20,plotB_0525);
  plotB_EffNum->SetBinContent(21,plotB_055);
  plotB_EffNum->SetBinContent(22,plotB_0575);
  plotB_EffNum->SetBinContent(23,plotB_060);
  plotB_EffNum->SetBinContent(24,plotB_0625);
  plotB_EffNum->SetBinContent(25,plotB_065);
  plotB_EffNum->SetBinContent(26,plotB_0675);
  plotB_EffNum->SetBinContent(27,plotB_070);
  plotB_EffNum->SetBinContent(28,plotB_0725);
  plotB_EffNum->SetBinContent(29,plotB_075);
  plotB_EffNum->SetBinContent(30,plotB_0775);
  plotB_EffNum->SetBinContent(31,plotB_080);
  plotB_EffNum->SetBinContent(32,plotB_0825);
  plotB_EffNum->SetBinContent(33,plotB_085);
  plotB_EffNum->SetBinContent(34,plotB_0875);
  plotB_EffNum->SetBinContent(35,plotB_090);
  plotB_EffNum->SetBinContent(36,plotB_0925);
  plotB_EffNum->SetBinContent(37,plotB_095);
  plotB_EffNum->SetBinContent(38,plotB_0975);
  plotB_EffNum->SetBinContent(39,plotB_1);
  plotB_EffNum->SetBinContent(40,plotB_1025);
  plotB_EffNum->SetBinContent(41,plotB_105);
  plotB_EffNum->SetBinContent(42,plotB_1075);
  plotB_EffNum->SetBinContent(43,plotB_11);

  plotB_EffDen->SetBinContent(1,nEvAfterSip);

  plota_EffEv->SetBinContent(1,plota_005*eventWeight);
  plota_EffEv->SetBinContent(2,plota_0075*eventWeight);
  plota_EffEv->SetBinContent(3,plota_010*eventWeight);
  plota_EffEv->SetBinContent(4,plota_0125*eventWeight);
  plota_EffEv->SetBinContent(5,plota_015*eventWeight);
  plota_EffEv->SetBinContent(6,plota_0175*eventWeight);
  plota_EffEv->SetBinContent(7,plota_020*eventWeight);
  plota_EffEv->SetBinContent(8,plota_0225*eventWeight);
  plota_EffEv->SetBinContent(9,plota_025*eventWeight);
  plota_EffEv->SetBinContent(10,plota_0275*eventWeight);
  plota_EffEv->SetBinContent(11,plota_030*eventWeight);
  plota_EffEv->SetBinContent(12,plota_0325*eventWeight);
  plota_EffEv->SetBinContent(13,plota_035*eventWeight);
  plota_EffEv->SetBinContent(14,plota_0375*eventWeight);
  plota_EffEv->SetBinContent(15,plota_040*eventWeight);
  plota_EffEv->SetBinContent(16,plota_0425*eventWeight);
  plota_EffEv->SetBinContent(17,plota_045*eventWeight);
  plota_EffEv->SetBinContent(18,plota_0475*eventWeight);
  plota_EffEv->SetBinContent(19,plota_050*eventWeight);
  plota_EffEv->SetBinContent(20,plota_0525*eventWeight);
  plota_EffEv->SetBinContent(21,plota_055*eventWeight);
  plota_EffEv->SetBinContent(22,plota_0575*eventWeight);
  plota_EffEv->SetBinContent(23,plota_060*eventWeight);
  plota_EffEv->SetBinContent(24,plota_0625*eventWeight);
  plota_EffEv->SetBinContent(25,plota_065*eventWeight);
  plota_EffEv->SetBinContent(26,plota_0675*eventWeight);
  plota_EffEv->SetBinContent(27,plota_070*eventWeight);
  plota_EffEv->SetBinContent(28,plota_0725*eventWeight);
  plota_EffEv->SetBinContent(29,plota_075*eventWeight);
  plota_EffEv->SetBinContent(30,plota_0775*eventWeight);
  plota_EffEv->SetBinContent(31,plota_080*eventWeight);
  plota_EffEv->SetBinContent(32,plota_0825*eventWeight);
  plota_EffEv->SetBinContent(33,plota_085*eventWeight);
  plota_EffEv->SetBinContent(34,plota_0875*eventWeight);
  plota_EffEv->SetBinContent(35,plota_090*eventWeight);
  plota_EffEv->SetBinContent(36,plota_0925*eventWeight);
  plota_EffEv->SetBinContent(37,plota_095*eventWeight);
  plota_EffEv->SetBinContent(38,plota_0975*eventWeight);
  plota_EffEv->SetBinContent(39,plota_1*eventWeight);
  plota_EffEv->SetBinContent(40,plota_1025*eventWeight);
  plota_EffEv->SetBinContent(41,plota_105*eventWeight);
  plota_EffEv->SetBinContent(42,plota_1075*eventWeight);
  plota_EffEv->SetBinContent(43,plota_11*eventWeight);

  plotb_EffEv->SetBinContent(1,plotb_005*eventWeight);
  plotb_EffEv->SetBinContent(2,plotb_0075*eventWeight);
  plotb_EffEv->SetBinContent(3,plotb_010*eventWeight);
  plotb_EffEv->SetBinContent(4,plotb_0125*eventWeight);
  plotb_EffEv->SetBinContent(5,plotb_015*eventWeight);
  plotb_EffEv->SetBinContent(6,plotb_0175*eventWeight);
  plotb_EffEv->SetBinContent(7,plotb_020*eventWeight);
  plotb_EffEv->SetBinContent(8,plotb_0225*eventWeight);
  plotb_EffEv->SetBinContent(9,plotb_025*eventWeight);
  plotb_EffEv->SetBinContent(10,plotb_0275*eventWeight);
  plotb_EffEv->SetBinContent(11,plotb_030*eventWeight);
  plotb_EffEv->SetBinContent(12,plotb_0325*eventWeight);
  plotb_EffEv->SetBinContent(13,plotb_035*eventWeight);
  plotb_EffEv->SetBinContent(14,plotb_0375*eventWeight);
  plotb_EffEv->SetBinContent(15,plotb_040*eventWeight);
  plotb_EffEv->SetBinContent(16,plotb_0425*eventWeight);
  plotb_EffEv->SetBinContent(17,plotb_045*eventWeight);
  plotb_EffEv->SetBinContent(18,plotb_0475*eventWeight);
  plotb_EffEv->SetBinContent(19,plotb_050*eventWeight);
  plotb_EffEv->SetBinContent(20,plotb_0525*eventWeight);
  plotb_EffEv->SetBinContent(21,plotb_055*eventWeight);
  plotb_EffEv->SetBinContent(22,plotb_0575*eventWeight);
  plotb_EffEv->SetBinContent(23,plotb_060*eventWeight);
  plotb_EffEv->SetBinContent(24,plotb_0625*eventWeight);
  plotb_EffEv->SetBinContent(25,plotb_065*eventWeight);
  plotb_EffEv->SetBinContent(26,plotb_0675*eventWeight);
  plotb_EffEv->SetBinContent(27,plotb_070*eventWeight);
  plotb_EffEv->SetBinContent(28,plotb_0725*eventWeight);
  plotb_EffEv->SetBinContent(29,plotb_075*eventWeight);
  plotb_EffEv->SetBinContent(30,plotb_0775*eventWeight);
  plotb_EffEv->SetBinContent(31,plotb_080*eventWeight);
  plotb_EffEv->SetBinContent(32,plotb_0825*eventWeight);
  plotb_EffEv->SetBinContent(33,plotb_085*eventWeight);
  plotb_EffEv->SetBinContent(34,plotb_0875*eventWeight);
  plotb_EffEv->SetBinContent(35,plotb_090*eventWeight);
  plotb_EffEv->SetBinContent(36,plotb_0925*eventWeight);
  plotb_EffEv->SetBinContent(37,plotb_095*eventWeight);
  plotb_EffEv->SetBinContent(38,plotb_0975*eventWeight);
  plotb_EffEv->SetBinContent(39,plotb_1*eventWeight);
  plotb_EffEv->SetBinContent(40,plotb_1025*eventWeight);
  plotb_EffEv->SetBinContent(41,plotb_105*eventWeight);
  plotb_EffEv->SetBinContent(42,plotb_1075*eventWeight);
  plotb_EffEv->SetBinContent(43,plotb_11*eventWeight);


  plotN0->SetBinContent(1,plotN0_005*eventWeight);
  plotN0->SetBinContent(2,plotN0_0075*eventWeight);
  plotN0->SetBinContent(3,plotN0_010*eventWeight);
  plotN0->SetBinContent(4,plotN0_0125*eventWeight);
  plotN0->SetBinContent(5,plotN0_015*eventWeight);
  plotN0->SetBinContent(6,plotN0_0175*eventWeight);
  plotN0->SetBinContent(7,plotN0_020*eventWeight);
  plotN0->SetBinContent(8,plotN0_0225*eventWeight);
  plotN0->SetBinContent(9,plotN0_025*eventWeight);
  plotN0->SetBinContent(10,plotN0_0275*eventWeight);
  plotN0->SetBinContent(11,plotN0_030*eventWeight);
  plotN0->SetBinContent(12,plotN0_0325*eventWeight);
  plotN0->SetBinContent(13,plotN0_035*eventWeight);
  plotN0->SetBinContent(14,plotN0_0375*eventWeight);
  plotN0->SetBinContent(15,plotN0_040*eventWeight);
  plotN0->SetBinContent(16,plotN0_0425*eventWeight);
  plotN0->SetBinContent(17,plotN0_045*eventWeight);
  plotN0->SetBinContent(18,plotN0_0475*eventWeight);
  plotN0->SetBinContent(19,plotN0_050*eventWeight);
  plotN0->SetBinContent(20,plotN0_0525*eventWeight);
  plotN0->SetBinContent(21,plotN0_055*eventWeight);
  plotN0->SetBinContent(22,plotN0_0575*eventWeight);
  plotN0->SetBinContent(23,plotN0_060*eventWeight);


  plotN1->SetBinContent(1,plotN1_005*eventWeight);
  plotN1->SetBinContent(2,plotN1_0075*eventWeight);
  plotN1->SetBinContent(3,plotN1_010*eventWeight);
  plotN1->SetBinContent(4,plotN1_0125*eventWeight);
  plotN1->SetBinContent(5,plotN1_015*eventWeight);
  plotN1->SetBinContent(6,plotN1_0175*eventWeight);
  plotN1->SetBinContent(7,plotN1_020*eventWeight);
  plotN1->SetBinContent(8,plotN1_0225*eventWeight);
  plotN1->SetBinContent(9,plotN1_025*eventWeight);
  plotN1->SetBinContent(10,plotN1_0275*eventWeight);
  plotN1->SetBinContent(11,plotN1_030*eventWeight);
  plotN1->SetBinContent(12,plotN1_0325*eventWeight);
  plotN1->SetBinContent(13,plotN1_035*eventWeight);
  plotN1->SetBinContent(14,plotN1_0375*eventWeight);
  plotN1->SetBinContent(15,plotN1_040*eventWeight);
  plotN1->SetBinContent(16,plotN1_0425*eventWeight);
  plotN1->SetBinContent(17,plotN1_045*eventWeight);
  plotN1->SetBinContent(18,plotN1_0475*eventWeight);
  plotN1->SetBinContent(19,plotN1_050*eventWeight);
  plotN1->SetBinContent(20,plotN1_0525*eventWeight);
  plotN1->SetBinContent(21,plotN1_055*eventWeight);
  plotN1->SetBinContent(22,plotN1_0575*eventWeight);
  plotN1->SetBinContent(23,plotN1_060*eventWeight);


  plotN2->SetBinContent(1,plotN2_005*eventWeight);
  plotN2->SetBinContent(2,plotN2_0075*eventWeight);
  plotN2->SetBinContent(3,plotN2_010*eventWeight);
  plotN2->SetBinContent(4,plotN2_0125*eventWeight);
  plotN2->SetBinContent(5,plotN2_015*eventWeight);
  plotN2->SetBinContent(6,plotN2_0175*eventWeight);
  plotN2->SetBinContent(7,plotN2_020*eventWeight);
  plotN2->SetBinContent(8,plotN2_0225*eventWeight);
  plotN2->SetBinContent(9,plotN2_025*eventWeight);
  plotN2->SetBinContent(10,plotN2_0275*eventWeight);
  plotN2->SetBinContent(11,plotN2_030*eventWeight);
  plotN2->SetBinContent(12,plotN2_0325*eventWeight);
  plotN2->SetBinContent(13,plotN2_035*eventWeight);
  plotN2->SetBinContent(14,plotN2_0375*eventWeight);
  plotN2->SetBinContent(15,plotN2_040*eventWeight);
  plotN2->SetBinContent(16,plotN2_0425*eventWeight);
  plotN2->SetBinContent(17,plotN2_045*eventWeight);
  plotN2->SetBinContent(18,plotN2_0475*eventWeight);
  plotN2->SetBinContent(19,plotN2_050*eventWeight);
  plotN2->SetBinContent(20,plotN2_0525*eventWeight);
  plotN2->SetBinContent(21,plotN2_055*eventWeight);
  plotN2->SetBinContent(22,plotN2_0575*eventWeight);
  
  plotN2->SetBinContent(23,plotN2_060*eventWeight);
  

}




void HZZ4LIsoEff::advanceIsoCounters(double m4l, double iso1, double iso2, bool isSignal,double evtWeight)
{

  using namespace std;

  if( !isSignal )
    {
      if( m4l > 100 && m4l < 200 )
	{
	  nEvAfterSip+=evtWeight;
	  
	  if( iso1 < 0.05  && iso2 < 0.05  ){ plotA_005+=evtWeight; plotN2_005+=evtWeight; }
	  if( iso1 < 0.075 && iso2 < 0.075 ){ plotA_0075+=evtWeight; plotN2_0075+=evtWeight; }
	  if( iso1 < 0.1   && iso2 < 0.1   ){ plotA_010+=evtWeight; plotN2_010+=evtWeight;}
	  if( iso1 < 0.125 && iso2 < 0.125  ){ plotA_0125+=evtWeight; plotN2_0125+=evtWeight;}
	  if( iso1 < 0.15 && iso2 < 0.15  ){ plotA_015+=evtWeight; plotN2_015+=evtWeight;}
	  if( iso1 < 0.175 && iso2 < 0.175  ){ plotA_0175+=evtWeight; plotN2_0175+=evtWeight; }
	  if( iso1 < 0.2 && iso2 < 0.2  ){ plotA_020+=evtWeight; plotN2_020+=evtWeight;}
	  if( iso1 < 0.225 && iso2 < 0.225  ){ plotA_0225+=evtWeight; plotN2_0225+=evtWeight;}
	  if( iso1 < 0.25 && iso2 < 0.25  ){ plotA_025+=evtWeight; plotN2_025+=evtWeight;}
	  if( iso1 < 0.275 && iso2 < 0.275  ){ plotA_0275+=evtWeight; plotN2_0275+=evtWeight;}
	  if( iso1 < 0.3 && iso2 < 0.3  ){ plotA_030+=evtWeight; plotN2_030+=evtWeight;}
	  if( iso1 < 0.325 && iso2 < 0.325  ){ plotA_0325+=evtWeight; plotN2_0325+=evtWeight;}
	  if( iso1 < 0.35 && iso2 < 0.35  ){ plotA_035+=evtWeight; plotN2_035+=evtWeight;}
	  if( iso1 < 0.375 && iso2 < 0.375  ){ plotA_0375+=evtWeight; plotN2_0375+=evtWeight;}
	  if( iso1 < 0.4 && iso2 < 0.4  ){ plotA_040+=evtWeight; plotN2_040+=evtWeight;}
          if( iso1 < 0.425 && iso2 < 0.425  ){ plotA_0425+=evtWeight; plotN2_0425+=evtWeight;}
          if( iso1 < 0.45 && iso2 < 0.45  ){ plotA_045+=evtWeight; plotN2_045+=evtWeight;}
          if( iso1 < 0.475 && iso2 < 0.475  ){ plotA_0475+=evtWeight; plotN2_0475+=evtWeight;}
          if( iso1 < 0.50 && iso2 < 0.50  ){ plotA_050+=evtWeight; plotN2_050+=evtWeight;}
          if( iso1 < 0.525 && iso2 < 0.525  ){ plotA_0525+=evtWeight; plotN2_0525+=evtWeight;}
          if( iso1 < 0.55 && iso2 < 0.55  ){ plotA_055+=evtWeight; plotN2_055+=evtWeight;}
          if( iso1 < 0.575 && iso2 < 0.575  ){ plotA_0575+=evtWeight; plotN2_0575+=evtWeight;}
          if( iso1 < 0.6 && iso2 < 0.6  ){ plotA_060+=evtWeight; plotN2_060+=evtWeight;}
          if( iso1 < 0.625 && iso2 < 0.625  ){ plotA_0625+=evtWeight; }
          if( iso1 < 0.65 && iso2 < 0.65  ){ plotA_065+=evtWeight; }
          if( iso1 < 0.675 && iso2 < 0.675  ){ plotA_0675+=evtWeight; }
          if( iso1 < 0.7 && iso2 < 0.7  ){ plotA_070+=evtWeight; }
          if( iso1 < 0.725 && iso2 < 0.725  ){ plotA_0725+=evtWeight; }
          if( iso1 < 0.75 && iso2 < 0.75  ){ plotA_075+=evtWeight; }
          if( iso1 < 0.775 && iso2 < 0.775  ){ plotA_0775+=evtWeight; }
          if( iso1 < 0.80 && iso2 < 0.80  ){ plotA_080+=evtWeight; }
          if( iso1 < 0.825 && iso2 < 0.825  ){ plotA_0825+=evtWeight; }
          if( iso1 < 0.85 && iso2 < 0.85  ){ plotA_085+=evtWeight; }
          if( iso1 < 0.875 && iso2 < 0.875  ){ plotA_0875+=evtWeight; }
          if( iso1 < 0.9 && iso2 < 0.9  ){ plotA_090+=evtWeight; }
          if( iso1 < 0.925 && iso2 < 0.925  ){ plotA_0925+=evtWeight; }
          if( iso1 < 0.95 && iso2 < 0.95  ){ plotA_095+=evtWeight; }
          if( iso1 < 0.975 && iso2 < 0.975  ){ plotA_0975+=evtWeight; }
          if( iso1 < 1.0 && iso2 < 1.0  ){ plotA_1+=evtWeight; }
          if( iso1 < 1.025 && iso2 < 1.025  ){ plotA_1025+=evtWeight; }
          if( iso1 < 1.05 && iso2 < 1.05  ){ plotA_105+=evtWeight; }
          if( iso1 < 1.075 && iso2 < 1.075  ){ plotA_1075+=evtWeight; }
          if( iso1 < 1.1 && iso2 < 1.1 ){ plotA_11+=evtWeight; }


	  
	  if( iso1 > 0.05  && iso2 < 0.05  ){ plotN1_005+=evtWeight; }
	  if( iso1 > 0.075 && iso2 < 0.075 ){ plotN1_0075+=evtWeight; }
	  if( iso1 > 0.1   && iso2 < 0.1   ){ plotN1_010+=evtWeight;}
	  if( iso1 > 0.125 && iso2 < 0.125  ){ plotN1_0125+=evtWeight;}
	  if( iso1 > 0.15 && iso2 < 0.15  ){plotN1_015+=evtWeight;}
	  if( iso1 > 0.175 && iso2 < 0.175  ){ plotN1_0175+=evtWeight; }
	  if( iso1 > 0.2 && iso2 < 0.2  ){plotN1_020+=evtWeight;}
	  if( iso1 > 0.225 && iso2 < 0.225  ){ plotN1_0225+=evtWeight;}
	  if( iso1 > 0.25 && iso2 < 0.25  ){ plotN1_025+=evtWeight;}
	  if( iso1 > 0.275 && iso2 < 0.275  ){ plotN1_0275+=evtWeight;}
	  if( iso1 > 0.3 && iso2 < 0.3  ){ plotN1_030+=evtWeight;}
	  if( iso1 > 0.325 && iso2 < 0.325  ){ plotN1_0325+=evtWeight;}
	  if( iso1 > 0.35 && iso2 < 0.35  ){ plotN1_035+=evtWeight;}
	  if( iso1 > 0.375 && iso2 < 0.375  ){ plotN1_0375+=evtWeight;}
	  if( iso1 > 0.4 && iso2 < 0.4  ){ plotN1_040+=evtWeight;}
          if( iso1 > 0.425 && iso2 < 0.425  ){ plotN1_0425+=evtWeight;}
          if( iso1 > 0.45 && iso2 < 0.45  ){ plotN1_045+=evtWeight;}
          if( iso1 > 0.475 && iso2 < 0.475  ){ plotN1_0475+=evtWeight;}
          if( iso1 > 0.5 && iso2 < 0.5  ){ plotN1_050+=evtWeight;}
          if( iso1 > 0.525 && iso2 < 0.525  ){ plotN1_0525+=evtWeight;}
          if( iso1 > 0.55 && iso2 < 0.55  ){ plotN1_055+=evtWeight;}
          if( iso1 > 0.575 && iso2 < 0.575  ){ plotN1_0575+=evtWeight;}
          if( iso1 > 0.6 && iso2 < 0.6  ){ plotN1_060+=evtWeight;}

	  if( iso1 > 0.05  && iso2 > 0.05  ){ plotN0_005+=evtWeight; }
	  if( iso1 > 0.075 && iso2 > 0.075 ){ plotN0_0075+=evtWeight; }
	  if( iso1 > 0.1   && iso2 > 0.1   ){ plotN0_010+=evtWeight;}
	  if( iso1 > 0.125 && iso2 > 0.125  ){ plotN0_0125+=evtWeight;}
	  if( iso1 > 0.15 && iso2 > 0.15  ){plotN0_015+=evtWeight;}
	  if( iso1 > 0.175 && iso2 > 0.175  ){ plotN0_0175+=evtWeight; }
	  if( iso1 > 0.2 && iso2 > 0.2  ){plotN0_020+=evtWeight;}
	  if( iso1 > 0.225 && iso2 > 0.225  ){ plotN0_0225+=evtWeight;}
	  if( iso1 > 0.25 && iso2 > 0.25  ){ plotN0_025+=evtWeight;}
	  if( iso1 > 0.275 && iso2 > 0.275  ){ plotN0_0275+=evtWeight;}
	  if( iso1 > 0.3 && iso2 > 0.3  ){ plotN0_030+=evtWeight;}
	  if( iso1 > 0.325 && iso2 > 0.325  ){ plotN0_0325+=evtWeight;}
	  if( iso1 > 0.35 && iso2 > 0.35  ){ plotN0_035+=evtWeight;}
	  if( iso1 > 0.375 && iso2 > 0.375  ){ plotN0_0375+=evtWeight;}
	  if( iso1 > 0.4 && iso2 > 0.4  ){ plotN0_040+=evtWeight;}
          if( iso1 > 0.425 && iso2 > 0.425  ){ plotN0_0425+=evtWeight;}
          if( iso1 > 0.45 && iso2 > 0.45  ){ plotN0_045+=evtWeight;}
          if( iso1 > 0.475 && iso2 > 0.475  ){ plotN0_0475+=evtWeight;}
          if( iso1 > 0.5 && iso2 > 0.5  ){ plotN0_050+=evtWeight;}
          if( iso1 > 0.525 && iso2 > 0.525  ){ plotN0_0525+=evtWeight;}
          if( iso1 > 0.55 && iso2 > 0.55  ){ plotN0_055+=evtWeight;}
          if( iso1 > 0.575 && iso2 > 0.575  ){ plotN0_0575+=evtWeight;}
          if( iso1 > 0.6 && iso2 > 0.6  ){ plotN0_060+=evtWeight;}
        	  
	  if( iso1 + iso2 < 0.05  ){ plotB_005+=evtWeight; }
	  if( iso1 + iso2 < 0.075 ){ plotB_0075+=evtWeight; }
	  if( iso1 + iso2 < 0.1   ){ plotB_010+=evtWeight; }
	  if( iso1 + iso2 < 0.125  ){ plotB_0125+=evtWeight; }
	  if( iso1 + iso2 < 0.15  ){ plotB_015+=evtWeight; }
	  if( iso1 + iso2 < 0.175  ){ plotB_0175+=evtWeight; }
	  if( iso1 + iso2 < 0.2  ){ plotB_020+=evtWeight; }
	  if( iso1 + iso2 < 0.225  ){ plotB_0225+=evtWeight; }
	  if( iso1 + iso2 < 0.25  ){ plotB_025+=evtWeight; }
	  if( iso1 + iso2 < 0.275  ){ plotB_0275+=evtWeight; }
	  if( iso1 + iso2 < 0.3  ){ plotB_030+=evtWeight; }
	  if( iso1 + iso2 < 0.325  ){ plotB_0325+=evtWeight; }
	  if( iso1 + iso2 < 0.35  ){ plotB_035+=evtWeight; }
	  if( iso1 + iso2 < 0.375  ){ plotB_0375+=evtWeight; }
	  if( iso1 + iso2 < 0.4  ){ plotB_040+=evtWeight; }
	  if( iso1 + iso2 < 0.425  ){ plotB_0425+=evtWeight; }
          if( iso1 + iso2 < 0.45  ){ plotB_045+=evtWeight; }
          if( iso1 + iso2 < 0.475  ){ plotB_0475+=evtWeight; }
          if( iso1 + iso2 < 0.5  ){ plotB_050+=evtWeight; }
          if( iso1 + iso2 < 0.525  ){ plotB_0525+=evtWeight; }
          if( iso1 + iso2 < 0.55  ){ plotB_055+=evtWeight; }
          if( iso1 + iso2 < 0.575  ){ plotB_0575+=evtWeight; }
          if( iso1 + iso2 < 0.6  ){ plotB_060+=evtWeight; }
	  if( iso1 + iso2 < 0.625  ){ plotB_0625+=evtWeight; }
          if( iso1 + iso2 < 0.65  ){ plotB_065+=evtWeight; }
          if( iso1 + iso2 < 0.675  ){ plotB_0675+=evtWeight; }
          if( iso1 + iso2 < 0.7  ){ plotB_070+=evtWeight; }
          if( iso1 + iso2 < 0.725  ){ plotB_0725+=evtWeight; }
          if( iso1 + iso2 < 0.75  ){ plotB_075+=evtWeight; }
          if( iso1 + iso2 < 0.775  ){ plotB_0775+=evtWeight; }
          if( iso1 + iso2 < 0.8  ){ plotB_080+=evtWeight; }
          if( iso1 + iso2 < 0.825  ){ plotB_0825+=evtWeight; }
          if( iso1 + iso2 < 0.85  ){ plotB_085+=evtWeight; }
          if( iso1 + iso2 < 0.875  ){ plotB_0875+=evtWeight; }
          if( iso1 + iso2 < 0.9  ){ plotB_090+=evtWeight; }
	  if( iso1 + iso2 < 0.925  ){ plotB_0925+=evtWeight; }
          if( iso1 + iso2 < 0.95  ){ plotB_095+=evtWeight; }
          if( iso1 + iso2 < 0.975  ){ plotB_0975+=evtWeight; }
          if( iso1 + iso2 < 1.0  ){ plotB_1+=evtWeight; }
          if( iso1 + iso2 < 1.025  ){ plotB_1025+=evtWeight; }
          if( iso1 + iso2 < 1.05  ){ plotB_105+=evtWeight; }
          if( iso1 + iso2 < 1.075  ){ plotB_1075+=evtWeight; }
          if( iso1 + iso2 < 1.1  ){ plotB_11+=evtWeight; }
         

	}
    }
  else
    {
      nEvAfterSip+=evtWeight;
      
      if( iso1 < 0.05  && iso2 < 0.05  ){ plotA_005+=evtWeight; plotN2_005+=evtWeight; }
      if( iso1 < 0.075 && iso2 < 0.075 ){ plotA_0075+=evtWeight; plotN2_0075+=evtWeight; }
      if( iso1 < 0.1   && iso2 < 0.1   ){ plotA_010+=evtWeight; plotN2_010+=evtWeight;}
      if( iso1 < 0.125 && iso2 < 0.125  ){ plotA_0125+=evtWeight; plotN2_0125+=evtWeight;}
      if( iso1 < 0.15 && iso2 < 0.15  ){ plotA_015+=evtWeight; plotN2_015+=evtWeight;}
      if( iso1 < 0.175 && iso2 < 0.175  ){ plotA_0175+=evtWeight; plotN2_0175+=evtWeight; }
      if( iso1 < 0.2 && iso2 < 0.2  ){ plotA_020+=evtWeight; plotN2_020+=evtWeight;}
      if( iso1 < 0.225 && iso2 < 0.225  ){ plotA_0225+=evtWeight; plotN2_0225+=evtWeight;}
      if( iso1 < 0.25 && iso2 < 0.25  ){ plotA_025+=evtWeight; plotN2_025+=evtWeight;}
      if( iso1 < 0.275 && iso2 < 0.275  ){ plotA_0275+=evtWeight; plotN2_0275+=evtWeight;}
      if( iso1 < 0.3 && iso2 < 0.3  ){ plotA_030+=evtWeight; plotN2_030+=evtWeight;}
      if( iso1 < 0.325 && iso2 < 0.325  ){ plotA_0325+=evtWeight; plotN2_0325+=evtWeight;}
      if( iso1 < 0.35 && iso2 < 0.35  ){ plotA_035+=evtWeight; plotN2_035+=evtWeight;}
      if( iso1 < 0.375 && iso2 < 0.375  ){ plotA_0375+=evtWeight; plotN2_0375+=evtWeight;}
      if( iso1 < 0.4 && iso2 < 0.4  ){ plotA_040+=evtWeight; plotN2_040+=evtWeight;}
      if( iso1 < 0.425 && iso2 < 0.425  ){ plotA_0425+=evtWeight; plotN2_0425+=evtWeight;}
      if( iso1 < 0.45 && iso2 < 0.45  ){ plotA_045+=evtWeight; plotN2_045+=evtWeight;}
      if( iso1 < 0.475 && iso2 < 0.475  ){ plotA_0475+=evtWeight; plotN2_0475+=evtWeight;}
      if( iso1 < 0.50 && iso2 < 0.50  ){ plotA_050+=evtWeight; plotN2_050+=evtWeight;}
      if( iso1 < 0.525 && iso2 < 0.525  ){ plotA_0525+=evtWeight; plotN2_0525+=evtWeight;}
      if( iso1 < 0.55 && iso2 < 0.55  ){ plotA_055+=evtWeight; plotN2_055+=evtWeight;}
      if( iso1 < 0.575 && iso2 < 0.575  ){ plotA_0575+=evtWeight; plotN2_0575+=evtWeight;}
      if( iso1 < 0.6 && iso2 < 0.6  ){ plotA_060+=evtWeight; plotN2_060+=evtWeight;}
      if( iso1 < 0.625 && iso2 < 0.625  ){ plotA_0625+=evtWeight; }
      if( iso1 < 0.65 && iso2 < 0.65  ){ plotA_065+=evtWeight; }
      if( iso1 < 0.675 && iso2 < 0.675  ){ plotA_0675+=evtWeight; }
      if( iso1 < 0.7 && iso2 < 0.7  ){ plotA_070+=evtWeight; }
      if( iso1 < 0.725 && iso2 < 0.725  ){ plotA_0725+=evtWeight; }
      if( iso1 < 0.75 && iso2 < 0.75  ){ plotA_075+=evtWeight; }
      if( iso1 < 0.775 && iso2 < 0.775  ){ plotA_0775+=evtWeight; }
      if( iso1 < 0.80 && iso2 < 0.80  ){ plotA_080+=evtWeight; }
      if( iso1 < 0.825 && iso2 < 0.825  ){ plotA_0825+=evtWeight; }
      if( iso1 < 0.85 && iso2 < 0.85  ){ plotA_085+=evtWeight; }
      if( iso1 < 0.875 && iso2 < 0.875  ){ plotA_0875+=evtWeight; }
      if( iso1 < 0.9 && iso2 < 0.9  ){ plotA_090+=evtWeight; }
      if( iso1 < 0.925 && iso2 < 0.925  ){ plotA_0925+=evtWeight; }
      if( iso1 < 0.95 && iso2 < 0.95  ){ plotA_095+=evtWeight; }
      if( iso1 < 0.975 && iso2 < 0.975  ){ plotA_0975+=evtWeight; }
      if( iso1 < 1.0 && iso2 < 1.0  ){ plotA_1+=evtWeight; }
      if( iso1 < 1.025 && iso2 < 1.025  ){ plotA_1025+=evtWeight; }
      if( iso1 < 1.05 && iso2 < 1.05  ){ plotA_105+=evtWeight; }
      if( iso1 < 1.075 && iso2 < 1.075  ){ plotA_1075+=evtWeight; }
      if( iso1 < 1.1 && iso2 < 1.1 ){ plotA_11+=evtWeight; }

      
      if( iso1 > 0.05  && iso2 < 0.05  ){ plotN1_005+=evtWeight; }
      if( iso1 > 0.075 && iso2 < 0.075 ){ plotN1_0075+=evtWeight; }
      if( iso1 > 0.1   && iso2 < 0.1   ){ plotN1_010+=evtWeight;}
      if( iso1 > 0.125 && iso2 < 0.125  ){ plotN1_0125+=evtWeight;}
      if( iso1 > 0.15 && iso2 < 0.15  ){plotN1_015+=evtWeight;}
      if( iso1 > 0.175 && iso2 < 0.175  ){ plotN1_0175+=evtWeight; }
      if( iso1 > 0.2 && iso2 < 0.2  ){plotN1_020+=evtWeight;}
      if( iso1 > 0.225 && iso2 < 0.225  ){ plotN1_0225+=evtWeight;}
      if( iso1 > 0.25 && iso2 < 0.25  ){ plotN1_025+=evtWeight;}
      if( iso1 > 0.275 && iso2 < 0.275  ){ plotN1_0275+=evtWeight;}
      if( iso1 > 0.3 && iso2 < 0.3  ){ plotN1_030+=evtWeight;}
      if( iso1 > 0.325 && iso2 < 0.325  ){ plotN1_0325+=evtWeight;}
      if( iso1 > 0.35 && iso2 < 0.35  ){ plotN1_035+=evtWeight;}
      if( iso1 > 0.375 && iso2 < 0.375  ){ plotN1_0375+=evtWeight;}
      if( iso1 > 0.4 && iso2 < 0.4  ){ plotN1_040+=evtWeight;}
      if( iso1 > 0.425 && iso2 < 0.425  ){ plotN1_0425+=evtWeight;}
      if( iso1 > 0.45 && iso2 < 0.45  ){ plotN1_045+=evtWeight;}
      if( iso1 > 0.475 && iso2 < 0.475  ){ plotN1_0475+=evtWeight;}
      if( iso1 > 0.5 && iso2 < 0.5  ){ plotN1_050+=evtWeight;}
      if( iso1 > 0.525 && iso2 < 0.525  ){ plotN1_0525+=evtWeight;}
      if( iso1 > 0.55 && iso2 < 0.55  ){ plotN1_055+=evtWeight;}
      if( iso1 > 0.575 && iso2 < 0.575  ){ plotN1_0575+=evtWeight;}
      if( iso1 > 0.6 && iso2 < 0.6  ){ plotN1_060+=evtWeight;}
      
      if( iso1 > 0.05  && iso2 > 0.05  ){ plotN0_005+=evtWeight; }
      if( iso1 > 0.075 && iso2 > 0.075 ){ plotN0_0075+=evtWeight; }
      if( iso1 > 0.1   && iso2 > 0.1   ){ plotN0_010+=evtWeight;}
      if( iso1 > 0.125 && iso2 > 0.125  ){ plotN0_0125+=evtWeight;}
      if( iso1 > 0.15 && iso2 > 0.15  ){plotN0_015+=evtWeight;}
      if( iso1 > 0.175 && iso2 > 0.175  ){ plotN0_0175+=evtWeight; }
      if( iso1 > 0.2 && iso2 > 0.2  ){plotN0_020+=evtWeight;}
      if( iso1 > 0.225 && iso2 > 0.225  ){ plotN0_0225+=evtWeight;}
      if( iso1 > 0.25 && iso2 > 0.25  ){ plotN0_025+=evtWeight;}
      if( iso1 > 0.275 && iso2 > 0.275  ){ plotN0_0275+=evtWeight;}
      if( iso1 > 0.3 && iso2 > 0.3  ){ plotN0_030+=evtWeight;}
      if( iso1 > 0.325 && iso2 > 0.325  ){ plotN0_0325+=evtWeight;}
      if( iso1 > 0.35 && iso2 > 0.35  ){ plotN0_035+=evtWeight;}
      if( iso1 > 0.375 && iso2 > 0.375  ){ plotN0_0375+=evtWeight;}
      if( iso1 > 0.4 && iso2 > 0.4  ){ plotN0_040+=evtWeight;}
      if( iso1 > 0.425 && iso2 > 0.425  ){ plotN0_0425+=evtWeight;}
      if( iso1 > 0.45 && iso2 > 0.45  ){ plotN0_045+=evtWeight;}
      if( iso1 > 0.475 && iso2 > 0.475  ){ plotN0_0475+=evtWeight;}
      if( iso1 > 0.5 && iso2 > 0.5  ){ plotN0_050+=evtWeight;}
      if( iso1 > 0.525 && iso2 > 0.525  ){ plotN0_0525+=evtWeight;}
      if( iso1 > 0.55 && iso2 > 0.55  ){ plotN0_055+=evtWeight;}
      if( iso1 > 0.575 && iso2 > 0.575  ){ plotN0_0575+=evtWeight;}
      if( iso1 > 0.6 && iso2 > 0.6  ){ plotN0_060+=evtWeight;}
      
      if( iso1 + iso2 < 0.05  ){ plotB_005+=evtWeight; }
      if( iso1 + iso2 < 0.075 ){ plotB_0075+=evtWeight; }
      if( iso1 + iso2 < 0.1   ){ plotB_010+=evtWeight; }
      if( iso1 + iso2 < 0.125  ){ plotB_0125+=evtWeight; }
      if( iso1 + iso2 < 0.15  ){ plotB_015+=evtWeight; }
      if( iso1 + iso2 < 0.175  ){ plotB_0175+=evtWeight; }
      if( iso1 + iso2 < 0.2  ){ plotB_020+=evtWeight; }
      if( iso1 + iso2 < 0.225  ){ plotB_0225+=evtWeight; }
      if( iso1 + iso2 < 0.25  ){ plotB_025+=evtWeight; }
      if( iso1 + iso2 < 0.275  ){ plotB_0275+=evtWeight; }
      if( iso1 + iso2 < 0.3  ){ plotB_030+=evtWeight; }
      if( iso1 + iso2 < 0.325  ){ plotB_0325+=evtWeight; }
      if( iso1 + iso2 < 0.35  ){ plotB_035+=evtWeight; }
      if( iso1 + iso2 < 0.375  ){ plotB_0375+=evtWeight; }
      if( iso1 + iso2 < 0.4  ){ plotB_040+=evtWeight; }
      if( iso1 + iso2 < 0.425  ){ plotB_0425+=evtWeight; }
      if( iso1 + iso2 < 0.45  ){ plotB_045+=evtWeight; }
      if( iso1 + iso2 < 0.475  ){ plotB_0475+=evtWeight; }
      if( iso1 + iso2 < 0.5  ){ plotB_050+=evtWeight; }
      if( iso1 + iso2 < 0.525  ){ plotB_0525+=evtWeight; }
      if( iso1 + iso2 < 0.55  ){ plotB_055+=evtWeight; }
      if( iso1 + iso2 < 0.575  ){ plotB_0575+=evtWeight; }
      if( iso1 + iso2 < 0.6  ){ plotB_060+=evtWeight; }
      if( iso1 + iso2 < 0.65  ){ plotB_065+=evtWeight; }
      if( iso1 + iso2 < 0.675  ){ plotB_0675+=evtWeight; }
      if( iso1 + iso2 < 0.7  ){ plotB_070+=evtWeight; }
      if( iso1 + iso2 < 0.725  ){ plotB_0725+=evtWeight; }
      if( iso1 + iso2 < 0.75  ){ plotB_075+=evtWeight; }
      if( iso1 + iso2 < 0.775  ){ plotB_0775+=evtWeight; }
      if( iso1 + iso2 < 0.8  ){ plotB_080+=evtWeight; }
      if( iso1 + iso2 < 0.825  ){ plotB_0825+=evtWeight; }
      if( iso1 + iso2 < 0.85  ){ plotB_085+=evtWeight; }
      if( iso1 + iso2 < 0.875  ){ plotB_0875+=evtWeight; }
      if( iso1 + iso2 < 0.9  ){ plotB_090+=evtWeight; }
      if( iso1 + iso2 < 0.925  ){ plotB_0925+=evtWeight; }
      if( iso1 + iso2 < 0.95  ){ plotB_095+=evtWeight; }
      if( iso1 + iso2 < 0.975  ){ plotB_0975+=evtWeight; }
      if( iso1 + iso2 < 1.0  ){ plotB_1+=evtWeight; }
      if( iso1 + iso2 < 1.025  ){ plotB_1025+=evtWeight; }
      if( iso1 + iso2 < 1.05  ){ plotB_105+=evtWeight; }
      if( iso1 + iso2 < 1.075  ){ plotB_1075+=evtWeight; }
      if( iso1 + iso2 < 1.1  ){ plotB_11+=evtWeight; }

      
    }


  if( m4l >= 110 && m4l <= 160 )
    {
      
      if( iso1 < 0.05  && iso2 < 0.05  ){ plota_005+=evtWeight;   }
      if( iso1 < 0.075 && iso2 < 0.075 ){ plota_0075+=evtWeight;  }
      if( iso1 < 0.1   && iso2 < 0.1   ){ plota_010+=evtWeight;   }
      if( iso1 < 0.125 && iso2 < 0.125  ){ plota_0125+=evtWeight; }
      if( iso1 < 0.15 && iso2 < 0.15  ){ plota_015+=evtWeight;    }
      if( iso1 < 0.175 && iso2 < 0.175  ){ plota_0175+=evtWeight; }
      if( iso1 < 0.2 && iso2 < 0.2  ){ plota_020+=evtWeight;      }
      if( iso1 < 0.225 && iso2 < 0.225  ){ plota_0225+=evtWeight; }
      if( iso1 < 0.25 && iso2 < 0.25  ){ plota_025+=evtWeight;    }
      if( iso1 < 0.275 && iso2 < 0.275  ){ plota_0275+=evtWeight; }
      if( iso1 < 0.3 && iso2 < 0.3  ){ plota_030+=evtWeight;      }
      if( iso1 < 0.325 && iso2 < 0.325  ){ plota_0325+=evtWeight; }
      if( iso1 < 0.35 && iso2 < 0.35  ){ plota_035+=evtWeight;    }
      if( iso1 < 0.375 && iso2 < 0.375  ){ plota_0375+=evtWeight; }
      if( iso1 < 0.4 && iso2 < 0.4  ){ plota_040+=evtWeight;      }
      if( iso1 < 0.425 && iso2 < 0.425  ){ plota_0425+=evtWeight; }
      if( iso1 < 0.45 && iso2 < 0.45  ){ plota_045+=evtWeight;    }
      if( iso1 < 0.475 && iso2 < 0.475  ){ plota_0475+=evtWeight; }
      if( iso1 < 0.50 && iso2 < 0.50  ){ plota_050+=evtWeight;    }
      if( iso1 < 0.525 && iso2 < 0.525  ){ plota_0525+=evtWeight; }
      if( iso1 < 0.55 && iso2 < 0.55  ){ plota_055+=evtWeight;    }
      if( iso1 < 0.575 && iso2 < 0.575  ){ plota_0575+=evtWeight; }
      if( iso1 < 0.6 && iso2 < 0.6  ){ plota_060+=evtWeight;      }
      if( iso1 < 0.625 && iso2 < 0.625  ){ plota_0625+=evtWeight; }
      if( iso1 < 0.65 && iso2 < 0.65  ){ plota_065+=evtWeight;    }
      if( iso1 < 0.675 && iso2 < 0.675  ){ plota_0675+=evtWeight; }
      if( iso1 < 0.7 && iso2 < 0.7  ){ plota_070+=evtWeight;      }
      if( iso1 < 0.725 && iso2 < 0.725  ){ plota_0725+=evtWeight; }
      if( iso1 < 0.75 && iso2 < 0.75  ){ plota_075+=evtWeight;    }
      if( iso1 < 0.775 && iso2 < 0.775  ){ plota_0775+=evtWeight; }
      if( iso1 < 0.80 && iso2 < 0.80  ){ plota_080+=evtWeight;    }
      if( iso1 < 0.825 && iso2 < 0.825  ){ plota_0825+=evtWeight; }
      if( iso1 < 0.85 && iso2 < 0.85  ){ plota_085+=evtWeight;    }
      if( iso1 < 0.875 && iso2 < 0.875  ){ plota_0875+=evtWeight; }
      if( iso1 < 0.9 && iso2 < 0.9  ){ plota_090+=evtWeight;      }
      if( iso1 < 0.925 && iso2 < 0.925  ){ plota_0925+=evtWeight; }
      if( iso1 < 0.95 && iso2 < 0.95  ){ plota_095+=evtWeight;    }
      if( iso1 < 0.975 && iso2 < 0.975  ){ plota_0975+=evtWeight; }
      if( iso1 < 1.0 && iso2 < 1.0  ){ plota_1+=evtWeight;        }
      if( iso1 < 1.025 && iso2 < 1.025  ){ plota_1025+=evtWeight; }
      if( iso1 < 1.05 && iso2 < 1.05  ){ plota_105+=evtWeight;    }
      if( iso1 < 1.075 && iso2 < 1.075  ){ plota_1075+=evtWeight; }
      if( iso1 < 1.1 && iso2 < 1.1 ){ plota_11+=evtWeight;        }
      
      
      if( iso1 + iso2 < 0.05  ){ plotb_005+=evtWeight; }
      if( iso1 + iso2 < 0.075 ){ plotb_0075+=evtWeight; }
      if( iso1 + iso2 < 0.1   ){ plotb_010+=evtWeight; }
      if( iso1 + iso2 < 0.125  ){ plotb_0125+=evtWeight; }
      if( iso1 + iso2 < 0.15  ){ plotb_015+=evtWeight; }
      if( iso1 + iso2 < 0.175  ){ plotb_0175+=evtWeight; }
      if( iso1 + iso2 < 0.2  ){ plotb_020+=evtWeight; }
      if( iso1 + iso2 < 0.225  ){ plotb_0225+=evtWeight; }
      if( iso1 + iso2 < 0.25  ){ plotb_025+=evtWeight; }
      if( iso1 + iso2 < 0.275  ){ plotb_0275+=evtWeight; }
      if( iso1 + iso2 < 0.3  ){ plotb_030+=evtWeight; }
      if( iso1 + iso2 < 0.325  ){ plotb_0325+=evtWeight; }
      if( iso1 + iso2 < 0.35  ){ plotb_035+=evtWeight; }
      if( iso1 + iso2 < 0.375  ){ plotb_0375+=evtWeight; }
      if( iso1 + iso2 < 0.4  ){ plotb_040+=evtWeight; }
      if( iso1 + iso2 < 0.425  ){ plotb_0425+=evtWeight; }
      if( iso1 + iso2 < 0.45  ){ plotb_045+=evtWeight; }
      if( iso1 + iso2 < 0.475  ){ plotb_0475+=evtWeight; }
      if( iso1 + iso2 < 0.5  ){ plotb_050+=evtWeight; }
      if( iso1 + iso2 < 0.525  ){ plotb_0525+=evtWeight; }
      if( iso1 + iso2 < 0.55  ){ plotb_055+=evtWeight; }
      if( iso1 + iso2 < 0.575  ){ plotb_0575+=evtWeight; }
      if( iso1 + iso2 < 0.6  ){ plotb_060+=evtWeight; }
      if( iso1 + iso2 < 0.65  ){ plotb_065+=evtWeight; }
      if( iso1 + iso2 < 0.675  ){ plotb_0675+=evtWeight; }
      if( iso1 + iso2 < 0.7  ){ plotb_070+=evtWeight; }
      if( iso1 + iso2 < 0.725  ){ plotb_0725+=evtWeight; }
      if( iso1 + iso2 < 0.75  ){ plotb_075+=evtWeight; }
      if( iso1 + iso2 < 0.775  ){ plotb_0775+=evtWeight; }
      if( iso1 + iso2 < 0.8  ){ plotb_080+=evtWeight; }
      if( iso1 + iso2 < 0.825  ){ plotb_0825+=evtWeight; }
      if( iso1 + iso2 < 0.85  ){ plotb_085+=evtWeight; }
      if( iso1 + iso2 < 0.875  ){ plotb_0875+=evtWeight; }
      if( iso1 + iso2 < 0.9  ){ plotb_090+=evtWeight; }
      if( iso1 + iso2 < 0.925  ){ plotb_0925+=evtWeight; }
      if( iso1 + iso2 < 0.95  ){ plotb_095+=evtWeight; }
      if( iso1 + iso2 < 0.975  ){ plotb_0975+=evtWeight; }
      if( iso1 + iso2 < 1.0  ){ plotb_1+=evtWeight; }
      if( iso1 + iso2 < 1.025  ){ plotb_1025+=evtWeight; }
      if( iso1 + iso2 < 1.05  ){ plotb_105+=evtWeight; }
      if( iso1 + iso2 < 1.075  ){ plotb_1075+=evtWeight; }
      if( iso1 + iso2 < 1.1  ){ plotb_11+=evtWeight; }
    }
    
}










#endif
