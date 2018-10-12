#pragma once
#include <memory>
#include "mnn/interfaces/NeuralNetworkInterface.hpp"
namespace mnn {
	class NeuronInterface;

	class MatrixLayeredNeuralNetwork : public NeuralNetworkInterface {
	protected:
		//LayerContainer
	public:
		virtual void process() override;
		using NeuralNetworkInterface::process;

		inline void add_input(std::shared_ptr<NeuronInterface> neuron) {
			m_inputs.push_back(neuron);
		}
		inline void add_output(std::shared_ptr<NeuronInterface> neuron) {
			m_outputs.push_back(neuron);
		}
	};
}