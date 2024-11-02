#include "../Headers/functions.h"
#include "../Headers/decoration.h"

int main()
{
    

    struct List spisok = {};

    ListCtor( &spisok );

    ListDump( &spisok );

    double to_insert = 52;

    ListInsert( &spisok, 3, &to_insert);
    // ListDelete( &spisok, 6 );

    ListDump( &spisok );
    

    //====== CHECK ===============
    ListElem a = 0;
    int b = 0;
    while(scanf("%d", &b))
    {
        ListTake( &spisok, b, &a );
        printf(RED "ELEMENT: %lf\n" DELETE_COLOR, a);
    }
    //============================

    ListDtor( &spisok );

    // system( "dot -Tpng graph.dot -o huy.png" );

    return 0;
}
