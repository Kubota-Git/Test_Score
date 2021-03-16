#define _CRT_SECURE_NO_WARNINGS
/*--------------------------------------------------------*/
/*���R�[�h���K��ꗗ*/
/*--------------------------------------------------------*/
/*--------------------------------------------------------*/
/*1)�����K��*/
/*�ϐ���:�S�ď������\�L�Ƃ���(�����q����_���ް�ް) aaa_bbb*/
/*��`��:�S�đ啶���\�L�Ƃ���(�����q����_���ް�ް) AAA_BBB*/
/*�֐���:���[���[�L�������P�[�X�\�L�Ƃ��� aaaBbb*/
/*--------------------------------------------------------*/
/*--------------------------------------------------------*/
/*2)�R�����g*/
/*���́A�T�v�A���� or�@�\���v�f�A�߂�l���L�q����*/
/*���ӎ�����������ۂ͓��L�ɂāA���e���L�q*/
/*--------------------------------------------------------*/
/*--------------------------------------------------------*/
/*3)�֐����[��*/
/*�Ȃ�ׂ����W���[�����x���キ���A�Ɨ��������߂�B*/
/*�K�v�Ȓl(�A�h���X)�݂̂�n��*/
/*�������K�v�ȏꍇ�͊֐����ŃR�s�[���s���A�����㌋�ʂ�Ԃ�*/
/*--------------------------------------------------------*/


/*--------------------------------------------------------*/
/*��include�t�@�C��*/
/*--------------------------------------------------------*/
#include <stdio.h>
#include <string.h>



/*--------------------------------------------------------*/
/*�@�萔��`*/
/*--------------------------------------------------------*/
/*--------------------------------------------------------*/
/*��`��	:STUDENT_NUM*/
/*�T�@�v	:���k�̑��l��*/
/*--------------------------------------------------------*/
#define STUDENT_NUM 50				/*���k�l��*/
#define NAME_NUM 32					/*���k���z�񃁃�����*/
#define ROW_NUM 8					/*�s*/
#define COL_NUM 10					/*��*/
#define FILE_NAME_NUM 128			/*�t�@�C������*/
#define OUTPUT_RANK_NUM 3				/*�o�̓����N��*/
#define OUTPUT_FILE_NAME "out.csv"	/*�o�̓t�@�C����*/

/*--------------------------------------------------------*/
/*�B�^��`*/
/*--------------------------------------------------------*/
/*--------------------------------------------------------*/
/*�^�@��	:SCORE_DATAFORM*/
/*�T�@�v	:���̓f�[�^�̏���*/
/*�����o1	:�����L���ONo.*/
/*�����o2	:�o�Ȕԍ�*/
/*�����o3	:����*/
/*�����o4	:����̓_��*/
/*�����o5	:�Z���̓_��*/
/*�����o6	:���Ȃ̓_��*/
/*�����o7	:�Љ�̓_��*/
/*�����o8	:�����_��*/
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
/*�^�@��	:DATAFORM*/
/*�T�@�v	:���o�f�[�^�̏���*/
/*�����o1	:�����L���ONo.*/
/*�����o2	:�o�Ȕԍ�*/
/*�����o3	:����*/
/*�����o4	:�e�_��*/

/*--------------------------------------------------------*/
typedef struct
{
	unsigned char rank_num;
	unsigned long num;
	char name[NAME_NUM];
	unsigned char score;

}DATAFORM;

/*--------------------------------------------------------*/
/*�^�@��	:COLUM_FORM*/
/*�T�@�v	:�񍀖�*/
/*�����o1	:�����L���ONo.*/
/*�����o2	:�o�Ȕԍ�*/
/*�����o3	:����*/
/*�����o4	:����̓_��*/
/*�����o5	:�Z���̓_��*/
/*�����o6	:���Ȃ̓_��*/
/*�����o7	:�Љ�̓_��*/
/*�����o8	:�����_��*/
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
/*�^�@��	:ANALYZE_FORM*/
/*�T�@�v	:��̓f�[�^�̏���*/
/*�����o1	:�Ȗږ�*/
/*�����o2	:�ő�l*/
/*�����o3	:���ϒl*/
/*�����o4	:�ŏ��l*/
/*--------------------------------------------------------*/
typedef struct
{
	unsigned short max;	/*�ő�*/
	unsigned short min;	/*�ŏ�*/
	double ave;			/*����*/
	char subject[32];	/*�Ȗږ�*/

}ANALYZE_DATAFORTM;


