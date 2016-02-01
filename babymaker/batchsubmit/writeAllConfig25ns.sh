#!/bin/bash

#
# All MT2 related datasets available on hadoop
#

TAG="softLep-v2_V00-01-10_25ns_miniaodv2"

#
# DATA
#

./writeConfig.sh /hadoop/cms/store/group/snt/run2_data/Run2015C_25ns_JetHT_MINIAOD_05Oct2015-v1/merged/V07-04-11/ ${TAG}_data_Run2015C_JetHT_05Oct2015
./writeConfig.sh /hadoop/cms/store/group/snt/run2_data/Run2015C_25ns_MET_MINIAOD_05Oct2015-v1/merged/V07-04-11/ ${TAG}_data_Run2015C_MET_05Oct2015
./writeConfig.sh /hadoop/cms/store/group/snt/run2_data/Run2015C_25ns_HTMHT_MINIAOD_05Oct2015-v1/merged/V07-04-11/ ${TAG}_data_Run2015C_HTMHT_05Oct2015
./writeConfig.sh /hadoop/cms/store/group/snt/run2_data/Run2015C_25ns_SingleMuon_MINIAOD_05Oct2015-v1/merged/V07-04-11/ ${TAG}_data_Run2015C_SingleMuon_05Oct2015
./writeConfig.sh /hadoop/cms/store/group/snt/run2_data/Run2015C_25ns_DoubleMuon_MINIAOD_05Oct2015-v1/merged/V07-04-11/ ${TAG}_data_Run2015C_DoubleMuon_05Oct2015
./writeConfig.sh /hadoop/cms/store/group/snt/run2_data/Run2015C_25ns_DoubleEG_MINIAOD_05Oct2015-v1/merged/V07-04-11/ ${TAG}_data_Run2015C_DoubleEG_05Oct2015
./writeConfig.sh /hadoop/cms/store/group/snt/run2_data/Run2015C_25ns_MuonEG_MINIAOD_05Oct2015-v1/merged/V07-04-11/ ${TAG}_data_Run2015C_MuonEG_05Oct2015
./writeConfig.sh /hadoop/cms/store/group/snt/run2_data/Run2015C_25ns_SingleElectron_MINIAOD_05Oct2015-v1/merged/V07-04-11/ ${TAG}_data_Run2015C_SingleElectron_05Oct2015
./writeConfig.sh /hadoop/cms/store/group/snt/run2_data/Run2015C_25ns_SinglePhoton_MINIAOD_05Oct2015-v1/merged/V07-04-11/ ${TAG}_data_Run2015C_SinglePhoton_05Oct2015

./writeConfig.sh /hadoop/cms/store/group/snt/run2_data/Run2015D_JetHT_MINIAOD_05Oct2015-v1/merged/V07-04-11/ ${TAG}_data_Run2015D_JetHT_05Oct2015
./writeConfig.sh /hadoop/cms/store/group/snt/run2_data/Run2015D_MET_MINIAOD_05Oct2015-v1/merged/V07-04-11/ ${TAG}_data_Run2015D_MET_05Oct2015
./writeConfig.sh /hadoop/cms/store/group/snt/run2_data/Run2015D_HTMHT_MINIAOD_05Oct2015-v1/merged/V07-04-11/ ${TAG}_data_Run2015D_HTMHT_05Oct2015
./writeConfig.sh /hadoop/cms/store/group/snt/run2_data/Run2015D_SingleMuon_MINIAOD_05Oct2015-v1/merged/V07-04-11/ ${TAG}_data_Run2015D_SingleMuon_05Oct2015
./writeConfig.sh /hadoop/cms/store/group/snt/run2_data/Run2015D_DoubleMuon_MINIAOD_05Oct2015-v1/merged/V07-04-11/ ${TAG}_data_Run2015D_DoubleMuon_05Oct2015
./writeConfig.sh /hadoop/cms/store/group/snt/run2_data/Run2015D_DoubleEG_MINIAOD_05Oct2015-v1/merged/V07-04-11/ ${TAG}_data_Run2015D_DoubleEG_05Oct2015
./writeConfig.sh /hadoop/cms/store/group/snt/run2_data/Run2015D_MuonEG_MINIAOD_05Oct2015-v1/merged/V07-04-11/ ${TAG}_data_Run2015D_MuonEG_05Oct2015
./writeConfig.sh /hadoop/cms/store/group/snt/run2_data/Run2015D_SingleElectron_MINIAOD_05Oct2015-v1/merged/V07-04-11/ ${TAG}_data_Run2015D_SingleElectron_05Oct2015
./writeConfig.sh /hadoop/cms/store/group/snt/run2_data/Run2015D_SinglePhoton_MINIAOD_05Oct2015-v1/merged/V07-04-11/ ${TAG}_data_Run2015D_SinglePhoton_05Oct2015

