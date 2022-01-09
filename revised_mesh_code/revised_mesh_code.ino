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
  
  
  if(arr[n1][n2]-arr[n1][n1]>1 || arr[n1][n1]-arr[n1][n2]>1){
    nextNode = 4;
  }
  
  if(arr[n1][n2]-arr[n1][n1]==1 || arr[n1][n1]-arr[n1][n2]==1){
    nextNode = n2;
  }
  
  return nextNode;      
}
