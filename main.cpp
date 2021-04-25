#include <iostream>
#include <string>
#include <filesystem>
namespace fs = std::filesystem;
using namespace std;

fs::path dir = fs::current_path();


int main() {
    std::cout << "Hello, World!" << std::endl;
    return 0;
}
