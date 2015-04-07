#include <sstream>
#include <iostream>
#include <malamute.h>

int main(int argc, char* argv[])
{
    try
    {
        //zsys_handler_set(NULL);

        // start a new Malamute broker
        zactor_t *broker = zactor_new(mlm_server, NULL);

        // start the message broker on the default port, timeout 
        zsock_send(broker, "ss", "BIND", "tcp://*:5677");
        zsock_send(broker, "sss", "SET", "server/timeout", "5000");
        //zsock_send(broker, "s", "VERBOSE");

        // Create the reader to process the heartbeats
        mlm_client_t* reader = mlm_client_new("tcp://127.0.0.1:5677", 5000, "monitor");
        //mlm_client_t* reader = mlm_client_new();
        //int rc = mlm_client_connect(reader, "tcp://127.0.0.1:5677", 5000, "monitor");
        if (!reader)
        {
            std::cerr << "Failed to create hearbeat reader." << std::endl;
        }
        else
        {
            // The reader consumes hearbeat messages off the "memdb" stream
            mlm_client_set_consumer(reader, "memdb", "heartbeat*");

            while (true)
            {
                // Receive a message is via the recvx method which stores multipart string data
                char *subject, *content;
                zmsg_t* msg = mlm_client_recv(reader);
                if (!msg) {
                    std::cout << "INTERRUPTED!" << std::endl;
                    break;
                }
                zstr_free(&subject);
                zstr_free(&content);
            }

            // shutdown the reader client using the destroy method
            mlm_client_destroy(&reader);
        }

        // shut down the broker by destroying the actor
        zactor_destroy(&broker);

        zsys_info("MemDB Router Service: interrupted...");
    }
    catch (std::exception& e)
    {
        std::cerr << "ERROR: " << e.what() << std::endl << std::endl;
        return -3;
    }

	return 0;
}
