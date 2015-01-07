#include <cstdio>
#include <bitset>
#include <vector>
#include <string>
using namespace std; 
using std::size_t;
using std::vector;
using std::bitset;
using std::string;
int vert,edge;
int max_click;
vector<string> links(100);
void B_K(bitset<100> P,int R, bitset<100> X){
	if( P.none() && X.none() ){
		max_click = (R > max_click )? R:max_click;  
		return;
	}
	int pot;
	if(( pot = (P.count() + R)) < max_click){
		return;
	}
	bitset<100> a = (P | X);
	size_t piv=0;
	while(!a.test(piv))
		++piv;
	int tmp=0;
	bitset<100> pivset(links[piv]);
	bitset<100> Q = P&(~pivset);
	while( Q.any() && pot > max_click){
		while(!Q.test(tmp))
			++tmp;
		bitset<100> tmpset(links[tmp]);
		if(  (Q|tmpset).any() || (tmp == piv) )
			B_K( (P & tmpset),R+1, (X & tmpset));
		--pot;
		P.reset(tmp);
		X.set(tmp);
		Q.reset(tmp);
	}
	return;
}
int main(int argc, char const *argv[])
{
	int tst;
	scanf("%d", &tst);
	while(tst--){
		vert=0,edge=0;
		scanf("%d%d", &vert, &edge);
		int f,t,r=0;
		for (int i = 0; i < vert; ++i){
			//links[i].set();
			//links[i][i].flip();
			links[i].replace(0,1,100,'1');
			links[i].replace(0,(100-vert),(100-vert),'0');
			links[i][99-i] = '0';
		}
		for (int i = 0; i < edge; ++i){// reads in the complementary graph
			scanf("%d%d", &f, &t);
			links[f][99-t]='0';
			links[t][99-f]='0';
		}
		string  p(vert,'1'), x(vert,'0'); 
		bitset<100>P(p),X(x);
		max_click = 0;
		B_K(P,r,X);
		printf("%d\n", max_click);
	}
	return 0;
}