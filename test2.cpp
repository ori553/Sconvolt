#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h> //include the header to initialize the image addon
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_native_dialog.h>



#include <iostream>

using namespace std;

int main()
{
    ALLEGRO_DISPLAY *Screen;
    ALLEGRO_EVENT_QUEUE *EventQueue;
    ALLEGRO_EVENT Event;
    ALLEGRO_BITMAP *Image = NULL; ///object the holds the graphic. initialize it empty
    bool Exit = false;




/*
    ALLEGRO_FONT *font = al_load_ttf_font("Fonts/Capture_it.ttf",72,0 );
       if (!font){
      fprintf(stderr, "Could not load 'pirulen.ttf'.\n");
      return -1;
   }
*/

   //ALLEGRO_FONT *font = al_load_ttf_font("Fonts/Capture_it.ttf",25,3 ); //Load Main font

    al_init();
    al_init_image_addon(); /// this must be called to load images. has to be called after al_init

    Screen = al_create_display(800, 600);

    EventQueue = al_create_event_queue();
    al_register_event_source(EventQueue, al_get_display_event_source(Screen));


al_init_font_addon(); // initialize the font addon
   al_init_ttf_addon();// initialize the ttf (True Type Font) addon

       ALLEGRO_FONT *font = al_load_ttf_font("Fonts/Capture_it.ttf",72,0 );
       if (!font){
      fprintf(stderr, "Could not load 'pirulen.ttf'.\n");
      return -1;
   }

       if(!al_install_mouse())
    {
        al_show_native_message_box(NULL, "Error!", "Failed to install mouse.", 0, 0, ALLEGRO_MESSAGEBOX_ERROR);
        return -1;
    }

    al_register_event_source(EventQueue, al_get_display_event_source(Screen));
    al_register_event_source(EventQueue, al_get_mouse_event_source()); ///Tell allegro to get events from the mouse

   // Image = al_load_bitmap("image.png"); ///load the bitmap from a file

    while(Exit == false)
    {

     al_draw_text(font, al_map_rgb(255,255,255), 640/2, (480/4),ALLEGRO_ALIGN_CENTRE, "Your Text Here!");

        ///draw an image at the position 0, 0
        //al_draw_bitmap(Image, 0, 0, 0);
        al_flip_display();

        al_wait_for_event(EventQueue, &Event);

        if(Event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) ///check if a mouse button was clicked
        {
                cout<<"________________________________"<<endl;
                cout<<"Mouse_x = "<<Event.mouse.x<<endl;
                cout<<"Mouse_y = "<<Event.mouse.y<<endl;
        }


        if(Event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
        {
            Exit = true;
        }
    }

    return 0;
}
