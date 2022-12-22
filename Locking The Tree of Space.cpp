using namespace std;
int inf=1e9+7, MOD=1e9+7;

int w = 1;

struct Tree{
    public :
        bool isLocked;
        bool isLockable;
        int id;
        int ma;
        Tree* p;
        vector<Tree*> c; 
        Tree(){
            isLocked = false;
            isLockable = true;
            id = -1;
            ma = w++;
            p = NULL;
        }
        Tree(Tree* parent){
            isLocked = false;
            isLockable = true;
            id = -1;
            ma = w++;
            p = parent;
        }
};
        // bool ll(Tree* n) return n->l;

        bool locking(Tree* n, int uuid){
            if(n->isLockable == false || (n->isLocked)) return false;
            Tree* T = n;
            queue<Tree*> q;
            q.push(T);
            while(!q.empty()){
                Tree* temp = q.front();
                q.pop();
                for(auto x: temp->c){
                    if(x->isLocked) return false;//checking if any of the descendants is locked.
                    q.push(x);
                }
            }
            n->id = uuid;
            n->isLocked = true;
            q.push(T);
            while(!q.empty()){
                Tree* temp = q.front();
                q.pop();
                for(auto x: temp->c){
                    x->isLockable = false;
                    q.push(x);
                }
            }
            return true;
        }
        
        bool unlocking(Tree* n,int uuid){
            if(n->isLockable == false ---indicates that is its ancestor is locked || n -> isLocked == false || (n->isLocked && uuid != n->id)) return false;
            Tree* T = n;
            n->isLocked= false;
            n->id = -1;
            queue<Tree*> q;
            q.push(T);
            while(!q.empty()){
                Tree* temp = q.front();
                q.pop();
                for(auto x: temp->c){
                    x->isLockable = true;
                    q.push(x);
                }
            }
            return true;
        }

        bool update(Tree* n,int uuid){
            if(n->isLockable == false || n->isLocked == true) return false;
            Tree* T = n;
            queue<Tree*> q;
            q.push(T);
            bool f = false;
            while(!q.empty()){
                Tree* temp = q.front();
                q.pop();
                for(auto x: temp->c){
                    if(x->isLocked == true && x->id != uuid) { return false; }
                    if(x->isLocked) f = true;
                    q.push(x);
                }
            }
            if(!f) return false;//if none of the children is locked
            
            q.push(T);
            while(!q.empty()){
                Tree* temp = q.front();
                q.pop();
                for(auto x: temp->c){
                    if(x->isLocked){
                        if(!unlocking(x,uuid)) return false;
                    }
                    q.push(x);
                }
            }
            // locking(n,uuid);
            return locking(n,uuid);
        }

        void Print(Tree* n){
            queue<Tree*> q;
            q.push(n);
            // cout << n->ma <<"\n";
            while(!q.empty()){
                Tree* temp = q.front();
                q.pop();
                for(auto x: temp->c){
                    cout << temp->ma << " -> " << x->ma << " ";
                }
            }
        }

unordered_map<string, Tree*> sToT;


int main(){
    int n,m,q;
    cin >> n >> m >>q;
    
    
    Tree* t = new Tree(); 
    string d;
    cin >> d;

    // a.c.push_back(&t);
    sToT[d] = t;
    queue<Tree*> queue;
    queue.push(t);
    int k = 1;
    while(!queue.empty()){
        auto temp = queue.front();
        queue.pop();
        // cout << temp->ma <<"\n";
        while(k < n  -->ensuring that the total number of nodes are n  && (int)temp->c.size() < m---> ensuring the number of children of each node is m){
            string s;
            cin >> s;
            // cout << s <<"\n";
            Tree* u = new Tree(temp);// making temp as the parent
            sToT[s] = u;//storing the tree corresponding to the string
            temp->c.push_back(u);// pushing u as the child of temp
            queue.push(u);
            k++;
            // cout << s <<" "<<sToT[s]->ma <<"\n";
        }
    }
    // Print(t);
    // dfs(1);
    FOR(i,q) {
        int qn,uuid;
        string name;
        bool ans;
        cin >> qn >> name >> uuid;
        if(qn == 1){
            ans = locking(sToT[name],uuid);
            // cout << name<<" "<< sToT[name]->id << " " << uuid << "\n";
        }
        else if(qn == 2){
            ans = unlocking(sToT[name],uuid);
            // cout << name<<" "<< sToT[name]->id << " " << uuid << "\n";
        }
        else {
            ans = update(sToT[name],uuid);
            // cout << ans << "\n";
        }
        // FOR(j,nuid.size()) cout << j << " " << nuid[j] <<" ";
        // cout <<"\n";
        if(ans) cout << "true\n";
        else cout << "false\n";
    }
    return 0;
}
