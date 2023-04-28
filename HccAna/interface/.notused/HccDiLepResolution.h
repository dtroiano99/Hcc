#ifndef HZZ4LDILEPRESOLUTION_H
#define HZZ4LDILEPRESOLUTION_H

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

class HZZ4LDiLepResolution
{

	public:

	HZZ4LDiLepResolution();
	void SetAppendName(TString appendName);
	~HZZ4LDiLepResolution();

	void bookHistograms(edm::Service<TFileService> fs, std::map<TString,TH1F*> &histContainer_, std::map<TString, TH2F*> &hist2DContainer_);
	void fillHistograms(std::map<TString,TH1F*> &histContainer_, std::map<TString, TH2F*> &hist2DContainer_, std::vector< pat::Electron > electrons, std::vector< pat::Muon > muons, double evtWeight, bool isData);
	void plotHistograms(std::map<TString,TH1F*> &histContainer_, bool weightEvents, double scaleWeight);

	double matchedGENDiLepMass(const pat::Muon *e1, const pat::Muon *e2);
	double matchedGEN3DiLepMass(const pat::Muon *e1, const pat::Muon *e2);
	double matchedGENDiLepMass(const pat::Electron *e1, const pat::Electron *e2);
	double matchedGEN3DiLepMass(const pat::Electron *e1, const pat::Electron *e2);

	private:

	TString  appName;
	TString  ZmmMassVsErr, ZeeMassVsErr, ZmmMassPull, ZeeMassPull, ZmmMassPull3, ZeeMassPull3, ZeeMassPull3AD;
        TString ZeeMass1, ZmmMass1, ZeeMass3, ZmmMass3; 
	HZZ4LMassErr massErr;

	TString ZmmMassRes, ZeeMassRes, ZmmMassRes3, ZeeMassRes3;

	TString  newZmmMassVsErr, newZeeMassVsErr, newZmmMassPull, newZeeMassPull, newZmmMassPull3, newZeeMassPull3;
	TString newZmmMassRes, newZeeMassRes, newZmmMassRes3, newZeeMassRes3;

        TString  ZmmMassVsRelErr, ZeeMassVsRelErr, ZeeMassVsRelErrAD, newZmmMassVsRelErr, newZeeMassVsRelErr; 
        TString  ZmmMassVsRelErr_mass, ZeeMassVsRelErr_mass, newZmmMassVsRelErr_mass, newZeeMassVsRelErr_mass;

////////////////////////////////////////

        double mZmm_reco, mZee_reco, mZee_gen1, mZee_gen3, mZmm_gen1, mZmm_gen3; double eventWeight;

        boost::shared_ptr<TFile>     fmu_res;
        boost::shared_ptr<TFile>     fel_res;
        boost::shared_ptr<TH2F>      muonres_corr; 
        boost::shared_ptr<TH2F>      electronres_corr;

        TString el_relpterr2D, mu_relpterr2D, Nel_relpterr2D, Nmu_relpterr2D;
        TString newel_relpterr2D, newmu_relpterr2D, newNmu_relpterr2D;

};


#endif

#ifndef HZZ4LDILEPRESOLUTION_CC
#define HZZ4LDILEPRESOLUTION_CC

HZZ4LDiLepResolution::HZZ4LDiLepResolution()
{

        mu_relpterr2D = "Zmu_relpterr2D";
        newmu_relpterr2D = "Znewmu_relpterr2D";
        Nmu_relpterr2D = "ZNmu_relpterr2D";
        newNmu_relpterr2D = "ZnewNmu_relpterr2D";

//////////////////////////////////////////////////////

	appName = "";
	ZmmMassVsErr = "ZmmMassVsErr";
	ZeeMassVsErr = "ZeeMassVsErr";

	ZmmMassVsRelErr = "ZmmMassVsRelErr";
	ZeeMassVsRelErr = "ZeeMassVsRelErr";
        ZeeMassVsRelErrAD = "ZeeMassVsRelErrAD";

        ZmmMassVsRelErr_mass = "ZmmMassVsRelErr_mass";
        ZeeMassVsRelErr_mass = "ZeeMassVsRelErr_mass";

////////////////////////////////////////////////////////////
	newZmmMassVsErr = "newZmmMassVsErr";
	newZeeMassVsErr = "newZeeMassVsErr";

	newZmmMassVsRelErr = "newZmmMassVsRelErr";
	newZeeMassVsRelErr = "newZeeMassVsRelErr";

	newZmmMassVsRelErr_mass = "newZmmMassVsRelErr_mass";
	newZeeMassVsRelErr_mass = "newZeeMassVsRelErr_mass";

//////////////////////////////////////////////////////////////
        ZmmMass1 = "ZmmMass1";
        ZeeMass1 = "ZeeMass1";
        ZmmMass3 = "ZmmMass3";
        ZeeMass3 = "ZeeMass3";

	ZmmMassPull = "ZmmMassPull";
	ZeeMassPull = "ZeeMassPull";
	ZmmMassPull3 = "ZmmMassPull3";
	ZeeMassPull3 = "ZeeMassPull3";

	ZmmMassRes = "ZmmMassRes";
	ZeeMassRes = "ZeeMassRes";
	ZmmMassRes3 = "ZmmMassRes3";
	ZeeMassRes3 = "ZeeMassRes3";

	newZmmMassPull = "newZmmMassPull";
	newZeeMassPull = "newZeeMassPull";
	newZmmMassPull3 = "newZmmMassPull3";
	newZeeMassPull3 = "newZeeMassPull3";

	newZmmMassRes = "newZmmMassRes";
	newZeeMassRes = "newZeeMassRes";
	newZmmMassRes3 = "newZmmMassRes3";
	newZeeMassRes3 = "newZeeMassRes3";

}

void HZZ4LDiLepResolution::SetAppendName(TString appendName)
{

	appName = appendName;
	ZmmMassVsErr = ZmmMassVsErr + appName;
	ZeeMassVsErr = ZeeMassVsErr + appName;

	ZmmMassPull = ZmmMassPull + appName;
	ZeeMassPull = ZeeMassPull + appName;
	ZmmMassPull3 = ZmmMassPull3 + appName;
	ZeeMassPull3 = ZeeMassPull3 + appName;

	ZmmMassRes = ZmmMassRes + appName;
	ZeeMassRes = ZeeMassRes + appName;
	ZmmMassRes3 = ZmmMassRes3 + appName;
	ZeeMassRes3 = ZeeMassRes3 + appName;

        ZmmMass1 = ZmmMass1 + appName;
        ZeeMass1 = ZeeMass1 + appName;
        ZmmMass3 = ZmmMass3 + appName;
        ZeeMass3 = ZeeMass3 + appName;

}


HZZ4LDiLepResolution::~HZZ4LDiLepResolution()
{

}

