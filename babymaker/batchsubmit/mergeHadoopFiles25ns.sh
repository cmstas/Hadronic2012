#!/bin/bash

function run () {
    echo root -b -q mergeHadoopFiles.C\(\"${HADOOPDIR}/${TAG}_$1/\",\"${OUTPUTDIR}/$1.root\"\)
    nohup nice -n 19 root -b -q mergeHadoopFiles.C\(\"${HADOOPDIR}/${TAG}_$1/\",\"${OUTPUTDIR}/$1.root\"\) >& log_merge_${TAG}_$1.txt &
}

TAG=softLep-v2_V00-01-10_25ns_miniaodv2

HADOOPDIR=/hadoop/cms/store/user/${USER}/mt2babies/
OUTPUTDIR=/nfs-6/userdata/mt2/$TAG/

mkdir -p $OUTPUTDIR
chmod -R a+wrx $OUTPUTDIR

#
# DATA
#

run data_Run2015C_JetHT_05Oct2015
run data_Run2015C_MET_05Oct2015
run data_Run2015C_HTMHT_05Oct2015
run data_Run2015C_SingleMuon_05Oct2015
run data_Run2015C_SingleElectron_05Oct2015
run data_Run2015C_SinglePhoton_05Oct2015
run data_Run2015C_DoubleMuon_05Oct2015
run data_Run2015C_DoubleEG_05Oct2015
run data_Run2015C_MuonEG_05Oct2015

run data_Run2015D_JetHT_05Oct2015
run data_Run2015D_MET_05Oct2015
run data_Run2015D_HTMHT_05Oct2015
run data_Run2015D_SingleMuon_05Oct2015
run data_Run2015D_SingleElectron_05Oct2015
run data_Run2015D_SinglePhoton_05Oct2015
run data_Run2015D_DoubleMuon_05Oct2015
run data_Run2015D_DoubleEG_05Oct2015
run data_Run2015D_MuonEG_05Oct2015

run data_Run2015D_JetHT_PromptReco
run data_Run2015D_MET_PromptReco
run data_Run2015D_HTMHT_PromptReco
run data_Run2015D_SingleMuon_PromptReco
run data_Run2015D_SingleElectron_PromptReco
run data_Run2015D_SinglePhoton_PromptReco
run data_Run2015D_DoubleMuon_PromptReco
run data_Run2015D_DoubleEG_PromptReco
run data_Run2015D_MuonEG_PromptReco

#
# TTBAR
#

run ttsl_mg_lo_top
run ttsl_mg_lo_tbar
run ttdl_mg_lo

#
# HIGH STATS TTBAR EXTENSION
#

# run ttsl_mg_lo_top_ext1
# run ttsl_mg_lo_tbar_ext1
# run ttdl_mg_lo_ext1

#
# W+JETS
#

# #run wjets_mg_lo
run wjets_ht100to200
run wjets_ht200to400
run wjets_ht400to600
run wjets_ht600to800
run wjets_ht800to1200
run wjets_ht1200to2500
run wjets_ht2500toInf

#
# SINGLE TOP
#

run singletop_powheg_4f_ttchan_l
run singletop_powheg_4f_tbartchan_l
run singletop_amcatnlo_4f_schan
run singletop_powheg_5f_tbarWchan
run singletop_powheg_5f_tWchan

#
# DY+JETS
#

# #run zjets_mg_lo
run dyjetsll_ht100to200
run dyjetsll_ht200to400
run dyjetsll_ht400to600
run dyjetsll_ht600toInf


#
# GAMMA + JETS
#

# run gjet_ht100to200
# run gjet_ht200to400
# run gjet_ht400to600
# run gjet_ht600toInf

#
# Z INVISIBLE
#

run zinv_ht100to200
run zinv_ht200to400
run zinv_ht400to600
run zinv_ht600toInf

#
# DIBOSON
#

run wwlnln_powheg
run wwlnqq_powheg
run wzllln_powheg
run wzllqq_amcnlo
run wzlnnn_amcnlo
run wzlnqq_amcnlo
run zzllll_powheg
run zzllnn_powheg
run zzllqq_amcatnlo
run zzqqnn_amcatnlo

#
# TRIBOSON
#

#
# TTV
#

run ttw_lnu_amcatnlo
run ttw_qq_amcatnlo
run ttz_qq_amcatnlo
run ttz_llnunu_amcatnlo
run ttg_amcatnlo
run tth_nonbb_amcatnlo
run tth_bb_amcatnlo

#
# QCD
#

# run qcd_pt120to170
# run qcd_pt170to300
# run qcd_pt300to470
# run qcd_pt470to600
# run qcd_pt600to800
# run qcd_pt800to1000
# run qcd_pt1000to1400
# run qcd_pt1400to1800
# run qcd_pt1800to2400
# run qcd_pt2400to3200
# run qcd_pt3200toInf

run qcd_ht200to300
run qcd_ht300to500
run qcd_ht500to700
run qcd_ht700to1000
run qcd_ht1000to1500
run qcd_ht1500to2000
run qcd_ht2000toInf

#
# SIGNAL
#

# run T1tttt_1500_100
# run T1tttt_1200_800
# run T1bbbb_1500_100
# run T1bbbb_1000_900
# run T1qqqq_1400_100
# run T1qqqq_1000_800

# fastsim v1
run T2-4bd_375_295to365
run T2-4bd_275_195to265

# fastsim v2
run T2-4bd_300_220to290
run T2-4bd_325_245to315
run T2-4bd_400_320to390
run T5qqqqWW_1025to1200_0to1175
run T5qqqqWW_1225to1400_0to1175
run T5qqqqWW_1425to1600_0to1175
