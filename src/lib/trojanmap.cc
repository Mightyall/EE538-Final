#include "trojanmap.h"
#include <limits.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <algorithm>
#include <fstream>
#include <locale>
#include <map>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <sstream>
#include <string>
#include <utility>
// #include <bits/stdc++.h>
#include <cmath>
#include <iostream>
#include <cctype>
#include <unordered_set>
#include <stack>
#include <chrono>

#include "opencv2/core.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/videoio.hpp"

//-----------------------------------------------------
// TODO (Students): You do not and should not change the following functions:
//-----------------------------------------------------

/**
 * PrintMenu: Create the menu
 *
 */
void TrojanMap::PrintMenu() {

  std::string menu =
      "**************************************************************\n"
      "* Select the function you want to execute.                    \n"
      "* 1. Autocomplete                                             \n"
      "* 2. Find the position                                        \n"
      "* 3. CalculateShortestPath                                    \n"
      "* 4. Travelling salesman problem                              \n"
      "* 5. Cycle Detection                                          \n"
      "* 6. Topological Sort                                         \n"
      "* 7. Find K Closest Points                                    \n"
      "* 8. Exit                                                     \n"
      "**************************************************************\n";
  std::cout << menu << std::endl;
  std::string input;
  getline(std::cin, input);
  char number = input[0];
  switch (number)
  {
  case '1':
  {
    menu =
        "**************************************************************\n"
        "* 1. Autocomplete                                             \n"
        "**************************************************************\n";
    std::cout << menu << std::endl;
    menu = "Please input a partial location:";
    std::cout << menu;
    getline(std::cin, input);
    auto start = std::chrono::high_resolution_clock::now();  //count the time: start
    auto results = Autocomplete(input);  // somethng we need to write
    auto stop = std::chrono::high_resolution_clock::now(); //count the time: stop
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    menu = "*************************Results******************************\n";
    std::cout << menu;
    if (results.size() != 0) {
      for (auto x : results) std::cout << x << std::endl;
    } else {
      std::cout << "No matched locations." << std::endl;
    }
    menu = "**************************************************************\n";
    std::cout << menu;
    std::cout << "Time taken by function: " << duration.count() << " microseconds" << std::endl << std::endl;
    PrintMenu();
    break;
  }
  case '2':
  {
    menu =
        "**************************************************************\n"
        "* 2. Find the position                                        \n"
        "**************************************************************\n";
    std::cout << menu << std::endl;
    menu = "Please input a location:";
    std::cout << menu;
    getline(std::cin, input);
    auto start = std::chrono::high_resolution_clock::now();
    auto results = GetPosition(input);
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    menu = "*************************Results******************************\n";
    std::cout << menu;
    if (results.first != -1) {
      std::cout << "Latitude: " << results.first
                << " Longitude: " << results.second << std::endl;
      PlotPoint(results.first, results.second);
    } else {
      std::cout << "No matched locations." << std::endl;
    }
    menu = "**************************************************************\n";
    std::cout << menu;
    std::cout << "Time taken by function: " << duration.count() << " microseconds" << std::endl << std::endl;
    PrintMenu();
    break;
  }
  case '3':
  {
    menu =
        "**************************************************************\n"
        "* 3. CalculateShortestPath                                    \n"
        "**************************************************************\n";
    std::cout << menu << std::endl;
    menu = "Please input the start location:";
    std::cout << menu;
    std::string input1;
    getline(std::cin, input1);
    menu = "Please input the destination:";
    std::cout << menu;
    std::string input2;
    getline(std::cin, input2);
    auto start = std::chrono::high_resolution_clock::now();
    //auto results = CalculateShortestPath_Dijkstra(input1, input2);


    auto results = CalculateShortestPath_Bellman_Ford(input1, input2);


    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    menu = "*************************Results******************************\n";
    std::cout << menu;
    if (results.size() != 0) {
      for (auto x : results) std::cout << x << std::endl;
      std::cout << "The distance of the path is:" << CalculatePathLength(results) << " miles" << std::endl;
      PlotPath(results);
    } else {
      std::cout << "No route from the start point to the destination."
                << std::endl;
    }
    menu = "**************************************************************\n";
    std::cout << menu;
    std::cout << "Time taken by function: " << duration.count() << " microseconds" << std::endl << std::endl;
    PrintMenu();
    break;
  }
  case '4':
  {
    menu =
        "**************************************************************\n"
        "* 4. Traveling salesman problem                              \n"
        "**************************************************************\n";
    std::cout << menu << std::endl;
    menu = "In this task, we will select N random points on the map and you need to find the path to travel these points and back to the start point.";
    std::cout << menu << std::endl << std::endl;
    menu = "Please input the number of the places:";
    std::cout << menu;
    getline(std::cin, input);
    int num = std::stoi(input);
    std::vector<std::string> keys;
    for (auto x : data) {
      keys.push_back(x.first);
    }
    std::vector<std::string> locations;
    srand(time(NULL));
    for (int i = 0; i < num; i++)
      locations.push_back(keys[rand() % keys.size()]);
    PlotPoints(locations);
    std::cout << "Calculating ..." << std::endl;
    auto start = std::chrono::high_resolution_clock::now();


    //auto results = TravellingTrojan(locations);


    //auto results = TravellingTrojan_2opt(locations);

    //auto results = TravellingTrojan_3opt(locations);

    auto results = TravellingTrojan_GA(locations);


    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    CreateAnimation(results.second);
    menu = "*************************Results******************************\n";
    std::cout << menu;
    if (results.second.size() != 0) {
      for (auto x : results.second[results.second.size()-1]) std::cout << x << std::endl;
      menu = "**************************************************************\n";
      std::cout << menu;
      std::cout << "The distance of the path is:" << results.first << " miles" << std::endl;
      PlotPath(results.second[results.second.size()-1]);
    } else {
      std::cout << "The size of the path is 0" << std::endl;
    }
    menu = "**************************************************************\n"
           "You could find your animation at src/lib/output.avi.          \n";
    std::cout << menu;
    std::cout << "Time taken by function: " << duration.count() << " microseconds" << std::endl << std::endl;
    PrintMenu();
    break;
  }
  case '5':
  {
    menu =
        "**************************************************************\n"
        "* 5. Cycle Detection                                          \n"
        "**************************************************************\n";
    std::cout << menu << std::endl;
    menu = "Please input the left bound longitude(between -118.299 and -118.264):";
    std::cout << menu;
    getline(std::cin, input);
    std::vector<double> square;
    square.push_back(atof(input.c_str()));

    menu = "Please input the right bound longitude(between -118.299 and -118.264):";
    std::cout << menu;
    getline(std::cin, input);
    square.push_back(atof(input.c_str()));

    menu = "Please input the upper bound latitude(between 34.011 and 34.032):";
    std::cout << menu;
    getline(std::cin, input);
    square.push_back(atof(input.c_str()));

    menu = "Please input the lower bound latitude(between 34.011 and 34.032):";
    std::cout << menu;
    getline(std::cin, input);
    square.push_back(atof(input.c_str()));

    auto start = std::chrono::high_resolution_clock::now();
    auto results = CycleDetection(square);
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    menu = "*************************Results******************************\n";
    std::cout << menu;
    if (results == true)
      std::cout << "there exists cycle in the subgraph " << std::endl;
    else
      std::cout << "there exist no cycle in the subgraph " << std::endl;
    menu = "**************************************************************\n";
    std::cout << menu;
    std::cout << "Time taken by function: " << duration.count() << " microseconds" << std::endl << std::endl;
    PrintMenu();
    break;
  }
  case '6':
  {
    menu =
        "**************************************************************\n"
        "* 6. Topological Sort                                         \n"
        "**************************************************************\n";
    std::cout << menu << std::endl;
    menu = "Please input the locations filename:";
    std::cout << menu;
    std::string locations_filename;
    getline(std::cin, locations_filename);
    menu = "Please input the dependencies filename:";
    std::cout << menu;
    std::string dependencies_filename;
    getline(std::cin, dependencies_filename);

    // Read location names from CSV file
    std::vector<std::string> location_names;
    if (locations_filename == "")
      //location_names = {"Cardinal Gardens", "Coffee Bean1","CVS"};
      //location_names = {"1", "2", "3", "4", "5"};
      location_names = {"1", "2", "3"};
    else
      location_names = ReadLocationsFromCSVFile(locations_filename);

    // Read dependencies from CSV file
    std::vector<std::vector<std::string>> dependencies;
    if (dependencies_filename == "")
      //dependencies = {{"Coffee Bean1","Cardinal Gardens"}, {"CVS","Cardinal Gardens"}, {"CVS","Coffee Bean1"}};
      dependencies = {{"1", "2"}, {"2", "3"}, {"3", "1"}};

      //dependencies = {{"1", "3"}, {"2", "4"}, {"1", "4"},{"2", "5"}};

    else
      dependencies = ReadDependenciesFromCSVFile(dependencies_filename);

    // std::vector<std::string> location_names = {"Cardinal Gardens", "Coffee Bean1","CVS"};
    // std::vector<std::vector<std::string>> dependencies = {{"Coffee Bean1","Cardinal Gardens"}, {"CVS","Cardinal Gardens"}, {"CVS","Coffee Bean1"}};
    auto start = std::chrono::high_resolution_clock::now();
    auto result = DeliveringTrojan(location_names, dependencies);
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    menu = "*************************Results******************************";
    std::cout << menu << std::endl;
    std::cout << "Topological Sorting Results:" << std::endl;
    for (auto x : result) std::cout << x << std::endl;
    std::vector<std::string> node_ids;
    for (auto x: result) {
      std::string id = GetID(x);
      node_ids.push_back(id);
    }
    PlotPointsOrder(node_ids);
    menu = "**************************************************************\n";
    std::cout << menu;
    std::cout << "Time taken by function: " << duration.count() << " microseconds" << std::endl << std::endl;
    PrintMenu();
    break;
  }
    case '7':
  {
    menu =
        "**************************************************************\n"
        "* 7. Find K Closest Points                                    \n"
        "**************************************************************\n";
    std::cout << menu << std::endl;

    menu = "Please input the locations:";
    std::cout << menu;
    std::string origin;
    getline(std::cin, origin);
    menu = "Please input k:";
    std::cout << menu;
    getline(std::cin, input);
    int k = std::stoi(input);

    auto start = std::chrono::high_resolution_clock::now();
    auto result = FindKClosestPoints(origin, k);
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    menu = "*************************Results******************************";
    std::cout << menu << std::endl;
    std::cout << "Find K Closest Points Results:" << std::endl;
    int cnt = 1;
    for (auto x : result) {
      std::cout << cnt << " " << data[x].name << std::endl;
      cnt++;
    }
    PlotPointsLabel(result, GetID(origin));
    menu = "**************************************************************\n";
    std::cout << menu;
    std::cout << "Time taken by function: " << duration.count() << " microseconds" << std::endl << std::endl;
    PrintMenu();
    break;
  }
  case '8':
    break;
  default:
  {
    std::cout << "Please select 1 - 8." << std::endl;
    PrintMenu();
    break;
  }
  }
}


