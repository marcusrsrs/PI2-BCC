
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>
#include <allegro5/keyboard.h>

//  573 / 3 = 191 → largura
// 644 / 4 = 161  → altura

// Definindo os estados do jogo
typedef enum {
    TELA_INICIAL,
    TELA_JOGO
} EstadoJogo;

int main() {
    al_init();
    al_init_font_addon();
    al_init_ttf_addon();
    al_init_image_addon();
    al_install_keyboard();
    //iniciando as funções declaradas antes da main

    ALLEGRO_DISPLAY* display = al_create_display(1200, 673); //criando a janela e utilizando o al_create para as dimensoes
    al_set_window_position(display, 300, 150); //onde a janela vai ser aberta
    al_set_window_title(display, "Where's princess?!"); //definindo o título do programa

    ALLEGRO_FONT* font = al_create_builtin_font(); //utilizando fonte padrão do allegro
    ALLEGRO_TIMER* timer = al_create_timer(1.0 / 40.0); // 40 FPS para maior fluidez -- define a velocidade da troca de frames (imagens) do boneco

    ALLEGRO_BITMAP* sprite = al_load_bitmap("./MEN.png"); //ponteiro para a imagem da sprite
    ALLEGRO_BITMAP* bg = al_load_bitmap("./bg.png");  //ponteiro para a imagem de fundo
    ALLEGRO_BITMAP* inicial = al_load_bitmap("./inicial.png"); //ponteiro para a imagem de fundo da tela inicial


    ALLEGRO_EVENT_QUEUE* event_queue = al_create_event_queue();
    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_timer_event_source(timer));
    al_register_event_source(event_queue, al_get_keyboard_event_source());
    al_start_timer(timer);

    float frame = 0.f;
    int pos_x = 115, pos_y = 50; //início da posição do personagem principal
    int current_frame_y = 64;

    EstadoJogo estadoAtual = TELA_INICIAL;  // Começamos na tela inicial
    ALLEGRO_KEYBOARD_STATE keyState;        // Armazenar o estado do teclado

    while (true) {
        ALLEGRO_EVENT event;
        al_wait_for_event(event_queue, &event);

        if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
            break;
        } //checando se ele clicou no clicou no X da página

        if (estadoAtual == TELA_INICIAL) {
            // Lógica da tela inicial
            if (event.type == ALLEGRO_EVENT_KEY_DOWN) {
                if (event.keyboard.keycode == ALLEGRO_KEY_ENTER) {
                    estadoAtual = TELA_JOGO;  // Vai para o estado de jogo
                }
            }

            // Desenhar a tela inicial
            al_draw_bitmap(inicial, 0, 0, 0); //desenhando o fundo da tela inicial
            al_draw_text(font, al_map_rgb(255, 255, 255), 600, 300, ALLEGRO_ALIGN_CENTER, "Pressione ENTER para iniciar o jogo");

            al_flip_display();

        }
        else if (estadoAtual == TELA_JOGO) {
            // Lógica da tela de jogo
            if (event.type == ALLEGRO_EVENT_TIMER) {
                // Atualizando o estado do teclado
                al_get_keyboard_state(&keyState);

                // Movimentação do personagem
                if (al_key_down(&keyState, ALLEGRO_KEY_RIGHT)) {
                    current_frame_y = 64;
                    pos_x += 2;
                }
                if (al_key_down(&keyState, ALLEGRO_KEY_LEFT)) {
                    current_frame_y = 64 * 3;
                    pos_x -= 2;
                }
                if (al_key_down(&keyState, ALLEGRO_KEY_DOWN)) {
                    current_frame_y = 64 * 2;
                    pos_y += 2;
                }
                if (al_key_down(&keyState, ALLEGRO_KEY_UP)) {
                    current_frame_y = 0;
                    pos_y -= 2;
                }

                frame += 0.3f;
                if (frame > 3) {
                    frame -= 3;
                }  // animação para ir alterando entre as imagens da linha do sprite

                // Desenhar o jogo
                al_clear_to_color(al_map_rgb(255, 255, 255));
                al_draw_bitmap(bg, 0, 0, 0); //desenhando o bg
                //al_draw_text(font, al_map_rgb(0, 0, 0), 7, 7, 0, "SCORE: dragon");
                al_draw_text(font, al_map_rgb(255, 255, 255), 5, 5, 0, "SCORE: dragon"); //criando um texto e o local
                al_draw_bitmap_region(sprite, 48 * (int)frame, current_frame_y, 48, 64, pos_x, pos_y, 0); //desenhando cada região do sprite

                al_flip_display();
            }
        }
    }

    // Destruindo os recursos
    al_destroy_bitmap(bg);
    al_destroy_bitmap(sprite);
    al_destroy_font(font);
    al_destroy_display(display);
    al_destroy_bitmap(inicial);
    al_destroy_event_queue(event_queue);

    return 0;
}
