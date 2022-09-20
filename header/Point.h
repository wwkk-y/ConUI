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
namespace cui {
    /**
     * @brief A {Point} object has 3 members:
              1. {(char)ch} implies whant charactor the point is holding.
              2. {(Position)absolutePos} is the absolute position of the point.
                 Type {Position} using type {POINT}, which has 2 members: (long)x and (long)y.
              3. {(PointColor)color} is the color information.
                 Type {PointColor} is self defined struct. See the breif intro of the struct in this .h file.
    */
    struct Point
    {
        using Position = POINT;

        char ch = '%';                     // charactor stored in the point
        Position absolutePos = { 0, 0 };   // abosolute position of the point
        PointColor color;                  // (foreGound & backGround) (color & intensity)

        Point() = default;                 // constructor

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
    };

    enum class Color { black = 0, blue, green, red, cyan, pink, yellow, white };
    enum class Inten { off = 0, on };

    /**
     * @brief The struct is only for all color information of one point, using enum class {Color} and {Inten}.
     * The color information is: foreground / background color and intensity.
    */
    struct PointColor
    {
        Color foreGround = Color::white;   // foreground color
        Inten foreIntens = Inten::on;      // foreground intensity
        Color backGround = Color::black;   // background color
        Inten backIntens = Inten::off;     // background intensity

        PointColor() = default;

        PointColor operator=(const PointColor tPC)
        {
            this->foreGround = tPC.foreGround;
            this->foreIntens = tPC.foreIntens;
            this->backGround = tPC.backGround;
            this->backIntens = tPC.backIntens;
        }
    };

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
