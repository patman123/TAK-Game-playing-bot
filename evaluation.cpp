#include<bits/stdc++.h>
#include "class.h"
#include "variables.h"	
#include "evaluation.h"


using namespace std;

vector<int> weights;
double learningR=0.00025; 
/*double *facefeatures;
double *facefeatures2;
double *influenceval;
*/
double facefeat10;
double facefeat11;
double facefeat12;
double facefeat13;

double facefeat20;
double facefeat21;
double facefeat22;
double facefeat23;

double influence0;
double influence1;
double influence2;

double ss;
double oneremaining1;
double oneremaining2;
void writeWeights()
{
  ofstream myfile;
  myfile.open ("weights.txt");
  for(int i=0;i<weights.size();i++)
  { myfile <<weights[i] <<" ";
   }
  myfile.close();

}
void initialWeights()
{	
	//weights.resize(10); 

	std::ifstream ifile("weights.txt", std::ios::in);
    std::vector<double> scores;

    //check to see that the file was opened correctly:
    if (!ifile.is_open()) {
        std::cerr << "There was a problem opening the input file!\n";
        exit(1);//exit or do additional error checking
    }

    double num = 0.0;
    //keep storing values from the text file so long as data exists:
    while (ifile >> num) {
        weights.push_back(num);
        cerr<<num<<endl; 
    }
    ifile.close();
	/*weights.resize(10);
	weights[0]=5; //in influence
	weights[1]=5; //in influence
	weights[2]=5; //in influence
	weights[3]=20; //num flat
	weights[4]=0; //num standing 
	weights[5]=10; //num cap
	weights[6]=10; //num cumulativestones in stacks
	weights[7]=40; //straightstones
	weights[8]=100; //oneremaining
	*/
}

void train(state s, double trueVal)
{
	double evaluation= evalFxn(s); 

//val=weights[0]*influence0+weights[1]*influence1+weights[2]*influence2+weights[3]*(facefeat10-facefeat20)+weights[4]*(facefeat11-facefeat21)+weights[5]*(facefeat12-facefeat22)+weights[6]*(facefeat13-facefeat23)+weights[7]*ss+weights[8]*oneremaining1+weights[9]*oneremaining2;

	weights[0]=weights[0]+learningR*2*(trueVal-evaluation)*influence0;
	weights[1]=weights[1]+learningR*2*(trueVal-evaluation)*influence1; 
	weights[2]=weights[2]+learningR*2*(trueVal-evaluation)*influence2; 
	weights[3]=weights[3]+learningR*2*(trueVal-evaluation)*(facefeat10);  //-facefeat20
	weights[4]=weights[4]+learningR*2*(trueVal-evaluation)*(facefeat11);  //-facefeat21
	weights[5]=weights[5]+learningR*2*(trueVal-evaluation)*(facefeat12);  //-facefeat22 
	weights[6]=weights[6]+learningR*2*(trueVal-evaluation)*(facefeat13);  //-facefeat23
	
	weights[7]=weights[7]+learningR*2*(trueVal-evaluation)*ss;	
	weights[8]=weights[8]+learningR*2*(trueVal-evaluation)*oneremaining1;
	weights[9]=weights[9]+learningR*2*(trueVal-evaluation)*oneremaining2;

	weights[10]=weights[10]+learningR*(-2)*(trueVal-evaluation)*(facefeat20);  //-facefeat20
	weights[11]=weights[11]+learningR*(-2)*(trueVal-evaluation)*(facefeat21);  //-facefeat21
	weights[12]=weights[12]+learningR*(-2)*(trueVal-evaluation)*(facefeat22);  //-facefeat22 
	weights[13]=weights[13]+learningR*(-2)*(trueVal-evaluation)*(facefeat23);  //-facefeat23

}

