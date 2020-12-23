#pragma once
#include "dependencies.cpp"

struct Node
{
	Node(const uint32_t nodeId)
	: nodeId(nodeId)
	{}
	
	Node(const uint32_t nodeId, const OpenZWave::ValueID valueId)
	: nodeId(nodeId), valueId(valueId)
	{}

	const uint32_t nodeId;
	const OpenZWave::ValueID valueId;
};

struct Home
{
	Home(const uint32_t homeId, const std::map<uint32_t, const Node> nodes)
	: homeId(homeId), nodes(nodes)
	{}

	Home(const Home &home)
	: homeId(home.homeId)
	{}

	static const Home Empty(const uint32_t homeId)
	{
		return Home(homeId, std::map<uint32_t, const Node>());
	}

	const uint32_t homeId;
	const std::map<uint32_t, const Node> nodes;
};

struct State
{
	const std::map<uint32_t, const Home> homes;

	State()
	: homes(std::map<uint32_t, const Home>())
	{}

	State(const std::map<uint32_t, const Home> homes)
	: homes(homes)
	{}

	const Home GetHome(const uint32_t homeId) const
	{
		auto home = homes.find(homeId);

		if (home != homes.end()) {
			return home->second;
		}
		else {
			return Home::Empty(homeId);
		}
	}

	const State AddOrReplaceNode(const uint32_t homeId, const Node node) const
	{
		auto home = GetHome(homeId);
		auto updatedNodes = home.nodes;
		auto updatedHomes = homes;

		updatedNodes.erase(node.nodeId);
		updatedNodes.emplace(node.nodeId, node);

		auto updatedHome = Home(homeId, updatedNodes);

		updatedHomes.erase(home.homeId);
		updatedHomes.emplace(home.homeId, updatedHome);

		return State(updatedHomes);
	}
};
