#include<iostream>//SUBSET SUM PROBLEM
#include<vector>
#include<algorithm>
#include<chrono>
using namespace std::chrono;
using namespace std;

bool SSP(int arr[],int S, int N)//WITHOUT REPITETIVE USE OF ELEMENTS
{
    vector<vector<bool>> tab(N+1,vector<bool>(N+1));
    for(int i=0;i<=N;++i)
    {                        // i=>N
        for(int j=0;j<=S;++j)//j corresponds to S or Sum
        {
            if(j==0)
                tab[i][j]=true;
            else if (i==0)
                tab[i][j]=false;
            else if (arr[i-1]>j)
                tab[i][j]=tab[i-1][j];
            else
                tab[i][j]=tab[i-1][j] or tab[i-1][j-arr[i-1]];
        }
    }

    return tab[N][S];

}

bool ESP(int arr[],int N)//equal sum partition
{
    int sum=0;
    for (int i = 0; i < N; ++i)
    {
       sum+=arr[i];
    }
    if(sum%2!=0)
        return false;
    int S=sum/2;
    vector<vector<int>> tab(N+1,vector<int>(S+1));

    for(int i=0;i <= N ;++i)
    {
        for(int j =0;j <= S ; ++j)
        {
            if(j==0)
                tab[i][j]=true;
            else if (i==0)
                tab[i][j]=false;
            else if(arr[i-1]>j)
                tab[i][j]=tab[i-1][j];
            else
                tab[i][j]=tab[i-1][j] or tab[i-1][j-arr[i-1]];          
        }
    }
    return tab[N][S];
    
}

int main()
{
   
    int arr[]={3,4,5,8};
    // if(SSP(arr,10,4))
    // cout<<"true";
    // else
    // cout<<"false";
    // cout<<endl;
   if(ESP(arr,6))
    cout<<"true";
   else
    cout<<"false";
 
}