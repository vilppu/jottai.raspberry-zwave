#pragma once
#include "dependencies.cpp"

const auto apiToken = std::string(getenv("JOTTAI_API_TOKEN"));

struct HttpRequest
{
    const bool isPost;
    const long timeout;
    const std::string path;
    const std::string jsonContent;

    HttpRequest(const std::string path, const std::string jsonContent, bool isPost, long timeout)
        : path(path), jsonContent(jsonContent), isPost(isPost), timeout(timeout)
    {
    }

    HttpRequest(const std::string path, const std::stringstream &jsonContent, bool isPost, long timeout)
        : path(path), jsonContent(jsonContent.str()), isPost(isPost), timeout(timeout)
    {
    }

    HttpRequest(const std::string path, const char *jsonContent, bool isPost, long timeout)
        : path(path), jsonContent(jsonContent), isPost(isPost), timeout(timeout)
    {
    }
};

CURLcode LogErrors(CURLcode curlCode)
{
    if (curlCode != CURLE_OK)
    {
        std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(curlCode) << std::endl;
    }

    return curlCode;
}

CURLcode ExecuteWithLogging(CURL *curl)
{
    return LogErrors(curl_easy_perform(curl));
}

void ExecuteWithLoggingUntilSucceed(CURL *curl)
{
    while (ExecuteWithLogging(curl) != CURLE_OK && !exiting)
    {
        std::cout << "Retrying after 5 seconds" << std::endl;
        sleep(5);
    }
}

size_t CurlStoreReponseCallback(char *ptr, size_t size, size_t nmemb, std::string *response)
{
    auto totalSize = size * nmemb;

    for (size_t i = 0; i < totalSize; i++)
    {
        char responseByte = ptr[i];
        (*response) += responseByte;
    }

    return totalSize;
}

size_t CurlDiscardReponseCallback(char *ptr, size_t size, size_t nmemb, void *_)
{
    auto totalSize = size * nmemb;

    return totalSize;
}

bool NotSuccess(long httpStatusCode)
{
    return httpStatusCode < 200 || httpStatusCode > 299;
}

// void RefreshBearerToken()
// {
//     auto curl = curl_easy_init();

//     if(curl)
//     {
//         std::string response = "";
//         std::string tokenUrl = getenv("JOTTAI_TOKEN_URL");
//         std::string grantType = "client_credentials";
//         std::string clientId = getenv("JOTTAI_CLIENT_ID");
//         std::string clientSecret = getenv("JOTTAI_CLIENT_SECRET");
//         std::string audience = getenv("JOTTAI_AUDIENCE");
//         std::string scope = "DeviceGroupId";

//         std::stringstream json;
//         json
//         <<"{ "
//         <<"  \"grant_type\": \""<<grantType<<"\","
//         <<"  \"client_id\": \""<<clientId<<"\","
//         <<"  \"client_secret\": \""<<clientSecret<<"\","
//         <<"  \"audience\": \""<<audience<<"\","
//         <<"  \"scope\": \""<<scope<<"\""
//         <<"}";

//         long httpStatusCode = 0;
//         struct curl_slist *headers = NULL;
//         auto jsonBody = json.str();
//         auto content = jsonBody.c_str();

//         headers = curl_slist_append(headers, "Accept: application/json");
//         headers = curl_slist_append(headers, "Content-Type: application/json");
//         headers = curl_slist_append(headers, "charsets: utf-8");

//         LogErrors(curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers));

//         curl_easy_setopt(curl, CURLOPT_TIMEOUT, 20L);
//         curl_easy_setopt(curl, CURLOPT_URL, "https://vilppu.eu.auth0.com/oauth/token");
//         curl_easy_setopt(curl, CURLOPT_POST, 1L);
//         curl_easy_setopt(curl, CURLOPT_POSTFIELDS, content);
//         curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
//         curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);
//         curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, CurlStoreReponseCallback);
//         curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

//         while (NotSuccess(httpStatusCode) && !exiting)
//         {
//             ExecuteWithLoggingUntilSucceed(curl);
//             LogErrors(curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &httpStatusCode));

//             if (NotSuccess(httpStatusCode))
//             {
//                 std::cerr<<"Fetching bearer token failed with status code: "<<httpStatusCode<<std::endl;
//                 std::cout<<"Retrying after 5 seconds"<<std::endl;
//                 sleep(5);
//             }
//         }

//         std::regex accessTokenRegex (".*\"access_token\"\\s*:\\s*\"([^\"]+)\".*");
//         std::smatch accessTokenResult;
//         std::regex_match(response, accessTokenResult, accessTokenRegex);

