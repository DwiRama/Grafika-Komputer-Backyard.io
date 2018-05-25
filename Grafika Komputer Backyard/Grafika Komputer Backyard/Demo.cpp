#include "Demo.h"

Demo::Demo() {

}

Demo::~Demo() {

}

void Demo::Init() {
	// build and compile our shader program
	// ------------------------------------
	shaderProgram = BuildShader("vertexShader.vert", "fragmentShader.frag", nullptr);
	tshaderProgram = BuildShader("texturedModel.vert", "texturedModel.frag", nullptr);
	
	BuildPole();

	BuildWindMill();

	BuildBush1();
	BuildBush2();
	BuildBush3();
	BuildBush4();

	BuildGrassWall();
	BuildGrassWall1();
	BuildGrassWall2();
	BuildGrassWall3();
	BuildGrassWall4();

	BuildFence();

	BuildPlane();
	BuildSkybox();

	InitCamera();
}

void Demo::DeInit() {
	// optional: de-allocate all resources once they've outlived their purpose:
	// ------------------------------------------------------------------------
	glDeleteVertexArrays(1, &VAOPlane);
	glDeleteBuffers(1, &VBOPlane);
	glDeleteBuffers(1, &EBOPlane);
	
	glDeleteVertexArrays(1, &VAOPole);
	glDeleteBuffers(1, &VBOPole);
	glDeleteBuffers(1, &EBOPole);

	glDeleteVertexArrays(1, &VAOWindmill);
	glDeleteBuffers(1, &VBOWindmill);
	glDeleteBuffers(1, &EBOWindmill);

	glDeleteVertexArrays(1, &VAOBush1);
	glDeleteBuffers(1, &VBOBush1);
	glDeleteBuffers(1, &EBOBush1);

	glDeleteVertexArrays(1, &VAOBush2);
	glDeleteBuffers(1, &VBOBush2);
	glDeleteBuffers(1, &EBOBush2);

	glDeleteVertexArrays(1, &VAOBush3);
	glDeleteBuffers(1, &VBOBush3);
	glDeleteBuffers(1, &EBOBush3);

	glDeleteVertexArrays(1, &VAOBush4);
	glDeleteBuffers(1, &VBOBush4);
	glDeleteBuffers(1, &EBOBush4);

	glDeleteVertexArrays(1, &VAOWall);
	glDeleteBuffers(1, &VBOWall);
	glDeleteBuffers(1, &EBOWall);

	glDeleteVertexArrays(1, &VAOWall1);
	glDeleteBuffers(1, &VBOWall1);
	glDeleteBuffers(1, &EBOWall1);

	glDeleteVertexArrays(1, &VAOWall2);
	glDeleteBuffers(1, &VBOWall2);
	glDeleteBuffers(1, &EBOWall2);

	glDeleteVertexArrays(1, &VAOWall3);
	glDeleteBuffers(1, &VBOWall3);
	glDeleteBuffers(1, &EBOWall3);

	glDeleteVertexArrays(1, &VAOWall4);
	glDeleteBuffers(1, &VBOWall4);
	glDeleteBuffers(1, &EBOWall4);

	glDeleteVertexArrays(1, &VAOFence);
	glDeleteBuffers(1, &VBOFence);
	glDeleteBuffers(1, &EBOFence);

	glDeleteVertexArrays(1, &VAOSkybox);
	glDeleteBuffers(1, &VBOSkybox);
	glDeleteBuffers(1, &EBOSkybox);
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void Demo::ProcessInput(GLFWwindow *window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}

	//// update object movement 
	//// -------------
	//if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
	//	posZ -= 1 * SPEED;
	//}
	//if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
	//	posZ += 1 * SPEED;
	//}

	//if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
	//	posX -= 1 * SPEED;
	//}

	//if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
	//	posX += 1 * SPEED;
	//}

	//if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
	//	posY += 1 * SPEED;
	//}

	//if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
	//	posY -= 1 * SPEED;
	//}

	/*if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
		angle -= (float)(1.5f / 1000);
	}

	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
		angle += (float)(1.5f / 1000);
	}*/

	// update camera movement 
	// -------------
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
		MoveCamera(CAMERA_SPEED);
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
		MoveCamera(-CAMERA_SPEED);
	}

	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
		StrafeCamera(-CAMERA_SPEED);
	}

	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
		StrafeCamera(CAMERA_SPEED);
	}

	// update camera rotation
	// ----------------------
	double mouseX, mouseY;
	double midX = screenWidth / 2;
	double midY = screenHeight / 2;
	float angleY = 0.0f;
	float angleZ = 0.0f;

	// Get mouse position
	glfwGetCursorPos(window, &mouseX, &mouseY);
	if ((mouseX == midX) && (mouseY == midY)) {
		return;
	}

	// Set mouse position
	glfwSetCursorPos(window, midX, midY);

	// Get the direction from the mouse cursor, set a resonable maneuvering speed
	angleY = (float)((midX - mouseX)) / 600;
	angleZ = (float)((midY - mouseY)) / 600;

	// The higher the value is the faster the camera looks around.
	viewCamY += angleZ * 2;

	// limit the rotation around the x-axis
	if ((viewCamY - posCamY) > 8) {
		viewCamY = posCamY + 8;
	}
	if ((viewCamY - posCamY) < -8) {
		viewCamY = posCamY - 8;
	}
	RotateCamera(-angleY);
}

void Demo::Update(double deltaTime) {
	angle += (float) ((deltaTime * 1.5f) / 1000);
	spinPosY += 1 * SPEED * (float)((deltaTime * 1.5f));
}

void Demo::Render() {
	glViewport(0, 0, this->screenWidth, this->screenHeight);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.35f, 0.5f, 0.7f, 1.0f);

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	glEnable(GL_DEPTH_TEST);

	// Pass perspective projection matrix
	glm::mat4 projection = glm::perspective(45.0f, (GLfloat)this->screenWidth / (GLfloat)this->screenHeight, 0.1f, 200.0f);
	GLint projLoc = glGetUniformLocation(this->shaderProgram, "projection");
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));

	// LookAt camera (position, target/direction, up)
	glm::mat4 view = glm::lookAt(glm::vec3(posCamX, posCamY, posCamZ), glm::vec3(viewCamX, viewCamY, viewCamZ), glm::vec3(upCamX, upCamY, upCamZ));
	GLint viewLoc = glGetUniformLocation(this->shaderProgram, "view");
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));

	// set lighting attributes
	GLint lightPosLoc = glGetUniformLocation(this->tshaderProgram, "lightPos");
	glUniform3f(lightPosLoc, 0, 1, 0);
	GLint viewPosLoc = glGetUniformLocation(this->tshaderProgram, "viewPos");
	glUniform3f(viewPosLoc, 0, 2, 3);
	GLint lightColorLoc = glGetUniformLocation(this->tshaderProgram, "lightColor");
	glUniform3f(lightColorLoc, 1.0f, 1.0f, 1.0f);

	DrawPole();
	DrawWindMill();
	DrawBush1();
	DrawBush2();
	DrawBush3();
	DrawBush4();

	DrawGrassWall();
	DrawGrassWall1();
	DrawGrassWall2();
	DrawGrassWall3();
	DrawGrassWall4();

	DrawFence();

	DrawPlane();

	DrawSkybox();

	glDisable(GL_DEPTH_TEST);
}

void Demo::BuildPole() {
	// load image into texture memory
	// ------------------------------
	// Load and create a texture 
	glGenTextures(1, &texturePole);
	glBindTexture(GL_TEXTURE_2D, texturePole);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	int width, height;
	unsigned char* image = SOIL_load_image("steel.jpg", &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);

	// set up vertex data (and buffer(s)) and configure vertex attributes
	// ------------------------------------------------------------------
	// set up vertex data (and buffer(s)) and configure vertex attributes
	// ------------------------------------------------------------------
	float vertices[] = {
		// format position, tex coords
		// bottom
		-0.2, 0,  0.2, 0, 0,  // 0
		0.2, 0,  0.2, 1, 0,   // 1
		0.2, 0, -0.2, 1, 1,   // 2
		-0.2, 0, -0.2, 0, 1,  // 3

		// top
		-0.2, 4,  0.2, 0, 1,  // 4
		0.2, 4,  0.2, 1, 1,  // 5
		0.2, 4, -0.2, 1, 0,  // 6
		-0.2, 4, -0.2, 0, 0,  // 7
	};

	unsigned int indices[] = {
		0,  4,  1,  1,  4,  5,   // front
		1,  2,  5,  2,  5,  6,   // right
		2,  6,  7,  2,  3,  7,  // back
		3,  4,  7,  0,  3,  4,  // left
		4,  5,  7,  5,  6,  7,  // upper
		0,  1,  3,  1,  2,  3   // bottom
	};

	glGenVertexArrays(1, &VAOPole);
	glGenBuffers(1, &VBOPole);
	glGenBuffers(1, &EBOPole);
	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(VAOPole);

	glBindBuffer(GL_ARRAY_BUFFER, VBOPole);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBOPole);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// define position pointer layout 0
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(0 * sizeof(GLfloat)));
	glEnableVertexAttribArray(0);

	// define texcoord pointer layout 1
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
	// VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
	glBindVertexArray(0);

	// remember: do NOT unbind the EBO while a VAO is active as the bound element buffer object IS stored in the VAO; keep the EBO bound.
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

}

