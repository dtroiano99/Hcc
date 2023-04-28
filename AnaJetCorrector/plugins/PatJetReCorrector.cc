#include <memory>
#include <vector>
#include <algorithm>

#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDProducer.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/Framework/interface/ESHandle.h"
#include "FWCore/Framework/interface/EventSetup.h"
#include "DataFormats/PatCandidates/interface/JetCorrFactors.h"
#include "JetMETCorrections/Objects/interface/JetCorrectionsRecord.h"
#include "CondFormats/JetMETObjects/interface/JetCorrectorParameters.h"
#include "CondFormats/JetMETObjects/interface/FactorizedJetCorrector.h"

/// Unfortunately there's no way otherwise to reset the jet energy corrections of a PAT Jet
#define private public
#define protected public
#include <DataFormats/PatCandidates/interface/Jet.h>
#undef private
#undef public



class PatJetReCorrector : public edm::EDProducer {
    public:
        explicit PatJetReCorrector(const edm::ParameterSet&);
        ~PatJetReCorrector();

    private:
        virtual void beginJob() ;
        virtual void produce(edm::Event&, const edm::EventSetup&);
        virtual void endJob() ;


        edm::InputTag jets_, rho_;
        /// label of payload
        std::string payload_;
        /// levels
        std::vector<std::string> levels_;
};

PatJetReCorrector::PatJetReCorrector(const edm::ParameterSet& iConfig) :
    jets_(iConfig.getParameter<edm::InputTag>("jets")),
    rho_(iConfig.getParameter<edm::InputTag>("rho")),
    payload_( iConfig.getParameter<std::string>("payload") ),
    levels_( iConfig.getParameter<std::vector<std::string> >("levels") )
{
    produces<std::vector<pat::Jet> >();
}




void PatJetReCorrector::produce(edm::Event& iEvent, const edm::EventSetup& iSetup) {
    edm::Handle<edm::View<pat::Jet> > jets;
    iEvent.getByLabel(jets_,jets);

    edm::Handle<double> rho;
    if(!rho_.label().empty()) iEvent.getByLabel(rho_, rho);

    // retreive parameters from the DB 
    edm::ESHandle<JetCorrectorParametersCollection> allparameters;
    iSetup.get<JetCorrectionsRecord>().get(payload_, allparameters); 

    //std::cout << "\n\nSelecting " << levels_.size() << " levels of correction parameters." << std::endl;        
    std::vector<JetCorrectorParameters> parameters;
    for (unsigned int level = 0, n = levels_.size(); level < n; ++level) {
        //std::cout << "Level " << level << "/" << n << ": " << levels_[level] << std::endl;
        parameters.push_back( (*allparameters)[levels_[level]] );
        //parameters.back().printScreen();
        //std::cout << std::endl;
    }
    //std::cout << std::endl;

    FactorizedJetCorrector corrector(parameters);

    std::unique_ptr<pat::JetCollection> pOut(new pat::JetCollection);
    pOut->reserve(jets->size());

    for(edm::View<pat::Jet>::const_iterator itJet = jets->begin(), edJet = jets->end(); itJet != edJet; ++itJet) {    
        // Print out original jet
        //std::cout << "Original jet with pt  " << itJet->pt() << ", eta " << itJet->eta() << std::endl;        
        // clear the table.
        pat::Jet jet = itJet->correctedJet("Uncorrected");
        jet.jec_.clear(); jet.currentJECLevel_ = 0;
        // now start making 
        //std::cout << "Jet with pt " << jet.pt() << ", eta " << jet.eta() << std::endl;        
        std::vector<pat::JetCorrFactors::CorrectionFactor> jec; 
        jec.push_back(
                std::make_pair(std::string("Uncorrected"), std::vector<float>(1, 1))
        );
        // initialize corrector
        double runningPt = jet.pt();
        // start adding levels
        for (unsigned int level = 0, n = levels_.size(); level < n; ++level) {
            // must initialize with the _uncorrected_ jet every time
            corrector.setJetPt(jet.pt()); corrector.setJetEta(jet.eta()); 
            corrector.setRho(*rho);       corrector.setJetA(jet.jetArea()); 
            // then get the product of all pieces
            std::vector<float> factors = corrector.getSubCorrections();
            // and take the ratio of the last two
            float factor = level ? factors[level]/factors[level-1] : factors[0];
            runningPt *= factor;
            //std::cout << "  after " << levels_[level] << ": pt " << runningPt << std::endl;        
            jec.push_back(
                std::make_pair(levels_[level], std::vector<float>(1, factor))
            );
        }
        jet.addJECFactors(pat::JetCorrFactors("corrections",jec));
        jet.initializeJEC(jet.jec_.back().jecLevel(levels_.back()));

        double scale = runningPt / itJet->pt();
        double scaledParticlePx = scale * itJet->px();
        double scaledParticlePy = scale * itJet->py();
        double scaledParticlePz = scale * itJet->pz();
        double scaledParticleEn = sqrt(scaledParticlePx*scaledParticlePx +
                                       scaledParticlePy*scaledParticlePy +
                                       scaledParticlePz*scaledParticlePz +
                                       itJet->mass()*itJet->mass());

        pat::Jet scaledJet(*itJet);
        reco::Candidate::LorentzVector shiftedJetP4(scaledParticlePx,scaledParticlePy,scaledParticlePz,scaledParticleEn);
        scaledJet.setP4(shiftedJetP4);

        // std::cout << "Final jet with pt " << scaledJet.pt() << ", eta " << scaledJet.eta() << std::endl;        
        // std::cout << std::endl;
        pOut->push_back(scaledJet);
    }

    iEvent.put(std::move(pOut));
}

PatJetReCorrector::~PatJetReCorrector() { }
void PatJetReCorrector::beginJob() { }
void PatJetReCorrector::endJob() { }
DEFINE_FWK_MODULE(PatJetReCorrector);
