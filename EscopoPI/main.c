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

    ALLEGRO_DISPLAY* display = al_create_display(1200, 673);
    al_set_window_position(display, 200, 200);
    al_set_window_title(display, "Here be Dragons!");

    ALLEGRO_FONT* font = al_create_builtin_font();
    ALLEGRO_TIMER* timer = al_create_timer(1.0 / 1.0);

    ALLEGRO_BITMAP* sprite = al_load_bitmap("./MEN.png");
    ALLEGRO_BITMAP* bg = al_load_bitmap("./bg.png");

    ALLEGRO_EVENT_QUEUE* event_queue = al_create_event_queue();
    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_timer_event_source(timer));
    al_register_event_source(event_queue, al_get_keyboard_event_source());
    al_start_timer(timer);

    float frame = 0.f;
    int pos_x = 115, pos_y = 50;
    int current_frame_y = 64;

    while (true) {
        ALLEGRO_EVENT event;
        al_wait_for_event(event_queue, &event);
        if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
            break;
        }
        else if (event.keyboard.keycode == ALLEGRO_KEY_RIGHT) {
            current_frame_y = 64;
            pos_x += 2;
        }
        else if (event.keyboard.keycode == ALLEGRO_KEY_LEFT) {
            current_frame_y = 64 * 3;
            pos_x -= 2;
        }
        else if (event.keyboard.keycode == ALLEGRO_KEY_DOWN) {
            current_frame_y = 64 * 2;
            pos_y += 2;
        }
        else if (event.keyboard.keycode == ALLEGRO_KEY_UP) {
            current_frame_y = 0;
            pos_y -= 2;
        }

        frame += 0.3f;
        if (frame > 3) {
            frame -= 3;
        }

        al_clear_to_color(al_map_rgb(255, 255, 255));
        al_draw_bitmap(bg, 0, 0, 0);
        al_draw_text(font, al_map_rgb(0, 0, 0), 7, 7, 0, "SCORE: dragon");
        al_draw_text(font, al_map_rgb(255, 255, 255), 5, 5, 0, "SCORE: dragon");
        al_draw_bitmap_region(sprite, 48 * (int)frame, current_frame_y, 48, 64, pos_x, pos_y, 0);
        al_flip_display();
    }

    al_destroy_bitmap(bg);
    al_destroy_bitmap(sprite);
    al_destroy_font(font);
    al_destroy_display(display);
    al_destroy_event_queue(event_queue);

    return 0;
}