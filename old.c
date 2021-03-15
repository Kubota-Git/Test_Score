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
/*3)関数ルール*/
/*なるべくモジュール強度を弱くし、独立性を高める。*/
/*必要な値(アドレス)のみを渡す*/
/*処理が必要な場合は関数内でコピーを行い、処理後結果を返す*/
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
#define NAME_NUM 32		/*生徒名配列メモリ数*/
/*#define row 7			/*行*/
/*#define col 7			/*列*/


/*--------------------------------------------------------*/
/*③型定義*/
/*--------------------------------------------------------*/
/*--------------------------------------------------------*/
/*型　名	:SCORE_DATAFORM*/
/*概　要	:入力データの書式*/
/*メンバ1	:ランキングNo.*/
/*メンバ2	:出席番号*/
/*メンバ3	:氏名*/
/*メンバ4	:国語の点数*/
/*メンバ5	:算数の点数*/
/*メンバ6	:理科の点数*/
/*メンバ7	:社会の点数*/
/*メンバ8	:総合点数*/
/*--------------------------------------------------------*/
typedef struct
{
	unsigned char rank_num;
	unsigned long num;
	char name[NAME_NUM];
	unsigned char japanese;
	unsigned char arithmetic;
	unsigned char science;
	unsigned char social;
	unsigned short total_score;

}SCORE_DATAFORM;


/*--------------------------------------------------------*/
/*型　名	:CLC_DATAFORM*/
/*概　要	:処理後値の書式*/
/*メンバ1	:出席番号*/
/*メンバ2	:氏名*/
/*メンバ3	:各の点数*/
/*--------------------------------------------------------*/
typedef struct
{
	unsigned char rank_num;
	unsigned long num;
	char name[NAME_NUM];
	unsigned char uni_score;

}CLC_DATAFORM;


/*--------------------------------------------------------*/
/*型　名	:RANK_FORM*/
/*概　要	:ランキング順位の書式*/

/*メンバ1	:国語ランキング*/
/*メンバ2	:算数ランキング*/
/*メンバ3	:理科ランキング*/
/*メンバ4	:社会ランキング*/
/*メンバ5	:総合ランキング*/
/*特　記	:各値には出席番号が記載*/
/*--------------------------------------------------------*/
/*
typedef struct
{
	unsigned long rank_japanese;	//配列番号:0
	unsigned long rank_arithmetic;	//配列番号:1
	unsigned long rank_science;		//配列番号:2
	unsigned long rank_social;		//配列番号:3
	unsigned long rank_total_score;	//配列番号:4

}RANK_FORM;
*/

/*--------------------------------------------------------*/
/*型　名	:ANALYZE_FORM*/
/*概　要	:解析データの書式*/
/*メンバ1	:科目名*/
/*メンバ2	:最大値*/
/*メンバ3	:平均値*/
/*メンバ4	:最小値*/
/*--------------------------------------------------------*/
typedef struct
{
	char subject[10];
	unsigned short max;
	unsigned short ave;
	unsigned short min;

}ANALYZE_DATAFORTM;


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
char colum_name[8][10] = { 0 };


/*--------------------------------------------------------*/
/*④関数宣言*/
/*--------------------------------------------------------*/
int openFile(void);
void rankNum(RANK_FORM*);
void sortNum(unsigned long*, unsigned int*);
void closeFile(FILE*);
//unsigned short analyzeScore(unsigned short*);
unsigned char searchNum(RANK_FORM*, unsigned char, unsigned long);
void switchValue(SCORE_DATAFORM*);


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


	int stu_data[NAME_NUM] = { 0 };

	int read_judge = 1;

	int i = 0;


	unsigned char list_size = sizeof(stu_data) / sizeof(stu_data[0]);

	/*入力値読み取り*/

	do {

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
	sscanf("総合点", "%s", &colum_name[6]);
	sscanf("順位", "%s", &colum_name[7]);

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
	FILE* fp = NULL;

	fopen_s(&fp, "out.csv", "w");

	/*項目名のセット*/
	fprintf(fp, "%s,%s,%s,%s,%s,%s\n",
		&colum_name[7],				//ランキング順位
		&colum_name[0],				//出席番号
		&colum_name[1],			//名前
		&colum_name[2],			//国語
		&colum_name[3],			//算数
		&colum_name[4],			//理科
		&colum_name[4],			//社会点数
		&colum_name[6]);			//総合点数

	/*各値の格納*/
	for (i = 0; i < STUDENT_NUM; i++)
	{
		fprintf(fp, "%d,%d,%s,%d,%d,%d,%d,%d\n",
			&score[i].rank_num,		/*ランキング順位*/
			&score[i].num,			/*出席番号*/
			&score[i].name,			/*名前*/
			&score[i].japanese,		/*国語*/
			&score[i].arithmetic,	/*算数*/
			&score[i].science,		/*理科*/
			&score[i].social,		/*社会点数*/
			&score[i].total_score);	/*社会点数*/
	}

	fclose(fp);

	return;
}



