
#include "glsupport.h"

GLuint program;

GLuint vertexPosition;
GLuint vertexTexture;

GLuint positionAttribute;
GLuint texCoordAttribute;

GLuint imgTexture;

GLuint keyPressUniform;
GLuint positionUniform;

float textureOffset = 0.0;

void display(void) {
    glClear(GL_COLOR_BUFFER_BIT);
    
    glUseProgram(program);
    
    glUniform1f(keyPressUniform, textureOffset);
    
    glBindBuffer(GL_ARRAY_BUFFER, vertexPosition);
    glVertexAttribPointer(positionAttribute, 2, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(positionAttribute);
    
    glBindBuffer(GL_ARRAY_BUFFER, vertexTexture);
    glVertexAttribPointer(texCoordAttribute, 2, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(texCoordAttribute);
    
    imgTexture = loadGLTexture("img.png");
    glBindTexture(GL_TEXTURE_2D, imgTexture);

    glUniform2f(positionUniform, -0.5, 0.0);
    glDrawArrays(GL_TRIANGLES, 0, 6);

    glUniform2f(positionUniform, 0.5, 0.0);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_DST_ALPHA);
    glClearColor(0.5, 0.5, 0.5, 1);
    
    glDisableVertexAttribArray(positionAttribute);
    glDisableVertexAttribArray(texCoordAttribute);
    
    glutSwapBuffers();
}

void init() {
    program = glCreateProgram();
    
    readAndCompileShader(program, "vertex.glsl", "fragment.glsl");
    
    glUseProgram(program);
    
    positionAttribute = glGetAttribLocation(program, "position");
    texCoordAttribute = glGetAttribLocation(program, "texCoord");
    keyPressUniform = glGetUniformLocation(program, "keyPress");
    positionUniform = glGetUniformLocation(program, "modelPosition");
    
    glGenBuffers(1, &vertexPosition);
    glBindBuffer(GL_ARRAY_BUFFER, vertexPosition);
    GLfloat sqVerts[12] = {
        -0.5f, -1.0f,
        0.5f, 1.0f,
        0.5f, -1.0f,
        
        -0.5f, -1.0f,
        -0.5f, 1.0f,
        0.5f, 1.0f
    };
    glBufferData(GL_ARRAY_BUFFER, 12*sizeof(GLfloat), sqVerts, GL_STATIC_DRAW);
    
    glGenBuffers(1, &vertexTexture);
    glBindBuffer(GL_ARRAY_BUFFER, vertexTexture);
    GLfloat sqTexCoords[12] = {
        0.0f, 1.0f,
        1.0f, 0.0f,
        1.0f, 1.0f,
        
        0.0f, 1.0f,
        0.0f, 0.0f,
        1.0f, 0.0f
    };
    glBufferData(GL_ARRAY_BUFFER, 12*sizeof(GLfloat), sqTexCoords, GL_STATIC_DRAW);
}

void reshape(int w, int h) {
    glViewport(0, 0, w, h);
}

void idle(void) {
    glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y) {
    switch(key) {
        case 'u':
            textureOffset += 0.1;
            break;
        case 'd':
            textureOffset -= 0.1;
            break;
    }
}



int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutCreateWindow("CS-6533");
    
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutIdleFunc(idle);
    
    glutKeyboardFunc(keyboard);
    
    init();
    glutMainLoop();
    return 0;
}
