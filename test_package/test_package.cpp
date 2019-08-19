#include <iostream>
#include <ppconsul/status.h>

using namespace ppconsul;
using namespace ppconsul::status;

int main() {

    // Create a consul client that uses default local endpoint `http://127.0.0.1:8500` and default data center
    try {
        Consul consul;

        // We need the status endpoint
        Status status(consul);

        // Determine whether a leader has been elected
        bool isLeaderElected = status.isLeaderElected();
        std::cout << "Consul has leader: " << isLeaderElected << std::endl;

        // Determine the actual raft leader
        auto leader = status.leader();
        std::cout << "Consul leader name: " << leader.get_value_or("none") << std::endl;

        // Determine the raft peers
        auto peers = status.peers();
        std::cout << "Consul peers count: " << peers.size() << std::endl;
    } catch(std::runtime_error err){
        std::cout << "Test exception: " << err.what() << std::endl;
    }

    return 0;
}