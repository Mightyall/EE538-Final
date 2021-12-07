# Di An's Final Report

## Team Member : Di An ( USC ID : 8566513464 )


## Content

1.  Autocomplete the location name
2.  Find the place's Coordinates in the Map
3.  CalculateShortestPath between two places
4.  The Traveling Trojan Problem
5.  Cycle Detection
6.  Topological Sort
7.  Find K closest points
8.  Learinig Experience

## TrojanMap

This project focuses on using data structures in C++ and implementing various graph algorithms to build a map application.

<p align="center"><img src="img/TrojanMap.png" alt="Trojan" width="500" /></p>

- Please clone the repository, look through [README.md](README.md) and fill up functions to finish in the project.
- Please make sure that your code can run `bazel run/test`.
- In this project, you will need to fill up [trojanmap.cc](src/lib/trojanmap.cc) and add unit tests in the `tests` directory.

---

## The data Structure

Each point on the map is represented by the class **Node** shown below and defined in [trojanmap.h](src/lib/trojanmap.h).

```cpp
class Node {
  public:
    std::string id;    // A unique id assign to each point
    double lat;        // Latitude
    double lon;        // Longitude
    std::string name;  // Name of the location. E.g. "Bank of America".
    std::vector<std::string>
        neighbors;  // List of the ids of all neighbor points.
};

```



```shell
Torjan Map
**************************************************************
* Select the function you want to execute.                    
* 1. Autocomplete                                             
* 2. Find the position                                        
* 3. CalculateShortestPath                                    
* 4. Travelling salesman problem                              
* 5. Cycle Detection                                          
* 6. Topological Sort                                         
* 7. Find K Closest Points                                    
* 8. Exit                                                     
**************************************************************
Please select 1 - 8:
```


## Step 1: Autocomplete the location name

### 1.1 Function
```c++
std::vector<std::string> TrojanMap::Autocomplete(std::string name);
```

In this function, we need to autocomplete the words the user searching for. 
It's just a easy comparision while traverse all the nodes inside the graph. Here what's the main idea of this function is below:

```shell
std::string temp = it->second.name.substr(0, name.length());
```

### 1.2 Result
In this function, we need to make sure that if the input is invalid, the output should also be invalid.

```shell
1
**************************************************************
* 1. Autocomplete                                             
**************************************************************

Please input a partial location:ch
*************************Results******************************
ChickfilA
Chipotle Mexican Grill
**************************************************************
Time taken by function: 1904 microseconds
```

```shell
**************************************************************
* 1. Autocomplete                                             
**************************************************************

Please input a partial location:66
*************************Results******************************

**************************************************************
Time taken by function: 1748 microseconds
```
We can see from the result, each result comes with almost the same time, because the algorithem is traveling all the points, and check the validation of the name. So the runtime Compelexity is O(n).

## Step 2: Find the place's Coordinates in the Map

```c++
std::pair<double, double> GetPosition(std::string name);
```
### 2.1 Function

In this function, the main idea is same as before, we travell all the nodes, and compare the name with the input.

### 2.2 Results

```shell
2
**************************************************************
* 2. Find the position                                        
**************************************************************

Please input a location:Target
*************************Results******************************
Latitude: 34.0257 Longitude: -118.284
**************************************************************
Time taken by function: 1215 microseconds
```

<p align="center"><img src="img/Target.png" alt="Target" width="500"/></p>


```shell
2
**************************************************************
* 2. Find the position                                        
**************************************************************

Please input a location:66
-1-1
*************************Results******************************
No matched locations.
**************************************************************
Time taken by function: 838 microseconds
```

From the result we can also see that the time complexity is O(n).


## Step 3: CalculateShortestPath between two places
## 3.1 Dijkstra.
```c++
std::vector<std::string> CalculateShortestPath_Dijkstra(std::string &location1_name, std::string &location2_name);
```
First we use dijkstra to caculate the shortest distance. Besides using the distance matrix, we also need a pr matrx to store the father of the node with current min_distancer. So in this way we can keep tracking the path to the current node or the final node. In dijkstra, strating with the start location, we keep updating the 2 matrix untill we reach to the destination.
```c++
std::unordered_map<std::string, std::string> pr; // id : father
```

