//----- M3_B.c -----//  12.04.18
//----- np.3.1 u3g.3u30.0: y3.A->y3.B  -----//
//----- CEPBEP -----//
#include <unistd.h>
#include <time.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stddef.h>
#include <stdio.h>
#include <sys/mman.h>
#include <sys/osinfo.h>
#include <process.h>
#include <conio.h>
#include <math.h>
#include <sys/psinfo.h>
#include <fcntl.h>
#include <signal.h>
#include <sys/proxy.h>
#include <sys/kernel.h>

#include "../include/tx_drv.h"
#include "../include/my_pcs.h"


void main(int argc, char *argv[]) {

int i, j, k, res, errHK=0, errCEB=0;
pid_t pid_timer;
timer_t id_timer;
struct itimerspec timer;
struct sigevent event;
pid_t proxy_RS=0;
//----- onucaHue gaHHblx npu pa6ome c MK -----//
int short owu6ka,i1;
pid_t pid;
dev_tx_t *dev;

//const AgpecHK=28,AgpecCEB=31,nogAgpecHK=0,nogAgpecCEB=0;// agpeca OY ???(CEB=17,18)
const AgpecHK=28,AgpecCEB=18,nogAgpecHK=0,nogAgpecCEB=0;// agpeca OY ???(CEB=17,18)
const HK=2,CEB=0;// No KAH MK
unsigned pci_index=0;
unsigned char s;
unsigned short Dout[24];
// <0>=0xba, <1>=0/1 -����稥 ��, <2-16> -��, <17>=0/1 -����稥 ���, <18-23> -���

    pid_timer = qnx_proxy_attach( 0, 0, 0, -1 );
    if( pid_timer == -1 ) {
      printf( "Unable to attach proxy." );
      return;
    }
    // Attach to the timer
    event.sigev_signo = -pid_timer;
    id_timer = timer_create( CLOCK_REALTIME, &event );
    if( id_timer == -1 ) {
      printf( "Unable to attach timer." );
      return;
    }
    timer.it_value.tv_sec     = 1L; //start after X sec
    timer.it_value.tv_nsec    = 0L;
    timer.it_interval.tv_sec  = 0;
    timer.it_interval.tv_nsec = 100000000;
    timer_settime( id_timer, 0, &timer, NULL );


//----- ����ன�� ������ RS-422 -----//
// �஢�ઠ ����᪠ �ࠩ��� ����� ��� ���-3-1
	pid_drv=get_pid_process("PCS",CVS_NODE);
	if (!pid_drv) {
		printf("!!! �ࠩ��� �� ����饭\n");
		exit(-1);
	}

// ���樠������ ������ ��� ��� �裡 � ���3.1-A
	init_pcs_s.type=1;
	init_pcs_s.cnl=1;				// ����� ������ ���
	init_pcs_s.speed=19200;			// ᪮���� ��।�� ������
	init_pcs_s.b_info=8;			// ���-�� ��� � ���ଠ樮���� ����
	init_pcs_s.b_StrStp=1;			// ���-�� �⮯-���
	init_pcs_s.b_prt='E';			// ����稥 � ⨯ ����� (�⭮���) ����
	init_pcs_s.dev=0; 				// ⨯ �-�� (0 - ����� RS �����)
	init_pcs_s.lvl_inp=48;			// �஢��� ���������� FIFO �� ���뢠���

	i=Send(pid_drv,&init_pcs_s,&init_pcs_r,sizeof(init_pcs_s),sizeof(init_pcs_r));
	if (i==-1) printf("��� ��饭�� � �ࠩ��஬\n");
	if (init_pcs_r.type==1)
		if (init_pcs_r.status!=0) {
			printf("!!! ���樠������ ������ 1 �� ��諠\n");
			exit(-1);
		}
	printf("���樠������ ������ 1 ��諠\n");
// ���� ������ ��� ��� �裡 � ���3.1-A
	start_pcs_s.type=2;
	start_pcs_s.cnl=1;
	start_pcs_s.ID_P=getpid();

	printf("my_id= %d\n",start_pcs_s.ID_P);
	Send(pid_drv,&start_pcs_s,&start_pcs_r,sizeof(start_pcs_s),sizeof(start_pcs_r));
	if (start_pcs_r.type==2) {
		if (start_pcs_r.status==-1) {
			printf("!!! ���� ������ 1 �� �믮����\n");
			exit(-1);
		}
		else { proxy_RS=start_pcs_r.Proxy;
		  printf("���� ������ 1 �믮����, proxy=%d\n", proxy_RS);
		}
	}
//----- Hacmpouka MaH4ecm.KaH. -----//
//owu6ka=0;
dev=OpenTx(pci_index);
if(dev==NULL) // ???
	{owu6ka=-1;//--- pa6oma 6e3 MK ---//
 	printf("\nowu6ka MK=%d",owu6ka);fflush(stdout);
	}//--- end pa6oma 6e3 MK ---//
//if(regim_ou(dev,HK,AgpecHK,true)==-1) {owu6ka|=0x2000;}
//if(regim_ou(dev,CEB,AgpecCEB,true)==-1) {owu6ka|=0x1000;}
if(regim_ou(dev,HK,AgpecHK,true)==-1) printf("Error OU HK\n");
if(regim_ou(dev,CEB,AgpecCEB,true)==-1) printf("Error OU CEB\n");

Dout[0]=0xba;
for(i=1;i<24;i++) Dout[i]=0;

//----- �������� ᮮ�饭�� �� �� � ����ᮢ �� RS
for(;;)//----- CEPBEP -----//
{
// pid=Receive(0,dev->tx_B,N_B*2);s=0;owu6ka&=0xF000;//ucnp-Mble.owu6ku
	pid=Receive(0,0,0); s=0;
	if(pid==dev->proxyR[HK]) s=1;
	if(pid==dev->proxyOUT[HK]) s=2;
	if(pid==dev->proxyMODE[HK]) s=3;
	if(pid==dev->proxyR[CEB]) s=4;
	if(pid==dev->proxyOUT[CEB]) s=5;
	if(pid==dev->proxyMODE[CEB]) s=6;
	if(pid==pid_timer) s=7;
	if(pid==proxy_RS) s=8;

	switch(s)
	{
	case 1://--- npueMHuk HK ---//
		if(ou_read(dev,HK,nogAgpecHK)) {break;} //�訡�� �⥭��

		if((dev->tx_B[3])!=32)  {owu6ka|=512;printf("error: read= %d\n",dev->tx_B[3]);break;}

//		#ifdef ASTRA
		if((dev->tx_B[1])!=0x11)  break; //���� ��ମ��� ��窨 (ᥩ�� ��������� ��� ASTRA � ����)
//		#else
//			if((dev->tx_B[1])!=0x12)  break; //���� ��ମ��� ��窨
//		#endif

		//if((dev->tx_B[3])!=15) {break;}			//���-�� ᫮� != 15
		for(j=0;j<15;j++) Dout[3+j]=dev->tx_B[4+j]; //--- npueM HK
		//puts("HK: "); for(j=0;j<32;j++) printf(" %Xh",dev->tx_B[4+j]); printf("\n"); //--- npueM HK
		errHK=0; Dout[1]=1; //���� ᨬ䮭��

//		printf("���䮭��\n");
//		for(i=0;i<3;i++)  printf(" %04x",Dout[i]); printf("\n");
//		for(i=3;i<18;i++) printf(" %04x",Dout[i]); printf("\n");

		Dout[3+12]=dev->tx_B[4+25]; //�������
		for(i=8;i<12;i++) Dout[3+i]=dev->tx_B[4+11+i]; //���� + ������

//		for(i=4;i<18;i++) printf(" %04x",Dout[i]); printf("\n");

	break;//--- end npueMHuk HK ---//

	case 2: break; // HEBEPEH proxy HK

	case 3://--- npueM KY cuHxp HK ---//
		ou_mode_read(dev,HK,0x8000);
	break;//--- end npueM KY cuHxp HK ---//

	case 4: //--- npueMHuk CEB ---//
		if(ou_read(dev,CEB,nogAgpecCEB)) {break;} //�訡�� �⥭��

		if((dev->tx_B[3])!=6) {	break;	}			 //���-�� ᫮� != 6
		for(j=0;j<6;j++) Dout[18+j]=dev->tx_B[4+j]; //--- npueM CEB
		errCEB=0; Dout[2]=1;
		//	printf("���\n");
	break; //--- end npueMHuk CEB ---//

	case 5:case 6: break; // HEBEPEH proxy CEB

	case 7: //--- �� ⠩����
		//	for(i=0;i<4;i++) printf(" %x",Dout[i]);

		//	�஢�ઠ ��।������� ������
		//printf("HK: %Xh CEB: %Xh |", Dout[1], Dout[2]);
		//printf(" errNK = %x  errSEV= %x",errHK,errCEB);
		//printf("\n");
		//for(j=0;j<6;j++) printf("  %Xh", Dout[18+j]);
		//printf("  %02x:%02x:%02x\n\n", Dout[20]>>8,Dout[21]>>8,Dout[21]&0x00ff);
		//	printf("\n");

		errHK++; errCEB++;
		if(errHK>5)  Dout[1]=0;
		if(errCEB>5) Dout[2]=0;
	break;

	case 8: //--- ����� �� ���3.1-A
		//�ਥ� ������ �� ������ 1 ���
		rd_cpcs_s.type=4;
		rd_cpcs_s.cnl=1;
		Send(pid_drv,&rd_cpcs_s,&rd_cpcs_r,sizeof(rd_cpcs_s),sizeof(rd_cpcs_r));

		//printf ("From PCS_M rd_cpcs_r.type=%d rd_cpcs_r.status= %d\n",rd_cpcs_r.type,rd_cpcs_r.status);
		//printf ("rd_cpcs_s.cnl=%d   rd_cpcs_r.cnt= %d\n", chan_rd, rd_cpcs_r.cnt);
		//for(i=0;i<rd_cpcs_r.cnt;i++) printf(" %2x",rd_cpcs_r.uim.dt[i]); printf("\n");

		if ((rd_cpcs_r.cnt==2) && (rd_cpcs_r.uim.dt[0]==0xab) && (rd_cpcs_r.uim.dt[1]==0xba)) {
			//��।�� ������ � ����� 1 ���
			wr_cpcs_s.type=5;
			wr_cpcs_s.cnl=1;
			wr_cpcs_s.cnt=48; //4
			//for(i=0;i<24;i++) {wr_cpcs_s.uom.dt[i*2]=Dout[i]&0xff;
			//					 wr_cpcs_s.uom.dt[i*2+1]=(Dout[i]>>8)&0xff;}
			//for(i=0;i<24;i++) wr_cpcs_s.uom.dt[i]=Dout[i];//
			memcpy(&wr_cpcs_s.uom.dt, &Dout, sizeof(Dout));

//			for(i=0;i<24;i++) printf("d%d=%Xh  ", i,Dout[i]);	printf("\n");
//			for(i=0;i<48;i++) printf("w%d= %Xh  ", i,wr_cpcs_s.uom.dt[i]);	printf("\n");
//			for(i=0;i<48;i++) printf(" %02x", wr_cpcs_s.uom.dt[i]);	printf("\n");

			Send(pid_drv,&wr_cpcs_s,&wr_cpcs_r,sizeof(wr_cpcs_s),sizeof(wr_cpcs_r));
		}
	break;

	} // ----- end switch (s)

} // ----- end CEPBEP for(;;)
}//----- end main()
