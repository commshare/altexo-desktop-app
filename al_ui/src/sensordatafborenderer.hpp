
#ifndef SENSORDATAFBORENDERER_H
#define SENSORDATAFBORENDERER_H

#include "AL_CB/al_sensor_cb.hpp"
#include "GLSLShader.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <vector>

class SensorDataFboRenderer : public AlSensorCb {
public:
  SensorDataFboRenderer();
  ~SensorDataFboRenderer();

  int init();
  void render(int viewWidth, int viewHeigt);

  // sensor cb
  void newFrame(std::vector<uint8_t> rgbFrame,
                std::vector<uint16_t> depthFrame);

private:
  bool m_debug;
  // shader reference
  GLSLShader shader;

  // vertex array and vertex buffer object IDs
  GLuint vaoID;
  GLuint vboVerticesID;
  GLuint vboIndicesID;

  GLuint sensorRGBTexID;
  GLuint sensorDepthTexID;

  // out vertex struct for interleaved attributes
  struct Vertex {
    glm::vec3 position;
    glm::vec3 color;
  };

  // triangle vertices and indices
  Vertex vertices[4];
  GLushort indices[6];

  // projection and modelview matrices
  glm::mat4 MV = glm::mat4(1);
  glm::mat4 P = glm::mat4(1);

  // internal data
  std::vector<uint8_t> m_rgbFrame;
  std::vector<uint16_t> m_depthFrame;
  bool m_newFrame;

  // sensor data resolution
  // this depends from sensor
  const int WIDTH_SENSOR = 640;
  const int HEIGHT_SENSOR = 480;
};

#endif // SENSORDATAFBORENDERER_H
