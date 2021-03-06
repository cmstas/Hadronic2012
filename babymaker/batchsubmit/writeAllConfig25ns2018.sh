#!/bin/bash

#
# All MT2 related datasets available on hadoop
#

# TAG="V00-10-03_2018_HEmiss_MC"
# TAG="V00-10-03_2018_HEmiss_data_relval"
TAG="V00-10-06_2018fullYear_17Sep2018"

#
# DATA
#

# ./writeConfig.sh /hadoop/cms/store/group/snt/run2_data2018_prompt/JetHT_Run2018A-PromptReco-v1_MINIAOD_CMS4_V10-01-00 ${TAG}_data_Run2018A_JetHT_PromptReco-v1
# ./writeConfig.sh /hadoop/cms/store/group/snt/run2_data2018_prompt/MET_Run2018A-PromptReco-v1_MINIAOD_CMS4_V10-01-00 ${TAG}_data_Run2018A_MET_PromptReco-v1
# ./writeConfig.sh /hadoop/cms/store/group/snt/run2_data2018_prompt/DoubleMuon_Run2018A-PromptReco-v1_MINIAOD_CMS4_V10-01-00 ${TAG}_data_Run2018A_DoubleMuon_PromptReco-v1
# ./writeConfig.sh /hadoop/cms/store/group/snt/run2_data2018_prompt/EGamma_Run2018A-PromptReco-v1_MINIAOD_CMS4_V10-01-00 ${TAG}_data_Run2018A_EGamma_PromptReco-v1
# ./writeConfig.sh /hadoop/cms/store/group/snt/run2_data2018_prompt/MuonEG_Run2018A-PromptReco-v1_MINIAOD_CMS4_V10-01-00 ${TAG}_data_Run2018A_MuonEG_PromptReco-v1
# ./writeConfig.sh /hadoop/cms/store/group/snt/run2_data2018_prompt/SingleMuon_Run2018A-PromptReco-v1_MINIAOD_CMS4_V10-01-00 ${TAG}_data_Run2018A_SingleMuon_PromptReco-v1

# ./writeConfig.sh /hadoop/cms/store/group/snt/run2_data2018_prompt/JetHT_Run2018A-PromptReco-v2_MINIAOD_CMS4_V10-01-00 ${TAG}_data_Run2018A_JetHT_PromptReco-v2
# ./writeConfig.sh /hadoop/cms/store/group/snt/run2_data2018_prompt/MET_Run2018A-PromptReco-v2_MINIAOD_CMS4_V10-01-00 ${TAG}_data_Run2018A_MET_PromptReco-v2
# ./writeConfig.sh /hadoop/cms/store/group/snt/run2_data2018_prompt/DoubleMuon_Run2018A-PromptReco-v2_MINIAOD_CMS4_V10-01-00 ${TAG}_data_Run2018A_DoubleMuon_PromptReco-v2
# ./writeConfig.sh /hadoop/cms/store/group/snt/run2_data2018_prompt/EGamma_Run2018A-PromptReco-v2_MINIAOD_CMS4_V10-01-00 ${TAG}_data_Run2018A_EGamma_PromptReco-v2
# ./writeConfig.sh /hadoop/cms/store/group/snt/run2_data2018_prompt/MuonEG_Run2018A-PromptReco-v2_MINIAOD_CMS4_V10-01-00 ${TAG}_data_Run2018A_MuonEG_PromptReco-v2
# ./writeConfig.sh /hadoop/cms/store/group/snt/run2_data2018_prompt/SingleMuon_Run2018A-PromptReco-v2_MINIAOD_CMS4_V10-01-00 ${TAG}_data_Run2018A_SingleMuon_PromptReco-v2

