#include "DataFormats/Math/interface/deltaR.h"
#include <iostream>
#include <cmath>
#include <algorithm>
//float dr1 = deltaR(GENlep_eta->at(r),GENlep_phi->at(r), lep_eta->at(j), lep_phi->at(j));


int DIM = 2;//number of plots
float lum=59000;

void distr_probHcc(TFile* f1,  float S,  TH1F  *hist[DIM]) {
    int tot=0;
    TH1F* h_num_eventi;
    float num_event;
    h_num_eventi = (TH1F*) f1->Get("Ana/sumWeights");
    num_event = h_num_eventi->Integral();
    tot = tot + num_event;
	

	TTree *T = (TTree*)f1->Get("Ana/passedEvents");
   	 TH1F *hist1 = new TH1F("hist1", "hist1", 20, 0, 1);
   	 TH1F *hist2 = new TH1F("hist2", "hist2", 20, 0, 1);

	std::vector<float> *probHcc = 0;
	std::vector<float> *AK8_eta = 0;
	std::vector<float> *AK8_phi = 0;
	std::vector<float> *AK8_pt = 0;
	std::vector<float> *GEN_eta = 0;
	std::vector<float> *GEN_phi = 0;
	std::vector<float> *quark_eta = 0;
        std::vector<float> *quark_phi = 0;
	std::vector<int> *quark_flavour = 0;
	std::vector<bool> *quark_VBF = 0;
	

	TBranch *b_probHcc = 0;
	TBranch *b_AK8_eta = 0;
	TBranch *b_AK8_phi = 0;
	TBranch *b_AK8_pt = 0;
	TBranch *b_GEN_eta = 0;
        TBranch *b_GEN_phi = 0;
	TBranch *b_quark_eta = 0;
        TBranch *b_quark_phi = 0;
	TBranch *b_quark_flavour = 0;
        TBranch *b_quark_VBF = 0;

   	T->SetBranchAddress("jet_pfParticleNetJetTags_probHcc",&probHcc,&b_probHcc);	
	T->SetBranchAddress("AK8PuppiJets_eta",&AK8_eta, &b_AK8_eta);
	T->SetBranchAddress("AK8PuppiJets_phi",&AK8_phi, &b_AK8_phi);
	T->SetBranchAddress("AK8PuppiJets_pt",&AK8_pt, &b_AK8_pt);
	T->SetBranchAddress("GENjet_eta",&GEN_eta, &b_GEN_eta);
        T->SetBranchAddress("GENjet_phi",&GEN_phi, &b_GEN_phi);		
	T->SetBranchAddress("quark_eta",&quark_eta, &b_quark_eta);
        T->SetBranchAddress("quark_phi",&quark_phi, &b_quark_phi);
	T->SetBranchAddress("quark_flavour",&quark_flavour, &b_quark_flavour);
        T->SetBranchAddress("quark_VBF",&quark_VBF, &b_quark_VBF);
//T->SetBranchAddress("jet_pfParticleNetJetTags_probHcc", &probHcc);


	Int_t nentries = (Int_t)T->GetEntries();
	cout<<nentries<<"\n";	
	//loop sugli eventi
	for (Int_t i=0;i<nentries;i++) {

	Long64_t tentry = T->LoadTree(i);
      	b_probHcc->GetEntry(tentry);
	b_AK8_eta->GetEntry(tentry);
	b_AK8_phi->GetEntry(tentry);
	b_AK8_pt->GetEntry(tentry);
	b_GEN_eta->GetEntry(tentry);
        b_GEN_phi->GetEntry(tentry);
	b_quark_eta->GetEntry(tentry);
        b_quark_phi->GetEntry(tentry);
	b_quark_flavour->GetEntry(tentry);
        b_quark_VBF->GetEntry(tentry);
	//hist1->Fill((Int_t)probHcc->size());
	//loop sugli AK8 in un evento
	for (UInt_t j = 0; j < probHcc->size(); ++j) {
	 //non faccio niente se nell'evento non c'è almeno un jet AK8
	  if(AK8_pt->at(j)>170){ hist1->Fill(probHcc->at(j));
		
		int g_idx = -1;
                int  g_bestidx1 = -1;
		int  g_bestidx2 = -1;
                float g_bestdr1 = 9999.;
		float g_bestdr2 = 9999.;
		//loop sui get generati
		for (UInt_t ii = 0; ii < GEN_eta->size(); ++ii) {
			g_idx = g_idx +1;			
			float dr1 = deltaR(GEN_eta->at(ii),GEN_phi->at(ii), AK8_eta->at(j), AK8_phi->at(j));
	   		if (dr1 < 0.5 && dr1 < g_bestdr1) {
				g_bestidx2 = g_bestidx1;
				g_bestdr2 = g_bestdr1;
			      	g_bestidx1 = g_idx;
	      			g_bestdr1 = dr1;}
			if (dr1 < 0.5 && dr1 > g_bestdr1 && dr1 <  g_bestdr2) {
                                g_bestidx2 = g_idx;
                                g_bestdr2 = dr1;}
		}//fine loop sui jet generati
	//se ci sono due jet generati che matchano col AK8
		if (g_bestidx2 > -1) {// hist2->Fill(probHcc->at(j));
//			cout<<"Nell'evento "<<i << " il Jet AK8 "<<j<<" èassociato ai generati "<<g_bestidx1<<" e "<<g_bestidx2<<"\n" ;
			int q_idx = -1;
                	int  q_bestidx1 = -1;
                	int  q_bestidx2 = -1;
                	float q_bestdr1 = 9999.;
			float q_bestdr2 = 9999.;
			
			//loop sui quark
			for (UInt_t z = 0; z < quark_eta->size(); ++z) {
				q_idx = q_idx +1;
				float qdr1 = deltaR(GEN_eta->at(g_bestidx1),GEN_phi->at(g_bestidx1), quark_eta->at(z), quark_phi->at(z));
				float qdr2 = deltaR(GEN_eta->at(g_bestidx2),GEN_phi->at(g_bestidx2), quark_eta->at(z), quark_phi->at(z));

				if(qdr1 < 0.3 && qdr1 < q_bestdr1 && qdr1 <= qdr2){
					q_bestidx1 = q_idx;
                                	q_bestdr1 = qdr1;
				}
					
				if(qdr2 < 0.3 && qdr2 < q_bestdr2 && qdr1 > qdr2){
                                        q_bestidx2 = q_idx;
                                        q_bestdr2 = qdr2;
                                }

			}//chiude i loop sui quark
			
			//se i jet generati matchano con una coppia ccbar non VBF riempio l'istogramma finale
			if(q_bestidx1 > -1 && q_bestidx2 > -1 /* &&     ( (quark_flavour->at(q_bestidx1) == 4 &&quark_flavour->at(q_bestidx2) == -4) || (quark_flavour->at(q_bestidx1) == -4 && quark_flavour->at(q_bestidx2) == 4))*/	&& quark_VBF->at(q_bestidx1) == quark_VBF->at(q_bestidx2) == 0 ){hist2->Fill(probHcc->at(j));}
				 
	}//chiude if se c'erano due jet generati compatibili con il jet AK8
 	
      }}//fine loop jet AK8
	}//fine loop eventi







	hist1->SetTitle("");
    	hist1->GetXaxis()->SetTitle("prob_Hcc");
    	hist1->GetYaxis()->SetTitle("a.u. / 0.05");
	
	hist2->SetTitle("");
        hist2->GetXaxis()->SetTitle("prob_Hcc");
        hist2->GetYaxis()->SetTitle("a.u. / 0.05");


	hist[0]= hist1;
	hist[1]= hist2;

//	hist[0]->Scale(S*lum/tot);
//	hist[1]->Scale(S*lum/tot);
		
}

