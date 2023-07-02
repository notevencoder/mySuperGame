#include "DebugRenderer.h"
#include "Game.h"


void DebugRenderer::DrawSolidPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color)
{
    
    b2Color cc;
    cc.r = 255;
    cc.g = 255;
    cc.b = 255;
    SDL_SetRenderDrawColor(ren,cc.r,cc.g,cc.b, 1);
    SDL_FPoint* points = new SDL_FPoint[vertexCount * 2];
   
    //fill in vertex positions as directed by Box2D
    for (int i = 0; i < vertexCount; i++) {
        points[i].x   = vertices[i].x - Game::getInstance()->getCamera()->x;
        points[i].y   = vertices[i].y - Game::getInstance()->getCamera()->y;
    }
    points[vertexCount] = points[0];
    SDL_RenderDrawLinesF(ren, points, vertexCount + 1);



    //draw lines
}