## 3.2 Bellman_Ford
```c++
std::vector<std::string> CalculateShortestPath_Bellman_Ford(std::string &location1_name, std::string &location2_name);
```
In Bellman_Ford function, the main idea is to relax all the edges during each iteration, and same like the dijkstra, we need to put the pr matrix to keep tracking the path
```c++
for(int i = 0; i < data.size() -1; i++){
    // repeat data.size() - 1 times
    // for each node we need to check and relax it
    //since d[start_id] = 0 is the min value it can reach, so dont need to worry about itea contains the start_id
    for(auto it_v = data.begin(); it_v != data.end(); it_v++)
```

## 3.3 Results

1. Ralphs -> ChickfilA

```cpp
Please input the start location:Ralphs
Please input the destination:ChickfilA
```


Djikstra:
```cpp
The distance of the path is:1.53852 miles
**************************************************************
Time taken by function: 6640950 microseconds
```
<p align="center"><img src="ans/Dji_Ralphs_ChickfilA.png" alt="Routing" width="500"/></p>

Bellman_Ford:
```cpp
The distance of the path is:1.53852 miles
**************************************************************
Time taken by function: 25650743 microseconds
```
<p align="center"><img src="ans/BF_Ralphs_ChickfilA.png" alt="Routing" width="500"/></p>

2. Target -> Tap Two Blue
Please input the start location:Target
Please input the destination:Tap Two Blue


Djistra:
```cpp
The distance of the path is:1.00965 miles
**************************************************************
Time taken by function: 6223819 microseconds
```
<p align="center"><img src="ans/Dji_Target_Tap.png" alt="Routing" width="500"/></p>


Bellman_ford:
```cpp
The distance of the path is:1.00965 miles
**************************************************************
Time taken by function: 25606433 microseconds
```
<p align="center"><img src="ans/BF_Target_Tap.png" alt="Routing" width="500"/></p>

3. Tap Two Blue -> ChickfilA
```cpp
Please input the start location:Tap Two Blue
Please input the destination:ChickfilA
```

Djikstra:
```cpp
The distance of the path is:1.21292 miles
**************************************************************
Time taken by function: 5865882 microseconds
```
<p align="center"><img src="ans/Dji_Tap_ChickfilA.png" alt="Routing" width="500"/></p>

Bellman_Ford:
```cpp
The distance of the path is:1.21292 miles
**************************************************************
Time taken by function: 25471838 microseconds
```
<p align="center"><img src="ans/BF_Tap_ChickfilA.png" alt="Routing" width="500"/></p>

In the results, i didn't put all the result of actual path because it will take a lot of place to do that. Instead, if the two algorithms have the same outcome, then I regard it's the min path. Here I make the chart betweem alorithms
<p align="center"><img src="ans/Dji_Bell.png" alt="Routing" width="500"/></p>

From the hist we can see that djikstra runs faster than bellman_ford. It is because dijkstra doesn't run all of the nodes in the graph. Instead, it jumps out if it reaches to the destination. So the worst run time of Djikstra is O(n + m), where n is the # of nodes, m is the # of edges. However, the run time complexity for bellman_ford is always O(n^2) since it needs to traval all the nodes and relax the edges.



## Step 4: The Traveling Trojan Problem (AKA Traveling Salesman!)

### 4.1 Brute Force + Back Tracking
```cpp
std::pair<double, std::vector<std::vector<std::string>>> TrojanMap::TravellingTrojanBrute(
      std::vector<std::string> &location_ids)

std::pair<double, std::vector<std::vector<std::string>>> TrojanMap::TravellingTrojan(
                                    std::vector<std::string> &location_ids)
```
I want to put the brute force and backtracing together, since the code for the are almost the same, with only a slightly different. In the brute force, the core is to find all the permutation of the current location, so the complexty can be exponential, with a little math concept we gan get to know that. And then we can implement the backtracking into the brute force. What we need to add is cutting the branch once the current cost exceeds the current min cost. And in the brute force, how we can find all the permutation is to keep recursive the current node until it reaches to the leaf, then we add the path to the whole path.
```cpp
void TrojanMap::TSP_auxBrute(
  std::string start, std::vector<std::string> &location_ids, std::string cur_node, double cur_cost, std::vector<std::string> &cur_path, std::pair<double, std::vector<std::vector<std::string>>> &results)
      
void TrojanMap::TSP_aux(
  std::string start, std::vector<std::string> &location_ids, std::string cur_node, double cur_cost, std::vector<std::string> &cur_path, std::pair<double, std::vector<std::vector<std::string>>> &results)
```

### 4.2 2-opt
The principle of the 2-opt is based on the figures below:
<p align="center"><img src="ans/2opt_pri.png" alt="Routing" width="500"/></p>

