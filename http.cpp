#include <condition_variable>
#include <chrono>
#include <curl/curl.h>
#include <unistd.h>
#include <functional>
#include <iostream>
#include <list>
#include <map>
#include <mutex>
#include <sstream>
#include <queue>
#include <thread>

struct HttpMessage
{
	std::string jsonContent;
};

void WaitUntilWebApiIsAvailable()
{ 
    auto apiHost = getenv("JOTTAI_API_HOST");
    auto curl = curl_easy_init();
	
	std::cout<<apiHost<<std::endl;
    
	if(curl)
    {
        curl_easy_setopt(curl, CURLOPT_TIMEOUT, 30L);
        curl_easy_setopt(curl, CURLOPT_URL, apiHost);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);
        
        while(1)
        {
            auto result = curl_easy_perform(curl);
        
            if(result == CURLE_OK)
            {
				std::cout<<"got response from API"<<std::endl;
                return;
            }
            std::cerr<<"failed to connect to server: "<<curl_easy_strerror(result)<<std::endl;
            std::cout<<"reconnecting in 5 seconds..."<<std::endl;
			sleep(5);
        }
        
        curl_easy_cleanup(curl);
    }
    else
    {
        std::cerr<<"failed to initialize libcurl"<<std::endl;
    }
}

void LogCurlError(CURLcode curlCode)
{
	if(curlCode != CURLE_OK)
	{
		std::cerr<<"curl_easy_perform() failed: "<<curl_easy_strerror(curlCode)<<std::endl;
	}
}

void SendHttpPostWithJsonBody(std::string json)
{   
    auto apiHost = getenv("JOTTAI_API_HOST");
    auto curl = curl_easy_init();

    if(curl)
    {
        long httpStatusCode = 0;
        struct curl_slist *headers = NULL;
        const char* content = json.c_str();
     
        // headers = curl_slist_append(headers, apiKeyHeader.c_str());
        // headers = curl_slist_append(headers, apiBotIdHeader.c_str());
        headers = curl_slist_append(headers, "Accept: application/json");
        headers = curl_slist_append(headers, "Content-Type: application/json");
        headers = curl_slist_append(headers, "charsets: utf-8");

        LogCurlError(curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers));
		
        curl_easy_setopt(curl, CURLOPT_TIMEOUT, 20L);
        curl_easy_setopt(curl, CURLOPT_URL, apiHost);
        curl_easy_setopt(curl, CURLOPT_POST, 1L);
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, content);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);

        LogCurlError(curl_easy_perform(curl));
        LogCurlError(curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &httpStatusCode));

        if (httpStatusCode != 201)
        {
            std::cerr<<"HTTP post failed with status code: "<<httpStatusCode<<std::endl;
        }

        curl_easy_cleanup(curl);
        curl_slist_free_all(headers);
    }
    else
    {
        std::cerr<<"failed to initialize libcurl"<<std::endl;
    }
}

struct HttpMessageQueue
{
	bool active;
	std::mutex messageQueueMutex;
	std::mutex messageWaiterMutex;
	std::thread thread;
	std::condition_variable messageWaiter;
	std::queue<HttpMessage> messages;

	HttpMessageQueue()
	: active(true), thread(Worker, this)
	{
	}

	~HttpMessageQueue()
	{
		active = false;
		messageWaiter.notify_one();
		thread.join();
	}

private:
	static bool IsEmpty(HttpMessageQueue *httpMessageQueue)
	{
		std::scoped_lock messageQueueLock(httpMessageQueue->messageQueueMutex);
		
		return httpMessageQueue->messages.empty();
	}

	static void Worker(HttpMessageQueue *httpMessageQueue)
	{
		std::unique_lock messageWaiterLock(httpMessageQueue->messageWaiterMutex);

		WaitUntilWebApiIsAvailable();

		while (httpMessageQueue->active)
		{			
			if(!IsEmpty(httpMessageQueue))
			{
				std::scoped_lock messageQueueLock(httpMessageQueue->messageQueueMutex);

				auto message = httpMessageQueue->messages.front();

				SendHttpPostWithJsonBody(message.jsonContent);

				httpMessageQueue->messages.pop();

				std::cout<<"Sent: "<<message.jsonContent<<std::endl;
			}
			else
			{
				httpMessageQueue->messageWaiter.wait(messageWaiterLock);
			}
		}
	}
};

void EnqueueHttpMessage(HttpMessageQueue& messageQueue, HttpMessage httpMesssage)
{		
	std::scoped_lock messageQueueLock(messageQueue.messageQueueMutex);	

	messageQueue.messages.push(httpMesssage);

	messageQueue.messageWaiter.notify_one();
}
