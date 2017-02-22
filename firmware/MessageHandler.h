#ifndef _MESSAGE_HANDER_H_
#define _MESSAGE_HANDER_H_
#include <SerialReceiver.h>
#include "DictPrinter.h"
#include "constants.h"
#include "SavedVariables.h"

class MessageHandler : public SerialReceiver {

 public:
  void processMsg();

 private:
  DictPrinter dprint;
  void msgSwitchYard();
  void handleGetDevInfo();
  void handleGetCmds();

  bool checkNumberOfArgs(int num);
  bool checkSerialNumberArg(int serial_number);
  void systemCmdRsp(bool flag);

  void handleGetRspCodes();
  void handleSetSerialNumber();

  bool checkRelayArg(int relay);
  bool checkBoardArg(int board);
  bool checkBoardRelayArg(int board_relay);

  void handleSetRelays();
  void handleSetRelayOn();
  void handleSetRelayOff();
  void handleSetAllRelaysOn();
  void handleSetAllRelaysOff();

  void handleSetBoardRelays();
  void handleSetBoardRelayOn();
  void handleSetBoardRelayOff();
  void handleSetAllBoardRelaysOn();
  void handleSetAllBoardRelaysOff();

  void handleToggleRelay();

  // Development
  void handleDebug();
};

extern MessageHandler messageHandler;
#endif
