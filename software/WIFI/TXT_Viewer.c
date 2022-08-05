/*
 *@����: HAH (BiliBili: iccery)
 *
 *@��ʾ������ַ���������:char *buf = "he\rllo,th\ris is a test.\ncan you see something here?\nIf you can see some words\n
 *                                     This test may have succeeded!\n1\n2\n3\n4\n5\n6\n7\n8\n9\n10\n"
 *
 *               3�ֽ�����ʽ�������������������'\r'��:
 *
 *       NORMAL              AUTO_BREAKLINE           CONSOLE_PRINT
 * +----------------+      +----------------+      +----------------+ 
 * |hello��this is a|      |hello��this is a|      |5               |
 * |can you see some|      |test. can you se|      |6               |
 * |If you can some |      |e something here|      |7               |
 * |This test may ha|      |If you can see s|      |8               |
 * |1               |      |ome words       |      |9               |
 * |2               |      |This test may ha|      |10              |
 * +----------------+      +----------------+      +----------------+ 
 *@���ܣ�
 *    1��3�ֽ�����           2��CONSOLE_PRINT�������Զ���
 *    3�����봰�ڸ���        4���������ô�С
 *    5����������λ��        6�����ڷָ��ַ�
 *    7����������ģʽ        8���ı��ַ�����Դ
 *    9�����ڸ������Զ���    10�������ַ�����
 *    11������ַ�����       12����ʼ����ӡ
 *    13��ȫ�ֶ�������
 *@���ƣ�
 *       �������ѭ���洢���Ի��з���β��һ�������ַ���Ϊһ���������С������洢λ�ô�����ʾ��ʼ����λ�ü���Ϊ�ռ���Ҫ���ǣ����ڴ洢λ�ô�������
 *       �µġ������С����µĿ�ʼ����λ�ý���������������С��ĵ�һ���ַ���λ��
 *
 *@���飺
 *    1��keyboard_mode��Ĭ��ģʽ
 *       keyboard_mode�����������У��ʺ�ʹ�ü��̸����������룬�������л�����������������հ׵����У���Ĭ��ģʽ�ǲ�����ж���Ŀհ���ʾ��
 *       ������������һ����'\n'��keyboard_mode����ʾһ���հ��У���Ĭ��ģʽ������ʾ
 *    2��filterOut_char��Ĭ��ģʽ
 *       ʹ��filterOut_char����˵��ַ�����������filter_bufһ�����ַ���ֻ������ʾ�������˴洢
 *    3��scroll_enable
 *       ʹ��scroll_enable�ᵼ��NORMAL��AUTO_BREAKLINE����������������٣���������ַ�ʼ���ڴ����ڣ����ῴ���������ַ���Ҳ�ᵼ��CONSOLE_PRINT
 *       �������������µ�log
 *    4��scroll_anim
 *       ʹ��scroll_anim�ᵼ�´��ڸ��ٲ���������NORMAL��AUTOBREAKLINE�����������(CONSOLE_PRINT)����ƽ�����ɵ����Զ��������������δ����������
 *       �������ӹ����ٶȣ����ڸ���Ҳ��ͬ���������ֽ����������Ķ���ԭ��ͬ��ǰ�����������ڸ�������λ�ò�ͬ��������ƫ�ƣ�CONSOLE_PRINT�Ǹ���
 *       txtViewer_printf����process_cntʲôʱ��������У��̶�ƫ��scroll_pixel��ֻҪ�����о��ж�����CONSOLE_PRINTģʽ��ƾ���Ϊ�����������ģʽ��
 *       ʹ�ù�����������Υ�����������ԭ����Ϊ���ģʽ���벻��ƫ��scroll_pixel�������ж�����ͬʱ����process_cnt������ң����оͻ�������
 *       �ͻᵼ�¶������ң����CONSOLE_PRINTģʽ�½�ֹ������룬ֻ��printf.
 *    5��loop_show
 *       ��Ϊ�ڳ�ʼ��ʱû�ж�ʱ���º�����Ҫ��ʵ�ֳ�ʼ����ӡ������Ӧ�����Ȳ�ʹ�ܸñ���
 *    6��scroll_pixel
 *       CONSOLE_PRINT����������ʷ�в鿴ƫ������scroll_pixelԽ�����Ϲ��������Խ�󣬲鿴����ʷ��Խ��
 *    7��txt_ofsetX
 *       NORMAL��������������ı���Xƫ����
 *    8��txt_ofsetY
 *       NORMAL��AUTOBREAKLINE��������������ı���Yƫ����
 *    9��window_x,window_y,window_w,window_h
 *       �Դ�Ϊ�������϶����x���꣬�������϶����y���꣬���ڿ�ȣ����ڸ߶�
 *    10��char_h��char_w
 *       ����ĸ߶ȺͿ��
 *    11��cursor_enable
 *        ���ģʽ����ʾ��ǰ����λ�ã��洢��ɾ���ַ����λ�ã���Ҫ�ܴ�����
 *
 *@��ֲ������
 *       ���������ײ�ֻ������������ĸ߶ȺͿ�ȣ������Ҫ֧�ִ��ڷָ�ͱ�������ʵ��������ͬ��ʾ���ĵ�mydraw_bitmap������
 *       ��ɫ��Ļʵ��������Ϊ���ӣ���Ϊÿ������bit����һ�����ص㣬��д����ʱ��Ҫʱ��ע�ⴰ��λ�ã�д����λ�ã����ڴ�С�Ĺ�ϵ
 *       �ᾭ�����ִ��ڱ��طָ�ͼ�����ݵ��������ɫ��Ļ����Ƚϼ򵥣���Ϊһ�����ص��Ƕ���ֽڣ�ֻ��Ҫ�ж����ص�������봰�ڵĹ�ϵ����
 *
 *@ʹ��ʾ����
 *       keypress:
 *           apis();
 *       not loop show to loop show:
 *           txtViewer.loop_show = true;
 *           
 *       SETUP:
 *           txtViewer_init(&txtViewer,buf_size,win_x,win_y,NORMAL);
 *       LOOP:
 *           txtViewer.run(&txtViewer);
 */
 
 
 
#include "TXT_Viewer.h"
#include <stdlib.h>
#include "draw.h"
#include "resources.h"
#include "gui_log_console.h"
#include "common.h"


#define CHAR_HEIGHT         8
#define CHAR_WITH           7

//Ҫ���˵��ַ�,�ַ�������ָ��ʾ���ˣ�ʵ�����Ѿ��洢���ڴ�����
static char * filter_buf = "\r\t";
//test buf
char * clang = "int main(int argc, char **argv)\n{\n\n    printf(\"hello world!\");\n    return 0;\n}\n";


//�ַ���������������

//1����ͨ�ı�ģʽ������txt�ı��������з�����
static void txtViewer_display_normal(txtViewer_t *viewer);
//2���ı��Զ�����ģʽ�����ı�ģʽ�������Զ����й��ܣ�
static void txtViewer_display_autoBreakLine(txtViewer_t *viewer);
//3���ն˴�ӡģʽ����ʾ��ʼλ�����ַ�������������У�ֻҪ��Ļû�����꣬ʼ�������ж�����֧�ֳ�ʼ��������ӡ��������ȫ���gui_log_console.c,�ڴ������ʸ���
static void txtViewer_console_print(txtViewer_t *viewer);


static u16 getTotalLine(txtViewer_t *viewer, u8 col_cnt);
static void Recalculate_processed_cnt(txtViewer_t *viewer);
static void txtViewer_printf(txtViewer_t *viewer, char *fmt, ...);
static void txtViewer_run(txtViewer_t *viewer);
//��װ��ͼ��
static void txtViewer_drawOneChar(char* string, bool invert, s16 x, s16 y, s16 start_x, s16 start_y, s16 boundary_h, s16 boundary_w)
{
    char c = *string - 0x20;
    mydraw_bitmap(x, y, smallFont[(byte)c], SMALLFONT_WIDTH, SMALLFONT_HEIGHT, invert, 0,start_x, start_y, boundary_h,boundary_w);
}

static void txtViewer_printOneChar(s16 x, s16 y,char *str, s16 start_x, s16 start_y, s16 boundary_h, s16 boundary_w)
{
	txtViewer_drawOneChar(str, false, x, y, start_x, start_y, boundary_h,boundary_w);
}
//���
const byte Curosor_str[][7] = {{0xFF,0x00,0x00,0x00,0x00,0x00,0x00}};
static void txtViewer_printCursor(s16 x, s16 y, s16 start_x, s16 start_y, s16 boundary_h, s16 boundary_w)
{
	mydraw_bitmap(x, y, Curosor_str[0], 7, SMALLFONT_HEIGHT, 0, 0,start_x, start_y, boundary_h,boundary_w);
}

//��̬�ַ�������������ʹ��malloc����̫���ڴ�ɹ��ʲ��ߣ���Ϊ��̬����
static char buf[1024];

