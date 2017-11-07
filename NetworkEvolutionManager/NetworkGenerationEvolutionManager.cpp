#include "NetworkGenerationEvolutionManager.hpp"
#include "AbstractLayerNetwork.hpp"
#include "Automatization.hpp"
mnn::NetworkGenerationEvolutionManager::~NetworkGenerationEvolutionManager() {
	for (auto &it : m_networks)
		delete it.second;
}
void mnn::NetworkGenerationEvolutionManager::newPopulation() {
	if (m_networks.size() != 0u) 
		while (m_networks.size()) {
			delete m_networks.back().second;
			m_networks.pop_back();
	}
	m_networks.reserve(m_units);
	for (size_t i = 0; i < m_units; i++)
		m_networks.push_back(std::make_pair(0, generateTypicalLayerNeuralNetwork(m_input_neurons, m_output_neurons,
																				 m_layer_divisor, m_hidden_neurons / m_layer_divisor,
																				 ConnectionPattern::EachFromPreviousLayerWithBias, random_weights)));
}
#include <algorithm>
void mnn::NetworkGenerationEvolutionManager::testPopulation() {
	for (auto &it : m_networks) {
		it.first = m_evaluate([&it](NeuronContainer<Type> inputs) -> NeuronContainer<Type> {
			it.second->calculate(inputs);
			return it.second->getOutputs();
		});
	}
}
void mnn::NetworkGenerationEvolutionManager::selectionStep() {
	std::sort(m_networks.begin(), m_networks.end(), [](auto l, auto r) { return l.first > r.first; });
	switch (m_selection_type) {
		Type mid_value;
		case SelectionType::Number:
			mid_value = m_units * m_selection_persent;
			while (m_networks.size() > mid_value) {
				delete m_networks.back().second;
				m_networks.pop_back();
			}
			break;
		case SelectionType::Value:
			mid_value = m_networks.front().first
				- (m_networks.front().first - m_networks.back().first) * m_selection_persent;

			while (m_networks.back().first < mid_value) {
				delete m_networks.back().second;
				m_networks.pop_back();
			}
			break;
	}
}
void mnn::NetworkGenerationEvolutionManager::recreatePopulation() {
	//To be implemented.
}