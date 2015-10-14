#include <ncurses.h>
#include <iostream>

#include "editor_view.hpp"

using TAP::EditorView;

void init()
{
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    nodelay(stdscr, TRUE);
    refresh();
}

int main(int argc, char **argv)
{
    init();
    EditorView editorView;
    if (argc == 2)
    {
        std::string file(argv[1]);
        editorView._editor.openFile(file);
    }
    editorView.initScreen();
    editorView.respondToUserInput();
    getch();
    endwin();
    std::cout << editorView._editor._buffers.size() << std::endl;
    std::cout << "Demise v0.01" << std::endl;
    return 0;
}
