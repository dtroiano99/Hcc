// -*- C++ -*-
//
// Package:    UFHZZAnalysisRun2/KalmanMuonCalibrationsProducer
// Class:      KalmanMuonCalibrationsProducer

// system include files
#include <memory>
#include <math.h>
#include "TLorentzVector.h"

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDProducer.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "DataFormats/PatCandidates/interface/Muon.h"

#include "TRandom3.h"
// Kalman Muon Corrections 
//#include "KaMuCa/Calibration/interface/KalmanMuonCalibrator.h"
// Rochester Corrections
#include "Hcc/KalmanMuonCalibrationsProducer/src/RoccoR.cc"
//
// class declaration
//

class KalmanMuonCalibrationsProducer : public edm::EDProducer {
   public:
      explicit KalmanMuonCalibrationsProducer(const edm::ParameterSet&);
      ~KalmanMuonCalibrationsProducer();

      static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);

   private:
      virtual void beginJob() override;
      virtual void produce(edm::Event&, const edm::EventSetup&) override;
      virtual void endJob() override;
      
      //virtual void beginRun(edm::Run const&, edm::EventSetup const&) override;
      //virtual void endRun(edm::Run const&, edm::EventSetup const&) override;
      //virtual void beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&) override;
      //virtual void endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&) override;

      // ----------member data ---------------------------

      // Kalman Muon Calibrator 
//      KalmanMuonCalibrator *kalmanMuonCalibrator;
      RoccoR  *calibrator;
      edm::EDGetToken muonsCollection_;
      bool isMC;
      bool isSync;
      bool useRochester;
      int rochesterSys;
      int year;
      //bool verbose;

};

//
// constants, enums and typedefs
//


//
// static data member definitions
//

//
// constructors and destructor
//
KalmanMuonCalibrationsProducer::KalmanMuonCalibrationsProducer(const edm::ParameterSet& iConfig) :
    muonsCollection_ (consumes<std::vector<pat::Muon> >(iConfig.getParameter<edm::InputTag>("muonsCollection"))),
    isMC(iConfig.getParameter<bool>("isMC")),
    isSync(iConfig.getParameter<bool>("isSync")),
    useRochester(iConfig.getUntrackedParameter<bool>("useRochester",false)),
    rochesterSys(iConfig.getUntrackedParameter<int>("rochesterSys",0)),
    year(iConfig.getUntrackedParameter<int>("year"))
{
//   if (isMC) {
//       kalmanMuonCalibrator = new KalmanMuonCalibrator("MC_80X_13TeV");
//   } else {
//       kalmanMuonCalibrator = new KalmanMuonCalibrator("DATA_80X_13TeV");
//   }
   
   std::string DATAPATH = std::getenv( "CMSSW_BASE" );
   if(year == 2018)    DATAPATH+="/src/Hcc/KalmanMuonCalibrationsProducer/data/roccor.Run2.v5/RoccoR2018UL.txt";
   if(year == 2017)    DATAPATH+="/src/Hcc/KalmanMuonCalibrationsProducer/data/roccor.Run2.v5/RoccoR2017UL.txt";
   if(year == 20165)    DATAPATH+="/src/Hcc/KalmanMuonCalibrationsProducer/data/roccor.Run2.v5/RoccoR2016bUL.txt"; // postVFP
   if(year == 20160)    DATAPATH+="/src/Hcc/KalmanMuonCalibrationsProducer/data/roccor.Run2.v5/RoccoR2016aUL.txt"; // APV preVFP
   if(useRochester) calibrator = new RoccoR(DATAPATH); 

   produces<std::vector<pat::Muon> >();      

}


