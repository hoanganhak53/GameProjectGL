#include "SpriteAnimation.h"

#include "Shader.h"
#include "Model.h"
#include "Camera.h"
#include "Texture.h"
#include "Application.h"



SpriteAnimation::SpriteAnimation(std::shared_ptr<Model> model, std::shared_ptr<Shader> shader, std::shared_ptr<Texture> texture, GLint numFrames, GLint numActions, GLint currentAction, GLfloat frameTime)
	: BaseObject(-1, model, shader, texture), m_iWidth(100), m_iHeight(50)
{
	m_numFrames = numFrames;
	m_numActions = numActions;
	m_frameTime = frameTime;
	m_currentFrame = 0;
	m_currentAction = 0;
	m_currentTime = 0.0f;
	m_currentAction = currentAction;
	Init();
}

SpriteAnimation::~SpriteAnimation()
{
}

void SpriteAnimation::Init()
{
	SetCamera(Application::GetInstance()->GetCamera());
	CalculateWorldMatrix();
}

void SpriteAnimation::Draw()
{
	if (m_pCamera == nullptr) return;
	glUseProgram(m_pShader->m_program);
	glBindBuffer(GL_ARRAY_BUFFER, m_pModel->GetVertexObject());
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_pModel->GetIndiceObject());

	GLuint iTempShaderVaribleGLID = -1;
	Matrix matrixWVP;

	matrixWVP = m_worldMatrix *m_pCamera->GetLookAtCameraMatrix();

	if (m_pTexture != nullptr)
	{
		glActiveTexture(GL_TEXTURE0);
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, m_pTexture->Get2DTextureAdd());
		if (m_pShader->m_iTextureLoc[0] != -1)
			glUniform1i(m_pShader->m_iTextureLoc[0], 0);
	}

	iTempShaderVaribleGLID = -1;
	iTempShaderVaribleGLID = m_pShader->GetAttribLocation((char*)"a_posL");
	if (iTempShaderVaribleGLID != -1)
	{
		glEnableVertexAttribArray(iTempShaderVaribleGLID);
		glVertexAttribPointer(iTempShaderVaribleGLID, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), VETEX_POSITION);
	}

	iTempShaderVaribleGLID = -1;
	iTempShaderVaribleGLID = m_pShader->GetAttribLocation((char*) "a_uv");
	if (iTempShaderVaribleGLID != -1)
	{
		glEnableVertexAttribArray(iTempShaderVaribleGLID);
		glVertexAttribPointer(iTempShaderVaribleGLID, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), VETEX_UV);
	}

	iTempShaderVaribleGLID = -1;
	iTempShaderVaribleGLID = m_pShader->GetUniformLocation((char*)"u_alpha");
	if (iTempShaderVaribleGLID != -1)
		glUniform1f(iTempShaderVaribleGLID, 1.0);

	iTempShaderVaribleGLID = -1;
	iTempShaderVaribleGLID = m_pShader->GetUniformLocation((char*)"u_matMVP");
	if (iTempShaderVaribleGLID != -1)
		glUniformMatrix4fv(iTempShaderVaribleGLID, 1, GL_FALSE, matrixWVP.m[0]);

	iTempShaderVaribleGLID = -1;
	iTempShaderVaribleGLID = m_pShader->GetUniformLocation((char*)"u_numFrames");
	if (iTempShaderVaribleGLID != -1)
		glUniform1f(iTempShaderVaribleGLID, m_numFrames);

	iTempShaderVaribleGLID = -1;
	iTempShaderVaribleGLID = m_pShader->GetUniformLocation((char*)"u_currentFrame");
	if (iTempShaderVaribleGLID != -1)
		glUniform1f(iTempShaderVaribleGLID, m_currentFrame);

	iTempShaderVaribleGLID = -1;
	iTempShaderVaribleGLID = m_pShader->GetUniformLocation((char*)"u_numActions");
	if (iTempShaderVaribleGLID != -1)
		glUniform1f(iTempShaderVaribleGLID, m_numActions);

	iTempShaderVaribleGLID = -1;
	iTempShaderVaribleGLID = m_pShader->GetUniformLocation((char*)"u_currentAction");
	if (iTempShaderVaribleGLID != -1)
		glUniform1f(iTempShaderVaribleGLID, m_currentAction);

	glDrawElements(GL_TRIANGLES, m_pModel->GetNumIndiceObject(), GL_UNSIGNED_INT, 0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindTexture(GL_TEXTURE_2D, 0);

}

