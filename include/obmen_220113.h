/*
	*********	IP-���� ������⮢ � ����� ���⮢   *********
	__________________________________________________________
	|	�ਡ�� |  IP-����    |  ��� ���		| ���� �ਥ�� |
	|__________|______________|_________________|_____________|
	|	MO3	   |  194.1.1.6   |  node5_l1_MO3K	|	8208      |
	|__________|______________|_________________|_____________|
	|	MO3K   |  194.1.1.9   |  mo3_k			|	8208      |	
	|__________|______________|_________________|_____________|		

*/


/*
	#######################################################
	#													  #
	#					�����  MO3 -> MO3K 				  #
	#													  #
	#######################################################
*/


typedef struct	{

	unsigned short	cr_com;	//!!!!!!! ���浪��� ����� ��᫥���� �������, �뤠���� �� ��.MO3 � ��.MO3K  � ������ ०���
							//0-USHRT_MAX
	short			num_com;//!!!!����� ��᫥���� �뤠���� ������� � ������ ०���
							//������� 1 - �����⮢�� � ᥠ��� �裡
							//������� 2 - ��砫� ᥠ�� �裡
							//������� 3 - �����襭��  ᥠ�� �裡

							//��ࠬ���� ������� 1	
	short			num_KS;	//����� ������ �裡 1 - ��-�1, 2 - ��-�2 
	short			Nkey_SHAKR;	// ����� ���� ���� 
	short			Nans_PSP;	// ����� ��ᠬ��� ��� 
	short			ZUNf;		// ��� ��� (����� �ࠢ����� ����饩 ���⮩)
	short			Nd_FRCH;	// ��� ��������� ���
	short			N_FRCH;		//��� ����� ���	
	float			P_ANT_1;	//������ ��⥭�� (� ������ ��砫� ᥠ��), ࠤ
	float			beta_1;		//㣮� ���� ��⥭�� (� ������ ��砫� ᥠ��), ࠤ
	float			Fd_1;		//ᤢ�� ����� (� ������ ��砫� ᥠ��), ��� 

	short			kod_Barker;	//�ਧ��� ࠡ��� � ����� ��થ� (0-��� ����,1-� �����)
	float			P_ANT_2;	//������ ��⥭�� (� ������ ��砫� ᥠ��+1cek), ࠤ
	int				T_SS;		//�६� ��砫� �� ᥪ � �ଠ� ���
								//(�६� ��ࢮ�� ����祭�� ��� ��᫥ �室� �� � ��� �裡)

								//��������� ��⥭�� � ᤢ�� ����� �� ������ ⠪�
	float			P_ANT;		//������ ��⥭��, ࠤ
	float			beta;		//㣮� ���� ��⥭��, ࠤ
	float			Fd;			//ᤢ�� �����, ��� 
	float			Vr;			//ࠤ���쭠� ��⠢����� ᪮��� ��, �/c 
	float			Ar;			//ࠤ���쭠� ��⠢����� �᪮७�� ��, �/c2

	float			D;			//��������� ���쭮��� �� ��   � 
								//���������� � ���⮩ 1�� � ������ ���⭮�� ��
	unsigned short    cr_SEANCE;//���浪��� ����� ��᫥����� ����祭���� ���ᨢ� ���
	unsigned short    Rejim_AS;	//०�� ���ᮯ஢������� 1-���/0-�⪫

}obmen_41_31_2t;



typedef struct	{

	unsigned short	cr_com;	//!!!!!!!!!!!!! ���浪��� ����� ��᫥���� �������, �뤠���� �� ��.MO3 � ��.MO3K � ����஫쭮� ०��� 
							//0-USHRT_MAX
	short			num_com;	//!!!!!!!!!!  ����� ��᫥���� �뤠���� �������  � ����஫쭮� ०���
							//������� 4 - ��⠭����� ��⥭�� � 㪠������ ���������
							//������� 5 - ��⠭����� 㪠����� ०��� ࠡ���
							//������� 6 - ᤢ�� ������

							//��ࠬ���� ������� 4	
	float			q;		//㣮� ��⠭���� ��⥭�� �� ������� ࠤ
	float			alfa;	//㣮� ��⠭���� ��⥭�� �� �७� ࠤ
	float			beta;		//㣮� ��⠭���� ��⥭�� �� 㣫� ���� ࠤ
	unsigned short    Rejim_AS;	//०�� ���ᮯ஢������� 1-���/0-�⪫
	float			Fd;		//ᤢ�� ������ -70 - +70 ���

							//��ࠬ���� ������� 5
	unsigned short	M1;		//��᪠ 1 ������ �� ���/�⪫ ���ன��  ⠡� 3
	unsigned short	M2;		//��᪠ 2 ������ �� ���/�⪫ ���ன��  ⠡� 4
	unsigned short	M3;		//��᪠ 3 ������ �� ���/�⪫ ���ன��  ⠡� 5 
	unsigned short	M4;		//��᪠ 4 ������ �� ���/�⪫ ���ன��  ⠡� 6


}obmen_42_31_2t;

typedef struct	{

	obmen_42_31_2t from42;
	obmen_41_31_2t from41;
	obmen_AK_MN3_MO3K_t	fromAK;
}obmen_MO3_MO3K_t;




/*
	#######################################################
	#													  #
	#					�����  MO3K -> MO3 				  #
	#													  #
	#######################################################
*/