./writeConfig.sh /hadoop/cms/store/group/snt/run2_data/Run2015D_JetHT_MINIAOD_PromptReco-v4/merged/V07-04-11/ ${TAG}_data_Run2015D_JetHT_PromptReco
./writeConfig.sh /hadoop/cms/store/group/snt/run2_data/Run2015D_MET_MINIAOD_PromptReco-v4/merged/V07-04-11/ ${TAG}_data_Run2015D_MET_PromptReco
./writeConfig.sh /hadoop/cms/store/group/snt/run2_data/Run2015D_HTMHT_MINIAOD_PromptReco-v4/merged/V07-04-11/ ${TAG}_data_Run2015D_HTMHT_PromptReco
./writeConfig.sh /hadoop/cms/store/group/snt/run2_data/Run2015D_SingleMuon_MINIAOD_PromptReco-v4/merged/V07-04-11/ ${TAG}_data_Run2015D_SingleMuon_PromptReco
./writeConfig.sh /hadoop/cms/store/group/snt/run2_data/Run2015D_DoubleMuon_MINIAOD_PromptReco-v4/merged/V07-04-11/ ${TAG}_data_Run2015D_DoubleMuon_PromptReco
./writeConfig.sh /hadoop/cms/store/group/snt/run2_data/Run2015D_DoubleEG_MINIAOD_PromptReco-v4/merged/V07-04-11/ ${TAG}_data_Run2015D_DoubleEG_PromptReco
./writeConfig.sh /hadoop/cms/store/group/snt/run2_data/Run2015D_MuonEG_MINIAOD_PromptReco-v4/merged/V07-04-11/ ${TAG}_data_Run2015D_MuonEG_PromptReco
./writeConfig.sh /hadoop/cms/store/group/snt/run2_data/Run2015D_SingleElectron_MINIAOD_PromptReco-v4/merged/V07-04-11/ ${TAG}_data_Run2015D_SingleElectron_PromptReco
./writeConfig.sh /hadoop/cms/store/group/snt/run2_data/Run2015D_SinglePhoton_MINIAOD_PromptReco-v4/merged/V07-04-11/ ${TAG}_data_Run2015D_SinglePhoton_PromptReco

#
# TTBAR
#

./writeConfig.sh /hadoop/cms/store/group/snt/run2_25ns_MiniAODv2/TTJets_SingleLeptFromT_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_RunIISpring15MiniAODv2-74X_mcRun2_asymptotic_v2-v1/V07-04-11/ ${TAG}_ttsl_mg_lo_top
./writeConfig.sh /hadoop/cms/store/group/snt/run2_25ns_MiniAODv2/TTJets_SingleLeptFromTbar_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_RunIISpring15MiniAODv2-74X_mcRun2_asymptotic_v2-v1/V07-04-11/ ${TAG}_ttsl_mg_lo_tbar
./writeConfig.sh /hadoop/cms/store/group/snt/run2_25ns_MiniAODv2/TTJets_DiLept_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_RunIISpring15MiniAODv2-74X_mcRun2_asymptotic_v2-v1/V07-04-11/ ${TAG}_ttdl_mg_lo