/*--------------------------------------------------------*/
/*�A�O���[�o���ϐ�*/
/*--------------------------------------------------------*/
/*--------------------------------------------------------*/
/*�ϐ���	:score_data*/
/*�T�v		:���̓t�@�C�����i�[*/
/*���L		:�Q�Ɛ���f�[�^�Ƃ���*/
/*--------------------------------------------------------*/

SCORE_DATAFORM score[STUDENT_NUM] = { 0 };



/*--------------------------------------------------------*/
/*�C�֐��錾*/
/*--------------------------------------------------------*/
/*�t�@�C������֐��ꗗ*/
int inputFile(COLUM_FORM*, SCORE_DATAFORM*);
int outputFile(COLUM_FORM*, SCORE_DATAFORM*);
void switchRow(SCORE_DATAFORM* pdata, int i);

/*�\�[�g�֐��ꗗ*/
void sortTotal_score(SCORE_DATAFORM*);
void sortJapanease_score(SCORE_DATAFORM*);
void sortArithmetic_score(SCORE_DATAFORM*);
void sortScience_score(SCORE_DATAFORM*);
void sortSocial_score(SCORE_DATAFORM*);

/*��͊֐��ꗗ*/
void JapaneseData(ANALYZE_DATAFORTM*, SCORE_DATAFORM*);
void ArithmeticData(ANALYZE_DATAFORTM*, SCORE_DATAFORM*);
void ScienceData(ANALYZE_DATAFORTM*, SCORE_DATAFORM*);
void SocialData(ANALYZE_DATAFORTM*, SCORE_DATAFORM*);

/*���@�\*/
void getColum(FILE**, COLUM_FORM*);
void sortScore(SCORE_DATAFORM*, char*, DATAFORM*, ANALYZE_DATAFORTM*);
void analyzeScore(DATAFORM*, ANALYZE_DATAFORTM*);
int outputScore(DATAFORM*, ANALYZE_DATAFORTM*);



/*--------------------------------------------------------*/
/*�D�e�֐�*/
/*--------------------------------------------------------*/
/*--------------------------------------------------------*/
/*�֐����FopenFile*/
/*�T�@�v�F���̓t�@�C�����J���f�[�^���i�[����*/
/*���@���F�Ȃ�*/
/*�߂�l�F�ǎ搬���F1�@�ǎ掸�s�F0*/
/*���@�L�F*/
/*--------------------------------------------------------*/
int inputFile(COLUM_FORM *pcolum_name, SCORE_DATAFORM* pscore)
{
	int i=0;
	int read_judge = 1;

	char cpy_file_name[FILE_NAME_NUM] = { 0 };
	COLUM_FORM cpy_colum_name = { 0 };
	SCORE_DATAFORM cpy_score[STUDENT_NUM] = { 0 };

	FILE* fp = NULL;

	/*���͒l�ǂݎ��*/
	do{
		printf("Test_score.exe�Ɠ����f�B���N�g������.csv�t�@�C�����i�[�����������B\n");
		printf("�i�[����.csv�t�@�C��������͂��AENTER�L�[�������Ă��������B\n-->");
		scanf_s("%s", cpy_file_name, sizeof(cpy_file_name));	/*�t�@�C�������L�[�{�[�h����*/
		read_judge = fopen_s(&fp, cpy_file_name, "r");				/*�t�@�C�����J��*/
		if (read_judge == EOF)
		{
			printf("ERROR1:���͂��ꂽ�t�@�C����������������܂���\n\n");
		}
	} while (read_judge == EOF);


	/*�񖼂̎擾*/
	getColum(fp,&cpy_colum_name); /*�Ȃ���&fp�œn���Ȃ�*/

	/*�l�̎擾*/
	for (i = 0; i < STUDENT_NUM; i++)
	{
		fscanf(fp, "%d,%[^,],%d,%d,%d,%d",
			&cpy_score[i].num,			/*�o�Ȕԍ�*/
			cpy_score[i].name,			/*���O*/
			&cpy_score[i].japanese,		/*����*/
			&cpy_score[i].arithmetic,	/*�Z��*/
			&cpy_score[i].science,		/*����*/
			&cpy_score[i].social);		/*�Љ�_��*/

		/*�����_*/
		cpy_score[i].total_score = cpy_score[i].japanese + cpy_score[i].arithmetic + cpy_score[i].science + cpy_score[i].social;

		/*�l�̕ԋp*/
		pscore[i] = cpy_score[i];
	}

	/*�l�̕ԋp*/
	*pcolum_name = cpy_colum_name;

	fclose(fp); 

	return 1;
}

