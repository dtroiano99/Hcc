#include "myAnalizer.C"
//#include "myAnalizer_control.C"
#include <TROOT.h>
#include <stdio.h>
#include <iostream>
#include <string.h>

using namespace std;

int main(int narg, char** arg){
    TTree *tree;
    char type[20];
    strcpy(type, arg[1]);
    cout << "type : " << type << endl;
    char datasetName[20];
    strcpy(datasetName, arg[2]);
    cout << "datasetName : " << datasetName << endl << endl;
    TString fileout = "";

    // Check input arguments
    if(strcmp(type, "MC") != 0 && strcmp(type, "data") != 0 && strcmp(type, "data_control") != 0 ){
        cout << "The first argument is wrong! Please choose among 'MC', 'data', 'data_control'" << endl;
        //return -1;
    }
    if( strcmp(type, "MC") == 0 && (strcmp(datasetName, "QCD_PT-120-170") != 0 && strcmp(datasetName, "QCD_PT-170-300") != 0 && strcmp(datasetName, "QCD_PT-300-470") != 0 && strcmp(datasetName, "QCD_PT-470-600") != 0 && strcmp(datasetName, "QCD_PT-600-800") != 0 && strcmp(datasetName, "QCD_PT-800-1000") != 0 &&  strcmp(datasetName, "QCD_PT-1000-1400") != 0 && strcmp(datasetName, "QCD_PT-1400-1800") != 0 && strcmp(datasetName, "QCD_PT-1800-2400") !=0  && strcmp(datasetName, "QCD_PT-2400-3200") != 0 &&  strcmp(datasetName, "Zqq_HT-200-400") != 0 && strcmp(datasetName, "Zqq_HT-400-600") != 0 && strcmp(datasetName, "Zqq_HT-600-800") != 0 && strcmp(datasetName, "Zqq_HT-800-inf") != 0  ) ){
    //if( strcmp(type, "MC") == 0 && (strcmp(datasetName, "QCD_PT-120-170") != 0 && strcmp(datasetName, "QCD_PT-170-300") != 0 && strcmp(datasetName, "QCD_PT-300-470") != 0 && strcmp(datasetName, "QCD_PT-470-600") != 0 && strcmp(datasetName, "QCD_PT-600-800") != 0 && strcmp(datasetName, "QCD_PT-800-1000") != 0 &&  strcmp(datasetName, "QCD_PT-1000-1400") != 0 && strcmp(datasetName, "QCD_PT-1800-2400") !=0  && strcmp(datasetName, "QCD_PT-2400-3200") != 0  ) ){
        cout << "The second argument is wrong!" << endl;
        return -1;
    }

    // ################ MC
    if ( strcmp(type, "MC") == 0 ){
        cout << "This is a MC" << endl;
        
        // ###SIGNAL samples
        // Ds -> Tau -> 3Mu
        
        TChain* chain = new TChain("Ana/passedEvents");
        //AddFile_MC
        //OutFile_MC
        myAnalizer class_data(chain, fileout);
        class_data.Loop_Hcc(type, datasetName);
        }
        /*// Bd -> Tau -> 3Mu
        if (strcmp(datasetName, "B0") == 0){
            cout << "MC Dataset : B0 -> Tau -> 3Mu" << endl << endl;
            TChain* chain = new TChain("TreeMakerBkg/ntuple");
        //AddFile_MCB0_tau3mu
        //OutFile_MCB0_tau3mu
        myAnalizer class_data(chain, fileout);
        class_data.Loop_Tau3mu(type, datasetName);
        }
        // Bu -> Tau -> 3Mu
        if (strcmp(datasetName, "Bp") == 0){
            cout << "MC Dataset : Bp -> Tau -> 3Mu" << endl << endl;
            TChain* chain = new TChain("TreeMakerBkg/ntuple");
        //AddFile_MCBp_tau3mu
        //OutFile_MCBp_tau3mu
        myAnalizer class_data(chain, fileout);
        class_data.Loop_Tau3mu(type, datasetName);
        }
        
        // ###Other samples
        // Ds -> PhiPi -> MuMuPi
         if (strcmp(datasetName, "DsPhiPi") == 0){
            cout << "MC Dataset : Ds -> PhiPi -> MuMuPi" << endl << endl;
            TChain* chain = new TChain("Tree3Mu/ntuple");
        //AddFile_MCDsPhiPi_tau3mu
        //OutFile_MCDsPhiPi_tau3mu
            myAnalizer_control class_data(chain, fileout);
            class_data.Loop_DsPhiPi(type, datasetName);
         }
        // Ds -> PhiMuNu -> 3MuNu
         if (strcmp(datasetName, "DsPhiMuNu") == 0){
         cout << "MC Dataset : Ds -> PhiMuNu -> 3MuNu" << endl << endl;
         TChain* chain = new TChain("TreeMakerBkg/ntuple");
        //AddFile_MCDsPhiMuNu_tau3mu
        //OutFile_MCDsPhiMuNu_tau3mu
        myAnalizer class_data(chain, fileout);
        class_data.Loop_Tau3mu(type, datasetName);
	}
   }*/

   //Data - tau3mu
   if(strcmp(type, "data") == 0){
	cout << "this is data" << endl;
        cout << "Data " << datasetName << endl << endl;
        TChain* chain = new TChain("Ana/passedEvents");
        //AddFile_data
        //OutFile_data
        myAnalizer class_data(chain, fileout);
        class_data.Loop_Hcc(type, datasetName);
    }
    
    /*if (strcmp(type, "data_control") == 0){
        cout << "Control channel analysis on data" << endl;
        cout << "Data " << datasetName << endl << endl;
        TChain* chain = new TChain("Tree3Mu/ntuple");
        //AddFile_data_control_control
        //OutFile_data_control_control
        myAnalizer_control class_data(chain, fileout);
        class_data.Loop_DsPhiPi(type, datasetName); 
    }*/

    return 0;
}
