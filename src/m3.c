#include <unistd.h>
#include <time.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stddef.h>
#include <stdio.h>
#include <sys/mman.h>
#include <sys/pci.h>
#include <sys/osinfo.h>
#include <process.h>
#include <conio.h>
#pragma off (check_stack)
#include <math.h>
#include <sys/psinfo.h>
#include <fcntl.h>
#include <signal.h>
#include <sys/proxy.h>
#include <sys/kernel.h>
#include "../include/tx_drv.h"
#include "../include/Mod_B.h"

float oldKK,deltaKK,beta1,alfa1,grad=180.0/PI;
short oldKOD,deltaKOD,byta2;
float Flt=0;
unsigned short toPR1[8]={0x07C7,0x0000,0x0000,0x0000,0x0000,0x0000,0x8410,0};
struct DefCMD acmd[2]={{0x1028,toPR1},{0x1428,NULL}}; // KC+D[] MK npu6opa 1

void main(int argc, char *argv[])
{	int i,j,k,res;
	int cnt_K2=0;
    pid_t pid_timer;
    timer_t id_timer;
	struct itimerspec timer;
    struct sigevent event;
	unsigned int N_TIMER=0;//���-�� �ࠡ��뢠��� ⠩���
	short TIMER10=0;//����� � ��1.0
	short TIMER41=0;
	float A; //㣮� ���ࠢ�� �� ࠧ����
	struct ispr_mo3k *ispr;
//----- onucaHue gaHHblx npu pa6ome c MK -----//
int short owu6ka,i1;
pid_t pid;
dev_tx_t *dev;
unsigned short Kypc,Ckopocmb,KpeH,DuHT;
unsigned short q=1,ncu=2,mema=3;
float 	C1,C2,C3,C4,C5,C6,C7,C8;
int direction=0;
int TIMESEV,setANT=0,minus_x;
double PSI=0,TETA=0,oldPSI=0,oldTETA=0;
double x,y,x1,y1,C,S,ri,r1,r2,r3,
		x2=0,y2=0;//������ �� ��窠�
double prim,primq,primcos;
float KK=0,KK1=0;	//���� ��ࠡ��
//const AgpecHK=28,AgpecCEB=31,nogAgpecHK=0,nogAgpecCEB=0;// agpeca OY
const AgpecHK=18,AgpecCEB=18,nogAgpecHK=0,nogAgpecCEB=0;// agpeca OY ???(CEB=17,18)
const Ynp_np1=1,HK=2,CEB=0;// No KAH MK
const Cnp1=1,CK1=Cnp1+8,CK2=CK1+20;//cMeweHue gaHHblx B Dout
const Cq=16,C42np1=10;//cMeweHue gaHHblx B Dout
unsigned pci_index=0;
unsigned char s,pewuM_K1;
int		 SIMF[6]={0,0,0,0}; //����稥 ᨬ䮭�� 0,1 - ModA :  2,3 - ModB : 4,5 - sevA
//��� ���-���஢�������:
int A1=0;
float old_RAZN_0=0, old_RAZN_1=0, fUM=0, fDUM=0, fAz=0;

//----- onucaHue daHHblx npu pa6ome c np.4-1,4-2 -----//

	C1=2048./pi;	C2=4096.0/360.0;	C3=180./pi;	C4=C1*Kncu;
	C5=C2*Kncu;		C6=C1*Kq;			C7=C3;		C8=C2*Kq;

    pid_timer = qnx_proxy_attach( 0, 0, 0, -1 );
    if( pid_timer == -1 ) {printf( "Unable to attach proxy." );return;}

    /* Attach to the timer */
    event.sigev_signo = -pid_timer;
    id_timer = timer_create( CLOCK_REALTIME, &event );
    if( id_timer == -1 ) {printf( "Unable to attach timer." );return;}

    timer.it_value.tv_sec     = 1L; //start after X sec
    timer.it_value.tv_nsec    = 0L;
    timer.it_interval.tv_sec  = 0;
    timer.it_interval.tv_nsec = 100*msec;
    timer_settime( id_timer, 0, &timer, NULL );

	create_shmem();
	delay(1000);
	open_shmem();
	printf("\n CTAPT M3\n\n");

	ispr = (struct ispr_mo3k *) & p->to_MO3.to42.Mispr;
	p->pr1_c=0;
	//----- Hacmpouka MaH4ecm.KaH. -----//
	owu6ka=0;dev=OpenTx(pci_index);

	if(regim_kk(dev,Ynp_np1,true)==-1) {owu6ka|=0x4000;}//Heucnp-Mble.owu6ku
	if(regim_ou(dev,HK,AgpecHK,true)==-1) {owu6ka|=0x2000;}
	if(regim_ou(dev,CEB,AgpecCEB,true)==-1) printf("Error OU CEB\n");
	Init_ModB();
	//p->to_MO3.to42.Mispr=0;
	p->toPR1[0]=0x07C7;
	p->M[0]=0;
	p->M[1]=0x000e;
	p->M[2]=0x0000;
	p->M[3]=0x8410;
//	p->M[3]=0xC430; //����祭�� ��

	p->jump=0;

for(;;)//----- CEPBEP -----//
{
 pid=Receive(0,dev->tx_B,N_B*2);s=0;owu6ka&=0xF000;//ucnp-Mble.owu6ku
 if(pid==dev->proxyR[Ynp_np1])s=1;
 if(pid==dev->proxyERR[Ynp_np1])s=2;
 if(pid==dev->proxyR[HK])s=3;
 if(pid==dev->proxyOUT[HK])s=4;
 if(pid==dev->proxyMODE[HK])s=5;
 if(pid==dev->proxyR[CEB])s=6;
 if(pid==dev->proxyOUT[CEB])s=7;
 if(pid==dev->proxyMODE[CEB])s=8;
 if(pid==proxy_RS)s=9;
 if(pid==pid_timer)s=12;


 switch(s)
 {	case 0:owu6ka|=1;break; // HEBEPEH proxy

	case 1://--- ������ ������ �� ��1
		if(KK_end(dev,Ynp_np1,2)==-1){owu6ka|=2;break;}

		p->pr1_c++;
		for(i=0;i<8;i++) p->PR1[i]=dev->tx_B[10+i];
		//for(i=3;i<7;i++) printf(" %d=%04x",i,dev->tx_B[10+i]);printf(" from\n");
		//for(i=3;i<7;i++) printf(" %d=%x",i,toPR1[i]);printf(" to\n");
		//for(i=3;i<8;i++) printf(" %x",p->PR1[i]);printf("\n");

		//if (p->PR1[4]&0x4000) p->to_MO3.to42.priem_K2=1; else p->to_MO3.to42.priem_K2=0;
		/*p->PR1[3]=p->PR1[3]|0x2000; //�� ����
		p->PR1[3]=p->PR1[3]|0x8000; //2018
		p->PR1[4]=p->PR1[4]|0x0800; //TVP SUM*/
		p->PR1[4]=p->PR1[4]|0x00ff; //��譨� ���� ᯨ᪠

		p->to_MO3.to42.Ms1=p->PR1[3];   //���ﭨ� �ਡ�� 1.0
		p->to_MO3.to42.Ms2=p->PR1[4];
		p->to_MO3.to42.Ms3=p->PR1[5];

		ispr->k1 = ((p->PR1[3]&0xFFF0)==0xFFF0) ? 0 : 1;// ���稪� �1
		ispr->k2 = ((p->PR1[4]&0x0F00)==0x0F00) ? 0 : 1;// ���稪� �2 (���)

		// ���४�� ������� ��᫥ ����祭�� � ��.1 (��। ��ࠢ��� �� ����)
		//p->to_MO3.to42.q = (1 - 0.0475) * p->to_MO3.to42.q = 0,9525 * p->to_MO3.to42.q;
		//fAz = (p->PR1[0]-1991)*2/RADtoGRAD * 0,9525;

		// ���४�� ������� ��᫥ ����祭�� � ��.1 (��। ��ࠢ��� �� ����)
		//p->PR1[0] = 0.9525 * (p->PR1[0] - 1991) + 1991; // => 
		p->PR1[0] = 0.9525 * p->PR1[0] + 94.5725; // (0.0475*1991)

		p->Dout41[Cq]=	p->PR1[0];// q
		p->Dout41[Cq+1]=p->PR1[1];// ncu
		p->Dout41[Cq+2]=p->PR1[2];// mema

		if (alfa1>0.251)				p->to_MO3.to42.alfa= 0.258;
		else if (alfa1<-0.251)			p->to_MO3.to42.alfa=-0.255;
			 else if (p->PR1[1]&0x800)	p->to_MO3.to42.alfa=(p->PR1[1]-0xFFF)/12.27/RADtoGRAD;//����
				  else 					p->to_MO3.to42.alfa= p->PR1[1]/C4;

		//ANGLE
	    memcpy(&byta2,&p->Dout41[0],2);	Flt=byta2*pi/(1<<14);	p->simfonia41.Kg=Flt;// printf("Kypc=%8.4f \n",Flt);
		p->to_MO3.to41.P_FACT=(p->Dout41[Cq]-1991)*2/RADtoGRAD+KK+x2;//������+����

		if (p->to_MO3.to41.P_FACT<0) 	p->to_MO3.to41.P_FACT+=2*pi;//������+����
		if (p->to_MO3.to41.P_FACT>2*PI) p->to_MO3.to41.P_FACT-=2*pi;//������+����

		if (p->Dout41[Cq+2]&0x800)	p->to_MO3.to41.beta_FACT=(360-p->Dout41[Cq+2]/C2)/C3; //���� �����
		else	 					p->to_MO3.to41.beta_FACT=	 -p->Dout41[Cq+2]/C1;

		p->to_MO3.to41.beta_FACT+=y2;
		TIMER10=0;//�� ����� � ��1.0
		break;

	case 2://--- ������ ������ � ��1
		if(KK_end(dev,Ynp_np1,2)==-1)owu6ka|=1024;else owu6ka|=4;
		break;

	case 3://--- HK
		SIMF[0]++; //���� ᨬ䮭�� A (HK A)
		if (SIMF[0]==60000) SIMF[0]=0;
		if(ou_read(dev,HK,nogAgpecHK)){owu6ka|=8;break;}
   		if((dev->tx_B[3])!=32)  {owu6ka|=512;printf("error=%d\n",dev->tx_B[3]);break;}
		//printf("ModA simf- "); 	for(j=0;j<dev->tx_B[3]+4;j++) printf("%x ",dev->tx_B[j]);printf("\n");
    	for(j=0;j<15;j++) p->Dout41[j]=dev->tx_B[4+j]; //--- npueM HK

		//printf("\nAdrKach= %x \n",dev->tx_B[1]);
		if((dev->tx_B[1])!=0x11)  break; //���� ��ମ��� ��窨 (ᥩ�� ��������� ��� ASTRA � ����)
		#ifdef ASTRA
			for(j=0;j<32;j++) p->to_MO3.toNT.oHK[j]=dev->tx_B[4+j];
//			if((dev->tx_B[1])!=0x11)  break; //���� ��ମ��� ��窨
//		#else
//			if((dev->tx_B[1])!=0x12)  break; //���� ��ମ��� ��窨
		#endif

		//printf("ModA simf- "); 	for(j=0;j<15;j++) printf("%x ",p->Dout41[j]);printf("\n");
	    KK=p->Dout41[5]*pi/(1<<14);
		KK=KK-pi;
		//if (KK>2*pi) KK=KK-2*pi; //��ॢ��� � ���� � ���
		//	printf("KK=%f ",KK);

//����� 3C-30
		oldPSI = PSI;	oldTETA = TETA;
		if (p->Dout41[3]&0x8000) 	TETA= -(p->Dout41[4])*NAVtoRAD/4; // ��<0
		    else				 	TETA=	p->Dout41[4] *NAVtoRAD/4;
		if (p->Dout41[1]&0x8000) 	PSI = -(p->Dout41[2])*NAVtoRAD/4; // ��<0
		    else				 	PSI =	p->Dout41[2] *NAVtoRAD/4;

		if (p->Dout41[1]==0x8000) PSI=0;	// ? (D)
		if (p->Dout41[3]==0x8000) TETA=0;	// ?

//		if (p->Dout41[7] == 0) PSI=0;	// �� V ��窨 �� �� =0 - ��� ��祪
//		if (p->Dout41[8] == 0) TETA=0;	// �� V ��窨 �� �७� =0 - ��� ��祪

		if (abs(PSI) >1/4)  PSI=oldPSI;		//���� �� ������ ����
		if (abs(TETA)>1/4) TETA=oldTETA;
//		printf("KK=%1.3f PSI=%1.3f(%1.3f) TETA=%1.3f(%1.3f)\n",KK,PSI,PSI*57.32,TETA,TETA*57.32);
//����� 3C-30

	//	printf(" A_simf "); 	for(j=0;j<9;j++) printf("%04x ",p->Dout41[j]);printf("\n");
  		break;

	case 4:owu6ka|=32;break; // HEBEPEH proxy HK

	case 5://--- npueM KY cuHxp HK ---//
		ou_mode_read(dev,HK,0x8000);
		break;

	case 6://--- npueMHuk CEB ---//
		SIMF[4]++; //���� CEB A
		if (SIMF[4]==60000) SIMF[2]=0;
		if(ou_read(dev,CEB,nogAgpecCEB)){owu6ka|=64;break;}
		//if((dev->tx_B[3])!=6){owu6ka|=128;break;}
		for(j=0;j<6;j++) p->CEB[j]=dev->tx_B[4+j]; //--- npueM CEB
		//for(j=0;j<6;j++) printf(" %04x",p->CEB[j]);printf("\n"); //--- npueM CEB
		//printf("%02x:%02x:%02x ", p->CEB[2]>>8,p->CEB[3]>>8,p->CEB[3]&0x00ff);printf("\n");
		break;//--- end npueMHuk CEB ---//

	case 7:case 8:owu6ka|=256;break; // HEBEPEH proxy CEB

	case 9:   //����� � ����
		SIMF[2]++; //����  ModB
		if (SIMF[2]==60000) SIMF[2]=0;

		i=Read_ModB(); //�⠥� ����� �� ��� �
		if (i!=48) break; //�᫨ �� 楫� ����� - ��室

		ispr->nkB  = (Din_ModB[1]==1) ? 0 : 1; //�ਧ��� ������ HK  � ��� �
		ispr->sevB = (Din_ModB[2]==1) ? 0 : 1; //�ਧ��� ������ CEB � ��� �

		if ( (ispr->nkA==1) && (ispr->nkB==0)) { //�᫨ ��� �� � ��� �, �� ���� � ��� � - ���� �� ��� �
			// �����㥬 �� ����樨 �� ��⮪��� �������, �����, �������

			#ifdef ASTRA
				p->to_MO3.toNT.oHK[25]=Din_ModB[3+12]; //�������
				for(j=8;j<12;j++) p->to_MO3.toNT.oHK[11+j]=Din_ModB[3+j]; //���� + ������
				for(j=0;j<11;j++) p->to_MO3.toNT.oHK[j]=Din_ModB[3+j]; //�����㥬 ��⠫�� �����
			#endif

			for(j=0;j<15;j++) p->Dout41[j]=Din_ModB[3+j]; //--- npueM HK

			KK=p->Dout41[5]*pi/(1<<14);
			KK=KK-pi;
			//if (KK>2*pi) KK=KK-2*pi; //��ॢ��� � ���� � ���
			//printf("KK=%1.3f PSI=%1.3f(%1.3f) TETA=%1.3f(%1.3f)\n",KK*57.32,PSI,PSI*57.32,TETA,TETA*57.32);
			//for(j=0; j<32;j++) printf("%04x %04x %04x ", p->to_MO3.toNT.oHK[j], p->Dout41[j], Din_ModB[3+j]);
		}

		if ((ispr->sevA==1) && (ispr->sevB==0))//�᫨ ��� ��� � ��� �, �� ���� � ��� � -> ���� �� ��� �
			for(j=0;j<6;j++) p->CEB[j]=Din_ModB[18+j]; //--- npueM CEB
		//printf("ModB - ");	for(j=0;j<3;j++) printf("%x ",Din_ModB[j]);printf("\n");
		break;

	case 12://��ࠡ��稪 ⠩��� (10 ��)
		N_TIMER++;//���稪 ⨪��
		TIMER41++;
		if (TIMER41>1) //  3/10 Hz
		{
			TIMER10++;//printf("TIMER10=%d\n",TIMER10);
			if (TIMER10<10)	ispr->mo1k=0; //���� ��1.0
			else			ispr->mo1k=1; //��� ��1.0

			if (p->num_com==3) //����� ᥠ�� �裡
			{
				setANT=0;
				p->jump=0;
				p->toPR1[0]=1991;
				p->toPR1[2]=0;
			}

			if (p->num_com==1) //�����⮢�� � ᥠ��� �裡
			{
				KK1=p->from_MO3.from41.P_ANT_1-KK;
				//printf("KK1=%1.4f ANT1=%1.4f KK=%1.4f ANT2=%1.4f ",KK1*57.32,p->from_MO3.from41.P_ANT_1*57.32,KK*57.32,p->from_MO3.from41.P_ANT_2*57.32);
				//if (KK1>4.71225)  KK1=KK1-2*PI;
				//if (KK1<-4.71225) KK1=KK1+2*PI;
				if (KK1> 4.71225) p->jump=-1;
				if (KK1<-4.71225) p->jump=+1;

				if (p->from_MO3.from41.P_ANT_2>p->from_MO3.from41.P_ANT_1)
					if (abs(p->from_MO3.from41.P_ANT_2-p->from_MO3.from41.P_ANT_1)<PI) direction=1; //�� �ᮢ��
					else direction=0;
				else
					if (abs(p->from_MO3.from41.P_ANT_2-p->from_MO3.from41.P_ANT_1)<PI) direction=0; //��⨢ �ᮢ��
					else direction=1;

				if 		((KK1> pi/2)&& (direction)) p->jump=-1; //�������� �� �ᮢ��
				else if ((KK1<-pi/2)&&(!direction)) p->jump+=1; //�������� ��⨢ �ᮢ��
						//else p->jump=0;

				KK1=KK1+2*p->jump*pi;
				//printf("KK1=%f j=%d dir=%d \n",KK1*57.32,p->jump,direction);

				//oldKK=KK1; //��࠭�� ��⠭������� ������ [�� �ᯮ������]
	    		if (p->from_MO3.from41.beta_1>=0)	p->toPR1[2]=-p->from_MO3.from41.beta_1*C1;//���� ����
			    else								p->toPR1[2]=(360+(-p->from_MO3.from41.beta_1*C3))*C2;//

				p->toPR1[0]=KK1*RADtoGRAD/2+1991;//������
				setANT=1;//�뫠 ����ன�� 㣫�� ��। ᥠ�ᮬ
			}
			else
			if (p->num_com==2) //ᥠ�� �裡 ��砫��
			{
				if (!setANT) //�� �஢����� ����ன��
				{
					KK1=p->from_MO3.from41.P_ANT_1-KK;
					if (KK1> 4.71225) p->jump=-1;
					if (KK1<-4.71225) p->jump=+1;

					if (p->from_MO3.from41.P_ANT_2>p->from_MO3.from41.P_ANT_1)
						if (abs(p->from_MO3.from41.P_ANT_2-p->from_MO3.from41.P_ANT_1)<PI) direction=1; //�� �ᮢ��
						else direction=0;
					else
						if (abs(p->from_MO3.from41.P_ANT_2-p->from_MO3.from41.P_ANT_1)<PI) direction=0; //��⨢ �ᮢ��
						else direction=1;

					if 		((KK1> pi/2)&& (direction)) p->jump=-1; //�������� �� �ᮢ��
					else if ((KK1<-pi/2)&&(!direction)) p->jump= 1; //�������� ��⨢ �ᮢ��
						
					setANT=1;//�뫠 ����ன�� 㣫�� ��। ᥠ�ᮬ
					//printf("KK1=%1.4f ANT1=%1.4f KK=%1.4f ANT2=%1.4f \n",KK1,p->from_MO3.from41.P_ANT_1,KK,p->from_MO3.from41.P_ANT_2);
				}
				KK1=p->from_MO3.from41.P_ANT-KK;
				//printf("ANT=%1.3f KK=%1.3f KK1=%1.3f ",p->from_MO3.from41.P_ANT,KK,KK1);
				//if (KK1>4.7)  KK1=KK1-2*PI;
				//if (KK1<-4.7) KK1=KK1+2*PI;
				//printf("KK2=%1.3f ",KK1);
				KK1=KK1+2*p->jump*pi;
				//printf("KK3=%1.3f ",KK1,p->jump);
				//if (KK1>4.7)  {KK1=KK1-2*PI;p->jump=0;}//1225
				//if (KK1<-4.7) {KK1=KK1+2*PI;p->jump=0;}
				//printf("KK=%1.3f PSI=%1.3f(%1.3f) TETA=%1.3f(%1.3f)\n",KK*57.32,PSI,PSI*57.32,TETA,TETA*57.32);
				//printf("KK4=%1.3f j=%d\n",KK1,p->jump);
	//			if (p->from_MO3.from41.beta>=0)	p->toPR1[2]=-p->from_MO3.from41.beta*C1;//���� ����
	//	    	else p->toPR1[2]=(360+(-p->from_MO3.from41.beta*C3))*C2;//

				if (p->Dout41[1]&0x8000) PSI=-(0xffff-p->Dout41[1])*pi/(1<<14);
					else PSI=p->Dout41[1]*pi/(1<<14);

				if (p->Dout41[3]&0x8000) TETA=(0xffff-p->Dout41[3])*pi/(1<<14);
					else TETA=-p->Dout41[3]*pi/(1<<14); //���⮢��
/*
				x=(double)KK1; //������ �� 4-1
				if (x<0) {	x+=2*PI;	minus_x=1;	}
				else 					minus_x=0;

				y=(double)p->from_MO3.from41.beta;
				r1=cos(y);			r3=sin(y);
				r2=r1*cos(x);		r1=r1*sin(x);
				C=cos(-PSI);		S=sin(-PSI);
				x1=C*r2+S*r3;		r3=C*r3-S*r2;
				S=sin(-TETA)*r1+cos(-TETA)*r3;
				y1=asin(S);

				prim=x1/cos(y1);
				if (prim>1) prim=1;

				x1=acos(prim);
				if (abs(x1-x) > abs(2*PI-x1-x)) x1=2*PI-x1;
				if (minus_x==1) x1=x1-2*PI;

				x2=x-x1; //����� �� x
				y2=y-y1; //����� �� y
*/
				x1=KK1;
				y1=p->from_MO3.from41.beta;
				// printf("KK=%3.1f x0=%3.1f y0=%3.1f PSI=%3.1f TETA=%3.1f x1=%3.1f y1=%3.1f\n\n",
						// KK*grad,x*grad,y*grad,PSI*grad,TETA*grad,x1*grad,y1*grad);

				p->toPR1[0]=x1*RADtoGRAD/2+1991;//������
				//printf("num_com = 2: Az= %x\n",p->toPR1[0]);
				if (y1>=0)	p->toPR1[2]=-y1*C1;//���� ����
		    		else 	p->toPR1[2]=(360+(-y1*C3))*C2;//
			}
			else
	    	//if ((p->num_com==4)||(p->num_com==5)) //4-� ��� 5-� ������� �� 4.2
	    	if (p->num_com==4) //4-� ������� �� 4.2
			{	//�ࠢ����� ��. 1.0 �� 4.2
				//����
				//printf("Az=%f Um=%f ",p->from_MO3.from42.q,p->from_MO3.from42.beta);
		        //for(i=0;i<3;i++) printf("  %x",toPR1[i]);printf("   to  \n");
				KK1=p->from_MO3.from42.q;//-KK;//������
				//०�� ���-���஢������� (��)
				if (p->from_MO3.from42.Rejim_AS==1)
				{
					p->to_MO3.to42.pr_rejim_AS=1;

					//if (p->U.SUM_4 > 1e11)
					if (p->to_MO3.to41.UR_sign_K1 > 49) // 39
					{
					// �� �� �������:
						//if ((fabs(p->U.RAZN_0) > 0.3) && (old_RAZN_0 != p->U.RAZN_0))
						if (fabs(p->U.RAZN_0) > 0.3)	// && (fabs(p->U.RAZN_0) < 3)
						{
							//old_RAZN_0 = p->U.RAZN_0;

							A1 = p->U.RAZN_0; //* 3;	// delta Az (kod)
							p->toPR1[0] = (p->PR1[0]&0x0fff) - A1;

							A1=0;
						}
						// �� �� ��
						//if ((fabs(p->U.RAZN_1) > 0.3) && (old_RAZN_1 != p->U.RAZN_1))
						if (fabs(p->U.RAZN_1) > 0.3) // && (fabs(p->U.RAZN_1) < 3)
						{
							//old_RAZN_1 = p->U.RAZN_1;
							if (p->PR1[2]&0x800)	fUM =  (360 - p->PR1[2]/C2)/C3; //�� ��� -> � ࠤ.
							else					fUM = -(p->PR1[2]/C1);

							fDUM = 0.007 * p->U.RAZN_1; // delta UM ࠤ (0.007ࠤ=0.4��) [1��=0.0175ࠤ]
							fUM = fUM - fDUM;

							if (fUM >= 0) p->toPR1[2] =	-fUM*C1; //��ॢ�� � ���
							else 		  p->toPR1[2] = (360 - fUM * C3) * C2;

							fUM=0;	fDUM=0.;
						}
					}
				//����� ०��� ���-���஢������� (��)
				}
				else //�᫨ �� ��
				{
					if (KK1==0)
					{// �� ࠡ�� � �����묨 ᪮���ﬨ ��祪 ���� �᫮��� � ���� else
					// �����
						beta1=p->from_MO3.from42.beta-PSI;
						if (beta1>=0)	p->toPR1[2]=-beta1*C1;//���� ����
						else 			p->toPR1[2]=(360+(-beta1*C3))*C2;//

						alfa1=p->from_MO3.from42.alfa-TETA;
						if (alfa1>=0)	p->toPR1[1]=alfa1*C4;//KPEH
						else 			p->toPR1[1]=0xFFF+(alfa1*RADtoGRAD)*12.27;
					}
					else
					{
						if (p->from_MO3.from42.beta>=0)	p->toPR1[2]=-p->from_MO3.from42.beta*C1;//���� ����
						else 							p->toPR1[2]=(360+(-p->from_MO3.from42.beta*C3))*C2;//

						if (p->from_MO3.from42.alfa>=0)	p->toPR1[1]=p->from_MO3.from42.alfa*C4;//KPEH
						else 							p->toPR1[1]=0xFFF+(p->from_MO3.from42.alfa*RADtoGRAD)*12.27;
					}
					p->toPR1[0]=KK1*RADtoGRAD/2+1991;//������
				}
				p->to_MO3.to42.pr_rejim_AS=p->from_MO3.from42.Rejim_AS;

				//	printf("com=4: Az= %x  KK=%1.2f  KK1=%1.2f\n",p->toPR1[0], KK, KK1);
				//	printf("AK: Peleng= % 2.2f  AKPeleng= % 2.2f  KK1 Korr= % 2.2f\n", KK1, (KK1-KK), (AKPeleng + AKPeleng * 0.0475));
			} // p->num_com==4

			if (p->num_com==301) //
			{	//
    			if (p->from_MO3.fromAK.beta>=0)	p->toPR1[2]=-p->from_MO3.fromAK.beta*C1;//���� ����
		    	else 							p->toPR1[2]=(360+(-p->from_MO3.fromAK.beta*C3))*C2;//

				KK1 = p->from_MO3.fromAK.Peleng - KK;
				if (KK1> 4.71225) KK1=KK1-2*PI;
				if (KK1<-4.71225) KK1=KK1+2*PI;	
				//printf("Peleng=%2.2f KK=%1.2f KK1=%1.2f\n", p->from_MO3.fromAK.Peleng, KK, KK1);
				p->toPR1[0]=KK1*RADtoGRAD/2+1991;//������
				//printf("com=301: Az= %0X  Peleng=%2.2f  KK=%1.2f  KK1=%1.2f\n",p->toPR1[0], p->from_MO3.fromAK.Peleng, KK, KK1);
			}
				//-------------------------------------------------------------
			TIMER41=0;
			if (SIMF[1]<SIMF[0]) ispr->nkA=0; //���� ᨬ� HK A
			else 				 ispr->nkA=1; //��� ᨬ� HK A

			SIMF[1]=SIMF[0];
 			if (SIMF[3]<SIMF[2]) ispr->cvsB=0; //����
			else 				 ispr->cvsB=1; //��� ����,���,��

			SIMF[3]=SIMF[2];
			if (SIMF[5]<SIMF[4]) ispr->sevA=0; //���� ᥢ A
			else 				 ispr->sevA=1; //���

			SIMF[5]=SIMF[4];
			if ((ispr->nkA==1)&&(ispr->nkB==1)) p->Dout41[24]=0;
			else 								p->Dout41[24]=1;
		} //����� 3-� ����
		//-------------------------- 10 Hz -------------------------
		p->toPR1[3]=p->M[0];		p->toPR1[4]=p->M[1];
		p->toPR1[5]=p->M[2];		p->toPR1[6]=p->M[3];
		for(i=0;i<3;i++) p->toPR1[i]=p->toPR1[i]&0x0fff;
		//-------------------------- 1 Pr -------------------------
		for(i=0;i<8;i++) toPR1[i]=p->toPR1[i];
		
		toPR1[0] = p->toPR1[0] * 1.0475 - 94.5;
		//printf("  p->toPR1=%x\n",p->toPR1[3]);
		//for(i=0;i<3;i++) printf("  %x",p->toPR1[i]);	printf("   to  \n"); // ���� 㣫�� -> � �.
		
		//for(i=3;i<4;i++) printf("  %x",p->toPR1[i]);printf("   to  \n");
		//printf("toPR1=%x from42=%f\n",toPR1[2],p->from_MO3.from41.beta);

	 	if((KK_frame(dev,Ynp_np1,2,acmd))==-1){owu6ka|=16;break;}

		if (ispr->nkA==1) 	Write_ModB(); //�᫨ ��� ������樨 ����� � ����� �
		else if (N_TIMER&1) Write_ModB();//���� ���� 5 ��
		break;
 }// ----- end switch
} // ----- end CEPBEP for(;;)
}//----- end main()