//ΪTXT_VIewer��ʼ����Ϊ����仺��
void txtViewer_init(txtViewer_t *viewer, int size, s16 win_x, s16 win_y, p_mode_t p_mode)
{
	viewer->char_h =  CHAR_HEIGHT;
	viewer->char_w =  CHAR_WITH;
	viewer->buf_size = size;
	viewer->txt_ofsetX = 0;
	viewer->txt_ofsetY = 0;
	viewer->window_x = win_x;
	viewer->window_y = win_y;
	viewer->window_h = 64;
	viewer->window_w = 128;
	viewer->data_buf = buf;
	viewer->printf = txtViewer_printf;
	//console_log(1,"malloc");
	//if(viewer->data_buf == NULL)
		//console_log(1,"malloc err!");
	//else
		//console_log(1,"success");
	console_log(1,"open Viewer!");
	
	viewer->disp_cb.start_charIdx = 0;
	viewer->disp_cb.store_charIdx = 0;
	viewer->disp_cb.cursor_idx = viewer->disp_cb.store_charIdx;
	viewer->loop_show = false;//ʼ��ѭ������
	viewer->scroll_anim = true;//��������
	viewer->scroll_enable = false;//��ֹ���ڸ��٣�NORMAL��AUTOBREAKLINE�������(CONSOLE_PRINT)
	viewer->keyboard_mode = false;//�رռ�������
	viewer->filterOut_char = false;//�ر��˳�'\r'�ַ�
	viewer->cursor_enable = true;//�򿪹��
	viewer->process_mode = p_mode;
	viewer->input_updata = false;//�������
	viewer->win_boundary = false;//���ƴ���
	viewer->cmd_mode = false;
	viewer->run = txtViewer_run;
	switch(p_mode)
	{
		case NORMAL: viewer->process = txtViewer_display_normal;break;
		case AUTO_BREAKLINE: viewer->process = txtViewer_display_autoBreakLine;break;
		case CONSOLE_PRINT: viewer->process = txtViewer_console_print;break;
		default:break;
	}
	//txtViewer_printf(viewer,"0\n1\n2\n3\n4\n5\n6\n7\n8\n9\n10\n");
	txtViewer_printf(viewer,"he\rllo,th\ris is a test.\ncan you see something here?\nIf you can see some words\nThis test may have succeeded!\n1\n2\n3\n4\n5\n6\n7\n8\n9\n10\n");
	txtViewer_printf(viewer,clang);
	viewer->scroll_enable = false;
}
//����һ���ַ�
void txtViewer_getChar(txtViewer_t *viewer,char data)
{
	if(!viewer->input_updata) {
		viewer->getchar = data;
		viewer->input_updata = true;
	}
}
//����������
void txtViewer_changeProcessMode(txtViewer_t *viewer, p_mode_t p_mode)
{
	switch(p_mode)
	{
		case NORMAL: viewer->process = txtViewer_display_normal;break;
		case AUTO_BREAKLINE: viewer->process = txtViewer_display_autoBreakLine;break;
		case CONSOLE_PRINT: viewer->process = txtViewer_console_print;break;
		default:break;
	}
	viewer->process_mode = p_mode;
	viewer->txt_ofsetX = 0;
	viewer->txt_ofsetY = 0;
	viewer->scroll_enable = false;
	viewer->disp_cb.cursor_idx = viewer->disp_cb.store_charIdx;
	Recalculate_processed_cnt(viewer);
}

void txtViewer_clearDataBuf(txtViewer_t *viewer)
{
	viewer->disp_cb.start_charIdx = 0;
	viewer->disp_cb.store_charIdx = 0;
	viewer->data_buf[viewer->disp_cb.store_charIdx]='\0';
	viewer->txt_ofsetX = 0;
	viewer->txt_ofsetY = 0;
	viewer->disp_cb.cursor_idx = 0;
	
	Recalculate_processed_cnt(viewer);
}

static u8 is_filterChar(char chr, char *filter_buf)
{
	while(*filter_buf != '\0')
	{
		if(chr == *filter_buf++)
			return true;
	}
	return false;
}

void setFilterOut(txtViewer_t *viewer)
{
	viewer->filterOut_char = !viewer->filterOut_char;
	Recalculate_processed_cnt(viewer);
}

//���������ַ�Դ
void txtViewer_changeSource(txtViewer_t *viewer, txtViewer_t *new_source)
{
	if(new_source->data_buf == NULL||new_source->data_buf == viewer->data_buf )
		return;
	viewer->disp_cb.start_charIdx = new_source->disp_cb.start_charIdx;
	viewer->disp_cb.store_charIdx = new_source->disp_cb.store_charIdx;
	viewer->data_buf = new_source->data_buf;
}

//��ȡѭ��������������ַ�����һ���ַ�λ��
static int getNext(txtViewer_t *viewer, u16 last_char_idx)
{
    last_char_idx++;
    if(last_char_idx >= viewer->buf_size)
    {
        last_char_idx = 0;
    }
    return last_char_idx;
}
static int getLast(txtViewer_t *viewer, u16 last_char_idx)
{
    last_char_idx--;
    if(last_char_idx >= viewer->buf_size)
    {
        last_char_idx = viewer->buf_size-1;
    }
    return last_char_idx;
}


static u16 findNewStartIdx(txtViewer_t *viewer)
{
	u16 store_idx = getNext(viewer,viewer->disp_cb.store_charIdx);
	
	while( viewer->data_buf[store_idx] != '\n'
		&& store_idx != viewer->disp_cb.store_charIdx )
	{
		store_idx = getNext(viewer,store_idx);
	}
	
	if(store_idx == viewer->disp_cb.store_charIdx)
		return store_idx;
	else
		return getNext(viewer,store_idx);
	
}


//�л�������Ҫ���¼���viewer->processd_cnt
static void Recalculate_processed_cnt(txtViewer_t *viewer)
{
	u16 cnt = 0;
	if(viewer->disp_cb.store_charIdx == viewer->disp_cb.start_charIdx) {
		viewer->processd_cnt= 0;
		return;
	}
	//��ȥ������
	u16 idx = getLast(viewer,viewer->disp_cb.store_charIdx);
	u16 col_cnt = viewer->window_w/viewer->char_w;
	cnt = 0;
	while( viewer->data_buf[idx] != '\n'
		&& idx != viewer->disp_cb.start_charIdx )
	{
		
		//�����ַ�
		if(viewer->filterOut_char) {
			if(!is_filterChar(viewer->data_buf[idx],filter_buf))
				cnt++;
		}
		else {
			cnt++;
		}
		
		idx = getLast(viewer,idx);
	}
	//�������������һ������Ҫ���⴦��һ��
	if(idx == viewer->disp_cb.start_charIdx) {
		if(viewer->filterOut_char) {
			if(!is_filterChar(viewer->data_buf[idx],filter_buf))
				cnt++;
		}
		else {
			cnt++;
		}
	}
	if(viewer->process_mode != NORMAL)
		viewer->processd_cnt = cnt % col_cnt;
	else
		viewer->processd_cnt = cnt;
}
//���ô��ڴ�С
void txtViewer_setWindow(txtViewer_t *viewer, u8 h, u8 w )
{
	viewer->window_h = h;
	viewer->window_w = w;
	viewer->txt_ofsetX = 0;
	viewer->txt_ofsetY = 0;
	Recalculate_processed_cnt(viewer);
}

//�ӵ�line�п�ʼ������ʣ��������ɱ������Ӷ����ٶ�
static u8 txtViewer_Dynamic_Aim_Speed(txtViewer_t *viewer,u8 line)
{
	//�ٶ����Ϊ (�ַ��߶�viewer->char_h-line+1) Pixels
	if (line > viewer->char_h)
		return 0;
	return viewer->scroll_pixel<=line*viewer->char_h ? 1:1+txtViewer_Dynamic_Aim_Speed(viewer, line+1);
}
//�ӵ�line�п�ʼ������ʣ��������ɱ������Ӷ����ٶ�
static u8 Dynamic_Aim_SpeedForWindow(txtViewer_t *viewer,u8 start_step, u8 step_size, s16 depend)
{
	u8 max_speed = 16;//pixel
	//�ٶ����Ϊ (max_speed-line+1) Pixels
	if (start_step > max_speed)
		return 0;
	return depend<=start_step*step_size ? 2:1+Dynamic_Aim_SpeedForWindow(viewer, start_step+1, step_size, depend);
}
//ɾ�����һ���洢λ�õ��ַ�����Ȼȡ�����Ƿ���˵��ַ�
void txtViewer_DeleteLastStoreChar(txtViewer_t *viewer)
{
	if(viewer->disp_cb.store_charIdx == viewer->disp_cb.start_charIdx)
		return;
	//��ȥ������
	u16 char_idx = getLast(viewer,viewer->disp_cb.store_charIdx);
	
				
	//�������˳��ַ���λ��
	if(viewer->filterOut_char)
	{
		while(is_filterChar(viewer->data_buf[char_idx], filter_buf))
		{
			if(char_idx == viewer->disp_cb.start_charIdx)
			{
				return;
			}

			char_idx = getLast(viewer, char_idx);
		}
	}
	viewer->disp_cb.store_charIdx=char_idx;
	viewer->data_buf[viewer->disp_cb.store_charIdx]='\0';
}

//���ָ��λ��ɾ���ַ�
void txtViewer_CursorDeleteChar(txtViewer_t *viewer)
{
	if(!viewer->cursor_enable)
		return;
	if(viewer->process_mode == CONSOLE_PRINT)
		return;
	if(viewer->disp_cb.cursor_idx == viewer->disp_cb.start_charIdx)
		return;
	viewer->scroll_enable = true;
	u8 flag=0;
	u16 j,i = viewer->disp_cb.cursor_idx;
	//�ҵ�Ҫɾ�����ַ�
	if(viewer->filterOut_char) {
		//�˳��ַ�
		i = getLast(viewer, i);
		if(i == viewer->disp_cb.start_charIdx)
			flag=1;
		while(is_filterChar(viewer->data_buf[i], filter_buf)) {
			if(flag)
				return;
			i = getLast(viewer, i);
			if(i == viewer->disp_cb.start_charIdx)
				flag=1;
		}
		
	} else {
		i = getLast(viewer, i);
	}
	j=i;
	//�ֽ��ƶ�
	for(;j != viewer->disp_cb.store_charIdx; i = getNext(viewer,i))
	{
		j = getNext(viewer,i);
		viewer->data_buf[i] = viewer->data_buf[j];
	}
	viewer->disp_cb.store_charIdx = getLast(viewer, viewer->disp_cb.store_charIdx);
	viewer->disp_cb.cursor_idx = getLast(viewer, viewer->disp_cb.cursor_idx);
}