#
# HIGH STATS TTBAR EXTENSION
#

#./writeConfig.sh /hadoop/cms/store/group/snt/run2_25ns_MiniAODv2/TTJets_SingleLeptFromT_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_RunIISpring15MiniAODv2-74X_mcRun2_asymptotic_v2_ext1-v1/V07-04-11 ${TAG}_ttsl_mg_lo_top_ext1
#./writeConfig.sh /hadoop/cms/store/group/snt/run2_25ns_MiniAODv2/TTJets_SingleLeptFromTbar_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_RunIISpring15MiniAODv2-74X_mcRun2_asymptotic_v2_ext1-v1/07-04-11/ ${TAG}_ttsl_mg_lo_tbar_ext1
# ./writeConfig.sh /hadoop/cms/store/group/snt/run2_25ns_MiniAODv2/TTJets_DiLept_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_RunIISpring15MiniAODv2-74X_mcRun2_asymptotic_v2_ext1-v1/V07-04-11/ ${TAG}_ttdl_mg_lo_ext1

#
# W+JETS
#

#./writeConfig.sh /hadoop/cms/store/group/snt/run2_25ns_MiniAODv2/WJetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_RunIISpring15MiniAODv2-74X_mcRun2_asymptotic_v2-v1/V07-04-11/ ${TAG}_wjets_mg_lo

./writeConfig.sh /hadoop/cms/store/group/snt/run2_25ns_MiniAODv2/WJetsToLNu_HT-100To200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_RunIISpring15MiniAODv2-74X_mcRun2_asymptotic_v2-v1/V07-04-11/ ${TAG}_wjets_ht100to200
./writeConfig.sh /hadoop/cms/store/group/snt/run2_25ns_MiniAODv2/WJetsToLNu_HT-200To400_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_RunIISpring15MiniAODv2-74X_mcRun2_asymptotic_v2-v1/V07-04-11/ ${TAG}_wjets_ht200to400
./writeConfig.sh /hadoop/cms/store/group/snt/run2_25ns_MiniAODv2/WJetsToLNu_HT-400To600_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_RunIISpring15MiniAODv2-74X_mcRun2_asymptotic_v2-v1/V07-04-11/ ${TAG}_wjets_ht400to600
./writeConfig.sh /hadoop/cms/store/group/snt/run2_25ns_MiniAODv2/WJetsToLNu_HT-600To800_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_RunIISpring15MiniAODv2-74X_mcRun2_asymptotic_v2-v1/V07-04-11/ ${TAG}_wjets_ht600to800
./writeConfig.sh /hadoop/cms/store/group/snt/run2_25ns_MiniAODv2/WJetsToLNu_HT-800To1200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_RunIISpring15MiniAODv2-74X_mcRun2_asymptotic_v2-v1/V07-04-11/ ${TAG}_wjets_ht800to1200
./writeConfig.sh /hadoop/cms/store/group/snt/run2_25ns_MiniAODv2/WJetsToLNu_HT-1200To2500_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_RunIISpring15MiniAODv2-74X_mcRun2_asymptotic_v2-v1/V07-04-11/ ${TAG}_wjets_ht1200to2500
./writeConfig.sh /hadoop/cms/store/group/snt/run2_25ns_MiniAODv2/WJetsToLNu_HT-2500ToInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_RunIISpring15MiniAODv2-74X_mcRun2_asymptotic_v2-v1/V07-04-11/ ${TAG}_wjets_ht2500toInf

#
# SINGLE TOP
#

