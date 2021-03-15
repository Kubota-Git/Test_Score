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
#define STUDENT_NUM 50				/*生徒人数*/
#define NAME_NUM 32					/*生徒名配列メモリ数*/
#define ROW_NUM 8					/*行*/
#define COL_NUM 10					/*列*/
#define FILE_NAME_NUM 128			/*ファイル名数*/
#define OUTPUT_FILE_NAME "out.csv"	/*出力ファイル名*/

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
/*型　名	:COLUM_FORM*/
/*概　要	:列項目*/
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
	char rank_num[NAME_NUM];
	char num[NAME_NUM];
	char name[NAME_NUM];
	char japanese[NAME_NUM];
	char arithmetic[NAME_NUM];
	char science[NAME_NUM];
	char social[NAME_NUM];
	char total_score[NAME_NUM];

}COLUM_FORM;



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
	unsigned short max;	/*最大*/
	unsigned short min;	/*最少*/
	double ave;			/*平均*/
	char subject[10];	/*科目名*/

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


/*--------------------------------------------------------*/
/*④関数宣言*/
/*--------------------------------------------------------*/
/*ファイル操作関数一覧*/
int inputFile(COLUM_FORM*, SCORE_DATAFORM*);
int outputFile(COLUM_FORM*, SCORE_DATAFORM*);
void switchRow(SCORE_DATAFORM* pdata, int i);

/*ソート関数一覧*/
void sortTotal_score(SCORE_DATAFORM*);
void sortJapanease_score(SCORE_DATAFORM*);
void sortArithmetic_score(SCORE_DATAFORM*);
void sortScience_score(SCORE_DATAFORM*);
void sortSocial_score(SCORE_DATAFORM*);

/*解析関数一覧*/
void JapaneseData(ANALYZE_DATAFORTM*, SCORE_DATAFORM*);
void ArithmeticData(ANALYZE_DATAFORTM*, SCORE_DATAFORM*);
void ScienceData(ANALYZE_DATAFORTM*, SCORE_DATAFORM*);
void SocialData(ANALYZE_DATAFORTM*, SCORE_DATAFORM*);


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
int inputFile(COLUM_FORM *pcolum_name, SCORE_DATAFORM* pscore)
{
	int i=0;
	int stu_data[NAME_NUM] = { 0 };
	int read_judge = 1;

	char cpy_file_name[FILE_NAME_NUM] = { 0 };
	COLUM_FORM cpy_colum_name = { 0 };
	SCORE_DATAFORM cpy_score[STUDENT_NUM] = { 0 };

	FILE* fp = NULL;

	unsigned char list_size = sizeof(stu_data) / sizeof(stu_data[0]);

	/*入力値読み取り*/
	
	do{

		printf("Test_score.exeと同じディレクトリ内に.csvファイルを格納しください。\n");
		printf("格納した.csvファイル名を入力し、ENTERキーを押してください。\n-->");
		scanf_s("%s", cpy_file_name, sizeof(cpy_file_name));	/*ファイル名をキーボード入力*/

		read_judge = fopen_s(&fp, cpy_file_name, "r");				/*ファイルを開く*/
		if (read_judge == EOF)
		{
			printf("ERROR1:入力されたファイル名が正しくありません\n\n");
		}

	} while (read_judge == EOF);

	/*列名の取得*/
	fscanf(fp, "%[^,],%[^,],%[^,],%[^,],%[^,],%[^\n]",
		cpy_colum_name.num,			/*出席番号*/
		cpy_colum_name.name,		/*名前*/
		cpy_colum_name.japanese,	/*国語*/
		cpy_colum_name.arithmetic,	/*算数*/
		cpy_colum_name.science,		/*理科*/
		cpy_colum_name.social);		/*社会点数*/
		

	sscanf("合計","%s",cpy_colum_name.total_score);
	sscanf("順位", "%s", cpy_colum_name.rank_num);

	/*値の取得*/
	for (i = 0; i < STUDENT_NUM; i++)
	{
		fscanf(fp, "%d,%[^,],%d,%d,%d,%d",
			&cpy_score[i].num,			/*出席番号*/
			cpy_score[i].name,			/*名前*/
			&cpy_score[i].japanese,		/*国語*/
			&cpy_score[i].arithmetic,	/*算数*/
			&cpy_score[i].science,		/*理科*/
			&cpy_score[i].social);		/*社会点数*/

		/*総合点*/
		cpy_score[i].total_score = cpy_score[i].japanese + cpy_score[i].arithmetic + cpy_score[i].science + cpy_score[i].social;

		/*値の返却*/
		pscore[i] = cpy_score[i];

	}

	/*値の返却*/
	*pcolum_name = cpy_colum_name;


	fclose(fp); 

	return 1;
}