void influence(state &s)
{
	double numEmpty=0.0;
	double numMyStones=0.0;
	double numOppStones=0.0;
	double numMySurrOpp=0.0;

	int n= s.boardState.size();
	for (int i=0;i<n;i++)
	{
		for (int j=0;j<n;j++)
		{
			if(s.boardState[i][j].size()!=0)
			{
				int stoneNumber=s.boardState[i][j][s.boardState[i][j].size()-1];
				if(stoneNumber==1 || stoneNumber==3 || stoneNumber==5)
				{
					if(i!=0){
						if(s.boardState[i-1][j].size()==0)
							numEmpty+=1;
						else{
							stoneNumber=s.boardState[i-1][j][s.boardState[i-1][j].size()-1];
							if(stoneNumber==1 || stoneNumber==3 || stoneNumber==5)
								numMyStones+=1;
							else
								numOppStones+=1;
						}
					}
					if(i!=n-1){
						if(s.boardState[i+1][j].size()==0)
							numEmpty+=1;
						else{
							stoneNumber=s.boardState[i+1][j][s.boardState[i+1][j].size()-1];
							if(stoneNumber==1 || stoneNumber==3 || stoneNumber==5)
								numMyStones+=1;
							else
								numOppStones+=1;
						}
					}
					if(j!=0){
						if(s.boardState[i][j-1].size()==0)
							numEmpty+=1;
						else{
							stoneNumber=s.boardState[i][j-1][s.boardState[i][j-1].size()-1];
							if(stoneNumber==1 || stoneNumber==3 || stoneNumber==5)
								numMyStones+=1;
							else
								numOppStones+=1;
						}
					}
					if(j!=n-1){
						if(s.boardState[i][j+1].size()==0)
							numEmpty+=1;
						else{
							stoneNumber=s.boardState[i][j+1][s.boardState[i][j+1].size()-1];
							if(stoneNumber==1 || stoneNumber==3 || stoneNumber==5)
								numMyStones+=1;
							else
								numOppStones+=1;
						}
					}
				}
				else if(stoneNumber==2 || stoneNumber==4 || stoneNumber==6)
				{
					if(i!=0){
						if(s.boardState[i-1][j].size()!=0){
							stoneNumber=s.boardState[i-1][j][s.boardState[i-1][j].size()-1];
							if(stoneNumber==1 || stoneNumber==3 || stoneNumber==5)
								numMySurrOpp+=1;
						}
					}
					if(i!=n-1){
						if(s.boardState[i+1][j].size()!=0){
							stoneNumber=s.boardState[i+1][j][s.boardState[i+1][j].size()-1];
							if(stoneNumber==1 || stoneNumber==3 || stoneNumber==5)
								numMySurrOpp+=1;
						}
					}
					if(j!=0){
						if(s.boardState[i][j-1].size()!=0){
							stoneNumber=s.boardState[i][j-1][s.boardState[i][j-1].size()-1];
							if(stoneNumber==1 || stoneNumber==3 || stoneNumber==5)
								numMySurrOpp+=1;
						}
					}
					if(j!=n-1){
						if(s.boardState[i][j+1].size()!=0){
							stoneNumber=s.boardState[i][j+1][s.boardState[i][j+1].size()-1];
							if(stoneNumber==1 || stoneNumber==3 || stoneNumber==5)
								numMySurrOpp+=1;
						}
					}
				}
			}
		}
	}
	double result[3];
	influence0=numEmpty;
	influence1=numMyStones-numOppStones;
	influence2=numMySurrOpp;
	//return result;
	//return double(weights[0]*result[0]+weights[1]*(result[1]-result[2])+weights[2]*result[3]);
}

