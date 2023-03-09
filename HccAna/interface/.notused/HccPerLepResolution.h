#ifndef HZZ4LPERLEPRESOLUTION_H
#define HZZ4LPERLEPRESOLUTION_H

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
#include "TH3.h"
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

#include <boost/shared_ptr.hpp>

using namespace std;

class HZZ4LPerLepResolution
{

	public:

	HZZ4LPerLepResolution();
	HZZ4LPerLepResolution(TString appendName);
	~HZZ4LPerLepResolution();

	void bookHistograms(edm::Service<TFileService> fs, std::map<TString,TH1F*> &histContainer_, std::map<TString, TH2F*> &hist2DContainer_,std::map<TString, TH3F*> &hist3DContainer_);
	void fillHistograms(std::map<TString,TH1F*> &histContainer_ , std::map<TString, TH2F*> &hist2DContainer_, std::map<TString, TH3F*> &hist3DContainer_, std::vector< pat::Electron > electrons, std::vector< pat::Muon > muons, double evtWeight, bool isData);
	void plotHistograms(std::map<TString,TH1F*> &histContainer_ , bool weightEvents, double scaleWeight);
	double matchedGen3MuonPt(const pat::Muon * e);
	double matchedGenMuonPt(const pat::Muon * e);
	double matchedGen3ElectronPt(const pat::Electron * e);
	double matchedGen2ElectronPt(const pat::Electron * e);
	double matchedGenElectronPt(const pat::Electron * e);


	private:

		boost::shared_ptr<TFile>     fmu;
		boost::shared_ptr<TFile>     fel;
                boost::shared_ptr<TH2F>      muon_corr_data;
                boost::shared_ptr<TH2F>      muon_corr_mc;
                boost::shared_ptr<TH2F>      electron_corr_data;
                boost::shared_ptr<TH2F>      electron_corr_mc;

	TString  appName;

        //pull
	TString  mu_pull1, mu_pull3, mu_relpterr;
	TString  mu_pull1_vs_pt, mu_pull3_vs_pt, mu_relpterr_vs_pt;
	TString  mu_pull1_vs_eta, mu_pull3_vs_eta, mu_relpterr_vs_eta;
        //res
	TString  mu_res1, mu_res3;
	TString  mu_res1_vs_pt, mu_res3_vs_pt; 
	TString  mu_res1_vs_eta, mu_res3_vs_eta; 
        //3d;
        TString  mu_pull1_vs_pt_eta, mu_pull3_vs_pt_eta;
        TString  mu_res1_vs_pt_eta, mu_res3_vs_pt_eta;

        //pull
	TString  newmu_pull1, newmu_relpterr;
	TString  newmu_pull1_vs_pt, newmu_relpterr_vs_pt;
	TString  newmu_pull1_vs_eta, newmu_relpterr_vs_eta;
        //res
	TString  newmu_res1;
	TString  newmu_res1_vs_pt; 
	TString  newmu_res1_vs_eta;
        //3d;
        TString  newmu_pull1_vs_pt_eta;
        TString  newmu_res1_vs_pt_eta;

/////////////////////////////////////////////////

        TString el_relpterr2D, mu_relpterr2D, Nel_relpterr2D, Nmu_relpterr2D;   
        TString newel_relpterr2D, newmu_relpterr2D, newNel_relpterr2D, newNmu_relpterr2D;

/////////////////////////////////////////////////

	TString el_pull1[7], el_pull2[7],  el_pull3[7], el_relpterr[7];
	TString el_pull1_vs_pt[7], el_pull2_vs_pt[7], el_pull3_vs_pt[7], el_relpterr_vs_pt[7];
	TString el_pull1_vs_eta[7], el_pull2_vs_eta[7], el_pull3_vs_eta[7], el_relpterr_vs_eta[7];

	TString el_res1[7],el_res2[7], el_res3[7];
	TString el_res1_vs_pt[7], el_res2_vs_pt[7], el_res3_vs_pt[7];
	TString el_res1_vs_eta[7], el_res2_vs_eta[7], el_res3_vs_eta[7];

        TString  el_pull1_vs_pt_eta, el_pull2_vs_pt_eta, el_pull3_vs_pt_eta;
        TString  el_res1_vs_pt_eta, el_res2_vs_pt_eta, el_res3_vs_pt_eta;

        TString el_pull1_vs_pt_eta_propertracker, el_res1_vs_pt_eta_propertracker; 
        TString el_pull3_vs_pt_eta_propertracker, el_res3_vs_pt_eta_propertracker;

/////////////

	TString newel_pull3[7], newel_relpterr[7];
	TString newel_pull3_vs_pt[7], newel_relpterr_vs_pt[7];
	TString newel_pull3_vs_eta[7], newel_relpterr_vs_eta[7];        
        TString newel_pull3_vs_pt_eta;

	TString newel_res3[7];
	TString newel_res3_vs_pt[7];
	TString newel_res3_vs_eta[7];
        TString newel_res3_vs_pt_eta;

//////////////////Non ecal driven electrons///////////////////////////////////////////////////////////////////////////

        TString  el_res1_nonecal, el_res2_nonecal, el_res3_nonecal;
        TString  el_pull1_nonecal, el_pull2_nonecal, el_pull3_nonecal;

        TString  el_res1_nonecal_tracker, el_res2_nonecal_tracker, el_res3_nonecal_tracker;
        TString  el_pull1_nonecal_tracker, el_pull2_nonecal_tracker, el_pull3_nonecal_tracker;

        TString  el_res1_nonecal_propertracker, el_res2_nonecal_propertracker, el_res3_nonecal_propertracker;
        TString  el_pull1_nonecal_propertracker, el_pull2_nonecal_propertracker, el_pull3_nonecal_propertracker;

        TString  el_pterr_nonecal2D, el_pterr_propernonecal2D, el_pterr_nonecal, el_pterr_nonecal_tracker, el_pterr_nonecal_propertracker;

};


#endif

#ifndef HZZ4LPERLEPRESOLUTION_CC
#define HZZ4LPERLEPRESOLUTION_CC