void Demo::DrawPole()
{
	glUseProgram(shaderProgram);

	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, texturePole);
	glUniform1i(glGetUniformLocation(this->shaderProgram, "ourTexture"), 1);

	glBindVertexArray(VAOPole); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
	
	glm::mat4 model;
		
	model = glm::translate(model, glm::vec3(0.2, 0.8, 14));

	model = glm::scale(model, glm::vec3(0.2, 0.2, 0.2));

	//model = glm::rotate(model, angle, glm::vec3(0, 0, 0));
	
	

	GLint modelLoc = glGetUniformLocation(this->shaderProgram, "model");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	glBindTexture(GL_TEXTURE_2D, 0);
	glBindVertexArray(0);
}

void Demo::BuildWindMill() {
	// load image into texture memory
	// ------------------------------
	// Load and create a texture 
	glGenTextures(1, &textureWindmill);
	glBindTexture(GL_TEXTURE_2D, textureWindmill);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	int width, height;
	unsigned char* image = SOIL_load_image("red_paper.jpg", &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);

	// set up vertex data (and buffer(s)) and configure vertex attributes
	// ------------------------------------------------------------------
	// set up vertex data (and buffer(s)) and configure vertex attributes
	// ------------------------------------------------------------------
	float vertices[] = {
		// format position, tex coords
		  0, 0, 0.7, 0, 0,   // 0
		  0, 0.2, 0.21, 1, 0,   // 1
		0.2, 0, 0.21, 1, 1,   // 2
	      0, -0.2, 0.21, 0, 1,   // 3
	   -0.2, 0, 0.21, 1, 1,   // 4

	   1, 2, 0.21, 0, 0, //5
	   1.5, 0.2, 0.21, 0, 1, //6

	   2.2, -0.7, 0.21, 1, 0, // 7	   
	   0.5, -1.4, 0.21, 0, 0, // 8
	   
	   -1, -2.2, 0.21, 1, 0,  // 9
	   -1.5, 0.2, 0.21, 0, 0, // 10

	   -2.2, 0.7, 0.21, 0, 0, // 11
	   -0.5, 1.2, 0.21, 0, 1, // 12
	};

	unsigned int indices[] = {
		//Limas Segiempat
		0, 1, 2,
		0, 2, 3,
		0, 3, 4,
		0, 1, 4,
		1, 2, 3,
		1, 3, 4,

		//Upper Right Propeller
		1, 5, 6, 1, 2, 6,

		//Bottom Right Propeller
		2, 7, 8, 2, 3, 8,

		//Bottom Left Propeller
		3, 4, 9, 4, 9, 10,

		//Upper Left Propeller
		1, 4, 12, 4, 11, 12,
	};

	glGenVertexArrays(1, &VAOWindmill);
	glGenBuffers(1, &VBOWindmill);
	glGenBuffers(1, &EBOWindmill);
	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(VAOWindmill);

	glBindBuffer(GL_ARRAY_BUFFER, VBOWindmill);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBOWindmill);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// define position pointer layout 0
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(0 * sizeof(GLfloat)));
	glEnableVertexAttribArray(0);

	// define texcoord pointer layout 1
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
	// VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
	glBindVertexArray(0);

	// remember: do NOT unbind the EBO while a VAO is active as the bound element buffer object IS stored in the VAO; keep the EBO bound.
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

}

void Demo::DrawWindMill()
{
	glUseProgram(shaderProgram);

	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, textureWindmill);
	glUniform1i(glGetUniformLocation(this->shaderProgram, "ourTexture"), 2);

	glBindVertexArray(VAOWindmill); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
	
	glm::mat4 model;

	model = glm::translate(model, glm::vec3(0.2, 1.6, 14));

	model = glm::scale(model, glm::vec3(0.15, 0.15, 0.2));

	model = glm::rotate(model, angle, glm::vec3(0, 0, -1));
		
	GLint modelLoc = glGetUniformLocation(this->shaderProgram, "model");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

	glDrawElements(GL_TRIANGLES, 42, GL_UNSIGNED_INT, 0);

	glBindTexture(GL_TEXTURE_2D, 0);
	glBindVertexArray(0);
}

void Demo::BuildBush1() {
	glGenTextures(1, &textureBush1);
	glBindTexture(GL_TEXTURE_2D, textureBush1);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	int width, height;
	unsigned char* image = SOIL_load_image("leaf.png", &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);
	
	float vertices[] = {
		// format position, tex coords
		// front
		-0.5, 0, 0.5, 0, 0,  // 0
		0.5, 0, 0.5, 1, 0,   // 1
		1,  1, 1, 1,1,   // 2
		-1,  1, 1, 0, 1,  // 3

		// right
		1,  1,  1, 0, 0,  // 4
		1,  1, -1, 1, 0,  // 5
		0.5, 0, -0.5, 1, 1,  // 6
		0.5, 0,  0.5, 0, 1,  // 7

		// back
		-0.5, 0, -0.5, 0, 0, // 8 
		0.5,  0, -0.5, 1, 0, // 9
		1,   1, -1, 1,1, // 10
		-1,  1, -1, 0, 1, // 11

		// left
		-0.5, 0, -0.5, 0, 0, // 12
		-0.5, 0,  0.5, 1, 0, // 13
		-1,  1,  1, 1,1, // 14
		-1,  1, -1, 0, 1, // 15

		// upper
		1, 1,  1, 0, 0,   // 16
		-1, 1,  1, 1, 0,  // 17
		-1, 1, -1, 1,1,  // 18
		1, 1, -1, 0, 1,   // 19

		// bottom
		-0.5, 0, -0.5, 0, 0, // 20
		0.5, 0, -0.5, 1, 0,  // 21
		0.5, 0,  0.5, 1,1,  // 22
		-0.5, 0,  0.5, 0, 1, // 23

		-1, 1, 1, 0, 0,  // 24
		1, 1, 1, 1, 0,   // 25
		0.4,  2, 0.4, 1, 1,   // 26
		-0.4,  2, 0.4, 0, 1,  // 27

		// right
		1,  1,  1, 0, 0,  // 28
		1,  1, -1, 1, 0,  // 29
		0.4, 2, -0.4, 1,1,  // 30
		0.4, 2,  0.4, 0, 1,  // 31

		// back
		-0.4, 2, -0.4, 0, 0, // 32 
		0.4,  2, -0.4, 1, 0, // 33
		1,   1, -1, 1,1, // 34
		-1,  1, -1, 0, 1, // 35

		// left
		-0.4, 2, -0.4, 0, 0, // 36
		-0.4, 2,  0.4, 1, 0, // 37
		-1,  1,  1, 1,1, // 38
		-1,  1, -1, 0, 1, // 39

		// upper
		-0.4, 2, -0.4, 0, 0, // 40
		0.4, 2, -0.4, 1, 0,  // 41
		0.4, 2,  0.4, 1,1,  // 42
		-0.4, 2,  0.4, 0, 1, // 43

		// bottom
		0.5, 1,  1, 0, 0,   // 44
		-0.5, 1,  1, 1, 0,  // 45
		-0.5, 1, -1, 1, 1,  // 46
		0.5, 1, -1, 0, 1,   // 47
	};

	unsigned int indices[] = {
		0,  1,  2,  0,  2,  3,   // front
		4,  5,  6,  4,  6,  7,   // right
		8,  9,  10, 8,  10, 11,  // back
		12, 14, 13, 12, 15, 14,  // left
		16, 18, 17, 16, 19, 18,  // upper
		20, 22, 21, 20, 23, 22,   // bottom

		24,  25,  26,  24,  26,  27,   // front
		28,  29,  30,  28,  30,  31,   // right
		32,  33,  34, 32,  34, 35,  // back
		36, 37, 38, 36, 38, 39,  // left
		40, 42, 41, 40, 43, 42,  // upper
		44, 46, 45, 44, 47, 46   // bottom
	};

	glGenVertexArrays(1, &VAOBush1);
	glGenBuffers(1, &VBOBush1);
	glGenBuffers(1, &EBOBush1);
	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(VAOBush1);

	glBindBuffer(GL_ARRAY_BUFFER, VBOBush1);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBOBush1);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// define position pointer layout 0
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(0 * sizeof(GLfloat)));
	glEnableVertexAttribArray(0);

	// define texcoord pointer layout 1
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
	// VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
	glBindVertexArray(0);

	// remember: do NOT unbind the EBO while a VAO is active as the bound element buffer object IS stored in the VAO; keep the EBO bound.
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void Demo::DrawBush1() {
	glUseProgram(shaderProgram);

	glActiveTexture(GL_TEXTURE3);
	glBindTexture(GL_TEXTURE_2D, textureBush1);
	glUniform1i(glGetUniformLocation(this->shaderProgram, "ourTexture"), 3);

	glBindVertexArray(VAOBush1); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized

	glm::mat4 model;

	model = glm::translate(model, glm::vec3(5, 0, 5));

	model = glm::scale(model, glm::vec3(0.5, 0.5, 0.5));

	model = glm::rotate(model, 45.0f, glm::vec3(0, 1, 0));

	GLint modelLoc = glGetUniformLocation(this->shaderProgram, "model");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

	glDrawElements(GL_TRIANGLES, 24 * 3, GL_UNSIGNED_INT, 0);

	glBindTexture(GL_TEXTURE_2D, 0);
	glBindVertexArray(0);
}