void HZZ4LDiLepResolution::bookHistograms(edm::Service<TFileService> fs, std::map<TString,TH1F*> &histContainer_, std::map<TString, TH2F*> &histContainer2D_) 
{

  //double ptranges_err[25] = {10,12,14,16,18,20,22,24,26,28,30,35,40,45,50,55,60,65,70,75,80,85,90,95,100};
  //double etaranges_err[13] = {0, 0.2, 0.4, 0.6, 0.8, 1.0, 1.2, 1.4, 1.6, 1.8, 2.0, 2.2, 2.5};

       //histContainer2D_[mu_relpterr2D]=fs->make<TH2F>(mu_relpterr2D, "rel pT err of mu; p_{T}^{reco}; |#eta^{reco}|", 24, ptranges_err, 12, etaranges_err);
       //histContainer2D_[Nmu_relpterr2D]=fs->make<TH2F>(Nmu_relpterr2D, "N of mu; p_{T}^{reco}; |#eta^{reco}|", 24, ptranges_err, 12, etaranges_err);
       
///////////////////////////////////////////////////////////////////////////////////////////////////////

	histContainer2D_[ZmmMassVsErr] = fs->make<TH2F>(ZmmMassVsErr, ZmmMassVsErr+"; new m_{Z#rightarrow#mu#mu}; #delta_{m}", 2400, 60, 120, 200, 0.0, 4.0);
	histContainer2D_[ZeeMassVsErr] = fs->make<TH2F>(ZeeMassVsErr, ZeeMassVsErr+"; new m_{Z#rightarrow ee}; #delta_{m}", 2400, 60, 120, 180, 0.4, 4.0);

	histContainer2D_[newZmmMassVsErr] = fs->make<TH2F>(newZmmMassVsErr, newZmmMassVsErr+"; m_{Z#rightarrow#mu#mu}; new #delta_{m}", 2400, 60, 120, 200, 0.0, 4.0);
	histContainer2D_[newZeeMassVsErr] = fs->make<TH2F>(newZeeMassVsErr, newZeeMassVsErr+"; m_{Z#rightarrow ee}; new #delta_{m}", 2400, 60, 120, 180, 0.4, 4.0);

///////////////////////////////
///// rel error

	histContainer2D_[ZmmMassVsRelErr] = fs->make<TH2F>(ZmmMassVsRelErr, ZmmMassVsRelErr+"; m_{Z#rightarrow#mu#mu}; new  #delta_{m}/m_{Z#rightarrow#mu#mu}", 2400, 60, 120, 200, 0.0/120, 4.0/60);
	histContainer2D_[ZeeMassVsRelErr] = fs->make<TH2F>(ZeeMassVsRelErr, ZeeMassVsRelErr+"; m_{Z#rightarrow ee}; new  #delta_{m}/m_{Z#rightarrow ee}", 2400, 60, 120, 180, 0.4/120, 4.0/60);

	histContainer2D_[newZmmMassVsRelErr] = fs->make<TH2F>(newZmmMassVsRelErr, newZmmMassVsRelErr+"; m_{Z#rightarrow#mu#mu}; new #delta_{m}/m_{Z#rightarrow#mu#mu}", 2400, 60, 120, 200, 0.0/120, 4.0/60);
	histContainer2D_[newZeeMassVsRelErr] = fs->make<TH2F>(newZeeMassVsRelErr, newZeeMassVsRelErr+"; m_{Z#rightarrow ee}; new #delta_{m}/m_{Z#rightarrow ee}", 2400, 60, 120, 180, 0.4/120, 4.0/60);

/////////////////////

	histContainer2D_[ZmmMassVsRelErr_mass] = fs->make<TH2F>(ZmmMassVsRelErr_mass, ZmmMassVsRelErr_mass+"; m_{Z#rightarrow#mu#mu}; new  #delta_{m}/m_{Z#rightarrow#mu#mu}", 2400, 60, 120, 200, 0.0/120, 4.0/60);
	histContainer2D_[ZeeMassVsRelErr_mass] = fs->make<TH2F>(ZeeMassVsRelErr_mass, ZeeMassVsRelErr_mass+"; m_{Z#rightarrow ee}; new  #delta_{m}/m_{Z#rightarrow ee}", 2400, 60, 120, 180, 0.4/120, 4.0/60);

	histContainer2D_[newZmmMassVsRelErr_mass] = fs->make<TH2F>(newZmmMassVsRelErr_mass, newZmmMassVsRelErr_mass+"; m_{Z#rightarrow#mu#mu}; new #delta_{m}/m_{Z#rightarrow#mu#mu}", 2400, 60, 120, 200, 0.0/120, 4.0/60);
	histContainer2D_[newZeeMassVsRelErr_mass] = fs->make<TH2F>(newZeeMassVsRelErr_mass, newZeeMassVsRelErr_mass+"; m_{Z#rightarrow ee}; new #delta_{m}/m_{Z#rightarrow ee}", 2400, 60, 120, 180, 0.4/120, 4.0/60);

///////////////////////////////

        histContainer_[ZmmMass1] = fs->make<TH1F>(ZmmMass1, ZmmMass1+"; m_{Z#rightarrow#mu#mu}; N Events", 2400, 60, 120);
        histContainer_[ZeeMass1] = fs->make<TH1F>(ZeeMass1, ZeeMass1+"; m_{Z#rightarrow ee}; N Events", 2400, 60, 120);
        histContainer_[ZmmMass3] = fs->make<TH1F>(ZmmMass3, ZmmMass3+"; m_{Z#rightarrow#mu#mu}; N Events", 2400, 60, 120);
        histContainer_[ZeeMass3] = fs->make<TH1F>(ZeeMass3, ZeeMass3+"; m_{Z#rightarrow ee}; N Events", 2400, 60, 120);

	histContainer_[ZmmMassPull] = fs->make<TH1F>(ZmmMassPull, ZmmMassPull+"; m_{Z#rightarrow#mu#mu} pull; N Events", 1000, -10, 10);
	histContainer_[ZeeMassPull] = fs->make<TH1F>(ZeeMassPull, ZeeMassPull+"; m_{Z#rightarrow ee} pull; N Events", 200, -10, 10);
	histContainer_[ZmmMassPull3] = fs->make<TH1F>(ZmmMassPull3, ZmmMassPull3+"; m_{Z#rightarrow#mu#mu} pull3; N Events", 200, -10, 10);
	histContainer_[ZeeMassPull3] = fs->make<TH1F>(ZeeMassPull3, ZeeMassPull3+"; m_{Z#rightarrow ee} pull3; N Events", 1000, -10, 10);
        histContainer_[ZeeMassPull3AD] = fs->make<TH1F>(ZeeMassPull3AD, ZeeMassPull3AD+"; m_{Z#rightarrow ee} pull3; N Events", 1000, -10, 10);

	histContainer_[ZmmMassRes] = fs->make<TH1F>(ZmmMassRes, ZmmMassRes+"; m_{Z#rightarrow#mu#mu} res; N Events", 500,-0.5,0.5);
	histContainer_[ZeeMassRes] = fs->make<TH1F>(ZeeMassRes, ZeeMassRes+"; m_{Z#rightarrow ee} res Events", 500,-0.5,0.5);
	histContainer_[ZmmMassRes3] = fs->make<TH1F>(ZmmMassRes3, ZmmMassRes3+"; m_{Z#rightarrow#mu#mu} res3; N Events", 500,-0.5,0.5);
	histContainer_[ZeeMassRes3] = fs->make<TH1F>(ZeeMassRes3, ZeeMassRes3+"; m_{Z#rightarrow ee} res3; N Events", 500,-0.5,0.5);

        ////////////////

	histContainer_[newZmmMassPull] = fs->make<TH1F>(newZmmMassPull, newZmmMassPull+"; new m_{Z#rightarrow#mu#mu} pull; N Events", 1000, -10, 10);
	histContainer_[newZeeMassPull3] = fs->make<TH1F>(newZeeMassPull3, newZeeMassPull3+"; new m_{Z#rightarrow ee} pull3; N Events", 1000, -10, 10);

	histContainer_[newZmmMassRes] = fs->make<TH1F>(newZmmMassRes, newZmmMassRes+"; new m_{Z#rightarrow#mu#mu} res; N Events", 500,-0.5,0.5);
	histContainer_[newZeeMassRes3] = fs->make<TH1F>(newZeeMassRes3, newZeeMassRes3+"; new m_{Z#rightarrow ee} res3; N Events", 500,-0.5,0.5);

	for(int cat=1; cat<=13; cat++){
                //Error
		TString sZmmCat = ZmmMassVsErr+"_"; sZmmCat+=cat; 
		histContainer2D_[sZmmCat.Data()] = fs->make<TH2F>(sZmmCat, sZmmCat+"; m_{Z#rightarrow#mu#mu}; #delta_{m}", 2400, 60, 120, 200, 0.0, 4.0);
		TString sZeeCat = ZeeMassVsErr+"_"; sZeeCat+=cat; 
		histContainer2D_[sZeeCat.Data()] = fs->make<TH2F>(sZeeCat, sZeeCat+"; m_{Z#rightarrow ee}; #delta_{m}", 2400, 60, 120, 180, 0.4, 4.0);
////////////////////////
//Rel error
		sZmmCat = ZmmMassVsRelErr+"_"; sZmmCat+=cat; 
		histContainer2D_[sZmmCat.Data()] = fs->make<TH2F>(sZmmCat, sZmmCat+"; m_{Z#rightarrow#mu#mu}; #delta_{m}/m_{Z#rightarrow#mu#mu}", 2400, 60, 120, 200, 0.0/120, 4.0/60);
		sZeeCat = ZeeMassVsRelErr+"_"; sZeeCat+=cat; 
		histContainer2D_[sZeeCat.Data()] = fs->make<TH2F>(sZeeCat, sZeeCat+"; m_{Z#rightarrow ee}; #delta_{m}/m_{Z#rightarrow ee}", 2400, 60, 120, 180, 0.4/120, 4.0/60);
//////////////////

		sZmmCat = ZmmMassVsRelErr_mass+"_"; sZmmCat+=cat; 
		histContainer2D_[sZmmCat.Data()] = fs->make<TH2F>(sZmmCat, sZmmCat+"; m_{Z#rightarrow#mu#mu}; #delta_{m}/m_{Z#rightarrow#mu#mu}", 2400, 60, 120, 200, 0.0/120, 4.0/60);
		sZeeCat = ZeeMassVsRelErr_mass+"_"; sZeeCat+=cat; 
		histContainer2D_[sZeeCat.Data()] = fs->make<TH2F>(sZeeCat, sZeeCat+"; m_{Z#rightarrow ee}; #delta_{m}/m_{Z#rightarrow ee}", 2400, 60, 120, 180, 0.4/120, 4.0/60);

//////////////////////////////////               
                //Pull
		sZmmCat = ZmmMassPull +"_"; sZmmCat+=cat; 
		histContainer_[sZmmCat.Data()] = fs->make<TH1F>(sZmmCat, sZmmCat+"; m_{Z#rightarrow#mu#mu} pull; N Events", 1000, -10, 10);
		sZeeCat = ZeeMassPull +"_"; sZeeCat+=cat; 
		histContainer_[sZeeCat.Data()] = fs->make<TH1F>(sZeeCat, sZeeCat+"; m_{Z#rightarrow ee} pull; N Events", 200, -10, 10);
		sZmmCat = ZmmMassPull3 +"_"; sZmmCat+=cat; 
		histContainer_[sZmmCat.Data()] = fs->make<TH1F>(sZmmCat, sZmmCat+"; m_{Z#rightarrow#mu#mu} pull3; N Events", 1000, -10, 10);
		sZeeCat = ZeeMassPull3 +"_"; sZeeCat+=cat; 
		histContainer_[sZeeCat.Data()] = fs->make<TH1F>(sZeeCat, sZeeCat+"; m_{Z#rightarrow ee} pull3; N Events", 200, -10, 10);

                //Res
		sZmmCat = ZmmMassRes +"_"; sZmmCat+=cat; 
		histContainer_[sZmmCat.Data()] = fs->make<TH1F>(sZmmCat, sZmmCat+"; m_{Z#rightarrow#mu#mu} res; N Events", 500,-0.5,0.5);
		sZeeCat = ZeeMassRes +"_"; sZeeCat+=cat; 
		histContainer_[sZeeCat.Data()] = fs->make<TH1F>(sZeeCat, sZeeCat+"; m_{Z#rightarrow ee} res; N Events", 500,-0.5,0.5);
		sZmmCat = ZmmMassRes3 +"_"; sZmmCat+=cat; 
		histContainer_[sZmmCat.Data()] = fs->make<TH1F>(sZmmCat, sZmmCat+"; m_{Z#rightarrow#mu#mu} res3; N Events", 500,-0.5,0.5);
		sZeeCat = ZeeMassRes3 +"_"; sZeeCat+=cat; 
		histContainer_[sZeeCat.Data()] = fs->make<TH1F>(sZeeCat, sZeeCat+"; m_{Z#rightarrow ee} res3; N Events", 500,-0.5,0.5);

                //Gen
		sZmmCat = ZmmMass1 +"_"; sZmmCat+=cat; 
		histContainer_[sZmmCat.Data()] = fs->make<TH1F>(sZmmCat, sZmmCat+"; m_{Z#rightarrow#mu#mu} gen; N Events", 2400, 60, 120);
		sZeeCat = ZeeMass1 +"_"; sZeeCat+=cat; 
		histContainer_[sZeeCat.Data()] = fs->make<TH1F>(sZeeCat, sZeeCat+"; m_{Z#rightarrow ee} gen; N Events", 2400, 60, 120);
		sZmmCat = ZmmMass3 +"_"; sZmmCat+=cat; 
		histContainer_[sZmmCat.Data()] = fs->make<TH1F>(sZmmCat, sZmmCat+"; m_{Z#rightarrow#mu#mu} gen3; N Events", 2400, 60, 120);
		sZeeCat = ZeeMass3 +"_"; sZeeCat+=cat; 
		histContainer_[sZeeCat.Data()] = fs->make<TH1F>(sZeeCat, sZeeCat+"; m_{Z#rightarrow ee} gen3; N Events", 2400, 60, 120);

                //newError
		TString newsZmmCat = newZmmMassVsErr+"_"; newsZmmCat+=cat; 
		histContainer2D_[newsZmmCat.Data()] = fs->make<TH2F>(newsZmmCat, newsZmmCat+"; m_{Z#rightarrow#mu#mu}; new #delta_{m}", 2400, 60, 120, 200, 0.0, 4.0);
		TString newsZeeCat = newZeeMassVsErr+"_"; newsZeeCat+=cat; 
		histContainer2D_[newsZeeCat.Data()] = fs->make<TH2F>(newsZeeCat, newsZeeCat+"; m_{Z#rightarrow ee}; new #delta_{m}", 2400, 60, 120, 180, 0.4, 4.0);
/////////////////////////////////// new rel error

		newsZmmCat = newZmmMassVsRelErr+"_"; newsZmmCat+=cat; 
		histContainer2D_[newsZmmCat.Data()] = fs->make<TH2F>(newsZmmCat, newsZmmCat+"; m_{Z#rightarrow#mu#mu}; new #delta_{m}/m_{Z#rightarrow#mu#mu}", 2400, 60, 120, 200, 0.0/120, 4.0/60);
		newsZeeCat = newZeeMassVsRelErr+"_"; newsZeeCat+=cat; 
		histContainer2D_[newsZeeCat.Data()] = fs->make<TH2F>(newsZeeCat, newsZeeCat+"; m_{Z#rightarrow ee}; new #delta_{m}/m_{Z#rightarrow ee}", 2400, 60, 120, 180, 0.4/120, 4.0/60);

//////////////////////////////////////////////

		newsZmmCat = newZmmMassVsRelErr_mass+"_"; newsZmmCat+=cat; 
		histContainer2D_[newsZmmCat.Data()] = fs->make<TH2F>(newsZmmCat, newsZmmCat+"; m_{Z#rightarrow#mu#mu}; new #delta_{m}/m_{Z#rightarrow#mu#mu}", 2400, 60, 120, 200, 0.0/120, 4.0/60);
		newsZeeCat = newZeeMassVsRelErr_mass+"_"; newsZeeCat+=cat; 
		histContainer2D_[newsZeeCat.Data()] = fs->make<TH2F>(newsZeeCat, newsZeeCat+"; m_{Z#rightarrow ee}; new #delta_{m}/m_{Z#rightarrow ee}", 2400, 60, 120, 180, 0.4/120, 4.0/60);

/////////////////////////////////////////////////////////////////////////////////////                

                //new Pull
		newsZmmCat = newZmmMassPull +"_"; newsZmmCat+=cat; 
		histContainer_[newsZmmCat.Data()] = fs->make<TH1F>(newsZmmCat, newsZmmCat+"; new m_{Z#rightarrow#mu#mu} pull; N Events", 200, -10, 10);
		newsZeeCat = newZeeMassPull3 +"_"; newsZeeCat+=cat; 
		histContainer_[newsZeeCat.Data()] = fs->make<TH1F>(newsZeeCat, newsZeeCat+"; new m_{Z#rightarrow ee} pull3; N Events", 200, -10, 10);
                 
	}

	histContainer2D_[ZeeMassVsErr+"_best"] = fs->make<TH2F>(ZeeMassVsErr+"_best", ZeeMassVsErr+"_best; m_{Z#rightarrow ee}; #delta_{m}", 2400, 60, 120, 180, 0.4, 4.0);
	histContainer2D_[ZeeMassVsErr+"_worst"] = fs->make<TH2F>(ZeeMassVsErr+"_worst", ZeeMassVsErr+"_worst; m_{Z#rightarrow ee}; #delta_{m}", 2400, 60, 120, 180, 0.4, 4.0);
	histContainer2D_[ZeeMassVsErr+"_medium"] = fs->make<TH2F>(ZeeMassVsErr+"_medium", ZeeMassVsErr+"_medium; m_{Z#rightarrow ee}; #delta_{m}", 2400, 60, 120, 180, 0.4, 4.0);

	histContainer2D_[newZeeMassVsErr+"_best"] = fs->make<TH2F>(newZeeMassVsErr+"_best", newZeeMassVsErr+"_best; m_{Z#rightarrow ee}; new #delta_{m}", 2400, 60, 120, 180, 0.4, 4.0);
	histContainer2D_[newZeeMassVsErr+"_worst"] = fs->make<TH2F>(newZeeMassVsErr+"_worst", newZeeMassVsErr+"_worst; m_{Z#rightarrow ee}; new #delta_{m}", 2400, 60, 120, 180, 0.4, 4.0);
	histContainer2D_[newZeeMassVsErr+"_medium"] = fs->make<TH2F>(newZeeMassVsErr+"_medium", newZeeMassVsErr+"_medium; m_{Z#rightarrow ee}; new #delta_{m}", 2400, 60, 120, 180, 0.4, 4.0);
///////////////////////////////////////////////////
// new rel error

	histContainer2D_[ZeeMassVsRelErr+"_best"] = fs->make<TH2F>(ZeeMassVsRelErr+"_best", ZeeMassVsRelErr+"_best; m_{Z#rightarrow ee}; #delta_{m}", 2400, 60, 120, 180, 0.4/120, 4.0/60);
	histContainer2D_[ZeeMassVsRelErr+"_worst"] = fs->make<TH2F>(ZeeMassVsRelErr+"_worst", ZeeMassVsRelErr+"_worst; m_{Z#rightarrow ee}; #delta_{m}", 2400, 60, 120, 180, 0.4/120, 4.0/60);
	histContainer2D_[ZeeMassVsRelErr+"_medium"] = fs->make<TH2F>(ZeeMassVsRelErr+"_medium", ZeeMassVsRelErr+"_medium; m_{Z#rightarrow ee}; #delta_{m}", 2400, 60, 120, 180, 0.4/120, 4.0/60);

	histContainer2D_[newZeeMassVsRelErr+"_best"] = fs->make<TH2F>(newZeeMassVsRelErr+"_best", newZeeMassVsRelErr+"_best; m_{Z#rightarrow ee}; new #delta_{m}", 2400, 60, 120, 180, 0.4/120, 4.0/60);
	histContainer2D_[newZeeMassVsRelErr+"_worst"] = fs->make<TH2F>(newZeeMassVsRelErr+"_worst", newZeeMassVsRelErr+"_worst; m_{Z#rightarrow ee}; new #delta_{m}", 2400, 60, 120, 180, 0.4/120, 4.0/60);
	histContainer2D_[newZeeMassVsRelErr+"_medium"] = fs->make<TH2F>(newZeeMassVsRelErr+"_medium", newZeeMassVsRelErr+"_medium; m_{Z#rightarrow ee}; new #delta_{m}", 2400, 60, 120, 180, 0.4/120, 4.0/60);

///////////////

	histContainer2D_[ZeeMassVsRelErr_mass+"_best"] = fs->make<TH2F>(ZeeMassVsRelErr_mass+"_best", ZeeMassVsRelErr_mass+"_best; m_{Z#rightarrow ee}; #delta_{m}", 2400, 60, 120, 180, 0.4/120, 4.0/60);
	histContainer2D_[ZeeMassVsRelErr_mass+"_worst"] = fs->make<TH2F>(ZeeMassVsRelErr_mass+"_worst", ZeeMassVsRelErr_mass+"_worst; m_{Z#rightarrow ee}; #delta_{m}", 2400, 60, 120, 180, 0.4/120, 4.0/60);
	histContainer2D_[ZeeMassVsRelErr_mass+"_medium"] = fs->make<TH2F>(ZeeMassVsRelErr_mass+"_medium", ZeeMassVsRelErr_mass+"_medium; m_{Z#rightarrow ee}; #delta_{m}", 2400, 60, 120, 180, 0.4/120, 4.0/60);

	histContainer2D_[newZeeMassVsRelErr_mass+"_best"] = fs->make<TH2F>(newZeeMassVsRelErr_mass+"_best", newZeeMassVsRelErr_mass+"_best; m_{Z#rightarrow ee}; new #delta_{m}", 2400, 60, 120, 180, 0.4/120, 4.0/60);
	histContainer2D_[newZeeMassVsRelErr_mass+"_worst"] = fs->make<TH2F>(newZeeMassVsRelErr_mass+"_worst", newZeeMassVsRelErr_mass+"_worst; m_{Z#rightarrow ee}; new #delta_{m}", 2400, 60, 120, 180, 0.4/120, 4.0/60);
	histContainer2D_[newZeeMassVsRelErr_mass+"_medium"] = fs->make<TH2F>(newZeeMassVsRelErr_mass+"_medium", newZeeMassVsRelErr_mass+"_medium; m_{Z#rightarrow ee}; new #delta_{m}", 2400, 60, 120, 180, 0.4/120, 4.0/60);

}