./writeConfig.sh /hadoop/cms/store/group/snt/run2_25ns_MiniAODv2/ST_t-channel_top_4f_leptonDecays_13TeV-powheg-pythia8_TuneCUETP8M1_RunIISpring15MiniAODv2-74X_mcRun2_asymptotic_v2-v1/V07-04-11/ ${TAG}_singletop_powheg_4f_ttchan_l
./writeConfig.sh /hadoop/cms/store/group/snt/run2_25ns_MiniAODv2/ST_t-channel_antitop_4f_leptonDecays_13TeV-powheg-pythia8_TuneCUETP8M1_RunIISpring15MiniAODv2-74X_mcRun2_asymptotic_v2-v1/V07-04-11/ ${TAG}_singletop_powheg_4f_tbartchan_l
./writeConfig.sh /hadoop/cms/store/group/snt/run2_25ns_MiniAODv2/ST_s-channel_4f_leptonDecays_13TeV-amcatnlo-pythia8_TuneCUETP8M1_RunIISpring15MiniAODv2-74X_mcRun2_asymptotic_v2-v1/V07-04-11/ ${TAG}_singletop_amcatnlo_4f_schan
./writeConfig.sh /hadoop/cms/store/group/snt/run2_25ns_MiniAODv2/ST_tW_top_5f_inclusiveDecays_13TeV-powheg-pythia8_TuneCUETP8M1_RunIISpring15MiniAODv2-74X_mcRun2_asymptotic_v2-v2/V07-04-11/ ${TAG}_singletop_powheg_5f_tWchan
./writeConfig.sh /hadoop/cms/store/group/snt/run2_25ns_MiniAODv2/ST_tW_antitop_5f_inclusiveDecays_13TeV-powheg-pythia8_TuneCUETP8M1_RunIISpring15MiniAODv2-74X_mcRun2_asymptotic_v2-v1/V07-04-11/ ${TAG}_singletop_powheg_5f_tbarWchan


#
# DY+JETS
#

#./writeConfig.sh /hadoop/cms/store/group/snt/run2_25ns_MiniAODv2/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_RunIISpring15MiniAODv2-74X_mcRun2_asymptotic_v2-v1/V07-04-11/ ${TAG}_zjets_mg_lo

./writeConfig.sh /hadoop/cms/store/group/snt/run2_25ns_MiniAODv2/DYJetsToLL_M-50_HT-100to200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_RunIISpring15MiniAODv2-74X_mcRun2_asymptotic_v2-v1/V07-04-11/ ${TAG}_dyjetsll_ht100to200
./writeConfig.sh /hadoop/cms/store/group/snt/run2_25ns_MiniAODv2/DYJetsToLL_M-50_HT-200to400_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_RunIISpring15MiniAODv2-74X_mcRun2_asymptotic_v2-v1/V07-04-11/ ${TAG}_dyjetsll_ht200to400
./writeConfig.sh /hadoop/cms/store/group/snt/run2_25ns_MiniAODv2/DYJetsToLL_M-50_HT-400to600_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_RunIISpring15MiniAODv2-74X_mcRun2_asymptotic_v2-v2/V07-04-11/ ${TAG}_dyjetsll_ht400to600
./writeConfig.sh /hadoop/cms/store/group/snt/run2_25ns_MiniAODv2/DYJetsToLL_M-50_HT-600toInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_RunIISpring15MiniAODv2-74X_mcRun2_asymptotic_v2-v1/V07-04-11/ ${TAG}_dyjetsll_ht600toInf

#
# GAMMA + JETS
#

# ./writeConfig.sh /hadoop/cms/store/group/snt/run2_25ns_MiniAODv2/GJets_HT-100To200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_RunIISpring15MiniAODv2-74X_mcRun2_asymptotic_v2-v1/V07-04-11/ ${TAG}_gjet_ht100to200
# ./writeConfig.sh /hadoop/cms/store/group/snt/run2_25ns_MiniAODv2/GJets_HT-200To400_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_RunIISpring15MiniAODv2-74X_mcRun2_asymptotic_v2-v1/V07-04-11/ ${TAG}_gjet_ht200to400
# ./writeConfig.sh /hadoop/cms/store/group/snt/run2_25ns_MiniAODv2/GJets_HT-400To600_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_RunIISpring15MiniAODv2-74X_mcRun2_asymptotic_v2-v1/V07-04-11/ ${TAG}_gjet_ht400to600
# ./writeConfig.sh /hadoop/cms/store/group/snt/run2_25ns_MiniAODv2/GJets_HT-600ToInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_RunIISpring15MiniAODv2-74X_mcRun2_asymptotic_v2-v1/V07-04-11/ ${TAG}_gjet_ht600toInf

