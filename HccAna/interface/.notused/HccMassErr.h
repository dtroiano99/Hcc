#ifndef HZZ4LMASSERR_H
#define HZZ4LMASSERR_H

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

//Angles     
#include "DataFormats/Math/interface/deltaR.h"
#include "DataFormats/Math/interface/deltaPhi.h"
#include "CommonTools/CandUtils/interface/CenterOfMassBooster.h"
#include "CommonTools/CandUtils/interface/Booster.h"
#include "CommonTools/CandUtils/interface/cloneDecayTree.h"

#include "DataFormats/PatCandidates/interface/Electron.h"
#include "DataFormats/PatCandidates/interface/Muon.h"
#include "DataFormats/ParticleFlowCandidate/interface/PFCandidate.h"

//Full Error
#include <cmath>
#include "DataFormats/Candidate/interface/Candidate.h"
#include "DataFormats/EgammaCandidates/interface/GsfElectron.h"
#include "DataFormats/MuonReco/interface/Muon.h"
#include "DataFormats/GsfTrackReco/interface/GsfTrack.h"
#include "FWCore/Framework/interface/EventSetup.h"

#include "TrackingTools/AnalyticalJacobians/interface/JacobianCurvilinearToCartesian.h"
#include "TrackingTools/TrajectoryParametrization/interface/GlobalTrajectoryParameters.h"
#include "TrackingTools/TrajectoryParametrization/interface/CartesianTrajectoryError.h"
#include "MagneticField/Records/interface/IdealMagneticFieldRecord.h"

#include "RecoParticleFlow/PFClusterTools/interface/PFEnergyResolution.h"

#include <TMatrixD.h>

namespace reco { class Candidate; class Muon; class GsfElectron; class Track; class PFCandidate; }
namespace edm { class EventSetup; }

#include <vector>
#include "FWCore/Framework/interface/ESHandle.h"
#include "MagneticField/Engine/interface/MagneticField.h"
#include <TMatrixDSym.h>
#include <boost/shared_ptr.hpp>

class HZZ4LMassErr
{
  public:
    HZZ4LMassErr();
    ~HZZ4LMassErr();

    double masserror(std::vector<TLorentzVector> Lep, std::vector<double> pterr);
    double calc4eErr(std::vector<pat::Electron> electrons, std::vector<pat::PFParticle> fsrPhotons, bool corr, bool isData); 
    double calc4muErr(std::vector<pat::Muon> muons, std::vector< pat::PFParticle> fsrPhotons, bool corr, bool isData); 
    double calc2e2muErr(std::vector<pat::Electron> electrons, std::vector<pat::Muon> muons, std::vector<pat::PFParticle> fsrPhotons, 
                        bool corr, bool isData);
    double getMassResolution(std::vector<pat::Electron>& electrons, std::vector<pat::Muon>& muons, 
                             std::vector<pat::PFParticle>& fsrPhotons);
    double getIndividualMassError(const reco::Candidate &c, int order, std::vector<pat::Electron>& electrons, 
                                  std::vector<pat::Muon>& muons, std::vector<pat::PFParticle>& fsrPhotons); 
    double getMassResolutionCorr(std::vector<pat::Electron>& electrons, std::vector<pat::Muon>& muons, 
                                 std::vector<pat::PFParticle>& fsrPhotons, bool corr, bool isData);
    void setdebug(int d){debug_= d;};

    //ForZ
    double calc2eErr(std::vector<pat::Electron> electrons, bool corr, bool isData);
    double calc2muErr(std::vector<pat::Muon> muons, bool corr, bool isData);
    double getZMassResolution(const std::vector<const pat::Electron*>& electrons);
    double getZMassResolution(const std::vector<const pat::Muon*>& muons);

    void init(const edm::EventSetup &iSetup);
    //double getMassResolution(const reco::Candidate &c) const ;

  private:
    void   fillP3Covariance(const reco::Candidate &c, TMatrixDSym &bigCov, int offset) const ;
    void   fillP3Covariance(const reco::GsfElectron &c, TMatrixDSym &bigCov, int offset) const ;
    void   fillP3Covariance(const reco::Muon &c, TMatrixDSym &bigCov, int offset) const ;
    void   fillP3Covariance(const reco::PFCandidate &c, TMatrixDSym &bigCov, int offset) const ;
    void   fillP3Covariance(const reco::Candidate &c, const reco::Track &t, TMatrixDSym &bigCov, int offset) const ;

    edm::ESHandle<MagneticField> magfield_;

    // 1 if this is a lead, recursive number of leafs if composite
    //void getLeaves(const reco::Candidate &c, std::vector<const reco::Candidate *> &out) const ;

    //double scaleFactor_mu ;
    int debug_;

    boost::shared_ptr<TFile>     fmu;
    boost::shared_ptr<TFile>     fel;
    boost::shared_ptr<TH2F>      muon_corr_data;
    boost::shared_ptr<TH2F>      muon_corr_mc; 
    boost::shared_ptr<TH2F>      electron_corr_data;
    boost::shared_ptr<TH2F>      electron_corr_mc;
};


#endif


