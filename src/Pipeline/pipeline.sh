#!/bin/bash
# usage: ./pipeline.sh [read1] [read2] [ref] [WD]
# ./pipeline.sh ~/Desktop/Data/NA12878_03_AACGTGAT_L001_R1_001.fastq.gz ~/Desktop/Data/NA12878_03_AACGTGAT_L001_R2_001.fastq.gz ~/Desktop/Data/GRCh37.fa

# clear old cache
#./empty-cache.sh
# make alias for colourful echoing progress
#alias cecho='f(){ echo -e "\e[33m$@ ";  unset -f f; }; f'

# copy data to cache
echo "copying data..."
cp $1 cache/read1.fastq.gz
cp $2 cache/read2.fastq.gz
cp $3* cache
echo "done"

echo "adding references..."
READ1=$PWD/cache/read1.fastq.gz
READ2=$PWD/cache/read2.fastq.gz
REF=$PWD/cache/GRCh37.fa

## [.fastQ]
#adapter trimming <SeqPurge>
echo "adapter trimming..."
~/miniconda3/bin/SeqPurge -in1 $READ1 -in2 $READ2 -out1 cache/R1_purged.fastq.gz -out2 cache/R2_purged.fastq.gz
READ1=$PWD/cache/R1_purged.fastq.gz
READ2=$PWD/cache/R2_purged.fastq.gz


#mapping <bwa>
echo "mapping..."
cd bwa
./bwa index $REF
./bwa mem $REF $READ1 $READ2 > ../cache/aligned.sam
cd ..
## [.sam]

#duplicate removal <samblaster>
echo "duplicate removal..."
samblaster/samblaster -M --removeDups -i cache/aligned.sam > cache/dupsRemoved.sam

#convert sam to bam <samtools> sam2bam sort index
echo "converting sam->bam..."
cd cache
samtools view -ub dupsRemoved.sam -o converted.bam
samtools sort converted.bam -o sorted.bam
samtools index sorted.bam
BAM=$PWD/sorted.bam
cd ..
## [.bam]

#indel realignment <ABRA2>
echo "indel realignment..."
TARGET=$PWD/../../data/target_region.bed
java -Xmx4G -jar abra2/temp/abra-0.94b.jar --ref $REF --in $BAM --out cache/indel.bam --working cache/tmpAbra --targets $TARGET
BAM=$PWD/cache/indel.bam
echo "abra cadabra done"

#variant calling <freebayes>
## [.vcf]
echo "variant calling..."
freebayes -f $REF $BAM > cache/free.vcf

# variant normalization <vcfallelicprimitives>
# usage: vcfallelicprimitives [options][file]
echo "variant normalization..."
~/miniconda3/pkgs/vcflib-1.0.0_rc3-py37hc088bd4_0/bin/vcfallelicprimitives -k cache/free.vcf > cache/norm.vcf

# break multi allelic variants <vcfbreakmulti>
# usage: vcfbreakmulti [options][file]
echo "break multi allelic variants..."
./ngs-bits-master/bin/VcfBreakMulti -in cache/norm.vcf -out cache/break.vcf

# left-align variants <VcfLeftNormalize>
echo "left-align variants..."
./ngs-bits-master/bin/VcfLeftNormalize -in cache/break.vcf -out cache/leftvar.vcf -ref $REF

# sort <VcfSort>
echo "sort vcf file..."
./ngs-bits-master/bin/VcfSort -in cache/leftvar.vcf -out cache/final.vcf
echo "done"