void distr_probHbb(TFile* f1,  float S,  TH1F  *hist[DIM]) {
    int tot=0;
    TH1F* h_num_eventi;
    float num_event;
    h_num_eventi = (TH1F*) f1->Get("Ana/sumWeights");
    num_event = h_num_eventi->Integral();
    tot = tot + num_event;
	

	TTree *T = (TTree*)f1->Get("Ana/passedEvents");
   	 TH1F *hist1 = new TH1F("hist1", "hist1", 20, 0, 1);
   	 TH1F *hist2 = new TH1F("hist2", "hist2", 20, 0, 1);

	std::vector<float> *probHcc = 0;
	std::vector<float> *AK8_eta = 0;
	std::vector<float> *AK8_phi = 0;
	std::vector<float> *AK8_pt = 0;
	

	TBranch *b_probHcc = 0;
	TBranch *b_AK8_eta = 0;
	TBranch *b_AK8_phi = 0;
	TBranch *b_AK8_pt = 0;


   	T->SetBranchAddress("jet_pfParticleNetJetTags_probHbb",&probHcc,&b_probHcc);	
	T->SetBranchAddress("AK8PuppiJets_eta",&AK8_eta, &b_AK8_eta);
	T->SetBranchAddress("AK8PuppiJets_phi",&AK8_phi, &b_AK8_phi);
	T->SetBranchAddress("AK8PuppiJets_pt",&AK8_pt, &b_AK8_pt);
		
//T->SetBranchAddress("jet_pfParticleNetJetTags_probHcc", &probHcc);


	Int_t nentries = (Int_t)T->GetEntries();
	
	//loop sugli eventi
	for (Int_t i=0;i<nentries;i++) {

	Long64_t tentry = T->LoadTree(i);
      	b_probHcc->GetEntry(tentry);
	b_AK8_eta->GetEntry(tentry);
	b_AK8_phi->GetEntry(tentry);
	b_AK8_pt->GetEntry(tentry);
	//hist1->Fill((Int_t)probHcc->size());
	//loop sugli AK8 in un evento
	for (UInt_t j = 0; j < probHcc->size(); ++j) {
 
       if(AK8_pt->at(j)>170){ hist1->Fill(probHcc->at(j));}
 	
      }
	}
//	cout<<tot;
   	 //for (Int_t i=0;i<nentries;i++) {
    	//	T->GetEntry(i);

		
///
//		hist1->Fill(probHcc.at(0));

//	}		

	hist1->SetTitle("");
    	hist1->GetXaxis()->SetTitle("prob_Hbb");
    	hist1->GetYaxis()->SetTitle("a.u. / 0.05");
	


	hist[0]= hist1;
	hist[1]= hist2;

//	hist[0]->Scale(S*lum/tot);
//	hist[1]->Scale(S*lum/tot);
		
}

void distr_2D(TFile* f1,  float S,  TH2F  *hist[1]) {
    int tot=0;
    TH1F* h_num_eventi;
    float num_event;
    h_num_eventi = (TH1F*) f1->Get("Ana/sumWeights");
    num_event = h_num_eventi->Integral();
    tot = tot + num_event;
	

	TTree *T = (TTree*)f1->Get("Ana/passedEvents");
   	TH2F *hist1 = new TH2F("hist1", "hist1", 15,-3.14,3.14, 10, -5, 5);
	TH2F *hist2 = new TH2F("hist2", "hist2", 15,-3.14,3.14, 10, -5, 5);
//	TH2F *hist1 = new TH2F("hist1", "hist1", 66, 170, 500, 40, 0, 1);   	 

	std::vector<float> *probHcc = 0;
	std::vector<float> *probHcc_md = 0;
	std::vector<float> *probHcc_ddx = 0;
	std::vector<float> *AK8_eta = 0;
	std::vector<float> *AK8_pt = 0;
	std::vector<float> *AK8_phi = 0;
	std::vector<float> *GEN_eta = 0;
	std::vector<float> *GEN_phi = 0;
	std::vector<float> *quark_eta = 0;
        std::vector<float> *quark_phi = 0;
	std::vector<int> *quark_flavour = 0;
	std::vector<bool> *quark_VBF = 0;
	

	TBranch *b_probHcc = 0;
	TBranch *b_probHcc_md = 0;
	TBranch *b_probHcc_ddx = 0;
	TBranch *b_AK8_eta = 0;
	TBranch *b_AK8_pt = 0;
	TBranch *b_AK8_phi = 0;
	TBranch *b_GEN_eta = 0;
        TBranch *b_GEN_phi = 0;
	TBranch *b_quark_eta = 0;
        TBranch *b_quark_phi = 0;
	TBranch *b_quark_flavour = 0;
        TBranch *b_quark_VBF = 0;

   	T->SetBranchAddress("jet_pfParticleNetJetTags_probHcc",&probHcc,&b_probHcc);	
	T->SetBranchAddress("jet_pfMassDecorrelatedParticleNetJetTags_probXcc",&probHcc_md,&b_probHcc_md);
	T->SetBranchAddress("jet_pfMassIndependentDeepDoubleCvLV2JetTags_probHcc",&probHcc_ddx,&b_probHcc_ddx);	
	T->SetBranchAddress("AK8PuppiJets_eta",&AK8_eta, &b_AK8_eta);
	T->SetBranchAddress("AK8PuppiJets_pt",&AK8_pt, &b_AK8_pt);
	T->SetBranchAddress("AK8PuppiJets_phi",&AK8_phi, &b_AK8_phi);
	T->SetBranchAddress("GENjet_eta",&GEN_eta, &b_GEN_eta);
        T->SetBranchAddress("GENjet_phi",&GEN_phi, &b_GEN_phi);		
	T->SetBranchAddress("quark_eta",&quark_eta, &b_quark_eta);
        T->SetBranchAddress("quark_phi",&quark_phi, &b_quark_phi);
	T->SetBranchAddress("quark_flavour",&quark_flavour, &b_quark_flavour);
        T->SetBranchAddress("quark_VBF",&quark_VBF, &b_quark_VBF);
//T->SetBranchAddress("jet_pfParticleNetJetTags_probHcc", &probHcc);

	float n_Higgs=0;
	float n_VBF=0;
	float n_tot=0;


	Int_t nentries = (Int_t)T->GetEntries();
	cout<<nentries<<"\n";	
	//loop sugli eventi
	for (Int_t i=0;i<nentries;i++) {

	Long64_t tentry = T->LoadTree(i);
      	b_probHcc->GetEntry(tentry);
	b_probHcc_md->GetEntry(tentry);
	b_probHcc_ddx->GetEntry(tentry);
	b_AK8_eta->GetEntry(tentry);
	b_AK8_pt->GetEntry(tentry);
	b_AK8_phi->GetEntry(tentry);
	b_GEN_eta->GetEntry(tentry);
        b_GEN_phi->GetEntry(tentry);
	b_quark_eta->GetEntry(tentry);
        b_quark_phi->GetEntry(tentry);
	b_quark_flavour->GetEntry(tentry);
        b_quark_VBF->GetEntry(tentry);
	//hist1->Fill((Int_t)probHcc->size());
	//loop sugli AK8 in un evento

	float Higgs_v1;
	float Higgs_v2;
	float Higgs_score =  -99999;

	for (UInt_t j = 0; j < probHcc->size(); ++j) {
	 //non faccio niente se nell'evento non c'è almeno un jet AK8
           if(AK8_pt->at(j)>170){

	     // 	 hist1->Fill(AK8_phi->at(j),AK8_eta->at(j));
	     float score_average;
	     
	     Int_t binx = hist1->GetXaxis()->FindBin(AK8_phi->at(j)); 
	     Int_t biny = hist1->GetYaxis()->FindBin(AK8_eta->at(j)); 
	     Int_t bin = hist1->GetBin(binx,biny,0); //see doc of TH1::GetBin h2->SetBinContent(bin,c); //where bin is the linearized bin number 
	     hist1->SetBinContent(bin,score_average);
	     hist2->SetBinContent(bin,score_average);
	     hist1->Divide(hist2);
	 int rq_idx = -1;
			int  rq_bestidx1 = -1;
			float rq_bestdr1 = 9999.;
			
			//loop sui quark
			for (UInt_t zz = 0; zz < quark_eta->size(); ++zz) {
				rq_idx = rq_idx +1;
				float rqdr1 = deltaR(AK8_eta->at(j),AK8_phi->at(j), quark_eta->at(zz), quark_phi->at(zz));
	
				if(rqdr1 < 0.5 && rqdr1 < rq_bestdr1 ){
					rq_bestidx1 = rq_idx;
                                	rq_bestdr1 = rqdr1;
				}
			
			}//chiude i loop sui quark

			if(rq_bestidx1 > -1 /*&&  abs(quark_flavour->at(rq_bestidx1)) == 4*/	&&  quark_VBF->at(rq_bestidx1) ==  1 /*&& probHcc->at(j) > Higgs_score*/){
			  //hist1->Fill(AK8_pt->at(j),probHcc->at(j))
			  //		  hist1->Fill(AK8_phi->at(j),AK8_eta->at(j));
																					/*		  	Higgs_score = probHcc->at(j);
			  Higgs_v1 = AK8_phi->at(j);
			  Higgs_v2 = AK8_eta->at(j);*/
}



}
}//fine loop jet AK8

	//	if(Higgs_score > -1){ hist1->Fill(Higgs_v1,Higgs_v2);}
	}//fine loop eventi


       //cout<<"Dei "<<n_tot << " che hanno come score 0 "<<n_Higgs<<" sono associati all'Higgs e "<<n_VBF<<" sono jet VBF\n" ;




	hist1->SetTitle("AK8 jets");
	hist1->GetXaxis()->SetTitle("#phi");
	//     	hist1->GetXaxis()->SetTitle("p_{T} [GeV]");
    	hist1->GetYaxis()->SetTitle("#eta");
//	hist1->GetYaxis()->SetTitle("probHcc");	


	hist[0]= hist1;


//	hist[0]->Scale(S*lum/tot);
//	hist[1]->Scale(S*lum/tot);
		
}

