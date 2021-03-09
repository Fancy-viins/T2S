#pragma once
#define M0_path  "D:\\work\\vs2019程序\\TimeNet2stateTree\\Data\\m0.txt"
#define Delay_path "D:\\work\\vs2019程序\\TimeNet2stateTree\\Data\\delay.txt"
#define GoalPlace_path "D:\\work\\vs2019程序\\TimeNet2stateTree\\Data\\GoalPlace.txt"
#define GoalMarking_path "D:\\work\\vs2019程序\\\TimeNet2stateTree\\Data\\\GoalMarking.txt"

void DataRead(short place_num, short M0[], float Delay[], Tree *Tree);
void DataRead_v2(short place_num, short M0[], float Delay[], Tree *Tree);