#
# Z INVISIBLE
#

./writeConfig.sh /hadoop/cms/store/group/snt/run2_25ns_MiniAODv2/ZJetsToNuNu_HT-100To200_13TeV-madgraph_RunIISpring15MiniAODv2-74X_mcRun2_asymptotic_v2-v1/V07-04-11/ ${TAG}_zinv_ht100to200
./writeConfig.sh /hadoop/cms/store/group/snt/run2_25ns_MiniAODv2/ZJetsToNuNu_HT-200To400_13TeV-madgraph_RunIISpring15MiniAODv2-74X_mcRun2_asymptotic_v2-v1/V07-04-11/ ${TAG}_zinv_ht200to400
./writeConfig.sh /hadoop/cms/store/group/snt/run2_25ns_MiniAODv2/ZJetsToNuNu_HT-400To600_13TeV-madgraph_RunIISpring15MiniAODv2-74X_mcRun2_asymptotic_v2-v1/V07-04-11/ ${TAG}_zinv_ht400to600
./writeConfig.sh /hadoop/cms/store/group/snt/run2_25ns_MiniAODv2/ZJetsToNuNu_HT-600ToInf_13TeV-madgraph_RunIISpring15MiniAODv2-74X_mcRun2_asymptotic_v2-v2/V07-04-11/ ${TAG}_zinv_ht600toInf

#
# DIBOSON
#

./writeConfig.sh /hadoop/cms/store/group/snt/run2_25ns_MiniAODv2/WWTo2L2Nu_13TeV-powheg_RunIISpring15MiniAODv2-74X_mcRun2_asymptotic_v2-v1/V07-04-11/ ${TAG}_wwlnln_powheg
./writeConfig.sh /hadoop/cms/store/group/snt/run2_25ns_MiniAODv2/WWToLNuQQ_13TeV-powheg_RunIISpring15MiniAODv2-74X_mcRun2_asymptotic_v2-v1/V07-04-11/ ${TAG}_wwlnqq_powheg
./writeConfig.sh /hadoop/cms/store/group/snt/run2_25ns_MiniAODv2/WZTo3LNu_TuneCUETP8M1_13TeV-powheg-pythia8_RunIISpring15MiniAODv2-74X_mcRun2_asymptotic_v2-v1/V07-04-11/ ${TAG}_wzllln_powheg
./writeConfig.sh /hadoop/cms/store/group/snt/run2_25ns_MiniAODv2/WZTo2L2Q_13TeV_amcatnloFXFX_madspin_pythia8_RunIISpring15MiniAODv2-74X_mcRun2_asymptotic_v2-v1/V07-04-11/ ${TAG}_wzllqq_amcnlo
./writeConfig.sh /hadoop/cms/store/group/snt/run2_25ns_MiniAODv2/WZTo1L3Nu_13TeV_amcatnloFXFX_madspin_pythia8_RunIISpring15MiniAODv2-74X_mcRun2_asymptotic_v2-v1/V07-04-11/ ${TAG}_wzlnnn_amcnlo
./writeConfig.sh /hadoop/cms/store/group/snt/run2_25ns_MiniAODv2/WZTo1L1Nu2Q_13TeV_amcatnloFXFX_madspin_pythia8_RunIISpring15MiniAODv2-74X_mcRun2_asymptotic_v2-v1/V07-04-11/ ${TAG}_wzlnqq_amcnlo
./writeConfig.sh /hadoop/cms/store/group/snt/run2_25ns_MiniAODv2/ZZTo4L_13TeV_powheg_pythia8_RunIISpring15MiniAODv2-74X_mcRun2_asymptotic_v2-v2/V07-04-11/ ${TAG}_zzllll_powheg
./writeConfig.sh /hadoop/cms/store/group/snt/run2_25ns_MiniAODv2/ZZTo2L2Nu_13TeV_powheg_pythia8_RunIISpring15MiniAODv2-74X_mcRun2_asymptotic_v2-v2/V07-04-11/ ${TAG}_zzllnn_powheg
./writeConfig.sh /hadoop/cms/store/group/snt/run2_25ns_MiniAODv2/ZZTo2L2Q_13TeV_amcatnloFXFX_madspin_pythia8_RunIISpring15MiniAODv2-74X_mcRun2_asymptotic_v2-v1/V07-04-11/ ${TAG}_zzllqq_amcatnlo
./writeConfig.sh /hadoop/cms/store/group/snt/run2_25ns_MiniAODv2/ZZTo2Q2Nu_13TeV_amcatnloFXFX_madspin_pythia8_RunIISpring15MiniAODv2-74X_mcRun2_asymptotic_v2-v1/V07-04-11/ ${TAG}_zzqqnn_amcatnlo

