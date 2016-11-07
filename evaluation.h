void influence(state &s);
void initialWeights();
void facefeat(state &s, int num);
vector<tuple<int,int> > neighbours(state &s, tuple<int,int> t, int who);
vector<tuple<int,int> > notNeighbours(state &s, tuple<int,int> t, int who);
double straightStones(state &s);
bool checkRoadWin(state &s, int num);
double oneLess1(state &s,int j,int a, int who);
double oneLess2(state &s,int j,int a, int who);
vector < vector<tuple<int,int> > > aux1(state &s, int t, int who);
vector < vector<tuple<int,int> > > aux2(state &s, int t, int who);
double intersection(vector < vector<tuple<int,int> > > &a, vector < vector<tuple<int,int> > > &b);
double oneRemaining(state &s, int num);
double evalFxn(state s);
void train(state s, double trueVal);
void writeWeights();
vector<tuple<int,int> > neighboursnew(state &s, tuple<int,int> t, int who) ;