void HZZ4LDiLepResolution::fillHistograms(std::map<TString,TH1F*> &histContainer_, std::map<TString, TH2F*> &histContainer2D_, std::vector< pat::Electron > electrons, std::vector< pat::Muon > muons, double evtWeight, bool isData)
{
  //bool onlyOneZperEvent = false;
	//double mdil = 0;
	//bool isMuMuWithZMass = false;
	int ZmmCategory = 0;
	for(unsigned int i=0; i< muons.size(); i++ ){
		bool ibarrel = false;
		if(fabs(muons[i].eta())<1.2) ibarrel = true;
		double ieta = muons[i].eta(); 
		//double abs_ieta = fabs(muons[i].eta());
		for(unsigned int j=i+1; j< muons.size(); j++ ){
			bool jbarrel = false;	
			if(fabs(muons[j].eta())<1.2) jbarrel = true;
			double jeta = muons[j].eta(); 
			//double abs_jeta = fabs(muons[j].eta());

                        if(muons[i].pt()<20 && muons[j].pt()<20 ) continue;

			math::XYZTLorentzVector zboson;
			zboson = muons[i].p4() + muons[j].p4();                      

			double m = zboson.M(); //double newm = newzboson.M();
			//mdil = m;
			if(muons[i].charge()==muons[j].charge()) continue;//fillDiLeptonTree(m, 1);
			if(m>60 and m<120) {
			  //isMuMuWithZMass = true;

				// booking 3  variables   ZmmCategory, ZmmMass, ZmmMassErr			
				if(ibarrel and jbarrel){ // BB
					if(ieta>0 and jeta>0) ZmmCategory = 1; //B+B+
					else if(ieta<0 and jeta<0) ZmmCategory = 2; //B-B-
					else ZmmCategory = 3; //B+B- or B-B+
				}else if(ibarrel or jbarrel){//BE
					bool postiveB = false;
					bool postiveE = false;
					if(ibarrel and ieta>0) postiveB = true;
					if(jbarrel and jeta>0) postiveB = true;
					if(ibarrel and jeta>0) postiveE = true;
					if(jbarrel and ieta>0) postiveE = true;
					if(postiveB and postiveE) ZmmCategory = 4; 
					if(postiveB and !postiveE) ZmmCategory = 5; 
					if(!postiveB and postiveE) ZmmCategory = 6; 
					if(!postiveB and !postiveE) ZmmCategory = 7; 
				}else{//EE
					if(ieta>0 and jeta>0) ZmmCategory = 8; //E+E+
					else if(ieta<0 and jeta<0) ZmmCategory = 9; //E-E-
					else ZmmCategory = 10; //E+E- or E-E+
				}
                                
				//onlyOneZperEvent = true;
				double mass = m; 

				vector< pat::Muon > vmtmp; vmtmp.clear();
				vmtmp.push_back(muons[i]);
				vmtmp.push_back(muons[j]);

				double err = massErr.calc2muErr(vmtmp,false,isData);
                                double newerr = massErr.calc2muErr(vmtmp,true,isData);
                                //double err = massErr.getZMassResolution(vmtmp);
                                double relerr = err/mass; double newrelerr = newerr/mass;

				int cat = ZmmCategory;
				histContainer2D_[ZmmMassVsErr]->Fill(mass,err, evtWeight);
				TString sZmmCat = ZmmMassVsErr+"_"; sZmmCat+=cat; 
				histContainer2D_[sZmmCat.Data()]->Fill(mass,err,evtWeight);
				if(cat>0 and cat<=3) histContainer2D_[ZmmMassVsErr+"_11"]->Fill(mass,err,evtWeight);
				if(cat>3 and cat<=7) histContainer2D_[ZmmMassVsErr+"_12"]->Fill(mass,err,evtWeight);
				if(cat>7 and cat<=10) histContainer2D_[ZmmMassVsErr+"_13"]->Fill(mass,err,evtWeight);

				histContainer2D_[newZmmMassVsErr]->Fill(mass,newerr, evtWeight);
				TString newsZmmCat = newZmmMassVsErr+"_"; newsZmmCat+=cat; 
				histContainer2D_[newsZmmCat.Data()]->Fill(mass,newerr,evtWeight);
				if(cat>0 and cat<=3) histContainer2D_[newZmmMassVsErr+"_11"]->Fill(mass,newerr,evtWeight);
				if(cat>3 and cat<=7) histContainer2D_[newZmmMassVsErr+"_12"]->Fill(mass,newerr,evtWeight);
				if(cat>7 and cat<=10) histContainer2D_[newZmmMassVsErr+"_13"]->Fill(mass,newerr,evtWeight);
/////////////////////////////////////////////
//////////////////////////////// rel err
				histContainer2D_[ZmmMassVsRelErr]->Fill(mass, relerr, evtWeight);
				sZmmCat = ZmmMassVsRelErr+"_"; sZmmCat+=cat; 
				histContainer2D_[sZmmCat.Data()]->Fill(mass, relerr,evtWeight);
				if(cat>0 and cat<=3) histContainer2D_[ZmmMassVsRelErr+"_11"]->Fill(mass,relerr,evtWeight);
				if(cat>3 and cat<=7) histContainer2D_[ZmmMassVsRelErr+"_12"]->Fill(mass,relerr,evtWeight);
				if(cat>7 and cat<=10) histContainer2D_[ZmmMassVsRelErr+"_13"]->Fill(mass,relerr,evtWeight);

				histContainer2D_[newZmmMassVsRelErr]->Fill(mass,newrelerr, evtWeight);
				newsZmmCat = newZmmMassVsRelErr+"_"; newsZmmCat+=cat; 
				histContainer2D_[newsZmmCat.Data()]->Fill(mass,newerr,evtWeight);
				if(cat>0 and cat<=3) histContainer2D_[newZmmMassVsRelErr+"_11"]->Fill(mass,newrelerr,evtWeight);
				if(cat>3 and cat<=7) histContainer2D_[newZmmMassVsRelErr+"_12"]->Fill(mass,newrelerr,evtWeight);
				if(cat>7 and cat<=10) histContainer2D_[newZmmMassVsRelErr+"_13"]->Fill(mass,newrelerr,evtWeight);
////////////////////////////////////////
//////////////////////////////// used for estimation of error from rel error
				histContainer2D_[ZmmMassVsRelErr_mass]->Fill(mass, relerr, mass*evtWeight);
				sZmmCat = ZmmMassVsRelErr_mass+"_"; sZmmCat+=cat; 
				histContainer2D_[sZmmCat.Data()]->Fill(mass, relerr,evtWeight);
				if(cat>0 and cat<=3) histContainer2D_[ZmmMassVsRelErr_mass+"_11"]->Fill(mass,relerr,mass*evtWeight);
				if(cat>3 and cat<=7) histContainer2D_[ZmmMassVsRelErr_mass+"_12"]->Fill(mass,relerr,mass*evtWeight);
				if(cat>7 and cat<=10) histContainer2D_[ZmmMassVsRelErr_mass+"_13"]->Fill(mass,relerr,mass*evtWeight);

				histContainer2D_[newZmmMassVsRelErr_mass]->Fill(mass,newrelerr, evtWeight);
				newsZmmCat = newZmmMassVsRelErr_mass+"_"; newsZmmCat+=cat; 
				histContainer2D_[newsZmmCat.Data()]->Fill(mass,newerr,evtWeight);
				if(cat>0 and cat<=3) histContainer2D_[newZmmMassVsRelErr_mass+"_11"]->Fill(mass,newrelerr,mass*evtWeight);
				if(cat>3 and cat<=7) histContainer2D_[newZmmMassVsRelErr_mass+"_12"]->Fill(mass,newrelerr,mass*evtWeight);
				if(cat>7 and cat<=10) histContainer2D_[newZmmMassVsRelErr_mass+"_13"]->Fill(mass,newrelerr,mass*evtWeight);
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
				//	    break;
				double massGEN = 0, massGEN3 = 0;
				massGEN = matchedGENDiLepMass(&muons[i], &muons[j]);
				massGEN3 = matchedGEN3DiLepMass(&muons[i], &muons[j]);

				if(massGEN>0) {
					double pull = (mass - massGEN)/err;
                                        double res = (mass - massGEN)/massGEN;	

					histContainer_[ZmmMassPull]->Fill(pull,evtWeight);
                                        histContainer_[ZmmMassRes]->Fill(res,evtWeight);
                                        histContainer_[ZmmMass1]->Fill(massGEN,evtWeight);                                   

					sZmmCat = ZmmMassPull+"_"; sZmmCat+=cat; 
					histContainer_[sZmmCat]->Fill(pull, evtWeight);
                                        sZmmCat = ZmmMassRes+"_"; sZmmCat+=cat;
                                        histContainer_[sZmmCat]->Fill(res, evtWeight);
                                        sZmmCat = ZmmMass1+"_"; sZmmCat+=cat;
                                        histContainer_[sZmmCat]->Fill(massGEN, evtWeight);

					if(cat>0 and cat<=3) histContainer_[ZmmMassPull+"_11"]->Fill(pull, evtWeight);
					if(cat>3 and cat<=7) histContainer_[ZmmMassPull+"_12"]->Fill(pull, evtWeight);
					if(cat>7 and cat<=10) histContainer_[ZmmMassPull+"_13"]->Fill(pull, evtWeight);

					if(cat>0 and cat<=3) histContainer_[ZmmMassRes+"_11"]->Fill(res, evtWeight);
					if(cat>3 and cat<=7) histContainer_[ZmmMassRes+"_12"]->Fill(res, evtWeight);
					if(cat>7 and cat<=10) histContainer_[ZmmMassRes+"_13"]->Fill(res, evtWeight);

					if(cat>0 and cat<=3) histContainer_[ZmmMass1+"_11"]->Fill(massGEN, evtWeight);
					if(cat>3 and cat<=7) histContainer_[ZmmMass1+"_12"]->Fill(massGEN, evtWeight);
					if(cat>7 and cat<=10) histContainer_[ZmmMass1+"_13"]->Fill(massGEN, evtWeight);

					double newpull = (mass - massGEN)/newerr;
                                        double newres = (mass - massGEN)/massGEN;

					histContainer_[newZmmMassPull]->Fill(newpull,evtWeight);
                                        histContainer_[newZmmMassRes]->Fill(newres,evtWeight);                                  

					newsZmmCat = newZmmMassPull+"_"; newsZmmCat+=cat; 
					histContainer_[newsZmmCat]->Fill(newpull, evtWeight);

					if(cat>0 and cat<=3) histContainer_[newZmmMassPull+"_11"]->Fill(newpull, evtWeight);
					if(cat>3 and cat<=7) histContainer_[newZmmMassPull+"_12"]->Fill(newpull, evtWeight);
					if(cat>7 and cat<=10) histContainer_[newZmmMassPull+"_13"]->Fill(newpull, evtWeight);

				}
				if(massGEN3>0) {
					double pull = (mass - massGEN3)/err;
                                        double res = (mass - massGEN3)/massGEN3;	
					histContainer_[ZmmMassPull3]->Fill(pull,evtWeight);
                                        histContainer_[ZmmMassRes3]->Fill(res,evtWeight);
                                        histContainer_[ZmmMass3]->Fill(massGEN3,evtWeight);

					sZmmCat = ZmmMassPull3+"_"; sZmmCat+=cat; 
					histContainer_[sZmmCat]->Fill(pull, evtWeight);
                                        sZmmCat = ZmmMassRes3+"_"; sZmmCat+=cat;
                                        histContainer_[sZmmCat]->Fill(res, evtWeight);
                                        sZmmCat = ZmmMass3+"_"; sZmmCat+=cat;
                                        histContainer_[sZmmCat]->Fill(massGEN3, evtWeight);

					if(cat>0 and cat<=3) histContainer_[ZmmMassPull3+"_11"]->Fill(pull, evtWeight);
					if(cat>3 and cat<=7) histContainer_[ZmmMassPull3+"_12"]->Fill(pull, evtWeight);
					if(cat>7 and cat<=10) histContainer_[ZmmMassPull3+"_13"]->Fill(pull, evtWeight);

					if(cat>0 and cat<=3) histContainer_[ZmmMassRes3+"_11"]->Fill(res, evtWeight);
					if(cat>3 and cat<=7) histContainer_[ZmmMassRes3+"_12"]->Fill(res, evtWeight);
					if(cat>7 and cat<=10) histContainer_[ZmmMassRes3+"_13"]->Fill(res, evtWeight);

					if(cat>0 and cat<=3) histContainer_[ZmmMass3+"_11"]->Fill(massGEN3, evtWeight);
					if(cat>3 and cat<=7) histContainer_[ZmmMass3+"_12"]->Fill(massGEN3, evtWeight);
					if(cat>7 and cat<=10) histContainer_[ZmmMass3+"_13"]->Fill(massGEN3, evtWeight);

                                        /////////////////////////////
                                        /*
					double newpull = (mass - massGEN3)/newerr;
                                        double newres = (mass - massGEN3)/massGEN3;	
					histContainer_[newZmmMassPull3]->Fill(newpull,evtWeight);
                                        histContainer_[newZmmMassRes3]->Fill(newres,evtWeight);

					newsZmmCat = newZmmMassPull3+"_"; newsZmmCat+=cat; 
					histContainer_[newsZmmCat]->Fill(newpull, evtWeight);
                                        newsZmmCat = newZmmMassRes3+"_"; newsZmmCat+=cat;
                                        histContainer_[newsZmmCat]->Fill(newres, evtWeight);

					if(cat>0 and cat<=3) histContainer_[newZmmMassPull3+"_11"]->Fill(newpull, evtWeight);
					if(cat>3 and cat<=7) histContainer_[newZmmMassPull3+"_12"]->Fill(newpull, evtWeight);
					if(cat>7 and cat<=10) histContainer_[newZmmMassPull3+"_13"]->Fill(newpull, evtWeight);

					if(cat>0 and cat<=3) histContainer_[newZmmMassRes3+"_11"]->Fill(newres, evtWeight);
					if(cat>3 and cat<=7) histContainer_[newZmmMassRes3+"_12"]->Fill(newres, evtWeight);
					if(cat>7 and cat<=10) histContainer_[newZmmMassRes3+"_13"]->Fill(newres, evtWeight);
                                        */
				}

			} 

		}
		// if(onlyOneZperEvent) break;
	}
	//onlyOneZperEvent = false;
	//bool hasRecoDiEle = false;
	int ZeeCategory = 0;
	for(unsigned int i=0; i< electrons.size(); i++ ){ 
		bool ibarrel = false; // barrel-and-nonshowering
		//if(fabs(electrons[i]->eta())<1.5 and electrons[i]->classification()<2 ) ibarrel = true;
		int iclass = electrons[i].classification();
		if(fabs(electrons[i].eta())<1.5 ) ibarrel = true;
		double ieta = electrons[i].eta();
		for(unsigned int j=i+1; j< electrons.size(); j++ ){
			bool jbarrel = false;	
			//if(fabs(electrons[j].eta())<1.5 and electrons[j].classification()<2) jbarrel = true;
			int jclass = electrons[j].classification();
			if(fabs(electrons[j].eta())<1.5 ) jbarrel = true;
			double jeta = electrons[j].eta();
			if(electrons[i].pt()<20 and electrons[j].pt()<20) continue;
			//hasRecoDiEle = true;

			math::XYZTLorentzVector zboson;
			zboson = electrons[i].p4() + electrons[j].p4();
			double m = zboson.M();

			//mdil = m;
			if(electrons[i].charge()==electrons[j].charge()) continue; //fillDiLeptonTree(m, 2);
			if(m>60 and m<120) {

				// booking 3  variables   ZeeCategory, ZeeMass, ZeeMassErr			
				if(ibarrel and jbarrel){ // BB
					if(ieta>0 and jeta>0) ZeeCategory = 1; //B+B+
					else if(ieta<0 and jeta<0) ZeeCategory = 2; //B-B-
					else ZeeCategory = 3; //B+B- or B-B+
				}else if(ibarrel or jbarrel){//BE
					bool postiveB = false;
					bool postiveE = false;
					if(ibarrel and ieta>0) postiveB = true;
					if(jbarrel and jeta>0) postiveB = true;
					if(ibarrel and jeta>0) postiveE = true;
					if(jbarrel and ieta>0) postiveE = true;
					if(postiveB and postiveE) ZeeCategory = 4; // B+E+
					if(postiveB and !postiveE) ZeeCategory = 5; //B+E-
					if(!postiveB and postiveE) ZeeCategory = 6; //B-E+
					if(!postiveB and !postiveE) ZeeCategory = 7; //B-E-
				}else{//EE
					if(ieta>0 and jeta>0) ZeeCategory = 8; //E+E+
					else if(ieta<0 and jeta<0) ZeeCategory = 9; //E-E-
					else ZeeCategory = 10; //E+E- or E-E+
				}

				//onlyOneZperEvent = true;
				double mass = m;

				vector< pat::Electron > vmtmp; vmtmp.clear();
				vmtmp.push_back(electrons[i]);
				vmtmp.push_back(electrons[j]);
 
				double err = massErr.calc2eErr(vmtmp,false,isData);
				double newerr = massErr.calc2eErr(vmtmp,true,isData);;
                                //double err = massErr.getZMassResolution(vmtmp);
                                double relerr = err/mass; double newrelerr = newerr/mass;

				int cat = ZeeCategory;
				histContainer2D_[ZeeMassVsErr]->Fill(mass,err,evtWeight);
				TString sZeeCat = ZeeMassVsErr+"_"; sZeeCat+=cat; 
				histContainer2D_[sZeeCat.Data()]->Fill(mass,err, evtWeight);
				if(cat>0 and cat<=3) histContainer2D_[ZeeMassVsErr+"_11"]->Fill(mass,err, evtWeight);
				if(cat>3 and cat<=7) histContainer2D_[ZeeMassVsErr+"_12"]->Fill(mass,err, evtWeight);
				if(cat>7 and cat<=10) histContainer2D_[ZeeMassVsErr+"_13"]->Fill(mass,err, evtWeight);
                                
				histContainer2D_[newZeeMassVsErr]->Fill(mass,newerr,evtWeight);
				TString newsZeeCat = newZeeMassVsErr+"_"; newsZeeCat+=cat; 
				histContainer2D_[newsZeeCat.Data()]->Fill(mass,newerr, evtWeight);
				if(cat>0 and cat<=3) histContainer2D_[newZeeMassVsErr+"_11"]->Fill(mass,newerr, evtWeight);
				if(cat>3 and cat<=7) histContainer2D_[newZeeMassVsErr+"_12"]->Fill(mass,newerr, evtWeight);
				if(cat>7 and cat<=10) histContainer2D_[newZeeMassVsErr+"_13"]->Fill(mass,newerr, evtWeight);
				//    break;
				
					/* *********
					 * 	   electron cat 
					 * 	   	   UNKNOWN = -1, GOLDEN = 0, BIGBREM = 1, OLDNARROW = 2, 
					 * 	   	   	   SHOWERING = 3, GAP = 4    
					 * 	   	   	   	   index = cat + 2
					 * 	   	   	   	   	 */

				if(ibarrel and jbarrel and (iclass==0 or iclass==1) and (jclass==0 or jclass==1)){
					// barrel non-showering  and barrel non-showering   --> best 
					histContainer2D_[ZeeMassVsErr+"_best"]->Fill(mass,err,evtWeight);
				}else if(!ibarrel and !jbarrel and (iclass==3) and (jclass==3)){
					// endcap showering and endcap showering   --> worst
					histContainer2D_[ZeeMassVsErr+"_worst"]->Fill(mass,err,evtWeight);
				}else{ // medium 
					histContainer2D_[ZeeMassVsErr+"_medium"]->Fill(mass,err,evtWeight);
				}	

				if(ibarrel and jbarrel and (iclass==0 or iclass==1) and (jclass==0 or jclass==1)){
					// barrel non-showering  and barrel non-showering   --> best 
					histContainer2D_[newZeeMassVsErr+"_best"]->Fill(mass,newerr,evtWeight);
				}else if(!ibarrel and !jbarrel and (iclass==3) and (jclass==3)){
					// endcap showering and endcap showering   --> worst
					histContainer2D_[newZeeMassVsErr+"_worst"]->Fill(mass,newerr,evtWeight);
				}else{ // medium 
					histContainer2D_[newZeeMassVsErr+"_medium"]->Fill(mass,newerr,evtWeight);
				}
//////////////////////////////////////////////////////////
//////////////////////////////// rel error
				histContainer2D_[ZeeMassVsRelErr]->Fill(mass,relerr,evtWeight);
				sZeeCat = ZeeMassVsRelErr+"_"; sZeeCat+=cat; 
				histContainer2D_[sZeeCat.Data()]->Fill(mass,relerr,evtWeight);
				if(cat>0 and cat<=3) histContainer2D_[ZeeMassVsRelErr+"_11"]->Fill(mass,relerr, evtWeight);
				if(cat>3 and cat<=7) histContainer2D_[ZeeMassVsRelErr+"_12"]->Fill(mass,relerr, evtWeight);
				if(cat>7 and cat<=10) histContainer2D_[ZeeMassVsRelErr+"_13"]->Fill(mass,relerr, evtWeight);

				histContainer2D_[newZeeMassVsRelErr]->Fill(mass,newrelerr,evtWeight);
				newsZeeCat = newZeeMassVsRelErr+"_"; newsZeeCat+=cat; 
				histContainer2D_[newsZeeCat.Data()]->Fill(mass,newrelerr, evtWeight);
				if(cat>0 and cat<=3) histContainer2D_[newZeeMassVsRelErr+"_11"]->Fill(mass,newrelerr, evtWeight);
				if(cat>3 and cat<=7) histContainer2D_[newZeeMassVsRelErr+"_12"]->Fill(mass,newrelerr, evtWeight);
				if(cat>7 and cat<=10) histContainer2D_[newZeeMassVsRelErr+"_13"]->Fill(mass,newrelerr, evtWeight);


///////////////////////////////////////////////////////////
/////////////////////////////// mass for error estimation from re error

				histContainer2D_[ZeeMassVsRelErr_mass]->Fill(mass,relerr,mass*evtWeight);
				sZeeCat = ZeeMassVsRelErr_mass+"_"; sZeeCat+=cat; 
				histContainer2D_[sZeeCat.Data()]->Fill(mass,relerr,mass*evtWeight);
				if(cat>0 and cat<=3) histContainer2D_[ZeeMassVsRelErr_mass+"_11"]->Fill(mass,relerr, mass*evtWeight);
				if(cat>3 and cat<=7) histContainer2D_[ZeeMassVsRelErr_mass+"_12"]->Fill(mass,relerr, mass*evtWeight);
				if(cat>7 and cat<=10) histContainer2D_[ZeeMassVsRelErr_mass+"_13"]->Fill(mass,relerr, mass*evtWeight);

				histContainer2D_[newZeeMassVsRelErr_mass]->Fill(mass,newrelerr,mass*evtWeight);
				newsZeeCat = newZeeMassVsRelErr_mass+"_"; newsZeeCat+=cat; 
				histContainer2D_[newsZeeCat.Data()]->Fill(mass,newrelerr, mass*evtWeight);
				if(cat>0 and cat<=3) histContainer2D_[newZeeMassVsRelErr_mass+"_11"]->Fill(mass,newrelerr, mass*evtWeight);
				if(cat>3 and cat<=7) histContainer2D_[newZeeMassVsRelErr_mass+"_12"]->Fill(mass,newrelerr, mass*evtWeight);
				if(cat>7 and cat<=10) histContainer2D_[newZeeMassVsRelErr_mass+"_13"]->Fill(mass,newrelerr, mass*evtWeight);
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
				//    break;
			
////////////////////////////////// rel error////////////////////////////////////////////////////////////////////////////	
					/* *********
					 * 	   electron cat 
					 * 	   	   UNKNOWN = -1, GOLDEN = 0, BIGBREM = 1, OLDNARROW = 2, 
					 * 	   	   	   SHOWERING = 3, GAP = 4    
					 * 	   	   	   	   index = cat + 2
					 * 	   	   	   	   	 */

				if(ibarrel and jbarrel and (iclass==0 or iclass==1) and (jclass==0 or jclass==1)){
					// barrel non-showering  and barrel non-showering   --> best 
					histContainer2D_[ZeeMassVsRelErr+"_best"]->Fill(mass,relerr,evtWeight);
				}else if(!ibarrel and !jbarrel and (iclass==3) and (jclass==3)){
					// endcap showering and endcap showering   --> worst
					histContainer2D_[ZeeMassVsRelErr+"_worst"]->Fill(mass,relerr,evtWeight);
				}else{ // medium 
					histContainer2D_[ZeeMassVsRelErr+"_medium"]->Fill(mass,relerr,evtWeight);
				}	

				if(ibarrel and jbarrel and (iclass==0 or iclass==1) and (jclass==0 or jclass==1)){
					// barrel non-showering  and barrel non-showering   --> best 
					histContainer2D_[newZeeMassVsRelErr+"_best"]->Fill(mass,newrelerr,mass*evtWeight);
				}else if(!ibarrel and !jbarrel and (iclass==3) and (jclass==3)){
					// endcap showering and endcap showering   --> worst
					histContainer2D_[newZeeMassVsRelErr+"_worst"]->Fill(mass,newrelerr,mass*evtWeight);
				}else{ // medium 
					histContainer2D_[newZeeMassVsRelErr+"_medium"]->Fill(mass,newrelerr,mass*evtWeight);
				}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////// 
				if(ibarrel and jbarrel and (iclass==0 or iclass==1) and (jclass==0 or jclass==1)){
					// barrel non-showering  and barrel non-showering   --> best 
					histContainer2D_[ZeeMassVsRelErr_mass+"_best"]->Fill(mass,relerr,mass*evtWeight);
				}else if(!ibarrel and !jbarrel and (iclass==3) and (jclass==3)){
					// endcap showering and endcap showering   --> worst
					histContainer2D_[ZeeMassVsRelErr_mass+"_worst"]->Fill(mass,relerr,mass*evtWeight);
				}else{ // medium 
					histContainer2D_[ZeeMassVsRelErr_mass+"_medium"]->Fill(mass,relerr,mass*evtWeight);
				}	

				if(ibarrel and jbarrel and (iclass==0 or iclass==1) and (jclass==0 or jclass==1)){
					// barrel non-showering  and barrel non-showering   --> best 
					histContainer2D_[newZeeMassVsRelErr_mass+"_best"]->Fill(mass,newrelerr,mass*evtWeight);
				}else if(!ibarrel and !jbarrel and (iclass==3) and (jclass==3)){
					// endcap showering and endcap showering   --> worst
					histContainer2D_[newZeeMassVsRelErr_mass+"_worst"]->Fill(mass,newrelerr,mass*evtWeight);
				}else{ // medium 
					histContainer2D_[newZeeMassVsRelErr_mass+"_medium"]->Fill(mass,newrelerr,mass*evtWeight);
				}

////////////////////////////////////////////////////////// 
				double massGEN = 0, massGEN3 = 0;
				massGEN = matchedGENDiLepMass(&electrons[i], &electrons[j]);
				massGEN3 = matchedGEN3DiLepMass(&electrons[i], &electrons[j]);

				if(massGEN>0) {
					double pull = (mass - massGEN)/err;	
                                        double res = (mass - massGEN)/massGEN;
					histContainer_[ZeeMassPull]->Fill(pull,evtWeight);
                                        histContainer_[ZeeMassRes]->Fill(res,evtWeight);
                                        histContainer_[ZeeMass1]->Fill(massGEN,evtWeight);

					sZeeCat = ZeeMassPull+"_"; sZeeCat+=cat; 
					histContainer_[sZeeCat]->Fill(pull, evtWeight);
                                        sZeeCat = ZeeMassRes+"_"; sZeeCat+=cat;  
                                        histContainer_[sZeeCat]->Fill(pull, evtWeight);
                                        sZeeCat = ZeeMass1+"_"; sZeeCat+=cat;  
                                        histContainer_[sZeeCat]->Fill(pull, evtWeight);

					if(cat>0 and cat<=3) histContainer_[ZeeMassPull+"_11"]->Fill(pull, evtWeight);
					if(cat>3 and cat<=7) histContainer_[ZeeMassPull+"_12"]->Fill(pull, evtWeight);
					if(cat>7 and cat<=10) histContainer_[ZeeMassPull+"_13"]->Fill(pull, evtWeight);

					if(cat>0 and cat<=3) histContainer_[ZeeMassRes+"_11"]->Fill(res, evtWeight);
					if(cat>3 and cat<=7) histContainer_[ZeeMassRes+"_12"]->Fill(res, evtWeight);
					if(cat>7 and cat<=10) histContainer_[ZeeMassRes+"_13"]->Fill(res, evtWeight);

					if(cat>0 and cat<=3) histContainer_[ZeeMass1+"_11"]->Fill(massGEN, evtWeight);
					if(cat>3 and cat<=7) histContainer_[ZeeMass1+"_12"]->Fill(massGEN, evtWeight);
					if(cat>7 and cat<=10) histContainer_[ZeeMass1+"_13"]->Fill(massGEN, evtWeight);

                                        /*
					double newpull = (mass - massGEN)/newerr;	
                                        double newres = (mass - massGEN)/massGEN;
					histContainer_[newZeeMassPull]->Fill(newpull,evtWeight);
                                        histContainer_[newZeeMassRes]->Fill(newres,evtWeight);;

					newsZeeCat = ZeeMassPull+"_"; newsZeeCat+=cat; 
					histContainer_[newsZeeCat]->Fill(newpull, evtWeight);
                                        newsZeeCat = newZeeMassRes+"_"; newsZeeCat+=cat;  
                                        histContainer_[sZeeCat]->Fill(newpull, evtWeight);

					if(cat>0 and cat<=3) histContainer_[newZeeMassPull+"_11"]->Fill(newpull, evtWeight);
					if(cat>3 and cat<=7) histContainer_[newZeeMassPull+"_12"]->Fill(newpull, evtWeight);
					if(cat>7 and cat<=10) histContainer_[newZeeMassPull+"_13"]->Fill(newpull, evtWeight);

					if(cat>0 and cat<=3) histContainer_[newZeeMassRes+"_11"]->Fill(newres, evtWeight);
					if(cat>3 and cat<=7) histContainer_[newZeeMassRes+"_12"]->Fill(newres, evtWeight);
					if(cat>7 and cat<=10) histContainer_[newZeeMassRes+"_13"]->Fill(newres, evtWeight);
                                        */

				}

				if(massGEN3>0) {
					double pull = (mass - massGEN3)/err;	
                                        double res = (mass - massGEN3)/massGEN3;

					histContainer_[ZeeMassPull3]->Fill(pull,evtWeight);
                                        histContainer_[ZeeMassRes3]->Fill(res,evtWeight);
                                        histContainer_[ZeeMass3]->Fill(massGEN3,evtWeight);

					sZeeCat = ZeeMassPull3+"_"; sZeeCat+=cat; 
					histContainer_[sZeeCat]->Fill(pull, evtWeight);
                                        sZeeCat = ZeeMassRes3+"_"; sZeeCat+=cat;  
                                        histContainer_[sZeeCat]->Fill(res, evtWeight);
                                        sZeeCat = ZeeMass3+"_"; sZeeCat+=cat;  
                                        histContainer_[sZeeCat]->Fill(massGEN3, evtWeight);

					if(cat>0 and cat<=3) histContainer_[ZeeMassPull3+"_11"]->Fill(pull, evtWeight);
					if(cat>3 and cat<=7) histContainer_[ZeeMassPull3+"_12"]->Fill(pull, evtWeight);
					if(cat>7 and cat<=10) histContainer_[ZeeMassPull3+"_13"]->Fill(pull, evtWeight);

					if(cat>0 and cat<=3) histContainer_[ZeeMassRes3+"_11"]->Fill(res, evtWeight);
					if(cat>3 and cat<=7) histContainer_[ZeeMassRes3+"_12"]->Fill(res, evtWeight);
					if(cat>7 and cat<=10) histContainer_[ZeeMassRes3+"_13"]->Fill(res, evtWeight);

					if(cat>0 and cat<=3) histContainer_[ZeeMass3+"_11"]->Fill(massGEN3, evtWeight);
					if(cat>3 and cat<=7) histContainer_[ZeeMass3+"_12"]->Fill(massGEN3, evtWeight);
					if(cat>7 and cat<=10) histContainer_[ZeeMass3+"_13"]->Fill(massGEN3, evtWeight);


					double newpull = (mass - massGEN3)/newerr;	

					histContainer_[newZeeMassPull3]->Fill(newpull,evtWeight);
                                    
					newsZeeCat = newZeeMassPull3+"_"; newsZeeCat+=cat; 
					histContainer_[newsZeeCat]->Fill(newpull, evtWeight);

					if(cat>0 and cat<=3) histContainer_[newZeeMassPull3+"_11"]->Fill(newpull, evtWeight);
					if(cat>3 and cat<=7) histContainer_[newZeeMassPull3+"_12"]->Fill(newpull, evtWeight);
					if(cat>7 and cat<=10) histContainer_[newZeeMassPull3+"_13"]->Fill(newpull, evtWeight);
				}

			} 

		}
		// if(onlyOneZperEvent) break;
	}
	// ****** end of Z mass error  

}


