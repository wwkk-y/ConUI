/*****************************************************************************
* @Author  : JamesNULLiu                                                     *
* @Date    : 2022/09/18                                                      *
* @File    :                                                                 *
* @Brief   :                                                                 *
* @Version : 1.0.0.0                                                         *
*****************************************************************************/

#ifndef CUI_BASEWINDOW_H
#define CUI_BASEWINDOW_H
#include <unordered_map>
#include "Point.h"
#include "ID_Set.h"

namespace cui {
    class BaseWindow
    {
    public:
        using allWinMap = std::unordered_map<int, Point[2]>;
        using Position = Point::Position;
        using exiPntMap = std::unordered_map<Position, Point, PositionComp>;

        BaseWindow(Position leftTop = { 0,0 }, Position rightBot = { 0,0 });
        ~BaseWindow();

    public:
        virtual void output() = 0;

    public:
        /**
         * @brief Return the distance from line x = 0 or y = 0 to 4 borders.
         * @param option <0> line x = 0 to left border; <1> line y = 0 to top border; <2> line x = 0 to right border; <3> line y = 0 to bottom border;
         * @return Return the distance based on {option}.
         */
        int get_border(int option) const;
        void addPoint();
        void gotoXY() const;
        /**
         * @brief  Refresh current window based on existing points in {_existPoint}.
         */
        void refresh();
        /**
         * @brief Resize the window.
         * @param row The number of row increased / decreased, <0> as not change.
         * @param col The number of column increased / decreased, <0> as not change.
         */
        void resize(int row, int col);
        /**
         * @ brief Move the left-top point (as well as the whole window) to targetPoint.
         */
        void move(const Position& targetPoint);
        bool checkRange(const Position& tPos) const;

    private: // Static members.
        static ID_set      __ID_SET;             // a set of all available IDs
        static int         __NUMOFWINDOW;        // number of exsisting windows
        static allWinMap   __ALLPOSITION;        // a map of all exsisting windows' positions with key {_windowID}

    private:
        int                _windowID;            // unique ID
        int                _offsetOnX;           // X axis offset based on absolute position of window.
        int                _offsetOnY;           // Y axis offset based on absolute position of window.
        exiPntMap          _existPoint;          // all exist points are stored in the map, with position as key.
    };

    inline BaseWindow::BaseWindow(Position leftTop, Position rightBot)
    {
        if (!(PositionComp()(leftTop, rightBot))) {
            throw; return;
        }
        // Get an available id for the new window, and pop the id from {__ID_SET} :
        _windowID = __ID_SET.get_availableAndPop();
        // Set 2 points' positions in {__ALLPOSITION[_windowID]} :
        __ALLPOSITION[_windowID][0].absolutePos = leftTop;
        __ALLPOSITION[_windowID][1].absolutePos = rightBot;
        // Increase {__NUMOFWINDOW} :
        ++__NUMOFWINDOW;
        // Calculate offset :
        _offsetOnX = leftTop.x;
        _offsetOnY = leftTop.y;
    }

    inline BaseWindow::~BaseWindow()
    {
        // When closing a window, push its {_windowID} back to {__ID_SET} :
        __ID_SET.push(_windowID);
        // Decrease {__NUMOFWINDOW}:
        --__NUMOFWINDOW;
    }

    inline int BaseWindow::get_border(int option) const
    {
        switch (option) {
        case 0: return __ALLPOSITION[_windowID][0].absolutePos.x; break;
        case 1: return __ALLPOSITION[_windowID][0].absolutePos.y; break;
        case 2: return __ALLPOSITION[_windowID][1].absolutePos.x; break;
        case 3: return __ALLPOSITION[_windowID][1].absolutePos.y; break;
        default: throw; return -1; break;
        }
    }

    inline bool BaseWindow::checkRange(const BaseWindow::Position& tPos) const
    {
        return (tPos.x > get_border(0) && tPos.x < get_border(2) && tPos.y>get_border(1) && tPos.y < get_border(3));
    }
}
#endif // !CUI_BASEWINDOW_H