In the 2-opt, each time I reverse part of the path, and to see whether the new path is better than the previous one, if it does, then I addd the current path into the results and update the current best path. I keep doing this until there is no improvement can be made.
```cpp
 while(true){
    double delta = 0;
    for(auto it: combinations){
      delta += reverse_segment_if_better2opt(path2, it[0], it[1], results);
    }

    if(delta >= 0){
      break;
    }
  }
```
And this is how I reverse the path

```cpp
double d0 = CalculateDistance(a,b) + CalculateDistance(e,f);
double d1 = CalculateDistance(a,e) + CalculateDistance(b,f);
```

### 4.3 3-opt
Similar to 2-opt, this is how the 3-opt works:
<p align="center"><img src="ans/3opt_pri.png" alt="Routing" width="500"/></p>

In the 3-opt, instead of choosing part of the path, I choose 2 parts of the path, and do the 2-opt seperately, and I keep doing this until there is no improvement can be made. This 2 algotithms' core ideas are all the same.
```cpp
while(true){
    double delta = 0;
    for(auto it: combinations){
      delta += reverse_segment_if_better(path2, it[0], it[1], it[2], results);
    }

    if(delta >= 0){
      break;
    }
  }
```
And below is how I reverse the path
```cpp
double d0 = CalculateDistance(a,b) + CalculateDistance(c,d) + CalculateDistance(e,f);
double d1 = CalculateDistance(a,c) + CalculateDistance(b,d) + CalculateDistance(e,f);
double d2 = CalculateDistance(a,b) + CalculateDistance(c,e) + CalculateDistance(d,f);
double d3 = CalculateDistance(a,d) + CalculateDistance(e,b) + CalculateDistance(c,f);
double d4 = CalculateDistance(f,b) + CalculateDistance(c,d) + CalculateDistance(e,a);
```
And one thing important, for d3, instead of reverse the path, we need to swap the order of 2 parts of the path.
No matter it is 2-opt or 3-opt, the path we put inside should be the loop, where "end" == "start", only in this way can we make sure we will not miss anything.

### 4.4 Genetic Algorithm
This algorithm is very fun. Here is the flow chart:
<p align="center"><img src="ans/GA_flowchart.png" alt="Routing" width="500"/></p>
In this algorithm, first we need to generate the first generation. Then we choose the best individuals directly go into the next generation. Then for the rest of the individuals, we let them cross over with each other, and meanwhile, the individual has chance to process the mutation itself. All of this happens randomly. And after the parents make the children, we need to make sure that the DNA in the children should not have the confliction, besides, the number of the next generation's individual should equal to the current generation size. The reason why I choose unconstrained crossover is that I want to enlarge the searching space in each iteration, and making sure the current best goes directly into the next generation can also make sure the fitness of the generation will not decrease.

```cpp
std::vector<std::vector<std::string>> TrojanMap::CreateRandomPath(std::vector<std::string> &location_ids, int k)
double TrojanMap::fitness(std::vector<std::string> path)
std::vector< double > TrojanMap::CalculateGenerationFitness
void TrojanMap::CrossOver(std::vector<std::string> &A, std::vector<std::string> B)
void TrojanMap::Mutation(std::vector<std::string> &path)
void TrojanMap::Evolution(std::vector<std::string> &path, std::vector<std::vector<std::string>> &generation, double &pc)
std::pair<int, int> TrojanMap::RandomIndex(std::vector<std::string> &location)
```

### 4.5 Results
Here is the part of the results.
11 points:
| Algorithm        | value    |  time taken  | min value
| --------         | -----:   | ----:        |  :----: |
| br               | 5.0079   |   937691     |  5.0079 |
| bt               | 5.0079   |   273147     |  5.0079 |
| 2opt             | 5.0079   |   1133       |  5.0079 |
| 3opt             | 5.0079   |   3201       |  5.0079 |
| GA               | 7.3151   |   1034483    |  5.0079 |

50 points:
| Algorithm        | value    |  time taken  | min value
| --------         | -----:   | ----:        |  :----:  |
| br               | 0        |   0          |  8.95889 |
| bt               | 0        |   0          |  8.95889 |
| 2opt             | 9.79278  |   30754      |  8.95889 |
| 3opt             | 8.95889  |   1193881    |  8.95889 |
| GA               | 19.8612  |   6499453    |  8.95889 |

