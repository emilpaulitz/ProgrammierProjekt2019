#!/bin/bash
# pipeline.sh

# call: pipeline.sh [reads] [ref]
# needs tools installed: bwa, freebayes, vcfallelicprimitives, samtools

READS=$1
REF=$2

# call bwa #TODO map, remove duplicates, indel-realignment
echo "#call bwa"
cd bwa
./bwa index $REF
./bwa mem $REF $READS > ../cache/mapped.sam
cd ..

# convert sam to bam file
echo "#convert .sam to .bam"
cd samtools-1.9
./samtools view -b ../cache/mapped.sam > ../cache/mapped.bam
cd ..

# Variant calling
echo "#variant calling"
BAM=../cache/mapped.bam
cd freebayes-1.3.1
freebayes -f $REF $BAM > ../cache/var.vcf
cd ..
echo "#done"

############################################################

## fastQ
#adapter trimming <SeqPurge>
#mapping <bwa>
#duplicate removal <samblaster>
#indel realignment <ABRA2>

#convert sam to bam <samtools>
## .bam

#variant calling <freebayes>
## vcf
#normalize <vcfallelicprimitives>
#left-align <VcfLeftNormalize> <vcfallelicprimitives>?
