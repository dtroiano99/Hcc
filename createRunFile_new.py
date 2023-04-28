import sys
import os
import csv
import string
import datetime

# Define the parser
import argparse
parser = argparse.ArgumentParser(description="Options to give to the script")
# Positional arguments
parser.add_argument("dataset", type=str, choices=['data', 'data_control', 'MC'], help="Specify if data or Monte Carlo")
parser.add_argument("anatype", type=str, choices=['Hcc', 'control'], help="Specify analysis type")
#parser.add_argument("--run", type=str, default='', choices=['2022B', '2022C_0', '2022C_1', '2022C_2', '2022C_3', '2022C_4', '2022C_5', '2022C_6', '2022C_7', '2022D-v1_0', '2022D-v1_1', '2022D-v1_2', '2022D-v1_3', '2022D-v1_4', '2022D-v1_5', '2022D-v1_6', '2022D-v1_7', '2022D-v2_0', '2022D-v2_1', '2022D-v2_2', '2022D-v2_3', '2022D-v2_4', '2022D-v2_5', '2022D-v2_6', '2022D-v2_7', '2022E_0', '2022E_1', '2022E_2', '2022E_3', '2022E_4', '2022E_5', '2022E_6', '2022E_7', '2022F_0', '2022F_1', '2022F_2', '2022F_3', '2022F_4', '2022F_5', '2022F_6', '2022F_7', '2022G_0', '2022G_1', '2022G_2', '2022G_3', '2022G_4', '2022G_5', '2022G_6', '2022G_7'], help="run in data")
parser.add_argument("--run", type=str, default='', choices=['2022B', '2022C', '2022D', '2022D', '2022E', '2022F', '2022G'], help="run in data")
# Optional Arguments
parser.add_argument("--outName", type=str, default="test", help="Specify name for output files")
parser.add_argument("--n", type=int, default=255, help="number of .root files per job")
parser.add_argument("--EE",type=str, default='preEE', choices=['preEE','postEE'], help="specify if it is simulated with preEE or postEE conditions")
parser.add_argument("--MCprocess", type=str, default='', choices=['Zqq_HT-200-400', 'Zqq_HT-400-600', 'Zqq_HT-600-800', 'Zqq_HT-800-inf', 'QCD_PT-120-170', 'QCD_PT-170-300', 'QCD_PT-300-470', 'QCD_PT-470-600', 'QCD_PT-600-800', 'QCD_PT-800-1000', 'QCD_PT-1000-1400', 'QCD_PT-1400-1800', 'QCD_PT-1800-2400', 'QCD_PT-2400-3200'], help="process in Monte Carlo")
args = parser.parse_args()

#prepare output filename  and option string
if args.dataset == 'data':
   out_filename = 'AnalysedTree_'+args.dataset+'_'+args.run+'_'+args.anatype
   temp = '_'+args.anatype
   option_string = ' "'+args.dataset+temp.replace("_Hcc","")+'" "'+args.run+'"'
elif args.dataset == 'data_control':
   out_filename = 'AnalysedTree_'+args.dataset+'_'+args.run+'_'+args.anatype
   temp = '_'+args.anatype
   option_string = ' "'+args.dataset+temp.replace("_control","")+'" "'+args.run+'"'
elif args.dataset == 'MC':
   out_filename = 'AnalysedTree_'+args.dataset+'_'+args.MCprocess+'_'+args.anatype
   temp = '_'+args.anatype
   option_string = ' "'+args.dataset+temp.replace("_Hcc","")+'" "'+args.MCprocess+'"'

#startTime = datetime.datetime.now().strftime("%Y%m%d_%H%M")

# Create target Directory if don't exist
if args.dataset == 'MC':
   output_name = args.MCprocess+"_"+args.anatype+"_"+args.outName
   #output_name = args.MCprocess+"_"+args.anatype+"_"+args.EE+"_"+args.outName
else: 
   output_name = args.run+"_"+args.anatype+"_"+args.outName

if not os.path.exists(output_name):
    os.mkdir(output_name)
    print('Directory '+output_name+' created\n')
else:    
    print('Directory '+output_name+' already exists\n')

