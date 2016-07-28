#include "hologramrenderer.hpp"

HologramRenderer::HologramRenderer()
    : WIDTH(0), HEIGHT(0), m_outPixel(0), pendingRenderTexResize(false),
      m_debug(true) {}

void HologramRenderer::updateResolution(int width, int height) {
  WIDTH = width;
  HEIGHT = height;
  m_outPixel.resize(WIDTH * HEIGHT * 2 * 3);
  pendingRenderTexResize = true;
}

int HologramRenderer::init() {
  m_newFrame = false;
  // GL_CHECK_ERRORS
  // load the shader
  shader.LoadFromFile(GL_VERTEX_SHADER, "../al_ui/shaders/shader.vert");
  shader.LoadFromFile(GL_FRAGMENT_SHADER, "../al_ui/shaders/shader.frag");
  // compile and link shader
  shader.CreateAndLinkProgram();
  shader.Use();
  // add attributes and uniforms
  shader.AddAttribute("vVertex");
  shader.AddAttribute("vCoord");
  shader.AddUniform("MVP");
  shader.AddUniform("textureMap");
  // pass values of constant uniforms at initialization
  glUniform1i(shader("textureMap"), 3);
  // pass values of constant uniforms at initialization
  shader.UnUse();

  // GL_CHECK_ERRORS

  // vertices[0].coord = glm::vec2(1, 0);
  // vertices[1].coord = glm::vec2(0, 1);
  // vertices[2].coord = glm::vec2(0, 0);
  // vertices[3].coord = glm::vec2(0, 1);

  int index = 0;
  for (int yCoord = 0; yCoord < 240; yCoord++) {
    for (int xCoord = 0; xCoord < 320; xCoord++) {
      vertices[index].position =
          glm::vec2(float(xCoord) / 320 - 0.5, float(yCoord) / 240 - 0.5);
      index++;
    }
  }

  // GL_CHECK_ERRORS

  // setup triangle vao and vbo stuff
  glGenVertexArrays(1, &vaoID);
  glGenBuffers(1, &vboVerticesID);
  glGenBuffers(1, &vboIndicesID);
  GLsizei stride = sizeof(Vertex);

  glBindVertexArray(vaoID);

  glBindBuffer(GL_ARRAY_BUFFER, vboVerticesID);
  // pass triangle verteices to buffer object
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), &vertices[0], GL_STATIC_DRAW);
  // GL_CHECK_ERRORS
  // enable vertex attribute array for position
  glEnableVertexAttribArray(shader["vVertex"]);
  glVertexAttribPointer(shader["vVertex"], 2, GL_FLOAT, GL_FALSE, stride, 0);
  // GL_CHECK_ERRORS
  // enable vertex attribute array for colour
  glEnableVertexAttribArray(shader["vCoord"]);
  glVertexAttribPointer(shader["vCoord"], 2, GL_FLOAT, GL_FALSE, stride,
                        (const GLvoid *)offsetof(Vertex, coord));
  // GL_CHECK_ERRORS
  // pass indices to element array buffer
  // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vboIndicesID);
  // glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), &indices[0],
  //              GL_STATIC_DRAW);
  // GL_CHECK_ERRORS

  // unbinding
  glBindVertexArray(0);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

  // some tex ==============
  glGenTextures(1, &sensorDepthTexID);
  glActiveTexture(GL_TEXTURE3);
  glBindTexture(GL_TEXTURE_2D, sensorDepthTexID);
  // set texture parameters
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
  glBindTexture(GL_TEXTURE_2D, 0);
  // =====================
  initFBO();

  m_sensorDataFboRenderer.init();

  // setup the camera position and target
  cam.SetPosition(glm::vec3(1, 1, 1));
  cam.SetTarget(glm::vec3(0, 0, 0));

  // also rotate the camera for proper orientation
  glm::vec3 look = glm::normalize(cam.GetTarget() - cam.GetPosition());

  float yaw = glm::degrees(float(atan2(look.z, look.x) + M_PI));
  float pitch = glm::degrees(asin(look.y));
  rX = yaw;
  rY = pitch;

  cam.Rotate(rX, rY, 0);

  cout << "Initialization successfull" << endl;
  return 1;
}

