#pragma once
void CalcEarnings(Node* PtrNode);
void stateTree2HStar(Tree *Tree);
bool InDone(Tree *Tree, PtrNodeType BackNode);
bool InNotDone(Tree *Tree, PtrNodeType BackNotDoneNode);
void CalcDeadLockH(Tree *Tree);
void NotDoneSort(Tree *Tree, PtrNodeType BackNode);
void DeleteNotDone(Tree *Tree, PtrNodeType BackNode);
PtrNodeType TwinToBackDone(Tree *Tree, PtrNodeType BackNode);
