#include <ncurses.h>

#include "editor_view.hpp"

using TAP::EditorView;

void init()
{
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
}

int main()
{
    init();
    EditorView editorView;
    getch();
    endwin();
    return 0;
}