# ./writeConfig.sh /hadoop/cms/store/group/snt/run2_data2018_prompt/JetHT_Run2018A-PromptReco-v3_MINIAOD_CMS4_V10-01-00 ${TAG}_data_Run2018A_JetHT_PromptReco-v3
# ./writeConfig.sh /hadoop/cms/store/group/snt/run2_data2018_prompt/MET_Run2018A-PromptReco-v3_MINIAOD_CMS4_V10-01-00 ${TAG}_data_Run2018A_MET_PromptReco-v3
# ./writeConfig.sh /hadoop/cms/store/group/snt/run2_data2018_prompt/DoubleMuon_Run2018A-PromptReco-v3_MINIAOD_CMS4_V10-01-00 ${TAG}_data_Run2018A_DoubleMuon_PromptReco-v3
# ./writeConfig.sh /hadoop/cms/store/group/snt/run2_data2018_prompt/EGamma_Run2018A-PromptReco-v3_MINIAOD_CMS4_V10-01-00 ${TAG}_data_Run2018A_EGamma_PromptReco-v3
# ./writeConfig.sh /hadoop/cms/store/group/snt/run2_data2018_prompt/MuonEG_Run2018A-PromptReco-v3_MINIAOD_CMS4_V10-01-00 ${TAG}_data_Run2018A_MuonEG_PromptReco-v3
# ./writeConfig.sh /hadoop/cms/store/group/snt/run2_data2018_prompt/SingleMuon_Run2018A-PromptReco-v3_MINIAOD_CMS4_V10-01-00 ${TAG}_data_Run2018A_SingleMuon_PromptReco-v3

# ./writeConfig.sh /hadoop/cms/store/group/snt/run2_data2018_prompt/JetHT_Run2018B-PromptReco-v1_MINIAOD_CMS4_V10-01-00 ${TAG}_data_Run2018B_JetHT_PromptReco-v1
# ./writeConfig.sh /hadoop/cms/store/group/snt/run2_data2018_prompt/MET_Run2018B-PromptReco-v1_MINIAOD_CMS4_V10-01-00 ${TAG}_data_Run2018B_MET_PromptReco-v1
# ./writeConfig.sh /hadoop/cms/store/group/snt/run2_data2018_prompt/DoubleMuon_Run2018B-PromptReco-v1_MINIAOD_CMS4_V10-01-00 ${TAG}_data_Run2018B_DoubleMuon_PromptReco-v1
# ./writeConfig.sh /hadoop/cms/store/group/snt/run2_data2018_prompt/EGamma_Run2018B-PromptReco-v1_MINIAOD_CMS4_V10-01-00 ${TAG}_data_Run2018B_EGamma_PromptReco-v1
# ./writeConfig.sh /hadoop/cms/store/group/snt/run2_data2018_prompt/MuonEG_Run2018B-PromptReco-v1_MINIAOD_CMS4_V10-01-00 ${TAG}_data_Run2018B_MuonEG_PromptReco-v1
# ./writeConfig.sh /hadoop/cms/store/group/snt/run2_data2018_prompt/SingleMuon_Run2018B-PromptReco-v1_MINIAOD_CMS4_V10-01-00 ${TAG}_data_Run2018B_SingleMuon_PromptReco-v1

# ./writeConfig.sh /hadoop/cms/store/group/snt/run2_data2018_prompt/JetHT_Run2018B-PromptReco-v2_MINIAOD_CMS4_V10-01-00 ${TAG}_data_Run2018B_JetHT_PromptReco-v2
# ./writeConfig.sh /hadoop/cms/store/group/snt/run2_data2018_prompt/MET_Run2018B-PromptReco-v2_MINIAOD_CMS4_V10-01-00 ${TAG}_data_Run2018B_MET_PromptReco-v2
# ./writeConfig.sh /hadoop/cms/store/group/snt/run2_data2018_prompt/DoubleMuon_Run2018B-PromptReco-v2_MINIAOD_CMS4_V10-01-00 ${TAG}_data_Run2018B_DoubleMuon_PromptReco-v2
# ./writeConfig.sh /hadoop/cms/store/group/snt/run2_data2018_prompt/EGamma_Run2018B-PromptReco-v2_MINIAOD_CMS4_V10-01-00 ${TAG}_data_Run2018B_EGamma_PromptReco-v2
# ./writeConfig.sh /hadoop/cms/store/group/snt/run2_data2018_prompt/MuonEG_Run2018B-PromptReco-v2_MINIAOD_CMS4_V10-01-00 ${TAG}_data_Run2018B_MuonEG_PromptReco-v2
# ./writeConfig.sh /hadoop/cms/store/group/snt/run2_data2018_prompt/SingleMuon_Run2018B-PromptReco-v2_MINIAOD_CMS4_V10-01-00 ${TAG}_data_Run2018B_SingleMuon_PromptReco-v2