//���ָ��λ�������ַ�
void txtViewer_CursorAddChar(txtViewer_t *viewer, char data)
{
	if(!viewer->cursor_enable)
		return;
	if(viewer->process_mode == CONSOLE_PRINT)
		return;
	viewer->scroll_enable = true;
	//����ڴ����ˣ������ַ��������ӵ��ַ�����
	if(getNext(viewer,viewer->disp_cb.store_charIdx) != viewer->disp_cb.start_charIdx) {
		viewer->disp_cb.store_charIdx = getNext(viewer,viewer->disp_cb.store_charIdx);
		viewer->data_buf[viewer->disp_cb.store_charIdx] = '\0';
	} 
	else
	{
		//���д�����ҹ�������һ��λ�ã��Ͳ�д��
		if(viewer->disp_cb.cursor_idx == viewer->disp_cb.store_charIdx)
		{
			return;
		}
	}
	
	u16 i,j = getLast(viewer,viewer->disp_cb.store_charIdx);
	i=j;
	//�ֽ��ƶ�
	for(;i != viewer->disp_cb.cursor_idx; j = getLast(viewer,j))
	{
		i = getLast(viewer,j);
		viewer->data_buf[j] = viewer->data_buf[i];
	}
	//д�����ӵ��ַ�
	viewer->data_buf[viewer->disp_cb.cursor_idx] = data;
	viewer->disp_cb.cursor_idx = getNext(viewer, viewer->disp_cb.cursor_idx);
}


static u16 calculat_CursorCharcnt(txtViewer_t *viewer)
{
	u16 cnt=0;
	u16 col_cnt = viewer->window_w/viewer->char_w;
	u16 cursor_idx = viewer->disp_cb.cursor_idx;
	//�������˵���ǿ�
	if(cursor_idx == viewer->disp_cb.start_charIdx)
		return cnt;
	//��ͳ�ƹ��λ��
	cursor_idx = getLast(viewer,cursor_idx);
	if(cursor_idx == viewer->disp_cb.start_charIdx) {
		return cnt;
	}
	while( viewer->data_buf[cursor_idx] != '\n' ) {
		//�����ַ�
		if(viewer->filterOut_char) {
			if(!is_filterChar(viewer->data_buf[cursor_idx],filter_buf))
				cnt++;
		}
		else {
			cnt++;
		}
		cursor_idx = getLast(viewer,cursor_idx);
		if(cursor_idx == viewer->disp_cb.start_charIdx) {
			break;
		}
	}
	////�������˵��buf�ǿգ���Ҫͳ�����һ����
	if(cursor_idx == viewer->disp_cb.start_charIdx) {
		if(viewer->filterOut_char) {
			if(!is_filterChar(viewer->data_buf[cursor_idx],filter_buf))
				cnt++;
		}
		else {
			cnt++;
		}
	}
	if(viewer->process_mode != NORMAL)
		return (cnt) % col_cnt;
	else
		return cnt;
}


//�������
void cursor_up(txtViewer_t *viewer)
{
	if(!viewer->cursor_enable)
		return;
	viewer->scroll_enable = true;
	u16 cursor_idx = viewer->disp_cb.cursor_idx;
	//�Ѿ�����ǰ��
	if(cursor_idx == viewer->disp_cb.start_charIdx)
		return;
	
	if (viewer->process_mode == NORMAL) {
		u16 thisline_cnt = calculat_CursorCharcnt(viewer)+1;
		if(viewer->data_buf[cursor_idx] == '\n') {
			cursor_idx = getLast(viewer,cursor_idx);
			if(cursor_idx == viewer->disp_cb.start_charIdx) {
				viewer->disp_cb.cursor_idx = cursor_idx;
				return;
			}
		}
			
		//��ǰ�ҵ�һ������
		while( viewer->data_buf[cursor_idx] != '\n' ) {
			cursor_idx = getLast(viewer,cursor_idx);
			if(cursor_idx == viewer->disp_cb.start_charIdx) {
				viewer->disp_cb.cursor_idx = cursor_idx;
				return;
			}
		}
		//�����������
		cursor_idx = getLast(viewer,cursor_idx);
		if(cursor_idx == viewer->disp_cb.start_charIdx)
		{
			viewer->disp_cb.cursor_idx = cursor_idx;
			return;
		}
		//��ǰ�ҵڶ�������
		while( viewer->data_buf[cursor_idx] != '\n' ) {
			cursor_idx = getLast(viewer,cursor_idx);
			if(cursor_idx == viewer->disp_cb.start_charIdx) {
				break;
			}
		}
		
		//����һ���ƶ����
		while(thisline_cnt) {
			if(viewer->filterOut_char) {
				if(!is_filterChar(viewer->data_buf[cursor_idx], filter_buf)) 
					thisline_cnt--;
				cursor_idx = getNext(viewer, cursor_idx);
			} else {
				cursor_idx = getNext(viewer, cursor_idx);
				thisline_cnt--;
			}
			if(cursor_idx == viewer->disp_cb.store_charIdx)
			{
				viewer->disp_cb.cursor_idx = cursor_idx;
				return;
			}
			if(viewer->data_buf[cursor_idx] == '\n')
			{
				viewer->disp_cb.cursor_idx = cursor_idx;
				return;
			}
		}
		viewer->disp_cb.cursor_idx = cursor_idx;
	} else if (viewer->process_mode == AUTO_BREAKLINE) {
			u16 col_cnt = viewer->window_w/viewer->char_w;
			u16 cnt = calculat_CursorCharcnt(viewer);
			
		
			if(viewer->data_buf[cursor_idx] == '\n') {
				cursor_idx = getLast(viewer,cursor_idx);
				if(cursor_idx == viewer->disp_cb.start_charIdx) {
					viewer->disp_cb.cursor_idx = cursor_idx;
					return;
				}
			}

			//����ֱ��,viewer->data_buf[cursor_idx] != '\n'���ǻ��о�����
			while(col_cnt && viewer->data_buf[cursor_idx] != '\n') {
				
				if(viewer->filterOut_char) {
					if(!is_filterChar(viewer->data_buf[cursor_idx], filter_buf)) 
						col_cnt--;
					cursor_idx = getLast(viewer, cursor_idx);
				} else {
					cursor_idx = getLast(viewer, cursor_idx);
					col_cnt--;
				}
				if(cursor_idx == viewer->disp_cb.start_charIdx)
				{
					viewer->disp_cb.cursor_idx = cursor_idx;
					return;
				}
				
			}
			if(viewer->data_buf[cursor_idx] == '\n')
			{
				viewer->disp_cb.cursor_idx = cursor_idx;
			}
			if(col_cnt == 0 ) {
				viewer->disp_cb.cursor_idx = cursor_idx;
				return;
			}
			
			u16 upline_cnt = calculat_CursorCharcnt(viewer);

			if(upline_cnt<cnt)
				upline_cnt=cnt;
			//����һ���ƶ����
			while(upline_cnt - cnt) {
				if(viewer->filterOut_char) {
					if(!is_filterChar(viewer->data_buf[cursor_idx], filter_buf)) 
						upline_cnt--;
					cursor_idx = getLast(viewer, cursor_idx);
				} else {
					cursor_idx = getLast(viewer, cursor_idx);
					upline_cnt--;
				}
				if(cursor_idx == viewer->disp_cb.start_charIdx)
				{
					viewer->disp_cb.cursor_idx = cursor_idx;
					return;
				}

			}
			viewer->disp_cb.cursor_idx = cursor_idx;	
		
	}
}