if args.anatype == 'Hcc':
   #### 2022
   if args.dataset == 'data' and args.run == '2022B':
      path = '' 
   if args.dataset == 'data' and args.run == '2022C':
      path = '/lustre/cms/store/user/dtroiano/JetMET/Run2022C_ntuple/230405_142008' 
   if args.dataset == 'data' and args.run == '2022D':
      path = '/lustre/cms/store/user/dtroiano/JetMET/Run2022D_ntuple/230405_143608'
   if args.dataset == 'data' and args.run == '2022E':
      path = '/lustre/cms/store/user/dtroiano/JetMET/Run2022E_ntuple/230405_144208'
   if args.dataset == 'data' and args.run == '2022F':
      path = '/lustre/cms/store/user/azaza/JetMET/DataRun3_EraF_ntuple/230405_155207'
   if args.dataset == 'data' and args.run == '2022G':
      path = '/lustre/cms/store/user/azaza/JetMET/DataRun3_EraG_ntuple/230405_155244'

if args.anatype == 'control':
   #if args.dataset == 'data_control' and args.run == '2022B':
   if args.dataset == 'data_control':
      path = ''

if args.EE == 'preEE':
   if args.dataset == 'MC' and args.MCprocess == 'QCD_PT-120-170':
      path = '/lustre/cms/store/user/azaza/QCD_PT-120to170_TuneCP5_13p6TeV_pythia8/crab_QCD_PT-120to170_TuneCP5_13p6TeV_pythia8_Run3Summer22MiniAODv3-124X_mcRun3_2022_realistic_v12-v2/230405_161508'
      #path = '/lustre/cms/store/user/azaza/QCD_PT-120to170_PROVA'
   if args.dataset == 'MC' and args.MCprocess == 'QCD_PT-170-300':
      path = '/lustre/cms/store/user/azaza/QCD_PT-170to300_EMEnriched_TuneCP5_13p6TeV_pythia8/crab_QCD_PT-170to300_EMEnriched_TuneCP5_13p6TeV_pythia8_Run3Summer22MiniAODv3/230405_184147'
   if args.dataset == 'MC' and args.MCprocess == 'QCD_PT-300-470':
      path = '/lustre/cms/store/user/azaza/QCD_PT-300to470_TuneCP5_13p6TeV_pythia8/crab_QCD_PT-300to470_TuneCP5_13p6TeV_pythia8_Run3Summer22MiniAODv3-124X_mcRun3_2022_realistic_v12-v2/230405_184210'
   if args.dataset == 'MC' and args.MCprocess == 'QCD_PT-470-600':
      path = '/lustre/cms/store/user/azaza/QCD_PT-470to600_TuneCP5_13p6TeV_pythia8/crab_QCD_PT-470to600_TuneCP5_13p6TeV_pythia8_Run3Summer22MiniAODv3-124X_mcRun3_2022_realistic_v12-v2/230405_184232'
   if args.dataset == 'MC' and args.MCprocess == 'QCD_PT-600-800':
      path = '/lustre/cms/store/user/azaza/QCD_PT-600to800_TuneCP5_13p6TeV_pythia8/crab_QCD_PT-600to800_TuneCP5_13p6TeV_pythia8_Run3Summer22MiniAODv3-124X_mcRun3_2022_realistic_v12-v2/230405_184254'
   if args.dataset == 'MC' and args.MCprocess == 'QCD_PT-800-1000':
      path = '/lustre/cms/store/user/azaza/QCD_PT-800to1000_TuneCP5_13p6TeV_pythia8/crab_QCD_PT-800to1000_TuneCP5_13p6TeV_pythia8_Run3Summer22MiniAODv3-124X_mcRun3_2022_realistic_v12-v2/230405_184317'
   if args.dataset == 'MC' and args.MCprocess == 'QCD_PT-1000-1400':
      path = ''
   if args.dataset == 'MC' and args.MCprocess == 'QCD_PT-1400-1800':
      path = '/lustre/cms/store/user/azaza/QCD_PT-1400to1800_TuneCP5_13p6TeV_pythia8/crab_QCD_PT-1400to1800_TuneCP5_13p6TeV_pythia8_Run3Summer22MiniAODv3-124X_mcRun3_2022_realistic_v12-v2/230405_184339'
   if args.dataset == 'MC' and args.MCprocess == 'QCD_PT-1800-2400':
      path = '/lustre/cms/store/user/azaza/QCD_PT-1800to2400_TuneCP5_13p6TeV_pythia8/crab_QCD_PT-1800to2400_TuneCP5_13p6TeV_pythia8_Run3Summer22MiniAODv3-124X_mcRun3_2022_realistic_v12-v2/230405_184401'
   if args.dataset == 'MC' and args.MCprocess == 'QCD_PT-2400-3200':
      path = '/lustre/cms/store/user/azaza/QCD_PT-2400to3200_TuneCP5_13p6TeV_pythia8/crab_QCD_PT-2400to3200_TuneCP5_13p6TeV_pythia8_Run3Summer22MiniAODv3-124X_mcRun3_2022_realistic_v12-v2/230405_184423'

   # ZToJets
   if args.dataset == 'MC' and args.MCprocess == 'Zqq_HT-200-400':
      path = '/lustre/cms/store/user/dtroiano/ZJetsToQQ_HT200to400_TuneCP5_13TeV-madgraphMLM-pythia8/Zqq_HT200to400_ntuple/230405_132349'
   if args.dataset == 'MC' and args.MCprocess == 'Zqq_HT-400-600':
      path = '/lustre/cms/store/user/dtroiano/ZJetsToQQ_HT400to600_TuneCP5_13TeV-madgraphMLM-pythia8/Zqq_HT400to600_ntuple/230405_133832'   
   if args.dataset == 'MC' and args.MCprocess == 'Zqq_HT-600-800':
      path = '/lustre/cms/store/user/dtroiano/ZJetsToQQ_HT600to800_TuneCP5_13TeV-madgraphMLM-pythia8/Zqq_HT600to800_ntuple/230405_134357'
   if args.dataset == 'MC' and args.MCprocess == 'Zqq_HT-800-inf':
      path = '/lustre/cms/store/user/dtroiano/ZJetsToQQ_HT800toInf_TuneCP5_13TeV-madgraphMLM-pythia8/Zqq_HT800toInf_ntuple/230405_121440'



