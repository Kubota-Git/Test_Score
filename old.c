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


/*--------------------------------------------------------*/
/*�@�萔��`*/
/*--------------------------------------------------------*/
/*--------------------------------------------------------*/
/*��`��	:STUDENT_NUM*/
/*�T�@�v	:���k�̑��l��*/
/*--------------------------------------------------------*/
#define STUDENT_NUM 50	/*���k�l��*/
#define NAME_NUM 32		/*���k���z�񃁃�����*/
/*#define row 7			/*�s*/
/*#define col 7			/*��*/


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
/*�^�@��	:CLC_DATAFORM*/
/*�T�@�v	:������l�̏���*/
/*�����o1	:�o�Ȕԍ�*/
/*�����o2	:����*/
/*�����o3	:�e�̓_��*/
/*--------------------------------------------------------*/
typedef struct
{
	unsigned char rank_num;
	unsigned long num;
	char name[NAME_NUM];
	unsigned char uni_score;

}CLC_DATAFORM;


/*--------------------------------------------------------*/
/*�^�@��	:RANK_FORM*/
/*�T�@�v	:�����L���O���ʂ̏���*/

/*�����o1	:���ꃉ���L���O*/
/*�����o2	:�Z�������L���O*/
/*�����o3	:���ȃ����L���O*/
/*�����o4	:�Љ���L���O*/
/*�����o5	:���������L���O*/
/*���@�L	:�e�l�ɂ͏o�Ȕԍ����L��*/
/*--------------------------------------------------------*/
/*
typedef struct
{
	unsigned long rank_japanese;	//�z��ԍ�:0
	unsigned long rank_arithmetic;	//�z��ԍ�:1
	unsigned long rank_science;		//�z��ԍ�:2
	unsigned long rank_social;		//�z��ԍ�:3
	unsigned long rank_total_score;	//�z��ԍ�:4

}RANK_FORM;
*/

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
	char subject[10];
	unsigned short max;
	unsigned short ave;
	unsigned short min;

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

char file_name[128] = { 0 };
char colum_name[8][10] = { 0 };


/*--------------------------------------------------------*/
/*�C�֐��錾*/
/*--------------------------------------------------------*/
int openFile(void);
void rankNum(RANK_FORM*);
void sortNum(unsigned long*, unsigned int*);
void closeFile(FILE*);
//unsigned short analyzeScore(unsigned short*);
unsigned char searchNum(RANK_FORM*, unsigned char, unsigned long);
void switchValue(SCORE_DATAFORM*);


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
int openFile(void)
{
	FILE* fp = NULL;


	int stu_data[NAME_NUM] = { 0 };

	int read_judge = 1;

	int i = 0;


	unsigned char list_size = sizeof(stu_data) / sizeof(stu_data[0]);

	/*���͒l�ǂݎ��*/

	do {

		printf("Test_score.exe�Ɠ����f�B���N�g������.csv�t�@�C�����i�[�����������B\n");
		printf("�i�[����.csv�t�@�C��������͂��AENTER�L�[�������Ă��������B\n-->");
		scanf_s("%s", file_name, sizeof(file_name));	/*�t�@�C�������L�[�{�[�h����*/

		/*�f�o�b�O�R�[�h
		printf("�v�f�T�C�Y�S�F%d\n", sizeof(file_name));
		printf("�v�f�T�C�Y�F%d\n", sizeof(file_name[0]));
		printf("�擾�����F%s\n", file_name);
		*/

		read_judge = fopen_s(&fp, file_name, "r");				/*�t�@�C�����J��*/
		if (read_judge == EOF)
		{
			printf("ERROR1:���͂��ꂽ�t�@�C����������������܂���\n\n");
		}

	} while (read_judge == EOF);


	fscanf(fp, "%[^,],%[^,],%[^,],%[^,],%[^,],%[^\n]",
		&colum_name[0],			//�o�Ȕԍ�
		&colum_name[1],			//���O
		&colum_name[2],			//����
		&colum_name[3],			//�Z��
		&colum_name[4],			//����
		&colum_name[5]);		//�Љ�_��
	sscanf("�����_", "%s", &colum_name[6]);
	sscanf("����", "%s", &colum_name[7]);

	/*�f�o�b�O����
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
			&score[i].num,			/*�o�Ȕԍ�*/
			&score[i].name,			/*���O*/
			&score[i].japanese,		/*����*/
			&score[i].arithmetic,	/*�Z��*/
			&score[i].science,		/*����*/
			&score[i].social);		/*�Љ�_��*/

		/*�����_*/
		score[i].total_score = score[i].japanese + score[i].arithmetic + score[i].science + score[i].social;

		/*�f�o�b�O�p
		printf("�o�Ȕԍ��F%d ", score[i].num);
		printf("�����F%s ", score[i].name);
		printf("����F%d ", score[i].japanese);
		printf("�Z���F%d ", score[i].arithmetic);
		printf("���ȁF%d ", score[i].science);
		printf("�Љ�F%d ", score[i].social);
		printf("�����_�F%d\n", score[i].total_score);
		*/
	}

	fclose(fp);

	return 1;
}

