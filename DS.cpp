// #include <iostream>
// #include <algorithm>
// #include <climits>
// #include <cstdlib>
// #include <ctime>
// #include <queue>
// #include <unordered_map>
// #include <vector>
// #include <cstring>
// #include <set>

// using namespace std;

// // ================= GRID =================
// const int N = 100;
// int grid[N][N];
// bool visited[N][N];
// pair<int,int> parent[N][N];

// int dx[4] = {-1,1,0,0};
// int dy[4] = {0,0,-1,1};

// void generateGrid(){
//     for(int i=0;i<N;i++){
//         for(int j=0;j<N;j++){
//             grid[i][j] = (rand()%4==0)?2:0;
//         }
//     }

//     // place stations
//     for(int i=0;i<10;i++){
//         int x = rand()%N;
//         int y = rand()%N;
//         grid[x][y] = 1;
//     }
// }

// pair<int,int> getRandomRoadLocation(){
//     while(true){
//         int x = rand()%N;
//         int y = rand()%N;
//         if(grid[x][y] == 0) return {x,y};
//     }
// }

// // ================= BFS =================
// pair<int,int> nearestStation(pair<int,int> carPos, int &distance){

//     queue<pair<int,int>> q;
//     memset(visited,false,sizeof(visited));

//     for(int i=0;i<N;i++){
//         for(int j=0;j<N;j++){
//             if(grid[i][j]==1){
//                 q.push({i,j});
//                 visited[i][j]=true;
//                 parent[i][j]={-1,-1};
//             }
//         }
//     }

//     while(!q.empty()){
//         auto curr = q.front(); q.pop();

//         if(curr == carPos){
//             distance = 0;
//             pair<int,int> p = curr;

//             while(parent[p.first][p.second] != make_pair(-1,-1)){
//                 p = parent[p.first][p.second];
//                 distance++;
//             }
//             return curr;
//         }

//         for(int i=0;i<4;i++){
//             int nx = curr.first + dx[i];
//             int ny = curr.second + dy[i];

//             if(nx>=0 && ny>=0 && nx<N && ny<N &&
//                !visited[nx][ny] && grid[nx][ny]!=2){

//                 visited[nx][ny]=true;
//                 parent[nx][ny]=curr;
//                 q.push({nx,ny});
//             }
//         }
//     }

//     return {-1,-1};
// }

// // ================= PATH GRID =================
// void showPathGrid(pair<int,int> carPos){

//     vector<pair<int,int>> path;

//     pair<int,int> p = carPos;

//     // build path
//     while(p.first != -1){
//         path.push_back(p);
//         p = parent[p.first][p.second];
//     }

//     reverse(path.begin(), path.end());

//     int minX=N, minY=N, maxX=0, maxY=0;

//     for(auto &c : path){
//         minX = min(minX, c.first);
//         minY = min(minY, c.second);
//         maxX = max(maxX, c.first);
//         maxY = max(maxY, c.second);
//     }

//     minX = max(0, minX-2);
//     minY = max(0, minY-2);
//     maxX = min(N-1, maxX+2);
//     maxY = min(N-1, maxY+2);

//     set<pair<int,int>> pathSet(path.begin(), path.end());

//     cout << "\n===== PATH MAP =====\n";

//     for(int i=minX;i<=maxX;i++){
//         for(int j=minY;j<=maxY;j++){

//             if(i==carPos.first && j==carPos.second){
//                 cout << "C ";
//             }
//             else if(grid[i][j]==1){
//                 cout << "S ";
//             }
//             else if(pathSet.count({i,j})){
//                 cout << "0 ";   // 🔥 PATH
//             }
//             else{
//                 cout << ". ";   // EVERYTHING ELSE
//             }
//         }
//         cout << "\n";
//     }
// }
// // ================= DATA STRUCTURES =================
// class CustomerNode {
// public:
//     string id, name, email, password, car;
//     CustomerNode *next;

//     CustomerNode(string i,string n,string e,string p,string c){
//         id=i; name=n; email=e; password=p; car=c;
//         next=NULL;
//     }
// };

// CustomerNode *customerHead=NULL;
// int custCount=0;

// class StationNode {
// public:
//     string id, name;
//     int cost;
//     StationNode *next;

//     StationNode(string i,string n,int c){
//         id=i; name=n; cost=c;
//         next=NULL;
//     }
// };

// StationNode *stationHead=NULL;
// int stationCount=0;

// // Queue
// class QueueNode{
// public:
//     string customerID;
//     QueueNode *next;

//     QueueNode(string id){
//         customerID=id;
//         next=NULL;
//     }
// };

// class Queue{
// public:
//     QueueNode *front,*rear;

//     Queue(){ front=rear=NULL; }

//     bool empty(){ return front==NULL; }

//     void push(string id){
//         QueueNode *n=new QueueNode(id);
//         if(empty()) front=rear=n;
//         else{
//             rear->next=n;
//             rear=n;
//         }
//     }

//     int size(){
//         int count=0;
//         QueueNode *t=front;
//         while(t){ count++; t=t->next; }
//         return count;
//     }
// };

