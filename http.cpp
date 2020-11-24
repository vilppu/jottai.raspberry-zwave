#include <condition_variable>
#include <chrono>
#include <functional>
#include <list>
#include <map>
#include <mutex>
#include <iostream>
#include <queue>
#include <thread>

struct HttpMessage
{
	std::string method = "GET";
	std::string requestUri;
	std::list<std::string> headers;
	std::string jsonContent;
};

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

		while (httpMessageQueue->active)
		{			
			if(!IsEmpty(httpMessageQueue))
			{
				std::scoped_lock messageQueueLock(httpMessageQueue->messageQueueMutex);

				auto message = httpMessageQueue->messages.front();

				httpMessageQueue->messages.pop();

				std::cout<<"Popped"<<message.method<<std::endl;
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
