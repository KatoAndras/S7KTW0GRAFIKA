#include "scene.h"
#include "texture.h"
#include <GL/gl.h>

#include <obj/load.h>
#include <obj/draw.h>

void init_scene(Scene* scene)
{
    // load_model(&(scene->cube), "assets/models/cube.obj");
    // scene->texture_id = load_texture("assets/textures/cube.png");
    load_model(&(scene->cube), "assets/models/cube.obj");
    scene->texture_id = load_texture("assets/textures/cube.png");

    glBindTexture(GL_TEXTURE_2D, scene->texture_id);

    scene->material.ambient.red = 0.0;
    scene->material.ambient.green = 0.0;
    scene->material.ambient.blue = 0.0;

    scene->material.diffuse.red = 1.0;
    scene->material.diffuse.green = 1.0;
    scene->material.diffuse.blue = 0.0;

    scene->material.specular.red = 0.0;
    scene->material.specular.green = 0.0;
    scene->material.specular.blue = 0.0;

    scene->material.shininess = 0.0;

    textures[0] = load_texture("black.jpg");
    textures[1] = load_texture("white.jpg");
    textures[2] = load_texture("black.jpg");
    textures[3] = load_texture("white.jpg");
    textures[4] = load_texture("black.jpg");
    textures[5] = load_texture("white.jpg");

    checker_texture = create_checker_texture();
}

void set_lighting()
{
    float ambient_light[] = { 0.0f, 0.0f, 0.0f, 1.0f };
    float diffuse_light[] = { 1.0f, 1.0f, 1.0, 1.0f };
    float specular_light[] = { 0.0f, 0.0f, 0.0f, 1.0f };
    float position[] = { 0.0f, 0.0f, 10.0f, 1.0f };

    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient_light);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse_light);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specular_light);
    glLightfv(GL_LIGHT0, GL_POSITION, position);
}

void set_material(const Material* material)
{
    float ambient_material_color[] = {
        material->ambient.red,
        material->ambient.green,
        material->ambient.blue
    };

    float diffuse_material_color[] = {
        material->diffuse.red,
        material->diffuse.green,
        material->diffuse.blue
    };

    float specular_material_color[] = {
        material->specular.red,
        material->specular.green,
        material->specular.blue
    };

    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient_material_color);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse_material_color);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular_material_color);

    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, &(material->shininess));
}

void update_scene(Scene* scene)
{
}

void render_scene(const Scene* scene)
{
    set_material(&(scene->material));
    set_lighting();
    draw_origin();
    draw_model(&(scene->cube));
}

void draw_origin()
{
    glBegin(GL_LINES);

    glColor3f(1, 0, 0);
    glVertex3f(0, 0, 0);
    glVertex3f(1, 0, 0);

    glColor3f(0, 1, 0);
    glVertex3f(0, 0, 0);
    glVertex3f(0, 1, 0);

    glColor3f(0, 0, 1);
    glVertex3f(0, 0, 0);
    glVertex3f(0, 0, 1);

    glEnd();
}

void draw_face(float size, GLuint tex_id) 
{
    glBindTexture(GL_TEXTURE_2D, tex_id);
    glBegin(GL_QUADS);
    
    glTexCoord2f(0.0, 0.0); glVertex3f(-size, -size, 0);
    glTexCoord2f(1.0, 0.0); glVertex3f(size, -size, 0);
    glTexCoord2f(1.0, 1.0); glVertex3f(size, size, 0);
    glTexCoord2f(0.0, 1.0); glVertex3f(-size, size, 0);

    glEnd();
}

void draw_cube(float size) 
{
    glPushMatrix();
    glTranslatef(0, 0, size);
    draw_face(size, textures[0]);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0, 0, -size);
    glRotatef(180, 0, 1, 0);
    draw_face(size, textures[1]);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-size, 0, 0);
    glRotatef(90, 0, 1, 0);
    draw_face(size, textures[2]);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(size, 0, 0);
    glRotatef(-90, 0, 1, 0);
    draw_face(size, textures[3]);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0, size, 0);
    glRotatef(-90, 1, 0, 0);
    draw_face(size, textures[4]);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0, -size, 0);
    glRotatef(90, 1, 0, 0);
    draw_face(size, textures[5]);
    glPopMatrix();
}

