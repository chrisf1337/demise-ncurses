#ifndef DEMISE_NCURSES_EDITOR_VIEW
#define DEMISE_NCURSES_EDITOR_VIEW

#include <memory>

#include <ncurses.h>
#include "spdlog.h"

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
    void respondToUserInput();

    TAP::Editor _editor;
    TAP::Buffer *_currentBuffer;

    WINDOW *_textWindow;
    WINDOW *_lineNumberWindow;
    WINDOW *_statusWindow;
    WINDOW *_commandModeWindow;

    int _lineNumberWindowWidth;

    int _HEIGHT;
    int _WIDTH;

private:
    std::unique_ptr<spdlog::logger> _logger;
};
}

#endif
