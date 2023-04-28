#ifndef HZZ4LRESOLUTION_H
#define HZZ4LRESOLUTION_H

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

using namespace std;

class HZZ4LResolution
{

	public:

	HZZ4LResolution();
	void SetAppendName(TString appendName);
	~HZZ4LResolution();

	void bookHistograms(edm::Service<TFileService> fs, std::map<TString,TH1F*> &histContainer_, std::map<TString, TH2F*> &hist2DContainer_);
	void fillHistograms(std::map<TString,TH1F*> &histContainer_, std::map<TString, TH2F*> &hist2DContainer_, std::vector< pat::Electron> & electrons, std::vector< pat::Muon>& muons, vector< pat::PFParticle>& fsrPhotons, double evtWeight, bool isData);	
        void plotHistograms(std::map<TString,TH1F*> &histContainer_, bool weightEvents, double scaleWeight);
	double genHiggsMass(const pat::Electron*elec);
	double genHiggsMass(const pat::Muon*elec);

	void setdebug(int d){debug_ = d;};

	private:

	TString  appName;
	TString  FourMuMassVsErr, FourElMassVsErr, FourMuMassPull, FourElMassPull, FourMuMassPull3, FourElMassPull3;
	TString  TwoMuElMassVsErr, TwoMuElMassPull, TwoMuElMassPull3;
	HZZ4LMassErr massErr;

	int debug_;

};


#endif

#ifndef HZZ4LRESOLUTION_CC
#define HZZ4LRESOLUTION_CC

HZZ4LResolution::HZZ4LResolution()
{ 

	appName = "";
	FourMuMassVsErr = "FourMuMassVsErr";
	FourElMassVsErr = "FourElMassVsErr";
	FourMuMassPull = "FourMuMassPull";
	FourElMassPull = "FourElMassPull";
	FourMuMassPull3 = "FourMuMassPull3";
	FourElMassPull3 = "FourElMassPull3";
	TwoMuElMassVsErr = "TwoMuElMassVsErr";
	TwoMuElMassPull = "TwoMuElMassPull";
	TwoMuElMassPull3 = "TwoMuElMassPull3";

	debug_=0;
}

void HZZ4LResolution::SetAppendName(TString appendName)
{

	appName = appendName;
	FourMuMassVsErr = FourMuMassVsErr + appName;
	FourElMassVsErr = FourElMassVsErr + appName;
	FourMuMassPull = FourMuMassPull + appName;
	FourElMassPull = FourElMassPull + appName;
	FourMuMassPull3 = FourMuMassPull3 + appName;
	FourElMassPull3 = FourElMassPull3 + appName;
	TwoMuElMassVsErr = TwoMuElMassVsErr + appName;
	TwoMuElMassPull = TwoMuElMassPull + appName;
	TwoMuElMassPull3 = TwoMuElMassPull3 + appName;
}


