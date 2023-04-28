// -*- C++ -*-
//
// Package:    UFHZZAnalysisRun2/SlimmedElectronMvaIDProducer
// Class:      SlimmedElectronMvaIDProducer
// 
/**\class SlimmedElectronMvaIDProducer SlimmedElectronMvaIDProducer.cc UFHZZAnalysisRun2/SlimmedElectronMvaIDProducer/plugins/SlimmedElectronMvaIDProducer.cc

 Description: [one line class summary]

 Implementation:
     [Notes on implementation]
*/
//
// Original Author:  Tongguang Cheng
//         Created:  Fri, 03 Apr 2015 13:52:09 GMT
//
//


// system include files
#include <memory>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDProducer.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "DataFormats/PatCandidates/interface/Electron.h"

// electron MvaID related
#include "EgammaAnalysis/ElectronTools/interface/EGammaMvaEleEstimatorCSA14.h"

//needed if create ID from reco/aod
#include "DataFormats/EgammaCandidates/interface/GsfElectron.h"
#include "DataFormats/EgammaCandidates/interface/GsfElectronFwd.h"
#include "DataFormats/PatCandidates/interface/Electron.h"
#include "DataFormats/VertexReco/interface/Vertex.h"
#include "DataFormats/VertexReco/interface/VertexFwd.h"
#include "TrackingTools/Records/interface/TransientTrackRecord.h"
#include "TrackingTools/IPTools/interface/IPTools.h"

//
// class declaration
//

class SlimmedElectronMvaIDProducer : public edm::EDProducer {
   public:
      explicit SlimmedElectronMvaIDProducer(const edm::ParameterSet&);
      ~SlimmedElectronMvaIDProducer();

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

     edm::EDGetTokenT<edm::ValueMap<float> > mvaValuesMapToken_;
     edm::EDGetToken electronsToken_;
     edm::EDGetToken electronsCollection_;

     std::string idname; 

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
SlimmedElectronMvaIDProducer::SlimmedElectronMvaIDProducer(const edm::ParameterSet& iConfig):
    mvaValuesMapToken_(consumes<edm::ValueMap<float> >(iConfig.getParameter<edm::InputTag>("mvaValuesMap")))
{

   electronsCollection_ = consumes<std::vector<pat::Electron> >(iConfig.getParameter<edm::InputTag>("electronsCollection"));
   electronsToken_ = mayConsume<edm::View<reco::GsfElectron> >(iConfig.getParameter<edm::InputTag>("electronsCollection"));
   idname = iConfig.getParameter<std::string>("idname");

   //register your products
   produces<std::vector<pat::Electron> >();      

}


SlimmedElectronMvaIDProducer::~SlimmedElectronMvaIDProducer()
{
 
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called to produce the data  ------------
void
SlimmedElectronMvaIDProducer::produce(edm::Event& iEvent, const edm::EventSetup& iSetup)
{
   using namespace edm;
   using namespace std;

   edm::Handle<vector<pat::Electron>> electronsCollection;
   iEvent.getByToken(electronsCollection_ , electronsCollection);

   edm::Handle<edm::View<reco::GsfElectron> > gsfelectrons;
   iEvent.getByToken(electronsToken_,gsfelectrons);
        
   edm::Handle<edm::ValueMap<float> > mvaValues;
   iEvent.getByToken(mvaValuesMapToken_,mvaValues);
   
   // output electrons
   std::vector<pat::Electron> * patElectrons = new std::vector<pat::Electron>();
   
   // input electrons
   const vector<pat::Electron> * theElectrons = electronsCollection.product();
   unsigned int nbElectron =  theElectrons->size();

   for(unsigned i = 0 ; i < nbElectron; i++){

        const auto gsf = gsfelectrons->ptrAt((size_t)i);

        float idvalue = (*mvaValues)[gsf]; 

        pat::Electron anElectron = theElectrons->at(i); 

        anElectron.addUserFloat(idname,idvalue);
        
        patElectrons->push_back(anElectron);    
        
    }
    
    // add the electrons to the event output
    std::unique_ptr<std::vector<pat::Electron> > ptr(patElectrons);
    iEvent.put(std::move(ptr));
    
}

// ------------ method called once each job just before starting event loop  ------------
void 
SlimmedElectronMvaIDProducer::beginJob()
{
}

// ------------ method called once each job just after ending the event loop  ------------
void 
SlimmedElectronMvaIDProducer::endJob() {
}

// ------------ method called when starting to processes a run  ------------
/*
void
SlimmedElectronMvaIDProducer::beginRun(edm::Run const&, edm::EventSetup const&)
{
}
*/
 
// ------------ method called when ending the processing of a run  ------------
/*
void
SlimmedElectronMvaIDProducer::endRun(edm::Run const&, edm::EventSetup const&)
{
}
*/
 
// ------------ method called when starting to processes a luminosity block  ------------
/*
void
SlimmedElectronMvaIDProducer::beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
{
}
*/
 
// ------------ method called when ending the processing of a luminosity block  ------------
/*
void
SlimmedElectronMvaIDProducer::endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
{
}
*/
 
// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void
SlimmedElectronMvaIDProducer::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);
}

//define this as a plug-in
DEFINE_FWK_MODULE(SlimmedElectronMvaIDProducer);
