#ifndef ORZ_BASE_RANDOM_H_INCLUDED
#define ORZ_BASE_RANDOM_H_INCLUDED

#include <stdlib.h>

namespace Orz
{
    class Random
    {
    public:
        Random(): up_limit(0), down_limit(RAND_MAX){}
        void SetLimit(int UpLimit, int DownLimit) {up_limit = UpLimit; down_limit = DownLimit;}
        void SetSeed(unsigned int Seed) { seed = Seed; srand(seed);}
        int GetNumber(){return rand();}
        int GetLimitNumber(){return down_limit + rand()%(up_limit + 1 - down_limit);}


    private:
        unsigned int seed;   // ����
        int up_limit;   // �������
        int down_limit; // �������
    };

}

#endif // ORZ_BASE_RANDOM_H_INCLUDED
