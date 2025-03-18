#include <ardelio.h>

int main() {
    GameObject root("Root");

    GameWindow window({1280u, 720u}, "Test", &root);

    window.run();
}