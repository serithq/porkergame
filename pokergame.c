/*
    ポーカーゲームのプログラムの改良
    ・全部の役の判定
    ・交換機能の開発（自分のカード（任意の回数））（相手のカード（１回））
    ・対戦にする
    (同役だった場合、一番強いカードで勝敗を決める。)
    (それでも勝敗が決まらなかった場合、引き分けにする。)
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// ソートする関数
void sort(int* A)
{
    for(int i=0;i<5;i++)
    {
        for(int j=i+1;j<5;j++)
        {
            if(A[i]>A[j])
            {
                int tmp=A[i];
                A[i]=A[j];
                A[j]=tmp;
            }
        }
    }
}

// 番号が並んでるかの判定
int whether_num_R_lined_up(int* B)
{
    int d=0;
    for(int i=0;i<4;i++)
    {
        int c=B[i]-B[i+1];
        if(c==-1)
        {
            d++;
        }
    }
    return d;
}

// カードを見せる
void show_cards(int* C)
{
    printf(" ------------    ------------    ------------    ------------    ------------\n");
    printf("|            |  |            |  |            |  |            |  |            |\n");
    printf("|            |  |            |  |            |  |            |  |            |\n");
    for (int i=0;i<5;i++)
    {
        if(C[i]/13==0)
        {
            if(C[i]%13<9)
            {
                printf("|  　ﾊｰﾄ %d   |  ",C[i]%13+1);
            }
            else
            {
                printf("|   ﾊｰﾄ %d   |  ",C[i]%13+1);
            }
            //10
        }
        else if(C[i]/13==1)
        {
            if(C[i]%13<9)
            {
                printf("| 　ﾀﾞｲﾔ  %d  |  ",C[i]%13+1);
            }
            else
            {
                printf("|　ﾀﾞｲﾔ  %d　|  ",C[i]%13+1);
            }
        }
        else if(C[i]/13==2)
        {
            if(C[i]%13<9)
            {
                printf("|  ｸﾛｰﾊﾞｰ %d  |  ",C[i]%13+1);
            }
            else
            {
                printf("|  ｸﾛｰﾊﾞｰ%d  |  ",C[i]%13+1);
            }
        }
        else
        {
            if(C[i]%13<9)
            {
                printf("|  ｽﾍﾟｰﾄﾞ %d  |  ",C[i]%13+1);
            }
            else
            {
                printf("|  ｽﾍﾟｰﾄﾞ%d  |  ",C[i]%13+1);
            }
        }
    }
    printf("\n");
    printf("|            |  |            |  |            |  |            |  |            |\n");
    printf("|            |  |            |  |            |  |            |  |            |\n");
    printf(" ------------    ------------    ------------    ------------    ------------\n");
}

// スートの判定
int judgment_of_suit(int* D)
{
    int flag_of_suit=0;
    for(int i=1;i<5;i++)
    {
        if((D[i-1]/13)==(D[i]/13))
        {
            flag_of_suit++;
        }
    }

    return flag_of_suit;
}

// 番号の判定
int judgment_of_number(int* E)
{
    int flag_of_number=0;

        for(int i=0;i<5;i++)
        {
            for(int j=i+1;j<5;j++)
            {
                int b=E[i]%13-E[j]%13;
                if(b==0)
                {
                    flag_of_number++;
                }
            }
        }
        return flag_of_number;
}

//最終結果用の数字の並び替え
void sort_of_number(int* F,int* G)
{
    if(F[0]==1)
    {
        for(int i=0;i<5;i++)
        {
            G[(i+4)%5]=F[i];
        }
    }
}

// 役の表示
void display_res(int H)
{
    switch (H)
    {
        case 0: puts("ノーペア"); break;
        case 3: puts("ワン・ペア"); break;
        case 6: puts("ツウ・ペア"); break;
        case 9: puts("スリーカード"); break;
        case 10: puts("ストレート"); break;
        case 11: puts("フラッシュ"); break;
        case 12: puts("フルハウス"); break;
        case 18: puts("フォア・カード"); break;
        case 19: puts("ストレート・フラッシュ"); break;
        case 20: puts("ロイヤルストレートフラッシュ"); break;
    }
}

int main(void)
{
    int my_cards[5]; //自分の５枚
    int cards[52]; //重複判定のための配列
    int my_number[5];
    int res=0,index=0;
    int my_result;
    int my_savecards[5];
    int my_final_number[5];

    int enemy_cards[5];//相手の５枚
    int enemy_number[5];
    int enemy_savecards[5];
    int enemy_result;
    int enemy_final_number[5];

    int count_of_change_card=0;

    int final_result;

    //配列の初期設定
    for (int i=0;i<52;i++)
    {
        cards[i]=0;
    }

    srand((unsigned) time(NULL));

    //カードを配る
    //自分
    while (index!=5)
    {
        //重複のないように配りたい
        res = rand() % 52;

        if (cards[res]==0)
        {
            cards[res]=1;
            my_cards[index]=res;
            index++;
        }
    }
    index=0;
    //相手
    while (index!=5)
    {
        //重複のないように配りたい
        res = rand() % 52;

        if (cards[res]==0)
        {
            cards[res]=1;
            enemy_cards[index]=res;
            index++;
        }
    }
    printf("my card\n");
    show_cards(my_cards);
    printf("enemy's card\n");
    show_cards(enemy_cards);

    //交換時の何枚目かの指定用
    for(int i=0;i<5;i++)
    {
        my_savecards[i]=my_cards[i];
        enemy_savecards[i]=enemy_cards[i];
    }

    // printf("あなたのカード\n");
    // show_cards(my_cards); 
    
    //役の判定（１）
    sort(my_cards);
    sort(enemy_cards);

    //数字判定のためのmy_number[]
    for(int i=0;i<5;i++)
    {
        my_number[i]=my_cards[i]%13+1;
        enemy_number[i]=enemy_cards[i]%13+1;
    }

    sort(my_number);
    sort(enemy_number);

    //自分
    if(whether_num_R_lined_up(my_number)==4)
    {
        my_result=10;
    }
    //相手
    if(whether_num_R_lined_up(enemy_number)==4)
    {
        enemy_result=10;
    }

    //自分
    if(judgment_of_suit(my_cards)==4)//スートが全部同じ
    {
        if(whether_num_R_lined_up(my_cards)==4)//数字が全部並んでる
        {
            my_result=19;
        }
        else if(my_number[0]==1&&my_number[1]==10&&my_number[2]==11&&my_number[3]==12&&my_number[4]==13)
        {
            my_result=20;
        }
        else//数字が並んでない
        {
            my_result=11;
        }
    }
    else if(my_result==10)
    {
    }
    else
    {
        my_result=judgment_of_number(my_cards)*3;
    }

    //相手
    if(judgment_of_suit(enemy_cards)==4)//スートが全部同じ
    {
        if(whether_num_R_lined_up(enemy_cards)==4)//数字が全部並んでる
        {
            enemy_result=19;
        }
        else if(enemy_number[0]==1&&enemy_number[1]==10&&enemy_number[2]==11&&enemy_number[3]==12&&enemy_number[4]==13)
        {
            enemy_result=20;
        }
        else//数字が並んでない
        {
            enemy_result=11;
        }
    }
    else if(enemy_result==10)
    {
    }
    else
    {
        enemy_result=judgment_of_number(enemy_cards)*3;
    }

    //役の表示
    //自分
    printf("\nあなたの役：");
    display_res(my_result);
    
    int end_of_game=0;

    //自分のカード交換
    while(end_of_game!=1)
    {
        int change_the_cards;
        int how_many_cards;

        puts("\nカードを交換しますか？");
        puts("交換する‥１　、　交換しない‥２");
        printf("入力：");
        scanf("%d",&change_the_cards);
        
        printf("\n");
        int which_card;
        
        if(change_the_cards==1)//交換する
        {
            count_of_change_card+=1;
            if (count_of_change_card==3)
            {
                end_of_game=1;
            }
            res=0;index=0;
            puts("何枚のカードを交換しますか？");
            scanf("%d",&how_many_cards);
            printf("\n");

            if(how_many_cards>6||how_many_cards<1)
            {
                printf("１~５の数字で入力してください\n");
            }
            else if(how_many_cards==5)//5枚交換
            {
                //カードを配る
                while (index!=5)
                {
                    //重複のないように配りたい
                    res = rand() % 52;

                    if (cards[res]==0)
                    {
                        cards[res]=1;
                        my_cards[index]=res;
                        index++;
                    }
                }
                for(int i=0;i<5;i++)
                {
                    my_savecards[i]=my_cards[i];
                }
                for(int i=0;i<5;i++)//交換時の何枚目かの指定用
                {
                    my_savecards[i]=my_cards[i];
                }
                printf("あなたのカード\n");
                show_cards(my_cards);
                sort(my_cards); 

                for(int i=0;i<5;i++)
                {
                    my_number[i]=my_cards[i]%13+1;
                }

                sort(my_number);

                if(whether_num_R_lined_up(my_number)==4)
                {
                    my_result=10;
                }

                if(judgment_of_suit(my_cards)==4)
                {
                    if(whether_num_R_lined_up(my_cards)==4)
                    {
                        my_result=19;
                    }
                    else if(my_number[0]==1&&my_number[1]==10&&my_number[2]==11&&my_number[3]==12&&my_number[4]==13)
                    {
                        my_result=20;
                    }
                    else//数字が並んでない
                    {
                        my_result=11;
                    }
                }
                else if(my_result==10)
                {
                }
                else
                {
                    my_result=judgment_of_number(my_cards)*3;
                }

                printf("\nあなたの役：");
                display_res(my_result);
            }
            else//1~4枚交換
            {
                int count_change = 0;
                int change[5]={0,0,0,0,0};
                while(count_change!=how_many_cards)
                {
                    puts("何枚目のカードを交換しますか");
                    printf("\n入力：");
                    scanf("%d",&which_card);
                    if(which_card>0&&which_card<6)
                    {   
                        if (change[which_card-1]==0)
                        {
                            change[which_card-1]=1;
                            int flag=0;
                            while(flag!=1)
                            {
                                res=rand()%52;
                                if(cards[res]==0)
                                {
                                    cards[res]=1;
                                    my_savecards[which_card-1]=res;
                                    for(int i=0;i<5;i++)
                                    {
                                        my_cards[i]=my_savecards[i];
                                    }
                                    flag+=1;
                                }
                            }
                            count_change+=1;
                        }
                        else
                        {
                            printf("同じカードは交換できません\n");
                        }
                    }
                    else
                    {
                        printf("1~5の数字を入力してください\n");
                    }
                    
                }
                printf("あなたのカード\n");
                show_cards(my_cards); 
                sort(my_cards); 

                for(int i=0;i<5;i++)
                {
                    my_number[i]=my_cards[i]%13+1;
                }

                sort(my_number);

                if(whether_num_R_lined_up(my_number)==4)
                {
                    my_result=10;
                }

                if(judgment_of_suit(my_cards)==4)
                {
                    if(whether_num_R_lined_up(my_cards)==4)
                    {
                        my_result=19;
                    }
                    else if(my_number[0]==1&&my_number[1]==10&&my_number[2]==11&&my_number[3]==12&&my_number[4]==13)
                    {
                        my_result=20;
                    }
                    else//数字が並んでない
                    {
                        my_result=11;
                    }
                }
                else if(my_result==10)
                {
                }
                else
                {
                    my_result=judgment_of_number(my_cards)*3;
                }

                printf("\nあなたの役：");
                display_res(my_result);
            }
        }
        else if(change_the_cards==2)//交換しないor3回交換した
        {
            end_of_game++;
            printf("あなたのカード\n");
            show_cards(my_savecards); //カードを見せる
            sort(my_cards); //並び変える

            for(int i=0;i<5;i++)
            {
                my_number[i]=my_cards[i]%13+1;
            }

            sort(my_number);

            if(whether_num_R_lined_up(my_number)==4)
            {
                my_result=10;
            }

            if(judgment_of_suit(my_cards)==4)//スートが全部同じ
            {
                if(whether_num_R_lined_up(my_cards)==4)//数字が全部並んでいる
                {
                    my_result=19;
                }
                else if(my_number[0]==1&&my_number[1]==10&&my_number[2]==11&&my_number[3]==12&&my_number[4]==13)
                {
                    my_result=20;
                }
                else//数字が並んでない
                {
                    my_result=11;
                }
            }
            else if(my_result==10)
            {
            }
            else
            {
                my_result=judgment_of_number(my_cards)*3;
            }
            printf("\nあなたの役：");
            display_res(my_result);
        }
        else
        {
            printf("１または２を入力してください");
        }
        
    }

    //相手のカード交換
    if(enemy_result==0)//ノーペアだったら交換する
    {
        index=0;
        if(enemy_number[0]==1)
        {
            for(int i=0;i<4;i++)
            {
                while (index!=4)//4枚交換
                {
                    //重複のないように配りたい
                    res = rand() % 52;

                    if (cards[res]==0)
                    {
                        cards[res]=1;
                        enemy_cards[index+1]=res;
                        index++;
                    }
                }
            }
        }
        else
        {
            for(int i=0;i<4;i++)
            {
                while (index!=4)//4枚交換
                {
                    //重複のないように配りたい
                    res = rand() % 52;

                    if (cards[res]==0)
                    {
                        cards[res]=1;
                        enemy_cards[index]=res;
                        index++;
                    }
                }
            }
        }
    }

    //相手
    if(judgment_of_suit(enemy_cards)==4)//スートが全部同じ
    {
        if(whether_num_R_lined_up(enemy_cards)==4)//数字が全部並んでる
        {
            enemy_result=19;
        }
        else if(enemy_number[0]==1&&enemy_number[1]==10&&enemy_number[2]==11&&enemy_number[3]==12&&enemy_number[4]==13)
        {
            enemy_result=20;
        }
        else//数字が並んでない
        {
            enemy_result=11;
        }
    }
    else if(enemy_result==10)
    {
    }
    else
    {
        enemy_result=judgment_of_number(enemy_cards)*3;
    }

    printf("\n相手のカード\n");
    show_cards(enemy_savecards);
    sort_of_number(my_number,my_final_number);
    sort_of_number(enemy_number,enemy_final_number);
    
    printf("\n相手の役：");
    display_res(enemy_result);

    int count=0;
    // 勝敗の判定！

    printf("\n結果：");
    if(my_result<enemy_result)
    {
        final_result=0;
    }
    else if(my_result>enemy_result)
    {
        final_result=1;
    }
    else
    {
        printf("引き分け");
        //役が同じ時の勝敗の判定
        if(my_result==0)//ノーペア
        {
            while(count==1)
            {
                for(int i=0;i<5;i++)
                {
                    if(my_number[4-i]!=enemy_number[4-i])
                    {
                        if(my_number[4-i]<enemy_number[4-i])
                        {
                            final_result=0;
                            count++;
                        }
                        else
                        {
                            final_result=1;
                            count++;
                        }
                    }
                    else
                    {
                        final_result=2;
                    }
                }
            }
        }
    }

    switch (final_result)
    {
        case 0: puts("あなたの負け"); break;
        case 1: puts("あなたの勝ち"); break;
        case 2: puts("引き分け"); break;
    }

    return 0; 
}