void distr_1D(TFile* f1,  float S,  TH1F  *hist[3]) {
    
	

	TTree *T = (TTree*)f1->Get("Ana/passedEvents");
	TH1F *hist1 = new TH1F("hist1", "hist1", 66, 170, 500);
	TH1F *hist2 = new TH1F("hist2", "hist2", 66, 170, 500);
	TH1F *hist3 = new TH1F("hist3", "hist3", 66, 170, 500);
	//TH1F *hist1 = new TH1F("hist1", "hist1",  100, -5, 5);
  	//TH1F *hist2 = new TH1F("hist2", "hist2",  100, -5, 5);

	/*	TH1F *hist1 = new TH1F("hist1", "hist1", 20, 0, 1);
   	 TH1F *hist2 = new TH1F("hist2", "hist2", 20, 0, 1);
	 TH1F *hist3 = new TH1F("hist3", "hist3", 20, 0, 1);
	*/
	std::vector<float> *probHcc = 0;
	std::vector<float> *probHcc_md = 0;
	std::vector<float> *probHcc_ddx = 0;
	std::vector<float> *AK8_eta = 0;
	std::vector<float> *AK8_pt = 0;
	std::vector<float> *AK8_phi = 0;
	std::vector<float> *GEN_eta = 0;
	std::vector<float> *GEN_phi = 0;
	std::vector<float> *quark_eta = 0;
        std::vector<float> *quark_phi = 0;
	std::vector<int> *quark_flavour = 0;
	std::vector<bool> *quark_VBF = 0;
	

	TBranch *b_probHcc = 0;
	TBranch *b_probHcc_md = 0;
	TBranch *b_probHcc_ddx = 0;
	TBranch *b_AK8_eta = 0;
	TBranch *b_AK8_pt = 0;
	TBranch *b_AK8_phi = 0;
	TBranch *b_GEN_eta = 0;
        TBranch *b_GEN_phi = 0;
	TBranch *b_quark_eta = 0;
        TBranch *b_quark_phi = 0;
	TBranch *b_quark_flavour = 0;
        TBranch *b_quark_VBF = 0;

   	T->SetBranchAddress("jet_pfParticleNetJetTags_probHcc",&probHcc,&b_probHcc);	
	T->SetBranchAddress("jet_pfMassDecorrelatedParticleNetJetTags_probXcc",&probHcc_md,&b_probHcc_md);
	T->SetBranchAddress("jet_pfMassIndependentDeepDoubleCvLV2JetTags_probHcc",&probHcc_ddx,&b_probHcc_ddx);	
	T->SetBranchAddress("AK8PuppiJets_eta",&AK8_eta, &b_AK8_eta);
	T->SetBranchAddress("AK8PuppiJets_pt",&AK8_pt, &b_AK8_pt);
	T->SetBranchAddress("AK8PuppiJets_phi",&AK8_phi, &b_AK8_phi);
	T->SetBranchAddress("GENjet_eta",&GEN_eta, &b_GEN_eta);
        T->SetBranchAddress("GENjet_phi",&GEN_phi, &b_GEN_phi);		
	T->SetBranchAddress("quark_eta",&quark_eta, &b_quark_eta);
        T->SetBranchAddress("quark_phi",&quark_phi, &b_quark_phi);
	T->SetBranchAddress("quark_flavour",&quark_flavour, &b_quark_flavour);
        T->SetBranchAddress("quark_VBF",&quark_VBF, &b_quark_VBF);



	Int_t nentries = (Int_t)T->GetEntries();
	cout<<nentries<<"\n";	
	//loop sugli eventi
	for (Int_t i=0;i<nentries;i++) {

	Long64_t tentry = T->LoadTree(i);
      	b_probHcc->GetEntry(tentry);
	b_probHcc_md->GetEntry(tentry);
	b_probHcc_ddx->GetEntry(tentry);
	b_AK8_eta->GetEntry(tentry);
	b_AK8_pt->GetEntry(tentry);
	b_AK8_phi->GetEntry(tentry);
	b_GEN_eta->GetEntry(tentry);
        b_GEN_phi->GetEntry(tentry);
	b_quark_eta->GetEntry(tentry);
        b_quark_phi->GetEntry(tentry);
	b_quark_flavour->GetEntry(tentry);
        b_quark_VBF->GetEntry(tentry);

	float Higgs_v;
	float Higgs_score =  -99999;

	 //loop sugli AK8 in un evento
	for (UInt_t j = 0; j < probHcc->size(); ++j) {
	 //non faccio niente se nell'evento non c'è almeno un jet AK8 buono
       if(AK8_pt->at(j)>170){ 
		hist3->Fill(AK8_pt->at(j));
				int rq_idx = -1;
			int  rq_bestidx1 = -1;
			float rq_bestdr1 = 9999.;
			
			//loop sui quark
			for (UInt_t zz = 0; zz < quark_eta->size(); ++zz) {
				rq_idx = rq_idx +1;
				float rqdr1 = deltaR(AK8_eta->at(j),AK8_phi->at(j), quark_eta->at(zz), quark_phi->at(zz));
		//		float qdr2 = deltaR(GEN_eta->at(g_bestidx2),GEN_phi->at(g_bestidx2), quark_eta->at(z), quark_phi->at(z));

				if(rqdr1 < 0.5 && rqdr1 < rq_bestdr1 ){
					rq_bestidx1 = rq_idx;
                                	rq_bestdr1 = rqdr1;
				}
	     
			}//chiude i loop sui quark

			if(rq_bestidx1 > -1 && /* abs(quark_flavour->at(rq_bestidx1)) == 4 	&& */ quark_VBF->at(rq_bestidx1) ==  1 ){hist2->Fill(AK8_pt->at(j));}
			if(rq_bestidx1 > -1 &&  abs(quark_flavour->at(rq_bestidx1)) == 4 	&&  quark_VBF->at(rq_bestidx1) ==  0 && probHcc->at(j) > Higgs_score){
			  Higgs_score = probHcc->at(j);
			  Higgs_v = AK8_pt->at(j);
			  
			  /*  hist1->Fill(probHcc->at(j));
			      hist2->Fill(probHcc_md->at(j));
			      hist3->Fill(probHcc_ddx->at(j));*/
			}


      }}//fine loop jet AK8

	if(Higgs_score > -1){ hist1->Fill(Higgs_v);}


	}//fine loop eventi



//	hist1->GetXaxis()->SetTitle("probHcc");	
	hist1->GetYaxis()->SetTitle("Normalized to 1");
	//hist2->GetXaxis()->SetTitle("probHcc");	
	hist2->GetYaxis()->SetTitle("Normalized to 1");
	//hist3->GetXaxis()->SetTitle("probHcc");	
	hist3->GetYaxis()->SetTitle("Normalized to 1");

	hist3->GetXaxis()->SetTitle("p_{T} [GeV]");

	hist1->SetTitle("Matched AK8 jets");
	hist1->GetXaxis()->SetTitle("p_{T} [GeV]");
	//hist1->GetYaxis()->SetTitle("a.u./ 5 GeV");
    	//hist1->GetXaxis()->SetTitle("#eta");
	//hist1->GetYaxis()->SetTitle("a.u./ 0.1");
	//hist2->GetYaxis()->SetTitle("a.u./ 0.1");
	hist2->SetTitle("Matched AK8 jets");
	hist3->SetTitle("All AK8 jets");
	hist2->GetXaxis()->SetTitle("p_{T} [GeV]");
	//     hist2->GetYaxis()->SetTitle("a.u./ 5 GeV");
	       //hist2->GetXaxis()->SetTitle("#eta");
 //

hist[1]= hist2;
	hist[0]= hist1;
hist[0]->SetLineColor(2);
        hist[1]->SetLineColor(4);
hist[2]= hist3;
hist[2]->SetLineColor(1);


//	hist[0]->Scale(S*lum/tot);
//	hist[1]->Scale(S*lum/tot);
		
}

