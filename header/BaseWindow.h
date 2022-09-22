/*****************************************************************************
* @Author  : JamesNULLiu                                                     *
* @Date    : 2022/Sep/18                                                     *
* @File    : BaseWindow.h                                                    *
* @Brief   : The abstract class of all window object.                        *
*            Three static member is for storing overall information:         *
*            | {__ID_set} is a set of all available IDs. When creating a wi- *
*            | | dow, it is given a unique ID from the set. To change the d- *
*            | | efault number of IDs, i.e., the maximun number of existing  *
*            | | windows, go to file "ID_Set.h" and change {MAXIDNUM}.       *
*            | {_numOfWindow} counts the number of existing windows.         *
*            | {_allPosition} is a map stroing position informating of all   *
*            | | existing windows, with each window's ID as the KEY. The va- *
*            | | lue is 2 * Point, respectively the left-top and the right-  *
*            | | bottom. Point type objects also carry color and char infor- *
*            | | mation which will by the way set the apparence of the wind- *
*            | | ow.                                                         *
*            {_existPoint} is a map of all existing points inside the windo- *
*            | w, with each point's POSITION as the KEY. The definition of   *
*            | POSITION and the function object to compare 2 POSITION objec- *
*            | ts are in file "Point.h".                                     *
*            {_thisConsole} is the handle of the console.                    *
* @Version : 1.0.2.0                                                         *
*****************************************************************************/

#ifndef CUI_BASEWINDOW_H
#define CUI_BASEWINDOW_H
#include <unordered_map>
#include <Windows.h>
#include <utility>
#include "Point.h"
#include "ID_Set.h"

namespace cui {
    // Handle of the console.
    extern HANDLE _thisConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    class BaseWindow
    {
    public:
        using allWinMap = std::unordered_map<int, Point[2]>;
        using Position = Point::Position;
        using exiPntMap = std::unordered_map<Position, Point, PositionComp>;

        BaseWindow(Position leftTop = { 0,0 }, Position rightBot = { 0,0 });
        ~BaseWindow();

    public:
        /**
         * @brief Return the distance from line x = 0 or y = 0 to 4 borders.
         * @param option <0> line x = 0 to left border; <1> line y = 0 to top border; <2> line x = 0 to right border; <3> line y = 0 to bottom border;
         * @return Return the distance based on {option}.
         */
        int get_border(int option) const;
        /**
         * @brief Move coursor to position {tPos}.
        */
        void gotoXY(Position tPos) const { SetConsoleCursorPosition(_thisConsole, tPos); }
        /**
         * @brief Set output color to {color}.
        */
        void setOutputColor(WORD color) const { SetConsoleTextAttribute(_thisConsole, color); }
        /**
         * @brief  Refresh current window based on existing points in {_existPoint}.
        */
        void refresh() const;

    public:
        /**
         * @brief Add a point in current window.
        */
        virtual void addPoint() = 0;
        /**
         * @brief Add an element in current window.
         * @tparam ElemType
        */
        template<class ElemType> void addElem() = 0;
        /**
         * @brief Resize the window.
         * @param row The number of row increased, <0> as not change.
         * @param col The number of column increased, <0> as not change.
        */
        virtual void resize(int row, int col) = 0;
        /**
         * @brief Move the left-top point (as well as the whole window) to targetPoint.
        */
        virtual void move(const Position& targetPoint) = 0;
        /**
         * @brief Check whether position {tPos} is in the range of current window.
        */
        bool checkRange(const Position& tPos) const { return (tPos.X > get_border(0) && tPos.X < get_border(2) && tPos.Y > get_border(1) && tPos.Y < get_border(3)); }

    private: // Static members.
        static ID_set      _id_SET;              // a set of all available IDs
        static int         _numOfWindow;         // number of exsisting windows
        static allWinMap   _allPosition;         // a map of all exsisting windows' positions with key {_windowID}

    private:
        int                _windowID;            // unique ID
        int                _offsetOnX;           // X axis offset based on absolute position of window.
        int                _offsetOnY;           // Y axis offset based on absolute position of window.
        exiPntMap          _existPoint;          // all exist points are stored in the map, with position as key.
    };


    inline int BaseWindow::get_border(int option) const
    {
        switch (option) {
        case 0: return _allPosition[_windowID][0].absolutePos.X; break;
        case 1: return _allPosition[_windowID][0].absolutePos.Y; break;
        case 2: return _allPosition[_windowID][1].absolutePos.X; break;
        case 3: return _allPosition[_windowID][1].absolutePos.Y; break;
        default: throw; return -1; break;
        }
    }
}
#endif // !CUI_BASEWINDOW_H
