#ifndef _CONSTANTS_H_
#define _CONSTANTS_H_

namespace constants {
  // Communications parameters
  extern const int baudrate;

  // Device parameters
  extern const int modelNumber;
  extern const int serialNumberMin;
  extern const int serialNumberMax;
  extern const int firmwareNumber;

  // Pin assignment
  extern const int relayDriverCsPin;
  extern const int relayDriverInPin;

  // Relay parameters
  extern const int relayCount;
  extern const int relayDriverDeviceCount;
  extern const int boardCount;
  extern const int boardRelayCount;

}
#endif
