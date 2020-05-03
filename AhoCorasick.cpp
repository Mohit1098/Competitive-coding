// without exit links


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
		int ind;
		
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
	
	void addString(string& s,int ind){
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
		nodes[cur]->ind=ind;
	}
	
	int suffLink(int nodeInd){
		node* n = nodes[nodeInd];
		if(n->suffLink==-1){
			n->suffLink = (n->parent ==0 ) ? 0 : (transition(suffLink(n->parent), n->charFromParent));
		}
		return n->suffLink;
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





///.................................
// With exit links
// amortized same complexity as without exit links

constexpr int K = 26;
struct Vertex {
	std::array<int, K> next;
	bool terminal = false;
	int terminal_idx = -1;
	int p = -1;
	char pch;
	int depth = 0;
	int link = 0;
	int next_terminal = 0;
	std::array<int, K> go;
	
	Vertex(int p, char ch, int depth) : p(p), pch(ch), depth(depth) {
		std::fill(next.begin(), next.end(), 0);
		std::fill(go.begin(), go.end(), 0);
	}
};

class AhoCorasick {
public:
	AhoCorasick() : t(1, {-1, '$', 0}) {}
	
	void add_string(std::string const& s, int idx) {
		int v = 0;
		for (char ch : s) {
			int c = ch - 'a';
			if (!t[v].next[c]) {
				t[v].next[c] = t.size();
				t.emplace_back(v, ch, t[v].depth + 1);
			}
			v = t[v].next[c];
		}
		t[v].terminal = true;
		t[v].terminal_idx = idx;
	}
	
	void push_links() {
		std::queue<int> q;
		q.push(0);
		while (!q.empty()) {
			int v = q.front();
			auto& cur = t[v];
			auto& link = t[cur.link];
			q.pop();
			cur.next_terminal = link.terminal ? cur.link : link.next_terminal;
			
			for (int c = 0; c < K; c++) {
				if (cur.next[c]) {
					t[cur.next[c]].link = v ? link.next[c] : 0;
					q.push(cur.next[c]);
				} else {
					cur.next[c] = link.next[c];
				}
			}
		}
	}
	
	int transition(int idx, char c) {
		return t[idx].next[c - 'a'];
	}
	
	Vertex const& getInfo(int idx) {
		return t[idx];
	}


	std::vector<Vertex> t;
};

int32_t main(){
	AhoCorasick ahoCorasick;
	
	string a = "bc";
	string b = "abc";
	string c = "ab";
	
	ahoCorasick.add_string(a,1);
	ahoCorasick.add_string(b,2);
	ahoCorasick.add_string(c,3);
	
	ahoCorasick.push_links();
	
	string s = "tabcbc";
	int node = 0;

	for (int i = 0; i < s.length(); i++) {
		node = ahoCorasick.transition(node, s[i]);
		if (ahoCorasick.t[node].terminal){
			cout << i << " ";
			cout<<ahoCorasick.t[node].terminal_idx<<endl;
		}
	}

}