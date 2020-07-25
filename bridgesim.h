#include "bridge.h"
bool comp(Lan* x, Lan* y);
bool comp2(Bridge* x, Bridge* y);
void span_tree (bool trace, int& time1,vector<Bridge*>& ab,vector<Lan*>& al, map<string,Node*>& an);

void transfer_packets(Node* a,Node* b,bool trace, int& time1,vector<Bridge*>& ab,vector<Lan*>& al, map<string,Node*>& an);