/**
 * CreateGraphFromCSVFile: Read the map data from the csv file
 *
 */
void TrojanMap::CreateGraphFromCSVFile() {
  std::fstream fin;
  fin.open("src/lib/map.csv", std::ios::in);
  std::string line, word;

  getline(fin, line);
  while (getline(fin, line)) {
    std::stringstream s(line);

    Node n;
    int count = 0;
    while (getline(s, word, ',')) {
      word.erase(std::remove(word.begin(), word.end(), '\''), word.end());
      word.erase(std::remove(word.begin(), word.end(), '"'), word.end());
      word.erase(std::remove(word.begin(), word.end(), '['), word.end());
      word.erase(std::remove(word.begin(), word.end(), ']'), word.end());
      if (count == 0)
        n.id = word;
      else if (count == 1)
        n.lat = stod(word);
      else if (count == 2)
        n.lon = stod(word);
      else if (count == 3)
        n.name = word;
      else {
        word.erase(std::remove(word.begin(), word.end(), ' '), word.end());
        n.neighbors.push_back(word);
      }
      count++;
    }
    data[n.id] = n;
  }
  fin.close();
}

/**
 * PlotPoint: Given a location id, plot the point on the map
 *
 * @param  {std::string} id : location id
 */
void TrojanMap::PlotPoint(std::string id) {
  std::string image_path = cv::samples::findFile("src/lib/input.jpg");
  cv::Mat img = cv::imread(image_path, cv::IMREAD_COLOR);
  auto result = GetPlotLocation(data[id].lat, data[id].lon);
  cv::circle(img, cv::Point(result.first, result.second), DOT_SIZE,
             cv::Scalar(0, 0, 255), cv::FILLED);
  cv::imshow("TrojanMap", img);
  cv::waitKey(1);
}
/**
 * PlotPoint: Given a lat and a lon, plot the point on the map
 *
 * @param  {double} lat : latitude
 * @param  {double} lon : longitude
 */
void TrojanMap::PlotPoint(double lat, double lon) {
  std::string image_path = cv::samples::findFile("src/lib/input.jpg");
  cv::Mat img = cv::imread(image_path, cv::IMREAD_COLOR);
  auto result = GetPlotLocation(lat, lon);
  cv::circle(img, cv::Point(int(result.first), int(result.second)), DOT_SIZE,
             cv::Scalar(0, 0, 255), cv::FILLED);
  cv::startWindowThread();
  cv::imshow("TrojanMap", img);
  cv::waitKey(1);
}

/**
 * PlotPath: Given a vector of location ids draws the path (connects the points)
 *
 * @param  {std::vector<std::string>} location_ids : path
 */
