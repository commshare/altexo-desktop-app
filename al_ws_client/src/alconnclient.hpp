#ifndef ALCONNCLIENT_H
#define ALCONNCLIENT_H

#include <cpr/cpr.h>
#include <iostream>
#include <vector>

#include "AL_CB/al_ws_cb.hpp"
#include "alwsclient.hpp"
#include "boost/thread.hpp"

class AlConnClient : public AlWsCb {
public:
  AlConnClient(AlWsCb *alWsCb);
  ~AlConnClient();

  // AlWsCb
  void onMessageCb(std::vector<char> peerId, std::vector<char> msg) {}
  void onWsMessageCb(std::vector<char> msg) {}

  enum HTTP_RESPONSE_TYPE {
    HTTP_LOGIN = 1,
    HTTP_ME,
    HTTP_INIT_WS_CONN,
  };

  void login(std::string login, std::string password);
  void sendMessageToPeer(std::vector<char> peerId, std::vector<char> msg);

  AlWsClient *getWsClientRef() { return &m_wsCl; };

private:
  void handleHttpResponse(cpr::Response r, int responseType);
  // void threadMain();

  std::string m_token;
  std::string m_wssLink;
  std::string m_peerId;

  AlWsClient m_wsCl;
  // boost::thread m_internalThread;
  AlWsCb *m_alWsCb;
};

#endif // ALCONNCLIENT_H