/*--------------------------------------------------------*/
/*関数名：closeFile*/
/*概　要：入力ファイルを開きデータを格納する*/
/*引　数：なし*/
/*戻り値：読取成功：1　読取失敗：0*/
/*特　記：各項目のソートも同時に行う*/
/*--------------------------------------------------------*/
int outputFile(COLUM_FORM* pcolum_name, SCORE_DATAFORM* pscore)
{
	int i = 0;
	COLUM_FORM cpy_colum_name = { 0 };
	SCORE_DATAFORM cpy_score[STUDENT_NUM] = { 0 };
	/*各科目データ*/
	ANALYZE_DATAFORTM japanese_data = { 0 };
	ANALYZE_DATAFORTM arithmetic_data = { 0 };
	ANALYZE_DATAFORTM science_data = { 0 };
	ANALYZE_DATAFORTM social_data = { 0 };

	/*値のコピー*/
	for (i = 0; i < STUDENT_NUM; i++)
	{
		cpy_score[i] = pscore[i];
	}

	cpy_colum_name = *pcolum_name;

	printf("%s\n", cpy_colum_name.rank_num);
	printf("%s\n", cpy_colum_name.num);
	printf("%s\n", cpy_colum_name.name);
	printf("%s\n", cpy_colum_name.japanese);
	printf("%s\n", cpy_colum_name.arithmetic);
	printf("%s\n", cpy_colum_name.science);
	printf("%s\n", cpy_colum_name.social);
	printf("%s\n", cpy_colum_name.total_score);


	FILE* fp = NULL;

	fopen_s(&fp, OUTPUT_FILE_NAME, "w");

	/*題目のセット*/
	fprintf(fp, "%s\n","■総合成績");/*項目1*/

	/*項目名のセット*/
	fprintf(fp, "%s,%s,%s,%s,%s,%s,%s,%s\n",
		cpy_colum_name.rank_num,		/*ランキング順位*/
		cpy_colum_name.num,				/*出席番号*/
		cpy_colum_name.name,			/*名前*/
		cpy_colum_name.japanese,		/*国語*/
		cpy_colum_name.arithmetic,		/*算数*/
		cpy_colum_name.science,			/*理科*/
		cpy_colum_name.social,			/*社会点数*/
		cpy_colum_name.total_score);	/*総合点数*/

	/*各値の格納*/
	for (i = 0; i < STUDENT_NUM; i++)
	{
		fprintf(fp, "%d,%d,%s,%d,%d,%d,%d,%d\n",
			cpy_score[i].rank_num,		/*ランキング順位*/
			cpy_score[i].num,			/*出席番号*/
			cpy_score[i].name,			/*名前*/
			cpy_score[i].japanese,		/*国語*/
			cpy_score[i].arithmetic,	/*算数*/
			cpy_score[i].science,		/*理科*/
			cpy_score[i].social,		/*社会点数*/
			cpy_score[i].total_score);	/*社会点数*/
	}

	/*題目のセット*/
	fprintf(fp, "\n%s\n", "■科目別成績(国語)");/*項目2*/

	/*項目名のセット*/
	fprintf(fp, "%s,%s,%s,%s\n",
		cpy_colum_name.rank_num,		/*ランキング順位*/
		cpy_colum_name.num,				/*出席番号*/
		cpy_colum_name.name,			/*名前*/
		"得点");						/*国語*/


	/*②-2処理：科目別上位者の表示*/
	sortJapanease_score(cpy_score);/*引数：スコア(アドレス情報)*/

	/*②-3処理：科目別の各項目を算出*/
	JapaneseData(&japanese_data, cpy_score);

	/*各値の格納*/
	for (i = 0; i < 4; i++)
	{
		fprintf(fp, "%d,%d,%s,%d\n",
			cpy_score[i].rank_num,		/*ランキング順位*/
			cpy_score[i].num,			/*出席番号*/
			cpy_score[i].name,			/*名前*/
			cpy_score[i].japanese);		/*国語*/
	}

	/*最大最少値のセット*/
	fprintf(fp, "%s,%d\n%s,%d\n%s,%.1f\n", /*小数点第1桁表示*/
		"最高", japanese_data.max,
		"最低", japanese_data.min,
		"平均", japanese_data.ave);


	/*題目のセット*/
	fprintf(fp, "\n%s\n", "■科目別成績(算数)");/*項目3*/

	/*項目名のセット*/
	fprintf(fp, "%s,%s,%s,%s\n",
		cpy_colum_name.rank_num,		/*ランキング順位*/
		cpy_colum_name.num,				/*出席番号*/
		cpy_colum_name.name,			/*名前*/
		"得点");						/*算数*/

		/*②-2処理：科目別上位者の表示*/
	sortArithmetic_score(cpy_score);/*引数：スコア(アドレス情報)*/

	/*②-3処理：科目別の各項目を算出*/
	ArithmeticData(&arithmetic_data, cpy_score);

	/*各値の格納*/
	for (i = 0; i < 4; i++)
	{
		fprintf(fp, "%d,%d,%s,%d\n",
			cpy_score[i].rank_num,		/*ランキング順位*/
			cpy_score[i].num,			/*出席番号*/
			cpy_score[i].name,			/*名前*/
			cpy_score[i].arithmetic);	/*算数*/
	}
	/*最大最少値のセット*/
	fprintf(fp, "%s,%d\n%s,%d\n%s,%.1f\n", /*小数点第1桁表示*/
		"最高", arithmetic_data.max,
		"最低", arithmetic_data.min,
		"平均", arithmetic_data.ave);


	/*題目のセット*/
	fprintf(fp, "\n%s\n", "■科目別成績(理科)");/*項目4*/

	/*項目名のセット*/
	fprintf(fp, "%s,%s,%s,%s\n",
		cpy_colum_name.rank_num,		/*ランキング順位*/
		cpy_colum_name.num,				/*出席番号*/
		cpy_colum_name.name,			/*名前*/
		"得点");						/*理科*/

			/*②-2処理：科目別上位者の表示*/
	sortScience_score(cpy_score);/*引数：スコア(アドレス情報)*/

	/*②-3処理：科目別の各項目を算出*/
	ScienceData(&science_data, cpy_score);

	/*各値の格納*/
	for (i = 0; i < 4; i++)
	{
		fprintf(fp, "%d,%d,%s,%d\n",
			cpy_score[i].rank_num,		/*ランキング順位*/
			cpy_score[i].num,			/*出席番号*/
			cpy_score[i].name,			/*名前*/
			cpy_score[i].science);		/*理科*/
	}
	/*最大最少値のセット*/
	fprintf(fp, "%s,%d\n%s,%d\n%s,%.1f\n", /*小数点第1桁表示*/
		"最高", science_data.max,
		"最低", science_data.min,
		"平均", science_data.ave);


	/*題目のセット*/
	fprintf(fp, "\n%s\n", "■科目別成績(社会)");/*項目5*/

	/*項目名のセット*/
	fprintf(fp, "%s,%s,%s,%s\n",
		cpy_colum_name.rank_num,		/*ランキング順位*/
		cpy_colum_name.num,				/*出席番号*/
		cpy_colum_name.name,			/*名前*/
		"得点");						/*社会*/

				/*②-2処理：科目別上位者の表示*/
	sortSocial_score(cpy_score);/*引数：スコア(アドレス情報)*/

	/*②-3処理：科目別の各項目を算出*/
	SocialData(&social_data, cpy_score);

	/*各値の格納*/
	for (i = 0; i < 4; i++)
	{
		fprintf(fp, "%d,%d,%s,%d\n",
			cpy_score[i].rank_num,		/*ランキング順位*/
			cpy_score[i].num,			/*出席番号*/
			cpy_score[i].name,			/*名前*/
			cpy_score[i].social);		/*社会*/
	}
	/*最大最少値のセット*/
	fprintf(fp, "%s,%d\n%s,%d\n%s,%.1f\n", /*小数点第1桁表示*/
		"最高", social_data.max,
		"最低", social_data.min,
		"平均", social_data.ave);

	fclose(fp);

	return 1;
}