#
# TRIBOSON
#

#
# TTV
#

./writeConfig.sh /hadoop/cms/store/group/snt/run2_25ns_MiniAODv2/TTWJetsToLNu_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-pythia8_RunIISpring15MiniAODv2-74X_mcRun2_asymptotic_v2-v1/V07-04-11/ ${TAG}_ttw_lnu_amcatnlo
./writeConfig.sh /hadoop/cms/store/group/snt/run2_25ns_MiniAODv2/TTWJetsToQQ_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-pythia8_RunIISpring15MiniAODv2-74X_mcRun2_asymptotic_v2-v1/V07-04-11/ ${TAG}_ttw_qq_amcatnlo
./writeConfig.sh /hadoop/cms/store/group/snt/run2_25ns_MiniAODv2/TTZToQQ_TuneCUETP8M1_13TeV-amcatnlo-pythia8_RunIISpring15MiniAODv2-74X_mcRun2_asymptotic_v2-v1/V07-04-11/ ${TAG}_ttz_qq_amcatnlo
./writeConfig.sh /hadoop/cms/store/group/snt/run2_25ns_MiniAODv2/TTZToLLNuNu_M-10_TuneCUETP8M1_13TeV-amcatnlo-pythia8_RunIISpring15MiniAODv2-74X_mcRun2_asymptotic_v2-v2/V07-04-11/ ${TAG}_ttz_llnunu_amcatnlo
./writeConfig.sh /hadoop/cms/store/group/snt/run2_25ns_MiniAODv2/TTGJets_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-pythia8_RunIISpring15MiniAODv2-74X_mcRun2_asymptotic_v2-v1/V07-04-11/ ${TAG}_ttg_amcatnlo
./writeConfig.sh /hadoop/cms/store/group/snt/run2_25ns_MiniAODv2/ttHJetToNonbb_M125_13TeV_amcatnloFXFX_madspin_pythia8_mWCutfix_RunIISpring15MiniAODv2-74X_mcRun2_asymptotic_v2-v1/V07-04-11/ ${TAG}_tth_nonbb_amcatnlo
./writeConfig.sh /hadoop/cms/store/group/snt/run2_25ns_MiniAODv2/ttHJetTobb_M125_13TeV_amcatnloFXFX_madspin_pythia8_RunIISpring15MiniAODv2-74X_mcRun2_asymptotic_v2-v1/V07-04-11/ ${TAG}_tth_bb_amcatnlo


#
# QCD
#

