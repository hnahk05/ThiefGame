#include "Thief.h"
#include "TextureManager.h"
#include "SDL.h"

Thief::Thief(Properties* props): Character(props){
    m_Row = 1;
    m_FrameCount = 2;
    m_AnimSpeed = 80;
}

void Thief::Draw(){
    TextureManager::GetInstance()->DrawFrame(m_TextureID, m_Transform->X, m_Transform->Y, m_Width, m_Height, m_Row, m_Frame);
}

void Thief::Update(float dt){
    m_Frame = (SDL_GetTicks()/m_AnimSpeed)%m_FrameCount;
}

void Thief::Clean(){
     TextureManager::GetInstance()->Clean();
}