void facefeat(state &s, int num) //returns the number of facing stones
{	
	int p,q,r;
	if(num==1)
	{
		p= 1 ;
		q= 3;
		r= 5 ;	
	}  
	else{
		p= 2 ;
		q= 4;
		r= 6 ;	
	}
	double flat = 0.0 ; 	//represents number of flatstones on top
	double standing= 0.0 ;
	double cap= 0.0 ;
	double cum= 0.0 ;		// in all the stacks the total number of my stones
	
	int boardSize=s.boardState.size();
	for(int i= 0 ;i<boardSize;i++)
	{   for(int j=0;j<boardSize;j++)
		{	
			if(s.boardState[i][j].size()>0)
			{	 
				int y= s.boardState[i][j][s.boardState[i][j].size()-1] ;
				if(y==p)
				flat=flat+1;
				else if(y==q)
				standing=standing+1;  	
				else if(y==r)
				cap=1;			
			}
			if(s.boardState[i][j].size()>=2)
			{	
				for(int d=0;d<s.boardState[i][j].size();d++)
				{
					if(s.boardState[i][j][d]==p||s.boardState[i][j][d]==r)
						cum=cum+1;	 
				}
			}
		}
	}
	/*double result[4];
	result[0]=flat;
	result[1]=standing;
	result[2]=cap;
	result[3]=cum;
	
	*///facefeatures=result;
	//cerr<<num<<" flat "<<flat<<endl;
	if(num==1)
	{
		facefeat10=flat;
		facefeat11=standing;
		facefeat12=cap;
		facefeat13=cum;
	}
	else
	{
		facefeat20=flat;
		facefeat21=standing;
		facefeat22=cap;
		facefeat23=cum;
	}
	//return result;
	//return weights[3]*flat+weights[4]*standing+weights[5]*cap+weights[6]*cum;
}

vector<tuple<int,int> > neighbours(state &s, tuple<int,int> t, int who)		//returns neighbours with flat or cap
{
	int n= s.boardState.size();
	vector<tuple<int,int> > result;
	int stoneNum;
	int row=get<0>(t);
	int column=get<1>(t);
	int p,q;
	if(who==1){
		p=1;
		q=5;
	}
	else{
		p=2;
		q=6;
	}

	if(row!=0)
	{
		if(s.boardState[row-1][column].size()==0)
			goto l2 ;
		stoneNum=s.boardState[row-1][column][s.boardState[row-1][column].size()-1];	
		if(stoneNum==p  ||  stoneNum==q)
		{
			result.push_back(make_tuple(row-1,column));
		}
	}
	l2: ;
	if(row!=n-1)
	{
		if(s.boardState[row+1][column].size()==0)
			goto l3 ;
		
		stoneNum=s.boardState[row+1][column][s.boardState[row+1][column].size()-1];	
		if(stoneNum==p  ||  stoneNum==q)
		{
			result.push_back(make_tuple(row+1,column));
		}
	}
	l3:;

	if(column!=0)
	{
		if(s.boardState[row][column-1].size()==0)
			goto l4 ;
		
		stoneNum=s.boardState[row][column-1][s.boardState[row][column-1].size()-1];	
		if(stoneNum==p  || stoneNum==q)
		{
			result.push_back(make_tuple(row,column-1));
		}
	}
	l4:;

	if(column!=n-1)
	{	
		if(s.boardState[row][column+1].size()==0)
			goto l5 ;
		
		stoneNum=s.boardState[row][column+1][s.boardState[row][column+1].size()-1];	
		if(stoneNum==p || stoneNum==q)
		{
			result.push_back(make_tuple(row,column+1));
		}
	}
	l5:;
	return result;
	
}