if args.EE == 'postEE':
   if args.dataset == 'MC' and args.MCprocess == 'QCD_PT-120-170':
      path = '/lustre/cms/store/user/azaza/QCD_PT-120to170_TuneCP5_13p6TeV_pythia8/crab_QCD_PT-120to170_TuneCP5_13p6TeV_pythia8_Run3Summer22EEMiniAODv3/230405_183617'
   if args.dataset == 'MC' and args.MCprocess == 'QCD_PT-170-300':
      path = '/lustre/cms/store/user/azaza/QCD_PT-170to300_TuneCP5_13p6TeV_pythia8/crab_QCD_PT-170to300_TuneCP5_13p6TeV_pythia8_Run3Summer22EEMiniAODv3/230405_183640'
   if args.dataset == 'MC' and args.MCprocess == 'QCD_PT-300-470':
      path = '/lustre/cms/store/user/azaza/QCD_PT-300to470_TuneCP5_13p6TeV_pythia8/crab_QCD_PT-300to470_TuneCP5_13p6TeV_pythia8_Run3Summer22EEMiniAODv3/230405_183703'
   if args.dataset == 'MC' and args.MCprocess == 'QCD_PT-470-600':
      path = '/lustre/cms/store/user/azaza/QCD_PT-470to600_TuneCP5_13p6TeV_pythia8/crab_QCD_PT-470to600_TuneCP5_13p6TeV_pythia8_Run3Summer22EEMiniAODv3/230405_183725'
   if args.dataset == 'MC' and args.MCprocess == 'QCD_PT-600-800':
      path = '/lustre/cms/store/user/azaza/QCD_PT-600to800_TuneCP5_13p6TeV_pythia8/crab_QCD_PT-600to800_TuneCP5_13p6TeV_pythia8_Run3Summer22EEMiniAODv3/230405_183748'
   if args.dataset == 'MC' and args.MCprocess == 'QCD_PT-800-1000':
      path = '/lustre/cms/store/user/azaza/QCD_PT-800to1000_TuneCP5_13p6TeV_pythia8/crab_QCD_PT-800to1000_TuneCP5_13p6TeV_pythia8_Run3Summer22EEMiniAODv3/230405_183810'
   if args.dataset == 'MC' and args.MCprocess == 'QCD_PT-1000-1400':
      path = '/lustre/cms/store/user/azaza/QCD_PT-1000to1400_TuneCP5_13p6TeV_pythia8/crab_QCD_PT-1000to1400_TuneCP5_13p6TeV_pythia8_Run3Summer22EEMiniAODv3/230405_183833'
   if args.dataset == 'MC' and args.MCprocess == 'QCD_PT-1400-1800':
      path = '/lustre/cms/store/user/azaza/QCD_PT-1400to1800_TuneCP5_13p6TeV_pythia8/crab_QCD_PT-1400to1800_TuneCP5_13p6TeV_pythia8_Run3Summer22EEMiniAODv3/230405_183855'
   if args.dataset == 'MC' and args.MCprocess == 'QCD_PT-1800-2400':
      path = '/lustre/cms/store/user/azaza/QCD_PT-1800to2400_TuneCP5_13p6TeV_pythia8/crab_QCD_PT-1800to2400_TuneCP5_13p6TeV_pythia8_Run3Summer22EEMiniAODv3/230405_183917'
   if args.dataset == 'MC' and args.MCprocess == 'QCD_PT-2400-3200':
      path = '/lustre/cms/store/user/azaza/QCD_PT-2400to3200_TuneCP5_13p6TeV_pythia8/crab_QCD_PT-2400to3200_TuneCP5_13p6TeV_pythia8_Run3Summer22EEMiniAODv3/230405_183940'

