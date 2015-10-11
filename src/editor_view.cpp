#include <memory>
#include <cmath>
#include <cassert>

#include <ncurses.h>

#include "editor_view.hpp"
#include "utils.hpp"

using TAP::EditorView;
using Utils::InclusiveRange;

EditorView::EditorView()
{
    getmaxyx(stdscr, _HEIGHT, _WIDTH);
    _lineNumberWindowWidth = (int) (log10(_HEIGHT) + 1);
    _currentBuffer = _editor._currentBuffer;
    assert(_WIDTH > _lineNumberWindowWidth);

    _textWindow = newwin(_HEIGHT, _WIDTH - _lineNumberWindowWidth, 0, _lineNumberWindowWidth);
    _lineNumberWindow = newwin(_HEIGHT, _lineNumberWindowWidth, 0, 0);
    wrefresh(_textWindow);
    wrefresh(_lineNumberWindow);
}

EditorView::~EditorView()
{
    delwin(_textWindow);
    delwin(_lineNumberWindow);
}

void EditorView::initScreen()
{
    _currentBuffer = _editor._currentBuffer;
    if (!_currentBuffer) return;
    std::string line;
    for (size_t i = 0; i < 10; ++i)
    {
        size_t currentLineStart = _currentBuffer->_lineStarts[i];
        size_t nextLineStart = _currentBuffer->_lineStarts[i + 1];
        line = _currentBuffer->rangeToString(InclusiveRange(currentLineStart, nextLineStart - 1));
        mvwprintw(_textWindow, i, 0, "%s", line.c_str());
    }
    wrefresh(_textWindow);
}
