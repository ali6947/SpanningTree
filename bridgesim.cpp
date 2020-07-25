#include "bridgesim.h"
#include<iostream>
#include<string>
#include <vector>
#include <map>
#include<algorithm>
using namespace std;
bool comp(Lan* x, Lan* y){
	return x->name<y->name;
}
bool comp2(Bridge* x, Bridge* y){
	return x->name<y->name;
}
void span_tree (bool trace, int& time1,vector<Bridge*>& ab,vector<Lan*>& al, map<string,Node*>& an){
	
	vector<string> messages;
	for(int i=0;i<ab.size();i++){
		for(int j=0;j<(ab[i]->ports).size();j++){
			msg x((ab[i]->ports)[j],ab[i]->dist,ab[i]->root,ab[i]);
			 for(int k=0;k<((ab[i]->ports)[j]->bridges).size();k++){
			 	if(((ab[i]->ports)[j]->bridges)[k]!=ab[i]){
			 	(((ab[i]->ports)[j]->bridges)[k]->nexttime).push_back(x);
			 	messages.push_back(to_string(time1)+" s B"+to_string(ab[i]->name)+" (B"+to_string(ab[i]->name)+", 0, B"+to_string(ab[i]->name)+")");
			 }
			 }
		}
	}
	while(true){
		time1++;
		for(int i=0;i<ab.size();i++){
			ab[i]->currtime=ab[i]->nexttime;
			(ab[i]->nexttime).clear();
		}
		bool changed=false;
		for(int i=0;i<ab.size();i++){
			for(int j=0;j<(ab[i]->currtime).size();j++){
				// if(((ab[i]->currtime)[j].root==ab[0])&&((ab[i]->currtime)[j].sender==ab[2])){
				// //	cout<<"^^^";
				// 	cout<<ab[3]->root->name<<" "<<ab[3]->dist<<"\n";
				// }
				msg t=(ab[i]->currtime)[j];
				// if(ab[i]->name==2){
				// 	cout<<ab[i]->name<<" "<<ab[i]->root->name<<" "<<t.port->name<<endl;
				// }
				messages.push_back(to_string(time1)+" r B"+to_string(ab[i]->name)+" (B"+to_string(t.root->name)+", "+to_string(t.dist)+", B"+to_string(t.sender->name)+")");
				if((t.root)->name<(ab[i]->root)->name){
					(ab[i]->root)=t.root;
					(ab[i]->dist)=1+t.dist;
					(ab[i]->parent)=t.sender;
					(ab[i]->root_port)=t.port;
					(ab[i]->deactive_ports).clear();
					(ab[i]->deactive_ports).push_back(t.port);
					ab[i]->gen_msg=false;
					changed=true;
				}
				else if ((t.root)->name==(ab[i]->root)->name){
					if(t.dist+1<ab[i]->dist){
						(ab[i]->dist)=1+t.dist;
						(ab[i]->root_port)=t.port;
						ab[i]->gen_msg=false;
						(ab[i]->deactive_ports).clear();
						(ab[i]->deactive_ports).push_back(t.port);
						(ab[i]->parent)=t.sender;
						changed=true;
					}
					else if((t.dist+1==ab[i]->dist)&&((t.sender)->name<((ab[i]->parent)->name)))
					{ 
						Lan* tmp=(ab[i]->root_port);
						(ab[i]->root_port)=t.port;
						ab[i]->gen_msg=false;
						(ab[i]->parent)=t.sender;
						if(find((ab[i]->deactive_ports).begin(),(ab[i]->deactive_ports).end(),tmp)==(ab[i]->deactive_ports).end()){
						(ab[i]->deactive_ports).push_back(tmp);	}
						changed=true;
					}
					else if((t.dist+1==ab[i]->dist)&&((t.sender)->name>((ab[i]->parent)->name)))
					{
						if(find((ab[i]->deactive_ports).begin(),(ab[i]->deactive_ports).end(),t.port)==(ab[i]->deactive_ports).end()){
						(ab[i]->deactive_ports).push_back(t.port);	}
					} // case reqd herer when parent is same but port is diff. See 4.in
					else if((t.dist+1==ab[i]->dist)&&((t.sender)->name==((ab[i]->parent)->name))){
						if(t.port->name < ab[i]->root_port->name){
							Lan* trr=ab[i]->root_port;
							ab[i]->root_port=t.port;
							changed=true;
							if(find((ab[i]->deactive_ports).begin(),(ab[i]->deactive_ports).end(),trr)==(ab[i]->deactive_ports).end()){
						(ab[i]->deactive_ports).push_back(trr);}
						// if(find((ab[i]->deactive_ports).begin(),(ab[i]->deactive_ports).end(),ab[i]->root_port)!=(ab[i]->deactive_ports).end()){
						// (ab[i]->deactive_ports).erase(find((ab[i]->deactive_ports).begin(),(ab[i]->deactive_ports).end(),ab[i]->root_port));}
						}
						else{
							if(find((ab[i]->deactive_ports).begin(),(ab[i]->deactive_ports).end(),t.port)==(ab[i]->deactive_ports).end()){
						(ab[i]->deactive_ports).push_back(t.port);}	
						}
					}
					else if((t.dist==ab[i]->dist)&&((ab[i]->name)>((t.sender)->name))){
						if(find((ab[i]->deactive_ports).begin(),(ab[i]->deactive_ports).end(),t.port)==(ab[i]->deactive_ports).end()){
						(ab[i]->deactive_ports).push_back(t.port);	}
					}
				}
				for(int k=0;k<(ab[i]->ports).size();k++){
					if(find((ab[i]->deactive_ports).begin(),(ab[i]->deactive_ports).end(),(ab[i]->ports)[k])==(ab[i]->deactive_ports).end()){
						msg y((ab[i]->ports)[k],ab[i]->dist,ab[i]->root,ab[i]);
						messages.push_back(to_string(time1)+" s B"+to_string(ab[i]->name)+" (B"+to_string(y.root->name)+", "+to_string(y.dist)+", B"+to_string(y.sender->name)+")"); 
						vector<Bridge*> br=((ab[i]->ports)[k])->bridges;
						for(int l=0;l<br.size();l++){
							if(br[l]!=ab[i]){
							(br[l]->nexttime).push_back(y);
							}
						}
					}
				}
			}
		}
		if(!changed){
			break;
		}
		for(int i=0;i<ab.size();i++){
			if(ab[i]->gen_msg){
				for(int j=0;j<(ab[i]->ports).size();j++){
				msg x((ab[i]->ports)[j],ab[i]->dist,ab[i]->root,ab[i]);
			 for(int k=0;k<((ab[i]->ports)[j]->bridges).size();k++){
			 	if(((ab[i]->ports)[j]->bridges)[k]!=ab[i]){
			 	(((ab[i]->ports)[j]->bridges)[k]->nexttime).push_back(x);
			 	messages.push_back(to_string(time1)+" s B"+to_string(ab[i]->name)+" (B"+to_string(ab[i]->root->name)+", "+to_string(ab[i]->dist)+", B"+to_string(ab[i]->name)+")");
			 }
			 }
		}
			}
		}
	}
	for(int i=0;i<ab.size();i++){
			vector<Lan*>::iterator tr=find(ab[i]->deactive_ports.begin(),ab[i]->deactive_ports.end(),ab[i]->root_port);
			if(tr!=ab[i]->deactive_ports.end()){
				ab[i]->deactive_ports.erase(tr);
			}
		}
	if(trace){
		sort(messages.begin(),messages.end());
		for(int i=0;i<messages.size();i++){
			cout<<messages[i]<<"\n";
		}
	}
}

