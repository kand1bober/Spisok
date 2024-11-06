#include "../Headers/functions.h"
#include "../Headers/output.h"
#include "../Headers/decoration.h"


int main()
{
    struct File_graph graph = {};
    StartOutput( &graph );

    struct List spisok = {};
    ListCtor( &spisok );
    ListDump( &spisok );

    ListElem to_insert = 1.11;
    ListInsert( &spisok, 9, &to_insert );
    ListInsert( &spisok, 8, &to_insert );
    ListInsert( &spisok, 7, &to_insert );
    ListInsert( &spisok, 6, &to_insert );
    ListDump( &spisok );
    
    //====== CHECK ===============
    // ListElem a = 0;
    // int b = 0;
    // while(1)
    // {
    //     printf(YELLOW "Type element and position you want to insert\n" DELETE_COLOR);
    //     if ( scanf("%lf %d", &a, &b) == 2 )
    //     {
    //         ListInsert( &spisok, b, &a );
    //         printf(GREEN "ELEMENT: %lf\n\n" DELETE_COLOR, a);
    //     }
    //     else 
    //     {
    //         break;
    //     }
    // }
    
    //==============================
    // ListElem a = 0, b = 0;
    // ListTakeHead( &spisok, 3, &a);
    // ListTakeTale( &spisok, 3, &b);
    // printf("\n\n3rd from 1st take: %lf  \n3rd from second take: %lf\n\n", a, b);
    //=====================================================================

    WriteAllBonds( &spisok, &graph);
    FinishOutput( &graph );

    ListDtor( &spisok );
    
    return 0;
}
