#include "app.h"
#include "scene.h"
#include "texture.h"
#include "draw.h"

#include <stdio.h>
#include <GL/glut.h>


void init_app() {
    set_lighting();
    init_textures();
    init_scene();
}

void render_app() {
    render_scene();
}

/**
 * Main function
 */
int main(int argc, char* argv[])
{
    App app;

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Sakktábla");

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    init_app();

    glutDisplayFunc(render_app);
    glutMainLoop();


    init_app(&app, 800, 600);
    while (app.is_running) 
    {
        handle_app_events(&app);
        update_app(&app);
        render_app(&app);
    }
    
    destroy_app(&app);

    return 0;
}