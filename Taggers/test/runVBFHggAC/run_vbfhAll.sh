#!/bin/bash

storageDir="/eos/cms/store/group/phys_higgs/cmshgg/emanuele/vbfhgg/HiggsCouplings/TreesInclusive_2024_04_15"
outDir="hggAC_Run2"
YEAR="2016preVFP"
samples="signal"

usage(){
    echo "Script to submit jobs. You can submit year-by-year or all years together."
    echo "-y|--year (default is 2016preVFP"
    echo "-d|--outdir (default is hggAC_Run2)"
    echo "-s|--samples (default is signal)"
}
# options may be followed by one colon to indicate they have a required argument
if ! options=$(getopt -u -o y:d:s:h -l help,year:,dir:,samples: -- "$@")
then
# something went wrong, getopt will put out an error message for us
exit 1
fi
set -- $options
while [ $# -gt 0 ]
do
case $1 in
-h|--help) usage; exit 0;;
-y|--year) YEAR=$2; shift ;;
-d|--dir) outDir=$2; shift ;;
-s|--samples) samples=$2; shift ;;
(--) shift; break;;
(-*) usage; echo "$0: error - unrecognized option $1" 1>&2; usage >> /dev/stderr; exit 1;;
(*) break;;
esac
shift
done

echo "Submitting jobs for year $YEAR"
afsdir=${outDir}_${samples}_${YEAR}

case $samples in 
    "signal")
        json="sig_jobs_${YEAR}_UL.json"
        ;;
    "background")
        json="bkg_jobs_${YEAR}_UL.json"
        ;;
    "data")
        json="data_jobs_${YEAR}_UL.json"
        ;;
    *)
        json="dummy"
        echo "unknown sample json (should be signal/background/data"
        ;;
esac

echo "creating directory on storage dir: ${storageDir}/${afsdir}"
echo "condor, log files will be in ${afsdir}"
mkdir -p ${storageDir}/${afsdir}

echo "running now fggRunJobs.py..."
fggRunJobs.py --load $CMSSW_BASE/src/flashgg/Systematics/test/runAnomCouplings/${json} -d ${afsdir} -x cmsRun ../vbfhgg_ac_dumper.py metaDataSrc=flashgg --nCondorCpu=5 pujidWP=tight maxEvents=-1 --stage-to=${storageDir}/${afsdir} -q workday -n 100 -H --no-copy-proxy --no-use-tarball & # --resubmit-missing --cont --max-resubmissions=10 &"