/*--------------------------------------------------------*/
/*�֐����FoutputFile*/
/*�T�@�v�F���̓t�@�C�����J���f�[�^���i�[����*/
/*���@���F�Ȃ�*/
/*�߂�l�F�ǎ搬���F1�@�ǎ掸�s�F0*/
/*���@�L�F�e���ڂ̃\�[�g�������ɍs��*/
/*--------------------------------------------------------*/
int outputFile(COLUM_FORM* pcolum_name, SCORE_DATAFORM* pscore)
{
	int i = 0;
	COLUM_FORM cpy_colum_name = { 0 };
	SCORE_DATAFORM cpy_score[STUDENT_NUM] = { 0 };
	/*�e�Ȗڃf�[�^*/
	ANALYZE_DATAFORTM japanese_parameter = { 0 };
	ANALYZE_DATAFORTM arithmetic_parameter = { 0 };
	ANALYZE_DATAFORTM science_parameter = { 0 };
	ANALYZE_DATAFORTM social_parameter = { 0 };

	/*�l�̃R�s�[*/
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

	/*��ڂ̃Z�b�g*/
	fprintf(fp, "%s\n","����������");/*����1*/

	/*���ږ��̃Z�b�g*/
	fprintf(fp, "%s,%s,%s,%s,%s,%s,%s,%s\n",
		cpy_colum_name.rank_num,		/*�����L���O����*/
		cpy_colum_name.num,				/*�o�Ȕԍ�*/
		cpy_colum_name.name,			/*���O*/
		cpy_colum_name.japanese,		/*����*/
		cpy_colum_name.arithmetic,		/*�Z��*/
		cpy_colum_name.science,			/*����*/
		cpy_colum_name.social,			/*�Љ�_��*/
		cpy_colum_name.total_score);	/*�����_��*/

	/*�e�l�̊i�[*/
	for (i = 0; i < STUDENT_NUM; i++)
	{
		fprintf(fp, "%d,%d,%s,%d,%d,%d,%d,%d\n",
			cpy_score[i].rank_num,		/*�����L���O����*/
			cpy_score[i].num,			/*�o�Ȕԍ�*/
			cpy_score[i].name,			/*���O*/
			cpy_score[i].japanese,		/*����*/
			cpy_score[i].arithmetic,	/*�Z��*/
			cpy_score[i].science,		/*����*/
			cpy_score[i].social,		/*�Љ�_��*/
			cpy_score[i].total_score);	/*�Љ�_��*/
	}

	fclose(fp);

	return 1;
}

