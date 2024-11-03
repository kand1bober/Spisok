#include "../Headers/functions.h"
#include "../Headers/output.h"

int main()
{


    struct File_graph graph = {};
    StartOutput( &graph );

    struct List spisok = {};
    ListCtor( &spisok );

    // ListDump( &spisok );

    // double to_insert = 17;
    // ListInsert( &spisok, 3, &to_insert);
    // ListInsert( &spisok, 6, &to_insert);

    // ListDump( &spisok );

    ListDelete( &spisok, 6 );

    ListDump( &spisok );
    
    // ListInsert( &spisok, 6, &to_insert);

    // ListDump( &spisok );

    //====== CHECK ===============
    // ListElem a = 0;
    // int b = 0;
    // while(scanf("%d", &b))
    // {
    //     ListTake( &spisok, b, &a );
    //     printf(RED "ELEMENT: %lf\n" DELETE_COLOR, a);
    // }
    //============================

    WriteAllBonds( &spisok, &graph);
    FinishOutput( &graph );

    ListDtor( &spisok );
    
    return 0;
}
