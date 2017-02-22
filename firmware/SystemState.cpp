#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif
#include "string.h"
#include "SystemState.h"

SystemState::SystemState() {
  setErrMsg("");
}

void SystemState::setErrMsg(char *msg) {
  strncpy(errMsg,msg,SYS_ERR_BUF_SZ);
}

void SystemState::initialize() {
  relayDriver = TLE7232G(constants::relayDriverCsPin,constants::relayDriverInPin);

  // Initialize SPI:
  SPI.setDataMode(SPI_MODE1);
  SPI.setClockDivider(SPI_CLOCK_DIV4);
  SPI.setBitOrder(MSBFIRST);
  SPI.begin();

  relayDriver.init(constants::relayDriverDeviceCount);
  setAllRelaysOff();

}

bool SystemState::setRelays(uint32_t relays) {
  relayDriver.setChannels(relays);
  return true;
}

bool SystemState::setRelayOn(int relay) {
  relayDriver.setChannelOn(relay);
  return true;
}

bool SystemState::setRelayOff(int relay) {
  relayDriver.setChannelOff(relay);
  return true;
}

bool SystemState::setAllRelaysOn() {
  uint32_t relays = 0;
  relays = ~relays;
  setRelays(relays);
  return true;
}

bool SystemState::setAllRelaysOff() {
  uint32_t relays = 0;
  setRelays(relays);
  return true;
}

bool SystemState::setBoardRelays(int board, uint32_t board_relays) {
  uint32_t relays = board_relays << board*constants::boardRelayCount;
  setRelays(relays);
  return true;
}

bool SystemState::setBoardRelayOn(int board, int board_relay) {
  int relay = board*constants::boardRelayCount + board_relay;
  setRelayOn(relay);
  return true;
}

bool SystemState::setBoardRelayOff(int board, int board_relay) {
  int relay = board*constants::boardRelayCount + board_relay;
  setRelayOff(relay);
  return true;
}

bool SystemState::setAllBoardRelaysOn(int board) {
  int relay;
  int relay_offset = board*constants::boardRelayCount;
  for (int board_relay=0; board_relay<constants::boardRelayCount; board_relay++) {
    relay = relay_offset + board_relay;
    setRelayOn(relay);
  };
  return true;
}

bool SystemState::setAllBoardRelaysOff(int board) {
  int relay;
  int relay_offset = board*constants::boardRelayCount;
  for (int board_relay=0; board_relay<constants::boardRelayCount; board_relay++) {
    relay = relay_offset + board_relay;
    setRelayOff(relay);
  };
  return true;
}

bool SystemState::toggleRelay(int relay) {
  uint32_t channels_on = relayDriver.getChannelsOn();
  uint32_t bit = 1;
  bit = bit << relay;
  channels_on = channels_on ^ bit;
  relayDriver.setChannels(channels_on);
  return true;
}

SystemState systemState;