void HZZ4LDiLepResolution::plotHistograms(std::map<TString,TH1F*> &histContainer_ , bool weightEvents, double scaleWeight)
{

	if(weightEvents)
	{

		//      if(histContainer_[pt1_4mu]->GetEntries() > 0){histContainer_[pt1_4mu]->Scale(scaleWeight);}
	}

}

double HZZ4LDiLepResolution::matchedGENDiLepMass(const pat::Muon *e1, const pat::Muon *e2){
	double mass = 0;
	math::XYZTLorentzVector v1, v2;
	bool b1=false, b2=false;
	for(unsigned int j = 0 ; j < e1->genParticleRefs().size() ; j++ ){
		if( e1->genParticle(j)->status() == 1 && abs(e1->genParticle(j)->pdgId()) == 13 ){
			v1 = e1->genParticle(j)->p4(); b1=true;
		}
	}
	for(unsigned int j = 0 ; j < e2->genParticleRefs().size() ; j++ ){
		if( e2->genParticle(j)->status() == 1 && abs(e2->genParticle(j)->pdgId()) == 13 ){
			v2 = e2->genParticle(j)->p4(); b2=true;
		}
	}

	if(b1 and b2) mass = (v1+v2).M();
	return mass;
}
double HZZ4LDiLepResolution::matchedGENDiLepMass(const pat::Electron *e1, const pat::Electron *e2){
	double mass = 0;
	math::XYZTLorentzVector v1, v2;
	bool b1=false, b2=false;
	for(unsigned int j = 0 ; j < e1->genParticleRefs().size() ; j++ ){
		if( e1->genParticle(j)->status() == 1 && abs(e1->genParticle(j)->pdgId()) == 11 ){
			v1 = e1->genParticle(j)->p4(); b1=true;
		}
	}
	for(unsigned int j = 0 ; j < e2->genParticleRefs().size() ; j++ ){
		if( e2->genParticle(j)->status() == 1 && abs(e2->genParticle(j)->pdgId()) == 11 ){
			v2 = e2->genParticle(j)->p4(); b2=true;
		}
	}

	if(b1 and b2) mass = (v1+v2).M();
	return mass;
}
double HZZ4LDiLepResolution::matchedGEN3DiLepMass(const pat::Muon *e1, const pat::Muon *e2){
	double mass = 0;
	math::XYZTLorentzVector v1, v2;
	bool b1=false, b2=false;
	for(unsigned int j = 0 ; j < e1->genParticleRefs().size() ; j++ ){
		if( e1->genParticle(j)->status() == 1 && abs(e1->genParticle(j)->pdgId()) == 13 ){
			if(abs(e1->genParticle(j)->mother()->pdgId())==13 and e1->genParticle(j)->mother()->status()==3){v1 = e1->genParticle(j)->mother()->p4(); b1=true; break;}
			if(abs(e1->genParticle(j)->mother()->mother()->pdgId())==13 and e1->genParticle(j)->mother()->mother()->status()==3){v1 = e1->genParticle(j)->mother()->mother()->p4(); b1=true; break;}
			if(abs(e1->genParticle(j)->mother()->mother()->mother()->pdgId())==13 and e1->genParticle(j)->mother()->mother()->mother()->status()==3){v1 = e1->genParticle(j)->mother()->mother()->mother()->p4(); b1=true; break;}
			if(abs(e1->genParticle(j)->mother()->mother()->mother()->mother()->pdgId())==13 and e1->genParticle(j)->mother()->mother()->mother()->mother()->status()==3){v1 = e1->genParticle(j)->mother()->mother()->mother()->mother()->p4(); b1=true; break;}
		}
	}
	for(unsigned int j = 0 ; j < e2->genParticleRefs().size() ; j++ ){
		if( e2->genParticle(j)->status() == 1 && abs(e2->genParticle(j)->pdgId()) == 13 ){
			if(abs(e2->genParticle(j)->mother()->pdgId())==13 and e2->genParticle(j)->mother()->status()==3){v2 = e2->genParticle(j)->mother()->p4(); b2=true; break;}
			if(abs(e2->genParticle(j)->mother()->mother()->pdgId())==13 and e2->genParticle(j)->mother()->mother()->status()==3){v2 = e2->genParticle(j)->mother()->mother()->p4(); b2=true; break;}
			if(abs(e2->genParticle(j)->mother()->mother()->mother()->pdgId())==13 and e2->genParticle(j)->mother()->mother()->mother()->status()==3){v2 = e2->genParticle(j)->mother()->mother()->mother()->p4(); b2=true; break;}
			if(abs(e2->genParticle(j)->mother()->mother()->mother()->mother()->pdgId())==13 and e2->genParticle(j)->mother()->mother()->mother()->mother()->status()==3){v2 = e2->genParticle(j)->mother()->mother()->mother()->mother()->p4(); b2=true; break;}
		}
	}

	if(b1 and b2) mass = (v1+v2).M();
	return mass;
}

