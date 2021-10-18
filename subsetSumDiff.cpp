#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

class Sol
{
	public:
	int MSSD(int arr[],int N);//minimum of subset sum difference
	int util(int arr[],int N,int sum);

	int CNSD(int arr[],int N,int Diff);//count no of subsets for given diff 
};
int main()
{
	Sol s;
	int arr[]={2,3,1,1};
	// int arr[]={4,6,5,11};
	int N = sizeof(arr)/sizeof(arr[0]);
	//cout<<"minimum is "<<s.MSSD(arr,N);//output should be 1
	cout<<"no of subset with given difference is "<<s.CNSD(arr,N,1);
	
	
}

int Sol::MSSD(int arr[],int N)
{
	
	int sum = 0;
	for(int i = 0;i<N;++i)
		sum+=arr[i];
	return util(arr,N,sum);
	
}

int Sol::CNSD(int arr[],int N,int diff)
{
	int sum=0;
	for(int i=0;i<N;++i)
		sum+=arr[i];
	int S=(sum-diff)/2;						//here s means a subset 
	vector<vector<int>> tab(N+1,vector<int>(S+1));//if a subset occurs n times then other subset
	for(int i = 0;i<= N; ++i)						//too occurs n times so n count 
	{
		for(int j=0;j<=S; ++j)
		{
			if(j==0)
				tab[i][j]=1;
			else if (i==0)
				tab[i][j]=0;
			else if (arr[i-1]>j)
				tab[i][j]=tab[i-1][j];
			else 
				tab[i][j]=tab[i-1][j-arr[i-1]] + tab[i-1][j];
		}
	}
	return tab[N][S];
}

int Sol::util(int arr[],int N, int sum)
{
	int S= sum/2;
	vector<vector<bool>> tab(N+1,vector<bool>(S+1));
	for(int i = 0;i<= N; ++i)
	{
		for(int j=0;j<=S; ++j)
		{
			if(j==0)
				tab[i][j]=true;
			else if (i==0)
				tab[i][j]=false;
			else if (arr[i-1]>j)
				tab[i][j]=tab[i-1][j];
			else 
				tab[i][j]=tab[i-1][j-arr[i-1]] or tab[i-1][j];
		}
	}
	int minimum=INT_MAX;
	for(int i=0;i<=S;++i)
	{									//let s1 be fist sum,s2 be second sum
		if(tab[N][i]==true)				//now for s2-s1 to be minimum
			minimum=min(minimum,sum-2*i); //s2=sum-s1; So s2-s1 =sum-s1-s1;here s1 is "i" until half of sum
	}
	return minimum;
}