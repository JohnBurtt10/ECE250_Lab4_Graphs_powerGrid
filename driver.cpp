#include "Graph.hpp"
#include <fstream> 
#include <iostream>
#include <tuple>
using namespace std;
typedef std::tuple<Vertex, Vertex, unsigned int> edge; 
class illegal_exception : public std::exception {
public:
    illegal_exception(const std::string& message) : message_(message) {}

    const char* what() const noexcept override {
        return message_.c_str();
    }

private:
    std::string message_;
};

bool illegalVertexArgument(int x) { 
    if (x <= 0 || x > 50000) {
        try {
            throw illegal_exception("illegal argument");
        } catch (illegal_exception mce) {
            std::cout << mce.what() << std::endl;
            return true;
        }

    }
    return false;
}

bool illegalWeightArgument(int x) { 
    if (x <= 0) {
        try {
            throw illegal_exception("illegal argument");
        } catch (illegal_exception mce) {
            std::cout << mce.what() << std::endl;
            return true;
        }

    }
    return false;
}

int main() {
    string cmd; 
    Graph G;
    while (cin >> cmd) {
        if(cmd == "LOAD"){
            string fName;
            int input;
            int a; 
            int b; 
            int w;
            unsigned int m;
            cin >> fName;
            ifstream fin(fName.c_str()); //Note that we are using the variable as the filename
            //Now do your parsing here. Remember to #include <fstream> at the top!
            fin >> m; 
            G.m += m;
            while (fin >> a && fin >> b && fin >> w) {
                G.insert(a,b,w);
            }
            std::cout << "success" << std::endl;
        } else if (cmd == "INSERT") { 
            G.m++;
            int a; 
            int b; 
            int w; 
            cin >> a; 
            cin >> b; 
            cin >> w; 
            if (illegalVertexArgument(a) || illegalVertexArgument(b) || illegalWeightArgument(w)) { 
                continue;
            }
            bool edgeExists;
            edgeExists = G.insert(a,b,w); 
            // the 
            if (edgeExists) { 
                std::cout << "failure" << std::endl;
            } else { 
                std::cout << "success" << std::endl;
            }
        } else if (cmd == "PRINT") { 
            int a; 
            cin >> a; 
            if (illegalVertexArgument(a)) { 
                continue;
            }
            G.print(a);
        } else if (cmd == "DELETE") { 
            int a; 
            cin >> a; 
            if (illegalVertexArgument(a)) { 
                continue;
            }
            G.graphDelete(a);
        } else if (cmd == "MST") { 
            if (G.V.size() <=1) { 
                std::cout << "failure" << std::endl;
                continue;
            }
            vector <edge> MST; 
            MST = G.MST();
            for (auto& e : MST) {
                std::cout << std::get<0>(e).value << " " << std::get<1>(e).value << " " << std::get<2>(e) << " ";
            }
            if (MST.size() == 0) {
                std::cout << "failure" << std::endl;
            } else { 
                std::cout << std::endl;
            }
        } else if (cmd == "COST") { 
             if (G.V.size() <=1) { 
                std::cout << "cost is 0" << std::endl;
                continue;
            }
            unsigned int cost = 0; 
            vector <edge> MST; 
            MST = G.MST(); 
            for (auto& e : MST) {
                cost += std::get<2>(e); 
            }
            std::cout << "cost is " << cost << std::endl;
        }
    }
    return 0;
}