#./writeConfig.sh  ${TAG}_qcd_pt120to170
#./writeConfig.sh  ${TAG}_qcd_pt170to300
#./writeConfig.sh  ${TAG}_qcd_pt300to470
#./writeConfig.sh  ${TAG}_qcd_pt470to600
#./writeConfig.sh  ${TAG}_qcd_pt600to800
#./writeConfig.sh  ${TAG}_qcd_pt800to1000
#./writeConfig.sh  ${TAG}_qcd_pt1000to1400
#./writeConfig.sh  ${TAG}_qcd_pt1400to1800
#./writeConfig.sh  ${TAG}_qcd_pt1800to2400
#./writeConfig.sh  ${TAG}_qcd_pt2400to3200
#./writeConfig.sh  ${TAG}_qcd_pt3200toInf

./writeConfig.sh /hadoop/cms/store/group/snt/run2_25ns_MiniAODv2/QCD_HT200to300_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_RunIISpring15MiniAODv2-74X_mcRun2_asymptotic_v2-v1/V07-04-11/ ${TAG}_qcd_ht200to300
./writeConfig.sh /hadoop/cms/store/group/snt/run2_25ns_MiniAODv2/QCD_HT300to500_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_RunIISpring15MiniAODv2-74X_mcRun2_asymptotic_v2-v1/V07-04-11/ ${TAG}_qcd_ht300to500
./writeConfig.sh /hadoop/cms/store/group/snt/run2_25ns_MiniAODv2/QCD_HT500to700_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_RunIISpring15MiniAODv2-74X_mcRun2_asymptotic_v2-v1/V07-04-11/ ${TAG}_qcd_ht500to700
./writeConfig.sh /hadoop/cms/store/group/snt/run2_25ns_MiniAODv2/QCD_HT700to1000_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_RunIISpring15MiniAODv2-74X_mcRun2_asymptotic_v2-v1/V07-04-11/ ${TAG}_qcd_ht700to1000
./writeConfig.sh /hadoop/cms/store/group/snt/run2_25ns_MiniAODv2/QCD_HT1000to1500_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_RunIISpring15MiniAODv2-74X_mcRun2_asymptotic_v2-v1/V07-04-11/ ${TAG}_qcd_ht1000to1500
./writeConfig.sh /hadoop/cms/store/group/snt/run2_25ns_MiniAODv2/QCD_HT1500to2000_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_RunIISpring15MiniAODv2-74X_mcRun2_asymptotic_v2-v1/V07-04-11/ ${TAG}_qcd_ht1500to2000
./writeConfig.sh /hadoop/cms/store/group/snt/run2_25ns_MiniAODv2/QCD_HT2000toInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_RunIISpring15MiniAODv2-74X_mcRun2_asymptotic_v2-v1/V07-04-11/ ${TAG}_qcd_ht2000toInf

#
# SIGNAL
#

# ./writeConfig.sh /hadoop/cms/store/group/snt/run2_25ns_MiniAODv2/SMS-T1tttt_mGluino-1500_mLSP-100_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_RunIISpring15MiniAODv2-74X_mcRun2_asymptotic_v2-v1/V07-04-11/ ${TAG}_T1tttt_1500_100
# ./writeConfig.sh /hadoop/cms/store/group/snt/run2_25ns_MiniAODv2/SMS-T1tttt_mGluino-1200_mLSP-800_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_RunIISpring15MiniAODv2-74X_mcRun2_asymptotic_v2-v1/V07-04-11/ ${TAG}_T1tttt_1200_800
# ./writeConfig.sh /hadoop/cms/store/group/snt/run2_25ns_MiniAODv2/SMS-T1bbbb_mGluino-1500_mLSP-100_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_RunIISpring15MiniAODv2-74X_mcRun2_asymptotic_v2-v1/V07-04-11/ ${TAG}_T1bbbb_1500_100
# ./writeConfig.sh /hadoop/cms/store/group/snt/run2_25ns_MiniAODv2/SMS-T1bbbb_mGluino-1000_mLSP-900_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_RunIISpring15MiniAODv2-74X_mcRun2_asymptotic_v2-v1/V07-04-11/ ${TAG}_T1bbbb_1000_900
# ./writeConfig.sh /hadoop/cms/store/group/snt/run2_25ns_MiniAODv2/SMS-T1qqqq_mGluino-1400_mLSP-100_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_RunIISpring15MiniAODv2-74X_mcRun2_asymptotic_v2-v1/V07-04-11/ ${TAG}_T1qqqq_1400_100
# ./writeConfig.sh /hadoop/cms/store/group/snt/run2_25ns_MiniAODv2/SMS-T1qqqq_mGluino-1000_mLSP-800_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_RunIISpring15MiniAODv2-74X_mcRun2_asymptotic_v2-v1/V07-04-11/ ${TAG}_T1qqqq_1000_800