KalmanMuonCalibrationsProducer::~KalmanMuonCalibrationsProducer()
{
 
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called to produce the data  ------------
void
KalmanMuonCalibrationsProducer::produce(edm::Event& iEvent, const edm::EventSetup& iSetup)
{
   using namespace edm;
   using namespace std;

   edm::Handle<vector<pat::Muon>> muonsCollection;
   iEvent.getByToken(muonsCollection_ , muonsCollection);
   
   // output muons
   std::vector<pat::Muon> * patMuons = new std::vector<pat::Muon>();
   
   // input muons
   const vector<pat::Muon> * theMuons = muonsCollection.product();
   unsigned int nbMuon =  theMuons->size();

   TLorentzVector p4;
   for(unsigned i = 0 ; i < nbMuon; i++){

       pat::Muon mu = theMuons->at(i); 
       double oldpt=mu.pt();
       double newpt=oldpt;
       double scale_factor=1.0;
       double oldpterr=mu.muonBestTrack()->ptError();
       double newpterr=oldpterr;
       double scale_error = 0.;
       double smear_error = 0.;

       TRandom3 rand;                                                                                                                                                                                                             
       rand.SetSeed(abs(static_cast<int>(sin(mu.phi())*100000)));                                                                                          


       double u1;
       if (isSync) {
           u1 = 0.5;
       }
       else {
           u1 = rand.Uniform(1.);
       }

       if (useRochester) {

           if(mu.muonBestTrackType() == 1 && mu.pt()<200.0) {


           int nl = mu.track()->hitPattern().trackerLayersWithMeasurement();

           //std::cout<<"test0 nl "<<nl<<std::endl;
           if(isMC && nl > 5)//Protection against muons with low number of layers, they are not used in the analysis anyway as we apply thight muon ID
           {
               
               /// ====== ON MC (correction plus smearing) =====
               auto gen_particle = mu.genParticle();       
               if ( gen_particle != 0)
               {                                                        
                   //std::cout<<"test1  charge "<<mu.charge()<<" oldpt "<<oldpt<<" eta "<<mu.eta()<<" phi "<<mu.phi()<<" genpt "<<gen_particle->pt()<<std::endl;
                   scale_factor = calibrator->kSpreadMC(mu.charge(), oldpt, mu.eta(), mu.phi(), gen_particle->pt(), 5, 0);
                   smear_error = calibrator->kSpreadMCerror(mu.charge(), oldpt, mu.eta(), mu.phi(), gen_particle->pt());
               }
               else
               {
                   //std::cout<<"test2  charge "<<mu.charge()<<" oldpt "<<oldpt<<" eta "<<mu.eta()<<" phi "<<mu.phi()<<std::endl;
                   scale_factor = calibrator->kSmearMC(mu.charge(), oldpt, mu.eta(), mu.phi(), nl, u1, 5, 0);
                   smear_error = calibrator->kSmearMCerror(mu.charge(), oldpt, mu.eta(), mu.phi(), nl, u1);
                   
               }

               scale_error = calibrator->kScaleDTerror(mu.charge(), oldpt, mu.eta(), mu.phi());

               newpt = oldpt*scale_factor;
               newpterr = oldpterr*scale_factor;
               //std::cout<<"scale_factor "<<scale_factor<<" newpt "<<newpt<<std::endl;

           }
            
           else if(!isMC && nl > 5)
           {
               /// ====== ON DATA (correction only) =====
               if(mu.pt()>2.0 && fabs(mu.eta())<2.4)
               {
                   scale_factor = calibrator->kScaleDT(mu.charge(), oldpt, mu.eta(), mu.phi(), 5, 0);
                   scale_error = calibrator->kScaleDTerror(mu.charge(), oldpt, mu.eta(), mu.phi());
                   smear_error = calibrator->kSmearMCerror(mu.charge(), oldpt, mu.eta(), mu.phi(), nl, u1);
               }
               else
               {
                   // keep old values
                   scale_factor = 1.;
                   scale_error = 0.;
                   smear_error = 0.;
               }
               
               newpt = oldpt*scale_factor;
               newpterr = oldpterr*scale_factor;
           }       

           /*
           double sf=1.0;
           if (!isMC) {
               sf = rc->kScaleDT(mu.charge(), oldpt, mu.eta(), mu.phi(), 0, 0);
           } else {
               TRandom3 rand;
               rand.SetSeed(abs(static_cast<int>(sin(mu.phi())*100000)));
               double u1 = rand.Uniform(1.); 
               double u2 = rand.Uniform(1.); 
               if (mu.genParticle()) {

                   sf = rc->kScaleFromGenMC(mu.charge(), oldpt, mu.eta(), mu.phi(), mu.innerTrack()->hitPattern().trackerLayersWithMeasurement(), mu.genParticle()->pt(), u1, 0, 0);

                   if (rochesterSys!=0) {
                       double statrms=0.0;
                       for (int i=0; i<100; i++) {
                           double sfi =  rc->kScaleFromGenMC(mu.charge(), oldpt, mu.eta(), mu.phi(), mu.innerTrack()->hitPattern().trackerLayersWithMeasurement(), mu.genParticle()->pt(), u1, 1, i);
                           statrms += (sfi-sf)*(sfi-sf);
                       }
                       double uncstat=sqrt(statrms/100);
                       double sfZpt =  rc->kScaleFromGenMC(mu.charge(), oldpt, mu.eta(), mu.phi(), mu.innerTrack()->hitPattern().trackerLayersWithMeasurement(), mu.genParticle()->pt(), u1, 2, 0);
                       double uncZpt=abs(sf-sfZpt);
              
                       double maxCorDm=0.0, maxFitDm=0.0;
                       double minCorDm=0.0, minFitDm=0.0;
                       for (int i=0; i<5; i++) {
                           double sfCorDm = rc->kScaleFromGenMC(mu.charge(), oldpt, mu.eta(), mu.phi(), mu.innerTrack()->hitPattern().trackerLayersWithMeasurement(), mu.genParticle()->pt(), u1, 4, i);
                           if ( (sfCorDm-sf)>maxCorDm ) maxCorDm = (sfCorDm-sf);
                           if ( (sfCorDm-sf)<minCorDm ) minCorDm = (sfCorDm-sf);
                           double sfFitDm = rc->kScaleFromGenMC(mu.charge(), oldpt, mu.eta(), mu.phi(), mu.innerTrack()->hitPattern().trackerLayersWithMeasurement(), mu.genParticle()->pt(), u1, 5, i);
                           if ( (sfFitDm-sf)>maxCorDm ) maxFitDm = (sfFitDm-sf);
                           if ( (sfFitDm-sf)<minCorDm ) minFitDm = (sfFitDm-sf);
                       }                       
                       double uncCorDm=0.0, uncFitDm=0.0;
                       if (rochesterSys==1) {
                           uncCorDm=abs(maxCorDm); uncFitDm=abs(maxFitDm);
                       } else if (rochesterSys==-1) {
                           uncCorDm=abs(minCorDm); uncFitDm=abs(minFitDm);
                       }

                       //std::cout<<uncstat<<" "<<uncZpt<<" "<<uncCorDm<<" "<<" "<<uncFitDm<<std::endl;
                       double total_unc = sqrt(uncstat*uncstat+uncZpt*uncZpt+uncCorDm*uncCorDm+uncFitDm*uncFitDm);
                       //std::cout<<"old sf: "<<sf<<std::endl;
                       if (rochesterSys==1) sf *= (1.0+total_unc);
                       if (rochesterSys==-1) sf /= (1.0+total_unc);
                       //std::cout<<"new sf: "<<sf<<std::endl;
                       
                   }
                       
               } else {

                   sf = rc->kScaleAndSmearMC(mu.charge(), oldpt, mu.eta(), mu.phi(), mu.innerTrack()->hitPattern().trackerLayersWithMeasurement(), u1, u2, 0, 0);

                   if (rochesterSys!=0) {
                       double statrms=0.0;
                       for (int i=0; i<100; i++) {
                           double sfi =  rc->kScaleAndSmearMC(mu.charge(), oldpt, mu.eta(), mu.phi(), mu.innerTrack()->hitPattern().trackerLayersWithMeasurement(), u1, u2, 1, i);
                           statrms += (sfi-sf)*(sfi-sf);
                       }
                       double uncstat=sqrt(statrms/100);
                       double sfZpt =  rc->kScaleAndSmearMC(mu.charge(), oldpt, mu.eta(), mu.phi(), mu.innerTrack()->hitPattern().trackerLayersWithMeasurement(), u1, u2, 2, 0);
                       double uncZpt=abs(sf-sfZpt);
              
                       double maxCorDm=0.0, maxFitDm=0.0;
                       double minCorDm=0.0, minFitDm=0.0;
                       for (int i=0; i<5; i++) {
                           double sfCorDm = rc->kScaleAndSmearMC(mu.charge(), oldpt, mu.eta(), mu.phi(), mu.innerTrack()->hitPattern().trackerLayersWithMeasurement(), u1, u2, 4, i);
                           if ( (sfCorDm-sf)>maxCorDm ) maxCorDm = (sfCorDm-sf);
                           if ( (sfCorDm-sf)<minCorDm ) minCorDm = (sfCorDm-sf);
                           double sfFitDm = rc->kScaleAndSmearMC(mu.charge(), oldpt, mu.eta(), mu.phi(), mu.innerTrack()->hitPattern().trackerLayersWithMeasurement(), u1, u2, 5, i);
                           if ( (sfFitDm-sf)>maxCorDm ) maxFitDm = (sfFitDm-sf);
                           if ( (sfFitDm-sf)<minCorDm ) minFitDm = (sfFitDm-sf);
                       }                       
                       double uncCorDm=0.0, uncFitDm=0.0;
                       if (rochesterSys==1) {
                           uncCorDm=abs(maxCorDm); uncFitDm=abs(maxFitDm);
                       } else if (rochesterSys==-1) {
                           uncCorDm=abs(minCorDm); uncFitDm=abs(minFitDm);
                       }

                       //std::cout<<uncstat<<" "<<uncZpt<<" "<<uncCorDm<<" "<<" "<<uncFitDm<<std::endl;
                       double total_unc = sqrt(uncstat*uncstat+uncZpt*uncZpt+uncCorDm*uncCorDm+uncFitDm*uncFitDm);
                       //std::cout<<"old sf: "<<sf<<std::endl;
                       if (rochesterSys==1) sf *= (1.0+total_unc);
                       if (rochesterSys==-1) sf /= (1.0+total_unc);
                       //std::cout<<"new sf: "<<sf<<std::endl;
                       
                   }
               }
           }
           
           if (std::isnan(sf) || sf<0.0) sf=1.0; 
           newpt = oldpt*sf;
           newpterr = oldpterr;
           */
           }
       } 
       //else {
         //  if(mu.muonBestTrackType() == 1 && mu.pt()<200.0) {
           //    if (!isMC) {
             //      if (mu.pt()>2.0 && abs(mu.eta())<2.4) {
               //        newpt = kalmanMuonCalibrator->getCorrectedPt(oldpt,mu.eta(),mu.phi(),mu.charge());
                 //      newpterr = newpt*kalmanMuonCalibrator->getCorrectedError(newpt,mu.eta(),oldpterr/newpt);
                   //}
       //        } else {
         //          double unsmearednewpt = kalmanMuonCalibrator->getCorrectedPt(oldpt, mu.eta(), mu.phi(), mu.charge());
           //        if (!isSync) newpt = kalmanMuonCalibrator->smear(unsmearednewpt, mu.eta());
             //      else newpt = kalmanMuonCalibrator->smearForSync(unsmearednewpt, mu.eta());
               //    newpterr = newpt*kalmanMuonCalibrator->getCorrectedError(newpt, mu.eta(), oldpterr/newpt );
               //}
           //}
       //}

       mu.addUserFloat("correctedPtError",newpterr);
       if (useRochester) {
           mu.addUserFloat("scale_unc", 1. + scale_error);
           mu.addUserFloat("smear_unc", 1. + smear_error);
       }
       patMuons->push_back(mu);    
       
       //std::cout<<"muon old pt: "<<mu.pt()<<" +/- "<<oldpterr<<", eta: "<< mu.eta()<<" new pt: "<<newpt<<" +/- "<<newpterr<<std::endl;
       
       p4.SetPtEtaPhiM(newpt, mu.eta(), mu.phi(), mu.mass());
       patMuons->back().setP4(reco::Particle::PolarLorentzVector(p4.Pt(), p4.Eta(), p4.Phi(), mu.mass()));


   }
   
   // add the muons to the event output
   std::unique_ptr<std::vector<pat::Muon> > ptr(patMuons);
   iEvent.put(std::move(ptr));
   
}

// ------------ method called once each job just before starting event loop  ------------
void 
KalmanMuonCalibrationsProducer::beginJob()
{
}

// ------------ method called once each job just after ending the event loop  ------------
void 
KalmanMuonCalibrationsProducer::endJob() {
}

// ------------ method called when starting to processes a run  ------------
/*
void
KalmanMuonCalibrationsProducer::beginRun(edm::Run const&, edm::EventSetup const&)
{
}
*/
 
// ------------ method called when ending the processing of a run  ------------
/*
void
KalmanMuonCalibrationsProducer::endRun(edm::Run const&, edm::EventSetup const&)
{
}
*/
 
// ------------ method called when starting to processes a luminosity block  ------------
/*
void
KalmanMuonCalibrationsProducer::beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
{
}
*/
 
// ------------ method called when ending the processing of a luminosity block  ------------
/*
void
KalmanMuonCalibrationsProducer::endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
{
}
*/
 
// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void
KalmanMuonCalibrationsProducer::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);
}

//define this as a plug-in
DEFINE_FWK_MODULE(KalmanMuonCalibrationsProducer);