/*--------------------------------------------------------*/
/*�֐����FcloseFile*/
/*�T�@�v�F���̓t�@�C�����J���f�[�^���i�[����*/
/*���@���F�Ȃ�*/
/*�߂�l�F�ǎ搬���F1�@�ǎ掸�s�F0*/
/*���@�L�F*/
/*--------------------------------------------------------*/
void closeFile(void)
{
	int i = 0;
	FILE* fp = NULL;

	fopen_s(&fp, "out.csv", "w");

	/*���ږ��̃Z�b�g*/
	fprintf(fp, "%s,%s,%s,%s,%s,%s\n",
		&colum_name[7],				//�����L���O����
		&colum_name[0],				//�o�Ȕԍ�
		&colum_name[1],			//���O
		&colum_name[2],			//����
		&colum_name[3],			//�Z��
		&colum_name[4],			//����
		&colum_name[4],			//�Љ�_��
		&colum_name[6]);			//�����_��

	/*�e�l�̊i�[*/
	for (i = 0; i < STUDENT_NUM; i++)
	{
		fprintf(fp, "%d,%d,%s,%d,%d,%d,%d,%d\n",
			&score[i].rank_num,		/*�����L���O����*/
			&score[i].num,			/*�o�Ȕԍ�*/
			&score[i].name,			/*���O*/
			&score[i].japanese,		/*����*/
			&score[i].arithmetic,	/*�Z��*/
			&score[i].science,		/*����*/
			&score[i].social,		/*�Љ�_��*/
			&score[i].total_score);	/*�Љ�_��*/
	}

	fclose(fp);

	return;
}



/*--------------------------------------------------------*/
/*�֐����FswitchRow*/
/*�T�@�v�F�O��s�̓��ւ̂�*/
/*���@���F�z��|�C���^,�C���N�������g�ԍ�i*/
/*�߂�l�F�Ȃ�*/
/*���@�L�F*/
/*--------------------------------------------------------*/
void switchRow(SCORE_DATAFORM* pdata, int i)
{
	SCORE_DATAFORM cpy_data[STUDENT_NUM] = { 0 };

	/*�z��ԍ�i�̑O��f�[�^�����ւ�*/
	cpy_data[i] = pdata[i + 1];
	cpy_data[i + 1] = pdata[i];
	pdata[i] = cpy_data[i];
	pdata[i + 1] = cpy_data[i + 1];

	return;
}


/*--------------------------------------------------------*/
/*�֐����FrankNum*/
/*�T�@�v�F�����L���O���ɓ���ւ���*/
/*���@���F�X�R�A�\*/
/*�߂�l�F����*/
/*���@�L�F	���o�u���\�[�g���̗p*/
/*			1)�O���r*/
/*			2)�オ�傫����Ώo�Ȕԍ���O�����ւ���*/
/*			3)�o�Ȕԍ�\n�ɂȂ�ƏI��*/
/*			4)�z��ԍ�n+1���1�`3���J��Ԃ�*/
/*			5)n+i=�z��ԍ��ɂȂ�ΏI��*/
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

	/*�ϐ����i�[*/
	for (i = 0; i < STUDENT_NUM; i++)
	{
		rank_j[i] = rank_a[i] = rank_sc[i] = rank_so[i] = rank_t[i] = score[i].num;
		rank_score_j[i] = score[i].japanese;
		rank_score_a[i] = score[i].arithmetic;
		rank_score_sc[i] = score[i].science;
		rank_score_so[i] = score[i].social;
		rank_score_t[i] = score[i].total_score;
	}

	/*�l�̃\�[�g�֐�*/
	sortNum(&rank_j, &rank_score_j);
	sortNum(&rank_a, &rank_score_a);
	sortNum(&rank_sc, &rank_score_sc);
	sortNum(&rank_so, &rank_score_so);
	sortNum(&rank_t, &rank_score_t);

	/*�l�̊i�[*/
	for (m = 0; m < STUDENT_NUM; m++)
	{
		pranking[m].rank_japanese = rank_j[m];
		pranking[m].rank_arithmetic = rank_a[m];
		pranking[m].rank_science = rank_sc[m];
		pranking[m].rank_social = rank_so[m];
		pranking[m].rank_total_score = rank_t[m];

		/*�f�o�b�N�`�F�b�N
		printf("����%d��:%d ", m + 1, pranking[m].rank_japanese);
		printf("�Z��%d��:%d ", m + 1, pranking[m].rank_arithmetic);
		printf("����%d��:%d ", m + 1, pranking[m].rank_science);
		printf("�Љ�%d��:%d ", m + 1, pranking[m].rank_social);
		printf("����%d��:%d\n", m + 1, pranking[m].rank_total_score);
		*/
	}
	return;
}