#define SUM_DCP_K1			1250	//max �᫮  �ᯮ��㥬�� ᫮� � ���ᨢ� ��� K1
#define SUM_DCP_K2			6250	//max �᫮  �ᯮ��㥬�� ᫮� � ���ᨢ� ��� K2

typedef struct	{

// !!!! �� ���䮭�� �� ��ठ� !!!!!

	short			pr_GSS;			//�ਧ��� ��⮢���� � ᥠ��� �裡 1-��⮢, 0-�� ��⮢
									//䠪��᪮� ��������� ��⥭�� 2�� �� �६� �ᥣ� ᥠ�� �裡
	float			P_FACT;			//������, ࠤ
	float			beta_FACT;		//㣮� ����, ࠤ
	float			Fd_FACT;		//ᤢ�� �����, ��� 

								//�ਧ���� ���⭮� �裡 	2�� �� �६� �ᥣ� ᥠ�� �裡
	short			pr_AS;			// !!!!!  �ਧ��� �ਥ��� ᨣ���� �� ��᫥���� ⠪�
									//(�� ࠡ�� � ०��� ��_�1) 1- �� �ਥ�, 0- ���
	short			pr_PD;			//!!!!!!  �ਧ��� �ਥ�� ᨣ���� �� ��᫥���� ⠪�
									//(�� ࠡ�� � ०��� ��_�2) 1- �� �ਥ�, 0- ���
									//�����, �ਭ��� � ��.MO3K � �� 
									//(����� ��।����� ����ﬨ, ᮮ⢥�����騬� ������ 
									//30-� ᥪ㭤���� 横�� ��।�� ����

	short			sost_CC_K2;		//���ﭨ� ᥠ�� �裡 �� ������ �2 (0-7)		

	short			UR_sign_K1;		//�஢��� ᨣ���� �� ������ �1 (0-100) -⠡�� ᨣ���� �1
	short			UR_sign_K2;		//�஢��� ᨣ���� �� ������ �2 (0-100) -⠡�� ᨣ���� �2
	short			PrM_K1;			//����稥 ᨣ���� "��� �1" (1-���� ᨣ���, 0- ��� ᨣ����)
									//(⠡�� �� �ਥ��	�1)	
	short			PrM_K2;			//����稥 ᨣ���� "��� �2" (1-���� ᨣ���, 0- ��� ᨣ����)
									//(⠡�� �� �ਥ��	�2)	
	short			Pr_ZI_K1;		//����稥 ᨣ���� �� ���� � ��������� �����
									//(1-���� ᨣ���, 0- ��� ᨣ����)
									//(⠡�� ��.��	�1)	
	short			Pr_ZI_K2;		//����稥 ᨣ���� �� ��� � ��������� �����
									//(1-���� ᨣ���, 0- ��� ᨣ����)
									//(⠡�� ��.��	�2)	
	short			GL_priem;		//����稥 ᨣ���� "�ਥ�" �� ��室� ���ਨ
									//(1-���� ᨣ���, 0- ��� ᨣ����)
									//(⠡�� �����-�ਥ�)	
	short			GL_CP;			//	����稥 ᨣ���� "��" �� ��室� ���ਨ
									//(1-���� ᨣ���, 0- ��� ᨣ����)
									//(⠡�� �����-��)	
	short			pr_rejim_AS;	//�ਧ��� ���ᮯ஢������� 1-����/0-���



	unsigned short	cr_SEANCE;		//���浪��� ����� ���ᨢ� ������ 横�� ��।�� 
									//0-USHRT_MAX
	short			sum_DCP;		//������⢮ �ਭ���� ᫮� � ���ᨢ� ��
	unsigned int	DCP_K1[SUM_DCP_K1];	//���ᨢ �� ��� ��-�1
	unsigned short	DCP_K2[SUM_DCP_K2];	//���ᨢ �� ��� ��-�2
}obmen_31_41_2t;


typedef struct	{

							//䠪��᪮� ��������� ��⥭�� (��।����� �� ������ ⠪�)

	float			q;		//㣮� ��⠭���� ��⥭�� �� ������� ࠤ
	float			alfa;	//㣮� ��⠭���� ��⥭�� �� �७� ࠤ
	float			beta;	//㣮� ��⠭���� ��⥭�� �� 㣫� ���� ࠤ
	unsigned short	Mispr;	//��᪠ ��ࠢ���� ��������� �� 3.1

							//����� ����⨢���� ����஫� ��������� �� 3.1
	float			sum_K1;		//�ਥ� ᨣ���� �㬬.K1(�ଠ� �)
	float			D_K1;		//�ਥ� ᨣ���� ����� K1(�ଠ� �)
	float			priem_K2;	//�ਥ� ᨣ���� K2	>0 - "�ਥ�",
								//					���� - "" 
	float			CR;			//��	>0 - "��",

	short			USign;		//�஢��� ᨣ���� ��, ��
	unsigned short	Ms1;		//��᪠ ���ﭨ� 1 ⠡� 7
	unsigned short	Ms2;		//��᪠ ���ﭨ� 1 ⠡� 8
	unsigned short	Ms3;		//��᪠ ���ﭨ� 1 ⠡� 9
	short			pr_rejim_AS;//�ਧ��� ���ᮯ஢������� 1-����/0-���

}obmen_31_42_2t;

typedef struct	{
	
	obmen_31_42_2t to42;
	obmen_31_41_2t to41;
	obmen_AK_MO3K_MN3_t toAK;
}obmen_MO3K_MO3_t;