/*--------------------------------------------------------*/
/*�֐����FcloseFile2*/
/*�T�@�v�F���̓t�@�C�����J���f�[�^���i�[����*/
/*���@���F�Ȃ�*/
/*�߂�l�F�ǎ搬���F1�@�ǎ掸�s�F0*/
/*���@�L�F�e���ڂ̃\�[�g�������ɍs��*/
/*--------------------------------------------------------*/
int outputScore(DATAFORM* pscore, ANALYZE_DATAFORTM* pparameter)
{
	int i = 0;
	char title[128] = { "���Ȗڕʐ���(" };


	FILE* fp = NULL;

	fopen_s(&fp, OUTPUT_FILE_NAME, "a");

	/*��ڂ̃Z�b�g*/
	strcat_s(title,sizeof(title),pparameter->subject);
	printf("�f�o�b�O�m�F�F%s", title);
	printf("�f�o�b�O�m�F�F%s", pparameter->subject);
	fprintf(fp, "\n%s)\n", title);

	/*�e�l�̊i�[*/
	for (i = 0; i < OUTPUT_RANK_NUM; i++)
	{
		fprintf(fp, "%d,%d,%s,%d\n",
			pscore[i].rank_num,		/*�����L���O����*/
			pscore[i].num,			/*�o�Ȕԍ�*/
			pscore[i].name,			/*���O*/
			pscore[i].score);		/*�l*/
	}
	/*�ő�ŏ��l�̃Z�b�g*/
	fprintf(fp, "%s,%d\n%s,%d\n%s,%.1f\n", /*�����_��1���\��*/
		"�ō�", pparameter->max,
		"�Œ�", pparameter->min,
		"����", pparameter->ave);

	fclose(fp);

	return 1;
}

/*--------------------------------------------------------*/
/*�֐����FgetColum*/
/*�T�@�v�F�񖼂̎擾*/
/*���@���F�t�@�C���n���h���A�񖼔z��|�C���^*/
/*�߂�l�F�Ȃ�*/
/*���@�L�FoPenFile�֐����Ŏg�p����*/
/*--------------------------------------------------------*/
void getColum(FILE** fp, COLUM_FORM* pcolum_name)
{
	COLUM_FORM cpy_colum_name = { 0 };
	/*�񖼂̎擾*/
	fscanf(fp, "%[^,],%[^,],%[^,],%[^,],%[^,],%[^\n]",
		cpy_colum_name.num,			/*�o�Ȕԍ�*/
		cpy_colum_name.name,		/*���O*/
		cpy_colum_name.japanese,	/*����*/
		cpy_colum_name.arithmetic,	/*�Z��*/
		cpy_colum_name.science,		/*����*/
		cpy_colum_name.social);		/*�Љ�_��*/


	sscanf("���v", "%s", cpy_colum_name.total_score);
	sscanf("����", "%s", cpy_colum_name.rank_num);

	*pcolum_name = cpy_colum_name;

	return;
}


/*--------------------------------------------------------*/
/*�֐����FJapaneseData*/
/*�T�@�v�FMax/Min/Ave�l�̎擾*/
/*���@���F�z��|�C���^*/
/*�߂�l�F�Ȃ�*/
/*���@�L�F����\�[�g��Ɏg�p*/
/*--------------------------------------------------------*/
void JapaneseData(ANALYZE_DATAFORTM* pdata, SCORE_DATAFORM* pscore)
{
	int i = 0;
	int j = 0;
	int k = 0;

	double ave_score = 0;
	ANALYZE_DATAFORTM score_data = { 0 };

	/*Max/Min�̎擾*/
	pdata->max = pscore[0].japanese;
	pdata->min = pscore[STUDENT_NUM - 1].japanese;

	/*Ave�̎擾*/
	for (i = 0; i < STUDENT_NUM; i++)
	{
		ave_score += pscore[i].japanese;
	}
	pdata->ave = ave_score / STUDENT_NUM;

	return;
}