/*--------------------------------------------------------*/
/*関数名：switchRow*/
/*概　要：前後行の入替のみ*/
/*引　数：配列ポインタ,インクリメント番号i*/
/*戻り値：なし*/
/*特　記：*/
/*--------------------------------------------------------*/
void switchRow(SCORE_DATAFORM* pdata, int i)
{
	SCORE_DATAFORM cpy_data[STUDENT_NUM] = { 0 };

	/*配列番号iの前後データを入れ替え*/
	cpy_data[i] = pdata[i + 1];
	cpy_data[i + 1] = pdata[i];
	pdata[i] = cpy_data[i];
	pdata[i + 1] = cpy_data[i + 1];

	return;
}


/*--------------------------------------------------------*/
/*関数名：rankNum*/
/*概　要：ランキング順に入れ替える*/
/*引　数：スコア表*/
/*戻り値：順位*/
/*特　記：	◎バブルソートを採用*/
/*			1)前後比較*/
/*			2)後が大きければ出席番号を前後入れ替える*/
/*			3)出席番号\nになると終了*/
/*			4)配列番号n+1より1～3を繰り返す*/
/*			5)n+i=配列番号になれば終了*/
/*--------------------------------------------------------*/

void rankNum(RANK_FORM* pranking)
{
	unsigned long rank_j[STUDENT_NUM] = { 0 };
	unsigned long rank_a[STUDENT_NUM] = { 0 };
	unsigned long rank_sc[STUDENT_NUM] = { 0 };
	unsigned long rank_so[STUDENT_NUM] = { 0 };
	unsigned long rank_t[STUDENT_NUM] = { 0 };
	unsigned int rank_score_j[STUDENT_NUM] = { 0 };
	unsigned int rank_score_a[STUDENT_NUM] = { 0 };
	unsigned int rank_score_sc[STUDENT_NUM] = { 0 };
	unsigned int rank_score_so[STUDENT_NUM] = { 0 };
	unsigned int rank_score_t[STUDENT_NUM] = { 0 };

	unsigned char i, j, k, m = 0;
	unsigned long anum = 0;
	unsigned long ascore = 0;

	/*変数を格納*/
	for (i = 0; i < STUDENT_NUM; i++)
	{
		rank_j[i] = rank_a[i] = rank_sc[i] = rank_so[i] = rank_t[i] = score[i].num;
		rank_score_j[i] = score[i].japanese;
		rank_score_a[i] = score[i].arithmetic;
		rank_score_sc[i] = score[i].science;
		rank_score_so[i] = score[i].social;
		rank_score_t[i] = score[i].total_score;
	}

	/*値のソート関数*/
	sortNum(&rank_j, &rank_score_j);
	sortNum(&rank_a, &rank_score_a);
	sortNum(&rank_sc, &rank_score_sc);
	sortNum(&rank_so, &rank_score_so);
	sortNum(&rank_t, &rank_score_t);

	/*値の格納*/
	for (m = 0; m < STUDENT_NUM; m++)
	{
		pranking[m].rank_japanese = rank_j[m];
		pranking[m].rank_arithmetic = rank_a[m];
		pranking[m].rank_science = rank_sc[m];
		pranking[m].rank_social = rank_so[m];
		pranking[m].rank_total_score = rank_t[m];

		/*デバックチェック
		printf("国語%d位:%d ", m + 1, pranking[m].rank_japanese);
		printf("算数%d位:%d ", m + 1, pranking[m].rank_arithmetic);
		printf("理科%d位:%d ", m + 1, pranking[m].rank_science);
		printf("社会%d位:%d ", m + 1, pranking[m].rank_social);
		printf("総合%d位:%d\n", m + 1, pranking[m].rank_total_score);
		*/
	}
	return;
}