//�������(��ȫ��bug)
void cursor_down(txtViewer_t *viewer)
{
	if(!viewer->cursor_enable)
		return;
	viewer->scroll_enable = true;
	u16 cursor_idx = viewer->disp_cb.cursor_idx;
	//�Ѿ��������
	if(cursor_idx == viewer->disp_cb.store_charIdx)
		return;
	/////
	if (viewer->process_mode == NORMAL) {
		//ͳ����һ�е��ַ���
		u16 cnt = calculat_CursorCharcnt(viewer);

		while( viewer->data_buf[cursor_idx] != '\n' ) {
			cursor_idx = getNext(viewer,cursor_idx);
			if(cursor_idx == viewer->disp_cb.store_charIdx) {
				viewer->disp_cb.cursor_idx = cursor_idx;
				return;
			}
		}
		//�����������
		cursor_idx = getNext(viewer,cursor_idx);
		if(cursor_idx == viewer->disp_cb.store_charIdx)
		{
			viewer->disp_cb.cursor_idx = cursor_idx;
			return;
		}
		//����һ���ƶ����
		while(cnt) {
			if(viewer->filterOut_char) {
				if(!is_filterChar(viewer->data_buf[cursor_idx], filter_buf)) 
					cnt--;
				cursor_idx = getNext(viewer, cursor_idx);
			} else {
				cursor_idx = getNext(viewer, cursor_idx);
				cnt--;
			}
			if(cursor_idx == viewer->disp_cb.store_charIdx)
			{
				viewer->disp_cb.cursor_idx = cursor_idx;
				return;
			}
			if(viewer->data_buf[cursor_idx] == '\n')
			{
				viewer->disp_cb.cursor_idx = cursor_idx;
				return;
			}
		}
		viewer->disp_cb.cursor_idx = cursor_idx;
		
		
	} else if (viewer->process_mode == AUTO_BREAKLINE) {
			u16 col_cnt = viewer->window_w/viewer->char_w;
			u16 cnt = calculat_CursorCharcnt(viewer);

			//����ֱ�ӣ���괦�ǻ��о�����
			while(col_cnt && viewer->data_buf[cursor_idx] != '\n') {
				
				if(viewer->filterOut_char) {
					if(!is_filterChar(viewer->data_buf[cursor_idx], filter_buf)) 
						col_cnt--;
					cursor_idx = getNext(viewer, cursor_idx);
				} else {
					cursor_idx = getNext(viewer, cursor_idx);
					col_cnt--;
				}
				if(cursor_idx == viewer->disp_cb.store_charIdx)
				{
					viewer->disp_cb.cursor_idx = cursor_idx;
					return;
				}
			}
			if(col_cnt == 0) {
				viewer->disp_cb.cursor_idx = cursor_idx;
				return;
			}
			//�����������
			cursor_idx = getNext(viewer,cursor_idx);
			if(cursor_idx == viewer->disp_cb.store_charIdx)
			{
				viewer->disp_cb.cursor_idx = cursor_idx;
				return;
			}
			//����һ���ƶ����
			while(cnt && viewer->data_buf[cursor_idx] != '\n') {
				if(viewer->filterOut_char) {
					if(!is_filterChar(viewer->data_buf[cursor_idx], filter_buf)) 
						cnt--;
					cursor_idx = getNext(viewer, cursor_idx);
				} else {
					cursor_idx = getNext(viewer, cursor_idx);
					cnt--;
				}
				if(cursor_idx == viewer->disp_cb.store_charIdx)
				{
					viewer->disp_cb.cursor_idx = cursor_idx;
					return;
				}
				if(viewer->data_buf[cursor_idx] == '\n')
				{
					viewer->disp_cb.cursor_idx = cursor_idx;
					return;
				}
			}
			viewer->disp_cb.cursor_idx = cursor_idx;
			
	}
}
//���--
void cursor_left(txtViewer_t *viewer)
{
	if(!viewer->cursor_enable)
		return;
	if(viewer->process_mode == CONSOLE_PRINT)
		return;
	if(viewer->disp_cb.cursor_idx == viewer->disp_cb.start_charIdx)
		return;
	u16 cursor_idx = viewer->disp_cb.cursor_idx;
	cursor_idx = getLast(viewer, cursor_idx);
	if(cursor_idx == viewer->disp_cb.start_charIdx) {
		viewer->disp_cb.cursor_idx = cursor_idx;
		return;
	}
	if(viewer->filterOut_char) {
		//�˳��ַ�
		while(is_filterChar(viewer->data_buf[cursor_idx], filter_buf)) {
			cursor_idx = getLast(viewer, cursor_idx);	
			if(cursor_idx == viewer->disp_cb.start_charIdx) {
				viewer->disp_cb.cursor_idx = cursor_idx;
				return;
			}
		}
		
	}
	viewer->disp_cb.cursor_idx = cursor_idx;
}
//���++
void cursor_right(txtViewer_t *viewer)
{
	if(!viewer->cursor_enable)
		return;
	if(viewer->process_mode == CONSOLE_PRINT)
		return;
	if(viewer->disp_cb.cursor_idx == viewer->disp_cb.store_charIdx)
		return;
	u16 cursor_idx = viewer->disp_cb.cursor_idx;
	
	cursor_idx = getNext(viewer, cursor_idx);	
	if(cursor_idx == viewer->disp_cb.store_charIdx) {
		viewer->disp_cb.cursor_idx = cursor_idx;
		return;
	}
	if(viewer->filterOut_char) {
		//�˳��ַ�
		while(is_filterChar(viewer->data_buf[cursor_idx], filter_buf)) {
			cursor_idx = getNext(viewer, cursor_idx);	
			if(cursor_idx == viewer->disp_cb.store_charIdx) {
				viewer->disp_cb.cursor_idx = cursor_idx;
				return;
			}
		}
	}
	viewer->disp_cb.cursor_idx = cursor_idx;
}

static void txtViewer_addString(txtViewer_t *viewer, char *str)
{
	//��¼���һ�������ַ��ǲ��ǻ��У���������Ǵ�ӡ��Ҫ���붯��
	static u8 ln_flag = 0;
	u8 flag = 0;
	u16 col_cnt = viewer->window_w/viewer->char_w;
	while(*str != '\0') {
		
		//�γɶ���ƫ��
		if(viewer->process_mode == CONSOLE_PRINT && viewer->scroll_anim) {
			if(*str=='\n') {
				if(viewer->keyboard_mode) {
					viewer->scroll_pixel += viewer->char_h;
				} else {
					//������е����γ�ƫ��
					if(ln_flag) {
						viewer->scroll_pixel += viewer->char_h;
					}
					ln_flag = 1;
				}
				viewer->processd_cnt=0;

			} else {

				//�����ַ�
				if(viewer->filterOut_char) {
					if(!is_filterChar(*str,filter_buf)) {
						//'\n'�Ӻ���
						if(ln_flag) {
							viewer->scroll_pixel += viewer->char_h;
						}
						ln_flag = 0;
						viewer->processd_cnt++;
					}
				} else {
					//'\n'�Ӻ���
					if(ln_flag)
						viewer->scroll_pixel += viewer->char_h;
					ln_flag = 0;
					viewer->processd_cnt++;
				}
				
			}

			if(viewer->processd_cnt > col_cnt) {
				viewer->scroll_pixel += viewer->char_h;
				viewer->processd_cnt = 1;
			}
			
		}
		
		if(viewer->process_mode == NORMAL ) {
			if(*str=='\n') {
				ln_flag = 1;
				if(viewer->keyboard_mode)
					viewer->processd_cnt=0;
			} else {
				
				//�����ַ�
				if(viewer->filterOut_char) {
					
					if(!is_filterChar(*str,filter_buf)) {
						//�Ӻ�����
						if(ln_flag)
							viewer->processd_cnt=0;
						ln_flag = 0;
						viewer->processd_cnt++;
					}
					
				} else {
					if(ln_flag)
							viewer->processd_cnt=0;
						ln_flag = 0;
					viewer->processd_cnt++;
				}
			}

			
		}
		
		if(viewer->process_mode == AUTO_BREAKLINE ) {
			if(*str=='\n') {
				viewer->processd_cnt=0;
			} else {
				
				//�����ַ�
				if(viewer->filterOut_char) {
					if(!is_filterChar(*str,filter_buf))
						viewer->processd_cnt++;
				} else {
					viewer->processd_cnt++;
				}
			}

			if(viewer->processd_cnt > col_cnt) {
				viewer->processd_cnt = 1;
			}
			
		}
		
		
		viewer->data_buf[viewer->disp_cb.store_charIdx] = *str++;
		viewer->disp_cb.store_charIdx = getNext(viewer,viewer->disp_cb.store_charIdx);
		//��Ҫ�����ҵ���ʼ���ݵĵ�ַ
		if(viewer->disp_cb.store_charIdx == viewer->disp_cb.start_charIdx)
			flag = 1;
	}
	viewer->data_buf[viewer->disp_cb.store_charIdx] = '\0';
	//ѭ���������Ĵ洢������ʼ������ʾ������ȡ�ڶ��е�һ���ַ�λ����Ϊ�µ�disp_cb.start_charIdx
	if(flag) {
		viewer->disp_cb.start_charIdx = findNewStartIdx(viewer);
		//�ҵ����к���Ҫ���¼���processed_cnt
		Recalculate_processed_cnt(viewer);
	}
	//��λ���
	viewer->disp_cb.cursor_idx = viewer->disp_cb.store_charIdx;
}

extern char firststr_buff[512];
//�ڽ�β����ӡ�ַ���
static void txtViewer_printf(txtViewer_t *viewer, char *fmt, ...)
{
	va_list ap;
	va_start(ap,fmt);
	vsprintf(firststr_buff,fmt,ap);
	va_end(ap);
	txtViewer_addString(viewer, firststr_buff);
	viewer->scroll_enable=1;//�򿪹������»��ߴ��ڸ����ַ�λ��
	//��ѭ��ģʽ��ȫ�ٴ�ӡ��ϣ���Ժ��ܹ淶ִ���ٶ�
	if(viewer->process_mode == CONSOLE_PRINT && !viewer->loop_show) {
		while(viewer->scroll_pixel) {
			
			memset(&oledBuffer, 0x00, FRAME_BUFFER_SIZE);
			viewer->process(viewer);
			oled_flush();
			
		}
	}
}

//NORMALģʽ��ʹ��
static u16 getFirstLineIdx(txtViewer_t *viewer,s16 skipCnt)
{
	u16 char_idx;
	char_idx = viewer->disp_cb.start_charIdx;
	
	if(skipCnt <= 0||char_idx == viewer->disp_cb.store_charIdx)
		return viewer->disp_cb.start_charIdx;
	char_idx = getNext(viewer, char_idx);
	
	//ѭ��cnt��,�ҵ�Ҫ��ʾ�ĵ�һ�еĵ�һ��λ��
	while(skipCnt--)
	{
		while( viewer->data_buf[char_idx] != '\n')
		{
			char_idx = getNext(viewer, char_idx);
		}
		char_idx = getNext(viewer, char_idx);
		if(char_idx == viewer->disp_cb.store_charIdx)
			break;
	}
	return char_idx;
}