vector<tuple<int,int> > notNeighbours(state &s, tuple<int,int> t, int who)	//returns neighbours which are not mine
{
	int n= s.boardState.size();
	vector<tuple<int,int> > result;
	int stoneNum;
	int row=get<0>(t);
	int column=get<1>(t);
	int p,q,r;
	if(who==1){
		p=1;
		q=5;
		r=3;
	}
	else{
		p=2;
		q=6;
		r=4;
	}

	if(row!=0)
	{
		if(s.boardState[row-1][column].size()==0)
		{
			result.push_back(make_tuple(row-1,column));
			goto l2 ;
		}
			
		stoneNum=s.boardState[row-1][column][s.boardState[row-1][column].size()-1];	
		if(stoneNum!=p && stoneNum!=q && stoneNum!=r)
		{
			result.push_back(make_tuple(row-1,column));
		}
	}
	l2:; 
	if(row!=n-1)
	{
		if(s.boardState[row+1][column].size()==0)
		{
			result.push_back(make_tuple(row+1,column));
			goto l3 ;
		}
			
		stoneNum=s.boardState[row+1][column][s.boardState[row+1][column].size()-1];	
		if(stoneNum!=p && stoneNum!=q && stoneNum!=r)
		{
			result.push_back(make_tuple(row+1,column));
		}
	}
	l3:;

	if(column!=0)
	{
		if(s.boardState[row][column-1].size()==0)
		{
			result.push_back(make_tuple(row,column-1));
			goto l4 ;
		}
		
		stoneNum=s.boardState[row][column-1][s.boardState[row][column-1].size()-1];	
		if(stoneNum!=p  && stoneNum!=q && stoneNum!=r)
		{
			result.push_back(make_tuple(row,column-1));
		}
	}
	l4:;

	if(column!=n-1)
	{	
		if(s.boardState[row][column+1].size()==0)
		{
			result.push_back(make_tuple(row,column+1));
			goto l5 ;
		}
		stoneNum=s.boardState[row][column+1][s.boardState[row][column+1].size()-1];	
		if(stoneNum!=p  && stoneNum!=q && stoneNum!=r)
		{
			result.push_back(make_tuple(row,column+1));
		}
	}
	l5:;
	return result;
}

double straightStones(state &s)
{
	double out=0;
	int n = s.boardState.size();
	set< tuple<int,int> > visited;
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<n;j++)
		{
			double inout=0;

			tuple< int, int > t1 = make_tuple(i,j);
			int init=visited.size();
			visited.insert(t1);

			if(visited.size()!=init && s.boardState[i][j].size()!=0)
			{

				int tem=s.boardState[i][j][s.boardState[i][j].size()-1];
				if(tem==1||tem==5)
				{
				//cout<<s.boardState[i][j][s.boardState[i][j].size()-1]<<'\n';
				tuple< int, int > t = make_tuple(i,j);

				//cout<<"size="<<neighbours(s,t).size()<<'\n';
				vector<tuple<int,int> > neigh123= neighbours(s,t,1);
				if(neigh123.size()==1)
				{
					double sizeLine=0;
					stack< tuple<int,int> > mystack;
					set< tuple<int,int> > myset;
					mystack.push(neigh123[0]);
					//sizeLine+=1;
					while(!mystack.empty())
					{
						//tuple< int, int > centre;
						tuple< int, int > current = mystack.top();
						mystack.pop();

						int initialSize=myset.size();
						myset.insert(current);
						visited.insert(current);
						if(initialSize!=myset.size())
						{
							sizeLine+=1;
							vector<tuple<int,int> > neigh= neighbours(s,current,1);
							for(int i=0;i<neigh.size();i++)
							{
								mystack.push(neigh[i]);
							}
						}	
					inout+=sizeLine;
					}
					out+=sizeLine;
				}
				}
			}
		}
	}
	return out;
}