/*--------------------------------------------------------*/
/*関数名：JapaneseData*/
/*概　要：Max/Min/Ave値の取得*/
/*引　数：配列ポインタ*/
/*戻り値：なし*/
/*特　記：国語ソート後に使用*/
/*--------------------------------------------------------*/
void JapaneseData(ANALYZE_DATAFORTM* pdata, SCORE_DATAFORM* pscore)
{
	int i = 0;
	int j = 0;
	int k = 0;

	double ave_score = 0;
	ANALYZE_DATAFORTM score_data = { 0 };

	/*Max/Minの取得*/
	pdata->max = pscore[0].japanese;
	pdata->min = pscore[STUDENT_NUM - 1].japanese;

	/*Aveの取得*/
	for (i = 0; i < STUDENT_NUM; i++)
	{
		ave_score += pscore[i].japanese;
	}
	pdata->ave = ave_score / STUDENT_NUM;

	return;
}

/*--------------------------------------------------------*/
/*関数名：ArithmeticData*/
/*概　要：Max/Min/Ave値の取得*/
/*引　数：配列ポインタ*/
/*戻り値：なし*/
/*特　記：算数ソート後に使用*/
/*--------------------------------------------------------*/
void ArithmeticData(ANALYZE_DATAFORTM* pdata, SCORE_DATAFORM* pscore)
{
	int i = 0;
	int j = 0;
	int k = 0;


	double ave_score = 0;
	ANALYZE_DATAFORTM score_data = { 0 };

	/*Max/Minの取得*/
	pdata->max = pscore[0].arithmetic;
	pdata->min = pscore[STUDENT_NUM - 1].arithmetic;

	/*Aveの取得*/
	for (i = 0; i < STUDENT_NUM; i++)
	{
		ave_score += pscore[i].arithmetic;
	}
	pdata->ave = ave_score / STUDENT_NUM;

	return;
}