#generating the list of all .root files in given directory and subdirectories
fileList = []
for r, d, f in os.walk(path): # r=root, d=directories, f = files
    for file in f:
        if '.root' in file:
            fileList.append(os.path.join(r, file))
            print file

#prepare final script
#final_script = open("submit_analysis_"+startTime+".sh", "w")
final_script = open("submit_analysis_"+output_name+".sh", "w")
final_script.write("#!/bin/bash\n")
final_script.write("chmod 777 -R *\n")
final_script.write("cd "+output_name+"\n")

#loop to generate one .cpp+executable+batch system conf file for each group of "n" files
n_chunk = len(fileList)//args.n
print('Number of files is {0:2d}'.format(len(fileList)))
print('Number of jobs is {0:2d}'.format(n_chunk+1))
for file_index in range(n_chunk+1):
      chunk = '' 
      for idx, l in enumerate(fileList):
         if idx < args.n*(file_index+1) and idx >= args.n*file_index:
             l = l.rstrip()
             l = '        chain->AddFile("{}");\n'.format(l)
             chunk = chunk + l

      #analysis.cpp template
      with open("templates/Analysis_template.cpp", "r") as in_file:
          buf = in_file.readlines()

      cpp_filename = "Analysis_"+args.dataset+"_"+args.run+args.MCprocess+"_"+args.anatype+"_chunk"+str(file_index)+".cpp"
      with open(cpp_filename, "w") as out_file:
          for lb in buf:
              if lb == '        //AddFile_'+args.dataset+'\n':
                  #write group of files
                  out_file.write(chunk)
              elif lb == '        //OutFile_'+args.dataset+'\n':
                  #write output file name
                  out_file.write('        fileout = "'+out_filename+str(file_index)+'.root";\n')
              else: out_file.write(lb)

              #elif lb == '            TString fileout = "AddOutput_'+args.dataset+args.MCprocess+'_'+args.anatype+'.root";\n':
                  #write output file name
               #   out_file.write('        TString fileout = "'+out_filename+str(file_index)+'.root";\n')
              #else: out_file.write(lb)

      #executable template
      with open("templates/launch_analysis_template.job", "r") as launch_infile:
          buf2 = launch_infile.readlines()

      launch_filename = "launch_analysis_"+args.dataset+"_"+args.run+args.MCprocess+"_"+args.anatype+"_"+str(file_index)+".job"
      with open(output_name+"/"+launch_filename, "w") as launch_outfile:
          for lb2 in buf2:
              if lb2 == "#compile\n":
                  launch_outfile.write("cd "+output_name+"\n")
                  launch_outfile.write("g++ -I $ROOTSYS/include ../"+cpp_filename+" `root-config --glibs` `root-config --libs` `root-config --cflags` -lTMVA -L $ROOTSYS/lib -o executable"+str(file_index)+"\n")
              elif lb2 == "#execute\n":
                  launch_outfile.write('./executable'+str(file_index)+option_string+'\n')
              else: launch_outfile.write(lb2)

      #myCondor template
      with open("templates/my_HTCondor_template.job", "r") as myCondor_infile:
          buf3 = myCondor_infile.readlines()

      condor_filename = "my_HTCondor_"+args.dataset+"_"+args.run+args.MCprocess+"_"+args.anatype+"_"+str(file_index)+".job"
      with open(output_name+"/"+condor_filename, "w") as myCondor_outfile:
          for lb3 in buf3:
              if lb3 == "Executable = launch_analysis_template.job\n":
                  myCondor_outfile.write("Executable = "+launch_filename+"\n")
              else: myCondor_outfile.write(lb3)

      #add lines to final script
      final_script.write("echo condor_submit "+condor_filename+" -name ettore\n")
      final_script.write("condor_submit "+condor_filename+" -name ettore\n")

final_script.close()
#submitName = "submit_analysis_"+startTime+".sh"
#source submitName
