#include "model.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int loadOBJ(const char *path, Model *outModel) 
{
    FILE *f = fopen(path,"r");
    if(!f) return 0;
    float *positions = NULL, *texcoords = NULL;
    unsigned int *indices = NULL;
    int posCount=0, uvCount=0, idxCount=0;

    //fajlbeolvasas
    char line[256];
    while(fgets(line,256,f))
    {
        if(strncmp(line,"v ",2)==0)
        {
            positions = realloc(positions, (posCount+3)*sizeof(float));
            sscanf(line+2,"%f %f %f",
                &positions[posCount+0],
                &positions[posCount+1],
                &positions[posCount+2]);
            posCount += 3;
        } 
        else if(strncmp(line,"vt ",3)==0)
        {
            texcoords = realloc(texcoords, (uvCount+2)*sizeof(float));
            sscanf(line+3,"%f %f",
                &texcoords[uvCount+0],
                &texcoords[uvCount+1]);
            uvCount += 2;
        } 
        else if(strncmp(line,"f ",2)==0)
        {
            int vi[3], uvi[3];
            
            sscanf(line+2,"%d/%d %d/%d %d/%d",
                &vi[0], &uvi[0],
                &vi[1], &uvi[1],
                &vi[2], &uvi[2]);
  
            indices = realloc(indices, (idxCount+3)*sizeof(unsigned int));
            indices[idxCount+0] = (vi[0]-1)*5 + (uvi[0]-1);
            indices[idxCount+1] = (vi[1]-1)*5 + (uvi[1]-1);
            indices[idxCount+2] = (vi[2]-1)*5 + (uvi[2]-1);
            idxCount += 3;
        }
    }
    fclose(f);

    //poziciok es uv-k
    int vertCount = posCount/3;
    float *vertexData = malloc(vertCount*5*sizeof(float));

    for(int i=0;i<vertCount;i++)
    {
      vertexData[i*5 + 0] = positions[i*3 + 0];
      vertexData[i*5 + 1] = positions[i*3 + 1];
      vertexData[i*5 + 2] = positions[i*3 + 2];
      vertexData[i*5 + 3] = texcoords[i*2 + 0];
      vertexData[i*5 + 4] = texcoords[i*2 + 1];
    }
    free(positions);
    free(texcoords);


    glGenVertexArrays(1, &outModel->vao);
    glBindVertexArray(outModel->vao);

    glGenBuffers(1, &outModel->vbo);
    glBindBuffer(GL_ARRAY_BUFFER, outModel->vbo);
    glBufferData(GL_ARRAY_BUFFER, vertCount*5*sizeof(float), vertexData, GL_STATIC_DRAW);

    glGenBuffers(1, &outModel->ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, outModel->ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, idxCount*sizeof(unsigned int), indices, GL_STATIC_DRAW);

    //pozicio
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5*sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5*sizeof(float), (void*)(3*sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);
    free(vertexData);
    free(indices);

    outModel->indexCount = idxCount;
    return 1;
}

void drawModel(const Model *m, GLuint tex) {
    // 1) bindold a textúrát
    glBindTexture(GL_TEXTURE_2D, tex);

    // 2) engedélyezd a client state‐eket
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);

    // 3) bindold a VBO/EBO és add meg a pointereket
    glBindBuffer(GL_ARRAY_BUFFER, m->vbo);
    glVertexPointer(3, GL_FLOAT, 5 * sizeof(float), (void*)0);
    glTexCoordPointer(2, GL_FLOAT, 5 * sizeof(float), (void*)(3 * sizeof(float)));

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m->ebo);

    // 4) rajzold
    glDrawElements(GL_TRIANGLES, m->indexCount, GL_UNSIGNED_INT, 0);

    // 5) cleanup
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);
    glDisableClientState(GL_VERTEX_ARRAY);
}
