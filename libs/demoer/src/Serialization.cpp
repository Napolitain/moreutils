#include "Serialization.hpp"

#include <fstream>
#include <ios>

Serialization::Serialization(const std::string &filename, const bool writeMode) {
	if (writeMode) {
		outFile_ = std::make_unique<std::ofstream>(filename, std::ios::binary);
		kjOut_ = std::make_unique<kj::std::StdOutputStream>(*outFile_);
	} else {
		inFile_ = std::make_unique<std::ifstream>(filename, std::ios::binary);
		kjIn_ = std::make_unique<kj::std::StdInputStream>(*inFile_);
	}
}

void Serialization::writeEventLog(kj::ArrayPtr<const int8_t> events, kj::ArrayPtr<const int8_t> timings) {
	capnp::MallocMessageBuilder message;
	EventLog::Builder log = message.initRoot<EventLog>();

	log.setEvents(events);
	log.setTimings(timings);

	capnp::writePackedMessage(*kjOut_, message);
}

bool Serialization::readNextEventLog(std::vector<int8_t> &events, std::vector<int8_t> &timings) {
	if (!inFile_ || !inFile_->good())
		return false;

	try {
		capnp::PackedMessageReader message(*kjIn_);
		EventLog::Reader log = message.getRoot<EventLog>();

		auto ev = log.getEvents();
		auto ti = log.getTimings();

		events.assign(ev.begin(), ev.end());
		timings.assign(ti.begin(), ti.end());
		return true;
	} catch (const kj::Exception &) {
		return false; // likely EOF or corrupted message
	}
}