void TrojanMap::PlotPath(std::vector<std::string> &location_ids) {
  std::string image_path = cv::samples::findFile("src/lib/input.jpg");
  cv::Mat img = cv::imread(image_path, cv::IMREAD_COLOR);
  auto start = GetPlotLocation(data[location_ids[0]].lat, data[location_ids[0]].lon);
  cv::circle(img, cv::Point(int(start.first), int(start.second)), DOT_SIZE,
             cv::Scalar(0, 0, 255), cv::FILLED);
  for (auto i = 1; i < location_ids.size(); i++) {
    auto start = GetPlotLocation(data[location_ids[i - 1]].lat, data[location_ids[i - 1]].lon);
    auto end = GetPlotLocation(data[location_ids[i]].lat, data[location_ids[i]].lon);
    cv::circle(img, cv::Point(int(end.first), int(end.second)), DOT_SIZE,
               cv::Scalar(0, 0, 255), cv::FILLED);
    cv::line(img, cv::Point(int(start.first), int(start.second)),
             cv::Point(int(end.first), int(end.second)), cv::Scalar(0, 255, 0),
             LINE_WIDTH);
  }
  cv::startWindowThread();
  cv::imshow("TrojanMap", img);
  cv::waitKey(1);
}

/**
 * PlotPoints: Given a vector of location ids draws the points on the map (no path).
 *
 * @param  {std::vector<std::string>} location_ids : points
 */
void TrojanMap::PlotPoints(std::vector<std::string> &location_ids) {
  std::string image_path = cv::samples::findFile("src/lib/input.jpg");
  cv::Mat img = cv::imread(image_path, cv::IMREAD_COLOR);
  for (auto x : location_ids) {
    auto result = GetPlotLocation(data[x].lat, data[x].lon);
    cv::circle(img, cv::Point(result.first, result.second), DOT_SIZE,
               cv::Scalar(0, 0, 255), cv::FILLED);
  }
  cv::imshow("TrojanMap", img);
  cv::waitKey(1);
}

/**
 * PlotPoints: Given a vector of location ids draws the points on the map (no path).
 *
 * @param  {std::vector<std::string>} location_ids : points inside square
 * @param  {std::vector<double>} square : boundary
 */
void TrojanMap::PlotPointsandEdges(std::vector<std::string> &location_ids, std::vector<double> &square) {
  std::string image_path = cv::samples::findFile("src/lib/input.jpg");
  cv::Mat img = cv::imread(image_path, cv::IMREAD_COLOR);
  auto upperleft = GetPlotLocation(square[2], square[0]);
  auto lowerright = GetPlotLocation(square[3], square[1]);
  cv::Point pt1(int(upperleft.first), int(upperleft.second));
  cv::Point pt2(int(lowerright.first), int(lowerright.second));
  cv::rectangle(img, pt2, pt1, cv::Scalar(0, 0, 255));
  for (auto x : location_ids) {
    auto result = GetPlotLocation(data[x].lat, data[x].lon);
    cv::circle(img, cv::Point(result.first, result.second), DOT_SIZE,
               cv::Scalar(0, 0, 255), cv::FILLED);
    for(auto y : data[x].neighbors) {
      auto start = GetPlotLocation(data[x].lat, data[x].lon);
      auto end = GetPlotLocation(data[y].lat, data[y].lon);
      cv::line(img, cv::Point(int(start.first), int(start.second)),
              cv::Point(int(end.first), int(end.second)), cv::Scalar(0, 255, 0),
              LINE_WIDTH);
    }
  }
  cv::imshow("TrojanMap", img);
  cv::waitKey(1);
}

/**
 * PlotPointsOrder: Given a vector of location ids draws the points on the map (no path).
 *
 * @param  {std::vector<std::string>} location_ids : points
 */
void TrojanMap::PlotPointsOrder(std::vector<std::string> &location_ids) {
  std::string image_path = cv::samples::findFile("src/lib/input.jpg");
  cv::Mat img = cv::imread(image_path, cv::IMREAD_COLOR);
  for (auto x : location_ids) {
    auto result = GetPlotLocation(data[x].lat, data[x].lon);
    cv::putText(img, data[x].name, cv::Point(result.first, result.second), cv::FONT_HERSHEY_DUPLEX, 1.0, CV_RGB(255, 0, 0), 2);
  }
  // Plot dots and lines
  auto start = GetPlotLocation(data[location_ids[0]].lat, data[location_ids[0]].lon);
  cv::circle(img, cv::Point(int(start.first), int(start.second)), DOT_SIZE,
             cv::Scalar(0, 0, 255), cv::FILLED);
  for (auto i = 1; i < location_ids.size(); i++) {
    auto start = GetPlotLocation(data[location_ids[i - 1]].lat, data[location_ids[i - 1]].lon);
    auto end = GetPlotLocation(data[location_ids[i]].lat, data[location_ids[i]].lon);
    cv::circle(img, cv::Point(int(end.first), int(end.second)), DOT_SIZE,
               cv::Scalar(0, 0, 255), cv::FILLED);
    cv::arrowedLine(img, cv::Point(int(start.first), int(start.second)),
             cv::Point(int(end.first), int(end.second)), cv::Scalar(0, 255, 0),
             LINE_WIDTH);
  }
  cv::imshow("TrojanMap", img);
  cv::waitKey(1);
}

/**
 * PlotPoints: Given a vector of location ids draws the points on the map (no path).
 *
 * @param  {std::vector<std::string>} location_ids : points
 */
void TrojanMap::PlotPointsLabel(std::vector<std::string> &location_ids, std::string origin) {
  std::string image_path = cv::samples::findFile("src/lib/input.jpg");
  cv::Mat img = cv::imread(image_path, cv::IMREAD_COLOR);
  int cnt = 1;
  auto result = GetPlotLocation(data[origin].lat, data[origin].lon);
  cv::circle(img, cv::Point(result.first, result.second), DOT_SIZE,
               cv::Scalar(0, 255, 0), cv::FILLED);
  for (auto x : location_ids) {
    auto result = GetPlotLocation(data[x].lat, data[x].lon);
    cv::circle(img, cv::Point(result.first, result.second), DOT_SIZE,
               cv::Scalar(0, 0, 255), cv::FILLED);
    cv::putText(img, std::to_string(cnt), cv::Point(result.first, result.second), cv::FONT_HERSHEY_DUPLEX, 1.0, CV_RGB(255, 0, 0), 2);
    cnt++;
  }
  cv::imshow("TrojanMap", img);
  cv::waitKey(1);
}

/**
 * CreateAnimation: Create the videos of the progress to get the path
 *
 * @param  {std::vector<std::vector<std::string>>} path_progress : the progress to get the path
 */
void TrojanMap::CreateAnimation(std::vector<std::vector<std::string>> path_progress){
  cv::VideoWriter video("src/lib/output.avi", cv::VideoWriter::fourcc('M','J','P','G'), 10, cv::Size(1248,992));
  for(auto location_ids: path_progress) {
    std::string image_path = cv::samples::findFile("src/lib/input.jpg");
    cv::Mat img = cv::imread(image_path, cv::IMREAD_COLOR);
    auto start = GetPlotLocation(data[location_ids[0]].lat, data[location_ids[0]].lon);
    cv::circle(img, cv::Point(int(start.first), int(start.second)), DOT_SIZE,
              cv::Scalar(0, 0, 255), cv::FILLED);
    for (auto i = 1; i < location_ids.size(); i++) {
      auto start = GetPlotLocation(data[location_ids[i - 1]].lat, data[location_ids[i - 1]].lon);
      auto end = GetPlotLocation(data[location_ids[i]].lat, data[location_ids[i]].lon);
      cv::circle(img, cv::Point(int(end.first), int(end.second)), DOT_SIZE,
                cv::Scalar(0, 0, 255), cv::FILLED);
      cv::line(img, cv::Point(int(start.first), int(start.second)),
              cv::Point(int(end.first), int(end.second)), cv::Scalar(0, 255, 0),
              LINE_WIDTH);
    }
    video.write(img);
    cv::imshow("TrojanMap", img);
    cv::waitKey(1);
  }
	video.release();
}
/**
 * GetPlotLocation: Transform the location to the position on the map
 *
 * @param  {double} lat         : latitude
 * @param  {double} lon         : longitude
 * @return {std::pair<double, double>}  : position on the map
 */