// unordered_map<string,Queue> stationQueues;
// unordered_map<string,int> batteryNeed;

// // ================= WAIT + BILL =================
// int getWaitTime(string id,int need){
//     Queue &q=stationQueues[id];
//     int total=0;

//     QueueNode *t=q.front;
//     while(t){
//         total += batteryNeed[t->customerID]*30;
//         t=t->next;
//     }

//     total += need*30;
//     return total;
// }

// int getBill(int need,int cost){
//     return need*cost;
// }

// // ================= FIND BEST =================
// void findBestStation(CustomerNode *user){

//     int curr,req;
//     cout<<"Enter Current Battery %: "; cin>>curr;
//     cout<<"Enter Required Battery %: "; cin>>req;

//     int need = max(0,req-curr);
//     batteryNeed[user->id]=need;

//     pair<int,int> carPos = getRandomRoadLocation();

//     int dist;
//     nearestStation(carPos,dist);

//     cout<<"\nCar Location: ("<<carPos.first<<","<<carPos.second<<")\n";
//     cout<<"Distance Needed: "<<dist<<"%\n";

//     if(dist > curr){
//         cout<<"Battery NOT enough!\n";
//         return;
//     }

//     showPathGrid(carPos);

//     StationNode *temp=stationHead;
//     StationNode *best=NULL;
//     int bestScore=INT_MAX;

//     while(temp){
//         int wait = getWaitTime(temp->id,need);
//         int bill = getBill(need,temp->cost);

//         cout<<"\nStation: "<<temp->name;
//         cout<<"\nWait: "<<wait/60<<" mins";
//         cout<<"\nCost: "<<bill<<"\n";

//         int score = dist + (wait/60) + bill/10;

//         if(score < bestScore){
//             bestScore=score;
//             best=temp;
//         }

//         temp=temp->next;
//     }

//     if(best){
//         cout<<"\n===== BEST =====\n";
//         cout<<"Station: "<<best->name<<"\n";

//         stationQueues[best->id].push(user->id);
//     }
// }

// // ================= BASIC =================
// void addCustomer(){
//     string name,email,pass,car;

//     cout<<"Name: "; cin>>name;
//     cout<<"Email: "; cin>>email;
//     cout<<"Password: "; cin>>pass;
//     cout<<"Car: "; cin>>car;

//     string id="cust"+to_string(++custCount);

//     CustomerNode *n=new CustomerNode(id,name,email,pass,car);

//     if(!customerHead) customerHead=n;
//     else{
//         CustomerNode *t=customerHead;
//         while(t->next) t=t->next;
//         t->next=n;
//     }

//     cout<<"Account Created!\n";
// }

// CustomerNode* loginCustomer(){
//     string email,pass;
//     cout<<"Email: "; cin>>email;
//     cout<<"Password: "; cin>>pass;

//     CustomerNode *t=customerHead;
//     while(t){
//         if(t->email==email && t->password==pass){
//             cout<<"Login Success\n";
//             return t;
//         }
//         t=t->next;
//     }
//     return NULL;
// }

// void addStation(){
//     string name;
//     int cost;

//     cout<<"Station Name: "; cin>>name;
//     cout<<"Cost per %: "; cin>>cost;

//     string id="st"+to_string(++stationCount);

//     StationNode *n=new StationNode(id,name,cost);

//     if(!stationHead) stationHead=n;
//     else{
//         StationNode *t=stationHead;
//         while(t->next) t=t->next;
//         t->next=n;
//     }

//     stationQueues[id]=Queue();

//     cout<<"Station Added!\n";
// }

// // ================= MAIN =================
// int main(){
//     srand(time(0));
//     generateGrid();

//     int choice;

//     while(true){
//         cout<<"\n1.Customer\n2.Vendor\n3.Exit\n";
//         cin>>choice;

//         if(choice==1){
//             int c;
//             cout<<"1.Login\n2.Signup\n";
//             cin>>c;

//             if(c==2) addCustomer();

//             CustomerNode *user = loginCustomer();

//             if(user){
//                 findBestStation(user);
//             }
//         }
//         else if(choice==2){
//             addStation();
//         }
//         else break;
//     }
// }





// #include <iostream>
// #include <algorithm>
// #include <climits>
// #include <cstdlib>
// #include <ctime>
// #include <queue>
// #include <unordered_map>
// #include <vector>
// #include <cstring>
// #include <set>

// using namespace std;

// // ================= GRID =================
// const int N = 100;
// int grid[N][N];
// bool visited[N][N];
// pair<int,int> parent[N][N];

// int dx[4] = {-1,1,0,0};
// int dy[4] = {0,0,-1,1};

// void generateGrid(){
//     for(int i=0;i<N;i++){
//         for(int j=0;j<N;j++){
//             grid[i][j] = (rand()%4==0)?2:0;
//         }
//     }

//     for(int i=0;i<10;i++){
//         int x = rand()%N;
//         int y = rand()%N;
//         grid[x][y] = 1;
//     }
// }