void multiplicity(TFile* f1,  float S,  TH1F  *hist[3]) {
  /* int tot=0;
    TH1F* h_num_eventi;
    float num_event;
    h_num_eventi = (TH1F*) f1->Get("Ana/sumWeights");
    num_event = h_num_eventi->Integral();
    tot = tot + num_event;
  */	

	TTree *T = (TTree*)f1->Get("Ana/passedEvents");
   	TH1F *hist1 = new TH1F("hist1", "hist1", 5, -0.5, 4.5);
	TH1F *hist2 = new TH1F("hist2", "hist2", 5, -0.5, 4.5);
	TH1F *hist3 = new TH1F("hist3", "hist3", 5, -0.5, 4.5);
	TH1F *hist4 = new TH1F("hist4", "hist4", 5, -0.5, 4.5);
//  	TH1F *hist2 = new TH1F("hist2", "hist2",  100, -5, 5);

	std::vector<float> *probHcc = 0;
	std::vector<float> *AK8_eta = 0;
	std::vector<float> *AK8_pt = 0;
	std::vector<float> *AK8_phi = 0;
	std::vector<float> *GEN_eta = 0;
	std::vector<float> *GEN_phi = 0;
	std::vector<float> *quark_eta = 0;
        std::vector<float> *quark_phi = 0;
	std::vector<int> *quark_flavour = 0;
	std::vector<bool> *quark_VBF = 0;
	

	TBranch *b_probHcc = 0;
	TBranch *b_AK8_eta = 0;
	TBranch *b_AK8_pt = 0;
	TBranch *b_AK8_phi = 0;
	TBranch *b_GEN_eta = 0;
        TBranch *b_GEN_phi = 0;
	TBranch *b_quark_eta = 0;
        TBranch *b_quark_phi = 0;
	TBranch *b_quark_flavour = 0;
        TBranch *b_quark_VBF = 0;

   	T->SetBranchAddress("jet_pfParticleNetJetTags_probHcc",&probHcc,&b_probHcc);	
		T->SetBranchAddress("AK8PuppiJets_eta",&AK8_eta, &b_AK8_eta);
	T->SetBranchAddress("AK8PuppiJets_pt",&AK8_pt, &b_AK8_pt);
	T->SetBranchAddress("AK8PuppiJets_phi",&AK8_phi, &b_AK8_phi);
//	T->SetBranchAddress("AK4PuppiJets_eta",&AK8_eta, &b_AK8_eta);
//	T->SetBranchAddress("AK4PuppiJets_pt",&AK8_pt, &b_AK8_pt);
//	T->SetBranchAddress("AK4PuppiJets_phi",&AK8_phi, &b_AK8_phi);
	T->SetBranchAddress("GENjet_eta",&GEN_eta, &b_GEN_eta);
        T->SetBranchAddress("GENjet_phi",&GEN_phi, &b_GEN_phi);		
	T->SetBranchAddress("quark_eta",&quark_eta, &b_quark_eta);
        T->SetBranchAddress("quark_phi",&quark_phi, &b_quark_phi);
	T->SetBranchAddress("quark_flavour",&quark_flavour, &b_quark_flavour);
        T->SetBranchAddress("quark_VBF",&quark_VBF, &b_quark_VBF);



	Int_t nentries = (Int_t)T->GetEntries();
	cout<<nentries<<"\n";	
	//loop sugli eventi
	for (Int_t i=0;i<nentries;i++) {

	Long64_t tentry = T->LoadTree(i);
      	b_probHcc->GetEntry(tentry);
	b_AK8_eta->GetEntry(tentry);
	b_AK8_pt->GetEntry(tentry);
	b_AK8_phi->GetEntry(tentry);
	b_GEN_eta->GetEntry(tentry);
        b_GEN_phi->GetEntry(tentry);
	b_quark_eta->GetEntry(tentry);
        b_quark_phi->GetEntry(tentry);
	b_quark_flavour->GetEntry(tentry);
        b_quark_VBF->GetEntry(tentry);

	float n_Higgs=0;
	float n_VBF=0;
	float n_AK8=0;
	float n_AK8p=0;



	 //loop sugli AK8 in un evento
	for (UInt_t j = 0; j < AK8_pt->size(); ++j) {
	 //non faccio niente se nell'evento non c'è almeno un jet AK8
	  if(AK8_pt->at(j)>170){ 
	 
	 n_AK8 = n_AK8 +1;
	 int rq_idx = -1;
			int  rq_bestidx1 = -1;
			float rq_bestdr1 = 9999.;
			
			//loop sui quark
			for (UInt_t zz = 0; zz < quark_eta->size(); ++zz) {
				rq_idx = rq_idx +1;
				float rqdr1 = deltaR(AK8_eta->at(j),AK8_phi->at(j), quark_eta->at(zz), quark_phi->at(zz));
		//		float qdr2 = deltaR(GEN_eta->at(g_bestidx2),GEN_phi->at(g_bestidx2), quark_eta->at(z), quark_phi->at(z));

				if(rqdr1 < 0.5 && rqdr1 < rq_bestdr1 ){
					rq_bestidx1 = rq_idx;
                                	rq_bestdr1 = rqdr1;
				}
	     
			}//chiude i loop sui quark

			if(rq_bestidx1 > -1 && /* abs(quark_flavour->at(rq_bestidx1)) == 4 	&& */ quark_VBF->at(rq_bestidx1) ==  1 ){n_Higgs = n_Higgs +1;}
			if(rq_bestidx1 > -1 &&  abs(quark_flavour->at(rq_bestidx1)) == 4 	&&  quark_VBF->at(rq_bestidx1) ==  0 ){n_VBF = n_VBF +1;}
		
	
				}//chiude i loop sui jet AK8 buoni
						 

 	
 	
      }//fine loop jet AK8

hist1->Fill(n_Higgs);

hist2->Fill(n_VBF);

hist3->Fill(n_AK8);

hist4->Fill(n_VBF+n_Higgs);
	}//fine loop eventi







	hist1->SetTitle("Multiplicity matched AK8 jets");
    	hist1->GetXaxis()->SetTitle("# jets");
	hist1->GetYaxis()->SetTitle("a.u.");
//    	hist1->GetXaxis()->SetTitle("#eta");
//hist1->GetYaxis()->SetTitle("a.u./ 0.1");
//hist2->GetYaxis()->SetTitle("a.u./ 0.1");
	hist2->SetTitle("");
      hist2->GetXaxis()->SetTitle("# jets");
              hist2->GetYaxis()->SetTitle("a.u.");
  //      hist2->GetXaxis()->SetTitle("#eta");
 //
hist3->SetTitle("Multiplicity all AK8 jets");
      hist3->GetXaxis()->SetTitle("# jets");
              hist3->GetYaxis()->SetTitle("a.u.");
hist4->SetTitle("");
      hist4->GetXaxis()->SetTitle("# jets");
              hist4->GetYaxis()->SetTitle("a.u.");

hist[1]= hist2;
	hist[0]= hist1;
hist[0]->SetLineColor(2);
        hist[1]->SetLineColor(4);

hist[2]= hist3;
	hist[3]= hist4;
hist[2]->SetLineColor(2);
        hist[3]->SetLineColor(4);


	auto c1 = new TCanvas("c1", "c1", 1200, 800);
	
	c1->cd();
	
	hist[0]->Draw("hist");
	hist[1]->Draw("histsame");
	
	auto leg = new TLegend{0.7,0.6,0.9,0.75}; // xmin, ymin, xmax, ymax rispetto al pad  
  leg->AddEntry(hist[0], "Higgs-jets"); 
  leg->AddEntry(hist[1], "VBF-jets");  // L'opzione F disegna il rettangolino, se non la metti ti disegna anche la croce nella legenda
    leg->SetBorderSize(0); // Per disegnarla senza il rettangolo intorno 
     leg->Draw();

    auto c2 = new TCanvas("c2", "c2", 1200, 800);
	
	c2->cd();
	
	hist[2]->Draw("hist");
	hist[3]->Draw("histsame");
	
	auto leg1 = new TLegend{0.7,0.6,0.9,0.75}; // xmin, ymin, xmax, ymax rispetto al pad  
  leg1->AddEntry(hist[2], "without match"); 
  leg1->AddEntry(hist[3], "with match");  // L'opzione F disegna il rettangolino, se non la metti ti disegna anche la croce nella legenda
    leg1->SetBorderSize(0); // Per disegnarla senza il rettangolo intorno 
     leg1->Draw();


//	hist[0]->Scale(S*lum/tot);
//	hist[1]->Scale(S*lum/tot);
		
}




