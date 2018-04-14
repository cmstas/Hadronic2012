#!/bin/bash

make all

INDIR=/nfs-6/userdata/dpgilber/MT2_ST_Friends_incl_skim
INDIR_UNSKIMMED=/nfs-6/userdata/dpgilber/MT2_ST_Friends
# bitwise: <doWZpt><doNtMin><doEta><doNj><doLep><doMT2><doDphiDiff><doHTMET><doHT>
# if any bits are high, do Nj > 0
#SELECTION=000000 # Inclusive
#SELECTION=000001 # HT
#SELECTION=000011 # HTMET, same behavior as 00010 = MET
#SELECTION=000111 # HTMETDphiDiff
#SELECTION=001111 # HTMETDphiDiffMT2
#SELECTION=011111 # HTMETDphiDiffMT2Lep
#SELECTION=100000 # Nj > 1
LOGDIR=logs

# 0 = SR, 1 = CRQCD, 2 = CRSL, 3 = CRDY
#REGION=1

mkdir -p ${LOGDIR}

#declare -a REGIONS=(0 1 2 3)
declare -a REGIONS=(2)
#declare -a REGIONS=(0 1)
#declare -a REGIONS=(2 3)
#declare -a SELECTIONS=(0) # inclusive
#declare -a SELECTIONS=(0 01000) # MT2
#declare -a SELECTIONS=(0 010000) # Leptons
#declare -a SELECTIONS=(0 10001) # Leptons and HT
#declare -a SELECTIONS=(0 110000) # Leptons and Nj > 1
#declare -a SELECTIONS=(0 1010001) # HTLepEta
#declare -a SELECTIONS=(0 0010001 1 0010011) # HTMETLep HTLep HT
declare -a SELECTIONS=(0 00010001 10000) # HTLep, Lep
declare -a Samples=(ttsl_fromT ttsl_fromTbar wjets_incl zinv_zpt100to200 zinv_zpt200toInf qcd_ht300to500 qcd_ht500to700 qcd_ht700to1000 qcd_ht1000to1500 qcd_ht1500to2000_ext1 qcd_ht2000toInf dyjetstoll_incl_ext1 ttdl)
#declare -a Samples=(ttdl)
#declare -a Samples=(wjets_incl)

for SELECTION in ${SELECTIONS[@]}; do
    for REGION in ${REGIONS[@]}; do
	for SAMPLE in ${Samples[@]}; do
	    echo "nohup nice -n 10 ./ShortTrackType.exe ${INDIR} ${SAMPLE} ${INDIR_UNSKIMMED} ${SELECTION} ${REGION} >& ${LOGDIR}/${SAMPLE}_${SELECTION}_${REGION}.log &"
	    eval "nohup nice -n 10 ./ShortTrackType.exe ${INDIR} ${SAMPLE} ${INDIR_UNSKIMMED} ${SELECTION} ${REGION} >& ${LOGDIR}/${SAMPLE}_${SELECTION}_${REGION}.log &"
	done
    done
done