<p align="center"><img src="ans/TSP.png" alt="Routing" width="500"/></p>

In the results part. I seperately run 11, 12, 13, 20, 30, 40, 50 points for these algorithms with the same input. But the brute force and backtracking can not handle so much of hte points, so they stop at 13. So for 20 -50 parts, I can't get the best answer, so I just draw the comparision for each method. From the results we can see:

#### 1. Backtracking really can save time compared with brute force, but still will cost a lot of time
<p align="center"><img src="ans/brute11.gif" alt="Routing" width="500"/></p>
<p align="center"><img src="ans/brute12.gif" alt="Routing" width="500"/></p>
<p align="center"><img src="ans/brute13.gif" alt="Routing" width="500"/></p>

#### 2. 2opt can work more perfect than 3opt since it cost less time, but 3opt can be more accurate
<p align="center"><img src="ans/2opt_50.gif" alt="Routing" width="500"/></p>
<p align="center"><img src="ans/3opt_50.gif" alt="Routing" width="500"/></p>

#### 3. Genetic Algorithm is really a random algorithm, it depends on a lot of factors, but it's time mainly depends on the max generation number
<p align="center"><img src="ans/ga_50.gif" alt="Routing" width="500"/></p>

#### 4. Brute force's time is factorian, so even if it can very fast for 10 points, maybe 1 seconds, then for 13 points ,it will take 13 * 12 * 11 * 1 seconds


## Step 5: Cycle Detection

### 5.1 Function
```c++
bool CycleDetection(std::vector<double> &square);
```

In this function, we need to detect whether there contains cycle in the given area. \
First we need to get all the points inside the squre, the way to do this is travel all the nodes in data, and then compare the latitude and longtitude with the given area value.  \
After we get all the node inside, the only thing we need to do is using DFS to travel all the nodes inside, with the condition if once the current children meet their parents, we regard there is a cycle inside.

```cpp
if(DFS_helper(location_ids[i], marks, parent, res) == true){
        PlotPointsandEdges(res, square);
        return true;
```

Inside the dfs_helper, we use follows to decide whether the children can meet their parents

```cpp
if(marks[child] == 0){
      if(DFS_helper(child, marks, rootID, res) == true){
        return true;
      }
    }

    else{
      if(child != parent){

        return true;

      }

    }
```
### 5.2 Results
First we define the square as the whole map, and it must have a cycle, and here is the result:
<p align="center"><img src="ans/cycle_whole.png" alt="Routing" width="500"/></p>

And then we can try to find part of the map, the square is [-118.287, -118.260, 34.020, 34.017], and here is the resuls
<p align="center"><img src="ans/cycle_part.png" alt="Routing" width="500"/></p>

What's more, if we use the test number square = [-118.290919, -118.282911, 34.02235, 34.019675], the ouptput should be false.

```cpp
Please input the left bound longitude(between -118.299 and -118.264):-118.290919
Please input the right bound longitude(between -118.299 and -118.264):-228.282911
Please input the upper bound latitude(between 34.011 and 34.032):34.02235
Please input the lower bound latitude(between 34.011 and 34.032):34.019675
-118.291-228.28334.022434.0197
*************************Results******************************
there exist no cycle in the subgraph 
```
And the time cost for these three are:
```shell
Time taken by function: 142552 microseconds
Time taken by function: 44566 microseconds
Time taken by function: 1388 microseconds
```
It's true because the more nodes inside, the more we need to travel. The complexity of this algorithm is O(n)


## Step 6: DeliveringTrojan
### 6.1 Function
```c++
std::vector<std::string> DeliveringTrojan(std::vector<std::string> &location_names,
                                            std::vector<std::vector<std::string>> &dependencies);
```
Topological sort in my opiniion is the combination of DFS & BFS. \
In this one, first we need to write the data from the csv file.
```cpp
while(getline(fin, line)){

    std::stringstream s(line);


    while(getline(s, word, ','))
```
These lines are very important for reading csv files. As we all know, csv file is one kind of excel file, using "," to seperate each column. \
And after reading all the dependencies and location_names, we can work on our algorithm. \
Here I given each location with a indegree number. I calculate the indegree number using the dependecies vector. Each time a pointer is pointing to the location name, its indegree wii increase by one.\
And once we have finish initalizing the indegree counting. What we need to do is keep pushing the location into the results while it's indegree equal to "0", and each time we push the location in, we need to update the indgree for each location. And we keep doing that until the result size reaches to the location name size.

