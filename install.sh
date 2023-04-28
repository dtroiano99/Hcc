SCRAM_ARCH=slc7_amd64_gcc900; export SCRAM_ARCH
cmsrel CMSSW_12_4_3
cd CMSSW_12_4_3/src/
cmsenv
git cms-init
git clone -b 12_4_3 git@github.com:BariGEMJetTau/Hcc.git

#### not needed ####
git cms-addpkg GeneratorInterface/RivetInterface
git cms-addpkg SimDataFormats/HTXS
git cms-addpkg RecoEgamma/EgammaTools
git cms-addpkg RecoEgamma/PhotonIdentification
git cms-addpkg EgammaAnalysis/ElectronTools
git cms-addpkg RecoJets/JetProducers
git cms-addpkg PhysicsTools/PatAlgos/
#### not needed ####

scramv1 b -j 8





#### OLD: USELESS ####
SCRAM_ARCH=slc7_amd64_gcc700; export SCRAM_ARCH
cmsrel CMSSW_10_6_26
cd CMSSW_10_6_26/src/
cmsenv
git cms-init
git clone git@github.com:ferrico/Hcc_v2.git
                                                        git clone git@github.com:angzaza/hcc_v2.git
git cms-merge-topic bonanomi:ElectronsMVA_UL
#git cms-merge-topic asculac:Electron_XGBoost_MVA_16UL_17UL
git cms-addpkg GeneratorInterface/RivetInterface
git cms-addpkg SimDataFormats/HTXS
git cms-addpkg RecoEgamma/EgammaTools
git clone https://github.com/cms-egamma/EgammaPostRecoTools.git
mv EgammaPostRecoTools/python/EgammaPostRecoTools.py RecoEgamma/EgammaTools/python/
git cms-addpkg RecoEgamma/PhotonIdentification
#git cms-addpkg RecoEgamma/ElectronIdentification
#git cms-merge-topic cms-egamma:EgammaPostRecoTools
git clone -b ULSSfiles_correctScaleSysMC https://github.com/jainshilpi/EgammaAnalysis-ElectronTools.git EgammaAnalysis/ElectronTools/data/
git cms-addpkg EgammaAnalysis/ElectronTools
git cms-addpkg RecoJets/JetProducers
git cms-addpkg PhysicsTools/PatAlgos/
git clone -b UL20_10_6_26  https://github.com/ferrico/KinZfitter.git
scramv1 b -j 8