std::pair<double, double> TrojanMap::GetPlotLocation(double lat, double lon) {
  std::pair<double, double> bottomLeft(34.01001, -118.30000);
  std::pair<double, double> upperRight(34.03302, -118.26502);
  double h = upperRight.first - bottomLeft.first;
  double w = upperRight.second - bottomLeft.second;
  std::pair<double, double> result((lon - bottomLeft.second) / w * 1248,
                                   (1 - (lat - bottomLeft.first) / h) * 992);
  return result;
}

//-----------------------------------------------------
// TODO: Student should implement the following:
//-----------------------------------------------------
/**
 * GetLat: Get the latitude of a Node given its id.
 *
 * @param  {std::string} id : location id
 * @return {double}         : latitude
 */
double TrojanMap::GetLat(std::string id) {
    double ans_lat = -1; // initial ans_lat with -1 if return ans_lat = -1 then the id doesn't exist

    auto it =data.find(id);
    if(it != data.end()){
      ans_lat = it->second.lat;
    }
    return ans_lat;
}


/**
 * GetLon: Get the longitude of a Node given its id.
 *
 * @param  {std::string} id : location id
 * @return {double}         : longitude
 */
double TrojanMap::GetLon(std::string id) {
    double ans_lon = -1; // -1 means id not exists
    auto it = data.find(id);
    if(it != data.end()){
      ans_lon = it->second.lon;
    }

    return ans_lon;
}

/**
 * GetName: Get the name of a Node given its id.
 *
 * @param  {std::string} id : location id
 * @return {std::string}    : name
 */
std::string TrojanMap::GetName(std::string id) {
    std::string ans_name = ""; // "" means id not exists
    auto it  = data.find(id);
    if(it != data.end()){
      ans_name = it->second.name;
    }
    return ans_name;
}

/**
 * GetNeighborIDs: Get the neighbor ids of a Node.
 *
 * @param  {std::string} id            : location id
 * @return {std::vector<std::string>}  : neighbor ids
 */
std::vector<std::string> TrojanMap::GetNeighborIDs(std::string id) {
    std::vector<std::string> ans_neighbors;
    auto it = data.find(id);
    if(it != data.end()){
      ans_neighbors = it->second.neighbors;
    }
    return ans_neighbors;
}

/**
 * CalculateDistance: Get the distance between 2 nodes.
 *
 * @param  {std::string} a  : a_id
 * @param  {std::string} b  : b_id
 * @return {double}  : distance in mile
 */
double TrojanMap::CalculateDistance(const std::string &a_id, const std::string &b_id) {
  // Do not change this function
  // TODO: Use Haversine Formula:
  // dlon = lon2 - lon1;
  // dlat = lat2 - lat1;
  // a = (sin(dlat / 2)) ^ 2 + cos(lat1) * cos(lat2) * (sin(dlon / 2)) ^ 2;
  // c = 2 * arcsin(min(1, sqrt(a)));
  // distances = 3961 * c;

  // where 3961 is the approximate radius of the earth at the latitude of
  // Washington, D.C., in miles
  Node a = data[a_id];
  Node b = data[b_id];
  double dlon = (b.lon - a.lon) * M_PI / 180.0;
  double dlat = (b.lat - a.lat) * M_PI / 180.0;
  double p = pow(sin(dlat / 2),2.0) + cos(a.lat * M_PI / 180.0) * cos(b.lat * M_PI / 180.0) * pow(sin(dlon / 2),2.0);
  double c = 2 * asin(std::min(1.0,sqrt(p)));
  return c * 3961;
}

/**
 * CalculatePathLength: Calculates the total path length for the locations inside the vector.
 *
 * @param  {std::vector<std::string>} path : path
 * @return {double}                        : path length
 */
double TrojanMap::CalculatePathLength(const std::vector<std::string> &path) {
  // Do not change this function
  double sum = 0;
  for (int i = 0;i < path.size()-1; i++) {
    sum += CalculateDistance(path[i], path[i+1]);
  }
  return sum;
}

/**
 * Autocomplete: Given a parital name return all the possible locations with
 * partial name as the prefix.
 *
 * @param  {std::string} name          : partial name
 * @return {std::vector<std::string>}  : a vector of full names
 */
std::vector<std::string> TrojanMap::Autocomplete(std::string name){
  std::vector<std::string> results;

  std::transform(name.begin(), name.end(), name.begin(), ::tolower);

  for(auto it = data.begin(); it != data.end(); it++){
    std::string temp = it->second.name.substr(0, name.length());
    std::transform(temp.begin(), temp.end(), temp.begin(),  ::tolower);
    if(name == temp){
      results.push_back(it->second.name);
    }

  }

  if(results.size() == 0){
    return {""};
  }

  return results;
}

/**
 * GetPosition: Given a location name, return the position.
 *
 * @param  {std::string} name          : location name
 * @return {std::pair<double,double>}  : (lat, lon)
 */
std::pair<double, double> TrojanMap::GetPosition(std::string name) {
  std::pair<double, double> results(-1, -1);    //if the name is not in the map, then we return -1 -1 to present error
  double lat_temp = -1;
  double lon_temp = -1;
  for(auto it = data.begin(); it != data.end(); it++){
    if(it->second.name == name){
      lat_temp = it->second.lat;
      lon_temp = it->second.lon;
      PlotPoint(lat_temp, lon_temp);
    }
  }
  std::cout<<lat_temp<<lon_temp<<std::endl;
  results.first = lat_temp;
  results.second = lon_temp;
  return results;
}

/**
 * GetID: Given a location name, return the id.
 * If the node does not exist, return an empty string.
 *
 * @param  {std::string} name          : location name
 * @return {int}  : id
 */
std::string TrojanMap::GetID(std::string name) {
  std::string res = "";
  for(auto it = data.begin(); it != data.end(); it++){
    if(name == it->second.name){
      res = it->first;
    }
  }
  return res;
}