HZZ4LPerLepResolution::HZZ4LPerLepResolution()
{

/////////////////////////////////////

	fmu = boost::shared_ptr<TFile>( new TFile("UFHZZAnalysisRun2/UFHZZ4LAna/data/finalCorrections.2012.root") ); 
	fel = boost::shared_ptr<TFile>( new TFile("UFHZZAnalysisRun2/UFHZZ4LAna/data/finalCorrections.2012.root") );

        muon_corr_data = boost::shared_ptr<TH2F>(  (static_cast<TH2F*>(fmu->Get( "mu_reco53x" )->Clone() )) );
        muon_corr_mc = boost::shared_ptr<TH2F>(  (static_cast<TH2F*>(fmu->Get( "mu_mc53x" )->Clone() )) );
        electron_corr_data = boost::shared_ptr<TH2F>(  (static_cast<TH2F*>(fel->Get( "el_reco53x" )->Clone() )) );
        electron_corr_mc = boost::shared_ptr<TH2F>(  (static_cast<TH2F*>(fel->Get( "el_mc53x" )->Clone() )) ); 

////////////////////////////////////

	appName = "";
	
        mu_pull1 = "mu_pull1";
	mu_pull3 = "mu_pull3";

	mu_res1 = "mu_res1";
	mu_res3 = "mu_res3";

	mu_pull1_vs_pt = "mu_pull1_vs_pt";
	mu_pull3_vs_pt = "mu_pull3_vs_pt";
	mu_pull1_vs_eta = "mu_pull1_vs_eta";
	mu_pull3_vs_eta = "mu_pull3_vs_eta";

	mu_res1_vs_pt = "mu_res1_vs_pt";
	mu_res3_vs_pt = "mu_res3_vs_pt";
	mu_res1_vs_eta = "mu_res1_vs_eta";
	mu_res3_vs_eta = "mu_res3_vs_eta";

        newmu_pull1 = "newmu_pull1";
	newmu_pull1_vs_pt = "newmu_pull1_vs_pt";
	newmu_pull1_vs_eta = "newmu_pull1_vs_eta";

        newmu_res1 = "newmu_res1";
	newmu_res1_vs_pt = "newmu_res1_vs_pt";
	newmu_res1_vs_eta = "newmu_res1_vs_eta";

//////////////////////////////////////

	mu_relpterr = "mu_relpterr";
	mu_relpterr_vs_pt = "mu_relpterr_vs_pt";
	mu_relpterr_vs_eta = "mu_relpterr_vs_eta";
	mu_pull1_vs_pt_eta= "mu_pull1_vs_pt_eta"; 
        mu_pull3_vs_pt_eta= "mu_pull3_vs_pt_eta";
	mu_res1_vs_pt_eta= "mu_res1_vs_pt_eta"; 

	newmu_relpterr = "newmu_relpterr";
	newmu_relpterr_vs_pt = "newmu_relpterr_vs_pt";
	newmu_relpterr_vs_eta = "newmu_relpterr_vs_eta";
	newmu_pull1_vs_pt_eta= "newmu_pull1_vs_pt_eta";
	newmu_res1_vs_pt_eta= "newmu_res1_vs_pt_eta";

////////////

        mu_relpterr2D = "mu_relpterr2D";
        newmu_relpterr2D = "newmu_relpterr2D";
        Nmu_relpterr2D = "Nmu_relpterr2D";
        newNmu_relpterr2D = "newNmu_relpterr2D";

//////////////////////////////////////////////////////
 
        el_relpterr2D = "el_relpterr2D";
        newel_relpterr2D = "newel_relpterr2D";
        Nel_relpterr2D = "Nel_relpterr2D";

        //3d
        el_pull3_vs_pt_eta= "el_pull3_vs_pt_eta";
        newel_pull3_vs_pt_eta= "newel_pull3_vs_pt_eta";

        //3d
	el_res3_vs_pt_eta= "el_res3_vs_pt_eta";
        newel_res3_vs_pt_eta= "newel_res3_vs_pt_eta";

	for(int i=0; i<7; i++){
		el_pull1[i] = "el_pull1_";  el_pull1[i]+=i;
		el_pull2[i] = "el_pull2_";  el_pull2[i]+=i;
		el_pull3[i] = "el_pull3_";  el_pull3[i]+=i;
		el_relpterr[i] = "el_relpterr_";  el_relpterr[i]+=i;
                el_res1[i] = "el_res1_";  el_res1[i]+=i;
                el_res2[i] = "el_res2_";  el_res2[i]+=i;
                el_res3[i] = "el_res3_";  el_res3[i]+=i;

                //new
		newel_pull3[i] = "newel_pull3_";  newel_pull3[i]+=i;
		newel_relpterr[i] = "newel_relpterr_";  newel_relpterr[i]+=i;
                newel_res3[i] = "newel_res3_";  newel_res3[i]+=

                //////////////////////////////
 
		el_pull1_vs_pt[i] = "el_pull1_vs_pt_";  el_pull1_vs_pt[i]+=i;
		el_pull2_vs_pt[i] = "el_pull2_vs_pt_";  el_pull2_vs_pt[i]+=i;                 
		el_pull3_vs_pt[i] = "el_pull3_vs_pt_";  el_pull3_vs_pt[i]+=i;
		el_relpterr_vs_pt[i] = "el_relpterr_vs_pt_";  el_relpterr_vs_pt[i]+=i;
		el_pull1_vs_eta[i] = "el_pull1_vs_eta_";  el_pull1_vs_eta[i]+=i;
		el_pull2_vs_eta[i] = "el_pull2_vs_eta_";  el_pull2_vs_eta[i]+=i;
		el_pull3_vs_eta[i] = "el_pull3_vs_eta_";  el_pull3_vs_eta[i]+=i;
		el_relpterr_vs_eta[i] = "el_relpterr_vs_eta_";  el_relpterr_vs_eta[i]+=i;

                el_res1_vs_pt[i] = "el_res1_vs_pt_";  el_res1_vs_pt[i]+=i;
                el_res2_vs_pt[i] = "el_res2_vs_pt_";  el_res2_vs_pt[i]+=i;
                el_res3_vs_pt[i] = "el_res3_vs_pt_";  el_res3_vs_pt[i]+=i;
                el_res1_vs_eta[i] = "el_res1_vs_eta_";  el_res1_vs_eta[i]+=i;
                el_res2_vs_eta[i] = "el_res2_vs_eta_";  el_res2_vs_eta[i]+=i;
                el_res3_vs_eta[i] = "el_res3_vs_eta_";  el_res3_vs_eta[i]+=i;

                //new 
		newel_pull3_vs_pt[i] = "newel_pull3_vs_pt_";  newel_pull3_vs_pt[i]+=i;
		newel_relpterr_vs_pt[i] = "newel_relpterr_vs_pt_";  newel_relpterr_vs_pt[i]+=i;
		newel_pull3_vs_eta[i] = "newel_pull3_vs_eta_";  newel_pull3_vs_eta[i]+=i;
		newel_relpterr_vs_eta[i] = "newel_relpterr_vs_eta_";  newel_relpterr_vs_eta[i]+=i;

		newel_res3_vs_eta[i] = "newel_pull3_vs_eta_";  newel_res3_vs_eta[i]+=i;
		newel_res3_vs_pt[i] = "newel_res3_vs_pt_";  newel_res3_vs_pt[i]+=i;

	}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        el_pterr_nonecal2D = "el_pterr_nonecal2D";
        el_pterr_propernonecal2D = "el_pterr_propernonecal2D";
        el_pterr_nonecal = "el_pterr_nonecal"; 
        el_pterr_nonecal_tracker = "el_pterr_nonecal_tracker";
        el_pterr_nonecal_propertracker = "el_pterr_nonecal_propertracker";

        el_res1_nonecal = "el_res1_vs_nonecal"; el_res2_nonecal = "el_res2_nonecal"; el_res3_nonecal = "el_res3_nonecal";
        el_pull1_nonecal = "el_pull1_vs_nonecal"; el_pull2_nonecal = "el_pull2_nonecal"; el_pull3_nonecal = "el_pull3_nonecal";

        el_res1_nonecal_tracker = "el_res1_nonecal_tracker"; el_res2_nonecal_tracker = "el_res2_nonecal_tracker"; 
        el_res3_nonecal_tracker = "el_res3_nonecal_tracker";
        el_pull1_nonecal_tracker = "el_pull1_nonecal_tracker"; el_pull2_nonecal_tracker = "el_pull2_nonecal_tracker"; 
        el_pull3_nonecal_tracker = "el_pull3_nonecal_tracker";
        ///////////////////////
        el_res1_nonecal_propertracker = "el_res1_nonecal_propertracker"; el_res2_nonecal_propertracker = "el_res2_nonecal_propertracker";
        el_res3_nonecal_propertracker = "el_res3_nonecal_propertracker";
        el_pull1_nonecal_propertracker = "el_pull1_nonecal_propertracker"; el_pull2_nonecal_propertracker = "el_pull2_nonecal_propertracker";
        el_pull3_nonecal_propertracker = "el_pull3_nonecal_propertracker";

        //for 2d pull and res
        el_pull1_vs_pt_eta_propertracker= "el_pull1_vs_pt_eta_propertracker";
        el_res1_vs_pt_eta_propertracker= "el_res1_vs_pt_eta_propertracker";

        el_pull1_vs_pt_eta= "el_pull1_vs_pt_eta";
        el_res1_vs_pt_eta= "el_res1_vs_pt_eta";

        el_pull3_vs_pt_eta_propertracker= "el_pull3_vs_pt_eta_propertracker";
	el_res3_vs_pt_eta_propertracker= "el_res3_vs_pt_eta_propertracker";

////////////////////////////////////////////////////////////


}

HZZ4LPerLepResolution::HZZ4LPerLepResolution(TString appendName)
{

	appName = appendName;
	mu_pull1 = mu_pull1 + appName;
	mu_pull3 = mu_pull3 + appName;
	mu_relpterr = mu_relpterr + appName;

        mu_relpterr2D = mu_relpterr2D + appName;
        el_relpterr2D = el_relpterr2D + appName;

	mu_pull1_vs_pt = mu_pull1_vs_pt + appName;
	mu_pull3_vs_pt = mu_pull3_vs_pt + appName;
	mu_pull1_vs_eta = mu_pull1_vs_eta + appName;
	mu_pull3_vs_eta = mu_pull3_vs_eta + appName;

	mu_res1_vs_pt = mu_res1_vs_pt + appName;
	mu_res3_vs_pt = mu_res3_vs_pt + appName;
	mu_res1_vs_eta = mu_res1_vs_eta + appName;
	mu_res3_vs_eta = mu_res3_vs_eta + appName;

	mu_relpterr_vs_pt = mu_relpterr_vs_pt + appName;
	mu_relpterr_vs_eta = mu_relpterr_vs_eta + appName;

///////////////////////////////////////////////////////////////////

	for(int i=0; i<7; i++){
		el_pull1 [i]= el_pull1 [i]+ appName;
		el_pull2 [i]= el_pull2 [i]+ appName;
		el_pull3 [i]= el_pull3 [i]+ appName;
		el_relpterr [i]= el_relpterr [i]+ appName;
		el_pull1_vs_pt [i]= el_pull1_vs_pt [i]+ appName;
		el_pull2_vs_pt [i]= el_pull2_vs_pt [i]+ appName;
		el_pull3_vs_pt [i]= el_pull3_vs_pt [i]+ appName;
		el_relpterr_vs_pt [i]= el_relpterr_vs_pt [i]+ appName;
		el_pull1_vs_eta [i]= el_pull1_vs_eta [i]+ appName;
		el_pull2_vs_eta [i]= el_pull2_vs_eta [i]+ appName;
		el_pull3_vs_eta [i]= el_pull3_vs_eta [i]+ appName;
		el_relpterr_vs_eta [i]= el_relpterr_vs_eta [i]+ appName;

		el_res1 [i]= el_res1 [i]+ appName;
		el_res2 [i]= el_res2 [i]+ appName;
		el_res3 [i]= el_res3 [i]+ appName;

		el_res1_vs_pt [i]= el_res1_vs_pt [i]+ appName;
		el_res2_vs_pt [i]= el_res2_vs_pt [i]+ appName;
		el_res3_vs_pt [i]= el_res3_vs_pt [i]+ appName;

		el_res1_vs_eta [i]= el_res1_vs_eta [i]+ appName;
		el_res2_vs_eta [i]= el_res2_vs_eta [i]+ appName;
		el_res3_vs_eta [i]= el_res3_vs_eta [i]+ appName;
	}
}