/*--------------------------------------------------------*/
/*�֐����FsortNum*/
/*�T�@�v�F�����L���O���ɓ���ւ���*/
/*���@���F�o�Ȕԍ��Ɗe�_���l*/
/*�߂�l�F�Ȃ�*/
/*���@�L�F	���o�u���\�[�g���̗p*/
/*			1)�O���r*/
/*			2)�オ�傫����Ώo�Ȕԍ���O�����ւ���*/
/*			3)STUDENT_NUM�ɂȂ�ƏI��*/
/*			4)1�`3���J��Ԃ�*/
/*			5)j=STUDENT_NUM�ɂȂ�ΏI��*/
/*--------------------------------------------------------*/
void sortNum(unsigned long* pnum, unsigned int* pscore)
{
	unsigned char i = 0;
	unsigned char j = 0;
	unsigned char k = 0;
	unsigned long anum = 0;
	unsigned long ascore = 0;

	/*�f�o�b�N�`�F�b�N
	for (i = 0; i < STUDENT_NUM; i++)
	{
		printf("pnum[%d]:%d\n", i, pnum[i]);
	}
	*/

	/*1)�O���r*/
	for (j = STUDENT_NUM; j > 0; j--)
	{
		for (k = 0; k < STUDENT_NUM - 1; k++)
		{
			/*2)�オ�傫����Ώo�Ȕԍ���O�����ւ���*/
			if (pscore[k] < pscore[k + 1])
			{
				ascore = pscore[k];
				anum = pnum[k];
				pscore[k] = pscore[k + 1];
				pnum[k] = pnum[k + 1];
				pscore[k + 1] = ascore;
				pnum[k + 1] = anum;
			}
			/*2-2)�l������̏ꍇ*/
			else if (pscore[k] == pscore[k + 1] && pnum[k] > pnum[k + 1])
			{
				anum = pnum[k];
				pnum[k] = pnum[k + 1];
				pnum[k + 1] = anum;
			}
			/*3)�o�Ȕԍ�\n�ɂȂ�ƏI��*/
		}
		/*4)�z��ԍ�n + 1���1�`3���J��Ԃ�*/
	}
	/*5)n+i=�z��ԍ��ɂȂ�ΏI��*/


	return;
}
/*--------------------------------------------------------*/
/*�֐����FsearchNum*/
/*�T�@�v�F�o�Ȕԍ�����z��ԍ����擾*/
/*���@���F�ϐ�ranking,���ׂ������ڔԍ�,���ׂ����o�Ȕԍ�*/
/*�߂�l�F�z��ԍ�*/
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
/*�֐����FanalyzeScore*/
/*�T�@�v�F�ő�E�ŏ��l�A���ϒl���Z�o*/
/*���@���F�e�i�[�v�z��*/
/*�߂�l�F�Ȃ�*/
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
/*���C���R�[�h*/
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


	/*���T�v����*/
	printf("<<���ѕ\�c�[���F���ѕ��̓v���O����>>\n\n");

	/*�@����:�t�@�C������*/
	openFile();


	/*�A-1�����F���я���*/
	rankNum(&ranking);


	/*�A-2�����F�Ȗڕʏ�ʎ҂̕\��*/
	//sortNum(&cpy_score);


	/*�A-3�����F�Ȗڕʂ̊e���ڂ��Z�o*/
	analyzeScore(&analyze_japanese, &ranking);

	/*�B�����F�t�@�C���o��*/
	closeFile();


	printf("�����̊���\n");

	switchRow(cpy_score);

	return 0;

}