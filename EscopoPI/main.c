#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>
#include <allegro5/keyboard.h>
//  573 / 3 = 191 → largura
// 644 / 4 = 161  → altura


int main() {

    al_init();
    al_init_font_addon();
    al_init_ttf_addon();
    al_init_image_addon();
    al_install_keyboard();
    //iniciando as funções declaradas antes da main

    ALLEGRO_DISPLAY* display = al_create_display(1200, 673); //criando a janela e utilizando o al_create para as dimensoes
    al_set_window_position(display, 300, 150); //onde a janela vai ser aberta
    al_set_window_title(display, "Here be Dragons!"); //definindo o título do programa

    ALLEGRO_FONT* font = al_create_builtin_font(); //utilizando fonte padrão do allegro
    ALLEGRO_TIMER* timer = al_create_timer(1.0 / 1.0); //como se fosse o fps -- define a velocidade da troca de frames (imagens) do boneco

    ALLEGRO_BITMAP* sprite = al_load_bitmap("./MEN.png"); //ponteiro para a imagem da sprite
    ALLEGRO_BITMAP* bg = al_load_bitmap("./bg.png"); //ponteiro para a imagem de fundo
    //colocando a imagem

    ALLEGRO_EVENT_QUEUE* event_queue = al_create_event_queue();
    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_timer_event_source(timer));
    al_register_event_source(event_queue, al_get_keyboard_event_source());
    al_start_timer(timer);

    float frame = 0.f;
    int pos_x = 115, pos_y = 50; //início da posição do personagem principal
    int current_frame_y = 64; 

    while (true) {
        ALLEGRO_EVENT event;
        al_wait_for_event(event_queue, &event);
        if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
            break;
        }//checando se ele clicou no clicou no X da página

        else if (event.keyboard.keycode == ALLEGRO_KEY_RIGHT) { // tipo de evento (mover para direita)
            current_frame_y = 64; // utilizando a animação em que ele vai para a direita
            pos_x += 2; //aumentando a quantidade de pixels para a direita
        } 
        else if (event.keyboard.keycode == ALLEGRO_KEY_LEFT) { // tipo de evento (mover para esquerda)
            current_frame_y = 64 * 3; // utilizando a animação em que ele volta para a esquerda
            pos_x -= 2; //diminuindo a quantidade de pixels para a direita
        }
        else if (event.keyboard.keycode == ALLEGRO_KEY_DOWN) { // tipo de evento (mover para baixo)
            current_frame_y = 64 * 2; // utilizando a animação em que ele volta para ir para baixo
            pos_y += 2; //aumentando a quantidade de pixels para a ir para baixo
        }
        else if (event.keyboard.keycode == ALLEGRO_KEY_UP) { // tipo de evento (mover para cima)
            current_frame_y = 0; // utilizando a animação em que ele volta para ir para cima
            pos_y -= 2; //diminuindo a quantidade de pixels para a ir para baixo
        }

        frame += 0.3f;
        if (frame > 3) { 
            frame -= 3;
        } // animação para ir alterando entre as imagens da linha do sprite

        al_clear_to_color(al_map_rgb(255, 255, 255));
        al_draw_bitmap(bg, 0, 0, 0); //desenhando o bg
        al_draw_text(font, al_map_rgb(0, 0, 0), 7, 7, 0, "SCORE: dragon");//criando um texto e o local
        al_draw_text(font, al_map_rgb(255, 255, 255), 5, 5, 0, "SCORE: dragon");
        al_draw_bitmap_region(sprite, 48 * (int)frame, current_frame_y, 48, 64, pos_x, pos_y, 0);//desenhando cada região do sprite
        al_flip_display();
    }

    al_destroy_bitmap(bg);
    al_destroy_bitmap(sprite);
    al_destroy_font(font);
    al_destroy_display(display);
    al_destroy_event_queue(event_queue);
    //destruindo o que foi criado

    return 0;
}