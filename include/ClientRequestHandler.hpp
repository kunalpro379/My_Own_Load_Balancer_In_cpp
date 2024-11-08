

#ifndef CLIENT_REQUEST_HANDLER_H
#define CLIENT_REQUEST_HANDLER_H

#include "RateLimiter.hpp"

class ClientRequestHandler{
public:
    ClientRequestHandler();
    void handleRequest();

private:
    RateLimiter rateLimiter;

};
#endif