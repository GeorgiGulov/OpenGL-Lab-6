#include <iostream>
#include <glut.h>
#include <Glaux.h>
#include <stdlib.h>
#include <Windows.h>
#include <cmath>
#define _USE_MATH_DEFINES
#define ESCAPE '\033'
using namespace std;

int y = 0;
GLfloat ctrlpoints[4][4][3] = {
{ {-7.5, -2.0, -5.5}, {-3.5, -2.0,-7.5 },     {-2.5, -2.0, -7.5 },     {1.5, -2.0,-7.5}},
{ {-7.5, -2.0, -3.5}, {-3.5, -5.0 - y,-3.5 }, {-2.5, -5.0 - y, -3.5 }, {1.5, -2.0,-3.5}},
{ {-7.5, -2.0, -2.5}, {-3.5, -2.0, -2.5 },    {-2.5, -2.0, -2.5 },     {1.5, -2.0, -2.5}},
{ {-7.5, -2.0, 1.5},  {-3.5, -2.0, 1.5 },     {-2.5, -2.0, 1.5 },      {1.5, -2.0, 1.5}}
};

GLfloat light_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };    // Параметры ПО УМОЛЧАНИЮ для рассеянного цвета

const double M_PI = 3.14;
float angle = 5;    // Угол поворота
GLfloat xrot = 0;   // Кординаты для поворотов
GLfloat yrot = 0;
GLfloat yrot_obj = 0;
GLfloat zrot = 0;

int j = 1;

GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };   // Параметры ПО УМОЛЧАНИЮ для зеркального света
GLfloat light_position[] = { 0.0, 1.0, 10.0, 1.0 };   
GLfloat light_position_1[] = { 10.0 , 0.0 , -1.0 , 1.0 };      
GLfloat light_position_2[] = { -10.0 , 0.0 , -1.0 , 1.0 };     

 GLuint filter;  // Используемый фильтр для текстур

 GLuint fogMode[] = { GL_EXP, GL_EXP2, GL_LINEAR };    // Хранит три типа тумана
GLfloat fogColor[4] = { 0.5f, 0.61f, 0.65f, 0.9f };   // Цвет тумана
 GLuint fogfilter = 0;   // Тип используемого тумана
  bool  gp = 0;          // Включён ли Туман  

void Keyboard(unsigned char key, int x, int y) {    // обработка с клавы

    if (key == ESCAPE)
        exit(0);
    if (key == 'a') {
        yrot -= 7;
        glutPostRedisplay();
    }
    if (key == 'd') {
        yrot += 7;
        glutPostRedisplay();

    }
    if (key == 'q') {
        yrot_obj += 7;
        glutPostRedisplay();

    }
    if (key == 'e') {
        yrot_obj -= 7;
        glutPostRedisplay();

    }
    if (key == 'z') {
        zrot += 7;
        glutPostRedisplay();

    }
    if (key == 'c') {
        zrot -= 7;
        glutPostRedisplay();

    }
    if (key == 's') {
        if (gp == 0)
            gp++;
        else if (gp == 1)
            gp = 0;;
        glutPostRedisplay();
    }
}

GLuint theTorus; // инициализируем список

static void torus(int numc, int numt) {
    int i, j, k;
    //double s;
    //double t;
    //double x;
    //double y;
    //double z;

    //double twopi = 2 * (double)M_PI;

    for (i = 0; i < numc; i++) {
       
        glBegin(GL_QUADS); // Начинаем рисование четырехугольников (quads)

                                // Нижняя поверхность
        glTexCoord2f(0.5f, 0.5f);
        glVertex3f(-0.5f, -0.5f, -0.5f);        // Верхний правый угол текстуры и четырехугольник
        glTexCoord2f(0.0f, 0.5f);
        glVertex3f(0.5f, -0.5f, -0.5f);        // Верхний левый угол текстуры и четырехугольник
        glTexCoord2f(0.0f, 0.0f);
        glVertex3f(0.5f, -0.5f, 0.5f);        // Нижний левый угол текстуры и четырехугольник
        glTexCoord2f(0.5f, 0.0f);
        glVertex3f(-0.5f, -0.5f, 0.5f);        // Нижний правый угол текстуры и четырехугольник
                                
                                // Передняя поверхность
        glTexCoord2f(0.0f, 0.0f);
        glVertex3f(-0.5f, -0.5f, 0.5f);       // Нижний левый угол текстуры и четырехугольник
        glTexCoord2f(0.5f, 0.0f);
        glVertex3f(0.5f, -0.5f, 0.5f);        // Нижний правый угол текстуры и четырехугольник
        glTexCoord2f(0.5f, 0.5f);
        glVertex3f(0.5f, 0.5f, 0.5f);         // Верхний правый угол текстуры и четырехугольник
        glTexCoord2f(0.0f, 0.5f);
        glVertex3f(-0.5f, 0.5f, 0.5f);        // Верхний левый угол текстуры и четырехугольник

                                // Задняя поверхность
        glTexCoord2f(0.5f, 0.0f);
        glVertex3f(-0.5f, -0.5f, -0.5f);       // Нижний правый угол текстуры и четырехугольник
        glTexCoord2f(0.5f, 0.5f);
        glVertex3f(-0.5f, 0.5f, -0.5f);        // Верхний правый угол текстуры и четырехугольник
        glTexCoord2f(0.0f, 0.5f);
        glVertex3f(0.5f, 0.5f, -0.5f);         // Верхний левый угол текстуры и четырехугольник
        glTexCoord2f(0.0f, 0.0f);
        glVertex3f(0.5f, -0.5f, -0.5f);        // Нижний левый угол текстуры и четырехугольник

                                // Правая поверхность
        glTexCoord2f(0.5f, 0.0f);
        glVertex3f(0.5f, -0.5f, -0.5f);       // Нижний правый угол текстуры и четырехугольник
        glTexCoord2f(0.5f, 0.5f);
        glVertex3f(0.5f, 0.5f, -0.5f);        // Верхний правый угол текстуры и четырехугольник
        glTexCoord2f(0.0f, 0.5f);
        glVertex3f(0.5f, 0.5f, 0.5f);         // Верхний левый угол текстуры и четырехугольник
        glTexCoord2f(0.0f, 0.0f);
        glVertex3f(0.5f, -0.5f, 0.5f);        // Нижний левый угол текстуры и четырехугольник

                                // Левая поверхность
        glTexCoord2f(0.0f, 0.0f);
        glVertex3f(-0.5f, -0.5f, -0.5f);        // Нижний левый угол текстуры и четырехугольник
        glTexCoord2f(0.5f, 0.0f);
        glVertex3f(-0.5f, -0.5f, 0.5f);        // Нижний правый угол текстуры и четырехугольник
        glTexCoord2f(0.5f, 0.5f);
        glVertex3f(-0.5f, 0.5f, 0.5f);        // Верхний правый угол текстуры и четырехугольник
        glTexCoord2f(0.0f, 0.5f);
        glVertex3f(-0.5f, 0.5f, -0.5f);        // Верхний левый угол текстуры и четырехугольник

        glEnd();               // Закончили рисование четырехугольников
    }
}