//CONSOLE��AUROģʽ��ʹ��
static u16 getFirstLineIdx_autoBreakLine(txtViewer_t *viewer,s16 skipCnt,u8 col_cnt)
{
	u16 char_idx;
	u8 col = 0;
	char_idx = viewer->disp_cb.start_charIdx;
	
	if(skipCnt <= 0||char_idx == viewer->disp_cb.store_charIdx)
		return viewer->disp_cb.start_charIdx;
	
	//ѭ��cnt��,�ҵ�Ҫ��ʾ�ĵ�һ�еĵ�һ��λ��
	while(skipCnt--)
	{
		while( viewer->data_buf[char_idx] != '\n' && col < col_cnt)
		{
			//�����ַ�
			if(viewer->filterOut_char) {
				if(!is_filterChar(viewer->data_buf[char_idx], filter_buf) )
					col++;
			}
			else {
				col++;
			}

			char_idx = getNext(viewer, char_idx);
		}
		col = 0;
		if(viewer->data_buf[char_idx] == '\n')
			char_idx = getNext(viewer, char_idx);
		if(char_idx == viewer->disp_cb.store_charIdx)
			break;
	}
	return char_idx;
}

//normalģʽ��ʹ��,ͬʱ������������һ��
static u16 getTotalLine_noAutoBrk(txtViewer_t *viewer)
{
	u8 line_cnt=0;
	u16 char_idx = viewer->disp_cb.start_charIdx;
	//������������һ��
	if(char_idx == viewer->disp_cb.cursor_idx)
		viewer->cursor_lineY = line_cnt;
	//
	while(viewer->data_buf[char_idx] != '\0')
	{
		while( viewer->data_buf[char_idx] != '\n' && viewer->data_buf[char_idx] != '\0')
		{
			char_idx = getNext(viewer, char_idx);
			//������������һ��
			if(char_idx == viewer->disp_cb.cursor_idx)
				viewer->cursor_lineY = line_cnt;
		}
		line_cnt++;
		if(viewer->data_buf[char_idx] == '\n') {
			char_idx = getNext(viewer, char_idx);
			//������������һ��
			if(char_idx == viewer->disp_cb.cursor_idx)
				viewer->cursor_lineY = line_cnt;
		}
	}
	//��������ģʽ�������ĩβ��⵽�л��У����������в���,����һ��
	if(viewer->keyboard_mode && line_cnt != 0) {
		//��ȥ������
		u16 idx = getLast(viewer,viewer->disp_cb.store_charIdx);
		if(viewer->data_buf[idx] == '\n')
			line_cnt++;
	}
	return line_cnt;
}
//CONSOLE��AUROģʽ��ʹ��
static u16 getTotalLine(txtViewer_t *viewer, u8 col_cnt)
{
	u8 line_cnt=0;
	u8 col = 0;
	u16 char_idx = viewer->disp_cb.start_charIdx;
	//������������һ��
	if(char_idx == viewer->disp_cb.cursor_idx)
		viewer->cursor_lineY = line_cnt;
	//ѭ��cnt��,�ҵ�Ҫ��ʾ�ĵ�һ�еĵ�һ��λ��
	while(viewer->data_buf[char_idx] != '\0')
	{
		while( viewer->data_buf[char_idx] != '\n' && col < col_cnt && viewer->data_buf[char_idx] != '\0')
		{
			
			//�����ַ�
			if(viewer->filterOut_char) {
				if(!is_filterChar(viewer->data_buf[char_idx], filter_buf))
					col++;
			}
			else {
				col++;
			}

			char_idx = getNext(viewer, char_idx);
			//������������һ��
			if(char_idx == viewer->disp_cb.cursor_idx)
				viewer->cursor_lineY = line_cnt+col/col_cnt;
		}
		line_cnt++;
		//
		if(viewer->filterOut_char)
		{
			while(is_filterChar(viewer->data_buf[char_idx], filter_buf))
			{
				char_idx = getNext(viewer, char_idx);
				//������������һ��
				if(char_idx == viewer->disp_cb.cursor_idx)
					viewer->cursor_lineY = line_cnt;
			}
		}
		col = 0;
		if(viewer->data_buf[char_idx] == '\n') {
			char_idx = getNext(viewer, char_idx);
			//������������һ��
			if(char_idx == viewer->disp_cb.cursor_idx)
				viewer->cursor_lineY = line_cnt;
		}
	}
	//��������ģʽ�������ĩβ��⵽�л��У����������в���
	if(viewer->keyboard_mode && line_cnt != 0) {
		//��ȥ������
		u16 idx = getLast(viewer,viewer->disp_cb.store_charIdx);
		if(viewer->data_buf[idx] == '\n')
			line_cnt++;
	}
	return line_cnt;
}
//��ͨ����ģʽ
static void txtViewer_display_normal(txtViewer_t *viewer)
{
	//������Ҫ����������
	s16 skipLineNum = viewer->txt_ofsetY/viewer->char_h;
	//��ȡ���ڵĵ�һ�еĵ�һ���ַ����ȽϺķ�����
	u16 char_idx = getFirstLineIdx(viewer,skipLineNum);
	
	//���㴰��ÿ��Ҫ��ʾ���ַ�����
	u16 line_cnt = viewer->window_h/viewer->char_h+1;
	//���㴰��ÿ��Ҫ��ʾ���ַ�����
	u16 col_cnt = viewer->window_w/viewer->char_w+1;
	//�д�ӡ������//�д�ӡ������
	u16 row_cnt = 0, col_char_cnt = 0;
	
	s16 eachLineCharOffsetNum = viewer->txt_ofsetX/viewer->char_w;
	//����������к͹�����
	u16 total_line = getTotalLine_noAutoBrk(viewer);
	//�����������
	viewer->cursor_lineX = calculat_CursorCharcnt(viewer);
	//���ȹ�����
	if(viewer->cursor_enable && viewer->scroll_enable && viewer->keyboard_mode)
	{
		//x����
		s16 length_x = (viewer->cursor_lineX+1) * viewer->char_w;
		if(length_x - viewer->txt_ofsetX > viewer->window_w) { 
			if(viewer->scroll_anim)
				viewer->txt_ofsetX+=Dynamic_Aim_SpeedForWindow(viewer,1,viewer->char_w,length_x - viewer->txt_ofsetX -viewer->window_w);
			else
				viewer->txt_ofsetX=length_x -viewer->window_w;
		}
		if((viewer->cursor_lineX - 5 < 0?0:viewer->cursor_lineX - 5) * viewer->char_w < viewer->txt_ofsetX) {
			if(viewer->scroll_anim)
				viewer->txt_ofsetX-=Dynamic_Aim_SpeedForWindow(viewer,1,viewer->char_w,viewer->txt_ofsetX - (5* viewer->char_w));
			else
				viewer->txt_ofsetX=((viewer->cursor_lineX - 5)* viewer->char_w) < 0 ? 0:(viewer->cursor_lineX - 5)* viewer->char_w;
		}
		//y����
		s16 length_y = viewer->char_h * (viewer->cursor_lineY+1);
		if(length_y - viewer->txt_ofsetY > viewer->window_h) { //��ֹ����ڴ�������
			if(viewer->scroll_anim)
				viewer->txt_ofsetY+=Dynamic_Aim_SpeedForWindow(viewer,1,viewer->char_h,length_y - viewer->txt_ofsetY - viewer->window_h);
			else
				viewer->txt_ofsetY=length_y - viewer->window_h;
		}
		if(viewer->cursor_lineY * viewer->char_h < viewer->txt_ofsetY) { //��ֹ����ڴ�������
			if(viewer->scroll_anim)
				viewer->txt_ofsetY-=Dynamic_Aim_SpeedForWindow(viewer,1,viewer->char_h,viewer->txt_ofsetY - (viewer->cursor_lineY* viewer->char_h));
			else
				viewer->txt_ofsetY=viewer->txt_ofsetY - viewer->char_h;
		}
		length_y = viewer->char_h * total_line;
		//��ӡʱʼ�ձ������һ���������棬��ֹ���иı�ʱ���廭�����ƣ�����м���ת�������룬�����׶�ʧ�ӽ�
		if(length_y - viewer->txt_ofsetY < viewer->window_h)
			viewer->txt_ofsetY = length_y - viewer->window_h;
	}
	//���ڸ����ַ���ӡ
	else if(viewer->scroll_enable)
	{
		s16 length_x = viewer->processd_cnt * viewer->char_w;
		if(length_x - viewer->txt_ofsetX > viewer->window_w) { 
			if(viewer->scroll_anim)
				viewer->txt_ofsetX+=Dynamic_Aim_SpeedForWindow(viewer,1,viewer->char_w,length_x - viewer->txt_ofsetX -viewer->window_w);
			else
				viewer->txt_ofsetX=length_x -viewer->window_w;
		}
		if((viewer->processd_cnt - 5 < 0?0:viewer->processd_cnt - 5) * viewer->char_w < viewer->txt_ofsetX) {
			if(viewer->scroll_anim)
				viewer->txt_ofsetX-=Dynamic_Aim_SpeedForWindow(viewer,1,viewer->char_w,viewer->txt_ofsetX - (5* viewer->char_w));
			else
				viewer->txt_ofsetX=((viewer->processd_cnt - 5)* viewer->char_w) < 0 ? 0:(viewer->processd_cnt - 5)* viewer->char_w;
		}
		s16 length_y = viewer->char_h * total_line;
		if(length_y - viewer->txt_ofsetY > viewer->window_h) {
			if(viewer->scroll_anim)
				viewer->txt_ofsetY+=Dynamic_Aim_SpeedForWindow(viewer,1,viewer->char_h,length_y - viewer->txt_ofsetY - viewer->window_h);
			else
				viewer->txt_ofsetY=length_y - viewer->window_h;
		}
		//��ӡʱʼ�ձ������һ���������棬��ֹ���иı�ʱ���廭�����ƣ�����м���ת�������룬�����׶�ʧ�ӽ�
		if(length_y - viewer->txt_ofsetY < viewer->window_h)
			viewer->txt_ofsetY = length_y - viewer->window_h;
	}
	
	char buff[4];
	sprintf_P(buff, PSTR("%d"), viewer->cursor_lineX);
	draw_string(buff, NOINVERT, 110, FRAME_HEIGHT - 8);
	sprintf_P(buff, PSTR("%d"), viewer->cursor_lineY);
	draw_string(buff, NOINVERT, 110, FRAME_HEIGHT - 16);
	
	//���ƴ����ַ�������ӡ
	while(row_cnt < line_cnt) {
		//����ÿһ���ַ��������У��������������ӡ����
		
		
			s16 txt_x = (col_char_cnt)*viewer->char_w - viewer->txt_ofsetX;
			s16 txt_y = (row_cnt + (skipLineNum > 0? skipLineNum:0))*viewer->char_h - viewer->txt_ofsetY;
			//��ӡ���
			if(viewer->cursor_enable) {
				static millis8_t lastUpdate;
				millis8_t now = millis();
				if ((millis8_t)(now - lastUpdate) >= 1000)
					lastUpdate = now;
				if ((millis8_t)(now - lastUpdate) < 500) {
					
					if(char_idx == viewer->disp_cb.cursor_idx ) {
						txtViewer_printCursor(txt_x + viewer->window_x, txt_y + viewer->window_y, 
								viewer->window_x,viewer->window_y, viewer->window_y + viewer->window_h, viewer->window_x + viewer->window_w);
					}
				}
				
			}
			
			//����ʾ�������µĴ洢�ַ�λ��ʱֹͣ��ʾ
			if(char_idx ==  viewer->disp_cb.store_charIdx||viewer->data_buf[char_idx] == '\0')
				break;
			
			//�����ַ�
			if(is_filterChar(viewer->data_buf[char_idx], filter_buf) && viewer->filterOut_char) {
				char_idx = getNext(viewer, char_idx);
				continue;
			}
			
			if(viewer->data_buf[char_idx] == '\n'){
				row_cnt++;
				col_char_cnt = 0;//�����µ����д�ӡ����������
			}
			else {
				
				//���ƴ����ַ���ӡde����
				if(col_char_cnt >= eachLineCharOffsetNum && col_char_cnt < col_cnt + eachLineCharOffsetNum) {
					
					if(col_char_cnt*viewer->char_w - viewer->txt_ofsetX > -viewer->char_w
						&&col_char_cnt*viewer->char_w < viewer->txt_ofsetX + viewer->window_w) {
						txtViewer_printOneChar(txt_x + viewer->window_x, txt_y + viewer->window_y, &viewer->data_buf[char_idx], 
							viewer->window_x,viewer->window_y, viewer->window_y + viewer->window_h, viewer->window_x + viewer->window_w);
					}
					
				}
				col_char_cnt++;
			}
			
			char_idx = getNext(viewer, char_idx);
			
	}
}


