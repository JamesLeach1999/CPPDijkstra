#include <iostream>
#include<string>
#include<vector>
#include<ostream>
#include<iostream>
// for infinity
#include<limits>
#include<utility>
#include<functional>
#include<queue>
using namespace std;

// simple queue with min elements first
typedef pair<string, int> pd;
struct myComp {
    constexpr bool operator()(
        pair<string, int> const& a,
        pair<string, int> const& b)
        const noexcept
    {
        return a.second > b.second;
    }
};

// for dequeing elements
pair<string ,int> pairPop(priority_queue<pd, vector<pd>, myComp> &g){
    pair<string, int> popped = g.top();
    g.pop();
    return popped;
}


class Edge{
    public:
        int weight;
        string destination;
        Edge(int val, string dest){
            this->weight = val;
            this->destination = dest;
        }
};


class Node{
    public:
        string value;
        vector<Edge*> Neighbours;
        Node(string val){
            this->value = val;
        }
};

class Graph{
    public:
        static vector< Node*> adjacencyList;
        int total = 0;

        void addNode(Node *node){
            adjacencyList.push_back(node);
            return;
        }

        Node *getNode(string value){
            for (int i = 0; i < adjacencyList.size(); i++)
            {
                if(adjacencyList[i]->value == value){
                    return adjacencyList[i];
                }
            }
            return NULL;
        }

        void dijkstra(Node *start, Node *end){
            int inf = numeric_limits<int>::max();
            vector<pair<string, string>> previous;
            vector<pair<string, int>> distances;
            priority_queue<pd, vector<pd>, myComp> nodes;
            for (int i = 0; i < this->adjacencyList.size(); i++)
            {
                previous.push_back(pair(this->adjacencyList[i]->value, "nothing"));
                if(this->adjacencyList[i]->value == start->value){
                    distances.push_back(pair(this->adjacencyList[i]->value, 0));
                    nodes.push(make_pair(this->adjacencyList[i]->value, 0));

                } else {
                    distances.push_back(pair(this->adjacencyList[i]->value, inf));
                    
                    nodes.push(make_pair(this->adjacencyList[i]->value, inf));
                }
            }
            vector<string> results;
            
            while(nodes.size() > 0){
                pair<string, int > smallest= pairPop(nodes);
                Node *smallestNode = getNode(smallest.first);
                
                if(smallestNode == end){
                    int prevIter = 0;
                    
                    for (int i = 0; i < previous.size(); i++)
                    {
                        if(previous[i].first == end->value){
                            prevIter = i;
                        }
                    }
                    results.push_back(previous[prevIter].first);
                    while(previous[prevIter].second != "nothing"){
                        for (int i = 0; i < previous.size(); i++)
                        {
                            if(previous[prevIter].second == previous[i].first){
                                prevIter = i;
                            }
                        }
                        results.push_back(previous[prevIter].first);
                    }
                    break;
                }
                int index = 0;
                for (int i = 0; i < this->adjacencyList.size(); i++)
                {
                    if(smallestNode->value == distances[i].first){
                        index = i;
                        break;
                    }
                }
                
                if(distances[index].second != inf){
                    for (int i = 0; i < smallestNode->Neighbours.size(); i++)
                    {
                        Node *foundNode = this->getNode(smallestNode->Neighbours[i]->destination);
                        Edge *nextNode = smallestNode->Neighbours[i];
                        int candidate = distances[index].second + nextNode->weight;
                        string nextNeighbour = nextNode->destination;
                        int index2 = 0;
                        for (int j = 0; j < this->adjacencyList.size(); j++)
                        {
                            if(distances[j].first == nextNeighbour){
                                index2 = j;
                            }
                        }
                        if(candidate < distances[index2].second){
                            distances[index2].second = candidate;
                            previous[index2].second = smallestNode->value;
                            nodes.push({foundNode->value, candidate});
                        }
                        
                    }
                    
                }
            }
            for (int i = results.size()-1; i >=0; i--)
            {
                if(results[i] == start->value){
                    cout<<"Starting destination \t"<<results[i]<<endl;
                } else if(results[i] == end->value){
                    cout<<"End destination \t"<<results[i]<<endl;
                } else {
                    cout<<results[i]<<endl;
                }
            }
        }
};

