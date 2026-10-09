// // here I'll use something else instead of win32 API to manage window creation, like GLFW
// #include <GLFW/glfw3.h>

// #include <chrono>
// int main(void) {
//   if (!glfwInit())
//     return -1;

//   GLFWwindow* window = glfwCreateWindow(640, 400, "What a beautiful window!", nullptr, nullptr);  // create the window
//   if (!window) {
//     glfwTerminate();
//     return -1;
//   }
//   glfwMakeContextCurrent(window);  // make the window the current context for OpenGL rendering
//   while (!glfwWindowShouldClose(window)) {
//     // clear the previous frame:
//     glClear(GL_COLOR_BUFFER_BIT);
//     // draw rectangle:
//     glBegin(GL_QUADS);

//     glVertex2f(-0.5f, -0.5f);
//     glVertex2f(0.5f, -0.5f);
//     glVertex2f(0.5f, 0.5f);
//     glVertex2f(-0.5f, 0.5f);

//     glEnd();

//     glfwSwapBuffers(window);  // swap the front and the back buffers to display the rendered content
//     glfwPollEvents();         // poll for and process events, such as keyboard input or window resizing
//   }
//   glfwDestroyWindow(window);
//   glfwTerminate();
//   return 0;
// }

//------------------------------------------------------3d cube example-------------------------------------------------------------
#include <GLFW/glfw3.h>

#include <cmath>
int main(void) {
  if (!glfwInit())
    return -1;
  GLFWwindow* window = glfwCreateWindow(1920, 1080, "3D Cube Example", nullptr, nullptr);
  if (!window) {
    glfwTerminate();
    return -1;
  }

  glfwMakeContextCurrent(window);
  glEnable(GL_DEPTH_TEST);  // enable depth testing
  // perspective:
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  float aspect = 1920.f / 1080.f;
  float f = 1.0f / tanf(45.0f * 3.14159265f / 360.0f);  // fov = 45 deg, near 0.1 ,far = 100,
  float projection[16] = {
      f / aspect,
      0,
      0,
      0,
      0,
      f,
      0,
      0,
      0,
      0,
      (100.0f + 0.1f) / (0.1f - 100.0f),
      -1,
      0,
      0,
      (2.0f * 100.0f * 0.1f) / (0.1f - 100.0f), 0};
  glLoadMatrixf(projection);
  glMatrixMode(GL_MODELVIEW);
  while (!glfwWindowShouldClose(window)) {
    // clear both color and depth buffers:
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    // move the cube away from the camera:
    glTranslatef(0.0f, 0.0f, -5.0f);
    // rotate it:
    float angle = static_cast<float>(glfwGetTime()) * 50.0f;
    glRotatef(angle, 1.0f, 1.0f, 0.0f);

    glBegin(GL_QUADS);
    // front face:
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex3f(-1.0f, -1.0f, 1.0f);
    glVertex3f(1.0f, -1.0f, 1.0f);
    glVertex3f(1.0f, 1.0f, 1.0f);
    glVertex3f(-1.0f, 1.0f, 1.0f);

    // Back face
    glColor3f(0.0f, 1.0f, 0.0f);
    glVertex3f(-1.0f, -1.0f, -1.0f);
    glVertex3f(-1.0f, 1.0f, -1.0f);
    glVertex3f(1.0f, 1.0f, -1.0f);
    glVertex3f(1.0f, -1.0f, -1.0f);

    // Left face
    glColor3f(0.0f, 0.0f, 1.0f);
    glVertex3f(-1.0f, -1.0f, -1.0f);
    glVertex3f(-1.0f, -1.0f, 1.0f);
    glVertex3f(-1.0f, 1.0f, 1.0f);
    glVertex3f(-1.0f, 1.0f, -1.0f);

    // Right face
    glColor3f(1.0f, 1.0f, 0.0f);
    glVertex3f(1.0f, -1.0f, -1.0f);
    glVertex3f(1.0f, 1.0f, -1.0f);
    glVertex3f(1.0f, 1.0f, 1.0f);
    glVertex3f(1.0f, -1.0f, 1.0f);

    // Top face
    glColor3f(1.0f, 0.0f, 1.0f);
    glVertex3f(-1.0f, 1.0f, -1.0f);
    glVertex3f(-1.0f, 1.0f, 1.0f);
    glVertex3f(1.0f, 1.0f, 1.0f);
    glVertex3f(1.0f, 1.0f, -1.0f);

    // Bottom face
    glColor3f(0.0f, 1.0f, 1.0f);
    glVertex3f(-1.0f, -1.0f, -1.0f);
    glVertex3f(1.0f, -1.0f, -1.0f);
    glVertex3f(1.0f, -1.0f, 1.0f);
    glVertex3f(-1.0f, -1.0f, 1.0f);

    glEnd();
    glfwSwapBuffers(window);
    glfwPollEvents();
  }
  glfwDestroyWindow(window);
  glfwTerminate();
  return 0;
}