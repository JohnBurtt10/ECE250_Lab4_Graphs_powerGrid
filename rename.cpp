#include "Graph.hpp"
#include <fstream> 
using namespace std;
// class illegal_exception : public std::exception {
// public:
//     illegal_exception(const std::string& message) : message_(message) {}

//     const char* what() const noexcept override {
//         return message_.c_str();
//     }

// private:
//     std::string message_;
// };

// bool illegalArgument(string word) { 
//     unsigned int i = 0;
//         bool flag = false;
//         while (word[i] != '\0') { 
//             if ((word[i] - 'A' + 1) < 1 || (word[i] - 'A' + 1) > 27) {
//                 try {
//                     throw illegal_exception("illegal argument");
//                 } catch (illegal_exception mce) {
//                     std::cout << mce.what() << std::endl;
//                     return true;
//                     break;
//                 }

//             }
//             i++;
//     }
//     return false;
// }

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
            G.m = m;
            // std::cout << "size: " << size << std::endl;
            while (fin) {
                fin >> a; 
                // std::cout << "a: " << a << std::endl;
                fin >> b; 
                // std::cout << "b: " << b << std::endl;
                fin >> w; 
                // std::cout << "w: " << w << std::endl;
                G.insert(a,b,w);
            }
            std::cout << "success" << std::endl;
        } else if (cmd == "INSERT") { 
            int a; 
            int b; 
            int w; 
            cin >> a; 
            cin >> b; 
            cin >> w; 
            // if (illegalArgument(word)) { 
            //     continue;
            // }
            G.insert(a,b,w); 
            std::cout << "success" << std::endl;
        } else if (cmd == "PRINT") { 
            int a; 
            cin >> a; 
            G.print(a);
        } else if (cmd == "MST") { 
            G.MST();
        }
    }
    return 0;
}