// Djikstra helper function I: FindMinInDButNotVisited   goal is as the function name
std::string TrojanMap::FindMinInDBUtNotInVisited(std::unordered_map<std::string, double> &d, std::vector<std::string> &visited){
  std::string min_id;
  double minValue;
  std::unordered_map<std::string, double> temp(d);
  double Inf = __INT_MAX__;
  //go through visited, for each iter, find the id corresponding to the temp ,change it value to Inf, then find the min value in temp
  for(int i = 0; i < visited.size(); i++){
    std::string temp_id = visited[i];
    auto it_find = temp.find(temp_id);
    if(it_find != temp.end()) it_find->second = Inf;

  }

  //find the min id, go through the temp, strore the min value and it's id;
  auto it_d = temp.begin();
  min_id = it_d->first;
  minValue = it_d->second;
  for(; it_d != temp.end(); it_d++){

    if(it_d->second < minValue){
      minValue = it_d->second;
      min_id = it_d->first;
    }

  }

  return min_id;
}

// Djikstra helper function II: Weight goal is to find the distance between input 2 id
double TrojanMap::Weight(std::string min_id, std::string temp_id){
    double weight;
    double Inf = __INT_MAX__;
    std::vector<std::string> min_id_neighbors = data[min_id].neighbors; // create the neighbors

    auto it = find(min_id_neighbors.begin(), min_id_neighbors.end(),  temp_id);

    if(it == min_id_neighbors.end()){
      weight = Inf; //current id not in the neighbors of min id, which means they are not connected
    }

    else if(min_id == temp_id){
      weight = 0;
    }

    else{
      weight = CalculateDistance(min_id, temp_id);

    }
  //}

  return weight;
}


/**
 * CalculateShortestPath_Dijkstra: Given 2 locations, return the shortest path which is a
 * list of id.
 *
 * @param  {std::string} location1_name     : start
 * @param  {std::string} location2_name     : goal
 * @return {std::vector<std::string>}       : path
 */

//   CalculateDistance(const std::string &a_id, const std::string &b_id)
std::vector<std::string> TrojanMap::CalculateShortestPath_Dijkstra(
    std::string location1_name, std::string location2_name) {

  std::vector<std::string> path;

  std::unordered_map<std::string, double> d;  // id : dist
  std::unordered_map<std::string, std::string> pr; // id : father
  std::vector<std::string> visited;
  std::string start = GetID(location1_name);
  std::string end = GetID(location2_name);
  std::string unknow = " ";

  for(auto it : data){
    // initial d and pr 
    d[it.first] = Weight(start, it.first);

    std::vector<std::string> startNei = GetNeighborIDs(start);

    if(std::find(startNei.begin(), startNei.end(), it.first) != startNei.end()){
      pr[it.first] = start;
    }

    else if(start == it.first){
      pr[it.first] = start;
    }

    else{
      pr[it.first] = unknow;
    }

  }

  visited.push_back(start);

  int count = 0;
  while(visited.size() < data.size()){

    count += 1;

    if(count == 50){
      std::cout<<"......."<<std::endl;
      count = 0;
    }

    std::string u = FindMinInDBUtNotInVisited(d, visited);

    visited.push_back(u);

    //update d and pr
    // since we have find the true value of the shortest path
    // we need to consider who the real father is
    // if current d[it.first] is changed, meaning there is an another father can make it smaller
    // so it.first current father must be changed to u !

    for(auto it : data){
      double old = d[it.first];
      d[it.first] = std::min(d[it.first], d[u] + Weight(u, it.first));

      if(old != d[it.first]){
        //current it is modified, change the father
        pr[it.first] = u;
      }
      
    }

    if(u == end){
      break;
    }
    
  }

  std::cout<<"final len to end  "<<d[end]<<std::endl;
  std::string father = pr[end];
  path.push_back(end);
  while(father != start){
    std::cout<<father<<std::endl;
    path.push_back(father);
    father = pr[father];
  }
  path.push_back(start);

  std::reverse(path.begin(), path.end());

  
  return path;
}



/**
 * CalculateShortestPath_Bellman_Ford: Given 2 locations, return the shortest path which is a
 * list of id.
 *
 * @param  {std::string} location1_name     : start
 * @param  {std::string} location2_name     : goal
 * @return {std::vector<std::string>}       : path
 */
std::vector<std::string> TrojanMap::CalculateShortestPath_Bellman_Ford(
    std::string location1_name, std::string location2_name){
  std::vector<std::string> path;

  double Inf = __INT_MAX__;
  std::string unknown = "-1";
  std::string start_id = GetID(location1_name);
  std::string end_id = GetID(location2_name);
  std::unordered_map<std::string, double> d(data.size());
  std::unordered_map<std::string, std::string> pr;   //pr id and it's precessor's id
  std::vector<std::string> temp_neighbors;

  //Step 1: initial graph
  for(auto it = data.begin(); it != data.end(); it++){
    if(it->first != start_id){
      // current id is not the start id, then d[id] = Inf, pr[id] = unknown;
      d[it->first] = Inf;
      pr[it->first] = unknown;
    }

    else{
      // current id is the start id, then d[start id] = 0, pr[start id] ??
      d[start_id] = 0;
      pr[start_id] = start_id;
    }
  }

  //Step 2:relax edges repeatedly
  for(int i = 0; i < data.size() -1; i++){
    // repeat data.size() - 1 times
    // for each node we need to check and relax it
    //since d[start_id] = 0 is the min value it can reach, so dont need to worry about itea contains the start_id
    for(auto it_v = data.begin(); it_v != data.end(); it_v++){

      temp_neighbors = it_v->second.neighbors;

      for(auto u = temp_neighbors.begin(); u != temp_neighbors.end(); u++){

        if(d[*u] + Weight(*u, it_v->first) < d[it_v->first]){
          d[it_v->first] = d[*u] + Weight(*u, it_v->first);
          pr[it_v->first] = *u;
        }
      }
    }
  }

  std::cout<<"caculation over"<<std::endl;

  path.push_back(end_id);
  std::string tempId = end_id;
  //find the path back
  while(tempId != start_id){

    //std::cout<<pr[tempId]<<std::endl;
    path.push_back(pr[tempId]);
    tempId = pr[tempId];

  }

  std::reverse(path.begin(), path.end());



  return path;
}

/**
 * Travelling salesman problem: Given a list of locations, return the shortest
 * path which visit all the places and back to the start point.
 *
 * @param  {std::vector<std::string>} input : a list of locations needs to visit
 * @return {std::pair<double, std::vector<std::vector<std::string>>} : a pair of total distance and the all the progress to get final path
 */
std::pair<double, std::vector<std::vector<std::string>>> TrojanMap::TravellingTrojan(
                                    std::vector<std::string> &location_ids) {
  std::pair<double, std::vector<std::vector<std::string>>> results;

  // we nned to change the full path condition
  // 3 conditions need to be consdier
  // 1) final cost > results -> frist ------- ignore
  // 2) final cost = results -> frist ------- results->second.push_bak current path
  // 3) final cost < results -> frist ------- results before are wrong!  -> reset results & results -> frist = final cost ; result -> second.push_back cur path

  std::string start = location_ids[0];
  std::cout<<location_ids.size()<<"          "<<start<<std::endl;
  std::vector<std::string> cur_path = {start};
  results.first = __INT_MAX__;
  TSP_aux(start, location_ids, start, 0, cur_path, results);
  std::cout<<"the shortest path is"<<results.first<<"  and the size the min_path is: "<<results.second.size()<<std::endl;
  
  return results;
}

