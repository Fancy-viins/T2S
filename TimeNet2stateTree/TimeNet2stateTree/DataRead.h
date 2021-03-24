#pragma once
#define M0_path  "F:\\github\\T2S\\TimeNet2stateTree\\Data\\m0.txt"
#define Delay_path "F:\\github\\T2S\\TimeNet2stateTree\\Data\\delay.txt"
#define GoalPlace_path "F:\\github\\T2S\\TimeNet2stateTree\\Data\\GoalPlace.txt"
#define GoalMarking_path "F:\\github\\T2S\\TimeNet2stateTree\\Data\\\GoalMarking.txt"

void DataRead(short place_num, short M0[], float Delay[], Tree *Tree);
void DataRead_v2(short place_num, short M0[], float Delay[], Tree *Tree);