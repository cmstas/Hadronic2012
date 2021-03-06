#!/bin/bash

#copy input files
#cp /nfs-7/userdata/bemarsh/mt2_limit_input/job_input.tar.gz .
cp /nfs-7/userdata/bemarsh/mt2_limit_input/job_input.tar.gz .
cp ../../babymaker/data/xsec_susy_13tev_run2.root .

#checkout PlotsSMS package
git clone git@github.com:bjmarsh/PlotsSMS.git

#put modified sms.py and model config files into PlotsSMS area
cp sms.py PlotsSMS/python
mkdir -p PlotsSMS/config/mt2
cp cfg/*_mt2.cfg PlotsSMS/config/mt2

#set environment
source /cvmfs/cms.cern.ch/cmssw/cmsset_default.sh > /dev/null 2>&1
export SCRAM_ARCH=slc6_amd64_gcc530 > /dev/null
pushd /cvmfs/cms.cern.ch/slc6_amd64_gcc530/cms/cmssw/CMSSW_8_1_0 > /dev/null
eval `scramv1 runtime -sh`
popd > /dev/null
