/*****************************************************************************
* @Author  : JamesNULLiu                                                     *
* @Date    : 2022/Sep/18                                                     *
* @File    : Point.h                                                         *
* @Brief   : Definition of class {Point}                                     *
*            | and revelant class {Color} {Iten} {PointColor}.               *
*            Definition of class {PositionComp} which is used as a function  *
*            | object when creating map with key {Position}.                 *
*            | Specifically, {PositionComp} is used in:                      *
*            |   - "BasedWindow.h"                                           *
* @Version : 1.0.0.0                                                         *
******************************************************************************
* Change History:                                                            *
* 2022/Sep/20 JamesNULLiu                                                    *
* |- Override {operator==()} in class {Point}.                               *
*****************************************************************************/

#ifndef CUI_POINT_H
#define CUI_POINT_H
#include <Windows.h>
#include <iostream>

namespace cui {
    /**
     * @brief A {Point} object has 3 members:
              1. {(char)ch} implies whant charactor the point is holding.
              2. {(Position)absolutePos} is the absolute position of the point.
                 Type {Position} using type {POINT}, which has 2 members: (long)x and (long)y.
              3. {(PointColor)color} is the color information.
                 Type {PointColor} is self defined struct. See the breif intro of the struct in this .h file.
    */
    inline void setColor(WORD color=0x07)
    {
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole, color);
    }

    inline void gotoxy(int x, int y)//¾ø¶ÔÎ»ÖÃ
    {
        HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
        COORD pos;
        pos.X = x;
        pos.Y = y;//COORD pos = {x,y}; 
        SetConsoleCursorPosition(handle, pos);
    }

    struct PointColor
    {
        WORD front;
        WORD back;
        PointColor(WORD front = 0x7, WORD back = 0x0) :front(front), back(back) {};
        void setFront(WORD front) { this->front = front; }
        void setBack(WORD back) { this->back = back; }
        void setColor(WORD color) { back = color / 16;  front = color % 16; }
        PointColor& operator=(WORD color)
        {
            back = color / 16;  front = color % 16;
            return *this;
        }
    };

    struct Point
    {
        using Position = POINT;

        char ch = '%';                     // charactor stored in the point
        Position absolutePos = { 0, 0 };   // abosolute position of the point
        PointColor color;                  // (foreGound & backGround) (color & intensity)

        //Point() = default;                 // constructor
        Point(int x=0, int y=0) :absolutePos{ x, y } {};

        Point operator=(const Point& tP)
        {
            this->ch = tP.ch;
            this->absolutePos = tP.absolutePos;
            this->color = tP.color;
        }

        bool operator==(const Point& tP)
        {
            return (this->absolutePos.x == tP.absolutePos.x) && (this->absolutePos.y == tP.absolutePos.y);
        }

        friend std::ostream& operator<<(std::ostream& os, Point& rhs)
        {
            gotoxy(rhs.absolutePos.x, rhs.absolutePos.y);
            setColor(rhs.color.back * 16 + rhs.color.front);
            os << rhs.ch;

            return os;
        }
    };

    struct Color
    {
        const static WORD
            black = 0, blueLight = 1, greenLight = 2, blueLake = 3,
            redLight = 4, purple = 5, yellow = 6, white = 7,
            blackLight = 8, blue = 9, green = 0xa, greenLightLight = 0xb,
            red = 0xc, purpleLight = 0xd, yellowLight = 0xe, whiteLight = 0xf;
    };
    //enum class Inten { off = 0, on };

    /**
     * @brief The struct is only for all color information of one point, using enum class {Color} and {Inten}.
     * The color information is: foreground / background color and intensity.
    */

    struct PositionComp
    {
        using Position = POINT;
        bool operator()(const Position& p1, const Position& p2)
        {
            return p1.x != p2.x || p1.y != p2.y;
        }
    };

    extern PositionComp posComp;
}
#endif // !CUI_POINT_H

/*
int main()
{
    using namespace cui;
    using namespace std;
    Point p={2,3};
    p.color.setFront(Color::purple);
    p.color.setBack(Color::white);
    cout << p;
    cin.get();
    return 0;
}
*/