#ifndef HZZ4LMASSERR_CC
#define HZZ4LMASSERR_CC
HZZ4LMassErr::HZZ4LMassErr()
{
  //declarations
  debug_ = 0;
  TString fmu_s, fel_s;
  fmu_s = TString(edm::FileInPath ( "UFHZZAnalysisRun2/UFHZZ4LAna/data/ebeOverallCorrections.Legacy2013.v0.root" ).fullPath());
  fel_s = TString(edm::FileInPath ( "UFHZZAnalysisRun2/UFHZZ4LAna/data/ebeOverallCorrections.Legacy2013.v0.root" ).fullPath());

  fmu = boost::shared_ptr<TFile>( new TFile(fmu_s)); 
  fel = boost::shared_ptr<TFile>( new TFile(fel_s));
  muon_corr_data = boost::shared_ptr<TH2F>(  (static_cast<TH2F*>(fmu->Get( "mu_reco53x" )->Clone() )) );
  muon_corr_mc = boost::shared_ptr<TH2F>(  (static_cast<TH2F*>(fmu->Get( "mu_mc53x" )->Clone() )) );
  electron_corr_data = boost::shared_ptr<TH2F>(  (static_cast<TH2F*>(fel->Get( "el_reco53x" )->Clone() )) ); 
  electron_corr_mc = boost::shared_ptr<TH2F>(  (static_cast<TH2F*>(fel->Get( "el_mc53x" )->Clone() )) );
}


HZZ4LMassErr::~HZZ4LMassErr()
{
}

void HZZ4LMassErr::init(const edm::EventSetup &iSetup) 
{
  iSetup.get<IdealMagneticFieldRecord>().get(magfield_);
}

/*
   void HZZ4LMassErr::getLeaves(const reco::Candidate &c, std::vector<const reco::Candidate *> &out) const {
   if (c.hasMasterClonePtr()) {
   getLeaves(*c.masterClonePtr(), out);
   } else if (c.hasMasterClone()) {
   getLeaves(*c.masterClone(), out);
   } else if (c.numberOfDaughters() > 0 &&                                             // Descend into composite objects
   (c.pdgId() != 22 || dynamic_cast<const reco::PFCandidate *>(&c) == 0)) { // but not PF photons:
//std::cout << "Descending leaves of a candidate of type " << typeid(c).name() << " with pdgId = " << c.pdgId() << " and charge " << c.charge() << std::endl;
for (int i = 0, n = c.numberOfDaughters(); i < n; ++i) {
getLeaves(*c.daughter(i), out);
}
} else {
//std::cout << "Requested to add to the list a candidate of type " << typeid(c).name() << " with pdgId = " << c.pdgId() << std::endl;
out.push_back(&c);
}
}
*/

double HZZ4LMassErr::getMassResolution( std::vector<pat::Electron>& electrons, std::vector<pat::Muon>& muons, std::vector<pat::PFParticle>& fsrPhotons)  
{ 
  //std::vector<const reco::Candidate *> leaves;
  //getLeaves(c, leaves);
  int nel = electrons.size(); int nmu = muons.size(); int nph = fsrPhotons.size(); 
  int ndim = (nel+nmu+nph)*3;

  double px = 0; double py = 0; double pz = 0; double e =0;
  for(int i =0; i<nel; i++)
  {
    const reco::Candidate &ci = *dynamic_cast<const reco::Candidate* >(&electrons[i]);
    px = px + ci.px(); py = py + ci.py(); pz = pz + ci.pz(); e = e + ci.energy();
  }
  for(int i =0; i<nmu; i++)
  {
    const reco::Candidate &ci = *dynamic_cast<const reco::Candidate* >(&muons[i]);
    px = px + ci.px(); py = py + ci.py(); pz = pz + ci.pz(); e = e + ci.energy();
  }
  for(int i =0; i<nph; i++)
  {
    const reco::Candidate &ci = *dynamic_cast<const reco::Candidate* >(&fsrPhotons[i]);
    px = px + ci.px(); py = py + ci.py(); pz = pz + ci.pz(); e = e + ci.energy();
  }
  double mass =sqrt(e*e-px*px-py*py-pz*pz);
  TMatrixDSym bigCov(ndim);
  TMatrixD jacobian(1,ndim);
  for (int i = 0, o = 0; i < nel; ++i, o += 3) 
  {
    const reco::Candidate &ci = *dynamic_cast<const reco::Candidate* >(&electrons[i]);
    fillP3Covariance(ci, bigCov, o);
    jacobian(0, o+0) = (e*(ci.px()/ci.energy()) - px)/mass;
    jacobian(0, o+1) = (e*(ci.py()/ci.energy()) - py)/mass;
    jacobian(0, o+2) = (e*(ci.pz()/ci.energy()) - pz)/mass;
  }
  for (int i = 0, o = nel*3; i < nmu; ++i, o += 3)  
  {
    const reco::Candidate &ci = *dynamic_cast<const reco::Candidate* >(&muons[i]);
    fillP3Covariance(ci, bigCov, o);
    jacobian(0, o+0) = (e*(ci.px()/ci.energy()) - px)/mass;
    jacobian(0, o+1) = (e*(ci.py()/ci.energy()) - py)/mass;
    jacobian(0, o+2) = (e*(ci.pz()/ci.energy()) - pz)/mass;
  }
  for (int i = 0, o = (nel+nmu)*3; i < nph; ++i, o += 3) 
  {
    const reco::Candidate &ci = *dynamic_cast<const reco::Candidate* >(&fsrPhotons[i]);
    fillP3Covariance(ci, bigCov, o);
    jacobian(0, o+0) = (e*(ci.px()/ci.energy()) - px)/mass;
    jacobian(0, o+1) = (e*(ci.py()/ci.energy()) - py)/mass;
    jacobian(0, o+2) = (e*(ci.pz()/ci.energy()) - pz)/mass;
  }

  TMatrixDSym massCov = bigCov.Similarity(jacobian);
  double dm2 = massCov(0,0);
  return (dm2 > 0 ? sqrt(dm2) : 0.0);
}


