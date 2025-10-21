#include <cstdlib>
#include <iostream>
#include <limits>
#include <ostream>
#include <random>
#include <sys/types.h>
#include <utility>
#include <vector>

const double INF = std::numeric_limits<double>::infinity();
class Graph {
    protected:
        int n;
        std::vector<int> V;
        std::vector<std::vector<bool>> adj_matr;
        std::vector<std::vector<std::pair<int, double>>> adj_list;

    public:
        virtual int AddVertex() = 0;
        virtual void AddEdge(int i, int j) = 0;
        virtual void DeleteVertex(int num) = 0;
        virtual void DeleteEdge(int i, int j) = 0;
        virtual void BuildLists() = 0;
        virtual void Print() = 0;
};
class NorGraph : public Graph {
    protected:
        int n;
        std::vector<int> V;
        std::vector<std::vector<bool>> adj_matr;
        std::vector<std::vector<std::pair<int, double>>> adj_list;

    public:
        NorGraph(int number)
            : n(number),
              V(number),
              adj_matr(number, std::vector<bool>(number)) {
            for (int i = 0; i < n; i++) {
                V[i] = i + 1;
                for (int j = 0; j < n; j++)
                    adj_matr[i][j] = 0;
            }
        }
        NorGraph()
            : n(0),
              V(0),
              adj_matr(0) {}

        NorGraph(int number, double p)
            : n(number),
              V(number),
              adj_matr(number, std::vector<bool>(number)) {

            std::uniform_real_distribution<double> unif(0, 1);
            std::default_random_engine re;
            for (int i = 0; i < n; i++) {
                V[i] = i + 1;
                for (int j = i + 1; j < n; j++) {
                    if (unif(re) < p) {
                        AddEdge(i + 1, j + 1);
                    }
                }
            }
        }
        int AddVertex() override {
            n++;
            V.push_back(n);
            for (int i = 0; i < n - 1; i++)
                adj_matr[i].push_back(0);
            adj_matr.push_back(std::vector<bool>(n, 0));

            return n;
        }

        void AddEdge(int i, int j) override {
            i--;
            j--;
            adj_matr[i][j] = 1;
            adj_matr[j][i] = 1;
        }

        void DeleteVertex(int num) override {
            adj_matr.erase(adj_matr.begin() + num - 1);
            n--;
            for (int i = 0; i < n; i++) {
                adj_matr[i].erase(adj_matr[i].begin() + num - 1);
            }
        }
        void DeleteEdge(int i, int j) override {
            i--;
            j--;
            adj_matr[i][j] = 0;
            adj_matr[j][i] = 0;
        }

        void Print() override {
            std::cout << "===============\n";
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    std::cout << adj_matr[i][j] << " ";
                }
                std::cout << std::endl;
            }
            std::cout << "===============\n";
        }
        void BuildLists() override {
            std::pair<int, double> a;
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    if (adj_matr[i][j] == 1) {
                        a.first = j;
                        a.second = 1;
                        adj_list[i].push_back(a);
                    }
                }
            }
        }
};
class OrGraph : public Graph {
    private:
        int n;
        std::vector<int> V;
        std::vector<std::vector<bool>> adj_matr;
        std::vector<std::vector<std::pair<int, double>>> adj_list;

    public:
        OrGraph(int number)
            : n(number),
              V(number),
              adj_matr(number, std::vector<bool>(number)) {
            for (int i = 0; i < n; i++) {
                V[i] = i + 1;
                for (int j = 0; j < n; j++)
                    adj_matr[i][j] = 0;
            }
        }
        OrGraph()
            : n(0),
              V(0),
              adj_matr(0) {}
        OrGraph(int number, double p)
            : n(number),
              V(number),
              adj_matr(number, std::vector<bool>(number)) {

            std::uniform_real_distribution<double> unif(0, 1);
            std::default_random_engine re;
            for (int i = 0; i < n; i++) {
                V[i] = i + 1;
                for (int j = i + 1; j < n; j++) {
                    if (unif(re) < p) {
                        AddEdge(i + 1, j + 1);
                    }
                }
            }
        }

        int AddVertex() override {
            n++;
            V.push_back(n);
            for (int i = 0; i < n - 1; i++)
                adj_matr[i].push_back(0);
            adj_matr.push_back(std::vector<bool>(n, 0));

            return n;
        }

        void AddEdge(int i, int j) override {
            i--;
            j--;
            adj_matr[i][j] = 1;
        }

        void DeleteVertex(int num) override {
            adj_matr.erase(adj_matr.begin() + num - 1);
            n--;
            for (int i = 0; i < n; i++) {
                adj_matr[i].erase(adj_matr[i].begin() + num - 1);
            }
        }
        void DeleteEdge(int i, int j) override {
            i--;
            j--;
            adj_matr[i][j] = 0;
        }
        void Print() override {
            std::cout << "===============\n";
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    std::cout << adj_matr[i][j] << " ";
                }
                std::cout << std::endl;
            }
            std::cout << "===============\n";
        }
        void BuildLists() override {
            std::pair<int, double> a;
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    if (adj_matr[i][j] == 1) {
                        a.first = j;
                        a.second = 1;
                        adj_list[i].push_back(a);
                    }
                }
            }
        }
};

class WOrGraph : public OrGraph {
    private:
        int n;
        std::vector<int> V;
        std::vector<std::vector<double>> adj_matr;
        std::vector<std::vector<std::pair<int, double>>> adj_list;

