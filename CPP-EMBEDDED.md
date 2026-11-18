# Embedded failure-budget companion
C++11 fixed-window fail-safe failure counter for device telemetry. Invalid settings and excess samples enter a latched Fault until explicit reset. No real-time clock, rolling window, persistence, service probes or network monitoring; this is a deterministic foundation rather than a production SLO service.

## Host validation
```sh
cmake -S . -B build
cmake --build build
ctest --test-dir build --output-on-failure
```
Run existing Python regression tests where present: `python -m unittest discover -s tests -v`.
Hardware safety: no GPIO actuation, no motor/pump/relay switching. Host tests do not establish Arduino Uno or ESP32 binary compatibility or device reliability. Use dedicated hardware watchdogs and physical interlocks for actuators.
