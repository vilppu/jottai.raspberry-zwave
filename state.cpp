struct Node
{
	Node(uint32_t nodeId)
	: nodeId(nodeId)
	{}

	const uint32_t nodeId;
};

struct Home
{
	Home(uint32_t homeId)
	: homeId(homeId)
	{}

	const uint32_t homeId;
	const std::map<uint32_t, Node> nodes;
};

struct State
{	
	const std::map<uint32_t, Home> Homes;
};

struct StateHolder
{
	std::mutex mutex;
	std::unique_ptr<State> state;	
};

State SetState(StateHolder& stateHolder, std::function<State()> stateProvider)
{
	std::scoped_lock lock(stateHolder.mutex);
	auto newState = stateProvider();

	stateHolder.state = std::make_unique<State>(newState);

	return newState;
}
