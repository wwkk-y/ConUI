/*****************************************************************************
* @Author  : JamesNULLiu                                                     *
* @Date    : 2022/Sep/18                                                     *
* @File    : Point.h                                                         *
* @Brief   : Definition of class {Point}.                                    *
*            Definition of class {PositionComp} which is used as a function  *
*            | object when creating map with key {Position}.                 *
*            | Specifically, {PositionComp} is used in:                      *
*            |   - "BasedWindow.h"                                           *
* @Version : 1.0.2.0                                                         *
*****************************************************************************/

#ifndef CUI_POINT_H
#define CUI_POINT_H
#include <Windows.h>
#include <iostream>

namespace cui {
    /**
     * @brief A {Point} object has 3 members:
              | 1. {(char)ch} implies whant charactor the point is holding.
              | 2. {(Position)absolutePos} is the absolute position of the point.
              |  | Type {Position} using type {COORD}, which has 2 members: (short)X and (short)Y.
              | 3. {(WORD)color} is the color information.
    */
    struct Point
    {
        using Position = COORD;
        char ch = '%';                     // charactor stored in the point
        Position absolutePos = { 0, 0 };   // abosolute position of the point
        WORD color = 0x0;                  // (foreGound & backGround) (color & intensity)
        Point() = default;                 // constructor
        Point(int x = 0, int y = 0) :absolutePos{ x, y } {};
    };
    struct PositionComp
    {
        using Position = Point::Position;
        bool operator()(const Position& p1, const Position& p2)
        {
            return p1.X != p2.X || p1.Y != p2.Y;
        }
    };
}

#endif // !CUI_POINT_H

