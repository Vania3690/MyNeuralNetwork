#pragma once
#include <exception>
namespace mnn::Exceptions {
	class MNNException : std::exception {
	public: using std::exception::exception;
	};
}
#define DefineNewMNNException(name) namespace mnn::Exceptions {class name : public mgl::Exceptions::MNNException {public: using MNNException::MNNException;};}