void transfer_packets(Node* a,Node* b,bool trace, int& time1,vector<Bridge*>& ab,vector<Lan*>& al, map<string,Node*>& an){ //a>>>>b
	vector<string> msg_trace;
	//cout<<"seeing for "<<a->name<<" -->"<<b->name<<endl;
	packet ty(a->par,b->par,a->par);
	for(int i=0;i<(a->par->bridges).size();i++){
		((a->par->bridges)[i]->nextp).push_back(ty);
	}
	while(true){
		time1++;
		int sum=0;
		for(int i=0;i<ab.size();i++){
			ab[i]->currp=ab[i]->nextp;
			//cout<<"**"<<ab[i]->name<<" "<<ab[i]->currp.size()<<"\n";
			(ab[i]->nextp).clear();
			sum+=ab[i]->currp.size();
		}
		//cout<<sum;
		if(sum==0) break;
		for(int i=0;i<ab.size();i++){ //cout<<i<<" **"<<ab.size()<<"\n";
			for(int j=0;j<ab[i]->currp.size();j++){ //cout<<j<<" "<<ab[i]->name<<" "<<ab[i]->currp.size()<<"\n";
				msg_trace.push_back(to_string(time1)+" r B"+to_string(ab[i]->name)+" "+((char)((ab[i]->currp)[j].sender->name+65))+"-->"+((char)((ab[i]->currp)[j].receiver->name+65)));
				//cout<<to_string(time1)+" r B"+to_string(ab[i]->name)+" "+((char)((ab[i]->currp)[j].sender->name+65))+"-->"+((char)((ab[i]->currp)[j].receiver->name+65))<<" "<<(ab[i]->currp)[j].port->name<<"\n";
				if(find((ab[i]->deactive_ports).begin(),(ab[i]->deactive_ports).end(),(ab[i]->currp)[j].port)==(ab[i]->deactive_ports).end()){
					if(ab[i]->forwarding_table.find(b->name)==ab[i]->forwarding_table.end()){ //cout<<"lo";
						(ab[i]->forwarding_table)[a->name]=(ab[i]->currp)[j].port;
						//cout<<(ab[i]->forwarding_table)[a->name]<<"**\n";
						for(int k=0;k<(ab[i]->ports).size();k++){ 
							// if(ab[i]==ab[4]){
							// 	for(int p=0;p<ab[i]->deactive_ports.size();p++){
							// 		cout<<(ab[i]->deactive_ports)[p]<<"* ";
							// 	}cout<<endl;
							// 	cout<<al[4]<<"#\n";
							// }
							if(find((ab[i]->deactive_ports).begin(), (ab[i]->deactive_ports).end(),(ab[i]->ports)[k])==(ab[i]->deactive_ports).end()){//cout<<(ab[i]->ports)[k]<<endl;
								
								if((ab[i]->ports)[k]!=(ab[i]->currp)[j].port){ //cout<<((ab[i]->currp)[j].port->name)<<" "<<(ab[i]->name)<<" "<<(ab[i]->ports)[k]->name<<"\n";
								//if(ab[i]==ab[4])  cout<<"%#"<<ab[i]->name<<" "<<(ab[i]->ports)[k]->name<<" "<<(ab[i]->currp)[j].port->name<<endl;
									for(int l=0;l<(ab[i]->ports)[k]->bridges.size();l++){	
										packet rr((ab[i]->currp)[j].sender,(ab[i]->currp)[j].receiver,(ab[i]->ports)[k]);
										if(ab[i]!=((ab[i]->ports)[k]->bridges)[l]) (((ab[i]->ports)[k]->bridges)[l]->nextp).push_back(rr);
										msg_trace.push_back(to_string(time1)+" s B"+to_string(ab[i]->name)+" "+((char)((ab[i]->currp)[j].sender->name+65))+"-->"+((char)((ab[i]->currp)[j].receiver->name+65)));
									}
								}
							}
						}
					}
					else{(ab[i]->forwarding_table)[a->name]=(ab[i]->currp)[j].port;
						Lan* tf=(ab[i]->forwarding_table)[b->name];
						if(tf!=(ab[i]->currp)[j].port){
							for(int l=0;l<tf->bridges.size();l++){
								packet rr((ab[i]->currp)[j].sender,(ab[i]->currp)[j].receiver,tf);
								if(ab[i]!=(tf->bridges)[l]) (tf->bridges)[l]->nextp.push_back(rr);
								msg_trace.push_back(to_string(time1)+" s B"+to_string(ab[i]->name)+" "+((char)((ab[i]->currp)[j].sender->name+65))+"-->"+((char)((ab[i]->currp)[j].receiver->name+65)));
							}
						}
					}
				}
			}
		}
	}
	if(trace){
		sort(msg_trace.begin(), msg_trace.end());
		for(int i=0;i<msg_trace.size();i++){
			cout<<msg_trace[i]<<"\n";
		}
	}
}

