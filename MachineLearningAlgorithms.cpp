//Linear Regression (Using Gradient Descent)
#include <iostream>
#include <vector>
using namespace std;

double computeCost(const vector<double>& x, const vector<double>& y, double m, double b) {
    double cost = 0;
    int n = x.size();
    for (int i = 0; i < n; ++i) {
        double prediction = m * x[i] + b;
        cost += (prediction - y[i]) * (prediction - y[i]);
    }
    return cost / (2 * n);
}

void linearRegression(const vector<double>& x, const vector<double>& y, double alpha, int iterations) {
    double m = 0, b = 0;
    int n = x.size();

    for (int i = 0; i < iterations; ++i) {
        double m_grad = 0, b_grad = 0;

        for (int j = 0; j < n; ++j) {
            double prediction = m * x[j] + b;
            m_grad += (prediction - y[j]) * x[j];
            b_grad += (prediction - y[j]);
        }

        m -= alpha * m_grad / n;
        b -= alpha * b_grad / n;

        if (i % 100 == 0)
            cout << "Iteration " << i << ": Cost = " << computeCost(x, y, m, b) << endl;
    }

    cout << "Final Model: y = " << m << "x + " << b << endl;
}
//K-Nearest Neighbors (KNN)
#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;

struct DataPoint {
    vector<double> features;
    int label;
};

double euclideanDistance(const vector<double>& a, const vector<double>& b) {
    double sum = 0;
    for (size_t i = 0; i < a.size(); ++i)
        sum += (a[i] - b[i]) * (a[i] - b[i]);
    return sqrt(sum);
}

int classifyKNN(const vector<DataPoint>& data, const vector<double>& input, int k) {
    vector<pair<double, int>> distances;
    for (const auto& point : data) {
        double dist = euclideanDistance(point.features, input);
        distances.push_back({dist, point.label});
    }

    sort(distances.begin(), distances.end());

    vector<int> votes(10, 0); // assuming labels from 0-9
    for (int i = 0; i < k; ++i)
        votes[distances[i].second]++;

    return max_element(votes.begin(), votes.end()) - votes.begin();
}
//Decision Tree (Very Simplified – Binary Split on 1 Feature)
#include <iostream>
#include <vector>
using namespace std;

struct Node {
    bool isLeaf;
    int label;
    int feature;
    double threshold;
    Node* left;
    Node* right;
};
Node* buildSimpleTree(const vector<vector<double>>& X, const vector<int>& y, int feature, double threshold) {
    Node* node = new Node();

    vector<int> leftLabels, rightLabels;
    for (size_t i = 0; i < X.size(); ++i) {
        if (X[i][feature] <= threshold)
            leftLabels.push_back(y[i]);
        else
            rightLabels.push_back(y[i]);
    }

    if (leftLabels.size() == y.size() || rightLabels.size() == y.size()) {
        node->isLeaf = true;
        node->label = y[0]; // Just take one label as result
        return node;
    }

    node->isLeaf = false;
    node->feature = feature;
    node->threshold = threshold;

    vector<vector<double>> leftX, rightX;
    vector<int> leftY, rightY;

    for (size_t i = 0; i < X.size(); ++i) {
        if (X[i][feature] <= threshold) {
            leftX.push_back(X[i]);
            leftY.push_back(y[i]);
        } else {
            rightX.push_back(X[i]);
            rightY.push_back(y[i]);
        }
    }

    node->left = buildSimpleTree(leftX, leftY, feature, threshold);  // In real cases, use recursion with new thresholds
    node->right = buildSimpleTree(rightX, rightY, feature, threshold);

    return node;
}
int predict(Node* tree, const vector<double>& input) {
    if (tree->isLeaf) return tree->label;
    if (input[tree->feature] <= tree->threshold)
        return predict(tree->left, input);
    else
        return predict(tree->right, input);
}
//Naive Bayes Classifier (for binary features & binary classification)
#include <iostream>
#include <vector>
using namespace std;

class NaiveBayes {
    double p0, p1; // prior probabilities
    vector<double> featureProbGiven0;
    vector<double> featureProbGiven1;

public:
    void train(const vector<vector<int>>& X, const vector<int>& y) {
        int n = X.size();
        int numFeatures = X[0].size();
        int count0 = 0, count1 = 0;
        vector<int> countFeature1Given0(numFeatures, 0);
        vector<int> countFeature1Given1(numFeatures, 0);

        for (int i = 0; i < n; ++i) {
            if (y[i] == 0) {
                count0++;
                for (int j = 0; j < numFeatures; ++j)
                    countFeature1Given0[j] += X[i][j];
            } else {
                count1++;
                for (int j = 0; j < numFeatures; ++j)
                    countFeature1Given1[j] += X[i][j];
            }
        }

        p0 = double(count0) / n;
        p1 = double(count1) / n;

        featureProbGiven0.resize(numFeatures);
        featureProbGiven1.resize(numFeatures);

        for (int j = 0; j < numFeatures; ++j) {
            featureProbGiven0[j] = double(countFeature1Given0[j] + 1) / (count0 + 2); // Laplace smoothing
            featureProbGiven1[j] = double(countFeature1Given1[j] + 1) / (count1 + 2);
        }
    }

    int predict(const vector<int>& input) {
        double prob0 = log(p0), prob1 = log(p1);

        for (int i = 0; i < input.size(); ++i) {
            if (input[i]) {
                prob0 += log(featureProbGiven0[i]);
                prob1 += log(featureProbGiven1[i]);
            } else {
                prob0 += log(1 - featureProbGiven0[i]);
                prob1 += log(1 - featureProbGiven1[i]);
            }
        }

        return (prob1 > prob0) ? 1 : 0;
    }
};
//Perceptron Algorithm (Simple Neural Network)
#include <iostream>
#include <vector>
using namespace std;

class Perceptron {
    vector<double> weights;
    double bias;
    double learningRate;

public:
    Perceptron(int inputSize, double lr = 0.1) {
        weights.resize(inputSize, 0.0);
        bias = 0.0;
        learningRate = lr;
    }

    int predict(const vector<double>& x) {
        double sum = bias;
        for (int i = 0; i < x.size(); ++i)
            sum += weights[i] * x[i];
        return (sum >= 0) ? 1 : 0;
    }

    void train(const vector<vector<double>>& X, const vector<int>& y, int epochs) {
        for (int e = 0; e < epochs; ++e) {
            for (int i = 0; i < X.size(); ++i) {
                int pred = predict(X[i]);
                int error = y[i] - pred;

                for (int j = 0; j < weights.size(); ++j)
                    weights[j] += learningRate * error * X[i][j];
                
                bias += learningRate * error;
            }
        }
    }
};
