#include<string>
#include <vector>
#include <map>
#include<algorithm>
using namespace std;

struct Bridge ;
struct Node;
struct cmpft {
    bool operator()(const std::string& a, const std::string& b) const {
        return stoi(a.substr(1))<stoi(b.substr(1));
    }
};
struct Lan{
	int name;
	vector<Bridge*> bridges;
	vector<Node*> nodes;
};

struct msg{ // sort by root sender
	Lan* port;
	int dist;
	Bridge* root;
	Bridge* sender;
	msg(){}
	msg(Lan* a, int x, Bridge* y, Bridge*z);
};

struct packet{
	Lan* sender;
	Lan* receiver;
	Lan* port;
	packet(Lan* x,Lan* y,Lan* z);
};

struct Bridge{
	int name;
	bool gen_msg;
	vector<Lan*> ports;
	vector<Lan*> deactive_ports; // dont send over them
	Lan* root_port; // root port is null means it is root
	Bridge* parent;
	Bridge* root;
	int dist;
	map<string,Lan*,cmpft> forwarding_table;
	vector<msg> currtime, nexttime ; // msg buffers
	vector<packet> currp,nextp;
	Bridge(int n);
};
struct Node{
	string name;
	Lan* par;
};