/*--------------------------------------------------------*/
/*関数名：SciencData*/
/*概　要：Max/Min/Ave値の取得*/
/*引　数：配列ポインタ*/
/*戻り値：なし*/
/*特　記：理科ソート後に使用*/
/*--------------------------------------------------------*/
void ScienceData(ANALYZE_DATAFORTM* pdata, SCORE_DATAFORM* pscore)
{
	int i = 0;
	int j = 0;
	int k = 0;

	double ave_score = 0;
	ANALYZE_DATAFORTM score_data = { 0 };

	/*Max/Minの取得*/
	pdata->max = pscore[0].science;
	pdata->min = pscore[STUDENT_NUM - 1].science;

	/*Aveの取得*/
	for (i = 0; i < STUDENT_NUM; i++)
	{
		ave_score += pscore[i].science;
	}
	pdata->ave = ave_score / STUDENT_NUM;

	return;
}

/*--------------------------------------------------------*/
/*関数名：SocialData*/
/*概　要：Max/Min/Ave値の取得*/
/*引　数：配列ポインタ*/
/*戻り値：なし*/
/*特　記：社会ソート後に使用*/
/*--------------------------------------------------------*/
void SocialData(ANALYZE_DATAFORTM* pdata, SCORE_DATAFORM* pscore)
{
	int i = 0;
	int j = 0;
	int k = 0;


	double ave_score = 0;
	ANALYZE_DATAFORTM score_data = { 0 };

	/*Max/Minの取得*/
	pdata->max = pscore[0].social;
	pdata->min = pscore[STUDENT_NUM - 1].social;

	/*Aveの取得*/
	for (i = 0; i < STUDENT_NUM; i++)
	{
		ave_score += pscore[i].social;
	}
	pdata->ave = ave_score / STUDENT_NUM;

	return;
}

