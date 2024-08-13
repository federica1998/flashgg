#!/bin/bash

storageDir="/afs/cern.ch/user/f/fderiggi/work/testv/Tree"
outDir=$1
if [[ -z $outDir ]]; then
    echo "usage: $0 <outDir>"
    exit -1
fi
year2016preVFPDir="data_IA_UL16preVFP"
year2016postVFPDir="data_IA_UL16postVFP"
year2017Dir="data_IA_UL17"
year2018Dir="data_IA_UL18"

mkdir -p ${storageDir}/${outDir}_${year2016preVFPDir}
fggRunJobs.py --load data_jobs_2016preVFP_UL.json -d ${outDir}_${year2016preVFPDir} -x cmsRun vbfhgg_ac_dumper.py metaDataSrc=flashgg doSystematics=False  --nCondorCpu=2 --no-use-tarball pujidWP=tight maxEvents=-1 --stage-to=${storageDir}/${outDir}_${year2016preVFPDir} -q workday -n 500 -H --no-copy-proxy --max-resubmissions=10 &

#mkdir -p ${storageDir}/${outDir}_${year2016postVFPDir}
#fggRunJobs.py --load data_jobs_2016postVFP_UL.json -d ${outDir}_${year2016postVFPDir} -x cmsRun vbfhgg_ac_dumper.py metaDataSrc=flashgg doSystematics=False  --nCondorCpu=2 --no-use-tarball pujidWP=tight maxEvents=-1 --stage-to=${storageDir}/${outDir}_${year2016postVFPDir} -q workday -n 500 -H --no-copy-proxy --max-resubmissions=10 &

#mkdir -p ${storageDir}/${outDir}_${year2017Dir}
#fggRunJobs.py --load data_jobs_2017_UL.json -d ${outDir}_${year2017Dir} -x cmsRun vbfhgg_ac_dumper.py metaDataSrc=flashgg doSystematics=False   --nCondorCpu=2 --no-use-tarball pujidWP=tight maxEvents=-1 --stage-to=${storageDir}/${outDir}_${year2017Dir} -q workday -n 500 -H --no-copy-proxy --max-resubmissions=10 &

#mkdir -p ${storageDir}/${outDir}_${year2018Dir}
#fggRunJobs.py --load data_jobs_2018_UL.json -d ${outDir}_${year2018Dir} -x cmsRun vbfhgg_ac_dumper.py metaDataSrc=flashgg  doSystematics=False   --nCondorCpu=2 --no-use-tarball pujidWP=tight maxEvents=-1 --stage-to=${storageDir}/${outDir}_${year2018Dir} -q workday -n 500 -H --no-copy-proxy --max-resubmissions=10 &