double HZZ4LMassErr::getIndividualMassError(const reco::Candidate &c, int offset, std::vector<pat::Electron>& electrons, 
                     std::vector<pat::Muon>& muons, std::vector<pat::PFParticle>& fsrPhotons)  
{
  int nel = electrons.size(); int nmu = muons.size(); int nph = fsrPhotons.size(); 
  int ndim = (nel+nmu+nph)*3;

  TMatrixDSym bigCov(ndim);
  TMatrixD jacobian(1,ndim);

  double px = 0; double py = 0; double pz = 0; double e =0;
  for(int i =0; i<nel; i++)
  {		
    const reco::Candidate &ci = *dynamic_cast<const reco::Candidate* >(&electrons[i]);
    px = px + ci.px(); py = py + ci.py(); pz = pz + ci.pz(); e = e + ci.energy();
  }
  for(int i =0; i<nmu; i++)
  {
    const reco::Candidate &ci = *dynamic_cast<const reco::Candidate* >(&muons[i]); 
    px = px + ci.px(); py = py + ci.py(); pz = pz + ci.pz(); e = e + ci.energy();
  }
  for(int i =0; i<nph; i++)
  {
    const reco::Candidate &ci = *dynamic_cast<const reco::Candidate* >(&fsrPhotons[i]);
    px = px + ci.px(); py = py + ci.py(); pz = pz + ci.pz(); e = e + ci.energy();
  }
  double mass =sqrt(e*e-px*px-py*py-pz*pz);

  for (int i = 0, o = 0; i < nel; ++i, o += 3) 
  {
    const reco::Candidate &ci = *dynamic_cast<const reco::Candidate* >(&electrons[i]);
    fillP3Covariance(ci, bigCov, o);
    jacobian(0, o+0) = (e*(ci.px()/ci.energy()) - px)/mass;
    jacobian(0, o+1) = (e*(ci.py()/ci.energy()) - py)/mass;
    jacobian(0, o+2) = (e*(ci.pz()/ci.energy()) - pz)/mass;
  }
  for (int i = 0, o = nel*3; i < nmu; ++i, o += 3) 
  {
    const reco::Candidate &ci = *dynamic_cast<const reco::Candidate* >(&muons[i]);
    fillP3Covariance(ci, bigCov, o); 
    jacobian(0, o+0) = (e*(ci.px()/ci.energy()) - px)/mass;
    jacobian(0, o+1) = (e*(ci.py()/ci.energy()) - py)/mass;
    jacobian(0, o+2) = (e*(ci.pz()/ci.energy()) - pz)/mass;
  }
  for (int i = 0, o = (nel+nmu)*3; i < nph; ++i, o += 3) 
  {
    const reco::Candidate &ci = *dynamic_cast<const reco::Candidate* >(&fsrPhotons[i]);
    fillP3Covariance(ci, bigCov, o);
    jacobian(0, o+0) = (e*(ci.px()/ci.energy()) - px)/mass;
    jacobian(0, o+1) = (e*(ci.py()/ci.energy()) - py)/mass;
    jacobian(0, o+2) = (e*(ci.pz()/ci.energy()) - pz)/mass;
  }

  TMatrixDSym bigCovOne(ndim);
  for (int ir = 0; ir < 3; ++ir) 
  { 
    for (int ic = 0; ic < 3; ++ic) 
    {
      bigCovOne(offset+ir,offset+ic) = bigCov(offset+ir,offset+ic);
    } 
  }
  double dm2 = bigCovOne.Similarity(jacobian)(0,0);
  return ( dm2 > 0 ? std::sqrt(dm2) : 0.0 );
}


double HZZ4LMassErr::getMassResolutionCorr(std::vector<pat::Electron>& electrons, std::vector<pat::Muon>& muons, 
                    std::vector<pat::PFParticle>& fsrPhotons, bool corr, bool isData)  
{
  double dm2 = 0.0;
  int o = 0;   
  std::cout <<"i am at 290 \n";
  int nel = electrons.size(); int nmu = muons.size(); int nph = fsrPhotons.size();

  // electron
  TH2F* el_corr;
   std::cout <<"i am at 295 \n";
  if(isData) el_corr = dynamic_cast<TH2F*>(electron_corr_data->Clone());
  else el_corr = dynamic_cast<TH2F*>(electron_corr_mc->Clone());
  std:: cout <<"i am at 298 \n";
  TAxis* x_elpTaxis = el_corr->GetXaxis(); TAxis* y_eletaaxis = el_corr->GetYaxis();
  double maxPt = x_elpTaxis->GetXmax(); double minPt = x_elpTaxis->GetXmin();
  std:: cout <<"i am at 301 \n";
  for(int i =0; i<nel; i++)
  {
     std::cout <<"i am at 304 \n";
    const reco::Candidate &ci = *dynamic_cast<const reco::Candidate* >(&electrons[i]);
    double dm_raw = getIndividualMassError( ci, o, electrons, muons, fsrPhotons);
    o = o+3;  
    double scale = 1.0;
    int xbin = x_elpTaxis->FindFixBin(electrons[i].pt()); int ybin = y_eletaaxis->FindFixBin(fabs(electrons[i].eta()));
    if(corr && electrons[i].pt()>minPt && electrons[i].pt()<maxPt){  scale = el_corr->GetBinContent(xbin,ybin);  }

    double dm2_corr = scale*scale*dm_raw*dm_raw;
    dm2 = dm2 + dm2_corr;
  
  }

  // muon
  TH2F* mu_corr;
   std::cout <<"i am at 319 \n";
  if(isData) mu_corr = dynamic_cast<TH2F*>(muon_corr_data->Clone());
  else mu_corr = dynamic_cast<TH2F*>(muon_corr_mc->Clone());

  TAxis* x_mupTaxis = mu_corr->GetXaxis(); TAxis* y_muetaaxis = mu_corr->GetYaxis();
  double maxPt_mu = x_mupTaxis->GetXmax(); double minPt_mu = x_mupTaxis->GetXmin();
   std::cout <<"i am at 325 \n";
  for(int i =0; i<nmu; i++)
  {
     std::cout <<"i am at 328 \n";
    const reco::Candidate &ci = *dynamic_cast<const reco::Candidate* >(&muons[i]);
    double dm_raw = getIndividualMassError( ci, o, electrons, muons, fsrPhotons);
    o = o+3;  
    double scale = 1.0;
    int xbin = x_mupTaxis->FindFixBin(muons[i].pt()); int ybin = y_muetaaxis->FindFixBin(fabs(muons[i].eta()));
    if(corr && muons[i].pt()>minPt_mu && muons[i].pt()<maxPt_mu){  scale = mu_corr->GetBinContent(xbin,ybin);  }
    double dm2_corr = scale*scale*dm_raw*dm_raw;
    dm2 = dm2 + dm2_corr;
  }

  // fsr photon
  for(int i =0; i<nph; i++)
  {
    std:: cout <<"i am at 342 \n";
    const reco::Candidate &ci = *dynamic_cast<const reco::Candidate* >(&fsrPhotons[i]);
    double dm_raw = getIndividualMassError( ci, o, electrons, muons, fsrPhotons);
    o = o+3;  
    double scale = 1.0;
    double dm2_corr = scale*scale*dm_raw*dm_raw;
    dm2 = dm2 + dm2_corr;
  }

  return (dm2 > 0 ? std::sqrt(dm2) : 0.0);
}


