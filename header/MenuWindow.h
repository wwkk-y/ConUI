/*****************************************************************************
* @Author  : JamesNULLiu                                                     *
* @Date    : 2022/Sep/18                                                     *
* @File    :                                                                 *
* @Brief   :                                                                 *
* @Version : 1.0.0.0                                                         *
*****************************************************************************/

#ifndef CUI_MENUWINDOW_H
#define CUI_MENUWINDOW_H
#include "BaseWindow.h"
namespace cui {
    class MenuWindow : public BaseWindow
    {
        using Position = BaseWindow::Position;
        MenuWindow(Position leftTop = { 0,0 }, Position rightBot = { 3,20 })
            : BaseWindow(leftTop, rightBot) {}
    };

    extern MenuWindow menu;
}

#endif // !CUI_MENUWINDOW_H
