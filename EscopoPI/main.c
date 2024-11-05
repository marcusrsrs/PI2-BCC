
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>
#include <allegro5/keyboard.h>

// Definindo os estados do jogo
typedef enum {
    TELA_INICIAL,  // Estado da tela inicial
    TELA_JOGO,     // Estado do jogo
    TELA_POPUP1,   // Estado do primeiro pop-up
    TELA_POPUP2    // Estado do segundo pop-up
} EstadoJogo;

void reiniciarTelaJogo(ALLEGRO_BITMAP* bg, ALLEGRO_BITMAP* sprite, ALLEGRO_FONT* font, ALLEGRO_DISPLAY* display, int* pos_x, int* pos_y, float* frame) {
    // Reinicia as variáveis do jogo
    *pos_x = 650;
    *pos_y = 50;
    *frame = 0;

    // Limpa a tela e redesenha o fundo
    al_clear_to_color(al_map_rgb(255, 255, 255));
    al_draw_bitmap(bg, 0, 0, 0); // Desenha o fundo
    al_draw_text(font, al_map_rgb(255, 255, 255), 5, 5, 0, "SCORE: dragão"); // Exibe a pontuação
    al_flip_display(); // Atualiza a tela
}

int main() {
    // Inicialização dos componentes do Allegro
    al_init();
    al_init_font_addon();
    al_init_ttf_addon();
    al_init_image_addon();
    al_install_keyboard();

    // Criando a tela de exibição
    ALLEGRO_DISPLAY* display = al_create_display(1200, 673);
    al_set_window_position(display, 300, 150);
    al_set_window_title(display, "Where is the princess?!");

    // Criando a fonte e o timer
    ALLEGRO_FONT* font = al_create_builtin_font();
    ALLEGRO_TIMER* timer = al_create_timer(1.0 / 40.0); // 40 FPS

    // Carregando as imagens necessárias
    ALLEGRO_BITMAP* sprite = al_load_bitmap("./MEN.png"); // Imagem do personagem
    ALLEGRO_BITMAP* bg = al_load_bitmap("./bg.png");       // Imagem de fundo
    ALLEGRO_BITMAP* inicial = al_load_bitmap("./inicial.png"); // Imagem da tela inicial
    ALLEGRO_BITMAP* popup_img1 = al_load_bitmap("./pop-up1.png"); // Imagem do pop-up 1
    ALLEGRO_BITMAP* popup_img2 = al_load_bitmap("./pop-up2.png"); // Imagem do pop-up 2

    // Criando a fila de eventos
    ALLEGRO_EVENT_QUEUE* event_queue = al_create_event_queue();
    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_timer_event_source(timer));
    al_register_event_source(event_queue, al_get_keyboard_event_source());
    al_start_timer(timer); // Iniciando o timer

    // Variáveis para controle do jogo
    float frame = 0.f; // Contador de quadros
    int pos_x = 115, pos_y = 50; // Posição inicial do personagem
    int current_frame_y = 64; // Posição vertical do sprite

    // Definindo os limites da tela de jogo (background)
    int lim_esquerdo = 0;
    int lim_direito = 1200 - 48; // largura da tela menos largura do sprite
    int lim_superior = 0;
    int lim_inferior = 673 - 64; // altura da tela menos altura do sprite

    EstadoJogo estadoAtual = TELA_INICIAL; // Estado inicial do jogo
    ALLEGRO_KEYBOARD_STATE keyState; // Estado do teclado

    while (true) {
        ALLEGRO_EVENT event;
        al_wait_for_event(event_queue, &event); // Aguardando eventos

        // Verifica se a janela foi fechada
        if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
            break; // Sai do loop principal
        }

        // Lógica para a tela inicial
        if (estadoAtual == TELA_INICIAL) {
            if (event.type == ALLEGRO_EVENT_KEY_DOWN) {
                if (event.keyboard.keycode == ALLEGRO_KEY_ENTER) {
                    estadoAtual = TELA_JOGO; // Muda para o estado do jogo
                }
            }
            al_draw_bitmap(inicial, 0, 0, 0); // Desenha a imagem da tela inicial
            al_flip_display(); // Atualiza a tela
        }
        // Lógica para o jogo
        else if (estadoAtual == TELA_JOGO) {
            if (event.type == ALLEGRO_EVENT_TIMER) {
                al_get_keyboard_state(&keyState); // Obtém o estado do teclado

                // Movimentação do personagem com limites
                if (al_key_down(&keyState, ALLEGRO_KEY_RIGHT) && pos_x < lim_direito) {
                    current_frame_y = 64;
                    pos_x += 2;
                }
                if (al_key_down(&keyState, ALLEGRO_KEY_LEFT) && pos_x > lim_esquerdo) {
                    current_frame_y = 64 * 3;
                    pos_x -= 2;
                }
                if (al_key_down(&keyState, ALLEGRO_KEY_DOWN) && pos_y < lim_inferior) {
                    current_frame_y = 64 * 2;
                    pos_y += 2;
                }
                if (al_key_down(&keyState, ALLEGRO_KEY_UP) && pos_y > lim_superior) {
                    current_frame_y = 0;
                    pos_y -= 2;
                }

                // Controle do frame do sprite
                frame += 0.3f; // Incrementa o contador de quadros
                if (frame > 3) {
                    frame -= 3; // Reinicia o contador se exceder
                }

                // Verifica a posição do personagem para mudar o estado para pop-up
                if (pos_x == 575 && pos_y == 50) {
                    estadoAtual = TELA_POPUP1; // Muda para o primeiro pop-up
                }
                if (pos_x >= 1120 && pos_y == 570) {
                    estadoAtual = TELA_POPUP2; // Muda para o segundo pop-up
                }

                // Limpa a tela e desenha o fundo e o personagem
                al_clear_to_color(al_map_rgb(255, 255, 255));
                al_draw_bitmap(bg, 0, 0, 0); // Desenha o fundo
                al_draw_text(font, al_map_rgb(255, 255, 255), 5, 5, 0, "SCORE: dragão"); // Exibe a pontuação
                al_draw_bitmap_region(sprite, 48 * (int)frame, current_frame_y, 48, 64, pos_x, pos_y, 0); // Desenha o sprite do personagem
                al_flip_display(); // Atualiza a tela
            }
        }
        // Lógica para o primeiro pop-up
        else if (estadoAtual == TELA_POPUP1) {
            // Desenhar a imagem do pop-up 1
            al_draw_bitmap(bg, 0, 0, 0); // Desenha o fundo
            al_draw_bitmap(popup_img1, 400, 200, 0); // Posição centralizada para o pop-up 1
            al_flip_display(); // Atualiza a tela

            // Verifica se o usuário quer sair do pop-up 1
            if (event.type == ALLEGRO_EVENT_KEY_DOWN) {
                if (event.keyboard.keycode == ALLEGRO_KEY_ESCAPE) {
                    // Destrói recursos e reinicia o jogo
                    reiniciarTelaJogo(bg, sprite, font, display, &pos_x, &pos_y, &frame);
                    estadoAtual = TELA_JOGO; // Retorna ao estado do jogo
                }
            }
        }
        // Lógica para o segundo pop-up
        else if (estadoAtual == TELA_POPUP2) {
            // Desenhar a imagem do pop-up 2
            al_draw_bitmap(bg, 0, 0, 0); // Desenha o fundo
            al_draw_bitmap(popup_img2, 0, 0, 0); // Posição centralizada para o pop-up 2
            al_flip_display(); // Atualiza a tela

            // Verifica se o usuário quer sair do pop-up 2
            if (event.type == ALLEGRO_EVENT_KEY_DOWN) {
                if (event.keyboard.keycode == ALLEGRO_KEY_ESCAPE) {
                    // Destrói recursos e reinicia o jogo
                    reiniciarTelaJogo(bg, sprite, font, display, &pos_x, &pos_y, &frame);
                    estadoAtual = TELA_JOGO; // Retorna ao estado do jogo
                }
            }
        }
    }

    // Liberação dos recursos utilizados
    al_destroy_bitmap(bg);
    al_destroy_bitmap(sprite);
    al_destroy_font(font);
    al_destroy_display(display);
    al_destroy_bitmap(inicial);
    al_destroy_bitmap(popup_img1);
    al_destroy_bitmap(popup_img2);
    al_destroy_event_queue(event_queue);

    return 0;
}







