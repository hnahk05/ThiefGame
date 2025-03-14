#ifndef THIEF_H
#define THIEF_H

#include "Character.h"

class Thief: public Character{

    public:
        Thief(Properties* props);

        virtual void Draw();
        virtual void Clean();
        virtual void Update(float dt);


    protected:
        int m_Row, m_Frame, m_FrameCount;
        int m_AnimSpeed;

    private:
};

#endif // THIEF_H