HZZ4LPerLepResolution::~HZZ4LPerLepResolution()
{

}


void HZZ4LPerLepResolution::bookHistograms(edm::Service<TFileService> fs, std::map<TString,TH1F*> &histContainer_, std::map<TString, TH2F*> &hist2DContainer_, std::map<TString, TH3F*> &hist3DContainer_) 
{



//////////////////////

        const int npt = 9; const int neta = 13;

	double ptranges[npt] =  {5, 15, 25, 35, 45, 55, 65, 85, 100};	
	double etaranges[neta] = {0, 0.2, 0.4, 0.6, 0.8, 1.0, 1.2, 1.4, 1.6, 1.8, 2.0, 2.2, 2.5};

/////////////////////
        const int Nres = 200; const int Npull = 2000;

        double resrangeE[Nres+1]; double resrangeM[Nres+1]; 
        double pullrange[Npull+1];

        for(int i = 0; i<=Nres; i++)
         {
           resrangeE[i]=-0.4+i*0.004;
           resrangeM[i]=-0.1+i*0.001;
         }      

        for(int i = 0; i<=Npull; i++)
         {
           pullrange[i]=-10+i*0.01;
         } 

//////////////////////////////

// mu pt err (2d)
	hist2DContainer_[mu_relpterr_vs_eta]=fs->make<TH2F>(mu_relpterr_vs_eta, "muon relative #sigma_{p_{T}}; #eta; #sigma_{p_{T}}/p_{T}",25, 0, 2.5, 200, 0, 1);
	hist2DContainer_[mu_relpterr_vs_pt]=fs->make<TH2F>(mu_relpterr_vs_pt, "muon relative #sigma_{p_{T}}; p_{T}; #sigma_{p_{T}}/p_{T}",50, 0, 100, 200, 0, 1);

// new mu pt err (2d)
	hist2DContainer_[newmu_relpterr_vs_eta]=fs->make<TH2F>(newmu_relpterr_vs_eta, "new muon relative #sigma_{p_{T}}; #eta; #sigma_{p_{T}}/p_{T}",25, 0, 2.5, 200, 0, 1);
	hist2DContainer_[newmu_relpterr_vs_pt]=fs->make<TH2F>(newmu_relpterr_vs_pt, "new muon relative #sigma_{p_{T}}; p_{T}; #sigma_{p_{T}}/p_{T}",50, 0, 100, 200, 0, 1);

        double ptranges_err[25] = {10,12,14,16,18,20,22,24,26,28,30,35,40,45,50,55,60,65,70,75,80,85,90,95,100};
        double etaranges_err[13] = {0, 0.2, 0.4, 0.6, 0.8, 1.0, 1.2, 1.4, 1.6, 1.8, 2.0, 2.2, 2.5}; 

        hist2DContainer_[mu_relpterr2D]
        =fs->make<TH2F>(mu_relpterr2D, "rel pT err of mu; p_{T}^{reco}; |#eta^{reco}|", 24, ptranges_err, 12, etaranges_err);
        hist2DContainer_[el_relpterr2D]
        =fs->make<TH2F>(el_relpterr2D, "rel pT err of el; p_{T}^{reco}; |#eta^{reco}|", 24, ptranges_err, 12, etaranges_err);
        hist2DContainer_[Nmu_relpterr2D]
        =fs->make<TH2F>(Nmu_relpterr2D, "N of mu; p_{T}^{reco}; |#eta^{reco}|", 24, ptranges_err, 12, etaranges_err);
        hist2DContainer_[Nel_relpterr2D]
        =fs->make<TH2F>(Nel_relpterr2D, "N of el; p_{T}^{reco}; |#eta^{reco}|", 24, ptranges_err, 12, etaranges_err);
        //
        hist2DContainer_[newmu_relpterr2D]
        =fs->make<TH2F>(newmu_relpterr2D, "new rel pT err of mu; p_{T}^{reco}; |#eta^{reco}|",24, ptranges_err, 12, etaranges_err);
        hist2DContainer_[newNmu_relpterr2D]
        =fs->make<TH2F>(newNmu_relpterr2D, "new N of mu; p_{T}^{reco}; |#eta^{reco}|",24, ptranges_err, 12, etaranges_err);
        hist2DContainer_[newel_relpterr2D]
        =fs->make<TH2F>(newel_relpterr2D, "new rel pT err of el; p_{T}^{reco}; |#eta^{reco}|",24, ptranges_err, 12, etaranges_err);
        hist2DContainer_[newNel_relpterr2D]
        =fs->make<TH2F>(newNel_relpterr2D, "new N of el; p_{T}^{reco}; |#eta^{reco}|",24, ptranges_err, 12, etaranges_err);
        //

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	histContainer_[mu_relpterr]=fs->make<TH1F>(mu_relpterr, "muon relative #sigma_{p_{T}} ; #sigma_{p_{T}}/p_{T}; N Events", 200, 0, 1);
	histContainer_[newmu_relpterr]=fs->make<TH1F>(newmu_relpterr, "new muon relative #sigma_{p_{T}} ; new #sigma_{p_{T}}/p_{T}; N Events", 200, 0, 1);

//////////////////////////

	hist2DContainer_[mu_pull1_vs_pt]=fs->make<TH2F>(mu_pull1_vs_pt, "pull1 of mu pT; p_{T}^{reco}; (p_{T}^{reco} - p_{T}^{gen})/#sigma_{p_{T}}",50, 0, 100, 200, -10, 10);
	hist2DContainer_[mu_pull3_vs_pt]=fs->make<TH2F>(mu_pull3_vs_pt, "pull3 of mu pT; p_{T}^{reco}; (p_{T}^{reco} - p_{T}^{gen3})/#sigma_{p_{T}}",50, 0, 100, 200, -10, 10);
	hist2DContainer_[mu_pull1_vs_eta]=fs->make<TH2F>(mu_pull1_vs_eta, "pull1 of mu pT; #eta^{reco}; (p_{T}^{reco} - p_{T}^{gen})/#sigma_{p_{T}}",25, 0, 2.5, 200, -10, 10);
	hist2DContainer_[mu_pull3_vs_eta]=fs->make<TH2F>(mu_pull3_vs_eta, "pull3 of mu pT; #eta^{reco}; (p_{T}^{reco} - p_{T}^{gen3})/#sigma_{p_{T}}",25, 0, 2.5, 200, -10, 10);

	hist2DContainer_[mu_res1_vs_pt]=fs->make<TH2F>(mu_res1_vs_pt, "res1 of mu pT; p_{T}^{reco}; (p_{T}^{reco} - p_{T}^{gen})/p_{T}^{gen}}",50, 0, 100, 500,-0.5,0.5);
	hist2DContainer_[mu_res3_vs_pt]=fs->make<TH2F>(mu_res3_vs_pt, "res3 of mu pT; p_{T}^{reco}; (p_{T}^{reco} - p_{T}^{gen3})/p_{T}^{gen3}}",50, 0, 100, 500,-0.5,0.5);
	hist2DContainer_[mu_res1_vs_eta]=fs->make<TH2F>(mu_res1_vs_eta, "res1 of mu pT; #eta^{reco}; (p_{T}^{reco} - p_{T}^{gen})/p_{T}^{gen}}",25, 0, 2.5, 500,-0.5,0.5);
	hist2DContainer_[mu_res3_vs_eta]=fs->make<TH2F>(mu_res3_vs_eta, "res3 of mu pT; #eta^{reco}; (p_{T}^{reco} - p_{T}^{gen3})/p_{T}^{gen3}}",25, 0, 2.5, 500,-0.5,0.5);

        //new
	hist2DContainer_[newmu_pull1_vs_pt]=fs->make<TH2F>(newmu_pull1_vs_pt, "new pull1 of mu pT; p_{T}^{reco}; (p_{T}^{reco} - p_{T}^{gen3})/new #sigma_{p_{T}}",50, 0, 100, 200, -10, 10);
	hist2DContainer_[newmu_pull1_vs_eta]=fs->make<TH2F>(newmu_pull1_vs_eta, "new pull1 of mu pT; #eta^{reco}; (p_{T}^{reco} - p_{T}^{gen})/new #sigma_{p_{T}}",25, 0, 2.5, 200, -10, 10);


// 3d mu pull and err
hist3DContainer_[mu_pull1_vs_pt_eta]=fs->make<TH3F>(mu_pull1_vs_pt_eta, "pull1 of mu pT; p_{T}^{reco}; #eta^{reco}; (p_{T}^{reco} - p_{T}^{gen})/#sigma_{p_{T}}", npt-1, ptranges, neta-1, etaranges, Npull, pullrange );
hist3DContainer_[mu_pull3_vs_pt_eta]=fs->make<TH3F>(mu_pull3_vs_pt_eta, "pull3 of mu pT; p_{T}^{reco}; #eta^{reco}; (p_{T}^{reco} - p_{T}^{gen})/#sigma_{p_{T}}", npt-1, ptranges, neta-1, etaranges, Npull, pullrange );
hist3DContainer_[mu_res1_vs_pt_eta]=fs->make<TH3F>(mu_res1_vs_pt_eta, "res1 of mu pT; p_{T}^{reco}; #eta^{reco}; (p_{T}^{reco} - p_{T}^{gen})/p_{T}^{gen}", npt-1, ptranges, neta-1, etaranges, Nres, resrangeM );

// new
hist3DContainer_[newmu_pull1_vs_pt_eta]=fs->make<TH3F>(newmu_pull1_vs_pt_eta, "new pull1 of mu pT; p_{T}^{reco}; #eta^{reco}; (p_{T}^{reco} - p_{T}^{gen})/new #sigma_{p_{T}}", npt-1, ptranges, neta-1, etaranges, Npull, pullrange );

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/////////////////////
// no ecal electron

//res
	histContainer_[el_res1_nonecal_tracker]=fs->make<TH1F>(el_res1_nonecal_tracker, "res1 of el pT; (p_{T}^{reco} - p_{T}^{gen})/p_{T}^{gen}; N Events", 500,-0.5,0.5);
	histContainer_[el_res1_nonecal]=fs->make<TH1F>(el_res1_nonecal, "res1 of el pT; (p_{T}^{reco} - p_{T}^{gen})/p_{T}^{gen}; N Events", 500,-0.5,0.5);

	histContainer_[el_res3_nonecal_tracker]=fs->make<TH1F>(el_res3_nonecal_tracker, "res3 of el pT; (p_{T}^{reco} - p_{T}^{gen})/p_{T}^{gen}; N Events", 500,-0.5,0.5);
	histContainer_[el_res3_nonecal]=fs->make<TH1F>(el_res3_nonecal, "res3 of el pT; (p_{T}^{reco} - p_{T}^{gen})/p_{T}^{gen}; N Events", 500,-0.5,0.5);

////////////////////
//pull

histContainer_[el_pull1_nonecal_tracker]=fs->make<TH1F>(el_pull1_nonecal_tracker, "pull1 of el pT; (p_{T}^{reco} - p_{T}^{gen})/#sigma_{p_{T}}; N Events", 200, -10, 10);
histContainer_[el_pull1_nonecal_propertracker]=fs->make<TH1F>(el_pull1_nonecal_propertracker, "pull1 of el pT; (p_{T}^{reco} - p_{T}^{gen})/#sigma_{p_{T}}; N Events", 200, -10, 10);
histContainer_[el_pull1_nonecal]=fs->make<TH1F>(el_pull1_nonecal, "pull1 of el pT; (p_{T}^{reco} - p_{T}^{gen})/#sigma_{p_{T}}; N Events", 200, -10, 10);

histContainer_[el_pull3_nonecal_tracker]=fs->make<TH1F>(el_pull3_nonecal_tracker, "pull3 of el pT; (p_{T}^{reco} - p_{T}^{gen})/#sigma_{p_{T}}; N Events", 200, -10, 10);
histContainer_[el_pull3_nonecal_propertracker]=fs->make<TH1F>(el_pull3_nonecal_propertracker, "pull1 of el pT; (p_{T}^{reco} - p_{T}^{gen})/#sigma_{p_{T}}; N Events", 200, -10, 10);
histContainer_[el_pull3_nonecal]=fs->make<TH1F>(el_pull3_nonecal, "pull3 of el pT; (p_{T}^{reco} - p_{T}^{gen})/#sigma_{p_{T}}; N Events", 200, -10, 10);

        // pt err
        //hist2DContainer_[el_pterr_nonecal2D]=fs->make<TH2F>(el_pterr_nonecal2D, "electron relative pterr; pterr; pterr_tracker",200, 0, 1, 200, 0, 1);
	histContainer_[el_pterr_nonecal]=fs->make<TH1F>(el_pterr_nonecal, "el relative #sigma_{p_{T}} ; #sigma_{p_{T}}/p_{T}; N Events", 200, 0, 1);
	histContainer_[el_pterr_nonecal_tracker]=fs->make<TH1F>(el_pterr_nonecal_tracker, "el relative tracker #sigma_{p_{T}} ; #sigma_{p_{T}}/p_{T}; N Events", 200, 0, 1);
        histContainer_[el_pterr_nonecal_propertracker]=fs->make<TH1F>(el_pterr_nonecal_propertracker, "el relative tracker #sigma_{p_{T}} ; #sigma_{p_{T}}/p_{T}; N Events", 200, 0, 1);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        
//3d pull and res
hist3DContainer_[el_pull1_vs_pt_eta]=fs->make<TH3F>(el_pull1_vs_pt_eta, "pull1 of el pT; p_{T}^{reco}; #eta^{reco}; (p_{T}^{reco} - p_{T}^{gen})/#sigma_{p_{T}}", npt-1, ptranges, neta-1, etaranges, Npull, pullrange );
hist3DContainer_[el_pull3_vs_pt_eta]=fs->make<TH3F>(el_pull3_vs_pt_eta, "pull3 of el pT; p_{T}^{reco}; #eta^{reco}; (p_{T}^{reco} - p_{T}^{gen})/#sigma_{p_{T}}", npt-1, ptranges, neta-1, etaranges, Npull, pullrange );
hist3DContainer_[el_res3_vs_pt_eta]=fs->make<TH3F>(el_res3_vs_pt_eta, "res3 of el pT; p_{T}^{reco}; #eta^{reco}; (p_{T}^{reco} - p_{T}^{gen})/p_{T}^{gen}", npt-1, ptranges, neta-1, etaranges, Nres, resrangeE );

//new 3d pull and res
hist3DContainer_[newel_pull3_vs_pt_eta]=fs->make<TH3F>(newel_pull3_vs_pt_eta, "new pull3 of el pT; p_{T}^{reco}; #eta^{reco}; (p_{T}^{reco} - p_{T}^{gen})/new #sigma_{p_{T}}", npt-1, ptranges, neta-1, etaranges, Npull, pullrange );

///////////////////////////////////////////

	for(int i=0; i<7; i++){
                //all 

		histContainer_[el_relpterr[i]]=fs->make<TH1F>(el_relpterr[i], "ele relative #sigma_{p_{T}} ; #sigma_{p_{T}}/p_{T}; N Events", 200, 0, 1);

                //new all

		histContainer_[newel_relpterr[i]]=fs->make<TH1F>(newel_relpterr[i], "new ele relative #sigma_{p_{T}} ; new #sigma_{p_{T}}/p_{T}; N Events", 200, 0, 1);

                //pull 
		hist2DContainer_[el_pull1_vs_pt[i]]=fs->make<TH2F>(el_pull1_vs_pt[i], "pull1 of ele pT; p_{T}^{reco}; (p_{T}^{reco} - p_{T}^{gen})/#sigma_{p_{T}}",50, 0, 100, 200, -10, 10);
		hist2DContainer_[el_pull3_vs_pt[i]]=fs->make<TH2F>(el_pull3_vs_pt[i], "pull3 of ele pT; p_{T}^{reco}; (p_{T}^{reco} - p_{T}^{gen3})/#sigma_{p_{T}}",50, 0, 100, 200, -10, 10);
		hist2DContainer_[el_relpterr_vs_pt[i]]=fs->make<TH2F>(el_relpterr_vs_pt[i], "ele relative #sigma_{p_{T}}; p_{T}; #sigma_{p_{T}}/p_{T}",500, 0, 100, 200, 0, 1);

		hist2DContainer_[el_pull1_vs_eta[i]]=fs->make<TH2F>(el_pull1_vs_eta[i], "pull1 of ele pT; #eta^{reco}; (p_{T}^{reco} - p_{T}^{gen})/#sigma_{p_{T}}",25, 0, 2.5, 200, -10, 10);
		hist2DContainer_[el_pull3_vs_eta[i]]=fs->make<TH2F>(el_pull3_vs_eta[i], "pull3 of ele pT; #eta^{reco}; (p_{T}^{reco} - p_{T}^{gen3})/#sigma_{p_{T}}",25, 0, 2.5, 200, -10, 10);
		hist2DContainer_[el_relpterr_vs_eta[i]]=fs->make<TH2F>(el_relpterr_vs_eta[i], "ele relative #sigma_{p_{T}}; #eta; #sigma_{p_{T}}/p_{T}",50, 0, 2.5, 200, 0, 1);
           
                //new pull
		hist2DContainer_[newel_pull3_vs_pt[i]]=fs->make<TH2F>(newel_pull3_vs_pt[i], "new pull3 of ele pT; p_{T}^{reco}; (p_{T}^{reco} - p_{T}^{gen3})/new #sigma_{p_{T}}",50, 0, 100, 200, -10, 10);
		hist2DContainer_[newel_relpterr_vs_pt[i]]=fs->make<TH2F>(newel_relpterr_vs_pt[i], "ele relative #sigma_{p_{T}}; p_{T}; new #sigma_{p_{T}}/p_{T}",500, 0, 100, 200, 0, 1);

		hist2DContainer_[newel_pull3_vs_eta[i]]=fs->make<TH2F>(newel_pull3_vs_eta[i], "new pull3 of ele pT; #eta^{reco}; (p_{T}^{reco} - p_{T}^{gen3})/new #sigma_{p_{T}}",25, 0, 2.5, 200, -10, 10);
		hist2DContainer_[newel_relpterr_vs_eta[i]]=fs->make<TH2F>(newel_relpterr_vs_eta[i], "new ele relative #sigma_{p_{T}}; #eta; new #sigma_{p_{T}}/p_{T}",50, 0, 2.5, 200, 0, 1);

                //res
                //hist2DContainer_[el_res1_vs_pt[i]]=fs->make<TH2F>(el_res1_vs_pt[i], "res1 of ele pT; p_{T}^{reco}; (p_{T}^{reco} - p_{T}^{gen})/p_{T}^{gen}",50, 0, 100, 500,-0.5,0.5);
                hist2DContainer_[el_res3_vs_pt[i]]=fs->make<TH2F>(el_res3_vs_pt[i], "res3 of ele pT; p_{T}^{reco}; (p_{T}^{reco} - p_{T}^{gen3})/p_{T}^{gen3}",50, 0, 100, 500,-0.5,0.5);

                //hist2DContainer_[el_res1_vs_eta[i]]=fs->make<TH2F>(el_res1_vs_eta[i], "res1 of ele pT; #eta^{reco}; (p_{T}^{reco} - p_{T}^{gen})/p_{T}^{gen}",25, 0, 2.5, 500,-0.5,0.5);
                hist2DContainer_[el_res3_vs_eta[i]]=fs->make<TH2F>(el_res3_vs_eta[i], "res3 of ele pT; #eta^{reco}; (p_{T}^{reco} - p_{T}^{gen3})/p_{T}^{gen3}",25, 0, 2.5, 500,-0.5,0.5);


	}
}