# ./writeConfig.sh /hadoop/cms/store/group/snt/run2_data2018_prompt/DoubleMuon_Run2018C-PromptReco-v1_MINIAOD_CMS4_V10-01-00 ${TAG}_data_Run2018C_DoubleMuon_PromptReco-v1
# ./writeConfig.sh /hadoop/cms/store/group/snt/run2_data2018_prompt/EGamma_Run2018C-PromptReco-v1_MINIAOD_CMS4_V10-01-00 ${TAG}_data_Run2018C_EGamma_PromptReco-v1
# ./writeConfig.sh /hadoop/cms/store/group/snt/run2_data2018_prompt/MuonEG_Run2018C-PromptReco-v1_MINIAOD_CMS4_V10-01-00 ${TAG}_data_Run2018C_MuonEG_PromptReco-v1
# ./writeConfig.sh /hadoop/cms/store/user/bemarsh/ProjectMetis/JetHT_Run2018C-PromptReco-v1_MINIAOD_CMS4_V10-01-00/ ${TAG}_data_Run2018C_JetHT_PromptReco-v1
# ./writeConfig.sh /hadoop/cms/store/user/bemarsh/ProjectMetis/MET_Run2018C-PromptReco-v1_MINIAOD_CMS4_V10-01-00/ ${TAG}_data_Run2018C_MET_PromptReco-v1
# ./writeConfig.sh /hadoop/cms/store/user/bemarsh/ProjectMetis/SingleMuon_Run2018C-PromptReco-v1_MINIAOD_CMS4_V10-01-00/ ${TAG}_data_Run2018C_SingleMuon_PromptReco-v1

# ./writeConfig.sh /hadoop/cms/store/group/snt/run2_data2018_prompt/DoubleMuon_Run2018C-PromptReco-v2_MINIAOD_CMS4_V10-01-00 ${TAG}_data_Run2018C_DoubleMuon_PromptReco-v2
# ./writeConfig.sh /hadoop/cms/store/group/snt/run2_data2018_prompt/EGamma_Run2018C-PromptReco-v2_MINIAOD_CMS4_V10-01-00 ${TAG}_data_Run2018C_EGamma_PromptReco-v2
# ./writeConfig.sh /hadoop/cms/store/group/snt/run2_data2018_prompt/MuonEG_Run2018C-PromptReco-v2_MINIAOD_CMS4_V10-01-00 ${TAG}_data_Run2018C_MuonEG_PromptReco-v2
# ./writeConfig.sh /hadoop/cms/store/user/bemarsh/ProjectMetis/JetHT_Run2018C-PromptReco-v2_MINIAOD_CMS4_V10-01-00/ ${TAG}_data_Run2018C_JetHT_PromptReco-v2
# ./writeConfig.sh /hadoop/cms/store/user/bemarsh/ProjectMetis/MET_Run2018C-PromptReco-v2_MINIAOD_CMS4_V10-01-00/ ${TAG}_data_Run2018C_MET_PromptReco-v2
# ./writeConfig.sh /hadoop/cms/store/user/bemarsh/ProjectMetis/SingleMuon_Run2018C-PromptReco-v2_MINIAOD_CMS4_V10-01-00/ ${TAG}_data_Run2018C_SingleMuon_PromptReco-v2