void Demo::BuildBush2() {
	glGenTextures(1, &textureBush1);
	glBindTexture(GL_TEXTURE_2D, textureBush1);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	int width, height;
	unsigned char* image = SOIL_load_image("leaf.png", &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);

	float vertices[] = {
		// format position, tex coords
		// front
		-0.5, 0, 0.5, 0, 0,  // 0
		0.5, 0, 0.5, 1, 0,   // 1
		1,  1, 1, 1,1,   // 2
		-1,  1, 1, 0, 1,  // 3

						  // right
						  1,  1,  1, 0, 0,  // 4
						  1,  1, -1, 1, 0,  // 5
						  0.5, 0, -0.5, 1, 1,  // 6
						  0.5, 0,  0.5, 0, 1,  // 7

											   // back
											   -0.5, 0, -0.5, 0, 0, // 8 
											   0.5,  0, -0.5, 1, 0, // 9
											   1,   1, -1, 1,1, // 10
											   -1,  1, -1, 0, 1, // 11

																 // left
																 -0.5, 0, -0.5, 0, 0, // 12
																 -0.5, 0,  0.5, 1, 0, // 13
																 -1,  1,  1, 1,1, // 14
																 -1,  1, -1, 0, 1, // 15

																				   // upper
																				   1, 1,  1, 0, 0,   // 16
																				   -1, 1,  1, 1, 0,  // 17
																				   -1, 1, -1, 1,1,  // 18
																				   1, 1, -1, 0, 1,   // 19

																									 // bottom
																									 -0.5, 0, -0.5, 0, 0, // 20
																									 0.5, 0, -0.5, 1, 0,  // 21
																									 0.5, 0,  0.5, 1,1,  // 22
																									 -0.5, 0,  0.5, 0, 1, // 23

																									 -1, 1, 1, 0, 0,  // 24
																									 1, 1, 1, 1, 0,   // 25
																									 0.4,  2, 0.4, 1, 1,   // 26
																									 -0.4,  2, 0.4, 0, 1,  // 27

																														   // right
																														   1,  1,  1, 0, 0,  // 28
																														   1,  1, -1, 1, 0,  // 29
																														   0.4, 2, -0.4, 1,1,  // 30
																														   0.4, 2,  0.4, 0, 1,  // 31

																																				// back
																																				-0.4, 2, -0.4, 0, 0, // 32 
																																				0.4,  2, -0.4, 1, 0, // 33
																																				1,   1, -1, 1,1, // 34
																																				-1,  1, -1, 0, 1, // 35

																																								  // left
																																								  -0.4, 2, -0.4, 0, 0, // 36
																																								  -0.4, 2,  0.4, 1, 0, // 37
																																								  -1,  1,  1, 1,1, // 38
																																								  -1,  1, -1, 0, 1, // 39

																																													// upper
																																													-0.4, 2, -0.4, 0, 0, // 40
																																													0.4, 2, -0.4, 1, 0,  // 41
																																													0.4, 2,  0.4, 1,1,  // 42
																																													-0.4, 2,  0.4, 0, 1, // 43

																																																		 // bottom
																																																		 0.5, 1,  1, 0, 0,   // 44
																																																		 -0.5, 1,  1, 1, 0,  // 45
																																																		 -0.5, 1, -1, 1, 1,  // 46
																																																		 0.5, 1, -1, 0, 1,   // 47
	};

	unsigned int indices[] = {
		0,  1,  2,  0,  2,  3,   // front
		4,  5,  6,  4,  6,  7,   // right
		8,  9,  10, 8,  10, 11,  // back
		12, 14, 13, 12, 15, 14,  // left
		16, 18, 17, 16, 19, 18,  // upper
		20, 22, 21, 20, 23, 22,   // bottom

		24,  25,  26,  24,  26,  27,   // front
		28,  29,  30,  28,  30,  31,   // right
		32,  33,  34, 32,  34, 35,  // back
		36, 37, 38, 36, 38, 39,  // left
		40, 42, 41, 40, 43, 42,  // upper
		44, 46, 45, 44, 47, 46   // bottom
	};

	glGenVertexArrays(1, &VAOBush2);
	glGenBuffers(1, &VBOBush2);
	glGenBuffers(1, &EBOBush2);
	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(VAOBush2);

	glBindBuffer(GL_ARRAY_BUFFER, VBOBush2);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBOBush2);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// define position pointer layout 0
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(0 * sizeof(GLfloat)));
	glEnableVertexAttribArray(0);

	// define texcoord pointer layout 1
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	
	glBindVertexArray(0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void Demo::DrawBush2() {
	glUseProgram(shaderProgram);

	glActiveTexture(GL_TEXTURE3);
	glBindTexture(GL_TEXTURE_2D, textureBush1);
	glUniform1i(glGetUniformLocation(this->shaderProgram, "ourTexture"), 3);

	glBindVertexArray(VAOBush1); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized

	glm::mat4 model;

	model = glm::translate(model, glm::vec3(8, 0, -2));

	model = glm::scale(model, glm::vec3(0.7, 0.5, 0.5));

	model = glm::rotate(model, 10.0f, glm::vec3(0, 1, 0));

	GLint modelLoc = glGetUniformLocation(this->shaderProgram, "model");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

	glDrawElements(GL_TRIANGLES, 24 * 3, GL_UNSIGNED_INT, 0);

	glBindTexture(GL_TEXTURE_2D, 0);
	glBindVertexArray(0);
}

void Demo::BuildBush3() {
	glGenTextures(1, &textureBush1);
	glBindTexture(GL_TEXTURE_2D, textureBush1);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	int width, height;
	unsigned char* image = SOIL_load_image("leaf.png", &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);

	float vertices[] = {
		// format position, tex coords
		// front
		-0.5, 0, 0.5, 0, 0,  // 0
		0.5, 0, 0.5, 1, 0,   // 1
		1,  1, 1, 1,1,   // 2
		-1,  1, 1, 0, 1,  // 3

						  // right
						  1,  1,  1, 0, 0,  // 4
						  1,  1, -1, 1, 0,  // 5
						  0.5, 0, -0.5, 1, 1,  // 6
						  0.5, 0,  0.5, 0, 1,  // 7

											   // back
											   -0.5, 0, -0.5, 0, 0, // 8 
											   0.5,  0, -0.5, 1, 0, // 9
											   1,   1, -1, 1,1, // 10
											   -1,  1, -1, 0, 1, // 11

																 // left
																 -0.5, 0, -0.5, 0, 0, // 12
																 -0.5, 0,  0.5, 1, 0, // 13
																 -1,  1,  1, 1,1, // 14
																 -1,  1, -1, 0, 1, // 15

																				   // upper
																				   1, 1,  1, 0, 0,   // 16
																				   -1, 1,  1, 1, 0,  // 17
																				   -1, 1, -1, 1,1,  // 18
																				   1, 1, -1, 0, 1,   // 19

																									 // bottom
																									 -0.5, 0, -0.5, 0, 0, // 20
																									 0.5, 0, -0.5, 1, 0,  // 21
																									 0.5, 0,  0.5, 1,1,  // 22
																									 -0.5, 0,  0.5, 0, 1, // 23

																									 -1, 1, 1, 0, 0,  // 24
																									 1, 1, 1, 1, 0,   // 25
																									 0.4,  2, 0.4, 1, 1,   // 26
																									 -0.4,  2, 0.4, 0, 1,  // 27

																														   // right
																														   1,  1,  1, 0, 0,  // 28
																														   1,  1, -1, 1, 0,  // 29
																														   0.4, 2, -0.4, 1,1,  // 30
																														   0.4, 2,  0.4, 0, 1,  // 31

																																				// back
																																				-0.4, 2, -0.4, 0, 0, // 32 
																																				0.4,  2, -0.4, 1, 0, // 33
																																				1,   1, -1, 1,1, // 34
																																				-1,  1, -1, 0, 1, // 35

																																								  // left
																																								  -0.4, 2, -0.4, 0, 0, // 36
																																								  -0.4, 2,  0.4, 1, 0, // 37
																																								  -1,  1,  1, 1,1, // 38
																																								  -1,  1, -1, 0, 1, // 39

																																													// upper
																																													-0.4, 2, -0.4, 0, 0, // 40
																																													0.4, 2, -0.4, 1, 0,  // 41
																																													0.4, 2,  0.4, 1,1,  // 42
																																													-0.4, 2,  0.4, 0, 1, // 43

																																																		 // bottom
																																																		 0.5, 1,  1, 0, 0,   // 44
																																																		 -0.5, 1,  1, 1, 0,  // 45
																																																		 -0.5, 1, -1, 1, 1,  // 46
																																																		 0.5, 1, -1, 0, 1,   // 47
	};

	unsigned int indices[] = {
		0,  1,  2,  0,  2,  3,   // front
		4,  5,  6,  4,  6,  7,   // right
		8,  9,  10, 8,  10, 11,  // back
		12, 14, 13, 12, 15, 14,  // left
		16, 18, 17, 16, 19, 18,  // upper
		20, 22, 21, 20, 23, 22,   // bottom

		24,  25,  26,  24,  26,  27,   // front
		28,  29,  30,  28,  30,  31,   // right
		32,  33,  34, 32,  34, 35,  // back
		36, 37, 38, 36, 38, 39,  // left
		40, 42, 41, 40, 43, 42,  // upper
		44, 46, 45, 44, 47, 46   // bottom
	};

	glGenVertexArrays(1, &VAOBush3);
	glGenBuffers(1, &VBOBush3);
	glGenBuffers(1, &EBOBush3);
	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(VAOBush3);

	glBindBuffer(GL_ARRAY_BUFFER, VBOBush3);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBOBush3);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// define position pointer layout 0
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(0 * sizeof(GLfloat)));
	glEnableVertexAttribArray(0);

	// define texcoord pointer layout 1
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void Demo::DrawBush3() {
	glUseProgram(shaderProgram);

	glActiveTexture(GL_TEXTURE3);
	glBindTexture(GL_TEXTURE_2D, textureBush1);
	glUniform1i(glGetUniformLocation(this->shaderProgram, "ourTexture"), 3);

	glBindVertexArray(VAOBush3); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized

	glm::mat4 model;

	model = glm::translate(model, glm::vec3(-2, 0, 0));

	model = glm::scale(model, glm::vec3(0.8, 0.7, 0.8));

	model = glm::rotate(model, 5.0f, glm::vec3(0, 1, 0));

	GLint modelLoc = glGetUniformLocation(this->shaderProgram, "model");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

	glDrawElements(GL_TRIANGLES, 24 * 3, GL_UNSIGNED_INT, 0);

	glBindTexture(GL_TEXTURE_2D, 0);
	glBindVertexArray(0);
}