bool checkRoadWin(state &s, int num)
{	
	int p,q;
	if(num==1)
		{p=1;q=5;}
	else
		{p=2;q=6;}
	int n= s.boardState.size();
	bool f = false;
	for(int i=0;i<n && f==false;i++)
	{
		for(int j=0;j<n;j++)
		{
			if(i==0 || i==n-1)
			{
				if(s.boardState[i][j].size()!=0)
				{
					int numStone = s.boardState[i][j][s.boardState[i][j].size()-1];
					if(numStone==p  || numStone==q)
					{
						f= true;
						goto l6;
						break;
					}
				}		
			}else if(j==0 || j==(n-1))
			{			
				if( s.boardState[i][j].size()!=0)
				{
					int numStone = s.boardState[i][j][s.boardState[i][j].size()-1];
					if(numStone==p || numStone==q)
					{
						f= true;
						goto l6;
						break;
					}
				}
			}
		}
		if(i==n-1)
			return false;
	}

	l6:;

	for(int t1=0;t1<n;t1++)
	{
	int numStone;
	if(s.boardState[t1][0].size()==0)
		continue ;
	numStone = s.boardState[t1][0][s.boardState[t1][0].size()-1];	
	if(numStone!=p && numStone!=q)
		continue;

	stack< tuple<int,int> > mystack;
	set< tuple<int,int> > myset;
	
	mystack.push(make_tuple(t1,0));
	while(!mystack.empty())
	{
		tuple<int,int> current = mystack.top();
		mystack.pop();
		int initialSize=myset.size();
		myset.insert(current);
		if(myset.size()==initialSize)
			continue;
		else{
			if(get<1>(current)==n-1)
				return true;
			{
				vector<tuple<int,int> > n=neighbours(s,current,num);
				for(int j=0;j<n.size();j++)
				{
					//if(neighbours(s,current)[j]!=mystack.top())
						mystack.push(n[j]);		
				}
			}
		}
	}
		
	}
	
	for(int t2=0;t2<n;t2++)
	{
	if(s.boardState[0][t2].size()==0)
		continue ;
	int numStone = s.boardState[0][t2][s.boardState[0][t2].size()-1];	
	if(numStone!=p && numStone!=q)
		continue;
	stack< tuple<int,int> > mystack;
	set< tuple<int,int> > myset;
	
	mystack.push(make_tuple(0,t2));
	while(!mystack.empty())
	{
		tuple<int,int> current = mystack.top();
		mystack.pop() ;
		int initialSize=myset.size();
		myset.insert(current);
		if(myset.size()==initialSize)
			continue;
		else{
			if(get<0>(current)==n-1)
				return true;
			{
				vector<tuple<int,int> > n=neighbours(s,current,num);
			
				for(int j=0;j<n.size();j++)
				{
					//if(neighbours(s,current)[j]!=mystack.top())
						mystack.push(n[j]);		
				}
			}
		}
	}
	
	}

	return false;
}


double oneLess1(state &s,int i,int a, int who)
{
	int n=s.boardState.size();
	double result=0;
	int p,q;
	if(who==1)
	{
		p=1;
		q=5;
	}else{
		p=2;
		q=6;
	}
	for(int j=0;j<n;j++)
	{
		
		if(s.boardState[i][j].size()!=0)
		{
			int num=s.boardState[i][j][s.boardState[i][j].size()-1];
			if(num==p||num==q)
			{
				stack< tuple<int,int> > mystack;
				set< tuple<int,int> > myset;
				mystack.push(make_tuple(i,j));
				while(!mystack.empty())
				{
					tuple<int,int> current = mystack.top();
					mystack.pop();
					int initialSize=myset.size();
					myset.insert(current);
					if(myset.size()!=initialSize)
					{
						if(get<0>(current)==a)
						{
							result+=1;
							goto a1;//TODO
						}
						vector<tuple<int,int> > v1=neighbours(s,current,who);
						for(int k=0;k<v1.size();k++)
						{
							mystack.push(v1[k]);		
						}
					}
		
				}
			}

		}
		a1:;
	}
	return result;
}