void efficiency(TFile* f1) {
  
  vector<Float_t> vpt;
  //  vpt.push_back(50);
  vpt.push_back(170);
  vpt.push_back(250);
  vpt.push_back(300);
  vpt.push_back(350);
  vpt.push_back(400);
  vpt.push_back(450);
  vpt.push_back(500);

  const Int_t NBINS = vpt.size()-1;

  Float_t vptm[NBINS];
  Float_t vpte[NBINS];

  Float_t eff_D[NBINS];
  Float_t eff_N1[NBINS];
  Float_t eff_N2[NBINS];
  Float_t eff_N3[NBINS];

  for(int pi=0;pi<NBINS;pi++){ 
    vptm[pi]=(vpt[pi+1]+vpt[pi])/2; 
    vpte[pi]=(vpt[pi+1]-vpt[pi])/2; 
    eff_D[pi]=0;
    eff_N1[pi]=0;
    eff_N2[pi]=0;
    eff_N3[pi]=0;    
}

  



  Float_t eff1[NBINS];
  Float_t eff2[NBINS];
  Float_t eff3[NBINS];
  Float_t eff1_er[NBINS];
  Float_t eff2_er[NBINS];
  Float_t eff3_er[NBINS];
  /*
  cout<<eff_D[0]<<"\n";
  eff_D[0] = eff_D[0]+9;
  cout<<eff_D[0]<<"\n";*/

  float n_jets = 0;
  float n_jets_300 = 0;
  
  	TTree *T = (TTree*)f1->Get("Ana/passedEvents");
	//  	TH1F *hist1 = new TH1F("hist1", "hist1", 5, -0.5, 4.5);
	//	TH1F *hist2 = new TH1F("hist2", "hist2", 5, -0.5, 4.5);
//	TH1F *hist1 = new TH1F("hist1", "hist1",  100, -5, 5);
//  	TH1F *hist2 = new TH1F("hist2", "hist2",  100, -5, 5);

	std::vector<float> *probHcc = 0;
	std::vector<float> *AK8_eta = 0;
	std::vector<float> *AK8_pt = 0;
	std::vector<float> *AK8_phi = 0;
	std::vector<float> *GEN_eta = 0;
	std::vector<float> *GEN_phi = 0;
	std::vector<float> *quark_eta = 0;
        std::vector<float> *quark_phi = 0;
	std::vector<int> *quark_flavour = 0;
	std::vector<bool> *quark_VBF = 0;
	

	TBranch *b_probHcc = 0;
	TBranch *b_AK8_eta = 0;
	TBranch *b_AK8_pt = 0;
	TBranch *b_AK8_phi = 0;
	TBranch *b_GEN_eta = 0;
        TBranch *b_GEN_phi = 0;
	TBranch *b_quark_eta = 0;
        TBranch *b_quark_phi = 0;
	TBranch *b_quark_flavour = 0;
        TBranch *b_quark_VBF = 0;

   	T->SetBranchAddress("jet_pfParticleNetJetTags_probHcc",&probHcc,&b_probHcc);	
		T->SetBranchAddress("AK8PuppiJets_eta",&AK8_eta, &b_AK8_eta);
	T->SetBranchAddress("AK8PuppiJets_pt",&AK8_pt, &b_AK8_pt);
	T->SetBranchAddress("AK8PuppiJets_phi",&AK8_phi, &b_AK8_phi);
//	T->SetBranchAddress("AK4PuppiJets_eta",&AK8_eta, &b_AK8_eta);
//	T->SetBranchAddress("AK4PuppiJets_pt",&AK8_pt, &b_AK8_pt);
//	T->SetBranchAddress("AK4PuppiJets_phi",&AK8_phi, &b_AK8_phi);
	T->SetBranchAddress("GENjet_eta",&GEN_eta, &b_GEN_eta);
        T->SetBranchAddress("GENjet_phi",&GEN_phi, &b_GEN_phi);		
	T->SetBranchAddress("quark_eta",&quark_eta, &b_quark_eta);
        T->SetBranchAddress("quark_phi",&quark_phi, &b_quark_phi);
	T->SetBranchAddress("quark_flavour",&quark_flavour, &b_quark_flavour);
        T->SetBranchAddress("quark_VBF",&quark_VBF, &b_quark_VBF);



	Int_t nentries = (Int_t)T->GetEntries();
	cout<<nentries<<"\n";	
	//loop sugli eventi
	for (Int_t i=0;i<nentries;i++) {

	Long64_t tentry = T->LoadTree(i);
      	b_probHcc->GetEntry(tentry);
	b_AK8_eta->GetEntry(tentry);
	b_AK8_pt->GetEntry(tentry);
	b_AK8_phi->GetEntry(tentry);
	b_GEN_eta->GetEntry(tentry);
        b_GEN_phi->GetEntry(tentry);
	b_quark_eta->GetEntry(tentry);
        b_quark_phi->GetEntry(tentry);
	b_quark_flavour->GetEntry(tentry);
        b_quark_VBF->GetEntry(tentry);





	 //loop sugli AK8 in un evento
	for (UInt_t j = 0; j < AK8_pt->size(); ++j) {
	  
	  int g_idx = -1;
                int  g_bestidx1 = -1;
		int  g_bestidx2 = -1;
                float g_bestdr1 = 9999.;
		float g_bestdr2 = 9999.;
		//loop sui get generati
		for (UInt_t ii = 0; ii < GEN_eta->size(); ++ii) {
			g_idx = g_idx +1;			
			float dr1 = deltaR(GEN_eta->at(ii),GEN_phi->at(ii), AK8_eta->at(j), AK8_phi->at(j));
			/*	if (dr1 < 0.8 && dr1 < g_bestdr1) {
				g_bestidx2 = g_bestidx1;
				g_bestdr2 = g_bestdr1;
			      	g_bestidx1 = g_idx;
	      			g_bestdr1 = dr1;}
			if (dr1 < 0.8 && dr1 > g_bestdr1 && dr1 <  g_bestdr2) {
                                g_bestidx2 = g_idx;
                                g_bestdr2 = dr1;}*/
			if (dr1 < 0.5 /* 0.3*/ && dr1 < g_bestdr1) {
			      	g_bestidx1 = g_idx;
	      			g_bestdr1 = dr1;}

		}//fine loop sui jet generati
	//se ci sono due jet generati che matchano col AK8
		if (g_bestidx1 > -1) {// hist2->Fill(probHcc->at(j));
	//			cout<<"Nell'evento "<<i << " il Jet AK8 "<<j<<" èassociato ai generati "<<g_bestidx1<<" e "<<g_bestidx2<<"\n" ;
				int q_idx = -1;
				int  q_bestidx1 = -1;
				int  q_bestidx2 = -1;
				float q_bestdr1 = 9999.;
				float q_bestdr2 = 9999.;
				
				//loop sui quark
				for (UInt_t z = 0; z < quark_eta->size(); ++z) {
					q_idx = q_idx +1;
					float qdr1 = deltaR(GEN_eta->at(g_bestidx1),GEN_phi->at(g_bestidx1), quark_eta->at(z), quark_phi->at(z));
			//		float qdr2 = deltaR(GEN_eta->at(g_bestidx2),GEN_phi->at(g_bestidx2), quark_eta->at(z), quark_phi->at(z));

					if(qdr1 < 0.3 && qdr1 < q_bestdr1 ){
						q_bestidx1 = q_idx;
						q_bestdr1 = qdr1;
					}
					/*	
					if(qdr2 < 99990.4 && qdr2 < q_bestdr2 && qdr1 > qdr2){
						q_bestidx2 = q_idx;
						q_bestdr2 = qdr2;
					}
	*/
				}//chiude i loop sui quark


				int rq_idx = -1;
			int  rq_bestidx1 = -1;
			float rq_bestdr1 = 9999.;
			
			//loop sui quark
			for (UInt_t zz = 0; zz < quark_eta->size(); ++zz) {
				rq_idx = rq_idx +1;
				float rqdr1 = deltaR(AK8_eta->at(j),AK8_phi->at(j), quark_eta->at(zz), quark_phi->at(zz));
		//		float qdr2 = deltaR(GEN_eta->at(g_bestidx2),GEN_phi->at(g_bestidx2), quark_eta->at(z), quark_phi->at(z));

				if(rqdr1 < 0.5 && rqdr1 < rq_bestdr1 ){
					rq_bestidx1 = rq_idx;
                                	rq_bestdr1 = rqdr1;
				}
				/*	
				if(qdr2 < 99990.4 && qdr2 < q_bestdr2 && qdr1 > qdr2){
                                        q_bestidx2 = q_idx;
                                        q_bestdr2 = qdr2;
                                }
*/
			}//chiude i loop sui quark
			
			if(rq_bestidx1 > -1 && abs(quark_flavour->at(rq_bestidx1)) == 4 	&& quark_VBF->at(rq_bestidx1 ) ==  0 ){
			  n_jets = n_jets +1;
			  if(AK8_pt->at(j)>300){
			    n_jets_300 = n_jets_300 +1;}}
				
				//se i jet generati matchano con una coppia ccbar non VBF riempio l'istogramma finale
				if(rq_bestidx1 > -1 && abs(quark_flavour->at(rq_bestidx1)) == 4 	&& quark_VBF->at(rq_bestidx1 ) ==  0 && AK8_pt->at(j) > vpt.at(NBINS-1))
				  {eff_D[NBINS-1] = eff_D[NBINS-1] +1;
				    if(probHcc->at(j) > 0.3){eff_N1[NBINS-1] = eff_N1[NBINS-1] +1;}
				    if(probHcc->at(j) > 0.5){eff_N2[NBINS-1] = eff_N2[NBINS-1] +1;}
				    if(probHcc->at(j) > 0.7){eff_N3[NBINS-1] = eff_N3[NBINS-1] +1;}
				  }
				
				for( int y=0;y<NBINS-1; y++){
  if(rq_bestidx1 > -1 && abs(quark_flavour->at(rq_bestidx1)) == 4 	&& quark_VBF->at(rq_bestidx1 ) ==  0 && AK8_pt->at(j) > vpt.at(y) && AK8_pt->at(j) < vpt.at(y+1))
    {eff_D[y] = eff_D[y] +1;
				    if(probHcc->at(j) > 0.3){eff_N1[y] = eff_N1[y] +1;}
				    if(probHcc->at(j) > 0.5){eff_N2[y] = eff_N2[y] +1;}
				    if(probHcc->at(j) > 0.7){eff_N3[y] = eff_N3[y] +1;}
				  }
				      }
				//				if(q_bestidx1 > -1 && /*abs(quark_flavour->at(q_bestidx1)) == 4   &&*/ quark_VBF->at(q_bestidx1) ==  1 && AK8_pt->at(j)>20){n_VBF = n_VBF +1;}			 
	}//chiude if se c'erano due jet generati compatibili con il jet AK8
 	

	  
}//fine loop jet AK8




}//fine loop eventi

	cout<<"Ci sono in totale " <<n_jets<<" Jet AK8 associati a un c Higgs e "<<n_jets_300<<" con pT >300 \n" ;

 for(int Pi=0;Pi<NBINS;Pi++){ 
   eff1[Pi]=eff_N1[Pi]/eff_D[Pi];
   eff2[Pi]=eff_N2[Pi]/eff_D[Pi];
   eff3[Pi]=eff_N3[Pi]/eff_D[Pi];
   eff1_er[Pi]= sqrt((sqrt(eff_N1[Pi])/eff_D[Pi])*(sqrt(eff_N1[Pi])/eff_D[Pi])+(eff_N1[Pi]*sqrt(eff_D[Pi])/(eff_D[Pi]*eff_D[Pi]))*(eff_N1[Pi]*sqrt(eff_D[Pi])/(eff_D[Pi]*eff_D[Pi])));
   eff2_er[Pi]= sqrt((sqrt(eff_N2[Pi])/eff_D[Pi])*(sqrt(eff_N2[Pi])/eff_D[Pi])+(eff_N2[Pi]*sqrt(eff_D[Pi])/(eff_D[Pi]*eff_D[Pi]))*(eff_N2[Pi]*sqrt(eff_D[Pi])/(eff_D[Pi]*eff_D[Pi])));
   eff3_er[Pi]= sqrt((sqrt(eff_N3[Pi])/eff_D[Pi])*(sqrt(eff_N3[Pi])/eff_D[Pi])+(eff_N3[Pi]*sqrt(eff_D[Pi])/(eff_D[Pi]*eff_D[Pi]))*(eff_N3[Pi]*sqrt(eff_D[Pi])/(eff_D[Pi]*eff_D[Pi])));
 }

 TGraphErrors *gr1 = new TGraphErrors(NBINS, vptm, eff1, vpte, eff1_er);
 gr1->SetMarkerColor(1);
 gr1->SetLineColor(1);
 gr1->SetMarkerStyle(4);
 TGraphErrors *gr2 = new TGraphErrors(NBINS, vptm, eff2, vpte, eff2_er);
 gr2->SetMarkerColor(2);
 gr2->SetLineColor(2);
 gr2->SetMarkerStyle(4);
 TGraphErrors *gr3 = new TGraphErrors(NBINS, vptm, eff3, vpte, eff3_er);
 gr3->SetMarkerColor(4);
 gr3->SetLineColor(4);
 gr3->SetMarkerStyle(4);

 gr1->SetMarkerSize(0.9);
 gr2->SetMarkerSize(1.5);
 gr3->SetMarkerSize(1.9);
  TMultiGraph *mg = new TMultiGraph();

	  // Draw the scatter plot on a canvas
  TCanvas *canvas = new TCanvas("Canvas", "Scatter Plot", 800, 600);
    
  mg->Add(gr1,"P");
  mg->Add(gr2,"P");
  mg->Add(gr3,"P");

  mg->GetXaxis()->SetLimits(vpt.at(0),vpt.at(NBINS) );
   mg->SetMinimum(0);
  
  mg->GetXaxis()->SetTitle("p_{T} [GeV]");
  mg->GetYaxis()->SetTitle("#epsilon");


  mg->Draw("a");


  auto leg = new TLegend{0.15, 0.65, 0.5, 0.85}; // xmin, ymin, xmax, ymax rispetto al pad  
  leg->AddEntry(gr1, "score H#rightarrow c#bar{c} > 0.3"); 
    leg->AddEntry(gr2, "score H#rightarrow c#bar{c} > 0.5");
    leg->AddEntry(gr3, "score H#rightarrow c#bar{c} > 0.7");// L'opzione F disegna il rettangolino, se non la metti ti disegna anche la croce nella legenda
    leg->SetBorderSize(0); // Per disegnarla senza il rettangolo intorno 
    leg->Draw();

  canvas->Update();
  
  // Save the canvas as an image
  canvas->SaveAs("efficiency.png");
	}



