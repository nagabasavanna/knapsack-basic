#include<iostream>//unbounded knapsack related problems
#include<vector>
#include<algorithm>

using namespace std;

class Knapsack
{
	public:
	int memoize(int wt[],int val[],int W,int N);
	int util(int wt[],int val[],int W,int N,vector<vector<int>> &memo);
	int tab(int wt[],int val[],int W,int N);// rod cutting problem is same as this
	int coinChangeWays(int coin[],int S,int N);
	int minCoinChange(int coin[],int S ,int N);

	
};

int main()
{
	// int   capacity = 8;				//capacity is same as total length
    // int val[] = {10, 40, 50, 70};	//val is same as price
    // int  wt[]  = {1, 3, 4, 5} ;     //wt is same as length 
	// //110 answer
	int coin[]={9, 6, 5, 1}; 
	int Sum=11;
	
	Knapsack k;
	//cout<<"memoized answer "<<k.memoize(wt,val,capacity,4);
	//cout<<"tabulation answer "<<k.tab(wt,val,capacity,4);
	//cout<<"no of ways to change coins "<<k.coinChangeWays(coin,Sum,3);
	cout<<"min ways of coin change " <<k.minCoinChange(coin,Sum,4);
}

int Knapsack::memoize(int wt[],int val[],int W,int N)
{
	vector<vector<int>> memo(N+1,vector<int>(W+1,-1));
	return util(wt,val,W,N,memo);
}

int Knapsack::util(int wt[],int val[],int W,int N,vector<vector<int>> &memo)
{
	if(memo[N][W]!=-1)
		return memo[N][W];
	if(N==0 or W==0)
		return 0;

	if(wt[N-1]>W)
		memo[N][W]= util(wt,val,W,N-1,memo);
	else
		memo[N][W]= max(util(wt,val,W,N-1,memo),val[N-1]+util(wt,val,W-wt[N-1],N,memo));
	return memo[N][W];
}

int Knapsack::tab(int wt[],int val[],int W,int N)
{
	vector<vector<int>> tab(N+1,vector<int>(W+1,-1));
	for(int i=0;i<=N;++i)
	{
		for(int j=0;j<=W;++j)
		{
			if(i==0 or j == 0)
				tab[i][j]=0;
			else if (wt[i-1]>j)
				tab[i][j]=tab[i-1][j];
			else 
				tab[i][j] = max(tab[i-1][j],val[i-1]+tab[i][j-wt[i-1]]);
		}
	}
	return tab[N][W];
}

int Knapsack::coinChangeWays(int coin[],int S,int N)
{
	if(S==0)
		return 1;
	if(N==0)
		return 0;
	if(coin[N-1]>S)
		return coinChangeWays(coin,S,N-1);
	else 
		return coinChangeWays(coin,S,N-1) + coinChangeWays(coin,S-coin[N-1],N);
}

int Knapsack::minCoinChange(int coin[],int S,int N)
{
	// RECURSIVE OR BRUTE FORCE WAY
	// if(S==0)
	// 	return 0;
	// if(N==0)
	// 	return INT_MAX-1;
	// if(coin[N-1]>S)
	// 	return minCoinChange(coin,S,N-1);
	// else 
	// 	return min(minCoinChange(coin,S,N-1),1+minCoinChange(coin,S-coin[N-1],N));
	vector<vector<int>> tab(N+1,vector<int>(S+1));
	for(int i=0;i<=N;++i)
	{
		for(int j=0;j<=S;++j)
		{
			if(j==0)
			tab[i][j]=0;
			else if(i==0)
			tab[i][j]=INT_MAX-1;//since adding 1 to int maxs gives overflow error
			else if(coin[i-1]>j)
			tab[i][j] = tab[i-1][j];
			else 
			tab[i][j] = min(tab[i-1][j],1+tab[i][j-coin[i-1]]);
		}
	}
	return tab[N][S];
}