



//                          O CÓDIGO ABAIXO É O CÓDIGO PRINCIPAL COM TODAS AS INTERAÇÕES FUNCIONANDO, EXCETO NA TORRE EIFFEL E NA ESTÁTUA DA LIBERDADE
//                                               NÃO CONSEGUI FAZER O CÓDIGO PRINCIPAL CHAMAR O CÓDIGO DO MINIGAME



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
    TELA_SURPRESA1,   // Estado do primeiro pop-up
    TELA_POPUP3,    // Estado do terceiro pop-up
    TELA_POPUP4,    // Estado do quarto pop-up
    TELA_FINAL    // Estado da tela final
} EstadoJogo;

void reiniciarTelaJogo(ALLEGRO_BITMAP* bg, ALLEGRO_BITMAP* sprite, ALLEGRO_FONT* font, ALLEGRO_DISPLAY* display, int* pos_x, int* pos_y, float* frame) {
    // Reinicia as variáveis do jogo
    *pos_x = 650;
    *pos_y = 50; 
    *frame = 0;


    // Limpa a tela e redesenha o fundo
    al_clear_to_color(al_map_rgb(255, 255, 255));
    al_draw_bitmap(bg, 0, 0, 0); // Desenha o fundo
    al_flip_display(); // Atualiza a tela
}

void reiniciarTelaJogo1(ALLEGRO_BITMAP* bg, ALLEGRO_BITMAP* sprite, ALLEGRO_FONT* font, ALLEGRO_DISPLAY* display, int* pos_x, int* pos_y, float* frame) {
    // Reinicia as variáveis do jogo
    *pos_x = 880;
    *pos_y = 50;
    *frame = 0;


    // Limpa a tela e redesenha o fundo
    al_clear_to_color(al_map_rgb(255, 255, 255));
    al_draw_bitmap(bg, 0, 0, 0); // Desenha o fundo
    al_flip_display(); // Atualiza a tela
}

void reiniciarTelaJogo2(ALLEGRO_BITMAP* bg, ALLEGRO_BITMAP* sprite, ALLEGRO_FONT* font, ALLEGRO_DISPLAY* display, int* pos_x, int* pos_y, float* frame) {
    // Reinicia as variáveis do jogo
    *pos_x = 290;
    *pos_y = 315;
    *frame = 0;


    // Limpa a tela e redesenha o fundo
    al_clear_to_color(al_map_rgb(255, 255, 255));
    al_draw_bitmap(bg, 0, 0, 0); // Desenha o fundo
    al_flip_display(); // Atualiza a tela
}