void SpriteAnimation::Update(GLfloat deltatime)
{
	m_currentTime += deltatime;
	if (m_currentTime >= m_frameTime)
	{
		m_currentFrame++;
		if (m_currentFrame >= m_numFrames)
			m_currentFrame = 0;
		m_currentTime -= m_frameTime;
	}
	Set2DPosition(Get2DPosition().x - Globals::moveCam, Get2DPosition().y);
}


void SpriteAnimation::Set2DPosition(GLint x, GLint y)
{
	m_position = Vector3((float)x, (float)y, 0.0f);
	CalculateWorldMatrix();
}

void SpriteAnimation::SetRotation(Vector3 rotation)
{
	m_rotation = rotation;
	CalculateWorldMatrix();
}

Vector3 SpriteAnimation::Get2DPosition()
{
	return m_position;
}

void SpriteAnimation::SetSize(GLint width, GLint height)
{
	m_iWidth = width;
	m_iHeight = height;
	m_scale = Vector3((float)m_iWidth, (float)m_iHeight, 1.0f);
	CalculateWorldMatrix();
}

Vector2 SpriteAnimation::getSize()
{
	return Vector2(m_iWidth,m_iHeight);
}

bool SpriteAnimation::CheckBound(std::shared_ptr<SpriteAnimation>  obj,int id)
{	
	int a_x1 = m_position.x - m_iWidth / 2 + 18, a_x2 = m_position.x + m_iWidth / 2 - 18;
	int a_y1 = m_position.y - m_iHeight / 2, a_y2 = m_position.y + m_iHeight / 2;
	int b_x1 = obj->Get2DPosition().x - obj->getSize().x / 2 , b_x2 = obj->Get2DPosition().x + obj->getSize().x / 2;
	int b_y1 = obj->Get2DPosition().y - obj->getSize().y / 2, b_y2 = obj->Get2DPosition().y + obj->getSize().y / 2;

	if (a_x1 < b_x2 && b_x1 < a_x2 && a_y1 < b_y2 && b_y1 < a_y2 && m_velocity <= 0)
	{
		Set2DPosition(m_position.x, obj->Get2DPosition().y - obj->getSize().y / 2 - m_iHeight / 2 + 1);
		return true;
	}
	return false;
}

bool SpriteAnimation::CheckBound(std::shared_ptr<SpriteAnimation>  obj)
{
	float a_x1 = m_position.x - m_iWidth / 2, a_x2 = m_position.x + m_iWidth / 2;
	float a_y1 = m_position.y - m_iHeight / 2, a_y2 = m_position.y + m_iHeight / 2;
	float b_x1 = obj->Get2DPosition().x - obj->getSize().x / 2 + 10, b_x2 = obj->Get2DPosition().x + obj->getSize().x / 2 - 10;
	float b_y1 = obj->Get2DPosition().y - obj->getSize().y / 2, b_y2 = obj->Get2DPosition().y + obj->getSize().y / 2;
	if (a_x1 < b_x2 && b_x1 < a_x2 && a_y1 < b_y2 && b_y1 < a_y2)
		return true;
	return false;
}


void SpriteAnimation::setJump(bool j)
{
	m_isJump = j;
}
GLint SpriteAnimation::getV()
{
	return m_velocity;
}
void SpriteAnimation::setV(GLint v)
{
	m_velocity = v;
	if (m_velocity < -5)
		m_velocity = -5;
}
bool SpriteAnimation::getActive()
{
	return m_isActive;
}
void SpriteAnimation::setActive(bool a)
{
	m_isActive = a;
}
bool SpriteAnimation::getJump()
{
	return m_isJump;
}