void HZZ4LPerLepResolution::fillHistograms(std::map<TString,TH1F*> &histContainer_, std::map<TString, TH2F*> &hist2DContainer_, std::map<TString, TH3F*> &hist3DContainer_, std::vector< pat::Electron > electrons, std::vector< pat::Muon > muons, double evtWeight, bool isData)
{

	for(unsigned int i=0; i< electrons.size(); i++){
		const pat::Electron *e = &(electrons[i]);

                if(!e->gsfTrack()){ cout<<"electron has no gsf"<<endl; continue;}  
		double perr = e->p4Error(reco::GsfElectron::P4_COMBINATION);

		double pterr = perr*e->pt()/e->p();
                double pterr_tracker = perr*e->pt()/e->p();
                double pterr_propertracker = e->gsfTrack()->ptModeError();

		if(perr>=998){
			pterr_tracker = e->gsfTrack()->ptError();
		}
               if (e->ecalDriven()) {
                perr = e->p4Error(reco::GsfElectron::P4_COMBINATION);
               } 
               else {

              // Parametrization from Claude Charlot, 
              // http://cmssw.cvs.cern.ch/cgi-bin/cmssw.cgi/UserCode/CJLST/ZZAnalysis/AnalysisStep/src/ZZMassErrors.cc?revision=1.2&view=markup
#if CMSSW_VERSION<500
                  double ecalEnergy = e->ecalEnergy() ;
#else
                  double ecalEnergy = e->correctedEcalEnergy() ;
#endif
                  double err2 = 0.0;
                  if (e->isEB()) {
                  err2 += (5.24e-02*5.24e-02)/ecalEnergy;  
                  err2 += (2.01e-01*2.01e-01)/(ecalEnergy*ecalEnergy);
                  err2 += 1.00e-02*1.00e-02;
                  } else if (e->isEE()) {
                  err2 += (1.46e-01*1.46e-01)/ecalEnergy;  
                  err2 += (9.21e-01*9.21e-01)/(ecalEnergy*ecalEnergy);
                  err2 += 1.94e-03*1.94e-03;
                  }
                  perr = ecalEnergy * sqrt(err2);
              }                

/////////////////////////////////////////////////////////////////////////////////////////////////////// 
                pterr = perr*e->pt()/e->p();

        TH2F* el_corr;

        if(isData) el_corr = dynamic_cast<TH2F*>(electron_corr_data->Clone());
        else el_corr = dynamic_cast<TH2F*>(electron_corr_mc->Clone());

        TAxis* x_elpTaxis = el_corr->GetXaxis(); TAxis* y_eletaaxis = el_corr->GetYaxis();
        double maxPt = x_elpTaxis->GetXmax(); double minPt = x_elpTaxis->GetXmin();

        double scaleFactor_el = 1.0;
        int xbin = x_elpTaxis->FindBin(e->pt()); int ybin = y_eletaaxis->FindBin(fabs(e->eta()));
        if( e->pt()>minPt && e->pt()<maxPt ) scaleFactor_el = el_corr->GetBinContent(xbin,ybin);

        double newpterr = scaleFactor_el*pterr;

		double recpt = e->pt();
		double eta = e->eta();

		double pt1 = 0, pt3 = 0; // pt2=0;
		pt1 = matchedGenElectronPt(e);
		pt3 = matchedGen3ElectronPt(e);
		//pt2 = matchedGen2ElectronPt(e);
               
                hist2DContainer_[el_relpterr2D]->Fill(recpt, fabs(eta), evtWeight*pterr/recpt);
                hist2DContainer_[newel_relpterr2D]->Fill(recpt, fabs(eta), evtWeight*newpterr/recpt);
                hist2DContainer_[Nel_relpterr2D]->Fill(recpt, fabs(eta),evtWeight);

		int cat = e->classification()+2;
		histContainer_[el_relpterr[cat]]->Fill(pterr/recpt, evtWeight);
		hist2DContainer_[el_relpterr_vs_eta[cat]]->Fill(fabs(eta),pterr/recpt,evtWeight);
		hist2DContainer_[el_relpterr_vs_pt[cat]]->Fill(recpt,pterr/recpt,evtWeight);
		histContainer_[el_relpterr[0]]->Fill(pterr/recpt, evtWeight);
		hist2DContainer_[el_relpterr_vs_eta[0]]->Fill(fabs(eta),pterr/recpt,evtWeight);
		hist2DContainer_[el_relpterr_vs_pt[0]]->Fill(recpt,pterr/recpt,evtWeight);
                ////////
		histContainer_[newel_relpterr[cat]]->Fill(newpterr/recpt, evtWeight);
		hist2DContainer_[newel_relpterr_vs_eta[cat]]->Fill(fabs(eta),newpterr/recpt,evtWeight);
		hist2DContainer_[newel_relpterr_vs_pt[cat]]->Fill(recpt,newpterr/recpt,evtWeight);
		histContainer_[newel_relpterr[0]]->Fill(newpterr/recpt, evtWeight);
		hist2DContainer_[newel_relpterr_vs_eta[0]]->Fill(fabs(eta),newpterr/recpt,evtWeight);
		hist2DContainer_[newel_relpterr_vs_pt[0]]->Fill(recpt,newpterr/recpt,evtWeight);

               if (e->ecalDriven())
             {

		if(pt1>0) {
 
                        //cout<<"el pt1"<<endl;

			//histContainer_[el_pull1[cat]]->Fill((recpt-pt1)/pterr, evtWeight);
			hist2DContainer_[el_pull1_vs_eta[cat]]->Fill(fabs(eta),(recpt-pt1)/pterr,evtWeight);
			hist2DContainer_[el_pull1_vs_pt[cat]]->Fill(recpt,(recpt-pt1)/pterr,evtWeight);
			//histContainer_[el_pull1[0]]->Fill((recpt-pt1)/pterr, evtWeight);
			hist2DContainer_[el_pull1_vs_eta[0]]->Fill(fabs(eta),(recpt-pt1)/pterr,evtWeight);
			hist2DContainer_[el_pull1_vs_pt[0]]->Fill(recpt,(recpt-pt1)/pterr,evtWeight);

                        //histContainer_[el_res1[cat]]->Fill((recpt-pt1)/pterr, evtWeight);
                        //hist2DContainer_[el_res1_vs_eta[cat]]->Fill(fabs(eta),(recpt-pt1)/pt1,evtWeight);
                        //hist2DContainer_[el_res1_vs_pt[cat]]->Fill(recpt,(recpt-pt1)/pt1,evtWeight);
                        //histContainer_[el_res1[0]]->Fill((recpt-pt1)/pterr, evtWeight);
                        //hist2DContainer_[el_res1_vs_eta[0]]->Fill(fabs(eta),(recpt-pt1)/pt1,evtWeight);
                        //hist2DContainer_[el_res1_vs_pt[0]]->Fill(recpt,(recpt-pt1)/pt1,evtWeight);

                       // for 3d pull and res 
                       hist3DContainer_[el_pull1_vs_pt_eta]->Fill(recpt,fabs(eta),(recpt-pt1)/pterr,evtWeight);  
                       //hist3DContainer_[el_res1_vs_pt_eta]->Fill(recpt,fabs(eta),(recpt-pt1)/pt1,evtWeight); 
                       //hist3DContainer_[el_pull1_vs_pt_eta_propertracker]->Fill(recpt,fabs(eta),(recpt-pt1)/pterr,evtWeight);                              
		}
                /*
		if(pt2>0) {

			histContainer_[el_pull2[cat]]->Fill((recpt-pt2)/pterr, evtWeight);
			hist2DContainer_[el_pull2_vs_eta[cat]]->Fill(fabs(eta),(recpt-pt2)/pterr,evtWeight);
			hist2DContainer_[el_pull2_vs_pt[cat]]->Fill(recpt,(recpt-pt2)/pterr,evtWeight);
			histContainer_[el_pull2[0]]->Fill((recpt-pt2)/pterr, evtWeight);
			hist2DContainer_[el_pull2_vs_eta[0]]->Fill(fabs(eta),(recpt-pt2)/pterr,evtWeight);
			hist2DContainer_[el_pull2_vs_pt[0]]->Fill(recpt,(recpt-pt2)/pterr,evtWeight);

                        hist2DContainer_[el_res2_vs_eta[cat]]->Fill(fabs(eta),(recpt-pt2)/pt2,evtWeight);
                        hist2DContainer_[el_res2_vs_pt[cat]]->Fill(recpt,(recpt-pt2)/pt2,evtWeight);
                        //histContainer_[el_res2[0]]->Fill((recpt-pt2)/pterr, evtWeight);
                        hist2DContainer_[el_res2_vs_eta[0]]->Fill(fabs(eta),(recpt-pt2)/pt2,evtWeight);
                        hist2DContainer_[el_res2_vs_pt[0]]->Fill(recpt,(recpt-pt2)/pt2,evtWeight);

                        // for 2d pull and res 
		}
                */
		if(pt3>0) {

                        //cout<<"el pt3"<<endl;

			//histContainer_[el_pull3[cat]]->Fill((recpt-pt3)/pterr, evtWeight);
			hist2DContainer_[el_pull3_vs_eta[cat]]->Fill(fabs(eta),(recpt-pt3)/pterr, evtWeight);
			hist2DContainer_[el_pull3_vs_pt[cat]]->Fill(recpt,(recpt-pt3)/pterr, evtWeight);
			//histContainer_[el_pull3[0]]->Fill((recpt-pt3)/pterr, evtWeight);
			hist2DContainer_[el_pull3_vs_eta[0]]->Fill(fabs(eta),(recpt-pt3)/pterr, evtWeight);
			hist2DContainer_[el_pull3_vs_pt[0]]->Fill(recpt,(recpt-pt3)/pterr, evtWeight);

                        //histContainer_[el_res3[cat]]->Fill((recpt-pt3)/pt3, evtWeight);
                        hist2DContainer_[el_res3_vs_eta[cat]]->Fill(fabs(eta),(recpt-pt3)/pt3, evtWeight);
                        hist2DContainer_[el_res3_vs_pt[cat]]->Fill(recpt,(recpt-pt3)/pt3, evtWeight);
                        //histContainer_[el_res3[0]]->Fill((recpt-pt3)/pt3, evtWeight);
                        hist2DContainer_[el_res3_vs_eta[0]]->Fill(fabs(eta),(recpt-pt3)/pt3, evtWeight);
                        hist2DContainer_[el_res3_vs_pt[0]]->Fill(recpt,(recpt-pt3)/pt3, evtWeight);

                        ///////new
			//histContainer_[newel_pull3[cat]]->Fill((recpt-pt3)/newpterr, evtWeight);
			hist2DContainer_[newel_pull3_vs_eta[cat]]->Fill(fabs(eta),(recpt-pt3)/newpterr, evtWeight);
			hist2DContainer_[newel_pull3_vs_pt[cat]]->Fill(recpt,(recpt-pt3)/newpterr, evtWeight);
			//histContainer_[newel_pull3[0]]->Fill((recpt-pt3)/newpterr, evtWeight);
			hist2DContainer_[newel_pull3_vs_eta[0]]->Fill(fabs(eta),(recpt-pt3)/newpterr, evtWeight);
			hist2DContainer_[newel_pull3_vs_pt[0]]->Fill(recpt,(recpt-pt3)/newpterr, evtWeight);

                       // for 3d pull and res
 
                       hist3DContainer_[el_pull3_vs_pt_eta]->Fill(recpt,fabs(eta),(recpt-pt3)/pterr, evtWeight);
                       hist3DContainer_[newel_pull3_vs_pt_eta]->Fill(recpt,fabs(eta),(recpt-pt3)/newpterr, evtWeight);
                       hist3DContainer_[el_res3_vs_pt_eta]->Fill(recpt,fabs(eta),(recpt-pt3)/pt3, evtWeight);
                       //hist3DContainer_[el_pull3_vs_pt_eta_propertracker]->Fill(recpt,fabs(eta),(recpt-pt3)/pterr,evtWeight);

		 }

              }
             else 
             {

               //hist2DContainer_[el_pterr_nonecal2D]->Fill((pterr/recpt), (pterr_tracker/recpt), evtWeight);
	       histContainer_[el_pterr_nonecal]->Fill((pterr/recpt), evtWeight);
	       histContainer_[el_pterr_nonecal_tracker]->Fill((pterr_tracker/recpt), evtWeight);
               histContainer_[el_pterr_nonecal_propertracker]->Fill((pterr_propertracker/recpt), evtWeight);              
 
               /////////////////////
               // pt pull and res
               if(pt1>0) {

                  ////cout<<"el pt1"<<endl;

	          histContainer_[el_res1_nonecal_tracker]->Fill((recpt-pt1)/pt1,evtWeight);
                  histContainer_[el_res1_nonecal]->Fill((recpt-pt1)/pt1,evtWeight);

                  histContainer_[el_pull1_nonecal_tracker]->Fill((recpt-pt1)/pterr_tracker, evtWeight);
                  histContainer_[el_pull1_nonecal_propertracker]->Fill((recpt-pt1)/pterr_propertracker, evtWeight);
                  histContainer_[el_pull1_nonecal]->Fill((recpt-pt1)/pterr, evtWeight);

////////////////////////////

                  //histContainer_[el_pull1[cat]]->Fill((recpt-pt1)/pterr, evtWeight);
                  hist2DContainer_[el_pull1_vs_eta[cat]]->Fill(fabs(eta),(recpt-pt1)/pterr,evtWeight);
                  hist2DContainer_[el_pull1_vs_pt[cat]]->Fill(recpt,(recpt-pt1)/pterr,evtWeight);
                  //histContainer_[el_pull1[0]]->Fill((recpt-pt1)/pterr, evtWeight);
                  hist2DContainer_[el_pull1_vs_eta[0]]->Fill(fabs(eta),(recpt-pt1)/pterr,evtWeight);
                  hist2DContainer_[el_pull1_vs_pt[0]]->Fill(recpt,(recpt-pt1)/pterr,evtWeight);

                  //histContainer_[el_res1[cat]]->Fill((recpt-pt1)/pterr, evtWeight);
                  //hist2DContainer_[el_res1_vs_eta[cat]]->Fill(fabs(eta),(recpt-pt1)/pt1,evtWeight);
                  //hist2DContainer_[el_res1_vs_pt[cat]]->Fill(recpt,(recpt-pt1)/pt1,evtWeight);
                  //histContainer_[el_res1[0]]->Fill((recpt-pt1)/pterr, evtWeight);
                  //hist2DContainer_[el_res1_vs_eta[0]]->Fill(fabs(eta),(recpt-pt1)/pt1,evtWeight);
                  //hist2DContainer_[el_res1_vs_pt[0]]->Fill(recpt,(recpt-pt1)/pt1,evtWeight);
////////////////////////////

                  // for 3d pull and res
                  hist3DContainer_[el_pull1_vs_pt_eta]->Fill(recpt,fabs(eta),(recpt-pt1)/pterr,evtWeight);
                  //hist3DContainer_[el_res1_vs_pt_eta]->Fill(recpt,fabs(eta),(recpt-pt1)/pt1,evtWeight);
                  //hist3DContainer_[el_pull1_vs_pt_eta_propertracker]->Fill(recpt,fabs(eta),(recpt-pt1)/pterr_propertracker,evtWeight);

                }
               /*
               if(pt2>0) {

	          histContainer_[el_res2_nonecal_tracker]->Fill((recpt-pt2)/pt2,evtWeight);
	          histContainer_[el_res2_nonecal]->Fill((recpt-pt2)/pt2,evtWeight);

                  histContainer_[el_pull2_nonecal_tracker]->Fill((recpt-pt2)/pterr_tracker, evtWeight);
                  histContainer_[el_pull2_nonecal_propertracker]->Fill((recpt-pt2)/pterr_propertracker, evtWeight);
                  histContainer_[el_pull2_nonecal]->Fill((recpt-pt2)/pterr, evtWeight);
/////////////////////////////////

                  histContainer_[el_pull2[cat]]->Fill((recpt-pt2)/pterr, evtWeight);
                  hist2DContainer_[el_pull2_vs_eta[cat]]->Fill(fabs(eta),(recpt-pt2)/pterr,evtWeight);
                  hist2DContainer_[el_pull2_vs_pt[cat]]->Fill(recpt,(recpt-pt2)/pterr,evtWeight);
                  histContainer_[el_pull2[0]]->Fill((recpt-pt2)/pterr, evtWeight);
                  hist2DContainer_[el_pull2_vs_eta[0]]->Fill(fabs(eta),(recpt-pt2)/pterr,evtWeight);
                  hist2DContainer_[el_pull2_vs_pt[0]]->Fill(recpt,(recpt-pt2)/pterr,evtWeight);

                  hist2DContainer_[el_res2_vs_eta[cat]]->Fill(fabs(eta),(recpt-pt2)/pt2,evtWeight);
                  hist2DContainer_[el_res2_vs_pt[cat]]->Fill(recpt,(recpt-pt2)/pt2,evtWeight);
                  //histContainer_[el_res2[0]]->Fill((recpt-pt2)/pterr, evtWeight);
                  hist2DContainer_[el_res2_vs_eta[0]]->Fill(fabs(eta),(recpt-pt2)/pt2,evtWeight);
                  hist2DContainer_[el_res2_vs_pt[0]]->Fill(recpt,(recpt-pt2)/pt2,evtWeight);
                }
                */

               if(pt3>0) {

                  //cout<<"el pt3"<<endl;

	          histContainer_[el_res3_nonecal_tracker]->Fill((recpt-pt3)/pt3, evtWeight);
	          histContainer_[el_res3_nonecal]->Fill((recpt-pt3)/pt3, evtWeight);

                  histContainer_[el_pull3_nonecal_tracker]->Fill((recpt-pt3)/pterr_tracker, evtWeight);
                  histContainer_[el_pull3_nonecal_propertracker]->Fill((recpt-pt3)/pterr_propertracker, evtWeight);
                  histContainer_[el_pull3_nonecal]->Fill((recpt-pt3)/pterr, evtWeight);
          
//////////////////////////////

                  //histContainer_[el_pull3[cat]]->Fill((recpt-pt3)/pterr, evtWeight);
                  hist2DContainer_[el_pull3_vs_eta[cat]]->Fill(fabs(eta),(recpt-pt3)/pterr, evtWeight);
                  hist2DContainer_[el_pull3_vs_pt[cat]]->Fill(recpt,(recpt-pt3)/pterr, evtWeight);
                  //histContainer_[el_pull3[0]]->Fill((recpt-pt3)/pterr, evtWeight);
                  hist2DContainer_[el_pull3_vs_eta[0]]->Fill(fabs(eta),(recpt-pt3)/pterr, evtWeight);
                  hist2DContainer_[el_pull3_vs_pt[0]]->Fill(recpt,(recpt-pt3)/pterr, evtWeight);

                  //histContainer_[el_res3[cat]]->Fill((recpt-pt3)/pt3, evtWeight);
                  hist2DContainer_[el_res3_vs_eta[cat]]->Fill(fabs(eta),(recpt-pt3)/pt3, evtWeight);
                  hist2DContainer_[el_res3_vs_pt[cat]]->Fill(recpt,(recpt-pt3)/pt3,evtWeight);
                  //histContainer_[el_res3[0]]->Fill((recpt-pt3)/pt3, evtWeight);
                  hist2DContainer_[el_res3_vs_eta[0]]->Fill(fabs(eta),(recpt-pt3)/pt3, evtWeight);
                  hist2DContainer_[el_res3_vs_pt[0]]->Fill(recpt,(recpt-pt3)/pt3, evtWeight);

/////////////////////////////

                  //histContainer_[newel_pull3[cat]]->Fill((recpt-pt3)/newpterr, evtWeight);
                  hist2DContainer_[newel_pull3_vs_eta[cat]]->Fill(fabs(eta),(recpt-pt3)/newpterr, evtWeight);
                  hist2DContainer_[newel_pull3_vs_pt[cat]]->Fill(recpt,(recpt-pt3)/newpterr, evtWeight);
                  //histContainer_[newel_pull3[0]]->Fill((recpt-pt3)/newpterr, evtWeight);
                  hist2DContainer_[newel_pull3_vs_eta[0]]->Fill(fabs(eta),(recpt-pt3)/newpterr, evtWeight);
                  hist2DContainer_[newel_pull3_vs_pt[0]]->Fill(recpt,(recpt-pt3)/newpterr, evtWeight);

                  //3d pull and res 

                  hist3DContainer_[el_pull3_vs_pt_eta]->Fill(recpt,fabs(eta),(recpt-pt3)/pterr, evtWeight);  
                  hist3DContainer_[el_res3_vs_pt_eta]->Fill(recpt,fabs(eta),(recpt-pt3)/pt3, evtWeight); 
                  hist3DContainer_[newel_pull3_vs_pt_eta]->Fill(recpt,fabs(eta),(recpt-pt3)/newpterr,evtWeight);  
                  //hist3DContainer_[el_pull3_vs_pt_eta_propertracker]->Fill(recpt,fabs(eta),(recpt-pt1)/pterr_propertracker,evtWeight);
                }

             }

	}


	for(unsigned int i=0; i< muons.size(); i++){
		const pat::Muon *e = &(muons[i]);
                if(!e->muonBestTrack()){ cout<<"muon has no tracker"<<endl; continue;} // miniAOD

		double pterr = e->muonBestTrack()->ptError();  // miniAOD
		double recpt = e->pt();
		double eta = e->eta();

                TH2F* mu_corr;

               if(isData) mu_corr = dynamic_cast<TH2F*>(muon_corr_data->Clone());
               else mu_corr = dynamic_cast<TH2F*>(muon_corr_mc->Clone());

               TAxis* x_mupTaxis = mu_corr->GetXaxis(); TAxis* y_muetaaxis = mu_corr->GetYaxis();
               double maxPt = x_mupTaxis->GetXmax(); double minPt = x_mupTaxis->GetXmin();

               double scaleFactor_mu = 1.0;
               int xbin = x_mupTaxis->FindBin(e->pt()); int ybin = y_muetaaxis->FindBin(fabs(e->eta()));
               if( e->pt()>minPt && e->pt()<maxPt ) scaleFactor_mu = mu_corr->GetBinContent(xbin,ybin);
               double newpterr = scaleFactor_mu*pterr;

                hist2DContainer_[mu_relpterr2D]->Fill(recpt,fabs(eta),evtWeight*pterr/recpt);
                hist2DContainer_[newmu_relpterr2D]->Fill(recpt,fabs(eta),evtWeight*newpterr/recpt);
                hist2DContainer_[Nmu_relpterr2D]->Fill(recpt,fabs(eta),evtWeight);
                hist2DContainer_[newNmu_relpterr2D]->Fill(recpt,fabs(eta),evtWeight);

		histContainer_[mu_relpterr]->Fill(pterr/recpt, evtWeight);
		hist2DContainer_[mu_relpterr_vs_eta]->Fill(fabs(eta),pterr/recpt,evtWeight);
		hist2DContainer_[mu_relpterr_vs_pt]->Fill(recpt,pterr/recpt,evtWeight);

		histContainer_[newmu_relpterr]->Fill(newpterr/recpt, evtWeight);
		hist2DContainer_[newmu_relpterr_vs_eta]->Fill(fabs(eta),newpterr/recpt,evtWeight);
		hist2DContainer_[newmu_relpterr_vs_pt]->Fill(recpt,newpterr/recpt,evtWeight);

		double pt1 = 0, pt3 = 0;
		pt1 = matchedGenMuonPt(e);
		pt3 = matchedGen3MuonPt(e);                 
                
		if(pt1>0) {
  
                        //cout<<"mu pt1"<<endl;

			//histContainer_[mu_pull1]->Fill((recpt-pt1)/pterr, evtWeight);
			hist2DContainer_[mu_pull1_vs_eta]->Fill(fabs(eta),(recpt-pt1)/pterr,evtWeight);
			hist2DContainer_[mu_pull1_vs_pt]->Fill(recpt,(recpt-pt1)/pterr,evtWeight);

			//histContainer_[newmu_pull1]->Fill((recpt-pt1)/newpterr, evtWeight);
			hist2DContainer_[newmu_pull1_vs_eta]->Fill(fabs(eta),(recpt-pt1)/newpterr,evtWeight);
			hist2DContainer_[newmu_pull1_vs_pt]->Fill(recpt,(recpt-pt1)/newpterr,evtWeight);

			//histContainer_[mu_res1]->Fill((recpt-pt1)/pt1, evtWeight);
			hist2DContainer_[mu_res1_vs_eta]->Fill(fabs(eta),(recpt-pt1)/pt1,evtWeight);
			hist2DContainer_[mu_res1_vs_pt]->Fill(recpt,(recpt-pt1)/pt1,evtWeight);
  
                       // for 3d pull and res 
                        hist3DContainer_[mu_pull1_vs_pt_eta]->Fill(recpt,fabs(eta),(recpt-pt1)/pterr, evtWeight);
                        hist3DContainer_[newmu_pull1_vs_pt_eta]->Fill(recpt,fabs(eta),(recpt-pt1)/newpterr, evtWeight);  
                      
		   }

		if(pt3>0) {

                        //cout<<"mu pt3"<<endl;

			//histContainer_[mu_pull3]->Fill((recpt-pt3)/pterr, evtWeight);
			hist2DContainer_[mu_pull3_vs_eta]->Fill(fabs(eta),(recpt-pt3)/pterr,evtWeight);
			hist2DContainer_[mu_pull3_vs_pt]->Fill(recpt,(recpt-pt3)/pterr,evtWeight);

			//histContainer_[mu_res3]->Fill((recpt-pt3)/pt3, evtWeight);
			hist2DContainer_[mu_res3_vs_eta]->Fill(fabs(eta),(recpt-pt3)/pt3,evtWeight);
			hist2DContainer_[mu_res3_vs_pt]->Fill(recpt,(recpt-pt3)/pt3,evtWeight);

                        hist3DContainer_[mu_pull3_vs_pt_eta]->Fill(recpt,fabs(eta),(recpt-pt3)/pterr, evtWeight);

		  }
        
	}

//   cout<<"fill perlep histos done"<<endl;
}