void taggers_Hcc(){
  gStyle->SetOptStat(0000);
  //signals
  TFile* f1 = TFile::Open("/afs/cern.ch/user/d/dtroiano/AK8/CMSSW_12_4_3/src/hcc_v2/UFHZZ4LAna/python/VBFHToCC_Run3_prova_DDX_1.root","read");
  float s1 = 0.01333521;
  /*  TH1F *sig_Hcc[DIM];
    distr_probHcc( f1, s1, sig_Hcc);

	auto c_Hcc = new TCanvas("c_Hcc", "c_Hcc", 1200, 800);
	
	sig_Hcc[0]->SetLineColor(2);
	sig_Hcc[1]->SetLineColor(4);
  

	auto legendHcc = new TLegend(0.7,0.5,0.9,0.7);
  legendHcc->AddEntry(sig_Hcc[0],"without reco-gen match","l");
	legendHcc->AddEntry(sig_Hcc[1],"with reco-gen match","l");
  //legend->AddEntry(sig_Hcc[0],"VBF","l");
  
  	c_Hcc->cd();
	c_Hcc->SetLogy();

	sig_Hcc[0]->Draw("hist");
	//	sig_Hcc[1]->Draw("histsame");
	
	//	legendHcc->Draw("");

	*/	
/*


	TH1F *sig_Hbb[DIM];
  distr_probHbb( f1, s1, sig_Hbb);

	auto c_Hbb = new TCanvas("c_Hbb", "c_Hbb", 1200, 800);
	
	sig_Hbb[0]->SetLineColor(2);


  auto legendHbb = new TLegend(0.7,0.5,0.9,0.7);
  legendHbb->AddEntry(sig_Hbb[0],"without reco-gen match","l");
  //legend->AddEntry(sig_Hcc[0],"VBF","l");
  
	c_Hbb->cd();
	c_Hbb->SetLogy();

	sig_Hbb[0]->Draw("hist");
	
	legendHbb->Draw("");

*/
//	TH1F *sig_1D[3];
			TH2F *sig_2D[1];
		distr_2D( f1, s1, sig_2D);	
		//	distr_1D( f1, s1, sig_1D);
	//multiplicity( f1, s1, sig_1D);
		auto c_Hbb = new TCanvas("c_Hbb", "c_Hbb", 1200, 800);
	

  
		c_Hbb->cd();
			c_Hbb->SetLogz();
	//	c_Hbb->SetLogy();
			sig_2D[0]->Draw("colz");

	
			//	sig_1D[0]->DrawNormalized("hist");
			//		sig_1D[1]->DrawNormalized("histsame");
	//	sig_1D[2]->DrawNormalized("hist");
			
			/*	auto legend1D = new TLegend(0.7,0.6,0.9,0.75);
  legend1D->AddEntry(sig_1D[0],"ParticleNet score","l");
	legend1D->AddEntry(sig_1D[1],"ParticleNet-MD score","l");
	legend1D->AddEntry(sig_1D[2],"DeepDobleX score","l");
	legend1D->SetBorderSize(0);
 legend1D->Draw("");
			*/

/*	auto legend1D = new TLegend(0.7,0.5,0.9,0.7);
  legend1D->AddEntry(sig_1D[0],"AK8->AK4gen->quark","l");
	legend1D->AddEntry(sig_1D[1],"AK8->quark","l");
 legend1D->Draw("");
*/

/*	auto legend1D = new TLegend(0.7,0.5,0.9,0.7);
  legend1D->AddEntry(sig_1D[0],"Higgs-jets","l");
	legend1D->AddEntry(sig_1D[1],"VBF-jets","l");
		legend1D->SetBorderSize(0);
 legend1D->Draw("");
*/

//	scatterplot( f1);
//	efficiency( f1);
}