//�Զ����н���ģʽ
static void txtViewer_display_autoBreakLine(txtViewer_t *viewer)
{
	//���㴰��ÿ��Ҫ��ʾ���ַ�����
	u16 col_cnt = viewer->window_w/viewer->char_w;
	//������Ҫ����������
	s16 skipLineNum = viewer->txt_ofsetY/viewer->char_h;
	//��ȡ���ڵĵ�һ�еĵ�һ���ַ��ȽϺķ�����
	u16 char_idx = getFirstLineIdx_autoBreakLine(viewer,skipLineNum,col_cnt);
	
	//���㴰��ÿ��Ҫ��ʾ���ַ�����
	u16 line_cnt = viewer->window_h/viewer->char_h+1;
	
	//�д�ӡ������//�д�ӡ������
	u16 row_cnt = 0, col_char_cnt = 0;
	
	u16 total_line = getTotalLine(viewer,col_cnt);
	//�����������
	viewer->cursor_lineX = calculat_CursorCharcnt(viewer);
	//���ȹ�����
	if(viewer->cursor_enable&&viewer->scroll_enable && viewer->keyboard_mode)
	{
		//y����
		s16 length_y = viewer->char_h * (viewer->cursor_lineY+1);
		if(length_y - viewer->txt_ofsetY > viewer->window_h) {
			if(viewer->scroll_anim)
				viewer->txt_ofsetY+=Dynamic_Aim_SpeedForWindow(viewer,1,viewer->char_h,length_y - viewer->txt_ofsetY - viewer->window_h);
			else
				viewer->txt_ofsetY=length_y - viewer->window_h;
		}
		if(viewer->cursor_lineY * viewer->char_h < viewer->txt_ofsetY) {
			if(viewer->scroll_anim)
				viewer->txt_ofsetY-=Dynamic_Aim_SpeedForWindow(viewer,1,viewer->char_h,viewer->txt_ofsetY - (viewer->cursor_lineY* viewer->char_h));
			else
				viewer->txt_ofsetY=viewer->txt_ofsetY - viewer->char_h;
		}
		length_y = viewer->char_h * total_line;
		//��ӡʱʼ�ձ������һ���������棬��ֹ���иı�ʱ���廭�����ƣ�����м���ת�������룬�����׶�ʧ�ӽ�
		if(length_y - viewer->txt_ofsetY < viewer->window_h)
			viewer->txt_ofsetY = length_y - viewer->window_h;
	}
	//���ڸ����ַ���ӡ
	else if(viewer->scroll_enable)
	{
		s16 length_y = viewer->char_h * total_line;
		if(length_y - viewer->txt_ofsetY > viewer->window_h) {
			if(viewer->scroll_anim)
				viewer->txt_ofsetY+=Dynamic_Aim_SpeedForWindow(viewer,1,viewer->char_h,length_y - viewer->txt_ofsetY - viewer->window_h);
			else
				viewer->txt_ofsetY=length_y - viewer->window_h;
		}
		//��ӡʱʼ�ձ������һ���������棬��ֹ���иı�ʱ���廭�����ƣ�����м���ת�������룬�����׶�ʧ�ӽ�
		if(length_y - viewer->txt_ofsetY < viewer->window_h)
			viewer->txt_ofsetY = length_y - viewer->window_h;
	}
	
	char buff[4];
	sprintf_P(buff, PSTR("%d"), viewer->cursor_lineX);
	draw_string(buff, NOINVERT, 110, FRAME_HEIGHT - 8);
	sprintf_P(buff, PSTR("%d"), viewer->cursor_lineY);
	draw_string(buff, NOINVERT, 110, FRAME_HEIGHT - 16);
	
	//���ƴ����ַ�������ӡ
	while(row_cnt < line_cnt) {
		
		s16 txt_x;
		s16 txt_y;
		//����ÿһ���ַ��������У��������������ӡ����
			
			//��ӡ���
			txt_x = (col_char_cnt)*viewer->char_w;
			txt_y = (row_cnt + (skipLineNum > 0? skipLineNum:0))*viewer->char_h - viewer->txt_ofsetY;
			if(viewer->cursor_enable) {
				static millis8_t lastUpdate;
				millis8_t now = millis();
				if ((millis8_t)(now - lastUpdate) >= 1000)
					lastUpdate = now;
				if ((millis8_t)(now - lastUpdate) < 500) {
					
					if(char_idx == viewer->disp_cb.cursor_idx ) {
						txtViewer_printCursor(txt_x + viewer->window_x, txt_y + viewer->window_y, 
								viewer->window_x,viewer->window_y, viewer->window_y + viewer->window_h, viewer->window_x + viewer->window_w);
					}
				}
				
			}
			//����ʾ�������µĴ洢�ַ�λ��ʱֹͣ��ʾ
			if(char_idx ==  viewer->disp_cb.store_charIdx||viewer->data_buf[char_idx] == '\0')
				break;
			
			//�����ַ�
			if(is_filterChar(viewer->data_buf[char_idx], filter_buf) && viewer->filterOut_char) {
				char_idx = getNext(viewer, char_idx);
				continue;
			}

			if(viewer->data_buf[char_idx] == '\n'){
				row_cnt++;
				col_char_cnt = 0;//�����µ����д�ӡ����������
			}
			else {
				//���ƴ����ַ���ӡde����
				if(col_char_cnt >= col_cnt) {
					row_cnt++;
					col_char_cnt = 0;
				}
					
				 txt_x = (col_char_cnt)*viewer->char_w;
				 txt_y = (row_cnt + (skipLineNum > 0? skipLineNum:0))*viewer->char_h - viewer->txt_ofsetY;
				
				
				txtViewer_printOneChar(txt_x + viewer->window_x, txt_y + viewer->window_y, &viewer->data_buf[char_idx], 
							viewer->window_x,viewer->window_y, viewer->window_y + viewer->window_h, viewer->window_x + viewer->window_w);
				
				col_char_cnt++;
			}
			
			char_idx = getNext(viewer, char_idx);
				
			
	}
}