HZZ4LResolution::~HZZ4LResolution()
{

}
void HZZ4LResolution::bookHistograms(edm::Service<TFileService> fs, std::map<TString,TH1F*> &histContainer_, std::map<TString, TH2F*> &hist2DContainer_) 
{
	hist2DContainer_["hmass_relerr_vs_recm_4mu"]=fs->make<TH2F>("hmass_relerr_vs_recm_4mu","four lepton mass reltive error vs. reco mass; m_{4#mu}^{RECO}; #sigma_{m_{4#mu}}^{RECO}/m_{4#mu}^{RECO}", 500, 100, 600, 500, 0, 0.2);
	hist2DContainer_["hmass_relerr_vs_genm_4mu"]=fs->make<TH2F>("hmass_relerr_vs_genm_4mu","four lepton mass reltive error vs. gen mass; m_{4#mu}^{GEN}; #sigma_{m_{4#mu}}^{RECO}/m_{4#mu}^{GEN}", 500, 100, 600, 500, 0, 0.2);
	hist2DContainer_["hmass_relerr_vs_recm_4e"]=fs->make<TH2F>("hmass_relerr_vs_recm_4e","four lepton mass reltive error vs. reco mass; m_{4e}^{RECO}; #sigma_{m_{4e}}^{RECO}/m_{4e}^{RECO}", 500, 100, 600, 500, 0, 0.2);
	hist2DContainer_["hmass_relerr_vs_genm_4e"]=fs->make<TH2F>("hmass_relerr_vs_genm_4e","four lepton mass reltive error vs. gen mass; m_{4e}^{GEN}; #sigma_{m_{4e}}^{RECO}/m_{4e}^{GEN}", 500, 100, 600, 500, 0, 0.2);
	hist2DContainer_["hmass_relerr_vs_recm_2e2mu"]=fs->make<TH2F>("hmass_relerr_vs_recm_2e2mu","four lepton mass reltive error vs. reco mass; m_{2e2#mu}^{RECO}; #sigma_{m_{2e2#mu}}^{RECO}/m_{2e2mu}^{RECO}", 500, 100, 600, 500, 0, 0.2);
	hist2DContainer_["hmass_relerr_vs_genm_2e2mu"]=fs->make<TH2F>("hmass_relerr_vs_genm_2e2mu","four lepton mass reltive error vs. gen mass; m_{2e2#mu}^{GEN}; #sigma_{m_{2e2#mu}}^{RECO}/m_{2e2#mu}^{GEN}", 500, 100, 600, 500, 0, 0.2);

///////////

	hist2DContainer_["newhmass_relerr_vs_recm_4mu"]=fs->make<TH2F>("newhmass_relerr_vs_recm_4mu","new four lepton mass reltive error vs. reco mass; m_{4#mu}^{RECO}; new #sigma_{m_{4#mu}}^{RECO}/m_{4#mu}^{RECO}", 500, 100, 600, 500, 0, 0.2);
	hist2DContainer_["newhmass_relerr_vs_genm_4mu"]=fs->make<TH2F>("newhmass_relerr_vs_genm_4mu","new four lepton mass reltive error vs. gen mass; m_{4#mu}^{GEN}; new #sigma_{m_{4#mu}}^{RECO}/m_{4#mu}^{GEN}", 500, 100, 600, 500, 0, 0.2);
	hist2DContainer_["newhmass_relerr_vs_recm_4e"]=fs->make<TH2F>("newhmass_relerr_vs_recm_4e","new four lepton mass reltive error vs. reco mass; m_{4e}^{RECO}; new #sigma_{m_{4e}}^{RECO}/m_{4e}^{RECO}", 500, 100, 600, 500, 0, 0.2);
	hist2DContainer_["newhmass_relerr_vs_genm_4e"]=fs->make<TH2F>("newhmass_relerr_vs_genm_4e","new four lepton mass reltive error vs. gen mass; m_{4e}^{GEN}; new #sigma_{m_{4e}}^{RECO}/m_{4e}^{GEN}", 500, 100, 600, 500, 0, 0.2);
	hist2DContainer_["newhmass_relerr_vs_recm_2e2mu"]=fs->make<TH2F>("newhmass_relerr_vs_recm_2e2mu","new four lepton mass reltive error vs. reco mass; m_{2e2#mu}^{RECO}; new #sigma_{m_{2e2#mu}}^{RECO}/m_{2e2mu}^{RECO}", 500, 100, 600, 500, 0, 0.2);
	hist2DContainer_["newhmass_relerr_vs_genm_2e2mu"]=fs->make<TH2F>("newhmass_relerr_vs_genm_2e2mu","new four lepton mass reltive error vs. gen mass; m_{2e2#mu}^{GEN}; new #sigma_{m_{2e2#mu}}^{RECO}/m_{2e2#mu}^{GEN}", 500, 100, 600, 500, 0, 0.2);

/////////////////////////////////////////////////
	histContainer_["hmass_pulls_4mu"]=fs->make<TH1F>("hmass_pulls_4mu","four lepton mass pulls (w.r.t Higgs); (m_{4#mu}^{RECO} - m_{Higgs})/#sigma_{m_{4#mu}}^{RECO}; N Events", 1000, -10, 10);
	histContainer_["hmass_pulls_4mugen"]=fs->make<TH1F>("hmass_pulls_4mugen","four lepton mass pulls (w.r.t 4 gen #mu); (m_{4#mu}^{RECO} - m_{4#mu}^{GEN})/#sigma_{m_{4#mu}}^{RECO}; N Events", 1000, -10, 10);
	//histContainer_["hmass_pulls_4mugen3"]=fs->make<TH1F>("hmass_pulls_4mugen3","four lepton mass pulls (w.r.t 4 gen3 #mu); (m_{4#mu}^{RECO} - m_{4#mu}^{GEN3})/#sigma_{m_{4#mu}}^{RECO}; N Events", 1000, -10, 10);

	histContainer_["hmass_res_4mu"]=fs->make<TH1F>("hmass_res_4mu","four lepton mass res (w.r.t Higgs); (m_{4#mu}^{RECO} - m_{Higgs})/m_{Higgs}; N Events", 1000, -0.5, 0.5);
	histContainer_["hmass_res_4mugen"]=fs->make<TH1F>("hmass_res_4mugen","four lepton mass res (w.r.t 4 gen #mu); (m_{4#mu}^{RECO} - m_{4#mu}^{GEN})/m_{4#mu}^{GEN}}; N Events", 1000, -0.5, 0.5);
	//histContainer_["hmass_res_4mugen3"]=fs->make<TH1F>("hmass_res_4mugen3","four lepton mass res (w.r.t 4 gen3 #mu); (m_{4#mu}^{RECO} - m_{4#mu}^{GEN3})/m_{4#mu}^{GEN3}; N Events", 4000, -1.5, 1.5);


	histContainer_["hmass_pulls_4e"]=fs->make<TH1F>("hmass_pulls_4e","four lepton mass pulls (w.r.t Higgs); (m_{4e}^{RECO} - m_{Higgs})/#sigma_{m_{4e}}^{RECO}; N Events", 1000, -10, 10);
	histContainer_["hmass_pulls_4egen"]=fs->make<TH1F>("hmass_pulls_4egen","four lepton mass pulls (w.r.t 4 gen e); (m_{4e}^{RECO} - m_{4e}^{GEN})/#sigma_{m_{4e}}^{RECO}; N Events", 1000, -10, 10);
	histContainer_["hmass_pulls_4egen3"]=fs->make<TH1F>("hmass_pulls_4egen3","four lepton mass pulls (w.r.t 4 gen3 e); (m_{4e}^{RECO} - m_{4e}^{GEN3})/#sigma_{m_{4e}}^{RECO}; N Events", 1000, -10, 10);

	histContainer_["hmass_res_4e"]=fs->make<TH1F>("hmass_res_4e","four lepton mass res (w.r.t Higgs); (m_{4e}^{RECO} - m_{Higgs})/m_{Higgs}; N Events", 1000, -0.5, 0.5);
	histContainer_["hmass_res_4egen"]=fs->make<TH1F>("hmass_res_4egen","four lepton mass res (w.r.t 4 gen e); (m_{4e}^{RECO} - m_{4e}^{GEN})/m_{4e}^{GEN}; N Events", 1000, -0.5, 0.5);
	histContainer_["hmass_res_4egen3"]=fs->make<TH1F>("hmass_res_4egen3","four lepton mass res (w.r.t 4 gen3 e); (m_{4e}^{RECO} - m_{4e}^{GEN3})/m_{4e}^{GEN}; N Events", 1000, -0.5, 0.5);

	histContainer_["hmass_pulls_2e2mu"]=fs->make<TH1F>("hmass_pulls_2e2mu","four lepton mass pulls (w.r.t Higgs); (m_{2e2#mu}^{RECO} - m_{Higgs})/#sigma_{m_{2e2#mu}}^{RECO}; N Events", 1000, -10, 10);
	histContainer_["hmass_pulls_2e2mugen"]=fs->make<TH1F>("hmass_pulls_2e2mugen","four lepton mass pulls (w.r.t gen 2e2#mu); (m_{2e2#mu}^{RECO} - m_{2e2#mu}^{GEN})/#sigma_{m_{2e2#mu}}^{RECO}; N Events", 1000, -10, 10);
	histContainer_["hmass_pulls_2e2mugen3"]=fs->make<TH1F>("hmass_pulls_2e2mugen3","four lepton mass pulls (w.r.t gen3 2e2#mu); (m_{2e2#mu}^{RECO} - m_{2e2#mu}^{GEN3})/#sigma_{m_{2e2#mu}}^{RECO}; N Events", 1000, -10, 10);

	histContainer_["hmass_res_2e2mu"]=fs->make<TH1F>("hmass_res_2e2mu","four lepton mass pulls (w.r.t Higgs); (m_{2e2#mu}^{RECO} - m_{Higgs})/m_{Higgs}}; N Events", 1000, -0.5, 0.5);
	histContainer_["hmass_res_2e2mugen"]=fs->make<TH1F>("hmass_res_2e2mugen","four lepton mass res (w.r.t gen 2e2#mu); (m_{2e2#mu}^{RECO} - m_{2e2#mu}^{GEN})/m_{2e2#mu}^{GEN}; N Events", 1000, -0.5, 0.5);
	histContainer_["hmass_res_2e2mugen3"]=fs->make<TH1F>("hmass_res_2e2mugen3","four lepton mass res (w.r.t gen3 2e2#mu); (m_{2e2#mu}^{RECO} - m_{2e2#mu}^{GEN3})/m_{2e2#mu}^{GEN}; N Events", 1000, -0.5, 0.5);

	histContainer_["hmass_pulls_4e_allBNS"]=fs->make<TH1F>("hmass_pulls_4e_allBNS","four lepton mass pulls (w.r.t Higgs), all barrel and non-showering; (m_{4e}^{RECO} - m_{Higgs})/#sigma_{m_{4e}}^{RECO}; N Events", 1000, -10, 10);
	histContainer_["hmass_pulls_4egen_allBNS"]=fs->make<TH1F>("hmass_pulls_4egen_allBNS","four lepton mass pulls (w.r.t 4egen), all barrel and non-showering; (m_{4e}^{RECO} - m_{4e}^{GEN})/#sigma_{m_{4e}}^{RECO}; N Events", 1000, -10, 10);
	histContainer_["hmass_pulls_4egen3_allBNS"]=fs->make<TH1F>("hmass_pulls_4egen3_allBNS","four lepton mass pulls (w.r.t 4egen3), all barrel and non-showering; (m_{4e}^{RECO} - m_{4e}^{GEN3})/#sigma_{m_{4e}}^{RECO}; N Events", 1000, -10, 10);

	histContainer_["hmass_pulls_4e_bad"]=fs->make<TH1F>("hmass_pulls_4e_bad","four lepton mass pulls (w.r.t Higgs), bad; (m_{4e}^{RECO} - m_{Higgs})/#sigma_{m_{4e}}^{RECO}; N Events", 1000, -10, 10);
	histContainer_["hmass_pulls_4egen_bad"]=fs->make<TH1F>("hmass_pulls_4egen_bad","four lepton mass pulls (w.r.t 4 gen e), bad; (m_{4e}^{RECO} - m_{4e}^{GEN})/#sigma_{m_{4e}}^{RECO}; N Events", 1000, -10, 10);
	histContainer_["hmass_pulls_4egen3_bad"]=fs->make<TH1F>("hmass_pulls_4egen3_bad","four lepton mass pulls (w.r.t 4 gen3 e), bad; (m_{4e}^{RECO} - m_{4e}^{GEN3})/#sigma_{m_{4e}}^{RECO}; N Events", 1000, -10, 10);

	histContainer_["hmass_pulls_4e_medium"]=fs->make<TH1F>("hmass_pulls_4e_medium","four lepton mass pulls (w.r.t Higgs), medium; (m_{4e}^{RECO} - m_{Higgs})/#sigma_{m_{4e}}^{RECO}; N Events", 1000, -10, 10);
	histContainer_["hmass_pulls_4egen_medium"]=fs->make<TH1F>("hmass_pulls_4egen_medium","four lepton mass pulls (w.r.t 4 gen e), medium; (m_{4e}^{RECO} - m_{4e}^{GEN})/#sigma_{m_{4e}}^{RECO}; N Events", 1000, -10, 10);
	histContainer_["hmass_pulls_4egen3_medium"]=fs->make<TH1F>("hmass_pulls_4egen3_medium","four lepton mass pulls (w.r.t 4 gen3 e), medium; (m_{4e}^{RECO} - m_{4e}^{GEN3})/#sigma_{m_{4e}}^{RECO}; N Events", 1000, -10, 10);

	histContainer_["hmass_pulls_4e_good"]=fs->make<TH1F>("hmass_pulls_4e_good","four lepton mass pulls (w.r.t Higgs), good; (m_{4e}^{RECO} - m_{Higgs})/#sigma_{m_{4e}}^{RECO}; N Events", 1000, -10, 10);
	histContainer_["hmass_pulls_4egen_good"]=fs->make<TH1F>("hmass_pulls_4egen_good","four lepton mass pulls (w.r.t 4 gen e), good; (m_{4e}^{RECO} - m_{4e}^{GEN})/#sigma_{m_{4e}}^{RECO}; N Events", 1000, -10, 10);
	histContainer_["hmass_pulls_4egen3_good"]=fs->make<TH1F>("hmass_pulls_4egen3_good","four lepton mass pulls (w.r.t 4 gen3 e), good; (m_{4e}^{RECO} - m_{4e}^{GEN3})/#sigma_{m_{4e}}^{RECO}; N Events", 1000, -10, 10);

	//histContainer_["hmass_pulls_2e2mugen_good"]=fs->make<TH1F>("hmass_pulls_2e2mugen_good","four lepton mass pulls (w.r.t gen 2e2#mu, good 2e); (m_{2e2#mu}^{RECO} - m_{2e2#mu}^{GEN})/#sigma_{m_{2e2#mu}}^{RECO}; N Events", 1000, -10, 10);
	//histContainer_["hmass_pulls_2e2mugen_bad"]=fs->make<TH1F>("hmass_pulls_2e2mugen_bad","four lepton mass pulls (w.r.t gen 2e2#mu, bad 2e); (m_{2e2#mu}^{RECO} - m_{2e2#mu}^{GEN})/#sigma_{m_{2e2#mu}}^{RECO}; N Events", 1000, -10, 10);

////////////////////////////////////////

	//histContainer_["newhmass_pulls_4mu"]=fs->make<TH1F>("newhmass_pulls_4mu","new four lepton mass pulls (w.r.t Higgs); (m_{4#mu}^{RECO} - m_{Higgs})/new #sigma_{m_{4#mu}}^{RECO}; N Events", 1000, -10, 10);
	histContainer_["newhmass_pulls_4mugen"]=fs->make<TH1F>("newhmass_pulls_4mugen","new four lepton mass pulls (w.r.t 4 gen #mu); (m_{4#mu}^{RECO} - m_{4#mu}^{GEN})/new #sigma_{m_{4#mu}}^{RECO}; N Events", 1000, -10, 10);
	//histContainer_["newhmass_pulls_4mugen3"]=fs->make<TH1F>("newhmass_pulls_4mugen3","new four lepton mass pulls (w.r.t 4 gen3 #mu); (m_{4#mu}^{RECO} - m_{4#mu}^{GEN3})/new #sigma_{m_{4#mu}}^{RECO}; N Events", 1000, -10, 10);

	//histContainer_["newhmass_res_4mu"]=fs->make<TH1F>("newhmass_res_4mu","new four lepton mass res (w.r.t Higgs); (m_{4#mu}^{RECO} - m_{Higgs})/m_{Higgs}; N Events", 4000, -1.5, 1.5);
	//histContainer_["newhmass_res_4mugen"]=fs->make<TH1F>("newhmass_res_4mugen","new four lepton mass res (w.r.t 4 gen #mu); (m_{4#mu}^{RECO} - m_{4#mu}^{GEN})/m_{4#mu}^{GEN}}; N Events", 1000, -0.5, 0.5);
	//histContainer_["newhmass_res_4mugen3"]=fs->make<TH1F>("newhmass_res_4mugen3","new four lepton mass res (w.r.t 4 gen3 #mu); (m_{4#mu}^{RECO} - m_{4#mu}^{GEN3})/m_{4#mu}^{GEN3}; N Events", 4000, -1.5, 1.5);


	//histContainer_["newhmass_pulls_4e"]=fs->make<TH1F>("newhmass_pulls_4e","new four lepton mass pulls (w.r.t Higgs); (m_{4e}^{RECO} - m_{Higgs})/new #sigma_{m_{4e}}^{RECO}; N Events", 1000, -10, 10);
	//histContainer_["newhmass_pulls_4egen"]=fs->make<TH1F>("newhmass_pulls_4egen","new four lepton mass pulls (w.r.t 4 gen e); (m_{4e}^{RECO} - m_{4e}^{GEN}/new #sigma_{m_{4e}}^{RECO}; N Events", 1000, -10, 10);
	histContainer_["newhmass_pulls_4egen3"]=fs->make<TH1F>("newhmass_pulls_4egen3","new four lepton mass pulls (w.r.t 4 gen3 e); (m_{4e}^{RECO} - m_{4e}^{GEN3})/new #sigma_{m_{4e}}^{RECO}; N Events", 1000, -10, 10);
       histContainer_["hmass_pulls_4egen3_adcorr"]=fs->make<TH1F>("hmass_pulls_4egen3_adcorr","new four lepton mass pulls (w.r.t 4 gen3 e); (m_{4e}^{RECO} - m_{4e}^{GEN3})/new #sigma_{m_{4e}}^{RECO}; N Events", 1000, -10, 10);

	//histContainer_["newhmass_res_4e"]=fs->make<TH1F>("newhmass_res_4e","new four lepton mass res (w.r.t Higgs); (m_{4e}^{RECO} - m_{Higgs})/m_{Higgs}; N Events", 4000, -1.5, 1.5);
	//histContainer_["newhmass_res_4egen"]=fs->make<TH1F>("newhmass_res_4egen","new four lepton mass res (w.r.t 4 gen e); (m_{4e}^{RECO} - m_{4e}^{GEN})/m_{4e}^{GEN}; N Events", 4000, -1.5, 1.5);
	//histContainer_["newhmass_res_4egen3"]=fs->make<TH1F>("newhmass_res_4egen3","new four lepton mass res (w.r.t 4 gen3 e); (m_{4e}^{RECO} - m_{4e}^{GEN3})/m_{4e}^{GEN}; N Events", 1000, -0.5, 0.5);

	//histContainer_["newhmass_pulls_2e2mu"]=fs->make<TH1F>("newhmass_pulls_2e2mu","new four lepton mass pulls (w.r.t Higgs); (m_{2e2#mu}^{RECO} - m_{Higgs})/new #sigma_{m_{2e2#mu}}^{RECO}; N Events", 1000, -10, 10);
	histContainer_["newhmass_pulls_2e2mugen"]=fs->make<TH1F>("newhmass_pulls_2e2mugen","new four lepton mass pulls (w.r.t gen 2e2#mu); (m_{2e2#mu}^{RECO} - m_{2e2#mu}^{GEN})/new #sigma_{m_{2e2#mu}}^{RECO}; N Events", 1000, -10, 10);
        histContainer_["hmass_pulls_2e2mugen_adcorr"]=fs->make<TH1F>("hmass_pulls_2e2mugen_adcorr","new four lepton mass pulls (w.r.t gen 2e2#mu); (m_{2e2#mu}^{RECO} - m_{2e2#mu}^{GEN})/new #sigma_{m_{2e2#mu}}^{RECO}; N Events", 1000, -10, 10);
	//histContainer_["newhmass_pulls_2e2mugen3"]=fs->make<TH1F>("newhmass_pulls_2e2mugen3","new four lepton mass pulls (w.r.t gen3 2e2#mu); (m_{2e2#mu}^{RECO} - m_{2e2#mu}^{GEN3})/new #sigma_{m_{2e2#mu}}^{RECO}; N Events", 1000, -10, 10);

	//histContainer_["newhmass_res_2e2mu"]=fs->make<TH1F>("newhmass_res_2e2mu","new four lepton mass pulls (w.r.t Higgs); (m_{2e2#mu}^{RECO} - m_{Higgs})/m_{Higgs}}; N Events", 4000, -1.5, 1.5);
	//histContainer_["newhmass_res_2e2mugen"]=fs->make<TH1F>("newhmass_res_2e2mugen","new four lepton mass res (w.r.t gen 2e2#mu); (m_{2e2#mu}^{RECO} - m_{2e2#mu}^{GEN})/m_{2e2#mu}^{GEN}; N Events", 1000, -0.5, 0.5);
	//histContainer_["newhmass_res_2e2mugen3"]=fs->make<TH1F>("newhmass_res_2e2mugen3","new four lepton mass res (w.r.t gen3 2e2#mu); (m_{2e2#mu}^{RECO} - m_{2e2#mu}^{GEN3})/m_{2e2#mu}^{GEN}; N Events", 4000, -1.5, 1.5);

	//histContainer_["newhmass_pulls_4e_allBNS"]=fs->make<TH1F>("newhmass_pulls_4e_allBNS","fnew our lepton mass pulls (w.r.t Higgs), all barrel and non-showering; (m_{4e}^{RECO} - m_{Higgs})/new #sigma_{m_{4e}}^{RECO}; N Events", 1000, -10, 10);
	//histContainer_["newhmass_pulls_4egen_allBNS"]=fs->make<TH1F>("newhmass_pulls_4egen_allBNS","new four lepton mass pulls (w.r.t 4egen), all barrel and non-showering; (m_{4e}^{RECO} - m_{4e}^{GEN})/new #sigma_{m_{4e}}^{RECO}; N Events", 1000, -10, 10);
	histContainer_["newhmass_pulls_4egen3_allBNS"]=fs->make<TH1F>("newhmass_pulls_4egen3_allBNS","new four lepton mass pulls (w.r.t 4egen3), all barrel and non-showering; (m_{4e}^{RECO} - m_{4e}^{GEN3})/new #sigma_{m_{4e}}^{RECO}; N Events", 1000, -10, 10);
        histContainer_["hmass_pulls_4egen3_allBNS_adcorr"]=fs->make<TH1F>("hmass_pulls_4egen3_allBNS_adcorr","new four lepton mass pulls (w.r.t 4egen3), all barrel and non-showering; (m_{4e}^{RECO} - m_{4e}^{GEN3})/new #sigma_{m_{4e}}^{RECO}; N Events", 1000, -10, 10);

	//histContainer_["newhmass_pulls_4e_bad"]=fs->make<TH1F>("newhmass_pulls_4e_bad","new four lepton mass pulls (w.r.t Higgs), bad; (m_{4e}^{RECO} - m_{Higgs})/#sigma_{m_{4e}}^{RECO}; N Events", 1000, -10, 10);
	//histContainer_["newhmass_pulls_4egen_bad"]=fs->make<TH1F>("newhmass_pulls_4egen_bad","new four lepton mass pulls (w.r.t 4 gen e), bad; (m_{4e}^{RECO} - m_{4e}^{GEN})/#sigma_{m_{4e}}^{RECO}; N Events", 1000, -10, 10);
	histContainer_["newhmass_pulls_4egen3_bad"]=fs->make<TH1F>("newhmass_pulls_4egen3_bad","new four lepton mass pulls (w.r.t 4 gen3 e), bad; (m_{4e}^{RECO} - m_{4e}^{GEN3})/new #sigma_{m_{4e}}^{RECO}; N Events", 1000, -10, 10);
        histContainer_["hmass_pulls_4egen3_bad_adcorr"]=fs->make<TH1F>("hmass_pulls_4egen3_bad_adcorr","new four lepton mass pulls (w.r.t 4 gen3 e), bad; (m_{4e}^{RECO} - m_{4e}^{GEN3})/new #sigma_{m_{4e}}^{RECO}; N Events", 1000, -10, 10);

	//histContainer_["newhmass_pulls_4e_medium"]=fs->make<TH1F>("newhmass_pulls_4e_medium","new four lepton mass pulls (w.r.t Higgs), medium; (m_{4e}^{RECO} - m_{Higgs})/new #sigma_{m_{4e}}^{RECO}; N Events", 1000, -10, 10);
	//histContainer_["newhmass_pulls_4egen_medium"]=fs->make<TH1F>("newhmass_pulls_4egen_medium","new four lepton mass pulls (w.r.t 4 gen e), medium; (m_{4e}^{RECO} - m_{4e}^{GEN})/new #sigma_{m_{4e}}^{RECO}; N Events", 1000, -10, 10);
	histContainer_["newhmass_pulls_4egen3_medium"]=fs->make<TH1F>("newhmass_pulls_4egen3_medium","new four lepton mass pulls (w.r.t 4 gen3 e), medium; (m_{4e}^{RECO} - m_{4e}^{GEN3})/new #sigma_{m_{4e}}^{RECO}; N Events", 1000, -10, 10);
       histContainer_["hmass_pulls_4egen3_medium_adcorr"]=fs->make<TH1F>("newhmass_pulls_4egen3_medium_adcorr","new four lepton mass pulls (w.r.t 4 gen3 e), medium; (m_{4e}^{RECO} - m_{4e}^{GEN3})/new #sigma_{m_{4e}}^{RECO}; N Events", 1000, -10, 10);

	//histContainer_["newhmass_pulls_4e_good"]=fs->make<TH1F>("newhmass_pulls_4e_good","new four lepton mass pulls (w.r.t Higgs), good; (m_{4e}^{RECO} - m_{Higgs})/new #sigma_{m_{4e}}^{RECO}; N Events", 1000, -10, 10);
	//histContainer_["newhmass_pulls_4egen_good"]=fs->make<TH1F>("newhmass_pulls_4egen_good","new four lepton mass pulls (w.r.t 4 gen e), good; (m_{4e}^{RECO} - m_{4e}^{GEN})/new #sigma_{m_{4e}}^{RECO}; N Events", 1000, -10, 10);
	histContainer_["newhmass_pulls_4egen3_good"]=fs->make<TH1F>("newhmass_pulls_4egen3_good","new four lepton mass pulls (w.r.t 4 gen3 e), good; (m_{4e}^{RECO} - m_{4e}^{GEN3})/new #sigma_{m_{4e}}^{RECO}; N Events", 1000, -10, 10);
        histContainer_["hmass_pulls_4egen3_good_adcorr"]=fs->make<TH1F>("hmass_pulls_4egen3_good_adcorr","new four lepton mass pulls (w.r.t 4 gen3 e), good; (m_{4e}^{RECO} - m_{4e}^{GEN3})/new #sigma_{m_{4e}}^{RECO}; N Events", 1000, -10, 10);

}
void HZZ4LResolution::fillHistograms(std::map<TString,TH1F*> &histContainer_, std::map<TString, TH2F*> &hist2DContainer_, std::vector< pat::Electron>& isolatedRecElectrons, std::vector< pat::Muon >& isolatedRecMuons, vector< pat::PFParticle>& fsrPhotons, double evtWeight, bool isData)
{

	// for 4e mass resolution 
	if(isolatedRecElectrons.size()>=4){
		int nposq = 0, nnegq =0;
		double genhiggsmass = -1;
		double gen4lmass = -1;
		double gen4lpmass = -1;
		TLorentzVector gen4l ;
		TLorentzVector gen4lp ;
		if(debug_) std::cout<<" initialized 4 isolated electrons "<<endl;

		vector<int> cats; cats.clear();
		vector<bool> regions; regions.clear();

		int ngenematched = 0;
		for(unsigned int i=0; i<isolatedRecElectrons.size(); i++){
			const pat::Electron *elec = &(isolatedRecElectrons[i]);
			if(elec->charge()==1) nposq++; 
			else nnegq++;
			cats.push_back(elec->classification());
			bool barrel = false;
			if(fabs(elec->eta())<1.5) barrel=true;
			regions.push_back(barrel);

			if(debug_) std::cout<< i <<" th  electron "<<endl;
			bool lepadded = false;
			for(unsigned int j = 0 ; j < elec->genParticleRefs().size() ; j++ ){
				if( elec->genParticle(j)->status() == 1 && abs(elec->genParticle(j)->pdgId()) == 11 ){
					if(!lepadded) {
						TLorentzVector tlvtmp; tlvtmp.SetPtEtaPhiM(
								elec->genParticle(j)->pt(), elec->genParticle(j)->eta(), elec->genParticle(j)->phi(),elec->genParticle(j)->mass());
						gen4l+=tlvtmp;

						const reco::Candidate * orignElec; 
						orignElec= ( const reco::Candidate*) (elec->genParticle(j)->mother());
						if(abs(orignElec->pdgId())==11){
							for(int l=0; l<10; l++){
								if(abs(orignElec->mother()->pdgId())==11){	
									orignElec = orignElec->mother();
								}else{
									break;
								}
							}
						}
						if(abs(elec->genParticle(j)->mother()->pdgId())==11){
							TLorentzVector tlvtmp2; tlvtmp2.SetPtEtaPhiM(
									elec->genParticle(j)->mother()->pt(), elec->genParticle(j)->mother()->eta(), elec->genParticle(j)->mother()->phi(),elec->genParticle(j)->mother()->mass());
							gen4lp+=tlvtmp2;
						}else{
							gen4lp+=tlvtmp;
						}
						lepadded= true;
						ngenematched++;
						if(debug_) std::cout<< i <<" th  electron, added "<<endl;
					}

					double m = genHiggsMass(elec); if(m>0) genhiggsmass = m;
				}
			}
		}
		if(debug_) std::cout<< " gen higgs mass = "<<genhiggsmass <<endl;

		gen4lmass = gen4l.M();
		gen4lpmass = gen4lp.M();
		if(debug_) std::cout<< " gen 4e mass = "<<gen4lmass <<endl;
		if(debug_) std::cout<< " gen 4ep mass = "<<gen4lpmass <<endl;
		if (nposq==2 && nnegq==2 && ngenematched==4){
			if(debug_) std::cout<< " 2e+ 2e- "<<endl;
			double merr = massErr.calc4eErr(isolatedRecElectrons,fsrPhotons,false,isData);
			double newmerr = massErr.calc4eErr(isolatedRecElectrons,fsrPhotons,true,isData);
                        //double merr = massErr.getMassResolution(isolatedRecElectrons,isolatedRecMuons,fsrPhotons);
                        //////////////
			double recmass = (isolatedRecElectrons[0].p4()+isolatedRecElectrons[1].p4()+isolatedRecElectrons[2].p4()+isolatedRecElectrons[3].p4()).M();
			if(debug_) std::cout<< " recm = "<< recmass<<endl;
			double relmerr = merr/recmass;
			double newrelmerr = newmerr/recmass;
			//histContainer_["hmass_relerr_4e"]->Fill(relmerr);
			hist2DContainer_["hmass_relerr_vs_recm_4e"]->Fill(recmass, relmerr, evtWeight);
			hist2DContainer_["newhmass_relerr_vs_recm_4e"]->Fill(recmass, newrelmerr, evtWeight);
			if(genhiggsmass>0){

                                //cout<<"4e"<<endl;

				//histContainer_["hmass_relerr_4e_gen"]->Fill(merr/genhiggsmass);
				hist2DContainer_["hmass_relerr_vs_genm_4e"]->Fill(genhiggsmass, merr/genhiggsmass, evtWeight);

				histContainer_["hmass_pulls_4e"]->Fill( (recmass-genhiggsmass)/merr , evtWeight);
				histContainer_["hmass_pulls_4egen"]->Fill( (recmass-gen4lmass)/merr , evtWeight);
				histContainer_["hmass_pulls_4egen3"]->Fill( (recmass-gen4lpmass)/merr , evtWeight);
                                //////////////////////////
				histContainer_["hmass_res_4e"]->Fill( (recmass-genhiggsmass)/genhiggsmass , evtWeight);
				histContainer_["hmass_res_4egen"]->Fill( (recmass-gen4lmass)/gen4lmass , evtWeight);
				histContainer_["hmass_res_4egen3"]->Fill( (recmass-gen4lpmass)/gen4lpmass , evtWeight);

				hist2DContainer_["newhmass_relerr_vs_genm_4e"]->Fill(genhiggsmass, newmerr/genhiggsmass, evtWeight);

				//histContainer_["newhmass_pulls_4e"]->Fill( (recmass-genhiggsmass)/newmerr , evtWeight);
				//histContainer_["newhmass_pulls_4egen"]->Fill( (recmass-gen4lmass)/newmerr , evtWeight);
				histContainer_["newhmass_pulls_4egen3"]->Fill( (recmass-gen4lpmass)/newmerr , evtWeight);
                                //////////////////////////

				if( (cats[0]==0 or cats[0]==1) and regions[0]==true and (cats[1]==0 or cats[1]==1) and regions[1]==true 
						and (cats[2]==0 or cats[2]==1) and regions[2]==true and (cats[3]==0 or cats[3]==1) and regions[3]==true ){
					histContainer_["hmass_pulls_4e_allBNS"]->Fill( (recmass-genhiggsmass)/merr , evtWeight);
					histContainer_["hmass_pulls_4egen_allBNS"]->Fill( (recmass-gen4lmass)/merr , evtWeight);
					histContainer_["hmass_pulls_4egen3_allBNS"]->Fill( (recmass-gen4lpmass)/merr , evtWeight);
				}

				if( (cats[0]==0 or cats[0]==1) and regions[0]==true and (cats[1]==0 or cats[1]==1) and regions[1]==true 
						and (cats[2]==0 or cats[2]==1) and regions[2]==true and (cats[3]==0 or cats[3]==1) and regions[3]==true ){
					//histContainer_["newhmass_pulls_4e_allBNS"]->Fill( (recmass-genhiggsmass)/newmerr , evtWeight);
					//histContainer_["newhmass_pulls_4egen_allBNS"]->Fill( (recmass-gen4lmass)/newmerr , evtWeight);
					histContainer_["newhmass_pulls_4egen3_allBNS"]->Fill( (recmass-gen4lpmass)/newmerr , evtWeight);
				}
				int nEB = 0; for(int j=0; j<4; j++) if(regions[j]) nEB++;
				int nNS = 0; for(int j=0; j<4; j++) if(cats[j]<2) nNS++;
				int nEBNS = 0; for(int j=0; j<4; j++) if(cats[j]<2 and regions[j]) nEBNS++;
				int nEENS = 0; for(int j=0; j<4; j++) if(cats[j]<2 and !regions[j]) nEENS++;
				if( nEB==4 and nNS >= 3 ){    //good
					histContainer_["hmass_pulls_4e_good"]->Fill( (recmass-genhiggsmass)/merr , evtWeight);
					histContainer_["hmass_pulls_4egen_good"]->Fill( (recmass-gen4lmass)/merr , evtWeight);
					histContainer_["hmass_pulls_4egen3_good"]->Fill( (recmass-gen4lpmass)/merr , evtWeight);
				}else if( (nEB==4 and nNS<3) or (nEBNS>=2 and nEENS==1) ){//meadium
					histContainer_["hmass_pulls_4e_medium"]->Fill( (recmass-genhiggsmass)/merr , evtWeight);
					histContainer_["hmass_pulls_4egen_medium"]->Fill( (recmass-gen4lmass)/merr , evtWeight);
					histContainer_["hmass_pulls_4egen3_medium"]->Fill( (recmass-gen4lpmass)/merr , evtWeight);
				}else{
					histContainer_["hmass_pulls_4e_bad"]->Fill( (recmass-genhiggsmass)/merr , evtWeight);
					histContainer_["hmass_pulls_4egen_bad"]->Fill( (recmass-gen4lmass)/merr , evtWeight);
					histContainer_["hmass_pulls_4egen3_bad"]->Fill( (recmass-gen4lpmass)/merr , evtWeight);
				}

				if( nEB==4 and nNS >= 3 ){    //good
					//histContainer_["newhmass_pulls_4e_good"]->Fill( (recmass-genhiggsmass)/newmerr , evtWeight);
					//histContainer_["newhmass_pulls_4egen_good"]->Fill( (recmass-gen4lmass)/newmerr , evtWeight);
					histContainer_["newhmass_pulls_4egen3_good"]->Fill( (recmass-gen4lpmass)/newmerr , evtWeight);
				}else if( (nEB==4 and nNS<3) or (nEBNS>=2 and nEENS==1) ){//meadium
					//histContainer_["newhmass_pulls_4e_medium"]->Fill( (recmass-genhiggsmass)/newmerr , evtWeight);
					//histContainer_["newhmass_pulls_4egen_medium"]->Fill( (recmass-gen4lmass)/newmerr , evtWeight);
					histContainer_["newhmass_pulls_4egen3_medium"]->Fill( (recmass-gen4lpmass)/newmerr , evtWeight);
				}else{
					//histContainer_["newhmass_pulls_4e_bad"]->Fill( (recmass-genhiggsmass)/newmerr , evtWeight);
					//histContainer_["newhmass_pulls_4egen_bad"]->Fill( (recmass-gen4lmass)/newmerr , evtWeight);
					histContainer_["newhmass_pulls_4egen3_bad"]->Fill( (recmass-gen4lpmass)/newmerr , evtWeight);
				}
				//histContainer_["hmass_diffHiggs4egen"]->Fill((genhiggsmass-gen4lmass)/genhiggsmass, evtWeight);
				//hist2DContainer_["hmass_rawreso_vs_genm_4e"]->Fill(genhiggsmass, (recmass-genhiggsmass)/genhiggsmass, evtWeight);
			}
			if(debug_) std::cout<< " filled 4e mass resolution "<<endl;
		}
	}

	if(isolatedRecMuons.size()>=4){
		// // only temporaly for HZZ4l samples
		int nposq = 0, nnegq =0;
		double genhiggsmass = -1;
		double gen4lmass = -1;
		TLorentzVector gen4l ;
		for(unsigned int i=0; i<isolatedRecMuons.size(); i++){
			const pat::Muon *mu = &(isolatedRecMuons[i]);
			if(mu->charge()==1) nposq++; 
			else nnegq++;

			bool lepadded = false;
			for(unsigned int i = 0 ; i < mu->genParticleRefs().size() ; i++ ){
				if( mu->genParticle(i)->status() == 1 && abs(mu->genParticle(i)->pdgId()) == 13 ){
					if(!lepadded) {
						TLorentzVector tlvtmp; tlvtmp.SetPtEtaPhiM(
								mu->genParticle(i)->pt(), mu->genParticle(i)->eta(), mu->genParticle(i)->phi(),mu->genParticle(i)->mass());
						gen4l+=tlvtmp;
						lepadded= true;
					}

					double m = genHiggsMass(mu); if(m>0) genhiggsmass = m;
				}
			}
		}

		gen4lmass = gen4l.M();
		if (nposq==2 && nnegq==2){
			double merr = massErr.calc4muErr(isolatedRecMuons,fsrPhotons,false,isData);
			double newmerr = massErr.calc4muErr(isolatedRecMuons,fsrPhotons,true,isData);

			double recmass = (isolatedRecMuons[0].p4()+isolatedRecMuons[1].p4()+isolatedRecMuons[2].p4()+isolatedRecMuons[3].p4()).M();
			double relmerr = merr/recmass;

			double newrelmerr = newmerr/recmass;

			//histContainer_["hmass_relerr_4mu"]->Fill(relmerr);
			hist2DContainer_["hmass_relerr_vs_recm_4mu"]->Fill(recmass, relmerr);

			hist2DContainer_["newhmass_relerr_vs_recm_4mu"]->Fill(recmass, newrelmerr);

			if(genhiggsmass>0){

                                //cout<<"4mu"<<endl;

				//histContainer_["hmass_relerr_4mu_gen"]->Fill(merr/genhiggsmass);
				hist2DContainer_["hmass_relerr_vs_genm_4mu"]->Fill(genhiggsmass, merr/genhiggsmass, evtWeight);
				histContainer_["hmass_pulls_4mu"]->Fill( (recmass-genhiggsmass)/merr , evtWeight);
				histContainer_["hmass_pulls_4mugen"]->Fill( (recmass-gen4lmass)/merr , evtWeight);
                                ///////////
                                histContainer_["hmass_res_4mu"]->Fill( (recmass-genhiggsmass)/genhiggsmass , evtWeight);
				histContainer_["hmass_res_4mugen"]->Fill( (recmass-gen4lmass)/gen4lmass , evtWeight);

				//histContainer_["newhmass_relerr_4mu_gen"]->Fill(newmerr/genhiggsmass);
				hist2DContainer_["newhmass_relerr_vs_genm_4mu"]->Fill(genhiggsmass, newmerr/genhiggsmass, evtWeight);
				//histContainer_["newhmass_pulls_4mu"]->Fill( (recmass-genhiggsmass)/newmerr , evtWeight);
				histContainer_["newhmass_pulls_4mugen"]->Fill( (recmass-gen4lmass)/newmerr , evtWeight);
                                ///////////

			}

		}
	}
	if(isolatedRecMuons.size()>=2 && isolatedRecElectrons.size()>=2){
		// // only temporaly for HZZ4l samples
		vector<int> cats; cats.clear();
		vector<bool> regions; regions.clear();
		int nposq = 0, nnegq =0;
		double genhiggsmass = -1;
		double gen4lmass = -1;
		TLorentzVector gen4l ;
		for(unsigned int i=0; i<isolatedRecMuons.size(); i++){
			const pat::Muon *mu = &(isolatedRecMuons[i]);
			if(mu->charge()==1) nposq++; 
			else nnegq++;
			bool lepadded = false;
			for(unsigned int i = 0 ; i < mu->genParticleRefs().size() ; i++ ){
				if( mu->genParticle(i)->status() == 1 && abs(mu->genParticle(i)->pdgId()) == 13 ){
					if(!lepadded) {
						TLorentzVector tlvtmp; tlvtmp.SetPtEtaPhiM(
								mu->genParticle(i)->pt(), mu->genParticle(i)->eta(), mu->genParticle(i)->phi(),mu->genParticle(i)->mass());
						gen4l+=tlvtmp;
						lepadded= true;
					}
					double m = genHiggsMass(mu); if(m>0) genhiggsmass = m;
				}
			}
		}

		for(unsigned int i=0; i<isolatedRecElectrons.size(); i++){
			const pat::Electron *elec = &(isolatedRecElectrons[i]);
			if(elec->charge()==1) nposq++; 
			else nnegq++;
			cats.push_back(elec->classification());
			bool barrel = false;
			if(fabs(elec->eta())<1.5) barrel=true;
			regions.push_back(barrel);

			bool lepadded = false;
			for(unsigned int j = 0 ; j < elec->genParticleRefs().size() ; j++ ){
				if( elec->genParticle(j)->status() == 1 && abs(elec->genParticle(j)->pdgId()) == 11 ){
					if(!lepadded) {
						TLorentzVector tlvtmp; tlvtmp.SetPtEtaPhiM(
								elec->genParticle(j)->pt(), elec->genParticle(j)->eta(), elec->genParticle(j)->phi(),elec->genParticle(j)->mass());
						gen4l+=tlvtmp;
						lepadded= true;
					}
					double m = genHiggsMass(elec); if(m>0) genhiggsmass = m;
				}
			}
		}
		gen4lmass = gen4l.M();
		if (nposq==2 && nnegq==2){

			double merr = massErr.calc2e2muErr(isolatedRecElectrons, isolatedRecMuons,fsrPhotons,false,isData);
                        double newmerr = massErr.calc2e2muErr(isolatedRecElectrons, isolatedRecMuons,fsrPhotons,true,isData);
                        //double merr = massErr.getMassResolution(isolatedRecElectrons, isolatedRecMuons,fsrPhotons);

			double recmass = (isolatedRecElectrons[0].p4()+isolatedRecElectrons[1].p4()+isolatedRecMuons[0].p4()+isolatedRecMuons[1].p4()).M();

			double relmerr = merr/recmass;
                        double newrelmerr = newmerr/recmass;

			//histContainer_["hmass_relerr_2e2mu"]->Fill(relmerr, evtWeight);
			hist2DContainer_["hmass_relerr_vs_recm_2e2mu"]->Fill(recmass, relmerr, evtWeight);
			hist2DContainer_["newhmass_relerr_vs_recm_2e2mu"]->Fill(recmass, newrelmerr, evtWeight);

			int nEB = 0; for(int j=0; j<2; j++) if(regions[j]) nEB++;
			int nNS = 0; for(int j=0; j<2; j++) if(cats[j]<2) nNS++;
			int nEBNS = 0; for(int j=0; j<2; j++) if(cats[j]<2 and regions[j]) nEBNS++;
			int nEENS = 0; for(int j=0; j<2; j++) if(cats[j]<2 and !regions[j]) nEENS++;
			if(genhiggsmass>0){

                                //cout<<"2e2mu"<<endl;

				//histContainer_["hmass_relerr_2e2mu_gen"]->Fill(merr/genhiggsmass, evtWeight);
				hist2DContainer_["hmass_relerr_vs_genm_2e2mu"]->Fill(genhiggsmass, merr/genhiggsmass, evtWeight);

				histContainer_["hmass_pulls_2e2mu"]->Fill( (recmass-genhiggsmass)/merr , evtWeight);
				histContainer_["hmass_pulls_2e2mugen"]->Fill( (recmass-gen4lmass)/merr , evtWeight);
				histContainer_["hmass_res_2e2mu"]->Fill( (recmass-genhiggsmass)/genhiggsmass , evtWeight);
				histContainer_["hmass_res_2e2mugen"]->Fill( (recmass-gen4lmass)/gen4lmass , evtWeight);
				/*
				if(nEBNS==2){
					histContainer_["hmass_pulls_2e2mugen_good"]->Fill( (recmass-gen4lmass)/merr , evtWeight);
				}else if(nEBNS==0){
				}else if(nEB==0 && nEENS==0){
					histContainer_["hmass_pulls_2e2mugen_bad"]->Fill( (recmass-gen4lmass)/merr , evtWeight);
				}
				*/

				//histContainer_["newhmass_relerr_2e2mu_gen"]->Fill(newmerr/genhiggsmass, evtWeight);
				hist2DContainer_["newhmass_relerr_vs_genm_2e2mu"]->Fill(genhiggsmass, newmerr/genhiggsmass, evtWeight);

				//histContainer_["newhmass_pulls_2e2mu"]->Fill( (recmass-genhiggsmass)/newmerr , evtWeight);
				histContainer_["newhmass_pulls_2e2mugen"]->Fill( (recmass-gen4lmass)/newmerr , evtWeight);
				/*
				if(nEBNS==2){
					histContainer_["newhmass_pulls_2e2mugen_good"]->Fill( (recmass-gen4lmass)/newmerr , evtWeight);
				}else if(nEBNS==0){
				}else if(nEB==0 && nEENS==0){
					histContainer_["newhmass_pulls_2e2mugen_bad"]->Fill( (recmass-gen4lmass)/newmerr , evtWeight);
				}
				*/
			}
		}
	}


}


