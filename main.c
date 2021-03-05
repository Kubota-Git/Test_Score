#define _CRT_SECURE_NO_WARNINGS
/*--------------------------------------------------------*/
/*◎コード既規定一覧*/
/*--------------------------------------------------------*/
/*--------------------------------------------------------*/
/*1)命名規則*/
/*変数名:全て小文字表記とする(文字繋ぎは_ｱﾝﾀﾞｰﾊﾞｰ) aaa_bbb*/
/*定義名:全て大文字表記とする(文字繋ぎは_ｱﾝﾀﾞｰﾊﾞｰ) AAA_BBB*/
/*関数名:ローワーキャメルケース表記とする aaaBbb*/
/*--------------------------------------------------------*/
/*--------------------------------------------------------*/
/*2)コメント*/
/*名称、概要、引数 or　構成要素、戻り値を記述する*/
/*注意事項等がある際は特記にて、内容を記述*/
/*--------------------------------------------------------*/


/*--------------------------------------------------------*/
/*○includeファイル*/
/*--------------------------------------------------------*/
#include <stdio.h>


/*--------------------------------------------------------*/
/*①定数定義*/
/*--------------------------------------------------------*/
/*--------------------------------------------------------*/
/*定義名	:STUDENT_NUM*/
/*概　要	:生徒の総人数*/
/*--------------------------------------------------------*/
#define STUDENT_NUM 50	/*生徒人数*/
#define row 7			/*行*/
#define col 7			/*列*/






/*--------------------------------------------------------*/
/*③型定義*/
/*--------------------------------------------------------*/
/*--------------------------------------------------------*/
/*型　名	:SCORE_DATAFORM*/
/*概　要	:入力データの書式*/
/*メンバ1	:出席番号*/
/*メンバ2	:氏名*/
/*メンバ3	:国語の点数*/
/*メンバ4	:算数の点数*/
/*メンバ5	:理科の点数*/
/*メンバ6	:社会の点数*/
/*メンバ6	:総合点数*/
/*--------------------------------------------------------*/
typedef struct
{
	int num;
	char name[32];
	unsigned char japanese;
	unsigned char arithmetic;
	unsigned char science;
	unsigned char social;
	unsigned short total_score;

}SCORE_DATAFORM;


/*--------------------------------------------------------*/
/*②グローバル変数*/
/*--------------------------------------------------------*/
/*--------------------------------------------------------*/
/*変数名	:score_data*/
/*概要		:入力ファイルを格納*/
/*特記		:参照制約データとする*/
/*--------------------------------------------------------*/

SCORE_DATAFORM score[STUDENT_NUM] = { 0 };
char file_name[128] = { 0 };
char colum_name[7][10] = { 0 };




/*--------------------------------------------------------*/
/*④関数宣言*/
/*--------------------------------------------------------*/
int openFile(void);
int sortNum(SCORE_DATAFORM*);
//unsigned short analyzeScore(unsigned short*);
void closeFile(FILE *);



