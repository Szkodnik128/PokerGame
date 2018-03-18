#include "server/Server.h"
#include "controller/Controller.h"
#include "model/Model.h"
#include "utils/BlockingQueue.h"
#include "event/Event.h"

#include <thread>

#define SERVER_ADDRESS "localhost"
#define SERVER_SERVICE "9988"
#define SERVER_MAX_CONNECTIONS 256

static void run_controller(Controller *controller)
{
    controller->run();
}

static void run_server(Server *server)
{
    server->run();
}

int main() {
    Server *server;
    Controller *controller;
    Model *model;
    BlockingQueue<Event *> *blockingQueue;

    /* Create objects */
    model = new Model();
    blockingQueue = new BlockingQueue<Event *>();
    controller = new Controller();
    server = new Server(blockingQueue, SERVER_ADDRESS, SERVER_SERVICE, SERVER_MAX_CONNECTIONS);

    /* Run controller as thread */
    std::cout << "Starting controller thread..." << std::endl;
    std::thread controller_thread(run_controller, controller);
    controller_thread.detach();
    std::cout << "Controller thread started" << std::endl;

    /* Run server */
    std::cout << "Starting server thread..." << std::endl;
    std::thread server_thread(run_server, server);
    server_thread.detach();
    std::cout << "Server thread started" << std::endl;

    while (true) {

    }

    return 0;
}