/*--------------------------------------------------------*/
/*関数名：sortNum*/
/*概　要：ランキング順に入れ替える*/
/*引　数：出席番号と各点数値*/
/*戻り値：なし*/
/*特　記：	◎バブルソートを採用*/
/*			1)前後比較*/
/*			2)後が大きければ出席番号を前後入れ替える*/
/*			3)STUDENT_NUMになると終了*/
/*			4)1～3を繰り返す*/
/*			5)j=STUDENT_NUMになれば終了*/
/*--------------------------------------------------------*/
void sortNum(unsigned long* pnum, unsigned int* pscore)
{
	unsigned char i = 0;
	unsigned char j = 0;
	unsigned char k = 0;
	unsigned long anum = 0;
	unsigned long ascore = 0;

	/*デバックチェック
	for (i = 0; i < STUDENT_NUM; i++)
	{
		printf("pnum[%d]:%d\n", i, pnum[i]);
	}
	*/

	/*1)前後比較*/
	for (j = STUDENT_NUM; j > 0; j--)
	{
		for (k = 0; k < STUDENT_NUM - 1; k++)
		{
			/*2)後が大きければ出席番号を前後入れ替える*/
			if (pscore[k] < pscore[k + 1])
			{
				ascore = pscore[k];
				anum = pnum[k];
				pscore[k] = pscore[k + 1];
				pnum[k] = pnum[k + 1];
				pscore[k + 1] = ascore;
				pnum[k + 1] = anum;
			}
			/*2-2)値が同列の場合*/
			else if (pscore[k] == pscore[k + 1] && pnum[k] > pnum[k + 1])
			{
				anum = pnum[k];
				pnum[k] = pnum[k + 1];
				pnum[k + 1] = anum;
			}
			/*3)出席番号\nになると終了*/
		}
		/*4)配列番号n + 1より1～3を繰り返す*/
	}
	/*5)n+i=配列番号になれば終了*/


	return;
}
/*--------------------------------------------------------*/
/*関数名：searchNum*/
/*概　要：出席番号から配列番号を取得*/
/*引　数：変数ranking,調べたい項目番号,調べたい出席番号*/
/*戻り値：配列番号*/
/*--------------------------------------------------------*/
unsigned char searchNum(RANK_FORM* pranking, unsigned char itemno, unsigned long num)
{


	unsigned char i;
	for (i = 0; i < STUDENT_NUM; i++)
	{
		if (pranking[i].rank_japanese == num)
		{
			return i;
		}
	}
}



/*--------------------------------------------------------*/
/*関数名：analyzeScore*/
/*概　要：最大・最小値、平均値を算出*/
/*引　数：各格納要配列*/
/*戻り値：なし*/
/*--------------------------------------------------------*/
void analyzeScore(unsigned short* pscore, RANK_FORM* pranking)
{
	unsigned char i = 0;
	unsigned char max = 0;
	unsigned char min = 0;
	float ave = 0;
	unsigned long sum = 0;


	for (i = 0; i < STUDENT_NUM; i++)
	{
		if (score[pranking[i].rank_japanese].japanese > score[(pranking[i].rank_japanese) + 1].japanese)
		{
			max = score[i].japanese;
		}
		else if (score[i].japanese < score[i + 1].japanese)
		{
			min = score[i].japanese;
		}
		sum = score[i].japanese;
	}
	ave = sum / STUDENT_NUM;

	printf("max:%d\n", max);
	printf("min:%d\n", min);
	printf("ave:%fl\n", ave);

}


/*--------------------------------------------------------*/
/*メインコード*/
/*--------------------------------------------------------*/
/*--------------------------------------------------------*/
int main(void)
{
	SCORE_DATAFORM cpy_score[STUDENT_NUM] = { 0 };
	RANK_FORM ranking[STUDENT_NUM] = { 0 };
	ANALYZE_FORTM analyze_japanese = { 0 };
	ANALYZE_FORTM analyze_arithemetic = { 0 };
	ANALYZE_FORTM analyze_science = { 0 };
	ANALYZE_FORTM analyze_social = { 0 };
	ANALYZE_FORTM total_score = { 0 };

	//unsigned char rank[STUDENT_NUM] = { 0 };
	unsigned char prank[STUDENT_NUM] = { 0 };
	//unsigned short jp_rank;
	//unsigned short ari_rank;
	//unsigned short sc_rank;
	//unsigned short so_rank;
	int i = 0;


	FILE* fp = NULL;


	/*○概要説明*/
	printf("<<成績表ツール：成績分析プログラム>>\n\n");

	/*①処理:ファイル入力*/
	openFile();


	/*②-1処理：成績順位*/
	rankNum(&ranking);


	/*②-2処理：科目別上位者の表示*/
	//sortNum(&cpy_score);


	/*②-3処理：科目別の各項目を算出*/
	analyzeScore(&analyze_japanese, &ranking);

	/*③処理：ファイル出力*/
	closeFile();


	printf("処理の完了\n");

	switchRow(cpy_score);

	return 0;

}