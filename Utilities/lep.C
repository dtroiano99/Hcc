#include "DataFormats/Math/interface/deltaR.h"
#include <iostream>
#include <cmath>
#include <algorithm>
//float dr1 = deltaR(GENlep_eta->at(r),GENlep_phi->at(r), lep_eta->at(j), lep_phi->at(j));
//
//
int DIM = 2;//number of plots
float lum=59000;

void distr_pt(TFile* f1,  float S,  TH1F  *hist[DIM]) {
    int tot=0;
    TH1F* h_num_eventi;
    float num_event;
    h_num_eventi = (TH1F*) f1->Get("Ana/sumWeights");
    num_event = h_num_eventi->Integral();
    tot = tot + num_event;
	

	TTree *T = (TTree*)f1->Get("Ana/passedEvents");
   	 TH1F *hist1 = new TH1F("hist1", "hist1", 70, 0, 350);
   	 TH1F *hist2 = new TH1F("hist2", "hist2", 70, 0, 350);

	std::vector<float> *AK4lep_pt = 0;
	std::vector<float> *ALLlep_pt = 0;
	std::vector<float> *lep_pt = 0;

	TBranch *b_AK4lep_pt = 0;
	TBranch *b_ALLlep_pt = 0;
	TBranch *b_lep_pt = 0;
	
	T->SetBranchAddress("AK4lep_pt",&AK4lep_pt, &b_AK4lep_pt);
	T->SetBranchAddress("ALLlep_pt",&ALLlep_pt, &b_ALLlep_pt);
	T->SetBranchAddress("lep_pt",&lep_pt, &b_lep_pt);

	Int_t nentries = (Int_t)T->GetEntries();
	cout<<nentries<<"\n";	
	//loop sugli eventi
	for (Int_t i=0;i<nentries;i++) {
	
		Long64_t tentry = T->LoadTree(i);

		b_AK4lep_pt->GetEntry(tentry);
		b_ALLlep_pt->GetEntry(tentry);
		b_lep_pt->GetEntry(tentry);
		
		//loop sui leptoni in un evento
		for (UInt_t j = 0; j < ALLlep_pt->size(); ++j) {
			hist1->Fill(ALLlep_pt->at(j));
		}

		for (UInt_t k = 0; k < lep_pt->size(); ++k) {
                        hist2->Fill(lep_pt->at(k));
                }
	}


	hist1->SetTitle("all leptons");
    	hist1->GetXaxis()->SetTitle("p_{T} [GeV]");
    	hist1->GetYaxis()->SetTitle("a.u. / 5 GeV");
	
	hist2->SetTitle("jet leptons");
        hist2->GetXaxis()->SetTitle("p_{T} [GeV]");
        hist2->GetYaxis()->SetTitle("a.u. / 5 GeV");


	hist[0]= hist1;
	hist[1]= hist2;	
}

void lep(){
//	gStyle->SetOptStat(0000);
	TFile* f1 = TFile::Open("VBFHToCC_Run3_prova_DDX_1.root","read");
	float s1 = 0.01333521;

	TH1F *sig_Hcc[DIM];
    	distr_pt( f1, s1, sig_Hcc);

	auto c1 = new TCanvas("c1", "c1", 1200, 800);

	c1->cd();
	//c_Hcc->SetLogy();

	sig_Hcc[0]->Draw("hist");

	auto c2 = new TCanvas("c2", "c2", 1200, 800);

        c2->cd();
        //c_Hcc->SetLogy();
        
	sig_Hcc[1]->Draw("hist");

}
