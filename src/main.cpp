#include "application.h"
#include "config.h"

int main() {
    Application app({ config::WINDOW_WIDTH, config::WINDOW_HEIGHT }, "Pathfinding Visualiser");
    app.run();
    return 0;
}