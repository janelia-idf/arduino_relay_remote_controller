#ifndef _SYSTEM_STATE_H_
#define _SYSTEM_STATE_H_
#include <SPI.h>
#include <util/atomic.h>
#include <Tle7232g.h>

#include "constants.h"

enum {SYS_ERR_BUF_SZ=50};

class SystemState {

 public:
  SystemState();

  void setErrMsg(char *);
  char errMsg[SYS_ERR_BUF_SZ];

  void initialize();

  bool setRelays(uint32_t relays);
  bool setRelayOn(int relay);
  bool setRelayOff(int relay);
  bool setAllRelaysOn();
  bool setAllRelaysOff();

  bool setBoardRelays(int board, uint32_t board_relays);
  bool setBoardRelayOn(int board, int board_relay);
  bool setBoardRelayOff(int board, int board_relay);
  bool setAllBoardRelaysOn(int board);
  bool setAllBoardRelaysOff(int board);

  bool toggleRelay(int relay);

 private:
  TLE7232G relayDriver;
  int relayOn;

};

extern SystemState systemState;

inline void inlineSetRelayOn(int relay) {systemState.setRelayOn(relay);}
inline void inlineSetRelayOff(int relay) {systemState.setRelayOff(relay);}

#endif
