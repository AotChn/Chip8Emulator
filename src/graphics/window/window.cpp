#include "window.h"

namespace acGraphics{

Window::Window() {
    window.create(sf::VideoMode(SCREEN_WIDTH,SCREEN_HEIGHT), WINDOW_NAME);
    window.setFramerateLimit(60);
}

void Window::run(){
    while (window.isOpen()) {
        process_events();
        update();
        render();
    }
}

void Window::render() {
    window.clear(BACKGROUND_DARK);
    draw();
    window.display();
}

void Window::draw() {
    Notify(window, Draw);
}

void Window::update() {

}

void Window::process_events(){
    sf::Event event;
    int key = event.key.code;
    if (window.pollEvent(event)) {
        switch(event.type) {
        case sf::Event::Closed:
            window.close();
            break;

        default:
            Notify(window, event.type);
            break;
        }
    }
    else Notify(window, CUSTOM_SFEV::Idle);  
}

void Window::close() {
    Notify(window, 0);
}

void Window::close(bool t) {
    if (t) {
        close();
    }
}
};