/*--------------------------------------------------------*/
/*�֐����FArithmeticData*/
/*�T�@�v�FMax/Min/Ave�l�̎擾*/
/*���@���F�z��|�C���^*/
/*�߂�l�F�Ȃ�*/
/*���@�L�F�Z���\�[�g��Ɏg�p*/
/*--------------------------------------------------------*/
void ArithmeticData(ANALYZE_DATAFORTM* pdata, SCORE_DATAFORM* pscore)
{
	int i = 0;
	int j = 0;
	int k = 0;


	double ave_score = 0;
	ANALYZE_DATAFORTM score_data = { 0 };

	/*Max/Min�̎擾*/
	pdata->max = pscore[0].arithmetic;
	pdata->min = pscore[STUDENT_NUM - 1].arithmetic;

	/*Ave�̎擾*/
	for (i = 0; i < STUDENT_NUM; i++)
	{
		ave_score += pscore[i].arithmetic;
	}
	pdata->ave = ave_score / STUDENT_NUM;

	return;
}

/*--------------------------------------------------------*/
/*�֐����FSciencData*/
/*�T�@�v�FMax/Min/Ave�l�̎擾*/
/*���@���F�z��|�C���^*/
/*�߂�l�F�Ȃ�*/
/*���@�L�F���ȃ\�[�g��Ɏg�p*/
/*--------------------------------------------------------*/
void ScienceData(ANALYZE_DATAFORTM* pdata, SCORE_DATAFORM* pscore)
{
	int i = 0;
	int j = 0;
	int k = 0;

	double ave_score = 0;
	ANALYZE_DATAFORTM score_data = { 0 };

	/*Max/Min�̎擾*/
	pdata->max = pscore[0].science;
	pdata->min = pscore[STUDENT_NUM - 1].science;

	/*Ave�̎擾*/
	for (i = 0; i < STUDENT_NUM; i++)
	{
		ave_score += pscore[i].science;
	}
	pdata->ave = ave_score / STUDENT_NUM;

	return;
}

/*--------------------------------------------------------*/
/*�֐����FSocialData*/
/*�T�@�v�FMax/Min/Ave�l�̎擾*/
/*���@���F�z��|�C���^*/
/*�߂�l�F�Ȃ�*/
/*���@�L�F�Љ�\�[�g��Ɏg�p*/
/*--------------------------------------------------------*/
void SocialData(ANALYZE_DATAFORTM* pdata, SCORE_DATAFORM* pscore)
{
	int i = 0;
	int j = 0;
	int k = 0;


	double ave_score = 0;
	ANALYZE_DATAFORTM score_data = { 0 };

	/*Max/Min�̎擾*/
	pdata->max = pscore[0].social;
	pdata->min = pscore[STUDENT_NUM - 1].social;

	/*Ave�̎擾*/
	for (i = 0; i < STUDENT_NUM; i++)
	{
		ave_score += pscore[i].social;
	}
	pdata->ave = ave_score / STUDENT_NUM;

	return;
}


/*--------------------------------------------------------*/
/*�֐����FanalyzeScore*/
/*�T�@�v�FMax/Min/Ave�l�̎擾*/
/*���@���F�X�R�A�|�C���^,��͒l�|�C���^*/
/*�߂�l�F�Ȃ�*/
/*���@�L�F�\�[�g��Ɏg�p*/
/*--------------------------------------------------------*/
void analyzeScore(DATAFORM* pscore, ANALYZE_DATAFORTM* pdata)
{
	int i = 0;
	int j = 0;
	int k = 0;


	double ave_score = 0;
	ANALYZE_DATAFORTM score_data = { 0 };

	/*Max/Min�̎擾*/
	pdata->max = pscore[0].score;
	pdata->min = pscore[STUDENT_NUM - 1].score;

	/*Ave�̎擾*/
	for (i = 0; i < STUDENT_NUM; i++)
	{
		ave_score += pscore[i].score;
	}
	pdata->ave = ave_score / STUDENT_NUM;

	return;
}


/*--------------------------------------------------------*/
/*�֐����FswitchRow*/
/*�T�@�v�F�O��s�̓��ւ̂�*/
/*���@���F�z��|�C���^,�C���N�������g�ԍ�i*/
/*�߂�l�F�Ȃ�*/
/*���@�L�F*/
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
		/*�z��ԍ�i�̑O��f�[�^�����ւ�*/
		cpy_data[0] = pdata[i];
		pdata[i] = pdata[i + 1];
		pdata[i + 1] = cpy_data[0];
	}
	return;
}