void Demo::BuildBush4() {
	glGenTextures(1, &textureBush1);
	glBindTexture(GL_TEXTURE_2D, textureBush1);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	int width, height;
	unsigned char* image = SOIL_load_image("leaf.png", &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);

	float vertices[] = {
		// format position, tex coords
		// front
		-0.5, 0, 0.5, 0, 0,  // 0
		0.5, 0, 0.5, 1, 0,   // 1
		1,  1, 1, 1,1,   // 2
		-1,  1, 1, 0, 1,  // 3

						  // right
						  1,  1,  1, 0, 0,  // 4
						  1,  1, -1, 1, 0,  // 5
						  0.5, 0, -0.5, 1, 1,  // 6
						  0.5, 0,  0.5, 0, 1,  // 7

											   // back
											   -0.5, 0, -0.5, 0, 0, // 8 
											   0.5,  0, -0.5, 1, 0, // 9
											   1,   1, -1, 1,1, // 10
											   -1,  1, -1, 0, 1, // 11

																 // left
																 -0.5, 0, -0.5, 0, 0, // 12
																 -0.5, 0,  0.5, 1, 0, // 13
																 -1,  1,  1, 1,1, // 14
																 -1,  1, -1, 0, 1, // 15

																				   // upper
																				   1, 1,  1, 0, 0,   // 16
																				   -1, 1,  1, 1, 0,  // 17
																				   -1, 1, -1, 1,1,  // 18
																				   1, 1, -1, 0, 1,   // 19

																									 // bottom
																									 -0.5, 0, -0.5, 0, 0, // 20
																									 0.5, 0, -0.5, 1, 0,  // 21
																									 0.5, 0,  0.5, 1,1,  // 22
																									 -0.5, 0,  0.5, 0, 1, // 23

																									 -1, 1, 1, 0, 0,  // 24
																									 1, 1, 1, 1, 0,   // 25
																									 0.4,  2, 0.4, 1, 1,   // 26
																									 -0.4,  2, 0.4, 0, 1,  // 27

																														   // right
																														   1,  1,  1, 0, 0,  // 28
																														   1,  1, -1, 1, 0,  // 29
																														   0.4, 2, -0.4, 1,1,  // 30
																														   0.4, 2,  0.4, 0, 1,  // 31

																																				// back
																																				-0.4, 2, -0.4, 0, 0, // 32 
																																				0.4,  2, -0.4, 1, 0, // 33
																																				1,   1, -1, 1,1, // 34
																																				-1,  1, -1, 0, 1, // 35

																																								  // left
																																								  -0.4, 2, -0.4, 0, 0, // 36
																																								  -0.4, 2,  0.4, 1, 0, // 37
																																								  -1,  1,  1, 1,1, // 38
																																								  -1,  1, -1, 0, 1, // 39

																																													// upper
																																													-0.4, 2, -0.4, 0, 0, // 40
																																													0.4, 2, -0.4, 1, 0,  // 41
																																													0.4, 2,  0.4, 1,1,  // 42
																																													-0.4, 2,  0.4, 0, 1, // 43

																																																		 // bottom
																																																		 0.5, 1,  1, 0, 0,   // 44
																																																		 -0.5, 1,  1, 1, 0,  // 45
																																																		 -0.5, 1, -1, 1, 1,  // 46
																																																		 0.5, 1, -1, 0, 1,   // 47
	};

	unsigned int indices[] = {
		0,  1,  2,  0,  2,  3,   // front
		4,  5,  6,  4,  6,  7,   // right
		8,  9,  10, 8,  10, 11,  // back
		12, 14, 13, 12, 15, 14,  // left
		16, 18, 17, 16, 19, 18,  // upper
		20, 22, 21, 20, 23, 22,   // bottom

		24,  25,  26,  24,  26,  27,   // front
		28,  29,  30,  28,  30,  31,   // right
		32,  33,  34, 32,  34, 35,  // back
		36, 37, 38, 36, 38, 39,  // left
		40, 42, 41, 40, 43, 42,  // upper
		44, 46, 45, 44, 47, 46   // bottom
	};

	glGenVertexArrays(1, &VAOBush4);
	glGenBuffers(1, &VBOBush4);
	glGenBuffers(1, &EBOBush4);
	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(VAOBush4);

	glBindBuffer(GL_ARRAY_BUFFER, VBOBush4);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBOBush4);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// define position pointer layout 0
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(0 * sizeof(GLfloat)));
	glEnableVertexAttribArray(0);

	// define texcoord pointer layout 1
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void Demo::DrawBush4() {
	glUseProgram(shaderProgram);

	glActiveTexture(GL_TEXTURE3);
	glBindTexture(GL_TEXTURE_2D, textureBush1);
	glUniform1i(glGetUniformLocation(this->shaderProgram, "ourTexture"), 3);

	glBindVertexArray(VAOBush4); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized

	glm::mat4 model;

	model = glm::translate(model, glm::vec3(-7, 0, 10));

	model = glm::scale(model, glm::vec3(0.55, 0.5, 0.5));

	model = glm::rotate(model, 90.0f, glm::vec3(0, 1, 0));

	GLint modelLoc = glGetUniformLocation(this->shaderProgram, "model");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

	glDrawElements(GL_TRIANGLES, 24 * 3, GL_UNSIGNED_INT, 0);

	glBindTexture(GL_TEXTURE_2D, 0);
	glBindVertexArray(0);
}