double oneLess2(state &s,int j,int a, int who)
{
	int n=s.boardState.size();
	double result=0;
	int p,q;
	if(who==1)
	{
		p=1;
		q=5;
	}else{
		p=2;
		q=6;
	}
	for(int i=0;i<n;i++)
	{
		if(s.boardState[i][j].size()!=0)
		{
			int num=s.boardState[i][j][s.boardState[i][j].size()-1];
			if(num==p||num==q)
			{
				stack< tuple<int,int> > mystack;
				set< tuple<int,int> > myset;
				mystack.push(make_tuple(i,j));
				while(!mystack.empty())
				{
					tuple<int,int> current = mystack.top();
					mystack.pop();
					int initialSize=myset.size();
					myset.insert(current);
					if(myset.size()!=initialSize)
					{
						if(get<1>(current)==a)
						{
							result+=1;
							goto a1;//TODO
						}
						vector<tuple<int,int> > v1=neighbours(s,current,who);
						for(int k=0;k<v1.size();k++)
						{
							mystack.push(v1[k]);		
						}
					}
		
				}
			}

		}
		a1:;
	}
	return result;
}


vector < vector<tuple<int,int> > > aux1(state &s, int t, int who)
{
	int n = s.boardState.size();
	vector< vector<tuple<int,int> > > out;
	int p,q;
	if(who==1){
		p=1;
		q=5;
	}else{
		p=2;
		q=6;
	}

	for(int i=0;i<n;i++)
	{
		if(s.boardState[i][t].size()!=0)
		{
			int num=s.boardState[i][t][s.boardState[i][t].size()-1];
			if(num==p || num ==q)
			{
				vector< tuple<int,int> > v2;
				stack< tuple<int,int> > mystack;
				set< tuple<int,int> > myset;
	
				mystack.push(make_tuple(i,t));
				while(!mystack.empty())
				{
					tuple<int,int> current = mystack.top();
					mystack.pop();
					int initialSize=myset.size();
					myset.insert(current);
					if(myset.size()!=initialSize)
					{
						int flag=0;
						vector<tuple<int,int> > v1=neighbours(s,current,who);
						for(int j=0;j<v1.size();j++)
						{
							int sizen=myset.size();
							myset.insert(v1[j]);
							if(myset.size()!=sizen)
							{
								mystack.push(v1[j]);
								myset.erase(v1[j]);
								flag=1;
							}				
						}
						if(flag==0)
						{
							//v2=notNeighbours(s,current);
							/*for(int t=0;t<v2.size();t++)
							{
								cout<<get<0>(v2[t])<<get<1>(v2[t])<<'\n';
							}*/
							//out.push_back(v2);
							std::set<tuple<int,int> >::iterator it;
							for (it = myset.begin(); it != myset.end(); ++it)
							{
								out.push_back(notNeighbours(s,*it,who));
							}
						}
					}
				}
			}
		}
	}
	return out;
}


vector < vector<tuple<int,int> > > aux2(state &s, int t, int who)
{
	int n = s.boardState.size();
	vector< vector<tuple<int,int> > > out;
	int p,q;
	if(who==1){
		p=1;
		q=5;
	}else{
		p=2;
		q=6;
	}

	for(int i=0;i<n;i++)
	{
		if(s.boardState[t][i].size()!=0)
		{
			int num=s.boardState[t][i][s.boardState[t][i].size()-1];
			if(num==p || num==q)
			{
				vector<tuple<int,int> > v2;
				stack< tuple<int,int> > mystack;
				set< tuple<int,int> > myset;
	
				mystack.push(make_tuple(t,i));
				while(!mystack.empty())
				{
					tuple<int,int> current = mystack.top();
					mystack.pop();
					int initialSize=myset.size();
					myset.insert(current);
					if(myset.size()!=initialSize)
					{
						int flag=0;
						vector<tuple<int,int> > v1=neighbours(s,current,who);
						for(int j=0;j<v1.size();j++)
						{
							int sizen=myset.size();
							myset.insert(v1[j]);
							if(myset.size()!=sizen)
							{
								mystack.push(v1[j]);
								myset.erase(v1[j]);
								flag=1;
							}
										
						}
						if(flag==0)
						{
							std::set<tuple<int,int> >::iterator it;
							for (it = myset.begin(); it != myset.end(); ++it)
							{
								out.push_back(notNeighbours(s,*it, who));
							}
						}
					}
					
				}
			}
		}
	}
	return out;
}


