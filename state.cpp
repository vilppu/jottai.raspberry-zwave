#pragma once
#include "dependencies.cpp"

struct Node
{
	Node(const uint32_t nodeId)
	: nodeId(nodeId)
	{}

	const uint32_t nodeId;
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

	const State AddOrReplaceHome(const Home home) const
	{
		std::map<uint32_t, const Home> updatedHomes = homes;
		
		updatedHomes.erase(home.homeId);
		updatedHomes.emplace(home.homeId, home);

		return State(updatedHomes);
	}

	const State RemoveHome(const Home home) const
	{
		std::map<uint32_t, const Home> updatedHomes = homes;
		
		updatedHomes.erase(home.homeId);

		return State(updatedHomes);
	}
};