# Fastsim v1
./writeConfig.sh /hadoop/cms/store/group/snt/run2_fastsim/SMS-T2-4bd_mStop-375_mLSP-295to365_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_RunIISpring15FSPremix-MCRUN2_74_V9-v1/V07-04-12_miniaodv1_FS/ ${TAG}_T2-4bd_375_295to365
./writeConfig.sh /hadoop/cms/store/group/snt/run2_fastsim/SMS-T2-4bd_mStop-275_mLSP-195to265_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_RunIISpring15FSPremix-MCRUN2_74_V9-v1/V07-04-12_miniaodv1_FS/ ${TAG}_T2-4bd_275_195to265
# Fastsim v2
./writeConfig.sh /hadoop/cms/store/group/snt/run2_fastsim/SMS-T2-4bd_mStop-300_mLSP-220to290_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_RunIISpring15MiniAODv2-FastAsympt25ns_74X_mcRun2_asymptotic_v2-v1/V07-04-12/ ${TAG}_T2-4bd_300_220to290
./writeConfig.sh /hadoop/cms/store/group/snt/run2_fastsim/SMS-T2-4bd_mStop-325_mLSP-245to315_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_RunIISpring15MiniAODv2-FastAsympt25ns_74X_mcRun2_asymptotic_v2-v1/V07-04-12/ ${TAG}_T2-4bd_325_245to315
./writeConfig.sh /hadoop/cms/store/group/snt/run2_fastsim/SMS-T2-4bd_mStop-400_mLSP-320to390_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_RunIISpring15MiniAODv2-FastAsympt25ns_74X_mcRun2_asymptotic_v2-v1/V07-04-12/ ${TAG}_T2-4bd_400_320to390
./writeConfig.sh /hadoop/cms/store/group/snt/run2_fastsim/SMS-T5qqqqWW_mGl-1025to1200_mLSP-0to1175_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_RunIISpring15MiniAODv2-FastAsympt25ns_74X_mcRun2_asymptotic_v2-v1/V07-04-12/ ${TAG}_T5qqqqWW_1025to1200_0to1175
./writeConfig.sh /hadoop/cms/store/group/snt/run2_fastsim/SMS-T5qqqqWW_mGl-1225to1400_mLSP-0to1175_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_RunIISpring15MiniAODv2-FastAsympt25ns_74X_mcRun2_asymptotic_v2-v1/V07-04-12/ ${TAG}_T5qqqqWW_1225to1400_0to1175
./writeConfig.sh /hadoop/cms/store/group/snt/run2_fastsim/SMS-T5qqqqWW_mGl-1425to1600_mLSP-0to1175_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_RunIISpring15MiniAODv2-FastAsympt25ns_74X_mcRun2_asymptotic_v2-v1/V07-04-12/ ${TAG}_T5qqqqWW_1425to1600_0to1175


# --- write submit script ---
mkdir -p configs_${TAG}

mv condor_${TAG}*.cmd configs_${TAG}
echo "#!/bin/bash" > submitAll.sh
echo "voms-proxy-init -voms cms -valid 240:00" >> submitAll.sh
for file in configs_${TAG}/*.cmd
do 
    echo "condor_submit ${file}" >> submitAll.sh
done
chmod +x submitAll.sh
echo "[writeAllConfig] wrote submit script submitAll.sh"
