#pragma once
#include <memory>
#include <string>
#include <vector>
#include <capnp/message.h>
#include <capnp/serialize-packed.h>


class Serialization {
	std::unique_ptr<std::ofstream> outFile_;
	std::unique_ptr<std::ifstream> inFile_;
	std::unique_ptr<kj::std::StdInputStream> kjIn_;
	std::unique_ptr<kj::std::StdOutputStream> kjOut_;

public:
	explicit Serialization(const std::string &filename, bool writeMode);

	void writeEventLog(kj::ArrayPtr<const int8_t> events, kj::ArrayPtr<const int8_t> timings);

	bool readNextEventLog(std::vector<int8_t> &events, std::vector<int8_t> &timings);
};