double intersection(vector < vector<tuple<int,int> > > &a, vector < vector<tuple<int,int> > > &b)
{
	double answer=0;
	for(int i=0;i<a.size();i++)
	{
		for(int j=0;j<b.size();j++)
		{
			for(int k=0;k<a[i].size();k++)
			{
				for(int l=0;l<b[j].size();l++)
				{
					if(get<0>(a[i][k])==get<0>(b[j][l]) && get<1>(a[i][k])==get<1>(b[j][l]))
						answer+=1;
				}
			}
		}
	}
	return answer;
}


double oneRemaining(state &s, int num)
{
	int n = s.boardState.size();
	double result=0;

	result+=oneLess1(s,0,n-2,num);
	//cout<<"oneless1"<<oneLess1(s,0,n-2)<<'\n';
	result+=oneLess1(s,n-1,1,num);
	//cout<<"oneless1"<<oneLess1(s,n-1,1)<<'\n';
	result+=oneLess2(s,0,n-2,num);
	//cout<<"oneless2"<<oneLess2(s,0,n-2)<<'\n';
	result+=oneLess2(s,n-1,1,num);
	//cout<<"oneless2"<<oneLess2(s,n-1,1)<<'\n';

	vector < vector<tuple<int,int> > > side1 = aux1(s, 0, num);
	vector < vector<tuple<int,int> > > side2 = aux1(s, n-1, num);
	vector < vector<tuple<int,int> > > side3 = aux2(s, 0, num);
	vector < vector<tuple<int,int> > > side4 = aux2(s, n-1, num);
	
	//cout<<"size 1 = "<<side1.size()<<"size 2 = "<<side2.size()<<'\n';
	if(side1.size()!=0 && side2.size()!=0)
	{
		
		//cout<<"intersection1"<<intersection(side1,side2)<<'\n';
		result+=intersection(side1,side2);
	}

	if(side3.size()!=0 && side4.size()!=0)
	{
		
		//cout<<"intersection3"<<intersection(side3,side4)<<'\n';
		result+=intersection(side3,side4);
	}

	return result;
}


double evalFxn(state s)
{
	//cerr<<"yoyo"<<endl;
	double val = 0.0 ;
	if(checkRoadWin(s,2))
	{	//cout<<"yes its happening"<<endl;
		return -10000000.00;
	}
	if(checkRoadWin(s,1))
	{	
		//cout<<"yes its happening 2"<<endl;
		return 10000000.00 ;
	}
	//-facefeat(s,2)
	/*double * facefeatures;
	facefeatures=facefeat(s,1);
	double * facefeatures2;
	facefeatures2=facefeat(s,2);
	double * influenceval;
	influenceval=influence(s);
	*/
	influence(s);
	facefeat(s,1);
	ss=straightStones(s);
	oneremaining1=oneRemaining(s,1);
	oneremaining2=oneRemaining(s,2);
	/*cerr<<"facefeatures= "<<facefeat10<<endl;
	cerr<<"influence= "<<influence0<<endl;
	cerr<<"straightstones= "<<ss<<endl;
	*/
	val=weights[0]*influence0+weights[1]*influence1+weights[2]*influence2+weights[3]*facefeat10-weights[10]*facefeat20+weights[4]*facefeat11-weights[11]*facefeat21+weights[5]*facefeat12-weights[12]*facefeat22+weights[6]*facefeat13-weights[13]*facefeat23+weights[7]*ss+weights[8]*oneremaining1+weights[9]*oneremaining2;
	//cerr<<val<<endl;
	return val ;   //returns a evaluation of state
}

//TODO check for standing stone in straightstones function
//add some evaluation value for number of stacks controlled