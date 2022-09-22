#include "../header/BaseWindow.h"

cui::BaseWindow::BaseWindow(Position leftTop, Position rightBot)
{
    if (!(PositionComp()(leftTop, rightBot))) {
        throw; return;
    }
    // Get an available id for the new window, and pop the id from {_id_SET} :
    _windowID = _id_SET.get_availableAndPop();
    // Set 2 points' positions in {_allPosition[_windowID]} :
    _allPosition[_windowID][0].absolutePos = leftTop;
    _allPosition[_windowID][1].absolutePos = rightBot;
    // Increase {_numOfWindow} :
    ++_numOfWindow;
    // Calculate offset :
    _offsetOnX = leftTop.X;
    _offsetOnY = leftTop.Y;
}

cui::BaseWindow::~BaseWindow()
{
    // Erase the window's position information in {_allPosition}.
    _allPosition.erase(_windowID);
    // Push its {_windowID} back to {_id_SET} :
    _id_SET.push(_windowID);
    // Decrease {_numOfWindow}:
    --_numOfWindow;
}

void cui::BaseWindow::refresh() const
{
    for (const std::pair<Position, Point>& point : _existPoint) {
        this->gotoXY(point.second.absolutePos);
        setOutputColor(point.second.color);
        printf("%c", point.second.ch);
    }
}