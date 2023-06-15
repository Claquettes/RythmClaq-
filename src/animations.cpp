#include "animations.h"
#include "pannel.h" 
#include "main_menu.h"

void Animations::movePannel(Pannel& pannel, int targetX, int targetY, int duration, SDL_Renderer* renderer) {
    int startX = pannel.getX();
    int startY = pannel.getY();
    int totalFrames = duration / 16; 
    int frameCount = 0;

    for (int i = 0; i < totalFrames; i++) {
        float progress = static_cast<float>(i) / totalFrames;
        int currentX = startX + static_cast<int>((targetX - startX) * progress);
        int currentY = startY + static_cast<int>((targetY - startY) * progress);

        //we render the animation
        pannel.render(renderer);
        SDL_RenderPresent(renderer);

        pannel.setPosition(currentX, currentY);
        SDL_Delay(16); // Delay for 16ms (60 FPS)
    }

    pannel.setPosition(targetX, targetY);
}

void Animations::resizePannel(Pannel& pannel, int targetWidth, int targetHeight, int duration, SDL_Renderer* renderer) {
    int startWidth = pannel.getWidth();
    int startHeight = pannel.getHeight();
    int totalFrames = duration / 16; // Assuming 60 FPS (16ms per frame)
    int frameCount = 0;

    for (int i = 0; i < totalFrames; i++) {
        float progress = static_cast<float>(i) / totalFrames;
        int currentWidth = startWidth + static_cast<int>((targetWidth - startWidth) * progress);
        int currentHeight = startHeight + static_cast<int>((targetHeight - startHeight) * progress);

        pannel.setWidth(currentWidth);
        pannel.setHeight(currentHeight);

        pannel.render(renderer);
        SDL_RenderPresent(renderer);

        SDL_Delay(16); // Delay for 16ms (60 FPS)
    }

    pannel.setWidth(targetWidth);
    pannel.setHeight(targetHeight);
}

void Animations::changeColor(Pannel& pannel, SDL_Color targetColor, int duration, SDL_Renderer* renderer) {
    SDL_Color startColor = pannel.getColor();
    int totalFrames = duration / 16; 
    int frameCount = 0;

    for (int i = 0; i < totalFrames; i++) {
        float progress = static_cast<float>(i) / totalFrames;
        Uint8 r = static_cast<Uint8>(startColor.r + (targetColor.r - startColor.r) * progress);
        Uint8 g = static_cast<Uint8>(startColor.g + (targetColor.g - startColor.g) * progress);
        Uint8 b = static_cast<Uint8>(startColor.b + (targetColor.b - startColor.b) * progress);

        pannel.setColor({ r, g, b });

        pannel.render(renderer);
        SDL_RenderPresent(renderer);

        SDL_Delay(16); // Delay for 16ms (60 FPS)
    }

    pannel.setColor(targetColor);
}

void Animations::fadeIn(Pannel& pannel, int duration, SDL_Renderer* renderer) {
    SDL_Color startColor = pannel.getColor();
    int totalFrames = duration / 16; 
    int frameCount = 0;

    for (int i = 0; i < totalFrames; i++) {
        float progress = static_cast<float>(i) / totalFrames;
        Uint8 r = static_cast<Uint8>(startColor.r + (255 - startColor.r) * progress);
        Uint8 g = static_cast<Uint8>(startColor.g + (255 - startColor.g) * progress);
        Uint8 b = static_cast<Uint8>(startColor.b + (255 - startColor.b) * progress);

        pannel.setColor({ r, g, b });

        pannel.render(renderer);
        SDL_RenderPresent(renderer);

        SDL_Delay(16); // Delay for 16ms (60 FPS)
    }

    pannel.setColor({ 255, 255, 255 });
}

void Animations::fadeOut(Pannel& pannel, int duration, SDL_Renderer* renderer) {
    SDL_Color startColor = pannel.getColor();
    int totalFrames = duration / 16; 
    int frameCount = 0;

    for (int i = 0; i < totalFrames; i++) {
        float progress = static_cast<float>(i) / totalFrames;
        Uint8 r = static_cast<Uint8>(startColor.r + (0 - startColor.r) * progress);
        Uint8 g = static_cast<Uint8>(startColor.g + (0 - startColor.g) * progress);
        Uint8 b = static_cast<Uint8>(startColor.b + (0 - startColor.b) * progress);

        pannel.setColor({ r, g, b });

        pannel.render(renderer);
        SDL_RenderPresent(renderer);

        SDL_Delay(16); // Delay for 16ms (60 FPS)
    }

    pannel.setColor({ 0, 0, 0 });
}

void Animations::fadeInOut(Pannel& pannel, int duration, SDL_Renderer* renderer) {
    SDL_Color startColor = pannel.getColor();
    int totalFrames = duration / 16; 
    int frameCount = 0;

    for (int i = 0; i < totalFrames; i++) {
        float progress = static_cast<float>(i) / totalFrames;
        Uint8 r = static_cast<Uint8>(startColor.r + (255 - startColor.r) * progress);
        Uint8 g = static_cast<Uint8>(startColor.g + (255 - startColor.g) * progress);
        Uint8 b = static_cast<Uint8>(startColor.b + (255 - startColor.b) * progress);

        pannel.setColor({ r, g, b });

        pannel.render(renderer);
        SDL_RenderPresent(renderer);

        SDL_Delay(16); // Delay for 16ms (60 FPS)
    }

    for (int i = 0; i < totalFrames; i++) {
        float progress = static_cast<float>(i) / totalFrames;
        Uint8 r = static_cast<Uint8>(255 - (255 * progress));
        Uint8 g = static_cast<Uint8>(255 - (255 * progress));
        Uint8 b = static_cast<Uint8>(255 - (255 * progress));

        pannel.setColor({ r, g, b });

        pannel.render(renderer);
        SDL_RenderPresent(renderer);

        SDL_Delay(16); // Delay for 16ms (60 FPS)
    }

    pannel.setColor({ 0, 0, 0 });
}

void Animations::fadeOutIn(Pannel& pannel, int duration, SDL_Renderer* renderer) {
    SDL_Color startColor = pannel.getColor();
    int totalFrames = duration / 16; 
    int frameCount = 0;

    for (int i = 0; i < totalFrames; i++) {
        float progress = static_cast<float>(i) / totalFrames;
        Uint8 r = static_cast<Uint8>(startColor.r + (0 - startColor.r) * progress);
        Uint8 g = static_cast<Uint8>(startColor.g + (0 - startColor.g) * progress);
        Uint8 b = static_cast<Uint8>(startColor.b + (0 - startColor.b) * progress);

        pannel.setColor({ r, g, b });

        pannel.render(renderer);
        SDL_RenderPresent(renderer);

        SDL_Delay(16); // Delay for 16ms (60 FPS)
    }

    for (int i = 0; i < totalFrames; i++) {
        float progress = static_cast<float>(i) / totalFrames;
        Uint8 r = static_cast<Uint8>(0 + (255 * progress));
        Uint8 g = static_cast<Uint8>(0 + (255 * progress));
        Uint8 b = static_cast<Uint8>(0 + (255 * progress));

        pannel.setColor({ r, g, b });

        pannel.render(renderer);
        SDL_RenderPresent(renderer);

        SDL_Delay(16); // Delay for 16ms (60 FPS)
    }

    pannel.setColor({ 255, 255, 255 });
}