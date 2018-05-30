#pragma once
#include "AbstractNetwork.hpp"
#include "AbstractNetworkControlFunctions.hpp"
namespace mnn {
	class AbstractNeuron;
	class AbstractLayerNetwork : public AbstractNetwork, public AbstractLayerNetworkControlFunctions<AbstractNeuron> {
		public: using AbstractNetwork::AbstractNetwork;
	};
	class AbstractBackpropagationNeuron;
	class AbstractBackpropagationLayerNetwork : public AbstractBackpropagationNetwork, public AbstractLayerNetworkControlFunctions<AbstractBackpropagationNeuron> {
		public: using AbstractBackpropagationNetwork::AbstractBackpropagationNetwork;
	};
}