/*--------------------------------------------------------*/
/*⑤各関数*/
/*--------------------------------------------------------*/
/*--------------------------------------------------------*/
/*関数名：openFile*/
/*概　要：入力ファイルを開きデータを格納する*/
/*引　数：なし*/
/*戻り値：読取成功：1　読取失敗：0*/
/*特　記：*/
/*--------------------------------------------------------*/
int openFile(void)
{
	FILE* fp = NULL;


	int stu_data[32] = { 0 };

	int read_judge = 1;

	int i = 0;


	unsigned char list_size = sizeof(stu_data) / sizeof(stu_data[0]);

	/*入力値読み取り*/

	do{

		printf("Test_score.exeと同じディレクトリ内に.csvファイルを格納しください。\n");
		printf("格納した.csvファイル名を入力し、ENTERキーを押してください。\n-->");
		scanf_s("%s", file_name, sizeof(file_name));	/*ファイル名をキーボード入力*/

		/*デバッグコード
		printf("要素サイズ全：%d\n", sizeof(file_name));
		printf("要素サイズ個：%d\n", sizeof(file_name[0]));
		printf("取得文字：%s\n", file_name);
		*/

		read_judge = fopen_s(&fp, file_name, "r");				/*ファイルを開く*/
		if (read_judge == EOF)
		{
			printf("ERROR1:入力されたファイル名が正しくありません\n\n");
		}

	} while (read_judge == EOF);


	fscanf(fp, "%[^,],%[^,],%[^,],%[^,],%[^,],%[^\n]",
		&colum_name[0],			//出席番号
		&colum_name[1],			//名前
		&colum_name[2],			//国語
		&colum_name[3],			//算数
		&colum_name[4],			//理科
		&colum_name[5]);		//社会点数
	sscanf("総合点","%s",&colum_name[6]);

	/*デバッグ処理
	printf("%s ", &colum_name[0]);
	printf("%s ", &colum_name[1]);
	printf("%s ", &colum_name[2]);
	printf("%s ", &colum_name[3]);
	printf("%s ", &colum_name[4]);
	printf("%s ", &colum_name[5]);
	printf("%s\n", &colum_name[6]);
	*/


	for (i = 0; i < STUDENT_NUM; i++)
	{
		fscanf(fp, "%d ,%[^,],%d,%d,%d,%d",
			&score[i].num,			/*出席番号*/
			&score[i].name,			/*名前*/
			&score[i].japanese,		/*国語*/
			&score[i].arithmetic,	/*算数*/
			&score[i].science,		/*理科*/
			&score[i].social);		/*社会点数*/

		/*総合点*/
		score[i].total_score = score[i].japanese + score[i].arithmetic + score[i].science + score[i].social;

		/*デバッグ用
		printf("出席番号：%d ", score[i].num);
		printf("氏名：%s ", score[i].name);
		printf("国語：%d ", score[i].japanese);
		printf("算数：%d ", score[i].arithmetic);
		printf("理科：%d ", score[i].science);
		printf("社会：%d ", score[i].social);
		printf("総合点：%d\n", score[i].total_score);
		*/
	}

	fclose(fp); 

	return 1;
}

/*--------------------------------------------------------*/
/*関数名：closeFile*/
/*概　要：入力ファイルを開きデータを格納する*/
/*引　数：なし*/
/*戻り値：読取成功：1　読取失敗：0*/
/*特　記：*/
/*--------------------------------------------------------*/
void closeFile(void)
{
	int i = 0;
	FILE* fp=NULL;

	fopen_s(&fp, "out.csv", "w");

	fprintf(fp, "%s,%s,%s,%s,%s,%s\n",
		&colum_name[0],			//出席番号
		&colum_name[1],			//名前
		&colum_name[2],			//国語
		&colum_name[3],			//算数
		&colum_name[4],			//理科
		&colum_name[4],			//社会点数
		&colum_name[6]);		//総合点数

	for (i = 0; i < STUDENT_NUM; i++)
	{
		fprintf(fp, "%d,%s,%d,%d,%d,%d\n",
			&score[i].num,			/*出席番号*/
			&score[i].name,			/*名前*/
			&score[i].japanese,		/*国語*/
			&score[i].arithmetic,	/*算数*/
			&score[i].science,		/*理科*/
			&score[i].social);		/*社会点数*/
	}

	fclose(fp);

	return;
}



/*--------------------------------------------------------*/
/*関数名：sortNum*/
/*概　要：ランキング順に入れ替える*/
/*引　数：スコア表*/
/*戻り値：入れ替え成功：1　入れ替え失敗：0*/
/*特　記：*/
/*--------------------------------------------------------*/
int sortNum(SCORE_DATAFORM *sort_score)
{
	/**/



	return 0;
}


/*--------------------------------------------------------*/
/*メインコード*/
/*--------------------------------------------------------*/
/*--------------------------------------------------------*/
int main(void)
{
	SCORE_DATAFORM cpy_score[STUDENT_NUM] = { 0 };
	//unsigned short rank = 0;
	//unsigned short jp_rank;
	//unsigned short ari_rank;
	//unsigned short sc_rank;
	//unsigned short so_rank;


	FILE *fp =NULL;


	/*○概要説明*/
	printf("<<成績表ツール：成績分析プログラム>>\n\n");
	
	/*①処理:ファイル入力*/
	openFile();


	/*②-1処理：総合成績*/
	sortNum(&cpy_score);

	/*②-2処理：科目別上位者の表示*/
	//sortNum(&cpy_score);


	/*②-3処理：科目別の各項目を算出*/
	//analyzeScore(&cpy_score);

	/*③処理：ファイル出力*/
	closeFile();


	printf("処理の完了\n");

	return 0;



}