/*--------------------------------------------------------*/
/*�֐����FsortScore*/
/*�T�@�v�F�\�[�g*/
/*���@���F�X�R�A�|�C���^,���Ȗ�,��͒l�|�C���^*/
/*�߂�l�F�Ȃ�*/
/*���@�L�F�\�[�g��ɍő�l�ŏ��l���擾*/
/*--------------------------------------------------------*/
void sortScore(SCORE_DATAFORM* pdata,char* colum_name, DATAFORM* pscore, ANALYZE_DATAFORTM* pparameter)
{
	int i = 0;
	int j = 0;
	int k = 0;
	DATAFORM cpy_score[STUDENT_NUM] = { 0 };
	DATAFORM switch_score[1] = { 0 };
	ANALYZE_DATAFORTM copy_parameter = {0};
	int colum_num = 0;

	if (colum_name == "����")
	{
		colum_num = 1;
	}
	else if (colum_name == "�Z��")
	{
		colum_num = 2;
	}
	else if (colum_name == "����")
	{
		colum_num = 3;
	}
	else if (colum_name == "�Љ�")
	{
		colum_num = 4;
	}
	else if (colum_name == "���v")
	{
		colum_num = 5;
	}

	/*�l�̃R�s�[*/
	for (i = 0; i < STUDENT_NUM; i++)
	{
		cpy_score[i].num = pdata[i].num;
		strcpy_s(cpy_score[i].name,sizeof(cpy_score[i].name),pdata[i].name);
		switch (colum_num)
		{
		case 1:
			cpy_score[i].score = pdata[i].japanese;
			break;
		case 2:
			cpy_score[i].score = pdata[i].arithmetic;
			break;
		case 3:
			cpy_score[i].score = pdata[i].science;
			break;
		case 4:
			cpy_score[i].score = pdata[i].social;
			break;
		case 5:
			cpy_score[i].score = pdata[i].total_score;
			break;
		}
	}


	/*�P���ɑ����_�̔�r*/
	for (j = STUDENT_NUM; j > 0; j--)
	{
		for (i = 0; i < j; i++)
		{
			if (cpy_score[i].score < cpy_score[i+1].score)
			{
				/*�z��ԍ�i�̑O��f�[�^�����ւ�*/
				switch_score[0] = cpy_score[i];
				cpy_score[i] = cpy_score[i + 1];
				cpy_score[i + 1] = switch_score[0];
			}
		}
	}

	/*���ʂ̒���*/
	for (k = 0; k < STUDENT_NUM; k++)
	{
		if (cpy_score[k].score > cpy_score[k+1].score)
		{
			cpy_score[k].rank_num = k + 1;
		}
		else if (cpy_score[k].score == cpy_score[k].score)
		{
			cpy_score[k].rank_num = k + 1;
			cpy_score[k + 1].rank_num = k + 1;
			k++;
		}
	}

	/*�ő�ŏ��l�̉��*/
	copy_parameter = *pparameter;
	strcpy_s(copy_parameter.subject, sizeof(copy_parameter.subject), colum_name);
	analyzeScore(&cpy_score, &copy_parameter);
	*pparameter = copy_parameter;

	/*�l�̕ԋp*/
	for (i = 0; i < STUDENT_NUM; i++)
	{
		pscore[i] = cpy_score[i];
	}

	return 0;
}


