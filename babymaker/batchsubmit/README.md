
# Running MT2 Looper In Batch Mode and Processing Babies

## Environment setup

See `MT2Analysis/README.txt`.  This setup sends the compiled libraries with the job so assumes that you're using a particular CMSSW/root version.

## Prepare job input files

Copy files to run looper into `job_input` directory
for example, from the `babymaker` directory
``` bash
cp -r *.so jetCorrections jsons btagsf lepsf data processBaby batchsubmit/job_input/
```
*** note that after copying the latest source files into the job_input subdir, you must run one of the writeConfig scripts below to recreate the input tarball which is used for the batch jobs!

## Setup writeConfig.sh scrip

Modify `writeConfig.sh` script for personal setup. Variables that should be modified by the user are
PROXY (not nedded anymore unless you have a special location for your proxy file)
COPYDIR to point to the desired output directory in hadoop ( default to `/hadoop/cms/store/user/${USERNAME}/mt2babies/`) where $USERNAME is your username

## Write condor configurations

to run on only one dataset for example run the `writeConfig.sh` script 
this takes two arguments, the dataset directory on hadoop and the name
you want to give the output babies and the output directory. 
for example
``` bash
 ./writeConfig.sh /hadoop/cms/store/group/snt/csa14/MC_CMS3_V07-00-03/TTJets_MSDecaysCKM_central_Tune4C_13TeV-madgraph-tauola/merged/ V00-00-01_TTJets
```
creates a condor config file
`condor_V00-00-01_TTJets.cmd`
to submit one job per file in the dataset directory 

Note, need to setup voms proxy since apparently this is needed to copy output files at the end of the job.
something like
``` bash
voms-proxy-init -voms cms -valid 240:00
```
now submit to condor
``` bash
condor_submit <CMDFILE>
```
check status 
``` bash
condor_q <USERNAME>
```
if jobs are listed as held ("H"):
``` bash
condor_release <USERNAME>
```
select datasets to run on in writeAllConfig.sh and execute
``` bash
./writeAllConfig.sh
```
This should create a set of .cmd files and a submit script submitAll.sh
``` bash
./submitAll.sh
```

the job .out and .err files should be located in the job_logs directory 
the submission log should be in submit_logs

## Verify outputs and resubmit as needed

To verify that jobs ran and produced all the output files, first run sweepRoot to check all output root files.
``` bash
git clone git@github.com:cmstas/NtupleTools.git
cd NtupleTools/condorMergingTools/libC
make
./sweepRoot -b -o "mt2" /hadoop/cms/store/user/${USER}/mt2babies/<BABYDIRS>/*.root
```
where <BABYDIRS> is something like V00-00-01_*

Delete the files reported as bad, then run checkAllConfig to see which output files are missing:
``` bash
./checkAllConfig.sh <CONFIGDIR>
```
where <CONFIGDIR> is something like `configs_V00-00-01/`

This creates resubmit configs for just the missing jobs, with names `*_resubmit.cmd`, in a new directory <CONFIGDIR>_resubmit.
To create the resubmit file for a single config:
``` bash
python checkConfig.py <CMDFILE>
```
Then submit the jobs again as before:
``` bash
condor_submit <NEWCMDFILE>
```

Using a bash for loop can be useful here:
``` bash
for i in `/bin/ls <CONFIGDIR>_resubmit`; do condor_submit $i; done
```


You may have to iterate this process to get all jobs to converge.

## Merge babies

Once the jobs are done, merge the output with the mergeHadoopOutput script
You can select which datasets to merge by editing the script below, then run it.
Note that all the merge jobs run locally in parallel, so you may not want to merge
everything at once
``` bash
./mergeHadoopFiles.sh
```
You can also specify the output directory in the script. Typically the babies are
stored under:
``` bash
/nfs-6/userdata/mt2/<VERSION>/
```

## Merge samples with extended statistics

Some MC samples have been produced in multiple datasets, that cover the exact same phase space but are statistically independent.
For example, in `writeAllConfig25nsMiniAODv2.sh` the samples `ttsl_mg_lo_top` and `ttsl_mg_lo_top_ext1` are defined.

We have a script to merge these and fix the `evt_scale1fb` variable to properly account for the full statistics of the merged sample:
``` bash
/nfs-6/userdata/mt2/mergeFixScale1fb.C
```
with a wrapper bash script to call this for multiple samples:
``` bash
/nfs-6/userdata/mt2/do_ext_merge.sh
```
Typically we create an additional subdirectory to hold these babies with the extensions merged in, like:
``` bash
/nfs-6/userdata/mt2/<VERSION>/extmerge/
```
To ensure that directory has a complete set of all babies, we can also use the script below to make soft links
to the remaining babies that didn't have extensions:
``` bash
/nfs-6/userdata/mt2/make_links_extmerge.sh
```

## Skim babies

For the standard MT2 analysis results, we apply a skim (i.e. remove some events) with a selection loose enough
to retain all of the signal region and control region events.

The script that does the skimming is here on the UAF:
``` bash
/nfs-6/userdata/mt2/skim_base_mt2_Zinv_v6_JECs.C
```

And we have a wrapper bash script to run this on multiple samples:
``` bash
/nfs-6/userdata/mt2/do_skim.sh
```
The directory also contains other skimming scripts for specific purposes.





#################################################################################
#                                                                               #
#   Instructions for running MT2 baby making within the Project Metis framework #
#                                                                               #
#################################################################################

1. Get Project Metis and mt2 babymaking submissions scripts
``` bash
source metis_setup.sh
```

2. Edit the datasets you wish to run on inside the appropriate ProjectMetis/examples/mt2baby*.py submissions scripts, point mt2home towards your base MT2Analysis directory, choose the tag for this babymaking run, and set the output directory for the unmerged babies (hadoop) and the merged babies (nfs). Metis will run on the most recent CMS4 version of this dataset by default. If you want to force a different tag, uncommented the 'tag = "CMS4_X_Y_Z"' line and set it to to the desired version.

3. Make a tar file of inputs for Metis
``` bash
source createTarFile.sh
```

4. Metis feeds its own generalized inputs the exectuable, so we can't use MT2's wrapper.sh. There is a separate metis_executable.sh that interfaces between Metis and processBaby. If you need to make any edits to the workflow (for example, maybe you edited the arguments taken by processBaby, or want to do rebalance and smear regardless of whether the output name contains "RebalanceAndSmear"), edit this file, not wrapper.sh.

5. Run Metis
``` bash
cd ProjectMetis
nohup python examples/my_mt2baby_submission_script.py &> metis.log &
```

Remember when using Metis to delete the corresponding tasks directory if you make a rerun on the same dataset. Otherwise, it will re-load the same old job from backup and execute the same thing over again.

When checking progress in the browser, you may have to clear the cache.