/*
   double HZZ4LMassErr::getMassResolution(const reco::Candidate &c) const  {
   std::vector<const reco::Candidate *> leaves;
   getLeaves(c, leaves);
   int n = leaves.size(), ndim = n*3;
   TMatrixDSym bigCov(ndim);
   TMatrixD jacobian(1,ndim);
   for (int i = 0, o = 0; i < n; ++i, o += 3) {
   const reco::Candidate &ci = *leaves[i];
   fillP3Covariance(ci, bigCov, o);
   jacobian(0, o+0) = (c.energy()*(ci.px()/ci.energy()) - c.px())/c.mass();
   jacobian(0, o+1) = (c.energy()*(ci.py()/ci.energy()) - c.py())/c.mass();
   jacobian(0, o+2) = (c.energy()*(ci.pz()/ci.energy()) - c.pz())/c.mass();
   }

   TMatrixDSym massCov = bigCov.Similarity(jacobian);

   double dm2 = massCov(0,0);
   return (dm2 > 0 ? std::sqrt(dm2) : 0.0);
   }
   */


void HZZ4LMassErr::fillP3Covariance(const reco::Candidate &c, TMatrixDSym &bigCov, int offset) const 
{
  const reco::GsfElectron *gsf; const reco::Muon *mu; const reco::PFCandidate *pf;
  if ((gsf = dynamic_cast<const reco::GsfElectron *>(&c)) != 0) 
  {
    fillP3Covariance(*gsf, bigCov, offset);
  } 
  else if ((mu = dynamic_cast<const reco::Muon *>(&c)) != 0) 
  {
    fillP3Covariance(*mu, bigCov, offset);
  }    
  else if ((pf = dynamic_cast<const reco::PFCandidate *>(&c)) != 0 && pf->pdgId() == 22) 
  {
    fillP3Covariance(*pf, bigCov, offset);
  } 
  else 
  {
    //throw cms::Exception("Unknown type") << "Candidate of type " << typeid(c).name() << " and pdgId = " << c.pdgId() << "\n";
    // miniAOD skip exception just do nothing.
  }
}

void HZZ4LMassErr::fillP3Covariance(const reco::Muon &c, TMatrixDSym &bigCov, int offset) const 
{
  fillP3Covariance(c, *c.muonBestTrack(), bigCov, offset);
}


void HZZ4LMassErr::fillP3Covariance(const reco::GsfElectron &c, TMatrixDSym &bigCov, int offset) const 
{
  double dp = 0.;
  if (c.ecalDriven()) 
  {
    dp = c.p4Error(reco::GsfElectron::P4_COMBINATION);
  }
  else 
  {
    // Parametrization from Claude Charlot, 
    // http://cmssw.cvs.cern.ch/cgi-bin/cmssw.cgi/UserCode/CJLST/ZZAnalysis/AnalysisStep/src/ZZMassErrors.cc?revision=1.2&view=markup
#if CMSSW_VERSION<500
    double ecalEnergy = c.ecalEnergy() ;
#else
    double ecalEnergy = c.correctedEcalEnergy() ;
#endif
    double err2 = 0.0;
    if (c.isEB()) 
    {
      err2 += (5.24e-02*5.24e-02)/ecalEnergy;  
      err2 += (2.01e-01*2.01e-01)/(ecalEnergy*ecalEnergy);
      err2 += 1.00e-02*1.00e-02;
    } 
    else if (c.isEE()) 
    {
      err2 += (1.46e-01*1.46e-01)/ecalEnergy;  
      err2 += (9.21e-01*9.21e-01)/(ecalEnergy*ecalEnergy);
      err2 += 1.94e-03*1.94e-03;
    }
    dp = ecalEnergy * sqrt(err2);
  }
  // In order to produce a 3x3 matrix, we need a jacobian from (p) to (px,py,pz), i.e.
  //            [ Px/P  ]                
  //  C_(3x3) = [ Py/P  ] * sigma^2(P) * [ Px/P Py/P Pz/P  ]
  //            [ Pz/P  ]                
  AlgebraicMatrix31 ptop3;
  ptop3(0,0) = c.px()/c.p();
  ptop3(1,0) = c.py()/c.p();
  ptop3(2,0) = c.pz()/c.p();
  AlgebraicSymMatrix33 mat = ROOT::Math::Similarity(ptop3, AlgebraicSymMatrix11(dp*dp) );
  for (int i = 0; i < 3; ++i) 
  { 
    for (int j = 0; j < 3; ++j) 
    {
      bigCov(offset+i,offset+j) = mat(i,j);
    } 
  } 

}