void HologramRenderer::render(int viewWidh, int viewHeight) {
  // TODO: move to 'onResize' event
  cam.SetupProjection(45, (GLfloat)viewWidh / viewHeight);

  if (pendingRenderTexResize) {
    pendingRenderTexResize = false;
    resizeRenderTex();
  }

  // ============ FBO ==============
  // enable FBO
  glBindFramebuffer(GL_FRAMEBUFFER, fboID);
  // render to colour attachment 0
  glDrawBuffer(GL_COLOR_ATTACHMENT0);
  // clear the colour and depth buffers
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  // clear the colour and depth buffer
  // ============ ~FBO ==============

  m_sensorDataFboRenderer.render(WIDTH * 2, HEIGHT);

  if (sendingFrames) {
    glReadPixels(0, 0, WIDTH * 2, HEIGHT, GL_RGB, GL_UNSIGNED_BYTE,
                 &(m_outPixel[0]));
    // TODO: NOT SURE IF IT IS OK TO MULTIPLY BY 2
    newFrameSignal(m_outPixel, WIDTH * 2, HEIGHT);
  }

  // ============ FBO ==============
  // unbind the FBO
  glBindFramebuffer(GL_FRAMEBUFFER, 0);
  // restore the default back buffer
  glDrawBuffer(GL_BACK_LEFT);
  // bind the FBO output at the current texture
  glActiveTexture(GL_TEXTURE3);
  glBindTexture(GL_TEXTURE_2D, renderTextureID);
  // ============ ~FBO ==============

  glViewport(0, 0, viewWidh, viewHeight);

  glBindVertexArray(vaoID);
  glBindBuffer(GL_ARRAY_BUFFER, vboVerticesID);
  // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vboIndicesID);

  // bind the shader
  shader.Use();

  // set the camera transformation
  glm::mat4 MV = cam.GetViewMatrix();
  glm::mat4 P = cam.GetProjectionMatrix();

  glm::mat4 MVP = P * MV;
  // if (m_debug) {
  //   std::cout << MV[0][0] << std::endl;
  // }

  // pass the shader uniform
  // glUniformMatrix4fv(shader("MVP"), 1, GL_FALSE, glm::value_ptr(P * MV));
  glUniformMatrix4fv(shader("MVP"), 1, GL_FALSE, glm::value_ptr(MVP));

  // drwa triangle
  glEnable(GL_PROGRAM_POINT_SIZE);
  // glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, 0);
  // glDrawElements(GL_POINTS, 4, GL_FLOAT, 0);
  glDrawArrays(GL_POINTS, 0, 320 * 240);
  // unbind the shader
  shader.UnUse();

  glBindVertexArray(0);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

  // seems to be needed by something, otherwise some artifacts appears
  glActiveTexture(GL_TEXTURE0);
}

// initialize FBO
void HologramRenderer::initFBO() {
  // generate and bind fbo ID
  glGenFramebuffers(1, &fboID);
  glBindFramebuffer(GL_FRAMEBUFFER, fboID);

  // generate and bind render buffer ID
  glGenRenderbuffers(1, &rbID);
  glBindRenderbuffer(GL_RENDERBUFFER, rbID);

  // set the render buffer storage
  glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT32, WIDTH * 2,
                        HEIGHT);

  // generate the offscreen texture
  glGenTextures(1, &renderTextureID);
  glBindTexture(GL_TEXTURE_2D, renderTextureID);

  // set texture parameters
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, WIDTH * 2, HEIGHT, 0, GL_BGRA,
               GL_UNSIGNED_BYTE, NULL);

  // bind the renderTextureID as colour attachment of FBO
  glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D,
                         renderTextureID, 0);
  // set the render buffer as the depth attachment of FBO
  glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT,
                            GL_RENDERBUFFER, rbID);

  // check for frame buffer completeness status
  GLuint status = glCheckFramebufferStatus(GL_FRAMEBUFFER);

  if (status == GL_FRAMEBUFFER_COMPLETE) {
    printf("FBO setup succeededa.\n");
  } else {
    printf("Error in FBO setup.\n");
  }
  // unbind the texture and FBO
  glBindTexture(GL_TEXTURE_2D, 0);
  glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void HologramRenderer::resizeRenderTex() {
  glBindRenderbuffer(GL_RENDERBUFFER, rbID);
  // set the render buffer storage
  glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT32, WIDTH * 2,
                        HEIGHT);
  glBindTexture(GL_TEXTURE_2D, renderTextureID);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, WIDTH * 2, HEIGHT, 0, GL_BGRA,
               GL_UNSIGNED_BYTE, NULL);
}