# ./writeConfig.sh /hadoop/cms/store/group/snt/run2_data2018_prompt/DoubleMuon_Run2018C-PromptReco-v3_MINIAOD_CMS4_V10-01-00 ${TAG}_data_Run2018C_DoubleMuon_PromptReco-v3
# ./writeConfig.sh /hadoop/cms/store/group/snt/run2_data2018_prompt/EGamma_Run2018C-PromptReco-v3_MINIAOD_CMS4_V10-01-00 ${TAG}_data_Run2018C_EGamma_PromptReco-v3
# ./writeConfig.sh /hadoop/cms/store/group/snt/run2_data2018_prompt/MuonEG_Run2018C-PromptReco-v3_MINIAOD_CMS4_V10-01-00 ${TAG}_data_Run2018C_MuonEG_PromptReco-v3
# ./writeConfig.sh /hadoop/cms/store/user/bemarsh/ProjectMetis/JetHT_Run2018C-PromptReco-v3_MINIAOD_CMS4_V10-01-00/ ${TAG}_data_Run2018C_JetHT_PromptReco-v3
# ./writeConfig.sh /hadoop/cms/store/user/bemarsh/ProjectMetis/MET_Run2018C-PromptReco-v3_MINIAOD_CMS4_V10-01-00/ ${TAG}_data_Run2018C_MET_PromptReco-v3
# ./writeConfig.sh /hadoop/cms/store/user/bemarsh/ProjectMetis/SingleMuon_Run2018C-PromptReco-v3_MINIAOD_CMS4_V10-01-00/ ${TAG}_data_Run2018C_SingleMuon_PromptReco-v3

# ./writeConfig.sh /hadoop/cms/store/group/snt/run2_data2018_prompt/DoubleMuon_Run2018D-PromptReco-v2_MINIAOD_CMS4_V10-01-00 ${TAG}_data_Run2018D_DoubleMuon_PromptReco-v2
# ./writeConfig.sh /hadoop/cms/store/group/snt/run2_data2018_prompt/EGamma_Run2018D-PromptReco-v2_MINIAOD_CMS4_V10-01-00 ${TAG}_data_Run2018D_EGamma_PromptReco-v2
# ./writeConfig.sh /hadoop/cms/store/group/snt/run2_data2018_prompt/MuonEG_Run2018D-PromptReco-v2_MINIAOD_CMS4_V10-01-00 ${TAG}_data_Run2018D_MuonEG_PromptReco-v2
# ./writeConfig.sh /hadoop/cms/store/user/bemarsh/ProjectMetis/JetHT_Run2018D-PromptReco-v2_MINIAOD_CMS4_V10-01-00/ ${TAG}_data_Run2018D_JetHT_PromptReco-v2
# ./writeConfig.sh /hadoop/cms/store/user/bemarsh/ProjectMetis/MET_Run2018D-PromptReco-v2_MINIAOD_CMS4_V10-01-00/ ${TAG}_data_Run2018D_MET_PromptReco-v2
# ./writeConfig.sh /hadoop/cms/store/user/bemarsh/ProjectMetis/SingleMuon_Run2018D-PromptReco-v2_MINIAOD_CMS4_V10-01-00/ ${TAG}_data_Run2018D_SingleMuon_PromptReco-v2

