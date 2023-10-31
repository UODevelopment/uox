#include <atomic>
#include <chrono>
#include <cstdint>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <filesystem>
#include <map>
#include <vector>

#include "account/account.hpp"
#include "network/client.hpp"
#include "gameobject/factory/itemfactory.hpp"
#include "gameobject/factory/playerfactory.hpp"
#include "packet/processpacket.hpp"
#include "network/server.hpp"
#include "configuration/serverconfig.hpp"
#include "utility/strutil.hpp"
#include "type/typedef.hpp"


using namespace std::string_literals;

//=====================================================================================
// This works on on the concept that the server is driven by "events"
// The following are the evengts:
//      network events (packets)
//      time events (timevents)
//      command events (keyboard)
//      maintenance events
// So first the system reads all configuration data
// Reads in uodata, and server data (objects/players), accounts.
// Opens the network
// And then loops on those events.

// Network events
//   Network is based on the concept of a Client, that is associated with a Player object after login.
//   The Client reads/writes asynchonise, but one a packet is received, another read is not started, until that packet
//   is grabbed for processing.
//   The ability to create/process packets are handled via dispatch tables, in createpacket/processpacket.
//===================================================================================================================

using STEADYCLOCK = std::chrono::steady_clock ;
constexpr auto MAINTENANCEDURATION = minute_t(2) ;

// Our main entities
ServerConfig serverConfig;
Account userAccounts ;
Server myserver;
std::atomic<systemstate_t> systemState(systemstate_t::RUN) ;
timepoint_t maintenanceTime ;
PlayerFactory playerFactory ;
ItemFactory itemFactory ;

int main(int argc, const char * argv[]) {
    auto errorcode = EXIT_SUCCESS;
    try {
        // Startup the network
        util::net::startup();
        // Get the configuration file
        auto configpath = std::filesystem::path("uox.cfg");
        if (argc > 1){
            configpath = std::filesystem::path(argv[1]);
        }
        // Configuration setup
        serverConfig.load(configpath);
        
        userAccounts.load(serverConfig.pathValue[PathCollection::ACCOUNT]/Account::ACCOUNTFILE) ;
        playerFactory.loadPlayer(serverConfig.pathValue[PathCollection::WORLD]/PlayerFactory::PLAYERFILE);
        
        userAccounts.autoCreate = serverConfig.boolValue[BoolCollection::CREATEACCOUNT] ;
        
        
        Client::serverKey = static_cast<std::uint32_t>(serverConfig.intValue[IntCollection::SERVERKEY]  );
        
        // Set the server information
        myserver.setLogInfo(serverConfig.pathValue[PathCollection::LOG], serverConfig.boolValue[BoolCollection::CLIENTLOG]);
        myserver.setAccess(serverConfig.pathValue[PathCollection::CONFIGURATION]/std::filesystem::path("allow.cfg"), serverConfig.pathValue[PathCollection::CONFIGURATION]/std::filesystem::path("deny.cfg"));
        myserver.setPublicIP(serverConfig.stringValue[StringCollection::PUBLICIP]);
        
        // Start listening and activate the loop
        myserver.listen(serverConfig.intValue[IntCollection::PORT]);
        auto minlooptime = milli_t(2) ; // Set a minimum loop time so we dont peg the machine
        maintenanceTime =  STEADYCLOCK::now();
        myserver.start();
        while (systemState == systemstate_t::RUN) {
            auto now = std::chrono::high_resolution_clock::now();
            auto packets = myserver.grabData();
            if (!packets.empty()){
                // Dispatch the packets
                for (auto &[client,data]:packets){
                    processPacket(client.get(), std::move(data)) ;
                }
            }
            // Check for any time events

            // Check for any keyboard events

            // Check for any maintenance events
            if (std::chrono::duration_cast<std::chrono::minutes>(STEADYCLOCK::now() - maintenanceTime).count() >= MAINTENANCEDURATION  ){
                // We should save
                userAccounts.save(serverConfig.pathValue[PathCollection::ACCOUNT]/ Account::ACCOUNTFILE) ;
                playerFactory.save(serverConfig.pathValue[PathCollection::WORLD]/ PlayerFactory::PLAYERFILE);
                maintenanceTime = STEADYCLOCK::now();
            }

            // Something else?
            auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - now).count() ;
            if (elapsed < minlooptime){
                // Sleep for a bit
                std::this_thread::sleep_for(static_cast<std::chrono::milliseconds>(minlooptime - elapsed));
            }
            
        }
        
    }
    catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        errorcode = EXIT_FAILURE;
    }
    util::net::shutdown();
     return errorcode;
}
