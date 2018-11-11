#include <QCoreApplication>
#include <QTimer>
#include <QThread>
#include <QObject>
#include <iostream>

#include <allegro5/allegro5.h>
#include <allegro5/allegro_color.h>
#include <allegro5/keycodes.h>
#include <allegro5/keyboard.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <allegro5/bitmap_draw.h>
#include <allegro5/allegro_font.h>


int main(int argc, char *argv[])
{
    ALLEGRO_DISPLAY *ventana;
    ALLEGRO_FONT *fuenteJuego;
    ALLEGRO_KEYBOARD_STATE estadoTeclado;



    al_init();
    al_install_keyboard();
    al_init_primitives_addon();
    al_init_image_addon();
    al_init_font_addon();

    //fuenteJuego = al_load_font("/fuente/arial.ttf",12,0);

    int estadoAuto=1;
    int posAutoX=100;
    int posAutoY=100;
    int autoVoltea=0;
    float rotar=0;

    int anchoAutoX=40;
    int anchoAutoY=70;





    ALLEGRO_BITMAP *auto_camina[4];
    auto_camina[0] = al_load_bitmap("sprites/run/car_1.png");
    auto_camina[1] = al_load_bitmap("sprites/run/car_2.png");
    auto_camina[2] = al_load_bitmap("sprites/run/car_3.png");
    auto_camina[3] = al_load_bitmap("sprites/run/car_4.png");
    int animAutoCamina=0;

//    ALLEGRO_BITMAP *auto_left;
//    auto_left = al_load_bitmap("sprites/left/car_left.png");

//    ALLEGRO_BITMAP *auto_right;
//    auto_right = al_load_bitmap("sprites/right/car_right.png");

    ALLEGRO_BITMAP *pista;
    pista = al_load_bitmap("sprites/pista/pista1.png");



    ventana = al_create_display(1024,800);



    QCoreApplication a(argc, argv);

    QTimer *entradas;
    entradas = new QTimer(&a);
    entradas->start(8);

    QTimer *animAuto;
    animAuto = new QTimer(&a);
    animAuto->start(150);


    QObject::connect(entradas, &QTimer::timeout, [&]()
    {


            al_draw_bitmap(pista,50,200,1);

            //al_draw_text(fuenteJuego,al_map_rgb(255,255,255),20,20,1,"hola");




           estadoAuto=1;
           al_get_keyboard_state(&estadoTeclado);
           if (al_key_down(&estadoTeclado, ALLEGRO_KEY_ESCAPE))
           {
               a.exit(0);
           }
           std::cout << rotar << std::endl;


           if (al_key_down(&estadoTeclado, ALLEGRO_KEY_LEFT) && posAutoX > 0)
           {
               if(rotar < 3.14)
               {
                   rotar+=0.01;
               }
               else
               {
               estadoAuto=1;
               posAutoX--;
               autoVoltea=1;
               }

           }
           if (al_key_down(&estadoTeclado, ALLEGRO_KEY_RIGHT) && posAutoX < (1024-anchoAutoX))
           {
               if(rotar<ALLEGRO_PI/2)
               {
              estadoAuto=1;
              posAutoX++;
              autoVoltea=0;
               }
               else
               {
                   rotar+=0.01;
               }
           }
           if (al_key_down(&estadoTeclado, ALLEGRO_KEY_UP)>0 && posAutoY > 100)
           {
              estadoAuto=1;
              posAutoY--;

           }
           if (al_key_down(&estadoTeclado, ALLEGRO_KEY_DOWN) && posAutoY < 800-anchoAutoY)
           {

            animAutoCamina=0;

              //al_draw_rotated_bitmap(auto_camina[animAutoCamina],60,50,posAutoX,posAutoY,rotar,0);
              rotar+=ALLEGRO_PI/200;
              animAutoCamina++;
              if(animAutoCamina>3)
              {
                  animAutoCamina=0;
              }
              if(rotar>ALLEGRO_PI/2)
              {

                  rotar=ALLEGRO_PI/2;
                  posAutoY++;
              }
              estadoAuto=1;
              //posAutoY++;

           }
           if(rotar>6.28)
           {
               rotar=0;
           }
           if (al_key_down(&estadoTeclado, ALLEGRO_KEY_SPACE))
           {
              //estadoAuto=2;
              rotar+=0.01;
              if(rotar>6.28)
              {
                  rotar=0;
              }
            }

    });

           QObject::connect(animAuto, &QTimer::timeout, [&]()
           {

               if(animAutoCamina>3)
               {
                   animAutoCamina=0;
               }



            switch (estadoAuto)
            {
            //case 0:
            //    al_draw_bitmap(auto_parado[animAutoParado],posAutoX,posAutoY,autoVoltea);
            //    animAutoParado++;
            //break;
            case 1:
                //al_draw_bitmap(auto_camina[animAutoCamina],posAutoX,posAutoY,autoVoltea);
                al_draw_rotated_bitmap(auto_camina[0],50,50,posAutoX,posAutoY,rotar,0);
                animAutoCamina++;
            break;

            }





            al_flip_display();
            al_clear_to_color(al_map_rgb(0,255,55));
           });





    return a.exec();
}