// pair<int,int> getRandomRoadLocation(){
//     while(true){
//         int x = rand()%N;
//         int y = rand()%N;
//         if(grid[x][y] == 0) return {x,y};
//     }
// }

// // ================= BFS =================
// pair<int,int> nearestStation(pair<int,int> carPos, int &distance){

//     queue<pair<int,int>> q;
//     memset(visited,false,sizeof(visited));

//     for(int i=0;i<N;i++){
//         for(int j=0;j<N;j++){
//             if(grid[i][j]==1){
//                 q.push({i,j});
//                 visited[i][j]=true;
//                 parent[i][j]={-1,-1};
//             }
//         }
//     }

//     while(!q.empty()){
//         auto curr = q.front(); q.pop();

//         if(curr == carPos){
//             distance = 0;
//             pair<int,int> p = curr;

//             while(parent[p.first][p.second] != make_pair(-1,-1)){
//                 p = parent[p.first][p.second];
//                 distance++;
//             }
//             return curr;
//         }

//         for(int i=0;i<4;i++){
//             int nx = curr.first + dx[i];
//             int ny = curr.second + dy[i];

//             if(nx>=0 && ny>=0 && nx<N && ny<N &&
//                !visited[nx][ny] && grid[nx][ny]!=2){

//                 visited[nx][ny]=true;
//                 parent[nx][ny]=curr;
//                 q.push({nx,ny});
//             }
//         }
//     }

//     return {-1,-1};
// }

// // ================= PATH MAP =================
// void showPathGrid(pair<int,int> carPos){

//     vector<pair<int,int>> path;

//     pair<int,int> p = carPos;

//     while(p.first != -1){
//         path.push_back(p);
//         p = parent[p.first][p.second];
//     }

//     reverse(path.begin(), path.end());

//     int minX=N, minY=N, maxX=0, maxY=0;

//     for(auto &c : path){
//         minX = min(minX, c.first);
//         minY = min(minY, c.second);
//         maxX = max(maxX, c.first);
//         maxY = max(maxY, c.second);
//     }

//     minX = max(0, minX-2);
//     minY = max(0, minY-2);
//     maxX = min(N-1, maxX+2);
//     maxY = min(N-1, maxY+2);

//     set<pair<int,int>> pathSet(path.begin(), path.end());

//     cout << "\n===== PATH MAP =====\n";

//     for(int i=minX;i<=maxX;i++){
//         for(int j=minY;j<=maxY;j++){

//             if(i==carPos.first && j==carPos.second){
//                 cout << "C ";
//             }
//             else if(grid[i][j]==1){
//                 cout << "S ";
//             }
//             else if(pathSet.count({i,j})){
//                 cout << "0 ";
//             }
//             else{
//                 cout << ". ";
//             }
//         }
//         cout << "\n";
//     }
// }

// // ================= FULL MAP =================
// void showFullMap(pair<int,int> carPos){
//     cout << "\n===== FULL MAP (100x100) =====\n";

//     for(int i=0;i<N;i++){
//         for(int j=0;j<N;j++){

//             if(i==carPos.first && j==carPos.second){
//                 cout << "C ";
//             }
//             else if(grid[i][j] == 1){
//                 cout << "S ";
//             }
//             else if(grid[i][j] == 2){
//                 cout << "# ";
//             }
//             else{
//                 cout << ". ";
//             }
//         }
//         cout << "\n";
//     }
// }

// // ================= DATA STRUCTURES =================
// class CustomerNode {
// public:
//     string id, name, email, password, car;
//     CustomerNode *next;

//     CustomerNode(string i,string n,string e,string p,string c){
//         id=i; name=n; email=e; password=p; car=c;
//         next=NULL;
//     }
// };

// CustomerNode *customerHead=NULL;
// int custCount=0;

// class StationNode {
// public:
//     string id, name;
//     int cost;
//     StationNode *next;

//     StationNode(string i,string n,int c){
//         id=i; name=n; cost=c;
//         next=NULL;
//     }
// };

// StationNode *stationHead=NULL;
// int stationCount=0;

// // Queue
// class QueueNode{
// public:
//     string customerID;
//     QueueNode *next;

//     QueueNode(string id){
//         customerID=id;
//         next=NULL;
//     }
// };

// class Queue{
// public:
//     QueueNode *front,*rear;

//     Queue(){ front=rear=NULL; }

//     bool empty(){ return front==NULL; }

//     void push(string id){
//         QueueNode *n=new QueueNode(id);
//         if(empty()) front=rear=n;
//         else{
//             rear->next=n;
//             rear=n;
//         }
//     }
// };

// unordered_map<string,Queue> stationQueues;
// unordered_map<string,int> batteryNeed;

// // ================= WAIT + BILL =================
// int getWaitTime(string id,int need){
//     Queue &q=stationQueues[id];
//     int total=0;

//     QueueNode *t=q.front;
//     while(t){
//         total += batteryNeed[t->customerID]*30;
//         t=t->next;
//     }

//     total += need*30;
//     return total;
// }

