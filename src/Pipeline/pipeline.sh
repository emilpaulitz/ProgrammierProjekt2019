#!/bin/bash
# usage: ./pipeline.sh [read1] [read2] [ref]
# ./pipeline.sh ~/Desktop/Data/NA12878_03_AACGTGAT_L001_R1_001.fastq.gz ~/Desktop/Data/NA12878_03_AACGTGAT_L001_R2_001.fastq.gz ~/Desktop/Data/GRCh37.fa


# clear old cache
#./empty-cache.sh
# make alias for colourful echoing progress
#alias cecho='f(){ echo -e "\e[33m$@  \e[0m";  unset -f f; }; f'

# copy data to cache
echo -e "\e[33m "copying data... \e[0m"
cp $1 cache/read1.fastq.gz
cp $2 cache/read2.fastq.gz
cp $3* cache
echo -e "\e[33m "done \e[0m"

echo -e "\e[33m "adding references... \e[0m"
READ1=$PWD/cache/read1.fastq.gz
READ2=$PWD/cache/read2.fastq.gz
REF=$PWD/cache/GRCh37.fa
echo -e "\e[33m "done \e[0m"

## [.fastQ]
#adapter trimming <SeqPurge>
echo -e "\e[33m "adapter trimming... \e[0m"
~/miniconda3/bin/SeqPurge -in1 $READ1 -in2 $READ2 -out1 cache/R1_purged.fastq.gz -out2 cache/R2_purged.fastq.gz
READ1=$PWD/cache/R1_purged.fastq.gz
READ2=$PWD/cache/R2_purged.fastq.gz
echo -e "\e[33m "done \e[0m"


#mapping <bwa>
echo -e "\e[33m "mapping... \e[0m"
cd bwa
./bwa index $REF
./bwa mem $REF $READ1 $READ2 > ../cache/aligned.sam
cd ..
echo -e "\e[33m "done \e[0m"
## [.sam]

#duplicate removal <samblaster>
samblaster/samblaster -M --removeDups -i cache/aligned.sam > cache/dupsRemoved.sam

#convert sam to bam <samtools> sam2bam sort index
echo -e "\e[33m "converting sam->bam... \e[0m"
cd cache
samtools view -ub dupsRemoved.sam -o converted.bam
samtools sort converted.bam -o sorted.bam
samtools index sorted.bam
BAM=$PWD/sorted.bam
cd ..
echo -e "\e[33m "done \e[0m"
## [.bam]

#indel realignment <ABRA2>
echo -e "\e[33m "indel realignment... \e[0m"
TARGET=$PWD/../../data/target_region.bed
java -Xmx4G -jar abra2/temp/abra-0.94b.jar --ref $REF --in $BAM --out cache/indel.bam --working cache/tmpAbra --targets $TARGET
BAM=$PWD/cache/indel.bam
echo -e "\e[33m "abra cadabra done \e[0m"

#variant calling <freebayes>
## [.vcf]
echo -e "\e[33m "variant calling... \e[0m"
freebayes -f $REF $BAM > cache/free.vcf
echo -e "\e[33m "done \e[0m"

# variant normalization <vcfallelicprimitives>
# usage: vcfallelicprimitives [options][file]
echo -e "\e[33m "variant normalization... \e[0m"
~/miniconda3/pkgs/vcflib-1.0.0_rc3-py37hc088bd4_0/bin/vcfallelicprimitives -k cache/free.vcf > cache/norm.vcf
echo -e "\e[33m "done \e[0m"

# break multi allelic variants <vcfbreakmulti>
# usage: vcfbreakmulti [options][file]
echo -e "\e[33m "break multi allelic variants"
./ngs-bits-master/bin/VcfBreakMulti -in cache/norm.vcf -out cache/break.vcf
echo -e "\e[33m "done \e[0m"

# left-align variants <VcfLeftNormalize>
echo -e "\e[33m "left-align variants"
./ngs-bits-master/bin/VcfLeftNormalize -in cache/break.vcf -out cache/leftvar.vcf -ref $REF
echo -e "\e[33m "done \e[0m"
