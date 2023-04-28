#!/bin/bash
# Usage:
#  submitAllJobs.sh



cd 2022C_Hcc_v1
echo -e "hadd AnalysedTree_data_2022C_Hcc_merged.root AnalysedTree_data_2022C_Hcc*.root"
hadd AnalysedTree_data_2022C_Hcc_merged.root AnalysedTree_data_2022C_Hcc*.root
cd ..
sleep 1

cd 2022D_Hcc_v1
echo -e "hadd AnalysedTree_data_2022D_Hcc_merged.root AnalysedTree_data_2022D_Hcc*.root"
hadd AnalysedTree_data_2022D_Hcc_merged.root AnalysedTree_data_2022D_Hcc*.root
cd ..
sleep 1




for i in QCD_PT-120-170 QCD_PT-170-300 QCD_PT-300-470 QCD_PT-470-600 QCD_PT-600-800 QCD_PT-800-1000 QCD_PT-1400-1800 QCD_PT-1800-2400 QCD_PT-2400-3200
do
		cd ${i}_Hcc_v1
		echo -e "hadd AnalysedTree_MC_${i}_Hcc_merged.root AnalysedTree_MC_${i}_Hcc*.root"
		hadd AnalysedTree_MC_${i}_Hcc_merged.root AnalysedTree_MC_${i}_Hcc*.root
		cd ..
		sleep 1
done


for j in Zqq_HT-200-400 Zqq_HT-400-600 Zqq_HT-600-800 Zqq_HT-800-inf
do 
		cd ${j}_Hcc_v1
		echo -e "hadd AnalysedTree_MC_${j}_Hcc_merged.root AnalysedTree_MC_${j}_Hcc*.root"
		hadd AnalysedTree_MC_${j}_Hcc_merged.root AnalysedTree_MC_${j}_Hcc*.root
		cd ..
		sleep 1

done

