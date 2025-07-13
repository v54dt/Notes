```
It's just a quick notes of my finance api design.

// Connection
void Connect();
void Disconnect();
bool IsConnected();
ConnectionState GetConnectionState();
void SetConnectionStateCallback(ConnectionStateCallback callback);


// Authentication
bool Login();
bool Logout();


// Orders
void PlaceOrder();
void ModifyOrder();
void CancelOrder();

void SetDealCallback();


// Accounts
void GetAccountSummary();
void GetPosition();
void EstimateTodaySettlement();
void GetRecentThreeDaySettlementAmounts();
void GetTradeHistory();
void GetUnrealizedProfitLoss();
void GetRealizedProfitLoss();
void GetMaintenanceRate();
void GetTodayTradeFills();


// Configuration
void SetRequestTimeout(std::chrono::milliseconds timeout);
void EnableAutoReconnect(bool enabled);

```