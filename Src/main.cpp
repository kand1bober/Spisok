#include "../Headers/library.h"
#include "../Headers/functions.h"
#include "../Headers/decoration.h"

int main()
{
    struct List list = {};

    ListCtor( &list );

    ListDump( &list );

    //====== CHECK ===============
    ListElem a = 0;
    int b = 0;
    while(scanf("%d", &b))
    {
        ListTake( &list, b, &a );
        printf(RED "ELEMENT: %lf\n" DELETE_COLOR, a);
    }
    //============================

    ListDtor( &list );

    return 0;
}
