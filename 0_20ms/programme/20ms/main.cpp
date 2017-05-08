
#include <windows.h>
#include <iostream>
#include <stdio.h>

using namespace std;

static long LOOPS = 1000;

int main()
{
    freopen("output.txt","w",stdout);
    LARGE_INTEGER timeStart;    //开始时间
    LARGE_INTEGER timeEnd;      //结束时间

    LARGE_INTEGER frequency;    //计时器频率
    QueryPerformanceFrequency(&frequency);
    double quadpart = (double)frequency.QuadPart;//计时器频率

    double elapsed = 0;

    QueryPerformanceCounter(&timeStart);
    Sleep(LOOPS);//延时一秒
    QueryPerformanceCounter(&timeEnd);
    //得到两个时间的耗时
    elapsed = (timeEnd.QuadPart - timeStart.QuadPart) / quadpart;
    std::cout << "SLEEP : " << LOOPS << "\ntime : " << elapsed << " s\n" << std::endl;//单位为秒，精度为微秒(1000000/cpu主频)

    LOOPS = 1;
    for (int i = 0; i < 9; i++) {
        LOOPS = LOOPS * 10;
        QueryPerformanceCounter(&timeStart);
        for (int i = 0; i < LOOPS; i++);
        QueryPerformanceCounter(&timeEnd);
        //得到两个时间的耗时
        elapsed = (timeEnd.QuadPart - timeStart.QuadPart) / quadpart;
        std::cout << "LOOPS : " << LOOPS << "\ntime : " << elapsed << " s\n" << std::endl;//单位为秒，精度为微秒(1000000/cpu主频)
    }

    system("pause");
    return 0;
}