void TrojanMap::TSP_aux(
  std::string start, std::vector<std::string> &location_ids, std::string cur_node, double cur_cost, std::vector<std::string> &cur_path, std::pair<double, std::vector<std::vector<std::string>>> &results)
  {
    if(cur_path.size() == location_ids.size()){
      // now we are in the leaf, check!
      cur_path.push_back(start);

      double final_cost = cur_cost + CalculateDistance(start, cur_node);

      // we need to decide whether to put this in
      if(final_cost <= results.first){
        // we get a min one
        results.second.push_back(cur_path);
        results.first = final_cost;
      }

      return;
    }

    if(cur_cost > results.first){
      return;
    }

    //Then we are not in the leaf
    for(auto it = location_ids.begin(); it != location_ids.end(); it++){
      auto itFindCurId = find(cur_path.begin(), cur_path.end(), *it);
      if(itFindCurId != cur_path.end()){
        //currrent id is in the path, we ignore
        continue;
      }

      else{
        //current item not in the path, we add it
        std::vector<std::string> next_path = cur_path;
        next_path.push_back(*it);
        TSP_aux(start, location_ids, *it, cur_cost + CalculateDistance(cur_node, *it), next_path, results);

      }
    }
}




// q6 topo

/**
 * Given CSV filename, it read and parse locations data from CSV file,
 * and return locations vector for topological sort problem.
 *
 * @param  {std::string} locations_filename     : locations_filename
 * @return {std::vector<std::string>}           : locations
 */
std::vector<std::string> TrojanMap::ReadLocationsFromCSVFile(std::string locations_filename){
  std::vector<std::string> location_names_from_csv;

  std::vector<std::string> name;

  std::fstream fin;
  fin.open(locations_filename, std::ios::in);  // open file accoring to the path <absolutue>
  std::string line, word;

  getline(fin, line);
  while(getline(fin, line)){

    std::stringstream s(line);


    while(getline(s, word, ',')){

      word.erase(std::remove(word.begin(), word.end(), '\''), word.end());
      word.erase(std::remove(word.begin(), word.end(), '"'), word.end());
      word.erase(std::remove(word.begin(), word.end(), '['), word.end());
      word.erase(std::remove(word.begin(), word.end(), ']'), word.end());

      name.push_back(word);


    }

  }

  fin.close();

  // for(auto it : name){
  //   std::cout<<it<<std::endl;
  // }

  location_names_from_csv = name;

  return location_names_from_csv;
}



/**
 * Given CSV filenames, it read and parse dependencise data from CSV file,
 * and return dependencies vector for topological sort problem.
 *
 * @param  {std::string} dependencies_filename     : dependencies_filename
 * @return {std::vector<std::vector<std::string>>} : dependencies
 */
std::vector<std::vector<std::string>> TrojanMap::ReadDependenciesFromCSVFile(std::string dependencies_filename){
  std::vector<std::vector<std::string>> dependencies_from_csv;

  std::string father;
  std::string child;


  std::fstream fin;
  fin.open(dependencies_filename, std::ios::in);  // open file accoring to the path <absolutue>
  std::string line, word;

  getline(fin, line);
  while(getline(fin, line)){

    std::stringstream s(line);

    int count = 0;

    std::vector<std::string> temp;

    while(getline(s, word, ',')){

      word.erase(std::remove(word.begin(), word.end(), '\''), word.end());
      word.erase(std::remove(word.begin(), word.end(), '"'), word.end());
      word.erase(std::remove(word.begin(), word.end(), '['), word.end());
      word.erase(std::remove(word.begin(), word.end(), ']'), word.end());

      if(count == 0){
        father = word;
        temp.push_back(father);
      }

      else if(count == 1){
       child = word;
       temp.push_back(child);
      }

      count += 1;
    }

    for(auto it : temp){
        std::cout<<it<<std::endl;
      }
      std::cout<<"---------------"<<std::endl;

    dependencies_from_csv.push_back(temp);

  }

  fin.close();

  return dependencies_from_csv;
}
// /Users/kk9912/Desktop/github/EE538FINAL/final-project-Mightyall/input/topologicalsort_locations.csv
// /Users/kk9912/Desktop/github/EE538FINAL/final-project-Mightyall/input/topologicalsort_dependencies.csv

/**
 * DeliveringTrojan: Given a vector of location names, it should return a sorting of nodes
 * that satisfies the given dependencies.
 *
 * @param  {std::vector<std::string>} locations                     : locations
 * @param  {std::vector<std::vector<std::string>>} dependencies     : prerequisites
 * @return {std::vector<std::string>} results                       : results
 */
std::vector<std::string> TrojanMap::DeliveringTrojan(std::vector<std::string> &locations,
                                                     std::vector<std::vector<std::string>> &dependencies){
  // void TrojanMap::PlotPointsOrder(std::vector<std::string> &location_ids)
  std::vector<std::string> result;

  std::map<std::string, int> indegree;
  std::map<std::string, int> marks;

  // initialize the indegree with 0
  for(auto ele : locations){
    indegree[ele] = 0;
    marks[ele] = 0;
  }


  // caculate the degree of ele in the locations
  for(auto i : dependencies){
    for(int j = 1; j < i.size(); j++){
      // current id is been pointed
      indegree[i[j]] += 1;
    }
  }

  for(auto i : indegree){
    std::cout<<i.first<<"   "<<i.second<<std::endl;
  }

  int count = 0;

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

    count += 1;

    if(count > 10*locations.size()){
      std::cout<<"There is no feasible answer"<<std::endl;
      std::vector<std::string> empty = {""};
      return empty;
    }

  }

  //std::reverse(result.begin(), result.end());

  PlotPointsOrder(result);
  return result;
}

// topo end

/**
 * Cycle Detection: Given four points of the square-shape subgraph, return true if there
 * is a cycle path inside the square, false otherwise.
 *
 * @param {std::vector<double>} square: four vertexes of the square area
 * @return {bool}: whether there is a cycle or not
 */
bool TrojanMap::CycleDetection(std::vector<double> &square) {
  // in this question, we may need to use void TrojanMap::PlotPointsandEdges(std::vector<std::string> &location_ids, std::vector<double> &square)
  //bool result = false;
  std::vector<std::string> location_ids;
  std::vector<std::string> res;
  //lat, lon is  34.0112 -118.283
  std::cout<<square[0]<<square[1]<<square[2]<<square[3]<<std::endl;
  std::map<std::string, int> marks;
  std::string parent = " ";

  // logical: When you start from a node, you mark it as visited.
  // If you hit a node that has a "visited" marking, it means there is a back edge.
  // If the cycle is connected to the parent, ignore it.

  for(auto it = data.begin(); it != data.end(); it++){

    int flag = 0;

    if(it->second.lat < square[2]){
      flag += 1;
    }

    if(it->second.lat > square[3]){
      flag += 1;
    }

    if(it->second.lon < square[1]){
      flag += 1;
    }

    if(it->second.lon > square[0]){
      flag += 1;
    }

    if(flag == 4){

      location_ids.push_back(it->second.id);

      marks[it->second.id] = 0;

    }
  }


  for(int i = 0; i <location_ids.size(); i++){
    //each node in location_id

    if(marks[location_ids[i]] != 1){

      //current id is not visited

      if(DFS_helper(location_ids[i], marks, parent, res) == true){
        PlotPointsandEdges(res, square);
        return true;
      }
    }
  }

  return false;
}


  // @ marks : visited
  // @ unvisited : ids that have not been visited
  // helper need to be bool ? once it reached to a cycle, return true, else continue
  // if you have iter all ids, cout them and return flase


