#include "NeuralNetwork.hpp"
#include "layer.hpp"
void mnn::MatrixLayeredNeuralNetwork::process() {
	if (m_layers.back()->size() != m_outputs.size())
		throw Exceptions::MatrixStructureIsBroken("Size of the last layer must be equal to number of outputs.");
	
	auto current = m_inputs;
	for (auto &layer : m_layers)
		current = layer->process(current);
	
	auto it1 = m_outputs.begin();
	auto it2 = current.cbegin();
	while (it1 != m_outputs.end() || it2 != current.cend()) {
		*it1 = *it2;
		it1++; it2++;
	}
}
void mnn::MatrixLayeredNeuralNetwork::add_layer(size_t const& size, bool bias, Value const& minimum_weight_value, Value const& maximum_weight_value) {
	m_layers.push_back(std::make_shared<Layer>(size, m_layers.empty() ? m_inputs.size() : m_layers.size(), bias, minimum_weight_value, maximum_weight_value));
}

mnn::MatrixLayeredBackpropagationNeuralNetwork::MatrixLayeredBackpropagationNeuralNetwork(size_t const& input_number, size_t const& output_number, 
																						  Value const& eta, Value const& alpha)
	: BackpropagationNeuralNetworkInterface(input_number, output_number), m_eta(eta), m_alpha(alpha) {}

void mnn::MatrixLayeredBackpropagationNeuralNetwork::process() {
	if (m_layers.back()->size() != m_outputs.size())
		throw Exceptions::MatrixStructureIsBroken("Size of the last layer must be equal to number of outputs.");

	auto current = m_inputs;
	for (auto &layer : m_layers)
		current = layer->process(current);

	auto it1 = m_outputs.begin();
	auto it2 = current.cbegin();
	while (it1 != m_outputs.end() || it2 != current.cend()) {
		*it1 = *it2;
		it1++; it2++;
	}
}
void mnn::MatrixLayeredBackpropagationNeuralNetwork::add_layer(size_t const& size, bool bias, Value const& minimum_weight_value, Value const& maximum_weight_value) {
	m_layers.push_back(std::make_shared<Layer>(size, m_layers.empty() ? m_inputs.size() : m_layers.back()->size(), bias, minimum_weight_value, maximum_weight_value));
}

void mnn::MatrixLayeredBackpropagationNeuralNetwork::backpropagate(NeuronContainer<Value> const& _outputs) {
	if (_outputs.size() != m_outputs.size())
		throw Exceptions::UnsupportedInputError("Unsupported number of outputs was passed.");
	if (m_layers.empty())
		return;

	mnn::NeuronContainer<mnn::Value> current_gradient(m_outputs.size());
	
	auto layer = m_layers.rbegin();
	auto next = layer;
	while (layer != m_layers.rend()) {
		if (layer == m_layers.rbegin())
			for (size_t i = 0; i < m_outputs.size(); i++)
				current_gradient.at(i) = (_outputs.at(i) - m_outputs.at(i)) * normalization_derivative(m_outputs.at(i));
		else {
			mnn::NeuronContainer<mnn::Value> next_gradient((*layer)->m_weights.front().size());

			for (size_t i = 0; i < (*layer)->m_weights.front().size(); i++) {
				for (size_t j = 0; j < current_gradient.size(); j++)
					next_gradient.at(i) += current_gradient.at(j) * (*next)->m_weights.at(i).at(j);
				next_gradient.at(i) *= normalization_derivative((*layer)->m_value.at(i));
			}
			current_gradient = next_gradient;
		}

		for (size_t i = 0; i < (*layer)->m_deltas.size(); i++)
			for (size_t j = 0; j < (*layer)->m_deltas.front().size(); j++) {
				if (layer == --m_layers.rend())
					(*layer)->m_deltas.at(i).at(j) = m_eta * current_gradient.at(j)
					* (i < (*layer)->m_deltas.size() - 1 ? m_inputs.at(i) : 1.0)
					+ m_alpha * (*layer)->m_deltas.at(i).at(j);
				else {
					auto next = layer;
					(*layer)->m_deltas.at(i).at(j) = m_eta * current_gradient.at(j)
						* (i < (*layer)->m_deltas.size() - 1 ? (*++next)->m_value.at(i) : 1.0)
						+ m_alpha * (*layer)->m_deltas.at(i).at(j);
				}

				(*layer)->m_weights.at(i).at(j) += (*layer)->m_deltas.at(i).at(j);
			}

		next = layer++;
	}
}