void HZZ4LMassErr::fillP3Covariance(const reco::Candidate &c, const reco::Track &t, TMatrixDSym &bigCov, int offset) const 
{
  GlobalTrajectoryParameters gp(GlobalPoint(t.vx(), t.vy(),  t.vz()),
                            GlobalVector(t.px(),t.py(),t.pz()),
                            t.charge(),	magfield_.product());
  JacobianCurvilinearToCartesian curv2cart(gp);
  CartesianTrajectoryError cartErr= ROOT::Math::Similarity(curv2cart.jacobian(), t.covariance());
  const AlgebraicSymMatrix66 mat = cartErr.matrix();
  for (int i = 0; i < 3; ++i) 
  { 
    for (int j = 0; j < 3; ++j) 
    {
      bigCov(offset+i,offset+j) = mat(i+3,j+3);
    } 
  } 
}

void HZZ4LMassErr::fillP3Covariance(const reco::PFCandidate &c, TMatrixDSym &bigCov, int offset) const 
{
  double dp = PFEnergyResolution().getEnergyResolutionEm(c.energy(), c.eta());
  // In order to produce a 3x3 matrix, we need a jacobian from (p) to (px,py,pz), i.e.
  //            [ Px/P  ]                
  //  C_(3x3) = [ Py/P  ] * sigma^2(P) * [ Px/P Py/P Pz/P  ]
  //            [ Pz/P  ]                
  AlgebraicMatrix31 ptop3;
  ptop3(0,0) = c.px()/c.p();
  ptop3(1,0) = c.py()/c.p();
  ptop3(2,0) = c.pz()/c.p();
  AlgebraicSymMatrix33 mat = ROOT::Math::Similarity(ptop3, AlgebraicSymMatrix11(dp*dp) );
  for (int i = 0; i < 3; ++i) 
  { 
    for (int j = 0; j < 3; ++j) 
    {
      bigCov(offset+i,offset+j) = mat(i,j);
    } 
  } 
}

/////////////////////////////////////////////////

double HZZ4LMassErr::masserror( std::vector<TLorentzVector> Lep, std::vector<double> pterr)
{ 
  // if(Lep.size()!=4 or pterr.size()!=4) {std::cout<<" Lepsize="<<Lep.size()<<", "<<pterr.size()<<std::endl;}
  TLorentzVector compositeParticle ;
  for(unsigned int i=0; i<Lep.size(); i++)
  {
    compositeParticle+=Lep[i];
    if(debug_) std::cout<<" in mass error :  add lep  "<<i<<std::endl;
  }
  double mass  =  compositeParticle.M();

  if(debug_) std::cout<<" in mass error :  mass "<<mass<<std::endl;
  double masserr = 0;
 
  for(unsigned int i=0; i<Lep.size(); i++)
  {
    if(debug_) std::cout<<" in mass error :  varying lep "<<i<<std::endl;
    TLorentzVector variedLep; // = Lep[i];
    if(debug_) std::cout<<" in mass error : pterr = "<<pterr[i]<<std::endl;
    variedLep.SetPtEtaPhiM(Lep[i].Pt()+ pterr[i], Lep[i].Eta(), Lep[i].Phi(), Lep[i].M());
    TLorentzVector compositeParticleVariation ;
    for(unsigned int j=0; j<Lep.size(); j++)
    {
      if(i!=j)compositeParticleVariation+=Lep[j];
      else compositeParticleVariation+=variedLep;
    }
    masserr += (compositeParticleVariation.M()-mass)*(compositeParticleVariation.M()-mass);
    if(debug_) std::cout<<" in mass error :  intermediate masserr "<<masserr<<std::endl;
  }

  return sqrt(masserr);
}

double HZZ4LMassErr::calc4muErr(std::vector<pat::Muon> muons, std::vector<pat::PFParticle> fsrPhotons, bool corr, bool isData )
{
  //if(muons.size() != 4) printf("[calc4muErr] Warning: number of muons is not 4, but %d \n", (int)(muons.size()));
  std::vector<TLorentzVector> vtlv; vtlv.clear();
  std::vector<double> vpterr; vpterr.clear();

  TH2F* mu_corr;
  if(isData) mu_corr = dynamic_cast<TH2F*>(muon_corr_data->Clone());
  else mu_corr = dynamic_cast<TH2F*>(muon_corr_mc->Clone());

  TAxis* x_mupTaxis = mu_corr->GetXaxis(); TAxis* y_muetaaxis = mu_corr->GetYaxis();
  double maxPt = x_mupTaxis->GetXmax(); double minPt = x_mupTaxis->GetXmin();

  for(unsigned int i=0; i< muons.size(); i++)
  {
    const pat::Muon *mu = &(muons[i]);
    TLorentzVector tlv; tlv.SetPtEtaPhiM(mu->pt(), mu->eta(), mu->phi(), 0.1066 );  
    double scaleFactor_mu = 1.0;
    int xbin = x_mupTaxis->FindBin(mu->pt()); int ybin = y_muetaaxis->FindBin(fabs(mu->eta()));
    if(corr && mu->pt()>minPt && mu->pt()<maxPt){  scaleFactor_mu = mu_corr->GetBinContent(xbin,ybin);  }
    vpterr.push_back(mu->muonBestTrack()->ptError() * scaleFactor_mu );
    vtlv.push_back(tlv);
  }
  for(unsigned int i=0; i< fsrPhotons.size(); i++)
  {
    const pat::PFParticle *ph = &(fsrPhotons[i]);
    TLorentzVector tlv; tlv.SetPtEtaPhiM(ph->pt(), ph->eta(), ph->phi(), 0 );    		
    double perr = PFEnergyResolution().getEnergyResolutionEm(ph->energy(), ph->eta());
    double pterr = perr*ph->pt()/ph->p(); 
    vpterr.push_back( pterr );
    vtlv.push_back(tlv);
  }
  return masserror(vtlv, vpterr);
}