double HZZ4LDiLepResolution::matchedGEN3DiLepMass(const pat::Electron *e1, const pat::Electron *e2){
	double mass = 0;
	math::XYZTLorentzVector v1, v2;
	bool b1=false, b2=false;
	for(unsigned int j = 0 ; j < e1->genParticleRefs().size() ; j++ ){
		if( e1->genParticle(j)->status() == 1 && abs(e1->genParticle(j)->pdgId()) == 11 ){
			if(abs(e1->genParticle(j)->mother()->pdgId())==11 and e1->genParticle(j)->mother()->status()==3){v1 = e1->genParticle(j)->mother()->p4(); b1=true; break;}
			if(abs(e1->genParticle(j)->mother()->mother()->pdgId())==11 and e1->genParticle(j)->mother()->mother()->status()==3){v1 = e1->genParticle(j)->mother()->mother()->p4(); b1=true; break;}
			if(abs(e1->genParticle(j)->mother()->mother()->mother()->pdgId())==11 and e1->genParticle(j)->mother()->mother()->mother()->status()==3){v1 = e1->genParticle(j)->mother()->mother()->mother()->p4(); b1=true; break;}
			if(abs(e1->genParticle(j)->mother()->mother()->mother()->mother()->pdgId())==11 and e1->genParticle(j)->mother()->mother()->mother()->mother()->status()==3){v1 = e1->genParticle(j)->mother()->mother()->mother()->mother()->p4(); b1=true; break;}
		}
	}
	for(unsigned int j = 0 ; j < e2->genParticleRefs().size() ; j++ ){
		if( e2->genParticle(j)->status() == 1 && abs(e2->genParticle(j)->pdgId()) == 11 ){
			if(abs(e2->genParticle(j)->mother()->pdgId())==11 and e2->genParticle(j)->mother()->status()==3){v2 = e2->genParticle(j)->mother()->p4(); b2=true; break;}
			if(abs(e2->genParticle(j)->mother()->mother()->pdgId())==11 and e2->genParticle(j)->mother()->mother()->status()==3){v2 = e2->genParticle(j)->mother()->mother()->p4(); b2=true; break;}
			if(abs(e2->genParticle(j)->mother()->mother()->mother()->pdgId())==11 and e2->genParticle(j)->mother()->mother()->mother()->status()==3){v2 = e2->genParticle(j)->mother()->mother()->mother()->p4(); b2=true; break;}
			if(abs(e2->genParticle(j)->mother()->mother()->mother()->mother()->pdgId())==11 and e2->genParticle(j)->mother()->mother()->mother()->mother()->status()==3){v2 = e2->genParticle(j)->mother()->mother()->mother()->mother()->p4(); b2=true; break;}
		}
	}

	if(b1 and b2) mass = (v1+v2).M();
	return mass;
}

#endif
