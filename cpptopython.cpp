#include <pybind11/pybind11.h>
#include <pybind11/stl.h>  // Include to handle std::vector and std::string

namespace py = pybind11;

struct SignalLogging {
    std::string aliasKey;
    std::string channelDevice;
    std::string channelGroupId;
    long channelGroupIdx;
};

// A function that returns a vector of SignalLogging objects
std::vector<SignalLogging> get_signal_loggings() {
    std::vector<SignalLogging> signals;

    // Example data
    SignalLogging signal1 = {"Key123", "DeviceX", "Group42", 1};
    SignalLogging signal2 = {"Key456", "DeviceY", "Group43", 2};

    signals.push_back(signal1);
    signals.push_back(signal2);

    return signals;
}

PYBIND11_MODULE(my_module, m) {
    // Expose the SignalLogging struct to Python
    py::class_<SignalLogging>(m, "SignalLogging")
        .def(py::init<>())  // Default constructor
        .def_readwrite("aliasKey", &SignalLogging::aliasKey)
        .def_readwrite("channelDevice", &SignalLogging::channelDevice)
        .def_readwrite("channelGroupId", &SignalLogging::channelGroupId)
        .def_readwrite("channelGroupIdx", &SignalLogging::channelGroupIdx);

    // Expose the vector of SignalLogging to Python
    m.def("get_signal_loggings", &get_signal_loggings, "A function that returns a vector of SignalLogging");
}