./writeConfig.sh /hadoop/cms/store/group/snt/run2_data2018/JetHT_Run2018A-17Sep2018-v1_MINIAOD_CMS4_V10-02-01/      ${TAG}_data_Run2018A_JetHT_17Sep2018
./writeConfig.sh /hadoop/cms/store/group/snt/run2_data2018/MET_Run2018A-17Sep2018-v1_MINIAOD_CMS4_V10-02-01/        ${TAG}_data_Run2018A_MET_17Sep2018
./writeConfig.sh /hadoop/cms/store/group/snt/run2_data2018/SingleMuon_Run2018A-17Sep2018-v2_MINIAOD_CMS4_V10-02-01/ ${TAG}_data_Run2018A_SingleMuon_17Sep2018
# ./writeConfig.sh /hadoop/cms/store/group/snt/run2_data2018/EGamma_Run2018A-17Sep2018-v1_MINIAOD_CMS4_V10-02-01/     ${TAG}_data_Run2018A_EGamma_17Sep2018
./writeConfig.sh /hadoop/cms/store/group/snt/run2_data2018/DoubleMuon_Run2018A-17Sep2018-v2_MINIAOD_CMS4_V10-02-01/ ${TAG}_data_Run2018A_DoubleMuon_17Sep2018
# ./writeConfig.sh /hadoop/cms/store/group/snt/run2_data2018/MuonEG_Run2018A-17Sep2018-v1_MINIAOD_CMS4_V10-02-01/     ${TAG}_data_Run2018A_MuonEG_17Sep2018

./writeConfig.sh /hadoop/cms/store/group/snt/run2_data2018/JetHT_Run2018B-17Sep2018-v1_MINIAOD_CMS4_V10-02-01/      ${TAG}_data_Run2018B_JetHT_17Sep2018
# ./writeConfig.sh /hadoop/cms/store/group/snt/run2_data2018/MET_Run2018B-17Sep2018-v1_MINIAOD_CMS4_V10-02-01/        ${TAG}_data_Run2018B_MET_17Sep2018
./writeConfig.sh /hadoop/cms/store/group/snt/run2_data2018/SingleMuon_Run2018B-17Sep2018-v1_MINIAOD_CMS4_V10-02-01/ ${TAG}_data_Run2018B_SingleMuon_17Sep2018
./writeConfig.sh /hadoop/cms/store/group/snt/run2_data2018/EGamma_Run2018B-17Sep2018-v1_MINIAOD_CMS4_V10-02-01/     ${TAG}_data_Run2018B_EGamma_17Sep2018
./writeConfig.sh /hadoop/cms/store/group/snt/run2_data2018/DoubleMuon_Run2018B-17Sep2018-v1_MINIAOD_CMS4_V10-02-01/ ${TAG}_data_Run2018B_DoubleMuon_17Sep2018
# ./writeConfig.sh /hadoop/cms/store/group/snt/run2_data2018/MuonEG_Run2018B-17Sep2018-v1_MINIAOD_CMS4_V10-02-01/     ${TAG}_data_Run2018B_MuonEG_17Sep2018

# ./writeConfig.sh /hadoop/cms/store/group/snt/run2_data2018/JetHT_Run2018C-17Sep2018-v1_MINIAOD_CMS4_V10-02-01/      ${TAG}_data_Run2018C_JetHT_17Sep2018
./writeConfig.sh /hadoop/cms/store/group/snt/run2_data2018/MET_Run2018C-17Sep2018-v1_MINIAOD_CMS4_V10-02-01/        ${TAG}_data_Run2018C_MET_17Sep2018
./writeConfig.sh /hadoop/cms/store/group/snt/run2_data2018/SingleMuon_Run2018C-17Sep2018-v1_MINIAOD_CMS4_V10-02-01/ ${TAG}_data_Run2018C_SingleMuon_17Sep2018
./writeConfig.sh /hadoop/cms/store/group/snt/run2_data2018/EGamma_Run2018C-17Sep2018-v1_MINIAOD_CMS4_V10-02-01/     ${TAG}_data_Run2018C_EGamma_17Sep2018
./writeConfig.sh /hadoop/cms/store/group/snt/run2_data2018/DoubleMuon_Run2018C-17Sep2018-v1_MINIAOD_CMS4_V10-02-01/ ${TAG}_data_Run2018C_DoubleMuon_17Sep2018
# ./writeConfig.sh /hadoop/cms/store/group/snt/run2_data2018/MuonEG_Run2018C-17Sep2018-v1_MINIAOD_CMS4_V10-02-01/     ${TAG}_data_Run2018C_MuonEG_17Sep2018