/*--------------------------------------------------------*/
/*関数名：switchRow*/
/*概　要：前後行の入替のみ*/
/*引　数：配列ポインタ,インクリメント番号i*/
/*戻り値：なし*/
/*特　記：*/
/*--------------------------------------------------------*/
void switchRow(SCORE_DATAFORM* pdata,int i)
{
	SCORE_DATAFORM cpy_data[1] = { 0 };

	if (i > STUDENT_NUM)
	{
		return;
	}
	else
	{
		/*配列番号iの前後データを入れ替え*/
		cpy_data[0] = pdata[i];
		pdata[i] = pdata[i + 1];
		pdata[i + 1] = cpy_data[0];
	}
	return;
}

/*--------------------------------------------------------*/
/*関数名：sortTotal_score*/
/*概　要：ソート*/
/*引　数：配列ポインタ*/
/*戻り値：なし*/
/*特　記：総合点のソート*/
/*--------------------------------------------------------*/
void sortTotal_score(SCORE_DATAFORM* pdata)
{
	int i = 0;
	int j = 0;
	int k = 0;

	/*単純に総合点の比較*/
	for (j = STUDENT_NUM; j > 0; j--)
	{
		for (i = 0; i < j; i++)
		{
			if (pdata[i].total_score < pdata[i+1].total_score)
			{
				switchRow(pdata, i);
			}
		}
	}

	/*順位の調整*/
	for (i = 0; i < STUDENT_NUM; i++)
	{
		if (pdata[i].total_score > pdata[i+1].total_score)
		{
			pdata[i].rank_num = i + 1;
		}
		else if (pdata[i].total_score == pdata[i+1].total_score)
		{
			pdata[i].rank_num = i + 1;
			pdata[i + 1].rank_num = i + 1;
			i++;
		}
	}

	return;
}

/*--------------------------------------------------------*/
/*関数名：sortJapanease_score*/
/*概　要：ソート*/
/*引　数：配列ポインタ*/
/*戻り値：なし*/
/*特　記：国語のソート*/
/*--------------------------------------------------------*/
void sortJapanease_score(SCORE_DATAFORM* pdata)
{
	int i = 0;
	int j = 0;
	int k = 0;
	
	/*単純に点の比較*/
	for (j = STUDENT_NUM; j > 0; j--)
	{
		for (i = 0; i < j; i++)
		{
			if (pdata[i].japanese < pdata[i + 1].japanese)
			{
				switchRow(pdata, i);
			}
		}
	}

	/*順位の調整*/
	for (i = 0; i < STUDENT_NUM; i++)
	{
		if (pdata[i].japanese > pdata[i + 1].japanese)
		{
			pdata[i].rank_num = i + 1;
		}
		else if (pdata[i].japanese == pdata[i + 1].japanese)
		{
			pdata[i].rank_num = i + 1;
			pdata[i + 1].rank_num = i + 1;
			i++;
		}
	}



	return;
}

