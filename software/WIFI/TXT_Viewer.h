/*
 *@author: HAH (BiliBili: iccery)
 */
#ifndef _TXT_VIEWER_H_
#define _TXT_VIEWER_H_

#include "sys.h"
#include "stdbool.h"
#include "string.h"


typedef enum
{
	NORMAL,
	AUTO_BREAKLINE,
	CONSOLE_PRINT,
} p_mode_t;

typedef struct disp_controlBlock{
	//��ʼ��ʾ�ַ�������ֵ��Ҳ������Ļ�е�һ����ʾ���ַ��ڻ����е�λ��
	u16 start_charIdx;
	//�����ַ�������ֵ
	u16 store_charIdx;
	//���λ��
	u16 cursor_idx;
}disp_cb_t;

typedef struct txtViewer txtViewer_t;

struct txtViewer{
	p_mode_t process_mode;
	//Ϊ�˷���������룬��ʹ�ü���ģʽʱ��������һ��һ���ַ������ȥ�ģ��������л�����������ʾ����ͨģʽ������з�����û���κ��ַ��ǲ�����ʾ�����հ׵�
	u8 keyboard_mode;
	u8 cmd_mode;
	u8 filterOut_char;
	s16 txt_ofsetX;
	s16 txt_ofsetY;
	u8 cursor_enable;
	u8 scroll_anim;
	u8 scroll_enable;
	//�����γ��ж�������¼ÿ�д�������ַ�����
	u16 processd_cnt;
	//��������
	u16 cursor_lineY;
	u16 cursor_lineX;
	u8 win_boundary;
	u8 getchar;
	u8 input_updata;
	u8 loop_show;
	s16 scroll_pixel;
	s16 window_x;
	s16 window_y;
	s16 window_h;
	s16 window_w;
	u8 char_h;
	u8 char_w;
	char *data_buf;
	u16 buf_size;
	disp_cb_t disp_cb;
	void (*process)(txtViewer_t *viewer);
	void (*run)(txtViewer_t *viewer);
	//��ĩβ��ӡ
	void (*printf)(txtViewer_t *viewer, char *fmt, ...);
};

extern txtViewer_t txtViewer;

void txt_test_open(void);


void txtViewer_init(txtViewer_t *viewer, int size, s16 win_x, s16 win_y, p_mode_t p_mode);
void txtViewer_getChar(txtViewer_t *viewer, char data);
void txtViewer_setWindow(txtViewer_t *viewer, u8 w, u8 h );
//�л��ַ�Դ
void txtViewer_changeSource(txtViewer_t *viewer, txtViewer_t *new_source);
//�л�������
void txtViewer_changeProcessMode(txtViewer_t *viewer, p_mode_t p_mode);
//�ڹ��ɾ��
void txtViewer_CursorDeleteChar(txtViewer_t *viewer);
//�ڹ�����
void txtViewer_CursorAddChar(txtViewer_t *viewer, char data);
//��ĩβɾ��һ���ַ�������cmd
void txtViewer_DeleteLastStoreChar(txtViewer_t *viewer);
#endif