//�ն��������ģʽ console print mode
static void txtViewer_console_print(txtViewer_t *viewer)
{
	//���㴰��ÿ��Ҫ��ʾ���ַ�����
	u16 col_cnt = viewer->window_w/viewer->char_w;
	//���㵱ǰ���������ȽϺķ�����
	u8 total_line = getTotalLine(viewer, col_cnt);
	//���㴰��ÿ��Ҫ��ʾ���ַ�����//9
	u16 line_cnt = viewer->window_h/viewer->char_h+1;
	//��ʷ����СΪһ�У���Ϊ���γ�һ���ַ�˲�䣬��������ƫ��һ���ַ��߶ȣ��������ʾһ����ʷ�оͻ��пն�����
	u16 history_line = viewer->scroll_pixel/viewer->char_h + 1;
	s16 skipLineNum = total_line - line_cnt + 1 - history_line;
	//��ȡ���ڵĵ�һ�еĵ�һ���ַ�
	u16 char_idx = getFirstLineIdx_autoBreakLine(viewer, skipLineNum, col_cnt);
	
	//�д�ӡ������//�д�ӡ������
	u16 row_cnt = 0, col_char_cnt = 0;
	
	//����������ƫ��
	if(viewer->scroll_pixel > 0 && viewer->scroll_pixel > (total_line - line_cnt + 1)*viewer->char_h)
		viewer->scroll_pixel = (total_line - line_cnt + 1)*viewer->char_h;
	
	//������С�ڴ�����������ӡ����Ҫ�����Ĵ���ֱ�Ӵ�ӡ
	if(total_line  <= line_cnt-1) {
		viewer->scroll_pixel = 0;
		history_line = 0;
		//total_line = 8ʱskipLineNum=-1����ʱ��Ӧ��ƫ�ƣ����ֱ����ʾ
		skipLineNum = 0;
	}
	
	
	if(viewer->scroll_anim) {
		if(viewer->scroll_enable)
		if(viewer->scroll_pixel > 0)
			viewer->scroll_pixel -= txtViewer_Dynamic_Aim_Speed(viewer, 1);
	} else {
		if(viewer->scroll_enable)
			viewer->scroll_pixel = 0;
	}
	
	
	
	
	char buff[4];
	sprintf_P(buff, PSTR("%d"), total_line);
	draw_string(buff, NOINVERT, 110, FRAME_HEIGHT - 8);
	sprintf_P(buff, PSTR("%d"), viewer->processd_cnt);
	draw_string(buff, NOINVERT, 110, FRAME_HEIGHT - 16);
	
	//���ƴ����ַ�������ӡ
	//��ʾ�����ڴ����и߶�+2��
	while(row_cnt < line_cnt+1) {
		s16 txt_x;
		s16 txt_y;
		
			//��ӡ���
			txt_x = (col_char_cnt)*viewer->char_w;
			txt_y = (row_cnt - history_line)*viewer->char_h + viewer->scroll_pixel + (skipLineNum == -1 ? viewer->char_h:0);
			if(viewer->cursor_enable) {
				static millis8_t lastUpdate;
				millis8_t now = millis();
				if ((millis8_t)(now - lastUpdate) >= 1000)
					lastUpdate = now;
				if ((millis8_t)(now - lastUpdate) < 500) {
					
					if(char_idx == viewer->disp_cb.cursor_idx ) {
						txtViewer_printCursor(txt_x + viewer->window_x, txt_y + viewer->window_y, 
								viewer->window_x,viewer->window_y, viewer->window_y + viewer->window_h, viewer->window_x + viewer->window_w);
					}
				}
				
			}
			//����ʾ�������µĴ洢�ַ�λ��ʱֹͣ��ʾ
			if(char_idx ==  viewer->disp_cb.store_charIdx||viewer->data_buf[char_idx] == '\0')
				break;
			
			//�����ַ�
			if(is_filterChar(viewer->data_buf[char_idx], filter_buf) && viewer->filterOut_char) {
				char_idx = getNext(viewer, char_idx);
				continue;
			}
				
			//����ÿһ���ַ��������У��������������ӡ����
			if(viewer->data_buf[char_idx] == '\n'){
				row_cnt++;
				col_char_cnt = 0;//�����µ����д�ӡ����������
			}
			else {
				//���ƴ����ַ���ӡde����
				if(col_char_cnt >= col_cnt) {
					row_cnt++;
					col_char_cnt = 0;
				}
				txt_x = (col_char_cnt)*viewer->char_w;
				//skipLineNum == -1 ��һ�������������ʱ��ʷ���Ҳ����ˣ���������ĵ�һ���ˣ���������ƫ��ʱ��һ����ʾ���ǵڶ��У���һ����ʾ���ǵ�һ��Ӧ���ֲ�
				txt_y = (row_cnt - history_line)*viewer->char_h + viewer->scroll_pixel + (skipLineNum == -1 ? viewer->char_h:0);
				
				
				txtViewer_printOneChar(txt_x + viewer->window_x, txt_y + viewer->window_y, &viewer->data_buf[char_idx], 
							viewer->window_x,viewer->window_y, viewer->window_y + viewer->window_h, viewer->window_x + viewer->window_w);
				
				col_char_cnt++;
			}
			char_idx = getNext(viewer, char_idx);
			
	}

	cmd_parser.run(&cmd_parser);
}



void txtViewer_drawBoundary(txtViewer_t *viewer)
{
	myOLED_DrawLine(viewer->window_x, viewer->window_y, viewer->window_x+viewer->window_w, viewer->window_y,true);
	myOLED_DrawLine(viewer->window_x+viewer->window_w, viewer->window_y, viewer->window_x+viewer->window_w, viewer->window_y+viewer->window_h,true);
	myOLED_DrawLine(viewer->window_x, viewer->window_y+viewer->window_h, viewer->window_x+viewer->window_w, viewer->window_y+viewer->window_h,true);
	
	
	myOLED_DrawLine(viewer->window_x, viewer->window_y, viewer->window_x, viewer->window_y+viewer->window_h,true);
}





static char * operator_buf = "\b";
static u8 is_operator(txtViewer_t *viewer)
{
	char *opt_buf = operator_buf;
	while(*opt_buf != '\0')
	{
		if(viewer->getchar == *opt_buf++)
			return true;
	}
	return false;
}

//ִ�в�������Ӧ�Ĳ���
void txtViewer_do_operator(txtViewer_t *viewer)
{
	//�˸�
	if(viewer->getchar == '\b') {
		if(viewer->keyboard_mode) {
			txtViewer_CursorDeleteChar(viewer);
		}
		else {
			//�ڽ�β��ɾ���ַ�
			viewer->disp_cb.cursor_idx = viewer->disp_cb.store_charIdx;
			txtViewer_CursorDeleteChar(viewer);
		}
	}
}

static void txtViewer_run(txtViewer_t *viewer)
{
	if(viewer->input_updata)
	{
		viewer->input_updata = false;
		if(is_operator(viewer)) {
			txtViewer_do_operator(viewer);
		} else {
			//ʹ�ܹ�꣬��괦�����ַ�
			if(viewer->cursor_enable)
				txtViewer_CursorAddChar(viewer,viewer->getchar);
			//�����ڽ�β�������ַ�
			else
				txtViewer_printf(viewer, "%c",viewer->getchar);
		}
		
	}
	txtViewer.process(&txtViewer);
	if(viewer->win_boundary) {
		txtViewer_drawBoundary(&txtViewer); 
	}
}

txtViewer_t txtViewer;


//////////////////////////////////////////////// ���ڿ���API //////////////////////////////////////////////////
static bool scroll_down()
{
	txtViewer.txt_ofsetY++;
	return false;
}

static bool scroll_up()
{
	txtViewer.txt_ofsetY--;
	return false;
}

static bool scroll_left()
{
	txtViewer.txt_ofsetX--;
	return false;
}

static bool scroll_right()
{
	txtViewer.txt_ofsetX++;
	return false;
}

static bool win_up()
{
	txtViewer.window_y--;
	return false;
}
static bool win_down()
{
	txtViewer.window_y++;
	return false;
}
static bool win_left()
{
	txtViewer.window_x--;
	return false;
}
static bool win_right()
{
	txtViewer.window_x++;
	return false;
}

static bool cur_down()
{
	cursor_down(&txtViewer);
	return true;
}

static bool cur_up()
{
	cursor_up(&txtViewer);
	return true;
}

static bool cur_L()
{
	cursor_left(&txtViewer);
	return true;
}

static bool cur_R()
{
	cursor_right(&txtViewer);
	return true;
}

static bool cur_del()
{
	txtViewer_CursorDeleteChar(&txtViewer);
	return true;
}

static bool cur_add()
{
	static u8 i=0;
	txtViewer_CursorAddChar(&txtViewer,++i%10+'0');
	return true;
}

///////////////////////////////////////////// �ַ��������� //////////////////////////////////////////////
extern bool keep_on;
extern unsigned char cmd_finish;
static void txtViewer_meun_open(void);
static display_t draw(void);
static button_f btndown = scroll_down;
static button_f btnup = scroll_up;

static bool btnExit()
{
	//free(txtViewer.data_buf);
	animation_start(txtViewer_meun_open, ANIM_MOVE_OFF);
	return true;
}

void txt_test_open(void)
{
	buttons_setFuncs(btndown, btnExit, btnup );
	beginAnimation2(NULL);
	if(txtViewer.data_buf == NULL)
	{
		txtViewer_init(&txtViewer,1024,0,0,NORMAL);
	}
	txtViewer.loop_show = true;
	display_setDrawFunc(draw);
	keep_on = true;
	cmd_finish=1;
}

static display_t draw()
{

	txtViewer.run(&txtViewer);
	
	return DISPLAY_BUSY;
}

//////////////////////////////////////////////// TXT_Viewer �˵�ѡ�� ///////////////////////////////////////////////
static prev_menu_s prevMenuData;
static void itemLoader(byte num);
static void mSelect(void);