void HZZ4LPerLepResolution::plotHistograms(std::map<TString,TH1F*> &histContainer_ , bool weightEvents, double scaleWeight)
{

	if(weightEvents)
	{

		//      if(histContainer_[pt1_4mu]->GetEntries() > 0){histContainer_[pt1_4mu]->Scale(scaleWeight);}
	}

}
double HZZ4LPerLepResolution::matchedGenElectronPt(const pat::Electron *e){
	for(unsigned int j = 0 ; j < e->genParticleRefs().size() ; j++ ){
		if( e->genParticle(j)->status() == 1 && fabs(e->genParticle(j)->pdgId()) == 11 ){
			return e->genParticle(j)->pt();
		}
	}
	return 0;
}
double HZZ4LPerLepResolution::matchedGen2ElectronPt(const pat::Electron *e){
	for(unsigned int j = 0 ; j < e->genParticleRefs().size() ; j++ ){
		if( e->genParticle(j)->status() == 1 && fabs(e->genParticle(j)->pdgId()) == 11 ){
			if(fabs(e->genParticle(j)->mother()->pdgId())==11){return e->genParticle(j)->mother()->pt();}
		}
	}
	return 0;
}
double HZZ4LPerLepResolution::matchedGen3ElectronPt(const pat::Electron *e){
	for(unsigned int j = 0 ; j < e->genParticleRefs().size() ; j++ ){
		if( e->genParticle(j)->status() == 1 && fabs(e->genParticle(j)->pdgId()) == 11 ){
			if(fabs(e->genParticle(j)->mother()->pdgId())==11 and e->genParticle(j)->mother()->status()==3){return e->genParticle(j)->mother()->pt();}
			if(fabs(e->genParticle(j)->mother()->mother()->pdgId())==11 and e->genParticle(j)->mother()->mother()->status()==3){return e->genParticle(j)->mother()->mother()->pt();}
			if(fabs(e->genParticle(j)->mother()->mother()->mother()->pdgId())==11 and e->genParticle(j)->mother()->mother()->mother()->status()==3){return e->genParticle(j)->mother()->mother()->mother()->pt();}
			if(fabs(e->genParticle(j)->mother()->mother()->mother()->mother()->pdgId())==11 and e->genParticle(j)->mother()->mother()->mother()->mother()->status()==3){return e->genParticle(j)->mother()->mother()->mother()->mother()->pt();}
		}
	}
	return 0;
}
double HZZ4LPerLepResolution::matchedGenMuonPt(const pat::Muon *e){
	for(unsigned int j = 0 ; j < e->genParticleRefs().size() ; j++ ){
		if( e->genParticle(j)->status() == 1 && fabs(e->genParticle(j)->pdgId()) == 13 ){
			return e->genParticle(j)->pt();
		}
	}
	return 0;
}
double HZZ4LPerLepResolution::matchedGen3MuonPt(const pat::Muon *e){
	for(unsigned int j = 0 ; j < e->genParticleRefs().size() ; j++ ){
		if( e->genParticle(j)->status() == 1 && fabs(e->genParticle(j)->pdgId()) == 13 ){
			if(fabs(e->genParticle(j)->mother()->pdgId())==13 and e->genParticle(j)->mother()->status()==3){return e->genParticle(j)->mother()->pt();}
			if(fabs(e->genParticle(j)->mother()->mother()->pdgId())==13 and e->genParticle(j)->mother()->mother()->status()==3){return e->genParticle(j)->mother()->mother()->pt();}
			if(fabs(e->genParticle(j)->mother()->mother()->mother()->pdgId())==13 and e->genParticle(j)->mother()->mother()->mother()->status()==3){return e->genParticle(j)->mother()->mother()->mother()->pt();}
			if(fabs(e->genParticle(j)->mother()->mother()->mother()->mother()->pdgId())==13 and e->genParticle(j)->mother()->mother()->mother()->mother()->status()==3){return e->genParticle(j)->mother()->mother()->mother()->mother()->pt();}
		}
	}
	return 0;
}

#endif
