extern "C"
{
    #include <nats/nats.h>
    #include "nats_operations/nats_operations.h"
}
#include <gtest/gtest.h>
#include <chrono>
#include <ctime>
#include <thread>

class NATS_Compact_Test : public testing::Test
{
    public:
    natsConnection      *conn      = NULL;
    natsOptions         *opts      = NULL;
    natsSubscription    *sub       = NULL;
    natsMsg             *msg       = NULL;
    natsStatus          s          = NATS_OK;
    char subject[256]{"foo"};
    char serverAdress[256]{"localhost:4222"};
    char message[256]{"Test Message \n"};
    int receivedMsgCount{0};

    NATS_Compact_Test()
    {
        s = natsOptions_Create(&opts);
        s = natsConnection_ConnectTo(&conn, serverAdress);
        if(s == NATS_OK) {s = natsConnection_SubscribeTimeout(&sub, conn, subject, 60000, onMsg, NULL);}; 
    };

    NATS_Compact_Test(int x)
    {
        s = natsOptions_Create(&opts);
        s = natsConnection_ConnectTo(&conn, serverAdress);
        if(s == NATS_OK) {s = natsConnection_PublishString(conn, subject, message);}; 
    };

    ~NATS_Compact_Test() override
    {
        natsConnection_Destroy(conn);
        natsOptions_Destroy(opts);
    };

   
};


TEST(TestingNats, TestingPublishSubscribe) {
 std::thread PublisherOne(NATS_Compact_Test);
 std::thread SubscriberOne(NATS_Compact_Test(1));
}