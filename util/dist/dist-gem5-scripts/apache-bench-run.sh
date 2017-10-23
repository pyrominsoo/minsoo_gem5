#! /bin/bash

# Authors: Mohammad Alian <malian2@illinois.edu>
# sample run script for launchin ab
#

GEM5_DIR=$(pwd)/$(dirname $0)/../../..

IMG=$M5_PATH/disks/aarch64-ubuntu-trusty-headless.img
VMLINUX=$M5_PATH/binaries/vmlinux.aarch64.20140821
DTB=$M5_PATH/binaries/vexpress.aarch64.20140821.dtb

FS_CONFIG=$GEM5_DIR/configs/example/fs.py
SW_CONFIG=$GEM5_DIR/configs/dist/sw.py
GEM5_EXE=$GEM5_DIR/build/ARM/gem5.opt

BOOT_SCRIPT=$GEM5_DIR/util/dist/apache-bench/run.ab.rcS
GEM5_DIST_SH=$GEM5_DIR/util/dist/gem5-dist.sh

DEBUG_FLAGS="--debug-flags=DistEthernet"
CHKPT_RESTORE="-r1"

CKPTDIR=$(pwd)
RUNDIR=$(pwd)/rundir
NNODES=2

$GEM5_DIST_SH -n $NNODES                                                     \
              -x $GEM5_EXE                                                   \
              -c $CKPTDIR                                                    \
              -r $RUNDIR                                                     \
              -s $SW_CONFIG                                                  \
              -f $FS_CONFIG                                                  \
              --m5-args                                                      \
                 $DEBUG_FLAGS                                                \
              --fs-args                                                      \
                  --cpu-type=AtomicSimpleCPU                                 \
		          --num-cpus=1                                               \
                  --machine-type=VExpress_EMM64                              \
                  --disk-image=$IMG                                          \
                  --kernel=$VMLINUX                                          \
                  --dtb-filename=$DTB                                        \
                  --script=$BOOT_SCRIPT                                      \
              --cf-args                                                      \
                  $CHKPT_RESTORE