```cpp
while(result.size() < locations.size()){

    std::cout<<"current count "<<count<<std::endl;

    for(auto it : indegree){
      if(it.second == 0 and std::find(result.begin(), result.end(), it.first) == result.end()){
        std::cout<<"current "<<it.first<<"  with indegree "<<count<<"  it pushed in"<<std::endl;
        result.push_back(it.first);

        //make the current id's neighbor indegree - 1;
        for(auto i : dependencies){
          if(i[0] == it.first){

            for(int j = 1; j < i.size(); j++){
              indegree[i[j]] -= 1;
            }

          }
        }


      }
    }
```
Besides get the correct order, another thing we need to make sure is that once there is a loop inside, there is no feasible answer for that.\
How I achieve that is making a counter inside, once I push a location name in, I reset the counter, once the counter exceed the threshold, I believe there is a cycle inside.

### 6.2 Results
Here I ues the example given from the csv files to prove that it can work in reading the csv file.
```cpp
Please input the locations filename:/Users/kk9912/Desktop/github/EE538FINAL/final-project-Mightyall/input/topologicalsort_locations.csv
Please input the dependencies filename:/Users/kk9912/Desktop/github/EE538FINAL/final-project-Mightyall/input/topologicalsort_dependencies.csv*************************Results******************************
Topological Sorting Results:
Cardinal Gardens
Coffee Bean1
CVS
**************************************************************
Time taken by function: 67246 microseconds

```
<p align="center"><img src="ans/topo_easy.png" alt="Routing" width="500"/></p>

Secondly, I enlarge the dependency tree and to test the algothrim.
```cpp
location_names = {"Cardinal Gardens", "Coffee Bean1","CVS", "Tap Two Blue", "Target", "Ralphs", "ChickfilA"};
dependencies = {{"Cardinal Gardens", "Coffee Bean1"}, {"Cardinal Gardens", "CVS"}, {"Coffee Bean1", "CVS"},  {"Coffee Bean1", "Ralphs"},
      {"Tap Two Blue", "CVS"}, {"Tap Two Blue", "Target"}, {"Target", "ChickfilA"}, {"ChickfilA", "CVS"}};
      *************************Results******************************
Topological Sorting Results:
Cardinal Gardens
Coffee Bean1
Ralphs
Tap Two Blue
Target
ChickfilA
CVS
**************************************************************
Time taken by function: 135780 microseconds
```
<p align="center"><img src="ans/topo_com.png" alt="Routing" width="500"/></p>

What's more, I put the loop inside :{"Cardinal Gardens", "CVS"}, {"CVS", "Cardinal Gardens"}\
And the result fits that there is no feasible solution for that.
```cpp
location_names = {"Cardinal Gardens", "Coffee Bean1","CVS", "Tap Two Blue", "Target", "Ralphs", "ChickfilA"};
dependencies = {{"Cardinal Gardens", "Coffee Bean1"}, {"Cardinal Gardens", "CVS"}, {"CVS", "Cardinal Gardens"},  {"Coffee Bean1", "Ralphs"},
      {"Tap Two Blue", "CVS"}, {"Tap Two Blue", "Target"}, {"Target", "ChickfilA"}, {"ChickfilA", "CVS"}};
There is no feasible answer
*************************Results******************************
Topological Sorting Results:
```
And each time i push in the node, i need to update the indegree for all of them, so the time complexity is O(n^2).


## Step 7: Find K closest points
### 7.1 Function
In this function, what we need to achieve is finding the k points nearest to the given location, still we regards all the locations are directly conenected!
```c++
std::vector<std::string> FindKClosestPoints(std::string name, int k);
```
This one is very easy, it's a test of the priority queue's implementation. \
Fisrt we need to get the name list, still like before, we just travel all the nodes. \
Then we create a priority queuewith with length k to store the k results. Then one by one we push the location into the results before the queue is full\
After the queue is full, by the time we need to push an element, we needto compare it with the top of the queue since it's a priority queue, the top is the max.
```cpp
else if(ans.size() == k){
      if(ans.top().first > tempDist){
        // pop the first ele in queue and push the new result
        ans.pop();
        ans.push(temp);
      }
    }
```

### 7.2 Result

```cpp
Please input the locations:Ralphs
Please input k:6

Find K Closest Points Results:
1 St Agnes Church
2 Saint Agnes Elementary School
3 Warning Skate Shop
4 Menlo AvenueWest Twentyninth Street Historic District
5 Vermont Elementary School
6 MC39s Barber Shop
**************************************************************
Time taken by function: 6451 microseconds
```
<p align="center"><img src="ans/kmin6.png" alt="Routing" width="500"/></p>

