/*
    �|�[�J�[�Q�[���̃v���O�����̉���
    �E�S���̖��̔���
    �E�����@�\�̊J���i�����̃J�[�h�i�C�ӂ̉񐔁j�j�i����̃J�[�h�i�P��j�j
    �E�ΐ�ɂ���
    (�����������ꍇ�A��ԋ����J�[�h�ŏ��s�����߂�B)
    (����ł����s�����܂�Ȃ������ꍇ�A���������ɂ���B)
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// �\�[�g����֐�
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

// �ԍ�������ł邩�̔���
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

// �J�[�h��������
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
                printf("|  �@ʰ� %d   |  ",C[i]%13+1);
            }
            else
            {
                printf("|   ʰ� %d   |  ",C[i]%13+1);
            }
            //10
        }
        else if(C[i]/13==1)
        {
            if(C[i]%13<9)
            {
                printf("| �@�޲�  %d  |  ",C[i]%13+1);
            }
            else
            {
                printf("|�@�޲�  %d�@|  ",C[i]%13+1);
            }
        }
        else if(C[i]/13==2)
        {
            if(C[i]%13<9)
            {
                printf("|  �۰�ް %d  |  ",C[i]%13+1);
            }
            else
            {
                printf("|  �۰�ް%d  |  ",C[i]%13+1);
            }
        }
        else
        {
            if(C[i]%13<9)
            {
                printf("|  ��߰�� %d  |  ",C[i]%13+1);
            }
            else
            {
                printf("|  ��߰��%d  |  ",C[i]%13+1);
            }
        }
    }
    printf("\n");
    printf("|            |  |            |  |            |  |            |  |            |\n");
    printf("|            |  |            |  |            |  |            |  |            |\n");
    printf(" ------------    ------------    ------------    ------------    ------------\n");
}

// �X�[�g�̔���
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

// �ԍ��̔���
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

//�ŏI���ʗp�̐����̕��ёւ�
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

// ���̕\��
void display_res(int H)
{
    switch (H)
    {
        case 0: puts("�m�[�y�A"); break;
        case 3: puts("�����E�y�A"); break;
        case 6: puts("�c�E�E�y�A"); break;
        case 9: puts("�X���[�J�[�h"); break;
        case 10: puts("�X�g���[�g"); break;
        case 11: puts("�t���b�V��"); break;
        case 12: puts("�t���n�E�X"); break;
        case 18: puts("�t�H�A�E�J�[�h"); break;
        case 19: puts("�X�g���[�g�E�t���b�V��"); break;
        case 20: puts("���C�����X�g���[�g�t���b�V��"); break;
    }
}

int main(void)
{
    int my_cards[5]; //�����̂T��
    int cards[52]; //�d������̂��߂̔z��
    int my_number[5];
    int res=0,index=0;
    int my_result;
    int my_savecards[5];
    int my_final_number[5];

    int enemy_cards[5];//����̂T��
    int enemy_number[5];
    int enemy_savecards[5];
    int enemy_result;
    int enemy_final_number[5];

    int count_of_change_card=0;

    int final_result;

    //�z��̏����ݒ�
    for (int i=0;i<52;i++)
    {
        cards[i]=0;
    }

    srand((unsigned) time(NULL));

    //�J�[�h��z��
    //����
    while (index!=5)
    {
        //�d���̂Ȃ��悤�ɔz�肽��
        res = rand() % 52;

        if (cards[res]==0)
        {
            cards[res]=1;
            my_cards[index]=res;
            index++;
        }
    }
    index=0;
    //����
    while (index!=5)
    {
        //�d���̂Ȃ��悤�ɔz�肽��
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

    //�������̉����ڂ��̎w��p
    for(int i=0;i<5;i++)
    {
        my_savecards[i]=my_cards[i];
        enemy_savecards[i]=enemy_cards[i];
    }

    // printf("���Ȃ��̃J�[�h\n");
    // show_cards(my_cards); 
    
    //���̔���i�P�j
    sort(my_cards);
    sort(enemy_cards);

    //��������̂��߂�my_number[]
    for(int i=0;i<5;i++)
    {
        my_number[i]=my_cards[i]%13+1;
        enemy_number[i]=enemy_cards[i]%13+1;
    }

    sort(my_number);
    sort(enemy_number);

    //����
    if(whether_num_R_lined_up(my_number)==4)
    {
        my_result=10;
    }
    //����
    if(whether_num_R_lined_up(enemy_number)==4)
    {
        enemy_result=10;
    }

    //����
    if(judgment_of_suit(my_cards)==4)//�X�[�g���S������
    {
        if(whether_num_R_lined_up(my_cards)==4)//�������S������ł�
        {
            my_result=19;
        }
        else if(my_number[0]==1&&my_number[1]==10&&my_number[2]==11&&my_number[3]==12&&my_number[4]==13)
        {
            my_result=20;
        }
        else//����������łȂ�
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

    //����
    if(judgment_of_suit(enemy_cards)==4)//�X�[�g���S������
    {
        if(whether_num_R_lined_up(enemy_cards)==4)//�������S������ł�
        {
            enemy_result=19;
        }
        else if(enemy_number[0]==1&&enemy_number[1]==10&&enemy_number[2]==11&&enemy_number[3]==12&&enemy_number[4]==13)
        {
            enemy_result=20;
        }
        else//����������łȂ�
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

    //���̕\��
    //����
    printf("\n���Ȃ��̖��F");
    display_res(my_result);
    
    int end_of_game=0;

    //�����̃J�[�h����
    while(end_of_game!=1)
    {
        int change_the_cards;
        int how_many_cards;

        puts("\n�J�[�h���������܂����H");
        puts("��������d�P�@�A�@�������Ȃ��d�Q");
        printf("���́F");
        scanf("%d",&change_the_cards);
        
        printf("\n");
        int which_card;
        
        if(change_the_cards==1)//��������
        {
            count_of_change_card+=1;
            if (count_of_change_card==3)
            {
                end_of_game=1;
            }
            res=0;index=0;
            puts("�����̃J�[�h���������܂����H");
            scanf("%d",&how_many_cards);
            printf("\n");

            if(how_many_cards>6||how_many_cards<1)
            {
                printf("�P~�T�̐����œ��͂��Ă�������\n");
            }
            else if(how_many_cards==5)//5������
            {
                //�J�[�h��z��
                while (index!=5)
                {
                    //�d���̂Ȃ��悤�ɔz�肽��
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
                for(int i=0;i<5;i++)//�������̉����ڂ��̎w��p
                {
                    my_savecards[i]=my_cards[i];
                }
                printf("���Ȃ��̃J�[�h\n");
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
                    else//����������łȂ�
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

                printf("\n���Ȃ��̖��F");
                display_res(my_result);
            }
            else//1~4������
            {
                int count_change = 0;
                int change[5]={0,0,0,0,0};
                while(count_change!=how_many_cards)
                {
                    puts("�����ڂ̃J�[�h���������܂���");
                    printf("\n���́F");
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
                            printf("�����J�[�h�͌����ł��܂���\n");
                        }
                    }
                    else
                    {
                        printf("1~5�̐�������͂��Ă�������\n");
                    }
                    
                }
                printf("���Ȃ��̃J�[�h\n");
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
                    else//����������łȂ�
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

                printf("\n���Ȃ��̖��F");
                display_res(my_result);
            }
        }
        else if(change_the_cards==2)//�������Ȃ�or3���������
        {
            end_of_game++;
            printf("���Ȃ��̃J�[�h\n");
            show_cards(my_savecards); //�J�[�h��������
            sort(my_cards); //���ѕς���

            for(int i=0;i<5;i++)
            {
                my_number[i]=my_cards[i]%13+1;
            }

            sort(my_number);

            if(whether_num_R_lined_up(my_number)==4)
            {
                my_result=10;
            }

            if(judgment_of_suit(my_cards)==4)//�X�[�g���S������
            {
                if(whether_num_R_lined_up(my_cards)==4)//�������S������ł���
                {
                    my_result=19;
                }
                else if(my_number[0]==1&&my_number[1]==10&&my_number[2]==11&&my_number[3]==12&&my_number[4]==13)
                {
                    my_result=20;
                }
                else//����������łȂ�
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
            printf("\n���Ȃ��̖��F");
            display_res(my_result);
        }
        else
        {
            printf("�P�܂��͂Q����͂��Ă�������");
        }
        
    }

    //����̃J�[�h����
    if(enemy_result==0)//�m�[�y�A���������������
    {
        index=0;
        if(enemy_number[0]==1)
        {
            for(int i=0;i<4;i++)
            {
                while (index!=4)//4������
                {
                    //�d���̂Ȃ��悤�ɔz�肽��
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
                while (index!=4)//4������
                {
                    //�d���̂Ȃ��悤�ɔz�肽��
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

    //����
    if(judgment_of_suit(enemy_cards)==4)//�X�[�g���S������
    {
        if(whether_num_R_lined_up(enemy_cards)==4)//�������S������ł�
        {
            enemy_result=19;
        }
        else if(enemy_number[0]==1&&enemy_number[1]==10&&enemy_number[2]==11&&enemy_number[3]==12&&enemy_number[4]==13)
        {
            enemy_result=20;
        }
        else//����������łȂ�
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

    printf("\n����̃J�[�h\n");
    show_cards(enemy_savecards);
    sort_of_number(my_number,my_final_number);
    sort_of_number(enemy_number,enemy_final_number);
    
    printf("\n����̖��F");
    display_res(enemy_result);

    int count=0;
    // ���s�̔���I

    printf("\n���ʁF");
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
        printf("��������");
        //�����������̏��s�̔���
        if(my_result==0)//�m�[�y�A
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
        case 0: puts("���Ȃ��̕���"); break;
        case 1: puts("���Ȃ��̏���"); break;
        case 2: puts("��������"); break;
    }

    return 0; 
}