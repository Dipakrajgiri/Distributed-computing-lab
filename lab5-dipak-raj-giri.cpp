#include <iostream>
#include <functional>
#include <unordered_map>
#include <string>

class RPCServer {
public:
    // Register RPC functions
    void registerProcedure(const std::string& name, std::function<int(int, int)> func) {
        rpcFunctions[name] = func;
    }

    // Execute the RPC function based on the name
    int executeProcedure(const std::string& name, int a, int b) {
        if (rpcFunctions.find(name) != rpcFunctions.end()) {
            return rpcFunctions[name](a, b);
        } else {
            std::cerr << "Error: RPC method not found!" << std::endl;
            return -1; // Indicating error
        }
    }

private:
    std::unordered_map<std::string, std::function<int(int, int)>> rpcFunctions;
};

// Sample function to be used in RPC
int addNumbers(int a, int b) {
    return a + b;
}

int main() {
    // Create an instance of the RPC server
    RPCServer server;

    // Registering RPC method (simulating remote call)
    server.registerProcedure("add", addNumbers);

    // Simulating a client calling the add function remotely
    int a = 5, b = 3;
    std::cout << "Calling remote procedure 'add' with parameters " << a << " and " << b << "..." << std::endl;

    // Execute the "remote procedure"
    int result = server.executeProcedure("add", a, b);

    // Display the result
    if (result != -1) {
        std::cout << "Result from remote procedure: " << result << std::endl;
    }

    return 0;
}
