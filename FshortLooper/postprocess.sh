#!/bin/bash

if [ "$#" -eq 0 ]; then
    echo "Need a tag"
    return
fi

tag=$1

declare -a inputs=(data_2017_${tag}.root mc_2017_${tag}.root data_2016_${tag}.root mc_2016_${tag}.root)
#declare -a inputs=(data_2017_${tag}.root data_2016_${tag}.root)

for input in ${inputs[@]}; do
    command="nohup python calculate_TFs.py output_merged/${input} &> /dev/null &"
    eval $command
    command="nohup python ewk_dists.py output_merged/${input} &> /dev/null &"
    eval $command
    command="nohup python ewk_contam.py output_merged/${input} &> /dev/null &"
    eval $command
done