vector<Node*> Graph::adjacencyList = {};


int main(){

    Graph graph;

    

    Node ldn("LDN");
    Node prs("PRS");
    Node hk("HK");
    Node la("LA");
    Node cai("CAI");
    Node mex("MEX");
    Node arg("ARG");
    Node aus("AUS");
    graph.addNode(&ldn);
    graph.addNode(&prs);
    graph.addNode(&hk);
    graph.addNode(&la);
    graph.addNode(&cai);
    graph.addNode(&mex);
    graph.addNode(&arg);
    graph.addNode(&aus);

    // ======================================================================================
    // ALL EDGES
    Edge lp(2, "PRS");
    Edge pl(2, "LDN");
    Edge laa(5, "LA");
    Edge lla(5, "LDN");
    Edge lh(6, "HK");
    Edge hl(6, "LDN");
    Edge pla(4, "LA");
    Edge lap(4, "PRS");
    Edge pc(3, "CAI");
    Edge cp(3, "PRS");
    Edge pa(6, "ARG");
    Edge ap(6, "PRS");
    Edge pau(8, "AUS");
    Edge aup(8, "PRS");
    Edge hau(4, "AUS");
    Edge auh(4, "HK");
    Edge hm(6, "MEX");
    Edge mh(6, "HK");
    Edge har(8, "ARG");
    Edge arh(8, "HK");
    Edge lam(2, "MEX");
    Edge mla(2, "LA");
    Edge lac(5, "CAI");
    Edge cla(5, "LA");
    Edge arm(3, "MEX");
    Edge mar(3, "ARG");
    Edge ala(4, "LA");
    Edge laar(4, "ARG");
    Edge cau(7, "AUS");
    Edge auc(7, "CAI");
    Edge ch(4, "HK");
    Edge hc(4, "CAI");
    Edge aar(9, "ARG");
    Edge aau(9, "AUS");
    // Edge pl(2, "LDN");
    // Edge lp(2, "LDN");
    Edge lc(3, "CAI");
    Edge cl(3, "LDN");
    
    ldn.Neighbours.push_back(&lp);
    ldn.Neighbours.push_back(&laa);
    ldn.Neighbours.push_back(&lh);
    ldn.Neighbours.push_back(&lc);

    prs.Neighbours.push_back(&pl);
    prs.Neighbours.push_back(&pla);
    prs.Neighbours.push_back(&pc);

    hk.Neighbours.push_back(&hl);
    hk.Neighbours.push_back(&hau);
    hk.Neighbours.push_back(&hm);
    hk.Neighbours.push_back(&har);
    hk.Neighbours.push_back(&hc);

    la.Neighbours.push_back(&lla);
    la.Neighbours.push_back(&lap);
    la.Neighbours.push_back(&lam);
    la.Neighbours.push_back(&laar);
    la.Neighbours.push_back(&lac);

    cai.Neighbours.push_back(&cp);
    cai.Neighbours.push_back(&cla);
    cai.Neighbours.push_back(&ch);
    cai.Neighbours.push_back(&cl);

    mex.Neighbours.push_back(&mh);
    mex.Neighbours.push_back(&mla);
    mex.Neighbours.push_back(&mar);

    arg.Neighbours.push_back(&arh);
    arg.Neighbours.push_back(&arm);
    arg.Neighbours.push_back(&aau);

    aus.Neighbours.push_back(&aup);
    aus.Neighbours.push_back(&auc);
    aus.Neighbours.push_back(&aar);

    // ===========================================================================

    graph.dijkstra(&ldn, &prs);

    
    return 0;

}
