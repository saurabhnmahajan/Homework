#include "glsupport.h"
#include "matrix4.h"

GLuint program;
GLuint vertexBO;
GLuint normalBO;
GLuint positionAttribute;
GLuint normalAttribute;
GLuint modelviewMatrixUniformLocation;
GLuint projectionMatrixUniformLocation;
GLuint normalMatrixUniformLocation;
GLuint colorUniform;

void display(void) {
    glUseProgram(program);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    glBindBuffer(GL_ARRAY_BUFFER, vertexBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, normalBO);
    
    glVertexAttribPointer(positionAttribute, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glVertexAttribPointer(normalAttribute, 3, GL_FLOAT, GL_FALSE, 0, 0);
    
    glEnableVertexAttribArray(positionAttribute);
    glEnableVertexAttribArray(normalAttribute);
    
    Matrix4 eyeMatrix;
    eyeMatrix = eyeMatrix.makeTranslation(Cvec3(0.0, 0.0, 30));
    Matrix4 projectionMatrix;
    projectionMatrix = projectionMatrix.makeProjection(45, 1.0, -0.1, -100);
    GLfloat glmatrixProjection[16];
    projectionMatrix.writeToColumnMajorMatrix(glmatrixProjection);
    glUniformMatrix4fv(projectionMatrixUniformLocation, 1, false, glmatrixProjection);
    int timeSinceStart = glutGet(GLUT_ELAPSED_TIME);
    
    //creating first cube and its normal
    Matrix4 objectMatrix;
    objectMatrix = objectMatrix.makeTranslation(Cvec3(0, 0, 0)) * objectMatrix.makeYRotation(timeSinceStart/25.0f);
    Matrix4 modelViewMatrix = inv(eyeMatrix) * objectMatrix;
    GLfloat glmatrix[16];
    modelViewMatrix.writeToColumnMajorMatrix(glmatrix);
    glUniformMatrix4fv(modelviewMatrixUniformLocation, 1, false, glmatrix);
    Matrix4 normalmatrix = normalMatrix(modelViewMatrix);
    GLfloat glmatrixNormal[16];
    normalmatrix.writeToColumnMajorMatrix(glmatrixNormal);
    glUniformMatrix4fv(normalMatrixUniformLocation, 1, false, glmatrixNormal);
    GLfloat color[] = { 1.0f, 0.0f, 0.0f};
    glUniform3fv(colorUniform, 1, color);
    glDrawArrays(GL_TRIANGLES, 0, 36);

    //creating second cube
    objectMatrix = objectMatrix.makeTranslation(Cvec3(-5, 0, 0)) * objectMatrix.makeXRotation(timeSinceStart/10.0f);
    modelViewMatrix *= objectMatrix;
    modelViewMatrix.writeToColumnMajorMatrix(glmatrix);
    glUniformMatrix4fv(modelviewMatrixUniformLocation, 1, false, glmatrix);
    normalmatrix = normalMatrix(modelViewMatrix);
    normalmatrix.writeToColumnMajorMatrix(glmatrixNormal);
    glUniformMatrix4fv(normalMatrixUniformLocation, 1, false, glmatrixNormal);
    color[1] = 1.0f;
    glUniform3fv(colorUniform, 1, color);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    
    //creating third cube
    objectMatrix = objectMatrix.makeTranslation(Cvec3(0, 5, 0)) * objectMatrix.makeYRotation(timeSinceStart/5.0f);
    modelViewMatrix *= objectMatrix;
    modelViewMatrix.writeToColumnMajorMatrix(glmatrix);
    glUniformMatrix4fv(modelviewMatrixUniformLocation, 1, false, glmatrix);
    normalmatrix = normalMatrix(modelViewMatrix);
    normalmatrix.writeToColumnMajorMatrix(glmatrixNormal);
    glUniformMatrix4fv(normalMatrixUniformLocation, 1, false, glmatrixNormal);
    color[2] = 1.0f;
    glUniform3fv(colorUniform, 1, color);
    glDrawArrays(GL_TRIANGLES, 0, 36);

    glDisableVertexAttribArray(positionAttribute);
    glDisableVertexAttribArray(normalAttribute);
    
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glClearColor(0.5, 0.5, 0.5, 1);
    glutSwapBuffers();
}

void init() {
    glClearDepth(0.0f);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_GREATER);
    
    program = glCreateProgram();
    readAndCompileShader(program, "vertex.glsl", "fragment.glsl");
    glUseProgram(program);
    
    positionAttribute = glGetAttribLocation(program, "position");
    normalAttribute = glGetAttribLocation(program, "normal");
    modelviewMatrixUniformLocation = glGetUniformLocation(program, "modelViewMatrix");
    projectionMatrixUniformLocation = glGetUniformLocation(program, "projectionMatrix");
    normalMatrixUniformLocation = glGetUniformLocation(program, "normalMatrix");
    colorUniform = glGetUniformLocation(program, "uColor");
    GLfloat cubeVerts[] = {
        -1.0f,-1.0f,-1.0f,
        -1.0f,-1.0f, 1.0f,
        -1.0f, 1.0f, 1.0f,
        1.0f, 1.0f,-1.0f,
        -1.0f,-1.0f,-1.0f,
        -1.0f, 1.0f,-1.0f,
        1.0f,-1.0f, 1.0f,
        -1.0f,-1.0f,-1.0f,
        1.0f,-1.0f,-1.0f,
        1.0f, 1.0f,-1.0f,
        1.0f,-1.0f,-1.0f,
        -1.0f,-1.0f,-1.0f,
        -1.0f,-1.0f,-1.0f,
        -1.0f, 1.0f, 1.0f,
        -1.0f, 1.0f,-1.0f,
        1.0f,-1.0f, 1.0f,
        -1.0f,-1.0f, 1.0f,
        -1.0f,-1.0f,-1.0f,
        -1.0f, 1.0f, 1.0f,
        -1.0f,-1.0f, 1.0f,
        1.0f,-1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f,-1.0f,-1.0f,
        1.0f, 1.0f,-1.0f,
        1.0f,-1.0f,-1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f,-1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f, 1.0f,-1.0f,
        -1.0f, 1.0f,-1.0f,
        1.0f, 1.0f, 1.0f,
        -1.0f, 1.0f,-1.0f,
        -1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        -1.0f, 1.0f, 1.0f,
        1.0f,-1.0f, 1.0f
    };
    GLfloat cubeNormals[] = {
        -1.0f, 0.0f, 0.0f,
        -1.0f, 0.0f, 0.0f,
        -1.0f, 0.0f, 0.0f,
        0.0f, 0.0f,-1.0f,
        0.0f, 0.0f,-1.0f,
        0.0f, 0.0f,-1.0f,
        0.0f,-1.0f,0.0f,
        0.0f,-1.0f,0.0f,
        0.0f,-1.0f,0.0f,
        0.0f, 0.0f,-1.0f,
        0.0f, 0.0f,-1.0f,
        0.0f, 0.0f,-1.0f,
        -1.0f, 0.0f,0.0f,
        -1.0f, 0.0f,0.0f,
        -1.0f, 0.0f,0.0f,
        0.0f,-1.0f, 0.0f,
        0.0f,-1.0f, 0.0f,
        0.0f,-1.0f,0.0f,
        0.0f, 0.0f, 1.0f,
        0.0f,0.0f, 1.0f,
        0.0f,0.0f, 1.0f,
        1.0f, 0.0f, 0.0f,
        1.0f,0.0f,0.0f,
        1.0f, 0.0f,0.0f,
        1.0f,0.0f,0.0f,
        1.0f, 0.0f, 0.0f,
        1.0f,0.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 1.0f,0.0f,
        0.0f, 1.0f,0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 1.0f,
        0.0f,0.0f, 1.0f
    };
    glGenBuffers(1, &vertexBO);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBO);
    glBufferData(GL_ARRAY_BUFFER, 36 * 3 * sizeof(GLfloat), cubeVerts, GL_STATIC_DRAW);
    glGenBuffers(1, &normalBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, normalBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 36 * 3 * sizeof(GLfloat), cubeNormals, GL_STATIC_DRAW);
}

void reshape(int w, int h) {
    glViewport(0, 0, w, h);
}

void idle(void) {
    glutPostRedisplay();
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(500, 500);
    glutCreateWindow("CS-6533");
    
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutIdleFunc(idle);
    
    init();
    glutMainLoop();
    return 0;
}