void Demo::BuildFence() {
	glGenTextures(1, &textureFence);
	glBindTexture(GL_TEXTURE_2D, textureFence);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	int width, height;
	unsigned char* image = SOIL_load_image("kayu.jpg", &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);

	float vertices[] = {
		// format position, tex coords //vertex index
		1.0 , 3.0 , 0.3 , 0.5 , 1 ,	//0
		1.0 , 3.0 , -0.3 , 1 , 1 ,	//1
		-1.0 , 3.0 , -0.3 ,	0.5 , 1 ,	//2
		-1.0 , 3.0 , 0.3 , 0 , 1 ,	//3
		1.0 , -3.0 , 0.3 , 0.5 , 0 ,	//4 
		1.0 , -3.0 , -0.3 , 1 , 0 , //5
		-1.0 , -3.0 , -0.3 , 0.5 , 0 ,//6
		-1.0 , -3.0 , 0.3 , 0 , 0 , //7	

		-1.6 , 3.0 , 0.3 , 0.5 , 1 ,	//8
		-1.6 , 3.0 , -0.3 , 1 , 1 ,	//9
		-3.6 , 3.0 , -0.3 ,	0.5 , 1 ,	//10
		-3.6 , 3.0 , 0.3 , 0 , 1 ,	//11
		-1.6 , -3.0 , 0.3 , 0.5 , 0 ,	//12
		-1.6 , -3.0 , -0.3 , 1 , 0 ,//13
		-3.6 , -3.0 , -0.3 , 0.5 , 0 ,//14
		-3.6 , -3.0 , 0.3 , 0 , 0 , //15

		3.6 , 3.0 , 0.3 , 0.5 , 1 ,	//16
		3.6 , 3.0 , -0.3 , 1 , 1 ,	//17
		1.6 , 3.0 , -0.3 ,	0.5 , 1 ,	//18
		1.6 , 3.0 , 0.3 , 0 , 1 ,	//19
		3.6 , -3.0 , 0.3 , 0.5 , 0 ,	//20
		3.6 , -3.0 , -0.3 , 1 , 0 , //21
		1.6 , -3.0 , -0.3 , 0.5 , 0 , //22
		1.6 , -3.0 , 0.3 , 0 , 0 ,  //23

		4.4 , 1.6 , -0.3 , 0.5 , 0 ,	//24
		4.4 , 1.6 , -1.1 , 1 , 0 ,	//25
		-4.4 , 1.6 , -1.1 ,	1 , 1 ,	//26
		-4.4 , 1.6 , -0.3 , 0.5 , 1 ,	//27
		4.4 , 0 , -0.3 , 0 , 0 ,	//28
		4.4 , 0 , -1.1 , 0.5 , 0 ,	//29
		-4.4 , 0 , -1.1 , 0.5 , 1 ,	//30
		-4.4 , 0 , -0.3 , 0 , 1 ,	//31

		4.4 , -2.0 , -0.3 , 0.5 , 0 ,	//32
		4.4 , -2.0 , -1.1 , 1 , 0 ,	//33
		-4.4 , -2.0 , -1.1 , 1 , 1 ,//34
		-4.4 , -2.0 , -0.3 , 0.5 , 1 ,//35
		4.4 , -3.6 , -0.3 , 0 , 0 ,	//36
		4.4 , -3.6 , -1.1 , 0.5 , 0 , //37
		-4.4 , -3.6 , -1.1 , 0.5 , 1 ,//38
		-4.4 , -3.6 , -0.3 , 0 , 1 //39																																																		 0.5, 1, -1, 0, 1,   // 47
	};

	unsigned int indices[] = {
		0 , 1 , 2 , 0 , 2 , 3 ,
		0 , 4 , 5 , 0 , 1 , 5 ,
		0 , 3 , 7 , 0 , 7 , 4 ,
		4 , 5 , 6 , 4 , 6 , 7 ,
		2 , 3 , 7 , 2 , 7 , 6 ,
		2 , 1 , 5 , 2 , 5 , 6 ,

		8 , 9 , 10 , 8 , 10 , 11 ,
		8 , 12 , 13 , 8 , 9 , 13 ,
		8 , 11 , 15 , 8 , 15 , 12 ,
		14, 10, 11, 14, 11, 15,
		14, 15, 12, 14, 13, 12,
		14, 9, 10, 14, 9, 13,

		16 , 17 , 18 , 16 , 18 , 19 ,
		16, 20, 21, 16, 21, 17,
		16, 23, 20, 16, 23, 19,
		20, 21, 22, 20, 22, 23,
		22, 17, 18, 22, 21, 17,
		22, 23, 19, 22, 19, 18,

		24, 26, 25, 24, 26, 27,
		24, 31, 27, 24, 31, 28,
		24, 29, 25, 24, 29, 28,
		30, 28, 31, 30, 28, 29,
		30, 27, 31, 30, 27, 26,
		30, 25, 26, 30, 25, 29,

		32, 34, 33, 32, 34, 35,
		32, 39, 35, 32, 39, 36,
		32, 37, 36, 32, 37, 33,
		38, 35, 39, 38, 35, 34,
		38, 33, 37, 38, 33, 34
	};

	glGenVertexArrays(1, &VAOFence);
	glGenBuffers(1, &VBOFence);
	glGenBuffers(1, &EBOFence);
	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(VAOFence);

	glBindBuffer(GL_ARRAY_BUFFER, VBOFence);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBOFence);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// define position pointer layout 0
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(0 * sizeof(GLfloat)));
	glEnableVertexAttribArray(0);

	// define texcoord pointer layout 1
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void Demo::DrawFence() {
	glUseProgram(shaderProgram);

	glActiveTexture(GL_TEXTURE4);
	glBindTexture(GL_TEXTURE_2D, textureFence);
	glUniform1i(glGetUniformLocation(this->shaderProgram, "ourTexture"), 4);

	glBindVertexArray(VAOFence); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized

	glm::mat4 model;

	model = glm::translate(model, glm::vec3(0, 0.6, 14));

	model = glm::scale(model, glm::vec3(0.2, 0.2, 0.2));

	//model = glm::rotate(model, 90.0f, glm::vec3(0, 0, 0));

	GLint modelLoc = glGetUniformLocation(this->shaderProgram, "model");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

	glDrawElements(GL_TRIANGLES, 60 * 3, GL_UNSIGNED_INT, 0);

	glBindTexture(GL_TEXTURE_2D, 0);
	glBindVertexArray(0);
}

void Demo::BuildGrassWall() {
	glGenTextures(1, &textureWall);
	glBindTexture(GL_TEXTURE_2D, textureWall);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	int width, height;
	unsigned char* image = SOIL_load_image("grass.png", &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);

	float vertices[] = {
		-2.5, -5.0, 0, 0, 0,  // 0
		2.5, -5.0, 0, 1, 0,   // 1
		3.5, -5.0, 0.5, 0, 0,   // 2
		3.5, -5.0, 1.0, 1, 0,  // 3

		2.5, -5.0, 1.5, 0, 0,  // 4
		-2.5, -5.0, 1.5, 1, 0,  // 5
		-3.5, -5.0, 1.0, 0, 0,  // 6
		-3.5, -5.0, 0.5, 1, 0,  // 7

		// top
		-2.5, 0, 0, 0, 1,  // 8
		2.5, 0, 0, 1, 1,   // 9
		3.5, 0, 0.5, 0, 1,   // 10
		3.5, 0, 1.0, 1, 1,  // 11

		2.5, 0, 1.5, 0, 1,  // 12
		-2.5, 0, 1.5, 1, 1,  // 13
		-3.5, 0, 1.0, 0, 1,  // 14
		-3.5, 0, 0.5, 1, 1,  // 15

		-2.5, 0, 0.75, 0, 1,  // 16
		2.5, 0, 0.75, 1, 1,   // 17																																																		 0.5, 1, -1, 0, 1,   // 47
	};

	unsigned int indices[] = {
		0,  1,  8,  1,  8,  9,   // front
		1,  2,  9,  2,  9,  10,   // right
		2,  3,  10, 3,  10, 11,  // back
		3,  4,  11, 4, 11, 12,  // left
		4,  5,  12, 5, 12, 13,  // upper
		5,  6,  13, 6, 13, 14,   // bottom
		6,  7,  14, 7, 14, 15,
		0,  7,  15, 0, 8, 15,
		8,  9,  13, 9, 12, 13,
		8,  15, 16, 14, 15, 16,
		13, 14, 16, 9, 10, 17,
		10, 11, 17, 11, 12, 17
	};

	glGenVertexArrays(1, &VAOWall);
	glGenBuffers(1, &VBOWall);
	glGenBuffers(1, &EBOWall);
	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(VAOWall);

	glBindBuffer(GL_ARRAY_BUFFER, VBOWall);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBOWall);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// define position pointer layout 0
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(0 * sizeof(GLfloat)));
	glEnableVertexAttribArray(0);

	// define texcoord pointer layout 1
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void Demo::DrawGrassWall() {
	glUseProgram(shaderProgram);

	glActiveTexture(GL_TEXTURE5);
	glBindTexture(GL_TEXTURE_2D, textureWall);
	glUniform1i(glGetUniformLocation(this->shaderProgram, "ourTexture"), 5);

	glBindVertexArray(VAOWall); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized

	glm::mat4 model;

	model = glm::translate(model, glm::vec3(0, 1, -10));

	model = glm::scale(model, glm::vec3(2, 1.2, 1));

	//model = glm::rotate(model, 90.0f, glm::vec3(0, 0, 0));

	GLint modelLoc = glGetUniformLocation(this->shaderProgram, "model");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

	glDrawElements(GL_TRIANGLES, 84, GL_UNSIGNED_INT, 0);

	glBindTexture(GL_TEXTURE_2D, 0);
	glBindVertexArray(0);
}

