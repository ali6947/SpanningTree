#include<string>
#include <vector>
#include <map>
#include<algorithm>
#include "bridge.h"
using namespace std;

msg::msg(Lan* a, int x, Bridge* y, Bridge*z){
		port=a; dist=x;root=y;sender=z;
	}

packet::packet(Lan* x,Lan* y,Lan* z){
		sender=x;receiver=y;port=z;
	}

Bridge::Bridge(int n=0){
		name=n;
		dist=0;
		root=this;
		parent=NULL;
		gen_msg=true;
		root_port=NULL;
	}




