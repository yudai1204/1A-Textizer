//使い方
//1.下の学番というところに自分の学番を入れる
//2.各ソースコードを1番から連番にしておく
//3.このプログラムを実行しファイル名のテンプレートを入力
//(例: kadai1-1.c , kadai1-2.c , kadai1-3.c …というように連番の場合、「ファイル名を入力」のところでkadai1-と入力する)
//(例2: prog1.c , prog2.c , prog3.c …というように連番の場合、「ファイル名を入力」のところでprogと入力する)
//4.kadai[授業回数]-[学番].txtというファイルが完成する
//注意:発展課題が連番になってない場合は、できたファイルに自分で追記してください
//注意2:設定項目を追加しました
//review、kadaiの選択と、ソースファイルのみの結合が選べます(無限ループのコードや、標準入力があるプログラムを含むの時用)
#include <stdio.h>
#include <stdlib.h>
int num = 0;
int id = 21127; //学番
int existFile(const char* path){
    FILE* fp = fopen(path, "r");
    if (fp == NULL) {
        return 0;
    }

    fclose(fp);
    return 1;
}

int writeFile(const char* path , int n ,int mode){
    FILE* fp = fopen(path, "a");
    if (fp == NULL) {
        printf("ERROR\n");
        return 0;
    }
    if(mode == 0)
        fprintf(fp,u8"\n\n\n<課題%d-%d>\n●ソース\n",num,n);
    else
        fprintf(fp,u8"\n\n●結果\n",num,n);
    fclose(fp);
    return 1;
}

int main(void){
    char filename[64],filenamed[64],textname[32],com[128];
    int i;
    char mode[32] = {""};
    char source_only='0';
    printf("モードを入力してください(kadai or review): ");
    while(mode[0] == '\0'){
        scanf("%s",mode);
    }
    while( source_only != 'y' && source_only != 'n' ){
        printf("各ファイルの結果を出力しますか？nを選択するとソースのみ結合されます: ( y / n )");
        scanf("%c",&source_only);
    }
    printf("授業回数を入力: ");
    scanf("%d",&num);
    printf("ファイル名を入力: ");
    scanf("%s",&filename);
    sprintf(filenamed,"%s1.c",filename);
    if (!existFile(filenamed)){
        printf("ファイルが存在しません\n");
        return 0;
    }
    printf("ファイルを結合します…\n");
    sprintf(textname,"%s%d-%d.txt",mode,num,id);
    //出力先ファイルを用意
    FILE *outputfile;         // 出力ストリーム
    outputfile = fopen(textname,"w,ccs=UTF-8");  // ファイルを書き込み用にオープン(開く)
    if (outputfile == NULL) {          // オープンに失敗した場合
        printf("cannot open\n");         // エラーメッセージを出して
        exit(1);                         // 異常終了
    }
    fprintf(outputfile, u8"AL%d\n",id); // ファイルに書く
    fclose(outputfile);          // ファイルをクローズ(閉じる)

    for(i=1;;i++){
        sprintf(&filenamed[0],"%s%d.c",filename,i);
        if (!existFile(filenamed))
            break;
        printf("結合中… : %s\n",filenamed);
        if(!writeFile(textname,i,0)) return 0;
        sprintf(com, "copy /b %s + %s %s",textname,filenamed,textname);
        system(com);
        if(!writeFile(textname,i,1)) return 0;
        if(source_only == 'y'){
            printf("コンパイル中…: %s\n",filenamed);
            sprintf(com, "gcc %s\n",filenamed);
            system(com);
            printf("結果出力中…: %s\n",filenamed);
            system("a.exe > result.txt\n");
            printf("結合中… : %s\n",filenamed);
            sprintf(com,"copy /b %s + result.txt\n",textname);
            system(com);
        }
    }

    printf("===ファイルを結合しました===\n");
    return 0;
}