void Demo::BuildGrassWall1() {
	glGenTextures(1, &textureWall);
	glBindTexture(GL_TEXTURE_2D, textureWall);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	int width, height;
	unsigned char* image = SOIL_load_image("grass.png", &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);

	float vertices[] = {
		-2.5, -5.0, 0, 0, 0,  // 0
		2.5, -5.0, 0, 1, 0,   // 1
		3.5, -5.0, 0.5, 0, 0,   // 2
		3.5, -5.0, 1.0, 1, 0,  // 3

		2.5, -5.0, 1.5, 0, 0,  // 4
		-2.5, -5.0, 1.5, 1, 0,  // 5
		-3.5, -5.0, 1.0, 0, 0,  // 6
		-3.5, -5.0, 0.5, 1, 0,  // 7

								// top
								-2.5, 0, 0, 0, 1,  // 8
								2.5, 0, 0, 1, 1,   // 9
								3.5, 0, 0.5, 0, 1,   // 10
								3.5, 0, 1.0, 1, 1,  // 11

								2.5, 0, 1.5, 0, 1,  // 12
								-2.5, 0, 1.5, 1, 1,  // 13
								-3.5, 0, 1.0, 0, 1,  // 14
								-3.5, 0, 0.5, 1, 1,  // 15

								-2.5, 0, 0.75, 0, 1,  // 16
								2.5, 0, 0.75, 1, 1,   // 17																																																		 0.5, 1, -1, 0, 1,   // 47
	};

	unsigned int indices[] = {
		0,  1,  8,  1,  8,  9,   // front
		1,  2,  9,  2,  9,  10,   // right
		2,  3,  10, 3,  10, 11,  // back
		3,  4,  11, 4, 11, 12,  // left
		4,  5,  12, 5, 12, 13,  // upper
		5,  6,  13, 6, 13, 14,   // bottom
		6,  7,  14, 7, 14, 15,
		0,  7,  15, 0, 8, 15,
		8,  9,  13, 9, 12, 13,
		8,  15, 16, 14, 15, 16,
		13, 14, 16, 9, 10, 17,
		10, 11, 17, 11, 12, 17
	};

	glGenVertexArrays(1, &VAOWall1);
	glGenBuffers(1, &VBOWall1);
	glGenBuffers(1, &EBOWall1);
	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(VAOWall1);

	glBindBuffer(GL_ARRAY_BUFFER, VBOWall1);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBOWall1);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// define position pointer layout 0
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(0 * sizeof(GLfloat)));
	glEnableVertexAttribArray(0);

	// define texcoord pointer layout 1
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void Demo::DrawGrassWall1() {
	glUseProgram(shaderProgram);

	glActiveTexture(GL_TEXTURE6);
	glBindTexture(GL_TEXTURE_2D, textureWall);
	glUniform1i(glGetUniformLocation(this->shaderProgram, "ourTexture"), 6);

	glBindVertexArray(VAOWall1); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized

	glm::mat4 model;

	model = glm::translate(model, glm::vec3(11, 1, -1));

	model = glm::scale(model, glm::vec3(2, 1.2, 1));

	model = glm::rotate(model, 90.0f, glm::vec3(0, 1, 0));

	GLint modelLoc = glGetUniformLocation(this->shaderProgram, "model");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

	glDrawElements(GL_TRIANGLES, 84, GL_UNSIGNED_INT, 0);

	glBindTexture(GL_TEXTURE_2D, 0);
	glBindVertexArray(0);
}

void Demo::BuildGrassWall2() {
	glGenTextures(1, &textureWall);
	glBindTexture(GL_TEXTURE_2D, textureWall);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	int width, height;
	unsigned char* image = SOIL_load_image("grass.png", &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);

	float vertices[] = {
		-2.5, -5.0, 0, 0, 0,  // 0
		2.5, -5.0, 0, 1, 0,   // 1
		3.5, -5.0, 0.5, 0, 0,   // 2
		3.5, -5.0, 1.0, 1, 0,  // 3

		2.5, -5.0, 1.5, 0, 0,  // 4
		-2.5, -5.0, 1.5, 1, 0,  // 5
		-3.5, -5.0, 1.0, 0, 0,  // 6
		-3.5, -5.0, 0.5, 1, 0,  // 7

								// top
								-2.5, 0, 0, 0, 1,  // 8
								2.5, 0, 0, 1, 1,   // 9
								3.5, 0, 0.5, 0, 1,   // 10
								3.5, 0, 1.0, 1, 1,  // 11

								2.5, 0, 1.5, 0, 1,  // 12
								-2.5, 0, 1.5, 1, 1,  // 13
								-3.5, 0, 1.0, 0, 1,  // 14
								-3.5, 0, 0.5, 1, 1,  // 15

								-2.5, 0, 0.75, 0, 1,  // 16
								2.5, 0, 0.75, 1, 1,   // 17																																																		 0.5, 1, -1, 0, 1,   // 47
	};

	unsigned int indices[] = {
		0,  1,  8,  1,  8,  9,   // front
		1,  2,  9,  2,  9,  10,   // right
		2,  3,  10, 3,  10, 11,  // back
		3,  4,  11, 4, 11, 12,  // left
		4,  5,  12, 5, 12, 13,  // upper
		5,  6,  13, 6, 13, 14,   // bottom
		6,  7,  14, 7, 14, 15,
		0,  7,  15, 0, 8, 15,
		8,  9,  13, 9, 12, 13,
		8,  15, 16, 14, 15, 16,
		13, 14, 16, 9, 10, 17,
		10, 11, 17, 11, 12, 17
	};

	glGenVertexArrays(1, &VAOWall2);
	glGenBuffers(1, &VBOWall2);
	glGenBuffers(1, &EBOWall2);
	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(VAOWall2);

	glBindBuffer(GL_ARRAY_BUFFER, VBOWall2);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBOWall2);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// define position pointer layout 0
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(0 * sizeof(GLfloat)));
	glEnableVertexAttribArray(0);

	// define texcoord pointer layout 1
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void Demo::DrawGrassWall2() {
	glUseProgram(shaderProgram);

	glActiveTexture(GL_TEXTURE7);
	glBindTexture(GL_TEXTURE_2D, textureWall);
	glUniform1i(glGetUniformLocation(this->shaderProgram, "ourTexture"), 7);

	glBindVertexArray(VAOWall2); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized

	glm::mat4 model;

	model = glm::translate(model, glm::vec3(-11, 1, -1));

	model = glm::scale(model, glm::vec3(2, 1.2, 1));

	model = glm::rotate(model, 90.0f, glm::vec3(0, -1, 0));

	GLint modelLoc = glGetUniformLocation(this->shaderProgram, "model");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

	glDrawElements(GL_TRIANGLES, 84, GL_UNSIGNED_INT, 0);

	glBindTexture(GL_TEXTURE_2D, 0);
	glBindVertexArray(0);
}

void Demo::BuildGrassWall3() {
	glGenTextures(1, &textureWall);
	glBindTexture(GL_TEXTURE_2D, textureWall);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	int width, height;
	unsigned char* image = SOIL_load_image("grass.png", &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);

	float vertices[] = {
		-2.5, -5.0, 0, 0, 0,  // 0
		2.5, -5.0, 0, 1, 0,   // 1
		3.5, -5.0, 0.5, 0, 0,   // 2
		3.5, -5.0, 1.0, 1, 0,  // 3

		2.5, -5.0, 1.5, 0, 0,  // 4
		-2.5, -5.0, 1.5, 1, 0,  // 5
		-3.5, -5.0, 1.0, 0, 0,  // 6
		-3.5, -5.0, 0.5, 1, 0,  // 7

								// top
								-2.5, 0, 0, 0, 1,  // 8
								2.5, 0, 0, 1, 1,   // 9
								3.5, 0, 0.5, 0, 1,   // 10
								3.5, 0, 1.0, 1, 1,  // 11

								2.5, 0, 1.5, 0, 1,  // 12
								-2.5, 0, 1.5, 1, 1,  // 13
								-3.5, 0, 1.0, 0, 1,  // 14
								-3.5, 0, 0.5, 1, 1,  // 15

								-2.5, 0, 0.75, 0, 1,  // 16
								2.5, 0, 0.75, 1, 1,   // 17																																																		 0.5, 1, -1, 0, 1,   // 47
	};

	unsigned int indices[] = {
		0,  1,  8,  1,  8,  9,   // front
		1,  2,  9,  2,  9,  10,   // right
		2,  3,  10, 3,  10, 11,  // back
		3,  4,  11, 4, 11, 12,  // left
		4,  5,  12, 5, 12, 13,  // upper
		5,  6,  13, 6, 13, 14,   // bottom
		6,  7,  14, 7, 14, 15,
		0,  7,  15, 0, 8, 15,
		8,  9,  13, 9, 12, 13,
		8,  15, 16, 14, 15, 16,
		13, 14, 16, 9, 10, 17,
		10, 11, 17, 11, 12, 17
	};

	glGenVertexArrays(1, &VAOWall3);
	glGenBuffers(1, &VBOWall3);
	glGenBuffers(1, &EBOWall3);
	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(VAOWall3);

	glBindBuffer(GL_ARRAY_BUFFER, VBOWall3);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBOWall3);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// define position pointer layout 0
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(0 * sizeof(GLfloat)));
	glEnableVertexAttribArray(0);

	// define texcoord pointer layout 1
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void Demo::DrawGrassWall3() {
	glUseProgram(shaderProgram);

	glActiveTexture(GL_TEXTURE8);
	glBindTexture(GL_TEXTURE_2D, textureWall);
	glUniform1i(glGetUniformLocation(this->shaderProgram, "ourTexture"), 8);

	glBindVertexArray(VAOWall3); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized

	glm::mat4 model;

	model = glm::translate(model, glm::vec3(-12, 1, 11));

	model = glm::scale(model, glm::vec3(2, 1.2, 1));

	model = glm::rotate(model, 180.0f, glm::vec3(0, -1, 0));

	GLint modelLoc = glGetUniformLocation(this->shaderProgram, "model");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

	glDrawElements(GL_TRIANGLES, 84, GL_UNSIGNED_INT, 0);

	glBindTexture(GL_TEXTURE_2D, 0);
	glBindVertexArray(0);
}

