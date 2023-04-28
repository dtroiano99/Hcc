#!/bin/bash
# Usage:
#  submitAllJobs.sh


echo -e "\npython createRunFile_new.py data Hcc --run 2022C --n 30 --outName v1 "
python createRunFile_new.py data Hcc --run 2022C --n 30 --outName v1
sleep 1
pwd
echo -e "\nsubmit_analysis_2022C_Hcc_v1.sh"
source submit_analysis_2022C_Hcc_v1.sh
cd ..
sleep 1


echo -e "\npython createRunFile_new.py data Hcc --run 2022D --n 30 --outName v1 "
python createRunFile_new.py data Hcc --run 2022D --n 30 --outName v1
sleep 1
echo -e "\nsubmit_analysis_2022D_Hcc_v1.sh"
source submit_analysis_2022D_Hcc_v1.sh
cd ..
sleep 1



for i in QCD_PT-120-170 QCD_PT-170-300 QCD_PT-300-470 QCD_PT-470-600 QCD_PT-600-800 QCD_PT-800-1000 QCD_PT-1400-1800 QCD_PT-1800-2400 QCD_PT-2400-3200
do
 		echo -e "\nMC $i"
    echo -e "\npython createRunFile_new.py MC Hcc --outName v1 --n 30 --EE preEE --MCprocess $i "
    python createRunFile_new.py MC Hcc --outName v1 --n 30 --EE preEE --MCprocess $i
    sleep 1
    echo -e "\nsubmit_analysis_${i}_Hcc_v1.sh"
    source submit_analysis_${i}_Hcc_v1.sh
    cd ..
    sleep 1
done


for j in Zqq_HT-200-400 Zqq_HT-400-600 Zqq_HT-600-800 Zqq_HT-800-inf
do
    echo -e "\nMC $j"
    echo -e "\npython createRunFile_new.py MC Hcc --outName v1 --n 30 --EE preEE --MCprocess $j "
    python createRunFile_new.py MC Hcc --outName v1 --n 50 --EE preEE --MCprocess $j
    sleep 1
    echo -e "\nsubmit_analysis_${j}_Hcc_v1.sh"
    source submit_analysis_${j}_Hcc_v1.sh
    cd ..
    sleep 1
done

