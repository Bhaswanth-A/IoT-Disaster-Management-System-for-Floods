#include "namedMesh.h"

#define MESH_SSID "ssid"
#define MESH_PASSWORD "password"
#define MESH_PORT 5555 // add mesh details


Scheduler userScheduler; // allows us to run tasks in the background
namedMesh mesh;


String nodeName = "<node number>"; // the node name is fixed and will be uploaded into the respective board. Example: nodeName = "0" for node 0.
String nodeNext = ""; // refers to the name of the node next in the path
String nodeDestination = ""; // refers to the name of the destination node

Task taskSendMessage( TASK_SECOND*30, TASK_FOREVER, []() {
  String msg = String(nodeDestination);
  String to = nodeNext;
  mesh.sendSingle(to, msg);
}); // scheduling messages from the source node to the next node


void setup() {
  Serial.begin(115200); // set baud rate
  
  mesh.setDebugMsgTypes(ERROR | DEBUG | CONNECTION); // set before init() so that you can see startup messages
  
  mesh.init(MESH_SSID, MESH_PASSWORD, &userScheduler, MESH_PORT); // initialize mesh with details entered earlier
  
  mesh.setName(nodeName); // set name of the current node
  
  Serial.println("Enter Destination Node number: ");
  while(Serial.available()==0){}
  nodeDestination = Serial.readString(); // take user input for name of destination node
  
  mesh.onReceive([](uint32_t from, String &msg) {
    nodeNext = mathAlgo(nodeName.toInt(),msg.toInt());
  }); // runs the math algo when node receives a message
  
  mesh.onChangedConnections([]() {
  Serial.println("Changed connection");
  }); // executes every time there is a change in mesh topology
  
  nodeNext = String(mathAlgo(nodeName.toInt(),nodeDestination.toInt())); // start path-finding math algorithm
  
  userScheduler.addTask(taskSendMessage); // schedules messages
  taskSendMessage.enable();
}


void loop() {
  mesh.update(); // keeps the mesh running
}


void mathAlgo(int n1, int n2)
{
  int MAX = 100;
  int n = 9;
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
  
//  for(int j=1;j<=n;j++){
//    Serial.print(arr[n1][j-1]);
//    Serial.print(" ");
//    if(j%3==0){
//      Serial.print("\n");
//    }
//  }
  
  if(arr[n1][n2]-arr[n1][n1]>1 || arr[n1][n1]-arr[n1][n2]>1){
    nextNode = 4;
  }
  
  if(arr[n1][n2]-arr[n1][n1]==1 || arr[n1][n1]-arr[n1][n2]==1){
    nextNode = n2;
  }
  
  return nextNode;      
}
