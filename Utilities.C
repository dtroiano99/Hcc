#define myAnalyzer_cxx
#define NCUTS 6

#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <iostream>
#include <TMVA/Reader.h>


void myAnalizer::TreeFin_Init(TTree *&tree, Double_t &isMC, Double_t &lumi, Double_t &run, Double_t &evt, Double_t &puFactor, Double_t &pt_jetC1, Double_t &pt_jetC2, Double_t &pt_jetVBF1, Double_t &pt_jetVBF2, Double_t &eta_jetC1, Double_t &eta_jetC2, Double_t &eta_jetVBF1, Double_t &eta_jetVBF2, Double_t &CvsAll_jetC1, Double_t &CvsAll_jetC2, Double_t &CvsB_jetC1, Double_t &CvsB_jetC2, Double_t &CvsL_jetC1, Double_t &CvsL_jetC2){
		// Set tree branches
		tree->Branch("isMC", &isMC);
		tree->Branch("lumi", &lumi);
		tree->Branch("run", &run);
		tree->Branch("evt", &evt);
		tree->Branch("puFactor", &puFactor);
    tree->Branch("pt_jetC1", &pt_jetC1);
    tree->Branch("pt_jetC2", &pt_jetC2);
    tree->Branch("pt_jetVBF1", &pt_jetVBF1);
    tree->Branch("pt_jetVBF2", &pt_jetVBF2);
    tree->Branch("eta_jetC1", &eta_jetC1);
    tree->Branch("eta_jetC2", &eta_jetC2);
    tree->Branch("eta_jetVBF1", &eta_jetVBF1);
    tree->Branch("eta_jetVBF2", &eta_jetVBF2);
    tree->Branch("CvsAll_jetC1", &CvsAll_jetC1);
    tree->Branch("CvsAll_jetC2", &CvsAll_jetC2);
    tree->Branch("CvsB_jetC1", &CvsB_jetC1);
    tree->Branch("CvsB_jetC2", &CvsB_jetC2);
    tree->Branch("CvsL_jetC1", &CvsL_jetC1);
    tree->Branch("CvsL_jetC2", &CvsL_jetC2);
}


void myAnalizer::Fill_CutName(TString listCut[NCUTS]){
    // Init a vector of strings w/ the names of the cuts
    listCut[0] = "BeforeCuts";
    listCut[1] = "HLT_fired";
    listCut[2] = "pT_cut";
    listCut[3] = "2C_cands";
    listCut[4] = "CvsAll_0p5";
    listCut[5] = "VBF_cut";
  
}

void myAnalizer::Draw_CutEffCanvas(TCanvas *canv, TH1I *hist, Int_t cut[NCUTS], TString listCut[NCUTS]){
    // This function writes on the canvas the histo of the cuts efficiency
    for(int k=0; k<NCUTS; k++){
      hist->Fill(k+1, cut[k]);
      hist->GetXaxis()->SetBinLabel(k+1, listCut[k]);
    }
    //    canv->SetLogy();
    hist->DrawCopy("HIST TEXT0");
    hist->Write();
    //    canv->Write();
    //    canv->Close();
}
    //

