#pragma once

// C libraries
#include <curl/curl.h>
#include <stdint.h>
#include <unistd.h>

// C++ libraries
#include <condition_variable>
#include <chrono>
#include <functional>
#include <iostream>
#include <list>
#include <map>
#include <mutex>
#include <sstream>
#include <queue>
#include <regex>
#include <thread>

// OpenZWave
#include "Defs.h"
#include "Options.h"
#include "Manager.h"
#include "Driver.h"
#include "Node.h"
#include "Group.h"
#include "Notification.h"
#include "value_classes/ValueStore.h"
#include "value_classes/Value.h"
#include "value_classes/ValueBool.h"
#include "platform/Log.h"

// Application
#include "http.cpp"
#include "agent.cpp"
#include "state.cpp"
#include "reducer.cpp"
#include "handler.cpp"
#include "application.cpp"