//Please input the left bound longitude(between -118.299 and -118.264):-118.290919
//Please input the right bound longitude(between -118.299 and -118.264):-118.282911
//Please input the upper bound latitude(between 34.011 and 34.032):34.02235
//Please input the lower bound latitude(between 34.011 and 34.032):34.019675

bool TrojanMap::DFS_helper(std::string rootID, std::map<std::string, int> &marks, std::string parent, std::vector<std::string> &res){

  // mark the current result as visited
  std::cout<<"currently visiting :  "<<rootID<<std::endl;
  marks[rootID] = 1;
  res.push_back(rootID);
  std::vector<std::string> tempNeighbors = GetNeighborIDs(rootID);
  for(auto child : tempNeighbors){
    //std::cout<<"current child is  "<<child<<"  with  parent  "<<rootID<<std::endl;

    if(marks[child] == 0){
      if(DFS_helper(child, marks, rootID, res) == true){
        return true;
      }
    }

    else{
      if(child != parent){

        std::cout<<"--------------"<<std::endl;
        std::cout<<"current child has been visited : "<<child<<" with parent :"<<parent<<std::endl;
        std::cout<<"--------------"<<std::endl;
        return true;

      }

    }

  }
  return false;

}

/**
 * FindKClosetPoints: Given a location id and k, find the k closest points on the map
 *
 * @param {std::string} name: the name of the location
 * @param {int} k: number of closest points
 * @return {std::vector<std::string>}: k closest points
 */
std::vector<std::string> TrojanMap::FindKClosestPoints(std::string name, int k) {
  std::vector<std::string> res;
  std::vector< std::pair<std::string, std::string> > nameAndId;
  std::priority_queue< std::pair<double, std::string> > ans; // value ; location name
  // we set queue size as k + 1, so there always exist itself be the minvalue = 0

  std::string startID = GetID(name);

  GetAllName(nameAndId);

  for(auto it : nameAndId){
    // it :: pair<name id>

    if(it.first == name){
      continue;
    }

    double tempDist = CalculateDistance(startID, it.second);
    std::pair<double, std::string> temp(tempDist, it.first);

    if(ans.size() < k){
      ans.push(temp);
    }

    else if(ans.size() == k){
      if(ans.top().first > tempDist){
        // pop the first ele in queue and push the new result
        ans.pop();
        ans.push(temp);
      }
    }

  }

  while(!ans.empty()){
    std::string temp = GetID(ans.top().second);
    //std::cout<<temp<<std::endl;
    res.push_back(temp);
    ans.pop();
  }

  std::reverse(res.begin(), res.end());
  for(auto it : res){
    std::cout<<it<<std::endl;
  }


  return res;
}



void TrojanMap::GetAllName(std::vector< std::pair<std::string, std::string> > &nameAndId){

  for(auto it : data){
    if(it.second.name != ""){
      //std::cout<<"name and id are :  "<<it.second.name<<"  "<<it.second.id<<std::endl;
      std::pair<std::string, std::string> temp(it.second.name, it.second.id);
      nameAndId.push_back(temp);
    }
  }

}


std::pair<double, std::vector<std::vector<std::string>>> TrojanMap::TravellingTrojan_3opt(
       std::vector<std::string> &location_ids){
  std::pair<double, std::vector<std::vector<std::string>>> results;
  std::vector< std::vector<int> > combinations;

  std::vector<std::string> path1(location_ids);
  std::vector<std::string> path2(location_ids);
  path2.push_back(location_ids[0]);



  // generate all comnbinations of segements
  for(int i = 1; i < location_ids.size(); i ++){
    for(int j = i + 2; j < location_ids.size(); j++){
      for(int k = j + 2; k < location_ids.size() + (i > 0); k++){
        std::vector<int> temp;
        temp.push_back(i);
        temp.push_back(j);
        temp.push_back(k);
        std::cout<<i<<j<<k<<std::endl;
        combinations.push_back(temp);
      }
    }
  }

  while(true){
    double delta = 0;
    for(auto it: combinations){
      delta += reverse_segment_if_better(path2, it[0], it[1], it[2], results);
    }

    if(delta >= 0){
      break;
    }
  }

  return results;
         
}

double TrojanMap::reverse_segment_if_better(std::vector<std::string> &path, int i, int j, int k, std::pair<double, std::vector<std::vector<std::string>>> &results){

  std::string a = path[i - 1];
  std::string b = path[i];

  std::string c = path[j - 1];
  std::string d = path[j];

  std::string e = path[k - 1];
  std::string f = path[k % path.size()];

  double d0 = CalculateDistance(a,b) + CalculateDistance(c,d) + CalculateDistance(e,f);
  double d1 = CalculateDistance(a,c) + CalculateDistance(b,d) + CalculateDistance(e,f);
  double d2 = CalculateDistance(a,b) + CalculateDistance(c,e) + CalculateDistance(d,f);
  double d3 = CalculateDistance(a,d) + CalculateDistance(e,b) + CalculateDistance(c,f);
  double d4 = CalculateDistance(f,b) + CalculateDistance(c,d) + CalculateDistance(e,a);

  if(d0 > d1){
    std::reverse(path.begin() + i, path.begin() + j);
    results.second.push_back(path);
    return d1 - d0;
  }

  else if(d0 > d2){
    std::reverse(path.begin() + j, path.begin() + k);
    results.second.push_back(path);
    return d2 - d0;
  }

  else if(d0 > d4){
    std::reverse(path.begin() + i, path.begin() + k);
    results.second.push_back(path);
    return d4 - d0;
  }

  else if(d0 > d3){
    int count = 0;
    std::vector<std::string> path1(path.begin() + j, path.begin() + k);
    std::vector<std::string> path2(path.begin() + i, path.begin() + j);
    path1.insert(path1.end(), path2.begin(), path2.end());

    for(auto it : path1){
      path[i + count] = it;
    }
    results.second.push_back(path);
    
    return d3 - d0;
  }


  return 0;
}




std::pair<double, std::vector<std::vector<std::string>>> TrojanMap::TravellingTrojan_2opt(
      std::vector<std::string> &location_ids){

  std::pair<double, std::vector<std::vector<std::string>>> results;
  std::vector< std::vector<int> > combinations;

  std::vector<std::string> path1(location_ids);
  std::vector<std::string> path2(location_ids);
  path2.push_back(location_ids[0]);



  // generate all comnbinations of segements
  for(int i = 1; i < location_ids.size(); i ++){

      for(int k = i + 1; k < location_ids.size() + 1; k++){
        std::vector<int> temp;
        temp.push_back(i);

        temp.push_back(k);
        //std::cout<<i<<j<<k<<std::endl;
        combinations.push_back(temp);
      }

  }

  while(true){
    double delta = 0;
    for(auto it: combinations){
      delta += reverse_segment_if_better2opt(path2, it[0], it[1], results);
    }

    if(delta >= 0){
      break;
    }
  }

  results.first = CalculatePathLength(results.second[results.second.size() - 1]);


  return results;
}