void reiniciarTelaJogo3(ALLEGRO_BITMAP* bg, ALLEGRO_BITMAP* sprite, ALLEGRO_FONT* font, ALLEGRO_DISPLAY* display, int* pos_x, int* pos_y, float* frame) {
    // Reinicia as variáveis do jogo
    *pos_x = 852;
    *pos_y = 410;
    *frame = 0;


    // Limpa a tela e redesenha o fundo
    al_clear_to_color(al_map_rgb(255, 255, 255));
    al_draw_bitmap(bg, 0, 0, 0); // Desenha o fundo
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
    ALLEGRO_BITMAP* popup_img11 = al_load_bitmap("./surpresa1.png"); // Imagem do pop-up 1.1
    ALLEGRO_BITMAP* popup_img3 = al_load_bitmap("./pop-up3.png"); // Imagem do pop-up 3
    ALLEGRO_BITMAP* popup_img4 = al_load_bitmap("./pop-up4.png"); // Imagem do pop-up 4
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

                if (pos_x >= 1120 && pos_y == 570) {
                    estadoAtual = TELA_FINAL; // Muda para a tela final
                }

                // Controle do frame do sprite
                frame += 0.3f; // Incrementa o contador de quadros
                if (frame > 3) {
                    frame -= 3; // Reinicia o contador se exceder
                }

                // Verifica a posição do personagem para mudar o estado para pop-up
                if (pos_x == 575 && pos_y >= 40 && pos_y <=55) {
                    estadoAtual = TELA_POPUP1; // Muda para o primeiro pop-up
                }

                if (pos_x == 800 && pos_y >= 40 && pos_y <= 55) {
                    estadoAtual = TELA_SURPRESA1; // Muda para o primeiro pop-up surpresa
                }

                if (pos_x >= 290 && pos_x <= 298 && pos_y == 250) {
                    estadoAtual = TELA_POPUP3; // Muda para o terceiro pop-up
                }

                if (pos_x >= 820 && pos_y >= 360 && pos_y <= 365) {
                    estadoAtual = TELA_POPUP4; // Muda para o quarto pop-up
                }


                // Limpa a tela e desenha o fundo e o personagem
                al_clear_to_color(al_map_rgb(255, 255, 255));
                al_draw_bitmap(bg, 0, 0, 0); // Desenha o fundo
                al_draw_bitmap_region(sprite, 48 * (int)frame, current_frame_y, 48, 64, pos_x, pos_y, 0); // Desenha o sprite do personagem
                al_flip_display(); // Atualiza a tela
            }
        }
        // Lógica para o primeiro pop-up
        else if (estadoAtual == TELA_POPUP1) {
            al_draw_bitmap(bg, 0, 0, 0); // Desenha o fundo
            al_draw_bitmap(popup_img1, 2, 360, 0); // Desenha o pop-up 1
            al_flip_display(); // Atualiza a tela

            if (event.type == ALLEGRO_EVENT_KEY_DOWN && event.keyboard.keycode == ALLEGRO_KEY_ESCAPE) {
                reiniciarTelaJogo(bg, sprite, font, display, &pos_x, &pos_y, &frame);
                estadoAtual = TELA_JOGO;
            }
        }
        // Lógica para o primeiro pop-up SURPRESA
        else if (estadoAtual == TELA_SURPRESA1) {
            al_draw_bitmap(bg, 0, 0, 0); // Desenha o fundo
            al_draw_bitmap(popup_img11, 2, 360, 0); // Desenha o pop-up 1
            al_flip_display(); // Atualiza a tela

            if (event.type == ALLEGRO_EVENT_KEY_DOWN && event.keyboard.keycode == ALLEGRO_KEY_ESCAPE) {
                reiniciarTelaJogo1(bg, sprite, font, display, &pos_x, &pos_y, &frame);
                estadoAtual = TELA_JOGO;
            }
        }

        // Lógica para o terceiro pop-up
        else if (estadoAtual == TELA_POPUP3) {
            al_draw_bitmap(bg, 0, 0, 0); // Desenha o fundo
            al_draw_bitmap(popup_img3, 2, 360, 0); // Desenha o pop-up 3
            al_flip_display(); // Atualiza a tela

            if (event.type == ALLEGRO_EVENT_KEY_DOWN && event.keyboard.keycode == ALLEGRO_KEY_ESCAPE) {
                reiniciarTelaJogo2(bg, sprite, font, display, &pos_x, &pos_y, &frame);
                estadoAtual = TELA_JOGO;
            }
        }

        // Lógica para o quarto pop-up
        else if (estadoAtual == TELA_POPUP4) {
            al_draw_bitmap(bg, 0, 0, 0); // Desenha o fundo
            al_draw_bitmap(popup_img4, 2, 360, 0); // Desenha o pop-up 3
            al_flip_display(); // Atualiza a tela

            if (event.type == ALLEGRO_EVENT_KEY_DOWN && event.keyboard.keycode == ALLEGRO_KEY_ESCAPE) {
                reiniciarTelaJogo3(bg, sprite, font, display, &pos_x, &pos_y, &frame);
                estadoAtual = TELA_JOGO;
            }
        }

        // Lógica para a tela final
        else if (estadoAtual == TELA_FINAL) {
            // Desenhar a imagem final
            al_draw_bitmap(bg, 0, 0, 0); // Desenha o fundo
            al_draw_bitmap(popup_img2, 0, 0, 0); // Posição centralizada para a img
            al_flip_display(); // Atualiza a tela

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
    al_destroy_bitmap(popup_img3);
    al_destroy_event_queue(event_queue);

    return 0;
}