double HZZ4LMassErr::calc4eErr(std::vector<pat::Electron> electrons, std::vector<pat::PFParticle> fsrPhotons, 
              bool corr, bool isData)
{
  //if(electrons.size() != 4) printf("[calc4eErr] Warning: number of electrons is not 4, but %d \n", (int)electrons.size());
  std::vector<TLorentzVector> vtlv; vtlv.clear();
  std::vector<double> vpterr; vpterr.clear();

  TH2F* el_corr;

  if(isData) el_corr = dynamic_cast<TH2F*>(electron_corr_data->Clone());
  else el_corr = dynamic_cast<TH2F*>(electron_corr_mc->Clone());

  TAxis* x_elpTaxis = el_corr->GetXaxis(); TAxis* y_eletaaxis = el_corr->GetYaxis();
  double maxPt = x_elpTaxis->GetXmax(); double minPt = x_elpTaxis->GetXmin();

  for(unsigned int i=0; i< electrons.size(); i++)
  {
    const pat::Electron *elec = &(electrons[i]);
    TLorentzVector tlv; tlv.SetPtEtaPhiM(elec->pt(), elec->eta(), elec->phi(), 0.000511); 
    vtlv.push_back(tlv);
    //double perr = elec->p4Error(reco::GsfElectron::P4_COMBINATION);
    //double pterr = perr*elec->pt()/elec->p();
    //if(perr > 998) pterr = elec->gsfTrack()->ptError();

    double perr = 0.;
    if (elec->ecalDriven()) 
    {
      perr = elec->p4Error(reco::GsfElectron::P4_COMBINATION);
      if(debug_) std::cout << "ecal driven: " << perr << std::endl;
    }
    else
    {
      // Parametrization from Claude Charlot, 
      // http://cmssw.cvs.cern.ch/cgi-bin/cmssw.cgi/UserCode/CJLST/ZZAnalysis/AnalysisStep/src/ZZMassErrors.cc?revision=1.2&view=markup
#if CMSSW_VERSION<500
      double ecalEnergy = elec->ecalEnergy() ;
#else
      double ecalEnergy = elec->correctedEcalEnergy() ;
#endif			
      double err2 = 0.0;
      if (elec->isEB()) 
      {
        err2 += (5.24e-02*5.24e-02)/ecalEnergy;  
        err2 += (2.01e-01*2.01e-01)/(ecalEnergy*ecalEnergy);
        err2 += 1.00e-02*1.00e-02;
      } 
      else if (elec->isEE()) 
      {
        err2 += (1.46e-01*1.46e-01)/ecalEnergy;  
        err2 += (9.21e-01*9.21e-01)/(ecalEnergy*ecalEnergy);
        err2 += 1.94e-03*1.94e-03;
      }
      perr = ecalEnergy * sqrt(err2);
      if(debug_) std::cout << "not ecal driven: " << perr << "  " << ecalEnergy << "  " << err2 << std::endl;
    }     

    double scaleFactor_el = 1.0;
    int xbin = x_elpTaxis->FindBin(elec->pt()); 
    int ybin = y_eletaaxis->FindBin(fabs(elec->eta()));
    if(corr && elec->pt()>minPt && elec->pt()<maxPt){  scaleFactor_el = el_corr->GetBinContent(xbin,ybin);  }

    double pterr = scaleFactor_el*(perr*elec->pt()/elec->p());
    //double pterr = elec->gsfTrack()->ptModeError();
    vpterr.push_back(pterr);
  }

  for(unsigned int i=0; i< fsrPhotons.size(); i++)
  {
    const pat::PFParticle *ph = &(fsrPhotons[i]);
    TLorentzVector tlv; tlv.SetPtEtaPhiM(ph->pt(), ph->eta(), ph->phi(), 0 );    		
    double perr = PFEnergyResolution().getEnergyResolutionEm(ph->energy(), ph->eta());
    double pterr = perr*ph->pt()/ph->p(); 
    vpterr.push_back( pterr );
    vtlv.push_back(tlv);
  }

  return masserror(vtlv, vpterr);
}

