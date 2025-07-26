#ifndef EXECTYPE_H_
#define EXECTYPE_H_

#include <unordered_map>

namespace fix {

// ref: https://fiximate.fixtrading.org/legacy/en/FIX.5.0/tag150.html

enum FIXExecType {
  New,
  DoneForDay,
  Canceled,
  Replaced,
  PendingCancel,
  Stopped,
  Rejected,
  Suspended,
  PendingNew,
  Calculated,
  Expired,
  Restated,
  PendingReplace,
  Trade,
  TradeCorrect,
  TradeCancel,
  OrderStatus,
  TradeInAClearingHold,
  TradeHasBeenReleasedToClearing,
  TriggeredOrActivatedBySystem
};

static std::unordered_map<std::string, enum FIXExecType> FIXExecTypeMap{
    {"0", FIXExecType::New},
    {"3", FIXExecType::DoneForDay},
    {"4", FIXExecType::Canceled},
    {"5", FIXExecType::Replaced},
    {"6", FIXExecType::PendingCancel},
    {"7", FIXExecType::Stopped},
    {"8", FIXExecType::Rejected},
    {"9", FIXExecType::Suspended},
    {"A", FIXExecType::PendingNew},
    {"B", FIXExecType::Calculated},
    {"C", FIXExecType::Expired},
    {"D", FIXExecType::Restated},
    {"E", FIXExecType::PendingReplace},
    {"F", FIXExecType::Trade},
    {"G", FIXExecType::TradeCorrect},
    {"H", FIXExecType::TradeCancel},
    {"I", FIXExecType::OrderStatus},
    {"J", FIXExecType::TradeInAClearingHold},
    {"K", FIXExecType::TradeHasBeenReleasedToClearing},
    {"L", FIXExecType::TriggeredOrActivatedBySystem}};

}  // namespace fix

#endif