// int getBill(int need,int cost){
//     return need*cost;
// }

// // ================= FIND BEST =================
// void findBestStation(CustomerNode *user){

//     int curr,req;
//     cout<<"Enter Current Battery %: "; cin>>curr;
//     cout<<"Enter Required Battery %: "; cin>>req;

//     int need = max(0,req-curr);
//     batteryNeed[user->id]=need;

//     pair<int,int> carPos = getRandomRoadLocation();

//     int dist;
//     nearestStation(carPos,dist);

//     cout<<"\nCar Location: ("<<carPos.first<<","<<carPos.second<<")\n";
//     cout<<"Distance Needed: "<<dist<<"%\n";

//     if(dist > curr){
//         cout<<"Battery NOT enough!\n";
//         return;
//     }

//     showPathGrid(carPos);

//     StationNode *temp=stationHead;
//     StationNode *best=NULL;
//     int bestScore=INT_MAX;

//     while(temp){
//         int wait = getWaitTime(temp->id,need);
//         int bill = getBill(need,temp->cost);

//         cout<<"\nStation: "<<temp->name;
//         cout<<"\nWait: "<<wait/60<<" mins";
//         cout<<"\nCost: "<<bill<<"\n";

//         int score = dist + (wait/60) + bill/10;

//         if(score < bestScore){
//             bestScore=score;
//             best=temp;
//         }

//         temp=temp->next;
//     }

//     if(best){
//         cout<<"\n===== BEST =====\n";
//         cout<<"Station: "<<best->name<<"\n";

//         stationQueues[best->id].push(user->id);
//     }
// }

// // ================= BASIC =================
// void addCustomer(){
//     string name,email,pass,car;

//     cout<<"Name: "; cin>>name;
//     cout<<"Email: "; cin>>email;
//     cout<<"Password: "; cin>>pass;
//     cout<<"Car: "; cin>>car;

//     string id="cust"+to_string(++custCount);

//     CustomerNode *n=new CustomerNode(id,name,email,pass,car);

//     if(!customerHead) customerHead=n;
//     else{
//         CustomerNode *t=customerHead;
//         while(t->next) t=t->next;
//         t->next=n;
//     }

//     cout<<"Account Created!\n";
// }

// CustomerNode* loginCustomer(){
//     string email,pass;
//     cout<<"Email: "; cin>>email;
//     cout<<"Password: "; cin>>pass;

//     CustomerNode *t=customerHead;
//     while(t){
//         if(t->email==email && t->password==pass){
//             cout<<"Login Success\n";
//             return t;
//         }
//         t=t->next;
//     }
//     return NULL;
// }

// void addStation(){
//     string name;
//     int cost;

//     cout<<"Station Name: "; cin>>name;
//     cout<<"Cost per %: "; cin>>cost;

//     string id="st"+to_string(++stationCount);

//     StationNode *n=new StationNode(id,name,cost);

//     if(!stationHead) stationHead=n;
//     else{
//         StationNode *t=stationHead;
//         while(t->next) t=t->next;
//         t->next=n;
//     }

//     stationQueues[id]=Queue();

//     cout<<"Station Added!\n";
// }

// // ================= MAIN =================
// int main(){
//     srand(time(0));
//     generateGrid();

//     int choice;

//     while(true){
//         cout<<"\n1.Customer\n2.Vendor\n3.Exit\n";
//         cin>>choice;

//         if(choice==1){
//             int c;
//             cout<<"1.Login\n2.Signup\n";
//             cin>>c;

//             if(c==2) addCustomer();

//             CustomerNode *user = loginCustomer();

//             if(user){
//                 int ch;

//                 while(true){
//                     cout << "\n1.Find Best Station\n2.Show Full Map\n3.Logout\n";
//                     cin >> ch;

//                     if(ch == 1){
//                         findBestStation(user);
//                     }
//                     else if(ch == 2){
//                         pair<int,int> carPos = getRandomRoadLocation();
//                         showFullMap(carPos);
//                     }
//                     else{
//                         break;
//                     }
//                 }
//             }
//         }
//         else if(choice==2){
//             addStation();
//         }
//         else break;
//     }
// }



// #include <iostream>
// #include <algorithm>
// #include <climits>
// #include <cstdlib>
// #include <ctime>
// #include <queue>
// #include <unordered_map>
// #include <vector>
// #include <cstring>
// #include <set>

// using namespace std;

// // ================= GRID =================
// const int N = 100;
// int grid[N][N];
// bool visited[N][N];
// pair<int,int> parent[N][N];

// int dx[4] = {-1,1,0,0};
// int dy[4] = {0,0,-1,1};

// // Generate grid with obstacles + stations
// void generateGrid(){
//     for(int i=0;i<N;i++){
//         for(int j=0;j<N;j++){
//             grid[i][j] = (rand()%4==0)?2:0;
//         }
//     }

//     // place 10 stations randomly
//     for(int i=0;i<10;i++){
//         int x = rand()%N;
//         int y = rand()%N;
//         grid[x][y] = 1;
//     }
// }

