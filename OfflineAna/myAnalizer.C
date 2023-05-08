#define myAnalizer_cxx
#define NCUTS 6
#include "myAnalizer.h"
#include "Utilities.C"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>

using namespace std;

bool compareByPt(const TLorentzVector &a, const TLorentzVector &b){
  return a.Pt() > b.Pt();
}

struct jet_struct{
  TLorentzVector jet_p4;
  float CvsAll;
  float CvsL;
  float CvsB;
  bool c_tagged;
};

bool compareByCvsAll(const jet_struct &a, const jet_struct &b){
  return a.CvsAll > b.CvsAll;
}




void myAnalizer::Loop_Hcc(TString type, TString datasetName)
{
//   In a ROOT session, you can do:
//      root> .L myAnalizer.C
//      root> myAnalizer t
//      root> t.GetEntry(12); // Fill t data members with entry number 12
//      root> t.Show();       // Show values of entry 12
//      root> t.Show(16);     // Read and show values of entry 16
//      root> t.Loop();       // Loop on all entries
//

//     This is the loop skeleton where:
//    jentry is the global entry number in the chain
//    ientry is the entry number in the current Tree
//  Note that the argument to GetEntry must be:
//    jentry for TChain::GetEntry
//    ientry for TTree::GetEntry and TBranch::GetEntry
//
//       To read only selected branches, Insert statements like:
// METHOD1:
//    fChain->SetBranchStatus("*",0);  // disable all branches
//    fChain->SetBranchStatus("branchname",1);  // activate branchname
// METHOD2: replace line
//    fChain->GetEntry(jentry);       //read all branches
//by  b_branchname->GetEntry(ientry); //read only this branch


   //variable and histo declaration
   TLorentzVector hltjet_p4;
   TLorentzVector GENjet_p4;
   TLorentzVector AK4puppi_p4;
   vector<TLorentzVector> AK4puppi_p4_vec;
   vector<TLorentzVector> cjets_hlt, VBFjets_hlt, fakejets_hlt;
   TVector3 hltjet_p3, quark_p3, GENjet_p3;
   int match_index=-10;
   int match_hltGen_index=-10;
   vector<bool> match_free, match_gen_free;
   bool match_gen_quark=false;
   bool match_hlt_gen=false;
   bool trigger_VBFPNet=false;

   vector<float> hltjet_pt;

   int hlt_count=0;
   int hltdouble_count=0;
   int hltOR_count=0;

   bool PtThr_passed=false;

   //define a vector of jet_struct
   std::vector<jet_struct> AK4puppi_sel;
   std::vector<jet_struct> AK4puppi_cHiggs;
   std::vector<jet_struct> AK4puppi_VBF;
   bool passed_selection=false;
   //

   float ParticleNet_CvsAll_value, ParticleNet_CvsB_value, ParticleNet_CvsL_value;
   TH1I *hCutEffEvt = new TH1I("CutEff_NEvents", "CutEff_NEvents", NCUTS, 0.5, (NCUTS+0.5));

   /*TH1F* PassedEvents= new TH1F("passed events","passed events",2,-0.5,1.5);
   TH1F* CvsAll_ptSel= new TH1F("PNet CvsAll (pt selection only)","PNet CvsAll (py selection only)",20,0,1);
   TH1F *pt_cjets=new TH1F("p_{T} c-tagged jets"," p_{T} c-tagged jets",100,0,250);
   TH1F *eta_cjets=new TH1F("#eta c-tagged jets"," #eta c-tagged jets",50,-5,5);
   TH1F *pt_VBFjets=new TH1F("p_{T} VBF-tagged jets"," p_{T} VBF-tagged jets",100,0,250);
   TH1F *eta_VBFjets=new TH1F("#eta VBF-tagged jets"," #eta VBF-tagged jets",50,-5,5);

   TH1F* deltaEta_cjets= new TH1F("#Delta#eta c-tagged jets","#Delta#eta c-tagged jets",50,0,12);
   TH1F* deltaEta_VBFjets= new TH1F("#Delta#eta VBF-tagged jets","#Delta#eta VBF-tagged jets",50,0,12);

   TH1F* invMass_cjets= new TH1F("Invariant mass c-tagged jets","Invariant mass c-tagged jets",100,0,200);
   TH1F* invMass_VBFjets= new TH1F("Invariant mass VBF-tagged jets","Invariant mass VBF-tagged jets",100,0,1500);

   TH1F* CvsAll_c1= new TH1F("PNet CvsAll first c-tagged jet","PNet CvsAll first c-tagged jet",20,0,1);
   TH1F* CvsAll_c2= new TH1F("PNet CvsAll second c-tagged jet","PNet CvsAll second c-tagged jet",20,0,1);
   TH1F* CvsL_c1= new TH1F("PNet CvsL first c-tagged jet","PNet CvsL first c-tagged jet",20,0,1);
   TH1F* CvsL_c2= new TH1F("PNet CvsL second c-tagged jet","PNet CvsL second c-tagged jet",20,0,1);
   TH1F* CvsB_c1= new TH1F("PNet CvsB first c-tagged jet","PNet CvsB first c-tagged jet",20,0,1);
   TH1F* CvsB_c2= new TH1F("PNet CvsB second c-tagged jet","PNet CvsB second c-tagged jet",20,0,1);
*/

   double isMC = -99;
   double run_n = 0, lumi_n = 0, evt_n = 0, pileupFactor=0;
   bool HLT_passed=false;
     if(datasetName.Contains("2022")) isMC=0;
      else{
        if(datasetName.Contains("QCD")) isMC=1;
       // if(datasetName.Contains("Bp")) isMC=2;
       // if(datasetName.Contains("B0")) isMC=3;
       }
   double pt_jetC1=0, pt_jetC2=0, pt_jetVBF1=0, pt_jetVBF2=0, eta_jetC1=0, eta_jetC2=0, eta_jetVBF1=0, eta_jetVBF2=0, CvsAll_jetC1=0, CvsAll_jetC2=0, CvsB_jetC1=0, CvsB_jetC2=0, CvsL_jetC1=0, CvsL_jetC2=0;
   int cutevt[NCUTS] = {0};

   TString listCut[NCUTS];
   Fill_CutName(listCut);

   //output file definition
   TString root_fileName = fileName;
   TFile *fout = new TFile(root_fileName, "RECREATE");
   fout->cd();
   TTree *tree = new TTree("FinalTree","FinalTree");
   //initialize output tree
   TreeFin_Init(tree, isMC, lumi_n, run_n, evt_n, pileupFactor, pt_jetC1, pt_jetC2, pt_jetVBF1, pt_jetVBF2, eta_jetC1, eta_jetC2, eta_jetVBF1, eta_jetVBF2, CvsAll_jetC1, CvsAll_jetC2, CvsB_jetC1, CvsB_jetC2, CvsL_jetC1, CvsL_jetC2);

   if(datasetName.Contains("2022")) isMC=0;
    else{
        if(datasetName.Contains("QCD")) isMC=1;
       // if(datasetName.Contains("Bp")) isMC=2;
       // if(datasetName.Contains("B0")) isMC=3;
    }
   
   if (fChain == 0) return;

   Long64_t nentries = fChain->GetEntriesFast();

   Long64_t nbytes = 0, nb = 0;
   
   //cycle on events
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      // if (Cut(ientry) < 0) continue;
      bool Eff_counter[NCUTS] = {false};
      AK4puppi_sel.clear();
      AK4puppi_cHiggs.clear();
      AK4puppi_VBF.clear();
      HLT_passed=false;
    
      //set default values
      PtThr_passed=false;
      passed_selection=false;

      Eff_counter[0] = true;

      run_n = Run; lumi_n = LumiSect; evt_n = Event; pileupFactor=nInt;  
     
      //HLT trigger
      for(int h=0; h<Trigger_hltname->size(); h++){
        TString hltName = Trigger_hltname->at(h);
        if( (hltName.Contains("HLT_QuadPFJet103_88_75_15_v") || hltName.Contains("HLT_QuadPFJet105_88_76_15_v") || hltName.Contains("HLT_QuadPFJet111_90_80_15_v") || hltName.Contains("HLT PFJet80_v") || hltName.Contains("HLT_QuadPFJet103_88_75_15_PFBTagDeepJet_1p3_VBF2_v") || hltName.Contains("HLT_QuadPFJet105_88_76_15_PFBTagDeepJet_1p3_VBF2_v") || hltName.Contains("HLT_QuadPFJet111_90_80_15_PFBTagDeepJet_1p3_VBF2_v") || hltName.Contains("HLT_QuadPFJet103_88_75_15_DoublePFBTagDeepJet_1p3_7p7_VBF1_v") || hltName.Contains("HLT_QuadPFJet105_88_76_15_DoublePFBTagDeepJet_1p3_7p7_VBF1_v") || hltName.Contains("HLT_QuadPFJet111_90_80_15_DoublePFBTagDeepJet_1p3_7p7_VBF1_v")) && Trigger_hltdecision->at(h) == 1){
           HLT_passed = true;
         }
      }

      if(!HLT_passed){
        cutevt[0]++;
        continue;
      }

      if(HLT_passed==true){
        Eff_counter[1] = true;
        //cycle on AK4 puppi jets
        for(unsigned int ijet=0; ijet< AK4PuppiJets_pt->size();ijet++){
          AK4puppi_p4.SetPtEtaPhiM(AK4PuppiJets_pt->at(ijet), AK4PuppiJets_eta->at(ijet), AK4PuppiJets_phi->at(ijet), AK4PuppiJets_mass->at(ijet));
          float num= jet_pfParticleNetAK4JetTags_probc->at(ijet);
          float den= jet_pfParticleNetAK4JetTags_probc->at(ijet)+ jet_pfParticleNetAK4JetTags_probb->at(ijet) + jet_pfParticleNetAK4JetTags_probuds->at(ijet) + jet_pfParticleNetAK4JetTags_probg->at(ijet);
          float CvsAll_val= (den!=0 || (num/den)<999)? num/den : -1;
          den = jet_pfParticleNetAK4JetTags_probc->at(ijet) + jet_pfParticleNetAK4JetTags_probuds->at(ijet) + jet_pfParticleNetAK4JetTags_probg->at(ijet);
          float CvsL_val= (den!=0 || (num/den)<999)? num/den : -1;
          den = jet_pfParticleNetAK4JetTags_probc->at(ijet) + jet_pfParticleNetAK4JetTags_probb->at(ijet);
          float CvsB_val= (den!=0 || (num/den)<999)? num/den : -1;
          if(fabs(AK4puppi_p4.Eta())<4.7){
            jet_struct jet_i={AK4puppi_p4,CvsAll_val,CvsL_val,CvsB_val, false};
            AK4puppi_sel.push_back(jet_i);
          }

        }//end cycle on puppi
        if(AK4puppi_sel.size()>=4){

          //resize the vector of selected jets, keeping only the first 4 of them (pt sorted)
          AK4puppi_sel.resize(4);
          float pt0= ((AK4puppi_sel.at(0)).jet_p4).Pt();
          float pt1= ((AK4puppi_sel.at(1)).jet_p4).Pt();;
          float pt2= ((AK4puppi_sel.at(2)).jet_p4).Pt();;
          float pt3= ((AK4puppi_sel.at(3)).jet_p4).Pt();;
          if(pt0>=110.0 && pt1>= 90. && pt2>=80. && pt3>=30){
            PtThr_passed=true;
          }
          if(PtThr_passed==true){
           Eff_counter[2]=true;
           //sort the AK4puppi_sel by descending CvsAll score
           std::sort(AK4puppi_sel.begin(),AK4puppi_sel.end(),compareByCvsAll );
          // CvsAll_ptSel->Fill(AK4puppi_sel.at(0).CvsAll);
           //tag as c jets the two jets with the highest CvsAll score within eta<2.4
           int n_cjets=0;
           for(unsigned int k=0; k<4; k++){
             if(n_cjets<=2){
               if(fabs((AK4puppi_sel.at(k).jet_p4).Eta())<=2.4){
                 AK4puppi_sel.at(k).c_tagged=true;
                 n_cjets++;
               }
             }  
           }
           if(n_cjets==2){
             Eff_counter[3]=true;
             //cout<<"2 c-jets found"<<endl;
             for(unsigned int j=0; j<4; j++){
               if(AK4puppi_sel.at(j).c_tagged==true){
                 AK4puppi_cHiggs.push_back(AK4puppi_sel.at(j));
               }
               else{
                 AK4puppi_VBF.push_back(AK4puppi_sel.at(j));
               }
             }
             //cout<<"CvsAll c1:"<<AK4puppi_cHiggs.at(0).CvsAll<<endl;
             if(AK4puppi_cHiggs.size()==2 && AK4puppi_VBF.size()==2){
               if(AK4puppi_cHiggs.at(0).CvsAll>=0.5){ //condition on ctag verified
                 Eff_counter[4]=true;
                 TLorentzVector jet_VBF1=AK4puppi_VBF.at(0).jet_p4;
                 TLorentzVector jet_VBF2=AK4puppi_VBF.at(1).jet_p4;
                 if((jet_VBF1+jet_VBF2).M()>=500. && fabs(jet_VBF1.Eta()-jet_VBF2.Eta())>=3.8){
                   passed_selection=true;
                 }
               }
             }
           }

         }
       }

       //PassedEvents->Fill(passed_selection);

       if(passed_selection==true){
         Eff_counter[5]=true;
         TLorentzVector jet_VBF1=AK4puppi_VBF.at(0).jet_p4;
         TLorentzVector jet_VBF2=AK4puppi_VBF.at(1).jet_p4;
         TLorentzVector jet_c1=AK4puppi_cHiggs.at(0).jet_p4;
         TLorentzVector jet_c2=AK4puppi_cHiggs.at(1).jet_p4;
         pt_jetC1=jet_c1.Pt();
         pt_jetC2=jet_c2.Pt();
     
         pt_jetVBF1=jet_VBF1.Pt();
         pt_jetVBF2=jet_VBF2.Pt();

         eta_jetC1=jet_c1.Eta();
         eta_jetC2=jet_c2.Eta();

         eta_jetVBF1=jet_VBF1.Eta();
         eta_jetVBF2=jet_VBF2.Eta();

         //deltaEta_cjets->Fill(fabs(jet_c1.Eta()-jet_c2.Eta()));
         //deltaEta_VBFjets->Fill(fabs(jet_VBF1.Eta()-jet_VBF2.Eta()));

         //invMass_cjets->Fill((jet_c1+jet_c2).M());
         //invMass_VBFjets->Fill((jet_VBF1+jet_VBF2).M());

         CvsAll_jetC1=AK4puppi_cHiggs.at(0).CvsAll;
         CvsAll_jetC2=AK4puppi_cHiggs.at(1).CvsAll;

         CvsL_jetC1=AK4puppi_cHiggs.at(0).CvsL;
         CvsL_jetC2=AK4puppi_cHiggs.at(1).CvsL;

         CvsB_jetC1=AK4puppi_cHiggs.at(0).CvsB;
         CvsB_jetC2=AK4puppi_cHiggs.at(1).CvsB;
         
         tree->Fill();
       }
     }//end condition on HLT
     for(int i=0; i<NCUTS; i++){
       if(Eff_counter[i] == true) cutevt[i]++;
     }
 } //end cycle on events



    TCanvas *canvEvt = new TCanvas("CutEfficiency_Nevents", "CutEfficiency_Nevents", 0, 0, 1200, 1000);
    Draw_CutEffCanvas(canvEvt, hCutEffEvt, cutevt, listCut);
    
    //Write and close the file
    fout->Write();
    fout->Close();
    

    /*TFile *rootFile = new TFile("AK4puppi_selEvents.root","RECREATE");
    CvsAll_ptSel->Write();
    pt_cjets->Write();
    pt_cjets->Write();
    pt_VBFjets->Write();
    pt_VBFjets->Write();
    eta_cjets->Write();
    eta_cjets->Write();
    eta_VBFjets->Write();
    eta_VBFjets->Write();
    deltaEta_cjets->Write();
    deltaEta_VBFjets->Write();
    invMass_cjets->Write();
    invMass_VBFjets->Write();
    CvsAll_c1->Write();
    CvsAll_c2->Write();
    CvsL_c1->Write();
    CvsL_c2->Write();
    CvsB_c1->Write();
    CvsB_c2->Write();
    rootFile->Close();*/
}
