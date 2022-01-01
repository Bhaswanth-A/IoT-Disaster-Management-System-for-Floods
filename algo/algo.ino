void setup() {
  Serial.begin(9600);
  mathAlgo(0,8);
}

void loop() {

}

void mathAlgo(int n1, int n2)
{
  int MAX = 100;
  int n = 9;
  int x[3][3];
  int k=0,p=0;
  int nextNode=0;
  
  int arr[n][n] = { { 0, 1, MAX, 1, 1, MAX, MAX, MAX, MAX },
                        { 1, 0, 1, 1, 1, 1, MAX, MAX, MAX },
                        { MAX, 1, 0, MAX, 1, 1, MAX, MAX, MAX },
                        { 1, 1, MAX, 0, 1, MAX, 1, 1, MAX },
                        { 1, 1, 1, 1, 0, 1, 1, 1, 1 },
                        { MAX, 1, 1, MAX, 1, 0, MAX, 1, 1 },
                        { MAX, MAX, MAX, 1, 1, MAX, 0, 1, MAX },
                        { MAX, MAX, MAX, 1, 1, 1, 1, 0, 1 },
                        { MAX, MAX, MAX, MAX, 1, 1, MAX, 1, 0 }};
    
    
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
      x[p][k] = arr[n1][j-1];
      k++;
      if(k==3){
        k=0;
        p++;
      }
    }
  
  
  for(int i=0;i<3;i++){
    for(int j=0;j<3;j++){
      Serial.print(x[i][j]);
      Serial.print(" ");
    }
    Serial.println(" ");
  }
  
  if(arr[n1][n2]-arr[n1][n1]>1 || arr[n1][n1]-arr[n1][n2]>1){
    nextNode = 4;
  }
  
  if(arr[n1][n2]-arr[n1][n1]==1 || arr[n1][n1]-arr[n1][n2]==1){
    nextNode = n2;
  }
  Serial.println(nextNode);  
        
}
