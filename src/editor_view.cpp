#include <memory>
#include <cmath>
#include <cassert>

#include <ncurses.h>

#include "editor_view.hpp"
#include "utils.hpp"

using TAP::EditorView;
using TAP::Utils::InclusiveRange;

EditorView::EditorView()
{
    getmaxyx(stdscr, _HEIGHT, _WIDTH);
    _lineNumberWindowWidth = (int) (log10(_HEIGHT) + 2);
    _currentBuffer = _editor._currentBuffer;
    assert(_WIDTH > _lineNumberWindowWidth);

    _textWindow = newwin(_HEIGHT, _WIDTH - _lineNumberWindowWidth, 0, _lineNumberWindowWidth);
    _lineNumberWindow = newwin(_HEIGHT, _lineNumberWindowWidth, 0, 0);
    wrefresh(_textWindow);
    wrefresh(_lineNumberWindow);

    typedef spdlog::sinks::simple_file_sink_mt simpleFileSink;
    _logger = std::make_unique<spdlog::logger>("demise-ncurses",
                                               std::make_shared<simpleFileSink>("../log/demise-ncurses.log",
                                                                                true));
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
    size_t numLines = (size_t) _HEIGHT < _currentBuffer->_lineStarts.size() ? _HEIGHT :
        _currentBuffer->_lineStarts.size();
    _logger->info("test");
    for (size_t i = 0; i < numLines; ++i)
    {
        size_t currentLineStart = _currentBuffer->_lineStarts[i];
        size_t nextLineStart = _currentBuffer->_lineStarts[i + 1];
        line = _currentBuffer->rangeToString(InclusiveRange(currentLineStart, nextLineStart - 1));
        mvwprintw(_textWindow, i, 0, "%s", line.c_str());
        mvwprintw(_lineNumberWindow, i, 0, "%lu", i + 1);
    }
    wrefresh(_textWindow);
    wrefresh(_lineNumberWindow);
}
