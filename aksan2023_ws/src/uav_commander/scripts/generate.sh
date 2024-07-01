#!/bin/bash

FILENAME=$(rospack find uav_commander)/pilot_files/$1
URUTAN[0]=$2
URUTAN[1]=$3
URUTAN[2]=$4
ELP[0]=$5
ELP[1]=$6

GRID1=(-3.30 1.03 -3.25 2.57 -3.18 4.20 -3.55 5.80)
GRID2=(-1.76 0.82 -1.70 2.48 -1.46 4.24 -1.52 5.80 -1.70 7.20)
GRID3=(-0.18 0.70 0.02 2.24 0.11 3.92 0.10 5.83)
GRID4=(1.67 0.40 1.85 2.10 1.97 3.90 2.10 5.55 1.70 7.08)
GRID5=(3.51 0.16 3.53 1.90 3.63 3.67 3.83 5.05)

echo "FILENAME=$FILENAME"

rm $FILENAME
echo "indoorInitialize; m;" | tee -a $FILENAME
echo "switchMode; m 1 strings GUIDED;" | tee -a $FILENAME
echo "armThrottle; m;" | tee -a $FILENAME
echo "takeoff; m 1 doubles 3.0;" | tee -a $FILENAME
echo "indoorGoTo; m 1 strings ${URUTAN[0]};" | tee -a $FILENAME
echo "loiterDZ; m 1 strings ${URUTAN[0]};" | tee -a $FILENAME
echo "wait; m 1 doubles 1.0;" | tee -a $FILENAME
echo "indoorGoTo; m 1 strings ${URUTAN[1]}; m 2 bools false true;" | tee -a $FILENAME
echo "loiterDZ; m 1 strings ${URUTAN[1]};" | tee -a $FILENAME
echo "wait; m 1 doubles 1.0;" | tee -a $FILENAME
echo "indoorGoTo; m 1 strings ${URUTAN[2]}; m 2 bools false true;" | tee -a $FILENAME
echo "loiterDZ; m 1 strings ${URUTAN[2]};" | tee -a $FILENAME
echo "wait; m 1 doubles 1.0;" | tee -a $FILENAME

ELPBASE=$(( $((${ELP[1]} - 1)) * 2))
GRIDNAMEX="GRID${ELP[0]}[$ELPBASE]"
GRIDNAMEY="GRID${ELP[0]}[$((ELPBASE+1))]"
ELPX=${!GRIDNAMEX}
ELPY=${!GRIDNAMEY}

echo "indoorGoTo; m 3 doubles $ELPX $ELPY 3.0;" | tee -a $FILENAME
echo "precLand; m 1 bools true;" | tee -a $FILENAME
exit 0