# # # special HE miss MC
# ./writeConfig.sh /hadoop/cms/store/group/snt/run2_mc2018_test/TTToSemiLeptonic_TuneCP5_13TeV-powheg-pythia8_RunIISpring18MiniAOD-HEMPremix_100X_upgrade2018_realistic_v10-v3_MINIAODSIM_CMS4_V10-01-00/ ${TAG}_ttsl_hemiss
# ./writeConfig.sh /hadoop/cms/store/group/snt/run2_mc2018_test/TTToSemiLeptonic_TuneCP5_13TeV-powheg-pythia8_RunIISpring18MiniAOD-100X_upgrade2018_realistic_v10_ext1-v1_MINIAODSIM_CMS4_V10-01-00/ ${TAG}_ttsl_nohemiss

# # # special HEmiss data relval
# ./writeConfig.sh /hadoop/cms/store/group/snt/run2_mc2018_test/JetHT_CMSSW_10_1_7-101X_dataRun2_Prompt_HEmiss_v1_RelVal_jetHT2018B-v1_MINIAOD_CMS4_V10-01-00/ ${TAG}_data_Run2018B_JetHT_HEmiss_RelVal
# ./writeConfig.sh /hadoop/cms/store/group/snt/run2_mc2018_test/JetHT_CMSSW_10_1_7-101X_dataRun2_Prompt_v11_RelVal_jetHT2018B-v1_MINIAOD_CMS4_V10-01-00/ ${TAG}_data_Run2018B_JetHT_noHEmiss_RelVal
# ./writeConfig.sh /hadoop/cms/store/group/snt/run2_mc2018_test/MET_CMSSW_10_1_7-101X_dataRun2_Prompt_HEmiss_v1_RelVal_met2018B-v1_MINIAOD_CMS4_V10-01-00/ ${TAG}_data_Run2018B_MET_HEmiss_RelVal
# ./writeConfig.sh /hadoop/cms/store/group/snt/run2_mc2018_test/MET_CMSSW_10_1_7-101X_dataRun2_Prompt_v11_RelVal_met2018B-v1_MINIAOD_CMS4_V10-01-00/ ${TAG}_data_Run2018B_MET_noHEmiss_RelVal

# #
# # TTBAR
# #


# #
# # HIGH STATS TTBAR EXTENSION
# #

# #
# # W+JETS
# #

# #
# # W+JETS extensions
# #

# #
# # SINGLE TOP
# #

# #
# # DY+JETS
# #

# #
# # GAMMA + JETS
# #

# #
# # Z INVISIBLE
# #

# #
# # Z INVISIBLE EXTENSIONS
# #

# # #
# # # DIBOSON
# # #


# # #
# # # TRIBOSON
# # #

# # #
# # # TTV, tt+X
# # #

# #
# # QCD HT BINS
# #

# #
# # QCD HT BINS Extension
# #

#
# QCD PT bins
#

# #
# # SIGNAL
# #

# # SIGNAL SCANS
# #


# --- write submit script ---
mkdir -p configs_${TAG}

mv condor_${TAG}*.cmd configs_${TAG}
echo "#!/bin/bash" > submitAll.sh
echo "voms-proxy-init -voms cms -valid 240:00" >> submitAll.sh
x=0
for file in configs_${TAG}/*.cmd
do 
    echo "condor_submit ${file}" >> submitAll.sh
    x=$((x+`grep "queue" $file | wc -l`))
done
echo "[writeAllConfig] TOTAL # JOBS: $x"
chmod +x submitAll.sh
echo "[writeAllConfig] wrote submit script submitAll.sh"
