//#include "cg.h"
//#include "camera.h"
//#include "vbocube.h"
//#include "vboplane.h"
//#include "vboteapot.h"
//
//void startup();
//void render();
//void shutdown();
//
//struct scene {
//	int width = 800, height = 600;
//	GLuint rendering_program;
//	GLuint vertex_array_object;
//
//	vec4 vertices[100];
//	vec4 colors[100];
//	unsigned int indices[100];
//	int num, numIndex;
//
//	// �𵨸� ����
//	VBOCube *cube;
//	VBOPlane *plane;
//	VBOTeapot *teapot;
//
//	// ���� ����
//	mat4 model, view, proj; 
//	//modeld : object->world ��ȯ ���
//	//view: world->camera��ǥ�� ��ȯ�ϴ� ���
//	GLint m_loc, v_loc, proj_loc, color_loc;
//
//	float theta; //theta ����
//};
//
//scene sc;
//
//
//// �� ó�� �ѹ� ����
//void startup()
//{
//	//------------------------------------------------------------------------
//	glEnable(GL_CULL_FACE);
//	glEnable(GL_DEPTH_TEST); glDepthFunc(GL_LEQUAL);
//	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
//	glShadeModel(GL_SMOOTH);
//
//	sc.rendering_program = compile_shaders("vview.glsl", "fview.glsl");
//	glUseProgram(sc.rendering_program);
//	
//	glGenVertexArrays(1, &sc.vertex_array_object);
//	glBindVertexArray(sc.vertex_array_object);
//
//	//vertex object����
//	sc.cube = new VBOCube();
//	sc.plane = new VBOPlane(5.0f, 10.0f, 10, 10); //planeũ�� //10-> 5.0
//	sc.teapot = new VBOTeapot(14, mat4(1.0));
//	
//	sc.view = LookAt(vec3(0.0f, 1.0f, 5.0f),
//					vec3(0.0f, 0.0f, 0.0f),
//					vec3(0.0f, 1.0f, 0.0f)); //////LookAt
//	//view ��Ŀ� ����
//
//	float cameraZ = sc.height * 0.5 / tan(radians(0.5*50.0));
////	sc.proj = Perspective(80.0f, (float)sc.width/(float)sc.height, (float)0.001*cameraZ, (float)10.0*cameraZ);
//	sc.proj = Perspective(50.0f, 1.33f, 0.5f, 100.0f);
////	sc.proj= Ortho(-5.0, 5.0,-2.0, 8.0, 0.3, 100.0); //ī�޶� lookat�� ���� ���ϴϱ� lookat�� ����ؼ� ortho()���������
//	//������ 0.3, �հ� 100
//
//	//ortho
//	sc.m_loc = glGetUniformLocation(sc.rendering_program, "m_matrix");
//	sc.v_loc = glGetUniformLocation(sc.rendering_program, "v_matrix");
//	sc.proj_loc = glGetUniformLocation(sc.rendering_program, "proj_matrix");
//	sc.color_loc = glGetUniformLocation(sc.rendering_program, "color");
//	//m_location v project color �� ���� ��ĳ־��ֱ�
//
//	glUniformMatrix4fv(sc.m_loc, 1, GL_FALSE, value_ptr(mat4(1.0))); 
//	glUniformMatrix4fv(sc.v_loc, 1, GL_FALSE, value_ptr(sc.view));
//	glUniformMatrix4fv(sc.proj_loc, 1, GL_TRUE, value_ptr(sc.proj));	
//
//	sc.theta = 0.0; //�ʱ�ȭ
//}
//
////  ����ؼ� �����
//void idle()
//{
//	glutPostRedisplay();
//	//ī�޶� ť�긦 �߽����� ���鼭 �����Ϸ���
//	//y�� 1�� ����
//	//xz��鿡�� ������ ������
//	/*
//	float x, z;
//	sc.theta += 0.001;
//	x = 5.0*cos(sc.theta);
//	z = 5.0*sin(sc.theta);
//	sc.view = lookAtRH(vec3(x, 1.0f, z), vec3(0.0f, 0.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f));
//	glUniformMatrix4fv(sc.v_loc, 1, GL_FALSE, value_ptr(sc.view));
//	*/
////	glutPostRedisplay();
//
//}
//
//void render()
//{
//	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//	glClearColor(0.6f, 0.6f, 0.6f, 1.0f);
//
//	glUseProgram(sc.rendering_program);
//
//	/////////////////
//	float x, z;
//	sc.theta += 0.0001; //0.001
//	x = 2.0*cos(sc.theta);
//	z = 2.0*sin(sc.theta);\
//	/* ����
//	sc.view = lookAtRH(vec3(0.0f, 1.0f, 5.0f),
//		vec3(0.0f, 0.0f, 0.0f),
//		vec3(0.0f, 1.0f, 0.0f));
//	*/
//	/*
//	sc.view = lookAtRH(vec3(x, 1.0f, z),  //LookAt()
//			vec3(0.0f, 0.0f, 0.0f),
//			vec3(0.0f, 1.0f, 0.0f));
//	*/
//	 
//	sc.view = lookAtRH(vec3(0.0f, 1.0f, 5.0f-sc.theta),
//		vec3(0.0f, 0.0f, -sc.theta),
//		vec3(0.0f, 1.0f, 0.0f));
//	
//	
//	glUniformMatrix4fv(sc.v_loc, 1, GL_FALSE, value_ptr(sc.view));
//
//	///////////////////////////////////////////////////
//
//	// floor
//	glUniformMatrix4fv(sc.m_loc, 1, GL_FALSE, value_ptr(mat4(1.0)));
//	glUniform4f(sc.color_loc, 0.3, 0.3, 0.3, 1.0);
//	sc.plane->render();
//
////	mat4 teapotmodel = rotate(mat4(1.0), (float)radians(-90.0), vec3(1.0, 0.0, 0.0));
////	sc.teapot->render();
//     
//	// Cube
//	mat4 model_base;
//	model_base = translate(mat4(1.0), vec3(0.0, 0.25, 0.0)); //������ �ݸ�ŭ �̵������ֱ� 0.25 
//	model_base = scale(model_base, vec3(1.0, 0.5, 1.0)); //y������ sacle down�Ȱ� 0.5��ŭ /���Ϸ��� 1,1,1
//	glUniformMatrix4fv(sc.m_loc, 1, GL_FALSE, value_ptr(model_base));
//	glUniform4f(sc.color_loc, 0.3, 0.2, 0.9, 1.0);
//	sc.cube->render();
//
//
//	//mat4 model_top;
//
//
//	
//	glutSwapBuffers();
//}
//
//
//void shutdown()
//{
//	glDeleteVertexArrays(1, &sc.vertex_array_object);
//	glDeleteProgram(sc.rendering_program);
//}
//
//int main(int argc, char **argv)
//{
//	glutInit(&argc, argv);
//	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH); 
//	// MAC
//	//glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH | GLUT_3_2_CORE_PROFILE);
//
//	glutInitWindowSize(sc.width, sc.height);
//	glutCreateWindow("3D Viewing");
//	glewInit();
//	version();
//
//	startup();
//	glutDisplayFunc(render);
//	glutIdleFunc(idle);
//
//	glutMainLoop();
//	shutdown();
//	return 0;
//}
