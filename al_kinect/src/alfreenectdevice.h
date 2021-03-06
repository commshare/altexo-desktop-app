#ifndef ALFREENECTDEVICE_H
#define ALFREENECTDEVICE_H

#include "libfreenect.hpp"
#include <cmath>
#include <iostream>
#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include <vector>

#define FLT_EPSILON 1.19209290E-07F

class Mutex {
public:
  Mutex() { pthread_mutex_init(&m_mutex, NULL); }
  void lock() { pthread_mutex_lock(&m_mutex); }
  void unlock() { pthread_mutex_unlock(&m_mutex); }

  class ScopedLock {
    Mutex &_mutex;

  public:
    ScopedLock(Mutex &mutex) : _mutex(mutex) { _mutex.lock(); }
    ~ScopedLock() { _mutex.unlock(); }
  };

private:
  pthread_mutex_t m_mutex;
};

class ALFreenectDevice : public Freenect::FreenectDevice {
public:
  ALFreenectDevice(freenect_context *_ctx, int _index);
  ~ALFreenectDevice() {}

  // Do not call directly even in child
  void VideoCallback(void *_rgb, uint32_t timestamp);
  // Do not call directly even in child
  void DepthCallback(void *_depth, uint32_t timestamp);

  std::vector<uint8_t> getRGB();
  std::vector<uint16_t> getDepth();

private:
  std::vector<uint16_t> m_bufferDepth;
  std::vector<uint8_t> m_bufferVideo;

  Mutex m_rgbMutex;
  Mutex m_depthMutex;

public:
  bool m_newRgbFrame;
  bool m_newDepthFrame;
};

#endif // ALFREENECTDEVICE_H
