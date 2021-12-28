#include "speed.h"

EngineTimers *new_engine_timers() {
  EngineTimers *engine_timers = (EngineTimers*)malloc(sizeof(EngineTimers));

  engine_timers->last_frame_ts = 0;
  engine_timers->millis_elapsed = 0;
  engine_timers->new_frame_ts = 0;
  return engine_timers;
}

void destroy_engine_timers(EngineTimers *engine_timers) {
  free(engine_timers);
}