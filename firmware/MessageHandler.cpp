#include <util/atomic.h>
#include "MessageHandler.h"
#include "Streaming.h"
#include "SystemState.h"

enum {
  cmdGetDevInfo,                    // Done
  cmdGetCmds,                       // Done
  cmdGetRspCodes,                   // Done
  cmdSetSerialNumber,               //

  cmdSetRelays,                 //
  cmdSetRelayOn,                //
  cmdSetRelayOff,               //
  cmdSetAllRelaysOn,            //
  cmdSetAllRelaysOff,           //

  cmdSetBoardRelays,
  cmdSetBoardRelayOn,                //
  cmdSetBoardRelayOff,                //
  cmdSetAllBoardRelaysOn,                //
  cmdSetAllBoardRelaysOff,                //

  cmdToggleRelay,                //

  // DEVELOPMENT
  cmdDebug,
};


const int rspSuccess = 1;
const int rspError = 0;

void MessageHandler::processMsg() {
  while (Serial.available() > 0) {
    process(Serial.read());
    if (messageReady()) {
      msgSwitchYard();
      reset();
    }
  }
  return;
}

void MessageHandler::msgSwitchYard() {
  int cmd = readInt(0);
  dprint.start();
  dprint.addIntItem("cmd_id", cmd);

  switch (cmd) {

    case cmdGetDevInfo:
      handleGetDevInfo();
      break;

    case cmdGetCmds:
      handleGetCmds();
      break;

    case cmdGetRspCodes:
      handleGetRspCodes();
      break;

    case cmdSetSerialNumber:
      handleSetSerialNumber();
      break;

    case cmdSetRelays:
      handleSetRelays();
      break;

    case cmdSetRelayOn:
      handleSetRelayOn();
      break;

    case cmdSetRelayOff:
      handleSetRelayOff();
      break;

    case cmdSetAllRelaysOn:
      handleSetAllRelaysOn();
      break;

    case cmdSetAllRelaysOff:
      handleSetAllRelaysOff();
      break;

    case cmdSetBoardRelays:
      handleSetBoardRelays();
      break;

    case cmdSetBoardRelayOn:
      handleSetBoardRelayOn();
      break;

    case cmdSetBoardRelayOff:
      handleSetBoardRelayOff();
      break;

    case cmdSetAllBoardRelaysOn:
      handleSetAllBoardRelaysOn();
      break;

    case cmdSetAllBoardRelaysOff:
      handleSetAllBoardRelaysOff();
      break;

    case cmdToggleRelay:
      handleToggleRelay();
      break;

      // DEVELOPMENT
    case cmdDebug:
      handleDebug();
      break;

    default:
      dprint.addIntItem("status", rspError);
      dprint.addStrItem("err_msg", "unknown command");
      break;
  }
  dprint.stop();
}

void MessageHandler::handleGetCmds() {
  dprint.addIntItem("status", rspSuccess);
  dprint.addIntItem("getDevInfo", cmdGetDevInfo);
  dprint.addIntItem("getCmds", cmdGetCmds);
  dprint.addIntItem("getRspCodes", cmdGetRspCodes);
  dprint.addIntItem("setArduinoSerialNumber", cmdSetSerialNumber);

  dprint.addIntItem("setRelays", cmdSetRelays);
  dprint.addIntItem("setRelayOn", cmdSetRelayOn);
  dprint.addIntItem("setRelayOff", cmdSetRelayOff);
  dprint.addIntItem("setAllRelaysOn", cmdSetAllRelaysOn);
  dprint.addIntItem("setAllRelaysOff", cmdSetAllRelaysOff);

  dprint.addIntItem("setBoardRelays", cmdSetBoardRelays);
  dprint.addIntItem("setBoardRelayOn", cmdSetBoardRelayOn);
  dprint.addIntItem("setBoardRelayOff", cmdSetBoardRelayOff);
  dprint.addIntItem("setAllBoardRelaysOn", cmdSetAllBoardRelaysOn);
  dprint.addIntItem("setAllBoardRelaysOff", cmdSetAllBoardRelaysOff);

  dprint.addIntItem("toggleRelay", cmdToggleRelay);

  // DEVELOPMENT
  dprint.addIntItem("cmdDebug", cmdDebug);
}

void MessageHandler::handleGetDevInfo() {
  dprint.addIntItem("status", rspSuccess);
  dprint.addIntItem("model_number",  constants::modelNumber);
  dprint.addIntItem("serial_number", savedVariables.getSerialNumber());
  dprint.addIntItem("firmware_number", constants::firmwareNumber);
  dprint.addIntItem("relay_count",  constants::relayCount);
  dprint.addIntItem("board_count",  constants::boardCount);
  dprint.addIntItem("board_relay_count",  constants::boardRelayCount);
}

bool MessageHandler::checkNumberOfArgs(int num) {
  bool flag = true;
  if (numberOfItems() != num) {
    dprint.addIntItem("status", rspError);
    dprint.addStrItem("err_msg", "incorrect number of arguments");
    flag = false;
  }
  return flag;
}

