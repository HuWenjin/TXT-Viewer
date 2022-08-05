/*
 *@author: HAH (BiliBili: iccery)
 */
#ifndef _CMD_PARSER_H_
#define _CMD_PARSER_H_

#include "sys.h"
#include "stdbool.h"


// void my_func(PCBNode_t *pcb, int argc, char argv[][COMMAND_MAX_ARG_LEN]);
#define MY_SETUP        if(pcb->state == SETUP) { \
	
#define SEUP_END     }

#define MY_LOOP         pcb->state = LOOP;  \
						if(pcb->state == LOOP) { \
							
#define LOOP_END     }

#define PARSER_STR_BUF_SIZE  50
#define COMMAND_MAX_ARGC 5
#define COMMAND_MAX_ARG_LEN 10


typedef enum
{
	COMMAND_WAIT,
	COMMAND_START,
	COMMAND_RUNING,
	COMMAND_CLOSE
} cmd_state_t;

typedef enum
{
	BLOCKING,
	SETUP,
	LOOP,
} process_state_t;

typedef struct PCBNode PCBNode_t;
typedef void (*pcb_main_f)(PCBNode_t *pcb, int argc, char argv[][COMMAND_MAX_ARG_LEN]);


struct PCBNode {
	process_state_t state;
	char *name;
	pcb_main_f main;
	u8 pid;
	u8 argc;
	char argv[COMMAND_MAX_ARGC][COMMAND_MAX_ARG_LEN];
	struct PCBNode *next;
};



typedef struct cmd_Parser cmd_Parser_t;

struct cmd_Parser{
	
	char *name;
	u8 updata;//�Ƿ�õ����ַ�
	
	//cmd״̬
	cmd_state_t state;
	
	u8 echo_enable;//����
	
	//������
	u8 pid_cnt;
	
	//���ַ�
	u8 getchar;
	//�����ַ�����
	u8 str_idx;
	
	//pcb_headҲ�����洢ǰ̨����
	PCBNode_t pcb_head;
	char cmd_strbuf[PARSER_STR_BUF_SIZE];
	void (*run)(cmd_Parser_t *cmd_parser);
	
	//�ӿڣ���Ҫʵ����Щ��������ʾ��������������ʾ����txtViewer������ģʽ
	//��ӡһ���ֽ�
	void (*print_oneChar)(cmd_Parser_t *cmd_parser, char str);
	//�˸����
	void (*Backspace)(cmd_Parser_t *cmd_parser);
	//��ʽ����ӡ�ַ�������ʾ��
	void (*printf)(char *fmt, ...);
};

extern cmd_Parser_t cmd_parser;

void cmd_getChar(cmd_Parser_t *cmd_parser, char data);

void cmd_Parser_Init(cmd_Parser_t *cmd_parser, char* name);
void cmd_Parser_Start(cmd_Parser_t *cmd_parser);
void cmd_Parser_Close(cmd_Parser_t *cmd_parser);
void cmd_RegisterFunc(cmd_Parser_t *cmd_parser, PCBNode_t *pcb, char* name , pcb_main_f func);


//test
void cmd_test_init(void);

#endif


