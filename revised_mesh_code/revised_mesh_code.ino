#include "painlessMesh.h"

#define MESH_SSID "disasterManagement"
#define MESH_PASSWORD "password"
#define MESH_PORT 5555


Scheduler userScheduler;
painlessMesh mesh;

String nodeName = "";
String nodeNext = "";
String nodeDestination = "";


void sendMessage();

Task taskSendMessage(TASK_SECOND * 1, TASK_FOREVER, &sendMessage);

void sendMessage(){
  String msg = String(nodeDestination);
  String to = nodeNext;
  mesh.sendSingle(to, msg);
}

void receivedCallback(uint32_t from, String &msg){
  nodeNext = mathAlgo(nodeName.toInt(), msg.toInt());
}

void newConnectionCallback(uint32_t nodeId){
  Serial.print("New connection, NodeId = ");
  Serial.println(nodeId);
}

void changedConnectionCallback(){
  Serial.println("Changed connection");
}

void setup(){
  Serial.begin(115200);
  mesh.setDebugMsgTypes(ERROR | DEBUG | CONNECTION);

  mesh.init(MESH_SSID, MESH_PASSWORD, &userScheduler, MESH_PORT);

  mesh.setName(nodeName);

  // get destination node number
  Serial.println("Enter Destination Node number: ");
  while(Serial.available()==0){}
  nodeDestination = Serial.readString();

  mesh.onReceive(&receivedCallback);
  mesh.onNewConnection(&newConnectionCallback);
  mesh.onChangedConnection(&changedConnectionCallback);

  nodeNext = String(mathAlgo(nodeName.toInt(),nodeDestination.toInt()));

  userScheduler.addTask(taskSendMessage);
  taskSendMessage.enable();  
}


void loop() {
  mesh.update(); 
}


void mathAlgo(int n1, int n2)  // Dijkstra's algorithm
{
  int MAX = 100;
  int n = 9;
  int i,j,u;
  int cost[n][n], distance[n],pred[n];
  int visited[n],count,mindistance,nextnode;
  int nodeNext;
  
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

    // printing all node distances and paths
//    for(i=0;i<n;i++)
//    {
//      if(i!=n1){
//        Serial.println("");
//        Serial.print("Distance of node");
//        Serial.print(i);
//        Serial.print("=");
//        Serial.println(distance[i]);
//        Serial.print("Path=");
//        Serial.print(i);
//        
//        j=i;
//        do
//        {
//          j=pred[j];
//          Serial.print("<-");
//          Serial.print(j);
//        }while(j!=n1);
//      }
//    }        

  for(i=0;i<n;i++)
  {
    if(i!=n1)
    {         
      Serial.println("");
      
      if(distance[i]==1)
      {
        nodeNext = i;
      }
      if(distance[i]==2)
      {
        nodeNext = pred[i];
      }
      
    }
  }   

  return nodeNext;      
}
