#ifndef ALSDKPLUGIN_H
#define ALSDKPLUGIN_H

#include "AL_API/sdk_api.hpp"
#include "AL_CB/al_sdk_cb.hpp"
#include "alcallback.h"
#include "allogger.hpp"
#include "altextmessage.hpp"

#ifdef _WIN32
#include "boost/dll/alias.hpp"
#endif

#include "boost/make_shared.hpp"
#include "boost/thread.hpp"
#include <boost/config.hpp>
#include <boost/signals2/signal.hpp>
#include <queue>
#include <string>

class AlManager;

class AlSdkPlugin : public AlSdkAPI, public AlCallback {
public:
  AlSdkPlugin();
  ~AlSdkPlugin();

#ifdef _WIN32
  // Factory method
  static boost::shared_ptr<AlSdkAPI> create() {
    return boost::make_shared<AlSdkPlugin>();
  }
#endif

  void init(AlSDKCb *alSdkCb);
  void init2();
  void initializePeerConnection();
  void setRemoteSdp(const char *cSdp);
  void setRemoteIceCandidate(std::vector<char> candidate);
  void setImageData(std::vector<unsigned char> imageBytes, int width,
                    int height);
  void updateResolution(int widht, int height);

  void setDesiredDataSource(int dataSource);
  void threadMain();

  void onSdpCb(const std::string &message) {
    AlTextMessage msg(message);
    m_sdkCb->onLocalSdpCb(msg);
  }

  void onCandidateCb(const std::string &message) {
    AlTextMessage msg(message);
    m_sdkCb->onLocalIceCandidateCb(msg);
  }

  // void sendHangUpCb(std::string peer_id) {
  //   if (m_debug) {
  //     std::cout << "sendHangUpCb" << std::endl;
  //   }
  // }
  //
  // void dequeueMessagesFromPeerCb() {
  //   if (m_debug) {
  //     std::cout << "dequeueMessagesFromPeerCb" << std::endl;
  //   }
  // }
  void stopLocalRendererCb() {
    if (m_debug) {
      std::cout << "stopLocalRendererCb" << std::endl;
    }
  }
  void stopRemoteRendererCb() {
    if (m_debug) {
      std::cout << "stopRemoteRendererCb" << std::endl;
    }
  }
  // void ensureStreamingUICb() {
  //   if (m_debug) {
  //     std::cout << "ensureStreamingUICb" << std::endl;
  //   }
  // }
  // void queueUIThreadCallbackCb(int msg_id, void *data) {
  //   if (m_debug) {
  //     std::cout << "queueUIThreadCallbackCb" << std::endl;
  //   }
  // }
  // void switchToPeerListCb(const Peers &peers) {
  //   if (m_debug) {
  //     std::cout << "switchToPeerListCb" << std::endl;
  //   }
  // }
  // void onDisconnectedCb() {
  //   if (m_debug) {
  //     std::cout << "onDisconnectedCb" << std::endl;
  //   }
  // }
  // void processUiEventsCb() {
  //   // if (m_debug) {
  //   // std::cout << "processUiEventsCb" << std::endl;
  //   // }
  // }
  // void SwitchToStreamingUI() {} // ????
  void onDevicesListChangedCb(std::vector<alMsg> deviceNames) {
    if (m_debug) {
      std::cout << "onDevicesListChangedCb" << std::endl;
      std::cout << deviceNames.size() << std::endl;
    }
    for (int i = 0; i < deviceNames.size(); i++) {
      AlTextMessage msg(deviceNames[i]);
      std::string msgStr = msg.toString();
      char *cstr = new char[msgStr.length() + 1];
      cstr[msgStr.length()] = '\n';
      std::strcpy(cstr, msgStr.c_str());
      // m_sdkCb->onNewCaptureDeciceCb(cstr);
      delete[] cstr;
    }
  }

  void updateFrameCb(const uint8_t *image, int width, int height);
  void updateLocalFrameCb(const uint8_t *image, int width, int height);
  void setDesiredVideDeviceName(const char *deviceName);

  //  TODO move to AlManager
  std::string getVideoDeviceName() {
    if (m_debug) {
      std::cout << "1111111111111111111111111111" << std::endl;
      std::cout << m_videoDeviceName << std::endl;
    }
    return m_videoDeviceName;
  }

  // getters
  bool ifNewMessage() {
    boost::lock_guard<boost::mutex> guard(m_mtx);
    return !m_messageQueue.empty();
  }
  std::pair<int, std::vector<char>> degueueMessage() {
    boost::lock_guard<boost::mutex> guard(m_mtx);
    std::pair<int, std::vector<char>> result = m_messageQueue.front();
    m_messageQueue.pop();
    return result;
  }

  std::vector<unsigned char> *getFrameRef() { return &m_imageBytes; }

  int getWidth() {
    boost::lock_guard<boost::mutex> guard(m_mtx);
    return WIDTH;
  }
  int getHeight() {
    boost::lock_guard<boost::mutex> guard(m_mtx);
    return HEIGHT;
  }

private:
  // AlSdk *m_sdk;
  AlManager *m_manager;
  AlSDKCb *m_sdkCb;
  boost::thread *m_internalThread;

  // signals
  boost::signals2::signal<void()> initPeerConnectionSignal;

  bool m_debug;

  boost::mutex m_mtx;
  std::vector<unsigned char> m_imageBytes;

  std::queue<std::pair<int, std::vector<char>>> m_messageQueue;

  std::string m_videoDeviceName;

  int WIDTH;
  int HEIGHT;
};

#ifdef _WIN32
BOOST_DLL_ALIAS(AlSdkPlugin::create, // <-- this function is exported with...
                create_plugin        // <-- ...this alias name
                )
#else
extern "C" BOOST_SYMBOL_EXPORT AlSdkPlugin plugin;
AlSdkPlugin plugin;
#endif

#endif // ALSDKPLUGIN_H
