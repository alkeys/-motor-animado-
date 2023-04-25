#include "GL/glut.h"
#include "ventana.h"
int main(int argc,char** argv) {
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

    glutInitWindowPosition(500,200);
    glutInitWindowSize(600,600);
    glutCreateWindow("Recortes");
     configurar();
    glutDisplayFunc(iniciar);
    glutMouseFunc(mouseEvent);
/*    glutKeyboardFunc(keyEvent);
   */
    glutMainLoop();return 0;
}