double TrojanMap::reverse_segment_if_better2opt(std::vector<std::string> &path, int i, int k, std::pair<double, std::vector<std::vector<std::string>>> &results){

  std::string a = path[i - 1];
  std::string b = path[i];


  std::string e = path[k - 1];
  std::string f = path[k % path.size()];

  double d0 = CalculateDistance(a,b) + CalculateDistance(e,f);
  double d1 = CalculateDistance(a,e) + CalculateDistance(b,f);
  


  if(d0 > d1){
    std::reverse(path.begin() + i, path.begin() + k);
    results.second.push_back(path);
    //results.first = CalculatePathLength(path);
    return d1 - d0;
  }


  return 0;
}















// GA

std::pair<double, std::vector<std::vector<std::string>>> TrojanMap::TravellingTrojan_GA(
       std::vector<std::string> &location_ids){
  std::pair<double, std::vector<std::vector<std::string>>> results;
  std::vector<std::vector<std::string>> BestPathEachGeneration;

  int maxGeneration = 1000;
  int inn = 50; //size of the population;
  int currentGenerationCounter = 0;

  double pc = 0.8; // crossover proportion
  double pm = 0.2; // mutation proportion
  //double pn = 0.1; // without changing proportion

  int pcIndex = inn * pc;
  int pmIndex = inn * pm;



  // first generate some random paths
  std::vector<std::vector<std::string>> generation = CreateRandomPath(location_ids, inn);


  std::vector<double> PathFitness = CalculateGenerationFitness(generation);
  auto biggest = std::max_element(PathFitness.begin(), PathFitness.end());
  int index_big = std::distance(PathFitness.begin(), biggest);
  std::cout<<"current best fitness is :  "<<PathFitness[index_big]<<std::endl;
  std::vector<std::string> tempLoop = generation[index_big];
  tempLoop.push_back(tempLoop[0]);
  BestPathEachGeneration.push_back(tempLoop); 
  results.first = PathFitness[index_big];


  // ---------------------------------- //
  // ---------start Algorithm---------- //
  // ---------------------------------- //
  
  while(currentGenerationCounter < maxGeneration){

    //push the best into res

    std::vector<std::vector<std::string>> NewGeneration;
    NewGeneration.push_back(generation[index_big]);

    //create new generations
    //std::vector<std::vector<std::string>> NewGeneration;
    for(int i = 0; i < generation.size() - 1; i++){

      Evolution(generation[i], generation, pc);
      NewGeneration.push_back(generation[i]);

    }
    std::cout<<"eve over this ge"<<std::endl;


    currentGenerationCounter += 1;
    std::cout<<currentGenerationCounter<<"     current generation"<<std::endl;
    generation = NewGeneration;

    PathFitness = CalculateGenerationFitness(generation);
    auto biggest = std::max_element(PathFitness.begin(), PathFitness.end());
    index_big = std::distance(PathFitness.begin(), biggest);
    if(results.first < PathFitness[index_big]){
      std::cout<<"current best fitness is :  "<<PathFitness[index_big]<<"  with current generation:  "<< currentGenerationCounter <<std::endl;
      tempLoop = generation[index_big];
      tempLoop.push_back(tempLoop[0]);
      BestPathEachGeneration.push_back(tempLoop);
      results.first = PathFitness[index_big];
    }
     
    
    

  }

  std::cout<<"evovle over !"<<std::endl;
  results.first = 0;
  results.second = BestPathEachGeneration;


  return results;
  }





std::vector<std::vector<std::string>> TrojanMap::CreateRandomPath(std::vector<std::string> &location_ids, int k){
  std::vector<std::vector<std::string>> results;
  std::vector< std::string > temp(location_ids);
  int i = 0;
  while(i < k){
    
    std::pair<int, int> minMax = RandomIndex(location_ids);
    int min = minMax.first;
    int max = minMax.second;

    std::vector< std::string > temp(location_ids);

    std::reverse(temp.begin() + min, temp.begin() + max);

    results.push_back(temp);

    i += 1;



  }
  return results;
}



double TrojanMap::fitness(std::vector<std::string> path){
  return 1/CalculatePathLength(path);
}

std::vector< double > TrojanMap::CalculateGenerationFitness(std::vector<std::vector<std::string>> generation){

  std::vector< double > res;

  for(auto it : generation){

    it.push_back(it[0]);
    
    res.push_back(fitness(it));
  }

  return res;

}



void TrojanMap::CrossOver(std::vector<std::string> &A, std::vector<std::string> B){

  std::vector<std::string> res;

  std::pair<int, int> minMax = RandomIndex(A);
  int min = minMax.first;
  int max = minMax.second;

  std::vector<std::string> Anew(A);
  std::vector<std::string> Bnew(B);

  std::vector<std::string> Apart1(A.begin() + min, A.begin() + max + 1);
  std::vector<std::string> Bpart1(B.begin() + min, B.begin() + max + 1);

  // make the reflect table
  for(int i = 0; i < A.size(); i++){


    if(i >= min and i <= max){
      //std::cout<<"B"<<i - min<<Bpart1[i - min]<<std::endl;
      Anew[i] = Bpart1[i - min];
      Bnew[i] = Apart1[i - min];

    }

    else{

    while (std::find(Bpart1.begin(), Bpart1.end(), Anew[i]) != Bpart1.end()){
      auto it = std::find(Bpart1.begin(), Bpart1.end(), Anew[i]);
      Anew[i] = Apart1[std::distance(Bpart1.begin(), it)];
    }

    while (std::find(Apart1.begin(), Apart1.end(), Bnew[i]) != Apart1.end()){
      auto it = std::find(Apart1.begin(), Apart1.end(), Bnew[i]);
      Bnew[i] = Bpart1[std::distance(Apart1.begin(), it)];
    }



    }

  }

  A = Anew;

}



// min max
std::pair<int, int> TrojanMap::RandomIndex(std::vector<std::string> &location){


  while(true){
    int a = rand()%location.size();
    int b = rand()%location.size();

    if(a > b){
      std::pair<int, int> res(b,a);
      return res;
    }

    else if(a < b){
      std::pair<int, int> res(a,b);
      return res;
    }

  }
}

void TrojanMap::Mutation(std::vector<std::string> &path){

  std::pair<int, int> minMax = RandomIndex(path);
  int min = minMax.first;
  int max = minMax.second;

  std::reverse(path.begin() + min, path.begin() + max);

}

void TrojanMap::Evolution(std::vector<std::string> &path, std::vector<std::vector<std::string>> &generation, double &pc){

  // toss a coin
  int toss = rand()%100;

  if(toss/100 < pc){

    //crossover choose a mate
    CrossOver(path,generation[rand()%generation.size()]);

  }

  else{

    Mutation(path);

  }
}