void Demo::BuildGrassWall4() {
	glGenTextures(1, &textureWall);
	glBindTexture(GL_TEXTURE_2D, textureWall);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	int width, height;
	unsigned char* image = SOIL_load_image("grass.png", &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);

	float vertices[] = {
		-2.5, -5.0, 0, 0, 0,  // 0
		2.5, -5.0, 0, 1, 0,   // 1
		3.5, -5.0, 0.5, 0, 0,   // 2
		3.5, -5.0, 1.0, 1, 0,  // 3

		2.5, -5.0, 1.5, 0, 0,  // 4
		-2.5, -5.0, 1.5, 1, 0,  // 5
		-3.5, -5.0, 1.0, 0, 0,  // 6
		-3.5, -5.0, 0.5, 1, 0,  // 7

								// top
								-2.5, 0, 0, 0, 1,  // 8
								2.5, 0, 0, 1, 1,   // 9
								3.5, 0, 0.5, 0, 1,   // 10
								3.5, 0, 1.0, 1, 1,  // 11

								2.5, 0, 1.5, 0, 1,  // 12
								-2.5, 0, 1.5, 1, 1,  // 13
								-3.5, 0, 1.0, 0, 1,  // 14
								-3.5, 0, 0.5, 1, 1,  // 15

								-2.5, 0, 0.75, 0, 1,  // 16
								2.5, 0, 0.75, 1, 1,   // 17																																																		 0.5, 1, -1, 0, 1,   // 47
	};

	unsigned int indices[] = {
		0,  1,  8,  1,  8,  9,   // front
		1,  2,  9,  2,  9,  10,   // right
		2,  3,  10, 3,  10, 11,  // back
		3,  4,  11, 4, 11, 12,  // left
		4,  5,  12, 5, 12, 13,  // upper
		5,  6,  13, 6, 13, 14,   // bottom
		6,  7,  14, 7, 14, 15,
		0,  7,  15, 0, 8, 15,
		8,  9,  13, 9, 12, 13,
		8,  15, 16, 14, 15, 16,
		13, 14, 16, 9, 10, 17,
		10, 11, 17, 11, 12, 17
	};

	glGenVertexArrays(1, &VAOWall4);
	glGenBuffers(1, &VBOWall4);
	glGenBuffers(1, &EBOWall4);
	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(VAOWall4);

	glBindBuffer(GL_ARRAY_BUFFER, VBOWall4);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBOWall4);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// define position pointer layout 0
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(0 * sizeof(GLfloat)));
	glEnableVertexAttribArray(0);

	// define texcoord pointer layout 1
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void Demo::DrawGrassWall4() {
	glUseProgram(shaderProgram);

	glActiveTexture(GL_TEXTURE9);
	glBindTexture(GL_TEXTURE_2D, textureWall);
	glUniform1i(glGetUniformLocation(this->shaderProgram, "ourTexture"), 9);

	glBindVertexArray(VAOWall4); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized

	glm::mat4 model;

	model = glm::translate(model, glm::vec3(12, 1, 11));

	model = glm::scale(model, glm::vec3(2, 1.2, 1));

	model = glm::rotate(model, 180.0f, glm::vec3(0, 1, 0));

	GLint modelLoc = glGetUniformLocation(this->shaderProgram, "model");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

	glDrawElements(GL_TRIANGLES, 84, GL_UNSIGNED_INT, 0);

	glBindTexture(GL_TEXTURE_2D, 0);
	glBindVertexArray(0);
}

void Demo::TBuildFence() {
	glGenTextures(1, &textureFence);
	glBindTexture(GL_TEXTURE_2D, textureFence);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	int width, height;
	unsigned char* image = SOIL_load_image("kayu.jpg", &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);

	float vertices[] = {
		// format position, tex coords //vertex index
		1.0 , 3.0 , 0.3 , 0.5 , 1 ,	//0
		1.0 , 3.0 , -0.3 , 1 , 1 ,	//1
		-1.0 , 3.0 , -0.3 ,	0.5 , 1 ,	//2
		-1.0 , 3.0 , 0.3 , 0 , 1 ,	//3
		1.0 , -3.0 , 0.3 , 0.5 , 0 ,	//4 
		1.0 , -3.0 , -0.3 , 1 , 0 , //5
		-1.0 , -3.0 , -0.3 , 0.5 , 0 ,//6
		-1.0 , -3.0 , 0.3 , 0 , 0 , //7	

		-1.6 , 3.0 , 0.3 , 0.5 , 1 ,	//8
		-1.6 , 3.0 , -0.3 , 1 , 1 ,	//9
		-3.6 , 3.0 , -0.3 ,	0.5 , 1 ,	//10
		-3.6 , 3.0 , 0.3 , 0 , 1 ,	//11
		-1.6 , -3.0 , 0.3 , 0.5 , 0 ,	//12
		-1.6 , -3.0 , -0.3 , 1 , 0 ,//13
		-3.6 , -3.0 , -0.3 , 0.5 , 0 ,//14
		-3.6 , -3.0 , 0.3 , 0 , 0 , //15

		3.6 , 3.0 , 0.3 , 0.5 , 1 ,	//16
		3.6 , 3.0 , -0.3 , 1 , 1 ,	//17
		1.6 , 3.0 , -0.3 ,	0.5 , 1 ,	//18
		1.6 , 3.0 , 0.3 , 0 , 1 ,	//19
		3.6 , -3.0 , 0.3 , 0.5 , 0 ,	//20
		3.6 , -3.0 , -0.3 , 1 , 0 , //21
		1.6 , -3.0 , -0.3 , 0.5 , 0 , //22
		1.6 , -3.0 , 0.3 , 0 , 0 ,  //23

		4.4 , 1.6 , -0.3 , 0.5 , 0 ,	//24
		4.4 , 1.6 , -1.1 , 1 , 0 ,	//25
		-4.4 , 1.6 , -1.1 ,	1 , 1 ,	//26
		-4.4 , 1.6 , -0.3 , 0.5 , 1 ,	//27
		4.4 , 0 , -0.3 , 0 , 0 ,	//28
		4.4 , 0 , -1.1 , 0.5 , 0 ,	//29
		-4.4 , 0 , -1.1 , 0.5 , 1 ,	//30
		-4.4 , 0 , -0.3 , 0 , 1 ,	//31

		4.4 , -2.0 , -0.3 , 0.5 , 0 ,	//32
		4.4 , -2.0 , -1.1 , 1 , 0 ,	//33
		-4.4 , -2.0 , -1.1 , 1 , 1 ,//34
		-4.4 , -2.0 , -0.3 , 0.5 , 1 ,//35
		4.4 , -3.6 , -0.3 , 0 , 0 ,	//36
		4.4 , -3.6 , -1.1 , 0.5 , 0 , //37
		-4.4 , -3.6 , -1.1 , 0.5 , 1 ,//38
		-4.4 , -3.6 , -0.3 , 0 , 1 //39																																																		 0.5, 1, -1, 0, 1,   // 47
	};

	unsigned int indices[] = {
		0 , 1 , 2 , 0 , 2 , 3 ,
		0 , 4 , 5 , 0 , 1 , 5 ,
		0 , 3 , 7 , 0 , 7 , 4 ,
		4 , 5 , 6 , 4 , 6 , 7 ,
		2 , 3 , 7 , 2 , 7 , 6 ,
		2 , 1 , 5 , 2 , 5 , 6 ,

		8 , 9 , 10 , 8 , 10 , 11 ,
		8 , 12 , 13 , 8 , 9 , 13 ,
		8 , 11 , 15 , 8 , 15 , 12 ,
		14, 10, 11, 14, 11, 15,
		14, 15, 12, 14, 13, 12,
		14, 9, 10, 14, 9, 13,

		16 , 17 , 18 , 16 , 18 , 19 ,
		16, 20, 21, 16, 21, 17,
		16, 23, 20, 16, 23, 19,
		20, 21, 22, 20, 22, 23,
		22, 17, 18, 22, 21, 17,
		22, 23, 19, 22, 19, 18,

		24, 26, 25, 24, 26, 27,
		24, 31, 27, 24, 31, 28,
		24, 29, 25, 24, 29, 28,
		30, 28, 31, 30, 28, 29,
		30, 27, 31, 30, 27, 26,
		30, 25, 26, 30, 25, 29,

		32, 34, 33, 32, 34, 35,
		32, 39, 35, 32, 39, 36,
		32, 37, 36, 32, 37, 33,
		38, 35, 39, 38, 35, 34,
		38, 33, 37, 38, 33, 34
	};

	glGenVertexArrays(1, &VAOFence);
	glGenBuffers(1, &VBOFence);
	glGenBuffers(1, &EBOFence);
	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(VAOFence);

	glBindBuffer(GL_ARRAY_BUFFER, VBOFence);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBOFence);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// define position pointer layout 0
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(0 * sizeof(GLfloat)));
	glEnableVertexAttribArray(0);

	// define texcoord pointer layout 1
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void Demo::TDrawFence() {
	glUseProgram(shaderProgram);

	glActiveTexture(GL_TEXTURE4);
	glBindTexture(GL_TEXTURE_2D, textureFence);
	glUniform1i(glGetUniformLocation(this->shaderProgram, "ourTexture"), 4);

	glBindVertexArray(VAOFence); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized

	glm::mat4 model;

	model = glm::translate(model, glm::vec3(0, 0.6, 14));

	model = glm::scale(model, glm::vec3(0.2, 0.2, 0.2));

	//model = glm::rotate(model, 90.0f, glm::vec3(0, 0, 0));

	GLint modelLoc = glGetUniformLocation(this->shaderProgram, "model");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

	glDrawElements(GL_TRIANGLES, 60 * 3, GL_UNSIGNED_INT, 0);

	glBindTexture(GL_TEXTURE_2D, 0);
	glBindVertexArray(0);
}

