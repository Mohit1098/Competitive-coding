class AhoCorasick{
	static const int ALPHABET_SIZE=26;
	
	class node{
	public:
		int parent;
		char charFromParent;
		int suffLink;
		int children[ALPHABET_SIZE];
		int transitions[ALPHABET_SIZE];
		bool leaf;
		int length;
		int beauty;
		
		node(){
			fill(children,children+ALPHABET_SIZE,-1);
			fill(transitions,transitions+ALPHABET_SIZE,-1);
			leaf=0;
			suffLink=-1;
		}
	};
	
	
public:
	
	node ** nodes;
	int nodeCount;
	
	
	AhoCorasick(int MaxNodes){
		nodes = new node*[MaxNodes];
		nodes[0] = new node();
		nodes[0]->suffLink =0 ;
		nodes[0]->parent=-1;
		nodeCount=1;
	}
	
	void addString(string& s,int b){
		int cur =0;
		for(auto it:s){
			int c = (it-'a');
			if(nodes[cur]->children[c]==-1){
				nodes[nodeCount] = new node ();
				nodes[nodeCount]->parent = cur;
				nodes[nodeCount]->charFromParent = it;
				nodes[cur]->children[c] =nodeCount++;
 			}
			cur = nodes[cur]->children[c];
		}
		nodes[cur]->leaf=1;
		nodes[cur]->beauty =b;
		nodes[cur]->length=s.length();
	}
	
	int suffLink(int nodeInd){
		node* n = nodes[nodeInd];
		if(n->suffLink==-1){
			n->suffLink = (n->parent ==0 ) ? 0 : (transition(suffLink(n->parent), n->charFromParent));
		}
	}
	
	int transition(int nodeIndex, char ch) {
		int c = ch - 'a';
		node* n = nodes[nodeIndex];
		if (n->transitions[c] == -1)
			n->transitions[c] = n->children[c] != -1 ? n->children[c] : (nodeIndex == 0 ? 0 : transition(suffLink(nodeIndex), ch));
		return n->transitions[c];
	}
};


// Example use
int32_t main(){
	AhoCorasick ahoCorasick(1000);
	
	string a = "bc";
	string b = "abc";
	
	ahoCorasick.addString(a,1);
	ahoCorasick.addString(b,1);
	
	string s = "tabcbc";
	int node = 0;

	for (int i = 0; i < s.length(); i++) {
		node = ahoCorasick.transition(node, s[i]);
		if (ahoCorasick.nodes[node]->leaf)
			cout<<i<<endl;
	}

}