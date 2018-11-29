#!/bin/bash

make -j 12 || return $?

LOGDIR=logs/
mkdir -p ${LOGDIR}

doD16=0
doM16=0
doD17=1
doM17=1

#tag=fsvarDefault_weight1
#tag=fsvarHT250_weight1
#tag=fsvarHT450_weight1
#tag=fsvarMET30_weight1
#tag=fsvarMET100_weight1
#tag=fsvarMET250_weight1
#tag=fsvarHT450MET100_weight1

tag=4_fsvarDefault_weight1

# 2016 MC
if [ "$doM16" -eq "1" ]; then
    OUTDIR=output_unmerged/2016_${tag}
    mkdir -p ${OUTDIR}
    CONFIG=mc_94x_Summer16
    INDIR=/nfs-6/userdata/dpgilber/mt2babies/mc_2016_loose
    declare -a Samples=(ttsl ttdl singletop qcd ttX dy wjets zinv ww)
    
    for SAMPLE in ${Samples[@]}; do
	command="nohup nice -n 10 ./ShortTrackLooper.exe ${OUTDIR}/${SAMPLE} ${INDIR}/${SAMPLE} ${CONFIG} ${tag} >& ${LOGDIR}/log_${SAMPLE}_2016.txt &"
	echo $command
	eval $command
    done
fi

# 2016 data
if [ "$doD16" -eq "1" ]; then
    OUTDIR=output_unmerged/2016_${tag}/data
    mkdir -p ${OUTDIR}
    CONFIG=data_2016_94x
    INDIR=/nfs-6/userdata/dpgilber/mt2babies/data_2016_loose
    declare -a Samples=(data_Run2016B data_Run2016C data_Run2016D data_Run2016E data_Run2016F data_Run2016G data_Run2016H)
    
    for SAMPLE in ${Samples[@]}; do
	command="nohup nice -n 10 ./ShortTrackLooper.exe ${OUTDIR}/${SAMPLE} ${INDIR}/${SAMPLE} ${CONFIG} ${tag} >& ${LOGDIR}/log_${SAMPLE}.txt &"
	echo $command
	eval $command
    done
fi


#2017 MC
if [ "$doM17" -eq "1" ]; then
    OUTDIR=output_unmerged/2017_${tag}
    mkdir -p ${OUTDIR}
    CONFIG=mc_94x_Fall17
    INDIR=/nfs-6/userdata/dpgilber/mt2babies/mc_2017_loose
    declare -a Samples=(ttsl ttdl singletop qcd ttX dy gjets wjets zinv multiboson)
    
    for SAMPLE in ${Samples[@]}; do
	command="nohup nice -n 10 ./ShortTrackLooper.exe ${OUTDIR}/${SAMPLE} ${INDIR}/${SAMPLE} ${CONFIG} ${tag} >& ${LOGDIR}/log_${SAMPLE}_2016.txt &"
	echo $command
	eval $command
    done
fi

# 2017 data
if [ "$doD17" -eq "1" ]; then
    OUTDIR=output_unmerged/2017_${tag}/data
    mkdir -p ${OUTDIR}
    CONFIG=data_2017_31Mar2018
    INDIR=/nfs-6/userdata/dpgilber/mt2babies/data_2017_loose
    declare -a Samples=(data_Run2017B data_Run2017C data_Run2017D data_Run2017E data_Run2017F)
    
    for SAMPLE in ${Samples[@]}; do
	command="nohup nice -n 10 ./ShortTrackLooper.exe ${OUTDIR}/${SAMPLE} ${INDIR}/${SAMPLE} ${CONFIG} ${tag} >& ${LOGDIR}/log_${SAMPLE}.txt &"
	echo $command
	eval $command
    done
fi