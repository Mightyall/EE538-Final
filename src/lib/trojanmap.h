#ifndef TROJAN_MAP_H
#define TROJAN_MAP_H
#define DOT_SIZE 5
#define LINE_WIDTH 3

#include <iostream>
#include <map>
#include <vector>
#include <unordered_map>
// A Node is the location of one point in the map.
class Node {
  public:
    Node(){};
    Node(const Node &n){id = n.id; lat = n.lat; lon = n.lon; name = n.name; neighbors = n.neighbors;};
    std::string id;    // A unique id assign to each point
    double lat;        // Latitude
    double lon;        // Longitude
    std::string name;  // Name of the location. E.g. "Bank of America".
    std::vector<std::string> neighbors;  // List of the ids of all neighbor points.
};

class TrojanMap {
 public:
  // A map of ids to Nodes.
  std::unordered_map<std::string, Node> data;
  
  //-----------------------------------------------------
  // TODO: You do not and should not change the following functions:

  // Create the menu.
  void PrintMenu();

  // Create the Dynamic menu.
  // void DynamicPrintMenu();

  // Read in the data
  void CreateGraphFromCSVFile();

  // Visualization
  // Given a location id, plot the point on the map.
  void PlotPoint(std::string id);

  // Given a lat and lon, plot the point on the map.
  void PlotPoint(double lat, double lon);

  // Given a vector of location ids draws the path (connects the points)
  void PlotPath(std::vector<std::string> &location_ids);

  // Given a vector of location ids draws the points on the map (no path).
  void PlotPoints(std::vector<std::string> &location_ids);

  // Given a vector of location ids draws the points on the map with path.
  void PlotPointsandEdges(std::vector<std::string> &location_ids, std::vector<double> &square);

  // Given a vector of location ids draws the points with their order on the map (no path).
  void PlotPointsOrder(std::vector<std::string> &location_ids);

  // Given a vector of location ids and origin, draws the points with their label.
  void PlotPointsLabel(std::vector<std::string> &location_ids, std::string origin);

  // Create the videos of the progress to get the path
  void CreateAnimation(std::vector<std::vector<std::string>>);

  // Transform the location to the position on the map
  std::pair<double, double> GetPlotLocation(double lat, double lon);
  //-----------------------------------------------------
  // TODO: Implement these functions and create unit tests for them:

  // Get the Latitude of a Node given its id.
  double GetLat(std::string id);

  // Get the Longitude of a Node given its id.
  double GetLon(std::string id);

  // Get the name of a Node given its id.
  std::string GetName(std::string id);

  // Get the id given its name.
  std::string GetID(std::string name);

  // Get the neighbor ids of a Node.
  std::vector<std::string> GetNeighborIDs(std::string id);

  // Get the distance between 2 nodes.
  double CalculateDistance(const std::string &a, const std::string &b);

  // Calculates the total path length for the locations inside the vector.
  double CalculatePathLength(const std::vector<std::string> &path);

  // Returns a vector of names given a partial name.
  std::vector<std::string> Autocomplete(std::string name);

  // Returns lat and long of the given the name.
  std::pair<double, double> GetPosition(std::string name);

  // Given the name of two locations, it should return the **ids** of the nodes
  // on the shortest path.
  std::vector<std::string> CalculateShortestPath_Dijkstra(std::string location1_name,
                                                 std::string location2_name);
  std::vector<std::string> CalculateShortestPath_Bellman_Ford(std::string location1_name,
                                                 std::string location2_name);

  // Given CSV filename, it read and parse locations data from CSV file,
  // and return locations vector for topological sort problem.
  std::vector<std::string> ReadLocationsFromCSVFile(std::string locations_filename);
  
  // Given CSV filenames, it read and parse dependencise data from CSV file,
  // and return dependencies vector for topological sort problem.
  std::vector<std::vector<std::string>> ReadDependenciesFromCSVFile(std::string dependencies_filename);

  // Given a vector of location names, it should return a sorting of nodes
  // that satisfies the given dependencies.
  std::vector<std::string> DeliveringTrojan(std::vector<std::string> &location_names,
                                            std::vector<std::vector<std::string>> &dependencies);

  // Given a vector of location ids, it should reorder them such that the path
  // that covers all these points has the minimum length.
  // The return value is a pair where the first member is the total_path,
  // and the second member is the reordered vector of points.
  // (Notice that we don't find the optimal answer. You can return an estimated
  // path.)
  std::pair<double, std::vector<std::vector<std::string>>> TravellingTrojanBrute(
      std::vector<std::string> &location_ids);
  
  std::pair<double, std::vector<std::vector<std::string>>> TravellingTrojan(
      std::vector<std::string> &location_ids);

  
  std::pair<double, std::vector<std::vector<std::string>>> TravellingTrojan_2opt(
      std::vector<std::string> &location_ids);

  // Given a subgraph specified by a square-shape area, determine whether there is a
  // cycle or not in this subgraph.
  // vector square has 4 elements: left/right/top/bottom bound in order.
  bool CycleDetection(std::vector<double> &square);

  // Given a location id and k, find the k closest points on the map
  std::vector<std::string> FindKClosestPoints(std::string name, int k);
  
  //----------------------------------------------------- User-defined functions
  // for djikstra
  std::string FindMinInDBUtNotInVisited(std::unordered_map<std::string, double> &d, std::vector<std::string> &visited);

  double Weight(std::string loc1, std::string loc2);

  //for tsp_backtracking

  void TSP_aux(
  std::string start, std::vector<std::string> &location_ids, std::string cur_node, double cur_cost, std::vector<std::string> &cur_path, std::pair<double, std::vector<std::vector<std::string>>> &results
);

  void TSP_auxBrute(
  std::string start, std::vector<std::string> &location_ids, std::string cur_node, double cur_cost, std::vector<std::string> &cur_path, std::pair<double, std::vector<std::vector<std::string>>> &results
);

// for circleDetection DFShelper
  bool DFS_helper(std::string rootID, std::map<std::string, int> &marks, std::string parent, std::vector<std::string> &res);

// for find K points
  void GetAllName(std::vector< std::pair<std::string, std::string> > &nameAndId);

// 2opt
double reverse_segment_if_better2opt(std::vector<std::string> &path, int i, int k, std::pair<double, std::vector<std::vector<std::string>>> &results);


// 3opt
std::pair<double, std::vector<std::vector<std::string>>> TravellingTrojan_3opt(
      std::vector<std::string> &location_ids);

double reverse_segment_if_better(std::vector<std::string> &path, int i, int j, int k, std::pair<double, std::vector<std::vector<std::string>>> &results);

//GA
std::pair<double, std::vector<std::vector<std::string>>> TravellingTrojan_GA(
       std::vector<std::string> &location_ids);

std::vector<std::vector<std::string>> CreateRandomPath(std::vector<std::string> &location_ids, int k);

double fitness(std::vector<std::string> path);

std::vector< double > CalculateGenerationFitness(std::vector<std::vector<std::string>> generation);

//std::vector<std::vector<std::string>> CrossOver(std::vector<std::string> A, std::vector<std::string> B);
void CrossOver(std::vector<std::string> &A, std::vector<std::string> B);

std::pair<int, int> RandomIndex(std::vector<std::string> &location);

void Mutation(std::vector<std::string> &path);

void Evolution(std::vector<std::string> &path, std::vector<std::vector<std::string>> &generation, double &pc);



};


#endif