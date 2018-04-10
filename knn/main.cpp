/*************************
 *Jamal Nasser
 *Fall 2017
 *Program demonstrating multiple optimization algorithms concerning
 *maximizing the amount of 'tastiness' in a 'candy bag'
 *Each line from input text describes a the 'weight' and 'taste' of a candy
 // Demonstrates: Greedy Heuristic, Iterative Refinement, Recursive search
 *************************/

#include <iostream>
#include <cstdlib>
#include <cmath>
#include <fstream>
#include <algorithm>
#include <queue>
using namespace std;

struct Node {
  int index;
  Node *left;
  Node *right;
  Node (int i) {index = i; left = right = NULL;}
};

struct Point {
  double quality;
  double *data;
};

int N, D, K; // N = number of wine entries, D = number of attributes, K = neighbors
Point *P;
typedef pair<double, int> pQ_Data;
priority_queue<pQ_Data> priorityQ;

double dist(int p, int q)
{
    double d_total = 0.0;
    for(int i = 0; i < D; i++)
        d_total += (P[p].data[i] - P[q].data[i]) * (P[p].data[i] - P[q].data[i]);
    return sqrt(d_total);
}

double oneD_Dist(int p, int q, int dim)
{
    double dist = abs(P[p].data[dim] - P[q].data[dim]);
    return dist;
}

Node *insert(Node *kd, int index, int dim)
{
  if (kd == NULL) return new Node(index);
  if (P[index].data[dim] < P[kd->index].data[dim])
    kd->left = insert(kd->left, index, (dim+1)%D);
  else
    kd->right = insert(kd->right, index, (dim+1)%D);
  return kd;
}

void nearest_neighbor(Node* kd, int i, int dim)
{
  if (kd == NULL) return;
  // Should kd->index replace worst neighbor in PQ?
  if (kd->index != i && dist(kd->index, i) < priorityQ.top().first){
      priorityQ.pop();
      priorityQ.push(pQ_Data(dist(i, kd->index), kd->index));
  }
  // Prune the search if the distance between the target node
  // and dividing line in current dimension is greater than
  // the current worst, best distance found
  if (P[i].data[dim] < P[kd->index].data[dim]){
      nearest_neighbor(kd->left, i, (dim+1)%D);
      //Prune the search
      if(oneD_Dist(i, kd->index, dim) < priorityQ.top().first)
          nearest_neighbor(kd->right, i, (dim+1)%D);
  }
  else{
      nearest_neighbor(kd->right, i, (dim+1)%D);
      //Prune the search
      if(oneD_Dist(i, kd->index, dim) < priorityQ.top().first)
          nearest_neighbor(kd->left, i, (dim+1)%D);
  }
}

// Guess that the label of a data point should be a weighted
// average of the labels of its k nearest neighbors
double classifyWine(){
  double sumWL = 0.0;
  double sumW = 0.0;

  int i = 0;
  while(!priorityQ.empty()){
    if(i < K){
      double d = priorityQ.top().first;
      double weight = pow(M_E, -0.1*d);
      int L = P[priorityQ.top().second].quality;
      sumWL += weight * L;
      sumW += weight;
    }
    i++;
    priorityQ.pop();
  }

  double weightedAverage = sumWL/sumW;
  return weightedAverage;

}

int main(int argc, char *argv[])
{
  if (argc != 3) {
    cout << "Usage: wine <data file> <k>\n";
    return 0;
  }

  /* Read input data */
  ifstream fin(argv[1]);
  K = atoi(argv[2]);
  fin >> N >> D;
  P = new Point[N];
  for (int i=0; i<N; i++) {
    fin >> P[i].quality;
    P[i].data = new double[D];
    for (int j=0; j<D; j++)
      fin >> P[i].data[j];
  }
  fin.close();

  /* Normalize data in each coordinate */
  for (int j=0; j<D; j++) {
    double mean = 0.0;
    for (int i=0; i<N; i++) mean += P[i].data[j];
    mean /= N;
    for (int i=0; i<N; i++) P[i].data[j] -= mean;
    double var = 0.0;
    for (int i=0; i<N; i++) var += pow(P[i].data[j],2);
    double stddev = sqrt(var/N);
    for (int i=0; i<N; i++) P[i].data[j] /= stddev;
  }

  // Now in each coordinate, we have a mean of zero and variance/standard deviation
  // of one, so the data set is "centered" at the origin and has the same relative
  // scale along each axis (so no attribute is "more important" than any other
  // attribute when computing distances).

  /* Create an array with 0...N-1 and then randomize them */
  int indices[N];
  for(int i = 0; i < N; i++)
    indices[i] = i;

  random_shuffle(&indices[0], &indices[N-1]);

  /* Create a kd-Tree by randomly inserting nodes with indexes */
  Node *kdTree = NULL;
  for(int i = 0; i < N; i++)
    kdTree = insert(kdTree, indices[i], 0);

  /* k-nearest neighbor search on each node */
  double wineClassifications[N];
  double squaredError = 0.0;
  for(int i = 0; i < N; i++){
    for(int j = 0; j < K; j++)
      priorityQ.push(pQ_Data(9999.99, -1));
    nearest_neighbor(kdTree, i, 0);
    wineClassifications[i] = classifyWine();
    squaredError += pow(P[i].quality - wineClassifications[i], 2.0);
  }

  cout << (1.0/N)*squaredError << endl;


  return 0;
}
