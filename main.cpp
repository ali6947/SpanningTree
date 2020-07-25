#include "bridgesim.h"
#include<iostream>
#include<string>
#include <vector>
#include <map>
#include<algorithm>
using namespace std;


vector<string> split(string s, string delimiter){
	size_t pos = 0;
	vector<string> ans;
	string token;
	while ((pos = s.find(delimiter)) != string::npos) {
    token = s.substr(0, pos);
    ans.push_back(token);
    s.erase(0, pos + delimiter.length());
	}
	token = s.substr(0, pos);
    ans.push_back(token);
	return ans;
}

int main(){
	vector<Bridge*> ab;
vector<Lan*> al;
map<string,Node*> an;
map<int,bool> nodec;
int time1=0;
	al.resize(26);
	int nlans=0; // index of largest lan
for(int i=0;i<26;i++){
	Lan* ty1 = new Lan();
	al[i]=ty1;
	al[i]->name=i;
}
	bool trace;
	int numb;
	string cc,dd;
	getline(cin,cc);
	getline(cin,dd); 
	trace=(cc=="1");
	numb=stoi(dd); //number may have more than 1 digit, correct
	for(int i=0;i<numb;i++){
		string dt;
		getline(cin,dt);
		
		if(dt.size()>0){
		vector<string> jj=split(dt,":");
		Bridge* ty = new Bridge(stoi(jj[0].substr(1)));
		ab.push_back(ty);
		for(int k=1;k<jj[1].size();k+=2){
			int po=jj[1][k]-'A';
			//nlans=max(nlans,po);
			if(nodec.count(po)==0){ nodec[po]=true; nlans++;}
			(al[po]->bridges).push_back(ty);
			(ty->ports).push_back(al[po]);
		}
	}
	}
	//flush(cout);
	span_tree(trace,time1,ab,al,an);
	// for (int i = 0; i < ab.size(); i++)
	// {
	// 	//cout<<ab[i]->gen_msg;
	// 	// if(ab[i]->parent==NULL){cout<<"root ";
	// 	// cout<<ab[i]->root->name<<" "<<ab[i]->dist<<"\n";}
	// 	// else{
	// 	// 	cout<<ab[i]->name<<" "<<ab[i]->root->name<<" "<<ab[i]->dist<<" "<<ab[i]->parent->name<<" "<<((char)((ab[i]->root_port)->name+65))<<"\n";
	// 	// }cout<<"the deactive_ports:\n";
	// 	// for(int j=0;j<ab[i]->deactive_ports.size();j++){
	// 	// 	cout<<((char)((ab[i]->deactive_ports)[j]->name+65))<<" ";
	// 	// }
	// 	// cout<<"\n";
	// }: C-NP F-RP E-DP
	//sort(ab.begin(), ab.end(),comp2);
	for(int i=0;i<ab.size();i++){
		cout<<"B"<<ab[i]->name<<":";
		sort((ab[i]->ports).begin(), (ab[i]->ports).end(),comp);
		for(int j=0;j<ab[i]->ports.size();j++){
			if((ab[i]->ports)[j]==ab[i]->root_port){
				cout<<" "<<((char)((ab[i]->ports)[j]->name+65))<<"-RP";
			}
			else if(find((ab[i]->deactive_ports).begin(), (ab[i]->deactive_ports).end(),(ab[i]->ports)[j])==(ab[i]->deactive_ports).end()){
				cout<<" "<<((char)((ab[i]->ports)[j]->name+65))<<"-DP";	
			}
			else{
				cout<<" "<<((char)((ab[i]->ports)[j]->name+65))<<"-NP";		
			}
		}
		cout<<"\n";
	}
	// for(int i=0;i<ab[4]->deactive_ports.size();i++){
	// 	cout<<(ab[4]->deactive_ports)[i]<<" ";
	// }cout<<endl;
	// cout<<al[4];
	// cout<<"*****\n";
	// for(int i=0;i<ab.size();i++){
	// 	if(ab[i]->root_port!=NULL)
	// 	cout<<ab[i]->root_port->name;
	// cout<<" deactive are: ";
	// 	for(int j=0;j<ab[i]->deactive_ports.size();j++){
	// 		cout<<(ab[i]->deactive_ports)[j]->name<<" ";
	// 	}
	// 	cout<<"\n";
	// }
	/////////////////////////////first part over
	for(int i=0;i<nlans;i++){ //  some alphabets may be missing,so any numebr may be seen
		string xx;
		getline(cin,xx);
		vector<string> hs;
		if(xx.size()>3)hs=split(xx.substr(3)," ");
		int ln=xx[0]-'A';
		for(int j=0;j<hs.size();j++) 
		{
			Node* uu= new Node();
			an[hs[j]]=uu;
			uu->name=hs[j];
			uu->par=al[ln];
			al[ln]->nodes.push_back(uu);
		}
		}
		// for(int i=0;i<26;i++){
		// 	for(int j=0;j<al[i]->nodes.size();j++){
		// 		cout<<(al[i]->nodes)[j]->name<<" ";
		// 	}cout<<endl;
		// }
	int num_transfer;
	//cin>>num_transfer;
	string yy;
	getline(cin,yy);
	num_transfer=stoi(yy);
	for(int i=0;i<num_transfer;i++){
		string fg;
		getline(cin,fg);
		vector<string> mates=split(fg," ");
		//cout<<fg<<endl;
		transfer_packets(an[mates[0]],an[mates[1]],trace,time1,ab,al,an); 

		for(int j=0;j<ab.size();j++){
			cout<<"B"<<ab[j]->name<<":\nHOST ID | FORWARDING PORT\n"; //map<string,Lan*> forwarding_table;
			for(map<string,Lan*>::iterator m=ab[j]->forwarding_table.begin();m!=ab[j]->forwarding_table.end();m++){//cout<<"jj";
				cout<<m->first<<" | "<<((char)(m->second->name+65))<<"\n";
			}
		}
		cout<<"\n";
	}
}
