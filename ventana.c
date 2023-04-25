//
// Created by alex on 18/04/23.
//
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/freeglut_std.h>
#include <stdio.h>
#include "GL/freeglut.h"
#include "math.h"
#include "ventana.h"

int contX1, contX2, contY1, contY2;

void configurar() {
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0, 600, 0, 600);
    glClearColor(0.75, 0.76, 0.75, 1);
}

void iniciar() {
    glClear(GL_COLOR_BUFFER_BIT);
    rectangulo(150, 150, 300, 300, 1, 0, 1);
    contX1 = 150;
    contX2 = 450;
    contY1 = 150;
    contY2 = 450;
    rectas();
    dibujar(136, 118, 289, 487);
    glFlush();
}

void dibujar(int x0, int y0, int x1, int y1) {
    dda(x0, y0, x1, y1, 5, 1, 1, 1);
    double p1[2];//x0 y0
    double p2[2];//x1 y1
    double a = y1 - y0;
    double m = a / (x1 - x0);
    double b;
    double yplanoRecorte, xplanoRecorte;
    int ok = 0;

    /////para los lados
    ///lado izquierdo
    b = y0 - m * x0;
    yplanoRecorte = m * contX1 + b;
    if (yplanoRecorte > contY1-1 & yplanoRecorte < contY2+1) {
        p1[0] = contX1;
        p1[1] = yplanoRecorte;


        b = y1 - m * x1;
        yplanoRecorte = m * contX2 + b;
        if (yplanoRecorte > contY1 & yplanoRecorte < contY2) {
            p2[0] = contX2;
            p2[1] = yplanoRecorte;
            ok = 1;
            //si no entra no esta en el plano derecho
        } else {

            b = y1 - m * x1;
            xplanoRecorte=(contY2-b)/m;
            if (xplanoRecorte>contX1-1 & xplanoRecorte<contX2+1) {
                p2[0] = xplanoRecorte;
                p2[1] = contY2;
                ok = 1;
            }else{
                xplanoRecorte=(contY1-b)/m;
                if(xplanoRecorte>contX1-1 & xplanoRecorte<contX2+1){
                    p2[0] = xplanoRecorte;
                    p2[1] = contY1;
                    ok = 1;
                }

            }
        }

    }
    //se le suma 150 por el rango del triangulo
    if(y0>=contY1 & y1<=contY2){
        if(x0>=contX1-1 & x1<=contX2+1){
            p1[0]=x0;
            p1[1]= y0;
            p2[0]=x1;
            p2[1]= y1;
            ok=1;
        }
    }
    //////////////////



    if (ok == 1) {
        dda(p1[0], p1[1], p2[0], p2[1], 5, 1, 1, 0);
        glColor3f(0, 0, 0);
        glPointSize(10);
        glBegin(GL_POINTS);
        glVertex2f(p1[0], p1[1]);
        glVertex2f(p2[0], p2[1]);
        glEnd();
    }


}


void rectas() {
    glColor3f(1, 0, 1);
    glRasterPos2f(50, 250);
    glutBitmapString(GLUT_BITMAP_9_BY_15, "0001");

    glRasterPos2f(50, 50);
    glutBitmapString(GLUT_BITMAP_9_BY_15, "0101");
    /*x= 64  y= 527 x= 300  y= 522 x= 523  y= 527
     * */
    glRasterPos2f(50, 530);
    glutBitmapString(GLUT_BITMAP_9_BY_15, "1001");
    glRasterPos2f(300, 522);
    glutBitmapString(GLUT_BITMAP_9_BY_15, "1000");
    glRasterPos2f(525, 530);
    glutBitmapString(GLUT_BITMAP_9_BY_15, "1010");
/*    x= 516  y= 318 x= 511  y= 72 x= 270  y= 71*/
    glRasterPos2f(520, 318);
    glutBitmapString(GLUT_BITMAP_9_BY_15, "0010");
    glRasterPos2f(510, 50);
    glutBitmapString(GLUT_BITMAP_9_BY_15, "0110");
    glRasterPos2f(270, 50);
    glutBitmapString(GLUT_BITMAP_9_BY_15, "0100");


    dda(150, 0, 150, 600, 2, 1, 0, 0);
    dda(450, 0, 450, 600, 2, 1, 0, 0);
    dda(0, 450, 600, 450, 2, 1, 0, 0);
    dda(0, 150, 600, 150, 2, 1, 0, 0);
}


void rectangulo(float x, float y, int xL, int Ly, float R, float G, float B) {
    glColor3f(R, G, B);
    glBegin(GL_QUADS);
    glVertex2i(x, y + Ly);
    glVertex2i(x + xL, y + Ly);
    glVertex2i(x + xL, y);
    glVertex2i(x, y);
    glEnd();
}


void mouseEvent(int boton, int estado, int x, int y) {
    if (boton == GLUT_LEFT_BUTTON && estado == GLUT_DOWN) {
        printf("x= %i  y= %i ", x, (600 - y));
        glFlush();
    }

}


/**
 *
 * @param x1 cordenada 1
 * @param y1 cordenada 1
 * @param x2 cordenada 2
 * @param y2 cordenada 2
 * @param puntosize tamano de punto
 * @param R color
 * @param G color
 * @param B color
 */
void dda(float x1, float y1, float x2, float y2, int puntosize, float R, float G, float B) {
    /**
     * algoritmo dda echo en c para lineas
     */
    float dx = x2 - x1;
    float dy = y2 - y1;
    float pasos, xIncrementos, yIncrementos, x = x1, y = y1;
    pasos = fabs(dx) > fabs(dy) ? fabs(dx) : fabs(dy);
    xIncrementos = dx / pasos;
    yIncrementos = dy / pasos;
    glPointSize(puntosize);
    glBegin(GL_POINTS);
    glColor3f(R, G, B);
    for (float i = 0; i < pasos; i++) {
        glVertex2f(x, y);
        x += xIncrementos;
        y += yIncrementos;
    }
    glEnd();
}