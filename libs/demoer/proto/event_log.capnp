@0xbf5147bdc0f99625;

struct EventLog {
  events @0: List(Int8);
  timings @1: List(Int8);  # same length as events, each timing corresponds to event
}
