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
#define row 7			/*�s*/
#define col 7			/*��*/






/*--------------------------------------------------------*/
/*�B�^��`*/
/*--------------------------------------------------------*/
/*--------------------------------------------------------*/
/*�^�@��	:SCORE_DATAFORM*/
/*�T�@�v	:���̓f�[�^�̏���*/
/*�����o1	:�o�Ȕԍ�*/
/*�����o2	:����*/
/*�����o3	:����̓_��*/
/*�����o4	:�Z���̓_��*/
/*�����o5	:���Ȃ̓_��*/
/*�����o6	:�Љ�̓_��*/
/*�����o6	:�����_��*/
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
/*�A�O���[�o���ϐ�*/
/*--------------------------------------------------------*/
/*--------------------------------------------------------*/
/*�ϐ���	:score_data*/
/*�T�v		:���̓t�@�C�����i�[*/
/*���L		:�Q�Ɛ���f�[�^�Ƃ���*/
/*--------------------------------------------------------*/

SCORE_DATAFORM score[STUDENT_NUM] = { 0 };
char file_name[128] = { 0 };
char colum_name[7][10] = { 0 };




/*--------------------------------------------------------*/
/*�C�֐��錾*/
/*--------------------------------------------------------*/
int openFile(void);
int sortNum(SCORE_DATAFORM*);
//unsigned short analyzeScore(unsigned short*);
void closeFile(FILE *);



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


	int stu_data[32] = { 0 };

	int read_judge = 1;

	int i = 0;


	unsigned char list_size = sizeof(stu_data) / sizeof(stu_data[0]);

	/*���͒l�ǂݎ��*/

	do{

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
	sscanf("�����_","%s",&colum_name[6]);

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
	FILE* fp=NULL;

	fopen_s(&fp, "out.csv", "w");

	fprintf(fp, "%s,%s,%s,%s,%s,%s\n",
		&colum_name[0],			//�o�Ȕԍ�
		&colum_name[1],			//���O
		&colum_name[2],			//����
		&colum_name[3],			//�Z��
		&colum_name[4],			//����
		&colum_name[4],			//�Љ�_��
		&colum_name[6]);		//�����_��

	for (i = 0; i < STUDENT_NUM; i++)
	{
		fprintf(fp, "%d,%s,%d,%d,%d,%d\n",
			&score[i].num,			/*�o�Ȕԍ�*/
			&score[i].name,			/*���O*/
			&score[i].japanese,		/*����*/
			&score[i].arithmetic,	/*�Z��*/
			&score[i].science,		/*����*/
			&score[i].social);		/*�Љ�_��*/
	}

	fclose(fp);

	return;
}



/*--------------------------------------------------------*/
/*�֐����FsortNum*/
/*�T�@�v�F�����L���O���ɓ���ւ���*/
/*���@���F�X�R�A�\*/
/*�߂�l�F����ւ������F1�@����ւ����s�F0*/
/*���@�L�F*/
/*--------------------------------------------------------*/
int sortNum(SCORE_DATAFORM *sort_score)
{
	/**/



	return 0;
}


/*--------------------------------------------------------*/
/*���C���R�[�h*/
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


	/*���T�v����*/
	printf("<<���ѕ\�c�[���F���ѕ��̓v���O����>>\n\n");
	
	/*�@����:�t�@�C������*/
	openFile();


	/*�A-1�����F��������*/
	sortNum(&cpy_score);

	/*�A-2�����F�Ȗڕʏ�ʎ҂̕\��*/
	//sortNum(&cpy_score);


	/*�A-3�����F�Ȗڕʂ̊e���ڂ��Z�o*/
	//analyzeScore(&cpy_score);

	/*�B�����F�t�@�C���o��*/
	closeFile();


	printf("�����̊���\n");

	return 0;



}