bool MessageHandler::checkSerialNumberArg(int serial_number) {
  bool flag = true;
  if ((serial_number<constants::serialNumberMin) || (constants::serialNumberMax<serial_number)) {
    dprint.addIntItem("status", rspError);
    dprint.addStrItem("err_msg", "serial number argument out of range");
    flag = false;
  }
  return flag;
}

void MessageHandler::systemCmdRsp(bool flag) {
  if (flag) {
    dprint.addIntItem("status", rspSuccess);
  }
  else {
    dprint.addIntItem("status", rspError);
    dprint.addStrItem("err_msg", systemState.errMsg);
  }
}

void MessageHandler::handleGetRspCodes() {
  dprint.addIntItem("status", rspSuccess);
  dprint.addIntItem("rsp_success",rspSuccess);
  dprint.addIntItem("rsp_error", rspError);
}

void MessageHandler::handleSetSerialNumber() {
  if (!checkNumberOfArgs(2)) {return;}
  int serialNumber = readInt(1);
  if (checkSerialNumberArg(serialNumber)) {
    systemCmdRsp(savedVariables.setSerialNumber(serialNumber));
  }
}

bool MessageHandler::checkRelayArg(int relay) {
  bool flag = true;
  if ((relay<0) || (constants::relayCount<=relay)) {
    dprint.addIntItem("status", rspError);
    dprint.addStrItem("err_msg", "relay argument out of range");
    flag = false;
  }
  return flag;
}

bool MessageHandler::checkBoardArg(int board) {
  bool flag = true;
  if ((board<0) || (constants::boardCount<=board)) {
    dprint.addIntItem("status", rspError);
    dprint.addStrItem("err_msg", "board argument out of range");
    flag = false;
  }
  return flag;
}

bool MessageHandler::checkBoardRelayArg(int board_relay) {
  bool flag = true;
  if ((board_relay<0) || (constants::boardRelayCount<=board_relay)) {
    dprint.addIntItem("status", rspError);
    dprint.addStrItem("err_msg", "board_relay argument out of range");
    flag = false;
  }
  return flag;
}

void MessageHandler::handleSetRelays() {
  if (!checkNumberOfArgs(2)) {return;}
  uint32_t relays = (uint32_t)readLong(1);
  systemCmdRsp(systemState.setRelays(relays));
}

void MessageHandler::handleSetRelayOn() {
  if (!checkNumberOfArgs(2)) {return;}
  int relay = readInt(1);
  if (checkRelayArg(relay)) {
    systemCmdRsp(systemState.setRelayOn(relay));
  }
}

void MessageHandler::handleSetRelayOff() {
  if (!checkNumberOfArgs(2)) {return;}
  int relay = readInt(1);
  if (checkRelayArg(relay)) {
    systemCmdRsp(systemState.setRelayOff(relay));
  }
}

void MessageHandler::handleSetAllRelaysOn() {
  systemCmdRsp(systemState.setAllRelaysOn());
}

void MessageHandler::handleSetAllRelaysOff() {
  systemCmdRsp(systemState.setAllRelaysOff());
}

void MessageHandler::handleSetBoardRelays() {
  if (!checkNumberOfArgs(3)) {return;}
  int board = readInt(1);
  uint32_t board_relays = (uint32_t)readLong(2);
  if (checkBoardArg(board)) {
    systemCmdRsp(systemState.setBoardRelays(board,board_relays));
  }
}

void MessageHandler::handleSetBoardRelayOn() {
  if (!checkNumberOfArgs(3)) {return;}
  int board = readInt(1);
  int board_relay = readInt(2);
  if ((checkBoardArg(board)) && (checkBoardRelayArg(board_relay))) {
    systemCmdRsp(systemState.setBoardRelayOn(board,board_relay));
  }
}

void MessageHandler::handleSetBoardRelayOff() {
  if (!checkNumberOfArgs(3)) {return;}
  int board = readInt(1);
  int board_relay = readInt(2);
  if ((checkBoardArg(board)) && (checkBoardRelayArg(board_relay))) {
    systemCmdRsp(systemState.setBoardRelayOff(board,board_relay));
  }
}

void MessageHandler::handleSetAllBoardRelaysOn() {
  if (!checkNumberOfArgs(2)) {return;}
  int board = readInt(1);
  if (checkBoardArg(board)) {
    systemCmdRsp(systemState.setAllBoardRelaysOn(board));
  }
}

void MessageHandler::handleSetAllBoardRelaysOff() {
  if (!checkNumberOfArgs(2)) {return;}
  int board = readInt(1);
  if (checkBoardArg(board)) {
    systemCmdRsp(systemState.setAllBoardRelaysOff(board));
  }
}

void MessageHandler::handleToggleRelay() {
  if (!checkNumberOfArgs(2)) {return;}
  int relay = readInt(1);
  if (checkRelayArg(relay)) {
    systemCmdRsp(systemState.toggleRelay(relay));
  }
}

// -------------------------------------------------


void MessageHandler::handleDebug() {
  char name[20];
  dprint.addIntItem("status", rspSuccess);
}


MessageHandler messageHandler;
