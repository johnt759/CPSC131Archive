//
//  main.cpp
//  Project4
//
//  Created by Bein, Doina on 4/21/18.
//  Copyright © 2018 Bein, Doina. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <list>
#include <string>
#include <stdexcept>

#include "graph.h"

using namespace std;

//////////////////////////////////////////////////////////////////////////////
// DO NOT EDIT THIS FILE (except for your own testing)
// CODE WILL BE GRADED USING A MAIN FUNCTION SIMILAR TO THIS
//////////////////////////////////////////////////////////////////////////////

template <typename T>
bool testAnswer(const string &nameOfTest, const T& received, const T& expected) {
  if (received == expected) {
    cout << "PASSED " << nameOfTest << ": expected and received " << received << endl;
    return true;
  }
  cout << "FAILED " << nameOfTest << ": expected " << expected << " but received " << received << endl;
  return false;
}

template <typename T>
bool testArrays(const string& nameOfTest, const T& received, const T& expected, const int& size) {
  for(int i = 0; i < size; i++) {
    if(received[i] != expected[i]) {
      cout << "FAILED " << nameOfTest << ": expected " << expected << " but received " << received << endl;
      return false;
    }
  }
    
  cout << "PASSED " << nameOfTest << ": expected and received matching arrays" << endl;
  return true;
}


int main() {

  Graph testGraph01(3, 100.0);
  testAnswer("testGraph01.getNSize()", testGraph01.getNSize(), 3);
  testAnswer("testGraph01.getESize()", testGraph01.getESize(), 0);
  testAnswer("testGraph01.getBudget()", testGraph01.getBudget(), (float)100.0);

  // add edges to testGraph01 and test 
  testGraph01.addEdge(0,1);
  testGraph01.addEdge(0,2);
  testAnswer("testGraph01.getESize()", testGraph01.getESize(), 2);
  
  // add values to testGraph01 and test
  testGraph01.setValue(0, -50.0);
  testGraph01.setValue(1, -60.0);
  testGraph01.setValue(2, -70.0);
  testAnswer("testGraph01.getValue(0)", testGraph01.getValue(0), (float) -50.0);
  testAnswer("testGraph01.getValue(2)", testGraph01.getValue(2), (float) -70.0);  
   
  // test the result of DFS traversal
  testAnswer("testGraph01.DFS(0)", testGraph01.DFS(0), 2);
  
  // test the bestStartVertex function
  testAnswer("testGraph.bestStartVertex()", testGraph01.bestStartVertex(), 0);
  
  //read from the file a small graph and test
  Graph testGraph02;
  testGraph02.readData("smallgraph.txt");
  
  testAnswer("testGraph02.getNSize()", testGraph02.getNSize(), 6);
  testAnswer("testGraph02.getESize()", testGraph02.getESize(), 5);
  testAnswer("testGraph02.getBudget()", testGraph02.getBudget(), (float) 100.0);
  testAnswer("testGraph02.getValue(0)", testGraph02.getValue(0), (float) -10.0);
  testAnswer("testGraph02.getValue(2)", testGraph02.getValue(2), (float) -50.0);

  // test the result of DFS traversal  
  testAnswer("testGraph02.DFS()", testGraph02.DFS(0), 4);
  //test the bestStartVertex function             
  testAnswer("testGraph.bestStartVertex()", testGraph02.bestStartVertex(), 4);

  //read from the file a large graph and test 
  Graph testGraph03;
  testGraph03.readData("biggraph.txt");

  testAnswer("testGraph03.getNSize()", testGraph03.getNSize(), 50);
  testAnswer("testGraph03.getESize()", testGraph03.getESize(), 59);
  testAnswer("testGraph03.getBudget()", testGraph03.getBudget(), (float) 100.0);
  testAnswer("testGraph03.getValue(0)", testGraph03.getValue(0), (float) -15.0);
  testAnswer("testGraph03.getValue(2)", testGraph03.getValue(2), (float) 10.0);

  // test the result of DFS traversal
  testAnswer("testGraph03.DFS(0)", testGraph03.DFS(0), 8);

  // test the bestStartVertex function
  testAnswer("testGraph03.bestStartVertex()", testGraph03.bestStartVertex(), 37);

  system("pause");
  return 0;
}
