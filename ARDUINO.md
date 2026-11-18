# Arduino failure-budget demo

Connect a normally-open dry-contact pushbutton between D2 and GND. The sketch configures `INPUT_PULLUP`; a closed switch is interpreted as a synthetic successful reading. Do not connect mains, motor voltages, or external voltage sources directly to D2. Target: Uno/Mega or ESP32 (adjust D2/LED pin mapping to the actual board; ESP32 pins have different electrical limits). The diagnostic LED is not a safety-rated interlock. It starts off, and turns off for warning/exhaustion/fault. At 10 samples the budget refuses further records until an explicit device reset; no automatic restart. On a disconnected switch, readings are failures and the LED stays off. This is a *fixed-count window*, not time-based rolling aggregation or persistent storage.

Host regression: `cmake -S . -B build && cmake --build build && ctest --test-dir build --output-on-failure`. Host tests are not proof of electrical or board behavior. No physical hardware verification has occurred. Keep `cpp/core.hpp` relative to the sketch or adjust the include path in copied sketches.

## Board-build CI (added 2026-11-17)
The `.github/workflows/arduino-board-compile.yml` workflow invokes `arduino-cli compile` for **Arduino Uno (AVR)** and **ESP32 generic dev module**. This checks board-toolchain compatibility in GitHub Actions; host CMake/g++ and Python CI remain separate. A green compile does not establish actual sensor readings, wiring, pin compatibility on every variant, watchdog behavior, or electrical safety. Test on the actual board before connecting actuators.

Fixed-window budget enters a latched Fault after overrun; recovery requires deliberate reset. No rolling time window, persistence, or safety-rated shutdown.