    public:
        WOrGraph(int number)
            : n(number),
              V(number),
              adj_matr(number, std::vector<double>(number)) {
            for (int i = 0; i < n; i++) {
                V[i] = i + 1;
                for (int j = 0; j < n; j++)
                    adj_matr[i][j] = INF;
                adj_matr[i][i] = 0;
            }
        }
        WOrGraph()
            : n(0),
              V(0),
              adj_matr(0) {}

        WOrGraph(int number, double p, int begin, int fin)
            : n(number),
              V(number),
              adj_matr(number, std::vector<double>(number)) {

            std::uniform_real_distribution<double> unif(0, 1);
            std::uniform_real_distribution<double> random(begin, fin);
            std::default_random_engine re;
            for (int i = 0; i < n; i++) {
                V[i] = i + 1;
                for (int j = i + 1; j < n; j++) {
                    if (unif(re) < p) {
                        AddEdge(i + 1, j + 1, random(re));
                    } else {
                        adj_matr[i][j] = INF;
                    }
                }
            }
        }

        int AddVertex() override {
            n++;
            V.push_back(n);
            for (int i = 0; i < n - 1; i++)
                adj_matr[i].push_back(INF);
            adj_matr.push_back(std::vector<double>(n, INF));
            adj_matr[n - 1][n - 1] = 0;
            return n;
        }

        void AddEdge(int i, int j, double w) {
            i--;
            j--;
            adj_matr[i][j] = w;
        }

        void DeleteVertex(int num) override {
            adj_matr.erase(adj_matr.begin() + num - 1);
            n--;
            for (int i = 0; i < n; i++) {
                adj_matr[i].erase(adj_matr[i].begin() + num - 1);
            }
        }
        void DeleteEdge(int i, int j) override {
            i--;
            j--;
            adj_matr[i][j] = INF; // if i != j
        }
        void Print() override {
            std::cout << "===============\n";
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    std::cout << adj_matr[i][j] << " ";
                }
                std::cout << std::endl;
            }
            std::cout << "===============\n";
        }
        void BuildLists() override {
            std::pair<int, double> a;
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    if (adj_matr[i][j] != INF && j != i) {
                        a.first = j;
                        a.second = adj_matr[i][j];
                        adj_list[i].push_back(a);
                    }
                }
            }
        }
};

class WNorGraph : public NorGraph {
    private:
        int n;
        std::vector<int> V;
        std::vector<std::vector<double>> adj_matr;
        std::vector<std::vector<std::pair<int, double>>> adj_list;

    public:
        WNorGraph(int number)
            : n(number),
              V(number),
              adj_matr(number, std::vector<double>(number)) {
            for (int i = 0; i < n; i++) {
                V[i] = i + 1;
                for (int j = 0; j < n; j++)
                    adj_matr[i][j] = INF;
                adj_matr[i][i] = 0;
            }
        }
        WNorGraph()
            : n(0),
              V(0),
              adj_matr(0) {}

        WNorGraph(int number, double p, int begin, int fin)
            : n(number),
              V(number),
              adj_matr(number, std::vector<double>(number)) {

            std::uniform_real_distribution<double> unif(0, 1);
            std::uniform_real_distribution<double> random(begin, fin);
            std::default_random_engine re;
            for (int i = 0; i < n; i++) {
                V[i] = i + 1;
                for (int j = i + 1; j < n; j++) {
                    if (unif(re) < p) {
                        AddEdge(i + 1, j + 1, random(re));
                    } else {
                        adj_matr[i][j] = INF;
                        adj_matr[j][i] = INF;
                    }
                }
            }
        }
        int AddVertex() override {
            n++;
            V.push_back(n);
            for (int i = 0; i < n - 1; i++)
                adj_matr[i].push_back(0);
            adj_matr.push_back(std::vector<double>(n, 0));

            return n;
        }

        void AddEdge(int i, int j, double w) {
            i--;
            j--;
            adj_matr[i][j] = w;
            adj_matr[j][i] = w;
        }

        void DeleteVertex(int num) override {
            adj_matr.erase(adj_matr.begin() + num - 1);
            n--;
            for (int i = 0; i < n; i++) {
                adj_matr[i].erase(adj_matr[i].begin() + num - 1);
            }
        }
        void DeleteEdge(int i, int j) override {
            i--;
            j--;
            adj_matr[i][j] = INF;
            adj_matr[j][i] = INF;
        }
        void Print() override {
            std::cout << "===============\n";
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {

                    std::cout << adj_matr[i][j] << " ";
                }
                std::cout << std::endl;
            }
            std::cout << "===============\n";
        }
        void BuildLists() override {
            std::pair<int, double> a;
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    if (adj_matr[i][j] != INF && j != i) {
                        a.first = j;
                        a.second = adj_matr[i][j];
                        adj_list[i].push_back(a);
                    }
                }
            }
        }
};

int main() {
    NorGraph G(10);
    G.Print();
    G.AddVertex();
    G.AddEdge(1, 2);
    G.AddEdge(2, 3);
    G.Print();
    G.DeleteVertex(1);
    G.Print();
    G.DeleteEdge(1, 2);
    G.Print();

    NorGraph G2(10, 0.5);
    G2.Print();

    WNorGraph G3(10, 0.5, -100, 100);
    G3.Print();
    // G2.Print();
}
