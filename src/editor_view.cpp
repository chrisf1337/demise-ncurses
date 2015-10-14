#include <memory>
#include <cmath>
#include <cassert>

#include <ncurses.h>

#include "editor_view.hpp"
#include "utils.hpp"
#include "editor_action.hpp"

static const int KEY_ESC = 27;

using TAP::EditorView;
using TAP::Utils::InclusiveRange;
using TAP::EditorAction;
using TAP::MoveAction;
using TAP::InsertAtUserPointAction;
using TAP::ActionResult;

EditorView::EditorView()
{
    getmaxyx(stdscr, _HEIGHT, _WIDTH);
    _lineNumberWindowWidth = (int) (log10(_HEIGHT) + 2);
    _currentBuffer = _editor._currentBuffer;
    assert(_WIDTH > _lineNumberWindowWidth);

    _textWindow = newwin(_HEIGHT - 2, _WIDTH - _lineNumberWindowWidth, 0, _lineNumberWindowWidth);
    _lineNumberWindow = newwin(_HEIGHT - 2, _lineNumberWindowWidth, 0, 0);
    _statusWindow = newwin(1, _WIDTH, _HEIGHT - 2, 0);
    _commandModeWindow = newwin(1, _WIDTH, _HEIGHT - 1, 0);
    wrefresh(_textWindow);
    wrefresh(_lineNumberWindow);
    wrefresh(_statusWindow);
    wrefresh(_commandModeWindow);

    typedef spdlog::sinks::simple_file_sink_mt simpleFileSink;
    _logger = std::make_unique<spdlog::logger>("demise-ncurses",
                                               std::make_shared<simpleFileSink>("../log/demise-ncurses.log",
                                                                                true));
}

EditorView::~EditorView()
{
    delwin(_textWindow);
    delwin(_lineNumberWindow);
    delwin(_statusWindow);
    delwin(_commandModeWindow);
}

void EditorView::initScreen()
{
    _currentBuffer = _editor._currentBuffer;
    if (_currentBuffer == nullptr) return;
    std::string line;
    size_t numLines = (size_t) _HEIGHT < _currentBuffer->_lineStarts.size() ? _HEIGHT :
        _currentBuffer->_lineStarts.size();
    _logger->info("Current buffer ");
    for (size_t i = 0; i < numLines; ++i)
    {
        size_t currentLineStart = _currentBuffer->_lineStarts[i];
        size_t nextLineStart;
        if (i == numLines - 1)
        {
            nextLineStart = _currentBuffer->_contents.size() - 1;
        }
        else
        {
            nextLineStart = _currentBuffer->_lineStarts[i + 1];
        }
        line = _currentBuffer->rangeToString(InclusiveRange(currentLineStart, nextLineStart - 1));
        _logger->info("{}", i);
        mvwprintw(_textWindow, i, 0, "%s", line.c_str());
        mvwprintw(_lineNumberWindow, i, 0, "%lu", i + 1);
    }
    mvwprintw(_statusWindow, 0, 0, "%s", _currentBuffer->_name.c_str());
    mvwprintw(_commandModeWindow, 0, 0, "Command mode window");

    wrefresh(_textWindow);
    wrefresh(_lineNumberWindow);
    wrefresh(_statusWindow);
    wrefresh(_commandModeWindow);
}

void EditorView::respondToUserInput()
{
    int key;
    assert(_textWindow);
    while ((key = wgetch(_textWindow)) != KEY_ESC)
    // while ((key = wgetch(_textWindow)))
    {
        _logger->info("{}", key);
        InsertAtUserPointAction action(&_editor, "abc");
        ActionResult result = _editor.performAction(action);
        int intResult = *boost::get<int>(&result);
        _logger->info("{}", intResult);
    }
}
