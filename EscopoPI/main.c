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
    al_draw_text(font, al_map_rgb(255, 255, 255), 5, 5, 0, "SCORE: dragão"); // Exibe a pontuação
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
    al_draw_text(font, al_map_rgb(255, 255, 255), 5, 5, 0, "SCORE: dragão"); // Exibe a pontuação
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
                if (pos_x == 575 && pos_y == 50) {
                    estadoAtual = TELA_POPUP1; // Muda para o primeiro pop-up
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
                al_draw_text(font, al_map_rgb(255, 255, 255), 5, 5, 0, "SCORE: dragão"); // Exibe a pontuação
                al_draw_bitmap_region(sprite, 48 * (int)frame, current_frame_y, 48, 64, pos_x, pos_y, 0); // Desenha o sprite do personagem
                al_flip_display(); // Atualiza a tela
            }
        }
        // Lógica para o primeiro pop-up
        else if (estadoAtual == TELA_POPUP1) {
            al_draw_bitmap(bg, 0, 0, 0); // Desenha o fundo
            al_draw_bitmap(popup_img1, 400, 200, 0); // Desenha o pop-up 1
            al_flip_display(); // Atualiza a tela

            if (event.type == ALLEGRO_EVENT_KEY_DOWN && event.keyboard.keycode == ALLEGRO_KEY_ESCAPE) {
                reiniciarTelaJogo(bg, sprite, font, display, &pos_x, &pos_y, &frame);
                estadoAtual = TELA_JOGO;
            }
        }

        // Lógica para o terceiro pop-up
        else if (estadoAtual == TELA_POPUP3) {
            al_draw_bitmap(bg, 0, 0, 0); // Desenha o fundo
            al_draw_bitmap(popup_img3, 400, 200, 0); // Desenha o pop-up 3
            al_flip_display(); // Atualiza a tela

            if (event.type == ALLEGRO_EVENT_KEY_DOWN && event.keyboard.keycode == ALLEGRO_KEY_ESCAPE) {
                reiniciarTelaJogo2(bg, sprite, font, display, &pos_x, &pos_y, &frame);
                estadoAtual = TELA_JOGO;
            }
        }

        // Lógica para o quarto pop-up
        else if (estadoAtual == TELA_POPUP4) {
            al_draw_bitmap(bg, 0, 0, 0); // Desenha o fundo
            al_draw_bitmap(popup_img3, 400, 200, 0); // Desenha o pop-up 3
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
// aqui no meu computador deu tudo certo, como tem vez que dá errado no senac vou deixar minha parte do minigame comentada 
//#include <allegro5/allegro.h>
//#include <allegro5/allegro_font.h>
//#include <allegro5/allegro_image.h>
//#include <allegro5/allegro_keyboard.h>
//#include <stdlib.h>
//#include <time.h>
//
//// Definindo os parâmetros do jogo
//#define LARGURA_TELA 800
//#define ALTURA_TELA 600
//#define SPRITE_LARGURA 64
//#define SPRITE_ALTURA 64
//#define VELOCIDADE_CANOS 5
//#define CANO_LARGURA 80
//#define ESPACO_ENTRE_CANOS 150
//
//typedef struct {
//    int x, y;
//    int largura, altura;
//} Cano;
//
//void desenhaCanos(Cano canos[], int quantidade, ALLEGRO_BITMAP* pipe) {
//    for (int i = 0; i < quantidade; i++) {
//        al_draw_bitmap(pipe, canos[i].x, canos[i].y, 0);
//    }
//}
//
//void moveCanos(Cano canos[], int quantidade) {
//    for (int i = 0; i < quantidade; i++) {
//        canos[i].x -= VELOCIDADE_CANOS;  // Move os canos para a esquerda
//        if (canos[i].x + CANO_LARGURA < 0) {
//            canos[i].x = LARGURA_TELA;
//            canos[i].y = rand() % (ALTURA_TELA - ESPACO_ENTRE_CANOS);  // Altera a altura do cano
//        }
//    }
//}
//
//bool checaColisao(int pos_x, int pos_y, Cano canos[], int quantidade) {
//    for (int i = 0; i < quantidade; i++) {
//        if (pos_x + SPRITE_LARGURA > canos[i].x && pos_x < canos[i].x + CANO_LARGURA) {
//            if (pos_y < canos[i].y || pos_y + SPRITE_ALTURA > canos[i].y + ESPACO_ENTRE_CANOS) {
//                return true;  // Colisão detectada
//            }
//        }
//    }
//    return false;
//}
//
//void telaFlappy(ALLEGRO_DISPLAY* display, ALLEGRO_FONT* font, ALLEGRO_BITMAP* bg, ALLEGRO_BITMAP* sprite, ALLEGRO_BITMAP* pipe) {
//    int pos_x = 300, pos_y = 315;  // Posição inicial do personagem
//    int score = 0;  // Pontuação do jogador
//    bool jogoAtivo = true;
//    ALLEGRO_KEYBOARD_STATE keyState;
//
//    // Inicializa os canos
//    Cano canos[3];
//    for (int i = 0; i < 3; i++) {
//        canos[i].x = LARGURA_TELA + i * (LARGURA_TELA / 2);  // Inicializa os canos fora da tela
//        canos[i].y = rand() % (ALTURA_TELA - ESPACO_ENTRE_CANOS);  // Altura aleatória dos canos
//        canos[i].largura = CANO_LARGURA;
//        canos[i].altura = ALTURA_TELA;
//    }
//
//    // Loop do mini-game
//    while (jogoAtivo) {
//        al_get_keyboard_state(&keyState);
//
//        // Verificar se o jogador pressionou ESC para sair do mini-game
//        if (al_key_down(&keyState, ALLEGRO_KEY_ESCAPE)) {
//            jogoAtivo = false;
//        }
//
//        // Movimentação do personagem (subir/descer)
//        if (al_key_down(&keyState, ALLEGRO_KEY_UP)) {
//            pos_y -= 2;  // Move para cima
//        }
//        if (al_key_down(&keyState, ALLEGRO_KEY_DOWN)) {
//            pos_y += 2;  // Move para baixo
//        }
//
//        // Garantir que o personagem não saia da tela
//        if (pos_y < 0) {
//            pos_y = 0;
//        }
//        else if (pos_y + SPRITE_ALTURA > ALTURA_TELA) {
//            pos_y = ALTURA_TELA - SPRITE_ALTURA;
//        }
//
//        // Movimenta os canos
//        moveCanos(canos, 3);
//
//        // Verifica colisões
//        if (checaColisao(pos_x, pos_y, canos, 3)) {
//            jogoAtivo = false;  // Fim de jogo
//        }
//
//        // Limpeza da tela e desenho dos elementos
//        al_clear_to_color(al_map_rgb(135, 206, 235)); // Fundo azul (céu)
//        al_draw_bitmap(bg, 0, 0, 0);  // Desenha o fundo
//        al_draw_bitmap_region(sprite, 0, 0, SPRITE_LARGURA, SPRITE_ALTURA, pos_x, pos_y, 0);  // Desenha o personagem
//        desenhaCanos(canos, 3, pipe);  // Desenha os canos
//
//        // Exibe a pontuação
//        char scoreText[20];
//        sprintf(scoreText, "Score: %d", score);
//        al_draw_text(font, al_map_rgb(255, 255, 255), 10, 10, 0, scoreText);
//
//        al_flip_display();  // Atualiza a tela
//
//        // Aumenta a pontuação conforme o tempo
//        score++;
//
//        // Aguarda um tempo para dar o efeito de FPS (40 FPS)
//        al_rest(0.025);
//    }
//}
//
//int main() {
//    // Inicializações
//    al_init();
//    al_init_font_addon();
//    al_init_image_addon();
//    al_install_keyboard();
//
//    ALLEGRO_DISPLAY* display = al_create_display(LARGURA_TELA, ALTURA_TELA);
//    al_set_window_title(display, "Mini-Game Flappy");
//
//    ALLEGRO_FONT* font = al_create_builtin_font();
//    ALLEGRO_BITMAP* sprite = al_load_bitmap("./flappy_bird.png"); // Sprite do personagem
//    ALLEGRO_BITMAP* bg = al_load_bitmap("./background.png");       // Imagem de fundo
//    ALLEGRO_BITMAP* pipe = al_load_bitmap("./pipe.png");           // Imagem do cano
//
//    if (!sprite || !bg || !pipe) {
//        printf("Erro ao carregar as imagens!\n");
//        return -1;
//    }
//
//    // Chama o mini-game
//    telaFlappy(display, font, bg, sprite, pipe);
//
//    // Libera recursos
//    al_destroy_bitmap(sprite);
//    al_destroy_bitmap(bg);
//    al_destroy_bitmap(pipe);
//    al_destroy_font(font);
//    al_destroy_display(display);
//
//    return 0;
//}

