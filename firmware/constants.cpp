#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif
#include "constants.h"
namespace constants {
  // Communications parameters
  const int baudrate = 9600;

  // Device parameters
  const int modelNumber = 2761;
  const int serialNumberMin = 0;
  const int serialNumberMax = 255;
  const int firmwareNumber = 2;

  // Pin assignment
  const int relayDriverCsPin = 49;
  const int relayDriverInPin = 48;

  // Relay parameters
  const int relayCount = 16;
  const int relayDriverDeviceCount = 2;
  const int boardCount = 4;
  const int boardRelayCount = 4;

}
