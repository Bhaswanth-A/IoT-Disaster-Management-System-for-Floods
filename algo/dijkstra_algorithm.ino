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
  int i,j,u;
  int cost[n][n], distance[n],pred[n];
  int visited[n],count,mindistance,nextnode;
  
  // int arr[n][n] = { { 0,1,MAX,MAX,1,1,MAX,MAX,MAX,MAX,MAX,MAX,MAX,MAX,MAX,MAX },
     //                   { 1,0,1,MAX,1,1,1,MAX,MAX,MAX,MAX,MAX,MAX,MAX,MAX,MAX },
     //                   { MAX,1,0,1,MAX,1,1,1,MAX,MAX,MAX,MAX,MAX,MAX,MAX,MAX },
     //                   { MAX,MAX,1,0,MAX,MAX,1,1,MAX,MAX,MAX,MAX,MAX,MAX,MAX,MAX },
     //                   { 1,1,MAX,MAX,0,1,MAX,MAX,1,1,MAX,MAX,MAX,MAX,MAX,MAX },
     //                   { MAX, 1, 1, MAX, 1, 0, MAX, 1, 1 },
     //                   { MAX, MAX, MAX, 1, 1, MAX, 0, 1, MAX },
      //                  { MAX, MAX, MAX, 1, 1, 1, 1, 0, 1 },
      //                  { MAX, MAX, MAX, MAX, 1, 1, MAX, 1, 0 }};
  
  int arr[n][n] = { { 0, 1, MAX, 1, 1, MAX, MAX, MAX, MAX },
                        { 1, 0, 1, 1, 1, 1, MAX, MAX, MAX },
                        { MAX, 1, 0, MAX, 1, 1, MAX, MAX, MAX },
                        { 1, 1, MAX, 0, 1, MAX, 1, 1, MAX },
                        { 1, 1, 1, 1, 0, 1, 1, 1, 1 },
                        { MAX, 1, 1, MAX, 1, 0, MAX, 1, 1 },
                        { MAX, MAX, MAX, 1, 1, MAX, 0, 1, MAX },
                        { MAX, MAX, MAX, 1, 1, 1, 1, 0, 1 },
                        { MAX, MAX, MAX, MAX, 1, 1, MAX, 1, 0 }};
  
  
  for(i=0;i<n;i++){
    for(j=0;j<n;j++){
      if(arr[i][j]==0){
        cost[i][j] = MAX;
      }
      else{
        cost[i][j] = arr[i][j];
      }
    }
  }
  
  for(i=0;i<n;i++)
  {
    distance[i] = cost[n1][i];
    pred[i] = n1;
    visited[i] = 0;
  }
  distance[n1] = 0;
  visited[n1] = 1;
  count = 1;
  
  while(count<=n+5)
  {
    mindistance = MAX;
    
    for(i=0;i<n;i++)
    {
      if(distance[i]<mindistance && !visited[i])
      {
        mindistance = distance[i];
        nextnode = i;
      }
    }
    
    visited[nextnode] = 1;
    for(i=0;i<n;i++)
    {
      if(!visited[i])
      {
        if(mindistance + cost[nextnode][i] < distance[i]){
          distance[i] = mindistance + cost[nextnode][i];
          pred[i] = nextnode;
        }
        count++;
      }
    }
  }
  
  
  
  for(i=0;i<n;i++)
  {
    if(i!=n1){
      Serial.println("");
      Serial.print("Distance of node");
      Serial.print(i);
      Serial.print("=");
      Serial.println(distance[i]);
      Serial.print("Path=");
      Serial.print(i);
      
      Serial.println("");
      
      if(distance[i]==1)
      {
        Serial.println(i);
      }
      if(distance[i]==2)
      {
        Serial.println(pred[i]);
      }
      
      j=i;
      do
      {
        j=pred[j];
        Serial.print("<-");
        Serial.print(j);
      }while(j!=n1);
    }
  }        
}
