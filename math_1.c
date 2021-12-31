#include <stdio.h>

int mathAlgo(int n1, int n2)
{
  int MAX = 100;
  int n = 9;
  
  int arr[n][n] = { { 0, 1, MAX, 1, MAX, MAX, MAX, MAX, MAX },
                        { 1, 0, 1, MAX, 1, MAX, MAX, MAX, MAX },
                        { MAX, 1, 0, MAX, MAX, 1, MAX, MAX, MAX },
                        { 1, MAX, MAX, 0, 1, MAX, 1, MAX, MAX },
                        { MAX, 1, MAX, 1, 0, 1, MAX, 1, MAX },
                        { MAX, MAX, 1, MAX, 1, 0, MAX, MAX, 1 },
                        { MAX, MAX, MAX, 1, MAX, MAX, 0, 1, MAX },
                        { MAX, MAX, MAX, MAX, 1, MAX, 1, 0, 1 },
                        { MAX, MAX, MAX, MAX, MAX, 1, MAX, 1, 0 }};
    
    
    for(int k=0;k<n;k++){
        for(int i=0;i<n;i++){
            for(int j=0;j<n;j++){
                if(arr[i][k] == MAX || arr[k][j] == MAX)
                    continue;
                else if(arr[i][k] + arr[k][j] < arr[i][j]){
                    arr[i][j] = arr[i][k] + arr[k][j];
                }
            }
        }
    }

    
    for(int j=1;j<=n;j++){
        printf("arr[%d][%d] ",arr[n1][j-1]);
        if(j%3==0){
            printf("\n");
        }
    }
}

int main()
{
    mathAlgo(0,8);
    
    return 0;
}