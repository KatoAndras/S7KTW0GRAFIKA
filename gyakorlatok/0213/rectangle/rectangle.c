#include <stdio.h>
#include <math.h>

//Cuboid létrehozása
struct Cuboid 
{
    double length;
    double width;
    double height;
};

// Méretek beállítása ellenőrzéssel
void set_size(struct Cuboid* cuboid, double length, double width, double height) 
{
    if (length > 0.0 && width > 0.0 && height > 0.0) 
    {
        cuboid->length = length;
        cuboid->width = width;
        cuboid->height = height;
    } else 
    {
        cuboid->length = cuboid->width = cuboid->height = NAN;
    }
}

//Térfogat
double calc_volume(const struct Cuboid* cuboid) 
{
    return cuboid->length * cuboid->width * cuboid->height;
}

//Felszín
double calc_surface(const struct Cuboid* cuboid) 
{
    return 2 * (cuboid->length * cuboid->width + cuboid->width * cuboid->height + cuboid->length * cuboid->height);
}

//Négyzetlap vizsgálat
int has_square_face(const struct Cuboid* cuboid) 
{
    return (cuboid->length == cuboid->width || 
            cuboid->width == cuboid->height || 
            cuboid->length == cuboid->height);
}

int main() {
    struct Cuboid cuboid = {10, 25, 5};
    
    printf("A terfogat: %.2f\n", calc_volume(&cuboid));
    printf("A felszín: %.2f\n", calc_surface(&cuboid));
    printf("Negyzet alaku lappal rendelkezik: %s\n", has_square_face(&cuboid) ? "igen" : "nem");
    
    return 0;
}
