#ifndef DEMISE_NCURSES_EDITOR_VIEW
#define DEMISE_NCURSES_EDITOR_VIEW

#include <ncurses.h>

#include "editor.hpp"
#include "buffer.hpp"

namespace TAP
{
class EditorView
{
public:
    EditorView();
    ~EditorView();

    void initScreen();

    TAP::Editor _editor;
    TAP::Buffer *_currentBuffer;

    WINDOW *_textWindow;
    WINDOW *_lineNumberWindow;

    int _lineNumberWindowWidth;

    int _HEIGHT;
    int _WIDTH;
};
}

#endif