void Demo::BuildPlane()
{
	// Load and create a texture 
	glGenTextures(1, &texturePlane);
	glBindTexture(GL_TEXTURE_2D, texturePlane);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	int width, height;
	unsigned char* image = SOIL_load_image("grass_tile.png", &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);

	// Build geometry
	GLfloat vertices[] = {
		// format position, tex coords
		// bottom
		-50.0, 0, -50.0,  0,  0,
		 50.0, 0, -50.0, 50,  0,
		 50.0, 0,  50.0, 50, 50,
		-50.0, 0,  50.0,  0, 50,

	};

	GLuint indices[] = { 0,  2,  1,  0,  3,  2 };

	glGenVertexArrays(1, &VAOPlane);
	glGenBuffers(1, &VBOPlane);
	glGenBuffers(1, &EBOPlane);

	glBindVertexArray(VAOPlane);

	glBindBuffer(GL_ARRAY_BUFFER, VBOPlane);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBOPlane);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// Position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), 0);
	glEnableVertexAttribArray(0);
	// TexCoord attribute
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	glBindVertexArray(0); // Unbind VAO
}

void Demo::DrawPlane()
{
	glUseProgram(shaderProgram);

	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, texturePlane);
	glUniform1i(glGetUniformLocation(this->shaderProgram, "ourTexture"), 1);

	glBindVertexArray(VAOPlane); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized

	glm::mat4 model;
	GLint modelLoc = glGetUniformLocation(this->shaderProgram, "model");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

	glBindTexture(GL_TEXTURE_2D, 0);
	glBindVertexArray(0);
}

void Demo::BuildSkybox()
{
	// Load and create a texture 
	glGenTextures(1, &textureSkybox);
	glBindTexture(GL_TEXTURE_2D, textureSkybox);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	int width, height;
	unsigned char* image = SOIL_load_image("skybox1.png", &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);

	// Build geometry
	GLfloat vertices[] = {
		// format position, tex coords
		-100.0, 80.0, -100.0,  1,  0.75, //0
		100.0, 80.0 , -100.0, 1,  0.5, //1
		100.0, 80.0 ,  100.0, 0.75, 0.5, //2
		-100.0, 80.0 ,  100.0,  0.75, 0.75, //3

		100.0, 80.0 , -100.0, 1,  0.5, //4
		100.0, 80.0 ,  100.0, 0.75, 0.5, //5
		100.0 , -80.0 , -100.0 , 1, 0.25, //6
		100.0 , -80 , 100 , 0.75 , 0.25, //7

		100.0, 80.0 ,  100.0, 0.75, 0.5, //8
		-100.0, 80.0 ,  100.0,  0.5, 0.5, //9
		100.0 , -80 , 100 , 0.75 , 0.25, //10
		-100, -80, 100 ,  0.5, 0.25, //11         

		- 100.0, 80.0 ,  100.0,  0.5, 0.5, //12
		-100.0, 80.0, -100.0,  0.25,  0.5, //13
		-100, -80, 100 ,  0.5 , 0.25, //14
		-100, -80 , -100 , 0.25 , 0.25,//15

		-100.0, 80.0, -100.0,  0.25,  0.5, //16
		100.0, 80.0 , -100.0, 0,  0.5, //17
		-100, -80 , -100.0 , 0.25, 0.25,//18
		100.0 , -80.0 , -100.0 , 0, 0.25 //19
	};

	GLuint indices[] = { 
		0,  2,  1,  0,  3,  2, 
		5,  6 , 4 , 5 , 6 , 7,
		9 , 8 , 10 , 9 , 10 , 11,
		12 , 15, 13  , 12 , 15, 14,
		16 , 19 , 17 , 16 , 19 , 18
	};

	glGenVertexArrays(1, &VAOSkybox);
	glGenBuffers(1, &VBOSkybox);
	glGenBuffers(1, &EBOSkybox);

	glBindVertexArray(VAOSkybox);

	glBindBuffer(GL_ARRAY_BUFFER, VBOSkybox);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBOSkybox);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// Position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), 0);
	glEnableVertexAttribArray(0);
	// TexCoord attribute
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	glBindVertexArray(0); // Unbind VAO
}

void Demo::DrawSkybox()
{
	glUseProgram(shaderProgram);

	glActiveTexture(GL_TEXTURE10);
	glBindTexture(GL_TEXTURE_2D, textureSkybox);
	glUniform1i(glGetUniformLocation(this->shaderProgram, "ourTexture"), 10);

	glBindVertexArray(VAOSkybox); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized

	glm::mat4 model;
	GLint modelLoc = glGetUniformLocation(this->shaderProgram, "model");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

	glDrawElements(GL_TRIANGLES, 10 * 3, GL_UNSIGNED_INT, 0);

	glBindTexture(GL_TEXTURE_2D, 0);
	glBindVertexArray(0);
}

void Demo::InitCamera()
{
	posCamX = 0.0f;
	posCamY = 1.0f;
	posCamZ = 8.0f;
	viewCamX = 0.0f;
	viewCamY = 1.0f;
	viewCamZ = 0.0f;
	upCamX = 0.0f;
	upCamY = 1.0f;
	upCamZ = 0.0f;
	CAMERA_SPEED = 0.001f;
	fovy = 50.0f;
	glfwSetInputMode(this->window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

void Demo::MoveCamera(float speed)
{
	float x = viewCamX - posCamX;
	float z = viewCamZ - posCamZ;
	// forward positive cameraspeed and backward negative -cameraspeed.
	posCamX = posCamX + x * speed;
	posCamZ = posCamZ + z * speed;
	viewCamX = viewCamX + x * speed;
	viewCamZ = viewCamZ + z * speed;
}

void Demo::StrafeCamera(float speed)
{
	float x = viewCamX - posCamX;
	float z = viewCamZ - posCamZ;
	float orthoX = -z;
	float orthoZ = x;

	// left positive cameraspeed and right negative -cameraspeed.
	posCamX = posCamX + orthoX * speed;
	posCamZ = posCamZ + orthoZ * speed;
	viewCamX = viewCamX + orthoX * speed;
	viewCamZ = viewCamZ + orthoZ * speed;
}

void Demo::RotateCamera(float speed)
{
	float x = viewCamX - posCamX;
	float z = viewCamZ - posCamZ;
	viewCamZ = (float)(posCamZ + glm::sin(speed) * x + glm::cos(speed) * z);
	viewCamX = (float)(posCamX + glm::cos(speed) * x - glm::sin(speed) * z);
}

int main(int argc, char** argv) {
	RenderEngine &app = Demo();
	app.Start("Backyard", 1280, 720, false, false);
}