// // get random road location
// pair<int,int> getRandomRoadLocation(){
//     while(true){
//         int x = rand()%N;
//         int y = rand()%N;
//         if(grid[x][y] == 0) return {x,y};
//     }
// }

// // ================= BFS =================
// // multi-source BFS to find nearest station
// pair<int,int> nearestStation(pair<int,int> carPos, int &distance){

//     queue<pair<int,int>> q;
//     memset(visited,false,sizeof(visited));

//     // push all stations
//     for(int i=0;i<N;i++){
//         for(int j=0;j<N;j++){
//             if(grid[i][j]==1){
//                 q.push({i,j});
//                 visited[i][j]=true;
//                 parent[i][j]={-1,-1};
//             }
//         }
//     }

//     while(!q.empty()){
//         auto curr = q.front(); q.pop();

//         if(curr == carPos){
//             distance = 0;
//             pair<int,int> p = curr;

//             while(parent[p.first][p.second] != make_pair(-1,-1)){
//                 p = parent[p.first][p.second];
//                 distance++;
//             }
//             return curr;
//         }

//         for(int i=0;i<4;i++){
//             int nx = curr.first + dx[i];
//             int ny = curr.second + dy[i];

//             if(nx>=0 && ny>=0 && nx<N && ny<N &&
//                !visited[nx][ny] && grid[nx][ny]!=2){

//                 visited[nx][ny]=true;
//                 parent[nx][ny]=curr;
//                 q.push({nx,ny});
//             }
//         }
//     }

//     return {-1,-1};
// }

// // ================= PATH =================
// void showPathGrid(pair<int,int> carPos){

//     vector<pair<int,int>> path;

//     pair<int,int> p = carPos;

//     while(p.first != -1){
//         path.push_back(p);
//         p = parent[p.first][p.second];
//     }

//     reverse(path.begin(), path.end());

//     set<pair<int,int>> pathSet(path.begin(), path.end());

//     cout << "\n===== PATH MAP =====\n";

//     for(auto &cell : path){
//         if(cell == carPos) cout << "C ";
//         else cout << "0 ";
//     }
//     cout << "S\n";
// }

// // ================= DATA STRUCTURES =================
// class CustomerNode {
// public:
//     string id, name, email, password, car;
//     CustomerNode *next;

//     CustomerNode(string i,string n,string e,string p,string c){
//         id=i; name=n; email=e; password=p; car=c;
//         next=NULL;
//     }
// };

// CustomerNode *customerHead=NULL;
// int custCount=0;

// // Station with capacity added
// class StationNode {
// public:
//     string id, name;
//     int cost;
//     int capacity; // NEW

//     StationNode *next;

//     StationNode(string i,string n,int c,int cap){
//         id=i; name=n; cost=c; capacity=cap;
//         next=NULL;
//     }
// };

// StationNode *stationHead=NULL;
// int stationCount=0;

// // Queue
// class QueueNode{
// public:
//     string customerID;
//     QueueNode *next;

//     QueueNode(string id){
//         customerID=id;
//         next=NULL;
//     }
// };

// class Queue{
// public:
//     QueueNode *front,*rear;

//     Queue(){ front=rear=NULL; }

//     bool empty(){ return front==NULL; }

//     void push(string id){
//         QueueNode *n=new QueueNode(id);
//         if(empty()) front=rear=n;
//         else{
//             rear->next=n;
//             rear=n;
//         }
//     }

//     int size(){
//         int count=0;
//         QueueNode *t=front;
//         while(t){ count++; t=t->next; }
//         return count;
//     }
// };

// unordered_map<string,Queue> stationQueues;
// unordered_map<string,int> batteryNeed;

// // ================= WAIT =================
// // capacity aware waiting time
// int getWaitTime(string id,int need, int capacity){
//     Queue &q=stationQueues[id];

//     int people = q.size();

//     // if ports free → no wait
//     if(people < capacity) return need*30;

//     int total = 0;
//     QueueNode *t=q.front;

//     while(t){
//         total += batteryNeed[t->customerID]*30;
//         t=t->next;
//     }

//     total += need*30;
//     return total;
// }

// int getBill(int need,int cost){
//     return need*cost;
// }

// // ================= FIND BEST =================
// void findBestStation(CustomerNode *user){

//     int curr,req;
//     cout<<"Enter Current Battery %: "; cin>>curr;
//     cout<<"Enter Required Battery %: "; cin>>req;

//     int need = max(0,req-curr);
//     batteryNeed[user->id]=need;

//     pair<int,int> carPos = getRandomRoadLocation();

//     int dist;
//     nearestStation(carPos,dist);

//     cout<<"\nCar Location: ("<<carPos.first<<","<<carPos.second<<")\n";
//     cout<<"Distance Needed: "<<dist<<"%\n";

//     // 🔋 LOW BATTERY CASE
//     if(dist > curr){
//         cout<<"\nLOW BATTERY!\n";
//         cout<<"Nearest Station Distance: "<<dist<<"\n";
//         cout<<"Go directly to nearest station!\n";
//         return;
//     }

