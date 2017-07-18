#pragma once
#include <QtWidgets/QWidget>
#include "ui_NetworkGenerationWindow.h"

#include <functional>

namespace MNN {
	enum class ConnectionPattern;
	class AbstractNeuron;
	class AbstractLayerNetwork;
}
namespace mnnt {
	class RealRandomEngine;
}

class NetworkGenerationWindow : public QWidget {
	Q_OBJECT

public:
	NetworkGenerationWindow(QObject* receiver, std::function<void(MNN::AbstractLayerNetwork*)> slot, QWidget *parent = Q_NULLPTR);
	~NetworkGenerationWindow();

protected:
	void hideAdditionalFields();
	void showAdditionalFields();

	static MNN::ConnectionPattern chooseConnection(size_t index);
	static std::function<float(MNN::AbstractNeuron*, MNN::AbstractNeuron*)> chooseDefaultWeights(size_t index);

private:
	Ui::NetworkGenerationWindowClass ui;
	bool areAdditionalFieldsShown;

	static mnnt::RealRandomEngine* m_random_generator;
	static bool isGeneratorInitialized;

protected slots:
	void toggleAdditionalFields();
	void startGeneration();

signals:
	void returnNetwork(MNN::AbstractLayerNetwork*);
};
