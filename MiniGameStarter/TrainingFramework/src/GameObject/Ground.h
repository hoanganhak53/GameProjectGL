#pragma once
#include "Sprite2D.h"
class Ground :
    public Sprite2D
{
public:
    Ground(std::shared_ptr<Model> model, std::shared_ptr<Shader> shader, std::shared_ptr<Texture> texture, int id);
    ~Ground();
    
    void    UpdateAnimation();

private:
    int     m_id;
};