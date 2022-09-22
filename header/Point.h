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
              2. {(Position)relativePos} is the relative position of the point.
                 Type {Position} using type {POINT}, which has 2 members: (long)x and (long)y.
              3. {(PointColor)color} is the color information.
                 Type {PointColor} is self defined struct. See the breif intro of the struct in this .h file.
    */
    struct Point
    {
        using Position = COORD;
    public: // Operator override
        Point operator=(const Point& tP)
        {
            this->ch = tP.ch;
            this->relativePos = tP.relativePos;
            this->color = tP.color;
        }
        // @brief Compares whether 2 Points have the same position.
        bool operator==(const Point& tP) { return (this->relativePos.X == tP.relativePos.X) && (this->relativePos.Y == tP.relativePos.Y); }
        // @brief Print method overriding {operator<<},
        friend std::ostream& operator<<(std::ostream& os, Point& rhs)
        {
            // Set cursor position:
            SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), rhs.relativePos);
            // Set color:
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), rhs.color.backColor << 4 + rhs.color.frontColor);
            os << rhs.ch;
            return os;
        }
    public: // Member
        char ch = '%';                     // charactor stored in the point
        Position relativePos = { 0, 0 };   // relative position of the point
        PointColor color;                  // (foreGound & backGround) (color & intensity)
        // @}
    public: // Method
        Point() = default;
        Point(const Position& pos) :relativePos(pos) {}
        Point(int x = 0, int y = 0) :relativePos{ x, y } {}

        // @breif Print method with {printf()}.
        void printPoint()
        {
            // Set cursor position:
            SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), this->relativePos);
            // Set color:
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), this->color.backColor << 4 + this->color.frontColor);
            printf("%c", ch);
        }
    };

    //inline void setColor(WORD color = 0x07)
    //{
    //    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    //    SetConsoleTextAttribute(hConsole, color);
    //}

    inline void gotoxy(int x, int y) //¾ø¶ÔÎ»ÖÃ
    {
        HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
        COORD pos;
        SetConsoleCursorPosition(handle, pos);
    }

    struct PointColor
    {
        WORD frontColor;
        WORD backColor;
        PointColor(WORD frontColor = 0x7, WORD backColor = 0x0) :frontColor(frontColor), backColor(backColor) {};
        void setFront(WORD frontColor) { this->frontColor = frontColor; }
        void setBack(WORD backColor) { this->backColor = backColor; }
        void setColor(WORD color) { backColor = color / 16;  frontColor = color % 16; }
        PointColor& operator=(WORD color)
        {
            backColor = color / 16;  frontColor = color % 16;
            return *this;
        }
    };

    // @brief Compare class for {Position} object. Override {operator()}, return {true} if two position not equal.
    //        e.g. if(PositionComp()(a, b)){...} compares if (Position)a and (Position)b equals.
    struct PositionComp
    {
        using Position = POINT;
        bool operator()(const Position& p1, const Position& p2)
        {
            return p1.x != p2.x || p1.y != p2.y;
        }
    };
}
#endif // !CUI_POINT_H