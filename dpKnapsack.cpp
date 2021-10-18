#include<iostream>
#include<algorithm>
#include<vector>

using namespace std;

class Knapsack
{
    public:
    int knapsackMemo (int wt[],int val[], int W, int n,vector<vector<int>> &memo);
    int knapsackTab  (int wt[],int val[], int W, int N);
};

 int main(){
    //  int value[] =  { 2, 4, 7, 3, 6, 33, 96, 77,7};
    //  int weight[]= { 3, 6, 7, 2, 8,  3, 55, 22,5};
    //  int capacity=100;
	int value[] = { 60, 100, 120 };
	int weight[] = { 10, 20, 30 };
	int capacity = 50;
     int n = sizeof(value)/sizeof(value[0]);
     vector<vector<int>> memory(n+1,vector<int>(capacity+1,-1));//here n'+1' and W '+1' important
     Knapsack ks;
     cout<<ks.knapsackTab(weight,value,capacity,n);
 
 }


// using simple recursion, takes O(2^n) times
int Knapsack::knapsackMemo( int wt[],int val[],int W, int n,vector<vector<int>> &memo)
{          //should be carefull while receiving vector as parameter "&" is important
      if(memo[n][W]!=-1)
    {
        return memo[n][W];
    }
    
    if(n==0 or W ==0)
    { 
        return 0;
    }
    if(wt[n-1]>W)
    {
        memo[n][W]= knapsackMemo(wt,val,W,n-1,memo);
        return memo[n][W];
    }
    memo[n][W]= max(knapsackMemo(wt,val,W,n-1,memo),val[n-1]
                                + 
                knapsackMemo(wt,val,W-wt[n-1],n-1,memo));
    return memo[n][W];
}



int Knapsack::knapsackTab(int wt[],int val[],int W,int n)
{ //	cout<<"W ="<<W<<"; n = "<<n<<endl;

	vector<vector<int>> tab(n+1,vector<int>(W+1)); //vector initialization with default zero 
                                                  //to initialize with say x it's "tab(n+1,vector<int>(W+1,x))" 
	for (int i = 0; i <= n ; ++i)
	{
		for(int j = 0;j <= W  ; ++j)
		{
			if(i==0 || j==0)
			{
				tab[i][j] = 0;
				
			}
			else if(wt[i-1]>j)
			{
				tab[i][j] = tab[i-1][j];
				
			}
			else
			{	// maximum of excluding and including present element
				tab[i][j] = max( tab[i-1][j] , 
                 val[i-1] + tab[i-1][j-wt[i-1]]);
				
			}

		}
		//cout<<endl;
	}
	return tab[n][W];
}