static void txtViewer_meun_open(void)
{
	menuData.isOpen = true;  //�򿪲˵�
	setPrevMenuOpen(&prevMenuData, txtViewer_meun_open);//��ν�������˵����ϼ��˵�Ҳ���ᱻ����
	buttons_setFuncs(menu_up, menu_select, menu_down);
	display_setDrawFunc(menu_draw);  //�󶨻��ƺ���Ϊmenu_draw
	setMenuInfo(24, MENU_TYPE_STR, PSTR("Viewer"));   //��ȡ��ǰ�˵���Ϣ��ѡ��������˵����������ֻ���ͼ�꣩
	setMenuFuncs(MENUFUNC_NEXT, mSelect, MENUFUNC_PREV, itemLoader);  //�󶨲˵��ĺ���,��ǰ������ѡ��ȷ��    
	beginAnimation2(NULL);
}

static void mSelect(void)
{
	setPrevMenuExit(&prevMenuData);//�洢�ϴβ˵���ѡ��
	doAction(true);  //���˳�����ִ��ָ��
	menuData.isOpen = false;
}
void up_down()
{
	txtViewer.scroll_enable=false;
	btndown = scroll_down;
	btnup = scroll_up;
	txt_test_open();
}
void left_right()
{
	txtViewer.scroll_enable=false;
	btndown = scroll_left;
	btnup = scroll_right;txt_test_open();
}
void win_upDown()
{
	btndown = win_down;
	btnup = win_up;txt_test_open();
}
void win_leftRight()
{
	btndown = win_left;
	btnup = win_right;txt_test_open();
}
void size48x64()
{
	txtViewer_setWindow(&txtViewer, 48,64);txt_test_open();
}

void size48x96()
{
	txtViewer_setWindow(&txtViewer, 48,96);txt_test_open();
}

void size32x64()
{
	txtViewer_setWindow(&txtViewer, 32,64);txt_test_open();
}
void sizefull()
{
	txtViewer_setWindow(&txtViewer, 64,128);txt_test_open();
	txtViewer.window_x = 0;
	txtViewer.window_y = 0;
}

static u8 i=0;
bool p_down()
{
	txtViewer_printf(&txtViewer, "%d\r",i++);
	return true;
}
bool p_downln()
{
	
	txtViewer_printf(&txtViewer, "hel\rlo\r%d\n",i++);
	return true;
}

bool p_up()
{
	txtViewer.scroll_enable = false;
	txtViewer.scroll_pixel++;
	return false;
}
void p_test()
{
	txtViewer_changeProcessMode(&txtViewer,CONSOLE_PRINT);
	btndown = p_down;
	btnup = p_up;
	txt_test_open();
}

void p_testln()
{
	txtViewer_changeProcessMode(&txtViewer,CONSOLE_PRINT);
	btndown = p_downln;
	btnup = p_up;
	txt_test_open();
}


void normal_print()
{
	txtViewer_changeProcessMode(&txtViewer,NORMAL);
	btndown = p_downln;
	btnup = p_down;
	txt_test_open();
}

void autobrk_print()
{
	txtViewer_changeProcessMode(&txtViewer,AUTO_BREAKLINE);
	btndown = p_downln;
	btnup = p_down;
	txt_test_open();
}

void normal()
{
	txtViewer_changeProcessMode(&txtViewer,NORMAL);
	up_down();
}

void autobrk()
{
	txtViewer_changeProcessMode(&txtViewer,AUTO_BREAKLINE);
	up_down();
}

void clear_buf()
{
	i=0;
	txt_test_open();
	txtViewer_clearDataBuf(&txtViewer);
}

void backto()
{
	//free(txtViewer.data_buf);
	wifi_test_open();
}

void flter_lr()
{
	setFilterOut(&txtViewer);
	txt_test_open();
}

void kbd_mode()
{
	txtViewer.keyboard_mode = !txtViewer.keyboard_mode;
	txt_test_open();
}

void scroll_anim()
{
	txtViewer.scroll_anim = !txtViewer.scroll_anim;
	txt_test_open();
}

void cursor_updown()
{
	btndown = cur_down;
	btnup = cur_up;
	txt_test_open();
}

void cursor_LR()
{
	btndown = cur_R;
	btnup = cur_L;
	txt_test_open();
}

void cursor_add()
{
	btndown = cur_del;
	btnup = cur_add;
	txt_test_open();
}

static u8 j=0;
bool cmd_ps()
{
	
	switch(j)
	{
		case 0: cmd_getChar(&cmd_parser, 'p');break;
		case 1: cmd_getChar(&cmd_parser, 's');break;
		case 2: cmd_getChar(&cmd_parser, ' ');break;
		case 3: cmd_getChar(&cmd_parser, '1');break;
		case 4: cmd_getChar(&cmd_parser, '2');break;
		case 5: cmd_getChar(&cmd_parser, ' ');break;
		case 6: cmd_getChar(&cmd_parser, '1');break;
		case 7: cmd_getChar(&cmd_parser, '3');break;
		default:break;
	}
	j++;
	return true;
}
bool cmd_go()
{
	j=0;
	cmd_getChar(&cmd_parser, '\n');
	return true;
}



bool cmd_add()
{
	cmd_getChar(&cmd_parser, j++%10 +'0');
	return true;
}
bool cmd_del()
{
	
	cmd_getChar(&cmd_parser, '\b');
	return true;
}


void cmdtest()
{
	txtViewer_changeProcessMode(&txtViewer,CONSOLE_PRINT);
	//txtViewer.keyboard_mode = true;
	txtViewer.cmd_mode = true;
	cmd_Parser_Start(&cmd_parser);


	btndown = cmd_go;
	btnup = cmd_ps;
	txt_test_open();
}

void cmdtest2()
{
	
	txtViewer_changeProcessMode(&txtViewer,CONSOLE_PRINT);
	//txtViewer.keyboard_mode = true;
	txtViewer.cmd_mode = true;
	cmd_Parser_Start(&cmd_parser);

	btndown = cmd_add;
	btnup = cmd_del;
	txt_test_open();
}

bool cmd_ps2()
{
	
	switch(j)
	{
		case 0: cmd_getChar(&cmd_parser, 'p');break;
		case 1: cmd_getChar(&cmd_parser, 's');break;
		case 2: cmd_getChar(&cmd_parser, ' ');break;
		case 3: cmd_getChar(&cmd_parser, '&');break;
		case 4: cmd_getChar(&cmd_parser, '\n');break;
		default:break;
	}
	j++;
	if(j ==5)
		j=0;
	return true;
}

bool cmd_kill()
{
	
	switch(j)
	{
		case 0: cmd_getChar(&cmd_parser, 'k');break;
		case 1: cmd_getChar(&cmd_parser, 'i');break;
		case 2: cmd_getChar(&cmd_parser, 'l');break;
		case 3: cmd_getChar(&cmd_parser, 'l');break;
		case 4: cmd_getChar(&cmd_parser, ' ');break;
		case 5: cmd_getChar(&cmd_parser, '1');break;
		case 6: cmd_getChar(&cmd_parser, '\n');break;
		default:break;
	}
	j++;
	if(j ==7)
		j=0;
	return true;
}
void cmdtest3()
{
	j=0;
	txtViewer_changeProcessMode(&txtViewer,CONSOLE_PRINT);
	//txtViewer.keyboard_mode = true;
	txtViewer.cmd_mode = true;
	cmd_Parser_Start(&cmd_parser);

	btndown = cmd_kill;
	btnup =  cmd_ps2;
	txt_test_open();
}

static void itemLoader(byte num)
{
	num = 0;
	setMenuOption_P(num++, PSTR("up down"), NULL, up_down);
	setMenuOption_P(num++, PSTR("left right"), NULL, left_right);
	setMenuOption_P(num++, PSTR("win up down"), NULL, win_upDown);
	setMenuOption_P(num++, PSTR("win left right"), NULL, win_leftRight);
	setMenuOption_P(num++, PSTR("filt lr"), NULL, flter_lr);
	setMenuOption_P(num++, PSTR("kbd md"), NULL, kbd_mode);
	setMenuOption_P(num++, PSTR("win 48x64"), NULL, size48x64);
	setMenuOption_P(num++, PSTR("win 32x64"), NULL, size32x64);
	setMenuOption_P(num++, PSTR("win 48x96"), NULL, size48x96);
	setMenuOption_P(num++, PSTR("win full"), NULL, sizefull);
	setMenuOption_P(num++, PSTR("clear"), NULL, clear_buf);
	setMenuOption_P(num++, PSTR("normal"), NULL, normal);
	setMenuOption_P(num++, PSTR("nor_print"), NULL, normal_print);
	setMenuOption_P(num++, PSTR("autobrk"), NULL, autobrk);
	setMenuOption_P(num++, PSTR("aut_print"), NULL, autobrk_print);
	setMenuOption_P(num++, PSTR("csl_print"), NULL, p_test);
	setMenuOption_P(num++, PSTR("csl_println"), NULL, p_testln);
	setMenuOption_P(num++, PSTR("anim"), NULL, scroll_anim);
	setMenuOption_P(num++, PSTR("curUD"), NULL, cursor_updown);
	setMenuOption_P(num++, PSTR("curLR"), NULL, cursor_LR);
	setMenuOption_P(num++, PSTR("curadd"), NULL, cursor_add);
	setMenuOption_P(num++, PSTR("CMD"), NULL, cmdtest);
	setMenuOption_P(num++, PSTR("CMDw"), NULL, cmdtest2);
	setMenuOption_P(num++, PSTR("ps_kill"), NULL, cmdtest3);
	setMenuOption_P(num++, PSTR("back"), NULL, backto);
}

