/*****************************************************************************
* @Author  : JamesNULLiu                                                     *
* @Date    : 2022/Sep/18                                                     *
* @File    : ID_Set.h                                                        *
* @Brief   : Class {ID_set} uses a queue to store digital IDs (0 : {MAXIDNU- *
*            | M}).                                                          *
*            Method {get_avaliableAndPop()} is the most recommanded choice   *
*            | to get a ID (as return value).                                *
*            When deleting a Window, its ID should be push back to the queue *
*            | with method {push()}.                                         *
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
