#include <GLFW/glfw3.h>

#include <cmath>
#include <cstdlib>
#include <ctime>
#include <vector>

struct Particle {
  float x;
  float y;

  float vx;
  float vy;
};

int main() {
  if (!glfwInit())
    return -1;

  GLFWwindow* window = glfwCreateWindow(
      1920, 1080,
      "Simple Black Hole",
      nullptr,
      nullptr);

  if (!window) {
    glfwTerminate();
    return -1;
  }

  glfwMakeContextCurrent(window);

  // We use a simple 2D coordinate system:
  //
  //              +Y
  //               |
  //               |
  //       -X -----+----- +X
  //               |
  //               |
  //              -Y

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  glOrtho(
      -4.0, 4.0,
      -3.0, 3.0,
      -1.0, 1.0);

  glMatrixMode(GL_MODELVIEW);

  // Random number generator
  std::srand(static_cast<unsigned>(std::time(nullptr)));

  std::vector<Particle> particles;

  // Create particles in an accretion disk.
  for (int i = 0; i < 1000; i++) {
    // Random distance from black hole.
    float angle = (std::rand() / (float)RAND_MAX) * 2.0f * 3.14159265f;

    float radius =
        1.0f +
        (std::rand() / (float)RAND_MAX) * 2.0f;

    Particle p;

    // Position
    p.x = std::cos(angle) * radius;
    p.y = std::sin(angle) * radius;

    // Circular orbital velocity.
    //
    // v = sqrt(GM / r)
    //
    // We simplify GM to 1.
    float speed = std::sqrt(1.0f / radius);

    // Tangent to the orbit.
    p.vx = -std::sin(angle) * speed;
    p.vy = std::cos(angle) * speed;

    particles.push_back(p);
  }

  double previousTime = glfwGetTime();

  while (!glfwWindowShouldClose(window)) {
    double currentTime = glfwGetTime();

    float dt = static_cast<float>(
        currentTime - previousTime);

    previousTime = currentTime;

    // Don't allow a huge timestep.
    if (dt > 0.02f)
      dt = 0.02f;

    // -----------------------------
    // SIMULATION
    // -----------------------------

    for (auto& p : particles) {
      float dx = -p.x;
      float dy = -p.y;

      float distanceSquared =
          dx * dx +
          dy * dy;

      float distance =
          std::sqrt(distanceSquared);

      // Simplified event horizon.
      if (distance < 0.15f) {
        // Put the particle somewhere
        // back in the disk.
        float angle =
            (std::rand() / (float)RAND_MAX) * 2.0f * 3.14159265f;

        float radius =
            1.5f +
            (std::rand() / (float)RAND_MAX) * 1.5f;

        p.x = std::cos(angle) * radius;
        p.y = std::sin(angle) * radius;

        float speed = std::sqrt(1.0f / radius);

        p.vx = -std::sin(angle) * speed;
        p.vy = std::cos(angle) * speed;

        continue;
      }

      // Gravitational acceleration.
      //
      // a = GM / r²
      //
      // GM = 1 in our simplified simulation.

      float acceleration =
          1.0f / distanceSquared;

      // Normalize direction toward black hole.
      float dirX = dx / distance;
      float dirY = dy / distance;

      // Apply acceleration to velocity.
      p.vx += dirX * acceleration * dt;
      p.vy += dirY * acceleration * dt;

      // Move particle.
      p.x += p.vx * dt;
      p.y += p.vy * dt;
    }

    // -----------------------------
    // RENDER
    // -----------------------------

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glLoadIdentity();

    // Draw the black hole.

    glPointSize(30.0f);

    glBegin(GL_POINTS);

    glColor3f(0.0f, 0.0f, 0.0f);
    glVertex2f(0.0f, 0.0f);

    glEnd();

    // Draw particles.

    glPointSize(2.0f);

    glBegin(GL_POINTS);

    for (const auto& p : particles) {
      // Distance from black hole.
      float distance =
          std::sqrt(
              p.x * p.x +
              p.y * p.y);

      // Make inner particles brighter.
      float brightness =
          1.0f / (distance * 0.5f);

      if (brightness > 1.0f)
        brightness = 1.0f;

      glColor3f(
          brightness,
          brightness * 0.5f,
          0.1f);

      glVertex2f(p.x, p.y);
    }

    glEnd();

    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  glfwDestroyWindow(window);
  glfwTerminate();

  return 0;
}