double HZZ4LMassErr::calc2e2muErr(std::vector<pat::Electron> electrons, std::vector<pat::Muon> muons, 
                 std::vector<pat::PFParticle> fsrPhotons, bool corr, bool isData)
{
  //if(muons.size() != 2) printf("[calc2e2muErr] Warning: number of muons is not 2, but %d \n", (int)muons.size());
  std::vector<TLorentzVector> vtlv; vtlv.clear();
  std::vector<double> vpterr; vpterr.clear();

  TH2F* mu_corr; TH2F* el_corr; 
  if(isData) { mu_corr = dynamic_cast<TH2F*>(muon_corr_data->Clone()); el_corr = dynamic_cast<TH2F*>(electron_corr_data->Clone()); }
  else { mu_corr = dynamic_cast<TH2F*>(muon_corr_data->Clone()); el_corr = dynamic_cast<TH2F*>(electron_corr_mc->Clone()); }

  TAxis* x_mupTaxis = mu_corr->GetXaxis(); TAxis* y_muetaaxis = mu_corr->GetYaxis();
  double maxMuPt = x_mupTaxis->GetXmax(); double minMuPt = x_mupTaxis->GetXmin();
  TAxis* x_elpTaxis = el_corr->GetXaxis(); TAxis* y_eletaaxis = el_corr->GetYaxis();
  double maxElPt = x_elpTaxis->GetXmax(); double minElPt = x_elpTaxis->GetXmin();

  for(unsigned int i=0; i< muons.size(); i++)
  {
    const pat::Muon *mu = &(muons[i]);
    TLorentzVector tlv; tlv.SetPtEtaPhiM(mu->pt(), mu->eta(), mu->phi(), 0.1066 ); 
    double scaleFactormu = 1.0;
    int xbin = x_mupTaxis->FindBin(mu->pt()); int ybin = y_muetaaxis->FindBin(fabs(mu->eta()));
    if(corr && mu->pt()>minMuPt && mu->pt()<maxMuPt){  scaleFactormu = mu_corr->GetBinContent(xbin,ybin);  }
    vpterr.push_back(mu->muonBestTrack()->ptError() * scaleFactormu );
    vtlv.push_back(tlv);
  }

  //if(electrons.size() != 2) printf("[calc2e2muErr] Warning: number of electrons is not 2, but %d \n", (int)electrons.size());
  for(unsigned int i=0; i< electrons.size(); i++)
  {
    const pat::Electron *elec = &(electrons[i]);
    TLorentzVector tlv; tlv.SetPtEtaPhiM(elec->pt(), elec->eta(), elec->phi(), 0.000511); 
    vtlv.push_back(tlv);
    //double perr = elec->p4Error(reco::GsfElectron::P4_COMBINATION);
    //double pterr = perr*elec->pt()/elec->p();
    //if(perr > 998) pterr = elec->gsfTrack()->ptError();
    double perr = 0.;
    if (elec->ecalDriven()) 
    {
      perr = elec->p4Error(reco::GsfElectron::P4_COMBINATION);
    } 
    else 
    {
      // Parametrization from Claude Charlot, 
      // http://cmssw.cvs.cern.ch/cgi-bin/cmssw.cgi/UserCode/CJLST/ZZAnalysis/AnalysisStep/src/ZZMassErrors.cc?revision=1.2&view=markup
#if CMSSW_VERSION<500
      double ecalEnergy = elec->ecalEnergy() ;
#else
      double ecalEnergy = elec->correctedEcalEnergy() ;
#endif
      double err2 = 0.0;
      if (elec->isEB()) 
      {
        err2 += (5.24e-02*5.24e-02)/ecalEnergy;  
        err2 += (2.01e-01*2.01e-01)/(ecalEnergy*ecalEnergy);
        err2 += 1.00e-02*1.00e-02;
      } 
      else if (elec->isEE()) 
      {
        err2 += (1.46e-01*1.46e-01)/ecalEnergy;  
        err2 += (9.21e-01*9.21e-01)/(ecalEnergy*ecalEnergy);
        err2 += 1.94e-03*1.94e-03;
      }
      perr = ecalEnergy * sqrt(err2);
    }                                

    double scaleFactor_el = 1.0;
    int xbin = x_elpTaxis->FindBin(elec->pt()); int ybin = y_eletaaxis->FindBin(fabs(elec->eta()));
    if(corr && elec->pt()>minElPt && elec->pt()<maxElPt){  scaleFactor_el = el_corr->GetBinContent(xbin,ybin);  }

    double pterr = scaleFactor_el*(perr*elec->pt()/elec->p());
    //double pterr = elec->gsfTrack()->ptModeError();
    vpterr.push_back(pterr);
  }

  for(unsigned int i=0; i< fsrPhotons.size(); i++)
  {
    const pat::PFParticle *ph = &(fsrPhotons[i]);
    TLorentzVector tlv; tlv.SetPtEtaPhiM(ph->pt(), ph->eta(), ph->phi(), 0 );    		
    double perr = PFEnergyResolution().getEnergyResolutionEm(ph->energy(), ph->eta());
    double pterr = perr*ph->pt()/ph->p(); 
    vpterr.push_back( pterr );
    vtlv.push_back(tlv);
  }

  return masserror(vtlv, vpterr);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////

double HZZ4LMassErr::calc2muErr( std::vector< pat::Muon > muons , bool corr, bool isData)
{
  //if(muons.size() != 4) printf("[calc4muErr] Warning: number of muons is not 4, but %d \n", (int)(muons.size()));
  std::vector<TLorentzVector> vtlv; vtlv.clear();
  std::vector<double> vpterr; vpterr.clear();      

  TH2F* mu_corr;
  if(isData) mu_corr = dynamic_cast<TH2F*> (muon_corr_data->Clone());
  else mu_corr = dynamic_cast<TH2F*> (muon_corr_mc->Clone());

  TAxis* x_mupTaxis = mu_corr->GetXaxis(); TAxis* y_muetaaxis = mu_corr->GetYaxis();
  double maxPt = x_mupTaxis->GetXmax(); double minPt = x_mupTaxis->GetXmin();

  for(unsigned int i=0; i< muons.size(); i++)
  {
    const pat::Muon *mu = &(muons[i]);
    TLorentzVector tlv; tlv.SetPtEtaPhiM(mu->pt(), mu->eta(), mu->phi(), 0.1066 );  
    double scaleFactormu = 1.0;
    int xbin = x_mupTaxis->FindBin(mu->pt()); int ybin = y_muetaaxis->FindBin(fabs(mu->eta()));
    if(corr && mu->pt()>minPt && mu->pt()<maxPt){  scaleFactormu = mu_corr->GetBinContent(xbin,ybin);  }
    vpterr.push_back(mu->muonBestTrack()->ptError() * scaleFactormu );
    vtlv.push_back(tlv);
  } 

  return masserror(vtlv, vpterr);
}

double HZZ4LMassErr::calc2eErr( std::vector< pat::Electron > electrons, bool corr, bool isData )
{
  //if(electrons.size() != 4) printf("[calc4eErr] Warning: number of electrons is not 4, but %d \n", (int)electrons.size());
  std::vector<TLorentzVector> vtlv; vtlv.clear();
  std::vector<double> vpterr; vpterr.clear();

  TH2F* el_corr;
  if(isData) el_corr = dynamic_cast<TH2F*>(electron_corr_data->Clone());
  else el_corr = dynamic_cast<TH2F*>(electron_corr_mc->Clone());

  TAxis* x_elpTaxis = el_corr->GetXaxis(); TAxis* y_eletaaxis = el_corr->GetYaxis();
  double maxPt = x_elpTaxis->GetXmax(); double minPt = x_elpTaxis->GetXmin();

  for(unsigned int i=0; i< electrons.size(); i++)
  {
    const pat::Electron *elec = &(electrons[i]);
    TLorentzVector tlv; tlv.SetPtEtaPhiM(elec->pt(), elec->eta(), elec->phi(), 0.000511); 
    vtlv.push_back(tlv);
    //double perr = elec->p4Error(reco::GsfElectron::P4_COMBINATION);
    //double pterr = perr*elec->pt()/elec->p();
    //if(perr > 998) pterr = elec->gsfTrack()->ptError();
    double perr = 0.;
    if (elec->ecalDriven()) 
    {
      perr = elec->p4Error(reco::GsfElectron::P4_COMBINATION);
    }  
    else 
    {
      // Parametrization from Claude Charlot, 
      // http://cmssw.cvs.cern.ch/cgi-bin/cmssw.cgi/UserCode/CJLST/ZZAnalysis/AnalysisStep/src/ZZMassErrors.cc?revision=1.2&view=markup
#if CMSSW_VERSION<500
      double ecalEnergy = elec->ecalEnergy() ;
#else
      double ecalEnergy = elec->correctedEcalEnergy() ;
#endif
      double err2 = 0.0;
      if (elec->isEB()) 
      {
        err2 += (5.24e-02*5.24e-02)/ecalEnergy;  
        err2 += (2.01e-01*2.01e-01)/(ecalEnergy*ecalEnergy);
        err2 += 1.00e-02*1.00e-02;
      } 
      else if (elec->isEE()) 
      {
        err2 += (1.46e-01*1.46e-01)/ecalEnergy;  
        err2 += (9.21e-01*9.21e-01)/(ecalEnergy*ecalEnergy);
        err2 += 1.94e-03*1.94e-03;
      }
      perr = ecalEnergy * sqrt(err2);
    }                         

    double scaleFactor_el = 1.0;
    int xbin = x_elpTaxis->FindBin(elec->pt()); int ybin = y_eletaaxis->FindBin(fabs(elec->eta()));
    if(corr && elec->pt()>minPt && elec->pt()<maxPt ){  scaleFactor_el = el_corr->GetBinContent(xbin,ybin);  }
    double pterr = scaleFactor_el*(perr*elec->pt()/elec->p());
    //double pterr = elec->gsfTrack()->ptModeError();
    vpterr.push_back(pterr);
  }
  return masserror(vtlv, vpterr);
}


double HZZ4LMassErr::getZMassResolution(const std::vector<const pat::Electron *>& electrons) 
{
  //std::vector<const reco::Candidate *> leaves;
  //getLeaves(c, leaves);
  int nel = electrons.size();  
  int ndim = nel*3;

  double px = 0; double py = 0; double pz = 0; double e =0;
  for(int i =0; i<nel; i++)
  {
    const reco::Candidate &ci = *dynamic_cast<const reco::Candidate* >(electrons[i]);
    px = px + ci.px(); py = py + ci.py(); pz = pz + ci.pz(); e = e + ci.energy();
  }
  double mass =sqrt(e*e-px*px-py*py-pz*pz);

  TMatrixDSym bigCov(ndim);
  TMatrixD jacobian(1,ndim);
  for (int i = 0, o = 0; i < nel; ++i, o += 3) 
  {
    const reco::Candidate &ci = *dynamic_cast<const reco::Candidate* >(electrons[i]);
    fillP3Covariance(ci, bigCov, o);
    jacobian(0, o+0) = (e*(ci.px()/ci.energy()) - px)/mass;
    jacobian(0, o+1) = (e*(ci.py()/ci.energy()) - py)/mass;
    jacobian(0, o+2) = (e*(ci.pz()/ci.energy()) - pz)/mass;
  }

  TMatrixDSym massCov = bigCov.Similarity(jacobian);

  double dm2 = massCov(0,0);
  return (dm2 > 0 ? std::sqrt(dm2) : 0.0);
}

double HZZ4LMassErr::getZMassResolution(const std::vector<const pat::Muon *>& muons)  
{
  //std::vector<const reco::Candidate *> leaves;
  //getLeaves(c, leaves);
  int nmu = muons.size();  
  int ndim = nmu*3;

  double px = 0; double py = 0; double pz = 0; double e =0;
  for(int i =0; i<nmu; i++)
  {
    const reco::Candidate &ci = *dynamic_cast<const reco::Candidate* >(muons[i]);
    px = px + ci.px(); py = py + ci.py(); pz = pz + ci.pz(); e = e + ci.energy();
  }

  double mass =sqrt(e*e-px*px-py*py-pz*pz);
  TMatrixDSym bigCov(ndim);
  TMatrixD jacobian(1,ndim);

  for (int i = 0, o = 0; i < nmu; ++i, o += 3) 
  {
    const reco::Candidate &ci = *dynamic_cast<const reco::Candidate* >(muons[i]);
    fillP3Covariance(ci, bigCov, o);
    jacobian(0, o+0) = (e*(ci.px()/ci.energy()) - px)/mass;
    jacobian(0, o+1) = (e*(ci.py()/ci.energy()) - py)/mass;
    jacobian(0, o+2) = (e*(ci.pz()/ci.energy()) - pz)/mass;
  }

  TMatrixDSym massCov = bigCov.Similarity(jacobian);
  double dm2 = massCov(0,0);
  return (dm2 > 0 ? std::sqrt(dm2) : 0.0);
}


#endif

