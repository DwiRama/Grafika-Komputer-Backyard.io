#pragma once
#include "RenderEngine.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/vector_angle.hpp>
#include <SOIL/SOIL.h>

class Demo :
	public RenderEngine
{
public:
	Demo();
	~Demo();
private:
	GLuint VBOPlane, VAOPlane, EBOPlane, texturePlane;
	GLuint shaderProgram, tshaderProgram, VBOPole, VAOPole, EBOPole, texturePole, VBOWindmill, VAOWindmill, EBOWindmill, textureWindmill;
	GLuint VBOBush1, VAOBush1, EBOBush1, textureBush1, VBOBush2, VAOBush2, EBOBush2, VBOBush3, VAOBush3, EBOBush3, VBOBush4, VAOBush4, EBOBush4;
	GLuint VBOFence, VAOFence, EBOFence, textureFence;
	GLuint VBOWall, VAOWall, EBOWall, VBOWall1, VAOWall1, EBOWall1, VBOWall2, VAOWall2, EBOWall2, VBOWall3, VAOWall3, EBOWall3, VBOWall4, VAOWall4, EBOWall4, textureWall;
	GLuint VBOSkybox, VAOSkybox, EBOSkybox, textureSkybox;
	float angle = 0, posX = 0, posY = 0, posZ = 0, spinPosX = 0, spinPosY = 0, spinPosZ = 0, dirX = 1, dirY = 0, dirZ = 1, SPEED = 0.1f;
	virtual void Init();
	virtual void DeInit();
	virtual void Update(double deltaTime);
	virtual void Render();
	virtual void ProcessInput(GLFWwindow *window);
	void BuildPole();
	void BuildWindMill();
	void BuildBush1();
	void BuildBush2();
	void BuildBush3();
	void BuildBush4();
	void BuildGrassWall();
	void BuildGrassWall1();
	void BuildGrassWall2();
	void BuildGrassWall3();
	void BuildGrassWall4();
	void BuildFence();
	void TBuildFence();
	void BuildPlane();
	void BuildSkybox();
	void DrawPole();
	void DrawWindMill();
	void DrawBush1();
	void DrawBush2();
	void DrawBush3();
	void DrawBush4();
	void DrawGrassWall();
	void DrawGrassWall1();
	void DrawGrassWall2();
	void DrawGrassWall3();
	void DrawGrassWall4();
	void DrawFence();
	void TDrawFence();
	void DrawPlane();
	void DrawSkybox();
	float viewCamX, viewCamY, viewCamZ, upCamX, upCamY, upCamZ, posCamX, posCamY, posCamZ, CAMERA_SPEED, fovy;
	void MoveCamera(float speed);
	void StrafeCamera(float speed);
	void RotateCamera(float speed);
	void InitCamera();
};