//     StationNode *temp=stationHead;
//     StationNode *best=NULL;
//     int bestScore=INT_MAX;

//     StationNode *minWaitStation=NULL;
//     int minWait=INT_MAX;

//     bool allFull=true;

//     while(temp){
//         int wait = getWaitTime(temp->id,need,temp->capacity);
//         int bill = getBill(need,temp->cost);

//         cout<<"\nStation: "<<temp->name;
//         cout<<"\nCapacity: "<<temp->capacity;
//         cout<<"\nQueue Size: "<<stationQueues[temp->id].size();
//         cout<<"\nWait: "<<wait/60<<" mins";
//         cout<<"\nCost: "<<bill<<"\n";

//         // check if station has free slot
//         if(stationQueues[temp->id].size() < temp->capacity){
//             allFull=false;
//         }

//         // best score
//         int score = dist + (wait/60) + bill/10;

//         if(score < bestScore){
//             bestScore=score;
//             best=temp;
//         }

//         // minimum wait tracking
//         if(wait < minWait){
//             minWait = wait;
//             minWaitStation = temp;
//         }

//         temp=temp->next;
//     }

//     // 🚨 ALL FULL CASE
//     if(allFull && minWaitStation){
//         cout<<"\nALL STATIONS FULL!\n";
//         cout<<"Best based on minimum wait: "<<minWaitStation->name<<"\n";
//         stationQueues[minWaitStation->id].push(user->id);
//         return;
//     }

//     if(best){
//         cout<<"\n===== BEST =====\n";
//         cout<<"Station: "<<best->name<<"\n";
//         stationQueues[best->id].push(user->id);
//     }
// }

// // ================= BASIC =================
// void addCustomer(){
//     string name,email,pass,car;

//     cout<<"Name: "; cin>>name;
//     cout<<"Email: "; cin>>email;
//     cout<<"Password: "; cin>>pass;
//     cout<<"Car: "; cin>>car;

//     string id="cust"+to_string(++custCount);

//     CustomerNode *n=new CustomerNode(id,name,email,pass,car);

//     if(!customerHead) customerHead=n;
//     else{
//         CustomerNode *t=customerHead;
//         while(t->next) t=t->next;
//         t->next=n;
//     }

//     cout<<"Account Created!\n";
// }

// CustomerNode* loginCustomer(){
//     string email,pass;
//     cout<<"Email: "; cin>>email;
//     cout<<"Password: "; cin>>pass;

//     CustomerNode *t=customerHead;
//     while(t){
//         if(t->email==email && t->password==pass){
//             cout<<"Login Success\n";
//             return t;
//         }
//         t=t->next;
//     }
//     return NULL;
// }

// // add station with RANDOM capacity (1–7)
// void addStation(){
//     string name;
//     int cost;

//     cout<<"Station Name: "; cin>>name;
//     cout<<"Cost per %: "; cin>>cost;

//     int cap = rand()%7 + 1;

//     string id="st"+to_string(++stationCount);

//     StationNode *n=new StationNode(id,name,cost,cap);

//     if(!stationHead) stationHead=n;
//     else{
//         StationNode *t=stationHead;
//         while(t->next) t=t->next;
//         t->next=n;
//     }

//     stationQueues[id]=Queue();

//     cout<<"Station Added with Capacity: "<<cap<<"\n";
// }

// // ================= MAIN =================
// int main(){
//     srand(time(0));
//     generateGrid();

//     int choice;

//     while(true){
//         cout<<"\n1.Customer\n2.Vendor\n3.Exit\n";
//         cin>>choice;

//         if(choice==1){
//             int c;
//             cout<<"1.Login\n2.Signup\n";
//             cin>>c;

//             if(c==2) addCustomer();

//             CustomerNode *user = loginCustomer();

//             if(user){
//                 findBestStation(user);
//             }
//         }
//         else if(choice==2){
//             addStation();
//         }
//         else break;
//     }
// }




#include <iostream>
#include <algorithm>
#include <climits>
#include <cstdlib>
#include <ctime>
#include <queue>
#include <unordered_map>
#include <vector>
#include <cstring>
#include <set>
#include <map>

using namespace std;

// GRID 
const int N = 100;
int grid[N][N];
bool visited[N][N];
pair<int,int> parent[N][N];

// movement directions
int dx[4] = {-1,1,0,0};
int dy[4] = {0,0,-1,1};

// station names
vector<string> stationNames = {
    "FastCharge", "EcoCharge", "PowerHub", "VoltPoint",
    "ChargeZone", "ElectroBay", "SparkStation",
    "GreenPlug", "ZapCharge", "UltraVolt"
};

// map grid → station name
map<pair<int,int>, string> stationGridMap;

// GRID GENERATION 
void generateGrid(){
    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++){
            grid[i][j] = (rand()%4==0)?2:0; // obstacle or road
        }
    }

    // place stations
    for(int i=0;i<10;i++){
        int x = rand()%N;
        int y = rand()%N;

        grid[x][y] = 1;
        stationGridMap[{x,y}] = stationNames[i];
    }
}