/* Создание списка отображения с тором и инициализация */
static void init(void) {
   
    theTorus = glGenLists(1); // создаём место для одного списка
    glNewList(theTorus, GL_COMPILE); // создаём список в памяти
    srand(time(NULL));
    torus(20, 20);
    glEndList();

    glMap2f(GL_MAP2_VERTEX_3, 0, 1, 3, 4,  0, 1, 12, 4, &ctrlpoints[0][0][0]);
    glEnable(GL_MAP2_VERTEX_3);
    glMapGrid2f(20, 0.0, 1.0, 20, 0.0, 1.0);
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.4, 0.4, 0.4, 0.0);
}

void display(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glEnable(GL_LIGHT0); // включаем фонарик 0
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse); // задаём параметры для рассеянного света
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);// задаём параметры для зеркального света
    glLightfv(GL_LIGHT0, GL_POSITION, light_position); // заадаём позицию источника света
    glEnable(GL_LIGHT1);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, light_diffuse); // задаём параметры для рассеянного света
    glLightfv(GL_LIGHT1, GL_POSITION, light_position_1); // заадаём позицию источника света
    glEnable(GL_LIGHT2);
    glLightfv(GL_LIGHT2, GL_SPECULAR, light_specular);// задаём параметры для зеркального света
    glLightfv(GL_LIGHT2, GL_POSITION, light_position_2); // заадаём позицию источника света
    glPopMatrix();

    glPushMatrix();
    glColor3f(1, 1, 1);
    glRotatef(85.0, 1.0, 1.0, 1.0); // поворот, чтобы не было пересченией
    
    for (j = 0; j <= 8; j++) {      // отрисовка линий для поверхности
        glBegin(GL_LINE_STRIP);
        for (int i = 0; i <= 30; i++)
            glEvalCoord2f((GLfloat)i / 30.0, (GLfloat)j / 8.0);
        glEnd();
        glBegin(GL_LINE_STRIP);
        for (int i = 0; i <= 30; i++)
            glEvalCoord2f((GLfloat)j / 8.0, (GLfloat)i / 30.0);
        glEnd();
    }
    glPopMatrix();


    glRotated(yrot, 0, 1, 0);
    glRotated(yrot_obj, 0, 0, 1);
    glRotated(zrot, 1, 0, 0);
    zrot = 0;
    yrot = 0;
    yrot_obj = 0;
    
    glPushMatrix();
    glColor3f(0.4, 0.5, 0.3);
    glScalef(1.0, 1.0, 1.0);
    glCallList(theTorus);
    glPopMatrix();

    glTranslated(0, 1.7, 0);
    
    glPushMatrix();
    glColor3f(0.9, 0.6, 0.1);
    glScalef(1.3, 1.3, 1.3);
    glCallList(theTorus);
    glPopMatrix();
    glTranslated(0, -4.1, 0);
    glColor3f(0.6, 0.6, 0.0);
    glCallList(theTorus);
    glTranslated(0, 2.4, 0);
    glFlush();  // glFlush гарантирует, что предыдущие команды OpenGL должны быть выполнены за конечное время так же говорят (только это секрет), что улучшает прорисовку

    if (gp == 1) {
        glEnable(GL_FOG);                       // Включает туман (GL_FOG)
        glFogi(GL_FOG_MODE, fogMode[fogfilter]);// Выбираем тип тумана
        glFogfv(GL_FOG_COLOR, fogColor);        // Устанавливаем цвет тумана
        glFogf(GL_FOG_DENSITY, 0.35f);          // Насколько густым будет туман
        glHint(GL_FOG_HINT, GL_DONT_CARE);      // Вспомогательная установка тумана
        glFogf(GL_FOG_START, 1.0f);             // Глубина, с которой начинается туман
        glFogf(GL_FOG_END, 5.0f);               // Глубина, где туман заканчивается
    }
    else {
        glDisable(GL_FOG);
    }

}

void reshape(int w, int h) {
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(30, (GLfloat)w / (GLfloat)h, 1.0, 100.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0, 10, 10, 0, 0, 0, 0, 1, 0);
}

int main(int argc, char** argv)
{
    glutInitWindowSize(768, 768);
    glutInitWindowPosition(400, 000);
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutCreateWindow(argv[0]);
    init();
    glutReshapeFunc(reshape);

    glutKeyboardFunc(Keyboard);
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}