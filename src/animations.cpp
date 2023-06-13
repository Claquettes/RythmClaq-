#include "animations.h"
#include "pannel.h" 

void Animations::movePannel(Pannel& Pannel, int targetX, int targetY, int duration) {

    int startX = Pannel.getX();
    int startY = Pannel.getY();
    int totalFrames = duration / 16; 
    int frameCount = 0;

    for (int i = 0; i < totalFrames; i++) {
        float progress = static_cast<float>(i) / totalFrames;
        int currentX = startX + static_cast<int>((targetX - startX) * progress);
        int currentY = startY + static_cast<int>((targetY - startY) * progress);

        Pannel.setPosition(currentX, currentY);
        SDL_Delay(16); // Delay for 16ms (60 FPS)
    }

    Pannel.setPosition(targetX, targetY);
}

void Animations::resizePannel(Pannel& Pannel, int targetSide, int duration) {
    int startSide = Pannel.getSide();
    int totalFrames = duration / 16; // Assuming 60 FPS (16ms per frame)
    int frameCount = 0;

    for (int i = 0; i < totalFrames; i++) {
        float progress = static_cast<float>(i) / totalFrames;
        int currentSide = startSide + static_cast<int>((targetSide - startSide) * progress);

        Pannel.setSide(currentSide);
        SDL_Delay(16); // Delay for 16ms (60 FPS)
    }

    Pannel.setSide(targetSide);
}

void Animations::changeColor(Pannel& Pannel, SDL_Color targetColor, int duration) {
    SDL_Color startColor = Pannel.getColor();
    int totalFrames = duration / 16; 
    int frameCount = 0;

    for (int i = 0; i < totalFrames; i++) {
        float progress = static_cast<float>(i) / totalFrames;
        Uint8 r = static_cast<Uint8>(startColor.r + (targetColor.r - startColor.r) * progress);
        Uint8 g = static_cast<Uint8>(startColor.g + (targetColor.g - startColor.g) * progress);
        Uint8 b = static_cast<Uint8>(startColor.b + (targetColor.b - startColor.b) * progress);

        Pannel.setColor({ r, g, b });
        SDL_Delay(16); // Delay for 16ms (60 FPS)
    }

    Pannel.setColor(targetColor);
}
