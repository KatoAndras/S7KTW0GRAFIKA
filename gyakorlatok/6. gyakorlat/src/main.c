#include "app.h"

#include <stdio.h>

/**
 * Main function
 */
int main(int argc, char* argv[])
{
    float light_intensity = 1.0f;
    
    App app;

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
