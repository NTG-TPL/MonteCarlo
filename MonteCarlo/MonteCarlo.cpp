
#include <vector>
#include "GLFW/glfw3.h"
#include <iostream>
#include "Functions.h"

int main()
{
    int n = 1e7;
    double S = 2.0 * sqrt(3.0);
    std::vector<double> index(n,0);
    std::vector<double> x;
    std::vector<double> y;
   
    InitPoints(x, y, n);
    SelectPoints(x, y, index, n);
    double sum_h = SumH(x, y, index, n);
    double I = S/n*sum_h;
    printf("%.15f\n", I);
#pragma region OpenGLDraws
    GLFWwindow* window;
    if (!glfwInit())
        return -1;
    window = glfwCreateWindow(600, 600, "Monte Carlo", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-0.1,0.1 ,-0.1,0.1,0.2,1000);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glfwMakeContextCurrent(window);
    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT);
        glPushMatrix();
        glRotatef(-70, 1, 0, 0);
        glRotatef(20, 0, 0, 1);
        glTranslatef(0,0,-0.28);
        glPointSize(1.0);
        glBegin(GL_POINTS);
        for (int i = 0; i < n; i++){
            if (index[i] == 1) {
                glColor3f(1, 0, 0);
                glVertex2d(x[i] * 0.7 - 2.1, y[i] * 0.7 - 0.5);
            }
            else {
                glColor3f(0, 0, 1);
                glVertex2d(x[i] * 0.7 - 2.1, y[i] * 0.7 - 0.5);
            } 

        }
        for (int i = 0; i < n; i++)
        {
            glColor3f(0, 1, 0);
            glVertex2d(x[i] * 0.7 - 2.1, sqrt(x[i] - 1) * 0.7 - 0.5);
        }
        glEnd();
        glTranslatef(0, 0, 0.7);
        glBegin(GL_POINTS);
        for (int i = 0; i < n; i++)
        {
            if (index[i] == 1) {
                glColor3f(0.5, 0.5, 0.5);
                glVertex3d(x[i] * 0.7 - 2.1, y[i] * 0.7 - 0.5, (sin(x[i] + y[i]) + cos(x[i] - y[i])) / (x[i] + y[i]));
            }
        }
        glEnd();
        glPopMatrix();
        glfwSwapBuffers(window);
        glfwPollEvents();
        glClearColor(0.2, 0.2, 0.2, 1.0);
    }
    glfwTerminate();
#pragma endregion
}