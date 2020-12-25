#pragma once
#include "dependencies.cpp"

struct Node
{
	const std::map<uint64_t, const OpenZWave::ValueID> valueIds;

	Node()
	{}

	Node(const std::map<uint64_t, const OpenZWave::ValueID> valueIds)
	: valueIds(valueIds)
	{
	}

	const Node AddOrReplaceValueId(const OpenZWave::ValueID valueId) const 
	{
		auto updatedValueIds = valueIds;
		auto key = valueId.GetId();

		updatedValueIds.erase(key);
		updatedValueIds.emplace(key, valueId);

		return Node(updatedValueIds);
	}

	const OpenZWave::ValueID GetValueId(const uint64_t key) const 
	{
		auto result = valueIds.find(key);

		if(result != valueIds.end())
		{
			return result->second;
		}
		else
		{
			std::cout<<"ValueId "<<key<<" not found. Creating an empty one."<<std::endl;

			return OpenZWave::ValueID();
		}
	}
};

struct Home
{
	const std::map<uint32_t, const Node> nodes;

	Home()
	{}

	Home(const std::map<uint32_t, const Node> nodes)
	: nodes(nodes)
	{
	}

	const Home AddOrReplaceNode(const uint32_t nodeId, const Node node) const 
	{
		auto updatedNodes = nodes;

		updatedNodes.erase(nodeId);
		updatedNodes.emplace(nodeId, node);

		return Home(updatedNodes);
	}

	const Node GetNode(const uint32_t nodeId) const 
	{
		auto result = nodes.find(nodeId);

		if(result != nodes.end())
		{
			return result->second;
		}
		else
		{
			std::cout<<"Node "<<nodeId<<" not found. Creating an empty one."<<std::endl;

			return Node();
		}
	}
};

struct State
{
	const std::map<uint32_t, const Home> homes;

	State()
	{}

	State(const std::map<uint32_t, const Home> homes)
	: homes(homes)
	{
	}

	const State AddOrReplaceHome(const uint32_t homeId, const Home node) const 
	{
		auto updatedHomes = homes;

		updatedHomes.erase(homeId);
		updatedHomes.emplace(homeId, node);

		return State(updatedHomes);
	}

	const Home GetHome(const uint32_t homeId) const 
	{
		auto result = homes.find(homeId);

		if(result != homes.end())
		{
			return result->second;
		}
		else
		{
			std::cout<<"Home "<<homeId<<" not found. Creating an empty one."<<std::endl;

			return Home();
		}
	}

	const State AddNode(const uint32_t homeId, const uint32_t nodeId) const 
	{		
		auto home = GetHome(homeId);				
		auto updatedHome = home.AddOrReplaceNode(nodeId, Node());		
		auto updatedState = AddOrReplaceHome(homeId, updatedHome);

		return State(updatedState);
	}

	const State AddOrReplaceValueId(const uint32_t homeId, const uint32_t nodeId, const OpenZWave::ValueID valueId) const 
	{		
		auto home = GetHome(homeId);		
		auto node = home.GetNode(nodeId);				
		auto updatedNode = node.AddOrReplaceValueId(valueId);
		auto updatedHome = home.AddOrReplaceNode(nodeId, updatedNode);
		auto updatedState = AddOrReplaceHome(homeId, updatedHome);

		return State(updatedState);
	}

	const OpenZWave::ValueID GetValueId(const uint32_t homeId, const uint32_t nodeId, const uint64_t key) const 
	{
		auto home = GetHome(homeId);
		auto node = home.GetNode(nodeId);
		auto valueId = node.GetValueId(key);

		return valueId;
	}
};
