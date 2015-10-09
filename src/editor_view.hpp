#ifndef DEMISE_NCURSES_EDITOR_VIEW
#define DEMISE_NCURSES_EDITOR_VIEW

#include "editor.hpp"

using TAP::Editor;

namespace TAP
{

class EditorView
{
public:
    EditorView();

    Editor editor;
};
}

#endif
