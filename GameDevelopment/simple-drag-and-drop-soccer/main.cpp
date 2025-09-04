#include <cstdio>
#include <iostream>
#include <SDL.h>
#include <math.h>
#include <ostream>
#define swidth 800
#define sheight 800

typedef struct {
    int x, y;
    int radius;
    int sides;
    int is_dragging;
    int offset_x, offset_y;
} Circle;

void draw_circle(SDL_Renderer* renderer, Circle* circle) {
    const double pi = 3.14159;
    double delta = 2 * pi / circle->sides;

    double angle = 0;
    int x0 = circle->x + (int)(circle->radius * cos(angle));
    int y0 = circle->y + (int)(circle->radius * sin(angle));
    int x_prev = x0;
    int y_prev = y0;

    for (int i = 1; i < circle->sides; ++i) {
        angle = i * delta;
        int x = circle->x + (int)(circle->radius * cos(angle));
        int y = circle->y + (int)(circle->radius * sin(angle));
        SDL_RenderDrawLine(renderer, x_prev, y_prev, x, y);
        x_prev = x;
        y_prev = y;
    }

    SDL_RenderDrawLine(renderer, x_prev, y_prev, x0, y0);
}

int is_point_in_circle(int x, int y, Circle* circle) {
    double d = sqrt(pow(circle->x - x, 2) + pow(circle->y - y, 2));
    if (d <= circle->radius) {
        return 1;
    }
    return 0;
}

void draw_field(SDL_Renderer* renderer) {
    //faixas do campo
    for (int x = 0; x < swidth; x = x + 160) {
        SDL_SetRenderDrawColor(renderer, 64, 166, 41, 255);
        SDL_Rect green = { x, 0, 80, 800 };
        SDL_RenderFillRect(renderer, &green);
        SDL_SetRenderDrawColor(renderer, 35, 124, 37, 255);
        SDL_Rect darker_green = { x + 80, 0, 80, 800 };
        SDL_RenderFillRect(renderer, &darker_green);
    }
    //delimitações
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_Rect border = { 20, 80, 10, 740 };
    SDL_RenderFillRect(renderer, &border);
    border = { 770, 80, 10, 740 };
    SDL_RenderFillRect(renderer, &border);
    border = { 20, 80, 760, 10 };
    SDL_RenderFillRect(renderer, &border);
    border = { 20, 780, 760, 10 };
    SDL_RenderFillRect(renderer, &border);

    //gol
    border = { 280, 5, 10, 75 };
    SDL_RenderFillRect(renderer, &border);
    border = { 280, 5, 240, 10 };
    SDL_RenderFillRect(renderer, &border);
    border = { 520, 5, 10, 75 };
    SDL_RenderFillRect(renderer, &border);

    // pequena area
    border = { 230, 90, 10, 200 };
    SDL_RenderFillRect(renderer, &border);
    border = { 240, 290, 320, 10 };
    SDL_RenderFillRect(renderer, &border);
    border = { 560, 90, 10, 200 };
    SDL_RenderFillRect(renderer, &border);

    // grande area
    border = { 150, 90, 10, 300 };
    SDL_RenderFillRect(renderer, &border);
    border = { 160, 390, 480, 10 };
    SDL_RenderFillRect(renderer, &border);
    border = { 640, 90, 10, 300 };
    SDL_RenderFillRect(renderer, &border);

}

void handle_mouse_events(SDL_Event* e, Circle* circle) {
    int mouseX, mouseY;
    SDL_GetMouseState(&mouseX, &mouseY);

    switch (e->type) {
        case SDL_MOUSEBUTTONDOWN:
            if (e->button.button == SDL_BUTTON_RIGHT && is_point_in_circle(mouseX, mouseY, circle)) {
                circle->is_dragging = 1;
                circle->offset_x = mouseX - circle->x;
                circle->offset_y = mouseY - circle->y;
            }
            break;
        case SDL_MOUSEMOTION:
            if (circle->is_dragging) {
                circle->x = mouseX - circle->offset_x;
                circle->y = mouseY - circle->offset_y;
            }
            break;
        case SDL_MOUSEBUTTONUP:
            if (e->button.button == SDL_BUTTON_RIGHT) {
                circle->is_dragging = 0;
            }
            break;
    }

}

int main(int argc, char* args[]) {

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        SDL_Log("SDL_Init: %s\n", SDL_GetError());
        return -1;
    }

    SDL_Window* window = SDL_CreateWindow(
        "Incredible Soccer",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        swidth,
        sheight,
        SDL_WINDOW_SHOWN
        );
    if (window == nullptr) {
        SDL_Log("SDL_Window_Create: %s\n", SDL_GetError());
        return -1;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(
        window,
        -1,
        SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
        );
    if (renderer == nullptr) {
        SDL_Log("SDL_Renderer_Create: %s\n", SDL_GetError());
        return -1;
    }

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);
    SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    Circle circle = {400, 600, 30, 64,0,0,0};
    draw_circle(renderer, &circle);

    draw_field(renderer);

    SDL_RenderPresent(renderer);

    // loop principal
    bool running = true;
    while (running) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            }else {
                handle_mouse_events(&event, &circle);
                draw_field(renderer);
                SDL_RenderPresent(renderer);
                SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
                draw_circle(renderer, &circle);
                SDL_RenderPresent(renderer);
            }
        }
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
