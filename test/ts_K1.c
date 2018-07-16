//****************************** test ЦВС-3.1 **********************************
// Входные параметры --> пар.ts + Size RAM + Режим:XXX + 
//   + BaseLTP1, BaseCOM1, BaseCOM2 +
//   + [Uzel], [BaseLPT1], [BaseCOM1], [BaseCOM2]
//---------------------------------------------------------------------------
// Copyright (c) 2000 Granit (Fomin D.A.) - Version 1.0
//***************************************************************************
#include <unistd.h>
#include <sys/osinfo.h>
#include <time.h>
#include <process.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/dev.h>
#include "ts.h"
#include "../include/my_pcs.h" // "my_pcs.h"

char test_K1[5][4]={{0x9F, 0x08},
					{0xB8, 0x00, 0x00, 0x40},
					{0xB8, 0x40, 0x00, 0x40},
					{0x86, 0x41},
					{0x96, 0x60, 0x00}};
char nastroika[]={0xB8, 0x00, 0x00, 0x00, 0x9f, 0x08};
char otvet[]={0xB8, 0x00, 0x00, 0x40};
pid_t pid_parent=0, proxy_DRV=0, proxy_DRV1=0, proxy_DRV2=0, proxy_DRV_K=0;
int msg=25,rmsg,i,rez_BU_wr=0,rez_BU_rd=0,cntl_code=0,ii=1;
int chan1=8, chan2=2, chan_rd, chan_wr; // chan2 - связь со стендом
int chanK=8; 			// chan1 - связь с устройством (УПОС(8) или ПОСТ-3Ц(3))
unsigned short form_receive[2],form_send[2],form_send_24[7],add_value;
int St_time, Fin_time; //прием ПЦС