// random road location
pair<int,int> getRandomRoadLocation(){
    while(true){
        int x = rand()%N;
        int y = rand()%N;
        if(grid[x][y] == 0) return {x,y};
    }
}

// BFS 
string nearestStationName;

pair<int,int> nearestStation(pair<int,int> carPos, int &distance){

    queue<pair<int,int>> q;
    memset(visited,false,sizeof(visited));

    // multi-source BFS
    for(auto &entry : stationGridMap){
        q.push(entry.first);
        visited[entry.first.first][entry.first.second] = true;
        parent[entry.first.first][entry.first.second] = {-1,-1};
    }

    while(!q.empty()){
        auto curr = q.front(); q.pop();

        if(curr == carPos){
            distance = 0;
            pair<int,int> p = curr;

            while(parent[p.first][p.second] != make_pair(-1,-1)){
                p = parent[p.first][p.second];
                distance++;
            }

            nearestStationName = stationGridMap[p];
            return curr;
        }

        for(int i=0;i<4;i++){
            int nx = curr.first + dx[i];
            int ny = curr.second + dy[i];

            if(nx>=0 && ny>=0 && nx<N && ny<N &&
               !visited[nx][ny] && grid[nx][ny]!=2){

                visited[nx][ny]=true;
                parent[nx][ny]=curr;
                q.push({nx,ny});
            }
        }
    }

    return {-1,-1};
}

// PATH 
void showPathGrid(pair<int,int> carPos){

    vector<pair<int,int>> path;
    pair<int,int> p = carPos;

    // build path
    while(p.first != -1){
        path.push_back(p);
        p = parent[p.first][p.second];
    }

    reverse(path.begin(), path.end());

    // find boundaries of sub-grid
    int minX=N, minY=N, maxX=0, maxY=0;

    for(auto &c : path){
        minX = min(minX, c.first);
        minY = min(minY, c.second);
        maxX = max(maxX, c.first);
        maxY = max(maxY, c.second);
    }

    // add padding
    minX = max(0, minX-2);
    minY = max(0, minY-2);
    maxX = min(N-1, maxX+2);
    maxY = min(N-1, maxY+2);

    set<pair<int,int>> pathSet(path.begin(), path.end());

    cout << "\n===== PATH MAP =====\n";

    for(int i=minX;i<=maxX;i++){
        for(int j=minY;j<=maxY;j++){

            if(i==carPos.first && j==carPos.second){
                cout << "C ";
            }
            else if(grid[i][j]==1){
                cout << "S ";
            }
            else if(grid[i][j] == 2){
                cout<< "^ ";
            }
            else if(pathSet.count({i,j})){
                cout << "0 ";   // path
            }
            else{
                cout << ". ";   // rest
            }
        }
        cout << "\n";
    }
}

// FULL MAP 
void showFullMap(pair<int,int> carPos){

    cout << "\n===== FULL MAP =====\n";

    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++){

            if(i==carPos.first && j==carPos.second){
                cout << "C ";
            }
            else if(grid[i][j]==1){
                cout << "S ";
            }
            else if(grid[i][j]==2){
                cout << "# ";
            }
            else{
                cout << ". ";
            }
        }
        cout << "\n";
    }

    cout << "\nStation List:\n";
    for(auto &it : stationGridMap){
        cout << it.second << " at (" 
             << it.first.first << "," 
             << it.first.second << ")\n";
    }
}

// BILL 
void generateBill(string stationName, int dist, int remaining, int need, int cost, int wait){

    cout << "\n===== BILL =====\n";

    cout << "Station: " << stationName << endl;
    cout << "Travel Used: " << dist << "%\n";
    cout << "Battery After Travel: " << remaining << "%\n";
    cout << "Charge Added: " << need << "%\n";
    cout << "Cost per %: " << cost << endl;

    int totalCost = need * cost;

    cout << "Total Cost: " << totalCost << endl;
    cout << "Total Time: " << (wait/60) << " mins\n";
}

// DATA STRUCTURES 
class CustomerNode {
public:
    string id, name, email, password, car;
    CustomerNode *next;

    CustomerNode(string i,string n,string e,string p,string c){
        id=i; name=n; email=e; password=p; car=c;
        next=NULL;
    }
};

CustomerNode *customerHead=NULL;
int custCount=0;

class StationNode {
public:
    string id, name;
    int cost;
    int capacity;
    StationNode *next;

    StationNode(string i,string n,int c,int cap){
        id=i; name=n; cost=c; capacity=cap;
        next=NULL;
    }
};

StationNode *stationHead=NULL;
int stationCount=0;

// QUEUE 
class QueueNode{
public:
    string customerID;
    QueueNode *next;

    QueueNode(string id){
        customerID=id;
        next=NULL;
    }
};

class Queue{
public:
    QueueNode *front,*rear;

    Queue(){ front=rear=NULL; }

    bool empty(){ return front==NULL; }

    void push(string id){
        QueueNode *n=new QueueNode(id);
        if(empty()) front=rear=n;
        else{
            rear->next=n;
            rear=n;
        }
    }

