#include <ncurses.h>

struct linked_list {
        char* desc;
        struct linked_list* next;
        struct linked_list* prev;
};

struct linked_list* todo_list = NULL; 
struct linked_list* selected = NULL;

/* screen size */
int x, y;

void remove_item()
{
        if (selected->prev)
                selected->prev->next = selected->next;
        if (selected->next)
                selected->next->prev = selected->prev;
        selected = (selected->prev) ? selected->prev : (selected->next) ? selected->next : NULL;
}

int main()
{
        /* ncurses init functions */
        initscr();
        noecho();
        keypad(stdscr, TRUE);
        getmaxyx(stdscr, x, y);

        int running = 1;
        int c;

        /* main loop */
        while (running) {
                print_list();

                c = getch();

                switch(c) {
                        case 'a':
                                add_item();
                                break;
                        case 'x':
                                remove_item();
                                break;
                        case 'q':
                                running = FALSE;
                                break;
                        case KEY_UP:
                                if (selected->prev)
                                        selected = selected->prev;
                                break;
                        case KEY_DOWN:
                                if (selected->next)
                                        selected = selected->next;
                                break;
                        default:
                                break;
                }
        }

        endwin();
        return 0;
}