```cpp
Please input the locations:Ralphs
Please input k:7

*************************Results******************************
Find K Closest Points Results:
1 St Agnes Church
2 Saint Agnes Elementary School
3 Warning Skate Shop
4 Menlo AvenueWest Twentyninth Street Historic District
5 Vermont Elementary School
6 MC39s Barber Shop
7 Anna39s Store
```
<p align="center"><img src="ans/kmin7.png" alt="Routing" width="500"/></p>

```cpp
Please input the locations:Ralphs
Please input k:8

*************************Results******************************
Find K Closest Points Results:
1 St Agnes Church
2 Saint Agnes Elementary School
3 Warning Skate Shop
4 Menlo AvenueWest Twentyninth Street Historic District
5 Vermont Elementary School
6 MC39s Barber Shop
7 Anna39s Store
8 Vermont 38 29th Metro 204 Southbound
**************************************************************
Time taken by function: 6178 microseconds
```
<p align="center"><img src="ans/kmin8.png" alt="Routing" width="500"/></p>

```cpp
Please input the locations:Ralphs
Please input k:9

*************************Results******************************
Find K Closest Points Results:
1 St Agnes Church
2 Saint Agnes Elementary School
3 Warning Skate Shop
4 Menlo AvenueWest Twentyninth Street Historic District
5 Vermont Elementary School
6 MC39s Barber Shop
7 Anna39s Store
8 Vermont 38 29th Metro 204 Southbound
9 Driveway
**************************************************************
Time taken by function: 6574 microseconds
```
<p align="center"><img src="ans/kmin9.png" alt="Routing" width="500"/></p>


```cpp
Please input the locations:Ralphs
Please input k:10

*************************Results******************************
Find K Closest Points Results:
1 St Agnes Church
2 Saint Agnes Elementary School
3 Warning Skate Shop
4 Menlo AvenueWest Twentyninth Street Historic District
5 Vermont Elementary School
6 MC39s Barber Shop
7 Anna39s Store
8 Vermont 38 29th Metro 204 Southbound
9 Driveway
10 Vermont 38 29th Metro 204 Northbound
**************************************************************
Time taken by function: 6866 microseconds
```
<p align="center"><img src="ans/kmin10.png" alt="Routing" width="500"/></p>

From the result we can see that each time with the growth of the results, our outcomes's orders are same, which means our results can be rely on.\
Then what's interesting is that, no matter how long the results are, the time are the same, which also corresponding to the results that we need to travel all the data inside the map, so the run time complexity is O(n).

## Step 8: Learning Experience

During this semester, what basically I have learnt is how to use CPP to achieve data structrue, e.g tress, heaps. This is a really good class, which fixs a lot about my bad habbit "theory beyond practice". I believe we all can suffer from this, we can think a question to be very easy with the professor's analysing, however when it comes a time for us to do it in practice alone, a lot of of troubles will show up.\
And at first, it will take me like a whole weekend to finish the homework, which it really killed me, a lot bugs showed up, a lot of errors that happens beyond my expectation. What's more, the horrible thing was that, the code could be comnpailed with no probelm, but the results is horrible, far away from I expected. And with practice and practice, I gradually figure out when each error occurs, I can fix the problem quickly and I can gradually "think like a computer", which means the rate of the unexpected outcome become less and less. I am very proud of it!\
When the time comes to do the final project, I decided to do it alone to test myself. Each time I finish a function, a great sence of satisfication will show up, which can motivate me to continue. What's amazing thing is that like this ,step by step, I gradually finsh the whole project, even with the bonus one, which I cannot imagine at the begining. What impressed me most is that when I do the genetic algorithm, at first I thought it's very difficult, but like before, I split it into pieces, slowly writing the helper functions one by one to achieve the whole body of the GA. By the time the results show, I couldn't believe I did it without any error! Though it is not perfect, still have the improvement space, I am still proud of myself have done such thing. It's true the converging rate of it is not perfect, but if I still have time, I will dig into that.\
At last, I really appreciate Mr.Arash for teaching us this lesson, and all this cannot be done without TA's hard work. They build the whole structure for us, which is the most difficult part of the project. I still have a long way to go.\
Again, I really like this lesson, and I am really glad to know such a great professor and the TA team. I appreciate it a lot
