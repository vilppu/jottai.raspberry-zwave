#pragma once
#include "dependencies.cpp"

std::string bearerToken = "";

struct JsonObject
{
    const std::string jsonContent;

    JsonObject(const std::string jsonContent)
    : jsonContent(jsonContent)
    {        
    }

    JsonObject(const std::stringstream& jsonContent)
    : jsonContent(jsonContent.str())
    {        
    }

    JsonObject(const char* jsonContent)
    : jsonContent(jsonContent)
    {
    }
};

CURLcode LogErrors(CURLcode curlCode)
{   
	if(curlCode != CURLE_OK)
	{
		std::cerr<<"curl_easy_perform() failed: "<<curl_easy_strerror(curlCode)<<std::endl;
	}

    return curlCode;
}

CURLcode ExecuteWithLogging(CURL* curl)
{
    return LogErrors(curl_easy_perform(curl));
}

void ExecuteWithLoggingUntilSucceed(CURL* curl)
{
	while(ExecuteWithLogging(curl) != CURLE_OK)
	{
		std::cout<<"Retrying after 5 seconds"<<std::endl;
        sleep(5);
	}
}

size_t CurlStoreReponseCallback(char *ptr, size_t size, size_t nmemb, std::string *response)
{
    auto totalSize = size*nmemb;

    for(size_t i=0; i<totalSize; i++)
    {        
        char responseByte = ptr[i];
        (*response) += responseByte;
    }

    return totalSize;
}

size_t CurlDiscardReponseCallback(char *ptr, size_t size, size_t nmemb, void *_)
{        
    auto totalSize = size*nmemb;

    return totalSize;
}

bool NotSuccess(long httpStatusCode)
{
    return httpStatusCode < 200 || httpStatusCode > 299;
}

void RefreshBearerToken()
{
    auto curl = curl_easy_init();

    if(curl)
    { 
        std::string response = "";
        std::string tokenUrl = getenv("JOTTAI_TOKEN_URL");
        std::string grantType = "client_credentials";
        std::string clientId = getenv("JOTTAI_CLIENT_ID");
        std::string clientSecret = getenv("JOTTAI_CLIENT_SECRET");
        std::string audience = getenv("JOTTAI_AUDIENCE");
        std::string scope = "DeviceGroupId";

        std::stringstream json;
        json
        <<"{ "
        <<"  \"grant_type\": \""<<grantType<<"\","
        <<"  \"client_id\": \""<<clientId<<"\","
        <<"  \"client_secret\": \""<<clientSecret<<"\","
        <<"  \"audience\": \""<<audience<<"\","
        <<"  \"scope\": \""<<scope<<"\""
        <<"}";

        long httpStatusCode = 0;
        struct curl_slist *headers = NULL;
        auto jsonBody = json.str();
        auto content = jsonBody.c_str();
        
        headers = curl_slist_append(headers, "Accept: application/json");
        headers = curl_slist_append(headers, "Content-Type: application/json");
        headers = curl_slist_append(headers, "charsets: utf-8");

        LogErrors(curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers));
		
        curl_easy_setopt(curl, CURLOPT_TIMEOUT, 20L);
        curl_easy_setopt(curl, CURLOPT_URL, "https://vilppu.eu.auth0.com/oauth/token");
        curl_easy_setopt(curl, CURLOPT_POST, 1L);
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, content);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, CurlStoreReponseCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

        while (NotSuccess(httpStatusCode))
        {
            ExecuteWithLoggingUntilSucceed(curl);
            LogErrors(curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &httpStatusCode));
            
            if (NotSuccess(httpStatusCode))
            {
                std::cerr<<"Fetching bearer token failed with status code: "<<httpStatusCode<<std::endl;
                std::cout<<"Retrying after 5 seconds"<<std::endl;
                sleep(5);
            }
        }
        
        std::regex accessTokenRegex (".*\"access_token\"\\s*:\\s*\"([^\"]+)\".*");        
        std::smatch accessTokenResult; 
        std::regex_match(response, accessTokenResult, accessTokenRegex);
        
        if(accessTokenResult.size() == 2)
        {
            bearerToken = accessTokenResult[1];            
        }        
        else
        {
            std::cerr<<"Could not parse bearer token"<<std::endl;
        }        

        curl_easy_cleanup(curl);
        curl_slist_free_all(headers);
    }
    else
    {
        std::cerr<<"failed to initialize libcurl"<<std::endl;
    }
}

long TryToSendJsonToAgent(std::string json)
{
    auto curl = curl_easy_init();

    if(curl)
    {        
        auto apiHost = getenv("JOTTAI_API_HOST");
        long httpStatusCode = 0;
        struct curl_slist *headers = NULL;
        auto content = json.c_str();
        auto authorization = std::string("Authorization: Bearer ") + bearerToken;
        
        headers = curl_slist_append(headers, "Accept: application/json");
        headers = curl_slist_append(headers, "Content-Type: application/json");
        headers = curl_slist_append(headers, "charsets: utf-8");
        headers = curl_slist_append(headers, authorization.c_str());

        LogErrors(curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers));
		
        curl_easy_setopt(curl, CURLOPT_TIMEOUT, 20L);
        curl_easy_setopt(curl, CURLOPT_URL, apiHost);
        curl_easy_setopt(curl, CURLOPT_POST, 1L);
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, content);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, CurlDiscardReponseCallback);
        ExecuteWithLoggingUntilSucceed(curl);   
        LogErrors(curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &httpStatusCode));            
        curl_easy_cleanup(curl);
        curl_slist_free_all(headers);

        return httpStatusCode;
    }
    else
    {
        std::cerr<<"failed to initialize libcurl"<<std::endl;

        return -1;
    }    
}

void SendJsonToAgent(std::string json)
{
    int httpStatusCode = 0;

    while (NotSuccess(httpStatusCode))
    {
        httpStatusCode = TryToSendJsonToAgent(json);        

        if(httpStatusCode == 401 || httpStatusCode == 405)
        {
            std::cout<<"Fetching a new bearer token"<<std::endl;
            RefreshBearerToken();
        }
        else if (NotSuccess(httpStatusCode))
        {
            std::cerr<<"HTTP post failed with status code: "<<httpStatusCode<<std::endl;
            std::cout<<"Retrying after 5 seconds"<<std::endl;
            sleep(5);
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
	std::queue<JsonObject> messages;

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

		while (self->active)
		{
			if(!IsEmpty(self))
			{
				std::scoped_lock messageQueueLock(self->messageQueueMutex);

				auto message = self->messages.front();

				SendJsonToAgent(message.jsonContent);

				self->messages.pop();

				std::cout<<"Sent: "<<message.jsonContent<<std::endl;
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

    void EnqueueHttpMessageToAgent(JsonObject httpMesssage)
    {
        std::scoped_lock messageQueueLock(messageQueue.messageQueueMutex);	

        messageQueue.messages.push(httpMesssage);

        messageQueue.messageWaiter.notify_one();
    }
};