//                                                 O CÓDIGO ABAIXO É O MINIGAME QUANDO O PERSONAGEM CHEGAR EM PARIS
//                                               NÃO CONSEGUI FAZER O CÓDIGO PRINCIPAL CHAMAR ESSE CÓDIGO DO MINIGAME






//
//#include <allegro5/allegro.h>
//#include <allegro5/allegro_primitives.h>
//#include <allegro5/allegro_font.h>
//#include <allegro5/allegro_ttf.h>
//
//#define SCREEN_WIDTH 800
//#define SCREEN_HEIGHT 600
//#define PADDLE_WIDTH 170
//#define PADDLE_HEIGHT 20
//#define BALL_SIZE 10
//#define BAR_WIDTH 90
//#define BAR_HEIGHT 20
//#define NUM_BARS 20 // Aumentando o número de barras
//
//// Estrutura para as barras
//typedef struct Bar {
//    float x, y;
//    bool active;
//} Bar;
//
//float paddle_x = SCREEN_WIDTH / 2 - PADDLE_WIDTH / 2;
//float paddle_y = SCREEN_HEIGHT - 50;
//float ball_x = SCREEN_WIDTH / 2;
//float ball_y = SCREEN_HEIGHT / 2;
//float ball_dx = 4.0f;
//float ball_dy = -4.0f;
//
//bool keys[2] = { false, false }; // Left, Right
//
//ALLEGRO_DISPLAY* display = NULL;
//ALLEGRO_EVENT_QUEUE* event_queue = NULL;
//ALLEGRO_TIMER* timer = NULL;
//ALLEGRO_FONT* font = NULL;
//
//// Declarando as barras como um array fixo
//Bar bars[NUM_BARS];
//
//void initialize() {
//    al_init();
//    al_init_primitives_addon();
//    al_init_font_addon();
//    al_init_ttf_addon();
//    al_install_keyboard();
//
//    display = al_create_display(SCREEN_WIDTH, SCREEN_HEIGHT);
//    event_queue = al_create_event_queue();
//    timer = al_create_timer(1.0 / 60.0); // 60 FPS
//
//    al_register_event_source(event_queue, al_get_display_event_source(display));
//    al_register_event_source(event_queue, al_get_keyboard_event_source());
//    al_register_event_source(event_queue, al_get_timer_event_source(timer));
//
//    font = al_create_builtin_font();
//
//    // Criar as barras no topo, distribuindo em várias linhas
//    int bars_per_row = SCREEN_WIDTH / (BAR_WIDTH + 10);  // Quantas barras cabem por linha
//    int current_row = 0;
//
//    for (int i = 0; i < NUM_BARS; i++) {
//        // Calcular a posição horizontal e vertical para as barras
//        bars[i].x = (i % bars_per_row) * (BAR_WIDTH + 10);  // Posição horizontal
//        bars[i].y = 50 + current_row * (BAR_HEIGHT + 5);    // Posição vertical
//        bars[i].active = true;                               // Barra ativa
//
//        // Mudar para a próxima linha quando atingir o final da linha
//        if ((i + 1) % bars_per_row == 0) {
//            current_row++;
//        }
//    }
//
//    al_start_timer(timer);
//}
//
//void draw_game() {
//    al_clear_to_color(al_map_rgb(0, 0, 0)); // Cor de fundo
//
//    // Desenhar o paddle
//    al_draw_filled_rectangle(paddle_x, paddle_y, paddle_x + PADDLE_WIDTH, paddle_y + PADDLE_HEIGHT, al_map_rgb(255, 0, 0));
//
//    // Desenhar a bola
//    al_draw_filled_circle(ball_x, ball_y, BALL_SIZE, al_map_rgb(0, 255, 0));
//
//    // Desenhar as barras
//    for (int i = 0; i < NUM_BARS; i++) {
//        if (bars[i].active) {
//            al_draw_filled_rectangle(bars[i].x, bars[i].y, bars[i].x + BAR_WIDTH, bars[i].y + BAR_HEIGHT, al_map_rgb(0, 0, 255));
//        }
//    }
//
//    al_flip_display();
//}
//
//void update_game() {
//    // Movimentação do paddle
//    if (keys[0] && paddle_x > 0) paddle_x -= 5.0f;
//    if (keys[1] && paddle_x < SCREEN_WIDTH - PADDLE_WIDTH) paddle_x += 5.0f;
//
//    // Movimentação da bola
//    ball_x += ball_dx;
//    ball_y += ball_dy;
//
//    // Colisão da bola com as paredes
//    if (ball_x - BALL_SIZE < 0 || ball_x + BALL_SIZE > SCREEN_WIDTH) ball_dx = -ball_dx;
//    if (ball_y - BALL_SIZE < 0) ball_dy = -ball_dy;
//
//    // Colisão da bola com o paddle
//    if (ball_y + BALL_SIZE >= paddle_y && ball_x >= paddle_x && ball_x <= paddle_x + PADDLE_WIDTH) {
//        ball_dy = -ball_dy;
//        ball_y = paddle_y - BALL_SIZE; // Evita que a bola fique presa no paddle
//    }
//
//    // Colisão da bola com as barras
//    for (int i = 0; i < NUM_BARS; i++) {
//        if (bars[i].active && ball_y - BALL_SIZE <= bars[i].y + BAR_HEIGHT && ball_x >= bars[i].x && ball_x <= bars[i].x + BAR_WIDTH) {
//            bars[i].active = false;  // Desativa a barra
//            ball_dy = -ball_dy;  // A bola rebate
//
//            // Acelerar a bola
//            ball_dx *= 1.05f;  // Aumenta a velocidade horizontal
//            ball_dy *= 1.05f;  // Aumenta a velocidade vertical
//        }
//    }
//
//    // Verificar se todas as barras foram destruídas
//    bool all_bars_destroyed = true;
//    for (int i = 0; i < NUM_BARS; i++) {
//        if (bars[i].active) {
//            all_bars_destroyed = false;
//            break;
//        }
//    }
//
//    if (all_bars_destroyed) {
//        al_draw_text(font, al_map_rgb(255, 255, 255), SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, ALLEGRO_ALIGN_CENTRE, "You Win!");
//        al_flip_display();
//        al_rest(2.0); // Pausa de 2 segundos para mostrar a mensagem
//        exit(0); // Encerra o jogo
//    }
//
//    // Caso a bola perca o paddle
//    if (ball_y > SCREEN_HEIGHT) {
//        // Game Over
//        al_draw_textf(font, al_map_rgb(255, 255, 255), SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, ALLEGRO_ALIGN_CENTRE, "Game Over!");
//        al_flip_display();
//        al_rest(2.0);
//        exit(0); // Encerra o jogo
//    }
//}
//
//int main() {
//    initialize();
//
//    while (true) {
//        ALLEGRO_EVENT event;
//        al_wait_for_event(event_queue, &event);
//
//        if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
//            break;
//
//        if (event.type == ALLEGRO_EVENT_KEY_DOWN) {
//            if (event.keyboard.keycode == ALLEGRO_KEY_LEFT) keys[0] = true;
//            if (event.keyboard.keycode == ALLEGRO_KEY_RIGHT) keys[1] = true;
//        }
//
//        if (event.type == ALLEGRO_EVENT_KEY_UP) {
//            if (event.keyboard.keycode == ALLEGRO_KEY_LEFT) keys[0] = false;
//            if (event.keyboard.keycode == ALLEGRO_KEY_RIGHT) keys[1] = false;
//        }
//
//        if (event.type == ALLEGRO_EVENT_TIMER) {
//            update_game();
//            draw_game();
//        }
//    }
//
//    al_destroy_display(display);
//    al_destroy_event_queue(event_queue);
//    al_destroy_timer(timer);
//    al_destroy_font(font);
//
//    return 0;
//}