//*********************************** MAIN **********************************
void main(int argc, char *argv[])
{
arginit(argc,argv,"тест модуля 686E\n");
//argp("BL=", "%x", &blpt1, "базовый адрес LPT");
//argp("N1=", "%s", name_dev1, "Имя устройства N1");
  
oopen();
     rez=-1; podswID();	rez=1;

//------------------------------------
// Проверка запуска драйвера модуля ПЦС ЦВС-3-1
	pid_drv=get_pid_process("PCS",CVS_NODE);
	if (!pid_drv) {
		form_send[0]=0xFFFF; //form_send[1]=IND_BU; //Драйвер не запущен
		printf("!!! Драйвер не запущен\n"); err++; rez=2;
		exit(rez);
	} 

// Инициализация канала ПЦС для связи с каналом chan1 (УПОС или ПОСТ-3Ц)
	init_pcs_s.type=1;
	init_pcs_s.cnl=chan1;			// номер канала ПЦС
	init_pcs_s.speed=19200;			// скорость передачи данных
	init_pcs_s.b_info=8;			// кол-во бит в информационном байте
	init_pcs_s.b_StrStp=1;			// кол-во стоп-бит
	if(chan1==8)
	  init_pcs_s.b_prt='E';			// наличие и тип паритета (четность) УПОС
	if(chan1==3)
	  init_pcs_s.b_prt=0;			// наличие и тип паритета (нет) ПОСТ-3Ц
	init_pcs_s.dev=0; 				// тип у-ва (0 - обычный RS канал) 
	init_pcs_s.lvl_inp=45;			// уровень заполнения FIFO до прерывания

	i=Send(pid_drv,&init_pcs_s,&init_pcs_r,sizeof(init_pcs_s),sizeof(init_pcs_r));
	if (i==-1) printf("Нет общения с драйвером\n");
	if (init_pcs_r.type==1) 
		if (init_pcs_r.status!=0) {
			printf("!!! Инициализация канала %d не прошла\n", chan1);
			exit(2);
		}
	printf("Инициализация канала %d прошла\n", chan1);

// Старт канала chan1
	start_pcs_s.type=2;
	start_pcs_s.cnl=chan1;
	start_pcs_s.ID_P=getpid();

	printf("my_id= %d\n",start_pcs_s.ID_P);
	Send(pid_drv,&start_pcs_s,&start_pcs_r,sizeof(start_pcs_s),sizeof(start_pcs_r));
	if (start_pcs_r.type==2) {
		if (start_pcs_r.status==-1) {
			printf("!!! Старт канала %d не выполнен\n", chan1);
			exit(2);
		} 
		else { proxy_DRV1=start_pcs_r.Proxy;
		  printf("Старт канала %d выполнен, proxy=%d\n", chan1, proxy_DRV1);
		}
	}       

// Очистка канала chan1
	rd_cpcs_s.type=4;
	rd_cpcs_s.cnl=chan1;
	Send(pid_drv,&rd_cpcs_s,&rd_cpcs_r,sizeof(rd_cpcs_s),sizeof(rd_cpcs_r));
// Настройка канала K1 или K2
  // Передача кода настройки в канал 8 ПЦС (УПОС)
	wr_cpcs_s.type=5;
	wr_cpcs_s.cnl=chanK;
	wr_cpcs_s.cnt=6;
//	nastroika[3]=0; // 0-УПОС, 1-ПОСТ-3Ц
	for(i=0;i<6;i++) wr_cpcs_s.uom.dt[i]=nastroika[i];
	Send(pid_drv,&wr_cpcs_s,&wr_cpcs_r,sizeof(wr_cpcs_s),sizeof(wr_cpcs_r));
	printf("Настройка канала =");
	for(i=0;i<6;i++) printf(" %02x",wr_cpcs_s.uom.dt[i]); printf("\n");
  // Прием подтверждения настройки
	delay(100);
	rd_cpcs_s.type=4;
	rd_cpcs_s.cnl=chanK;
	Send(pid_drv,&rd_cpcs_s,&rd_cpcs_r,sizeof(rd_cpcs_s),sizeof(rd_cpcs_r));
	printf("Ответ =");
	for(i=0;i<rd_cpcs_r.cnt;i++) printf(" %02x",rd_cpcs_r.uim.dt[i]); printf("\n");

  // Передача кода проверки (2) в канал 8 ПЦС (УПОС)
	wr_cpcs_s.type=5;
	wr_cpcs_s.cnl=chan1;
	wr_cpcs_s.cnt=4;
	for(i=0;i<4;i++) wr_cpcs_s.uom.dt[i]=test_K1[2][i];
	Send(pid_drv,&wr_cpcs_s,&wr_cpcs_r,sizeof(wr_cpcs_s),sizeof(wr_cpcs_r));
	printf("Тест канала К1(2) =");
	for(i=0;i<4;i++) printf(" %02x",wr_cpcs_s.uom.dt[i]); printf("\n");
	delay(100);
  // Передача кода проверки (3) в канал 8 ПЦС (УПОС)
	wr_cpcs_s.type=5;
	wr_cpcs_s.cnl=chan1;
	wr_cpcs_s.cnt=2;
	for(i=0;i<2;i++) wr_cpcs_s.uom.dt[i]=test_K1[3][i];
	Send(pid_drv,&wr_cpcs_s,&wr_cpcs_r,sizeof(wr_cpcs_s),sizeof(wr_cpcs_r));
	printf("Тест канала К1(3) =");
	for(i=0;i<2;i++) printf(" %02x",wr_cpcs_s.uom.dt[i]); printf("\n");  
  // Прием ответного кода
	delay(3000);
	rd_cpcs_s.type=4;
	rd_cpcs_s.cnl=chan1;
	Send(pid_drv,&rd_cpcs_s,&rd_cpcs_r,sizeof(rd_cpcs_s),sizeof(rd_cpcs_r));
	printf("Ответ =");
	for(i=0;i<rd_cpcs_r.cnt;i++) printf(" %02x",rd_cpcs_r.uim.dt[i]); printf("\n");
	for(i=0;i<rd_cpcs_r.cnt;i++) if (rd_cpcs_r.uim.dt[i] != test_K1[4][i]) err++;
	if (rd_cpcs_r.uim.dt[1] != 0) 
	{
		printf("otv OK \n");
		printf("CVS3.1 - A\n");
	    system("//9/home/cvs_a");
	}
	else 
	{
		printf("otv not OK \n");
		printf("CVS3.1 - B\n");
		system("//9/home/cvs_b");
	}
//------------------------------------

  if(err!=0) rez=2;
  else rez = 1;
printf("Rez=%d\n",rez);
  oclose(); exit(rez);
} //*************************************************************************
