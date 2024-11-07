#include "../Headers/functions.h"
#include "../Headers/output.h"
#include "../Headers/decoration.h"


int main()
{
    struct File_graph graph = {};
    StartOutput( &graph );

    struct Data chain = {};
    ListCtor( &chain );
    ListDump( &chain.spisok, &chain.free );

    PAUSE
    ListElem to_insert_1 = 1.11;
    ListElem to_insert_2 = 1.22;
    ListElem to_insert_3 = 1.33;
    ListElem to_insert_4 = 1.44;
    ListElem to_insert_5 = 1.55;
    ListInsert( &chain.spisok, &chain.free, 1, &to_insert_1 );
    PAUSE
    ListInsert( &chain.spisok, &chain.free, 2, &to_insert_2 );
    PAUSE
    ListInsert( &chain.spisok, &chain.free, 3, &to_insert_3 );
    PAUSE
    ListInsert( &chain.spisok, &chain.free, 4, &to_insert_4 );
    PAUSE

    ListDelete( &chain.spisok, &chain.free, 3 );
    PAUSE
    ListInsert( &chain.spisok, &chain.free, 1, &to_insert_5 );
    

    // // ====== CHECK ===============
    // ListElem a = 0;
    // int b = 0;
    // while(1)
    // {
    //     printf(YELLOW "Type element and position you want to insert\n" DELETE_COLOR);
    //     if ( scanf("%lf %d", &a, &b) == 2 )
    //     {
    //         ListInsert( &chain.spisok, &chain.free, b, &a );
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

    ListDump( &chain.spisok, &chain.free );

    WriteAllBonds( &chain.spisok, &graph);
    FinishOutput( &graph );

    ListDtor( &chain );
    
    return 0;
}
