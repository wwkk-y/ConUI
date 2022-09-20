/*****************************************************************************
* @Author  : JamesNULLiu                                                     *
* @Date    : 2022/09/18                                                      *
* @File    :                                                                 *
* @Brief   :                                                                 *
* @Version : 1.0.0.0                                                         *
*****************************************************************************/

#ifndef CUI_ID_SET_H
#define CUI_ID_SET_H
#include <queue>
namespace cui {
    constexpr int MAXIDNUM = 10;
    class ID_set
    {
    public:
        ID_set()
        {
            for (int i = 0; i < MAXIDNUM; ++i) { idset.emplace(i); }
        }
        int get_available()
        {
            if (idset.empty()) { throw; return -1; }
            return idset.front();
        }
        int get_availableAndPop()
        {
            int ava = get_available();
            idset.pop();
            return ava;
        }
        void pop() { idset.pop(); }
        void push(int id) { idset.push(id); }

    private:
        std::queue<int> idset;
    };
}

#endif // !CUI_ID_SET_H
