#include <gtest/gtest.h>
#include <drogon/drogon.h>
#include <drogon/HttpClient.h>

class IntegrationTest : public ::testing::Test {
protected:
    void SetUp() override {
        drogon::app().addListener("127.0.0.1", 8848);
        drogon::app().setThreadNum(1);
        drogon::app().run();
    }

    void TearDown() override {
        drogon::app().quit();
    }
};

TEST_F(IntegrationTest, ProcessDataEndpoint) {
    auto client = drogon::HttpClient::newHttpClient("http://127.0.0.1:8848");
    auto req = drogon::HttpRequest::newHttpRequest();
    req->setPath("/processData");

    auto resp = client->sendRequest(req);
    ASSERT_TRUE(resp->getStatusCode() == drogon::HttpStatusCode::k200OK);
}