//         if(accessTokenResult.size() == 2)
//         {
//             bearerToken = accessTokenResult[1];
//         }
//         else
//         {
//             std::cerr<<"Could not parse bearer token"<<std::endl;
//         }

//         curl_easy_cleanup(curl);
//         curl_slist_free_all(headers);
//     }
//     else
//     {
//         std::cerr<<"failed to initialize libcurl"<<std::endl;
//     }
// }

std::tuple<long, const std::string> TryToSendToAgent(HttpRequest request)
{
    auto curl = curl_easy_init();

    if (curl)
    {
        std::string response = "";
        auto apiHost = std::string(getenv("JOTTAI_API_HOST"));
        auto url = apiHost + request.path;
        long httpStatusCode = 0;
        struct curl_slist *headers = NULL;
        auto content = request.jsonContent.c_str();
        auto authorization = std::string("Authorization: Bearer ") + apiToken;

        headers = curl_slist_append(headers, "Accept: application/json");
        headers = curl_slist_append(headers, "Content-Type: application/json");
        headers = curl_slist_append(headers, "charsets: utf-8");
        headers = curl_slist_append(headers, authorization.c_str());

        LogErrors(curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers));
        curl_easy_setopt(curl, CURLOPT_TIMEOUT, request.timeout);
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        if (request.isPost)
        {
            curl_easy_setopt(curl, CURLOPT_POST, 1L);
            curl_easy_setopt(curl, CURLOPT_POSTFIELDS, content);
        }
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, CurlStoreReponseCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
        ExecuteWithLoggingUntilSucceed(curl);
        LogErrors(curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &httpStatusCode));
        curl_easy_cleanup(curl);
        curl_slist_free_all(headers);

        return {httpStatusCode, response};
    }
    else
    {
        std::cerr << "failed to initialize libcurl" << std::endl;

        return {-1, std::string()};
    }
}

std::tuple<long, const std::string> SendToAgent(HttpRequest request)
{
    int httpStatusCode = 0;

    while (true)
    {
        auto [httpStatusCode, response] = TryToSendToAgent(request);

        if (exiting)
        {
            return {httpStatusCode, response};
        }
        // else if (httpStatusCode == 401)
        // {
        //     std::cout << "Fetching a new bearer token" << std::endl;
        //     RefreshBearerToken();
        // }
        // else if (httpStatusCode == 403)
        // {
        //     std::cout << "Access denied" << std::endl;
        //     std::cout << "Fetching a new bearer token in 10 seconds" << std::endl;
        //     sleep(10);
        //     RefreshBearerToken();
        // }
        else if (NotSuccess(httpStatusCode))
        {
            std::cerr << "HTTP request to " << request.path << " failed with status code: " << httpStatusCode << std::endl;
            std::cout << "Retrying after 5 seconds" << std::endl;
            sleep(5);
        }
        else
        {
            return {httpStatusCode, response};
        }
    }
}

struct HttpMessagesToAgentQueue
{
    bool active;
    std::mutex messageQueueMutex;
    std::mutex messageWaiterMutex;
    std::thread thread;
    std::condition_variable messageWaiter;
    std::queue<HttpRequest> messages;

    HttpMessagesToAgentQueue()
        : active(true), thread(Worker, this)
    {
    }

    ~HttpMessagesToAgentQueue()
    {
        active = false;
        messageWaiter.notify_one();
        thread.join();
    }

private:
    static bool IsEmpty(HttpMessagesToAgentQueue *self)
    {
        std::scoped_lock messageQueueLock(self->messageQueueMutex);

        return self->messages.empty();
    }

    static void Worker(HttpMessagesToAgentQueue *self)
    {
        std::unique_lock messageWaiterLock(self->messageWaiterMutex);

        while (self->active && !exiting)
        {
            if (!IsEmpty(self))
            {
                std::scoped_lock messageQueueLock(self->messageQueueMutex);

                auto message = self->messages.front();

                SendToAgent(message);

                self->messages.pop();
            }
            else
            {
                self->messageWaiter.wait(messageWaiterLock);
            }
        }
    }
};

struct Http
{
    HttpMessagesToAgentQueue messageQueue;

    void EnqueueHttpMessageToAgent(HttpRequest httpMesssage)
    {
        std::scoped_lock messageQueueLock(messageQueue.messageQueueMutex);

        messageQueue.messages.push(httpMesssage);

        messageQueue.messageWaiter.notify_one();
    }
};