void scatterplot(TFile* f1) {
    
  TGraph *graph = new TGraph();

	TTree *T = (TTree*)f1->Get("Ana/passedEvents");
	//  	TH1F *hist1 = new TH1F("hist1", "hist1", 5, -0.5, 4.5);
	//	TH1F *hist2 = new TH1F("hist2", "hist2", 5, -0.5, 4.5);
//	TH1F *hist1 = new TH1F("hist1", "hist1",  100, -5, 5);
//  	TH1F *hist2 = new TH1F("hist2", "hist2",  100, -5, 5);

	std::vector<float> *probHcc = 0;
	std::vector<float> *AK8_eta = 0;
	std::vector<float> *AK8_pt = 0;
	std::vector<float> *AK8_phi = 0;
	std::vector<float> *GEN_eta = 0;
	std::vector<float> *GEN_phi = 0;
	std::vector<float> *quark_eta = 0;
        std::vector<float> *quark_phi = 0;
	std::vector<int> *quark_flavour = 0;
	std::vector<bool> *quark_VBF = 0;
	

	TBranch *b_probHcc = 0;
	TBranch *b_AK8_eta = 0;
	TBranch *b_AK8_pt = 0;
	TBranch *b_AK8_phi = 0;
	TBranch *b_GEN_eta = 0;
        TBranch *b_GEN_phi = 0;
	TBranch *b_quark_eta = 0;
        TBranch *b_quark_phi = 0;
	TBranch *b_quark_flavour = 0;
        TBranch *b_quark_VBF = 0;

   	T->SetBranchAddress("jet_pfParticleNetJetTags_probHcc",&probHcc,&b_probHcc);	
		T->SetBranchAddress("AK8PuppiJets_eta",&AK8_eta, &b_AK8_eta);
	T->SetBranchAddress("AK8PuppiJets_pt",&AK8_pt, &b_AK8_pt);
	T->SetBranchAddress("AK8PuppiJets_phi",&AK8_phi, &b_AK8_phi);
//	T->SetBranchAddress("AK4PuppiJets_eta",&AK8_eta, &b_AK8_eta);
//	T->SetBranchAddress("AK4PuppiJets_pt",&AK8_pt, &b_AK8_pt);
//	T->SetBranchAddress("AK4PuppiJets_phi",&AK8_phi, &b_AK8_phi);
	T->SetBranchAddress("GENjet_eta",&GEN_eta, &b_GEN_eta);
        T->SetBranchAddress("GENjet_phi",&GEN_phi, &b_GEN_phi);		
	T->SetBranchAddress("quark_eta",&quark_eta, &b_quark_eta);
        T->SetBranchAddress("quark_phi",&quark_phi, &b_quark_phi);
	T->SetBranchAddress("quark_flavour",&quark_flavour, &b_quark_flavour);
        T->SetBranchAddress("quark_VBF",&quark_VBF, &b_quark_VBF);



	Int_t nentries = (Int_t)T->GetEntries();
	cout<<nentries<<"\n";	
	//loop sugli eventi
	for (Int_t i=0;i<nentries;i++) {

	Long64_t tentry = T->LoadTree(i);
      	b_probHcc->GetEntry(tentry);
	b_AK8_eta->GetEntry(tentry);
	b_AK8_pt->GetEntry(tentry);
	b_AK8_phi->GetEntry(tentry);
	b_GEN_eta->GetEntry(tentry);
        b_GEN_phi->GetEntry(tentry);
	b_quark_eta->GetEntry(tentry);
        b_quark_phi->GetEntry(tentry);
	b_quark_flavour->GetEntry(tentry);
        b_quark_VBF->GetEntry(tentry);





	 //loop sugli AK8 in un evento
	for (UInt_t j = 0; j < AK8_pt->size(); ++j) {

	  
	 graph->SetPoint(i, AK8_pt->at(j), probHcc->at(j));
}//fine loop jet AK8

}//fine loop eventi
	  // Draw the scatter plot on a canvas
  TCanvas *canvas = new TCanvas("Canvas", "Scatter Plot", 800, 600);
  graph->Draw("AP");
  graph->GetXaxis()->SetTitle("p_{T} [GeV]");
  graph->GetYaxis()->SetTitle("probHcc");
  canvas->Update();
  
  // Save the canvas as an image
  canvas->SaveAs("scatterplot.png");
	}