/*--------------------------------------------------------*/
/*�֐����FsortTotal_score*/
/*�T�@�v�F�\�[�g*/
/*���@���F�z��|�C���^*/
/*�߂�l�F�Ȃ�*/
/*���@�L�F�����_�̃\�[�g*/
/*--------------------------------------------------------*/
void sortTotal_score(SCORE_DATAFORM* pdata)
{
	int i = 0;
	int j = 0;
	int k = 0;

	/*�P���ɑ����_�̔�r*/
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

	/*���ʂ̒���*/
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
/*�֐����FsortJapanease_score*/
/*�T�@�v�F�\�[�g*/
/*���@���F�z��|�C���^*/
/*�߂�l�F�Ȃ�*/
/*���@�L�F����̃\�[�g*/
/*--------------------------------------------------------*/
void sortJapanease_score(SCORE_DATAFORM* pdata)
{
	int i = 0;
	int j = 0;
	int k = 0;
	
	/*�P���ɓ_�̔�r*/
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

	/*���ʂ̒���*/
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
/*�֐����FsortArithmetic_score*/
/*�T�@�v�F�\�[�g*/
/*���@���F�z��|�C���^*/
/*�߂�l�F�Ȃ�*/
/*���@�L�F�Z���̃\�[�g*/
/*--------------------------------------------------------*/
void sortArithmetic_score(SCORE_DATAFORM* pdata)
{
	int i = 0;
	int j = 0;
	int k = 0;


	/*�P���ɓ_�̔�r*/
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

	/*���ʂ̒���*/
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
/*�֐����FsortScience_score*/
/*�T�@�v�F�\�[�g*/
/*���@���F�z��|�C���^*/
/*�߂�l�F�Ȃ�*/
/*���@�L�F���Ȃ̃\�[�g*/
/*--------------------------------------------------------*/
void sortScience_score(SCORE_DATAFORM* pdata)
{
	int i = 0;
	int j = 0;
	int k = 0;


	/*�P���ɑ����_�̔�r*/
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

	/*���ʂ̒���*/
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
/*�֐����FsortSocial_score*/
/*�T�@�v�F�\�[�g*/
/*���@���F�z��|�C���^*/
/*�߂�l�F�Ȃ�*/
/*���@�L�F�Љ�̃\�[�g*/
/*--------------------------------------------------------*/
void sortSocial_score(SCORE_DATAFORM* pdata)
{
	int i = 0;
	int j = 0;
	int k = 0;


	/*�P���ɑ����_�̔�r*/
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

	/*���ʂ̒���*/
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
/*���C���R�[�h*/
/*--------------------------------------------------------*/
/*--------------------------------------------------------*/
int main(void)
{
	/*��{�f�[�^*/
	SCORE_DATAFORM score[STUDENT_NUM] = { 0 };
	COLUM_FORM colum_name = { 0 };
	DATAFORM japanese_score[STUDENT_NUM] = { 0 };
	DATAFORM arithmetic_score;
	DATAFORM science_score;
	DATAFORM social_score;

	ANALYZE_DATAFORTM japanese_parameter = { 0 };
	ANALYZE_DATAFORTM arithmetic_parameter = { 0 };
	ANALYZE_DATAFORTM science_parameter = { 0 };
	ANALYZE_DATAFORTM social_parameter = { 0 };


	/*���T�v����*/
	printf("<<���ѕ\�c�[���F���ѕ��̓v���O����>>\n\n");
	
	/*�@����:�t�@�C������*/
	inputFile(&colum_name, score);/*�����F��,�X�R�A(�A�h���X���)*/

	/*�A-1�����F���я���*/
	sortTotal_score(score);/*�����F�X�R�A(�A�h���X���)*/


	/*�A-2�����F�Ȗڕʏ���*/
	sortScore(&score, "����", &japanese_score, &japanese_parameter);
	sortScore(&score, "�Z��", &arithmetic_score,&arithmetic_parameter);
	sortScore(&score, "����", &science_score,&science_parameter);
	sortScore(&score, "�Љ�", &social_score,&social_parameter);


	
	/*�B�����F�t�@�C���o��*/
	outputFile(&colum_name, score);/*�����F�t�@�C����,��,�X�R�A*/
	outputScore(&japanese_score, &japanese_parameter);
	outputScore(&arithmetic_score, &arithmetic_parameter);
	outputScore(&science_score, &science_parameter);
	outputScore(&social_score, &social_parameter);

	printf("<<�����̊���>>\n\n");
	printf("�f�B���N�g�����Ƀt�@�C�����F%s�ɂďo�͂������܂����B\n",OUTPUT_FILE_NAME);

	return 0;

}