/*--------------------------------------------------------*/
/*関数名：sortArithmetic_score*/
/*概　要：ソート*/
/*引　数：配列ポインタ*/
/*戻り値：なし*/
/*特　記：算数のソート*/
/*--------------------------------------------------------*/
void sortArithmetic_score(SCORE_DATAFORM* pdata)
{
	int i = 0;
	int j = 0;
	int k = 0;


	/*単純に点の比較*/
	for (j = STUDENT_NUM; j > 0; j--)
	{
		for (i = 0; i < j; i++)
		{
			if (pdata[i].arithmetic < pdata[i + 1].arithmetic)
			{
				switchRow(pdata, i);
			}
		}
	}

	/*順位の調整*/
	for (i = 0; i < STUDENT_NUM; i++)
	{
		if (pdata[i].arithmetic > pdata[i + 1].arithmetic)
		{
			pdata[i].rank_num = i + 1;
		}
		else if (pdata[i].arithmetic == pdata[i + 1].arithmetic)
		{
			pdata[i].rank_num = i + 1;
			pdata[i + 1].rank_num = i + 1;
			i++;
		}
	}



	return;
}

/*--------------------------------------------------------*/
/*関数名：sortScience_score*/
/*概　要：ソート*/
/*引　数：配列ポインタ*/
/*戻り値：なし*/
/*特　記：理科のソート*/
/*--------------------------------------------------------*/
void sortScience_score(SCORE_DATAFORM* pdata)
{
	int i = 0;
	int j = 0;
	int k = 0;


	/*単純に総合点の比較*/
	for (j = STUDENT_NUM; j > 0; j--)
	{
		for (i = 0; i < j; i++)
		{
			if (pdata[i].science < pdata[i + 1].science)
			{
				switchRow(pdata, i);
			}
		}
	}

	/*順位の調整*/
	for (i = 0; i < STUDENT_NUM; i++)
	{
		if (pdata[i].science > pdata[i + 1].science)
		{
			pdata[i].rank_num = i + 1;
		}
		else if (pdata[i].science == pdata[i + 1].science)
		{
			pdata[i].rank_num = i + 1;
			pdata[i + 1].rank_num = i + 1;
			i++;
		}
	}



	return;
}

/*--------------------------------------------------------*/
/*関数名：sortSocial_score*/
/*概　要：ソート*/
/*引　数：配列ポインタ*/
/*戻り値：なし*/
/*特　記：社会のソート*/
/*--------------------------------------------------------*/
void sortSocial_score(SCORE_DATAFORM* pdata)
{
	int i = 0;
	int j = 0;
	int k = 0;


	/*単純に総合点の比較*/
	for (j = STUDENT_NUM; j > 0; j--)
	{
		for (i = 0; i < j; i++)
		{
			if (pdata[i].social < pdata[i + 1].social)
			{
				switchRow(pdata, i);
			}
		}
	}

	/*順位の調整*/
	for (i = 0; i < STUDENT_NUM; i++)
	{
		if (pdata[i].social > pdata[i + 1].social)
		{
			pdata[i].rank_num = i + 1;
		}
		else if (pdata[i].social == pdata[i + 1].social)
		{
			pdata[i].rank_num = i + 1;
			pdata[i + 1].rank_num = i + 1;
			i++;
		}
	}



	return;
}




/*--------------------------------------------------------*/
/*メインコード*/
/*--------------------------------------------------------*/
/*--------------------------------------------------------*/
int main(void)
{
	/*基本データ*/
	SCORE_DATAFORM score[STUDENT_NUM] = { 0 };
	COLUM_FORM colum_name = { 0 };

	/*○概要説明*/
	printf("<<成績表ツール：成績分析プログラム>>\n\n");
	
	/*①処理:ファイル入力*/
	inputFile(&colum_name, score);/*引数：列名,スコア(アドレス情報)*/

	/*②-1処理：成績順位*/
	sortTotal_score(score);/*引数：スコア(アドレス情報)*/
	
	/*③処理：ファイル出力*/
	outputFile(&colum_name, score);/*引数：ファイル名,列名,スコア*/

	printf("<<処理の完了>>\n\n");
	printf("ディレクトリ内にファイル名：%sにて出力いたしました。\n",OUTPUT_FILE_NAME);

	return 0;

}