void HZZ4LResolution::plotHistograms(std::map<TString,TH1F*> &histContainer_ , bool weightEvents, double scaleWeight)
{

	if(weightEvents)
	{

		//      if(histContainer_[pt1_4mu]->GetEntries() > 0){histContainer_[pt1_4mu]->Scale(scaleWeight);}
	}

}

double HZZ4LResolution::genHiggsMass(const pat::Electron*elec){
	double genhiggsmass = -1;
	for(unsigned int j = 0 ; j < elec->genParticleRefs().size() ; j++ ){
		const reco::Candidate * orignElec; 
		orignElec= ( const reco::Candidate*) (elec->genParticle(j)->mother());
		for(int l=0; l<10; l++){
			if(orignElec==NULL) break;
			if(abs(orignElec->pdgId())==25){	
				genhiggsmass=orignElec->mass();
				return genhiggsmass;
			}
			orignElec = orignElec->mother();
		}
	}
	return genhiggsmass;
}
double HZZ4LResolution::genHiggsMass(const pat::Muon*elec){
	double genhiggsmass = -1;
	for(unsigned int j = 0 ; j < elec->genParticleRefs().size() ; j++ ){
		const reco::Candidate * orignElec; 
		orignElec= ( const reco::Candidate*) (elec->genParticle(j)->mother());
		for(int l=0; l<10; l++){
			if(orignElec==NULL) break;
			if(abs(orignElec->pdgId())==25){	
				genhiggsmass=orignElec->mass();
				return genhiggsmass;
			}
			orignElec = orignElec->mother();
		}
	}
	return genhiggsmass;
}


#endif