    int size(){
        int count=0;
        QueueNode *t=front;
        while(t){ count++; t=t->next; }
        return count;
    }
};

unordered_map<string,Queue> stationQueues;
unordered_map<string,int> batteryNeed;

// WAIT 
int getWaitTime(string id,int need,int capacity){

    Queue &q=stationQueues[id];

    if(q.size() < capacity) return need*30;

    int total=0;
    QueueNode *t=q.front;

    while(t){
        total += batteryNeed[t->customerID]*30;
        t=t->next;
    }

    total += need*30;
    return total;
}

// FIND BEST 
void findBestStation(CustomerNode *user){

    int curr,req;
    cout<<"Enter Current Battery %: "; cin>>curr;
    cout<<"Enter Required Battery %: "; cin>>req;

    pair<int,int> carPos = getRandomRoadLocation();

    int dist;
    nearestStation(carPos,dist);

    cout<<"\nCar Location: ("<<carPos.first<<","<<carPos.second<<")\n";
    cout<<"Distance Needed: "<<dist<<"%\n";
    cout<<"Nearest Station: "<<nearestStationName<<"\n";

    // battery after travel
    int remaining = curr - dist;

    if(remaining < 0){
        cout<<"\nLOW BATTERY!\n";
        cout<<"Cannot reach station safely!\n";
        return;
    }

    // updated need formula
    int need = max(0, req - remaining);

    cout<<"Battery after reaching station: "<<remaining<<"%\n";
    cout<<"Charging needed: "<<need<<"%\n";

    batteryNeed[user->id]=need;

    showPathGrid(carPos);

    StationNode *temp=stationHead;
    StationNode *best=NULL;
    int bestScore=INT_MAX;

    while(temp){
        int wait = getWaitTime(temp->id,need,temp->capacity);
        int bill = need * temp->cost;

        cout<<"\nStation: "<<temp->name;
        cout<<"\nCapacity: "<<temp->capacity;
        cout<<"\nQueue Size: "<<stationQueues[temp->id].size();
        cout<<"\nWait: "<<wait/60<<" mins";
        cout<<"\nCost: "<<bill<<"\n";

        int score = dist + (wait/60) + bill/10;

        if(score < bestScore){
            bestScore=score;
            best=temp;
        }

        temp=temp->next;
    }

    if(best){
        cout<<"\n===== BEST =====\n";
        cout<<"Station: "<<best->name<<"\n";

        stationQueues[best->id].push(user->id);

        int wait = getWaitTime(best->id, need, best->capacity);

        generateBill(best->name, dist, remaining, need, best->cost, wait);
    }
}

// BASIC 
void addCustomer(){
    string name,email,pass,car;

    cout<<"Name: "; cin>>name;
    cout<<"Email: "; cin>>email;
    cout<<"Password: "; cin>>pass;
    cout<<"Car: "; cin>>car;

    string id="cust"+to_string(++custCount);

    CustomerNode *n=new CustomerNode(id,name,email,pass,car);

    if(!customerHead) customerHead=n;
    else{
        CustomerNode *t=customerHead;
        while(t->next) t=t->next;
        t->next=n;
    }

    cout<<"Account Created!\n";
}

CustomerNode* loginCustomer(){
    string email,pass;
    cout<<"Email: "; cin>>email;
    cout<<"Password: "; cin>>pass;

    CustomerNode *t=customerHead;
    while(t){
        if(t->email==email && t->password==pass){
            cout<<"Login Success\n";
            return t;
        }
        t=t->next;
    }
    return NULL;
}

// add station
void addStation(){
    string name;
    int cost;

    cout<<"Station Name: "; cin>>name;
    cout<<"Cost per %: "; cin>>cost;

    int cap = rand()%7 + 1;

    string id=name;

    StationNode *n=new StationNode(id,name,cost,cap);

    if(!stationHead) stationHead=n;
    else{
        StationNode *t=stationHead;
        while(t->next) t=t->next;
        t->next=n;
    }

    stationQueues[id]=Queue();

    cout<<"Station Added with Capacity: "<<cap<<"\n";
}

// MAIN 
int main(){
    srand(time(0));
    generateGrid();

    int choice;

    while(true){
        cout<<"\n1.Customer\n2.Vendor\n3.Exit\n";
        cin>>choice;

        if(choice==1){
            int c;
            cout<<"1.Login\n2.Signup\n";
            cin>>c;

            if(c==2) addCustomer();

            CustomerNode *user = loginCustomer();

            if(user){

                int ch;

                while(true){
                    cout << "\n1.Find Best Station\n2.Show Full Map\n3.Logout\n";
                    cin >> ch;

                    if(ch == 1){
                        findBestStation(user);
                    }
                    else if(ch == 2){
                        pair<int,int> carPos = getRandomRoadLocation();
                        showFullMap(carPos);
                    }
                    else{
                        break;
                    }
                }

                
            }
        }
        else if(choice==2){
            addStation();
        }
        else break;
    }
}